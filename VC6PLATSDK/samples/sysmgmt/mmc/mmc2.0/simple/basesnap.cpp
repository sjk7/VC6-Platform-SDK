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
//  Abstract:  This file contains implementations for CComponentData's
//             class factory and the Snap-in DLL exported functions


#include <ObjBase.h>
#include <InitGuid.h>
#include "Guids.h"
#include "BaseSnap.h"
#include "Comp.h"
#include "CompData.h"
#include "Registry.h"
#include "Globals.h"

/////////////////////////////////////////////////////////////////////////////
//  Implementation of IClassFactory for CComponentData

//---------------------------------------------------------------------------
CClassFactory::CClassFactory()
             : m_cRef(0)
{
  InterlockedIncrement((long*)&g_uObjectCount);  
}


//---------------------------------------------------------------------------
CClassFactory::~CClassFactory()
{
  InterlockedDecrement((long*)&g_uObjectCount);
}


//---------------------------------------------------------------------------
STDMETHODIMP CClassFactory::QueryInterface
(
  REFIID   riid,             //[in] Identifier of the requested interface
  LPVOID*  ppv               //[out] Address of requested interface
)
{
  if( NULL == ppv )
    return E_FAIL;
    
  HRESULT hResult = E_NOINTERFACE;
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
  {
    *ppv = static_cast<IClassFactory *>(this);
  }
  else if( IsEqualIID(riid, IID_IClassFactory) )
  {
    *ppv = static_cast<IClassFactory *>(this);
  }
        
  if( *ppv )
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    hResult = S_OK;
  }
        
  return hResult;
}


//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CClassFactory::AddRef()
{
  return InterlockedIncrement( (long*)&m_cRef );
}


//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CClassFactory::Release()
{
  if( 0 == InterlockedDecrement( (long*)&m_cRef) )
  {
    delete this;
    return 0;
  }
  return m_cRef;
}

//---------------------------------------------------------------------------
//  Creates an instance of CComponentData
//
STDMETHODIMP CClassFactory::CreateInstance
(
  LPUNKNOWN  pUnkOuter,      //[in] NULL unless object is part of aggregate
  REFIID     riid,           //[in] Reference to interface indentifier
  LPVOID*    ppvObj          //[out] Address of requested interface pointer
)
{
  HRESULT  hResult = E_FAIL;
  void*    pObject = NULL;
    
  if( NULL == ppvObj )
    return hResult;
    
  *ppvObj = NULL;
    
  // Our object does does not support aggregation, so we need to
  // fail if they ask us to do aggregation.
  if( pUnkOuter )
    return CLASS_E_NOAGGREGATION;
    
  pObject = new CComponentData();
  if( NULL == pObject )                // Fail to create CComponentData
    return E_OUTOFMEMORY;
    
  // QueryInterface will do the AddRef() for us, don't do it here
  hResult = ( (LPUNKNOWN)pObject)->QueryInterface( riid, ppvObj );
    
  if( S_OK != hResult )
    delete pObject;

  return hResult;
}


//---------------------------------------------------------------------------
STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
  if( TRUE == fLock )
    InterlockedIncrement((long*)&g_uServerLocks);
  else
    InterlockedDecrement((long*)&g_uServerLocks);
    
  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
//  Our Snap-in's exported functions
//

//---------------------------------------------------------------------------
//  Entry point into our Snap-in DLL
//
BOOL WINAPI DllMain
(
  HINSTANCE  hInstDLL,         //[in] Handle to DLL module
  DWORD      fdwReason,        //[in] Reason for calling function 
  void*      lpvReserved       //[in] Reserved
)
{
  if( DLL_PROCESS_ATTACH == fdwReason )
  {
     g_hInst = hInstDLL;
  }
    
  return TRUE;
}


//---------------------------------------------------------------------------
STDAPI DllGetClassObject
(
  REFCLSID   rclsid,         //[in] CLSID for the class object
  REFIID     riid,           //[in] Reference to interface identifier 
  LPVOID     *ppvObj         //[out] Object which recieves interface pointer
)
{
  if( rclsid != CLSID_CComponentData )
    return CLASS_E_CLASSNOTAVAILABLE;
    
  if( !ppvObj )
    return E_FAIL;
    
  *ppvObj = NULL;
    
  // We can only hand out IUnknown and IClassFactory pointers.  Fail
  // if they ask for anything else.
  if( !IsEqualIID(riid, IID_IUnknown) && !IsEqualIID(riid, IID_IClassFactory) )
    return E_NOINTERFACE;
    
  CClassFactory *pFactory = new CClassFactory();
  if( NULL == pFactory )
    return E_OUTOFMEMORY;
    
  HRESULT hResult = pFactory->QueryInterface( riid, ppvObj );
    
  return hResult;
}


//---------------------------------------------------------------------------
STDAPI DllCanUnloadNow(void)
{
  if( 0 == g_uObjectCount && 0 == g_uServerLocks )
    return S_OK;
  else
    return S_FALSE;
}


//---------------------------------------------------------------------------
STDAPI DllRegisterServer()
{
  if( S_OK == RegisterServer( g_hInst, CLSID_CComponentData, gtszSNAPIN_NAME) )
    return RegisterSnapin( CLSID_CComponentData, gtszSNAPIN_NAME, IID_NULL, FALSE );
  else
    return E_FAIL;
}


//---------------------------------------------------------------------------
STDAPI DllUnregisterServer()
{
  if( S_OK == UnregisterServer(CLSID_CComponentData) )
    return UnregisterSnapin(CLSID_CComponentData);
  else
    return E_FAIL;
}

