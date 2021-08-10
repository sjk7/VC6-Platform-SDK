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


#include "Globals.h"
#include "PropPageX.h"
#include "Resource.h"

                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CExtendPropertySheet2")

/////////////////////////////////////////////////////////////////////////////
//  Implementation of IUnknown

//---------------------------------------------------------------------------
//  XPROPPAGE:  MMC will only QI for IExtendPropertySheet in an extension.
//
STDMETHODIMP CExtendPropertySheet::QueryInterface
(
  REFIID   riid,       //[in] Identifier of the requested interface
  LPVOID   *ppv        //[out] Address of requested interface 
)
{
  if( !ppv )
    return E_FAIL;
    
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
    *ppv = static_cast<IExtendPropertySheet*>(this);
  else if( IsEqualIID(riid, IID_IExtendPropertySheet) )
    *ppv = static_cast<IExtendPropertySheet*>(this);


  if( *ppv )
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
  }
    
  return E_NOINTERFACE;
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CExtendPropertySheet::AddRef()
{
  return InterlockedIncrement((LONG*)&m_cRef);
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CExtendPropertySheet::Release()
{
  if( InterlockedDecrement((LONG*)&m_cRef) == 0 )
  {
    delete this;
    return 0;
  }
  return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
//  Construction-Destruction

//---------------------------------------------------------------------------
CExtendPropertySheet::CExtendPropertySheet()
{
  InterlockedIncrement((long*)&g_uObjectCount);  

  //XPROPPAGE:  Register the clipformat
  g_cfNodeAttrPtr  = RegisterClipboardFormat( T_CCF_ATTRIB_PTR );

  m_cRef         = 0;
  m_nPageCount   = 1;
  m_dwXAttribs   = 0;

  TRACE_START(_T("New instance of CExtendPropertySheet") );
}

//---------------------------------------------------------------------------
CExtendPropertySheet::~CExtendPropertySheet()
{
  InterlockedDecrement((long*)&g_uObjectCount);
}


/////////////////////////////////////////////////////////////////////////////
//  IExtendPropertySheet

//---------------------------------------------------------------------------
//  The console calls this when the primary Snap-in brings up it's Property
//  page.  We get a data object from the primary which should contain the
//  info we need to extend the properties of the node.
//
STDMETHODIMP CExtendPropertySheet::CreatePropertyPages
( 
  LPPROPERTYSHEETCALLBACK lpCallback,  //[in] Pointer to callback interface
  LONG_PTR                Handle,      //[in] NULL for extensions
  LPDATAOBJECT            ipDataObject //[in] Pointer to data object
)
{
  _ASSERT( NULL != ipDataObject );
  HRESULT hResult = S_FALSE;

  // Setup the struct we need to retrive the data
  STGMEDIUM StgMedium = { TYMED_HGLOBAL,  NULL  };
  FORMATETC FormatEtc = { g_cfNodeAttrPtr, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

  // Ask the data object for a pointer to NODE_ATTRIBS  
  hResult = ipDataObject->GetData( &FormatEtc, &StgMedium );
  NODE_ATTRIBS*  pTmpAttribs = (NODE_ATTRIBS*)GlobalLock( StgMedium.hGlobal );

  // Copy the data into a local buffer
  wcscpy( m_pNodeAttribs.szObjectPath, pTmpAttribs->szObjectPath );

  // Now we can unlock and free hGlobal
  GlobalUnlock( StgMedium.hGlobal ); 
  GlobalFree( StgMedium.hGlobal );
  
  HPROPSHEETPAGE hPPage = NULL;          
  PROPSHEETPAGE  psp;
  ZeroMemory( &psp, sizeof(PROPSHEETPAGE) );

  psp.dwSize      = sizeof(PROPSHEETPAGE);
  psp.dwFlags     = PSP_DEFAULT | PSP_USETITLE;  // | PSP_HASHELP;   
  psp.hInstance   = g_hInst;
  psp.pszTemplate = MAKEINTRESOURCE(IDD_PPAGE0);
  psp.pfnDlgProc  = PPageWndProcX;
  psp.lParam      = reinterpret_cast<LPARAM>(this);            
  psp.pszTitle    = _T("Extended");   
  psp.pfnCallback = NULL;
  
  hPPage  = ::CreatePropertySheetPage( &psp );

  hResult = lpCallback->AddPage( hPPage );

  return hResult;
}
            
//---------------------------------------------------------------------------
//  This method is not even called for extensions
//
STDMETHODIMP CExtendPropertySheet::QueryPagesFor
(
  LPDATAOBJECT ipDataObject  //[in] Pointer to selected data object
)
{
  _ASSERT( NULL != ipDataObject );
  return S_OK;
}
            

/////////////////////////////////////////////////////////////////////////////
//  Private methods


//---------------------------------------------------------------------------
//  Dialog Proc for our PropertySheet
//
BOOL CALLBACK CExtendPropertySheet::PPageWndProcX
(
  HWND    hPage,     //[in] Handle to property page
  UINT    uMsg,      //[in] Message
  WPARAM  wParam,    //[in] First message parameter
  LPARAM  lParam     //[in] Second message parameter
)
{
  static CExtendPropertySheet* pApp = NULL;  
         BOOL bReturn = FALSE;

  switch( uMsg )                       // Begin message switch
  {
    case WM_INITDIALOG:
    {
      // Cache the pointer to the calling instance of CExtendPropertySheet
      // and call it's OnInitPropPage method
      PROPSHEETPAGE* psp = (PROPSHEETPAGE*)lParam;
      pApp = reinterpret_cast<CExtendPropertySheet*>(psp->lParam);
      pApp->OnInitPropPage( hPage, wParam, lParam );
      break;
    }
    case WM_HELP:
    {
      // Not handling WM_HELP in this sample
      break;
    }    
    case WM_COMMAND:
    {
      // Activate the 'Apply' button if the user clicked a button
      if( BN_CLICKED == HIWORD(wParam) )
        SendMessage(GetParent(hPage), PSM_CHANGED, (WPARAM)hPage, 0);

      break;
    }
    case WM_DESTROY:
    {
      TRACE_START( _T("WM_DESTROY") );
      bReturn = TRUE;
    }

    case WM_NOTIFY:
    {
      if( 0 == lParam )  //BUGLIST:  AV if we don't do this
        return 0;

      switch( (reinterpret_cast<NMHDR*>(lParam))->code )
      {
        case PSN_APPLY:      // Really the 'OK' button
        {
          pApp->OnApplyChanges( hPage, wParam, lParam ); 
          return PSNRET_NOERROR;
        }
        case PSN_HELP:
        {
          return PSNRET_NOERROR;
        }
        default:
        {
          break;
        }      
      } //end lParam->code switch
    } // end WM_NOTIFY
 
    default: break;

  } // end uMsg switch

  return bReturn;

} 


//---------------------------------------------------------------------------
BOOL CExtendPropertySheet::OnInitPropPage
(
  HWND     hPage,      //[in] Handle to Property Page
  WPARAM   wParam,     //[in] First message parameter
  LPARAM   lParam      //[in] Second message parameter
)
{
  LRESULT lResult = 0;

  HWND hCompressCtrl  = GetDlgItem( hPage, IDC_ATTR_COMPRESSED ); 
  HWND hEncryptedCtrl = GetDlgItem( hPage, IDC_ATTR_ENCRYPTED  );


  if( TRUE == IsAttributeSet( ATTRIBUTE_DATA_COMPRESSED ) )
    lResult = SendMessage( hCompressCtrl,  BM_SETCHECK, BST_CHECKED, 0 );   

  if( TRUE == IsAttributeSet( ATTRIBUTE_DATA_ENCRYPTED ) )
    lResult = SendMessage( hEncryptedCtrl,  BM_SETCHECK, BST_CHECKED, 0 );   

  return TRUE;
}

//---------------------------------------------------------------------------
BOOL CExtendPropertySheet::OnApplyChanges
(
  HWND     hPage,      //[in] Handle to Property Page
  WPARAM   wParam,     //[in] First message parameter
  LPARAM   lParam      //[in] Second message parameter
)
{
  // In this sample we're not saving changes.
  return TRUE;
}


//---------------------------------------------------------------------------
BOOL CExtendPropertySheet::IsAttributeSet
( 
  DWORD dwAttribute           //[in] Attribute to set
)
{
  return (m_dwXAttribs & dwAttribute) ? TRUE : FALSE;
}


