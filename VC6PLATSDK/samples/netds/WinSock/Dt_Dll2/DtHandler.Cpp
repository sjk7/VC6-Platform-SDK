// Filename  : DTHandler.cpp
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
//             Copyright (C) 1998 - 2002,  Microsoft Corporation.
//             All rights reserved.

#pragma warning(disable: 4100 4512)

#include "DTHandler.hpp"
#include "dt_dll.hpp"


bool (* DTHandler::_dispatchTable[MAX_DTCODE + 1])(DTHandler *, APIHook<void> &, va_list) = {

    NULL,
    DTHandler::_accept,
    DTHandler::_bind,
    DTHandler::_closesocket,
    DTHandler::_connect,
    DTHandler::_getpeername,
    DTHandler::_getsockname,
    DTHandler::_getsockopt,
    DTHandler::_htonl,
    DTHandler::_htons,
    DTHandler::_ioctlsocket,
    DTHandler::_listen,
    DTHandler::_ntohl,
    DTHandler::_ntohs,
    DTHandler::_recv,
    DTHandler::_recvfrom,
    DTHandler::_select,
    DTHandler::_send,
    DTHandler::_sendto,
    DTHandler::_setsockopt,
    DTHandler::_shutdown,
    DTHandler::_socket,
    DTHandler::_WSAAccept,
    DTHandler::_WSAAsyncSelect,
    DTHandler::_WSACancelBlockingCall,
    DTHandler::_WSACleanup,
    DTHandler::_WSACloseEvent,
    DTHandler::_WSAConnect,
    DTHandler::_WSACreateEvent,
    DTHandler::_WSADuplicateSocketA,
    DTHandler::_WSAEnumNetworkEvents,
    DTHandler::_WSAEnumProtocolsA,
    DTHandler::_WSAEventSelect,
    DTHandler::_WSAGetLastError,
    DTHandler::_WSAGetOverlappedResult,
    DTHandler::_WSAGetQOSByName,
    DTHandler::_WSAHtonl,
    DTHandler::_WSAHtons,
    DTHandler::_WSAIoctl,
    DTHandler::_WSAIsBlocking,
    DTHandler::_WSAJoinLeaf,
    DTHandler::_WSANtohl,
    DTHandler::_WSANtohs,
    DTHandler::_WSARecv,
    DTHandler::_WSARecvDisconnect,
    DTHandler::_WSARecvFrom,
    DTHandler::_WSAResetEvent,
    DTHandler::_WSASend,
    DTHandler::_WSASendDisconnect,
    DTHandler::_WSASendTo,
    DTHandler::_WSASetBlockingHook,
    DTHandler::_WSASetEvent,
    DTHandler::_WSASetLastError,
    DTHandler::_WSASocketA,
    DTHandler::_WSAStartup,
    DTHandler::_WSAUnhookBlockingHook,
    DTHandler::_WSAWaitForMultipleEvents,
    DTHandler::_gethostbyaddr,
    DTHandler::_gethostbyname,
    DTHandler::_gethostname,
    DTHandler::_getprotobyname,
    DTHandler::_getprotobynumber,
    DTHandler::_getservbyname,
    DTHandler::_getservbyport,
    DTHandler::_inet_addr,
    DTHandler::_inet_ntoa,
    DTHandler::_WSAAsyncGetHostByAddr,
    DTHandler::_WSAAsyncGetHostByName,
    DTHandler::_WSAAsyncGetProtoByName,
    DTHandler::_WSAAsyncGetProtoByNumber,
    DTHandler::_WSAAsyncGetServByName,
    DTHandler::_WSAAsyncGetServByPort,
    DTHandler::_WSACancelAsyncRequest,
    DTHandler::_WSPAccept,
    DTHandler::_WSPAsyncSelect,
    DTHandler::_WSPBind,
    DTHandler::_WSPCancelBlockingCall,
    DTHandler::_WSPCleanup,
    DTHandler::_WSPCloseSocket,
    DTHandler::_WSPConnect,
    DTHandler::_WSPDuplicateSocket,
    DTHandler::_WSPEnumNetworkEvents,
    DTHandler::_WSPEventSelect,
    DTHandler::_WSPGetOverlappedResult,
    DTHandler::_WSPGetPeerName,
    NULL, // DTHandler::_WSPGetProcTable
    DTHandler::_WSPGetSockName,
    DTHandler::_WSPGetSockOpt,
    DTHandler::_WSPGetQOSByName,
    DTHandler::_WSPIoctl,
    DTHandler::_WSPJoinLeaf,
    DTHandler::_WSPListen,
    DTHandler::_WSPRecv,
    DTHandler::_WSPRecvDisconnect,
    DTHandler::_WSPRecvFrom,
    DTHandler::_WSPSelect,
    DTHandler::_WSPSend,
    DTHandler::_WSPSendDisconnect,
    DTHandler::_WSPSendTo,
    DTHandler::_WSPSetSockOpt,
    DTHandler::_WSPShutdown,
    DTHandler::_WSPSocket,
    DTHandler::_WSPStartup,
    DTHandler::_WPUCloseEvent,
    DTHandler::_WPUCloseSocketHandle,
    DTHandler::_WPUCreateEvent,
    DTHandler::_WPUCreateSocketHandle,
    DTHandler::_WSCDeinstallProvider,
    DTHandler::_WSCInstallProvider,
    DTHandler::_WPUModifyIFSHandle,
    DTHandler::_WPUQueryBlockingCallback,
    DTHandler::_WPUQuerySocketHandleContext,
    DTHandler::_WPUQueueApc,
    DTHandler::_WPUResetEvent,
    DTHandler::_WPUSetEvent,
    DTHandler::_WSCEnumProtocols,
    DTHandler::_WPUGetProviderPath,
    DTHandler::_WPUPostMessage,
    DTHandler::_WPUFDIsSet,
    DTHandler::_WSADuplicateSocketW,
    DTHandler::_WSAEnumProtocolsW,
    DTHandler::_WSASocketW,
    DTHandler::___WSAFDIsSet,
    DTHandler::_WSAAddressToStringA,
    DTHandler::_WSAAddressToStringW,
    DTHandler::_WSAStringToAddressA,
    DTHandler::_WSAStringToAddressW,
    DTHandler::_WSALookupServiceBeginA,
    DTHandler::_WSALookupServiceBeginW,
    DTHandler::_WSALookupServiceNextA,
    DTHandler::_WSALookupServiceNextW,
    DTHandler::_WSALookupServiceEnd,
    NULL, // DTHandler::_WSAGetAddressByNameA
    NULL, // DTHandler::_WSAGetAddressByNameW
    DTHandler::_WSAInstallServiceClassA,
    DTHandler::_WSAInstallServiceClassW,
    DTHandler::_WSASetServiceA,
    DTHandler::_WSASetServiceW,
    DTHandler::_WSARemoveServiceClass,
    DTHandler::_WSAGetServiceClassInfoA,
    DTHandler::_WSAGetServiceClassInfoW,
    DTHandler::_WSAEnumNameSpaceProvidersA,
    DTHandler::_WSAEnumNameSpaceProvidersW,
    DTHandler::_WSAGetServiceClassNameByClassIdA,
    DTHandler::_WSAGetServiceClassNameByClassIdW,
    DTHandler::_NSPAddressToString,
    DTHandler::_NSPStringToAddress,
    DTHandler::_NSPLookupServiceBegin,
    DTHandler::_NSPLookupServiceNext,
    DTHandler::_NSPLookupServiceEnd,
    DTHandler::_NSPGetAddressByName,
    DTHandler::_NSPInstallServiceClass,
    DTHandler::_NSPSetService,
    DTHandler::_NSPRemoveServiceClass,
    DTHandler::_NSPGetServiceClassInfo,
    NULL, // DTHandler::_NSPEnumNameSpaceProviders
    DTHandler::_NSPGetServiceClassNameByClassId,
    DTHandler::_WSCGetProviderPath,
    DTHandler::_WSCInstallNameSpace,
    DTHandler::_WSCUnInstallNameSpace,
    DTHandler::_WSCEnableNSProvider,
    DTHandler::_WSPAddressToString,
    DTHandler::_WSPStringToAddress,
#if (WINVER >= 0x0501)
    DTHandler::_WSANSPIoctl,
    DTHandler::_NSPIoctl,
    DTHandler::_WPUCompleteOverlappedRequest,
    DTHandler::_WSAProviderConfigChange,
    DTHandler::_WSCWriteProviderOrder,
    DTHandler::_WSCWriteNameSpaceOrder,
    DTHandler::_WSCUpdateProvider,
    DTHandler::_getaddrinfo,
    DTHandler::_getnameinfo,
    DTHandler::_freeaddrinfo,
    DTHandler::_NSPStartup,
    DTHandler::_WPUOpenCurrentThread,
    DTHandler::_WPUCloseThread,
#if defined(_WIN64)
    DTHandler::_WSCEnumProtocols32,
    DTHandler::_WSCInstallProvider64_32,
    DTHandler::_WSCDeinstallProvider32,
    DTHandler::_WSCGetProviderPath32,
    DTHandler::_WSCUpdateProvider32,
    DTHandler::_WSCWriteProviderOrder32,
    DTHandler::_WSCEnumNameSpaceProviders32,
    DTHandler::_WSCInstallNameSpace32,
    DTHandler::_WSCUnInstallNameSpace32,
    DTHandler::_WSCEnableNSProvider32,
    DTHandler::_WSCWriteNameSpaceOrder32,
#endif // defined(_WIN64)
#endif // (WINVER >= 0x0501)

}; // DTHandler::_dispatchTable


bool
DTHandler::dispatch(int notificationCode, void *returnCode, char *LibraryName, bool preAPI, va_list vl) {

    if ((notificationCode >= 1) && (notificationCode <= MAX_DTCODE) && (_dispatchTable[notificationCode] != NULL)) {

        APIHook<void> hook(returnCode, LibraryName, preAPI);

        return (_dispatchTable[notificationCode](this, hook, vl));

    }

    return (false);

} // DTHandler::dispatch()


bool
DTHandler::accept(SOCKET s, struct sockaddr *addr, int *addrlen, APIHook<SOCKET> &hook) {
    
    return (false);

} // DTHandler::accept()


bool
DTHandler::_accept(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *addr = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    int *addrlen = (int *)*va_arg(vList, int **);

    return (handler->accept(s, addr, addrlen, (APIHook<SOCKET> &)hook));

} // DTHandler::_accept()


bool
DTHandler::bind(SOCKET s, const struct sockaddr *name, int namelen, APIHook<int> &hook) {

    return (false);

} // DTHandler::bind()


bool
DTHandler::_bind(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);

    return (handler->bind(s, name, namelen, (APIHook<int> &)hook));

} // DTHandler::_bind()


bool
DTHandler::closesocket(SOCKET s, APIHook<int> &hook) {

    return (false);

} // DTHandler::closesocket()


bool
DTHandler::_closesocket(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);

    return (handler->closesocket(s, (APIHook<int> &)hook));

} // DTHandler::_closesocket()


bool
DTHandler::connect(SOCKET s, const struct sockaddr *name, int namelen, APIHook<int> &hook) {

    return (false);

} // DTHandler::connect()


bool
DTHandler::_connect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);

    return (handler->connect(s, name, namelen, (APIHook<int> &)hook));

} // DTHandler::_connect()


bool
DTHandler::getpeername(SOCKET s, struct sockaddr *name, int *namelen, APIHook<int> &hook) {

    return (false);

} // DTHandler::getpeername()


bool
DTHandler::_getpeername(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    int *namelen = (int *)*va_arg(vList, int **);

    return (handler->getpeername(s, name, namelen, (APIHook<int> &)hook));

} // DTHandler::_getpeername()


bool
DTHandler::getsockname(SOCKET s, struct sockaddr *name, int *namelen, APIHook<int> &hook) {

    return (false);

} // DTHandler::getsockname()


bool
DTHandler::_getsockname(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    int *namelen = (int *)*va_arg(vList, int **);

    return (handler->getsockname(s, name, namelen, (APIHook<int> &)hook));

} // DTHandler::_getsockname()


bool
DTHandler::getsockopt(SOCKET s, int level, int optname, char *optval, int *optlen, APIHook<int> &hook) {

    return (false);

} // DTHandler::getsockopt()


bool
DTHandler::_getsockopt(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int level = (int)*va_arg(vList, int *);
    int optname = (int)*va_arg(vList, int *);
    char *optval = (char *)*va_arg(vList, char **);
    int *optlen = (int *)*va_arg(vList, int **);

    return (handler->getsockopt(s, level, optname, optval, optlen, (APIHook<int> &)hook));

} // DTHandler::_getsockopt()


bool
DTHandler::htonl(DWORD hostlong, APIHook<DWORD> &hook) {

    return (false);

} // DTHandler::htonl()


bool
DTHandler::_htonl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    DWORD hostlong = (DWORD)*va_arg(vList, DWORD *);

    return (handler->htonl(hostlong, (APIHook<DWORD> &)hook));

} // DTHandler::_htonl()


bool
DTHandler::htons(unsigned short hostshort, APIHook<unsigned short> &hook) {

    return (false);

} // DTHandler::htons()


bool
DTHandler::_htons(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    unsigned short hostshort = (unsigned short)*va_arg(vList, unsigned short *);

    return (handler->htons(hostshort, (APIHook<unsigned short> &)hook));

} // DTHandler::_htons()


bool
DTHandler::ioctlsocket(SOCKET s, long cmd, unsigned long *argp, APIHook<int> &hook) {

    return (false);

} // DTHandler::ioctlsocket()


bool
DTHandler::_ioctlsocket(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    long cmd = (long)*va_arg(vList, long *);
    unsigned long *argp = (unsigned long *)*va_arg(vList, unsigned long **);

    return (handler->ioctlsocket(s, cmd, argp, (APIHook<int> &)hook));

} // DTHandler::_ioctlsocket()


bool
DTHandler::listen(SOCKET s, int backlog, APIHook<int> &hook) {

    return (false);

} // DTHandler::listen()


bool
DTHandler::_listen(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int backlog = (int)*va_arg(vList, int *);

    return (handler->listen(s, backlog, (APIHook<int> &)hook));

} // DTHandler::_listen()


bool
DTHandler::ntohl(unsigned long netlong, APIHook<DWORD> &hook) {

    return (false);

} // DTHandler::ntohl()


bool
DTHandler::_ntohl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    unsigned long netlong = (unsigned long)*va_arg(vList, unsigned long *);

    return (handler->ntohl(netlong, (APIHook<DWORD> &)hook));

} // DTHandler::_ntohl()


bool
DTHandler::ntohs(unsigned short netshort, APIHook<unsigned short> &hook) {

    return (false);

} // DTHandler::ntohs()


bool
DTHandler::_ntohs(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    unsigned short netshort = (unsigned short)*va_arg(vList, unsigned short *);

    return (handler->ntohs(netshort, (APIHook<WORD> &)hook));

} // DTHandler::_ntohs()


bool
DTHandler::recv(SOCKET s, char *buf, int len, int flags, APIHook<int> &hook) {

    return (false);

} // DTHandler::recv()


bool
DTHandler::_recv(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    char *buf = (char *)*va_arg(vList, char **);
    int len = (int)*va_arg(vList, int *);
    int flags = (int)*va_arg(vList, int *);

    return (handler->recv(s, buf, len, flags, (APIHook<int> &)hook));

} // DTHandler::_recv()


bool
DTHandler::recvfrom(SOCKET s, char *buf, int len, int flags, struct sockaddr *from, int *fromlen, APIHook<int> &hook) {

    return (false);

} // DTHandler::recvfrom()


bool
DTHandler::_recvfrom(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    char *buf = (char *)*va_arg(vList, char **);
    int len = (int)*va_arg(vList, int *);
    int flags = (int)*va_arg(vList, int *);
    struct sockaddr *from = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    int *fromlen = (int *)*va_arg(vList, int **);

    return (handler->recvfrom(s, buf, len, flags, from, fromlen, (APIHook<int> &)hook));

} // DTHandler::_recvfrom()


bool
DTHandler::select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                  const struct timeval *timeout, APIHook<int> &hook) {

    return (false);

} // DTHandler::select()


bool
DTHandler::_select(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int nfds = (int)*va_arg(vList, int *);
    fd_set *readfds = (fd_set *)*va_arg(vList, fd_set **);
    fd_set *writefds = (fd_set *)*va_arg(vList, fd_set **);
    fd_set *exceptfds = (fd_set *)*va_arg(vList, fd_set **);
    const struct timeval *timeout = (const struct timeval *)*va_arg(vList, const struct timeval **);

    return (handler->select(nfds, readfds, writefds, exceptfds, timeout, (APIHook<int> &)hook));

} // DTHandler::_select()


bool
DTHandler::send(SOCKET s, const char *buf, int len, int flags, APIHook<int> &hook) {

    return (false);

} // DTHandler::send()


bool
DTHandler::_send(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const char *buf = (const char *)*va_arg(vList, const char **);
    int len = (int)*va_arg(vList, int *);
    int flags = (int)*va_arg(vList, int *);

    return (handler->send(s, buf, len, flags, (APIHook<int> &)hook));

} // DTHandler::_send()


bool
DTHandler::sendto(SOCKET s, const char *buf, int len, int flags, const struct sockaddr *to, int tolen, APIHook<int> &hook) {

    return (false);

} // DTHandler::sendto()


bool
DTHandler::_sendto(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const char *buf = (const char *)*va_arg(vList, const char **);
    int len = (int)*va_arg(vList, int *);
    int flags = (int)*va_arg(vList, int *);
    const struct sockaddr *to = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int tolen = (int)*va_arg(vList, int *);
    
    return (handler->sendto(s, buf, len, flags, to, tolen, (APIHook<int> &)hook));

} // DTHandler::_sendto()


bool
DTHandler::setsockopt(SOCKET s, int level, int optname, const char *optval, int optlen, APIHook<int> &hook) {

    return (false);

} // DTHandler::setsockopt()


bool
DTHandler::_setsockopt(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int level = (int)*va_arg(vList, int *);
    int optname = (int)*va_arg(vList, int *);
    const char *optval = (const char *)*va_arg(vList, const char **);
    int optlen = (int)*va_arg(vList, int *);

    return (handler->setsockopt(s, level, optname, optval, optlen, (APIHook<int> &)hook));

} // DTHandler::_setsockopt()


bool
DTHandler::shutdown(SOCKET s, int how, APIHook<int> &hook) {
    
    return (false);

} // DTHandler::shutdown()


bool
DTHandler::_shutdown(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int how = (int)*va_arg(vList, int *);

    return (handler->shutdown(s, how, (APIHook<int> &)hook));

} // DTHandler::_shutdown()


bool
DTHandler::socket(int af, int type, int protocol, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::socket()


bool
DTHandler::_socket(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int af = (int)*va_arg(vList, int *);
    int type = (int)*va_arg(vList, int *);
    int protocol = (int)*va_arg(vList, int *);

    return (handler->socket(af, type, protocol, (APIHook<SOCKET> &)hook));

} // DTHandler::_socket()


bool
DTHandler::WSAAccept(SOCKET s, struct sockaddr *addr, int *addrlen, LPCONDITIONPROC lpfnCondition,
                     unsigned long dwCallbackData, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSAAccept()


bool
DTHandler::_WSAAccept(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *addr = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    int *addrlen = (int *)*va_arg(vList, int **);
    LPCONDITIONPROC lpfnCondition = (LPCONDITIONPROC)*va_arg(vList, LPCONDITIONPROC *);
    unsigned long dwCallbackData = (unsigned long)*va_arg(vList, unsigned long *);

    return (handler->WSAAccept(s, addr, addrlen, lpfnCondition, dwCallbackData, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSAAccept()


bool
DTHandler::WSAAsyncSelect(SOCKET s, HWND hWnd, unsigned int wMsg, long lEvent, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAAsyncSelect()


bool
DTHandler::_WSAAsyncSelect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    long lEvent = (long)*va_arg(vList, long *);

    return (handler->WSAAsyncSelect(s, hWnd, wMsg, lEvent, (APIHook<int> &)hook));

} // DTHandler::_WSAAsyncSelect()


bool
DTHandler::WSACancelBlockingCall(APIHook<int> &hook) {

    return (false);

} // DTHandler::WSACancelBlockingCall()


bool
DTHandler::_WSACancelBlockingCall(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    return (handler->WSACancelBlockingCall((APIHook<int> &)hook));

} // DTHandler::_WSACancelBlockingCall()


bool
DTHandler::WSACleanup(APIHook<int> &hook) {

    return (false);

} // DTHandler::WSACleanup()


bool
DTHandler::_WSACleanup(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    return (handler->WSACleanup((APIHook<int> &)hook));

} // DTHandler::_WSACleanup()


bool
DTHandler::WSACloseEvent(WSAEVENT hEvent, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSACloseEvent()


bool
DTHandler::_WSACloseEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);

    return (handler->WSACloseEvent(hEvent, (APIHook<int> &)hook));

} // DTHandler::_WSACloseEvent()


bool
DTHandler::WSAConnect(SOCKET s, const struct sockaddr *name, int namelen, LPWSABUF lpCallerData,
                      LPWSABUF lpCalleeData, LPQOS lpSQOS, LPQOS lpGQOS, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAConnect()


bool
DTHandler::_WSAConnect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);
    LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
    LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);

    return (handler->WSAConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS, (APIHook<int> &)hook));

} // DTHandler::_WSAConnect()


bool
DTHandler::WSACreateEvent(APIHook<WSAEVENT> &hook) {

    return (false);

} // DTHandler::WSACreateEvent()


bool
DTHandler::_WSACreateEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    return (handler->WSACreateEvent((APIHook<WSAEVENT> &)hook));

} // DTHandler::_WSACreateEvent()


bool
DTHandler::WSADuplicateSocketA(SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOA lpProtocolInfo, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSADuplicateSocketA()


bool
DTHandler::_WSADuplicateSocketA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    DWORD dwProcessId = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);

    return (handler->WSADuplicateSocketA(s, dwProcessId, lpProtocolInfo, (APIHook<int> &)hook));

} // DTHandler::_WSADuplicateSocketA()


bool
DTHandler::WSADuplicateSocketW(SOCKET s, DWORD dwProcessId, LPWSAPROTOCOL_INFOW lpProtocolInfo, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSADuplicateSocketW()


bool
DTHandler::_WSADuplicateSocketW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    DWORD dwProcessId = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOA *);

    return (handler->WSADuplicateSocketW(s, dwProcessId, lpProtocolInfo, (APIHook<int> &)hook));

} // DTHandler::_WSADuplicateSocketW()


bool
DTHandler::WSAEnumNetworkEvents(SOCKET s, WSAEVENT hEventObject, LPWSANETWORKEVENTS lpNetworkEvents, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAEnumNetworkEvents()


bool
DTHandler::_WSAEnumNetworkEvents(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    LPWSANETWORKEVENTS lpNetworkEvents = (LPWSANETWORKEVENTS)*va_arg(vList, LPWSANETWORKEVENTS *);

    return (handler->WSAEnumNetworkEvents(s, hEventObject, lpNetworkEvents, (APIHook<int> &)hook));

} // DTHandler::_WSAEnumNetworkEvents()


bool
DTHandler::WSAEnumProtocolsA(LPINT lpiProtocols, LPWSAPROTOCOL_INFOA lpProtocolBuffer,
                             LPDWORD lpdwBufferLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAEnumProtocolsA()


bool
DTHandler::_WSAEnumProtocolsA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
    LPWSAPROTOCOL_INFOA lpProtocolBuffer = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAEnumProtocolsA(lpiProtocols, lpProtocolBuffer, lpdwBufferLength, (APIHook<int> &)hook));

} // DTHandler::_WSAEnumProtocolsA()


bool
DTHandler::WSAEnumProtocolsW(LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                             LPDWORD lpdwBufferLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAEnumProtocolsW()


bool
DTHandler::_WSAEnumProtocolsW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
    LPWSAPROTOCOL_INFOW lpProtocolBuffer = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAEnumProtocolsW(lpiProtocols, lpProtocolBuffer, lpdwBufferLength, (APIHook<int> &)hook));

} // DTHandler::_WSAEnumProtocolsW()


bool
DTHandler::WSAEventSelect(SOCKET s, WSAEVENT hEventObject, long lNetworkEvents, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAEventSelect()


bool
DTHandler::_WSAEventSelect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    long lNetworkEvents = (long)*va_arg(vList, long *);

    return (handler->WSAEventSelect(s, hEventObject, lNetworkEvents, (APIHook<int> &)hook));

} // DTHandler::_WSAEventSelect()


bool
DTHandler::WSAGetLastError(APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAGetLastError()


bool
DTHandler::_WSAGetLastError(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    return (handler->WSAGetLastError((APIHook<int> &)hook));

} // DTHandler::_WSAGetLastError()


bool
DTHandler::WSAGetOverlappedResult(SOCKET s, LPWSAOVERLAPPED lpOverlapped, LPDWORD lpcbTransfer,
                                  BOOL fWait, LPDWORD lpdwFlags, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAGetOverlappedResult()


bool
DTHandler::_WSAGetOverlappedResult(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPDWORD lpcbTransfer = (LPDWORD)*va_arg(vList, LPDWORD *);
    BOOL fWait = (BOOL)*va_arg(vList, BOOL *);
    LPDWORD lpdwFlags = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAGetOverlappedResult(s, lpOverlapped, lpcbTransfer, fWait, lpdwFlags, (APIHook<int> &)hook));

} // DTHandler::_WSAGetOverlappedResult()


bool
DTHandler::WSAGetQOSByName(SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAGetQOSByName()


bool
DTHandler::_WSAGetQOSByName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpQOSName = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPQOS lpQOS = (LPQOS)*va_arg(vList, LPQOS *);

    return (handler->WSAGetQOSByName(s, lpQOSName, lpQOS, (APIHook<int> &)hook));

} // DTHandler::_WSAGetQOSByName()


bool
DTHandler::WSAHtonl(SOCKET s, unsigned long hostlong, unsigned long *lpnetlong, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAHtonl()


bool
DTHandler::_WSAHtonl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    unsigned long hostlong = (unsigned long)*va_arg(vList, unsigned long *);
    unsigned long *lpnetlong = (unsigned long *)*va_arg(vList, unsigned long **);

    return (handler->WSAHtonl(s, hostlong, lpnetlong, (APIHook<int> &)hook));

} // DTHandler::_WSAHtonl()


bool
DTHandler::WSAHtons(SOCKET s, unsigned short hostshort, unsigned short *lpnetshort, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAHtons()


bool
DTHandler::_WSAHtons(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    unsigned short hostshort = (unsigned short)*va_arg(vList, unsigned short *);
    unsigned short *lpnetshort = (unsigned short *)*va_arg(vList, unsigned short **);

    return (handler->WSAHtons(s, hostshort, lpnetshort, (APIHook<int> &)hook));

} // DTHandler::_WSAHtons()


bool
DTHandler::WSAIoctl(SOCKET s, DWORD dwIoControlCode,
                    LPVOID lpvInBuffer, DWORD cbInBuffer,
                    LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                    LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped,
                    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAIoctl()


bool
DTHandler::_WSAIoctl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    DWORD dwIoControlCode = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvInBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbInBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvOutBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbOutBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpcbBytesReturned = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);

    return (handler->WSAIoctl(s, dwIoControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer, cbOutBuffer,
                              lpcbBytesReturned, lpOverlapped, lpCompletionRoutine, (APIHook<int> &)hook));

} // DTHandler::_WSAIoctl()


bool
DTHandler::WSAIsBlocking(APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAIsBlocking()


bool
DTHandler::_WSAIsBlocking(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    return (handler->WSAIsBlocking((APIHook<int> &)hook));

} // DTHandler::_WSAIsBlocking()


bool
DTHandler::WSAJoinLeaf(SOCKET s, const struct sockaddr *name, int namelen,
                       LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                       LPQOS lpSQOS, LPQOS lpGQOS, DWORD dwFlags,
                       APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSAJoinLeaf()


bool
DTHandler::_WSAJoinLeaf(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);
    LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
    LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    
    return (handler->WSAJoinLeaf(s, name, namelen, lpCallerData, lpCalleeData,
                                 lpSQOS, lpGQOS, dwFlags, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSAJoinLeaf()


bool
DTHandler::WSANtohl(SOCKET s, unsigned long netlong, unsigned long *lphostlong, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSANtohl()


bool
DTHandler::_WSANtohl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    unsigned long netlong = (unsigned long)*va_arg(vList, unsigned long *);
    unsigned long *lphostlong = (unsigned long *)*va_arg(vList, unsigned long **);

    return (handler->WSANtohl(s, netlong, lphostlong, (APIHook<int> &)hook));

} // DTHandler::_WSANtohl()


bool
DTHandler::WSANtohs(SOCKET s, unsigned short netshort, unsigned short *lphostshort, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSANtohs()


bool
DTHandler::_WSANtohs(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    unsigned short netshort = (unsigned short)*va_arg(vList, unsigned short *);
    unsigned short *lphostshort = (unsigned short *)*va_arg(vList, unsigned short **);

    return (handler->WSANtohs(s, netshort, lphostshort, (APIHook<int> &)hook));

} // DTHandler::_WSANtohs()


bool
DTHandler::WSARecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                   LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                   LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   APIHook<int> &hook) {

    return (false);

} // DTHandler::WSARecv()


bool
DTHandler::_WSARecv(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    
    return (handler->WSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                             lpOverlapped, lpCompletionRoutine, (APIHook<int> &)hook));

} // DTHandler::_WSARecv()


bool
DTHandler::WSARecvDisconnect(SOCKET s, LPWSABUF lpInboundDisconnectData, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSARecvDisconnect()


bool
DTHandler::_WSARecvDisconnect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpInboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    
    return (handler->WSARecvDisconnect(s, lpInboundDisconnectData, (APIHook<int> &)hook));

} // DTHandler::_WSARecvDisconnect()


bool
DTHandler::WSARecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                       LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                       struct sockaddr *lpFrom, LPINT lpFromlen,
                       LPWSAOVERLAPPED lpOverlapped,
                       LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                       APIHook<int> &hook) {

    return (false);

} // DTHandler::WSARecvFrom()


bool
DTHandler::_WSARecvFrom(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
    struct sockaddr *lpFrom = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    LPINT lpFromlen = (LPINT)*va_arg(vList, LPINT *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);

    return (handler->WSARecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                                 lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine, (APIHook<int> &)hook));

} // DTHandler::_WSARecvFrom()


bool
DTHandler::WSAResetEvent(WSAEVENT hEvent, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAResetEvent()


bool
DTHandler::_WSAResetEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);

    return (handler->WSAResetEvent(hEvent, (APIHook<int> &)hook));

} // DTHandler::_WSAResetEvent()


bool
DTHandler::WSASend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent,
                   DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   APIHook<int> &hook) {

    return (false);

} // DTHandler::WSASend()


bool
DTHandler::_WSASend(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    
    return (handler->WSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                             lpOverlapped, lpCompletionRoutine, (APIHook<int> &)hook));

} // DTHandler::_WSASend()


bool
DTHandler::WSASendDisconnect(SOCKET s, LPWSABUF lpOutboundDisconnectData, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSASendDisconnect()


bool
DTHandler::_WSASendDisconnect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpOutboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);

    return (handler->WSASendDisconnect(s, lpOutboundDisconnectData, (APIHook<int> &)hook));

} // DTHandler::_WSASendDisconnect()


bool
DTHandler::WSASendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent,
                     DWORD dwFlags, const struct sockaddr *lpTo, int iTolen, LPWSAOVERLAPPED lpOverlapped,
                     LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                     APIHook<int> &hook) {

    return (false);

} // DTHandler::WSASendTo()


bool
DTHandler::_WSASendTo(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    const struct sockaddr *lpTo = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int iTolen = (int)*va_arg(vList, int *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    
    return (handler->WSASendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                               lpTo, iTolen, lpOverlapped, lpCompletionRoutine, (APIHook<int> &)hook));

} // DTHandler::_WSASendTo()


bool
DTHandler::WSASetBlockingHook(FARPROC lpBlockFunc, APIHook<FARPROC> &hook) {

    return (false);

} // DTHandler::WSASetBlockingHook()


bool
DTHandler::_WSASetBlockingHook(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    FARPROC lpBlockFunc = (FARPROC)*va_arg(vList, FARPROC *);

    return (handler->WSASetBlockingHook(lpBlockFunc, (APIHook<FARPROC> &)hook));

} // DTHandler::_WSASetBlockingHook()


bool
DTHandler::WSASetEvent(WSAEVENT hEvent, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSASetEvent()


bool
DTHandler::_WSASetEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);

    return (handler->WSASetEvent(hEvent, (APIHook<int> &)hook));

} // DTHandler::_WSASetEvent()


bool
DTHandler::WSASetLastError(int iError, APIHook<void> &hook) {

    return (false);

} // DTHandler::WSASetLastError()


bool
DTHandler::_WSASetLastError(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int iError = (int)*va_arg(vList, int *);

    return (handler->WSASetLastError(iError, hook));

} // DTHandler::_WSASetLastError()


bool
DTHandler::WSASocketA(int af, int type, int protocol, LPWSAPROTOCOL_INFOA lpProtocolInfo,
                      GROUP g, DWORD dwFlags, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSASocketA()


bool
DTHandler::_WSASocketA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int af = (int)*va_arg(vList, int *);
    int type = (int)*va_arg(vList, int *);
    int protocol = (int)*va_arg(vList, int *);
    LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
    GROUP g = (GROUP)*va_arg(vList, GROUP *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    
    return (handler->WSASocketA(af, type, protocol, lpProtocolInfo, g, dwFlags, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSASocketA()


bool
DTHandler::WSASocketW(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo,
                      GROUP g, DWORD dwFlags, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSASocketW()


bool
DTHandler::_WSASocketW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int af = (int)*va_arg(vList, int *);
    int type = (int)*va_arg(vList, int *);
    int protocol = (int)*va_arg(vList, int *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    GROUP g = (GROUP)*va_arg(vList, GROUP *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    
    return (handler->WSASocketW(af, type, protocol, lpProtocolInfo, g, dwFlags, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSASocketW()


bool
DTHandler::WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAStartup()


bool
DTHandler::_WSAStartup(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WORD wVersionRequested = (WORD)*va_arg(vList, LPDWORD);
    LPWSADATA lpWSAData = (LPWSADATA)*va_arg(vList, LPWSADATA *);
    
    return (handler->WSAStartup(wVersionRequested, lpWSAData, (APIHook<int> &)hook));

} // DTHandler::_WSAStartup()


bool
DTHandler::WSAUnhookBlockingHook(APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAUnhookBlockingHook()


bool
DTHandler::_WSAUnhookBlockingHook(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    return (handler->WSAUnhookBlockingHook((APIHook<int> &)hook));

} // DTHandler::_WSAUnhookBlockingHook()


bool
DTHandler::WSAWaitForMultipleEvents(DWORD cEvents, const WSAEVENT *lphEvents,
                                    BOOL fWaitAll, DWORD dwTimeout, BOOL fAlertable,
                                    APIHook<DWORD> &hook) {

    return (false);

} // DTHandler::WSAWaitForMultipleEvents()


bool
DTHandler::_WSAWaitForMultipleEvents(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    DWORD cEvents = (DWORD)*va_arg(vList, DWORD *);
    const WSAEVENT *lphEvents = (const WSAEVENT *)*va_arg(vList, const WSAEVENT **);
    BOOL fWaitAll = (BOOL)*va_arg(vList, BOOL *);
    DWORD dwTimeout = (DWORD)*va_arg(vList, DWORD *);
    BOOL fAlertable = (BOOL)*va_arg(vList, BOOL *);
    
    return (handler->WSAWaitForMultipleEvents(cEvents, lphEvents, fWaitAll, dwTimeout, fAlertable, (APIHook<DWORD> &)hook));

} // DTHandler::_WSAWaitForMultipleEvents()


bool
DTHandler::gethostbyaddr(const char *addr, int len, int type, APIHook<HOSTENT> &hook) {

    return (false);

} // DTHandler::gethostbyaddr()


bool
DTHandler::_gethostbyaddr(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const char *addr = (const char *)*va_arg(vList, const char **);
    int len = (int)*va_arg(vList, int *);
    int type = (int)*va_arg(vList, int *);
    
    return (handler->gethostbyaddr(addr, len, type, (APIHook<HOSTENT> &)hook));

} // DTHandler::_gethostbyaddr()


bool
DTHandler::gethostbyname(const char *name, APIHook<HOSTENT> &hook) {

    return (false);

} // DTHandler::gethostbyname()


bool
DTHandler::_gethostbyname(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const char *name = (const char *)*va_arg(vList, const char **);

    return (handler->gethostbyname(name, (APIHook<HOSTENT> &)hook));

} // DTHandler::_gethostbyname()


bool
DTHandler::gethostname(char *name, int namelen, APIHook<int> &hook) {

    return (false);

} // DTHandler::gethostname()


bool
DTHandler::_gethostname(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    char *name = (char *)*va_arg(vList, char **);
    int namelen = (int)*va_arg(vList, int *);

    return (handler->gethostname(name, namelen, (APIHook<int> &)hook));

} // DTHandler::_gethostname()


bool
DTHandler::getprotobyname(const char *name, APIHook<PROTOENT> &hook) {

    return (false);

} // DTHandler::getprotobyname()


bool
DTHandler::_getprotobyname(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const char *name = (const char *)*va_arg(vList, const char **);

    return (handler->getprotobyname(name, (APIHook<PROTOENT> &)hook));

} // DTHandler::_getprotobyname()


bool
DTHandler::getprotobynumber(int number, APIHook<PROTOENT> &hook) {

    return (false);

} // DTHandler::getprotobynumber()


bool
DTHandler::_getprotobynumber(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int number = (int)*va_arg(vList, int *);

    return (handler->getprotobynumber(number, (APIHook<PROTOENT> &)hook));

} // DTHandler::_getprotobynumber()


bool
DTHandler::getservbyname(const char *name, const char *proto, APIHook<SERVENT> &hook) {

    return (false);

} // DTHandler::getservbyname()


bool
DTHandler::_getservbyname(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const char *name = (const char *)*va_arg(vList, const char **);
    const char *proto = (const char *)*va_arg(vList, const char **);

    return (handler->getservbyname(name, proto, (APIHook<SERVENT> &)hook));

} // DTHandler::_getservbyname()


bool
DTHandler::getservbyport(int port, const char *proto, APIHook<SERVENT> &hook) {

    return (false);

} // DTHandler::getservbyport()


bool
DTHandler::_getservbyport(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int port = (int)*va_arg(vList, int *);
    const char *proto = (const char *)*va_arg(vList, const char **);

    return (handler->getservbyport(port, proto, (APIHook<SERVENT> &)hook));

} // DTHandler::_getservbyport()


bool
DTHandler::inet_addr(const char *cp, APIHook<unsigned long> &hook) {

    return (false);

} // DTHandler::inet_addr()


bool
DTHandler::_inet_addr(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const char *cp = (const char *)*va_arg(vList, const char **);

    return (handler->inet_addr(cp, (APIHook<unsigned long> &)hook));

} // DTHandler::_inet_addr()


bool
DTHandler::inet_ntoa(struct in_addr in, APIHook<char *> &hook) {

    return (false);

} // DTHandler::inet_ntoa()


bool
DTHandler::_inet_ntoa(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    struct in_addr in = (struct in_addr)*va_arg(vList, struct in_addr *);

    return (handler->inet_ntoa(in, (APIHook<char *> &)hook));

} // DTHandler::_inet_ntoa()


bool
DTHandler::WSAAsyncGetHostByAddr(HWND hWnd, unsigned int wMsg, const char *addr,  
                                 int len, int type, char *buf, int buflen,
                                 APIHook<HANDLE> &hook) {

    return (false);

} // DTHandler::WSAAsyncGetHostByAddr()


bool
DTHandler::_WSAAsyncGetHostByAddr(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    const char *addr = (const char *)*va_arg(vList, const char **);
    int len = (int)*va_arg(vList, int *);
    int type = (int)*va_arg(vList, int *);
    char *buf = (char *)*va_arg(vList, char **);
    int buflen = (int)*va_arg(vList, int *);

    return (handler->WSAAsyncGetHostByAddr(hWnd, wMsg, addr, len, type, buf, buflen, (APIHook<HANDLE> &)hook));

} // DTHandler::_WSAAsyncGetHostByAddr()


bool
DTHandler::WSAAsyncGetHostByName(HWND hWnd, unsigned int wMsg, const char *name,  
                                 char *buf, int buflen, APIHook<HANDLE> &hook) {

    return (false);

} // DTHandler::WSAAsyncGetHostByName()


bool
DTHandler::_WSAAsyncGetHostByName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    const char *name = (const char *)*va_arg(vList, const char **);
    char *buf = (char *)*va_arg(vList, char **);
    int buflen = (int)*va_arg(vList, int *);

    return (handler->WSAAsyncGetHostByName(hWnd, wMsg, name, buf, buflen, (APIHook<HANDLE> &)hook));

} // DTHandler::_WSAAsyncGetHostByName()


bool
DTHandler::WSAAsyncGetProtoByName(HWND hWnd, unsigned int wMsg, const char *name,  
                                  char *buf, int buflen, APIHook<HANDLE> &hook) {

    return (false);

} // DTHandler::WSAAsyncGetProtoByName()


bool
DTHandler::_WSAAsyncGetProtoByName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    const char *name = (const char *)*va_arg(vList, const char **);
    char *buf = (char *)*va_arg(vList, char **);
    int buflen = (int)*va_arg(vList, int *);

    return (handler->WSAAsyncGetProtoByName(hWnd, wMsg, name, buf, buflen, (APIHook<HANDLE> &)hook));

} // DTHandler::_WSAAsyncGetProtoByName()


bool
DTHandler::WSAAsyncGetProtoByNumber(HWND hWnd, unsigned int wMsg, int number, char *buf,
                                    int buflen, APIHook<HANDLE> &hook) {

    return (false);

} // DTHandler::WSAAsyncGetProtoByNumber()


bool
DTHandler::_WSAAsyncGetProtoByNumber(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    int number = (int)*va_arg(vList, int *);
    char *buf = (char *)*va_arg(vList, char **);
    int buflen = (int)*va_arg(vList, int *);

    return (handler->WSAAsyncGetProtoByNumber(hWnd, wMsg, number, buf, buflen, (APIHook<HANDLE> &)hook));

} // DTHandler::_WSAAsyncGetProtoByNumber()


bool
DTHandler::WSAAsyncGetServByName(HWND hWnd, unsigned int wMsg, const char *name,  
                                 const char *proto, char *buf, int buflen,
                                 APIHook<HANDLE> &hook) {

    return (false);

} // DTHandler::WSAAsyncGetServByName()


bool
DTHandler::_WSAAsyncGetServByName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    const char *name = (const char *)*va_arg(vList, const char **);
    const char *proto = (const char *)*va_arg(vList, const char **);
    char *buf = (char *)*va_arg(vList, char **);
    int buflen = (int)*va_arg(vList, int *);

    return (handler->WSAAsyncGetServByName(hWnd, wMsg, name, proto, buf, buflen, (APIHook<HANDLE> &)hook));

} // DTHandler::_WSAAsyncGetServByName()


bool
DTHandler::WSAAsyncGetServByPort(HWND hWnd, unsigned int wMsg, int port,
                                 const char *proto, char *buf, int buflen,
                                 APIHook<HANDLE> &hook) {

    return (false);

} // DTHandler::WSAAsyncGetServByPort()


bool
DTHandler::_WSAAsyncGetServByPort(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    int port = (int)*va_arg(vList, int *);
    char *proto = (char *)*va_arg(vList, char **);
    char *buf = (char *)*va_arg(vList, char **);
    int buflen = (int)*va_arg(vList, int *);

    return (handler->WSAAsyncGetServByPort(hWnd, wMsg, port, proto, buf, buflen, (APIHook<HANDLE> &)hook));

} // DTHandler::_WSAAsyncGetServByPort()


bool
DTHandler::WSACancelAsyncRequest(HANDLE hAsyncTaskHandle, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSACancelAsyncRequest()


bool
DTHandler::_WSACancelAsyncRequest(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hAsyncTaskHandle = (HANDLE)*va_arg(vList, HANDLE *);

    return (handler->WSACancelAsyncRequest(hAsyncTaskHandle, (APIHook<int> &)hook));

} // DTHandler::_WSACancelAsyncRequest()


bool
DTHandler::WSPAccept(SOCKET s, struct sockaddr *addr, LPINT addrlen,
                     LPCONDITIONPROC lpfnCondition, DWORD dwCallbackData,
                     LPINT lpErrno, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSPAccept()


bool
DTHandler::_WSPAccept(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *addr = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    LPINT addrlen = (LPINT)*va_arg(vList, LPINT *);
    LPCONDITIONPROC lpfnCondition = (LPCONDITIONPROC)*va_arg(vList, LPCONDITIONPROC *);
    DWORD dwCallbackData = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPAccept(s, addr, addrlen, lpfnCondition, dwCallbackData, lpErrno, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSPAccept()


bool
DTHandler::WSPAsyncSelect(SOCKET s, HWND hWnd, unsigned int wMsg,
                          long lEvent, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPAsyncSelect()


bool
DTHandler::_WSPAsyncSelect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    unsigned int wMsg = (unsigned int)*va_arg(vList, unsigned int *);
    long lEvent = (long)*va_arg(vList, long *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPAsyncSelect(s, hWnd, wMsg, lEvent, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPAsyncSelect()


bool
DTHandler::WSPBind(SOCKET s, const struct sockaddr *name, int namelen,
                   LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPBind()


bool
DTHandler::_WSPBind(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPBind(s, name, namelen, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPBind()


bool
DTHandler::WSPCancelBlockingCall(LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPCancelBlockingCall()


bool
DTHandler::_WSPCancelBlockingCall(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPCancelBlockingCall(lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPCancelBlockingCall()


bool
DTHandler::WSPCleanup(LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPCleanup()


bool
DTHandler::_WSPCleanup(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPCleanup(lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPCleanup()


bool
DTHandler::WSPCloseSocket(SOCKET s, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPCloseSocket()


bool
DTHandler::_WSPCloseSocket(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPCloseSocket(s, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPCloseSocket()


bool
DTHandler::WSPConnect(SOCKET s, const struct sockaddr *name, int namelen,
                      LPWSABUF lpCallerData, LPWSABUF lpCalleeData,
                      LPQOS lpSQOS, LPQOS lpGQOS, LPINT lpErrno,
                      APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPConnect()


bool
DTHandler::_WSPConnect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);
    LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
    LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPConnect(s, name, namelen, lpCallerData, lpCalleeData,
                           lpSQOS, lpGQOS, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPConnect()


bool
DTHandler::WSPDuplicateSocket(SOCKET s, DWORD dwProcessId,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPINT lpErrno,
                              APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPDuplicateSocket()


bool
DTHandler::_WSPDuplicateSocket(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    DWORD dwProcessId = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPDuplicateSocket(s, dwProcessId, lpProtocolInfo, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPDuplicateSocket()


bool
DTHandler::WSPEnumNetworkEvents(SOCKET s, WSAEVENT hEventObject,
                                LPWSANETWORKEVENTS lpNetworkEvents, LPINT lpErrno,
                                APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPEnumNetworkEvents()


bool
DTHandler::_WSPEnumNetworkEvents(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    LPWSANETWORKEVENTS lpNetworkEvents = (LPWSANETWORKEVENTS)*va_arg(vList, LPWSANETWORKEVENTS *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPEnumNetworkEvents(s, hEventObject, lpNetworkEvents, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPEnumNetworkEvents()


bool
DTHandler::WSPEventSelect(SOCKET s, WSAEVENT hEventObject, long lNetworkEvents,
                          LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPEventSelect()


bool
DTHandler::_WSPEventSelect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    WSAEVENT hEventObject = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    long lNetworkEvents = (long)*va_arg(vList, long *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPEventSelect(s, hEventObject, lNetworkEvents, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPEventSelect()


bool
DTHandler::WSPGetOverlappedResult(SOCKET s, LPWSAOVERLAPPED lpOverlapped,
                                  LPDWORD lpcbTransfer, BOOL fWait, LPDWORD lpdwFlags,
                                  LPINT lpErrno, APIHook<BOOL> &hook) {

    return (false);

} // DTHandler::WSPGetOverlappedResult()


bool
DTHandler::_WSPGetOverlappedResult(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPDWORD lpcbTransfer = (LPDWORD)*va_arg(vList, LPDWORD *);
    BOOL fWait = (BOOL)*va_arg(vList, BOOL *);
    LPDWORD lpdwFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPGetOverlappedResult(s, lpOverlapped, lpcbTransfer, fWait,
                                            lpdwFlags, lpErrno, (APIHook<BOOL> &)hook));

} // DTHandler::_WSPGetOverlappedResult()


bool
DTHandler::WSPGetPeerName(SOCKET s, struct sockaddr *name, LPINT namelen,
                          LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPGetPeerName()


bool
DTHandler::_WSPGetPeerName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    LPINT namelen = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPGetPeerName(s, name, namelen, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPGetPeerName()


bool
DTHandler::WSPGetSockName(SOCKET s, struct sockaddr *name, LPINT namelen,
                          LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPGetSockName()


bool
DTHandler::_WSPGetSockName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    struct sockaddr *name = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    LPINT namelen = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPGetSockName(s, name, namelen, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPGetSockName()


bool
DTHandler::WSPGetSockOpt(SOCKET s, int level, int optname, char *optval, 
                         LPINT optlen, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPGetSockOpt()


bool
DTHandler::_WSPGetSockOpt(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int level = (int)*va_arg(vList, int *);
    int optname = (int)*va_arg(vList, int *);
    char *optval = (char *)*va_arg(vList, char **);
    LPINT optlen = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPGetSockOpt(s, level, optname, optval, optlen, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPGetSockOpt()


bool
DTHandler::WSPGetQOSByName(SOCKET s, LPWSABUF lpQOSName, LPQOS lpQOS,
                           LPINT lpErrno, APIHook<BOOL> &hook) {

    return (false);

} // DTHandler::WSPGetQOSByName()


bool 
DTHandler::_WSPGetQOSByName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpQOSName = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPQOS lpQOS = (LPQOS)*va_arg(vList, LPQOS *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPGetQOSByName(s, lpQOSName, lpQOS, lpErrno, (APIHook<BOOL> &)hook));

} // DTHandler::_WSPGetQOSByName()


bool
DTHandler::WSPIoctl(SOCKET s, DWORD dwIoControlCode, LPVOID lpvInBuffer,
                    DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer,
                    LPDWORD lpcbBytesReturned, LPWSAOVERLAPPED lpOverlapped,
                    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                    LPWSATHREADID lpThreadId, LPINT lpErrno,
                    APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPIoctl()


bool
DTHandler::_WSPIoctl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    DWORD dwIoControlCode = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvInBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbInBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvOutBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbOutBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpcbBytesReturned = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPIoctl(s, dwIoControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer,
                              cbOutBuffer, lpcbBytesReturned, lpOverlapped,
                              lpCompletionRoutine, lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPIoctl()


bool
DTHandler::WSPJoinLeaf(SOCKET s, const struct sockaddr *name, int namelen,
                       LPWSABUF lpCallerData, LPWSABUF lpCalleeData, LPQOS lpSQOS,
                       LPQOS lpGQOS, DWORD dwFlags, LPINT lpErrno,
                       APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSPJoinLeaf()


bool
DTHandler::_WSPJoinLeaf(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    const struct sockaddr *name = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int namelen = (int)*va_arg(vList, int *);
    LPWSABUF lpCallerData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPWSABUF lpCalleeData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPQOS lpSQOS = (LPQOS)*va_arg(vList, LPQOS *);
    LPQOS lpGQOS = (LPQOS)*va_arg(vList, LPQOS *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPJoinLeaf(s, name, namelen, lpCallerData, lpCalleeData,
                                 lpSQOS, lpGQOS, dwFlags, lpErrno, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSPJoinLeaf()


bool
DTHandler::WSPListen(SOCKET s, int backlog, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPListen()


bool
DTHandler::_WSPListen(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int backlog = (int)*va_arg(vList, int *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPListen(s, backlog, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPListen()


bool
DTHandler::WSPRecv(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                   LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                   LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   LPWSATHREADID lpThreadId, LPINT lpErrno,
                   APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPRecv()


bool
DTHandler::_WSPRecv(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPRecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                             lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPRecv()


bool
DTHandler::WSPRecvDisconnect(SOCKET s, LPWSABUF lpInboundDisconnectData,
                             LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPRecvDisconnect()


bool
DTHandler::_WSPRecvDisconnect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpInboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPRecvDisconnect(s, lpInboundDisconnectData, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPRecvDisconnect()


bool
DTHandler::WSPRecvFrom(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                       LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,
                       struct sockaddr *lpFrom, LPINT lpFromlen,
                       LPWSAOVERLAPPED lpOverlapped,
                       LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                       LPWSATHREADID lpThreadId, LPINT lpErrno,
                       APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPRecvFrom()


bool
DTHandler::_WSPRecvFrom(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesRecvd = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPDWORD lpFlags = (LPDWORD)*va_arg(vList, LPDWORD *);
    struct sockaddr *lpFrom = (struct sockaddr *)*va_arg(vList, struct sockaddr **);
    LPINT lpFromlen = (LPINT)*va_arg(vList, LPINT *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPRecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags,
                                 lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine,
                                 lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPRecvFrom()


bool
DTHandler::WSPSelect(int nfds, fd_set *readfds, fd_set *writefds,
                     fd_set *exceptfds, const struct timeval *timeout,
                     LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPSelect()


bool
DTHandler::_WSPSelect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int nfds = (int)*va_arg(vList, int *);
    fd_set *readfds = (fd_set *)*va_arg(vList, fd_set **);
    fd_set *writefds = (fd_set *)*va_arg(vList, fd_set **);
    fd_set *exceptfds = (fd_set *)*va_arg(vList, fd_set **);
    const struct timeval *timeout = (const struct timeval *)*va_arg(vList, const struct timeval **);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPSelect(nfds, readfds, writefds, exceptfds, timeout, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPSelect()


bool
DTHandler::WSPSend(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                   LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                   LPWSAOVERLAPPED lpOverlapped,
                   LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                   LPWSATHREADID lpThreadId, LPINT lpErrno,
                   APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPSend()


bool
DTHandler::_WSPSend(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPSend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                             lpOverlapped, lpCompletionRoutine, lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPSend()


bool
DTHandler::WSPSendDisconnect(SOCKET s, LPWSABUF lpOutboundDisconnectData,
                             LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPSendDisconnect()


bool
DTHandler::_WSPSendDisconnect(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpOutboundDisconnectData = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPSendDisconnect(s, lpOutboundDisconnectData, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPSendDisconnect()


bool
DTHandler::WSPSendTo(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount,
                     LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
                     const struct sockaddr *lpTo, int iTolen,
                     LPWSAOVERLAPPED lpOverlapped,
                     LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
                     LPWSATHREADID lpThreadId, LPINT lpErrno,
                     APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPSendTo()


bool
DTHandler::_WSPSendTo(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSABUF lpBuffers = (LPWSABUF)*va_arg(vList, LPWSABUF *);
    DWORD dwBufferCount = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpNumberOfBytesSent = (LPDWORD)*va_arg(vList, LPDWORD *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    const struct sockaddr *lpTo = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    int iTolen = (int)*va_arg(vList, int *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine =
    (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);
    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPSendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags,
                               lpTo, iTolen, lpOverlapped, lpCompletionRoutine,
                               lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPSendTo()


bool
DTHandler::WSPSetSockOpt(SOCKET s, int level, int optname, const char *optval,
                         int optlen, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPSetSockOpt()


bool
DTHandler::_WSPSetSockOpt(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int level = (int)*va_arg(vList, int *);
    int optname = (int)*va_arg(vList, int *);
    const char *optval = (const char *)*va_arg(vList, const char **);
    int optlen = (int)*va_arg(vList, int *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPSetSockOpt(s, level, optname, optval, optlen, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPSetSockOpt()


bool
DTHandler::WSPShutdown(SOCKET s, int how, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPShutdown()


bool
DTHandler::_WSPShutdown(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    int how = (int)*va_arg(vList, int *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPShutdown(s, how, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPShutdown()


bool
DTHandler::WSPSocket(int af, int type, int protocol, LPWSAPROTOCOL_INFOW lpProtocolInfo,
                     GROUP g, DWORD dwFlags, LPINT lpErrno, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WSPSocket()


bool
DTHandler::_WSPSocket(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    int af = (int)*va_arg(vList, int *);
    int type = (int)*va_arg(vList, int *);
    int protocol = (int)*va_arg(vList, int *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    GROUP g = (GROUP)*va_arg(vList, GROUP *);
    DWORD dwFlags = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPSocket(af, type, protocol, lpProtocolInfo, g, dwFlags, lpErrno, (APIHook<SOCKET> &)hook));

} // DTHandler::_WSPSocket()


bool
DTHandler::WSPStartup(WORD wVersionRequested, LPWSPDATA lpWSPData,
                      LPWSAPROTOCOL_INFOW lpProtocolInfo, WSPUPCALLTABLE UpcallTable,
                      LPWSPPROC_TABLE lpProcTable, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPStartup()


bool
DTHandler::_WSPStartup(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WORD wVersionRequested = (WORD)*va_arg(vList, WORD *);
    LPWSPDATA lpWSPData = (LPWSPDATA)*va_arg(vList, LPWSPDATA *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    WSPUPCALLTABLE UpcallTable = (WSPUPCALLTABLE)*va_arg(vList, WSPUPCALLTABLE *);
    LPWSPPROC_TABLE lpProcTable = (LPWSPPROC_TABLE)*va_arg(vList, LPWSPPROC_TABLE *);

    return (handler->WSPStartup(wVersionRequested, lpWSPData, lpProtocolInfo,
                                UpcallTable, lpProcTable, (APIHook<int> &)hook));

} // DTHandler::_WSPStartup()


bool
DTHandler::WPUCloseEvent(WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> &hook) {

    return (false);

} // DTHandler::WPUCloseEvent()


bool
DTHandler::_WPUCloseEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUCloseEvent(hEvent, lpErrno, (APIHook<BOOL> &)hook));

} // DTHandler::_WPUCloseEvent()


bool
DTHandler::WPUCloseSocketHandle(SOCKET s, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUCloseSocketHandle()


bool
DTHandler::_WPUCloseSocketHandle(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUCloseSocketHandle(s, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUCloseSocketHandle()


bool
DTHandler::WPUCreateEvent(LPINT lpErrno, APIHook<WSAEVENT> &hook) {

    return (false);

} // DTHandler::WPUCreateEvent()


bool
DTHandler::_WPUCreateEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUCreateEvent(lpErrno, (APIHook<WSAEVENT> &)hook));

} // DTHandler::_WPUCreateEvent()


bool
DTHandler::WPUCreateSocketHandle(DWORD dwCatalogEntryId, DWORD dwContext,
                                 LPINT lpErrno, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WPUCreateSocketHandle()


bool
DTHandler::_WPUCreateSocketHandle(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    DWORD dwCatalogEntryId = (DWORD)*va_arg(vList, DWORD *);
    DWORD dwContext = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUCreateSocketHandle(dwCatalogEntryId, dwContext, lpErrno, (APIHook<SOCKET> &)hook));

} // DTHandler::_WPUCreateSocketHandle()


bool
DTHandler::WSCDeinstallProvider(LPGUID lpProviderId, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCDeinstallProvider()


bool
DTHandler::_WSCDeinstallProvider(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCDeinstallProvider(lpProviderId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCDeinstallProvider()


bool
DTHandler::WSCInstallProvider(const LPGUID lpProviderId, const LPWSTR lpszProviderDllPath,
                              const LPWSAPROTOCOL_INFOW lpProtocolInfoList,
                              DWORD dwNumberOfEntries, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCInstallProvider()


bool
DTHandler::_WSCInstallProvider(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const LPGUID lpProviderId = (const LPGUID)*va_arg(vList, const LPGUID *);
    const LPWSTR lpszProviderDllPath = (const LPWSTR)*va_arg(vList, const LPWSTR *);
    const LPWSAPROTOCOL_INFOW lpProtocolInfoList = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCInstallProvider(lpProviderId, lpszProviderDllPath, lpProtocolInfoList,
                                        dwNumberOfEntries, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCInstallProvider()


bool
DTHandler::WPUModifyIFSHandle(DWORD dwCatalogEntryId, SOCKET ProposedHandle,
                              LPINT lpErrno, APIHook<SOCKET> &hook) {

    return (false);

} // DTHandler::WPUModifyIFSHandle()


bool
DTHandler::_WPUModifyIFSHandle(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    DWORD dwCatalogEntryId = (DWORD)*va_arg(vList, DWORD *);
    SOCKET ProposedHandle = (SOCKET)*va_arg(vList, SOCKET *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUModifyIFSHandle(dwCatalogEntryId, ProposedHandle, lpErrno, (APIHook<SOCKET> &)hook));

} // DTHandler::_WPUModifyIFSHandle()


bool
DTHandler::WPUQueryBlockingCallback(DWORD dwCatalogEntryId,
                                    LPBLOCKINGCALLBACK *lplpfnCallback,
                                    LPDWORD lpdwContext, LPINT lpErrno,
                                    APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUQueryBlockingCallback()


bool
DTHandler::_WPUQueryBlockingCallback(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    DWORD dwCatalogEntryId = (DWORD)*va_arg(vList, DWORD *);
    LPBLOCKINGCALLBACK *lplpfnCallback = (LPBLOCKINGCALLBACK *)*va_arg(vList, LPBLOCKINGCALLBACK **);
    LPDWORD lpdwContext = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUQueryBlockingCallback(dwCatalogEntryId, lplpfnCallback, lpdwContext, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUQueryBlockingCallback()


bool
DTHandler::WPUQuerySocketHandleContext(SOCKET s, LPDWORD lpContext,
                                       LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUQuerySocketHandleContext()


bool
DTHandler::_WPUQuerySocketHandleContext(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPDWORD lpContext = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUQuerySocketHandleContext(s, lpContext, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUQuerySocketHandleContext()


bool
DTHandler::WPUQueueApc(LPWSATHREADID lpThreadId, LPWSAUSERAPC lpfnUserApc,
                       DWORD dwContext, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUQueueApc()


bool
DTHandler::_WPUQueueApc(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPWSAUSERAPC lpfnUserApc = (LPWSAUSERAPC)*va_arg(vList, LPWSAUSERAPC *);
    DWORD dwContext = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUQueueApc(lpThreadId, lpfnUserApc, dwContext, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUQueueApc()


bool
DTHandler::WPUResetEvent(WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> &hook) {

    return (false);

} // DTHandler::WPUResetEvent()


bool
DTHandler::_WPUResetEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUResetEvent(hEvent, lpErrno, (APIHook<BOOL> &)hook));

} // DTHandler::_WPUResetEvent()


bool
DTHandler::WPUSetEvent(WSAEVENT hEvent, LPINT lpErrno, APIHook<BOOL> &hook) {

    return (false);

} // DTHandler::WPUSetEvent()


bool
DTHandler::_WPUSetEvent(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    WSAEVENT hEvent = (WSAEVENT)*va_arg(vList, WSAEVENT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUSetEvent(hEvent, lpErrno, (APIHook<BOOL> &)hook));

} // DTHandler::_WPUSetEvent()


bool
DTHandler::WPUFDIsSet(SOCKET s, FD_SET *set, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUFDIsSet()


bool
DTHandler::_WPUFDIsSet(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    FD_SET *set = (FD_SET *)*va_arg(vList, FD_SET **);

    return (handler->WPUFDIsSet(s, set, (APIHook<int> &)hook));

} // DTHandler::_WPUFDIsSet()


bool
DTHandler::WPUGetProviderPath(LPGUID lpProviderId, LPWSTR lpszProviderDllPath,
                              LPINT lpProviderDllPathLen, LPINT lpErrno,
                              APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUGetProviderPath()


bool
DTHandler::_WPUGetProviderPath(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSTR lpszProviderDllPath = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPINT lpProviderDllPathLen = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUGetProviderPath(lpProviderId, lpszProviderDllPath, lpProviderDllPathLen,
                                        lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUGetProviderPath()


bool
DTHandler::WPUPostMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, APIHook<BOOL> &hook) {

    return (false);

} // DTHandler::WPUPostMessage()


bool
DTHandler::_WPUPostMessage(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HWND hWnd = (HWND)*va_arg(vList, HWND *);
    UINT Msg = (UINT)*va_arg(vList, UINT *);
    WPARAM wParam = (WPARAM)*va_arg(vList, WPARAM *);
    LPARAM lParam = (LPARAM)*va_arg(vList, LPARAM *);

    return (handler->WPUPostMessage(hWnd, Msg, wParam, lParam, (APIHook<BOOL> &)hook));

} // DTHandler::_WPUPostMessage()


bool
DTHandler::__WSAFDIsSet(SOCKET s, FD_SET *set, APIHook<int> &hook) {

    return (false);

} // DTHandler::__WSAFDIsSet()


bool
DTHandler::___WSAFDIsSet(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    FD_SET *set = (FD_SET *)*va_arg(vList, FD_SET **);

    return (handler->WPUFDIsSet(s, set, (APIHook<int> &)hook));

} // DTHandler::___WSAFDIsSet()


bool
DTHandler::WSCEnumProtocols(LPINT lpiProtocols, LPWSAPROTOCOL_INFOW lpProtocolBuffer,
                            LPDWORD lpdwBufferLength, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCEnumProtocols()


bool
DTHandler::_WSCEnumProtocols(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
    LPWSAPROTOCOL_INFOW lpProtocolBuffer = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCEnumProtocols(lpiProtocols, lpProtocolBuffer, lpdwBufferLength,
                                      lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCEnumProtocols()


bool
DTHandler::WSAAddressToStringA(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                               LPWSAPROTOCOL_INFOA lpProtocolInfo, OUT LPTSTR lpszAddressString,
                               IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAAddressToStringA()


bool
DTHandler::_WSAAddressToStringA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
    LPTSTR lpszAddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
    LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAAddressToStringA(lpsaAddress, dwAddressLength, lpProtocolInfo,
                                         lpszAddressString, lpdwAddressStringLength, (APIHook<INT> &)hook));

} // DTHandler::_WSAAddressToStringA()


bool
DTHandler::WSAAddressToStringW(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                               LPWSAPROTOCOL_INFOW lpProtocolInfo, OUT LPTSTR lpszAddressString,
                               IN OUT LPDWORD lpdwAddressStringLength, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAAddressToStringW()


bool
DTHandler::_WSAAddressToStringW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPTSTR lpszAddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
    LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAAddressToStringW(lpsaAddress, dwAddressLength, lpProtocolInfo,
                                         lpszAddressString, lpdwAddressStringLength, (APIHook<INT> &)hook));

} // DTHandler::_WSAAddressToStringW()


bool
DTHandler::WSAStringToAddressA(LPTSTR AddressString, INT AddressFamily,
                               LPWSAPROTOCOL_INFOA lpProtocolInfo, LPSOCKADDR lpAddress,
                               LPINT lpAddressLength, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAStringToAddressA()


bool
DTHandler::_WSAStringToAddressA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPTSTR AddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
    INT AddressFamily = (INT)*va_arg(vList, INT *);
    LPWSAPROTOCOL_INFOA lpProtocolInfo = (LPWSAPROTOCOL_INFOA)*va_arg(vList, LPWSAPROTOCOL_INFOA *);
    LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSAStringToAddressA(AddressString, AddressFamily, lpProtocolInfo,
                                         lpAddress, lpAddressLength, (APIHook<INT> &)hook));

} // DTHandler::_WSAStringToAddressA()


bool
DTHandler::WSAStringToAddressW(LPTSTR AddressString, INT AddressFamily,
                           LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                           LPINT lpAddressLength, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAStringToAddressW()


bool
DTHandler::_WSAStringToAddressW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPTSTR AddressString = (LPTSTR)*va_arg(vList, LPTSTR *);
    INT AddressFamily = (INT)*va_arg(vList, INT *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSAStringToAddressW(AddressString, AddressFamily, lpProtocolInfo,
                                         lpAddress, lpAddressLength, (APIHook<INT> &)hook));

} // DTHandler::_WSAStringToAddressW()


bool
DTHandler::WSALookupServiceBeginA(LPWSAQUERYSETA lpqsRestrictions, DWORD dwControlFlags,
                                  LPHANDLE lphLookup, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSALookupServiceBeginA()


bool
DTHandler::_WSALookupServiceBeginA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSAQUERYSETA lpqsRestrictions = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
    LPHANDLE lphLookup = (LPHANDLE)*va_arg(vList, LPHANDLE *);

    return (handler->WSALookupServiceBeginA(lpqsRestrictions, dwControlFlags, lphLookup, (APIHook<INT> &)hook));

} // DTHandler::_WSALookupServiceBeginA()


bool
DTHandler::WSALookupServiceBeginW(LPWSAQUERYSETW lpqsRestrictions, DWORD dwControlFlags,
                                  LPHANDLE lphLookup, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSALookupServiceBeginW()


bool
DTHandler::_WSALookupServiceBeginW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSAQUERYSETW lpqsRestrictions = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
    LPHANDLE lphLookup = (LPHANDLE)*va_arg(vList, LPHANDLE *);

    return (handler->WSALookupServiceBeginW(lpqsRestrictions, dwControlFlags, lphLookup, (APIHook<INT> &)hook));

} // DTHandler::_WSALookupServiceBeginW()


bool
DTHandler::WSALookupServiceNextA(HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                 LPWSAQUERYSETA lpqsResults, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSALookupServiceNextA()


bool
DTHandler::_WSALookupServiceNextA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAQUERYSETA lpqsResults = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);

    return (handler->WSALookupServiceNextA(hLookup, dwControlFlags, lpdwBufferLength,
                                           lpqsResults, (APIHook<INT> &)hook));

} // DTHandler::_WSALookupServiceNextA()


bool
DTHandler::WSALookupServiceNextW(HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                 LPWSAQUERYSETW lpqsResults, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSALookupServiceNextW()


bool
DTHandler::_WSALookupServiceNextW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAQUERYSETW lpqsResults = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);

    return (handler->WSALookupServiceNextW(hLookup, dwControlFlags, lpdwBufferLength,
                                           lpqsResults, (APIHook<INT> &)hook));

} // DTHandler::_WSALookupServiceNextW()


bool
DTHandler::WSALookupServiceEnd(HANDLE hLookup, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSALookupServiceEnd()


bool
DTHandler::_WSALookupServiceEnd(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);

    return (handler->WSALookupServiceEnd(hLookup, (APIHook<INT> &)hook));

} // DTHandler::_WSALookupServiceEnd()


bool
DTHandler::WSAInstallServiceClassA(LPWSASERVICECLASSINFOA lpServiceClassInfo, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAInstallServiceClassA()


bool
DTHandler::_WSAInstallServiceClassA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSASERVICECLASSINFOA lpServiceClassInfo = (LPWSASERVICECLASSINFOA)*va_arg(vList, LPWSASERVICECLASSINFOA *);

    return (handler->WSAInstallServiceClassA(lpServiceClassInfo, (APIHook<INT> &)hook));

} // DTHandler::_WSAInstallServiceClassA()


bool
DTHandler::WSAInstallServiceClassW(LPWSASERVICECLASSINFOW lpServiceClassInfo, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAInstallServiceClassW()


bool
DTHandler::_WSAInstallServiceClassW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);

    return (handler->WSAInstallServiceClassW(lpServiceClassInfo, (APIHook<INT> &)hook));

} // DTHandler::_WSAInstallServiceClassW()


bool
DTHandler::WSASetServiceA(LPWSAQUERYSETA lpqsRegInfo, WSAESETSERVICEOP essOperation,
                          DWORD dwControlFlags, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSASetServiceA()


bool
DTHandler::_WSASetServiceA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSAQUERYSETA lpqsRegInfo = (LPWSAQUERYSETA)*va_arg(vList, LPWSAQUERYSETA *);
    WSAESETSERVICEOP essOperation = (WSAESETSERVICEOP)*va_arg(vList, LPWSAESETSERVICEOP);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);

    return (handler->WSASetServiceA(lpqsRegInfo, essOperation, dwControlFlags, (APIHook<INT> &)hook));

} // DTHandler::_WSASetServiceA()


bool
DTHandler::WSASetServiceW(LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation,
                          DWORD dwControlFlags, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSASetServiceW()


bool
DTHandler::_WSASetServiceW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSAQUERYSETW lpqsRegInfo = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
    WSAESETSERVICEOP essOperation = (WSAESETSERVICEOP)*va_arg(vList, LPWSAESETSERVICEOP);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);

    return (handler->WSASetServiceW(lpqsRegInfo, essOperation, dwControlFlags, (APIHook<INT> &)hook));

} // DTHandler::_WSASetServiceW()


bool
DTHandler::WSARemoveServiceClass(LPGUID lpServiceClassId, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSARemoveServiceClass()


bool
DTHandler::_WSARemoveServiceClass(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);

    return (handler->WSARemoveServiceClass(lpServiceClassId, (APIHook<INT> &)hook));

} // DTHandler::_WSARemoveServiceClass()


bool
DTHandler::WSAGetServiceClassInfoA(LPGUID lpProviderId, LPGUID lpServiceClassId,
                                   LPDWORD lpdwBufferLength, LPWSASERVICECLASSINFOA lpServiceClassInfo,
                                   APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAGetServiceClassInfoA()


bool
DTHandler::_WSAGetServiceClassInfoA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSASERVICECLASSINFOA lpServiceClassInfo = (LPWSASERVICECLASSINFOA)*va_arg(vList, LPWSASERVICECLASSINFOA *);

    return (handler->WSAGetServiceClassInfoA(lpProviderId, lpServiceClassId, lpdwBufferLength,
                                             lpServiceClassInfo, (APIHook<INT> &)hook));

} // DTHandler::_WSAGetServiceClassInfoA()


bool
DTHandler::WSAGetServiceClassInfoW(LPGUID lpProviderId, LPGUID lpServiceClassId,
                                   LPDWORD lpdwBufferLength, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                   APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAGetServiceClassInfoW()


bool
DTHandler::_WSAGetServiceClassInfoW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);

    return (handler->WSAGetServiceClassInfoW(lpProviderId, lpServiceClassId, lpdwBufferLength,
                                             lpServiceClassInfo, (APIHook<INT> &)hook));

} // DTHandler::_WSAGetServiceClassInfoW()


bool
DTHandler::WSAEnumNameSpaceProvidersA(IN OUT LPDWORD lpdwBufferLength,
                                      OUT LPWSANAMESPACE_INFOA lpnspBuffer,
                                      APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAEnumNameSpaceProvidersA()


bool
DTHandler::_WSAEnumNameSpaceProvidersA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSANAMESPACE_INFOA lpnspBuffer = (LPWSANAMESPACE_INFOA)*va_arg(vList, LPWSANAMESPACE_INFOA *);

    return (handler->WSAEnumNameSpaceProvidersA(lpdwBufferLength, lpnspBuffer, (APIHook<INT> &)hook));

} // DTHandler::_WSAEnumNameSpaceProvidersA()


bool
DTHandler::WSAEnumNameSpaceProvidersW(IN OUT LPDWORD lpdwBufferLength,
                                      OUT LPWSANAMESPACE_INFOW lpnspBuffer,
                                      APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSAEnumNameSpaceProvidersW()


bool
DTHandler::_WSAEnumNameSpaceProvidersW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSANAMESPACE_INFOW lpnspBuffer = (LPWSANAMESPACE_INFOW)*va_arg(vList, LPWSANAMESPACE_INFOW *);

    return (handler->WSAEnumNameSpaceProvidersW(lpdwBufferLength, lpnspBuffer, (APIHook<INT> &)hook));

} // DTHandler::_WSAEnumNameSpaceProvidersW()


bool
DTHandler::WSAGetServiceClassNameByClassIdA(LPGUID lpServiceClassId, LPSTR lpszServiceClassName,
                                            LPDWORD lpdwBufferLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAGetServiceClassNameByClassIdA()


bool
DTHandler::_WSAGetServiceClassNameByClassIdA(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
    LPSTR lpszServiceClassName = (LPSTR)*va_arg(vList, LPSTR *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAGetServiceClassNameByClassIdA(lpServiceClassId, lpszServiceClassName,
                                                      lpdwBufferLength, (APIHook<int> &)hook));

} // DTHandler::_WSAGetServiceClassNameByClassIdA()


bool
DTHandler::WSAGetServiceClassNameByClassIdW(LPGUID lpServiceClassId, LPWSTR lpszServiceClassName,
                                            LPDWORD lpdwBufferLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAGetServiceClassNameByClassIdW()


bool
DTHandler::_WSAGetServiceClassNameByClassIdW(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSTR lpszServiceClassName = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->WSAGetServiceClassNameByClassIdW(lpServiceClassId, lpszServiceClassName,
                                                      lpdwBufferLength, (APIHook<int> &)hook));

} // DTHandler::_WSAGetServiceClassNameByClassIdW()


bool
DTHandler::NSPAddressToString(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPWSTR lpszAddressString,
                              LPDWORD lpdwAddressStringLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPAddressToString()


bool
DTHandler::_NSPAddressToString(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPWSTR lpszAddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->NSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo,
                                        lpszAddressString, lpdwAddressStringLength, (APIHook<int> &)hook));

} // DTHandler::_NSPAddressToString()


bool
DTHandler::NSPStringToAddress(LPWSTR AddressString, INT AddressFamily,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                              LPINT lpAddressLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPStringToAddress()


bool
DTHandler::_NSPStringToAddress(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSTR AddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
    INT AddressFamily = (INT)*va_arg(vList, INT *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);

    return (handler->NSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo,
                                        lpAddress, lpAddressLength, (APIHook<int> &)hook));

} // DTHandler::_NSPStringToAddress()


bool
DTHandler::NSPLookupServiceBegin(LPGUID lpProviderId, LPWSAQUERYSETW lpqsRestrictions,
                                 LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                 DWORD dwControlFlags, LPHANDLE lphLookup,
                                 APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPLookupServiceBegin()


bool
DTHandler::_NSPLookupServiceBegin(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSAQUERYSETW lpqsRestrictions = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
    LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
    LPHANDLE lphLookup = (LPHANDLE)*va_arg(vList, LPHANDLE *);

    return (handler->NSPLookupServiceBegin(lpProviderId, lpqsRestrictions, lpServiceClassInfo,
                                           dwControlFlags, lphLookup, (APIHook<int> &)hook));

} // DTHandler::_NSPLookupServiceBegin()


bool
DTHandler::NSPLookupServiceNext(HANDLE hLookup, DWORD dwControlFlags, LPDWORD lpdwBufferLength,
                                LPWSAQUERYSET lpqsResults, APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPLookupServiceNext()


bool
DTHandler::_NSPLookupServiceNext(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAQUERYSET lpqsResults = (LPWSAQUERYSET)*va_arg(vList, LPWSAQUERYSET *);

    return (handler->NSPLookupServiceNext(hLookup, dwControlFlags, lpdwBufferLength,
                                          lpqsResults, (APIHook<int> &)hook));

} // DTHandler::_NSPLookupServiceNext()


bool
DTHandler::NSPLookupServiceEnd(HANDLE hLookup, APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPLookupServiceEnd()


bool
DTHandler::_NSPLookupServiceEnd(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);

    return (handler->NSPLookupServiceEnd(hLookup, (APIHook<int> &)hook));

} // DTHandler::_NSPLookupServiceEnd()


bool
DTHandler::NSPGetAddressByName(LPWSTR lpszServiceInstanceName, LPGUID lpServiceClassId,
                               DWORD dwNameSpace, LPDWORD lpdwBufferLength,
                               LPWSAQUERYSETW lpqsResults, DWORD dwResolution,
                               LPWSTR lpszAliasBuffer, LPDWORD lpdwAliasBufferLength,
                               APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPGetAddressByName()


bool
DTHandler::_NSPGetAddressByName(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSTR lpszServiceInstanceName = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
    DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSAQUERYSETW lpqsResults = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
    DWORD dwResolution = (DWORD)*va_arg(vList, DWORD *);
    LPWSTR lpszAliasBuffer = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPDWORD lpdwAliasBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->NSPGetAddressByName(lpszServiceInstanceName, lpServiceClassId, dwNameSpace,
                                         lpdwBufferLength, lpqsResults, dwResolution,
                                         lpszAliasBuffer, lpdwAliasBufferLength, (APIHook<int> &)hook));

} // DTHandler::_NSPGetAddressByName()


bool
DTHandler::NSPInstallServiceClass(LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                  APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPInstallServiceClass()


bool
DTHandler::_NSPInstallServiceClass(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);

    return (handler->NSPInstallServiceClass(lpProviderId, lpServiceClassInfo, (APIHook<int> &)hook));

} // DTHandler::_NSPInstallServiceClass()


bool
DTHandler::NSPSetService(LPGUID lpProviderId, LPWSASERVICECLASSINFOW lpServiceClassInfo,
                         LPWSAQUERYSETW lpqsRegInfo, WSAESETSERVICEOP essOperation,
                         DWORD dwControlFlags, APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPSetService()


bool
DTHandler::_NSPSetService(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);
    LPWSAQUERYSETW lpqsRegInfo = (LPWSAQUERYSETW)*va_arg(vList, LPWSAQUERYSETW *);
    WSAESETSERVICEOP essOperation = (WSAESETSERVICEOP)*va_arg(vList, WSAESETSERVICEOP *);
    DWORD dwControlFlags = (DWORD)*va_arg(vList, DWORD *);

    return (handler->NSPSetService(lpProviderId, lpServiceClassInfo, lpqsRegInfo, essOperation,
                                   dwControlFlags, (APIHook<int> &)hook));

} // DTHandler::_NSPSetService()


bool
DTHandler::NSPRemoveServiceClass(IN LPGUID lpProviderId, IN LPGUID lpServiceClassId,
                                 APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPRemoveServiceClass()


bool
DTHandler::_NSPRemoveServiceClass(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);

    return (handler->NSPRemoveServiceClass(lpProviderId, lpServiceClassId, (APIHook<int> &)hook));

} // DTHandler::_NSPRemoveServiceClass()


bool
DTHandler::NSPGetServiceClassInfo(IN LPGUID lpProviderId, IN OUT LPDWORD lpdwBufSize,
                                  IN OUT LPWSASERVICECLASSINFOW lpServiceClassInfo,
                                  APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPGetServiceClassInfo()


bool
DTHandler::_NSPGetServiceClassInfo(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPDWORD lpdwBufSize = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSASERVICECLASSINFOW lpServiceClassInfo = (LPWSASERVICECLASSINFOW)*va_arg(vList, LPWSASERVICECLASSINFOW *);

    return (handler->NSPGetServiceClassInfo(lpProviderId, lpdwBufSize, lpServiceClassInfo, (APIHook<int> &)hook));

} // DTHandler::_NSPGetServiceClassInfo()


bool
DTHandler::NSPGetServiceClassNameByClassId(LPGUID lpServiceClassId, LPWSTR lpszServiceClassName,
                                           LPDWORD lpdwBufferLength, APIHook<int> &hook) {

    return (false);

} // DTHandler::NSPGetServiceClassNameByClassId()


bool
DTHandler::_NSPGetServiceClassNameByClassId(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpServiceClassId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSTR lpszServiceClassName = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);

    return (handler->NSPGetServiceClassNameByClassId(lpServiceClassId, lpszServiceClassName,
                                                     lpdwBufferLength, (APIHook<int> &)hook));

} // DTHandler::_NSPGetServiceClassNameByClassId()


bool
DTHandler::WSCGetProviderPath(LPGUID lpProviderId, LPWSTR lpszProviderDllPath,
                              LPINT lpProviderDllPathLen, LPINT lpErrno,
                              APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCGetProviderPath()


bool
DTHandler::_WSCGetProviderPath(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSTR lpszProviderDllPath = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPINT lpProviderDllPathLen = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCGetProviderPath(lpProviderId, lpszProviderDllPath, lpProviderDllPathLen,
                                        lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCGetProviderPath()


bool
DTHandler::WSCInstallNameSpace(LPWSTR lpszIdentifier, LPWSTR lpszPathName,
                               DWORD dwNameSpace, DWORD dwVersion,
                               LPGUID lpProviderId, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCInstallNameSpace()


bool
DTHandler::_WSCInstallNameSpace(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSTR lpszIdentifier = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPWSTR lpszPathName = (LPWSTR)*va_arg(vList, LPWSTR *);
    DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
    DWORD dwVersion = (DWORD)*va_arg(vList, DWORD *);
    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);

    return (handler->WSCInstallNameSpace(lpszIdentifier, lpszPathName, dwNameSpace,
                                         dwVersion, lpProviderId, (APIHook<int> &)hook));

} // DTHandler::_WSCInstallNameSpace()


bool
DTHandler::WSCUnInstallNameSpace(LPGUID lpProviderId, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCUnInstallNameSpace()


bool
DTHandler::_WSCUnInstallNameSpace(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);

    return (handler->WSCUnInstallNameSpace(lpProviderId, (APIHook<int> &)hook));

} // DTHandler::_WSCUnInstallNameSpace()


bool
DTHandler::WSCEnableNSProvider(LPGUID lpProviderId, BOOL fEnable, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCEnableNSProvider()


bool
DTHandler::_WSCEnableNSProvider(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    BOOL fEnable = (BOOL)*va_arg(vList, BOOL *);

    return (handler->WSCEnableNSProvider(lpProviderId, fEnable, (APIHook<int> &)hook));

} // DTHandler::_WSCEnableNSProvider()

bool
DTHandler::WSPAddressToString(LPSOCKADDR lpsaAddress, DWORD dwAddressLength,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo,
                              LPWSTR lpszAddressString, LPDWORD lpdwAddressStringLength,
                              LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPAddressToString()


bool
DTHandler::_WSPAddressToString(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPSOCKADDR lpsaAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    DWORD dwAddressLength = (DWORD)*va_arg(vList, DWORD *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPWSTR lpszAddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPDWORD lpdwAddressStringLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPAddressToString(lpsaAddress, dwAddressLength, lpProtocolInfo, lpszAddressString,
                                        lpdwAddressStringLength, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPAddressToString()


bool
DTHandler::WSPStringToAddress(LPWSTR AddressString, INT AddressFamily,
                              LPWSAPROTOCOL_INFOW lpProtocolInfo, LPSOCKADDR lpAddress,
                              LPINT lpAddressLength, LPINT lpErrno,
                              APIHook<int> &hook) {

    return (false);

} // DTHandler::WSPStringToAddress()


bool
DTHandler::_WSPStringToAddress(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSTR AddressString = (LPWSTR)*va_arg(vList, LPWSTR *);
    INT AddressFamily = (INT)*va_arg(vList, INT *);
    LPWSAPROTOCOL_INFOW lpProtocolInfo = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPSOCKADDR lpAddress = (LPSOCKADDR)*va_arg(vList, LPSOCKADDR *);
    LPINT lpAddressLength = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSPStringToAddress(AddressString, AddressFamily, lpProtocolInfo, lpAddress,
                                        lpAddressLength, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSPStringToAddress()


#if (WINVER >= 0x0501)

bool
DTHandler::WSANSPIoctl(IN HANDLE hLookup, IN DWORD dwControlCode, IN LPVOID lpvInBuffer, IN DWORD cbInBuffer, OUT LPVOID lpvOutBuffer, IN DWORD cbOutBuffer, OUT LPDWORD lpcbBytesReturned, IN LPWSACOMPLETION lpCompletion, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSANSPIoctl()


bool
DTHandler::_WSANSPIoctl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
    DWORD dwControlCode = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvInBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbInBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvOutBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbOutBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpcbBytesReturned = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSACOMPLETION lpCompletion = (LPWSACOMPLETION)*va_arg(vList, LPWSACOMPLETION *);

    return (handler->WSANSPIoctl(hLookup, dwControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer, cbOutBuffer, lpcbBytesReturned, lpCompletion, (APIHook<INT> &)hook));

} // DTHandler::_WSANSPIoctl()


bool
DTHandler::NSPIoctl(HANDLE hLookup, DWORD dwControlCode, LPVOID lpvInBuffer, DWORD cbInBuffer, LPVOID lpvOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbBytesReturned, LPWSACOMPLETION lpCompletion, LPWSATHREADID lpThreadId, APIHook<INT> &hook) {

    return (false);

} // DTHandler::NSPIoctl()


bool
DTHandler::_NSPIoctl(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    HANDLE hLookup = (HANDLE)*va_arg(vList, HANDLE *);
    DWORD dwControlCode = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvInBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbInBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPVOID lpvOutBuffer = (LPVOID)*va_arg(vList, LPVOID *);
    DWORD cbOutBuffer = (DWORD)*va_arg(vList, DWORD *);
    LPDWORD lpcbBytesReturned = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSACOMPLETION lpCompletion = (LPWSACOMPLETION)*va_arg(vList, LPWSACOMPLETION *);
    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);

    return (handler->NSPIoctl(hLookup, dwControlCode, lpvInBuffer, cbInBuffer, lpvOutBuffer, cbOutBuffer, lpcbBytesReturned, lpCompletion, lpThreadId, (APIHook<INT> &)hook));

} // DTHandler::_NSPIoctl()


bool
DTHandler::WPUCompleteOverlappedRequest(SOCKET s, LPWSAOVERLAPPED lpOverlapped, DWORD dwError, DWORD cbTransferred, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUCompleteOverlappedRequest()


bool
DTHandler::_WPUCompleteOverlappedRequest(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    SOCKET s = (SOCKET)*va_arg(vList, SOCKET *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    DWORD dwError = (DWORD)*va_arg(vList, DWORD *);
    DWORD cbTransferred = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUCompleteOverlappedRequest(s, lpOverlapped, dwError, cbTransferred, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUCompleteOverlappedRequest()


bool
DTHandler::WSAProviderConfigChange(IN OUT LPHANDLE lpNotificationHandle, IN LPWSAOVERLAPPED lpOverlapped, IN LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSAProviderConfigChange()


bool
DTHandler::_WSAProviderConfigChange(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPHANDLE lpNotifcationHandle = (LPHANDLE)*va_arg(vList, LPHANDLE *);
    LPWSAOVERLAPPED lpOverlapped = (LPWSAOVERLAPPED)*va_arg(vList, LPWSAOVERLAPPED *);
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine = (LPWSAOVERLAPPED_COMPLETION_ROUTINE)*va_arg(vList, LPWSAOVERLAPPED_COMPLETION_ROUTINE *);

    return (handler->WSAProviderConfigChange(lpNotifcationHandle, lpOverlapped, lpCompletionRoutine, (APIHook<int> &)hook));

} // DTHandler::_WSAProviderConfigChange()


bool
DTHandler::WSCWriteProviderOrder(IN LPDWORD lpwdCatalogEntryId, IN DWORD dwNumberOfEntries, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCWriteProviderOrder()


bool
DTHandler::_WSCWriteProviderOrder(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPDWORD lpwdCatalogEntryId = (LPDWORD)*va_arg(vList, LPDWORD *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);

    return (handler->WSCWriteProviderOrder(lpwdCatalogEntryId, dwNumberOfEntries, (APIHook<int> &)hook));

} // DTHandler::_WSCWriteProviderOrder()


bool
DTHandler::WSCWriteNameSpaceOrder(IN LPGUID lpProviderId, IN DWORD dwNumberOfEntries, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCWriteNameSpaceOrder()


bool
DTHandler::_WSCWriteNameSpaceOrder(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);

    return (handler->WSCWriteNameSpaceOrder(lpProviderId, dwNumberOfEntries, (APIHook<int> &)hook));

} // DTHandler::_WSCWriteNameSpaceOrder()


bool
DTHandler::WSCUpdateProvider(IN LPGUID lpProviderId, IN const WCHAR FAR *lpszProviderDllPath, IN const LPWSAPROTOCOL_INFOW lpProtocolInfoList, IN DWORD dwNumberOfEntries, OUT LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCUpdateProvider()


bool
DTHandler::_WSCUpdateProvider(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    const WCHAR FAR *lpszProviderDllPath = (const WCHAR FAR *)*va_arg(vList, const WCHAR FAR **);
    const LPWSAPROTOCOL_INFOW lpProtocolInfoList = (const LPWSAPROTOCOL_INFOW)*va_arg(vList, const LPWSAPROTOCOL_INFOW *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCUpdateProvider(lpProviderId, lpszProviderDllPath, lpProtocolInfoList, dwNumberOfEntries, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCUpdateProvider()


bool
DTHandler::getaddrinfo(IN const char FAR *NodeName, IN const char FAR *ServiceName, IN const struct addrinfo FAR *Hints, OUT struct addrinfo FAR * FAR *Result, APIHook<INT> &hook) {

    return (false);

} // DTHandler::getaddrinfo()


bool
DTHandler::_getaddrinfo(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const char FAR *NodeName = (const char FAR *)*va_arg(vList, const char FAR **);
    const char FAR *ServiceName = (const char FAR *)*va_arg(vList, const char FAR **);
    const struct addrinfo FAR *Hints = (const struct addrinfo FAR *)*va_arg(vList, const struct addrinfo FAR **);
    struct addrinfo FAR * FAR *Result = (struct addrinfo FAR * FAR *)*va_arg(vList, struct addrinfo FAR * FAR **);

    return (handler->getaddrinfo(NodeName, ServiceName, Hints, Result, (APIHook<INT> &)hook));

} // DTHandler::_getaddrinfo()


bool
DTHandler::getnameinfo(IN const struct sockaddr *SocketAddress, IN socklen_t SocketAddressLength, OUT PCHAR NodeName, IN DWORD NodeBufferSize, OUT PCHAR ServiceName, IN DWORD ServiceBufferSize, IN INT Flags, APIHook<INT> &hook) {

    return (false);

} // DTHandler::getnameinfo()


bool
DTHandler::_getnameinfo(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const struct sockaddr *SocketAddress = (const struct sockaddr *)*va_arg(vList, const struct sockaddr **);
    socklen_t SocketAddressLength = (socklen_t)*va_arg(vList, socklen_t *);
    PCHAR NodeName = (PCHAR)*va_arg(vList, PCHAR *);
    DWORD NodeBufferSize = (DWORD)*va_arg(vList, DWORD *);
    PCHAR ServiceName = (PCHAR)*va_arg(vList, PCHAR *);
    DWORD ServiceBufferSize = (DWORD)*va_arg(vList, DWORD *);
    INT Flags = (INT)*va_arg(vList, INT *);

    return (handler->getnameinfo(SocketAddress, SocketAddressLength, NodeName, NodeBufferSize, ServiceName, ServiceBufferSize, Flags, (APIHook<INT> &)hook));

} // DTHandler::_getnameinfo()


bool
DTHandler::freeaddrinfo(IN OUT struct addrinfo *Free, APIHook<void> &hook) {

    return (false);

} // DTHandler::freeaddrinfo()


bool
DTHandler::_freeaddrinfo(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    struct addrinfo *Free = (struct addrinfo *)*va_arg(vList, struct addrinfo **);

    return (handler->freeaddrinfo(Free, (APIHook<void> &)hook));

} // DTHandler::_freeaddrinfo()


bool
DTHandler::NSPStartup(LPGUID lpProviderId, LPNSP_ROUTINE lpnspRoutines, APIHook<INT> &hook) {

    return (false);

} // DTHandler::NSPStartup()


bool
DTHandler::_NSPStartup(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPNSP_ROUTINE lpnspRoutines = (LPNSP_ROUTINE)*va_arg(vList, LPNSP_ROUTINE *);

    return (handler->NSPStartup(lpProviderId, lpnspRoutines, (APIHook<INT> &)hook));

} // DTHandler::_NSPStartup()


bool
DTHandler::WPUOpenCurrentThread(OUT LPWSATHREADID lpThreadId, OUT LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUOpenCurrentThread()


bool
DTHandler::_WPUOpenCurrentThread(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUOpenCurrentThread(lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUOpenCurrentThread()


bool
DTHandler::WPUCloseThread(IN LPWSATHREADID lpThreadId, OUT LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WPUCloseThread()


bool
DTHandler::_WPUCloseThread(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSATHREADID lpThreadId = (LPWSATHREADID)*va_arg(vList, LPWSATHREADID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WPUCloseThread(lpThreadId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WPUCloseThread()


#if defined(_WIN64)

bool
DTHandler::WSCEnumProtocols32(IN LPINT lpiProtocols, OUT LPWSAPROTOCOL_INFOW lpProtocolBuffer, IN OUT LPDWORD lpdwBufferLength, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCEnumProtocols32()


bool
DTHandler::_WSCEnumProtocols32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPINT lpiProtocols = (LPINT)*va_arg(vList, LPINT *);
    LPWSAPROTOCOL_INFOW lpProtocolBuffer = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCEnumProtocols32(lpiProtocols, lpProtocolBuffer, lpdwBufferLength, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCEnumProtocols32()


bool
DTHandler::WSCInstallProvider64_32(const LPGUID lpProviderId, const LPWSTR lpszProviderDllPath, const LPWSAPROTOCOL_INFOW lpProtocolInfoList, DWORD dwNumberOfEntries, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCInstallProvider64_32()


bool
DTHandler::_WSCInstallProvider64_32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    const LPGUID lpProviderId = (const LPGUID)*va_arg(vList, const LPGUID *);
    const LPWSTR lpszProviderDllPath = (const LPWSTR)*va_arg(vList, const LPWSTR *);
    const LPWSAPROTOCOL_INFOW lpProtocolInfoList = (LPWSAPROTOCOL_INFOW)*va_arg(vList, LPWSAPROTOCOL_INFOW *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCInstallProvider64_32(lpProviderId, lpszProviderDllPath, lpProtocolInfoList, dwNumberOfEntries, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCInstallProvider64_32()


bool
DTHandler::WSCDeinstallProvider32(LPGUID lpProviderId, LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCDeinstallProvider32()


bool
DTHandler::_WSCDeinstallProvider32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCDeinstallProvider32(lpProviderId, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCDeinstallProvider32()


bool
DTHandler::WSCGetProviderPath32(IN LPGUID lpProviderId, OUT WCHAR FAR *lpszProviderDllPath, IN OUT LPINT ProviderDLLPathLen, OUT LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCGetProviderPath32()


bool
DTHandler::_WSCGetProviderPath32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    LPWSTR lpszProviderDllPath = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPINT lpProviderDllPathLen = (LPINT)*va_arg(vList, LPINT *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCGetProviderPath32(lpProviderId, lpszProviderDllPath, lpProviderDllPathLen, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCGetProviderPath32()


bool
DTHandler::WSCUpdateProvider32(IN LPGUID lpProviderId, IN const WCHAR FAR *lpszProviderDllPath, IN const LPWSAPROTOCOL_INFOW lpProtocolInfoList, IN DWORD dwNumberOfEntries, OUT LPINT lpErrno, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCUpdateProvider32()


bool
DTHandler::_WSCUpdateProvider32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    const WCHAR FAR *lpszProviderDllPath = (const WCHAR FAR *)*va_arg(vList, const WCHAR FAR **);
    const LPWSAPROTOCOL_INFOW lpProtocolInfoList = (const LPWSAPROTOCOL_INFOW)*va_arg(vList, const LPWSAPROTOCOL_INFOW *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);
    LPINT lpErrno = (LPINT)*va_arg(vList, LPINT *);

    return (handler->WSCUpdateProvider32(lpProviderId, lpszProviderDllPath, lpProtocolInfoList, dwNumberOfEntries, lpErrno, (APIHook<int> &)hook));

} // DTHandler::_WSCUpdateProvider32()


bool
DTHandler::WSCWriteProviderOrder32(IN LPDWORD lpwdCatalogEntryId, IN DWORD dwNumberOfEntries, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCWriteProviderOrder32()


bool
DTHandler::_WSCWriteProviderOrder32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPDWORD lpwdCatalogEntryId = (LPDWORD)*va_arg(vList, LPDWORD *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);

    return (handler->WSCWriteProviderOrder32(lpwdCatalogEntryId, dwNumberOfEntries, (APIHook<int> &)hook));

} // DTHandler::_WSCWriteProviderOrder32()


bool
DTHandler::WSCEnumNameSpaceProviders32(IN OUT LPDWORD lpdwBufferLength, IN OUT LPWSANAMESPACE_INFOW lpnspBuffer, APIHook<INT> &hook) {

    return (false);

} // DTHandler::WSCEnumNameSpaceProviders32()


bool
DTHandler::_WSCEnumNameSpaceProviders32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPDWORD lpdwBufferLength = (LPDWORD)*va_arg(vList, LPDWORD *);
    LPWSANAMESPACE_INFOW lpnspBuffer = (LPWSANAMESPACE_INFOW)*va_arg(vList, LPWSANAMESPACE_INFOW *);

    return (handler->WSCEnumNameSpaceProviders32(lpdwBufferLength, lpnspBuffer, (APIHook<INT> &)hook));

} // DTHandler::_WSCEnumNameSpaceProviders32()


bool
DTHandler::WSCInstallNameSpace32(LPWSTR lpszIdentifier, LPWSTR lpszPathName, DWORD dwNameSpace, DWORD dwVersion, LPGUID lpProviderId, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCInstallNameSpace32()


bool
DTHandler::_WSCInstallNameSpace32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPWSTR lpszIdentifier = (LPWSTR)*va_arg(vList, LPWSTR *);
    LPWSTR lpszPathName = (LPWSTR)*va_arg(vList, LPWSTR *);
    DWORD dwNameSpace = (DWORD)*va_arg(vList, DWORD *);
    DWORD dwVersion = (DWORD)*va_arg(vList, DWORD *);
    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);

    return (handler->WSCInstallNameSpace32(lpszIdentifier, lpszPathName, dwNameSpace, dwVersion, lpProviderId, (APIHook<int> &)hook));

} // DTHandler::_WSCInstallNameSpace32()


bool
DTHandler::WSCUnInstallNameSpace32(LPGUID lpProviderId, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCUnInstallNameSpace32()


bool
DTHandler::_WSCUnInstallNameSpace32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);

    return (handler->WSCUnInstallNameSpace32(lpProviderId, (APIHook<int> &)hook));

} // DTHandler::_WSCUnInstallNameSpace32()


bool
DTHandler::WSCEnableNSProvider32(LPGUID lpProviderId, BOOL fEnable, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCEnableNSProvider32()


bool
DTHandler::_WSCEnableNSProvider32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    BOOL fEnable = (BOOL)*va_arg(vList, BOOL *);

    return (handler->WSCEnableNSProvider32(lpProviderId, fEnable, (APIHook<int> &)hook));

} // DTHandler::_WSCEnableNSProvider32()


bool
DTHandler::WSCWriteNameSpaceOrder32(IN LPGUID lpProviderId, IN DWORD dwNumberOfEntries, APIHook<int> &hook) {

    return (false);

} // DTHandler::WSCWriteNameSpaceOrder32()


bool
DTHandler::_WSCWriteNameSpaceOrder32(DTHandler *handler, APIHook<void> &hook, va_list vList) {

    LPGUID lpProviderId = (LPGUID)*va_arg(vList, LPGUID *);
    DWORD dwNumberOfEntries = (DWORD)*va_arg(vList, DWORD *);

    return (handler->WSCWriteNameSpaceOrder32(lpProviderId, dwNumberOfEntries, (APIHook<int> &)hook));

} // DTHandler::_WSCWriteNameSpaceOrder32()


#endif // defined(_WIN64)
#endif // (WINVER >= 0x0501)
