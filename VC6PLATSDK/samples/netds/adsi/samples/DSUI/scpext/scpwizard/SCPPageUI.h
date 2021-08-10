//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPPageUI.h
//
//--------------------------------------------------------------------------

#ifndef _SCPPAGEUI_H
#define _SCPPAGEUI_H

#include "resource.h"
#include "util.h"

class CSCPWiz;

class CSCPPageGeneral : public CPropertyPage
{
public:
  CSCPPageGeneral(CSCPWiz* pWizExt) 
    : CPropertyPage(IDD_SCP_PAGE_GENERAL) 
  {
    m_pWizExt = pWizExt;
    m_szName  = _T("");
    m_szServiceClassName  = _T("");
    m_szServiceDNSName    = _T("");
    m_bNeedCreate = TRUE;
  }

  virtual ~CSCPPageGeneral() 
  {
  }

  enum { IDD = IDD_SCP_PAGE_GENERAL};

  virtual BOOL OnInitDialog();
  virtual BOOL OnKillActive();
  virtual BOOL OnSetActive();

  afx_msg void OnNameChange();
  afx_msg void OnServiceClassChange();
  afx_msg void OnDNSNameChange();
  afx_msg void OnDNSNameTypeChange();

  void SetWizardButtons();

  void GetSummaryInfo(CString& szSummary);

  DECLARE_MESSAGE_MAP()

private:
  CString   m_szName;
  CString   m_szServiceClassName;
  CString   m_szServiceDNSName;
  CString   m_szServiceDNSNameType;

  BOOL      m_bNeedCreate;

  CSCPWiz*  m_pWizExt;
};

class CSCPPageBindingInfo : public CPropertyPage
{
public:
  CSCPPageBindingInfo(CSCPWiz* pWizExt);

  virtual ~CSCPPageBindingInfo() 
  {
    if (m_pAttributeEditor != NULL)
      delete m_pAttributeEditor;
  }

  enum { IDD = IDD_SCP_PAGE_BINDING_INFO};

  virtual BOOL OnInitDialog();
  virtual BOOL OnKillActive();
  virtual BOOL OnSetActive();

  afx_msg void OnButtonClick();

  void SetWizardButtons();

  void GetSummaryInfo(CString& szSummary);

  DECLARE_MESSAGE_MAP()

private:
  CSCPWiz* m_pWizExt;

  CStringList m_szValueList;

  CMultiValuedAttributeEditor*  m_pAttributeEditor;
};


class CSCPPageKeywords : public CPropertyPage
{
public:
  CSCPPageKeywords(CSCPWiz* pWizExt);

  virtual ~CSCPPageKeywords() 
  {
    if (m_pAttributeEditor != NULL)
      delete m_pAttributeEditor;
  }

  enum { IDD = IDD_SCP_PAGE_KEYWORDS};

  virtual BOOL OnInitDialog();
  virtual BOOL OnKillActive();
  virtual BOOL OnSetActive();

  void SetWizardButtons();

  void GetSummaryInfo(CString& szSummary);

  DECLARE_MESSAGE_MAP()

private:
  CSCPWiz* m_pWizExt;

  CStringList m_szValueList;
  CMultiValuedAttributeEditor*  m_pAttributeEditor;
};

#endif //_SCPPAGEUI_H