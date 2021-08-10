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
  m_pComponentData = pParent;

}

//---------------------------------------------------------------------------
CComponent::~CComponent()
{
}

/////////////////////////////////////////////////////////////////////////////
//  Implementation of IUnknown

//---------------------------------------------------------------------------
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
  HRESULT hResult = S_OK;

  // Have to return S_OK here or we will get the dreaded message
  // "The selected snap-in did not initialize properly"
    
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
  TRACE_EVENT( _T("Notify"), MmcEvent );
  // Not doing anything here except providing trace output for 
  // MMC's notifications

  return E_NOTIMPL;
}

//---------------------------------------------------------------------------
STDMETHODIMP CComponent::Destroy
( 
  MMC_COOKIE nCookie   //[in] Not used
)
{
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
  return E_NOTIMPL;
}

//---------------------------------------------------------------------------
//  Delegate this to the static node
//
STDMETHODIMP CComponent::GetResultViewType
( 
  MMC_COOKIE          nCookie,     //[in]  Indentifier of selected node
  LPOLESTR __RPC_FAR* ppViewType,  //[out] Points to view type string
  long __RPC_FAR*     pViewOptions //[out] Points to MMC_VIEW_OPTIONS enumeration
)   
{
  HRESULT hResult = E_NOTIMPL;   //S_FALSE;

  _ASSERT( FALSE );    //BUGLIST:  Should never get called

/*
  if( NULL == nCookie ) 
  {
    CStaticNode* pNode = m_pComponentData->GetStaticNode();
    hResult = pNode->GetResultViewType( ppViewType, pViewOptions );
  }
  else
  {
    _ASSERT( FALSE );
  }    
*/

  return hResult;
}


//---------------------------------------------------------------------------
STDMETHODIMP CComponent::GetDisplayInfo
( 
  RESULTDATAITEM __RPC_FAR* pResultDataItem  //[in][out] Result item struct
)
{
  HRESULT hResult = S_FALSE;

  // This never gets called in this sample
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
    _ASSERT( FALSE );
  }    

  TRACE_HRESULT(_T("GetResultViewType2"), hResult );
  return hResult;
}



//---------------------------------------------------------------------------
HRESULT CComponent::RestoreResultView
(
  MMC_COOKIE             nCookie,         //[in] Identifier of object
  PRESULT_VIEW_TYPE_INFO pResultViewType  //[in,out] View type info data
)
{
  return E_NOTIMPL;
}

