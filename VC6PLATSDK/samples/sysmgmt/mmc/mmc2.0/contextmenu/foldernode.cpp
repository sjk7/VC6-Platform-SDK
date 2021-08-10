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
//  Abstract:     Implementation of the CFolderNode class.
//


#include "FolderNode.h"
#include "CompData.h"
#include "Comp.h"
                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CFolderNode")


// Initialize our static GUID just once
GUID CFolderNode::thisGUID = CLSID_CFolderNode;   


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

CFolderNode::CFolderNode()
{
  m_SDI.mask        = DEFAULT_SDI_MASK;
  m_SDI.displayname = MMC_CALLBACK;
  m_SDI.nImage      = IMG_FOLDER_DEFAULT;              
  m_SDI.nOpenImage  = IMG_FOLDER_DEFAULT;
  m_SDI.cChildren   = 0;              // Determines if the '+' is displayed
  m_SDI.lParam      = reinterpret_cast<LPARAM>(this);

  m_dwAttributes    = 0;
  m_pCompData       = NULL;
}


CFolderNode::~CFolderNode()
{
}

//---------------------------------------------------------------------------
//  This node does not make calls to it's parent so 
//  pNodeProps->pParentOject is ignored.
//
HRESULT CFolderNode::Initialize( NODE_PROPERTIES* pNodeProps )
{
  _ASSERT( NULL != pNodeProps );

  UINT   nLen   = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName = pszTmp;
  m_pCompData    = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);

  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods

//---------------------------------------------------------------------------
HRESULT CFolderNode::GetResultViewType2
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
HRESULT CFolderNode::GetDisplayInfo
( 
  SCOPEDATAITEM* pSDI        //[in][out] Points to SCOPEDATAITEM
)
{
  _ASSERT( NULL != pSDI );
  pSDI->displayname = m_pwszNodeName;

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::GetDisplayInfo
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
        pRDI->str = L"No attributes";
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
HRESULT CFolderNode::OnSelect
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LONG          nArg,          //[in] Bools for context & selection state
  LONG          nParam,        //[in] Not used
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT hResult = S_FALSE;

  // Not setting verbs for this node

  TRACE_HRESULT(_T("OnSelect"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CFolderNode::OnShow
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LONG          nArg,          //[in] TRUE if node was selcted
  LONG          nParam,        //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT  hResult = S_FALSE;

  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

  LPHEADERCTRL2  ipHeaderCtrl2 = NULL;
  hResult = pComp->GetInterface( REQUEST_IHEADERCTRL2, (LONG_PTR*)&ipHeaderCtrl2 ); 
  if( S_OK != hResult )
   return hResult;              

  LPRESULTDATA  ipResultData = NULL;
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData ); 
  if( S_OK != hResult )
   return hResult;              


  ipHeaderCtrl2->AddRef();
  ipResultData->AddRef();

  if( TRUE == nArg )  // Selecting a scope node
  {
    do                                 
    {                                  
      hResult = ipHeaderCtrl2->InsertColumn( 0, L"File Name", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipHeaderCtrl2->InsertColumn( 1, L"Attributes", 0, 150 );
      BREAK_ON_ERROR( hResult );

      hResult = ipResultData->ModifyViewStyle( MMC_NOSORTHEADER, (MMC_RESULT_VIEW_STYLE)NULL );      
      BREAK_ON_ERROR( hResult );

    }while(0);
  }
  else // not handling deselect notifications
  {
  }

  ipHeaderCtrl2->Release();
  ipResultData->Release();

  TRACE_HRESULT(_T("OnShow"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::OnExpand
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LONG           nArg,         //[in] TRUE if node was selcted
  LONG           nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_FALSE;

  if( NULL == m_pCompData )
    m_pCompData = reinterpret_cast<CComponentData*>(pCompData);


  TRACE_HRESULT( _T("OnExpand"), hResult );
  return hResult;              // Not expanding anything
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::OnRemoveChildren
( 
  LPDATAOBJECT   ipDataObject, //[in] Points to selected data object   
  LONG           nArg,         //[in] TRUE if node was selcted
  LONG           nParam,       //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR       pCompData     //[in] Points to calling CComponentData 
)
{
  HRESULT hResult = S_FALSE;

  // This method not used in this project

  TRACE_HRESULT( _T("OnRemoveChildren"), hResult );
  return hResult;
}


/////////////////////////////////////////////////////////////////////////////
//  Support for Context Menus

//---------------------------------------------------------------------------
HRESULT CFolderNode::AddMenuItems
( 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  return E_NOTIMPL;
}

//---------------------------------------------------------------------------
HRESULT CFolderNode::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  return E_NOTIMPL;
}
