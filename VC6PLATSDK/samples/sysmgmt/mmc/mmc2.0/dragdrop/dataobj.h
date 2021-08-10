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

#ifndef _CLASS_CDATAOBJECT_
#define _CLASS_CDATAOBJECT_

#include "Globals.h"
#include "StaticNode.h"
#include "EnumFormatEtc.h"             // DRAGDROP: New interface implemented

//---------------------------------------------------------------------------
class CDataObject : public IDataObject
{
  private:
    ULONG			m_cRef;
    ULONG     m_uCookie;
    ULONG     m_uContext;
    ULONG     m_uNodeTypeFlg;          // DRAGDROP: New data member

  public:
    CDataObject();            
    ~CDataObject();
    
  public:  // Interface IUnknown
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID* ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
  public:  // IDataObject methods 
    STDMETHODIMP GetDataHere (FORMATETC* pFormatEtc, STGMEDIUM* pStgMedium);
    STDMETHODIMP GetData (FORMATETC* pFormatEtc, STGMEDIUM* pStgMedium);
    STDMETHODIMP QueryGetData (FORMATETC* pFormatEtc);
    STDMETHODIMP EnumFormatEtc (DWORD dwDirection, LPENUMFORMATETC* ppEnumFormatEtc);
 
   
    // The rest are not implemented
    STDMETHODIMP GetCanonicalFormatEtc (LPFORMATETC lpFormatetcIn, LPFORMATETC lpFormatetcOut)
    { return E_NOTIMPL; };
    
    STDMETHODIMP SetData (LPFORMATETC lpFormatetc, LPSTGMEDIUM lpMedium, BOOL bRelease)
    { return E_NOTIMPL; };
    
    STDMETHODIMP DAdvise (LPFORMATETC lpFormatetc, DWORD advf, LPADVISESINK pAdvSink, LPDWORD pdwConnection)
    { return E_NOTIMPL; };
    
    STDMETHODIMP DUnadvise (DWORD dwConnection)
    { return E_NOTIMPL; };
    
    STDMETHODIMP EnumDAdvise (LPENUMSTATDATA* ppEnumAdvise)
    { return E_NOTIMPL; };
    
  ///////////////////////////////////////////////////////////////////////////
  // Custom Methods
  public:
    VOID   SetPrivateData( ULONG uCookie, ULONG uContext );

    ULONG  GetContext() { return m_uContext; }
    ULONG  GetCookie()  { return m_uCookie;  }   // Returns unique indentifier

  public:
    CEnumFormatEtc*    m_pEnumFormatEtc;


  ///////////////////////////////////////////////////////////////////////////
  // Handlers for required clipboard formats
  private:
    HRESULT  RetrieveDisplayString( IStream* ipStream );
    HRESULT  RetrieveSnapInClassID( IStream* ipStream );    
    HRESULT  RetrieveNodeTypeGuid( IStream* ipStream );
    HRESULT  RetrieveGuidString( IStream* ipStream );
    HRESULT  RetrieveBaseNodePtr( IStream* ipStream );
    HRESULT  RetrieveDataObjPtr( IStream* ipStream );

    // DRAGDROP: New methods to support interprocess DragDrop
    HRESULT  RetrieveNodePropPtr( STGMEDIUM*  pStgMedium );
    HRESULT  RetrieveNodeTypeFlg( STGMEDIUM*  pStgmedium );    

};

#endif //_CLASS_CDATAOBJECT_
