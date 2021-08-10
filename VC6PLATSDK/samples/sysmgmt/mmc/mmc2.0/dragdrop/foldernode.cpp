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
#include "DataObj.h"
#include "DeviceNode.h"
#include "VirtualFIle.h"
                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CFolderNode")


// Initialize our static GUID just once
GUID CFolderNode::thisGUID = CLSID_CFolderNode;   


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

//---------------------------------------------------------------------------
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
  m_pParentNode     = NULL;
}

//---------------------------------------------------------------------------
CFolderNode::~CFolderNode()
{
  RemoveNodes();             // Remove children if we are being deleted
  
  if( NULL != m_hMessageWnd )
    DestroyWindow( m_hMessageWnd );
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::Initialize
( 
  LPNODEPROPS  pNodeProps    //[in] Properties of this node
)
{
  _ASSERT( NULL != pNodeProps );
  HRESULT hResult = S_OK;

  UINT   nLen   = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName = pszTmp;
  m_pCompData    = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);
  m_pParentNode  = reinterpret_cast<CDeviceNode*>(pNodeProps->pParentObject);  

  CVirtualFile* pNode  = NULL;
  LONG  nChildCount    = pNodeProps->nChildCount;
  LPCHILDPROPS pChProp = &pNodeProps->pChildProps;
  BYTE* pCounter = (BYTE*)pChProp;
 
  if( INIT_DEFAULT_NODE == pNodeProps->nChildCount )
  {
    InitDefaultVFile();
  }  
  else
  {
    pNodeProps->pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);
    pNodeProps->pParentObject  = reinterpret_cast<LONG_PTR>(this);
    pNodeProps->nChildCount    = 0;

    // Create a new VirtualFile node for each ChildProperties struct
    // in the array
    // 
    for( LONG nCount = 0; nCount < nChildCount; nCount++ )
    {
      wcscpy( pNodeProps->szNodeName, pChProp->szNodeName );
      pNodeProps->dwAttributes = pChProp->dwAttributes;
      pNode = new CVirtualFile;
      pNode->Initialize( pNodeProps );
      m_NodeList.AddTail( pNode );
      pCounter += sizeof(CHILDPROPS);
      pChProp = (LPCHILDPROPS)pCounter;
    }
  }  

  // We create a hidden window to allow us to communicate with modeless
  // dialogs and other objects which run in a seperate thread.
  //
  WNDCLASS wc;
  ZeroMemory(&wc, sizeof(WNDCLASS));
  wc.cbWndExtra    = sizeof(this);
  wc.lpfnWndProc   = FolderNodeWndProc;
  wc.hInstance     = g_hInst;   
  wc.lpszClassName = _T("FolderNodeMessageWindow");

  RegisterClass( &wc );
  m_hMessageWnd = CreateWindow( _T("FolderNodeMessageWindow"), NULL, 
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
      break;
    }
    default:
      return DefWindowProc( hWnd, uMsg, wParam, lParam );
  }
  return 0;  
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods


//---------------------------------------------------------------------------
//  DRAGDROP:  This method supports the CCF_NODEPROP_PTR clipboard format.
//             The Node Properties struct is allocated in global memory so
//             so that interproccess CUT/COPY/PASTE will work.
//             The caller is responsible for freeing the memory.
//
HRESULT CFolderNode::GetProperties
( 
  LPNODEPROPS* ppNodeProps   //[out] Properties of this node 
)
{
  _ASSERT( NULL == *ppNodeProps );

  LONG nChildCount = m_NodeList.GetCount();
  LONG nBlockSize  = (nChildCount * sizeof(CHILDPROPS)) + sizeof(NODEPROPS);

  HGLOBAL hMemBlock = NULL;
  hMemBlock = ::GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, nBlockSize );
  if( NULL == hMemBlock )
    return E_OUTOFMEMORY;

  hMemBlock = ::GlobalLock( hMemBlock ); 
  LPNODEPROPS pTmpProps = (LPNODEPROPS)hMemBlock;
  
  ZeroMemory( pTmpProps, nBlockSize );
  wcscpy( pTmpProps->szNodeName,  m_pwszNodeName );
  pTmpProps->pComponentData = NULL;        // Pointers not used for DragDrop
  pTmpProps->pParentObject  = NULL;
  pTmpProps->dwAttributes   = m_dwAttributes;         
  pTmpProps->nChildCount    = nChildCount;
  pTmpProps->nBlockSize     = nBlockSize;

  LPCHILDPROPS pChProps = &pTmpProps->pChildProps;
  BYTE* pCounter = (BYTE*)&pTmpProps->pChildProps;

  CVirtualFile* pNode = NULL;
  POSITION   Pos = m_NodeList.GetHeadPosition();
  while( Pos )
  {
    pNode = m_NodeList.GetNext( Pos );
    wcscpy( pChProps->szNodeName, pNode->GetNodeName() );
    pChProps->dwAttributes = pNode->GetAttributes();
    pCounter += sizeof(CHILDPROPS);    // Next element in the array  
    pChProps = (LPCHILDPROPS)pCounter;
  }

  ::GlobalUnlock( hMemBlock );
  *ppNodeProps = (LPNODEPROPS)hMemBlock;
  
  return S_OK;
}

//---------------------------------------------------------------------------
//  The minimum implementation of this method is to return the
//  Persistable View Description string.  This string must be allocated
//  with CoTaskMemAlloc.  The console will free the string.
//
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

  pRVTinfo->eViewType     = MMC_VIEW_TYPE_LIST;
  pRVTinfo->dwListOptions = RVTI_LIST_OPTIONS_ALLOWPASTE;

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

  //TRACE_HRESULT(_T("GetDisplayInfo"), hResult );
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
  HRESULT hResult    = S_FALSE;
  BOOL    fScopePane = LOWORD(nArg);
  BOOL    fSelected  = HIWORD(nArg); 

  if( TRUE == fSelected )
  {
    CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

    IConsoleVerb* ipConsoleVerb = NULL;
    hResult = pComp->GetInterface( REQUEST_ICONSOLEVERB, (LONG_PTR*)&ipConsoleVerb ); 

    // DRAGDROP: Add MMC_VERB_CUT/COPY/PASTE for this object only
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_CUT,   ENABLED, TRUE );
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_COPY,  ENABLED, TRUE );
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_PASTE, ENABLED, TRUE );

    // Enable Rename as well
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_RENAME, ENABLED, TRUE );
  }
 
  //TRACE_HRESULT(_T("OnSelect"), hResult );
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

  LPHEADERCTRL2  ipHeaderCtrl = NULL;
  hResult = pComp->GetInterface( REQUEST_IHEADERCTRL, (LONG_PTR*)&ipHeaderCtrl ); 
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
      hResult = ipHeaderCtrl->InsertColumn( 0, L"File Name", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipHeaderCtrl->InsertColumn( 1, L"Attributes", 0, 150 );
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

  //TRACE_HRESULT(_T("OnShow"), hResult );
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

  //TRACE_HRESULT( _T("OnExpand"), hResult );
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

  //TRACE_HRESULT( _T("OnRemoveChildren"), hResult );
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

  LONG_PTR pScopeCookie = pComp->GetScopeCookie();

  if( pScopeCookie == (LONG_PTR)this )
    hResult = EnumerateResultItems( ipResultData );

  //TRACE_HRESULT( _T("OnViewChange"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
//  This message must return S_OK to allow the rename.  Anything else will
//  disallow the rename
//
HRESULT CFolderNode::OnRename
( 
  LPDATAOBJECT ipDataObject,   //[in] Points to Data Object
  LPARAM       nArg,           //[in] Not used
  LPARAM       nParam,         //[in] Pointer to the new name
  LONG_PTR     pCompData       //[in] Points to calling IComponentData
)
{
  _ASSERT( NULL != ipDataObject );
  HRESULT hResult = S_OK;

  LPWSTR pszTmpName = NULL;
  LPWSTR pszNewName = (LPWSTR)nParam;  // New name
  LONG   nLen = wcslen( pszNewName ) + 1;

  pszTmpName = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  if( NULL == pszTmpName )
  { 
    hResult = S_FALSE;                 // Can't change the name
  }
  else
  {
    wcscpy( pszTmpName, pszNewName );
    CoTaskMemFree( m_pwszNodeName );   // Free existing name...
    m_pwszNodeName = pszTmpName;       // Assign new name to pointer        
  }
  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
// DRAGDROP: Notifications which support DragDrop

//---------------------------------------------------------------------------
//  MMC20: nParam has changed to a DWORD* which can be used to specify
//         the default behaviour of DragDrop
//
HRESULT CFolderNode::OnQueryPaste
( 
  LPDATAOBJECT ipDataObject,   //[in] Data object of the selected node
  LPARAM       nArg,           //[in] Data object of node to be pasted
  LPARAM       nParam,         //[in] DWORD* which specifies default operation
  LONG_PTR     pComponent      //[in] Points to calling IComponent 
)
{
  _ASSERT( NULL != nArg );
  ULONG nTypeFlag = ExtractNodeTypeFlg( reinterpret_cast<LPDATAOBJECT>(nArg) );
  return (NODETYPE_VFILE == nTypeFlag) ? S_OK : S_FALSE;
} 

//---------------------------------------------------------------------------
//  DRAGDROP: This implementation always creates a new node object, and
//            depending on whether we got a cut or copy flag in nParam,
//            pass on the info so the source node can delete itself.
//            We also have to assume the source DataObject is out-of-proc
//            so we can't convert it to a CDataObject.
//
HRESULT CFolderNode::OnPaste
( 
  LPDATAOBJECT ipDataObject,   //[in] Data object of the destination node
  LPARAM       nArg,           //[in] Data object of the source node
  LPARAM       nParam,         //[in] NULL for copy, data object for cut
  LONG_PTR     pComponent      //[in] Points to calling IComponent 
)
{
  _ASSERT( NULL != nArg );
  _ASSERT( NULL != pComponent );

  HRESULT hResult = S_FALSE;
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  LPDATAOBJECT ipSourceDO = reinterpret_cast<LPDATAOBJECT>(nArg);

  do
  {
    // Test to see if the data object supports the clipformat we need
    FORMATETC NodePropFormatEtc = NP_FORMATETC;
    hResult = ipSourceDO->QueryGetData( &NodePropFormatEtc );
    BREAK_ON_ERROR( hResult );

    STGMEDIUM StgMedium = {TYMED_HGLOBAL, NULL};
    hResult = ipSourceDO->GetData( &NodePropFormatEtc, &StgMedium );
    BREAK_ON_ERROR( hResult );

    NODE_PROPERTIES* pNodeProps = NULL;
    pNodeProps = (NODE_PROPERTIES*)::GlobalLock( StgMedium.hGlobal );

    // Set variables which must be local
    pNodeProps->pParentObject  = reinterpret_cast<LONG_PTR>(this);
    pNodeProps->pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);

    // Now add the new node
    CVirtualFile* pNode = NULL;
    pNode = new CVirtualFile;
    pNode->Initialize( pNodeProps );
    m_NodeList.AddTail( pNode );

    // Now do some housekeeping, and test that everything went OK....
    BOOL    bStatus = ::GlobalUnlock( StgMedium.hGlobal );
    HGLOBAL hReturn = ::GlobalFree( StgMedium.hGlobal );
    _ASSERT( NULL == hReturn );

    if( NULL != nParam )
    {
      // We must AddRef it becuase MMC will release it once when we 
      // return, and again when CFolderNode::OnCutOrMove returns.      
      //
      BOOL* pbPasted = reinterpret_cast<BOOL*>(nParam);
      ULONG nCount = ipSourceDO->AddRef();      
      *pbPasted = reinterpret_cast<BOOL>(ipSourceDO);   
    }
 
    // Force ourself to be selected so the new result items
    // will be displayed
    //   
//    LPCONSOLE3 ipConsole3 = NULL;
//    hResult = m_pCompData->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole3 );
//    hResult = ipConsole3->SelectScopeItem( m_SDI.ID );

	  LPCONSOLE3 ipConsole3 = NULL;
	  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole3 );
	  if( S_OK != hResult )
		return hResult; 

	  hResult = ipConsole3->UpdateAllViews( ipDataObject, 0, (LONG_PTR)this );
  }while(0);       

  return hResult;
} 

//---------------------------------------------------------------------------
// DRAGDROP:  This notification is where we delete ourselves.
//
HRESULT CFolderNode::OnCutOrMove
( 
  LPDATAOBJECT ipDataObject,   //[in] NULL
  LPARAM       nArg,           //[in] Pointer to the data object
  LPARAM       nParam,         //[in] Not used
  LONG_PTR     pComponent      //[in] Points to calling IComponent 
)
{
  _ASSERT( NULL != m_pParentNode );
  _ASSERT( NULL != m_pCompData );
  HRESULT hResult = S_FALSE;

  LPCONSOLENAMESPACE2 ipCNS = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLENAMESPACE, (LONG_PTR*)&ipCNS );
  hResult = ipCNS->DeleteItem( m_SDI.ID, TRUE );  

  m_pParentNode->RemoveChildNode( (LONG_PTR)this );  

  delete this;               // Now we can delete ourselves

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
//  Helper methods

//---------------------------------------------------------------------------
//  This is called by a child node to have itself removed from the list
//  of child nodes.  The node itself is not deleted, the child node will
//  delete itself when this function returns.
//
VOID CFolderNode::RemoveChildNode
( 
  LONG_PTR pChildNode    //[in] Child node to remove from list
)
{
  CVirtualFile* pNode  = NULL;
  CVirtualFile* pChild = reinterpret_cast<CVirtualFile*>(pChildNode);
  POSITION      NewPos = m_NodeList.GetHeadPosition();
  POSITION      OldPos = NULL;
  while( NewPos )
  {
    OldPos = NewPos;                   // Need to save this
    pNode = m_NodeList.GetNext( NewPos );
    if( pNode == pChild )
    {
      m_NodeList.RemoveAt( OldPos );
      continue;                        // Exit, found it
    }
  }
}


//---------------------------------------------------------------------------
// Creates a default Virtual File
//
HRESULT CFolderNode::InitDefaultVFile()
{
  NODE_PROPERTIES NodeProps;
  NodeProps.pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);
  NodeProps.pParentObject  = reinterpret_cast<LONG_PTR>(this);
  NodeProps.dwAttributes   = ATTRIBUTE_DATA_ARCHIVE;

  RemoveNodes();             // Clean the node list

  CVirtualFile* pNode = NULL;
  wcscpy( NodeProps.szNodeName, gwszVFILE_NODE_NAME ); 
  pNode = new CVirtualFile;
  pNode->Initialize( &NodeProps );
  m_NodeList.AddTail( pNode );

  return S_OK;
}

//---------------------------------------------------------------------------
//  This is only called to cleanup when we are being deleted
//
VOID CFolderNode::RemoveNodes()
{
  CVirtualFile* pNode = NULL;
  POSITION   Pos = m_NodeList.GetHeadPosition();
  while( Pos )
  {
    pNode = m_NodeList.GetNext( Pos );
    delete pNode;
  }
  m_NodeList.RemoveAll();              // Clean the list
}


//---------------------------------------------------------------------------
//  This is where OOP gets to be fun.
//  We use the NodeProperties pointer which originally came from the 
//  modeless AddVFileDlg, by way of our hidden window, to create a new
//  Virtual File node and add it to our linked list.
//  This by itself will not cause the new node to be displayed.  To do
//  that we need to call IResultData::InsertItem().  However we don't
//  have a way to get that pointer.  So we have to be indirect.  We call 
//  IComponentData::QueryDataObject() to create a data object.  The data
//  object points back to this node.  We can then pass that to 
//  IConsole2::UpdateAllViews().  This makes sure all instances of 
//  IComponent are called (there may me several running).  Then the 
//  MMCN_VIEW_CHANGE notification is delegated back to this node, along
//  with a pointer to the correct IComponent.  With this pointer we can
//  call GetInterface() to get an IResultData pointer which we can then
//  pass to EnumerateResultItems() to display the new Virtual File.
//
HRESULT CFolderNode::AddVirtualFile
(
  LPNODEPROPS pNodeProps     //[in] Properties of new node
)
{
  _ASSERT( NULL != pNodeProps );
  HRESULT hResult = S_FALSE;

  pNodeProps->pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);
  pNodeProps->pParentObject  = reinterpret_cast<LONG_PTR>(this);

  CVirtualFile* pNode = NULL;
  pNode = new CVirtualFile;
  pNode->Initialize( pNodeProps );
  m_NodeList.AddTail( pNode );

  LPCONSOLE3 ipConsole3 = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole3 );
  if( S_OK != hResult )
    return hResult; 

  LPDATAOBJECT pDO = NULL;
  m_pCompData->QueryDataObject( (MMC_COOKIE)this, CCT_SCOPE, &pDO );

  hResult = ipConsole3->UpdateAllViews( pDO, 0, 0 );
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
  HRESULT hResult = S_OK;

  if( FALSE == m_NodeList.IsEmpty() )
    hResult = ipResultData->DeleteAllRsltItems();

  if( S_OK == hResult )  
  {
    CVirtualFile*  pNode = NULL;
    POSITION       Pos   = m_NodeList.GetHeadPosition();
    while( Pos )
    {                                       
      pNode = m_NodeList.GetNext( Pos );   
      hResult = ipResultData->InsertItem( &pNode->m_RDI );
      _ASSERT( S_OK == hResult );
    }
  }

  //TRACE_HRESULT( _T("EnumerateResultItems"), hResult );
  return hResult; 
}

