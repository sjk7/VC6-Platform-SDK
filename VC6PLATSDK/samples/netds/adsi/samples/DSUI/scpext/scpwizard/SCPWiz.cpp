//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPWiz.cpp
//
//--------------------------------------------------------------------------

// SCPWiz.cpp : Implementation of CSCPWiz
#include "stdafx.h"
#include "SCPWiz.h"
#include "util.h"


/////////////////////////////////////////////////////////////////////////////
// CWizExtBase

HRESULT CSCPWiz::Initialize(IADsContainer*				pADsContainerObj,
																IADs*									pADsCopySource,
																LPCWSTR								lpszClassName,
																IDsAdminNewObj*				pDsAdminNewObj,
																LPDSA_NEWOBJ_DISPINFO pDispInfo)
{
  HRESULT hr = S_OK;
  //
  // Debug Traces
  //
	TRACE(_T("IDsAdminNewObjExt::Initialize()\n"));
	TRACE(_T("\tpADsContainerObj = %p\n"), pADsContainerObj);
  TRACE(_T("\tlpszClassName = <%s>\n"), lpszClassName);
	TRACE(_T("\tpDsAdminNewObj = %p\n"), pDsAdminNewObj);
	TRACE(_T("\tpDispInfo = %p\n"), pDispInfo);
  
  //
  // make sure we have valid parameters
  //
  if ( (pADsContainerObj == NULL) || (pDsAdminNewObj == NULL) || (lpszClassName == NULL) )
  {
    hr = E_INVALIDARG;
  }

  if ( (pDispInfo == NULL) || (pDispInfo->dwSize != sizeof(DSA_NEWOBJ_DISPINFO)) ) 
  {
    hr = E_INVALIDARG;
  }

  //
  // save the parameters passed
  //
  m_spDsAdminNewObj			= pDsAdminNewObj;
  m_spADsCopySourceObj	= pADsCopySource;
  m_spADsContainerObj		= pADsContainerObj;
  m_szClassName					= lpszClassName;

  hr = m_spDsAdminNewObj->QueryInterface(IID_IDsAdminNewObjPrimarySite, 
                                                 (PVOID*)&m_spDsAdminNewObjPrimarySite);
  if (FAILED(hr))
  {
    m_spDsAdminNewObjPrimarySite = NULL;
  }

  //
  // save data from the DSA_NEWOBJ_DISPINFO struct
  //
  TRACE(_T("\tpDispInfo->dwSize = %d\n"), pDispInfo->dwSize);
  TRACE(_T("\tpDispInfo->hObjClassIcon	= 0x%x\n"), pDispInfo->hObjClassIcon);
  TRACE(_T("\tpDispInfo->lpszWizTitle = <%s>\n"), pDispInfo->lpszWizTitle);
  TRACE(_T("\tpDispInfo->lpszContDisplayName = <%s>\n"), pDispInfo->lpszContDisplayName);

  m_hObjClassIcon = pDispInfo->hObjClassIcon;
  m_szTitle = pDispInfo->lpszWizTitle;
  m_szContCanonicalName = pDispInfo->lpszContDisplayName;

  return hr;
}


HRESULT CSCPWiz::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
  //
  // Add the pages for the wizard extension in the order they are to appear.
  //
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
  m_pWizPage1 = new CSCPPageGeneral(this);
  (*lpfnAddPage)(CreatePropertySheetPage((PROPSHEETPAGE*)(&m_pWizPage1->m_psp)), lParam);

  m_pWizPage2 = new CSCPPageBindingInfo(this);
  (*lpfnAddPage)(CreatePropertySheetPage((PROPSHEETPAGE*)(&m_pWizPage2->m_psp)), lParam);

  m_pWizPage3 = new CSCPPageKeywords(this);
  (*lpfnAddPage)(CreatePropertySheetPage((PROPSHEETPAGE*)(&m_pWizPage3->m_psp)), lParam);

  return S_OK;
}

HRESULT CSCPWiz::SetObject(IADs* pADsObj)
{
  //
  // Hang on to the object passed in
  // the smart pointer will handle the ref count
  //
  m_spADsObj = pADsObj;
  return S_OK;
}

HRESULT CSCPWiz::WriteData(HWND hWnd, ULONG uContext)
{
  HRESULT hr = E_INVALIDARG;
  //
  // NOTICE: when the property page has received the kill focus
  // notification, it has already written the data, so we do not
  // need to do anything on a precommit notification.
  //
  if (uContext == DSA_NEWOBJ_CTX_PRECOMMIT)
  {
    hr = S_OK;
  }

  //
  // This extension does not write anything during the post commit phase
  // so we can just return.
  //
  if (uContext == DSA_NEWOBJ_CTX_POSTCOMMIT)
  {
    hr = S_OK;
  }

  //
  // We have to handle the case when the creation failed, the object
  // got destroyed, a new temporary object was created, and it has to
  // be initialized again.
  //
  if (uContext == DSA_NEWOBJ_CTX_CLEANUP)
  {
    //
    // Call the helper function to do a precommit write.
    //
    hr = WriteDataHelper();
  }

  return hr;
}

HRESULT CSCPWiz::WriteDataHelper()
{
  //
  // Write the data from the page to the temporary object given to the extension
  // by SetObject()
  //


  return S_OK;
}

HRESULT CSCPWiz::GetSummaryInfo(BSTR* pBstrText)
{
  //
  // Verify valid arguments
  //
  if (pBstrText == NULL)
  {
    return E_INVALIDARG;
  }

  //
  // Format the summary string which will be displayed on the finish page of the wizard.
  //
  CString strSummary, szPage1, szPage2, szPage3;
  m_pWizPage1->GetSummaryInfo(szPage1);
  m_pWizPage2->GetSummaryInfo(szPage2);
  m_pWizPage3->GetSummaryInfo(szPage3);

  strSummary = szPage1 + szPage2 + szPage3;
  
  //
  // Copy to BSTR
  //
  *pBstrText = ::SysAllocString(strSummary);
  return S_OK;
}

HRESULT CSCPWiz::OnError(HWND hWnd, HRESULT hr, ULONG uContext)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());
 
  CString szMessage;

  if (uContext == DSA_NEWOBJ_CTX_COMMIT)
  {
    //
    // The extension gets notified if the SetInfo() or an attempt to cleanup
    // a temporary object failed.
    //
    szMessage.Format(_T("SetInfo() failed: hr = 0x%x"), hr);
    AfxMessageBox(szMessage);
  }
  else if (uContext == DSA_NEWOBJ_CTX_PRECOMMIT)
  {
    //
    // Pre-commit failure is rare.  If it does occur handle the error here.
    //
  }
  else if (uContext == DSA_NEWOBJ_CTX_POSTCOMMIT)
  {
    //
    // Post-commit failure is rare.  If it does occur handle the error here.
    //
  }
  else if (uContext == DSA_NEWOBJ_CTX_CLEANUP)
  {
    //
    // For some reason (e.g. network failure or not enough privileges) DS Admin
    // could not remove the ill constructed (but committed) object after a 
    // failure to write on post commit.  If appropriate, the extension can 
    // handle the error message.
    //

    //
    // NOTE : this is not a primary extension so we will leave it up to DS Admin
    //        to handle this error message.
    //
    return E_FAIL;
  }

  //
  // Returning success means that DS Admin will not put up its own generic
  // error message.
  //
  return S_OK;
}

