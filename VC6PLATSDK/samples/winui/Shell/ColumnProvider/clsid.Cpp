//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  Clsid.cpp
//
//      Functions to retrieve the CLSID of the object.
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"
#include "Resource.h"

extern HINSTANCE hDllInstance;

BOOL WINAPI GetObjectClsid (LPTSTR lpszClsid, DWORD cbClsid)
{
    if (!LoadString (hDllInstance, IDS_CLSID, lpszClsid, cbClsid))
        return FALSE;
    return TRUE;
}


BOOL WINAPI GetObjectClsid (LPCLSID pClsid)
{
    if (pClsid == NULL)
        return FALSE;

    TCHAR szClsid[40];
    WCHAR wszClsid[40];

    if (!GetObjectClsid (szClsid, 40))
        return FALSE;

#ifndef UNICODE
    MultiByteToWideChar (CP_ACP, 0, szClsid, -1, wszClsid, 40);
#else
    lstrcpyn (wszClsid, szClsid, ARRAYSIZE(wszClsid));
#endif

    if (FAILED(CLSIDFromString (wszClsid, pClsid)))
        return FALSE;
    return TRUE;
}


