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
#include "dogcf.h"
#include "cdog.h"

// IUnknown
STDMETHODIMP CClassFactory::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IClassFactory)
        *ppv = this;
    else 
        return ResultFromScode(E_NOINTERFACE); 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG) CClassFactory::AddRef()
{
    return InterlockedIncrement(&m_cRef);
}


STDMETHODIMP_(ULONG) CClassFactory::Release()
{   
    if(InterlockedDecrement(&m_cRef) == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

// IClassFactory
STDMETHODIMP CClassFactory::CreateInstance(IUnknown FAR* punkOuter, REFIID riid, 
										   void FAR* FAR* ppv)
{
    extern HINSTANCE g_hInst;
    
    HRESULT hr;
    CDog * pDog;
    
    *ppv = NULL;
    
    // This implementation does not allow aggregation
    if (punkOuter)
        return ResultFromScode(CLASS_E_NOAGGREGATION);
        
    // Create an instance of the Dog object. 
    pDog = new CDog; 
	
    hr = pDog->QueryInterface(riid, ppv);
    if (FAILED(hr)) 
    {
        delete pDog;
        return hr;
    }  
    return NOERROR;
}

STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
    extern LONG g_cLocks;
    
    if (fLock)
        InterlockedIncrement(&g_cLocks);
    else
        InterlockedDecrement(&g_cLocks);

    return NOERROR;       
}


