// Filename  : SocketMon.cpp
// Abstract  : This object is inherited from DTHandler and implements
//             our custom DT Winsock API hooking.
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998 - 2002, Microsoft Corporation.
//             All rights reserved.

#include <stdio.h>
#include "SocketMon.hpp"


bool
SocketMonitor::WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData, APIHook<int> &hook) {

    char buffer[1024];

    if (hook.preAPI()) {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "\nWinsock API\t\t: WSAStartup()\n"
                  "     Calling library\t\t: %s\n"
                  "     Pre-API notify\t\t: Yes\n"
                  "Parameter values\t\t:\n"
                  "     wVersionRequested\t: %u\n",
                  hook.libName(),
                  wVersionRequested);

    } else {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "\nWinsock API\t\t\t: WSAStartup()\n"
                  "     Calling library\t\t\t: %s\n"
                  "     Pre-API notify\t\t\t: No\n"
                  "Reference parameter values\t\t:\n"
                  "     lpWSAData->wVersion\t\t: %d\n"
                  "     lpWSAData->wHighVersion\t: %d\n"
                  "     lpWSAData->iMaxSockets\t\t: %d\n"
                  "     lpWSAData->iMaxUdpDg\t\t: %d\n"
                  "     lpWSAData->szDescription\t: %s\n"
                  "     lpWSAData->szSystemStatus\t: %s\n"
                  "     lpWSAData->lpVendorInfo\t\t: %s\n"
                  "API return value\t\t\t: %d\n",
                  hook.libName(),
                  lpWSAData->wVersion,
                  lpWSAData->wHighVersion,
                  lpWSAData->iMaxSockets,
                  lpWSAData->iMaxUdpDg,
                  lpWSAData->szDescription,
                  lpWSAData->szSystemStatus,
                  lpWSAData->lpVendorInfo,
                  *hook.rValue());

    }

    buffer[sizeof(buffer) - 1] = '\0';
    MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);
    
    return (false); // don't veto API call

} // SocketMonitor::WSAStartup()


bool
SocketMonitor::WSACleanup(APIHook<int> &hook) {

    char buffer[1024];

    if (hook.preAPI()) {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "\nWinsock API\t\t: WSACleanup()\n"
                  "     Calling library\t\t: %s\n"
                  "     Pre-API notify\t\t: Yes\n",
                  hook.libName());

    } else {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "\nWinsock API\t\t: WSACleanup()\n"
                  "     Calling library\t\t: %s\n"
                  "     Pre-API notify\t\t: No\n"
                  "     API return value\t\t: %d\n",
                  hook.libName(),
                  *hook.rValue());

    }

    buffer[sizeof(buffer) - 1] = '\0';
    MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);

    return (false); // don't veto API call

} // SocketMonitor::WSACleanup()


bool
SocketMonitor::send(SOCKET s, const char FAR *buf, int len, int flags, APIHook<int> &hook) {

    char buffer[1024];

    if (hook.preAPI()) {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                "Winsock API\t\t: send()\n"
                "     Calling library\t\t: %s\n"
                "     Pre-API notify\t\t: Yes\n"
                "Parameter values\t\t:\n"
                "     s\t\t\t: %d\n"
                "     buf\t\t\t: 0x%08x\n"
                "     len\t\t\t: %d\n"
                "     flags\t\t\t: %d\n",
                hook.libName(),
                s,
                *buf,
                len,
                flags);

    } else {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "Winsock API\t\t\t: send()\n"
                  "     Calling library\t\t\t: %s\n"
                  "     Pre-API notify\t\t\t: No\n"
                  "     API return value\t\t\t: %d\n",
                  hook.libName(),
                  *hook.rValue());

    }

    buffer[sizeof(buffer) - 1] = '\0';
    MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);

    return (false); // don't veto API call

} // SocketMonitor::send()


bool
SocketMonitor::recv(SOCKET s, char FAR *buf, int len, int flags, APIHook<int> &hook) {

    char buffer[1024];

    if (hook.preAPI()) {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "[DT Hook]\n"
                  "\tWinsock API\t\t: recv()\n"
                  "     \tCalling library\t\t: %s\n"
                  "     \tPre-API notify\t\t: Yes\n"
                  "\tParameter values\t:\n"
                  "     \ts\t\t\t: %d\n"
                  "     \tbuf\t\t\t: 0x%08x\n"
                  "     \tlen\t\t\t: %d\n"
                  "     \tflags\t\t\t: %d\n",
                  hook.libName(),
                  s,
                  *buf,
                  len,
                  flags);

    } else {

        _snprintf(buffer,
                  sizeof(buffer) - 1,
                  "Winsock API\t\t\t: send()\n"
                  "     Calling library\t\t\t: %s\n"
                  "     Pre-API notify\t\t\t: No\n"
                  "     API return value\t\t\t: %d\n"
                  "Reference parameter values:\t:\n",
                  hook.libName(),
                  *hook.rValue());

    }

    buffer[sizeof(buffer) - 1] = '\0';
    MessageBox(0, buffer, "DT Hook", MB_OK | MB_ICONINFORMATION);

    return (false); // don't veto API call

} // SocketMonitor::recv()
