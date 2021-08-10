//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPPageUI.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "SCPPageUI.h"
#include "SCPWiz.h"
#include "util.h"

BEGIN_MESSAGE_MAP(CSCPPageGeneral, CPropertyPage)
  ON_EN_CHANGE(IDC_NAME_EDIT, OnNameChange)
  ON_EN_CHANGE(IDC_DNS_NAME_EDIT, OnDNSNameChange)
  ON_EN_CHANGE(IDC_SERVICE_CLASS_EDIT, OnServiceClassChange)
  ON_EN_CHANGE(IDC_DNS_NAME_TYPE_EDIT, OnDNSNameTypeChange)
END_MESSAGE_MAP()

BOOL CSCPPageGeneral::OnInitDialog()
{
  BOOL bResult = CPropertyPage::OnInitDialog();

  //
  // Set the name of the container
  //
  SetDlgItemText(IDC_EDIT_CONTAINER, m_pWizExt->GetContainerCanonicalName());

  // 
  // Set the class icon
  //
  ((CStatic*)GetDlgItem(IDC_STATIC_ICON))->SetIcon(m_pWizExt->GetClassIcon());

  // Disable the Next wizard button until all the controls are filled with valid data.
  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(0, FALSE);
  if (FAILED(hr))
  {
    // Give error message if the buttons don't get set
    CString szErrorMessage;
    szErrorMessage.Format(_T("SetButtons(0, FALSE) failed with %x"), hr);
    AfxMessageBox(szErrorMessage);
  }
  return bResult;
}

void CSCPPageGeneral::OnDNSNameChange()
{
  GetDlgItem(IDC_DNS_NAME_EDIT)->GetWindowText(m_szServiceDNSName);
  SetWizardButtons();
}

void CSCPPageGeneral::OnDNSNameTypeChange()
{
  GetDlgItem(IDC_DNS_NAME_TYPE_EDIT)->GetWindowText(m_szServiceDNSNameType);
  SetWizardButtons();
}

void CSCPPageGeneral::OnServiceClassChange()
{
  GetDlgItem(IDC_SERVICE_CLASS_EDIT)->GetWindowText(m_szServiceClassName);
  SetWizardButtons();
}

void CSCPPageGeneral::OnNameChange()
{
  GetDlgItem(IDC_NAME_EDIT)->GetWindowText(m_szName);
  if (m_pWizExt->GetObj() != NULL)
  {
    m_bNeedCreate = TRUE;
  }
  SetWizardButtons();
}

BOOL CSCPPageGeneral::OnKillActive()
{
  HRESULT hr = S_OK;
  BOOL bRet = TRUE;

  // Write changes to temporary object
  ASSERT(m_pWizExt != NULL);
  CComPtr<IDsAdminNewObjPrimarySite> spPrimarySite;
  spPrimarySite = m_pWizExt->GetIDsAdminNewObjPrimarySite();
  ASSERT(spPrimarySite != NULL);

  if (spPrimarySite != NULL)
  {
    CString szName;
    GetDlgItem(IDC_NAME_EDIT)->GetWindowText(szName);
    if (!szName.IsEmpty() && m_bNeedCreate)
    {
      hr = spPrimarySite->CreateNew(szName);
      if (FAILED(hr))
      {
        AfxMessageBox(_T("Failed to create temporary object."));
        bRet = FALSE;
      }
      else
      {
        m_bNeedCreate = FALSE;
      }
    }
  }

  if (m_pWizExt->GetObj() != NULL && bRet)
  {
    CString szDescription;
    GetDlgItem(IDC_DESCRIPTION_EDIT)->GetWindowText(szDescription);
    if (!szDescription.IsEmpty())
    {
      hr = SetStringAttribute(m_pWizExt->GetObj(), L"adminDescription", szDescription);
      if (FAILED(hr))
      {
        AfxMessageBox(_T("Failed to set the description."));
        bRet = FALSE;
      }
    }
    if (bRet)
    {
      hr = SetStringAttribute(m_pWizExt->GetObj(), L"serviceClassName", m_szServiceClassName);
      if (FAILED(hr))
      {
        AfxMessageBox(_T("Failed to set the service class name."));
        bRet = FALSE;
      }
    }

    if (bRet)
    {
      hr = SetStringAttribute(m_pWizExt->GetObj(), L"serviceDNSName", m_szServiceDNSName);
      if (FAILED(hr))
      {
        AfxMessageBox(_T("Failed to set the service DNS name."));
        bRet = FALSE;
      }
    }

    if (bRet)
    {
      hr = SetStringAttribute(m_pWizExt->GetObj(), L"serviceDNSNameType", m_szServiceDNSNameType);
      if (FAILED(hr))
      {
        AfxMessageBox(_T("Failed to set the service DNS name type."));
        bRet = FALSE;
      }
    }

  }

  return bRet;
}

BOOL CSCPPageGeneral::OnSetActive()
{
  SetWizardButtons();
  return TRUE;
}

void CSCPPageGeneral::SetWizardButtons()
{
  ASSERT(m_pWizExt != NULL);

  //
  // Enable the next button if the user has supplied a name, dns name,
  // class name, and dns name type
  //
  BOOL bValid = FALSE;
  if (!m_szName.IsEmpty() && 
      !m_szServiceDNSName.IsEmpty() && 
      !m_szServiceClassName.IsEmpty() &&
      !m_szServiceDNSNameType.IsEmpty())
  {
    bValid = TRUE;
  }
  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(0, bValid);
}

void CSCPPageGeneral::GetSummaryInfo(CString& szSummary)
{
  szSummary =   _T("Name:\t") + m_szName + _T("\n");
  szSummary +=  _T("Service DNS Name:\t") + m_szServiceDNSName + _T("\n");
  szSummary +=  _T("Service DNS Name Type:\t") + m_szServiceDNSNameType + _T("\n");
  szSummary +=  _T("Service Class Name:\t") + m_szServiceClassName + _T("\n");

  CString szDescription;
  GetDlgItem(IDC_DESCRIPTION_EDIT)->GetWindowText(szDescription);
  if (!szDescription.IsEmpty())
  {
    szSummary += _T("Description:\t") + szDescription + _T("\n");
  }
}

//
//
//


BEGIN_MESSAGE_MAP(CSCPPageBindingInfo, CPropertyPage)
  ON_BN_CLICKED(IDC_ADD_BUTTON, OnButtonClick)
  ON_BN_CLICKED(IDC_DELETE_BUTTON, OnButtonClick)
END_MESSAGE_MAP()

CSCPPageBindingInfo::CSCPPageBindingInfo(CSCPWiz* pWizExt)
  : CPropertyPage(IDD_SCP_PAGE_BINDING_INFO) 
{
  m_pWizExt = pWizExt;
  m_pAttributeEditor = NULL;
}


BOOL CSCPPageBindingInfo::OnInitDialog()
{
  BOOL bResult = CPropertyPage::OnInitDialog();

  //
  // Set the name of the container
  //
  SetDlgItemText(IDC_EDIT_CONTAINER, m_pWizExt->GetContainerCanonicalName());

  // 
  // Set the class icon
  //
  ((CStatic*)GetDlgItem(IDC_STATIC_ICON))->SetIcon(m_pWizExt->GetClassIcon());

  // Disable the Next wizard button until all the controls are filled with valid data.
  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(1, FALSE);
  if (FAILED(hr))
  {
    // Give error message if the buttons don't get set
    CString szErrorMessage;
    szErrorMessage.Format(_T("SetButtons(1, FALSE) failed with %x"), hr);
    AfxMessageBox(szErrorMessage);
  }

  m_pAttributeEditor = new CMultiValuedAttributeEditor(m_szValueList);
  m_pAttributeEditor->Initialize(IDC_KEYWORD_EDIT,
                                  IDC_KEYWORD_LIST,
                                  IDC_ADD_BUTTON,
                                  IDC_DELETE_BUTTON,
                                  this);

  return bResult;
}

BOOL CSCPPageBindingInfo::OnKillActive()
{
  BOOL bRet = TRUE;
  HRESULT hr = S_OK;

  // Write changes to temporary object
  ASSERT(m_pWizExt != NULL);
  if (m_pWizExt != NULL && m_pWizExt->GetObj() != NULL)
  {
    hr = SetStringListAttribute(m_pWizExt->GetObj(), L"serviceBindingInformation", m_szValueList);
    if (FAILED(hr))
    {
      AfxMessageBox(_T("Failed to set binding information in temporary object."));
      bRet = FALSE;
    }
  }
  return bRet;
}

BOOL CSCPPageBindingInfo::OnSetActive()
{
  SetWizardButtons();
  return TRUE;
}

void CSCPPageBindingInfo::OnButtonClick()
{
  SetWizardButtons();
}

void CSCPPageBindingInfo::SetWizardButtons()
{
  ASSERT(m_pWizExt != NULL);

  //
  // Enable the next button if the user has supplied at least one value
  //
  BOOL bValid = (m_szValueList.GetCount() > 0) ? TRUE : FALSE;
  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(1, bValid);
}

void CSCPPageBindingInfo::GetSummaryInfo(CString& szSummary)
{
  szSummary = _T("Binding Info:\n");
  POSITION pos = m_szValueList.GetHeadPosition();
  while (pos != NULL)
  {
    CString szValue = m_szValueList.GetNext(pos);
    szSummary += _T("\t") + szValue + _T("\n");
  }
}

//
//
//


BEGIN_MESSAGE_MAP(CSCPPageKeywords, CPropertyPage)
END_MESSAGE_MAP()

CSCPPageKeywords::CSCPPageKeywords(CSCPWiz* pWizExt) 
  : CPropertyPage(IDD_SCP_PAGE_KEYWORDS) 
{
  m_pWizExt = pWizExt;
  m_pAttributeEditor = NULL;
}

BOOL CSCPPageKeywords::OnInitDialog()
{
  BOOL bResult = CPropertyPage::OnInitDialog();

  //
  // Set the name of the container
  //
  SetDlgItemText(IDC_EDIT_CONTAINER, m_pWizExt->GetContainerCanonicalName());

  // 
  // Set the class icon
  //
  ((CStatic*)GetDlgItem(IDC_STATIC_ICON))->SetIcon(m_pWizExt->GetClassIcon());

  // Disable the Next wizard button until all the controls are filled with valid data.
  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(2, FALSE);
  if (FAILED(hr))
  {
    // Give error message if the buttons don't get set
    CString szErrorMessage;
    szErrorMessage.Format(_T("SetButtons(2, FALSE) failed with %x"), hr);
    AfxMessageBox(szErrorMessage);
  }

  
  m_pAttributeEditor = new CMultiValuedAttributeEditor(m_szValueList);
  m_pAttributeEditor->Initialize(IDC_KEYWORD_EDIT,
                                  IDC_KEYWORD_LIST,
                                  IDC_ADD_BUTTON,
                                  IDC_DELETE_BUTTON,
                                  this);


  return bResult;
}

BOOL CSCPPageKeywords::OnKillActive()
{
  BOOL bRet = TRUE;
  HRESULT hr = S_OK;

  // Write changes to temporary object
  ASSERT(m_pWizExt != NULL);
  if (m_pWizExt != NULL && m_pWizExt->GetObj() != NULL)
  {
    if (m_szValueList.GetCount() > 0)
    {
      hr = SetStringListAttribute(m_pWizExt->GetObj(), L"keywords", m_szValueList);
      if (FAILED(hr))
      {
        AfxMessageBox(_T("Failed to set keywords in temporary object."));
        bRet = FALSE;
      }
    }
  }
  return bRet;
}

BOOL CSCPPageKeywords::OnSetActive()
{
  SetWizardButtons();
  return TRUE;
}

void CSCPPageKeywords::SetWizardButtons()
{
  ASSERT(m_pWizExt != NULL);

  //
  // Enable the next button if the user has supplied at least on value
  //
  BOOL bValid = TRUE;
  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(2, bValid);
}

void CSCPPageKeywords::GetSummaryInfo(CString& szSummary)
{
  szSummary = _T("Keywords:\n");
  POSITION pos = m_szValueList.GetHeadPosition();
  while (pos != NULL)
  {
    CString szValue = m_szValueList.GetNext(pos);
    szSummary += _T("\t") + szValue + _T("\n");
  }
}
