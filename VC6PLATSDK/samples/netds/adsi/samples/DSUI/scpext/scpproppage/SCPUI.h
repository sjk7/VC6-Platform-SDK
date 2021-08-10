//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPUI.h
//
//--------------------------------------------------------------------------

#ifndef _SCPUI_H
#define _SCPUI_H

#include "resource.h"
#include "util.h"

//
// General Page Definition
//
class CSCPUIGeneral : public CPropertyPage
{
  DECLARE_DYNCREATE(CSCPUIGeneral)
public:
  CSCPUIGeneral() {}
  CSCPUIGeneral(HWND hNotifyObj) 
    : CPropertyPage(IDD_SCP_GENERAL_PAGE),
      m_hNotifyObj(hNotifyObj)
  {
    m_bDirty = FALSE;
    m_szServiceDNSName    = _T("");
    m_szServiceDNSNameType= _T("");
    m_szBindingInfo       = _T("");
    m_szDescription       = _T("");
    m_szServiceClassName  = _T("");
  }

  ~CSCPUIGeneral()
  {
  }

  virtual BOOL OnInitDialog();
  virtual BOOL OnApply();
  virtual void OnDestroy();

  afx_msg void OnPropertyChange();

  virtual HRESULT Init(PWSTR pszPath, PWSTR pszClass);

  virtual void SetUIData();
  virtual void GetUIData();

  DECLARE_MESSAGE_MAP()

private:
  //
  // Member Data
  //
  HWND                      m_hNotifyObj;
  CString                   m_szPath;
  CString                   m_szClass;
  CComPtr<IDirectoryObject> m_spDsObj;
  PADS_ATTR_INFO            m_pWritableAttrs;

  BOOL                      m_bDirty;
  CString                   m_szServiceDNSName;
  CString                   m_szServiceDNSNameType;
  CString                   m_szBindingInfo;
  CString                   m_szDescription;
  CString                   m_szServiceClassName;
};

//
// Keywords Page Definition
//
class CSCPUIBindingInfo : public CPropertyPage
{
  DECLARE_DYNCREATE(CSCPUIBindingInfo)
public:
  CSCPUIBindingInfo() {}
  CSCPUIBindingInfo(HWND hNotifyObj) 
    : CPropertyPage(IDD_SCP_BINDING_INFO_PAGE),
      m_hNotifyObj(hNotifyObj)
  {
    m_bDirty = FALSE;
    m_pAttributeEditor = NULL;
  }

  ~CSCPUIBindingInfo()
  {
    if (m_pAttributeEditor != NULL)
      delete m_pAttributeEditor;
  }

  virtual BOOL OnInitDialog();
  virtual BOOL OnApply();
  virtual void OnDestroy();

  afx_msg void OnPropertyChange();

  virtual HRESULT Init(PWSTR pszPath, PWSTR pszClass);

  virtual void SetUIData();

  DECLARE_MESSAGE_MAP()

private:
  //
  // Member Data
  //
  HWND                      m_hNotifyObj;
  CString                   m_szPath;
  CString                   m_szClass;
  CComPtr<IDirectoryObject> m_spDsObj;
  PADS_ATTR_INFO            m_pWritableAttrs;

  BOOL                      m_bDirty;

  CStringList               m_szValueList;
  CMultiValuedAttributeEditor*  m_pAttributeEditor;
};

//
// Keywords Page Definition
//
class CSCPUIKeywords : public CPropertyPage
{
  DECLARE_DYNCREATE(CSCPUIKeywords)
public:
  CSCPUIKeywords() {}
  CSCPUIKeywords(HWND hNotifyObj) 
    : CPropertyPage(IDD_SCP_KEYWORDS_PAGE),
      m_hNotifyObj(hNotifyObj)
  {
    m_bDirty = FALSE;
    m_pAttributeEditor = NULL;
  }

  ~CSCPUIKeywords()
  {
    if (m_pAttributeEditor != NULL)
      delete m_pAttributeEditor;
  }

  virtual BOOL OnInitDialog();
  virtual BOOL OnApply();
  virtual void OnDestroy();

  afx_msg void OnPropertyChange();

  virtual HRESULT Init(PWSTR pszPath, PWSTR pszClass);

  virtual void SetUIData();

  DECLARE_MESSAGE_MAP()

private:
  //
  // Member Data
  //
  HWND                      m_hNotifyObj;
  CString                   m_szPath;
  CString                   m_szClass;
  CComPtr<IDirectoryObject> m_spDsObj;
  PADS_ATTR_INFO            m_pWritableAttrs;

  BOOL                      m_bDirty;

  CStringList               m_szValueList;
  CMultiValuedAttributeEditor*  m_pAttributeEditor;
};

#endif // _SCPUI_H