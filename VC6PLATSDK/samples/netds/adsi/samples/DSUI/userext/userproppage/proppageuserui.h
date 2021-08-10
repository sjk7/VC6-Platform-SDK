//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       proppageuserui.h
//
//--------------------------------------------------------------------------

#ifndef _PROPPAGEUSERUI_H
#define _PROPPAGEUSERUI_H

#include "resource.h"
#include "util.h"




///////////////////////////////////////////////////////////////

class CProppageUserUI : public CPropertyPage
{
public:
  CProppageUserUI(HWND hNotifyObj) 
    : CPropertyPage(IDD_USER_PAGE_EXT),
      m_hNotifyObj(hNotifyObj)
  {
  }

  ~CProppageUserUI()
  {
  }

  afx_msg void OnChangePicture();
  afx_msg void OnClearPicture();
  afx_msg void OnEmployeeIDChange();

  virtual BOOL OnInitDialog();
  virtual BOOL OnApply();
  virtual void OnDestroy();


  HRESULT Init(PWSTR pszPath, PWSTR pszClass);

private:
  void SetUIData();
  void SetUIEmployeeID();
  void SetUIPhoto();

  HRESULT WriteEmployeeID();


  // Control accessors
  CButton* GetChangePictureButton() { return (CButton*)GetDlgItem(IDC_BUTTON_CHANGE_PICTURE); }
  CButton* GetClearPictureButton() { return (CButton*)GetDlgItem(IDC_BUTTON_CLEAR_PICTURE); }
  CEdit*   GetPathEdit() { return (CEdit*)GetDlgItem(IDC_EDIT_PICTURE_PATH); }
  CEdit*   GetIDEdit() { return (CEdit*)GetDlgItem(IDC_EDIT_EMPLOYEE_ID); }
  CStatic* GetPicture() { return (CStatic*)GetDlgItem(IDC_PICTURE_DISPLAY); }

private:
  HWND    m_hNotifyObj;
  CString                   m_szPath;
  CString                   m_szClass;

  CThumbNailPhotoHolder     m_thumbNailPhotoHolder;
  
  CComPtr<IDirectoryObject> m_spDsObj;
  PADS_ATTR_INFO            m_pWritableAttrs;

  DECLARE_MESSAGE_MAP()
};

#endif // _PROPPAGEUSERUI_H