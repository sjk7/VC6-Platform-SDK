//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       ExtPageUser.h
//
//--------------------------------------------------------------------------

#ifndef _EXTPAGEUSER_H
#define _EXTPAGEUSER_H

#include "resource.h"
#include "util.h"

class CWizExtUser;

class CExtPageUser : public CPropertyPage
{
public:
  CExtPageUser(CWizExtUser* pWizExt) 
    : CPropertyPage(IDD_USER_PAGE_EXT) 
  {
    m_pWizExt = pWizExt;
  }

  virtual ~CExtPageUser() 
  {
  }

  enum { IDD = IDD_USER_PAGE_EXT};

  afx_msg void OnChangePicture();
  afx_msg void OnClearPicture();


  virtual BOOL OnInitDialog();
  virtual BOOL OnKillActive();
  virtual BOOL OnSetActive();

private:
  CButton* GetChangePictureButton() { return (CButton*)GetDlgItem(IDC_BUTTON_CHANGE_PICTURE); }
  CButton* GetClearPictureButton() { return (CButton*)GetDlgItem(IDC_BUTTON_CLEAR_PICTURE); }
  CEdit*   GetPathEdit() { return (CEdit*)GetDlgItem(IDC_EDIT_PICTURE_PATH); }
  CEdit*   GetIDEdit() { return (CEdit*)GetDlgItem(IDC_EDIT_EMPLOYEE_ID); }
  CStatic* GetPicture() { return (CStatic*)GetDlgItem(IDC_PICTURE_DISPLAY); }

  void SetWizardButtons();

  HRESULT WriteDataHelper();
  void GetSummaryInfo(BSTR* pBstrText);

private:

  CThumbNailPhotoHolder     m_thumbNailPhotoHolder;

  
  CWizExtUser* m_pWizExt;
  friend class CWizExtUser;

  DECLARE_MESSAGE_MAP()
};

#endif //_EXTPAGEUSER_H