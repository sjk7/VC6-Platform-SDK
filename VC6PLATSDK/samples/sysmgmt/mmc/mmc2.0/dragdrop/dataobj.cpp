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
  m_uCookie  = 0;
  m_uContext = 0;

  m_uNodeTypeFlg   = 0;                // DRAGDROP: New data members
  m_pEnumFormatEtc = NULL;
}

//---------------------------------------------------------------------------
// MMC20: In versions 1.X of MMC the pointer returned by ::EnumFormatEtc()
//        was leaked.  This is fixed in 2.X but will cause an AV when your
//        1.X Snap-in runs on 2.X, and you release the cached pointer used
//        to work around the leak.  If your code needs to run on both
//        platforms you should do something like this:
//
CDataObject::~CDataObject()
{
  if( g_CV.nMajor < 2 )      // Running under MMC 1.X
  {
    if( NULL != m_pEnumFormatEtc )
    {
      LONG cRef = m_pEnumFormatEtc->Release();
      _ASSERT( 0 == cRef );
    } 
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
  if( InterlockedDecrement((LONG*)&m_cRef) == 0 )
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
  FORMATETC* pFormatEtc,     //[in]  Pointer to the FORMATETC structure 
  STGMEDIUM* pMedium         //[out] Pointer to the STGMEDIUM structure  
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
//  DRAGDROP:  Support for the two custom clipboard formats we need to 
//             make interprocess DragDrop work
//
HRESULT CDataObject::GetData
(
  FORMATETC*  pFormatEtc,    //[in]  Pointer to the FORMATETC structure 
  STGMEDIUM*  pStgMedium     //[out] Pointer to the STGMEDIUM structure 
)
{
  HRESULT hResult = DATA_E_FORMATETC;

  if( g_cfNodePropPtr == pFormatEtc->cfFormat )  // Looking for Node Properties
  {
    hResult = RetrieveNodePropPtr( pStgMedium );
  }
  else if( g_cfNodeTypeFlg == pFormatEtc->cfFormat )
  {
    hResult = RetrieveNodeTypeFlg( pStgMedium );
  }

  return hResult;
}


//---------------------------------------------------------------------------
//  DRAGDROP:  We now implement this method so that the caller can test
//             to see if a clipformat is supported by GetData
//
HRESULT CDataObject::QueryGetData
(
  FORMATETC* pFormatEtc      //[in] FormatEtc struct to test
)
{
  HRESULT hResult = DATA_E_FORMATETC;

  if( (DVASPECT_CONTENT & pFormatEtc->dwAspect) && (TYMED_HGLOBAL & pFormatEtc->tymed) )
  {
    if( g_cfNodePropPtr == pFormatEtc->cfFormat )  
    {  
      hResult = S_OK;
    }
    else if( g_cfNodeTypeFlg == pFormatEtc->cfFormat )  
    {  
      hResult = S_OK;
    }
  }

  return hResult;
}


//---------------------------------------------------------------------------
//  The console will call this to get the enumeration of custom clipboard
//  formats we support for DragDrop.
//
HRESULT CDataObject::EnumFormatEtc 
(
  DWORD            dwDirection,      //[in]  Only DATADIR_GET supported
  LPENUMFORMATETC* ppEnumFormatEtc   //[out] Points to IEnumFormatEtc
)
{
  HRESULT hResult = S_FALSE;

  static FORMATETC FormatArray[2];   // Use array so we can add more later 

  FormatArray[0].cfFormat  = g_cfNodePropPtr;
  FormatArray[0].dwAspect  = DVASPECT_CONTENT;
  FormatArray[0].ptd       = NULL;
  FormatArray[0].tymed     = TYMED_HGLOBAL;
  FormatArray[0].lindex    = -1;

  FormatArray[1].cfFormat  = g_cfNodeTypeFlg;
  FormatArray[1].dwAspect  = DVASPECT_CONTENT;
  FormatArray[1].ptd       = NULL;
  FormatArray[1].tymed     = TYMED_HGLOBAL;
  FormatArray[1].lindex    = -1;
  

  switch( dwDirection )
  {
    case DATADIR_GET:
    {
      if( NULL == m_pEnumFormatEtc )
        m_pEnumFormatEtc = new CEnumFormatEtc( 2, FormatArray );

      *ppEnumFormatEtc = m_pEnumFormatEtc;
      (*ppEnumFormatEtc)->AddRef();
      hResult = S_OK;
      break;
    }
    case DATADIR_SET:
    {
      *ppEnumFormatEtc = NULL;
      hResult = E_FAIL;
      break;
    }
  }
  return hResult;
}


//---------------------------------------------------------------------------
VOID CDataObject::SetPrivateData
(
  ULONG  uCookie,      //[in] Pointer to node this object represents
  ULONG  uContext      //[in] Context of the node
)
{
  m_uCookie  = uCookie;
  m_uContext = uContext;

  LPBASENODE pNode = reinterpret_cast<LPBASENODE>(m_uCookie);
  m_uNodeTypeFlg   = pNode->GetNodeType();
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
  IStream* ipStream        //[in][out] Stream to return our data in.
)
{                              
  CBaseNode* pNode = reinterpret_cast<CBaseNode*>(m_uCookie);  
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
  IStream* ipStream        //[in][out] Stream to return our data in.
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
  IStream* ipStream        //[in][out] Stream to return our data in.
)
{
  CBaseNode* pNode = reinterpret_cast<CBaseNode*>(m_uCookie);  
  GUID* pGuid = (GUID*)&pNode->GetNodeGUID();

  return ipStream->Write( (void*)pGuid, sizeof(GUID), NULL );
}


//---------------------------------------------------------------------------
//  CCF_SZNODETYPE is a required clipboard format.
//  We return the node's GUID as a wide string.
//
HRESULT CDataObject::RetrieveGuidString
( 
  IStream* ipStream        //[in][out] Stream to return our data in.
)
{
  LPOLESTR pszGUID;
  CBaseNode* pNode = reinterpret_cast<CBaseNode*>(m_uCookie);  

  HRESULT  hResult = StringFromCLSID( pNode->GetNodeGUID(), &pszGUID );
  if( S_OK == hResult )
  {
    hResult = ipStream->Write( pszGUID, (wcslen(pszGUID) + 1) * sizeof(WCHAR), NULL );
    CoTaskMemFree( pszGUID );
  }

  return hResult;
} 

/////////////////////////////////////////////////////////////////////////////
//  Handlers for the Snap-in's custom clipboard formats


//---------------------------------------------------------------------------
//  DRAGDROP: Memory for the NodeProps struct is globally allocated by the 
//            node and free'd by the target node.  We just pass it on.
//
HRESULT CDataObject::RetrieveNodePropPtr
( 
  STGMEDIUM*  pStgMedium     //[out] Struct to store the data in
)
{
  _ASSERT( NULL != pStgMedium );
  HRESULT hResult = S_OK;

  LPBASENODE  pNode = reinterpret_cast<LPBASENODE>(m_uCookie);
  LPNODEPROPS pNodeProps = NULL;
  pNode->GetProperties( &pNodeProps );
  if( NULL == pNodeProps )
  {
    hResult = E_OUTOFMEMORY;
  }
  else
  {
    pStgMedium->hGlobal = (HGLOBAL)pNodeProps;     // 
    pStgMedium->tymed   = TYMED_HGLOBAL;
    pStgMedium->pUnkForRelease = NULL;
  }

  return hResult;
}


//---------------------------------------------------------------------------
//  DRAGDROP:  Since this project supports interprocess Copy/Cut/Paste,
//             we need a custom clipboard format which will return the
//             node type without using pointers
//
HRESULT CDataObject::RetrieveNodeTypeFlg
( 
  STGMEDIUM*  pStgMedium     //[out] Struct to store the data in
)
{
  _ASSERT( NULL != pStgMedium );
  HRESULT hResult = S_OK;

  ULONG* pNodeTypeFlg = (ULONG*)::GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, sizeof(ULONG) );
  if( NULL == pNodeTypeFlg )
  {
    hResult = E_OUTOFMEMORY;
  }
  else
  {
    pNodeTypeFlg  = (ULONG*)::GlobalLock( pNodeTypeFlg );
    *pNodeTypeFlg = m_uNodeTypeFlg;
    ::GlobalUnlock( pNodeTypeFlg );

    pStgMedium->hGlobal = pNodeTypeFlg;     
    pStgMedium->tymed   = TYMED_HGLOBAL;
    pStgMedium->pUnkForRelease = NULL;
  }

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CDataObject::RetrieveBaseNodePtr
( 
  IStream* ipStream        //[in][out] Stream to return our data in.
)
{
  LPBASENODE pNode = reinterpret_cast<LPBASENODE>(m_uCookie);
  return ipStream->Write( &pNode, sizeof(LPBASENODE), NULL );
}

//---------------------------------------------------------------------------
HRESULT CDataObject::RetrieveDataObjPtr
( 
  IStream* ipStream        //[in][out] Stream to return our data in.
)
{
  CDataObject* pThis = this;
  return ipStream->Write( &pThis, sizeof(CDataObject*), NULL );
}

