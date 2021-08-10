/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//
//  Abstract:  This module provides the basic COM and DLL methods to create
//             and load the Snap-in.  IClassFactory::CreateInstance creates
//             an instance of CComponentData which is the Snap-in's root
//             or static node
//


#ifndef _BASESNAP_H_
#define _BASESNAP_H_

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppvObj);
STDAPI DllCanUnloadNow(void);

//---------------------------------------------------------------------------
class CClassFactory : public IClassFactory
{
  private:
    ULONG	m_cRef;
    
  public:
    CClassFactory();
    ~CClassFactory();
    
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
    STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID*);
    STDMETHODIMP LockServer(BOOL);
};

#endif _BASESNAP_H_
