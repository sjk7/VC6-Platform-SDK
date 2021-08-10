//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPWiz.h
//
//--------------------------------------------------------------------------

// SCPWiz.h : Declaration of the CSCPWiz

#ifndef __SCPWIZ_H
#define __SCPWIZ_H

#include "resource.h"       // main symbols
#include "SCPWizard.h"
#include "SCPPageUI.h"


////////////////////////////////////////////////////////////////////////////////
// CSCPWiz
//
// This class implements the interface needed for a primary wizard extension
// for DS Admin.
//
////////////////////////////////////////////////////////////////////////////////

class /*ATL_NO_VTABLE*/ CSCPWiz : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDsAdminNewObjExt,
  public CComCoClass<CSCPWiz, &CLSID_SCPWizard>
{
public:
	CSCPWiz()
	{
    m_hObjClassIcon = NULL;
    m_pWizPage1 = NULL;
    m_pWizPage2 = NULL;
    m_pWizPage3 = NULL;
	}

 	~CSCPWiz()
	{
    if (m_pWizPage1 != NULL)
      delete m_pWizPage1;

    if (m_pWizPage2 != NULL)
      delete m_pWizPage2;

    if (m_pWizPage3 != NULL)
      delete m_pWizPage3;
	}


BEGIN_COM_MAP(CSCPWiz)
	COM_INTERFACE_ENTRY(IDsAdminNewObjExt)
END_COM_MAP()


public:
  DECLARE_REGISTRY_CLSID();

  //
  // IDsAdminNewObjExt interface
  //
  STDMETHOD(Initialize)(IADsContainer* pADsContainerObj,
                        IADs* pADsCopySource,
                        LPCWSTR lpszClassName,
                        IDsAdminNewObj* pDsAdminNewObj,
                        LPDSA_NEWOBJ_DISPINFO pDispInfo);

  STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
  STDMETHOD(SetObject)(IADs* pADsObj);
  STDMETHOD(WriteData)(HWND hWnd, ULONG uContext);
  STDMETHOD(OnError)(HWND hWnd, HRESULT hr, ULONG uContext);
  STDMETHOD(GetSummaryInfo)(BSTR* pBstrText);

  //
  // Helper functions
  //
  HRESULT WriteDataHelper();

  //
  // accessor functions
  //
  IADs* GetObj() { return m_spADsObj;}
  void SetObj(IADs* pADsObj) { m_spADsObj = pADsObj;}
  IADsContainer* GetContainer() { return m_spADsContainerObj;}
  IDsAdminNewObj* GetIDsAdminNewObj() { return m_spDsAdminNewObj;}
  IDsAdminNewObjPrimarySite* GetIDsAdminNewObjPrimarySite() { return m_spDsAdminNewObjPrimarySite; }

  IADs* GetCopySourceObj() { return m_spADsCopySourceObj;}

  LPCWSTR GetClassName() { return m_szClassName;}
  LPCWSTR GetContainerCanonicalName() { return m_szContCanonicalName;}
  HICON   GetClassIcon() { return m_hObjClassIcon;}
  LPCWSTR GetTitle() { return m_szTitle;}
	void GetDefaultSummary(CString& s);

private:
  //
  // container for object creation, passed to IDsAdminNewObjExt::Initialize()
  //
  CComPtr<IADsContainer> m_spADsContainerObj;   

  //
  // object under creation, passed to IDsAdminNewObjExt::SetObject()
  //
  CComPtr<IADs> m_spADsObj;           
  
  //
  // if present, cached pointer to the source (for copy operation)
  //
  CComPtr<IADs> m_spADsCopySourceObj;

  //
  // interface to the DS admin Object creation site
  //
  CComPtr<IDsAdminNewObj> m_spDsAdminNewObj;

  //
  // interface to the DS admin Object creation primary site
  //
  CComPtr<IDsAdminNewObjPrimarySite> m_spDsAdminNewObjPrimarySite;

protected:
  //
  // class name the extension called for, passed to IDsAdminNewObjExt::Initialize()
  //
  CString m_szClassName;   

  //
  // display information passed to ::Initialize() in the LPDSA_NEWOBJ_DISPINFO struct
  //
  CString m_szTitle;      
  CString m_szContCanonicalName;
  HICON   m_hObjClassIcon;

  //
  // The classes that handle the user interface for the creation wizard
  //
  CSCPPageGeneral*      m_pWizPage1;
  CSCPPageBindingInfo*  m_pWizPage2;
  CSCPPageKeywords*     m_pWizPage3;
};


#endif //__SCPWIZ_H