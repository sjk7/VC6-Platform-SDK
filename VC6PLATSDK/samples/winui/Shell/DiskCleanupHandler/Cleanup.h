//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  Cleanup.h
//
//////////////////////////////////////////////////////////////////////

#ifndef _CLEANUP_H_INCLUDED
#define _CLEANUP_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <olectl.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <emptyvc.h>

#define MAX_DISPLAY_LEN     100
#define MAX_DESCRIPTION_LEN 500
#define MAX_BUTTONTEXT_LEN  25

#define MAKEDWORDLONG(high,low) ((DWORDLONG)(((high) << 32) | (low)))
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))

extern HINSTANCE hDllInstance;
extern ULONG nDllRefCount;

//
//  GetStringByteSize
//
//      Returns the number of bytes for a string, including the
//      terminating NULL character
//
inline UINT GetStringByteSize (LPTSTR pszString) {return ((lstrlen(pszString) + 1) * sizeof(TCHAR));}

//
//  GetStringByteSizeUnicode
//
//      Returns the number of bytes required to convert an ANSI 
//      string to UNICODE. Used in the sample when allocating
//      memory for ANSI->UNICODE conversions
//
inline UINT GetStringByteSizeUnicode (LPCSTR pszString) {return ((lstrlen(pszString) + 1) * sizeof(WCHAR));}

#endif // _VCCLEANUP_H_INCLUDED