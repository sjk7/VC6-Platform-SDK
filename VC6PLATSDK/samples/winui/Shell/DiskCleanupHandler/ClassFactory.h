//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  ClassFactory.h
//
//      Interface for the CClassFactory class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CLASSFACTORY_H_INCLUDED
#define _CLASSFACTORY_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClassFactory : public IClassFactory  
{
public:
    CClassFactory();
    virtual ~CClassFactory();

    // IUnknown methods
    STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObject);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IClassFactory methods
    STDMETHODIMP CreateInstance (LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppvObject);
    STDMETHODIMP LockServer (BOOL bLock);
private:
    ULONG m_nRefCount;
};

#endif // _CLASSFACTORY_H_INCLUDED
