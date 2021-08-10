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

//---------------------------------------------------------------------------
class CDataObject : public IDataObject
{
  private:
    ULONG			m_cRef;
    ULONG     m_uCookie;
    ULONG     m_uContext;

  public:
    CDataObject();            
    ~CDataObject();
    
  public:  // Interface IUnknown
    STDMETHODIMP QueryInterface( REFIID riid, LPVOID* ppv );
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
  public:  // IDataObject methods 
    STDMETHODIMP GetDataHere (FORMATETC *pformatetc, STGMEDIUM *pmedium);
    
    // The rest are not implemented
    STDMETHODIMP GetData (LPFORMATETC lpFormatetcIn, LPSTGMEDIUM lpMedium)
    { return E_NOTIMPL; };
    
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
    VOID   SetPrivateData( ULONG uCookie, ULONG uContext );

    // For future use, not used in this sample
    ULONG  GetContext() { return m_uContext; }
    ULONG  GetCookie()  { return m_uCookie;  }

  ///////////////////////////////////////////////////////////////////////////
  // Handlers for required clipboard formats
  private:
    HRESULT  RetrieveDisplayString( IStream* ipStream );
    HRESULT  RetrieveSnapInClassID( IStream* ipStream );    
    HRESULT  RetrieveNodeTypeGuid( IStream* ipStream );
    HRESULT  RetrieveGuidString( IStream* ipStream );

};

#endif //_CLASS_CDATAOBJECT_
