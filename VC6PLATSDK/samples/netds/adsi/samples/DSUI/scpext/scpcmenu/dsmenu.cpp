//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 2000
//
//  File:      dsmenu.cpp
//
//  Contents:  object to implement context menu extensions
//
//  History:   3-august-99 jeffjon    Created
//             
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "resource.h"
#include "SCPCMenu.h"
#include "dsmenu.h"
#include "SCPCMenuUI.h"
#include <dsclient.h>

#define ARRAYLEN(x) (sizeof(x) / sizeof((x)[0]))



///////////////////////////////////////////////////////////////////////////
// CContextMenu

CContextMenu::CContextMenu()
{
	ATLTRACE(_T("CContextMenu::CContextMenu()\n"));    
}

CContextMenu::~CContextMenu()
{
	ATLTRACE(_T("CContextMenu::~CContextMenu()\n"));  
}


////////////////////////////////////////////////////////////
// IShellExtInit methods
STDMETHODIMP
CContextMenu::Initialize(LPCITEMIDLIST pIDFolder, 
                           LPDATAOBJECT pDataObj,
                           HKEY hKeyID )
{
  
  ATLTRACE(_T("CContextMenu::Initialize.\n"));

  if (pDataObj == NULL)
  {
    return E_INVALIDARG; // no point in going on
  }

  //
  // Store a pointer to the data object
  //
  m_spDataObj = pDataObj;

  return NOERROR;
}




BOOL _InsertMenuHelper(
    HMENU hMenu,          // handle to menu
    UINT uPosition,       // menu item that new menu item precedes
    UINT uFlags,          // menu item flags
    UINT_PTR uIDNewItem,  // menu item identifier or handle to drop-down 
                          // menu or submenu
    LPCTSTR lpNewItem,    // menu item content
    UINT* pnCurrentCount
    )
{
  if (::InsertMenu(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem))
  {
    (*pnCurrentCount)++;
    return TRUE;
  }
  return FALSE;
}



///////////////////////////////////////////////////////////
// IContextMenu methods
STDMETHODIMP
CContextMenu::QueryContextMenu(HMENU hMenu,
                                 UINT indexMenu,
                                 UINT idCmdFirst, 
                                 UINT idCmdLast,
                                 UINT uFlags )

{

  TCHAR szBuffer[MAX_PATH];
  UINT nMenuItemsAdded = 0;
  
  ATLTRACE(_T("CContextMenu::QueryContextMenu.\n"));

  
  // add them items to your menu, inserting them at indexMenu + the offset for your
  // item.  idCmdFirst / idCmdList is the range you should use, they should
  // not exceed this range.  On exit return the number of items and IDs you claimed,

    if ( !LoadString(_Module.GetModuleInstance(), IDS_SCP_MENU,
                     szBuffer, ARRAYLEN(szBuffer)) ) 
    {
      ATLTRACE(_T("Failed to load resource for menu item.\n"));
    }
    _InsertMenuHelper(hMenu,
             indexMenu, 
             MF_BYPOSITION|MF_STRING,
             idCmdFirst,
             szBuffer, &nMenuItemsAdded);
	
	return nMenuItemsAdded;
}


STDMETHODIMP
CContextMenu::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
  HRESULT hr = S_OK;
  ATLTRACE (_T("CDSContextMenu::InvokeCommand\n"));
  ATLTRACE (_T("\tlpcmi->lpVerb is %d.\n"), lpcmi->lpVerb);

  switch ((INT_PTR)(lpcmi->lpVerb)) 
  {
  case 0:
	  ShowClipformatInfo();
    break;
  }
  return hr;
}

STDMETHODIMP
CContextMenu::GetCommandString(UINT_PTR idCmd,
                                   UINT uFlags,
                                   UINT FAR* reserved, 
                                   LPSTR pszName,
                                   UINT ccMax)

{
  HRESULT hr = S_OK;
  TCHAR szBuffer[MAX_PATH];
  

  ATLTRACE (_T("CContextMenu::GetCommandString\n"));
  ATLTRACE (_T("\tidCmd is %d.\n"), idCmd);
  if (uFlags != GCS_HELPTEXT) 
  {
    ATLTRACE (_T("CDSContextMenu::GetCommand String- flags don't request helptext. flags: %lx\n"),
           uFlags);
    return hr;
  }

  switch ((idCmd)) 
  {
  case 0:
    if ( !LoadString(_Module.GetModuleInstance(), IDS_SCP_MENU,
                     szBuffer, ARRAYLEN(szBuffer)) ) 
    break;
  }

  
  wcscpy ((LPWSTR)pszName, (LPWSTR)(LPCWSTR)szBuffer);
  return hr;
}


void CContextMenu::ShowClipformatInfo()
{
  CSCPCMenuDialog dlg(m_spDataObj);
  dlg.DoModal();
}

