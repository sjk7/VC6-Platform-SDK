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
//      Unregisters the Disk Cleanup Handler.
//
//////////////////////////////////////////////////////////////////////

#include "Cleanup.h"
#include "Resource.h"

extern HINSTANCE hDllInstance;

STDAPI DllUnregisterServer (VOID)
{
    HRESULT     hResult     = S_OK;
    LRESULT     lResult     = NOERROR;
    HKEY        hKey        = NULL;
    TCHAR       szClsid[MAX_PATH] = TEXT("");
    TCHAR       szSubKey[MAX_PATH] = TEXT("");
    TCHAR       szDisplay[MAX_PATH] = TEXT("");
    TCHAR       szEmptyVCSubKey[MAX_PATH] = TEXT("");

    //
    //  Load some necessary string values
    //
    LoadString (hDllInstance, IDS_CLSID, szClsid, MAX_PATH);
    LoadString (hDllInstance, IDS_DISPLAY, szDisplay, MAX_PATH);
    LoadString (hDllInstance, IDS_EMPTYVC_SUBKEY, szEmptyVCSubKey, MAX_PATH);

    //
    //  Delete the key HKCR\CLSID\{CLSID}\InprocServer32
    //  Delete the key HKCR\CLSID\{CLSID}\DefaultIcon
    //
    wsprintf (szSubKey, TEXT("CLSID\\%s"), szClsid);
    lResult = RegOpenKeyEx (HKEY_CLASSES_ROOT, szSubKey, 0, KEY_ALL_ACCESS, &hKey);
    if (lResult == NOERROR)
    {
        lResult = RegDeleteKey (hKey, TEXT("InprocServer32"));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        lResult = RegDeleteKey (hKey, TEXT("DefaultIcon"));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;
        RegCloseKey (hKey);
    }
    else
        hResult = SELFREG_E_CLASS;

    //
    //  Delete the key HKCR\CLSID\{CLSID}
    //
    lResult = RegOpenKeyEx (HKEY_CLASSES_ROOT, TEXT("CLSID"), 0, KEY_ALL_ACCESS, &hKey);

    if (lResult == NOERROR) 
    {
        lResult = RegDeleteKey (hKey, szClsid);
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;
        RegCloseKey (hKey);
    }
    else
        hResult = SELFREG_E_CLASS;

    //
    //  Delete the key HKLM\Software\Microsoft\Windows\CurrentVersion
    //                   \Explorer\VolumeCaches\CleanupSample 
    //
    lResult = RegOpenKeyEx (HKEY_LOCAL_MACHINE, szEmptyVCSubKey, 0, KEY_ALL_ACCESS, &hKey);

    if (lResult == NOERROR)
    {
        lResult = RegDeleteKey (hKey, szDisplay);
        if (lResult != NOERROR) hResult = SELFREG_E_CLASS;

        RegCloseKey (hKey);
    }
    else
        hResult = SELFREG_E_CLASS;

    return hResult;
}

