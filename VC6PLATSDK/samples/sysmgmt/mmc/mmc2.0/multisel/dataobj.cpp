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
#include "DataObj.h"
#include "StaticNode.h"

                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CDataObject")


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction


//---------------------------------------------------------------------------
CDataObject::CDataObject()  
{
  m_cRef     = 0;
  m_nCookie  = 0;
  m_uContext = 0;
  
}

//---------------------------------------------------------------------------
//
//
CDataObject::~CDataObject()
{
  if( MMC_MULTI_SELECT_COOKIE == m_nCookie ) 
  {
    // The object list contains pointers to IDataObjects which store info
    // on multiselect nodes.  MMC doesn't know about these so we need to 
    // clean them up
    //
    //LPDATAOBJECT pDO = NULL;
    //POSITION     Pos = m_ObjectList.GetHeadPosition();
    //while( Pos )
    //{
    //  pDO = m_ObjectList.GetNext( Pos );
    //  pDO->Release();
    //}

    // The Cookie list just has pointers to nodes, just delete the list 
    m_CookieList.RemoveAll();              

    // The Guid list just has pointers to GUIDs, just delete the list.
    m_GuidList.RemoveAll();
  }
}

/////////////////////////////////////////////////////////////////////////////
// IUnknown implementation

//---------------------------------------------------------------------------
STDMETHODIMP CDataObject::QueryInterface
(
  REFIID   riid,
  LPVOID*  ppv
)
{
  if( !ppv )
    return E_FAIL;
    
  HRESULT hResult = E_NOINTERFACE;
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
    *ppv = static_cast<IDataObject*>(this);
  else if( IsEqualIID(riid, IID_IDataObject) )
    *ppv = static_cast<IDataObject*>(this);
    
  if( *ppv )
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    hResult = S_OK;
  }
    
  return hResult;
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CDataObject::AddRef()
{
    return InterlockedIncrement((LONG*)&m_cRef);
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CDataObject::Release()
{
  if (InterlockedDecrement((LONG*)&m_cRef) == 0)
  {
    delete this;
    return 0;
  }
  return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
// IDataObject implementation
// 

//---------------------------------------------------------------------------
//  MMC will call GetDataHere() for it's required clipboard formats
//
HRESULT CDataObject::GetDataHere
(
  FORMATETC *pFormatEtc,     //[in]  Pointer to the FORMATETC structure 
  STGMEDIUM *pMedium         //[out] Pointer to the STGMEDIUM structure  
)
{
  const CLIPFORMAT cf = pFormatEtc->cfFormat;
  IStream* ipStream = NULL;

  HRESULT hResult = CreateStreamOnHGlobal( pMedium->hGlobal, FALSE, &ipStream );
  if( S_OK != hResult )
    return hResult;                        // Minimal error checking
    
  hResult = DV_E_FORMATETC;                // Unknown format

  if( cf == g_cfDisplayName )
  {
    hResult = RetrieveDisplayString( ipStream );
  }  
  else if( cf == g_cfSnapinClsid )
  {
    hResult = RetrieveSnapInClassID( ipStream );
  } 
  else if( cf == g_cfNodeType )
  {
    hResult = RetrieveNodeTypeGuid( ipStream );
  }
  else if( cf == g_cfszNodeType )
  {
    hResult = RetrieveGuidString( ipStream );
  }
  else if( cf == g_cfBaseNodePtr )
  {
    hResult = RetrieveBaseNodePtr( ipStream );
  }
  else if( cf == g_cfDataObjPtr )
  {
    hResult = RetrieveDataObjPtr( ipStream );
  }
  
  ipStream->Release();
    
  return hResult;
}

//---------------------------------------------------------------------------
//  MULTISELECT: MMC will call here for multiselect clipboard formats
//
HRESULT CDataObject::GetData
(
  FORMATETC* pFormatEtc,     //[in]  Pointer to the FORMATETC structure 
  STGMEDIUM* pStgMedium      //[out] Pointer to the STGMEDIUM structure  
)
{
  HRESULT hResult = DV_E_FORMATETC;

  do
  {
    if( g_cfMS_Cookies == pFormatEtc->cfFormat )
    {
      hResult = RetrieveMultiSelectCookies( pStgMedium );
      continue;
    }
    if( g_cfMS_Objects == pFormatEtc->cfFormat )
    {
      hResult = RetrieveMultiSelectTypes( pStgMedium );
      continue;
    }
    if( g_cfMS_IsMsObj == pFormatEtc->cfFormat )
    {
      hResult = S_FALSE;
      continue;
    }
  }while( 0 );

  return hResult;
}

//---------------------------------------------------------------------------
VOID CDataObject::SetPrivateData
(
  INT_PTR  nCookie,      //[in] Pointer to node this object represents
  ULONG    uContext      //[in] Context of the node
)
{
  m_nCookie  = nCookie;
  m_uContext = uContext;
}

/////////////////////////////////////////////////////////////////////////////
//  Handlers for MMC's required clipboard formats


//---------------------------------------------------------------------------
// CCF_DISPLAY_NAME is one of the required clipformats.
// MMC askes for this string to display the name of the SnapIn's StaticNode
// in the ScopePane
//                                        
HRESULT CDataObject::RetrieveDisplayString
( 
  IStream* ipStream        //[in-out] Stream to return our data in.
)
{                              
  CBaseNode* pNode = reinterpret_cast<CBaseNode*>(m_nCookie);  
  LPWSTR pNodeName = pNode->GetNodeName();

  ULONG ulSizeofName = (wcslen(pNodeName) + 1) * sizeof(WCHAR);
  return ipStream->Write(pNodeName, ulSizeofName, NULL);

} 

//---------------------------------------------------------------------------
//  CCF_SNAPIN_CLASSID is one of the required clipformats.
//  MMC will ask for this data.  This ClassID which we return represents
//  the COM object which is the entry point for our SnapIn
//
HRESULT CDataObject::RetrieveSnapInClassID
( 
  IStream* ipStream        //[in-out] Stream to return our data in.
)
{
  return ipStream->Write( &CLSID_CComponentData, sizeof(GUID), NULL );
} 


//---------------------------------------------------------------------------
//  CCF_NODETYPE is one of the required clipformats.
//  MMC needs the NodeType GUID to determine what extensions to activate
//  for a node.  It looks under the MMC/NodeTypes registry key for the GUID
//  and enumerates the extensions found beneath it.  MMC uses this GUID
//  strictly as a uniquie identifier.  It does not expect it to correspond
//  to the ClaseID of a com object. 
//
HRESULT CDataObject::RetrieveNodeTypeGuid
( 
  IStream* ipStream        //[in-out] Stream to return our data in.
)
{
  CBaseNode* pNode = reinterpret_cast<CBaseNode*>(m_nCookie);  
  GUID* pGuid = (GUID*)&pNode->GetNodeGUID();

  return ipStream->Write( (void*)pGuid, sizeof(GUID), NULL );
}


//---------------------------------------------------------------------------
//  CCF_SZNODETYPE is a required clipboard format.
//  We return the node's GUID as a wide string.
//
HRESULT CDataObject::RetrieveGuidString
( 
  IStream* ipStream        //[in-out] Stream to return our data in.
)
{
  LPOLESTR pszGUID;
  CBaseNode* pNode = reinterpret_cast<CBaseNode*>(m_nCookie);  

  HRESULT  hResult = StringFromCLSID( pNode->GetNodeGUID(), &pszGUID );
  if( S_OK == hResult )
  {
    hResult = ipStream->Write( pszGUID, (wcslen(pszGUID) + 1) * sizeof(WCHAR), NULL );
    CoTaskMemFree( pszGUID );
  }

  return hResult;
} 

//---------------------------------------------------------------------------
HRESULT CDataObject::RetrieveBaseNodePtr
( 
  IStream* ipStream        //[in-out] Stream to return our data in.
)
{
  LPBASENODE pNode = reinterpret_cast<LPBASENODE>(m_nCookie);
  return ipStream->Write( &pNode, sizeof(LPBASENODE), NULL );
}

//---------------------------------------------------------------------------
HRESULT CDataObject::RetrieveDataObjPtr
( 
  IStream* ipStream        //[in-out] Stream to return our data in.
)
{
  CDataObject* pThis = this;
  return ipStream->Write( &pThis, sizeof(CDataObject*), NULL );
}

/////////////////////////////////////////////////////////////////////////////
//  MULTISELECT:  Support for multiselect clipformats and helper methods


//---------------------------------------------------------------------------
//  
//

HRESULT CDataObject::RetrieveMultiSelectCookies
( 
  STGMEDIUM* pStgMedium      //[out] Pointer to the STGMEDIUM structure 
)
{
  HRESULT hResult = S_OK;
  DWORD dwMemSize = (m_CookieList.GetCount() * sizeof(LONG_PTR)) + sizeof(DWORD);
  
  HGLOBAL hMem =  GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, dwMemSize);
  if( NULL == hMem )
    hResult = E_OUTOFMEMORY;               
  else
  {
    MULTISELECT_COOKIES* pMSCookies = (MULTISELECT_COOKIES*)GlobalLock( hMem );
    pMSCookies->count = m_CookieList.GetCount();
   
    LONG nIndex  = 0;
    POSITION Pos = m_CookieList.GetHeadPosition();    
    while( Pos )
    {
      pMSCookies->Cookies[nIndex] = m_CookieList.GetNext( Pos );        
      nIndex++;
    }

    GlobalUnlock( hMem );
    pStgMedium->hGlobal        = hMem;
    pStgMedium->tymed          = TYMED_HGLOBAL;
    pStgMedium->pUnkForRelease = NULL;
  }
  return hResult;
}

//---------------------------------------------------------------------------
//  MULTISELECT:  Support for CCF_OBJECT_TYPES_IN_MULTI_SELECT 
//
HRESULT CDataObject::RetrieveMultiSelectTypes
( 
  STGMEDIUM* pStgMedium      //[out] Pointer to the STGMEDIUM structure 
)
{
  HRESULT hResult = S_OK;
  DWORD dwMemSize = (m_GuidList.GetCount() * sizeof(GUID)) + sizeof(DWORD);

  DATA_OBJECT_TYPES type = (DATA_OBJECT_TYPES)m_uContext;

  HGLOBAL hMem =  GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, dwMemSize );
  if( NULL == hMem )
    hResult = E_OUTOFMEMORY;               
  else
  {
    SMMCObjectTypes* pMSObjTypes = (SMMCObjectTypes*)GlobalLock( hMem );
    pMSObjTypes->count = m_GuidList.GetCount();
   
    LONG nIndex  = 0;
    POSITION Pos = m_GuidList.GetHeadPosition();    
    while( Pos )
    {
      CopyMemory( (void*)&pMSObjTypes->guid[nIndex], (void*)m_GuidList.GetNext( Pos ), sizeof(GUID) );
      nIndex++;
    }

    GlobalUnlock( hMem );
    pStgMedium->hGlobal        = hMem;
    pStgMedium->tymed          = TYMED_HGLOBAL;
    pStgMedium->pUnkForRelease = NULL;
  }

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CDataObject::AddMultiSelectCookie
( 
  LONG_PTR   nCookie         //[in] Cookie to add to multiselect list
)
{
  _ASSERT( nCookie > 0 ); 
  m_CookieList.AddTail( nCookie );     // Add the data object to our list 

  return S_OK;
}

//---------------------------------------------------------------------------
//  MULTISELECT:  Add a new GUID pointer to the list.  This method places 
//  the onus of determining the uniqueness of GUIDs on the caller.  All
//  GUIDs in this list must be unique.
//
HRESULT CDataObject::AddMultiSelectGuid
( 
  GUID*  pGuid         //[in] GUID to add to multiselect list
)
{
  _ASSERT( NULL != pGuid );
  m_GuidList.AddTail( pGuid );     // Add the GUID to our list 

  return S_OK;
}

