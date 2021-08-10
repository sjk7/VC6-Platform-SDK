// Filename  : dt_dll.cpp
// Abstract  : The main dt_dll.dll source file.  It creates a
//             SocketMonitor object which is inherited from DTHandler
//             to provide custom DT Winsock API hooking.  It exports
//             the requires API calls per the DT specification.
//             (Please review the dt_dll sample on the Platform SDK.)
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998 - 2001,  Microsoft Corporation.
//             All rights reserved.

#include "SocketMon.hpp"


SocketMonitor gSocketMonitor;


BOOL WINAPI
DllMain(HINSTANCE, DWORD reason, LPVOID) {

    switch (reason) {

        case DLL_PROCESS_ATTACH :
            break;

        case DLL_THREAD_ATTACH :
            break;

        case DLL_PROCESS_DETACH :
            break;

        case DLL_THREAD_DETACH :
            break;

        default :
            return (FALSE);

    } // switch (reason)

    return (TRUE);

} // DllMain


// Function     : WSAPreApiNotify
// Description  : Builds a string for output and passes it, along with
//                information about the call, to a handler function.
// Arguments    : 'NotificationCode'
//                  Specifies which API function called us.
//                'ReturnCode'
//                  A generic pointer to the return value of the API function.
//                  Can be used to change the return value in the case of a
//                  short-circuit (see how the return value from PreApiNotify
//                  works for more information on short-circuiting the API
//                  function).
//                'LibraryName'
//                  A string pointing to the name of the library that called us.
//                '...'
//                  Variable number argument list.  These are pointers to the
//                  actual parameters of the API functions.
// Return Value : Returns TRUE if we want to short-circuit the API function;
//                in other words, returning non-zero here forces the API
//                function to return immediately before any other actions take
//                place.  Returns FALSE if we want to proceed with the API
//                function.

BOOL WINAPIV
WSAPreApiNotify(IN INT NotificationCode, OUT LPVOID ReturnCode, IN LPSTR LibraryName, ...) {

    va_list vl;

    // Protect against system calls within the hook; save the previous error.
    const int lastError = GetLastError();

    va_start(vl, LibraryName);
    BOOL rVal = gSocketMonitor.dispatch(NotificationCode, ReturnCode, LibraryName, true, vl);
    va_end(vl);

    // Restore the previous error.
    SetLastError(lastError);

    return (rVal);

} // WSAPreApiNotify


// Function     : WSAPostApiNotify
// Description  : Like PreApiNotify, builds a string and passes it, along with
//                information about the call, to a handler function.
// Arguments    : 'NotificationCode'
//                  Specifies which API function called us.
//                'ReturnCode'
//                  A generic pointer to the return value of the API function.
//                'LibraryName'
//                  A string pointing to the name of the library that called us.
//                '...'
//                  Variable number argument list.  These are pointers to the
//                  actual parameters of the API functions.
// Return Value : Return value is currently meaningless.

BOOL WINAPIV
WSAPostApiNotify(IN INT NotificationCode, OUT LPVOID ReturnCode, IN LPSTR LibraryName, ...) {

  va_list vl;

  // Protect against system calls within the hook; save the previous error.
  const int lastError = GetLastError();

  va_start(vl, LibraryName);
  BOOL rVal = gSocketMonitor.dispatch(NotificationCode, ReturnCode, LibraryName, false, vl);
  va_end(vl);

  // Restore the previous error.
  SetLastError(lastError);

  return (rVal);

} // WSAPostApiNotify
