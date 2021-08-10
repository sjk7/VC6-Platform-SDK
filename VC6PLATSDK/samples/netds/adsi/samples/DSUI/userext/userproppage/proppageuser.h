//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       proppageuser.h
//
//--------------------------------------------------------------------------

#ifndef _PROPPAGEUSER_H
#define _PROPPAGEUSER_H

#include "stdafx.h"
#include "userproppage.h"
#include "ProppageUserUI.h"

class /*ATL_NO_VTABLE*/ CProppageUser : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IShellExtInit,
  public IShellPropSheetExt,
  public CComCoClass<CProppageUser, &CLSID_ProppageUser>
{
public:
	CProppageUser()
	{
    TRACE(L"CProppageUser::CProppageUser()\n");
	}

 	~CProppageUser()
	{
    TRACE(L"CProppageUser::~CProppageUser()\n");
	}


BEGIN_COM_MAP(CProppageUser)
	COM_INTERFACE_ENTRY(IShellExtInit)
  COM_INTERFACE_ENTRY(IShellPropSheetExt)
END_COM_MAP()

DECLARE_REGISTRY_CLSID();

public:

  // IShellExtInit interface
  STDMETHOD(Initialize)(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObject, HKEY hKeyID);

  // IShellPropSheetExt interface
  STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE pAddPageProc, LPARAM lParam);
  STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam);

private:
  CComPtr<IDataObject> m_spDataObj;
};


#endif // _PROPPAGEUSER_H
