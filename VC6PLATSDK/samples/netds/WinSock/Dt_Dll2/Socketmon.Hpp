// Filename  : SocketMon.hpp
// Abstract  : This object is inherited from DTHandler and implements
//             our custom DT Winsock API hooking.
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998 - 2001,  Microsoft Corporation.
//             All rights reserved.

#ifndef SOCKET_MONITOR_HPP
#define SOCKET_MONITOR_HPP

#pragma warning(disable: 4512)

#include "DTHandler.hpp"

class SocketMonitor : public DTHandler {

protected :

  bool WSAStartup (WORD wVersionRequested, LPWSADATA lpWSAData, APIHook<int> &hook);
  bool WSACleanup (APIHook<int> &hook);
  bool send       (SOCKET s, const char FAR *buf, int len, int flags, APIHook<int> &hook);
  bool recv       (SOCKET s, char FAR *buf, int len, int flags, APIHook<int> &hook);

}; // class SocketMonitor

#endif
