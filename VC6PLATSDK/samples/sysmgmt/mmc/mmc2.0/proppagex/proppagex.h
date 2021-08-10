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


#ifndef _CLASS_CPROPERTYSHEETX_
#define _CLASS_CPROPERTYSHEETX_


#include "Globals.h"

//---------------------------------------------------------------------------
class CExtendPropertySheet : public IExtendPropertySheet
{
  private:
    ULONG			     m_cRef;
    ULONG          m_nPageCount;
    NODE_ATTRIBS   m_pNodeAttribs;     // Path to object
    DWORD          m_dwXAttribs;       // Our extended attributes  

  public:

  public:
    CExtendPropertySheet();
    ~CExtendPropertySheet();
  
  ///////////////////////////////////////////////////////////////////////////
  // Interface IUnknown
  public:
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID *ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();


  /////////////////////////////////////////////////////////////////////////
  // Interface IExtendPropertySheet
  public:
    HRESULT STDMETHODCALLTYPE CreatePropertyPages
            ( /*[in]*/ LPPROPERTYSHEETCALLBACK lpProvider,
              /*[in]*/ LONG_PTR Handle,
              /*[in]*/ LPDATAOBJECT ipIDataObject
            );
            
    HRESULT STDMETHODCALLTYPE QueryPagesFor
            ( /*[in]*/ LPDATAOBJECT ipDataObject
            );
            

  private:
    static BOOL CALLBACK PPageWndProcX( HWND hPage, UINT uMsg, WPARAM wParam, LPARAM lParam );

    BOOL OnInitPropPage( HWND hPage, WPARAM wParam, LPARAM lParam );
    BOOL OnApplyChanges( HWND hPage, WPARAM wParam, LPARAM lParam );

    BOOL IsAttributeSet( DWORD dwAttribute ); 

};

#endif //_CLASS_CPROPERTYSHEETX_