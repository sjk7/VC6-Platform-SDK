//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       scpcmenuui.h
//
//--------------------------------------------------------------------------

#ifndef __SCPCMENUUI_H
#define __SCPCMENUUI_H

#define BYTE_OFFSET(base, offset) (((LPBYTE)base)+offset)

class CSCPCMenuDialog : public CDialog
{
public:
  CSCPCMenuDialog(IDataObject* pDataObj) : CDialog(IDD_SCP_MENU_DIALOG)
  {
    m_spDataObj   = pDataObj;
    m_szPrefix    = _T("");
    m_szUsername  = _T("");
    m_szServer    = _T("");
    m_szServerConfigPath = _T("");
    m_szADsPath   = _T("");
    m_szClass     = _T("");
  }

  ~CSCPCMenuDialog() {}

  virtual BOOL OnInitDialog();

  void RetrieveData();
  void SetUIData();

  DECLARE_MESSAGE_MAP()
private:
  CComPtr<IDataObject>  m_spDataObj;
  CLIPFORMAT            m_cfDsDisplaySpecOptions;
  CLIPFORMAT            m_cfDsObjectNames;

  CString               m_szPrefix;
  CString               m_szUsername;
  CString               m_szServer;
  CString               m_szServerConfigPath;
  CString               m_szADsPath;
  CString               m_szClass;
};

#endif // __SCPCMENUUI_H