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
//  Abstract:  Implements our virtual file class derived from CBaseNode.  This
//             class will represent our result items
//

#include "VirtualFile.h"
#include "Globals.h"
#include "CompData.h"
#include "Comp.h"
#include "FolderNode.h"
                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CVirtualFile")


// Initialize our static GUID just once
GUID CVirtualFile::thisGUID = CLSID_CVirtualFile;   


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

//---------------------------------------------------------------------------
CVirtualFile::CVirtualFile()
{
  m_RDI.mask       = DEFAULT_RDI_MASK;
  m_RDI.str        = MMC_CALLBACK;
  m_RDI.nImage     = IMG_DATA_FILE;              
  m_RDI.lParam     = reinterpret_cast<LPARAM>(this);

  m_dwAttributes   = 0;
  m_pParentFolder  = NULL;
  m_pCompData      = NULL;
  m_nPropPageCount = 1;      // Number of property pages this node supports
  m_nNotifyHandle  = 0;      // Cached notification handle (not used)
}

//---------------------------------------------------------------------------
CVirtualFile::~CVirtualFile()
{
}

//---------------------------------------------------------------------------
HRESULT CVirtualFile::Initialize( NODE_PROPERTIES* pNodeProps )
{
  _ASSERT( NULL != pNodeProps );
  _ASSERT( NULL != pNodeProps->pParentObject );

  SIZE_T   nLen  = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName  = pszTmp;
  m_pParentFolder = reinterpret_cast<CFolderNode*>(pNodeProps->pParentObject);
  m_pCompData     = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);
  m_dwAttributes  = pNodeProps->dwAttributes;

  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods

//---------------------------------------------------------------------------
HRESULT CVirtualFile::GetDisplayInfo
( 
  RESULTDATAITEM* pRDI       //[in-out] RESULTDATAITEM struct
)
{
  HRESULT hResult = S_OK;

  if( pRDI->mask & RDI_STR )         // Console is requesting strings...
  {                                  // for each column     
    switch( pRDI->nCol )
    {
      case 0:
        pRDI->str = m_pwszNodeName;
        break;

      case 1:                        // Return Attributes as string 
        pRDI->str = GetAttributeString();
        break;

      default:
        hResult = S_FALSE;
        TRACE_VAL(_T("GetDisplayInfo"), _T("Column"), pRDI->nCol );
        break;
    }
  }

  if( pRDI->mask & RDI_IMAGE )       // Looking for an image?
  {
    pRDI->nImage = m_RDI.nImage;
  }

  //TRACE_HRESULT(_T("GetDisplayInfo"), hResult );
  return hResult;
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods

//---------------------------------------------------------------------------
HRESULT CVirtualFile::OnSelect
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] Bools for context & selection state
  LPARAM        nParam,        //[in] Not used
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT hResult = S_FALSE;

  BOOL    fScopePane = LOWORD(nArg);
  BOOL    fSelected  = HIWORD(nArg);

  // Don't care about de-select notifications so just return
  if( FALSE == fSelected )
    return hResult;
  
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

  IConsoleVerb* ipConsoleVerb = NULL;
  hResult = pComp->GetInterface( REQUEST_ICONSOLEVERB, (LONG_PTR*)&ipConsoleVerb ); 
  if( S_OK != hResult )
   return hResult;              

  // Adding the Properties verb and making it the default
  hResult = ipConsoleVerb->SetVerbState( MMC_VERB_DELETE,     ENABLED, TRUE );
  hResult = ipConsoleVerb->SetVerbState( MMC_VERB_PROPERTIES, ENABLED, TRUE );

  hResult = ipConsoleVerb->SetDefaultVerb( MMC_VERB_PROPERTIES );

  TRACE_HRESULT(_T("OnSelect"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CVirtualFile::OnShow
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] TRUE if node was selcted
  LPARAM        nParam,        //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT  hResult = S_FALSE;

  TRACE_HRESULT(_T("OnShow"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CVirtualFile::OnDelete
( 
  LPDATAOBJECT ipDataObject,   //[in] Points to Data Object
  LPARAM       nArg,           //[in] Not used
  LPARAM       nParam,         //[in] Not used
  LONG_PTR     pComponent      //[in] Points to calling IComponent
)
{
  _ASSERT( NULL != ipDataObject );
  _ASSERT( NULL != m_pParentFolder );

  HRESULT hResult = S_FALSE;

  m_pParentFolder->RemoveVirtualFile( this );

  LPRESULTDATA ipResultData = NULL;
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData );
  if( S_OK != hResult )
    return hResult;

  ipResultData->DeleteItem( m_RDI.itemID, 0 );
  delete this;

  return hResult;
}

//---------------------------------------------------------------------------
//  MMC_HELP:  This gets called when a VirtualFile node is selected and
//  the F1 key is pressed.
//
HRESULT CVirtualFile::OnContextHelp
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] Not used
  LPARAM        nParam,        //[in] Not used
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT   hResult = S_FALSE;
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

  LPOLESTR pszBaseHelpPath  = GetHelpFilePath();
  LPOLESTR pszTopicPath     = L"::/VirtualFiles.html";

  // Allocate space for the topic string
  SIZE_T nBasePathLen  = wcslen( pszBaseHelpPath );
  SIZE_T nTopicPathLen = wcslen( pszTopicPath );
  SIZE_T nBufferSize   = (nBasePathLen + nTopicPathLen + 1) * sizeof(WCHAR);

  // Build the topic string
  LPOLESTR pszThisTopicPath = (LPOLESTR)CoTaskMemAlloc( nBufferSize ); 
  wcscpy( pszThisTopicPath, pszBaseHelpPath );
  wcscat( pszThisTopicPath, pszTopicPath );

  // Request a pointer to IDisplayHelp
  IDisplayHelp* ipDisplayHelp = NULL;
  pComp->GetInterface( REQUEST_IDISPLAYHELP, (LONG_PTR*)&ipDisplayHelp );

  hResult = ipDisplayHelp->ShowTopic( pszThisTopicPath );

  TRACE_HRESULT(_T("OnContextHelp"), hResult );   // Return value is not used
  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
//  IExtendContextMenu implementation

//---------------------------------------------------------------------------
HRESULT CVirtualFile::AddMenuItems
( 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  HRESULT hResult = E_NOTIMPL;
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CVirtualFile::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  HRESULT hResult = E_NOTIMPL;
  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
//  IExtendPropertySheet2 implementation

//---------------------------------------------------------------------------
//  Tell the console that this node supports property pages 
//
HRESULT CVirtualFile::QueryForPropertyPage()
{
  TRACE_HRESULT(_T("OnShow"), S_OK );
  return S_OK;
}


//---------------------------------------------------------------------------
HRESULT CVirtualFile::CreatePropertyPages
( 
  LPPROPERTYSHEETCALLBACK lpCallback,  //[in] Pointer to callback interface
  LONG_PTR                Handle       //[in] Routing handle
) 
{
  HRESULT hResult = S_FALSE;

  m_nNotifyHandle = Handle;            // Cache the routing handle

  // Create an array of PropertySheetPages
  HPROPSHEETPAGE* hPPages = new HPROPSHEETPAGE[m_nPropPageCount];
  if( NULL == hPPages )
    return E_OUTOFMEMORY;

  PROPSHEETPAGE  psp;

  psp.dwSize      = sizeof(PROPSHEETPAGE);
  psp.dwFlags     = PSP_DEFAULT | PSP_USETITLE | PSP_HASHELP;  
  psp.hInstance   = g_hInst;
  psp.pszTemplate = MAKEINTRESOURCE(IDD_VFILE_PPAGE0);
  psp.pfnDlgProc  = (DLGPROC)PPageWndProc0;
  psp.lParam      = reinterpret_cast<LPARAM>(this);            
  psp.pszTitle    = _T("General");   
  psp.pfnCallback = NULL;

  
  hPPages[0] = ::CreatePropertySheetPage( &psp );

  // Add the pages to the console's Property Sheet 
  for( LONG nPageCount = 0; nPageCount < m_nPropPageCount; nPageCount++ )
  {
    hResult = lpCallback->AddPage( hPPages[nPageCount] );
    BREAK_ON_ERROR( hResult );
  }

  delete [] hPPages;

  return hResult; 
}

//---------------------------------------------------------------------------
HRESULT CVirtualFile::GetWatermarks
( 
  HBITMAP __RPC_FAR*  lphWatermark,  //[out] Pointer to watermark bitmap
  HBITMAP __RPC_FAR*  lphHeader,     //[out] Pointer to header bitmap
  HPALETTE __RPC_FAR* lphPalette,    //[out] Pointer to palette
  BOOL __RPC_FAR*     bStretch       //[out] TRUE to stretch instead of tile
)
{
  HRESULT hResult = S_FALSE;


  return hResult;
}

//---------------------------------------------------------------------------
//
//
BOOL CALLBACK CVirtualFile::PPageWndProc0
(
  HWND    hPage,     //[in] Handle to property page
  UINT    uMsg,      //[in] Message
  WPARAM  wParam,    //[in] First message parameter
  LPARAM  lParam     //[in] Second message parameter
)
{
  static CVirtualFile* pVFile  = NULL;  
         BOOL          bReturn = FALSE;

  switch( uMsg )                       // Begin message switch
  {
    case WM_INITDIALOG:
    {
      // Cache the pointer to the calling instance of CVirtualFile and
      // call it's OnInitPropPage method
      PROPSHEETPAGE* psp = (PROPSHEETPAGE*)lParam;
      pVFile = reinterpret_cast<CVirtualFile*>(psp->lParam);
      pVFile->OnInitPropPage( hPage, wParam, lParam );
      break;
    }
    case WM_HELP:
    {
      LPOLESTR pszBasePath  = GetHelpFilePath(); 
      LPOLESTR pszTopicPath = L"::/WM_HELP.html";

      SIZE_T nBasePathLen  = wcslen( pszBasePath  );  
      SIZE_T nTopicPathLen = wcslen( pszTopicPath );
      SIZE_T nBufferSize   = (nBasePathLen + nTopicPathLen + 1) * sizeof(WCHAR);

      LPOLESTR pszThisTopicPath = (LPOLESTR)CoTaskMemAlloc( nBufferSize ); 
      wcscpy( pszThisTopicPath, pszBasePath  );
      wcscat( pszThisTopicPath, pszTopicPath );

      CoTaskMemFree( pszBasePath );

      MMCPropertyHelp( pszThisTopicPath );
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
      MMCFreeNotifyHandle( pVFile->m_nNotifyHandle );
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
          pVFile->OnApplyChanges( hPage, wParam, lParam );          
          return PSNRET_NOERROR;
        }
        case PSN_HELP:
        {
          LPOLESTR pszBasePath  = GetHelpFilePath(); 
          LPOLESTR pszTopicPath = L"::/PSN_HELP.html";

          SIZE_T nBasePathLen  = wcslen( pszBasePath  );  
          SIZE_T nTopicPathLen = wcslen( pszTopicPath );
          SIZE_T nBufferSize   = (nBasePathLen + nTopicPathLen + 1) * sizeof(WCHAR);

          LPOLESTR pszThisTopicPath = (LPOLESTR)CoTaskMemAlloc( nBufferSize ); 
          wcscpy( pszThisTopicPath, pszBasePath  );
          wcscat( pszThisTopicPath, pszTopicPath );

          CoTaskMemFree( pszBasePath );

          MMCPropertyHelp( pszThisTopicPath );
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
BOOL CVirtualFile::OnInitPropPage
(
  HWND     hPage,      //[in] Handle to Property Page
  WPARAM   wParam,     //[in] First message parameter
  LPARAM   lparam      //[in] Second message parameter
)
{
  LRESULT lResult = 0;

  HWND hArchiveCtrl  = GetDlgItem( hPage, IDC_ARCHIVE_ATTR  ); 
  HWND hHiddenCtrl   = GetDlgItem( hPage, IDC_HIDDEN_ATTR   );
  HWND hLockedCtrl   = GetDlgItem( hPage, IDC_LOCKED_ATTR   );
  HWND hReadOnlyCtrl = GetDlgItem( hPage, IDC_READONLY_ATTR );


  if( TRUE == IsAttributeSet( ATTRIBUTE_DATA_ARCHIVE ) )
    lResult = SendMessage( hArchiveCtrl,  BM_SETCHECK, BST_CHECKED, 0 );   

  if( TRUE == IsAttributeSet( ATTRIBUTE_DATA_HIDDEN ) )
    lResult = SendMessage( hHiddenCtrl,  BM_SETCHECK, BST_CHECKED, 0 );   

  if( TRUE == IsAttributeSet( ATTRIBUTE_DATA_LOCKED ) )
    lResult = SendMessage( hLockedCtrl,  BM_SETCHECK, BST_CHECKED, 0 );   

  if( TRUE == IsAttributeSet( ATTRIBUTE_DATA_READONLY ) )
    lResult = SendMessage( hReadOnlyCtrl,  BM_SETCHECK, BST_CHECKED, 0 );   

  return TRUE;
}

//---------------------------------------------------------------------------
BOOL CVirtualFile::OnApplyChanges
(
  HWND     hPage,      //[in] Handle to Property Page
  WPARAM   wParam,     //[in] First message parameter
  LPARAM   lparam      //[in] Second message parameter
)
{
  LRESULT lResult = 0;

  HWND hArchiveCtrl  = GetDlgItem( hPage, IDC_ARCHIVE_ATTR  ); 
  if( BST_CHECKED == SendMessage( hArchiveCtrl, BM_GETCHECK, 0, 0 ) )
    SetAttribute( ATTRIBUTE_DATA_ARCHIVE );
  else
    RemoveAttribute( ATTRIBUTE_DATA_ARCHIVE ); 

  HWND hHiddenCtrl   = GetDlgItem( hPage, IDC_HIDDEN_ATTR   );
  if( BST_CHECKED == SendMessage( hHiddenCtrl, BM_GETCHECK, 0, 0 ) )
    SetAttribute( ATTRIBUTE_DATA_HIDDEN );
  else
    RemoveAttribute( ATTRIBUTE_DATA_HIDDEN ); 

  HWND hLockedCtrl   = GetDlgItem( hPage, IDC_LOCKED_ATTR   );
  if( BST_CHECKED == SendMessage( hLockedCtrl, BM_GETCHECK, 0, 0 ) )
    SetAttribute( ATTRIBUTE_DATA_LOCKED );
  else
    RemoveAttribute( ATTRIBUTE_DATA_LOCKED ); 

  HWND hReadOnlyCtrl   = GetDlgItem( hPage, IDC_READONLY_ATTR   );
  if( BST_CHECKED == SendMessage( hReadOnlyCtrl, BM_GETCHECK, 0, 0 ) )
    SetAttribute( ATTRIBUTE_DATA_READONLY );
  else
    RemoveAttribute( ATTRIBUTE_DATA_READONLY ); 

  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
//  CVirtualFile methods

//---------------------------------------------------------------------------
BOOL CVirtualFile::IsAttributeSet
( 
  DWORD dwAttribute           //[in] Attribute to set
)
{
  return (m_dwAttributes & dwAttribute) ? TRUE : FALSE;
}

//---------------------------------------------------------------------------
VOID CVirtualFile::SetAttribute
( 
  DWORD dwAttribute           //[in] Attribute to set
)
{
  m_dwAttributes |= dwAttribute;
}

//---------------------------------------------------------------------------
VOID CVirtualFile::RemoveAttribute
( 
  DWORD dwAttribute           //[in] Attribute to remove
)
{
  m_dwAttributes &= ~dwAttribute;
}

//---------------------------------------------------------------------------
//
LPWSTR CVirtualFile::GetAttributeString()
{
  *m_pAttributeStr = NULL;
  
  if( IsAttributeSet(ATTRIBUTE_DATA_ARCHIVE) )
    wcscat( m_pAttributeStr, L"A " );

  if( IsAttributeSet(ATTRIBUTE_DATA_HIDDEN) )
    wcscat( m_pAttributeStr, L"H " );

  if( IsAttributeSet(ATTRIBUTE_DATA_LOCKED) )
    wcscat( m_pAttributeStr, L"L " );

  if( IsAttributeSet(ATTRIBUTE_DATA_READONLY) )
    wcscat( m_pAttributeStr, L"R " );

  return m_pAttributeStr;
}


