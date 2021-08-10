//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       scpcmenuui.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "resource.h"
#include "SCPCMenuUI.h"
#include <dsclient.h> // Clipboard formats

BEGIN_MESSAGE_MAP(CSCPCMenuDialog, CDialog)
END_MESSAGE_MAP()

BOOL CSCPCMenuDialog::OnInitDialog()
{
  //
  // Register the clipboard formats for retrieving info from the DS object
  //
  m_cfDsDisplaySpecOptions  = RegisterClipboardFormat(CFSTR_DS_DISPLAY_SPEC_OPTIONS);
  m_cfDsObjectNames         = RegisterClipboardFormat(CFSTR_DSOBJECTNAMES);

  RetrieveData();
  SetUIData();
  return TRUE;
}

void CSCPCMenuDialog::RetrieveData()
{
  //
  // Get display info using CFSTR_DS_DISPLAY_SPEC_OPTIONS
  //
  PDSDISPLAYSPECOPTIONS pDsSpecOptions = NULL;

  //
  // Need to get CFSTR_Ds_DISPLAY_SPEC_OPTIONS as HGLOBAL
  //
  STGMEDIUM stgmedium = { TYMED_HGLOBAL, NULL, NULL };

  //
  // Initialize formatetc for CFSTR_DS_DISPLAY_SPEC_OPTIONS format.
  //
  FORMATETC formatetc = { m_cfDsDisplaySpecOptions, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

  //
  // Get the global memory block containing the display option 
  // info for the selected object
  //
  HRESULT hr = m_spDataObj->GetData(&formatetc, &stgmedium);
  if (FAILED(hr))
  {
    return;
  }

  //
  // Assign pointer to DSDISPLAYSPECOPTIONS structure
  //
  pDsSpecOptions = (PDSDISPLAYSPECOPTIONS)GlobalLock(stgmedium.hGlobal);
  if (pDsSpecOptions != NULL)
  {
    m_szPrefix    = (PWSTR)BYTE_OFFSET(pDsSpecOptions, pDsSpecOptions->offsetAttribPrefix);
    m_szUsername  = (PWSTR)BYTE_OFFSET(pDsSpecOptions, pDsSpecOptions->offsetUserName);
    m_szServer    = (PWSTR)BYTE_OFFSET(pDsSpecOptions, pDsSpecOptions->offsetServer);
    m_szServerConfigPath = (PWSTR)BYTE_OFFSET(pDsSpecOptions, pDsSpecOptions->offsetServerConfigPath);
  }

  //
  // Clean up
  //
  GlobalUnlock(stgmedium.hGlobal);
  ReleaseStgMedium(&stgmedium);


  //
  // Get display info using CFSTR_DSOBJECTNAMES
  //
  FORMATETC fmte = { m_cfDsObjectNames, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
  STGMEDIUM objMedium;

  hr = m_spDataObj->GetData(&fmte, &objMedium);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to retrieve data from medium."));
    return;
  }

  LPDSOBJECTNAMES pDsObjectNames;
  pDsObjectNames = (LPDSOBJECTNAMES)objMedium.hGlobal;
  if (pDsObjectNames->cItems < 1)
  {
    return;
  }

  m_szADsPath = (PWSTR)BYTE_OFFSET(pDsObjectNames, pDsObjectNames->aObjects[0].offsetName);
  m_szClass = (PWSTR)BYTE_OFFSET(pDsObjectNames, pDsObjectNames->aObjects[0].offsetClass);
}

void CSCPCMenuDialog::SetUIData()
{
  GetDlgItem(IDC_PREFIX_EDIT)->SetWindowText(m_szPrefix);
  GetDlgItem(IDC_USER_EDIT)->SetWindowText(m_szUsername);
  GetDlgItem(IDC_SERVER_EDIT)->SetWindowText(m_szServer);
  GetDlgItem(IDC_SERVER_CONFIG_PATH_EDIT)->SetWindowText(m_szServerConfigPath);
  GetDlgItem(IDC_PATH_EDIT)->SetWindowText(m_szADsPath);
  GetDlgItem(IDC_CLASS_EDIT)->SetWindowText(m_szClass);
}