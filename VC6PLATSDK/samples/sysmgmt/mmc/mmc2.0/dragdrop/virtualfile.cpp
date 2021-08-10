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
//  Abstract:  Implements our virtual file class derived from CBaseNode.  This
//             class will represent our result items
//

#include "VirtualFile.h"
#include "FolderNode.h"
#include "Globals.h"
#include "CompData.h"
#include "Comp.h"
                             // Tracing stuff
#include "TraceMacro.h"
#undef  MODULESTRING         
#define MODULESTRING  _T("CVirtualFile")


// Initialize our static GUID just once
GUID CVirtualFile::thisGUID = CLSID_CVirtualFile;   


/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

//---------------------------------------------------------------------------
CVirtualFile::CVirtualFile()
{
  m_RDI.mask      = DEFAULT_RDI_MASK;
  m_RDI.str       = MMC_CALLBACK;
  m_RDI.nImage    = IMG_DATA_FILE;              
  m_RDI.lParam    = reinterpret_cast<LPARAM>(this);

  m_dwAttributes  = 0;
  m_pParentFolder = NULL;
  m_pCompData     = NULL;
}

//---------------------------------------------------------------------------
CVirtualFile::~CVirtualFile()
{
}

//---------------------------------------------------------------------------
HRESULT CVirtualFile::Initialize
( 
  LPNODEPROPS  pNodeProps    //[in] Properties for this node
)
{
  _ASSERT( NULL != pNodeProps );

  UINT   nLen   = wcslen( pNodeProps->szNodeName ) + 1;
  LPWSTR pszTmp = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  wcscpy( pszTmp, pNodeProps->szNodeName );
  if( NULL != m_pwszNodeName )
    CoTaskMemFree( m_pwszNodeName );

  m_pwszNodeName  = pszTmp;
  m_pParentFolder = reinterpret_cast<CFolderNode*>(pNodeProps->pParentObject);
  m_pCompData     = reinterpret_cast<CComponentData*>(pNodeProps->pComponentData);
  m_dwAttributes  = pNodeProps->dwAttributes;

  return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods

//---------------------------------------------------------------------------
//  DRAGDROP:  This method supports the CCF_NODEPROP_PTR clipboard format.
//             The Node Properties struct is allocated in global memory so
//             so that interproccess CUT/COPY/PASTE will work.
//             The caller is responsible for freeing the memory.
//
HRESULT CVirtualFile::GetProperties
( 
  LPNODEPROPS* ppNodeProps   //[out] Properties of this node 
)
{
  _ASSERT( NULL == *ppNodeProps );

  LONG nBlockSize = sizeof(NODEPROPS);
  LPNODEPROPS pTmpProps = NULL;
  HGLOBAL hMemory = ::GlobalAlloc( GMEM_SHARE | GMEM_MOVEABLE, nBlockSize );
  if( NULL == hMemory )
    return E_OUTOFMEMORY;

  pTmpProps = (LPNODEPROPS)::GlobalLock( hMemory ); 
  ZeroMemory( pTmpProps, nBlockSize );
  wcscpy( pTmpProps->szNodeName,  m_pwszNodeName );
  pTmpProps->pComponentData = NULL;    // Pointers not used for DragDrop
  pTmpProps->pParentObject  = NULL;
  pTmpProps->dwAttributes   = m_dwAttributes;         
  pTmpProps->nChildCount    = 0;       // Result nodes don't have children
  pTmpProps->nBlockSize     = nBlockSize;

  ::GlobalUnlock( pTmpProps );
  *ppNodeProps = pTmpProps;            // Return the properties 

  return S_OK;
}

//---------------------------------------------------------------------------
HRESULT CVirtualFile::GetDisplayInfo
( 
  RESULTDATAITEM* pRDI       //[in-out] RESULTDATAITEM struct
)
{
  HRESULT hResult = S_OK;

  if( pRDI->mask & RDI_STR )         // Console is requesting strings...
  {                                  // for each column     
    switch( pRDI->nCol )
    {
      case 0:
        pRDI->str = m_pwszNodeName;
        break;

      case 1:                        // Display attributes as a string
        pRDI->str = GetAttributeString();
        break;

      default:
        hResult = S_FALSE;
        TRACE_VAL(_T("GetDisplayInfo"), _T("Column"), pRDI->nCol );
        break;
    }
  }

  if( pRDI->mask & RDI_IMAGE )       // Looking for an image?
  {
    pRDI->nImage = m_RDI.nImage;
  }

  //TRACE_HRESULT(_T("GetDisplayInfo"), hResult );
  return hResult;
}


/////////////////////////////////////////////////////////////////////////////
// Implementation of virtual methods


//---------------------------------------------------------------------------
HRESULT CVirtualFile::OnSelect
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] Bools for context & selection state
  LPARAM        nParam,        //[in] Not used
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT hResult = S_FALSE;

  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

  IConsoleVerb* ipConsoleVerb = NULL;
  hResult = pComp->GetInterface( REQUEST_ICONSOLEVERB, (LONG_PTR*)&ipConsoleVerb ); 
  if( S_OK == hResult )
  {
    // DRAGDROP: Add MMC_VERB_CUT/COPY/PASTE verbs for this object.
    //
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_CUT,   ENABLED, TRUE );
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_COPY,  ENABLED, TRUE );
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_PASTE, ENABLED, TRUE );

    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_RENAME, ENABLED, TRUE );
  }
  //TRACE_HRESULT(_T("OnSelect"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CVirtualFile::OnShow
( 
  LPDATAOBJECT  ipDataObject,  //[in] Points to selected node
  LPARAM        nArg,          //[in] TRUE if node was selcted
  LPARAM        nParam,        //[in] HSCOPEITEM of selected/deselected item
  LONG_PTR      pComponent     //[in] Points calling CComponent
)
{
  HRESULT  hResult = S_FALSE;
  //TRACE_HRESULT(_T("OnShow"), hResult );
  return hResult;
}

//---------------------------------------------------------------------------
//  The parent node just AddRef'd the data object which we don't use,
//  so we can just let MMC release it.
//  We just tell the parent node to remove it's pointer to us from it's
//  list of children, then we can delete ourselves.
//
HRESULT CVirtualFile::OnCutOrMove
( 
  LPDATAOBJECT ipDataObject, //[in] NULL
  LPARAM       nArg,         //[in] Pointer to data object
  LPARAM       nParam,       //[in] Not used
  LONG_PTR     pComponent    //[in] Points calling CComponent
)
{
  _ASSERT( NULL != m_pParentFolder );
  HRESULT hResult = S_FALSE;

  m_pParentFolder->RemoveChildNode( reinterpret_cast<LONG_PTR>(this) );

  LPRESULTDATA ipResultData = NULL;
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData );
  if( S_OK == hResult )
  {
    hResult = ipResultData->DeleteItem( m_RDI.itemID, 0 );
    delete this;
  }
  return hResult;
}

//---------------------------------------------------------------------------
//  This message must return S_OK to allow the rename.  Anything else will
//  disallow the rename
//
HRESULT CVirtualFile::OnRename
( 
  LPDATAOBJECT ipDataObject,   //[in] Points to Data Object
  LPARAM       nArg,           //[in] Not used
  LPARAM       nParam,         //[in] Pointer to the new name
  LONG_PTR     pComponent      //[in] Points to calling IComponent
)
{
  _ASSERT( NULL != ipDataObject );
  HRESULT hResult = S_OK;

  LPWSTR pszTmpName = NULL;
  LPWSTR pszNewName = (LPWSTR)nParam;  // New name
  LONG   nLen = wcslen( pszNewName ) + 1;

  pszTmpName = (LPWSTR)CoTaskMemAlloc(nLen * sizeof(WCHAR));
  if( NULL == pszTmpName )
  { 
    hResult = S_FALSE;                 // Can't change the name
  }
  else
  {
    wcscpy( pszTmpName, pszNewName );
    CoTaskMemFree( m_pwszNodeName );   // Free existing name...
    m_pwszNodeName = pszTmpName;       // Assign new name to pointer        
  }

  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
// DRAGDROP:  Support for DragDrop on result pane items.

//---------------------------------------------------------------------------
//  MMC20: nParam has changed to a DWORD* which can be used to specify
//         the default behaviour of DragDrop.
//         We disallow copy/paste to ourself, and only accept other
//         VFiles as source objects.
//
HRESULT CVirtualFile::OnQueryPaste
( 
  LPDATAOBJECT ipTargetDO,     //[in] Data object of the selected node
  LPARAM       nArg,           //[in] Data object of node to be pasted
  LPARAM       nParam,         //[in] DWORD* which specifies default operation
  LONG_PTR     pComponent      //[in] Points to calling IComponent 
)
{
  _ASSERT( NULL != nArg );
  HRESULT hResult = S_FALSE;

  // Make the default operation "Copy Here" as opposed to "Move Here"
  //
  DWORD* pdwDefaultOperation = reinterpret_cast<DWORD*>(nParam);
  *pdwDefaultOperation = MMC_DEFAULT_OPERATION_COPY;

  // Disallow pasting on top of ourself
  //
  CBaseNode* pNode1 = ExtractBaseNodePtr( ipTargetDO );
  CBaseNode* pNode2 = ExtractBaseNodePtr( reinterpret_cast<LPDATAOBJECT>(nArg) ); 
  if( pNode1 == pNode2 )
    return S_FALSE;

  // Only allow other VFiles as source objects 
  // 
  ULONG nTypeFlag = ExtractNodeTypeFlg( reinterpret_cast<LPDATAOBJECT>(nArg) );
  return (NODETYPE_VFILE == nTypeFlag) ? S_OK : S_FALSE;
} 


//---------------------------------------------------------------------------
//  DRAGDROP:  We implement a slightly different behavior for Result Nodes.
//             Since ResultNodes don't have children, we copy the Attributes            
//             from the source node to the target node.  The default action
//             is a non destructive copy.  If a right click drag or move
//             was selected the source node is deleted.            
//
HRESULT CVirtualFile::OnPaste
( 
  LPDATAOBJECT ipDataObject,   //[in] Data object of the destination node
  LPARAM       nArg,           //[in] Data object of the source node
  LPARAM       nParam,         //[in] NULL for copy, DataObject pointer for cut
  LONG_PTR     pComponent      //[in] Points to calling IComponent 
)
{
  _ASSERT( NULL != nArg );
  _ASSERT( NULL != pComponent );

  HRESULT hResult = S_FALSE;
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  LPDATAOBJECT ipSourceDO = reinterpret_cast<LPDATAOBJECT>(nArg);

  do
  {
    // Test to see if the data object supports the clipformat we need
    //
    FORMATETC NodePropFormatEtc = NP_FORMATETC;
    hResult = ipSourceDO->QueryGetData( &NodePropFormatEtc );
    BREAK_ON_ERROR( hResult );

    STGMEDIUM StgMedium = {TYMED_HGLOBAL, NULL};
    hResult = ipSourceDO->GetData( &NodePropFormatEtc, &StgMedium );
    BREAK_ON_ERROR( hResult );

    NODE_PROPERTIES* pNodeProps = NULL;
    pNodeProps = (NODE_PROPERTIES*)::GlobalLock( StgMedium.hGlobal );

    // Set variables which must be local
    //
    pNodeProps->pParentObject  = reinterpret_cast<LONG_PTR>(this);
    pNodeProps->pComponentData = reinterpret_cast<LONG_PTR>(m_pCompData);

    // For Virtual Files all we care about are Attributes
    //
    SetAttribute( pNodeProps->dwAttributes );

    // Now do some housekeeping, and test that everything went OK....
    //
    BOOL    bStatus = ::GlobalUnlock( StgMedium.hGlobal );
    HGLOBAL hReturn = ::GlobalFree( StgMedium.hGlobal );
    _ASSERT( NULL == hReturn );

    if( NULL != nParam )              // Is this a copy or move?
    {
      // We just AddRef it becuase MMC will release it once when we 
      // return, and again when CVirtualFile::OnCutOrMove returns.      
      // 
      BOOL* pbPasted = reinterpret_cast<BOOL*>(nParam);
      ULONG nCount = ipSourceDO->AddRef();
      *pbPasted = reinterpret_cast<BOOL>(ipSourceDO);   
    }

    LPCONSOLE3 ipConsole3 = NULL;
    hResult = m_pCompData->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole3 );
    hResult = ipConsole3->SelectScopeItem( m_pParentFolder->m_SDI.ID );

  }while(0);       

  return hResult;
} 



/////////////////////////////////////////////////////////////////////////////
//  CVirtualFile methods

//---------------------------------------------------------------------------
BOOL CVirtualFile::IsAttributeSet
( 
  DWORD dwAttribute           //[in] Attribute to set
)
{
  return (m_dwAttributes & dwAttribute) ? TRUE : FALSE;
}

//---------------------------------------------------------------------------
VOID CVirtualFile::SetAttribute
( 
  DWORD dwAttribute           //[in] Attribute to set
)
{
  m_dwAttributes |= dwAttribute;
}

//---------------------------------------------------------------------------
VOID CVirtualFile::RemoveAttribute
( 
  DWORD dwAttribute           //[in] Attribute to remove
)
{
  m_dwAttributes &= ~dwAttribute;
}

//---------------------------------------------------------------------------
LPWSTR CVirtualFile::GetAttributeString()
{
  *m_pAttributeStr = NULL;
  
  if( IsAttributeSet(ATTRIBUTE_DATA_ARCHIVE) )
    wcscat( m_pAttributeStr, L"A " );

  if( IsAttributeSet(ATTRIBUTE_DATA_HIDDEN) )
    wcscat( m_pAttributeStr, L"H " );

  if( IsAttributeSet(ATTRIBUTE_DATA_LOCKED) )
    wcscat( m_pAttributeStr, L"L " );

  if( IsAttributeSet(ATTRIBUTE_DATA_READONLY) )
    wcscat( m_pAttributeStr, L"R " );

  return m_pAttributeStr;
}


/////////////////////////////////////////////////////////////////////////////
// IExtendContextMenu 

//---------------------------------------------------------------------------
HRESULT CVirtualFile::AddMenuItems
( 
  LPCONTEXTMENUCALLBACK ipCallback,  //[in] Pointer to an IContextMenuCallback
  long __RPC_FAR* pInsertionAllowed  //[in-out] Insertion flags
)
{
  HRESULT hResult = E_NOTIMPL;
  //TRACE_HRESULT(_T("AddMenuItems"), hResult );
  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CVirtualFile::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  HRESULT hResult = E_NOTIMPL;
  //TRACE_HRESULT(_T("Command"), hResult );
  return hResult;
}
