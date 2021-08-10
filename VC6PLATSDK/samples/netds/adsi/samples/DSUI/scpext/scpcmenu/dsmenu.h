//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       dsmenu.h
//
//--------------------------------------------------------------------------

#ifndef __DSMENU_H
#define __DSMENU_H

class CContextMenu:
  IShellExtInit,
  IContextMenu,
  public CComObjectRoot,
  public CComCoClass<CContextMenu, &CLSID_SCPContextMenu>
{
  BEGIN_COM_MAP(CContextMenu)
    COM_INTERFACE_ENTRY(IShellExtInit)
    COM_INTERFACE_ENTRY(IContextMenu)
  END_COM_MAP()

public:
  DECLARE_REGISTRY_CLSID()

  CContextMenu();
  ~CContextMenu();

  //
  // IShellExtInit
  //
  STDMETHODIMP Initialize(LPCITEMIDLIST pIDFolder, 
                          LPDATAOBJECT pDataObj, 
                          HKEY hKeyID );
  
  //
  // IContextMenu
  //
  STDMETHODIMP QueryContextMenu(HMENU hShellMenu,
                                UINT indexMenu,
                                UINT idCmdFirst, 
                                UINT idCmdLast,
                                UINT uFlags );
  STDMETHODIMP InvokeCommand( LPCMINVOKECOMMANDINFO lpcmi );
  STDMETHODIMP GetCommandString( UINT_PTR idCmd,
                                 UINT uFlags,
                                 UINT FAR* reserved,
                                 LPSTR pszName, 
                                 UINT ccMax );

  void ShowClipformatInfo();

private:
  CComPtr<IDataObject>  m_spDataObj;
};

#endif // __DSMENU_H