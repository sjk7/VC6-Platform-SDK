//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       ExtPageUser.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "ExtPageUser.h"
#include "WizExt.h"
#include "util.h"

BEGIN_MESSAGE_MAP(CExtPageUser, CPropertyPage)
  ON_BN_CLICKED(IDC_BUTTON_CHANGE_PICTURE, OnChangePicture)
  ON_BN_CLICKED(IDC_BUTTON_CLEAR_PICTURE, OnClearPicture)
END_MESSAGE_MAP()

BOOL CExtPageUser::OnInitDialog()
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

  //
  // Initialize the object that manipulates the thumbnail photo
  //
  m_thumbNailPhotoHolder.Initialize(GetPathEdit()->m_hWnd, GetPicture()->m_hWnd);

  return bResult;
}

BOOL CExtPageUser::OnKillActive()
{
  //
  // Write changes to temporary object
  //
  ASSERT(m_pWizExt != NULL);
  return (SUCCEEDED(WriteDataHelper()));
}

BOOL CExtPageUser::OnSetActive()
{
  //
  // Make sure we reset the next/back buttons state, just in case
  // some other extension changes it
  //
  SetWizardButtons();

  return TRUE;
}

void CExtPageUser::SetWizardButtons()
{
  ASSERT(m_pWizExt != NULL);

  //
  // Always enable the next button, we allow to have 
  // the fields not filled in.
  //

  HRESULT hr = m_pWizExt->GetIDsAdminNewObj()->SetButtons(0, TRUE /*bValid*/);
}

void CExtPageUser::OnChangePicture()
{
  //
  // just call the thumbnail photo holder to do the job
  // 
  m_thumbNailPhotoHolder.Change(m_hWnd);
}



void CExtPageUser::OnClearPicture()
{
  //
  // just call the thumbnail photo holder to do the job
  // 
  m_thumbNailPhotoHolder.Clear();
}



HRESULT CExtPageUser::WriteDataHelper()
{
  ASSERT(m_pWizExt->GetObj() != NULL);
  //
  // Write the data from the page to the temporary object given to the extension
  // by SetObject()
  //

  HRESULT hr = S_OK;

  CString szEmployeeID;
  GetIDEdit()->GetWindowText(szEmployeeID);
  hr = SetStringAttribute(m_pWizExt->GetObj(), _T("employeeID"), szEmployeeID);
  if (FAILED(hr))
  {
    // Format and display error message
    CString szErrorMessage;
    szErrorMessage.Format(_T("Failed to set employeeID to %s, hr = 0x%x"), (LPCWSTR)szEmployeeID, hr);
    AfxMessageBox(szErrorMessage);
    return hr;
  }

  //
  // Set the thumbnail photo in the temporary object
  //
  hr = m_thumbNailPhotoHolder.Write(m_pWizExt->GetObj());

  return hr;
}


void CExtPageUser::GetSummaryInfo(BSTR* pBstrText)
{
  //
  // Format the summary string which will be displayed on the finish page of the wizard.
  //
  CString szEmployeeID;
  GetIDEdit()->GetWindowText(szEmployeeID);

  CString strSummary;
  strSummary.Format(_T("Extension summary:\n\tEmployee ID: %s\n"), (LPCWSTR)szEmployeeID);

  //
  // Copy to BSTR
  //
  *pBstrText = ::SysAllocString(strSummary);

}

