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


#ifndef _CLASS_CCOMPONENT_
#define _CLASS_CCOMPONENT_

#include "Globals.h"


class CComponentData;                  // References


//---------------------------------------------------------------------------
class CComponent : public IComponent2
{
  // Construction/Destruction
  public:
    CComponent( CComponentData* pParent );
    ~CComponent();


    /////////////////////////////////////////////////////////////////////////
    // Interface IUnknown
    //
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
        
    /////////////////////////////////////////////////////////////////////////
    // Interface IComponent
    //
    HRESULT STDMETHODCALLTYPE Initialize
            ( /*[in] */ LPCONSOLE ipConsole );
            
    HRESULT STDMETHODCALLTYPE Notify
            ( /*[in] */ LPDATAOBJECT ipDataObject,
              /*[in] */ MMC_NOTIFY_TYPE MmcEvent,
              /*[in] */ LONG nArg,
              /*[in] */ LONG nParam
            );
            
    HRESULT STDMETHODCALLTYPE Destroy
            ( /*[in] */ MMC_COOKIE nCookie );
            
    HRESULT STDMETHODCALLTYPE QueryDataObject
            ( /*[in] */  MMC_COOKIE nCookie,
              /*[in] */  DATA_OBJECT_TYPES nEnumType,
              /*[out]*/  LPDATAOBJECT __RPC_FAR* ppDataObject
            );
            
    HRESULT STDMETHODCALLTYPE GetResultViewType
            ( /*[in] */  MMC_COOKIE nCookie,
              /*[out]*/  LPOLESTR __RPC_FAR* ppViewType,
              /*[out]*/  long __RPC_FAR* pViewOptions
            );
            
    HRESULT STDMETHODCALLTYPE GetDisplayInfo
            ( /*[in,out]*/ RESULTDATAITEM __RPC_FAR* pResultDataItem );
            
    HRESULT STDMETHODCALLTYPE CompareObjects
            ( /*[in] */ LPDATAOBJECT lpDataObjectA,
              /*[in] */ LPDATAOBJECT lpDataObjectB
            );
    HRESULT STDMETHODCALLTYPE QueryDispatch
            ( /*[in] */  MMC_COOKIE  nCookie,
              /*[in] */  DATA_OBJECT_TYPES eType,
              /*[out]*/  LPDISPATCH* pipDispatch
            );

    HRESULT STDMETHODCALLTYPE GetResultViewType2
            ( /*[in] */    MMC_COOKIE nCookie,
              /*[in,out]*/ PRESULT_VIEW_TYPE_INFO pRVTinfo
            );

    HRESULT STDMETHODCALLTYPE RestoreResultView
            ( /*[in] */    MMC_COOKIE nCookie,
              /*[in,out]*/ PRESULT_VIEW_TYPE_INFO pResultViewType
            );

  private:
    ULONG            m_cRef;
    CComponentData*  m_pComponentData;

};

#endif //_CLASS_CCOMPONENT_
