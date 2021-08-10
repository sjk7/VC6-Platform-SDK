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
//  Abstract:     Implementation of the CStaticNode class.
//

#include "StaticNode.h"
#include "DeviceNode.h"
#include "CompData.h"
#include "Comp.h"
#include "AddDeviceDlg.h"

                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CStaticNode")


// Initialize our static GUID just once.  We use the GUID for 
// CComponentData because this node handles events for the 
// Snap-in's namespace
GUID CStaticNode::m_thisGUID = CLSID_CComponentData;


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

//---------------------------------------------------------------------------
CStaticNode::CStaticNode()
{
  m_SDI.mask        = DEFAULT_SDI_MASK;
  m_SDI.displayname = MMC_CALLBACK;
  m_SDI.nImage      = IMG_DEVICE_DEFAULT;             
  m_SDI.nOpenImage  = IMG_DEVICE_DEFAULT;
  m_SDI.cChildren   = 1;              // Determines if the '+' is displayed
  m_SDI.lParam      = reinterpret_cast<LPARAM>(this);

  m_hStaticNode     = NULL;
  m_pCompData       = NULL;
  m_hAddDeviceDlg   = NULL;
}

//---------------------------------------------------------------------------
CStaticNode::~CStaticNode()
{
  if( NULL != m_hMessageWnd )
    DestroyWindow( m_hMessageWnd );
}

//---------------------------------------------------------------------------
HRESULT CStaticNode::Initialize( NODE_PROPERTIES* pNodeProps )
{
  _ASSERT( NULL != pNodeProps );
  _ASSERT( NULL != pNodeProps->pComponentData );

  HRESULT hResult = S_FALSE;

  UINT   nLen   = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName = pszTmp;
  m_pCompData = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);

  hResult = RefreshNodeList();         // Initialize scope nodes

  // We create a hidden window to allow us to communicate with modeless
  // dialogs and other things which run in a seperate thread.

  WNDCLASS wc;
  ZeroMemory (&wc, sizeof(WNDCLASS));
  wc.cbWndExtra    = sizeof(this);
  wc.lpfnWndProc   = StaticNodeWndProc;
  wc.hInstance     = g_hInst;   
  wc.lpszClassName = _T("StaticNodeMessageWindow");

  RegisterClass( &wc );
  m_hMessageWnd = CreateWindow( _T("StaticNodeMessageWindow"), NULL, 
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
LRESULT CALLBACK CStaticNode::StaticNodeWndProc
( 
  HWND   hWnd,     //[in] Handle to window
  UINT   uMsg,     //[in] Message identifier
  WPARAM wParam,   //[in] First message parameter
  LPARAM lParam    //[in] Second message parameter
)
{
  switch( uMsg )
  {
    // Since we registered the WndClass in Initialize, our WndProc will be
    // called with WM_CREATE right away.  Store our 'hWnd' pointer in the
    // CREATESTRUCT so we can retreive it later to get back to the specific 
    // instance of CComponentData
    //
    case WM_CREATE:
    {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      SetWindowLongPtr( hWnd, 0, (LONG_PTR)lpcs->lpCreateParams );
      break;
    }

    // This is our custom message which could have been sent from a worker
    // thread, or in this case a modeless dialog.  We retrieve our 'this'
    // pointer from the WndClass and cast it to a CComponentData pointer.
    // WPARAM is cast to a NODE_PROPERTIES struct which can be used to 
    // call AddDeviceNode() 
    //
    case WM_ADDNEW_NODE:
    {
      CStaticNode* pThisNode = (CStaticNode*)GetWindowLongPtr( hWnd, 0 );
      NODE_PROPERTIES* pProps = (NODE_PROPERTIES*)wParam;
      pThisNode->AddDeviceNode( pProps );
      break;
    }

    // This message is sent by the AddDeviceDlg to let us know it's 
    // being terminated.  Set our member handle to NULL so the item
    // will be show on the context menu
    // 
    case WM_DIALOG_CLOSED:
    {
      CStaticNode* pThisNode = (CStaticNode*)GetWindowLongPtr( hWnd, 0 );
      pThisNode->m_hAddDeviceDlg = NULL; 
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
HRESULT CStaticNode::GetResultViewType2
( 
  MMC_COOKIE             nCookie,  //[in] Identifier of object
  PRESULT_VIEW_TYPE_INFO pRVTinfo  //[in,out] ViewTypeInfo struct
)    
{
  LPOLESTR pszDescStr = (LPOLESTR)CoTaskMemAlloc( sizeof(L"DefaultListView")+sizeof(WCHAR) );
  if( NULL == pszDescStr )
    return E_OUTOFMEMORY;      

  wcscpy( pszDescStr, L"DefaultListView" );
  pRVTinfo->pstrPersistableViewDescription = pszDescStr;

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CStaticNode::GetDisplayInfo
( 
  SCOPEDATAITEM* pSDI        //[in][out] Points to SCOPEDATAITEM
)
{
  _ASSERT( NULL != pSDI );
  pSDI->displayname = m_pwszNodeName;

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CStaticNode::GetDisplayInfo
( 
  RESULTDATAITEM* pRDI
)
{
  // This method will not get called since the static node is never
  // displayed in the result pane  
  return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation of notification handlers

//---------------------------------------------------------------------------
HRESULT CStaticNode::OnShow
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] TRUE if node was selcted
  LPARAM        nParam,        //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR      pComponent     //[in] Points to calling IComponent
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


  if( TRUE == nArg )  // Selecting a scope node
  {
    do                                 
    {                                  
      hResult = ipHeaderCtrl->InsertColumn( 0, L"Device Name", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipHeaderCtrl->InsertColumn( 1, L"Status", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipResultData->ModifyViewStyle( MMC_NOSORTHEADER, (MMC_RESULT_VIEW_STYLE)NULL );      
      BREAK_ON_ERROR( hResult );

    }while(0);
  }
  else // not handling deselect notifications
  {
  }

  //TRACE_HRESULT(_T("OnShow"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CStaticNode::OnSelect
(
  LPDATAOBJECT   ipDataObject,   //[in] Points to the selected data object
  LPARAM         nArg,           //[in] Status of selected item
  LPARAM         nParam,         //[in] Not used
  LONG_PTR       pComponent      //[in] Pointer to parent CComponent
)
{
  BOOL    fScopePane = LOWORD(nArg);
  BOOL    fSelected  = HIWORD(nArg);
  HRESULT hResult    = S_FALSE;
  
  if( NULL == ipDataObject )           // Can get this when closing the SnapIn
    return hResult;

  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  LPCONSOLEVERB  ipConsoleVerb = NULL;
  hResult = pComp->GetInterface( REQUEST_ICONSOLEVERB, (LONG_PTR*)&ipConsoleVerb ); 
  if( S_OK != hResult )
    return hResult;              


  if( TRUE == fScopePane && TRUE == fSelected )            
  {                                      
    // This is where we will set verbs in later versions
  }

  TRACE_HRESULT(_T("OnSelect"), hResult );
  return hResult;

} 

//---------------------------------------------------------------------------
//  The static node is a special case.  The CComponentData pointer is also
//  our parent so we don't need to use the pCompData parameter
//
HRESULT CStaticNode::OnExpand
(
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_FALSE;

  if( NULL == m_hStaticNode )          // Cache the root node handle
    m_hStaticNode = (HSCOPEITEM)nParam; 

  if( NULL == m_pCompData )
    m_pCompData = reinterpret_cast<CComponentData*>(pCompData);

  // Request an IConsoleNameSpace2 pointer from CComponentData
  // The static node is a unique case since it's parent is also IComponentData
  //
  LPCONSOLENAMESPACE2 ipCNS = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLENAMESPACE, (LONG_PTR*)&ipCNS );
  if( S_OK != hResult )
    return hResult; 


  hResult = DeleteScopeItems( ipCNS );
  hResult = InsertScopeItems( ipCNS );

  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CStaticNode::OnRemoveChildren
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_OK;

  if( NULL == m_pCompData )
    m_pCompData = reinterpret_cast<CComponentData*>(pCompData);


  POSITION   Pos   = m_NodeList.GetHeadPosition();
  LPBASENODE pNode = NULL;
  while( Pos )                         // Delete everything...
  {
    pNode = m_NodeList.GetNext( Pos );
    pNode->OnRemoveChildren( ipDataObject, nArg, nParam, pCompData );
    delete pNode;
  }

  m_NodeList.RemoveAll();              // Cleanup the list

  //TRACE_HRESULT( _T("OnRemoveChildren"), hResult );
  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
// Private helper methods


//---------------------------------------------------------------------------
//  Initializes the node list.
//
HRESULT CStaticNode::RefreshNodeList()
{
  NODE_PROPERTIES NodeProps;
  ZeroMemory( &NodeProps, sizeof(NODE_PROPERTIES) );

  NodeProps.pParentObject  = reinterpret_cast<LONG_PTR>(this);
  NodeProps.pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);

  WCHAR  szNames[2][32];
  wcscpy( szNames[0], L"RamDisk 0" );
  wcscpy( szNames[1], L"Archive 0" );

  RemoveNodes();                       // Clean the node list

  CDeviceNode* pNode = NULL;
  for( DWORD i = 0; i < 2; i++ )
  {
    wcscpy( NodeProps.szNodeName, szNames[i] ); 
    pNode = new CDeviceNode;
    pNode->Initialize( &NodeProps );
    m_NodeList.AddTail( pNode );

    // Kind of a hack, make the second device a backup device
    NodeProps.dwAttributes |= ATTRIBUTE_BACKUP_DEVICE;
  }

  return S_OK;
}


//---------------------------------------------------------------------------
//  For these first level nodes the parent is always the static or root
//  node.  
//
HRESULT CStaticNode::InsertScopeItems
(
  LPCONSOLENAMESPACE2 ipCNS    //[in] Needed to insert items
)
{
  _ASSERT( NULL != ipCNS );
  _ASSERT( NULL != m_hStaticNode );

  HRESULT      hResult = S_FALSE;  
  POSITION     Pos     = m_NodeList.GetHeadPosition();
  CDeviceNode* pNode   = NULL;

  while( Pos )                         
  {
    pNode   = m_NodeList.GetNext( Pos );
    pNode->m_SDI.relativeID = m_hStaticNode;
    hResult = ipCNS->InsertItem( &pNode->m_SDI );   
  }

  return hResult;
}  


//---------------------------------------------------------------------------
//  Delete the HSCOPEITEMS only, we leave the list of nodes untouched
//
HRESULT CStaticNode::DeleteScopeItems
(
  LPCONSOLENAMESPACE2 ipCNS    //[in] Needed to delete items
)
{
  _ASSERT( NULL != ipCNS );

  POSITION    Pos     = m_NodeList.GetHeadPosition();
  HSCOPEITEM  hItem   = NULL;
  LPBASENODE  pNode   = NULL;
  HRESULT     hResult = S_FALSE;

  while( Pos )                         // Delete everything...
  {
    pNode = m_NodeList.GetNext( Pos );
    hItem = (HSCOPEITEM)pNode->m_SDI.ID;
    if( 0 != hItem )
      hResult = ipCNS->DeleteItem( hItem, TRUE );   
  }

  return hResult;

}

//---------------------------------------------------------------------------
//  We do this instead of just calling RemoveAll() because our list contains
//  CBaseNode pointers and so RemoveAll() does not call the destructor for 
//  the derived class object.  
//
VOID CStaticNode::RemoveNodes()
{
  LPBASENODE pNode = NULL;
  POSITION   Pos   = m_NodeList.GetHeadPosition();
  while( Pos )
  {
    pNode = m_NodeList.GetNext( Pos );
    delete pNode;
  }
  m_NodeList.RemoveAll();              // Clean the list
}

//---------------------------------------------------------------------------
HRESULT CStaticNode::AddDeviceNode
( 
  NODE_PROPERTIES*    pProps   //[in] Properties for the new node
)
{
  _ASSERT( NULL != pProps );

  CDeviceNode* pNode   = NULL;
  HRESULT      hResult = S_FALSE;

  // In this case we always have the same parent
  pProps->pParentObject  = reinterpret_cast<LONG_PTR>(this);        
  pProps->pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);        

  pNode = new CDeviceNode;         // Create and initialize the new
  pNode->Initialize( pProps );     // node, then add to our linked
  m_NodeList.AddTail( pNode );     // list, then insert the node

  pNode->m_SDI.relativeID = m_hStaticNode;

  LPCONSOLENAMESPACE2 ipCNS = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLENAMESPACE, (LONG_PTR*)&ipCNS );
  if( S_OK != hResult )
    return hResult; 

  hResult = ipCNS->InsertItem( &pNode->m_SDI );   

  return hResult;
}

//---------------------------------------------------------------------------
//  Get the selected node and call it's ToggleStatus method
//
VOID CStaticNode::ToggleStatus
(
  LPDATAOBJECT ipDataObject
)
{
  CDeviceNode* pNode = (CDeviceNode*)ExtractBaseNodePtr( ipDataObject );
  if( NULL != pNode )
    pNode->ToggleStatus(); 

}


/////////////////////////////////////////////////////////////////////////////
//  Support for Context Menus

//---------------------------------------------------------------------------
//  NOTE:  Don't AddRef ipCallback.  Check docs.
//
HRESULT CStaticNode::AddMenuItems
( 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  _ASSERT( NULL != ipCallback );
  HRESULT hResult = S_FALSE;

  static CONTEXTMENUITEM ctxMenu;           
    ctxMenu.lCommandID        = IDM_NEW_DEVICE;
    ctxMenu.lInsertionPointID = CCM_INSERTIONPOINTID_PRIMARY_NEW; 
    ctxMenu.fSpecialFlags     = 0;
    ctxMenu.strName           = L"New Device...";
    ctxMenu.strStatusBarText  = L"Add a new device";

  
  if( NULL == m_hAddDeviceDlg )    // If the AddDevice dialog is running
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
HRESULT CStaticNode::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  HRESULT hResult = S_OK;

  switch( lCommandID )
  {
    case IDM_NEW_DEVICE:
    {
      CAddDeviceDlg* pDlg = new CAddDeviceDlg( IDD_ADDDEVICE_DLG, m_hMessageWnd );
      m_hAddDeviceDlg = pDlg->Create( g_hInst, GetDesktopWindow(), 0 );
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
//  Toolbar methods

//---------------------------------------------------------------------------
HRESULT CStaticNode::ControlbarNotify
( 
  LPARAM     nArg,         //[in] Selection status 
  LPARAM     lParam,       //[in] Not used 
  LONG_PTR   pComp         //[in] Points to CComponent
)
{ 
  HRESULT hResult = S_FALSE;
  BOOL bScope  = (BOOL)LOWORD(nArg);
  BOOL bSelect = (BOOL)HIWORD(nArg);

  CComponent* pComponent = reinterpret_cast<CComponent*>(pComp);

  IControlbar* ipControlbar = NULL;
  hResult = pComponent->GetInterface( REQUEST_ICONTROLBAR, (LONG_PTR*)&ipControlbar );
  if( S_OK != hResult )
    return hResult; 

  IToolbar* ipToolbar = NULL;
  hResult = pComponent->GetInterface( REQUEST_ISTATICTOOLBAR, (LONG_PTR*)&ipToolbar );
  if( S_OK != hResult )
    return hResult; 

  if( TRUE == bSelect )
  {
    hResult = ipControlbar->Attach(TOOLBAR, (LPUNKNOWN)ipToolbar);
    hResult = ipToolbar->SetButtonState( IDM_NEW_DEVICE, ENABLED, TRUE );
  }
  else
  {
    hResult = ipControlbar->Detach( (LPUNKNOWN)ipToolbar );
  }

  return hResult;
}
