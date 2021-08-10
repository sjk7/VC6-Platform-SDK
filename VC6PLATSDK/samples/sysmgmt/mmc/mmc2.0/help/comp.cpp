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
#include "StaticNode.h"

                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CComponent")


//---------------------------------------------------------------------------
//  Our default constuctor provides a pointer to the parent CComponentData
//  class which we cache for use in later samples.
//
CComponent::CComponent
(
  CComponentData*  pParent   //[in] Points to parent object
)
{
  _ASSERT( NULL != pParent );

  m_cRef           = 0;
  m_hImageStrip16  = NULL;
  m_hImageStrip32  = NULL;
  m_ipConsole      = NULL;
  m_ipConsoleVerb  = NULL;
  m_ipResultData   = NULL;
  m_ipHeaderCtrl2  = NULL;
  m_ipDisplayHelp  = NULL;
  m_pComponentData = pParent;

}

//---------------------------------------------------------------------------
CComponent::~CComponent()
{
}

/////////////////////////////////////////////////////////////////////////////
//  Implementation of IUnknown

//---------------------------------------------------------------------------
//  PROPPAGE:  Support for IExtendPropertySheet2 added
//
STDMETHODIMP CComponent::QueryInterface
(
  REFIID   riid,       //[in] Identifier of the requested interface
  LPVOID   *ppv        //[out] Address of requested interface 
)
{
  if( !ppv )
    return E_FAIL;
    
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
    *ppv = static_cast<IComponent*>(this);
  else if( IsEqualIID(riid, IID_IComponent) )
    *ppv = static_cast<IComponent*>(this);    
  else if( IsEqualIID(riid, IID_IComponent2) )
    *ppv = static_cast<IComponent2*>(this);    
  else if( IsEqualIID(riid, IID_IExtendPropertySheet2) )
    *ppv = static_cast<IExtendPropertySheet2*>(this);


  if( *ppv )
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
  }
    
  return E_NOINTERFACE;
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CComponent::AddRef()
{
  return InterlockedIncrement((LONG*)&m_cRef);
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CComponent::Release()
{
  if( InterlockedDecrement((LONG*)&m_cRef) == 0 )
  {
    delete this;
    return 0;
  }
  return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation of IComponent

//---------------------------------------------------------------------------
STDMETHODIMP CComponent::Initialize
( 
  LPCONSOLE ipConsole    //[in] Points to the console's IUnknown 
)
{
  HRESULT hResult = S_FALSE;

  do
  {
		hResult = ipConsole->QueryInterface( IID_IConsole3,(VOID**)&m_ipConsole );
		BREAK_ON_ERROR( hResult );

    hResult = m_ipConsole->QueryConsoleVerb( &m_ipConsoleVerb );
		BREAK_ON_ERROR( hResult ); 

    hResult = m_ipConsole->QueryInterface( IID_IResultData,(VOID**)&m_ipResultData );
    BREAK_ON_ERROR( hResult );

    hResult = m_ipConsole->QueryInterface( IID_IHeaderCtrl2,(VOID**)&m_ipHeaderCtrl2 );
    BREAK_ON_ERROR( hResult );

    // MMC_HELP:  Cache IDisplay help for RequestInterface()
    hResult = m_ipConsole->QueryInterface( IID_IDisplayHelp,(VOID**)&m_ipDisplayHelp );
    BREAK_ON_ERROR( hResult );

    // Load the bitmaps from the dll for the results pane
    m_hImageStrip16 = ::LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NODEIMAGES_16));
    if( NULL == m_hImageStrip16 )
    {
      hResult = S_FALSE;
      continue;
    }

    m_hImageStrip32 = ::LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NODEIMAGES_32));
    if( NULL == m_hImageStrip32 )
    {
      hResult = S_FALSE;
      continue;
    }

  }while( 0 );

  TRACE_HRESULT(_T("Initialize"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
STDMETHODIMP CComponent::Notify 
( 
  LPDATAOBJECT     ipDataObject,   //[in] Points to the selected data object
  MMC_NOTIFY_TYPE  MmcEvent,       //[in] Identifies action taken by user
  LPARAM           nArg,           //[in] Depends on the notification type
  LPARAM           nParam          //[in] Depends on the notification type
)
{
  HRESULT hResult = S_FALSE;       // Return this for unhandled notifications
  TRACE_EVENT( _T("Notify"), MmcEvent );

  LPBASENODE pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL == pNode ) 
    return E_FAIL;            


  switch( MmcEvent )
  {
    case MMCN_ADD_IMAGES:
      hResult = OnAddImages( ipDataObject, nArg, nParam );
      break; 

    case MMCN_SELECT:
      hResult = pNode->OnSelect( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    case MMCN_SHOW:
      hResult = pNode->OnShow( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    case MMCN_VIEW_CHANGE:
      hResult = pNode->OnViewChange( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    case MMCN_DELETE:
      hResult = pNode->OnDelete( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    case MMCN_CONTEXTHELP:
      hResult = pNode->OnContextHelp( ipDataObject, nArg, nParam, (LONG_PTR)this );
      break;

    case MMCN_DBLCLICK:
      break;                            

    default:
      break;
  }
  return hResult;
}

//---------------------------------------------------------------------------
STDMETHODIMP CComponent::Destroy
( 
  MMC_COOKIE nCookie   //[in] Not used
)
{
  SAFE_RELEASE( m_ipConsole     );
  SAFE_RELEASE( m_ipHeaderCtrl2 );
  SAFE_RELEASE( m_ipResultData  );
  SAFE_RELEASE( m_ipConsoleVerb );

  SAFE_FREE_BITMAP( m_hImageStrip16 );
  SAFE_FREE_BITMAP( m_hImageStrip32 );

  return S_OK;
}

//---------------------------------------------------------------------------
STDMETHODIMP CComponent::QueryDataObject
( 
  MMC_COOKIE              nCookie,     //[in]  Indentifier of the selected node
  DATA_OBJECT_TYPES       nEnumType,   //[in]  Context in which this object was created 
  LPDATAOBJECT __RPC_FAR* ppDataObject //[out] Points to data object we create
)
{
  _ASSERT( NULL != nCookie );
  HRESULT hResult = S_FALSE;
 
  CDataObject* pNewObject = new CDataObject();
  if( NULL == pNewObject )
    hResult = E_OUTOFMEMORY;

  pNewObject->SetPrivateData( nCookie, (ULONG)nEnumType );   

  hResult = pNewObject->QueryInterface( IID_IDataObject, (void**)ppDataObject );
    
  return hResult;
}

//---------------------------------------------------------------------------
//  This method not used in MMC20
//
STDMETHODIMP CComponent::GetResultViewType
( 
  MMC_COOKIE          nCookie,     //[in]  Indentifier of selected node
  LPOLESTR __RPC_FAR* ppViewType,  //[out] Points to view type string
  long __RPC_FAR*     pViewOptions //[out] Points to MMC_VIEW_OPTIONS enumeration
)   
{
  _ASSERT( FALSE );                // This should never be called in 2.0
  return E_NOTIMPL;
}


//---------------------------------------------------------------------------
STDMETHODIMP CComponent::GetDisplayInfo
( 
  RESULTDATAITEM __RPC_FAR* pResultDataItem  //[in-out] Result item struct
)
{
  _ASSERT( NULL != pResultDataItem );
  _ASSERT( NULL != pResultDataItem->lParam ); 

  HRESULT  hResult = S_FALSE;

  LPBASENODE pNode = reinterpret_cast<LPBASENODE>(pResultDataItem->lParam);
  hResult = pNode->GetDisplayInfo( pResultDataItem );

  //TRACE_HRESULT( _T("GetDisplayInfo"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
STDMETHODIMP CComponent::CompareObjects
( 
  LPDATAOBJECT ipDataObjectA,    //[in] First data object to compare 
  LPDATAOBJECT ipDataObjectB     //[in] Second data object to compare 
)
{
  HRESULT hResult = S_FALSE;

  CDataObject* pDO_A = ExtractDataObjPtr( ipDataObjectA );
  CDataObject* pDO_B = ExtractDataObjPtr( ipDataObjectB );
  if( NULL == pDO_A || NULL == pDO_B )
    return hResult;

  (pDO_A->GetCookie() == pDO_B->GetCookie()) ? hResult = S_OK : hResult = S_FALSE;

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CComponent::QueryDispatch
(
  MMC_COOKIE         nCookie,    //[in]  Item for which IDispatch is requested
  DATA_OBJECT_TYPES  eType,      //[in]  Context of item
  LPDISPATCH*        pipDispatch //[out] IDispatch pointer
)
{
  return E_NOTIMPL;
}

//---------------------------------------------------------------------------
//  NOTE:  Failure to correctly implement this method will result in
//         the error:  "Snap-in failed to initialize"
//
HRESULT CComponent::GetResultViewType2
(
  MMC_COOKIE             nCookie,  //[in] Identifier of object
  PRESULT_VIEW_TYPE_INFO pRVTinfo  //[in,out] ViewTypeInfo struct
)
{
  HRESULT hResult = S_FALSE;

  if( NULL == nCookie ) 
  {
    CStaticNode* pNode = m_pComponentData->GetStaticNode();
    hResult = pNode->GetResultViewType2( nCookie, pRVTinfo );
  }
  else
  {
    CBaseNode* pNode = reinterpret_cast<CBaseNode*>(nCookie);
    hResult = pNode->GetResultViewType2( nCookie, pRVTinfo );
  }    

  TRACE_HRESULT(_T("GetResultViewType2"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CComponent::RestoreResultView
(
  MMC_COOKIE             nCookie,  //[in] Identifier of object
  PRESULT_VIEW_TYPE_INFO pRVTinfo  //[in,out] ViewTypeInfo struct
)
{
  return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
//  IExtendPropertySheet2


//---------------------------------------------------------------------------
//  PROPPAGE:  Nodes own their own property pages so we delegate creating
//             the pages.
//
STDMETHODIMP CComponent::CreatePropertyPages
( 
  LPPROPERTYSHEETCALLBACK lpProvider,  //[in] Pointer to callback interface
  LONG_PTR                Handle,      //[in] Handle for routing notification
  LPDATAOBJECT            ipDataObject //[in] Pointer to data object
)
{
  _ASSERT( NULL != ipDataObject );
  HRESULT hResult = S_FALSE;

  LPBASENODE pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL == pNode ) 
    return E_FAIL;

  return pNode->CreatePropertyPages( lpProvider, Handle );

}
            
//---------------------------------------------------------------------------
//  PROPPAGE:  If the Property Page verb is enabled, the console will call
//             this method to see if the node has a propery page to add.
//
STDMETHODIMP CComponent::QueryPagesFor
(
  LPDATAOBJECT ipDataObject  //[in] Pointer to selected data object
)
{
  _ASSERT( NULL != ipDataObject );
  HRESULT hResult = S_FALSE;

  LPBASENODE pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL == pNode ) 
    return E_FAIL;

  return pNode->QueryForPropertyPage();

}
            
//---------------------------------------------------------------------------
STDMETHODIMP CComponent::GetWatermarks
( 
  LPDATAOBJECT        ipDataObject,  //[in]  Pointer to data object
  HBITMAP __RPC_FAR*  lphWatermark,  //[out] Pointer to watermark bitmap
  HBITMAP __RPC_FAR*  lphHeader,     //[out] Pointer to header bitmap
  HPALETTE __RPC_FAR* lphPalette,    //[out] Pointer to palette
  BOOL __RPC_FAR*     bStretch       //[out] TRUE to stretch instead of tile
)
{
  _ASSERT( NULL != ipDataObject );
  HRESULT hResult = S_FALSE;


  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
//  Notification handlers


//---------------------------------------------------------------------------
HRESULT CComponent::OnAddImages
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to the selected data object
  LPARAM         nArg,         //[in] Pointer to IImageList
  LPARAM         nParam        //[in] HSCOPEITEM of selected/deselected item 

)
{
  HRESULT hResult = S_FALSE;
    
  if( NULL != nArg )           // May get this when shutting down
  {
    IImageList* ipImageList = reinterpret_cast<IImageList*>(nArg);
    hResult = ipImageList->ImageListSetStrip( (LONG_PTR*)m_hImageStrip16,
                                              (LONG_PTR*)m_hImageStrip32,
                                              0,
                                              RGB(0,255,0)
                                            );
  }
  TRACE_HRESULT(_T("OnAddImages"), hResult );
  return hResult;

} 

/////////////////////////////////////////////////////////////////////////////
//  Public helper methods

//---------------------------------------------------------------------------
//  Supplies interfaces to node objects.
//
HRESULT CComponent::GetInterface
( 
  DWORD dwRequestedInterface,  //[in] Request flag
  LONG_PTR* ppInterface        //[in-out] Interface pointer to return
)
{
  _ASSERT( NULL != ppInterface );
  HRESULT hResult = S_OK;

  switch( dwRequestedInterface )
  {
    case REQUEST_ICONSOLE:   
      _ASSERT( NULL != m_ipConsole );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipConsole);
      break; 

    case REQUEST_ICONSOLEVERB: 
      _ASSERT( NULL != m_ipConsoleVerb );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipConsoleVerb);
      break;   

    case REQUEST_IRESULTDATA:
      _ASSERT( NULL != m_ipResultData );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipResultData);
      break;

    case REQUEST_IHEADERCTRL2:
      _ASSERT( NULL != m_ipHeaderCtrl2 );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipHeaderCtrl2);
      break;

    case REQUEST_IDISPLAYHELP:
      _ASSERT( NULL != m_ipDisplayHelp );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipDisplayHelp);
      break;
    
    default:
      hResult = S_FALSE;
      *ppInterface = NULL;
      break;
  }
  return hResult;
}
