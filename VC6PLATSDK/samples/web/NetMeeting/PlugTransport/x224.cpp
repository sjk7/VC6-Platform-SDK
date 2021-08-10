//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       X224.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"


//****************************************************************************
//
//    FUNCTION:   CX224::CX224()
//
//    PURPOSE:    Construction

//    COMMENTS:
//       
//
//****************************************************************************

CX224::CX224()
{
    m_hListenSocket = INVALID_SOCKET;
    m_hSocket = INVALID_SOCKET;
    m_szHostName[0] = '\0';
}


//****************************************************************************
//
//    FUNCTION:   CX224::~CX224()
//
//    PURPOSE:    Destruction

//    COMMENTS:
//      
//
//****************************************************************************

CX224::~CX224()
{}


//****************************************************************************
//
//    FUNCTION:   HRESULT CX224::CreateListenSocket(HWND hwnd)
//
//    PURPOSE:    Creates a listen socket ready to accept connections

//    COMMENTS:
//     
//
//****************************************************************************

HRESULT CX224::CreateListenSocket(HWND hwnd)
{
    SOCKADDR_IN socket_control;
    SOCKET      socket_number   = INVALID_SOCKET;

    // We are already have created a listenning socket
    if (m_hListenSocket != INVALID_SOCKET)
        return S_OK;

    // Create the listening socket.
    socket_number = ::socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == socket_number)
        return E_FAIL;

    // The listen socket only waits for FD_ACCEPT msgs.
    int nRet = ::WSAAsyncSelect(socket_number, hwnd, WM_PLUGABLE_SOCKET, FD_ACCEPT);
    if (SOCKET_ERROR == nRet)
        return E_FAIL;
    
    
    // Load the socket control structure with the parameters necessary.
    // Internet socket
    // Let it assign any address to this socket
    // Assign our port number
    socket_control.sin_family = AF_INET;
    socket_control.sin_addr.s_addr = INADDR_ANY;
    socket_control.sin_port = htons(PLUGABLE_PORT_NUMBER);

    char * szReuse = "1";
    nRet = setsockopt(socket_number, SOL_SOCKET, SO_REUSEADDR, szReuse, sizeof(int));

    // Issue the bind call
    nRet = ::bind(socket_number, (LPSOCKADDR) &socket_control, sizeof(SOCKADDR_IN));
    if (SOCKET_ERROR == nRet)
    {
        return E_FAIL;
    }

    // Issue a listen to WinSock to tell it we are willing to accept calls.
    // This is a non-blocking listen, therefore we will receive FD_ACCEPT
    // if someone is trying to call us.
    nRet =::listen(socket_number, 3); // LISTEN_QUEUE_SIZE
    if (SOCKET_ERROR == nRet)
        return E_FAIL;

    m_hListenSocket = socket_number;
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CX224::CreateConnectSocket(HWND hwnd, LPSTR pszHostName)
//
//    PURPOSE:    Creates a socket and establishes a connection to it

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT CX224::CreateConnectSocket(HWND hwnd, LPSTR pszHostName)
{
    SOCKET      socket_number   = INVALID_SOCKET;
    u_short     uPort           = PLUGABLE_PORT_NUMBER;
    PHOSTENT    phe             = NULL;
    SOCKADDR_IN socket_control;
    DWORD       dwIPAddress     = 0;

    lstrcpyn(m_szHostName, pszHostName, MAXHOSTNAMELENGTH);

    // create the connect socket
    socket_number = ::socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == socket_number)
        return HRESULT_FROM_WIN32(WSAGetLastError());

    // Enable Tx and Rx messages to the window
    int nRet = ::WSAAsyncSelect(socket_number, hwnd, WM_PLUGABLE_SOCKET,
                           FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT);
    if (SOCKET_ERROR == nRet)
        return E_FAIL;

    // fill in other info in SockAddr
    ::ZeroMemory(&socket_control, sizeof(socket_control));
    socket_control.sin_family = AF_INET;
    socket_control.sin_port = htons (PLUGABLE_PORT_NUMBER);

    // get server's IP address
    dwIPAddress = ::inet_addr(m_szHostName);
    if (dwIPAddress != INADDR_NONE)
    {
        *((PDWORD) &socket_control.sin_addr) = dwIPAddress;
    }
    else
    {
        phe = ::gethostbyname(m_szHostName);
        if (NULL == phe)
        {
            return 0;
        }

        ::CopyMemory(&socket_control.sin_addr, phe->h_addr, phe->h_length);
    }

    // Attempt a connection to the remote site
    nRet = ::connect(socket_number, (const struct sockaddr *) &socket_control, sizeof(socket_control));
//    if (SOCKET_ERROR == nRet) //&& WSAEWOULDBLOCK != ::WSAGetLastError())
//        return E_FAIL;

    m_hSocket = socket_number;
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CX224::CreateAcceptSocket(HWND hWnd)
//
//    PURPOSE:    Accepts an incoming connection attempt on a socket

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CX224::CreateAcceptSocket(HWND hWnd)
{
    SOCKADDR_IN socket_control;
    int         size    = sizeof(socket_control);
    int         nRet    = 0;
    
    m_hSocket = accept(m_hListenSocket, (struct sockaddr *) &socket_control, &size);
    if (INVALID_SOCKET == m_hSocket)
    {
        return HRESULT_FROM_WIN32(WSAGetLastError());
    }

    nRet = ::WSAAsyncSelect(    m_hSocket, 
                                hWnd,
                                WM_PLUGABLE_SOCKET, 
                                FD_READ | FD_WRITE | FD_CLOSE | FD_CONNECT);
    if (SOCKET_ERROR == nRet)
       return E_FAIL;

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   LPSTR CX224::SetAndGetHostName()
//
//    PURPOSE:    Sets and returns the host name of the machine where 
//                the application runs

//    COMMENTS:
//       
//
//****************************************************************************

LPSTR CX224::SetAndGetHostName()
{
    gethostname(m_szHostName, MAXHOSTNAMELENGTH);
    return m_szHostName;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CX224::CloseSocket()
//
//    PURPOSE:  

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CX224::CloseSocket()
{
    HRESULT hr = S_FALSE;

    if (m_hSocket != INVALID_SOCKET)
    {
        closesocket(m_hListenSocket);
        m_hSocket = INVALID_SOCKET;
        hr = S_OK;
    }

    // close listen socket also
    CloseListenSocket();

    return hr;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CX224::CloseListenSocket()
//
//    PURPOSE:    Close the listen socket. We stop accepting new connections after it

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CX224::CloseListenSocket()
{
    if (m_hListenSocket != INVALID_SOCKET)
    {
        closesocket(m_hListenSocket);
        m_hListenSocket = INVALID_SOCKET;
        return S_OK;
    }

    return S_FALSE;
}


//****************************************************************************
//
//    FUNCTION:   SOCKET CX224::GetSocket()
//
//    PURPOSE: 

//    COMMENTS:
//     
//
//****************************************************************************

SOCKET CX224::GetSocket()
{
  return m_hSocket;
}
