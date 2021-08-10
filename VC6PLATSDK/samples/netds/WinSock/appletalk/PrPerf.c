/*++

Copyright 1994 - 2000 Microsoft Corporation

Module Name: prperf.c


Abstract: This Sample Windows Socket Application demonstrates use of
          the AppleTalk PAP Protocol. Both a server and a client
          application are included in this source file. The client
          app reads a file and sends the contents to the server.


--*/

#include <winsock.h>
#include <windows.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

//
// the following header contains appletalk specific definitions.
// should be included for AppleTalk Windows Socket Applications
//
#include <atalkwsh.h>
#include "prsamp.h"

#define SOCKET_COUNT                    32

#define DEF_SERVER_NAME                 "Windows Adsp"
#define DEF_SERVER_TYPE                 "Windows Sockets"
#define DEF_SERVER_ZONE                 "*"
#define BLOCKSIZE                       4096

#define DEF_QUEUE_LEN                   5
#define PROTOCOL_LEN                    10

CHAR        gServerName[MAX_ENTITY]         = DEF_SERVER_NAME;
CHAR        gServerType[MAX_ENTITY]         = DEF_SERVER_TYPE;
CHAR        gServerZone[MAX_ENTITY]         = DEF_SERVER_ZONE;
CHAR        gProtocolName[PROTOCOL_LEN]     = "ADSP";
size_t      gNumTimes                       = 5;

SYSTEMTIME    SystemStartTime;
SYSTEMTIME    SystemEndTime;
FILETIME      FileTime;

BOOL fVerify = FALSE;
BOOL fRDM    = FALSE;

int loop = 1, looptot;
double Throughput, AvgThroughPut, MinThroughPut, MaxThroughPut;

CHAR DataString[] = {"0123456789abcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+"};

typedef struct Sock_Info {
    int     socket_type;
    int     protocol;

    SOCKET  socket;
    HANDLE  thread;

    struct Sock_Info *next, *prev;

} *PTEST_INFO, TEST_INFO;

PTEST_INFO       gSocketList=NULL;  // List of client sockets
CRITICAL_SECTION gListCritSec;      

/******************************************************************************
 
 Function - InsertSockInfo()

 Comments - Inserts a socket context structure at the head of a linked list.
            The server maintains a list of all connected clients.
            
******************************************************************************/
void InsertSockInfo(TEST_INFO **head, TEST_INFO *info)
{
    info->next = info->prev = NULL;

    if (*head == NULL)
    {
        *head = info;
    }
    else
    {
        (*head)->prev = info;
        info->next    = *head;
        *head         = info;
    }
}

/******************************************************************************
 
 Function - RemoveSockInfo()

 Comments - Removes the given socket context structure from the list. The 
            server maintains a list of all connected clients.
            
******************************************************************************/
void RemoveSockInfo(TEST_INFO **head, TEST_INFO *info)
{
    if (info->next)
        info->next->prev = info->prev;
    if (info->prev)
        info->prev->next = info->next;

    if (info == *head)
    {
        *head = info->next;
    }
}

/******************************************************************************
 
 Function - main()

 Comments - Parses the command line and starts either the client or server
            code.
            
******************************************************************************/
int __cdecl main (int argc, char **argv)
{
    WSADATA WsaData;
    BOOL    fClient = FALSE;
    BOOL    fServer = FALSE;
    int     i, r;

    for(i = 1; i < argc; i++)
    {
        if ( (strlen(argv[i]) == 2) && ( (argv[i][0] == '/') || (argv[i][0] == '-') ) )
        {
            switch(tolower(argv[i][1]))
            {
                case 'n':
                    if (i+1 >= argc)
                        usage();
                    strncpy(gServerName, argv[++i], MAX_ENTITY-1);
                    break;
                case 't':
                    if (i+1 >= argc)
                        usage();
                    strncpy(gServerType, argv[++i], MAX_ENTITY-1);
                    break;
                case 'z':
                    if (i+1 >= argc)
                        usage();
                    strncpy(gServerZone, argv[++i], MAX_ENTITY-1);
                    break;
                case 's':
                    if (fClient == TRUE)
                        usage();
                    fServer = TRUE;
                    break;
                case 'c':
                    if (fServer == TRUE)
                        usage();
                    fClient = TRUE;
                    break;
                case 'p':
                    if (i+1 >= argc)
                        usage();
                    strncpy(gProtocolName, argv[++i], PROTOCOL_LEN-1);
                    break;
                case 'b':
                    if (i+1 >= argc)
                        usage();
                    gNumTimes = atoi(argv[++i]);
                    break;
                case 'l':
                    if (i+1 >= argc)
                        usage();
                    loop = atoi(argv[++i]);
                    break;
                case 'v':
                    fVerify = TRUE;
                    break;
                case 'y':
                    fRDM = TRUE;
                    break;
                case '?':
                default:
                    usage();

            }
        }
        else
        {
            usage();
        }

    }


    printf("Server Name %s\n", gServerName);
    printf("Server Type %s\n", gServerType);
    printf("Server Zone %s\n", gServerZone);

    printf("%s throughput measurement\n", gProtocolName);

    if(_strnicmp(gProtocolName, "ADSP", 4) && _strnicmp(gProtocolName, "PAP", 3))
    {
        printf("\nInvalid Protocol Specified\n\n");
        usage();
    }

    if(!(fClient || fServer))
        usage();

    // Load winsock
    r = WSAStartup(0x0101, &WsaData);
    if (r != 0)
    {
        printf("Startup failed: %d\n", r);
        WSACleanup();
        return(0);
    }

    if(fClient)
    {
        BOOL DClnt;

        looptot       = 0;
        MaxThroughPut = 0;
        AvgThroughPut = 0;

        while (looptot < loop)
        {
            DClnt = DoClient();
            if(DClnt)
            {
                if ((looptot == 0) || (MinThroughPut > Throughput))
                    MinThroughPut = Throughput;

                if (MaxThroughPut < Throughput)
                    MaxThroughPut = Throughput;

                AvgThroughPut = ((AvgThroughPut * looptot) + Throughput)
                    / (looptot+1);
                printf("Loop %2d/%d Throughput Cur/Min/Max/Ave :", ++looptot, loop);
                printf(" %6.2f/%6.2f/%6.2f/%6.2f\n\n\n", Throughput,
                        MinThroughPut,
                        MaxThroughPut,
                        AvgThroughPut);
                Throughput = 0.0;
            }
            else
            {
                break;
            }
        }
    }
    else if (fServer)
    {
        DoServer();
    }

    WSACleanup();

    return(0);
}

/******************************************************************************
 
 Function - DoServer()

 Calling Function - main();

 Comments - This section of code calls the Server side of the application.
            
******************************************************************************/
BOOL DoServer()
{
    BOOL   fRet = FALSE;

    //
    // register the name specified on the command line  or use the
    // defaults.
    //

    fRet = OpenSocketRegisterAndListen();

    return(fRet);

}


/******************************************************************************
 
 Function - OpenSocketRegisterAndListen()

 Calling Function - DoServer();

 Comments - This section of code controls the Server side of the application.
            
******************************************************************************/

BOOL OpenSocketRegisterAndListen()
{

    int                  r = 0;         // return from socket calls
    BOOL                 fRet = TRUE;
    SOCKET               sock, newsock; // SOCKET descriptor
    SOCKADDR_AT          atalkaddr;     // See atalkwsh.h
    WSH_REGISTER_NAME    nbpname;       // structure for registering NBP name
                                        // see atalkwsh.h
    fd_set               readfds;       // fd_set strutture for select call
    int                  addrlen;
    PTEST_INFO           test;
    int                  sockettype = SOCK_STREAM;
    int                  protocoltype = ATPROTO_ADSP;
    unsigned long        ThreadId;
    struct timeval       tval;
    TEST_INFO           *sockptr, 
                        *socktmp;


    //
    // open a appletalk socket. The protocol family should be AF_APPLETALK,
    // the socket type can be SOCK_STREAM or SOCK_RDM, and the ProtocolType
    // for PAP socket must be ATPROTO_PAP. Note that opening a socket does
    // not yet create an endpoint on the AppleTalk Protocol. A bind must
    // happen before this socket can be used with AppleTalk;
    //

    do
    {
        if (!_strnicmp(gProtocolName, "PAP", 3))
        {
            sockettype = SOCK_RDM;
            protocoltype = ATPROTO_PAP;
        }
        else if (fRDM)
        {
            sockettype = SOCK_RDM;
        }


        sock = socket(AF_APPLETALK, sockettype, protocoltype);

        if (sock == INVALID_SOCKET)
        {
            printf("Open Socket: Error = %ld\n", WSAGetLastError());
            r = SOCKET_ERROR;
            break;
        }

        atalkaddr.sat_socket = 0;
        atalkaddr.sat_family = AF_APPLETALK;

        r = bind(sock, (struct sockaddr *)&atalkaddr, sizeof(SOCKADDR_AT));
        if(r == SOCKET_ERROR)
        {
            printf("Bind:Error = %d\n", WSAGetLastError());
            break;
        }

        //
        // end point has now been created on the AppleTalk Protocol
        // now register the name that the client will look up.
        //

        strncpy(nbpname.ObjectName, gServerName, MAX_ENTITY-1);
        nbpname.ObjectNameLen = (char) strlen(nbpname.ObjectName);

        strncpy(nbpname.TypeName, gServerType, MAX_ENTITY-1);
        nbpname.TypeNameLen = (char) strlen(nbpname.TypeName);

        strncpy(nbpname.ZoneName, "*", MAX_ENTITY-1);
        nbpname.ZoneNameLen = (char) strlen(nbpname.ZoneName);

        printf("Registering %s:%s@%s\n", 
                nbpname.ObjectName,
                nbpname.TypeName,
                nbpname.ZoneName);


        r = setsockopt(
                sock,                          // socket descriptor
                SOL_APPLETALK,                 // socket level - always SOL_APPLETALK
                SO_REGISTER_NAME,              // socket option
                (char *)&nbpname,              // nbp name structure
                sizeof(WSH_NBP_NAME));         // size of nbp name structure

        if (r == SOCKET_ERROR)
        {
            printf("Register Name: Error = %d\n", WSAGetLastError());
            break;
        }

        printf("Socket bound and registered\n");

    } while(FALSE);

    if(r == SOCKET_ERROR)
    {
        closesocket(sock);
        return(FALSE);
    }

    //
    // Post a listen on this socket. The default queue length is 5
    //

    r =  listen(sock, DEF_QUEUE_LEN);
    if (r == SOCKET_ERROR)
    {
        printf("Listen:Error = %d\n", WSAGetLastError());
        closesocket(sock);
        return FALSE;
    }

    __try {
        InitializeCriticalSection(&gListCritSec);
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        fprintf(stderr, "Unable to initialize critical section!\n");
        closesocket(sock);
        return FALSE;
    }

    //
    // listen is successful. select the socket for reading
    //

    do
    {
        FD_ZERO(&readfds);            // clear set
        FD_SET(sock, &readfds);       // add sock to set

        tval.tv_sec  = 1;
        tval.tv_usec = 0;

        //
        // this is a blocking select. Select will complete when
        // a client connects.
        //

        r = select(0, &readfds, NULL, NULL, &tval);

        if (r == SOCKET_ERROR)
        {
            printf("Select: Error = %d\n", WSAGetLastError());
            fRet = FALSE;
            break;
        }

        if (r == 0)
        {

            // Timeout, check for exiting threads
            sockptr     = gSocketList;
            while (sockptr)
            {
                r = WaitForSingleObject(sockptr->thread, 0);
                if ((r != WAIT_FAILED) && (r != WAIT_TIMEOUT))
                {
                    printf("Freeing client connection ...\n");

                    EnterCriticalSection(&gListCritSec);
                    if (sockptr->socket == INVALID_SOCKET)
                    {
                        closesocket(sockptr->socket);
                        sockptr->socket = INVALID_SOCKET;
                    }
                    socktmp = sockptr->next;

                    CloseHandle(sockptr->thread);
                    RemoveSockInfo(&gSocketList, sockptr);
                    HeapFree(GetProcessHeap(), 0, sockptr);

                    LeaveCriticalSection(&gListCritSec);

                    sockptr = socktmp;
                }
                else if (r == WAIT_TIMEOUT)
                {
                    sockptr = sockptr->next;
                }
                else if (r == WAIT_FAILED)
                {
                    fRet = FALSE;
                    break;
                }
            }
            if (fRet == FALSE)
                break;

            continue;
        }

        //
        // Accept an incoming request.
        //

        addrlen = sizeof(SOCKADDR_AT);
        newsock = accept(sock, (struct sockaddr *)&atalkaddr, &addrlen);

        if (newsock == INVALID_SOCKET)
        {
            printf("Accept: Socket Error = %d\n", WSAGetLastError());

            fRet = FALSE;
            break;
        }

        printf("Accepted connection from %x:%x:%x\n",
                atalkaddr.sat_net,
                atalkaddr.sat_node,
                atalkaddr.sat_socket);

        test = (PTEST_INFO) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TEST_INFO));  
        if (test == NULL)
        {
            fprintf(stderr, "HeapAlloc failed: %d\n", GetLastError());
            closesocket(newsock);
            fRet = FALSE;
            break;
        }

        test->socket_type = sockettype;
        test->protocol    = protocoltype;
        test->socket      = newsock;

        InsertSockInfo(&gSocketList, test);

        test->thread = CreateThread(
                 NULL, 
                 0, 
                 (LPTHREAD_START_ROUTINE)PerfThread,
                 (PTEST_INFO) test, 
                 0, 
                 &ThreadId);
        if (test->thread == NULL)
        {
            fprintf(stderr,"CreateThread NULL 0 PerfThread(%d, 0, %d, 0, %p)",
                    test->socket_type, test->protocol, &ThreadId);
            fRet = FALSE;
            break;
        }

        if (fRet == FALSE)
        {
            break;
        }

    } while (TRUE);

    closesocket(sock);

    //
    // send all done - force client threads to close if outstanding
    //
    sockptr = gSocketList;
    while (sockptr)
    {
        // Close the socket
        EnterCriticalSection(&gListCritSec);
        if (sockptr->socket != INVALID_SOCKET)
        {
            closesocket(sockptr->socket);
            sockptr->socket = INVALID_SOCKET;
        }
        LeaveCriticalSection(&gListCritSec);

        // Once socket is closed, client thread should exit thread on an error
        r = WaitForSingleObject(sockptr->thread, 10000);
        if (r == WAIT_FAILED)
        {
            fprintf(stderr, "WaitForSingleObject failed: %d\n", GetLastError());
        }
        else if (r == WAIT_TIMEOUT)
        {
            fprintf(stderr, "Thread not closing in a timely fashion!\n");
        }

        // Close the thread handle and free the structure
        socktmp = sockptr->next;

        CloseHandle(sockptr->thread);
        RemoveSockInfo(&gSocketList, sockptr);
        HeapFree(GetProcessHeap(), 0, sockptr);

        sockptr = socktmp;
    }

    DeleteCriticalSection(&gListCritSec);

    return(TRUE);
}


/******************************************************************************
 
 Function - PerfThread()

 Calling Function - OpenSocketRegisterAndListen();

 Comments - This section of code controls the Server side Recieve and Verification
            for the application.
            
******************************************************************************/

unsigned long PerfThread( PTEST_INFO lpvTest )
{
    int     r;                          // return from socket calls
    int     recvflags = 0;              // see WSARecvEx call
    CHAR    recvbuf[BLOCKSIZE];         // recv buffer
    u_long  blockmode = 1;              // see ioctlsocket call
    BOOL    fRet = TRUE;
    int     NumBytesRecvd = 0;

    //
    // make socket non blocking. As far as possible, use non
    // blocking sockets to improve performance of app.
    //
    //

    r = ioctlsocket(lpvTest->socket, FIONBIO, &blockmode);

    if( r == SOCKET_ERROR)
    {
        printf("ioctlsocket: error = %d\n", WSAGetLastError());
        fRet = FALSE;
        ExitThread(FALSE);
    }

    do
    {
        //
        // Prime a Read here. This will enable the receive to complete
        // This is PAP specific. For other AppleTalk protocols -
        // ADSP and DDP a recv can be posted directly
        //

        if(!_strnicmp(gProtocolName, "PAP", 3))
        {

            r = setsockopt(lpvTest->socket,
                    SOL_APPLETALK,
                    SO_PAP_PRIME_READ,
                    recvbuf,
                    sizeof(recvbuf));

            if (r == SOCKET_ERROR)
            {
                printf("primeread: error = %d\n", WSAGetLastError());
                fRet = FALSE;
                break;
            }
        }

        fRet = CheckForRecv(lpvTest->socket);

        if (fRet == FALSE)
            break;

        recvflags = 0;
        r = WSARecvEx(lpvTest->socket,recvbuf,sizeof(recvbuf), &recvflags);

        if( r == SOCKET_ERROR)
        {

            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                continue;
            }
            else
            {
                if(WSAGetLastError() == WSAENOTCONN || WSAGetLastError() == WSAEFAULT)
                    break;
                printf("recv: error = %d\n", WSAGetLastError());
                fRet = FALSE;
                break;
            }

        }
        if (r == 0)
             break;

        if ((lpvTest->socket_type == SOCK_RDM) && (r < sizeof(recvbuf)))
        {
            printf("Did not receive entire message (%d bytes)\n", r);
            fRet = FALSE;
            break;
        }

        printf("Recvd %d bytes\n", r);

        if (fVerify)
        {
            int rr, sendoffset, sendleft;

            sendoffset = 0;
            sendleft   = r;

            do
            {
                fRet = CheckForSend(lpvTest->socket);

                if (fRet == FALSE)
                {
                    printf("send select error\n");
                    break;
                }

                rr = send(lpvTest->socket, &recvbuf[sendoffset], sendleft, 0);   

                if ( rr == SOCKET_ERROR )
                {
                    if(WSAGetLastError() == WSAEWOULDBLOCK)
                    {  
                        printf("Send: error = WSAEWOULDBLOCK\n");
                        continue;
                    }
                    else
                    {
                        printf("send: error = %d\n", WSAGetLastError());
                        break;
                    }

                }

                printf("Bytes Sent %d\n", rr);

                sendoffset += rr;
                sendleft   -= rr;

            } while(sendleft > 0);

        }  // endif Verify


        NumBytesRecvd += r;

    } while(TRUE);

    printf("Total Number of Bytes Received = %d \n",NumBytesRecvd);

    EnterCriticalSection(&gListCritSec);

    closesocket(lpvTest->socket);
    lpvTest->socket = INVALID_SOCKET;

    LeaveCriticalSection(&gListCritSec);

    ExitThread(TRUE);
}

/******************************************************************************
 
 Function - DoClient()

 Calling Function - main();

 Comments - This section of code controls the Client side of the application.
            
******************************************************************************/

BOOL DoClient()
{
    int                  r = 0;             // return code
    BOOL                 fRet = FALSE;      //
    CHAR                 LookupBuffer[512]; // LookUp results return buffer
    PCHAR                ptupleBuffer;
    PWSH_LOOKUP_NAME     pLookup;
    PWSH_NBP_TUPLE       pTempTuple;
    SOCKADDR_AT          ataddress;
    int                  WrittenSize;
    SOCKET               clntsock;
    u_long               blockmode = 1;          // for ioctlsocket
    int                  BytesTransferred = 0;
    char *               memhandle;
    DWORD                hourdiff;          //, minutediff, seconddiff;
    double               StartSecond, EndSecond, ElapsedSeconds;
    int                  sendleft, sendoffset, recvleft, recvoffset;
    int                  sockettype = SOCK_STREAM;
    int                  prototype = ATPROTO_ADSP;
    size_t               i,copycount;

    if (!_strnicmp(gProtocolName, "PAP", 3))
    {
        sockettype = SOCK_RDM;
        prototype = ATPROTO_PAP;
    }
    else if (fRDM)
    {
        sockettype = SOCK_RDM;
    }

    do
    {
        //
        // See socket call in OpenSocketRegisterAndListen for desc
        //
        clntsock = socket(AF_APPLETALK, sockettype, prototype);

        if(clntsock == INVALID_SOCKET)
        {
            printf("Open Socket: Error = %ld\n", WSAGetLastError());
            r = SOCKET_ERROR;
            break;
        }

        ataddress.sat_socket = 0;
        ataddress.sat_family = AF_APPLETALK;

        r = bind(clntsock, (struct sockaddr *)&ataddress, sizeof(SOCKADDR_AT));

        if (r == SOCKET_ERROR)
        {
            printf("Bind:Error = %d\n", WSAGetLastError());
            break;
        }

        //
        // end point has now been created on the AppleTalk Protocol.
        // lookup the server name.
        //

        pLookup = (PWSH_LOOKUP_NAME)LookupBuffer;

        strncpy(pLookup->LookupTuple.NbpName.ObjectName, gServerName, MAX_ENTITY-1);
        pLookup->LookupTuple.NbpName.ObjectNameLen = (char) strlen(gServerName);

        strncpy(pLookup->LookupTuple.NbpName.TypeName,  gServerType, MAX_ENTITY-1);
        pLookup->LookupTuple.NbpName.TypeNameLen = (char) strlen(gServerType);

        strncpy(pLookup->LookupTuple.NbpName.ZoneName, gServerZone, MAX_ENTITY-1);
        pLookup->LookupTuple.NbpName.ZoneNameLen = (char) strlen(gServerZone);

        printf("Looking up %s:%s@%s\n",
                pLookup->LookupTuple.NbpName.ObjectName,
                pLookup->LookupTuple.NbpName.TypeName,
                pLookup->LookupTuple.NbpName.ZoneName);

        WrittenSize = sizeof(LookupBuffer);

        r = getsockopt(clntsock, SOL_APPLETALK, SO_LOOKUP_NAME,
                (char*)LookupBuffer,
                &WrittenSize);

        if(r == SOCKET_ERROR)
        {
            printf("getsockopt:error = %d\n", WSAGetLastError());
            break;

        }

        if (pLookup->NoTuples <= 0)
        {
            printf("LookupName failed - no tuples found\n");
            r=-1;
            break;
        }

        ptupleBuffer = (char *)pLookup+sizeof(WSH_LOOKUP_NAME);
        pTempTuple = (PWSH_NBP_TUPLE)ptupleBuffer;

        ataddress.sat_family = AF_APPLETALK;
        ataddress.sat_net = pTempTuple[0].Address.Network;
        ataddress.sat_node = pTempTuple[0].Address.Node;
        ataddress.sat_socket = pTempTuple[0].Address.Socket;

        printf("server address = %lx.%lx.%lx.\n", ataddress.sat_net,
                ataddress.sat_node,
                ataddress.sat_socket);

        //
        // lookup succeeded. Use the address in ataddress to connect to the
        // server
        //

        r =  connect(clntsock, (struct sockaddr *)&ataddress, sizeof(SOCKADDR_AT));

        if (r == SOCKET_ERROR)
        {
            printf("connect: error = %d\n", WSAGetLastError());
            break;
        }

#ifdef DEBUG
        //       printf("Connect Succeeded\n");
#endif


    }while(FALSE);

    if (r == SOCKET_ERROR)
    {
        if (clntsock != INVALID_SOCKET)
        {
            closesocket(clntsock);
            clntsock = INVALID_SOCKET;
        }
        return(FALSE);
    }

    //
    //  Set Socket to non blocking mode
    //

    r = ioctlsocket(clntsock, FIONBIO, &blockmode);

#ifdef DEBUG
    //       printf("ioctlsocket Succeeded\n");
#endif

    if( r == SOCKET_ERROR)
    {
        printf("ioctlsocket: error = %d\n", WSAGetLastError());
        return FALSE;
    }

    //
    // Fill Up Send Buffer with Data
    //
    memhandle = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, BLOCKSIZE);
    if (memhandle == NULL)
    {
        printf("LocalAlloc Failed %d\n", GetLastError());
        closesocket(clntsock);
        return(FALSE);
    }

    //
    // fill the buffer with Data
    //
    i = 0;
    while (i < BLOCKSIZE)
    {
        if (i+strlen(DataString) <= BLOCKSIZE)
            copycount = strlen(DataString);
        else
            copycount = BLOCKSIZE - i;
        memcpy(&memhandle[i], DataString, copycount);
        i += copycount;
    }
    memhandle[BLOCKSIZE-1] = '\0';

    fRet = CheckForSend(clntsock);

    if(fRet == FALSE)
    {
        closesocket(clntsock);
        HeapFree(GetProcessHeap(), 0, memhandle);
        return FALSE;
    }

    GetLocalTime(&SystemStartTime);

#ifdef DEBUG
    printf("Data Size = %d\n", lstrlen(memhandle)+1);
    //   printf("Base Data sent: %s\n",DataStartPtr);
    printf("Start Time:%d:%2d:%2d:%2d\t", SystemStartTime.wHour,
            SystemStartTime.wMinute,
            SystemStartTime.wSecond,
            SystemStartTime.wMilliseconds);
#endif

    for( i= 0; i < gNumTimes; i++)
    {
        //
        // Can I send - CheckForSend calls select to find if we can send
        // without blocking
        //

        sendleft   = BLOCKSIZE;
        sendoffset = 0;

        do
        {
            fRet = CheckForSend(clntsock);

            if(fRet == FALSE)
            {
                printf("send select error\n");
                break;
            }

            r = send(clntsock, &memhandle[sendoffset], sendleft, 0);

            if ( r == SOCKET_ERROR )
            {

                if( WSAGetLastError() == WSAEWOULDBLOCK )
                {
                    printf("send: wouldblock\n");
                    continue;
                }
                else
                {
                    printf("send: error = %d\n", WSAGetLastError());
                    fRet = FALSE;
                    break;
                }

            }

            sendleft   -= r;
            sendoffset += r;

        } while(sendleft > 0);

        if (fRet == FALSE)
            break;

        printf("Sent %d bytes\n", sendoffset);

        if ((fVerify) && (sendleft == 0))
        {
            CHAR buffer[BLOCKSIZE];
            int recvflag = 0;
            int rr, pos = 0;

            //
            // Prime a Read here. This will enable the receive to complete
            // This is PAP specific. For other AppleTalk protocols -
            // ADSP and DDP a recv can be posted directly
            //

            if(!_strnicmp(gProtocolName, "PAP", 3))
            {
                rr = setsockopt(clntsock,
                        SOL_APPLETALK,
                        SO_PAP_PRIME_READ,
                        buffer,
                        sizeof(buffer));

                if (rr == SOCKET_ERROR)
                {
                    printf("primeread: error = %d\n", WSAGetLastError());
                    fRet = FALSE;
                    break;
                }
            }

            recvleft   = sendoffset;
            recvoffset = 0;
            do
            {

                fRet = CheckForRecv(clntsock);

                if(fRet == FALSE)
                    break;

                recvflag = 0;
                rr = WSARecvEx(clntsock, &buffer[recvoffset], recvleft, &recvflag);

                if( rr == SOCKET_ERROR)
                {
                    if (WSAGetLastError() == WSAEWOULDBLOCK)
                        continue;
                    else
                    {
                        printf("recv: error = %d\n", WSAGetLastError());
                        fRet = FALSE;
                        break;
                    }
                }

                recvoffset += rr;
                recvleft   -= rr;

                printf("Recv'd %d bytes\n", rr);

                if ( (recvflag == 0) || (sockettype == SOCK_RDM) || 
                        (recvleft == 0)  )
                    break;

            } while(recvleft > 0);


            if ((memcmp(memhandle, buffer, BLOCKSIZE) != 0) && (fRet != FALSE))
            {
                printf("Strings do not compare\n");
#ifdef DEBUG
                //                       printf("Data sent: \n%s\n",memhandle);
                //                       printf("Data recv'd: \n%s\n",buffer);
#endif

            }


        } // IF (fVerify)

        BytesTransferred += sendoffset;


    } // FOR

    GetLocalTime(&SystemEndTime);

#ifdef DEBUG
    printf("End Time:%d:%2d:%2d:%2d\t", SystemEndTime.wHour,
            SystemEndTime.wMinute,
            SystemEndTime.wSecond,
            SystemEndTime.wMilliseconds);
#endif

    //
    // calculate the difference
    //

    hourdiff = SystemEndTime.wHour - SystemStartTime.wHour;

    StartSecond = (SystemStartTime.wHour * 3600) +
        (SystemStartTime.wMinute * 60) +
        SystemStartTime.wSecond +
        (SystemStartTime.wMilliseconds * 0.001);

    EndSecond = 0;

    if(SystemEndTime.wMonth != SystemStartTime.wMonth)
    {
        EndSecond = (SystemEndTime.wDay * 24) * 3600;
        switch (SystemStartTime.wMonth)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                EndSecond = ((31 - SystemStartTime.wDay) * 24) + EndSecond;
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                EndSecond = ((30 - SystemStartTime.wDay) * 24) + EndSecond;
                break;
            case 2:
                if((SystemStartTime.wYear % 400 == 0) || 
                        ((SystemStartTime.wYear % 4 == 0) &&
                         (SystemStartTime.wYear % 100 != 0)))
                    EndSecond = ((29 - SystemStartTime.wDay) *
                            24) + EndSecond;
                else
                    EndSecond = ((28 - SystemStartTime.wDay) *
                            24) + EndSecond;
                break;
        }
    }
    else
        if(SystemEndTime.wDay > SystemStartTime.wDay)
        {
            EndSecond = ((SystemEndTime.wDay - SystemStartTime.wDay) * 24) * 3600;
        }

    EndSecond = EndSecond + (SystemEndTime.wHour * 3600) +
        (SystemEndTime.wMinute * 60) + SystemEndTime.wSecond +
        (SystemEndTime.wMilliseconds * 0.001);

    ElapsedSeconds = EndSecond-StartSecond;

#ifdef DEBUG
    printf("Elapsed Time (secs) = %6.3f\n", ElapsedSeconds);
    printf("Bytes Transferred = %ld\n", BytesTransferred);
    printf("Send All Done\n");
#endif


    if(ElapsedSeconds !=0)
    {
        Throughput = (BytesTransferred)/(ElapsedSeconds) ;

#ifdef DEBUG
        printf("Throughput (bytes/sec) = %6.2f\n", Throughput);
#endif

    }

    printf("\n");

    closesocket(clntsock);

    HeapFree(GetProcessHeap(), 0, memhandle);

    return(TRUE);

}

/******************************************************************************
 
 Function - CheckForSend()

 Comments - Calls select with the given socket handle to determine if it is
            writeable.
            
******************************************************************************/
BOOL CheckForSend(SOCKET s)
{

   fd_set writefds;
   int r;


#ifdef DEBUG
   printf("\t\tChecking for Send..\n");
#endif

   FD_ZERO(&writefds);
   FD_SET(s, &writefds);

   //
   // indefinite wait select
   //
   r = select(0, NULL, &writefds, NULL, NULL);

   if (r != 1)
   {
       printf("select:error = %d\n", WSAGetLastError());
       return(FALSE);
   }
   return(TRUE);
}
  
/******************************************************************************
 
 Function - CheckForRecv()

 Comments - Calls select with the given socket handle to determine if the socket
            is readable.
            
******************************************************************************/
BOOL CheckForRecv(SOCKET s)
{

   fd_set readfds;
   int r;

   FD_ZERO(&readfds);
   FD_SET(s, &readfds);

#ifdef DEBUG
   printf("\t\tChecking for Recv..\n");
#endif

   r = select(0, &readfds, NULL, NULL, NULL);

   if (r != 1)
   {
       printf("select:error = %d\n", WSAGetLastError());
       return(FALSE);
   }
   return(TRUE);
}

void usage()
{

   printf("prperf -s/c <options>\n");
   printf("\t-s/c\t Server/Client\n");
   printf("\t-n\t Server Name\n");
   printf("\t-t\t Server Type \n");
   printf("\t-z\t Server Zone \n");
   printf("\t-p\t Protocol Name (ADSP/PAP)\n");
   printf("\t-b\t Number of times to send a 4k buffer (Default = 5) \n");
   printf("\t-l\t Number of times to re-start prperf (Default = 1) (Client only)\n");
   printf("\t-v\t Verify Integrity of data transmission. \n");
   printf("\t-y\t Change ADSP to use SOCK_RDM instead of SOCK_STREAM. \n");
   printf("\n");
   exit(1);

}
