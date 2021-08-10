//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  UnregisterServer.cpp
//
//      Unregisters the Column Provider
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"
#include "Resource.h"

extern HINSTANCE hDllInstance;

STDAPI DllUnregisterServer (VOID)
{
    HRESULT     hResult     = S_OK;
    LRESULT     lResult     = NOERROR;
    HKEY        hKey        = NULL;
    TCHAR       szClsid[MAX_PATH] = TEXT("");
    TCHAR       szSubKey[MAX_PATH] = TEXT("");

    //
    //  Load some necessary string values
    //
    LoadString (hDllInstance, IDS_CLSID, szClsid, MAX_PATH);

    //
    //  Delete the key HKCR\CLSID\{CLSID}\InprocServer32
    //
    wsprintf (szSubKey, TEXT("CLSID\\%s\\InprocServer32"), szClsid);
    lResult = RegDeleteKey (HKEY_CLASSES_ROOT, szSubKey);
    if (lResult != NOERROR)
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Delete the key HKCR\CLSID\{CLSID}
    //
    wsprintf (szSubKey, TEXT("CLSID\\%s"), szClsid);
    lResult = RegDeleteKey (HKEY_CLASSES_ROOT, szSubKey);
    if (lResult != NOERROR)
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Delete the key HKCR\Folder\shellex\ColumnHandlers\{CLSID}
    //
    LoadString (hDllInstance, IDS_REGKEY_COLUMNPROVIDER, szSubKey, MAX_PATH);
    StrCatBuff (szSubKey, TEXT("\\"), ARRAYSIZE(szSubKey));
    StrCatBuff (szSubKey, szClsid, ARRAYSIZE(szSubKey));
    lResult = RegDeleteKey (HKEY_CLASSES_ROOT, szSubKey);
    if (lResult != NOERROR)
    {
        hResult = SELFREG_E_CLASS;
    }

    return hResult;
}

