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


#ifndef _CLASS_CCOMPONENTDATA_
#define _CLASS_CCOMPONENTDATA_


#include <ObjIdl.h>
#include "Globals.h"
#include "StaticNode.h"
#include "Comp.h"

//---------------------------------------------------------------------------
class CComponentData : public IComponentData2
{
  private:
    ULONG				         m_cRef;
    LPCONSOLE			       m_ipConsole2;           // Not used in this sample
    LPCONSOLENAMESPACE	 m_ipConsoleNameSpace2;  // Not used in this sample
    CStaticNode*         m_pStaticNode;
    
  public:
    CComponentData();
    ~CComponentData();
    
    /////////////////////////////////////////////////////////////////////////
    // Interface IUnknown
    //
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID *ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
    /////////////////////////////////////////////////////////////////////////
    // Interface IComponentData
    //
    HRESULT STDMETHODCALLTYPE Initialize
            ( /*[in] */ LPUNKNOWN pUnknown );
        
    HRESULT STDMETHODCALLTYPE CreateComponent
            ( /*[out]*/ LPCOMPONENT __RPC_FAR* ppComponent);
        
    HRESULT STDMETHODCALLTYPE Notify
            ( /*[in] */ LPDATAOBJECT ipDataObject,
              /*[in] */ MMC_NOTIFY_TYPE MmcEvent,
              /*[in] */ LONG nArg,
              /*[in] */ LONG nParam
            );
        
    HRESULT STDMETHODCALLTYPE Destroy( void);
    
    HRESULT STDMETHODCALLTYPE QueryDataObject
            ( /*[in] */  MMC_COOKIE uCookie,
              /*[in] */  DATA_OBJECT_TYPES nEnumType,
              /*[out] */ LPDATAOBJECT __RPC_FAR* ppDataObject
            );
    
    HRESULT STDMETHODCALLTYPE GetDisplayInfo
            ( /*[in,out]*/ SCOPEDATAITEM __RPC_FAR* pScopeDataItem );
        
    HRESULT STDMETHODCALLTYPE CompareObjects
            ( /*[in] */ LPDATAOBJECT lpDataObjectA,
              /*[in] */ LPDATAOBJECT lpDataObjectB
            );

    HRESULT STDMETHODCALLTYPE QueryDispatch
            ( /*[in] */  MMC_COOKIE  nCookie,
              /*[in] */  DATA_OBJECT_TYPES eType,
              /*[out]*/  LPDISPATCH* pipDispatch
            );
        
  // Pulic helper methods
  public:
    CStaticNode* GetStaticNode() { return m_pStaticNode; } 

};

#endif //_CLASS_CCOMPONENTDATA_
