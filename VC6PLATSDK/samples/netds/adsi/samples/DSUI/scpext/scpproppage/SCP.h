//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCP.h
//
//--------------------------------------------------------------------------

#ifndef _SCP_H
#define _SCP_H

#include "stdafx.h"
#include "SCPProppage.h"
#include "SCPUI.h"

class /*ATL_NO_VTABLE*/ CSCP : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IShellExtInit,
  public IShellPropSheetExt,
  public CComCoClass<CSCP, &CLSID_ProppageSCP>
{
public:
	CSCP()
	{
    m_pProppageUIGeneral      = NULL;
    m_pProppageUIBindingInfo  = NULL;
    m_pProppageUIKeywords     = NULL;
	}

 	~CSCP()
	{
	}


BEGIN_COM_MAP(CSCP)
	COM_INTERFACE_ENTRY(IShellExtInit)
  COM_INTERFACE_ENTRY(IShellPropSheetExt)
END_COM_MAP()

DECLARE_REGISTRY_CLSID();

public:

  //
  // IShellExtInit interface
  //
  STDMETHOD(Initialize)(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObject, HKEY hKeyID);

  //
  // IShellPropSheetExt interface
  //
  STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE pAddPageProc, LPARAM lParam);
  STDMETHOD(ReplacePage)(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam);

private:
  CSCPUIGeneral*      m_pProppageUIGeneral;
  CSCPUIBindingInfo*  m_pProppageUIBindingInfo;
  CSCPUIKeywords*     m_pProppageUIKeywords;

  CComPtr<IDataObject> m_spDataObj;
};


#endif // _SCP_H