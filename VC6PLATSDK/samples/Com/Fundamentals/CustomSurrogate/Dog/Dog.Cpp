// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

#include <windows.h>
#include "idog_i.c"
#include "dogcf.h"

LONG g_cLocks;
LONG g_cObjects;
HINSTANCE g_hInst;

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID pvReserved)
{
    switch (dwReason) 
	{
      case DLL_PROCESS_ATTACH:
		  {
			  g_hInst = hInstance;
			  g_cObjects = 0;
			  g_cLocks = 0;
		  }
		  break;
      case DLL_THREAD_ATTACH:
		  break;
      case DLL_THREAD_DETACH:
		  break;
      case DLL_PROCESS_DETACH:
		  break;
    }

    return TRUE;
}

STDAPI DllRegisterServer()
{
    return S_OK;
}

STDAPI DllUnregisterServer()
{
    return S_OK;
}

STDAPI DllCanUnloadNow()
{
    return (g_cLocks | g_cObjects) ? S_FALSE : S_OK;
}

STDAPI  DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv)
{
    HRESULT hr;
    CClassFactory* pv;

    if (!ppv)
        return E_INVALIDARG;

    if (!IsEqualCLSID(rclsid, CLSID_DogClass))
        return CLASS_E_CLASSNOTAVAILABLE;

    pv = new CClassFactory();
    if (!pv)
        return E_OUTOFMEMORY;

    hr = ((IUnknown *)pv)->QueryInterface(riid, ppv);

    return hr;
}

