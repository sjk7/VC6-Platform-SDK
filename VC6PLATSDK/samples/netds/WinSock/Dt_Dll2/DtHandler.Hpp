// Filename  : DTHandler.hpp
// Abstract  : This object implements a mechanism for hooking Winsock
//             API calls via the 'DT hooks' present in the checked-build
//             version of the ws2_32.dll. (See the Winsock DT sample on
//             on the Platform SDK for specifications.)  Through invoking
//             the DTHandler::dispatch() method, this object translates
//             the hook's code ordinal and calls the appropriate virtual
//             member function of the same Winsock API name, which you can
//             overload through inheritance, with the proper API parameters
//             expanded from DT's variable argument list call, making it
//             possible for you to easily trace your Winsock application
//             in a debug setting.
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998 - 2001,  Microsoft Corporation.
//             All rights reserved.

#ifndef _DTHANDLER_H
#define _DTHANDLER_H

// Prevent inclusion of winsock.h in windows.h
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#endif

#include <ws2spi.h>
#include <ws2tcpip.h>
#include "APIHook.hpp"
#include "dt_dll.hpp"

class DTHandler {

    static bool (* _dispatchTable[MAX_DTCODE + 1])(DTHandler *, APIHook<void> &, va_list);

    static bool _accept                                  (DTHandler *, APIHook<void> &, va_list);
    static bool _bind                                    (DTHandler *, APIHook<void> &, va_list);
    static bool _closesocket                             (DTHandler *, APIHook<void> &, va_list);
    static bool _connect                                 (DTHandler *, APIHook<void> &, va_list);
    static bool _getpeername                             (DTHandler *, APIHook<void> &, va_list);
    static bool _getsockname                             (DTHandler *, APIHook<void> &, va_list);
    static bool _getsockopt                              (DTHandler *, APIHook<void> &, va_list);
    static bool _htonl                                   (DTHandler *, APIHook<void> &, va_list);
    static bool _htons                                   (DTHandler *, APIHook<void> &, va_list);
    static bool _ioctlsocket                             (DTHandler *, APIHook<void> &, va_list);
    static bool _listen                                  (DTHandler *, APIHook<void> &, va_list);
    static bool _ntohl                                   (DTHandler *, APIHook<void> &, va_list);
    static bool _ntohs                                   (DTHandler *, APIHook<void> &, va_list);
    static bool _recv                                    (DTHandler *, APIHook<void> &, va_list);
    static bool _recvfrom                                (DTHandler *, APIHook<void> &, va_list);
    static bool _select                                  (DTHandler *, APIHook<void> &, va_list);
    static bool _send                                    (DTHandler *, APIHook<void> &, va_list);
    static bool _sendto                                  (DTHandler *, APIHook<void> &, va_list);
    static bool _setsockopt                              (DTHandler *, APIHook<void> &, va_list);
    static bool _shutdown                                (DTHandler *, APIHook<void> &, va_list);
    static bool _socket                                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAccept                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncSelect                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSACancelBlockingCall                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSACleanup                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSACloseEvent                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAConnect                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSACreateEvent                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSADuplicateSocketA                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSADuplicateSocketW                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAEnumNetworkEvents                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAEnumProtocolsA                       (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAEnumProtocolsW                       (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAEventSelect                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetLastError                         (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetOverlappedResult                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetQOSByName                         (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAHtonl                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAHtons                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAIoctl                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAIsBlocking                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAJoinLeaf                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSANtohl                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSANtohs                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSARecv                                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSARecvDisconnect                       (DTHandler *, APIHook<void> &, va_list);
    static bool _WSARecvFrom                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAResetEvent                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASend                                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASendDisconnect                       (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASendTo                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASetBlockingHook                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASetEvent                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASetLastError                         (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASocketA                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASocketW                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAStartup                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAUnhookBlockingHook                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAWaitForMultipleEvents                (DTHandler *, APIHook<void> &, va_list);
    static bool _gethostbyaddr                           (DTHandler *, APIHook<void> &, va_list);
    static bool _gethostbyname                           (DTHandler *, APIHook<void> &, va_list);
    static bool _gethostname                             (DTHandler *, APIHook<void> &, va_list);
    static bool _getprotobyname                          (DTHandler *, APIHook<void> &, va_list);
    static bool _getprotobynumber                        (DTHandler *, APIHook<void> &, va_list);
    static bool _getservbyname                           (DTHandler *, APIHook<void> &, va_list);
    static bool _getservbyport                           (DTHandler *, APIHook<void> &, va_list);
    static bool _inet_addr                               (DTHandler *, APIHook<void> &, va_list);
    static bool _inet_ntoa                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncGetHostByAddr                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncGetHostByName                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncGetProtoByName                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncGetProtoByNumber                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncGetServByName                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAsyncGetServByPort                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSACancelAsyncRequest                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPAccept                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPAsyncSelect                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPBind                                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPCancelBlockingCall                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPCleanup                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPCloseSocket                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPConnect                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPDuplicateSocket                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPEnumNetworkEvents                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPEventSelect                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPGetOverlappedResult                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPGetPeerName                          (DTHandler *, APIHook<void> &, va_list);
//  static bool _WSPGetProcTable                         (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPGetSockName                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPGetSockOpt                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPGetQOSByName                         (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPIoctl                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPJoinLeaf                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPListen                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPRecv                                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPRecvDisconnect                       (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPRecvFrom                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPSelect                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPSend                                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPSendDisconnect                       (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPSendTo                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPSetSockOpt                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPShutdown                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPSocket                               (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPStartup                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUCloseEvent                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUCloseSocketHandle                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUCreateEvent                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUCreateSocketHandle                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCDeinstallProvider                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCInstallProvider                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUModifyIFSHandle                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUQueryBlockingCallback                (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUQuerySocketHandleContext             (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUQueueApc                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUResetEvent                           (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUSetEvent                             (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUFDIsSet                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUGetProviderPath                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUPostMessage                          (DTHandler *, APIHook<void> &, va_list);
    static bool ___WSAFDIsSet                            (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCEnumProtocols                        (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAddressToStringA                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAAddressToStringW                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAStringToAddressA                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAStringToAddressW                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSALookupServiceBeginA                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSALookupServiceBeginW                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSALookupServiceNextA                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSALookupServiceNextW                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSALookupServiceEnd                     (DTHandler *, APIHook<void> &, va_list);
//  static bool _WSAGetAddressByNameA                    (DTHandler *, APIHook<void> &, va_list);
//  static bool _WSAGetAddressByNameW                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAInstallServiceClassA                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAInstallServiceClassW                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASetServiceA                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSASetServiceW                          (DTHandler *, APIHook<void> &, va_list);
    static bool _WSARemoveServiceClass                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetServiceClassInfoA                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetServiceClassInfoW                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAEnumNameSpaceProvidersA              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAEnumNameSpaceProvidersW              (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetServiceClassNameByClassIdA        (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAGetServiceClassNameByClassIdW        (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPAddressToString                      (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPStringToAddress                      (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPCleanup                              (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPLookupServiceBegin                   (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPLookupServiceNext                    (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPLookupServiceEnd                     (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPGetAddressByName                     (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPSetService                           (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPInstallServiceClass                  (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPRemoveServiceClass                   (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPGetServiceClassInfo                  (DTHandler *, APIHook<void> &, va_list);
//  static bool _NSPEnumNameSpaceProviders               (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPGetServiceClassNameByClassId         (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCGetProviderPath                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCInstallNameSpace                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCUnInstallNameSpace                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCEnableNSProvider                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPAddressToString                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WSPStringToAddress                      (DTHandler *, APIHook<void> &, va_list);
#if (WINVER >= 0x0501)
    static bool _WSANSPIoctl                             (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPIoctl                                (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUCompleteOverlappedRequest            (DTHandler *, APIHook<void> &, va_list);
    static bool _WSAProviderConfigChange                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCWriteProviderOrder                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCWriteNameSpaceOrder                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCUpdateProvider                       (DTHandler *, APIHook<void> &, va_list);
    static bool _getaddrinfo                             (DTHandler *, APIHook<void> &, va_list);
    static bool _getnameinfo                             (DTHandler *, APIHook<void> &, va_list);
    static bool _freeaddrinfo                            (DTHandler *, APIHook<void> &, va_list);
    static bool _NSPStartup                              (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUOpenCurrentThread                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WPUCloseThread                          (DTHandler *, APIHook<void> &, va_list);
#if defined(_WIN64)
    static bool _WSCEnumProtocols32                      (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCInstallProvider64_32                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCDeinstallProvider32                  (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCGetProviderPath32                    (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCUpdateProvider32                     (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCWriteProviderOrder32                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCEnumNameSpaceProviders32             (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCInstallNameSpace32                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCUnInstallNameSpace32                 (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCEnableNSProvider32                   (DTHandler *, APIHook<void> &, va_list);
    static bool _WSCWriteNameSpaceOrder32                (DTHandler *, APIHook<void> &, va_list);
#endif // defined(_WIN64)
#endif // (WINVER >= 0x0501)

protected :

    virtual bool accept                           (SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen, APIHook<SOCKET> &hook);
    virtual bool bind                             (SOCKET s, const struct sockaddr FAR *name, int namelen, APIHook<int> &hook);
    virtual bool closesocket                      (SOCKET s, APIHook<int> &hook);
    virtual bool connect                          (SOCKET s, const struct sockaddr FAR *name, int namelen, APIHook<int> &hook);
    virtual bool getpeername                      (SOCKET s, struct sockaddr FAR *name, int FAR *namelen, APIHook<int> &hook);
    virtual bool getsockname                      (SOCKET s, struct sockaddr FAR *name, int FAR *namelen, APIHook<int> &hook);
    virtual bool getsockopt                       (SOCKET s, int level, int optname, char FAR *optval, int FAR *optlen, APIHook<int> &hook);
    virtual bool htonl                            (unsigned long hostlong, APIHook<unsigned long> &hook);
    virtual bool htons                            (unsigned short hostshort, APIHook<unsigned short> &hook);
    virtual bool ioctlsocket                      (SOCKET s, long cmd, unsigned long FAR *argp, APIHook<int> &hook);
    virtual bool listen                           (SOCKET s, int backlog, APIHook<int> &hook);
    virtual bool ntohl                            (unsigned long netlong, APIHook<unsigned long> &hook);
    virtual bool ntohs                            (unsigned short netshort, APIHook<unsigned short> &hook);
    virtual bool recv                             (SOCKET s, char FAR *buf, int len, int flags, APIHook<int> &hook);
    virtual bool recvfrom                         (SOCKET s, char FAR *buf, int len, int flags, struct sockaddr FAR *from, int FAR *fromlen, APIHook<int> &hook);
    virtual bool select                           (int nfds, fd_set FAR *readfds, fd_set FAR *writefds, fd_set FAR *exceptfds, const struct timeval FAR *timeout, APIHook<int> &hook);
    virtual bool send                             (SOCKET s, const char FAR *buf, int len, int flags, APIHook<int> &hook);
    virtual bool sendto                           (SOCKET s, const char FAR *buf, int len, int flags, const struct sockaddr FAR *to, int tolen, APIHook<int> &hook);
    virtual bool setsockopt                       (SOCKET s, int level, int optname, const char FAR *optval, int optlen, APIHook<int> &hook);
    virtual bool shutdown                         (SOCKET s, int how, APIHook<int> &hook);
    virtual bool socket                           (int af, int type, int protocol, APIHook<SOCKET> &hook);
    virtual bool WSAAccept                        (SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen, LPCONDITIONPROC lpfnCondition, unsigned long dwCallbackData, APIHook<SOCKET> &hook);
    virtual bool WSAAsyncSelect                   (SOCKET s, HWND hWnd, unsigned int wMsg, long lEvent, APIHook<int> &hook);
    virtual bool WSACancelBlockingCall            (APIHook<int> &hook);
    virtual bool WSACleanup                       (APIHook<int> &hook);
    virtual bool WSACloseEvent                    (WSAEVENT hEvent, APIHook<int> &hook);
    virtual bool WSAConnect                       (SOCKET s, const struct sockaddr FAR *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, APIHook<int> &hook);
    virtual bool WSACreateEvent                   (APIHook<WSAEVENT> &hook);
    virtual bool WSADuplicateSocketA              (SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOA lpProtocolInfo, APIHook<int> &hook);
    virtual bool WSADuplicateSocketW              (SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOW lpProtocolInfo, APIHook<int> &hook);
    virtual bool WSAEnumNetworkEvents             (SOCKET s, WSAEVENT hEventObject, LPWSANETWORKEVENTS lpNetworkEvents, APIHook<int> &hook);
    virtual bool WSAEnumProtocolsA                (LPINT lpiProtocols, LPWSAPROTOCOL_INFOA lpProtocolBuffer, LPDWORD lpdwBufferLength, APIHook<int> &hook);
    virtual bool WSAEnumProtocolsW                (LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer, LPDWORD lpdwBufferLength, APIHook<int> &hook);
    virtual bool WSAEventSelect                   (SOCKET s, WSAEVENT hEventObject, long lNetworkEvents, APIHook<int> &hook);
    virtual bool WSAGetLastError                  (APIHook<int> &hook);
    virtual bool WSAGetOverlappedResult           (SOCKET s, LPWSAOVERLAPPED lpOverlapped, LPDWORD lpcbTransfer, BOOL fWait, unsigned long *lpdwFlags, APIHook<int> &hook);
    virtual bool WSAGetQOSByName                  (SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS, APIHook<int> &hook);
    virtual bool WSAHtonl                         (SOCKET s, unsigned long hostlong, unsigned long FAR *lpnetlong, APIHook<int> &hook);
    virtual bool WSAHtons                         (SOCKET s, unsigned short hostshort, unsigned short FAR *lpnetshort, APIHook<int> &hook);
    virtual bool WSAIoctl                         (SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook);
    virtual bool WSAIsBlocking                    (APIHook<int> &hook);
    virtual bool WSAJoinLeaf                      (SOCKET s, const struct sockaddr *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags, APIHook<SOCKET> &hook);
    virtual bool WSANtohl                         (SOCKET s, unsigned long netlong, unsigned long *lphostlong, APIHook<int> &hook);
    virtual bool WSANtohs                         (SOCKET s, unsigned short netshort, unsigned short *lphostshort, APIHook<int> &hook);
    virtual bool WSARecv                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook);
    virtual bool WSARecvDisconnect                (SOCKET s, LPWSABUF lpInboundDisconnectData, APIHook<int> &hook);
    virtual bool WSARecvFrom                      (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr *lpFrom, LPINT lpFromlen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook);
    virtual bool WSAResetEvent                    (WSAEVENT hEvent, APIHook<int> &hook);
    virtual bool WSASend                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook);
    virtual bool WSASendDisconnect                (SOCKET s, LPWSABUF lpOutboundDisconnectData, APIHook<int> &hook);
    virtual bool WSASendTo                        (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook);
    virtual bool WSASetBlockingHook               (FARPROC lpBlockFunc, APIHook<FARPROC> &hook);
    virtual bool WSASetEvent                      (WSAEVENT hEvent, APIHook<int> &hook);
    virtual bool WSASetLastError                  (int iError, APIHook<void> &hook);
    virtual bool WSASocketA                       (int af, int type, int protocol, LPWSAPROTOCOL_INFOA lpProtocolInfo, GROUP g, DWORD dwFlags, APIHook<SOCKET> &hook);
    virtual bool WSASocketW                       (int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags, APIHook<SOCKET> &hook);
    virtual bool WSAStartup                       (WORD wVersionRequested, LPWSADATA lpWSAData, APIHook<int> &hook);
    virtual bool WSAUnhookBlockingHook            (APIHook<int> &hook);
    virtual bool WSAWaitForMultipleEvents         (DWORD cEvents, const WSAEVENT FAR *lphEvents, BOOL fWaitAll, DWORD dwTimeout, BOOL fAlertable, APIHook<DWORD> &hook);
    virtual bool gethostbyaddr                    (const char FAR *addr, int len, int type, APIHook<HOSTENT> &hook);
    virtual bool gethostbyname                    (const char FAR *name, APIHook<HOSTENT> &hook);
    virtual bool gethostname                      (char FAR *name, int namelen, APIHook<int> &hook);
    virtual bool getprotobyname                   (const char FAR *name, APIHook<PROTOENT> &hook);
    virtual bool getprotobynumber                 (int number, APIHook<PROTOENT> &hook);
    virtual bool getservbyname                    (const char FAR *name, const char FAR *proto, APIHook<SERVENT> &hook);
    virtual bool getservbyport                    (int port, const char FAR *proto, APIHook<SERVENT> &hook);
    virtual bool inet_addr                        (const char FAR *cp, APIHook<unsigned long> &hook);
    virtual bool inet_ntoa                        (struct in_addr in, APIHook<char FAR *> &hook);
    virtual bool WSAAsyncGetHostByAddr            (HWND hWnd, unsigned int wMsg, const char FAR *addr, int len, int type, char FAR *buf, int buflen, APIHook<HANDLE> &hook);
    virtual bool WSAAsyncGetHostByName            (HWND hWnd, unsigned int wMsg, const char FAR *name, char FAR *buf, int buflen, APIHook<HANDLE> &hook);
    virtual bool WSAAsyncGetProtoByName           (HWND hWnd, unsigned int wMsg, const char FAR *name, char FAR *buf, int buflen, APIHook<HANDLE> &hook);
    virtual bool WSAAsyncGetProtoByNumber         (HWND hWnd, unsigned int wMsg, int number, char FAR *buf, int buflen, APIHook<HANDLE> &hook);
    virtual bool WSAAsyncGetServByName            (HWND hWnd, unsigned int wMsg, const char FAR *name, const char FAR *proto, char FAR *buf, int buflen, APIHook<HANDLE> &hook);
    virtual bool WSAAsyncGetServByPort            (HWND hWnd, unsigned int wMsg, int port, const char FAR *proto, char FAR *buf, int buflen, APIHook<HANDLE> &hook);
    virtual bool WSACancelAsyncRequest            (HANDLE hAsyncTaskHandle, APIHook<int> &hook);
    virtual bool WSPAccept                        (SOCKET s, struct sockaddr FAR *addr, LPINT addrlen, LPCONDITIONPROC lpfnCondition, DWORD dwCallbackData, LPINT lpErrno, APIHook<SOCKET> &hook);
    virtual bool WSPAsyncSelect                   (SOCKET s, HWND hWnd, unsigned int wMsg, long lEvent, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPBind                          (SOCKET s, const struct sockaddr FAR *name, int namelen, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPCancelBlockingCall            (LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPCleanup                       (LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPCloseSocket                   (SOCKET s, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPConnect                       (SOCKET s, const struct sockaddr FAR *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPDuplicateSocket               (SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPEnumNetworkEvents             (SOCKET s, WSAEVENT hEventObject, LPWSANETWORKEVENTS lpNetworkEvents, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPEventSelect                   (SOCKET s, WSAEVENT hEventObject, long lNetworkEvents, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPGetOverlappedResult           (SOCKET s, LPWSAOVERLAPPED lpOverlapped, LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags, LPINT lpErrno, APIHook<BOOL> &hook);
    virtual bool WSPGetPeerName                   (SOCKET s, struct sockaddr FAR *name, LPINT namelen, LPINT lpErrno, APIHook<int> &hook);
//  virtual bool _WSPGetProcTable                 ();
    virtual bool WSPGetSockName                   (SOCKET s, struct sockaddr FAR *name, LPINT namelen, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPGetSockOpt                    (SOCKET s, int level, int optname, char FAR *optval, LPINT optlen, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPGetQOSByName                  (SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS, LPINT lpErrno, APIHook<BOOL> &hook);
    virtual bool WSPIoctl                         (SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, LPWSATHREADID lpThreadId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPJoinLeaf                      (SOCKET s, const struct sockaddr FAR *name, int namelen, LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags, LPINT lpErrno, APIHook<SOCKET> &hook);
    virtual bool WSPListen                        (SOCKET s, int backlog, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPRecv                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, LPWSATHREADID lpThreadId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPRecvDisconnect                (SOCKET s, LPWSABUF lpInboundDisconnectData, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPRecvFrom                      (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags, struct sockaddr FAR *lpFrom, LPINT lpFromlen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, LPWSATHREADID lpThreadId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPSelect                        (int nfds, fd_set FAR *readfds, fd_set FAR *writefds, fd_set FAR *exceptfds, const struct timeval FAR *timeout, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPSend                          (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, LPWSATHREADID lpThreadId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPSendDisconnect                (SOCKET s, LPWSABUF lpOutboundDisconnectData, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPSendTo                        (SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags, const struct sockaddr FAR *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, LPWSATHREADID lpThreadId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPSetSockOpt                    (SOCKET s, int level, int optname, const char FAR *optval, int optlen, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPShutdown                      (SOCKET s, int how, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPSocket                        (int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo, GROUP g, DWORD dwFlags, LPINT lpErrno, APIHook<SOCKET> &hook);
    virtual bool WSPStartup                       (WORD wVersionRequested, LPWSPDATA lpWSPData, LPWSAPROTOCOL_INFOW lpProtocolInfo, WSPUPCALLTABLE UpcallTable, LPWSPPROC_TABLE lpProcTable, APIHook<int> &hook);
    virtual bool WPUCloseEvent                    (WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> &hook);
    virtual bool WPUCloseSocketHandle             (SOCKET s, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUCreateEvent                   (LPINT lpErrno, APIHook<WSAEVENT> &hook);
    virtual bool WPUCreateSocketHandle            (DWORD dwCatalogEntryId, DWORD dwContext, LPINT lpErrno, APIHook<SOCKET> &hook);
    virtual bool WSCDeinstallProvider             (LPGUID lpProviderId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCInstallProvider               (const LPGUID lpProviderId, const LPWSTR lpszProviderDllPath, const LPWSAPROTOCOL_INFOW lpProtocolInfoList, DWORD dwNumberOfEntries, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUModifyIFSHandle               (DWORD dwCatalogEntryId, SOCKET ProposedHandle, LPINT lpErrno, APIHook<SOCKET> &hook);
    virtual bool WPUQueryBlockingCallback         (DWORD dwCatalogEntryId, LPBLOCKINGCALLBACK FAR *lplpfnCallback, LPDWORD lpdwContext, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUQuerySocketHandleContext      (SOCKET s, LPDWORD lpContext, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUQueueApc                      (LPWSATHREADID lpThreadId, LPWSAUSERAPC lpfnUserApc, DWORD dwContext, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUResetEvent                    (WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> &hook);
    virtual bool WPUSetEvent                      (WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> &hook);
    virtual bool WPUFDIsSet                       (SOCKET s, FD_SET FAR *set, APIHook<int> &hook);
    virtual bool WPUGetProviderPath               (LPGUID lpProviderId, LPWSTR lpszProviderDllPath, LPINT lpProviderDllPathLen, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUPostMessage                   (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, APIHook<BOOL> &hook);
    virtual bool __WSAFDIsSet                     (SOCKET s, FD_SET FAR *set, APIHook<int> &hook);
    virtual bool WSCEnumProtocols                 (LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer, LPDWORD lpdwBufferLength, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSAAddressToStringA              (LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOA lpProtocolInfo, OUT LPTSTR lpszAddressString, IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> &hook);
    virtual bool WSAAddressToStringW              (LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, OUT LPTSTR lpszAddressString, IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> &hook);
    virtual bool WSAStringToAddressA              (LPTSTR AddressString, INT AddressFamily, LPWSAPROTOCOL_INFOA lpProtocolInfo, LPSOCKADDR lpAddress, LPINT lpAddressLength, APIHook<INT> &hook);
    virtual bool WSAStringToAddressW              (LPTSTR AddressString, INT AddressFamily, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress, LPINT lpAddressLength, APIHook<INT> &hook);
    virtual bool WSALookupServiceBeginA           (LPWSAQUERYSETA lpqsRestrictions, DWORD dwControlFlags, LPHANDLE lphLookup, APIHook<INT> &hook);
    virtual bool WSALookupServiceBeginW           (LPWSAQUERYSETW lpqsRestrictions, DWORD dwControlFlags, LPHANDLE lphLookup, APIHook<INT> &hook);
    virtual bool WSALookupServiceNextA            (HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength, LPWSAQUERYSETA lpqsResults, APIHook<INT> &hook);
    virtual bool WSALookupServiceNextW            (HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength, LPWSAQUERYSETW lpqsResults, APIHook<INT> &hook);
    virtual bool WSALookupServiceEnd              (HANDLE hLookup, APIHook<INT> &hook);
//  virtual bool WSAGetAddressByNameA             ();
//  virtual bool WSAGetAddressByNameW             ();
    virtual bool WSAInstallServiceClassA          (LPWSASERVICECLASSINFOA lpServiceClassInfo, APIHook<INT> &hook);
    virtual bool WSAInstallServiceClassW          (LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<INT> &hook);
    virtual bool WSASetServiceA                   (LPWSAQUERYSETA lpqsRegInfo, WSAESETSERVICEOP essOperation, DWORD dwControlFlags, APIHook<INT> &hook);
    virtual bool WSASetServiceW                   (LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation, DWORD dwControlFlags, APIHook<INT> &hook);
    virtual bool WSARemoveServiceClass            (LPGUID lpServiceClassId, APIHook<INT> &hook);
    virtual bool WSAGetServiceClassInfoA          (LPGUID lpProviderId, LPGUID lpServiceClassId, LPDWORD lpdwBufferLength, LPWSASERVICECLASSINFOA lpServiceClassInfo, APIHook<INT> &hook);
    virtual bool WSAGetServiceClassInfoW          (LPGUID lpProviderId, LPGUID lpServiceClassId, LPDWORD lpdwBufferLength, LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<INT> &hook);
    virtual bool WSAEnumNameSpaceProvidersA       (IN OUT LPDWORD lpdwBufferLength, OUT LPWSANAMESPACE_INFOA lpnspBuffer, APIHook<INT> &hook);
    virtual bool WSAEnumNameSpaceProvidersW       (IN OUT LPDWORD lpdwBufferLength, OUT LPWSANAMESPACE_INFOW lpnspBuffer, APIHook<INT> &hook);
    virtual bool WSAGetServiceClassNameByClassIdA (LPGUID lpServiceClassId, LPSTR lpszServiceClassName, LPDWORD lpdwBufferLength, APIHook<int> &hook);
    virtual bool WSAGetServiceClassNameByClassIdW (LPGUID lpServiceClassId, LPWSTR lpszServiceClassName, LPDWORD lpdwBufferLength, APIHook<int> &hook);
    virtual bool NSPAddressToString               (LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength, APIHook<int> &hook);
    virtual bool NSPStringToAddress               (LPWSTR AddressString, INT AddressFamily, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress, LPINT lpAddressLength, APIHook<int> &hook);
    virtual bool NSPLookupServiceBegin            (LPGUID lpProviderId, LPWSAQUERYSETW lpqsRestrictions, LPWSASERVICECLASSINFOW lpServiceClassInfo, DWORD dwControlFlags, LPHANDLE lphLookup, APIHook<int> &hook);
    virtual bool NSPLookupServiceNext             (HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength, LPWSAQUERYSET lpqsResults, APIHook<int> &hook);
    virtual bool NSPLookupServiceEnd              (HANDLE hLookup, APIHook<int> &hook);
    virtual bool NSPGetAddressByName              (LPWSTR lpszServiceInstanceName, LPGUID lpServiceClassId, DWORD dwNameSpace, LPDWORD lpdwBufferLength, LPWSAQUERYSETW lpqsResults, DWORD dwResolution, LPWSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength, APIHook<int> &hook);
    virtual bool NSPInstallServiceClass           (LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<int> &hook);
    virtual bool NSPSetService                    (LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo, LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation, DWORD dwControlFlags, APIHook<int> &hook);
    virtual bool NSPRemoveServiceClass            (IN LPGUID lpProviderId, IN LPGUID lpServiceClassId, APIHook<int> &hook);
    virtual bool NSPGetServiceClassInfo           (IN LPGUID lpProviderId, IN OUT LPDWORD lpdwBufSize, IN OUT LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<int> &hook);
//  virtual bool NSPEnumNameSpaceProviders        ();
    virtual bool NSPGetServiceClassNameByClassId  (LPGUID lpServiceClassId, LPWSTR lpszServiceClassName, LPDWORD lpdwBufferLength, APIHook<int> &hook);
    virtual bool WSCGetProviderPath               (LPGUID lpProviderId, LPWSTR lpszProviderDllPath, LPINT lpProviderDllPathLen, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCInstallNameSpace              (LPWSTR lpszIdentifier, LPWSTR lpszPathName, DWORD dwNameSpace, DWORD dwVersion, LPGUID lpProviderId, APIHook<int> &hook);
    virtual bool WSCUnInstallNameSpace            (LPGUID lpProviderId, APIHook<int> &hook);
    virtual bool WSCEnableNSProvider              (LPGUID lpProviderId, BOOL fEnable, APIHook<int> &hook);
    virtual bool WSPAddressToString               (LPSOCKADDR lpsaAddress, DWORD dwAddressLength, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSPStringToAddress               (LPWSTR AddressString, INT AddressFamily, LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,  LPINT lpAddressLength, LPINT lpErrno, APIHook<int> &hook);
#if (WINVER >= 0x0501)
    virtual bool WSANSPIoctl                      (IN HANDLE hLookup, IN DWORD dwControlCode, IN LPVOID lpvInBuffer, IN DWORD cbInBuffer, OUT LPVOID lpvOutBuffer, IN DWORD cbOutBuffer, OUT LPDWORD lpcbBytesReturned, IN LPWSACOMPLETION lpCompletion, APIHook<INT> &hook);
    virtual bool NSPIoctl                         (HANDLE hLookup, DWORD dwControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPWSACOMPLETION lpCompletion, LPWSATHREADID lpThreadId, APIHook<INT> &hook);
    virtual bool WPUCompleteOverlappedRequest     (SOCKET s, LPWSAOVERLAPPED lpOverlapped, DWORD dwError, DWORD cbTransferred, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSAProviderConfigChange          (IN OUT LPHANDLE lpNotificationHandle, IN LPWSAOVERLAPPED lpOverlapped, IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook);
    virtual bool WSCWriteProviderOrder            (IN LPDWORD lpwdCatalogEntryId, IN DWORD dwNumberOfEntries, APIHook<int> &hook);
    virtual bool WSCWriteNameSpaceOrder           (IN LPGUID lpProviderId, IN DWORD dwNumberOfEntries, APIHook<int> &hook);
    virtual bool WSCUpdateProvider                (IN LPGUID lpProviderId, IN const WCHAR FAR *lpszProviderDllPath, IN const LPWSAPROTOCOL_INFOW lpProtocolInfoList, IN DWORD dwNumberOfEntries, OUT LPINT lpErrno, APIHook<int> &hook);
    virtual bool getaddrinfo                      (IN const char FAR *NodeName, IN const char FAR *ServiceName, IN const struct addrinfo FAR *Hints, OUT struct addrinfo FAR * FAR *Result, APIHook<INT> &hook);
    virtual bool getnameinfo                      (IN const struct sockaddr *SocketAddress, IN socklen_t SocketAddressLength, OUT PCHAR NodeName, IN DWORD NodeBufferSize, OUT PCHAR ServiceName, IN DWORD ServiceBufferSize, IN INT Flags, APIHook<INT> &hook);
    virtual bool freeaddrinfo                     (IN OUT struct addrinfo *Free, APIHook<void> &hook);
    virtual bool NSPStartup                       (LPGUID lpProviderId, LPNSP_ROUTINE lpnspRoutines, APIHook<INT> &hook);
    virtual bool WPUOpenCurrentThread             (OUT LPWSATHREADID lpThreadId, OUT LPINT lpErrno, APIHook<int> &hook);
    virtual bool WPUCloseThread                   (IN LPWSATHREADID lpThreadId, OUT LPINT lpErrno, APIHook<int> &hook);
#if defined(_WIN64)
    virtual bool WSCEnumProtocols32               (IN LPINT lpiProtocols, OUT LPWSAPROTOCOL_INFOW lpProtocolBuffer, IN OUT LPDWORD lpdwBufferLength, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCInstallProvider64_32          (const LPGUID lpProviderId, const LPWSTR lpszProviderDllPath, const LPWSAPROTOCOL_INFOW lpProtocolInfoList, DWORD dwNumberOfEntries, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCDeinstallProvider32           (LPGUID lpProviderId, LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCGetProviderPath32             (IN LPGUID lpProviderId, OUT WCHAR FAR *lpszProviderDllPath, IN OUT LPINT ProviderDLLPathLen, OUT LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCUpdateProvider32              (IN LPGUID lpProviderId, IN const WCHAR FAR *lpszProviderDllPath, IN const LPWSAPROTOCOL_INFOW lpProtocolInfoList, IN DWORD dwNumberOfEntries, OUT LPINT lpErrno, APIHook<int> &hook);
    virtual bool WSCWriteProviderOrder32          (IN LPDWORD lpwdCatalogEntryId, IN DWORD dwNumberOfEntries, APIHook<int> &hook);
    virtual bool WSCEnumNameSpaceProviders32      (IN OUT LPDWORD lpdwBufferLength, IN OUT LPWSANAMESPACE_INFOW lpnspBuffer, APIHook<INT> &hook);
    virtual bool WSCInstallNameSpace32            (LPWSTR lpszIdentifier, LPWSTR lpszPathName, DWORD dwNameSpace, DWORD dwVersion, LPGUID lpProviderId, APIHook<int> &hook);
    virtual bool WSCUnInstallNameSpace32          (LPGUID lpProviderId, APIHook<int> &hook);
    virtual bool WSCEnableNSProvider32            (LPGUID lpProviderId, BOOL fEnable, APIHook<int> &hook);
    virtual bool WSCWriteNameSpaceOrder32         (IN LPGUID lpProviderId, IN DWORD dwNumberOfEntries, APIHook<int> &hook);
#endif // defined(_WIN64)
#endif // (WINVER >= 0x0501)

public :

    bool
    dispatch(int notificationCode, void *returnCode, char *LibraryName, bool preAPI, va_list vl);

}; // class DTHandler

#endif
