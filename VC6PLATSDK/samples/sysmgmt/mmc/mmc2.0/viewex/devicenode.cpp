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
//  Abstract:     Implementation of the CDeviceNode class.
//


#include "DeviceNode.h"
#include "CompData.h"
#include "Comp.h"
                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CDeviceNode")



// Initialize our static GUID just once
GUID CDeviceNode::thisGUID = CLSID_DeviceNode;   


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CDeviceNode::CDeviceNode()
{
  m_SDI.mask        = DEFAULT_SDI_MASK;
  m_SDI.displayname = MMC_CALLBACK;
  m_SDI.cChildren   = 1;              // Determines if the '+' is displayed
  m_SDI.lParam      = reinterpret_cast<LPARAM>(this);

  m_hParentNode     = NULL;
  m_dwAttributes    = 0;
  m_wzStatus        = NULL;
  m_pCompData       = NULL;
}


CDeviceNode::~CDeviceNode()
{
}

//---------------------------------------------------------------------------
HRESULT CDeviceNode::Initialize( NODE_PROPERTIES* pNodeProps )
{
  _ASSERT( NULL != pNodeProps );

  UINT   nLen   = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName = pszTmp;
  m_pCompData = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);

  RefreshNodeList();                   // Add child nodes
                                       // and set images

  if( pNodeProps->dwAttributes & ATTRIBUTE_BACKUP_DEVICE )
  {
    m_SDI.nImage      = IMG_DEVICE_DEFAULT; 
    m_SDI.nOpenImage  = IMG_DEVICE_DEFAULT;
    m_dwAttributes   |= ATTRIBUTE_BACKUP_DEVICE;
  }
  else
  { 
    m_SDI.nImage      = IMG_DRIVE_DEFAULT; 
    m_SDI.nOpenImage  = IMG_DRIVE_DEFAULT;
    m_dwAttributes   |= ~ATTRIBUTE_BACKUP_DEVICE;
  }
  
  m_wzStatus      = L"Online";    // Node successfully initialized
  m_bOnlineStatus = STATUS_ONLINE;
  
  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods


//---------------------------------------------------------------------------
HRESULT CDeviceNode::GetResultViewType2
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
HRESULT CDeviceNode::GetDisplayInfo
( 
  SCOPEDATAITEM* pSDI        //[in][out] Points to SCOPEDATAITEM
)
{
  _ASSERT( NULL != pSDI );
  pSDI->displayname = m_pwszNodeName;

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CDeviceNode::GetDisplayInfo
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
        pRDI->str = m_wzStatus;
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
HRESULT CDeviceNode::OnSelect
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] Bools for context & selection state
  LPARAM        nParam,        //[in] Not used
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT hResult = S_FALSE;

  // Not setting verbs for this node

  //TRACE_HRESULT(_T("OnSelect"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CDeviceNode::OnShow
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
      hResult = ipHeaderCtrl->InsertColumn( 0, L"Folder Name", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipHeaderCtrl->InsertColumn( 1, L"Attributes", 0, 150 );
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
HRESULT CDeviceNode::OnExpand
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object    
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_FALSE;

  // Cache HSCOPEITEM of Parent
  m_hParentNode = static_cast<HSCOPEITEM>(nParam); 
 
  if( NULL == m_pCompData )
    m_pCompData = reinterpret_cast<CComponentData*>(pCompData);

  // Request an IConsoleNameSpace2 pointer from CComponentData
  LPCONSOLENAMESPACE2 ipCNS = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLENAMESPACE, (LONG_PTR*)&ipCNS );
  if( S_OK != hResult )
    return hResult; 

  hResult = DeleteChildItems( ipCNS );
  hResult = InsertChildItems( ipCNS );

  //TRACE_HRESULT( _T("OnExpand"), hResult );
  return hResult;              
}


//---------------------------------------------------------------------------
HRESULT CDeviceNode::OnRemoveChildren
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LPARAM         nArg,         //[in] TRUE if node was selcted
  LPARAM         nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_FALSE;

  POSITION   Pos   = m_NodeList.GetHeadPosition();
  LPBASENODE pNode = NULL;
  while( Pos )                         // Delete everything...
  {
    pNode = m_NodeList.GetNext( Pos );
    hResult = pNode->OnRemoveChildren( ipDataObject, nArg, nParam, pCompData );
    delete pNode;
  }

  m_NodeList.RemoveAll();            // Cleans up the list

  TRACE_HRESULT( _T("OnRemoveChildren"), hResult );
  return hResult;

}


/////////////////////////////////////////////////////////////////////////////
//  Private Helpers

//---------------------------------------------------------------------------
HRESULT CDeviceNode::DeleteChildItems
( 
  LPCONSOLENAMESPACE2 ipCNS      //[in] IConsoleNameSpace pointer
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
HRESULT CDeviceNode::InsertChildItems
( 
  LPCONSOLENAMESPACE2 ipCNS      //[in] IConsoleNameSpace pointer 
)
{
  _ASSERT( NULL != ipCNS );
  _ASSERT( NULL != m_hParentNode );

  HRESULT    hResult = S_FALSE;  
  POSITION   Pos     = m_NodeList.GetHeadPosition();
  LPBASENODE pNode   = NULL;

  while( Pos )                         
  {
    pNode   = m_NodeList.GetNext( Pos );
    pNode->m_SDI.relativeID = m_hParentNode;
    hResult = ipCNS->InsertItem( &pNode->m_SDI );   
  }

  return hResult;
}


//---------------------------------------------------------------------------
//  Only add one child node in this sample
//
HRESULT CDeviceNode::RefreshNodeList()
{
  NODE_PROPERTIES NodeProps;
  NodeProps.pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);
  NodeProps.pParentObject  = reinterpret_cast<LONG_PTR>(this);
  NodeProps.dwAttributes   = 0;

  WCHAR  szNames[1][32];
  wcscpy( szNames[0], L"Root Folder" );

  RemoveChildNodes();                  // Clean the node list

  LPBASENODE pNode = NULL;
  for( DWORD i = 0; i < 1; i++ )
  {
    wcscpy( NodeProps.szNodeName, szNames[i] ); 
    pNode = new CFolderNode;
    pNode->Initialize( &NodeProps );
    m_NodeList.AddTail( pNode );
  }

  return S_OK;
}

//---------------------------------------------------------------------------
//  We do this instead of just calling RemoveAll() because our list contains
//  CBaseNode pointers and so RemoveAll() does not call the destructor for 
//  the derived class object.  
//
VOID CDeviceNode::RemoveChildNodes()
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

/////////////////////////////////////////////////////////////////////////////
//  Public helpers

//---------------------------------------------------------------------------
VOID CDeviceNode::ToggleStatus()
{
  // First we have to set the image indexes according to the Online Status
  // and the device type
  //
  if( STATUS_ONLINE == m_bOnlineStatus )
  { 
    m_bOnlineStatus = STATUS_OFFLINE;
    m_wzStatus      = L"Offline";
    if( m_dwAttributes & ATTRIBUTE_BACKUP_DEVICE )
    {
      m_SDI.nImage      = IMG_DEVICE_OFFLINE; 
      m_SDI.nOpenImage  = IMG_DEVICE_OFFLINE;
    }
    else
    {
      m_SDI.nImage      = IMG_DRIVE_OFFLINE; 
      m_SDI.nOpenImage  = IMG_DRIVE_OFFLINE;
    }
  }
  else
  {
    m_bOnlineStatus = STATUS_ONLINE;
    m_wzStatus      = L"Online";
    if( m_dwAttributes & ATTRIBUTE_BACKUP_DEVICE )
    {
      m_SDI.nImage      = IMG_DEVICE_DEFAULT; 
      m_SDI.nOpenImage  = IMG_DEVICE_DEFAULT;
    }
    else
    {
      m_SDI.nImage      = IMG_DRIVE_DEFAULT; 
      m_SDI.nOpenImage  = IMG_DRIVE_DEFAULT;
    }
  }
  // This is a scope node, so GetDisplayInfo will only ask for images for
  // this node when it is in the Result Pane.  To change the image for the
  // the Scope Pane we need to call IConsoleNameSpace::SetItem().  This
  // call forces the scope node to be redrawn. 
  //
  SCOPEDATAITEM  sdi;
  ZeroMemory( &sdi, sizeof(SCOPEDATAITEM) );  
  sdi.mask        = SDI_IMAGE | SDI_OPENIMAGE ;
  sdi.ID          = m_SDI.ID;
  sdi.nImage      = m_SDI.nImage;
  sdi.nOpenImage  = m_SDI.nOpenImage;  

  // Request an IConsoleNameSpace pointer from CComponentData
  HRESULT  hResult = S_FALSE;
  LPCONSOLENAMESPACE2 ipCNS = NULL;
  hResult = m_pCompData->GetInterface( REQUEST_ICONSOLENAMESPACE, (LONG*)&ipCNS );
  if( S_OK == hResult )
    hResult = ipCNS->SetItem( &sdi );  

}


/////////////////////////////////////////////////////////////////////////////
//  Support for Context Menus

//---------------------------------------------------------------------------
//  Devices can only add a folder
//
HRESULT CDeviceNode::AddMenuItems
( 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  _ASSERT( NULL != ipCallback );
  HRESULT hResult = S_FALSE;

  static CONTEXTMENUITEM ctxMenu[2];           
    ctxMenu[0].lCommandID        = IDM_NEW_FOLDER;
    ctxMenu[0].lInsertionPointID = CCM_INSERTIONPOINTID_PRIMARY_NEW; 
    ctxMenu[0].fFlags            = MF_GRAYED;
    ctxMenu[0].fSpecialFlags     = 0;
    ctxMenu[0].strName           = L"New Folder...";
    ctxMenu[0].strStatusBarText  = L"Add a new folder";

    ctxMenu[1].lCommandID        = IDM_TOGGLE_STATUS;
    ctxMenu[1].lInsertionPointID = CCM_INSERTIONPOINTID_PRIMARY_TASK; 
    ctxMenu[1].fFlags            = 0;
    ctxMenu[1].fSpecialFlags     = 0;
    ctxMenu[1].strName           = L"Toggle Online Status";
    ctxMenu[1].strStatusBarText  = L"Toggles the device status";


  // Add the Add new folder command
  if( CCM_INSERTIONALLOWED_NEW & *pInsertionAllowed )
  {
    hResult = ipCallback->AddItem( &ctxMenu[0] );
  } 

  // Add the Toggle item to the Task menu if allowed...
  if( CCM_INSERTIONALLOWED_TOP & *pInsertionAllowed )
  {
    hResult = ipCallback->AddItem( &ctxMenu[1] );
  }  

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CDeviceNode::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  HRESULT hResult = S_OK;

  switch( lCommandID )
  {  
    case IDM_TOGGLE_STATUS:
    {
      ToggleStatus();     
      break;
    }
    case IDM_NEW_FOLDER:
    {
      // Not handling this command in this sample
      break;
    }
    default:
      hResult = S_FALSE;
      break;

  }
  return hResult;
}
