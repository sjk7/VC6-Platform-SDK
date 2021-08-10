//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       proppageuserui.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "ProppageUserUI.h"
#include "util.h"
#include "adsprop.h"

///////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CProppageUserUI, CPropertyPage)
  ON_BN_CLICKED(IDC_BUTTON_CHANGE_PICTURE, OnChangePicture)
  ON_BN_CLICKED(IDC_BUTTON_CLEAR_PICTURE, OnClearPicture)
  ON_EN_CHANGE(IDC_EDIT_EMPLOYEE_ID, OnEmployeeIDChange)
  ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL CProppageUserUI::OnInitDialog()
{
  //
  // Verify that this page is only coming up for users
  //
  ASSERT(m_szClass == _T("user"));

  BOOL bRes = CPropertyPage::OnInitDialog();


  m_thumbNailPhotoHolder.Initialize(GetPathEdit()->m_hWnd, GetPicture()->m_hWnd);

  
  //
  // Display data in UI
  //
  SetUIData();
  return bRes;
}

HRESULT CProppageUserUI::Init(PWSTR pszPath, PWSTR pszClass)
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

void CProppageUserUI::SetUIData()
{
  //
  // Prime the controls with the data from the object
  //
  SetUIEmployeeID();
  SetUIPhoto();
}

void CProppageUserUI::SetUIPhoto()
{
  // 
  // Get the thumbnailPhoto information from the object
  //
  m_thumbNailPhotoHolder.Read(m_spDsObj);

  //
  // Disable the Change/Clear buttons if the user does not
  // have write permissions for the thumbnailPhoto attribute
  //
  if (!ADsPropCheckIfWritable(_T("thumbnailPhoto"), m_pWritableAttrs))
  {
    GetChangePictureButton()->EnableWindow(FALSE);
    GetClearPictureButton()->EnableWindow(FALSE);
  }

}


void CProppageUserUI::OnChangePicture()
{
  if (m_thumbNailPhotoHolder.Change(m_hWnd))
  {
    //
    // Enable the Apply button
    //
    SetModified(TRUE);
  }
}

void CProppageUserUI::OnClearPicture()
{
  if(m_thumbNailPhotoHolder.Clear())
  {
    //
    // Enable the Apply button
    //
    SetModified(TRUE);
  }
}



void CProppageUserUI::SetUIEmployeeID()
{
  LPWSTR lpszAttrArray[] = { _T("employeeID") };
  PADS_ATTR_INFO pAttrInfo;
  DWORD dwReturned = 0;

  //
  // Get the employee ID
  //
  HRESULT hr = m_spDsObj->GetObjectAttributes(lpszAttrArray, 1, &pAttrInfo, &dwReturned);
  if (FAILED(hr))
  {
    CString szMsg;
    szMsg.Format(_T("Failed to read Employee ID attribute, with hr = 0x%x\n"), hr);
    AfxMessageBox(szMsg);
    return;
  }


  //
  // Retrieve the employee ID from the attribute 
  // information and set it in the edit box
  //
  if (dwReturned == 1)
  {
    ASSERT(pAttrInfo != NULL);
    
    LPCWSTR lpszText = NULL;
    if (pAttrInfo->dwNumValues > 0)
    {
      lpszText = pAttrInfo->pADsValues->CaseIgnoreString;
    }

    //
    // write data to the edit control
    GetIDEdit()->SetWindowText(lpszText);

    //
    // Free the attribute memory
    //
    FreeADsMem(pAttrInfo);
  }

  //
  // Disable the ID edit box if user does not have write permissions on the attribute
  //
  if (!ADsPropCheckIfWritable(_T("employeeID"), m_pWritableAttrs))
  {
    GetIDEdit()->EnableWindow(FALSE);
  }

}

void CProppageUserUI::OnEmployeeIDChange()
{
  //
  // Enable the apply button, it's dirty
  //
  SetModified(TRUE);
}

BOOL CProppageUserUI::OnApply()
{
  ASSERT(m_spDsObj != NULL);

  //
  // update the two attributes
  //
  HRESULT hr = m_thumbNailPhotoHolder.Write(m_spDsObj);


  hr = WriteEmployeeID();
  if (FAILED(hr))
  {
    CString szMsg;
    szMsg.Format(_T("Failed to write Employee ID, with hr = 0x%x\n"), hr);
    AfxMessageBox(szMsg);
    return FALSE;
  }


  // Signal the change notification. Note that the notify-apply 
  // message must be sent even if the page is not dirty so that 
  // the notify ref-counting will properly decrement.
  ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_APPLY, TRUE, 0);

  return TRUE;
}

void CProppageUserUI::OnDestroy()
{
  if (::IsWindow(m_hNotifyObj))
  {
    ::SendMessage(m_hNotifyObj, WM_ADSPROP_NOTIFY_EXIT, 0, 0);
  }
  CPropertyPage::OnDestroy();
  delete this;
}



HRESULT CProppageUserUI::WriteEmployeeID()
{
  ADS_ATTR_INFO attrInfo[1];
  PWSTR rgpwzAttrNames[] = {_T("employeeID") };
  ADSVALUE Value[1];

  //
  // Set the update/clear value
  //

  CString szEmployeeID;
  GetIDEdit()->GetWindowText(szEmployeeID);
  BOOL bUpdate = !szEmployeeID.IsEmpty();

  attrInfo[0].dwADsType = ADSTYPE_CASE_IGNORE_STRING;
  attrInfo[0].pszAttrName = rgpwzAttrNames[0];
  
  Value[0].dwType = ADSTYPE_CASE_IGNORE_STRING;
  Value[0].CaseIgnoreString  = bUpdate ? (LPWSTR)(LPCWSTR)szEmployeeID : NULL;
  
  attrInfo[0].pADsValues = &Value[0];
  attrInfo[0].dwNumValues = 1;
  attrInfo[0].dwControlCode = bUpdate ? ADS_ATTR_UPDATE : ADS_ATTR_CLEAR;

  //
  // Write the changes to the object
  //
  DWORD dwModified = 0;
  return m_spDsObj->SetObjectAttributes(attrInfo, 1, &dwModified);
}


