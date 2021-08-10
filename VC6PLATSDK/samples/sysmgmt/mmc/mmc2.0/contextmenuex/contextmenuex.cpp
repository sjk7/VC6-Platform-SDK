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
#include "ContextMenuEx.h"
#include "Resource.h"

                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CExtendContextMenuEx")

/////////////////////////////////////////////////////////////////////////////
//  Implementation of IUnknown

//---------------------------------------------------------------------------
// MMC will only QI for IExtendContextMenu in an extension.
//
STDMETHODIMP CExtendContextMenuEx::QueryInterface
(
  REFIID   riid,       //[in] Identifier of the requested interface
  LPVOID   *ppv        //[out] Address of requested interface 
)
{
  if( !ppv )
    return E_FAIL;
    
  *ppv = NULL;
    
  if( IsEqualIID(riid, IID_IUnknown) )
    *ppv = static_cast<IExtendContextMenu*>(this);
  else if( IsEqualIID(riid, IID_IExtendContextMenu) )
    *ppv = static_cast<IExtendContextMenu*>(this);


  if( *ppv )
  {
    reinterpret_cast<IUnknown*>(*ppv)->AddRef();
    return S_OK;
  }
    
  return E_NOINTERFACE;
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CExtendContextMenuEx::AddRef()
{
  return InterlockedIncrement((LONG*)&m_cRef);
}

//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CExtendContextMenuEx::Release()
{
  if( InterlockedDecrement((LONG*)&m_cRef) == 0 )
  {
    delete this;
    return 0;
  }
  return m_cRef;
}

/////////////////////////////////////////////////////////////////////////////
//  Construction-Destruction

//---------------------------------------------------------------------------
CExtendContextMenuEx::CExtendContextMenuEx()
{
  InterlockedIncrement((long*)&g_uObjectCount);  

  m_cRef = 0;

  TRACE_START(_T("New instance of CExtendContextMenuEx") );
}

//---------------------------------------------------------------------------
CExtendContextMenuEx::~CExtendContextMenuEx()
{
  InterlockedDecrement((long*)&g_uObjectCount);
}


/////////////////////////////////////////////////////////////////////////////
//  IExtendContextMenu

//---------------------------------------------------------------------------
//  Devices can only add a folder
//
HRESULT CExtendContextMenuEx::AddMenuItems
( 
  LPDATAOBJECT ipDataObject,         //[in] Data object  
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  _ASSERT( NULL != ipCallback );
  HRESULT hResult = S_FALSE;

  static CONTEXTMENUITEM ctxMenu;           
    ctxMenu.lCommandID        = IDM_QUERY_ATTRIBS;
    ctxMenu.lInsertionPointID = CCM_INSERTIONPOINTID_3RDPARTY_TASK; 
    ctxMenu.fFlags            = 0;
    ctxMenu.fSpecialFlags     = 0;
    ctxMenu.strName           = L"Query Attributes";
    ctxMenu.strStatusBarText  = L"Query Device Attributes";


  // Add the Query item to the Task menu if allowed...
  if( CCM_INSERTIONALLOWED_TASK & *pInsertionAllowed )
  {
    hResult = ipCallback->AddItem( &ctxMenu );
  }  

  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CExtendContextMenuEx::Command
( 
  long lCommandID,          //[in] Indentifier for menu ID
  LPDATAOBJECT ipDataObject
)
{
  HRESULT hResult = S_OK;

  switch( lCommandID )
  {  
    case IDM_QUERY_ATTRIBS:
    {
      MsgBox( _T("New Queries not supported"), _T("Test") );
      break;
    }
    default:
      hResult = S_FALSE;
      break;

  }
  return hResult;
}
            

/////////////////////////////////////////////////////////////////////////////
//  Private methods


