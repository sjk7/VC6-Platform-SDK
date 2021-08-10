//+--------------------------------------------------------------------------
//
//      File:       RuSocket.h
//
//      Synopsis:   Simple socket abstraction.
//
//      Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//+--------------------------------------------------------------------------

#pragma once

#include <winsock2.h>

#ifdef __cplusplus
extern "C" {
#endif

//
//  Typedef and utility function for looking up WSAEventSelect dynamically
//
typedef int (WINAPI *pfnWSAEventSelectSpec)(SOCKET, WSAEVENT, long);
pfnWSAEventSelectSpec LookupWSAEventSelect();

struct _RU_SOCKET;
typedef struct _RU_SOCKET* HSOCKET;

//+--------------------------------------------------------------------------
//
// Synopsis: Information needed to create a socket
//
//      args:
//          dwPort      Port to connect to (client) or listen on (server)
//          pszDest     IpAddress or DNS name to connect to (client) or bind
//                      to (server)
//
//+--------------------------------------------------------------------------
typedef struct _RU_SOCKET_CREATE_DATA 
{
    UINT uiPort;
    CHAR* pszDest;
    CHAR* pszSrc;
    
} RU_SOCKET_CREATE_DATA;

HRESULT 
RuSocketInit ();

HRESULT 
RuSocketCleanup ();

HRESULT 
RuSocketCreate (
    IN  RU_SOCKET_CREATE_DATA* pCreateData, 
    OUT HSOCKET* phSocket); 
        
HRESULT 
RuSocketCreateServer (
    IN  RU_SOCKET_CREATE_DATA* pCreateData, 
    OUT HSOCKET* phServerSock);
        
HRESULT 
RuSocketListen (
    IN  HSOCKET hServerSock, 
    OUT HSOCKET* phSocket);
        
HRESULT 
RuSocketClose (
    IN  HSOCKET IN phSocket);

HRESULT 
RuSocketRead (
    IN      HSOCKET hSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize);

HRESULT 
RuSocketReadBlock(
    IN      HSOCKET hSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize);

HRESULT 
RuSocketReadCurrent (
    IN      HSOCKET hSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize,
    OUT     BOOL*  pbNoMore);

HRESULT 
RuSocketReadLine (
    IN      HSOCKET hSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize);
        
HRESULT 
RuSocketWrite (
    IN      HSOCKET hSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize);

HRESULT 
RuSocketWriteLine (
    IN      HSOCKET hSocket,
    IN      BYTE*  pbBuffer,
    IN OUT  UINT*  lpuiBufSize);

HRESULT
RuSocketGetAddress(
    IN  HSOCKET hSocket,
    OUT DWORD*  lpdwAddress);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
//----------------------------------------------------------------------------
//
//                  C++ implementation (RuSocket class)
//
//----------------------------------------------------------------------------
class RuSocket
{
public:
    RuSocket();
    ~RuSocket();

    static HRESULT Initialize();
    static HRESULT Cleanup();

    VOID Assign(IN HSOCKET hSocket);

    HRESULT 
    Open(
        IN UINT uiPort, 
        IN CHAR* pszHostOrIpDst, 
        IN CHAR* pszIpSrc = NULL);
        
    VOID Close();

    HRESULT GetAddress(OUT DWORD*  lpdwAddress);

    HRESULT
    Read(
        IN      BYTE*  pbBuffer,
        IN OUT  UINT*  lpuiBufSize,
        IN      BOOL   fBlock = TRUE);

    HRESULT
    ReadLine(
        IN      BYTE*  pbBuffer,
        IN OUT  UINT*  lpuiBufSize);

    HRESULT
    ReadCurrent(
        IN      BYTE*  pbBuffer,
        IN OUT  UINT*  lpuiBufSize,
        OUT     BOOL*  pbNoMore);

    HRESULT 
    Write (
        IN      BYTE*  pbBuffer,
        IN OUT  UINT*  lpuiBufSize);

    HRESULT 
    WriteLine (
        IN      BYTE*  pbBuffer,
        IN OUT  UINT*  lpuiBufSize);

    HRESULT SetEvent(IN HANDLE hEvent, IN LONG lFlags);
    
private:
    HSOCKET m_hSocket;
    pfnWSAEventSelectSpec m_pfnWSAEventSelect;
};

class RuServerSocket
{
public:
    RuServerSocket();
    ~RuServerSocket();

    HRESULT
    Create(
        IN  UINT uiPort,
        IN OPTIONAL CHAR* pszLocalIpAddress = NULL);

    VOID Close();

    HRESULT Listen(OUT RuSocket* pClient);

    HRESULT SetEvent(IN HANDLE hEvent, IN LONG lFlags = FD_ACCEPT);
    
private:
    HSOCKET m_hSocket;
    pfnWSAEventSelectSpec m_pfnWSAEventSelect;
};


#endif

