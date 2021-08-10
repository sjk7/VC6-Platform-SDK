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
#include "FolderNode.h"
#include "VirtualFile.h"

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
  m_ipConsole      = NULL;
  m_ipConsoleVerb  = NULL;
  m_ipResultData   = NULL;
  m_ipHeaderCtrl   = NULL;
  m_pScopeCookie   = NULL;
  m_pComponentData = pParent;

  m_ipControlbar     = NULL;           
  m_ipStaticToolbar  = NULL;           
  m_ipDeviceToolbar  = NULL;
  m_ipVFileToolbar   = NULL;
}

//---------------------------------------------------------------------------
CComponent::~CComponent()
{
}

/////////////////////////////////////////////////////////////////////////////
//  Implementation of IUnknown

//---------------------------------------------------------------------------
//  Add support for IComponent2 & IExtendControlBar 
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
  else if( IsEqualIID(riid, IID_IExtendControlbar) )
    *ppv = static_cast<IExtendControlbar*>(this);


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
		hResult = ipConsole->QueryInterface( IID_IConsole,(VOID**)&m_ipConsole );
		BREAK_ON_ERROR( hResult );

    hResult = m_ipConsole->QueryConsoleVerb( &m_ipConsoleVerb );
		BREAK_ON_ERROR( hResult ); 

    hResult = m_ipConsole->QueryInterface( IID_IResultData,(VOID**)&m_ipResultData );
    BREAK_ON_ERROR( hResult );

    hResult = m_ipConsole->QueryInterface( IID_IHeaderCtrl2,(VOID**)&m_ipHeaderCtrl );
    BREAK_ON_ERROR( hResult );

  }while( 0 );

  TRACE_HRESULT(_T("Initialize"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
STDMETHODIMP CComponent::Notify 
( 
  LPDATAOBJECT     ipDataObject,   //[in] Points to the selected data object
  MMC_NOTIFY_TYPE  MmcEvent,       //[in] Identifies action taken by user
  LONG             nArg,           //[in] Depends on the notification type
  LONG             nParam          //[in] Depends on the notification type
)
{
  HRESULT hResult = S_FALSE;       // Return this for unhandled notifications
  TRACE_EVENT( _T("Notify"), MmcEvent );

  if( NULL == ipDataObject )       // Not handling notifications with
    return hResult;                // NULL data objects

  // Make sure we have a valid node
  LPBASENODE pNode = ExtractBaseNodePtr( ipDataObject );
  if( NULL == pNode ) 
    return hResult;                     

  if( MMC_MULTI_SELECT_COOKIE == (INT_PTR)pNode )
    return S_OK;
                                       

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
      if( TRUE == nArg )     
        m_pScopeCookie = (LONG_PTR)ExtractBaseNodePtr(ipDataObject);
      else
        m_pScopeCookie = NULL; 

      break;

    case MMCN_VIEW_CHANGE:
      hResult = pNode->OnViewChange( ipDataObject, nArg, nParam, (LONG_PTR)this );
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
STDMETHODIMP CComponent::Destroy
( 
  MMC_COOKIE nCookie   //[in] Not used
)
{
  SAFE_RELEASE( m_ipConsole     );
  SAFE_RELEASE( m_ipHeaderCtrl  );
  SAFE_RELEASE( m_ipResultData  );
  SAFE_RELEASE( m_ipConsoleVerb );

  // Cached Controlbar/Toolbar interfaces are released in SetControlbar()

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
    return E_OUTOFMEMORY;

  if( MMC_MULTI_SELECT_COOKIE == nCookie )
  {
    hResult = QueryMultiSelDataObject( nCookie, nEnumType, &pNewObject );
  }
  else
  {
    pNewObject->SetPrivateData( nCookie, (ULONG)nEnumType );   
  }  

  hResult = pNewObject->QueryInterface( IID_IDataObject, (void**)ppDataObject );
  return hResult;
}

//---------------------------------------------------------------------------
//  Builds a multiselect data object
//
HRESULT CComponent::QueryMultiSelDataObject
( 
  MMC_COOKIE         nCookie,     //[in]  Indentifier of the selected node
  DATA_OBJECT_TYPES  nEnumType,   //[in]  Context in which this object was created 
  CDataObject**      ppDataObject //[out] Points to data object we create
)
{
  HRESULT        hResult  = S_OK;
  LPBASENODE     pTmpNode = NULL;
  CDataObject*   pMSelObj = *ppDataObject;
  RESULTDATAITEM rdi;                    

  ZeroMemory( &rdi, sizeof(RESULTDATAITEM) );
  rdi.mask   = RDI_STATE;
  rdi.nIndex = -1;
  rdi.nState = TVIS_SELECTED;
  
  // Store the basic info in the MS DataObject
  pMSelObj->SetPrivateData( nCookie, (ULONG)nEnumType );


  // Iterate through the selected items, create a new data object for each
  // and add it to the list
  while( S_OK == m_ipResultData->GetNextItem(&rdi) )
  {
    pTmpNode = reinterpret_cast<LPBASENODE>(rdi.lParam);   // Need to save this...
    pMSelObj->AddMultiSelectCookie( rdi.lParam );
  }
   
  // All our result items are of one type so there is only one GUID
  // to support in CCF_OBJECT_TYPES_IN_MULTI_SELECT 
  pMSelObj->AddMultiSelectGuid( &pTmpNode->GetNodeGUID() ); 

  //TRACE_PTR(_T("QueryMultiSelDataObject"),_T("pDO"), (ULONG_PTR)*ppDataObject );
  return hResult;
}

//---------------------------------------------------------------------------
//  This method not used when the Console's QI for IComponent2 is successful
//
STDMETHODIMP CComponent::GetResultViewType
( 
  MMC_COOKIE          nCookie,     //[in]  Indentifier of selected node
  LPOLESTR __RPC_FAR* ppViewType,  //[out] Points to view type string
  long __RPC_FAR*     pViewOptions //[out] Points to MMC_VIEW_OPTIONS enumeration
)   
{
  return E_NOTIMPL;
}


//---------------------------------------------------------------------------
STDMETHODIMP CComponent::GetDisplayInfo
( 
  RESULTDATAITEM __RPC_FAR* pResultDataItem  //[in][out] Result item struct
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
  return E_NOTIMPL;
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
//  If we support IComponent2 this method is called to set the view type
//  parameters.
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
//  Notification handlers


//---------------------------------------------------------------------------
HRESULT CComponent::OnAddImages
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to the selected data object
  LONG           nArg,         //[in] Pointer to IImageList
  LONG           nParam        //[in] HSCOPEITEM of selected/deselected item 

)
{
  HRESULT hResult = S_FALSE;
    
  HBITMAP hImageStrip16 = ::LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NODEIMAGES_16));
  HBITMAP hImageStrip32 = ::LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_NODEIMAGES_32));

  if( NULL != nArg )           // May get this when shutting down
  {
    IImageList* ipImageList = reinterpret_cast<IImageList*>(nArg);
    hResult = ipImageList->ImageListSetStrip( (LONG_PTR*)hImageStrip16,
                                              (LONG_PTR*)hImageStrip32,
                                              0,
                                              RGB(0,255,0)
                                            );
  }

  SAFE_FREE_BITMAP( hImageStrip16 );
  SAFE_FREE_BITMAP( hImageStrip32 );

  TRACE_HRESULT(_T("OnAddImages"), hResult );
  return hResult;
} 

/////////////////////////////////////////////////////////////////////////////
//  Interface IExtendControlBar


//---------------------------------------------------------------------------
//  TOOLBAR:  This method is only called when the static node is selected
//            after selecting the console root node.
//            We just build the toolbars with this notification, we do not
//            attach or display them.
//
HRESULT CComponent::SetControlbar 
( 
  LPCONTROLBAR ipControlbar  //[in] Pointer to the IControlbar interface
)
{
  HRESULT hResult = S_FALSE;

  if( NULL == ipControlbar )           // Snap-in is deactivating
  {
    if( NULL == m_ipControlbar )       // Needed to prevent AVs
      return hResult;

    hResult = m_ipControlbar->Detach( (LPUNKNOWN)m_ipStaticToolbar );

    SAFE_RELEASE( m_ipVFileToolbar  );
    SAFE_RELEASE( m_ipDeviceToolbar ); // We release these here instead of
    SAFE_RELEASE( m_ipStaticToolbar ); // Destroy() because this gets called
    SAFE_RELEASE( m_ipControlbar    ); // after Destroy()
                                                                         
    return hResult;
  }

  if( NULL == m_ipControlbar )         // Cache the control bar if we don't
  {                                    // have it already
    m_ipControlbar = ipControlbar;
    m_ipControlbar->AddRef();
  }

  if( NULL == m_ipStaticToolbar )      // Static Node toolbar not created 
  {                                    
    hResult = m_ipControlbar->Create( TOOLBAR, this, (LPUNKNOWN*)&m_ipStaticToolbar );

    HBITMAP hbmpStaticToolbar = LoadBitmap( g_hInst, MAKEINTRESOURCE(IDR_STATIC_TOOLBAR) );
    hResult = m_ipStaticToolbar->AddBitmap( 1, hbmpStaticToolbar, 16, 16, RGB(0,255,0) );

    hResult = m_ipStaticToolbar->AddButtons(1, StaticToolButtons);
  }

  if( NULL == m_ipDeviceToolbar )      // Device Node toolbar not created 
  {                                    
    hResult = m_ipControlbar->Create( TOOLBAR, this, (LPUNKNOWN*)&m_ipDeviceToolbar );

    HBITMAP hbmpDeviceToolbar = LoadBitmap( g_hInst, MAKEINTRESOURCE(IDR_DEVICE_TOOLBAR) );
    hResult = m_ipDeviceToolbar->AddBitmap( 1, hbmpDeviceToolbar, 16, 16, RGB(0,255,0) );

    hResult = m_ipDeviceToolbar->AddButtons(2, DeviceToolButtons);
  }

  if( NULL == m_ipVFileToolbar )       // Virtual File toolbar not created 
  {                                    
    hResult = m_ipControlbar->Create( TOOLBAR, this, (LPUNKNOWN*)&m_ipVFileToolbar );

    HBITMAP hbmpVFileToolbar = LoadBitmap( g_hInst, MAKEINTRESOURCE(IDR_VFILE_TOOLBAR) );
    hResult = m_ipVFileToolbar->AddBitmap( 1, hbmpVFileToolbar, 16, 16, RGB(0,255,0) );

    hResult = m_ipVFileToolbar->AddButtons(1, VFileToolButtons);
  }

  return hResult;
}


//---------------------------------------------------------------------------
//  Handle notifications from our custom toolbars 
//
HRESULT CComponent::ControlbarNotify 
( 
  MMC_NOTIFY_TYPE MmcEvent,  //[in] User action event
  LPARAM          nArg,      //[in] Depends on the event parameter
  LPARAM          lParam     //[in] Depends on the event parameter
)            
{
  HRESULT hResult = S_FALSE;
  TRACE_START(_T("ControlbarNotify") );

  switch( MmcEvent )
  {
    case MMCN_SELECT:
    {
      _ASSERT( NULL != lParam );
      LPBASENODE pNode = ExtractBaseNodePtr( reinterpret_cast<IDataObject*>(lParam) );
      if( NULL == pNode )
      {
        // MULTISELECT:  If pNode is NULL, the data object doesn't belong to
        // us.  If a multiple selection was made, the data object will be a
        // composite data object from the console which supports the clipboard
        // format CCF_MMC_MULTISELECT_DATAOBJECT.  If the return value is 1,
        // then this is a multiselect data object.   
        // There are two ways to handle this:
        // - Just return S_OK.  That will result in the toolbar buttons being
        //   greyed out. 
        // - Enable toolbar buttons for all result item types.  
        //
        // Note: IsCompositeDataObject is defined in Globals.cpp
        
        if( IsCompositeDataObject( (IDataObject*)lParam ) )            
        {
          BOOL bSelect = (BOOL)HIWORD(nArg);
          if( TRUE == bSelect )
          {
            hResult = m_ipControlbar->Attach(TOOLBAR, (LPUNKNOWN)m_ipVFileToolbar);
            hResult = m_ipVFileToolbar->SetButtonState( IDM_CLEAR_ATTRIBS, ENABLED, TRUE );
          }
          else
          {
            hResult = m_ipControlbar->Detach( (LPUNKNOWN)m_ipVFileToolbar );
          } 
        }  // Not a composite data object, return S_FALSE
      } 
      else // pNode is not null, must be single selection
      {
        hResult = pNode->ControlbarNotify( nArg, lParam, (LONG_PTR)this );
      }
      break;
    }
    case MMCN_BTN_CLICK:
    {
      _ASSERT( NULL != nArg );

      // MULTISELECT:  First we have to determine if this is a single selection 
      // or a multiselect.  We do a double test, first is the data object our 
      // own.  If yes then definitely a single selection was made. 

      LPBASENODE pNode = ExtractBaseNodePtr( reinterpret_cast<IDataObject*>(nArg) );
      if( NULL == pNode )
      {
        // If the data object is not ours, is it a MMC Composite Data Object?
        if( IsCompositeDataObject( (IDataObject*)nArg ) )            
        {
          // If it's a MMC Composite Data Object, extract the data which is
          // stored as a SMMCDataObject.  First we extract this object, then
          // from it we get the cookie array.  The cookie array is our own 
          // custom clipboard format which stores an array of pointers to the
          // selected nodes.  Then for each node we delegate the command.  
          // Don't forget to update all views to reflect any changes.

          FORMATETC FormatEtc = { g_cfMS_Snapins, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};       
          STGMEDIUM StgMedium = { TYMED_HGLOBAL,  NULL };

          IDataObject* ipDO = reinterpret_cast<IDataObject*>(nArg);
          hResult = ipDO->GetData( &FormatEtc, &StgMedium );
          if( S_OK == hResult )
          {
            SMMCDataObjects* pMSObjs = (SMMCDataObjects*)StgMedium.hGlobal;
            for( DWORD dwObjCount = 0; dwObjCount < pMSObjs->count; dwObjCount++ )
            {            
              IDataObject* ipDO = pMSObjs->lpDataObject[dwObjCount];
              FORMATETC FormatEtc = { g_cfMS_Cookies, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};       
              STGMEDIUM StgMedium = { TYMED_HGLOBAL,  NULL };

              hResult = ipDO->GetData( &FormatEtc, &StgMedium );
              _ASSERT( S_OK == hResult );

              MULTISELECT_COOKIES* pCookieArray = (MULTISELECT_COOKIES*)GlobalLock(StgMedium.hGlobal); 
              CVirtualFile* pNode = NULL;              

              for( DWORD dwIndex = 0; dwIndex < pCookieArray->count; dwIndex++ )
              {
                pNode = (CVirtualFile*)pCookieArray->Cookies[dwIndex];
                hResult = pNode->Command( lParam );
              }
              LPDATAOBJECT pTmpDO = NULL;
              QueryDataObject( (MMC_COOKIE)pNode->GetParent(), CCT_SCOPE, &pTmpDO );
              hResult = m_ipConsole->UpdateAllViews( pTmpDO, 0, 0 );
              pTmpDO->Release();                 // Free the temp data object

              GlobalUnlock( StgMedium.hGlobal );
              GlobalFree( StgMedium.hGlobal );   // Free the cookie array
            }
            GlobalFree( StgMedium.hGlobal );     // Free SMMCDataObjects
          }
        }  // Return whatever we got from ipDO->GetData()
      }
      else // Single selection was made
      {
        hResult = pNode->Command( lParam );  
        LPDATAOBJECT pTmpDO = NULL;
        QueryDataObject( (MMC_COOKIE)((CVirtualFile*)pNode)->GetParent(), CCT_SCOPE, &pTmpDO );
        hResult = m_ipConsole->UpdateAllViews( pTmpDO, 0, 0 );
        pTmpDO->Release();                 // Free the temp data object
      }        
      break;
    }
    default:
      break; 
  }
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

    case REQUEST_IHEADERCTRL:
      _ASSERT( NULL != m_ipHeaderCtrl );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipHeaderCtrl);
      break;

    case REQUEST_ICONTROLBAR:
      _ASSERT( NULL != m_ipControlbar );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipControlbar);
      break;

    case REQUEST_ISTATICTOOLBAR:
      _ASSERT( NULL != m_ipStaticToolbar );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipStaticToolbar);
      break;

    case REQUEST_IDEVICETOOLBAR:
      _ASSERT( NULL != m_ipDeviceToolbar );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipDeviceToolbar);
      break;

    case REQUEST_IVFILETOOLBAR:
      _ASSERT( NULL != m_ipVFileToolbar );
      *ppInterface = reinterpret_cast<LONG_PTR>(m_ipVFileToolbar);
      break;

   default:
      hResult = S_FALSE;
      *ppInterface = NULL;
      break;
  }
  return hResult;
}
