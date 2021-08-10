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


CDataObject::CDataObject()  
{
  m_cRef     = 0;
  m_uCookie  = 0;
  m_uContext = 0;
  
}

CDataObject::~CDataObject()
{
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
VOID CDataObject::SetPrivateData
(
  ULONG_PTR  uCookie,      //[in] Pointer to node this object represents
  ULONG  uContext      //[in] Context of the node
)
{
  m_uCookie  = uCookie;
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

