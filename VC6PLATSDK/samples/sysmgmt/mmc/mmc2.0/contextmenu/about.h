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
//  Abstract:     This class implements ISnapinAbout



#ifndef _CLASS_CSNAPINABOUT_
#define _CLASS_CSNAPINABOUT_

#include <mmc.h>


//---------------------------------------------------------------------------
class CSnapinAbout : public ISnapinAbout
{
  private:
    ULONG				m_cRef;
    HBITMAP			m_hSmallImage;
    HBITMAP			m_hLargeImage;
    HBITMAP			m_hOpenImage;
    HICON				m_hAppIcon;
    
  public:
    CSnapinAbout();
    ~CSnapinAbout();
    
    /////////////////////////////////////////////////////////////////////////
    // Interface IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, LPVOID *ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();
    
    /////////////////////////////////////////////////////////////////////////
    // Interface ISnapinAbout
    STDMETHODIMP GetSnapinDescription(/*[out]*/ LPOLESTR* pszDescription );
        
    STDMETHODIMP GetProvider(/*[out]*/ LPOLESTR* pszProvider );
        
    STDMETHODIMP GetSnapinVersion(/*[out]*/ LPOLESTR* pszVersion);
        
    STDMETHODIMP GetSnapinImage(/*[out]*/ HICON* hAppIcon );
        
    STDMETHODIMP GetStaticFolderImage
                 (/*[out]*/ HBITMAP*  hSmallImage,
                  /*[out]*/ HBITMAP*  hOpenImage,
                  /*[out]*/ HBITMAP*  hLargeImage,
                  /*[out]*/ COLORREF* cMask
                 );
};

#endif _CLASS_CSNAPINABOUT_
