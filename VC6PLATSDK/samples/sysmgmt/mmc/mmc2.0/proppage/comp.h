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
class CComponent : public IComponent2,
                          IExtendPropertySheet2
{
  // Construction/Destruction
  public:
    CComponent( CComponentData* pParent );
    ~CComponent();


  ///////////////////////////////////////////////////////////////////////////
  // Interface IUnknown
  //
  public:
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
        
  ///////////////////////////////////////////////////////////////////////////
  // Interface IComponent2
  //
  public:
    HRESULT STDMETHODCALLTYPE Initialize
            ( /*[in]*/ LPCONSOLE ipConsole );
            
    HRESULT STDMETHODCALLTYPE Notify
            ( /*[in]*/ LPDATAOBJECT ipDataObject,
              /*[in]*/ MMC_NOTIFY_TYPE MmcEvent,
              /*[in]*/ LONG nArg,
              /*[in]*/ LONG nParam
            );
            
    HRESULT STDMETHODCALLTYPE Destroy
            ( /*[in]*/ MMC_COOKIE nCookie );
            
    HRESULT STDMETHODCALLTYPE QueryDataObject
            ( /*[in]*/  MMC_COOKIE nCookie,
              /*[in]*/  DATA_OBJECT_TYPES nEnumType,
              /*[out]*/ LPDATAOBJECT __RPC_FAR* ppDataObject
            );
            
    HRESULT STDMETHODCALLTYPE GetResultViewType
            ( /*[in]*/  MMC_COOKIE nCookie,
              /*[out]*/ LPOLESTR __RPC_FAR* ppViewType,
              /*[out]*/ long __RPC_FAR* pViewOptions
            );
            
    HRESULT STDMETHODCALLTYPE GetDisplayInfo
            ( /*[out][in]*/ RESULTDATAITEM __RPC_FAR* pResultDataItem );
            
    HRESULT STDMETHODCALLTYPE CompareObjects
            ( /*[in]*/ LPDATAOBJECT lpDataObjectA,
              /*[in]*/ LPDATAOBJECT lpDataObjectB
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


  /////////////////////////////////////////////////////////////////////////
  // Interface IExtendPropertySheet2
  //
  public:
    HRESULT STDMETHODCALLTYPE CreatePropertyPages
            ( /*[in]*/ LPPROPERTYSHEETCALLBACK lpProvider,
              /*[in]*/ LONG_PTR Handle,
              /*[in]*/ LPDATAOBJECT ipIDataObject
            );
            
    HRESULT STDMETHODCALLTYPE QueryPagesFor
            ( /*[in]*/ LPDATAOBJECT ipDataObject
            );
            
    HRESULT STDMETHODCALLTYPE GetWatermarks
            ( /*[in] */ LPDATAOBJECT lpIDataObject,
              /*[out]*/ HBITMAP __RPC_FAR *lphWatermark,
              /*[out]*/ HBITMAP __RPC_FAR *lphHeader,
              /*[out]*/ HPALETTE __RPC_FAR *lphPalette,
              /*[out]*/ BOOL __RPC_FAR *bStretch
            );

  // Private data
  private:
    ULONG            m_cRef;
    HBITMAP          m_hImageStrip16;
    HBITMAP          m_hImageStrip32;
    IConsole3*       m_ipConsole;
    LPCONSOLEVERB    m_ipConsoleVerb;
    LPRESULTDATA     m_ipResultData;
    LPHEADERCTRL2    m_ipHeaderCtrl;
    CComponentData*  m_pComponentData;
    

  ///////////////////////////////////////////////////////////////////////////
  //  Handlers for notifications which are not delegated 
  private:
    HRESULT  OnAddImages( LPDATAOBJECT ipDataObject, LONG nArg, LONG nParam );


  ///////////////////////////////////////////////////////////////////////////
  //  Public helpers
  public:
    HRESULT  GetInterface( DWORD dwRequestedInterface,  LONG_PTR* ppInterface );

};

#endif //_CLASS_CCOMPONENT_
