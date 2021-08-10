//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPUI.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "SCPUI.h"
#include "util.h"
#include "adsprop.h"

//
// General Page
//

BEGIN_MESSAGE_MAP(CSCPUIGeneral, CPropertyPage)
  ON_EN_CHANGE(IDC_DNS_NAME_EDIT, OnPropertyChange)
  ON_EN_CHANGE(IDC_DNS_NAME_TYPE_EDIT, OnPropertyChange)
  ON_EN_CHANGE(IDC_SERVICE_CLASS_EDIT, OnPropertyChange)
  ON_EN_CHANGE(IDC_DESCRIPTION_EDIT, OnPropertyChange)
  ON_WM_DESTROY()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CSCPUIGeneral, CPropertyPage)

BOOL CSCPUIGeneral::OnInitDialog()
{
  BOOL bRes = CPropertyPage::OnInitDialog();

  //
  // Verify that this page is only coming up for users
  //
  ASSERT(m_szClass == _T("serviceConnectionPoint"));

  //
  // Display data in UI
  //
  SetUIData();

  //
  // The page may have become dirty due to the SetWindowText() in SetUIData(),
  // so clear the dirty flag.
  //
  m_bDirty = FALSE;
  return bRes;
}

HRESULT CSCPUIGeneral::Init(PWSTR pszPath, PWSTR pszClass)
{
  //
  // Store local versions of the path and class
  //
  m_szPath = pszPath;
  m_szClass = pszClass;

  // 
  // Get the property page initialization parameters from the notify window
  //
  ADSPROPINITPARAMS InitParams = {0};
  InitParams.dwSize = sizeof(ADSPROPINITPARAMS);
  if (!ADsPropGetInitInfo(m_hNotifyObj, &InitParams))
  {
    return E_FAIL;
  }

  if (FAILED(InitParams.hr))
  {
    return InitParams.hr;
  }

  //
  // Store local versions of the IDirectoryObject interface pointer
  // and the writable attributes
  //
  m_spDsObj = InitParams.pDsObj;
  m_pWritableAttrs = InitParams.pWritableAttrs;

  return S_OK;
}

void CSCPUIGeneral::SetUIData()
{
  //
  // Prime the controls with the data from the object
  //
  LPWSTR ppszAttrNames[] = { _T("adminDescription"), 
                             _T("serviceDnsName"),
                             _T("serviceDnsNameType"),
                             _T("serviceClassName") };
  PADS_ATTR_INFO pAttrInfo = NULL;
  DWORD dwReturned = 0;

  //
  // Retrieve the data
  //
  HRESULT hr = m_spDsObj->GetObjectAttributes(ppszAttrNames, 4, &pAttrInfo, &dwReturned);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to retrieve data for this object."));
    return;
  }

  //
  // Put the data in the appropriate control
  //
  for (DWORD idx = 0; idx < dwReturned; idx++)
  {
    ASSERT(pAttrInfo != NULL);
    if (_wcsicmp(pAttrInfo[idx].pszAttrName, L"adminDescription") == 0)
    {
      m_szDescription = pAttrInfo[idx].pADsValues->CaseIgnoreString;
      GetDlgItem(IDC_DESCRIPTION_EDIT)->SetWindowText(m_szDescription);
    }
    else if (_wcsicmp(pAttrInfo[idx].pszAttrName, L"serviceDnsName") == 0)
    {
      m_szServiceDNSName = pAttrInfo[idx].pADsValues->CaseIgnoreString;
      GetDlgItem(IDC_DNS_NAME_EDIT)->SetWindowText(m_szServiceDNSName);
    }
    else if (_wcsicmp(pAttrInfo[idx].pszAttrName, L"serviceDnsNameType") == 0)
    {
      m_szServiceDNSNameType = pAttrInfo[idx].pADsValues->CaseIgnoreString;
      GetDlgItem(IDC_DNS_NAME_TYPE_EDIT)->SetWindowText(m_szServiceDNSNameType);
    }
    else if (_wcsicmp(pAttrInfo[idx].pszAttrName, L"serviceClassName") == 0)
    {
      m_szServiceClassName = pAttrInfo[idx].pADsValues->CaseIgnoreString;
      GetDlgItem(IDC_SERVICE_CLASS_EDIT)->SetWindowText(m_szServiceClassName);
    }
  }

  //
  // Free the memory allocated by GetObjectAttributes()
  //
  FreeADsMem(pAttrInfo);
}



void CSCPUIGeneral::GetUIData()
{
  //
  // Retrieve the data from the controls
  //
  GetDlgItem(IDC_DESCRIPTION_EDIT)->GetWindowText(m_szDescription);
  GetDlgItem(IDC_DNS_NAME_EDIT)->GetWindowText(m_szServiceDNSName);
  GetDlgItem(IDC_SERVICE_CLASS_EDIT)->GetWindowText(m_szServiceClassName);
  GetDlgItem(IDC_DNS_NAME_TYPE_EDIT)->GetWindowText(m_szServiceDNSNameType);
}

BOOL CSCPUIGeneral::OnApply()
{
  if (!m_bDirty)
  {
    //
    // Signal the change notification. Note that the notify-apply 
    // message must be sent even if the page is not dirty so that 
    // the notify ref-counting will properly decrement.
    //
    ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

    return TRUE;
  }

  ASSERT(m_spDsObj != NULL);

  //
  // Retrieve the data from the UI
  //
  GetUIData();

  HRESULT hr = S_OK;
  ADS_ATTR_INFO attrInfo[4];
  PWSTR rgpwzAttrNames[] = { _T("adminDescription"),
                             _T("serviceDNSName"),
                             _T("serviceDNSNameType"),
                             _T("serviceClassName") };
  ADSVALUE Value[4];

  //
  // Set the update values for adminDescription
  //
  attrInfo[0].dwADsType = ADSTYPE_OCTET_STRING;
  attrInfo[0].pszAttrName = rgpwzAttrNames[0];
  
  Value[0].dwType = ADSTYPE_CASE_IGNORE_STRING;
  Value[0].CaseIgnoreString = (LPWSTR)(LPCWSTR)m_szDescription;

  attrInfo[0].pADsValues = &Value[0];
  attrInfo[0].dwNumValues = 1;
  attrInfo[0].dwControlCode = ADS_ATTR_UPDATE;

  //
  // Set the update values for serviceDNSName
  //
  attrInfo[1].dwADsType = ADSTYPE_CASE_IGNORE_STRING;
  attrInfo[1].pszAttrName = rgpwzAttrNames[1];
  
  Value[1].dwType = ADSTYPE_CASE_IGNORE_STRING;
  Value[1].CaseIgnoreString  = (LPWSTR)(LPCWSTR)m_szServiceDNSName;
  
  attrInfo[1].pADsValues = &Value[1];
  attrInfo[1].dwNumValues = 1;
  attrInfo[1].dwControlCode = ADS_ATTR_UPDATE;

  //
  // Set the update values for serviceDNSNameType
  //
  attrInfo[2].dwADsType = ADSTYPE_CASE_IGNORE_STRING;
  attrInfo[2].pszAttrName = rgpwzAttrNames[2];
  
  Value[2].dwType = ADSTYPE_CASE_IGNORE_STRING;
  Value[2].CaseIgnoreString  = (LPWSTR)(LPCWSTR)m_szServiceDNSNameType;
  
  attrInfo[2].pADsValues = &Value[2];
  attrInfo[2].dwNumValues = 1;
  attrInfo[2].dwControlCode = ADS_ATTR_UPDATE;

  //
  // Set the update values for serviceClassName
  //
  attrInfo[3].dwADsType = ADSTYPE_CASE_IGNORE_STRING;
  attrInfo[3].pszAttrName = rgpwzAttrNames[3];
  
  Value[3].dwType = ADSTYPE_CASE_IGNORE_STRING;
  Value[3].CaseIgnoreString = (LPWSTR)(LPCWSTR)m_szServiceClassName;
  
  attrInfo[3].pADsValues = &Value[3];
  attrInfo[3].dwNumValues = 1;
  attrInfo[3].dwControlCode = ADS_ATTR_UPDATE;

  //
  // Set the new values in Active Directory
  //
  DWORD dwReturned = 0;
  hr = m_spDsObj->SetObjectAttributes(attrInfo, 4, &dwReturned);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to set values for object."));
    return FALSE;
  }

  if (dwReturned < 4)
  {
    AfxMessageBox(_T("Failed to set values for object."));
    return FALSE;
  }

  //
  // Signal the change notification. Note that the notify-apply 
  // message must be sent even if the page is not dirty so that 
  // the notify ref-counting will properly decrement.
  //
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

  return TRUE;
}

void CSCPUIGeneral::OnPropertyChange()
{
  m_bDirty = TRUE;

  //
  // Enable the apply button
  //
  SetModified(TRUE);
}

void CSCPUIGeneral::OnDestroy()
{
  CPropertyPage::OnDestroy();

  //
  // Tell the notification object to shut down
  //
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_EXIT, 0, 0);

  delete this;
}


//
// Binding Information page
//

BEGIN_MESSAGE_MAP(CSCPUIBindingInfo, CPropertyPage)
  ON_BN_CLICKED(IDC_ADD_BUTTON, OnPropertyChange)
  ON_BN_CLICKED(IDC_DELETE_BUTTON, OnPropertyChange)
  ON_WM_DESTROY()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CSCPUIBindingInfo, CPropertyPage)

BOOL CSCPUIBindingInfo::OnInitDialog()
{
  BOOL bRes = CPropertyPage::OnInitDialog();

  //
  // Verify that this page is only coming up for users
  //
  ASSERT(m_szClass == _T("serviceConnectionPoint"));

  //
  // Display data in UI
  //
  SetUIData();

  //
  // Create and initialize the multi-valued attribute editor
  //
  m_pAttributeEditor = new CMultiValuedAttributeEditor(m_szValueList);
  m_pAttributeEditor->Initialize(IDC_KEYWORD_EDIT,
                                  IDC_KEYWORD_LIST,
                                  IDC_ADD_BUTTON,
                                  IDC_DELETE_BUTTON,
                                  this);

  //
  // The page may have been marked dirty due to the SetWindowText() in SetUIData(),
  // so clear the dirty flag.
  //
  m_bDirty = FALSE;
  return bRes;
}

HRESULT CSCPUIBindingInfo::Init(PWSTR pszPath, PWSTR pszClass)
{
  //
  // Store local versions of the path and class
  //
  m_szPath = pszPath;
  m_szClass = pszClass;

  // 
  // Get the property page initialization parameters from the notify window
  //
  ADSPROPINITPARAMS InitParams = {0};
  InitParams.dwSize = sizeof(ADSPROPINITPARAMS);
  if (!ADsPropGetInitInfo(m_hNotifyObj, &InitParams))
  {
    return E_FAIL;
  }

  if (FAILED(InitParams.hr))
  {
    return InitParams.hr;
  }

  //
  // Store local versions of the IDirectoryObject interface pointer
  // and the writable attributes
  //
  m_spDsObj = InitParams.pDsObj;
  m_pWritableAttrs = InitParams.pWritableAttrs;

  return S_OK;
}

void CSCPUIBindingInfo::SetUIData()
{
  //
  // Prime the controls with the data from the object
  //
  LPWSTR ppszAttrNames[] = { _T("serviceBindingInformation") };
  PADS_ATTR_INFO pAttrInfo = NULL;
  DWORD dwReturned = 0;

  //
  // Retrieve the data from Active Directory
  //
  HRESULT hr = m_spDsObj->GetObjectAttributes(ppszAttrNames, 1, &pAttrInfo, &dwReturned);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to retrieve data for this object."));
    return;
  }

  if (dwReturned < 1)
  {
    AfxMessageBox(_T("Failed to retrieve data for this object."));
    return;
  }

  ASSERT(pAttrInfo != NULL);

  //
  // Store the data locally
  //
  for (DWORD idx = 0; idx < dwReturned; idx++)
  {
    for (UINT nCount = 0; nCount < pAttrInfo->dwNumValues; nCount++)
    {
      m_szValueList.AddTail(pAttrInfo->pADsValues[nCount].CaseIgnoreString);
    }
  }

  //
  // Free the memory allocated by GetObjectAttributes()
  FreeADsMem(pAttrInfo);
}

BOOL CSCPUIBindingInfo::OnApply()
{
  if (!m_bDirty)
  {
    //
    // Signal the change notification. Note that the notify-apply 
    // message must be sent even if the page is not dirty so that 
    // the notify ref-counting will properly decrement.
    //
    ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

    return TRUE;
  }

  ASSERT(m_spDsObj != NULL);

  HRESULT hr = S_OK;
  ADS_ATTR_INFO attrInfo[1];
  PWSTR rgpwzAttrNames[] = { _T("serviceBindingInformation") };
  ADSVALUE* pValue = new ADSVALUE[m_szValueList.GetCount()];
  ASSERT(pValue != NULL);
  if (pValue == NULL)
    return FALSE;

  //
  // Set the update values for adminDescription
  //
  attrInfo[0].dwADsType = ADSTYPE_CASE_IGNORE_STRING;
  attrInfo[0].pszAttrName = rgpwzAttrNames[0];
  
  POSITION pos = m_szValueList.GetHeadPosition();
  for (int idx = 0; idx < m_szValueList.GetCount(); idx++)
  {
    CString szValue = m_szValueList.GetNext(pos);
    pValue[idx].dwType = ADSTYPE_CASE_IGNORE_STRING;
    pValue[idx].CaseIgnoreString = (LPWSTR)(LPCWSTR)szValue;

    if (pos == NULL)
    {
      break;
    }
  }

  attrInfo[0].pADsValues = pValue;
  attrInfo[0].dwNumValues = m_szValueList.GetCount();
  attrInfo[0].dwControlCode = ADS_ATTR_UPDATE;

  //
  // Update the data in Active Directory
  //
  DWORD dwReturned = 0;
  hr = m_spDsObj->SetObjectAttributes(attrInfo, 1, &dwReturned);
  if (FAILED(hr))
  {
    delete[] pValue;
    AfxMessageBox(_T("Failed to set values for object."));
    return FALSE;
  }
  //
  // Free the memory used to set the values
  //
  delete[] pValue;

  if (dwReturned < 1)
  {
    AfxMessageBox(_T("Failed to set values for object."));
    return FALSE;
  }
  //
  // Signal the change notification. Note that the notify-apply 
  // message must be sent even if the page is not dirty so that 
  // the notify ref-counting will properly decrement.
  //
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

  return TRUE;
}

void CSCPUIBindingInfo::OnPropertyChange()
{
  m_bDirty = TRUE;

  //
  // Enable the apply button
  //
  SetModified(TRUE);
}

void CSCPUIBindingInfo::OnDestroy()
{
  CPropertyPage::OnDestroy();

  //
  // Tell the notification object to shut down
  //
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_EXIT, 0, 0);

  delete this;
}


//
// Keywords Page
//

BEGIN_MESSAGE_MAP(CSCPUIKeywords, CPropertyPage)
  ON_BN_CLICKED(IDC_ADD_BUTTON, OnPropertyChange)
  ON_BN_CLICKED(IDC_DELETE_BUTTON, OnPropertyChange)
  ON_WM_DESTROY()
END_MESSAGE_MAP()

IMPLEMENT_DYNCREATE(CSCPUIKeywords, CPropertyPage)

BOOL CSCPUIKeywords::OnInitDialog()
{
  BOOL bRes = CPropertyPage::OnInitDialog();

  //
  // Verify that this page is only coming up for users
  //
  ASSERT(m_szClass == _T("serviceConnectionPoint"));

  //
  // Display data in UI
  //
  SetUIData();

  //
  // Create and initialize the multi-valued attribute editor
  //
  m_pAttributeEditor = new CMultiValuedAttributeEditor(m_szValueList);
  m_pAttributeEditor->Initialize(IDC_KEYWORD_EDIT,
                                  IDC_KEYWORD_LIST,
                                  IDC_ADD_BUTTON,
                                  IDC_DELETE_BUTTON,
                                  this);

  //
  // The page may have been marked dirty due to the SetWindowText() in SetUIData(),
  // so clear the dirty flag.
  //
  m_bDirty = FALSE;
  return bRes;
}

HRESULT CSCPUIKeywords::Init(PWSTR pszPath, PWSTR pszClass)
{
  //
  // Store local versions of the path and class
  //
  m_szPath = pszPath;
  m_szClass = pszClass;

  // 
  // Get the property page initialization parameters from the notify window
  //
  ADSPROPINITPARAMS InitParams = {0};
  InitParams.dwSize = sizeof(ADSPROPINITPARAMS);
  if (!ADsPropGetInitInfo(m_hNotifyObj, &InitParams))
  {
    return E_FAIL;
  }

  if (FAILED(InitParams.hr))
  {
    return InitParams.hr;
  }

  //
  // Store local versions of the IDirectoryObject interface pointer
  // and the writable attributes
  //
  m_spDsObj = InitParams.pDsObj;
  m_pWritableAttrs = InitParams.pWritableAttrs;

  return S_OK;
}

void CSCPUIKeywords::SetUIData()
{
  //
  // Prime the controls with the data from the object
  //
  LPWSTR ppszAttrNames[] = {  _T("keywords") };
  PADS_ATTR_INFO pAttrInfo = NULL;
  DWORD dwReturned = 0;

  //
  // Retrieve the data from Active Directory
  //
  HRESULT hr = m_spDsObj->GetObjectAttributes(ppszAttrNames, 1, &pAttrInfo, &dwReturned);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to retrieve data for this object."));
    return;
  }

  if (dwReturned < 1)
  {
    AfxMessageBox(_T("Failed to retrieve data for this object."));
    return;
  }

  ASSERT(pAttrInfo != NULL);

  //
  // Store the data locally
  //
  for (DWORD idx = 0; idx < dwReturned; idx++)
  {
    for (UINT nCount = 0; nCount < pAttrInfo->dwNumValues; nCount++)
    {
      m_szValueList.AddTail(pAttrInfo->pADsValues[nCount].CaseIgnoreString);
    }
  }

  //
  // Free the memory allocated by GetObjectAttributes()
  //
  FreeADsMem(pAttrInfo);
}

BOOL CSCPUIKeywords::OnApply()
{
  if (!m_bDirty)
  {
    //
    // Signal the change notification. Note that the notify-apply 
    // message must be sent even if the page is not dirty so that 
    // the notify ref-counting will properly decrement.
    //
    ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

    return TRUE;
  }

  ASSERT(m_spDsObj != NULL);

  HRESULT hr = S_OK;
  ADS_ATTR_INFO attrInfo[1];
  PWSTR rgpwzAttrNames[] = { _T("keywords") };
  ADSVALUE* pValue = new ADSVALUE[m_szValueList.GetCount()];
  ASSERT(pValue != NULL);
  if (pValue == NULL)
    return FALSE;

  //
  // Set the update values for adminDescription
  //
  attrInfo[0].dwADsType = ADSTYPE_CASE_IGNORE_STRING;
  attrInfo[0].pszAttrName = rgpwzAttrNames[0];
  
  POSITION pos = m_szValueList.GetHeadPosition();
  for (int idx = 0; idx < m_szValueList.GetCount(); idx++)
  {
    CString szValue = m_szValueList.GetNext(pos);
    pValue[idx].dwType = ADSTYPE_CASE_IGNORE_STRING;
    pValue[idx].CaseIgnoreString = (LPWSTR)(LPCWSTR)szValue;

    if (pos == NULL)
    {
      break;
    }
  }

  attrInfo[0].pADsValues = pValue;
  attrInfo[0].dwNumValues = m_szValueList.GetCount();
  attrInfo[0].dwControlCode = ADS_ATTR_UPDATE;

  //
  // Update the data in Active Directory
  //
  DWORD dwReturned = 0;
  hr = m_spDsObj->SetObjectAttributes(attrInfo, 1, &dwReturned);
  if (FAILED(hr))
  {
    delete[] pValue;
    AfxMessageBox(_T("Failed to set values for object."));
    return FALSE;
  }
  //
  // Free the memory used for SetObjectAttributes()
  //
  delete[] pValue;

  if (dwReturned < 1)
  {
    AfxMessageBox(_T("Failed to set values for object."));
    return FALSE;
  }

  
  //
  // Signal the change notification. Note that the notify-apply 
  // message must be sent even if the page is not dirty so that 
  // the notify ref-counting will properly decrement.
  //
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

  return TRUE;
}

void CSCPUIKeywords::OnPropertyChange()
{
  m_bDirty = TRUE;

  //
  // Enable the apply button
  //
  SetModified(TRUE);
}

void CSCPUIKeywords::OnDestroy()
{
  CPropertyPage::OnDestroy();

  //
  // Tell the notification object to shut down
  //
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_EXIT, 0, 0);

  delete this;
}