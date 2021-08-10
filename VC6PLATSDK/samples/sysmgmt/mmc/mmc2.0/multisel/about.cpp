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
//  Abstract:  Implementation of ISnapinAbout
//


#include "Globals.h"
#include "About.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
//  Construction/Destruction

//---------------------------------------------------------------------------
CSnapinAbout::CSnapinAbout()
{
  m_cRef = 0;
  InterlockedIncrement((long*)&g_uObjectCount);

  m_hSmallImage = (HBITMAP)LoadImage(g_hInst, MAKEINTRESOURCE(IDB_APPIMG_16), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);
  m_hLargeImage = (HBITMAP)LoadImage(g_hInst, MAKEINTRESOURCE(IDB_APPIMG_32), IMAGE_BITMAP, 32, 32, LR_LOADTRANSPARENT);

  // This image is displayed when the static node is selected
  m_hOpenImage  = (HBITMAP)LoadImage(g_hInst, MAKEINTRESOURCE(IDB_APPIMG_16), IMAGE_BITMAP, 16, 16, LR_LOADTRANSPARENT);
    
  m_hAppIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_APP_ICON));
}

CSnapinAbout::~CSnapinAbout()
{
  SAFE_FREE_BITMAP( m_hSmallImage );
  SAFE_FREE_BITMAP( m_hLargeImage );
  SAFE_FREE_BITMAP( m_hOpenImage  );
  SAFE_FREE_ICON( m_hAppIcon );
 
  InterlockedDecrement((long*)&g_uObjectCount);
}

/////////////////////////////////////////////////////////////////////////////
// IUnknown implementation

//---------------------------------------------------------------------------
STDMETHODIMP CSnapinAbout::QueryInterface
(
  REFIID   riid,       //[in] Identifier of the requested interface
  LPVOID   *ppv        //[out] Address of requested interface 
)
{
  if( !ppv )
    return E_FAIL;
    
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
    *ppv = static_cast<ISnapinAbout*>(this);
  else if( IsEqualIID(riid, IID_ISnapinAbout) )
    *ppv = static_cast<ISnapinAbout*>(this);
    
  if( *ppv )
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
  }
    
  return E_NOINTERFACE;
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSnapinAbout::AddRef()
{
  return InterlockedIncrement((long*)&m_cRef);
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSnapinAbout::Release()
{
  if( 0 == InterlockedDecrement((long*)&m_cRef) )
  {
    // we need to decrement our object count in the DLL
    delete this;
    return 0;
  }
  return m_cRef;
}


/////////////////////////////////////////////////////////////////////////////
// Interface ISnapinAbout

//---------------------------------------------------------------------------
STDMETHODIMP CSnapinAbout::GetSnapinDescription
( 
  LPOLESTR* pszDescription   //[out] Pointer to the description text
)
{
  LONG nLen = wcslen( gwszABOUT_DESCRIPTION ) + 1;
  *pszDescription = (LPOLESTR)CoTaskMemAlloc( nLen * sizeof(WCHAR) );
  if( NULL == *pszDescription )
    return E_OUTOFMEMORY;

  wcscpy( *pszDescription, gwszABOUT_DESCRIPTION );
  return S_OK;
}

//---------------------------------------------------------------------------
STDMETHODIMP CSnapinAbout::GetProvider
( 
  LPOLESTR* pszProvider      //[out] Pointer to provider text
)
{
  LONG nLen = wcslen( gwszABOUT_PROVIDER ) + 1;
  *pszProvider = (LPOLESTR)CoTaskMemAlloc( nLen * sizeof(WCHAR) );
  if( NULL == *pszProvider )
    return E_OUTOFMEMORY;

  wcscpy( *pszProvider, gwszABOUT_PROVIDER );
  return S_OK;
}

//---------------------------------------------------------------------------
STDMETHODIMP CSnapinAbout::GetSnapinVersion
( 
  LPOLESTR*  pszVersion      //[out] Pointer to version text
)
{
  LONG nLen = wcslen( gwszABOUT_VERSION ) + 1;
  *pszVersion = (LPOLESTR)CoTaskMemAlloc( nLen * sizeof(WCHAR) );
  if( NULL == *pszVersion )
    return E_OUTOFMEMORY;

  wcscpy( *pszVersion, gwszABOUT_VERSION );
  return S_OK;
}

//---------------------------------------------------------------------------
STDMETHODIMP CSnapinAbout::GetSnapinImage
( 
  HICON *hAppIcon            //[out] Pointer to the Snap-in's main icon
)
{
  *hAppIcon = m_hAppIcon;
  HRESULT hResult = S_FALSE;    
  (NULL == *hAppIcon ) ? hResult = E_FAIL : hResult = S_OK; 

  return hResult;
}

//---------------------------------------------------------------------------
STDMETHODIMP CSnapinAbout::GetStaticFolderImage
( 
  HBITMAP*   hSmallImage,      //[out] Pointer to small image
  HBITMAP*   hOpenImage,       //[out] Pointer to open folder image
  HBITMAP*   hLargeImage,      //[out] Pointer to large image 
  COLORREF*  cMask             //[out] Pointer to image color mask
)
{
  *hSmallImage = m_hSmallImage;
  *hLargeImage = m_hLargeImage;
  *hOpenImage  = m_hOpenImage;
  *cMask       = RGB(0, 255, 0);
    
  if( NULL == *hSmallImage || NULL == *hLargeImage || NULL == *hOpenImage )
    return E_FAIL;

  return S_OK;
}

