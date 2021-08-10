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
#include "LListImpl.h"       // MULTISELECT:  Need to keep a list of nodes



//---------------------------------------------------------------------------
typedef struct _MultiSelectCookies
{
  DWORD    count;
  LONG_PTR Cookies[1];

} MULTISELECT_COOKIES;



//---------------------------------------------------------------------------
class CDataObject : public IDataObject
{
  private:
    ULONG			m_cRef;
    INT_PTR   m_nCookie;
    ULONG     m_uContext;

  public:
    CDataObject();            
    ~CDataObject();
    
  public:  // Interface IUnknown
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID* ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
  public:  // IDataObject methods 
    STDMETHODIMP GetDataHere( FORMATETC* pFormatEtc, STGMEDIUM* pStgMedium );
    
    STDMETHODIMP GetData( FORMATETC* pFormatEtc, STGMEDIUM* pStgMedium );

    // The rest are not implemented
    //    
    STDMETHODIMP EnumFormatEtc (DWORD dwDirection, LPENUMFORMATETC* ppEnumFormatEtc)
    { return E_NOTIMPL; };
    
    STDMETHODIMP QueryGetData (LPFORMATETC lpFormatetc) 
    { return E_NOTIMPL; };
    
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
    VOID   SetPrivateData( INT_PTR nCookie, ULONG uContext );

    // For future use, not used in this sample
    ULONG    GetContext() { return m_uContext; }
    INT_PTR  GetCookie()  { return m_nCookie;  }

  ///////////////////////////////////////////////////////////////////////////
  // Handlers for required clipboard formats
  private:
    HRESULT  RetrieveDisplayString( IStream* ipStream );
    HRESULT  RetrieveSnapInClassID( IStream* ipStream );    
    HRESULT  RetrieveNodeTypeGuid( IStream* ipStream );
    HRESULT  RetrieveGuidString( IStream* ipStream );
    HRESULT  RetrieveBaseNodePtr( IStream* ipStream );
    HRESULT  RetrieveDataObjPtr( IStream* ipStream );

  ///////////////////////////////////////////////////////////////////////////
  // MULTISELECT:  New methods to support multiselect
  public:
    HRESULT  AddMultiSelectCookie( LONG_PTR nCookie );
    HRESULT  AddMultiSelectGuid( GUID* pGuid );

    HRESULT  RetrieveMultiSelectCookies( STGMEDIUM* pStgMedium );
    HRESULT  RetrieveMultiSelectTypes( STGMEDIUM* pStgMedium );

  private:
    CLListImpl<LONG_PTR, LONG_PTR >  m_CookieList;
    CLListImpl<GUID*,GUID*>          m_GuidList;

};

#endif //_CLASS_CDATAOBJECT_
