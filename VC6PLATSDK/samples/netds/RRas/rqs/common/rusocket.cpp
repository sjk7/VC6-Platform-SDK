//+--------------------------------------------------------------------------
//
//      File:       RuSocket.h
//
//      Synopsis:   Simply socket abstraction.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------


#include "rasutil.h"
#include <winsock2.h>

//+--------------------------------------------------------------------------
//
// Synopsis: Utility function to look up the procedure address for the 
//           WSAEventSelect function. This allows code using socket classes
//           to work on platforms that don't have ws2_32.dll installed.
//
//+--------------------------------------------------------------------------
pfnWSAEventSelectSpec LookupWSAEventSelect()
{
    pfnWSAEventSelectSpec pfnWSAEventSelect = NULL;
    
    HMODULE hWinsock2 = GetModuleHandle(TEXT("ws2_32.dll"));

    if (hWinsock2)
    {
        pfnWSAEventSelect = (pfnWSAEventSelectSpec)GetProcAddress(hWinsock2, "WSAEventSelect");
    }

    return pfnWSAEventSelect;
}

//+--------------------------------------------------------------------------
//
// Synopsis: A socket
//
//+--------------------------------------------------------------------------
typedef struct _RU_SOCKET 
{
    SOCKET Socket;
    SOCKADDR addr;
    UINT uiSize;
    
} RU_SOCKET;

//+--------------------------------------------------------------------------
//
// Synopsis: Initialize the socket library
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketInit () 
{
    INT iErr;
    WSADATA wsaData;

    iErr = WSAStartup (MAKEWORD(2, 0), &wsaData);
    if (iErr != 0)
    {
        return HRESULT_FROM_WIN32(iErr);
    }       
    
    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Cleans up the socket library
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketCleanup () 
{
    INT iErr;

    iErr = WSACleanup();
    if (iErr != 0)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }       
    
    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Creates a client socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketCreate(
    IN RU_SOCKET_CREATE_DATA* pCreateData, 
    OUT HSOCKET* phSocket) 
{
    u_short uPort = (u_short)pCreateData->uiPort;
    RU_SOCKET* pSocket = NULL;
    struct hostent * pHost;
    SOCKADDR_IN sin, bindsin;
    SOCKET Socket;
    DWORD dwAddress, dwAddressS;
    HRESULT hr = S_OK;
    BOOL bOk = FALSE;
    INT iErr;

    // Lookup the host
    //
    pHost = gethostbyname (pCreateData->pszDest);
    if (pHost) 
    {
        dwAddress = (DWORD)(*((DWORD*)(pHost->h_addr_list[0])));
    }
    else 
    {
        dwAddress = inet_addr (pCreateData->pszDest);
    }

    dwAddressS = INADDR_ANY;
    if (pCreateData->pszSrc)
    {
        dwAddressS = inet_addr (pCreateData->pszSrc);
    }

    // Initialize the address
    //
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = dwAddress;
    sin.sin_port = htons (uPort);

    // Initialize the binding information
    //
    bindsin.sin_family = AF_INET;
    bindsin.sin_addr.s_addr = dwAddressS;
    bindsin.sin_port = 0;

    // Initailiaze the return value
    //
    *phSocket = NULL;
    pSocket = (RU_SOCKET*) RuAlloc(sizeof(RU_SOCKET), TRUE);
    if (! pSocket)
    {
        return E_OUTOFMEMORY;
    }
    pSocket->uiSize = sizeof(pSocket->addr);

    __try
    {
        // Create a new socket
        //
        Socket = socket (PF_INET, SOCK_STREAM, 0);
        if (Socket == INVALID_SOCKET)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }

        // Bind the socket to the given port
        //
        iErr = bind(Socket, (LPSOCKADDR)&bindsin, sizeof(bindsin));
        if (iErr != 0)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }

        // Connect to the remote machine
        //
        iErr = connect(Socket, (LPSOCKADDR)&sin, sizeof(sin));
        if (iErr != 0)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }
        
        pSocket->Socket = Socket;
        bOk = TRUE;
        
    }

    __finally
    {
        if (! bOk) 
        {
            RuFree (pSocket);
            pSocket = NULL;
        }
    }

    // Set the return value
    *phSocket = pSocket;
    
    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Creates a server socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketCreateServer (
    IN  RU_SOCKET_CREATE_DATA* pCreateData, 
    OUT HSOCKET * phServerSock)
{
    RU_SOCKET* pSocket = NULL;
    SOCKADDR_IN sin;
    SOCKET Socket;
    BOOL bOk = FALSE;
    INT iErr;
    HRESULT hr = S_OK;
    DWORD dwAddress;
    
    // Initialize the addr
    //
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons ((USHORT)pCreateData->uiPort);

    // Initailiaze the return value
    //
    *phServerSock = NULL;
    pSocket = (RU_SOCKET*) RuAlloc(sizeof(RU_SOCKET), TRUE);
    if (! pSocket)
    {
        return E_OUTOFMEMORY;
    }
    pSocket->uiSize = sizeof(pSocket->addr);

    __try
    {
        if (pCreateData->pszDest)
        {
            dwAddress = inet_addr (pCreateData->pszDest);
            sin.sin_addr.s_addr = dwAddress;
        }
        
        // Create a new socket
        //
        Socket = socket (PF_INET, SOCK_STREAM, 0);
        if (Socket == INVALID_SOCKET)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }

        // Bind the socket to the given port
        //
        iErr = bind(Socket, (LPSOCKADDR)&sin, sizeof(sin));
        if (iErr != 0)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }

        // Listen
        //
        iErr = listen (Socket, SOMAXCONN);
        if (iErr != 0)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }

        pSocket->Socket = Socket;
        bOk = TRUE;
        
    }

    __finally
    {
        if (! bOk) 
        {
            RuFree (pSocket);
            pSocket = NULL;
        }
    }

    // Set the return value
    //
    *phServerSock = pSocket;
    
    return hr;

}
        
//+--------------------------------------------------------------------------
//
// Synopsis: Causes a server socket to listen on its port and return a client 
//           socket when a connection is established.
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketListen (
    IN HSOCKET pServer, 
    OUT HSOCKET* phSocket) 
{
    RU_SOCKET* pClient = NULL;
    HRESULT hr = S_OK;

    if (! pServer)
    {
        return E_INVALIDARG;
    }
    
    // Initailiaze the return value
    //
    *phSocket = NULL;
    pClient = (RU_SOCKET*) RuAlloc(sizeof(RU_SOCKET), TRUE);
    if (! pClient)
    {
        return E_OUTOFMEMORY;
    }
    pClient->uiSize = sizeof(pClient->addr);

    __try
    {
        // Accept the connection
        //
        pClient->Socket = accept (
                            pServer->Socket, 
                            &(pClient->addr), 
                            (INT*)&(pClient->uiSize));
        if (pClient->Socket == INVALID_SOCKET)
        {
            hr = HRESULT_FROM_WIN32(WSAGetLastError());
            __leave;
        }

        // Assign the return value
        //
        *phSocket = pClient;
        
    }        

    __finally
    {
        if (hr != S_OK)
        {
            if (pClient)
            {
                RuFree(pClient);
            }
        }
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Closes a socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketClose (
    IN HSOCKET pSocket) 
{
    // Validate 
    //
    if (! pSocket)
    {
        return E_INVALIDARG;
    }

    // Close the socket
    //
    closesocket (pSocket->Socket);
    
    // Free 
    //
    RuFree (pSocket);

    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reads from a socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketRead (
    IN      HSOCKET pSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT* lpdwBufSize)
{
    INT iRet;

    // Validate 
    //
    if (! pSocket)
    {
        return E_INVALIDARG;
    }

    // Read from the socket
    //
    iRet = recv (pSocket->Socket, (CHAR*)pbBuffer, *lpdwBufSize, 0);
    if (iRet == SOCKET_ERROR)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }

    // Record the bytes read
    //
    *lpdwBufSize = iRet;

    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reads from a socket
//
//+--------------------------------------------------------------------------
HRESULT
RuSocketReadBlock(
    IN HSOCKET pSocket, 
    IN BYTE* pbBuffer, 
    IN OUT UINT* lpuiBufSize)
{
    HRESULT hr;
    INT iRet;
    fd_set fdSet;

    hr = RuSocketRead(pSocket, pbBuffer, lpuiBufSize);
    if (S_OK == hr)
    {
        return hr;
    }
    else if (HRESULT_FROM_WIN32(WSAEWOULDBLOCK) == hr)
    {
        ZeroMemory(&fdSet, sizeof(fdSet));
        FD_SET(pSocket->Socket, &fdSet);

        // Block until there is read data
        //
        iRet = select(0, &fdSet, NULL, NULL, NULL);
        if (iRet == SOCKET_ERROR)
        {
            return HRESULT_FROM_WIN32(WSAGetLastError());
        }

        // Read the data that has arrived
        //
        hr = RuSocketRead(pSocket, pbBuffer, lpuiBufSize);
    }

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: 
//
//   Read variant that does not block.  Rather, it returns everything that
//   has been received up till now.
//
//   Sets pbNoMore to true if everything currently received off the wire
//   has been consumed.
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketReadCurrent (
    IN      HSOCKET pSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT* lpdwBufSize,
    OUT     BOOL* pbNoMore)
{
    HRESULT hr = S_OK;
    fd_set fdSet;
    int iRet;
    struct timeval timeout;

    // Initialize the socket set
    //
    ZeroMemory(&fdSet, sizeof(fdSet));
    FD_SET(pSocket->Socket, &fdSet);

    // Initialize the timeout
    //
    ZeroMemory(&timeout, sizeof(timeout));
    timeout.tv_sec = 0;
    timeout.tv_usec = 1000;

    // Get the read status of the socket
    //
    iRet = select(0, &fdSet, NULL, NULL, &timeout);

    // Error
    //
    if (iRet == SOCKET_ERROR)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }

    // Timeout -- there is nothing to read
    //
    if (iRet == 0)
    {
        *pbNoMore = TRUE;
        return S_OK;
    }

    // There's something to read
    //
    *pbNoMore = FALSE;
    return RuSocketRead(pSocket, pbBuffer, lpdwBufSize);
    
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reads a line of text from a socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketReadLine (
    IN      HSOCKET pSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT* lpdwBufSize)
{
    HRESULT dwMaxSize = *lpdwBufSize, i = 0;
    INT iRet;
    BYTE bCur = '\n';
    HRESULT hr = S_OK;

    // Validate 
    //
    if (! pSocket)
    {
        return E_INVALIDARG;
    }

    while (i < dwMaxSize)
    {
        iRet = recv (pSocket->Socket, (CHAR*)&bCur, 1, 0);
        if (iRet == SOCKET_ERROR)
        {
            return HRESULT_FROM_WIN32(WSAGetLastError());
        }
        else if (iRet == 0)
        {
            hr = HRESULT_FROM_WIN32(ERROR_HANDLE_EOF);
            break;
        }
        if (bCur == '\r')
        {
            continue;
        }
        if (bCur == '\n')
        {
            break;
        }
        *pbBuffer = bCur;
        pbBuffer++;
        i++;
    }
        
    *pbBuffer = 0;
    if (i > 0)
    {
        i++;
    }

    // Record the bytes read
    //
    *lpdwBufSize = i;

    return hr;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Writes to a socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketWrite(
    IN      HSOCKET pSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT* lpdwBufSize)
{
    INT iRet;

    // Validate 
    //
    if (! pSocket)
    {
        return E_INVALIDARG;
    }

    // Read from the socket
    //
    iRet = send (pSocket->Socket, (const CHAR*)pbBuffer, *lpdwBufSize, 0);
    if (iRet == SOCKET_ERROR)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }

    // Record the bytes read
    //
    *lpdwBufSize = iRet;

    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Writes a line to a socket, appending the carriage return and 
//           line feed if needed.
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocketWriteLine(
    IN      HSOCKET pSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT* lpdwBufSize)
{
    DWORD dwMaxSize = *lpdwBufSize, i = 0, uiSize;
    INT iRet;
    BYTE bCur = 0;

    // Validate 
    //
    if (! pSocket)
    {
        return E_INVALIDARG;
    }

    // Send on the socket
    //
    while ((i < dwMaxSize) && (bCur != '\r') && (bCur != '\n')) 
    {
        uiSize = sizeof(bCur);
        bCur = *pbBuffer;
        iRet = send (pSocket->Socket, (CHAR*)&bCur, 1, 0);
        if (iRet == SOCKET_ERROR)
        {
            return HRESULT_FROM_WIN32(WSAGetLastError());
        }
        pbBuffer++;
        i++;
    }       

    // Send the newline
    //
    send (pSocket->Socket, "\r\n", 2, 0);

    // Record the bytes read
    //
    *lpdwBufSize = i;

    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: 
//
//   Get the socket address (address the socket is bound to) in network order.
//
//+--------------------------------------------------------------------------
HRESULT
RuSocketGetAddress(
    IN  HSOCKET pSocket,
    OUT DWORD*  lpdwAddress)
{
    struct sockaddr_in* pData = (struct sockaddr_in*)&(pSocket->addr);
    *lpdwAddress = *((DWORD*)&(pData->sin_addr));

    return S_OK;        
}

//+--------------------------------------------------------------------------
//
// Synopsis: C++ initialization of the socket library
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocket::Initialize() 
{
    return RuSocketInit();
}

//+--------------------------------------------------------------------------
//
// Synopsis: C++ cleanup of the socket library
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocket::Cleanup() 
{
    return RuSocketCleanup();
}

//+--------------------------------------------------------------------------
//
// Synopsis: Creates a socket
//
//+--------------------------------------------------------------------------
RuSocket::RuSocket() : m_hSocket(NULL) , m_pfnWSAEventSelect(NULL)
{
}

//+--------------------------------------------------------------------------
//
// Synopsis: Cleans up a socket
//
//+--------------------------------------------------------------------------
RuSocket::~RuSocket() 
{
    Close();
}

//+--------------------------------------------------------------------------
//
// Synopsis: Creates a socket from an HSOCKET.  Ownership of hSocket is given
//           to this instance of RuSocket.
//
//+--------------------------------------------------------------------------
VOID
RuSocket::Assign(
    IN HSOCKET hSocket)
{
    Close();
    m_hSocket = hSocket;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Opens a socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocket::Open(
    IN UINT uiPort,
    IN CHAR* pszHostOrIp,
    IN CHAR* pszIpSrc)
{
    RU_SOCKET_CREATE_DATA cData = {uiPort, pszHostOrIp, pszIpSrc};
    
    return RuSocketCreate(&cData, &m_hSocket);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Closes a socket
//
//+--------------------------------------------------------------------------
VOID
RuSocket::Close()
{
    if (m_hSocket) 
    {
        RuSocketClose(m_hSocket); 
        m_hSocket = NULL;
    }
}

//+--------------------------------------------------------------------------
//
// Synopsis: Retrieves the IPv4 address this socket is bound to.
//
//+--------------------------------------------------------------------------
HRESULT
RuSocket::GetAddress(
    OUT DWORD*  lpdwAddress)
{
    return RuSocketGetAddress(m_hSocket, lpdwAddress);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reads from a socket
//
//+--------------------------------------------------------------------------
HRESULT
RuSocket::Read(
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize,
    IN      BOOL   fBlock)
{
    if (fBlock)
    {
        return RuSocketReadBlock(m_hSocket, pbBuffer, lpuiBufSize);
    }
    
    return RuSocketRead(m_hSocket, pbBuffer, lpuiBufSize);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reads the next line of text from a socket
//
//+--------------------------------------------------------------------------
HRESULT
RuSocket::ReadLine(
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize)
{
    return RuSocketReadLine(m_hSocket, pbBuffer, lpuiBufSize);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Reads data current cached in a socket (already received)
//
//+--------------------------------------------------------------------------
HRESULT
RuSocket::ReadCurrent(
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize,
    OUT     BOOL*  pbNoMore)
{
    return RuSocketReadCurrent(m_hSocket, pbBuffer, lpuiBufSize, pbNoMore);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Writes to a socket
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocket::Write (
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize)
{
    return RuSocketWrite(m_hSocket, pbBuffer, lpuiBufSize);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Writes a line of text to a socket (appends carriage return and
//           linefeed if needed)
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocket::WriteLine (
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize)
{
    return RuSocketWriteLine(m_hSocket, pbBuffer, lpuiBufSize);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Causes this socket to signal when something transpires in the
//           system.
//
//+--------------------------------------------------------------------------
HRESULT 
RuSocket::SetEvent(
    IN HANDLE hEvent,
    IN LONG lFlags)
{
    INT iRet;
    
    if (m_hSocket == NULL)
    {
        return E_FAIL;
    }

    if (m_pfnWSAEventSelect == NULL)
    {
        m_pfnWSAEventSelect = LookupWSAEventSelect();

        if (m_pfnWSAEventSelect == NULL)
        {
            return E_FAIL;
        }
    }

    iRet = m_pfnWSAEventSelect(m_hSocket->Socket, hEvent, lFlags);
    if (iRet != 0)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }

    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Causes this socket to signal when something transpires in the
//           system.
//
//+--------------------------------------------------------------------------
HRESULT 
RuServerSocket::SetEvent(
    IN HANDLE hEvent,
    IN LONG lFlags)
{
    INT iRet;
    
    if (m_hSocket == NULL)
    {
        return E_FAIL;
    }

    if (m_pfnWSAEventSelect == NULL)
    {
        m_pfnWSAEventSelect = LookupWSAEventSelect();

        if (m_pfnWSAEventSelect == NULL)
        {
            return E_FAIL;
        }
    }

    iRet = m_pfnWSAEventSelect(m_hSocket->Socket, hEvent, lFlags);
    if (iRet != 0)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }

    return S_OK;
}

//+--------------------------------------------------------------------------
//
// Synopsis: Creates a server socket
//
//+--------------------------------------------------------------------------
RuServerSocket::RuServerSocket() : m_hSocket(NULL) , m_pfnWSAEventSelect(NULL)
{
}

//+--------------------------------------------------------------------------
//
// Synopsis: Cleans up a server socket
//
//+--------------------------------------------------------------------------
RuServerSocket::~RuServerSocket() 
{
    Close();
}

//+--------------------------------------------------------------------------
//
// Synopsis: Binds a server socket to a port and (optional) local address.
//
//+--------------------------------------------------------------------------
HRESULT
RuServerSocket::Create(
    IN  UINT uiPort,
    IN OPTIONAL CHAR* pszLocalIpAddress)
{
    RU_SOCKET_CREATE_DATA cData = {uiPort, pszLocalIpAddress};
    
    return RuSocketCreateServer(&cData, &m_hSocket);
}

//+--------------------------------------------------------------------------
//
// Synopsis: Closes a server socket, releasing the resources associated with 
//           it.
//
//+--------------------------------------------------------------------------
VOID
RuServerSocket::Close()
{
    if (m_hSocket) 
    {
        RuSocketClose(m_hSocket); 
        m_hSocket = NULL;
    }
}

//+--------------------------------------------------------------------------
//
// Synopsis: Causes the server socket to wait for the next client to connect.
//
//    args:
//       pClient - when a client connects, pClient is opened against the new
//                 client connection then the method returns.
//
//+--------------------------------------------------------------------------
HRESULT
RuServerSocket::Listen(
    OUT RuSocket* pClient)
{
    HSOCKET hSocket = NULL;
    HRESULT hr;

    hr = RuSocketListen(m_hSocket, &hSocket);
    if (S_OK == hr)
    {
        pClient->Assign(hSocket);
    }

    return hr;
}


