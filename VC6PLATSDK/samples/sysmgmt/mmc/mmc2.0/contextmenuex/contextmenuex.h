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


#ifndef _CLASS_CCONTEXTMENUX_
#define _CLASS_CCONTEXTMENUX_


#include "Globals.h"

//---------------------------------------------------------------------------
class CExtendContextMenuEx : public IExtendContextMenu
{
  private:
    ULONG			     m_cRef;

  public:
    CExtendContextMenuEx();
    ~CExtendContextMenuEx();
  
  ///////////////////////////////////////////////////////////////////////////
  // Interface IUnknown
  public:
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID *ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();


    /////////////////////////////////////////////////////////////////////////
    // Interface IExtendContextMenu
    //
    HRESULT STDMETHODCALLTYPE AddMenuItems
            ( /*[in]*/ LPDATAOBJECT ipDataObject,
              /*[in]*/ LPCONTEXTMENUCALLBACK ipCallback,
              /*[out,in]*/ long __RPC_FAR* pInsertionAllowed
            );

    HRESULT STDMETHODCALLTYPE Command
            ( /*[in]*/ long lCommandID,
              /*[in]*/ LPDATAOBJECT piDataObject
            );

  private:

};

#endif //_CLASS_CCONTEXTMENUX_