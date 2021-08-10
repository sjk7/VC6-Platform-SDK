//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  RegisterServer.cpp
//
//      Registers the Disk Cleanup Handler in the registry. The 
//      following registry keys will be created to register the
//      volume cache:
//
//          HKEY_CLASSES_ROOT\CLSID\{CLSID}
//          HKEY_CLASSES_ROOT\CLSID\{CLSID}\InProcServer32
//
//          HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\
//              CurrentVersion\Explorer\VolumeCaches\CleanupSample  
//
//////////////////////////////////////////////////////////////////////

#include "Cleanup.h"
#include "Resource.h"

PSECURITY_DESCRIPTOR WINAPI CreateDacl ();

extern HINSTANCE hDllInstance;

STDAPI DllRegisterServer (VOID)
{
    SECURITY_ATTRIBUTES sa = {0};
    SECURITY_ATTRIBUTES *pSA = &sa;
    TCHAR       szModuleName[MAX_PATH]; 
    HRESULT     hResult = S_OK;
    TCHAR       szBuffer[500] = TEXT("");
    TCHAR       szClsid[MAX_PATH] = TEXT("");
    TCHAR       szSubKey[MAX_PATH] = TEXT("");
    TCHAR       szDisplay[MAX_PATH] = TEXT("");
    TCHAR       szDescription[MAX_PATH] = TEXT("");
    TCHAR       szEmptyVCSubKey[MAX_PATH] = TEXT("");

    //
    //  Load some necessary string values
    //
    LoadString (hDllInstance, IDS_CLSID, szClsid, MAX_PATH);
    LoadString (hDllInstance, IDS_DISPLAY, szDisplay, MAX_PATH);
    LoadString (hDllInstance, IDS_DESCRIPTION, szDescription, MAX_PATH);
    LoadString (hDllInstance, IDS_EMPTYVC_SUBKEY, szEmptyVCSubKey, MAX_PATH);

#if _WIN32_WINNT >= 0x5000 
    //
    //  Initialize the security attributes structure
    //
    sa.nLength              = sizeof (SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = CreateDacl ();
    sa.bInheritHandle       = FALSE;
#else
    pSA = NULL;
#endif
    //
    //  Get the name of this module
    //
    GetModuleFileName (hDllInstance, szModuleName, MAX_PATH);

    //
    //  Register the component under HKCR\CLSID
    //
    HKEY    hKey            = NULL;
    DWORD   dwDisposition   = 0;
    LRESULT lResult         = 0;

    wsprintf (szSubKey, TEXT("CLSID\\%s"), szClsid);
    lResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              pSA, &hKey, &dwDisposition);

    if (lResult == NOERROR)
    {
        lResult = RegSetValueEx (hKey, TEXT(""), 0, REG_SZ, 
				 (LPBYTE) szDisplay, GetStringByteSize(szDisplay));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;
        RegCloseKey (hKey);
        hKey = NULL;
    }
    else
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Register component information under HKCR\CLSID\{CLSID}
    //
    StrCatBuff (szSubKey, TEXT("\\InprocServer32"), ARRAYSIZE(szSubKey));
    lResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              pSA, &hKey, &dwDisposition);

    if (lResult == NOERROR)
    {
        lstrcpyn (szBuffer, TEXT("Apartment"), ARRAYSIZE(szBuffer));
        lResult = RegSetValueEx (hKey, TEXT("ThreadingModel"), 0, REG_SZ, 
				 (LPBYTE) szBuffer, GetStringByteSize (szBuffer));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        lResult = RegSetValueEx (hKey, TEXT(""), 0, REG_SZ, 
				 (LPBYTE) szModuleName, GetStringByteSize(szModuleName));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        RegCloseKey (hKey);
        hKey = NULL;
    }
    else
    {
        hResult = SELFREG_E_CLASS;
    }

    wsprintf (szSubKey, TEXT("CLSID\\%s\\DefaultIcon"), szClsid);
    lResult = RegCreateKeyEx (HKEY_CLASSES_ROOT, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              pSA, &hKey, &dwDisposition);

    if (lResult == NOERROR)
    {
        wsprintf (szBuffer, TEXT("%s,%d"), szModuleName, 0);
        lResult = RegSetValueEx (hKey, TEXT(""), 0, REG_SZ, 
				 (LPBYTE) szBuffer, GetStringByteSize(szBuffer));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        RegCloseKey (hKey);
        hKey = NULL;
    }
    else
    {
        hResult = SELFREG_E_CLASS;
    }


    //
    //  Register the shell extension under 
    //  HKLM\Software\Microsoft\Windows\CurrentVersion\Explorer\VolumeCaches
    //
    wsprintf (szSubKey, TEXT("%s\\%s"), szEmptyVCSubKey, szDisplay);
    lResult = RegCreateKeyEx (HKEY_LOCAL_MACHINE, szSubKey,
                              0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                              pSA, &hKey, &dwDisposition);

    if (lResult == NOERROR)
    {
        lResult = RegSetValueEx (hKey, TEXT("Description"), 0, REG_SZ, 
				 (LPBYTE)szDescription, GetStringByteSize(szDescription));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        lResult = RegSetValueEx (hKey, TEXT("Display"), 0, REG_SZ, 
				 (LPBYTE)szDisplay, GetStringByteSize(szDisplay));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        lResult = RegSetValueEx (hKey, TEXT(""), 0, REG_SZ, 
				 (LPBYTE)szClsid, GetStringByteSize(szClsid));
        if (lResult != NOERROR)
            hResult = SELFREG_E_CLASS;

        RegCloseKey (hKey);
        hKey = NULL;
    }
    else
    {
        hResult = SELFREG_E_CLASS;
    }

    //
    //  Free the security descriptor
    //
    if (sa.lpSecurityDescriptor) {
      LocalFree(sa.lpSecurityDescriptor);
    }

    return hResult;
}
