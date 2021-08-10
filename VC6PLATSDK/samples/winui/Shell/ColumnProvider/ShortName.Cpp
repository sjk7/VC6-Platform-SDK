//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  ShortName.cpp
//
//      Implements DLL entry-point (DllMain), DllGetClassObject and
//      DllCanUnloadNow functions.
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"
#include "ClassFactory.h"

HINSTANCE hDllInstance = NULL;
ULONG nDllRefCount = 0;

CLSID CLSID_ShortNameColumnProvider = {0};

BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            hDllInstance = hInstance;
            nDllRefCount = 0;

            //
            //  Initialize CLSID_ShortNameColumnProvider
            //
            GetObjectClsid (&CLSID_ShortNameColumnProvider);
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            break;

        default:
            break;
    }
    return TRUE;
}


STDAPI DllCanUnloadNow (VOID)
{
    if (nDllRefCount > 0)
        return S_FALSE;
    return S_OK;
}


STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
    if (ppv == NULL)
        return E_INVALIDARG;

    *ppv = NULL;

    if (!IsEqualIID(rclsid, CLSID_ShortNameColumnProvider))
        return CLASS_E_CLASSNOTAVAILABLE;

    CClassFactory *pFactory = new CClassFactory;
    if (!pFactory)
        return E_OUTOFMEMORY;

    HRESULT hResult = NOERROR;
    hResult = pFactory->QueryInterface (riid, ppv);

    return hResult;
}
