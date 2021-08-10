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
//  Abstract: This module provides the basic COM and DLL methods to create
//            and load the Snap-in.  IClassFactory::CreateInstance creates
//            an instance of a class whose type is passed in the constructor
//              


#ifndef _BASESNAP_H_
#define _BASESNAP_H_

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppvObj);
STDAPI DllCanUnloadNow(void);

//---------------------------------------------------------------------------
class CClassFactory : public IClassFactory
{
  public:
    enum FACTORY_TYPE {COMPONENTDATA = 0, ABOUT = 1};

  public:
    CClassFactory(FACTORY_TYPE eFactoryType);
    ~CClassFactory();
    
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID* ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
    STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID*);
    STDMETHODIMP LockServer(BOOL);

  private:
    ULONG	        m_cRef;
    FACTORY_TYPE  m_FactoryType;

};

#endif _BASESNAP_H_
