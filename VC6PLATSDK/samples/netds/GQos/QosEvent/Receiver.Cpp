// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1998 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// Module:
//      receiver.cpp
//
// Abstract: 
//      Implement receive-side functionality.  The reciever can accept up to 
//      MAXCLIENT connections from senders (no limit for UDP).  The receiver 
//      uses WSAEventSelect to handle the potential multiple connections as  
//      well as to allow the receiver to receive notification of QOS activity 
//      via the FD_QOS notification.
//
//      Additionally, the receiver can be setup to receive multicast data for 
//      a given group.  This is accomplished by using the -m:Group-IP option 
//      which joins thereceiver to that Group-IP multicast group.
//
//      The template used when enabling QOS is specified with the commandline
//      option -q:template.  A value of default for template will result in 
//      default values being entered for sending and receiving flowspec (see 
//      FillQos). Otherwisethe specified template is used (again see FillQos).
//
//      QOS can be enabled in the receiver in the following manner
//      -i:b    before WSAAccept on the listening socket using WSAIoctl
//      -i:d    during WSAAccept in the condition function
//      -i:a    after WSAAccept on the accepted socket using WSAIoctl
//      -i:q    upon receipt of FD_QOS.  In order to receive FD_QOS (i.e. 
//              enable the gqossp) qos is set using WSAIoctl prior to 
//              WSAEventSelect
//      For non-multicast UDP QOS tranfers there is no API that gets called 
//      prior to initiating the data transfers, therefore QOS is 
//      set prior to the data transfers (i.e. -i:b).
//  
//      Receipt of RESV confirmation can be requested using the -c commandline
//      option (not yet implemented).  
//
// Author:
//      Barry R. Butterklee
//

#include "qosevent.h"

#define MAXCLIENTS 4


// encapsulate socket, events, buffers, and various flags and counters that
// control how/when data is received into a structure
typedef struct _RECV_INFO
{
    SOCKET          sd[MAXCLIENTS+1];
    WSAEVENT        hEvents[MAXCLIENTS+1];
    CHAR *          recvbuf;
    int             nTotalClients;
} RECV_INFO;


static SOCKET g_sd;


static BOOL CreateReceivingSocket(RECV_INFO *, OPTIONS *, WSAPROTOCOL_INFO *);
static BOOL fd_accept_func(DWORD, WSANETWORKEVENTS *, RECV_INFO *, OPTIONS *);
static BOOL fd_read_func(DWORD, WSANETWORKEVENTS *, RECV_INFO *, OPTIONS *);
static BOOL fd_qos_func(DWORD, WSANETWORKEVENTS *, RECV_INFO *, OPTIONS *);
static BOOL fd_close_func(DWORD, WSANETWORKEVENTS *, RECV_INFO *, OPTIONS *);
int CALLBACK AcceptCondFunc(
    LPWSABUF, LPWSABUF, LPQOS, LPQOS, LPWSABUF, 
    LPWSABUF, GROUP FAR *, DWORD_PTR);


// Abstract:
//      Main function to create a socket that allows clients to connect and
//      send it data.  Upto MAXCLIENTS can connect and send data.  The data
//      is read in and then tossed (the data is not used).  
//
//      When using TCP, the first socket/event in the array of sockets/events 
//      (RECV_INFO) is the listening socket and the remaining are to handle the
//      accepted connections.  For UDP, only the first socket/event is used.
//
VOID Receiver(
    OPTIONS             *pOptions, 
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
{
    WSANETWORKEVENTS NetworkEvents;
    long lNetworkEvents;
    BOOL bProcessEventsDone;
    RECV_INFO RecvInfo;
    int i;

    printf("Receiver\n");

    // initialize data structures
    ZeroMemory(&RecvInfo, sizeof(RECV_INFO));
    for (i=0; i<MAXCLIENTS+1; i++)
    {
        RecvInfo.sd[i] = INVALID_SOCKET;

        if (WSA_INVALID_EVENT == (RecvInfo.hEvents[i] = WSACreateEvent()))
        {
            printf("WSACreateEvent(%d): %d\n", i, WSAGetLastError());
            goto CLEANUP;
        }
    }

    // create the receiving/listening socket
    if (!CreateReceivingSocket(&RecvInfo, pOptions, pProtocolInfo))
        goto CLEANUP;


    // TCP sockets need to accept a connection prior to receiving data.  ,
    // Additionally if we are doing UDP and multicasting, IP Multicasting does
    // not support rooted planes and thus a receiving end will not get 
    // FD_ACCEPT notification
    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
        lNetworkEvents = FD_ACCEPT;
    else
        lNetworkEvents = (FD_READ|FD_QOS|FD_CLOSE);
    
    if (SOCKET_ERROR == WSAEventSelect(RecvInfo.sd[0], RecvInfo.hEvents[0], 
                                        lNetworkEvents))
    {
        printf("WSAEventSelect: %d\n", WSAGetLastError());
        goto CLEANUP;
    }

    bProcessEventsDone = FALSE;
    do 
    {
        DWORD dwEvent = WSAWaitForMultipleEvents((MAXCLIENTS+1), RecvInfo.hEvents, 
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
            // lets see what network activity trigged this event
            NetworkEvents.lNetworkEvents = 0;
            dwEvent -= WSA_WAIT_EVENT_0;

            if (SOCKET_ERROR == WSAEnumNetworkEvents(RecvInfo.sd[dwEvent], 
                                                     RecvInfo.hEvents[dwEvent],
                                                     &NetworkEvents))
            {
                printf("WSAEnumNetworkEvent: %d dwEvent %d lNetworkEvent %X\n", 
                            WSAGetLastError(), dwEvent, 
                            NetworkEvents.lNetworkEvents);
                
                goto CLEANUP;
            }
            
            // it is possible that more than one notification triggered
            //printf("WSAEnumNetworkEvents %X\n", NetworkEvents.lNetworkEvents)
            if (FD_ACCEPT & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_accept_func(dwEvent, 
                                                     &NetworkEvents, 
                                                     &RecvInfo, 
                                                     pOptions);
            
            if (FD_READ & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_read_func(dwEvent, 
                                                     &NetworkEvents, 
                                                     &RecvInfo, 
                                                     pOptions);
            
            if (FD_QOS     & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_qos_func(dwEvent, 
                                                  &NetworkEvents, 
                                                  &RecvInfo, 
                                                  pOptions);
            
            if (FD_CLOSE   & NetworkEvents.lNetworkEvents)
                bProcessEventsDone |= fd_close_func(dwEvent, 
                                                    &NetworkEvents, 
                                                    &RecvInfo, 
                                                    pOptions);

            break;
        }
    } while (!bProcessEventsDone);

CLEANUP:
    for (i=0; i<MAXCLIENTS+1; i++)
    {
        if (    (WSA_INVALID_EVENT != RecvInfo.hEvents[i])
            &&  (NULL != RecvInfo.hEvents[i]))
            WSACloseEvent(RecvInfo.hEvents[i]);

        if (    (INVALID_SOCKET != RecvInfo.sd[i])
             && (NULL != RecvInfo.sd[i]))
            closesocket(RecvInfo.sd[i]);
    }

    return;
}




// Abstract:
//      Create a socket on which to receive data.  Note that this differs 
//      depending upon whether TCP or UDP is used.  Also, please note that  
//      WSA_FLAG_OVERLAPPED *MUST* be specified.  Also, note that the 
//      parameters for WSASocket and the data to fill in the SOCKADDR_IN 
//      structure come from the supplied protocol info structure instead of 
//      being hardcoded.
//
//      The listening socket (and thus all accepted sockets) can be made into a
//      QOS socket if the -i:b option is set.  If -i:q is set then we actually 
//      need to inform the GQOSSP that we wish to receive FD_QOS if we ask for 
//      them. As a consequence we also need to make the socket into a QOS 
//      socket before WSAEventSelect is called.  I choose to make the socket a
//      QOS socket (if -i:q) here to accomadate both TCP and UDP sockets 
//      instead of in the FD_ACCEPT handler because the FD_ACCEPT handler will
//      not be invoked for UDP.
//
static BOOL CreateReceivingSocket(
    RECV_INFO           *pRecvInfo, 
    OPTIONS             *pOptions, 
    WSAPROTOCOL_INFO    *pProtocolInfo
    )
{
    SOCKADDR_IN addr_srv;
    int         nRet;
    QOS         qos;
    QOS         *pQos;
    DWORD       cbQosLen;
    DWORD       dwSocketFlags = WSA_FLAG_OVERLAPPED;


    // If we are multicast enabled set the control and data planes to leafs.
    // These flags must be set for IP multicasting.
    if (pOptions->spOptions.bMulticast)
        dwSocketFlags |= 
                    (WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF);
    
    pRecvInfo->sd[0] = WSASocket(FROM_PROTOCOL_INFO, 
                                 FROM_PROTOCOL_INFO, 
                                 FROM_PROTOCOL_INFO, 
                                 pProtocolInfo, 
                                 0, 
                                 dwSocketFlags);
    
    if (INVALID_SOCKET == pRecvInfo->sd[0])
    {
        printf("WSASocket %d", WSAGetLastError());
        return(FALSE);
    }

    ZeroMemory((PVOID)&addr_srv, sizeof(addr_srv));
    addr_srv.sin_family      = (USHORT) pProtocolInfo->iAddressFamily;
    addr_srv.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_srv.sin_port        = htons(pOptions->port);
    
    nRet = bind(pRecvInfo->sd[0], (LPSOCKADDR)&addr_srv, sizeof(addr_srv));
    if (SOCKET_ERROR == nRet)
    {
        printf("bind %d", WSAGetLastError());
        return(FALSE);
    }

    // Set the time-to-live (TTL) option for multicasting if enabled. This 
    // limits how far data sent to a group will go.
    if (pOptions->spOptions.bMulticast)
    {
        int optval = 64;

        if (SOCKET_ERROR ==setsockopt(pRecvInfo->sd[0], IPPROTO_IP, 
                                      IP_MULTICAST_TTL, (char *)&optval, 
                                      sizeof(int)))
        {
            printf("setsockopt(IP_MULTICAST_TTL) %d\n", WSAGetLastError());
            return(FALSE);
        }
    }

    // for TCP we need to call listen
    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
    {
        nRet = listen(pRecvInfo->sd[0], SOMAXCONN);
        if (SOCKET_ERROR == nRet)
        {
            printf("listen %d", WSAGetLastError());
            return(FALSE);
        }
    }

    g_sd = pRecvInfo->sd[0];

    pQos = NULL;
    if (pOptions->spOptions.bQos)
    {
        switch (pOptions->qosOptions.qosIoctlSet)
        {
        case QOS_IOCTL_SET_BEFORE:
            if (SetQos(pRecvInfo->sd[0], &pOptions->qosOptions,
                        TRUE, &qos, &cbQosLen))
                printf("  QOS set before accept\n");
            break;
            
        case QOS_IOCTL_SET_QOS:
            // this one is tricky.  The intent is to send the RESV after 
            // receiving FD_QOS notification.  However, unless we somehow 
            // inform the GQOSSP that we are interested in QOS, it will not
            // send us FD_QOS when receiving a RESV.  However, we do not want 
            // to send out a RESV until we explicitedly set QOS.  We therefore
            // do not want QOS signalling (i.e. RSVP messages) to be sent.
            pOptions->qosOptions.bDisableSignalling = TRUE;
            if (SetQos(pRecvInfo->sd[0], &pOptions->qosOptions, 
                        TRUE, &qos, &cbQosLen))
            {
                printf("  QOS set qos before accept - will be set again in FD_QOS\n");
                pQos = &qos;
            }
            break;
        }
    }

    // Join the multicast group if specfied.  We may also specify a given QOS 
    // structure at this time.
    if (pOptions->spOptions.bMulticast)
    {
        SOCKADDR_IN mult_addr;

        ZeroMemory((PVOID)&mult_addr, sizeof(mult_addr));
        mult_addr.sin_family      = (USHORT) pProtocolInfo->iAddressFamily;
        mult_addr.sin_addr.s_addr = inet_addr(pOptions->szHostname);
        mult_addr.sin_port        = htons(pOptions->port);

        nRet = (int) WSAJoinLeaf(pRecvInfo->sd[0], (LPSOCKADDR)&mult_addr, 
                                  sizeof(mult_addr), NULL, NULL, pQos, 
                                   NULL, JL_BOTH);
        if (INVALID_SOCKET == nRet)
        {
            printf("WSAJoinLeaf %d", WSAGetLastError());
            return(FALSE);
        }

        if (    (pOptions->spOptions.bQos) 
            &&  (QOS_IOCTL_SET_AFTER == pOptions->qosOptions.qosIoctlSet)
            &&  (SetQos(pRecvInfo->sd[0], &pOptions->qosOptions, TRUE, &qos, &cbQosLen)))
                printf("    QOS set after WSAJoinLeaf\n");
    }

    return(TRUE);
}




// Abstract:
//      FD_ACCEPT handler.  Invoked when a client is trying to connect 
//      (TCP-only). WSAAccept is called and an Accept Condition function is 
//      supplied to allow a connection to be rejected if too many client have 
//      already connected.
//      
//      The condition function allows the accepted socket to be made into a QOS
//      socket (if -i:d option has been specified).  The socket can also be  
//      made into a QOS socket after WSAAccept returns.
//
//      After a successful WSAAccept, the proper notifications for a TCP socket
//      are set with WSAEventSelect.
//
static BOOL fd_accept_func(
    DWORD               dwEvent, 
    WSANETWORKEVENTS    *NetworkEvents, 
    RECV_INFO           *pRecvInfo, 
    OPTIONS             *pOptions
    )
{
    SOCKET  temp_socket;
    int     i, nRet;
    QOS     qos;
    DWORD   cbQosLen;


    printf("  FD_ACCEPT: dwEvent=%d error code =%d\n", 
            dwEvent, NetworkEvents->iErrorCode[FD_ACCEPT_BIT]);

    if (NetworkEvents->iErrorCode[FD_ACCEPT_BIT])
        return(TRUE);

    temp_socket = WSAAccept(pRecvInfo->sd[0], NULL, NULL, 
                    AcceptCondFunc, (DWORD_PTR)pOptions); 
    
    if (INVALID_SOCKET == temp_socket)
    {
        printf("    WSAAccept %d\n", WSAGetLastError());
        return(FALSE);
    }
    
    // keep list of connected sockets
    printf("    socket connection accepted\n");
    for (i = 1; i < MAXCLIENTS; i++)
        if (INVALID_SOCKET == pRecvInfo->sd[i])
        {
            pRecvInfo->sd[i] = temp_socket;
            break;
        }

    _assume(i < MAXCLIENTS);

    if (    (pOptions->spOptions.bQos) 
        &&  (QOS_IOCTL_SET_AFTER == pOptions->qosOptions.qosIoctlSet)
        &&  (SetQos(temp_socket, &pOptions->qosOptions, TRUE, &qos, &cbQosLen)))
            printf("    QOS set after accept\n");

    nRet = WSAEventSelect(temp_socket, 
                          pRecvInfo->hEvents[i], 
                          (FD_READ|FD_QOS|FD_CLOSE));

    if (SOCKET_ERROR == nRet)
    {
        printf("    WSAEventSelect: %d\n", WSAGetLastError());
        return(TRUE);
    }

    return(FALSE);
}
    


// Abstract:
//      FD_READ handler.  Handling FD_READ notifications is pretty   
//      straight-forward. Just read the amount of data you are interested in 
//      reading at this moment. If there is more data left, you will get 
//      another FD_READ.
//
//      *** Currently, I am reusing the same buffer for all reads.  Though note
//       that since I am not really "using" any ofthe data I read it is not a 
//      problem.
//
static BOOL fd_read_func(
    DWORD               dwEvent, 
    WSANETWORKEVENTS    *NetworkEvents, 
    RECV_INFO           *pRecvInfo, 
    OPTIONS             *pOptions
    )
{
    int         nRecv;
    static CHAR *bufptr = pOptions->buf;
    static int  nBytesToRecv = pOptions->nBufSize;

    printf("  FD_READ: dwEvent=%d error code =%d bytestorecv=%d\n", 
        dwEvent, NetworkEvents->iErrorCode[FD_READ_BIT], nBytesToRecv);

    if (NetworkEvents->iErrorCode[FD_READ_BIT])
        return(TRUE);

    // if UDP use recvfrom()
    if (IPPROTO_TCP == pOptions->spOptions.iProtocol)
        nRecv = recv(pRecvInfo->sd[dwEvent], bufptr, nBytesToRecv, 0);
    else
        nRecv = recvfrom(pRecvInfo->sd[dwEvent], bufptr, 
                         nBytesToRecv, 0, NULL, NULL);
    
    if (SOCKET_ERROR == nRecv)
        switch (WSAGetLastError())
        {
            case WSAEWOULDBLOCK:
                printf("    recv[from]: WSAEWOULDBLOCK, wait for next FD_READ\n");
                return(FALSE);

            case WSAECONNRESET:
                // FD_CLOSE will follow (sender terminated early)
                return(FALSE);  

            default:
                // any other read errors will close app
                return(TRUE);	 
        }

    // we got data
    if (nRecv)
        printf("    recv'ed bytes=%d char=<%c>\n", nRecv, *bufptr);
    else
        printf("    recv'ed 0 bytes\n"); 

    bufptr += nRecv;
    nBytesToRecv -= nRecv;
    if (0 == nBytesToRecv)
    {
        bufptr = pOptions->buf;
        nBytesToRecv = pOptions->nBufSize;
    }
    
    return (FALSE);
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
    RECV_INFO           *pRecvInfo, 
    OPTIONS             *pOptions
    )
{
    int     nRet;
    DWORD   cbQosLen;
    DWORD   dwBytes;
    QOS     *pQos = NULL;

    // used for looking into provider information
    QOS_OBJECT_HDR   *pObjectHdr;
    RSVP_STATUS_INFO *pRsvpStatus;

    printf("  FD_QOS: dwEvent=%d error/status code =%d\n", 
    dwEvent, NetworkEvents->iErrorCode[FD_QOS_BIT]);

    if (NetworkEvents->iErrorCode[FD_QOS_BIT])
        return(TRUE);

    do 
    {
        if (pQos != NULL) 
        {
            free(pQos);
            pQos = NULL;
        }

        // Keep going till the getqos call says we are done
        if (!GetQos(pRecvInfo->sd[dwEvent], 
                    pOptions->qosOptions.bQueryBufferSize, 
                    &pQos))
            break;

        PrintQos(pQos, "    ");
        
        // Move on if aren't supposed to set qos now
        if (    !pOptions->spOptions.bQos
            ||  (QOS_IOCTL_SET_QOS != pOptions->qosOptions.qosIoctlSet))
            continue;

        pQos->SendingFlowspec = default_notraffic;

        // Make sure we have a providerspecific buffer
        if (pQos->ProviderSpecific.buf == NULL)
            continue;
        
        pObjectHdr = (QOS_OBJECT_HDR *) pQos->ProviderSpecific.buf;

        // Make sure we have the right object
        if (RSVP_OBJECT_STATUS_INFO != pObjectHdr->ObjectType)
            continue;
        
        pRsvpStatus = (RSVP_STATUS_INFO *)pObjectHdr;

        // check to see if it is a path message and set it
        if (WSA_QOS_SENDERS != pRsvpStatus->StatusCode)
            continue;
        
        pQos->ProviderSpecific.buf = NULL;
        pQos->ProviderSpecific.len = 0;


        // Do the SetQos
        cbQosLen = sizeof(QOS) + pQos->ProviderSpecific.len;
        dwBytes  = 0;
        nRet = WSAIoctl(pRecvInfo->sd[dwEvent], 
                        SIO_SET_QOS, (LPVOID)pQos,
                        cbQosLen, NULL, 0, 
                        &dwBytes, NULL, NULL);
        
        if (SOCKET_ERROR == nRet)
            printf("WSAIoctl:SIO_SET_QOS %d\n", WSAGetLastError());
        else
        	printf("    QOS set during FD_QOS\n");
        
    }while (TRUE);

    // check for end-to-end qos
    if (pOptions->qosOptions.bQosabilityIoctls)
    {
        DWORD outbuf;
        DWORD inbuf = END_TO_END_QOSABILITY; 

        dwBytes = 0;
        nRet = WSAIoctl(pRecvInfo->sd[dwEvent], SIO_CHK_QOS, 
                        (LPVOID)&inbuf, sizeof(inbuf),
                        (LPVOID)&outbuf, sizeof(outbuf),
                        &dwBytes, NULL, NULL);

        if (SOCKET_ERROR == nRet)
            printf("  SIO_CHK_QOS(END_TO_END_QOSABILITY) %d\n", WSAGetLastError());
        else
        {
            printf("  End-toEnd Qosability = ");

            switch(outbuf)
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
//      FD_CLOSE handler.  When receiving FD_CLOSE, it is still possible for  
//      data to be queued up and therefore the socket should be drained of that
//      data so as not to lose that data.  Winsock2 events are manual reset 
//      events and FD_CLOSE has no re-enabling function, therefore must reset 
//      the event here, otherwise we would get additional FD_CLOSE 
//      notifications.
//
static BOOL fd_close_func(
    DWORD               dwEvent, 
    WSANETWORKEVENTS    *NetworkEvents, 
    RECV_INFO           *pRecvInfo, 
    OPTIONS             *pOptions
    )
{

    printf("  FD_CLOSE: dwEvent=%d error code =%d\n", 
        dwEvent, NetworkEvents->iErrorCode[FD_CLOSE_BIT]);

    if (NetworkEvents->iErrorCode[FD_CLOSE_BIT])
        return(TRUE);

    // drain the socket
    printf("    Draining socket\n");

    do
    {
        int nRecv = recv(pRecvInfo->sd[dwEvent], pOptions->buf, pOptions->nBufSize, 0);

        printf("     recv: nRecv=%d", nRecv);
        
        if (nRecv <= 0) 
            break;

        printf(" char=<%c>\n", *pOptions->buf); 
    } while (TRUE);

    printf("\n");

    WSAResetEvent(pRecvInfo->hEvents[dwEvent]);
    closesocket(pRecvInfo->sd[dwEvent]);
    pRecvInfo->sd[dwEvent] = INVALID_SOCKET;
    pOptions->dwTotalClients--;

    return(FALSE);
}




// Abstract:
//      Function called by Winsock to accept or reject a connection.  If more 
//      than MAXCLIENTS attempt to connect the connection will be rejected 
//      (CF_REJECT) and the connection reset.  Please note that a connect (at
//      the TCP level) can be successful even if the receiving application does 
//      not call WSAAccept (or accept).  The the effect of CF_REJECT is to 
//      reset an already established connection.
//
//      If lpSQos is supplied, then QOS must be set to valid values for Win98 -
//      NT5 does not have this restriction.  On Windows2000 the contents of 
//      lpSQos will be QOS_NOT_SPECIFIED (even if PATH data has arrived prior  
//      to executing this function).  This behaviour is by design for the 
//      Microsoft GQOSSP.
//
int CALLBACK AcceptCondFunc(
    LPWSABUF    lpCallerId,
    LPWSABUF    lpCallerData,
    LPQOS       lpSQos,
    LPQOS       lpGQos,
    LPWSABUF    lpCalleeId,
    LPWSABUF    lpCalleeData,
    GROUP FAR   *Group,
    DWORD_PTR   CallbackData
    )
{
    OPTIONS *pOptions;

    UNREFERENCED_PARAMETER(Group);
    UNREFERENCED_PARAMETER(lpCalleeData);
    UNREFERENCED_PARAMETER(lpGQos);
    UNREFERENCED_PARAMETER(lpCallerData);

    pOptions = (OPTIONS *)CallbackData;
    
    printf("    AcceptCondFunc\n");
    if (lpCallerId)
    {
        // NOTE:  This program only supports TCP or UDP
        SOCKADDR_IN *sockaddr = (SOCKADDR_IN *)lpCallerId->buf;
        printf("      lpCallerId address family=%d, port=%d\n", 
            sockaddr->sin_family, ntohs(sockaddr->sin_port));
    }

    if (lpSQos)
    {
        printf("    AcceptCondFunc: lpSQos valid\n");

        if (pOptions->spOptions.bQos)
            // bMustSetQosInAccept will not be set for Windows2000 but only for
            // Win98. Win98 currently requires valid QOS parameters to be set
            // here iff lpSQos is a valid pointer.
            if (    (QOS_IOCTL_SET_DURING == pOptions->qosOptions.qosIoctlSet) 
                ||  pOptions->qosOptions.bMustSetQosInAccept)
            {
                DWORD cbQosLen;
                printf("    AcceptCondFunc: filling in Qos\n");

                if (SetQos(g_sd, &pOptions->qosOptions,  FALSE, lpSQos, &cbQosLen))
                    PrintQos(lpSQos, "    ");
                else
                    printf("    Failed to SetQos\n");
            }
    }

    if (lpCalleeId)
    {
        // NOTE:  This program only supports TCP or UDP
        SOCKADDR_IN *sockaddr = (SOCKADDR_IN *)lpCalleeId->buf;
        printf("      lpCalleeId: address family=%d, port=%d\n", 
                    sockaddr->sin_family, ntohs(sockaddr->sin_port));
    }

    //
    // Determine where to accept or reject the new connection based
    // on the number of clients currently connected.
    if (MAXCLIENTS == pOptions->dwTotalClients)
    {
        printf("      Rejecting connection, limit of %d clients reached\n",
                    pOptions->dwTotalClients);

        // At this point a connection will already have been established,
        // this will just cause the connection to be reset.
        return(CF_REJECT);
    }

    pOptions->dwTotalClients++;

    return(CF_ACCEPT);
} 

