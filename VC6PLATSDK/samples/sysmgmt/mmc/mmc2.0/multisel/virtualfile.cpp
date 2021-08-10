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
GUID CVirtualFile::m_thisGUID = CLSID_CVirtualFile;   


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

  m_pComponent = reinterpret_cast<CComponent*>(pComponent); 

  IConsoleVerb* ipConsoleVerb = NULL;
  hResult = m_pComponent->GetInterface( REQUEST_ICONSOLEVERB, (LONG_PTR*)&ipConsoleVerb ); 
  if( S_OK == hResult )
  {
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_RENAME, ENABLED, TRUE );
    hResult = ipConsoleVerb->SetVerbState( MMC_VERB_DELETE, ENABLED, TRUE );
  }
  TRACE_HRESULT(_T("OnSelect"), hResult );
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
// IExtendToolbar

//---------------------------------------------------------------------------
HRESULT CVirtualFile::ControlbarNotify
( 
  LPARAM   nArg,         //[in] Selection status 
  LPARAM   lParam,       //[in] Not used 
  LONG_PTR pComp         //[in] Points to CComponent
)
{ 
  HRESULT hResult = S_FALSE;
  BOOL bScope  = (BOOL)LOWORD(nArg);
  BOOL bSelect = (BOOL)HIWORD(nArg);

  CComponent* pComponent = reinterpret_cast<CComponent*>(pComp);

  IControlbar* ipControlbar = NULL;
  hResult = pComponent->GetInterface( REQUEST_ICONTROLBAR, (LONG_PTR*)&ipControlbar );
  if( S_OK != hResult )
    return hResult; 

  IToolbar* ipToolbar = NULL;
  hResult = pComponent->GetInterface( REQUEST_IVFILETOOLBAR, (LONG_PTR*)&ipToolbar );
  if( S_OK != hResult )
    return hResult; 

  if( TRUE == bSelect )
  {
    hResult = ipControlbar->Attach(TOOLBAR, (LPUNKNOWN)ipToolbar);
    hResult = ipToolbar->SetButtonState( IDM_CLEAR_ATTRIBS, ENABLED, TRUE );
  }
  else
  {
    hResult = ipControlbar->Detach( (LPUNKNOWN)ipToolbar );
  }

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
//  This handles commands for both Context Menu items and Toolbar items
//
HRESULT CVirtualFile::Command
( 
  long lCommandID          //[in] Indentifier for menu ID
)
{
  HRESULT hResult = S_OK;

  switch( lCommandID )
  {  
    case IDM_CLEAR_ATTRIBS:
    {
     m_dwAttributes = 0;
     break;
    }
    default:
      hResult = S_FALSE;
      break;

  }
  return hResult;
}
