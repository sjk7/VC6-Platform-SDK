//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  ClassFactory.cpp
//
//      Implementation of the CClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "ShortName.h"
#include "ClassFactory.h"
#include "ColumnProvider.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClassFactory::CClassFactory()
{
    m_nRefCount = 0;
    nDllRefCount++;
}

CClassFactory::~CClassFactory()
{
    nDllRefCount--;
}

/////////////////////////////////////////////////////////////////////
//  IUnknown Methods
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, LPVOID *ppvObject)
{
    HRESULT hr = E_NOINTERFACE;

    *ppvObject = NULL;
    if (IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_IClassFactory))
    {
        *ppvObject = (LPVOID)(LPCLASSFACTORY) this;
    }

    if (*ppvObject != NULL)
    {
        ((LPUNKNOWN)*ppvObject)->AddRef ();
        hr = S_OK;
    }
    return hr;
}

STDMETHODIMP_(ULONG) CClassFactory::AddRef()
{
    m_nRefCount++;
    return m_nRefCount;
}

STDMETHODIMP_(ULONG) CClassFactory::Release()
{
    if (--m_nRefCount == 0)
    {
        delete this;
        return 0;
    }
    return m_nRefCount;
}

/////////////////////////////////////////////////////////////////////
//  IClassFactory Methods
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObject)
{
    *ppvObject = NULL;
    if (pUnkOuter)
    {
        return CLASS_E_NOAGGREGATION;
    }

    CColumnProvider *pcp = new CColumnProvider;
    if (!pcp) 
    {
        return E_OUTOFMEMORY;
    }

    HRESULT hResult = pcp->QueryInterface (riid, ppvObject);
    if (FAILED(hResult))
    {
        delete pcp;
        *ppvObject = NULL;
    }
    return hResult;
}

STDMETHODIMP CClassFactory::LockServer (BOOL bLock)
{
    return S_OK;
}
