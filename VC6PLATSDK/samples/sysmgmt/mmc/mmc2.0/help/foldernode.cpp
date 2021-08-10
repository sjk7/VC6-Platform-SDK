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
//  Abstract:     Implementation of the CFolderNode class.
//


#include "FolderNode.h"
#include "CompData.h"
#include "Comp.h"
#include "AddVFileDlg.h"
                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CFolderNode")


// Initialize our static GUID just once
GUID CFolderNode::thisGUID = CLSID_CFolderNode;   


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CFolderNode::CFolderNode()
{
  m_SDI.mask        = DEFAULT_SDI_MASK;
  m_SDI.displayname = MMC_CALLBACK;
  m_SDI.nImage      = IMG_FOLDER_DEFAULT;              
  m_SDI.nOpenImage  = IMG_FOLDER_DEFAULT;
  m_SDI.cChildren   = 0;              // Determines if the '+' is displayed
  m_SDI.lParam      = reinterpret_cast<LPARAM>(this);

  m_dwAttributes    = 0;
  m_pCompData       = NULL;
  m_hAddVFileDlg    = NULL;
  m_hMessageWnd     = NULL;

}

CFolderNode::~CFolderNode()
{
}

//---------------------------------------------------------------------------
//  This node does not need to call it's parent so we can ignore
//  pNodeProps->pParentObject
//
HRESULT CFolderNode::Initialize( NODE_PROPERTIES* pNodeProps )
{
  _ASSERT( NULL != pNodeProps );
  HRESULT hResult = S_FALSE;

  SIZE_T  nLen   = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName = pszTmp;
  m_pCompData = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);

  RefreshNodeList();         // Create Result Item nodes

  // We create a hidden window to allow us to communicate with modeless
  // dialogs and other things which run in a seperate thread.

  WNDCLASS wc;
  ZeroMemory (&wc, sizeof(WNDCLASS));
  wc.cbWndExtra    = sizeof(this);
  wc.lpfnWndProc   = FolderNodeWndProc;
  wc.hInstance     = g_hInst;   
  wc.lpszClassName = _T("FolderNodeMsgWnd");

  RegisterClass( &wc );
  m_hMessageWnd = CreateWindow( _T("FolderNodeMsgWnd"), NULL, 
                                0, 0, 0, 0, 0, NULL, 0, g_hInst, this);

  if( NULL == m_hMessageWnd )
    hResult = S_FALSE;  

  return hResult;
}

//---------------------------------------------------------------------------
//  This is our hidden window which is just used for handling messages.  We
//  go to all this trouble so that we don't ever pass interface pointers or
//  other objects across threads.
//
LRESULT CALLBACK CFolderNode::FolderNodeWndProc
( 
  HWND   hWnd,     //[in] Handle to window
  UINT   uMsg,     //[in] Message identifier
  WPARAM wParam,   //[in] First message parameter
  LPARAM lParam    //[in] Second message parameter
)
{
  switch( uMsg )
  {
    case WM_CREATE:
    {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      SetWindowLongPtr( hWnd, 0, (LONG_PTR)lpcs->lpCreateParams );
      break;
    }

    case WM_ADD_VIRTUALFILE:
    {
      CFolderNode* pThisNode = (CFolderNode*)GetWindowLongPtr( hWnd, 0 );
      NODE_PROPERTIES* pProps = (NODE_PROPERTIES*)wParam;
      pThisNode->AddVirtualFile( pProps );
      break;
    }

    case WM_VIRTUALFILE_CLOSED:
    {
      CFolderNode* pThisNode = (CFolderNode*)GetWindowLongPtr( hWnd, 0 );
      pThisNode->m_hAddVFileDlg = NULL; 
    }
    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
  }
  return 0;  
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods

//---------------------------------------------------------------------------
HRESULT CFolderNode::GetResultViewType2
( 
  MMC_COOKIE             nCookie,  //[in] Identifier of object
  PRESULT_VIEW_TYPE_INFO pRVTinfo  //[in,out] ViewTypeInfo struct
)    
{
  LPOLESTR pszDescStr = (LPOLESTR)CoTaskMemAlloc( sizeof(L"DefaultListView")+1 );
  if( NULL == pszDescStr )
    return E_OUTOFMEMORY;      

  wcscpy( pszDescStr, L"DefaultListView" );
  pRVTinfo->pstrPersistableViewDescription = pszDescStr;

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::GetDisplayInfo
( 
  SCOPEDATAITEM* pSDI        //[in][out] Points to SCOPEDATAITEM
)
{
  _ASSERT( NULL != pSDI );
  pSDI->displayname = m_pwszNodeName;

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::GetDisplayInfo
( 
  RESULTDATAITEM* pRDI
)
{
  _ASSERT( NULL != pRDI );

  HRESULT hResult = S_OK;

  if( pRDI->mask & RDI_STR )         // Console is requesting strings...
  {                                  // for each column     
    switch( pRDI->nCol )
    {
      case 0:
        pRDI->str = m_pwszNodeName;
        break;

      case 1:                        // Attributes not supported yet
        pRDI->str = L"No attributes";
        break;

      default:
        hResult = S_FALSE;
        TRACE_VAL(_T("GetDisplayInfo"), _T("Column"), pRDI->nCol );
        break;
    }
  }
  if( pRDI->mask & RDI_IMAGE )       // Looking for an image?
  {
    pRDI->nImage = m_SDI.nImage;
  }

  TRACE_HRESULT(_T("GetDisplayInfo"), hResult );
  return hResult;

}

/////////////////////////////////////////////////////////////////////////////
// Implementation of notification handlers


//---------------------------------------------------------------------------
HRESULT CFolderNode::OnSelect
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] Bools for context & selection state
  LPARAM        nParam,        //[in] Not used
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT hResult = S_FALSE;

  // Not setting verbs for this node

  TRACE_HRESULT(_T("OnSelect"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CFolderNode::OnShow
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] TRUE if node was selcted
  LPARAM        nParam,        //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT  hResult = S_FALSE;

  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

  LPHEADERCTRL2  ipHeaderCtrl2 = NULL;
  hResult = pComp->GetInterface( REQUEST_IHEADERCTRL2, (LONG_PTR*)&ipHeaderCtrl2 ); 
  if( S_OK != hResult )
   return hResult;              

  LPRESULTDATA  ipResultData = NULL;
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData ); 
  if( S_OK != hResult )
   return hResult;              


  if( TRUE == nArg )         // Selecting a scope node
  {
    do                                 
    {                                  
      hResult = ipHeaderCtrl2->InsertColumn( 0, L"File Name", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipHeaderCtrl2->InsertColumn( 1, L"Attributes", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipResultData->ModifyViewStyle( MMC_NOSORTHEADER, (MMC_RESULT_VIEW_STYLE)NULL );      
      BREAK_ON_ERROR( hResult );

      hResult = EnumerateResultItems( ipResultData );
      BREAK_ON_ERROR( hResult );

    }while(0);
  }
  else                       // Clean up result items on deselection
  {
    hResult = ipResultData->DeleteAllRsltItems();
  }

  TRACE_HRESULT(_T("OnShow"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::OnExpand
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_FALSE;

  if( NULL == m_pCompData )
    m_pCompData = reinterpret_cast<CComponentData*>(pCompData);


  TRACE_HRESULT( _T("OnExpand"), hResult );
  return hResult;              // Not expanding anything
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::OnRemoveChildren
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_OK;      // Just delete our child nodes, the
                               // corresponding result items are cleaned
  RemoveNodes();               // up in MMCN_SHOW -> FALSE

  TRACE_HRESULT( _T("OnRemoveChildren"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::OnViewChange
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pComponent    //[in] Points to calling IComponent 
)
{
  HRESULT hResult = S_FALSE;
  LPRESULTDATA ipResultData = NULL;

  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData );
  if( S_OK != hResult )
    return hResult;  

  hResult = EnumerateResultItems( ipResultData );

  TRACE_HRESULT( _T("OnViewChange"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
//  MMC_HELP:  This gets called when a FolderNode is selected and
//  the F1 key is pressed.
//
HRESULT CFolderNode::OnContextHelp
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
  LPOLESTR pszTopicPath     = L"::/FolderNodes.html";

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
//  Support for Context Menus

//---------------------------------------------------------------------------
HRESULT CFolderNode::AddMenuItems
( 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  _ASSERT( NULL != ipCallback );
  HRESULT hResult = S_FALSE;

  static CONTEXTMENUITEM ctxMenu;           
    ctxMenu.lCommandID        = IDM_NEW_VIRTFILE;
    ctxMenu.lInsertionPointID = CCM_INSERTIONPOINTID_PRIMARY_NEW; 
    ctxMenu.fSpecialFlags     = 0;
    ctxMenu.strName           = L"New Virtual File...";
    ctxMenu.strStatusBarText  = L"Add a new virtual file";

  
  if( NULL == m_hAddVFileDlg )     // If the AddVFile dialog is running
    ctxMenu.fFlags = 0;            // gray the menu selection
  else
    ctxMenu.fFlags = MF_GRAYED;   


  // Add the 'New Device' option to the New menu if allowed... 
  if( CCM_INSERTIONALLOWED_NEW & *pInsertionAllowed )
  {
    hResult = ipCallback->AddItem( &ctxMenu );
  } 

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  HRESULT hResult = S_OK;

  switch( lCommandID )
  {
    case IDM_NEW_VIRTFILE:
    {
      CAddVFileDlg* pDlg = new CAddVFileDlg( IDD_ADDVFILE_DLG, m_hMessageWnd );
      m_hAddVFileDlg = pDlg->Create( g_hInst, GetDesktopWindow(), 0 );
      break;
    }
    default:
    {
      hResult = S_FALSE;
      break;
    }
  }
  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
//  Private helpers

//---------------------------------------------------------------------------
HRESULT CFolderNode::RefreshNodeList()
{
  NODE_PROPERTIES NodeProps;
  ZeroMemory( &NodeProps, sizeof(NODE_PROPERTIES) );
  NodeProps.pParentObject  = reinterpret_cast<LONG_PTR>(this);
  NodeProps.pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);
  NodeProps.dwAttributes   = 0;

  WCHAR  szNames[1][32];
  wcscpy( szNames[0], L"Virtual File 1" );

  RemoveNodes();             // Clean the node list

  CVirtualFile* pNode = NULL;
  for( DWORD i = 0; i < 1; i++ )
  {
    wcscpy( NodeProps.szNodeName, szNames[i] ); 
    pNode = new CVirtualFile;
    pNode->Initialize( &NodeProps );
    m_NodeList.AddTail( pNode );
  }

  return S_OK;
}

//---------------------------------------------------------------------------
VOID CFolderNode::RemoveNodes()
{
  CVirtualFile* pNode = NULL;
  POSITION   Pos   = m_NodeList.GetHeadPosition();
  while( Pos )
  {
    pNode = m_NodeList.GetNext( Pos );
    delete pNode;
  }
  m_NodeList.RemoveAll();              // Clean the list
}

//---------------------------------------------------------------------------
VOID CFolderNode::RemoveVirtualFile
( 
  CVirtualFile* pDeadNode    //[in] CVirtualFile to remove from list
)
{
  CVirtualFile* pNode = NULL;
  POSITION     NewPos = m_NodeList.GetHeadPosition();
  POSITION     OldPos = NULL;
  while( NewPos )
  {
    OldPos = NewPos;                   // Need to save this
    pNode = m_NodeList.GetNext( NewPos );
    if( pNode == pDeadNode )
    {
      m_NodeList.RemoveAt( OldPos );
      continue;                        // Exit, found it
    }
  }
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::AddVirtualFile
(
  NODE_PROPERTIES* pProps    //[in] Properties of new node
)
{
  _ASSERT( NULL != pProps );
  HRESULT hResult = S_FALSE;

  pProps->pParentObject  = reinterpret_cast<LONG_PTR>(this);
  pProps->pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);

  CVirtualFile* pNode = NULL;
  pNode = new CVirtualFile;
  pNode->Initialize( pProps );
  m_NodeList.AddTail( pNode );

  LPCONSOLE3 ipConsole = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole );
  if( S_OK != hResult )
    return hResult; 

  LPDATAOBJECT pDO = NULL;
  m_pCompData->QueryDataObject( (MMC_COOKIE)this, CCT_SCOPE, &pDO );

  ipConsole->UpdateAllViews( pDO, 0, 0 );
  pDO->Release();
  
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CFolderNode::EnumerateResultItems
( 
  LPRESULTDATA ipResultData  //[in] Points to cached IResultData
)
{
  _ASSERT( NULL != ipResultData );
  HRESULT hResult = S_FALSE;

  hResult = ipResultData->DeleteAllRsltItems();

  CVirtualFile*  pNode = NULL;
  POSITION       Pos   = m_NodeList.GetHeadPosition();
  while( Pos )
  {                                       
    pNode = m_NodeList.GetNext( Pos );   
    hResult = ipResultData->InsertItem( &pNode->m_RDI );
  }

  return hResult; 
}
