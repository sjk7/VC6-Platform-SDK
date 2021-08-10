// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      sender.cpp
//
// Abstract:
//      Implement send-side functionality.  The sender uses a combination of
//      WSASend and WSAEventSelect to support sending of either TCP or UDP data 
//      and receive notification of QOS activity on the socket.  Additionally,
//      data may be sent to a multicast group with or without QOS.  Note that 
//      when a Class D address (multicast group address) is used (by -n:Group-IP), 
//      the program will automatically treat that as a multicast socket (as if
//      the -m option was used). For a complete list of valid multicast 
//      addresses consult RFC1112 and RFC1700.
//
//      The template used when enabling QOS is specified with the commandline 
//      option -q:template.  A value of default for template will result in default 
//      values being entered for sending and receiving flowspec (see FillQos).  
//      Otherwise the specified template is used (again see FillQos).
//
//      QOS can be enabled in the sender in the following manner
//      -i:b    before WSAConnect/WSAJoinLeaf on the sending socket using WSAIoctl
//      -i:d    during WSAConnect/WSAJoinLeaf using the lpSQos parameter of WSAConnect
//      -i:a    after WSAConnect/WSAJoinLeaf on the sending socket using WSAIoctl
//      For non-multicast UDP QOS tranfers there is no API that gets called 
//      prior to initiating the data transfers, therefore QOS is 
//      set prior to the data transfers (i.e. -i:b).
//  
//      A QOS-enabled application should always check whether it is ok to start
//      data transfers before receipt of a RESV from the receiver.  
//
// Entry Points:
//      Sender - send contents of data buffer to receiver program.
//
// Author:
//      Barry R. Butterklee

#include "qosevent.h"


#define WSAEVENTSELECT_EVENT 0
#define WSASEND_EVENT 1
#define TOTAL_EVENTS 2


// encapsulate socket, events, buffers, and various flags and counters that
// control how/when data is sent into a structure
typedef struct _SEND_INFO
{
    SOCKET          sd;             
    WSAEVENT        hEvents[TOTAL_EVENTS];     // WSASend and WSAEventSelect
                                               // events
    WSAOVERLAPPED   ovr;
    BOOL            bSendEnabled;
    BOOL            bSendComplete;
    int             nTotalSends;
    WSABUF          sndbuf;
} SEND_INFO;



static BOOL CreateSendingSocket(SEND_INFO *, OPTIONS *, WSAPROTOCOL_INFO *);
static BOOL fd_connect_func(DWORD, WSANETWORKEVENTS *, SEND_INFO *, OPTIONS *);
static BOOL fd_qos_func(DWORD, WSANETWORKEVENTS *, SEND_INFO *, OPTIONS *);
static BOOL fd_close_func(DWORD, WSANETWORKEVENTS *, SEND_INFO *);
static BOOL PostSend(SEND_INFO *, OPTIONS *);
static BOOL CompleteSend(SEND_INFO *, OPTIONS *);




// Abstract:
//      Main function to establish connection (if using TCP) to server and then 
//      send data to server.  WSASend and WSAEventSelect are used to send data 
//      and monitor socket activity, respectively.  
//      
//      Due to the nature of this application - just sending data in a loop - 
//      FD_WRITE is not suitable whereas using WSASend with overlapped I/O is.  
//      The reason is because FD_WRITE will only be delivered after the inital 
//      connection has been established and only after sends block would 
//      WSAEWOULDBLOCK and buffer space becomes available once again.  Thus 
//      WSAWaitForMultipleEvents waits on the event associated with overlapped 
//      structure passed to WSASend AND the event associated with 
//      WSAEventSelect.
//
VOID Sender(
    OPTIONS             *pOptions, 
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
{
    WSANETWORKEVENTS    NetworkEvents;
    BOOL                bProcessEventsDone;
    SEND_INFO           SendInfo;
    int                 i;
    BOOL                bDisableQos = TRUE;
    BOOL                bErr;

    printf("Sender\n");
    
    //Initialize SEND_INFO
    ZeroMemory((char *)&SendInfo,sizeof(SendInfo));      
    for (i=0; i<TOTAL_EVENTS; i++)
    {
        SendInfo.hEvents[i] = WSACreateEvent();
        if (WSA_INVALID_EVENT == SendInfo.hEvents[i])
        {
            printf("WSACreateEvent(%d): %d\n", i, WSAGetLastError());
            goto CLEANUP;
        }
    }
    
    SendInfo.sd           = INVALID_SOCKET;
    SendInfo.ovr.hEvent   = SendInfo.hEvents[WSASEND_EVENT];
    SendInfo.sndbuf.buf   = pOptions->buf;
    SendInfo.sndbuf.len   = pOptions->nBufSize;
    SendInfo.nTotalSends  = 0;

    // Should we be able to send yet?
    if (!pOptions->spOptions.bQos)
        SendInfo.bSendEnabled = TRUE;
    else
        SendInfo.bSendEnabled = !pOptions->qosOptions.bWaitToSend;

    bErr = CreateSendingSocket(&SendInfo, pOptions, pProtocolInfo);

    if (!bErr)
        goto CLEANUP;

    // If we are using UDP.  
    if (IPPROTO_UDP == pOptions->spOptions.iProtocol)
        //
        // Post the first send.
        if (PostSend(&SendInfo, pOptions))
            goto CLEANUP;

    bProcessEventsDone = FALSE;
    do
    {
        DWORD dwEvent = WSAWaitForMultipleEvents(TOTAL_EVENTS, SendInfo.hEvents, 
                                                    FALSE, WSA_INFINITE, FALSE);
        switch (dwEvent)
        {
        case WSA_WAIT_FAILED:
            printf("WSAEventSelect: %d\n", WSAGetLastError());
            goto CLEANUP;
            
        case WAIT_IO_COMPLETION:
        case WSA_WAIT_TIMEOUT:
            _assume(0);
            break;

        default:
            dwEvent -= WSA_WAIT_EVENT_0;

            if (WSAEVENTSELECT_EVENT != dwEvent) {
                bProcessEventsDone = CompleteSend(&SendInfo, pOptions);
                break;
            }
            
            // lets see what network activity trigged this event
            if (SOCKET_ERROR == WSAEnumNetworkEvents(
                                    SendInfo.sd, 
                                    SendInfo.hEvents[WSAEVENTSELECT_EVENT], 
                                    &NetworkEvents))
            {
                printf("WSAEnumNetworkEvent: %d lNetworkEvent %X\n", 
                    WSAGetLastError(), NetworkEvents.lNetworkEvents);
                NetworkEvents.lNetworkEvents = 0;
                break;
            }
            
            if (FD_CONNECT & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_connect_func(dwEvent, 
                                                      &NetworkEvents, 
                                                      &SendInfo, 
                                                      pOptions);
            
            if (FD_QOS     & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_qos_func(dwEvent, 
                                                  &NetworkEvents, 
                                                  &SendInfo, 
                                                  pOptions);
            
            if (FD_CLOSE   & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_close_func(dwEvent, 
                                                    &NetworkEvents, 
                                                    &SendInfo);
        }

        // allow pauses between notifications
        if (pOptions->dwSleep)
            Sleep(pOptions->dwSleep);

        // alternate every N sends enabling or disabling QOS on a socket
        if (    pOptions->spOptions.bQos 
            &&  pOptions->qosOptions.bAlternateQos
            &&  ((SendInfo.nTotalSends % 5) == 0) )
        {           
            QOS     qos;
            DWORD   dwBytes, cbQosLen;
            int     nRet;

            if (bDisableQos)
            {
                bDisableQos = FALSE;

                qos.ReceivingFlowspec    = default_notraffic;
                qos.SendingFlowspec      = default_notraffic;
                qos.ProviderSpecific.buf = NULL;
                qos.ProviderSpecific.len = 0;

                cbQosLen = sizeof(QOS) + qos.ProviderSpecific.len;

                nRet = WSAIoctl(SendInfo.sd, SIO_SET_QOS, (LPVOID)&qos, 
                                    cbQosLen, NULL, 0, &dwBytes, NULL, NULL);
                
                if (SOCKET_ERROR == nRet)
                    printf("WSAIoctl:SIO_SET_QOS %d\n", WSAGetLastError());

                SendInfo.bSendEnabled = TRUE;
            } 
            else 
            {
                bDisableQos = TRUE;

                SetQos(SendInfo.sd, &pOptions->qosOptions, TRUE, 
                        &qos, &cbQosLen);

                // sender should not send data until RESV arrives for this new
                // PATH msg if -rsvp-wait flag is specified.
                SendInfo.bSendEnabled = !pOptions->qosOptions.bWaitToSend;
            }
            
            printf("	bSendEnabled = %s\n", (
                        SendInfo.bSendEnabled?"TRUE":"FALSE"));

        }
    } while (!bProcessEventsDone);


CLEANUP:
    if (    (INVALID_SOCKET != SendInfo.sd) 
        &&  (NULL != SendInfo.sd))
        closesocket(SendInfo.sd);
    
    for (i=0; i<TOTAL_EVENTS; i++)
        if (    (WSA_INVALID_EVENT != SendInfo.hEvents[i]) 
            &&  (NULL != SendInfo.hEvents[i]))
            WSACloseEvent(SendInfo.hEvents[i]);

}


// Abstract:
//      Create a socket on which to send data.  Also, please 
//      note that WSA_FLAG_OVERLAPPED *MUST* be specified.  Also, note that 
//      the parameters for WSASocket and the data to fill in the SOCKADDR_IN 
//      structure come from the supplied protocol info structure instead of 
//      being hardcoded.
//
//      The socket can be made into a QOS socket either before, during, or  
//      after WSAConnect has been called.
//
static BOOL CreateSendingSocket(
    SEND_INFO           *pSendInfo, 
    OPTIONS             *pOptions, 
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
{
    DWORD       dwSocketFlags;
    QOS         qos;
    QOS         *pQos;
    long        lNetworkEvents;
    int         nRet;
    DWORD       cbQosLen;

    // set up the address structure of the destination which is needed on  
    // connect and/or sendto operations.
    ZeroMemory((PVOID)&g_destaddr, sizeof(g_destaddr));
    g_destaddr.sin_family = (USHORT) pProtocolInfo->iAddressFamily;
    g_destaddr.sin_port = htons(pOptions->port);
    g_destaddr.sin_addr.s_addr = inet_addr(pOptions->szHostname);
    
    if (INADDR_NONE == g_destaddr.sin_addr.s_addr)
    {
        struct addrinfo hints, *ai; 
        LPSOCKADDR_IN   in_ai; 

        memset(&hints, 0, sizeof(hints));
        hints.ai_family   = PF_INET;
        hints.ai_socktype = (IPPROTO_UDP == pOptions->spOptions.iProtocol) ? 
                                SOCK_DGRAM : SOCK_STREAM;
        
        // the host name for the server is not in dot format, 
        // try it as a string
        nRet = getaddrinfo(pOptions->szHostname, NULL, &hints, &ai);
        if (nRet != 0) 
        {
            printf("getaddrinfo %d for %s", WSAGetLastError(), 
                    pOptions->szHostname);
            return(FALSE);
        }

        in_ai = (LPSOCKADDR_IN) ai->ai_addr;
        g_destaddr.sin_addr = in_ai->sin_addr;      
        freeaddrinfo(ai);
    }

    // Test if the destination address is multi-cast by looking at the
    // first byte of the ip address to start with 1110 for Class D.
    if ((g_destaddr.sin_addr.S_un.S_addr & 0xF0) == 0xE0)
    {
        // Treat this as though -m option has been given
        pOptions->spOptions.bMulticast = TRUE;
        pOptions->qosOptions.bSetDestaddr = FALSE;
    }

    dwSocketFlags = WSA_FLAG_OVERLAPPED;

    // For a socket to join a multicast group you must specify whether you are
    // acting as a root or leaf in the control and data planes. IP multicasting
    // only supports leaves in both control and data planes.
    if (pOptions->spOptions.bMulticast)
        dwSocketFlags |= (WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF);

    pSendInfo->sd = WSASocket(FROM_PROTOCOL_INFO, 
                              FROM_PROTOCOL_INFO, 
                              FROM_PROTOCOL_INFO, 
                              pProtocolInfo, 
                              0, 
                              dwSocketFlags);             
    
    if (INVALID_SOCKET == pSendInfo->sd)
    {
        printf("socket %d", WSAGetLastError());
        return(FALSE);
    }

    // When using UDP (not multicast) and QOS, the sending socket must be bound
    // for QOS to work. 
    if (    (IPPROTO_UDP == pOptions->spOptions.iProtocol)
         && (pOptions->spOptions.bQos)  
         && (!pOptions->spOptions.bMulticast))
    {
        SOCKADDR_IN srcaddr;

        ZeroMemory((PVOID)&srcaddr, sizeof(srcaddr));
        srcaddr.sin_family      = (USHORT) pProtocolInfo->iAddressFamily;
        srcaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        srcaddr.sin_port        = 0;
        
        nRet = bind(pSendInfo->sd, (LPSOCKADDR)&srcaddr, sizeof(srcaddr));

        if (SOCKET_ERROR == nRet)
        {
            printf("bind %d", WSAGetLastError());
            return(FALSE);
        }
    }

    // If needed do a SetQos, or flll out the pQos structure for the connect
    if (pOptions->spOptions.bQos)
    {
        switch (pOptions->qosOptions.qosIoctlSet) 
        {
        case QOS_IOCTL_SET_BEFORE:
            if (SetQos(pSendInfo->sd, &pOptions->qosOptions, TRUE, &qos, &cbQosLen))
                printf("  QOS set before connect\n");

            pQos = NULL;
            break;
            
        case QOS_IOCTL_SET_DURING:
            if (SetQos(pSendInfo->sd, &pOptions->qosOptions, FALSE, &qos, &cbQosLen))
                pQos = &qos;
            else
                pQos = NULL;

            break;
            
        case QOS_IOCTL_SET_AFTER:
            pQos = NULL;

            break;
        }
    }

    // Set up events to recieve
    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
        lNetworkEvents = FD_CONNECT;
    else
        lNetworkEvents = (FD_QOS|FD_CLOSE);
    
    if (SOCKET_ERROR == WSAEventSelect(
                                pSendInfo->sd, 
                                pSendInfo->hEvents[WSAEVENTSELECT_EVENT], 
                                lNetworkEvents))
    {
        printf("WSAEventSelect: %d\n", WSAGetLastError());
        return(FALSE);
    }


    // Do Connects
    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
    {
        // Tcp Connect
        nRet = WSAConnect(pSendInfo->sd, (LPSOCKADDR)&g_destaddr, 
                            sizeof(g_destaddr), NULL, NULL, pQos, NULL);
        
        if (SOCKET_ERROR == nRet)
        {
            DWORD dwErr = WSAGetLastError();
            if (WSAEWOULDBLOCK != dwErr)
            {
                printf("WSAConnect: %d\n", dwErr);
                return(FALSE);
            }
        }

        // Is it time to do a setqos?
        if (    (pOptions->spOptions.bQos) 
            &&  (QOS_IOCTL_SET_AFTER == pOptions->qosOptions.qosIoctlSet))
        {
            if (SetQos(pSendInfo->sd, &pOptions->qosOptions, 
                        TRUE, &qos, &cbQosLen))
                printf("    QOS set after connect\n");
        }
    } 
    else 
    {    
        // UDP
        
        if (pOptions->spOptions.bMulticast)
        {
            nRet = (int) WSAJoinLeaf(pSendInfo->sd, (LPSOCKADDR)&g_destaddr, 
                                     sizeof(g_destaddr), NULL, NULL, pQos, 
                                     NULL, JL_SENDER_ONLY);
            
            if (INVALID_SOCKET == nRet)
            {
                printf("WSAJoinLeaf: %d\n", WSAGetLastError());
                return(FALSE);
            }
            
            if (    (pOptions->spOptions.bQos) 
                &&  (QOS_IOCTL_SET_AFTER == pOptions->qosOptions.qosIoctlSet))
            {
                if (SetQos(pSendInfo->sd, &pOptions->qosOptions, 
                            TRUE, &qos, &cbQosLen))
                    printf("    QOS set after connect\n");
            }
        } 
        else 
        {
            // for TCP the following happens in the connect handler
            if (!pOptions->spOptions.bQos)
                pSendInfo->bSendEnabled = TRUE;
            else
            {
                if (pOptions->qosOptions.bWaitToSend)
                    pSendInfo->bSendEnabled = FALSE;
                else
                    pSendInfo->bSendEnabled = ChkQosSend(pSendInfo->sd);
            }
            printf("  CreateSendingSocket QOS bSendEnabled = %s\n", 
                    (pSendInfo->bSendEnabled?"TRUE":"FALSE"));
        }
    }

    return(TRUE);
}


// Abstract:
//      FD_CONNECT handler.  This handler is invoked when an asynchronous 
//      connect completes, successfully or otherwise.  After the socket  
//      connects additional notifications will be enabled using WSAEventSelect.
//
//      The connected socket will be made into a QOS socket after connect if 
//      the -i:a option is used.
//
static BOOL fd_connect_func(
    DWORD               dwEvent, 
    WSANETWORKEVENTS    *NetworkEvents, 
    SEND_INFO           *pSendInfo, 
    OPTIONS             *pOptions
    )
{
    int     nRet;
    QOS     qos;
    DWORD   cbQosLen;


    printf("  FD_CONNECT: dwEvent=%d error code =%d\n", 
    dwEvent, NetworkEvents->iErrorCode[FD_CONNECT_BIT]);

    if (NetworkEvents->iErrorCode[FD_CONNECT_BIT] != 0)
        return(TRUE); 

    // SetQos if it's time
    if (    (pOptions->spOptions.bQos) 
        &&  (QOS_IOCTL_SET_AFTER == pOptions->qosOptions.qosIoctlSet)
        &&  SetQos(pSendInfo->sd, &pOptions->qosOptions, TRUE, &qos, &cbQosLen))
            printf("    QOS set after connect\n");

    nRet = WSAEventSelect(pSendInfo->sd, 
                          pSendInfo->hEvents[WSAEVENTSELECT_EVENT], 
                          (FD_QOS|FD_CLOSE));
    
    if (SOCKET_ERROR == nRet)
    {
        printf("WSAEventSelect: %d\n", WSAGetLastError());
        return(FALSE);
    }

    // determine when to start sending data.  If not using QOS then start
    // sending right away.  Also note that the socket must be a QOS socket
    // before we can call use this ioctl, otherwise we would get WSAEINVAL.

    if (!pOptions->spOptions.bQos)
        pSendInfo->bSendEnabled = TRUE;
    else
    {
        if (pOptions->qosOptions.bWaitToSend)
            pSendInfo->bSendEnabled = FALSE;
        else
            pSendInfo->bSendEnabled = ChkQosSend(pSendInfo->sd);
    }        
    
    printf("    bSendEnabled = %s\n", 
                (pSendInfo->bSendEnabled?"TRUE":"FALSE"));

    // potentially post initial send (if we are here we are using TCP)
    if (    !pOptions->spOptions.bQos
        ||  !pOptions->qosOptions.bWaitToSend)
        return(PostSend(pSendInfo, pOptions));

    return(FALSE);
}




// Abstract:
//      FD_QOS handler.  This notification indicates that the GQOSSP wants to 
//      indicate a change in QOS status (i.e. delivery of an RSVP message).  
//      Only a change in QOS will cause FD_QOS notifications to be delivered,
//      periodic RSVP refresh messages will not cause an FD_QOS notification.
//
//      Note that the iErrorCode is not really an errorcode but a status code.  
//
//      Also notice that multiple QOS structures may be queued up per FD_QOS 
//      notification and should be examined.
//
static BOOL fd_qos_func(
    DWORD               dwEvent, 
    WSANETWORKEVENTS    *NetworkEvents, 
    SEND_INFO           *pSendInfo, 
    OPTIONS             *pOptions
    )
{
    printf("  FD_QOS: dwEvent=%d status code =%d\n", 
    dwEvent, NetworkEvents->iErrorCode[FD_QOS_BIT]);

    do
    {
        QOS                 *pQos;
        QOS_OBJECT_HDR      *pObjectHdr;
        RSVP_STATUS_INFO    *pRsvpStatus;

        if (!GetQos(pSendInfo->sd, pOptions->qosOptions.bQueryBufferSize, &pQos))
            break;

        PrintQos(pQos, "    ");

        pObjectHdr  = (QOS_OBJECT_HDR *) pQos->ProviderSpecific.buf;
        
        if (RSVP_OBJECT_STATUS_INFO != pObjectHdr->ObjectType)
        {
            printf("FD_QOS: not rsvp_object_status_info\n");
            free(pQos);
            break;
        }

        pRsvpStatus = (RSVP_STATUS_INFO *) pObjectHdr;
         
        switch (pRsvpStatus->StatusCode)
        {
            case WSA_QOS_RECEIVERS:
                if (pOptions->qosOptions.bWaitToSend)
                {
                    printf("FD_QOS: start sending data\n");
                    pSendInfo->bSendEnabled = TRUE;
                    PostSend(pSendInfo, pOptions);
                }
                break;

            case WSA_QOS_NO_RECEIVERS:
                if (pOptions->qosOptions.bWaitToSend)
                {
                    printf("FD_QOS: Stop sending data\n");
                    pSendInfo->bSendEnabled = FALSE;
                }
                break;

            default:
                printf("FD_QOS: Status code %d - no action taken\n", 
                            pRsvpStatus->StatusCode);
        }
        
        free(pQos);  
    }while (TRUE);

    // check for local traffic control
    if (pOptions->qosOptions.bQosabilityIoctls)
    {
        int   nRet;
        DWORD dwBytes, outbuf;
        DWORD inbuf = LOCAL_TRAFFIC_CONTROL;
        
        nRet = WSAIoctl(pSendInfo->sd, SIO_CHK_QOS, (LPVOID)&inbuf, 
                        sizeof(inbuf), (LPVOID)&outbuf, 
                        sizeof(outbuf), &dwBytes, NULL, NULL);
        
        if (SOCKET_ERROR == nRet)
            printf("  SIO_CHK_QOS(LOCAL_TRAFFIC_CONTROL) %d\n", WSAGetLastError());
        else 
        {
            printf("  Local Traffic = ");

            switch( outbuf )
            {
                case INFO_NOT_AVAILABLE:
                    printf("INFO_NOT_AVAILABLE\n");
                    break;
                case 1:
                    printf("Available\n");
                    break;
                case 0:
                    printf("Not available\n");
                    break;
                default:
                     _assume(0);
            }
        }
    }

    return(FALSE);
}




// Abstract:
//      FD_CLOSE handler.   If server closes before we have sent all the data,  
//      then we are done.  Winsock2 events are manual reset events and FD_CLOSE
//      has no re-enabling function, therefore must reset the event here, 
//      otherwise we would get additional FD_CLOSE notifications.
//
static BOOL fd_close_func(
    DWORD               dwEvent, 
    WSANETWORKEVENTS    *NetworkEvents, 
    SEND_INFO           *pSendInfo
    )
{
    printf("  FD_CLOSE: dwEvent=%d error code =%d\n", 
            dwEvent, NetworkEvents->iErrorCode[FD_CLOSE_BIT]);

    WSAResetEvent(pSendInfo->hEvents[WSAEVENTSELECT_EVENT]);
    closesocket(pSendInfo->sd);
    
    return(TRUE);
}




// Abstract:
//      Post an overlapped send and indicate a send is in progress if it doesn
//      not complete immediately.  If the WSASend completes immediately bump 
//      the counters and indicate the send completed.  The send flag is needed   
//      to what needs to be done in CompleteSend() - wait for overlapped 
//      results or post another send.
//      
static BOOL PostSend(
    SEND_INFO   *pSendInfo, 
    OPTIONS     *pOptions
    )
{
    int     nRet;
    DWORD   cbBytesXfer = 0;

    if (pSendInfo->bSendEnabled)
        return(FALSE);

    printf("  PostSend\n");
      
    pSendInfo->bSendComplete = FALSE;
    
    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
        nRet = WSASend(pSendInfo->sd, &pSendInfo->sndbuf, 1, &cbBytesXfer,
                        0, &pSendInfo->ovr, NULL);
    else
        nRet = WSASendTo(pSendInfo->sd, &pSendInfo->sndbuf, 1, &cbBytesXfer, 0,
                            (LPSOCKADDR)&g_destaddr, sizeof(g_destaddr), 
                            &pSendInfo->ovr, NULL);
    
    if (SOCKET_ERROR == nRet) {
        DWORD dwErr = WSAGetLastError();
        
        if (WSA_IO_PENDING != dwErr)
        {
            // Real Error
            printf("WSASend %d\n", dwErr);
            return(TRUE);
        }
        
        return(FALSE);
    }

    // the send completed immediately
    pSendInfo->sndbuf.len -= cbBytesXfer;
    pSendInfo->sndbuf.buf += cbBytesXfer;
    return(TRUE);
}




// Abstract:
//      Handle the completion of a WSASend.  This may involve posting another 
//      overlapped send or closing the socket.  Actually to be more precise,
//      if a TCP socket is being used, shutdown is called and closesocket
//      is handled explicitedly in the FD_CLOSE handler function whereas a
//      UDP socket is closed immediately since it will not receive an FD_CLOSE
//      notification.
//
static BOOL CompleteSend(
    SEND_INFO   *pSendInfo, 
    OPTIONS     *pOptions
    )
{
    BOOL    bProcessEventsDone  = FALSE;
    BOOL    bNormalShutdown     = FALSE;
    int     i;

    printf("  CompleteSend\n");
    
    if (!pSendInfo->bSendComplete)
    {
        DWORD   dwFlags = 0;
        DWORD   cbBytesXfer;

        // handle getting overlapped results
        if (!WSAGetOverlappedResult(pSendInfo->sd, &pSendInfo->ovr, 
                                    &cbBytesXfer, TRUE, &dwFlags))
        {
            printf("WSAGetOverlappedResults = %d\n", WSAGetLastError());
            bProcessEventsDone = TRUE;
        } 
        else 
        {
            pSendInfo->bSendComplete = TRUE;
            pSendInfo->sndbuf.len -= cbBytesXfer;
            pSendInfo->sndbuf.buf += cbBytesXfer;
        }
    }

    // We need to send more
    if (pSendInfo->sndbuf.len > 0) 
    {
        PostSend(pSendInfo, pOptions);
        return FALSE;
    }

    // now we have sent the entire buffer, check repeat count to
    // see if buffer needs to be sent again.
    if (pOptions->nRepeat || pOptions->qosOptions.bAlternateQos)
        pSendInfo->nTotalSends++;
    else
        pSendInfo->nTotalSends = -1;
    
    pSendInfo->sndbuf.buf = pOptions->buf;
    pSendInfo->sndbuf.len = pOptions->nBufSize;
    
    if (    pSendInfo->nTotalSends <= pOptions->nRepeat - 1 
        ||  pOptions->qosOptions.bAlternateQos)
    {
        PostSend(pSendInfo, pOptions);
        return FALSE;
    }

    // We are done sending, go into cleanup
    printf("    repeat count complete - closing\n");
    
    if (IPPROTO_UDP == pOptions->spOptions.iProtocol)
    {
        // UDP will not recieve FD_CLOSE, nor is shutdown applicable
        closesocket(pSendInfo->sd);
        WSAResetEvent(pSendInfo->hEvents[WSASEND_EVENT]);
        return(TRUE);
    }

    //TCP case
    // On NT it is possible that shutdown returns WSAENOTCONN even
    // after receipt of an FD_CONNECT notification (see KB).  To
    // get around this, just add a little delay.

    for (i=0; i<20; i++)
    {
        int nRet = shutdown(pSendInfo->sd, SD_SEND);

        if (0 == nRet)
        {
            bNormalShutdown = TRUE;
            break;
        } 
        else 
        {
            DWORD dwErr = WSAGetLastError();

            if (dwErr == WSAENOTCONN)
                Sleep(100);   
            else 
            {
                printf("    shutdown: %d\n", dwErr);
                break;
            }
        }
    }

    if (! bNormalShutdown)
    {
        //
        // Normal shutdown failed... too bad.
        closesocket(pSendInfo->sd);
        bProcessEventsDone = TRUE;
    }
    
    WSAResetEvent(pSendInfo->hEvents[WSASEND_EVENT]);
    return(bProcessEventsDone);
}



