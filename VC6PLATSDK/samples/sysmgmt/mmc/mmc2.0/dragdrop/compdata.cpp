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
#include "Comp.h"
#include "CompData.h"
#include "DataObj.h"
#include "Resource.h"

                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CComponentData")


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction


//---------------------------------------------------------------------------
//  This constructor is called when the Snap-in is selected from the 
//  Add/Remove dialog.  Build our static node and load the required
//  clipformats before MMC calls us.
//
CComponentData::CComponentData()
{
	// Do not assume only one instance of IComponentData implementation is created.


    m_cRef                = 0;
    m_ipConsoleNameSpace  = NULL;  
    m_ipConsole           = NULL;

    // Increment this so DllCanUnloadNow works correctly  
    InterlockedIncrement((long*)&g_uObjectCount);

    NODEPROPS NodeProps;
    ZeroMemory( &NodeProps, sizeof(NODEPROPS) );
    wcscpy( NodeProps.szNodeName, gwszROOT_NODE_NAME );
    NodeProps.pComponentData = reinterpret_cast<LONG_PTR>(this);
    NodeProps.pParentObject  = NULL;
    NodeProps.nChildCount    = INIT_DEFAULT_NODE;
        
    m_pStaticNode = new CStaticNode;
    m_pStaticNode->Initialize( &NodeProps );

    InitClipboardFormats();
}

//---------------------------------------------------------------------------
CComponentData::~CComponentData()
{
  if( NULL != m_pStaticNode )
  {
    delete m_pStaticNode;
    m_pStaticNode = NULL;
  }
  
  // All done, decrement object count so the dll can be unloaded    
  InterlockedDecrement((long*)&g_uObjectCount);
}


/////////////////////////////////////////////////////////////////////////////
// IUnknown implementation

//---------------------------------------------------------------------------
STDMETHODIMP CComponentData::QueryInterface
(
  REFIID   riid,       //[in] Identifier of the requested interface
  LPVOID   *ppv        //[out] Address of requested interface 
)
{
  if( !ppv )
    return E_FAIL;
    
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
    *ppv = static_cast<IComponentData*>(this);
  else if( IsEqualIID(riid, IID_IComponentData) )
    *ppv = static_cast<IComponentData*>(this);
  else if( IsEqualIID(riid, IID_IComponentData2) )
    *ppv = static_cast<IComponentData2*>(this);
  else if( IsEqualIID(riid, IID_IExtendContextMenu) )
    *ppv = static_cast<IExtendContextMenu *>(this);

    
  if( *ppv ) 
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
  }
    
  return E_NOINTERFACE;
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CComponentData::AddRef()
{
  return InterlockedIncrement((LONG*)&m_cRef);
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CComponentData::Release()
{
  if( InterlockedDecrement((LONG*)&m_cRef) == 0 )
  {
    delete this;
    return 0;
  }
    
  return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
// Interface IComponentData

//---------------------------------------------------------------------------
//  Called when the user selects the Snap-in from the scope pane.
//  This is where we QI and cache interfaces we will use later.  These 
//  interfaces are for future use since they are not used in this sample
//
HRESULT CComponentData::Initialize
( 
  LPUNKNOWN pUnknown         //[in] Pointer to the console's IUnknown
)
{
  HRESULT hResult = S_FALSE;
  hResult = GetConsoleVersion( &g_CV );  
                             // S_FALSE is returned for any version earlier
                             // than 2.0.  The values in g_CV will be 0.0  

                             // Fail to initialize if we can't get the 
  do                         // interfaces we need to cache
  {                          
    hResult = pUnknown->QueryInterface(IID_IConsole3, (void**)&m_ipConsole);
    BREAK_ON_ERROR( hResult );

    hResult = pUnknown->QueryInterface(IID_IConsoleNameSpace2, (void**)&m_ipConsoleNameSpace);
    BREAK_ON_ERROR( hResult );

    // Add the images for the scope tree
    LPIMAGELIST ipScopeImage = NULL; 
    hResult = m_ipConsole->QueryScopeImageList(&ipScopeImage);
    BREAK_ON_ERROR( hResult );
	
    // Load the bitmaps from the dll
    HBITMAP hImageStrip16 = ::LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NODEIMAGES_16) );
    if( NULL == hImageStrip16 )
    {
      hResult = S_FALSE;
      continue;
    }

    HBITMAP hImageStrip32 = ::LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NODEIMAGES_32) );
	   if( NULL == hImageStrip32)
    {
      hResult = S_FALSE;
      continue;
    }
	
    // Set the images
    hResult = ipScopeImage->ImageListSetStrip( (LONG_PTR*)hImageStrip16,
  	                                           (LONG_PTR*)hImageStrip32,
                                               0,
                                               RGB(0,255,0)
                                             );
    BREAK_ON_ERROR( hResult );

    SAFE_RELEASE( ipScopeImage      ); // Release these here.  IComponent
    SAFE_FREE_BITMAP( hImageStrip16 ); // will get an MMCN_ADD_IMAGES when 
    SAFE_FREE_BITMAP( hImageStrip32 ); // the console needs them again.
  }
  while( 0 );
    
  return hResult;
}

//---------------------------------------------------------------------------
//  Called by the console every time we need to create a new result view.
//  There can be several different result views. Aside from the default one
//  created when the Snap-in initializes, additional ones are created by 
//  selecting "New window from here" in MMC's user interface. 
//
HRESULT CComponentData::CreateComponent
( 
  LPCOMPONENT __RPC_FAR* ppComponent   //[out] Points to new IComponent class
) 
{
  *ppComponent = NULL;
    
  // Pass the new CComponent a pointer to it's parent
  CComponent* pComponent = new CComponent( this );
    
  if( NULL == pComponent )
    return E_OUTOFMEMORY;
    
  return pComponent->QueryInterface( IID_IComponent, (void**)ppComponent );
}

//---------------------------------------------------------------------------
//  Handles notification events from MMC
//
HRESULT CComponentData::Notify
( 
  LPDATAOBJECT     ipDataObject,   //[in] Points to the selected data object
  MMC_NOTIFY_TYPE  MmcEvent,       //[in] Identifies action taken by user
  LONG             nArg,           //[in] Depends on the notification type
  LONG             nParam          //[in] Depends on the notification type
)
{
  TRACE_EVENT( _T("Notify"), MmcEvent );  // Provides trace output

  HRESULT hResult = S_FALSE;
  LPBASENODE pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL == pNode )
    return hResult;

  switch( MmcEvent )
  {
    case MMCN_EXPAND:
      hResult = pNode->OnExpand( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    case MMCN_REMOVE_CHILDREN:
      hResult = pNode->OnRemoveChildren( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;         

    case MMCN_PRELOAD:                 // Notification not implemented
    case MMCN_PROPERTY_CHANGE:         // Notification not implemented 
    case MMCN_DELETE:                  // Notification not implemented
      break;

    case MMCN_RENAME:
      hResult = pNode->OnRename( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    default:
      break;
  }

  return hResult; 
}

//---------------------------------------------------------------------------
//  This is where we release any cached interface pointers or any
//  allocated resources.
//
HRESULT CComponentData::Destroy( void)
{
  SAFE_RELEASE( m_ipConsoleNameSpace );
  SAFE_RELEASE( m_ipConsole          );

  return S_OK;
}

//---------------------------------------------------------------------------
//  MMC provides a NULL cookie for the static/root node.  In this sample
//  we don't pass that on, instead we use the pointer to our static node
//  object which handles notifications
//
HRESULT CComponentData::QueryDataObject
( 
  MMC_COOKIE              nCookie,     //[in]  Indentifier of the selected node
  DATA_OBJECT_TYPES       nEnumType,   //[in]  Context in which this object was created 
  LPDATAOBJECT __RPC_FAR* ppDataObject //[out] Points to data object we create
) 
{
  HRESULT hResult = S_FALSE;
  ULONG   uCookie = 0;

  CDataObject* pNewObject = new CDataObject();
  if( NULL == pNewObject )
    hResult = E_OUTOFMEMORY;

  (0 == nCookie) ? uCookie = (ULONG)m_pStaticNode : uCookie = nCookie; 
  pNewObject->SetPrivateData( uCookie, (ULONG)nEnumType );   

  hResult = pNewObject->QueryInterface( IID_IDataObject, (void**)ppDataObject );
    
  return hResult;
}
 
//---------------------------------------------------------------------------
//  Delegate the call to the static node object
//
HRESULT CComponentData::GetDisplayInfo
( 
  SCOPEDATAITEM* pScopeDataItem    //[out][in] Points to a SCOPEDATAITEM struct
)
{
  _ASSERT( NULL != pScopeDataItem );
  HRESULT hResult = S_OK;
    
  // The console will only ask for the name string
  if(  pScopeDataItem->mask & SDI_STR ) 
  {
    CBaseNode* pNode = reinterpret_cast<CBaseNode*>(pScopeDataItem->lParam);
    hResult = pNode->GetDisplayInfo( pScopeDataItem );
  }

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CComponentData::CompareObjects
( 
  LPDATAOBJECT ipDataObjectA,    //[in] First data object to compare 
  LPDATAOBJECT ipDataObjectB     //[in] Second data object to compare 
)
{
  return E_NOTIMPL;
}


//---------------------------------------------------------------------------
HRESULT CComponentData::QueryDispatch
(
  MMC_COOKIE         nCookie,    //[in]  Item for which IDispatch is requested
  DATA_OBJECT_TYPES  eType,      //[in]  Context of item
  LPDISPATCH*        pipDispatch //[out] IDispatch pointer
)
{
  return E_NOTIMPL;
}


/////////////////////////////////////////////////////////////////////////////
// Interface IExtendContextMenu

//---------------------------------------------------------------------------
HRESULT CComponentData::AddMenuItems
( 
  LPDATAOBJECT ipDataObject,         //[in] 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] 
  long __RPC_FAR* pInsertionAllowed  //[out-in] 
)
{
  _ASSERT( NULL != ipCallback );
  HRESULT hResult = S_FALSE; 

  LPBASENODE pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL != pNode )
    hResult = pNode->AddMenuItems( ipCallback, pInsertionAllowed ); 

  return hResult;
}

//---------------------------------------------------------------------------
//
HRESULT CComponentData::Command
(
  long         lCommandID,   //[in] Identifier of the menu item
  LPDATAOBJECT ipDataObject  //[in] DataObject for selected node
)
{
  HRESULT hResult = S_OK;

  CBaseNode* pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL != pNode )
    hResult = pNode->Command( lCommandID );

  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
//  Helper methods

//---------------------------------------------------------------------------
HRESULT CComponentData::GetInterface
( 
  DWORD     dwRequestedInterface,  //[in] Request flag
  LONG_PTR* ppInterface            //[in-out] Interface pointer to return
)
{
  _ASSERT( NULL != ppInterface );
  HRESULT hResult = S_OK;

  switch( dwRequestedInterface )
  {
    case REQUEST_ICONSOLENAMESPACE:
      _ASSERT( NULL != m_ipConsoleNameSpace );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipConsoleNameSpace);
      break;
    
    case REQUEST_ICONSOLE:
      _ASSERT( NULL != m_ipConsole );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipConsole);
      break;

    default:
      hResult = S_FALSE;
      *ppInterface = NULL;
      break;
  }

  return hResult;
}


