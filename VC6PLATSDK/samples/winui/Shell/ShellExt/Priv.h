//--------------------------------------------------------------
// common user interface routines
//
// Copyright 1993 - 2000 Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------


#ifndef STRICT
#define STRICT
#endif

#define INC_OLE2        // WIN32, get ole2 from windows.h

#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>

#define ResultFromShort(i)  ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(i)))
