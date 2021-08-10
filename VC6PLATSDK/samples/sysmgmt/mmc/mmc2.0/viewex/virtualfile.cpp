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

#include <stdio.h>
#include "VirtualFile.h"
#include "Globals.h"
#include "CompData.h"
#include "Comp.h"
#include "FolderNode.h"
#include "Scripts.h"         // Supporting scripts in this node 

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
HRESULT CVirtualFile::Initialize( NODE_PROPERTIES* pNodeProps )
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

  wcscpy( m_pDescripStr, L"VFile object created at " );

  GetLocalTime( &m_InitTime );
  WCHAR  szTimeBuffer[32];
  swprintf( szTimeBuffer, L"%u:%u:%u ", m_InitTime.wHour, m_InitTime.wMinute, m_InitTime.wSecond ); 
  wcscat( m_pDescripStr, szTimeBuffer );

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

      case 1:                        // Return attributes as a string
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

  BOOL  fScopePane = LOWORD(nArg);
  BOOL  fSelected  = HIWORD(nArg);

  // Don't care about de-select notifications so just return
  if( FALSE == fSelected )
    return hResult;
  
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

  IConsoleVerb* ipConsoleVerb = NULL;
  hResult = pComp->GetInterface( REQUEST_ICONSOLEVERB, (LONG_PTR*)&ipConsoleVerb ); 
  if( S_OK != hResult )
   return hResult;              

  // Not setting a default verb
  //
  hResult = ipConsoleVerb->SetVerbState( MMC_VERB_DELETE, ENABLED, TRUE );
  hResult = ipConsoleVerb->SetVerbState( MMC_VERB_RENAME, ENABLED, TRUE );

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
  HRESULT hResult = S_OK;

  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);

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

  LPRESULTDATA  ipResultData = NULL;
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData ); 
  if( S_OK != hResult )
   return hResult;              

  // VIEWEX:  When MMCN_RENAME is called from the object model via a 
  //          script, there is no automatic call to GetDisplayInfo, so
  //          we need to explicitly call UpdateItem to redraw the node
  hResult = ipResultData->UpdateItem( m_RDI.itemID );

  // In order to handle the case where multiple windows are open we need to
  // create a data object which represents our parent node.  We can then call
  // IConsole::UpdateAllViews with this data object.  MMC will direct the 
  // MMCN_VIEW_CHANGE notification to the parent node which will update all
  // result views which it owns (is the selected scope node)
  //
  LPCONSOLE3 ipConsole = NULL;
  hResult = pComp->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole );
  _ASSERT( NULL != ipConsole );

  LPDATAOBJECT pDO = NULL;
  hResult = pComp->QueryDataObject( (LONG_PTR)m_pParentFolder, CCT_SCOPE, &pDO );
  hResult = ipConsole->UpdateAllViews( pDO, NULL, HINT_UPDATE_ITEM );
  pDO->Release();

  return hResult;
}


//---------------------------------------------------------------------------
HRESULT CVirtualFile::OnDelete
( 
  LPDATAOBJECT ipDataObject,   //[in] Points to Data Object
  LPARAM       nArg,           //[in] Not used
  LPARAM       nParam,         //[in] Not used
  LONG_PTR     pComponent      //[in] Points to calling IComponent
)
{
  _ASSERT( NULL != ipDataObject );
  _ASSERT( NULL != m_pParentFolder );

  HRESULT hResult = S_FALSE;

  // Tell our parent node to remove us from it's list of children
  m_pParentFolder->RemoveVirtualFile( this );

  LPRESULTDATA ipResultData = NULL;
  CComponent* pComp = reinterpret_cast<CComponent*>(pComponent);
  hResult = pComp->GetInterface( REQUEST_IRESULTDATA, (LONG_PTR*)&ipResultData );
  if( S_OK != hResult )
    return hResult;

  hResult = ipResultData->DeleteItem( m_RDI.itemID, 0 );

  // In order to handle the case where multiple windows are open we need to
  // create a data object which represents our parent node.  We can then call
  // IConsole::UpdateAllViews with this data object.  MMC will direct the 
  // MMCN_VIEW_CHANGE notification to the parent node which will update all
  // result views which it owns (is the selected scope node)
  //
  LPCONSOLE3 ipConsole = NULL;
  hResult = pComp->GetInterface( REQUEST_ICONSOLE, (LONG_PTR*)&ipConsole );
  _ASSERT( NULL != ipConsole );

  LPDATAOBJECT pDO = NULL;
  hResult = pComp->QueryDataObject( (LONG_PTR)m_pParentFolder, CCT_SCOPE, &pDO );
  hResult = ipConsole->UpdateAllViews( pDO, NULL, HINT_UPDATE_ITEM );
  pDO->Release();

  delete this;

  return hResult;
}

/////////////////////////////////////////////////////////////////////////////
// CVirtualFile does not support a context menu

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

/////////////////////////////////////////////////////////////////////////////
// CVirtualFile methods to support INodeProperties

//---------------------------------------------------------------------------
//  VIEWEX:  This method is called by the View Extension to get the text
//           properties of the selected node.  It passes in the text
//           representation of the clipboard formats.  This method is the
//           the prefered method of doing this although the clipboard
//           formats can also be handled in the data object.
//
HRESULT CVirtualFile::GetProperty
( 
  BSTR   bstrPropertyName,   //[in]  Name of the property being retrieved
  PBSTR  pbstrProperty       //[out] Text value for the property
)
{
  HRESULT hResult = S_FALSE;
  BSTR bstrDesc = SysAllocString( L"CCF_DESCRIPTION" );
  BSTR bstrHTML = SysAllocString( L"CCF_HTML_DETAILS");

  if( NULL == bstrDesc || NULL == bstrHTML )
    return E_OUTOFMEMORY;

  if( VARCMP_EQ == VarBstrCmp(bstrPropertyName, bstrDesc, 0, 0) )
  {  
    *pbstrProperty = SysAllocString( m_pDescripStr );
    if( NULL != *pbstrProperty )
      hResult = S_OK;
  }

  if( VARCMP_EQ == VarBstrCmp( bstrPropertyName, bstrHTML, 0, 0 ) )
  {    
    // Build the script we want to run from our predefined mini-scripts
    // which are defined in Scripts.h 
    //
    WCHAR szScriptBuffer[1024];
    wcscpy( szScriptBuffer, GSCRP_BEGIN_FORM    );   
    wcscat( szScriptBuffer, GSCRP_RENAME_BUTTON );   
    wcscat( szScriptBuffer, GSCRP_DELETE_BUTTON );
    wcscat( szScriptBuffer, GSCRP_LINK_HOMEPAGE );
    wcscat( szScriptBuffer, GSCRP_END_FORM      );

    *pbstrProperty = SysAllocString( szScriptBuffer );
    if( NULL != *pbstrProperty )
      hResult = S_OK;                  // If you don't return S_OK the HTML
  }                                    // code will not be executed

  SysFreeString( bstrDesc );           // Free string resources   
  SysFreeString( bstrHTML );
   
  return hResult;
 }


/////////////////////////////////////////////////////////////////////////////
//  CVirtualFile methods to support attributes

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
//  Return a string representation of the node's attributes.
//
LPWSTR CVirtualFile::GetAttributeString()
{
  *m_pAttribStr = NULL;
  
  if( IsAttributeSet(ATTRIBUTE_DATA_ARCHIVE) )
    wcscat( m_pAttribStr, L"A " );

  if( IsAttributeSet(ATTRIBUTE_DATA_HIDDEN) )
    wcscat( m_pAttribStr, L"H " );

  if( IsAttributeSet(ATTRIBUTE_DATA_LOCKED) )
    wcscat( m_pAttribStr, L"L " );

  if( IsAttributeSet(ATTRIBUTE_DATA_READONLY) )
    wcscat( m_pAttribStr, L"R " );

  return m_pAttribStr;
}
