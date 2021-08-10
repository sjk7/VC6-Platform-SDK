//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCP.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "SCP.h"
#include "util.h"
#include "adsprop.h"
#include "dsclient.h"   //CFSTR_DSOBJECTNAMES

//
// IShellExtInit interface
//
STDMETHODIMP CSCP::Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObject, HKEY hKeyID)
{
  if (pDataObject != NULL)
  {
    //
    // Store the IDataObject in a smart pointer.
    //
    m_spDataObj = pDataObject;
  }
  else
  {
    return E_INVALIDARG;
  }
  return S_OK;
}

//
// IShellPropSheetExt interface
//
STDMETHODIMP CSCP::AddPages(LPFNADDPROPSHEETPAGE pAddPageProc, LPARAM lParam)
{
  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  //
  // Unpack the data pointer and create the property page.
  // Register clipboard format
  //
  CLIPFORMAT cfDsObjectNames = (CLIPFORMAT)RegisterClipboardFormat(CFSTR_DSOBJECTNAMES);
  ASSERT(cfDsObjectNames != 0);

  FORMATETC fmte = { cfDsObjectNames, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
  STGMEDIUM objMedium;

  HRESULT hr = m_spDataObj->GetData(&fmte, &objMedium);
  if (FAILED(hr))
  {
    AfxMessageBox(_T("Failed to retrieve data from medium."));
    return hr;
  }

  LPDSOBJECTNAMES pDsObjectNames;
  pDsObjectNames = (LPDSOBJECTNAMES)objMedium.hGlobal;
  if (pDsObjectNames->cItems < 1)
  {
    return ERROR_INVALID_DATA;
  }

  PWSTR pszObjADsPath = (PWSTR)BYTE_OFFSET(pDsObjectNames, pDsObjectNames->aObjects[0].offsetName);
  PWSTR pszClass = (PWSTR)BYTE_OFFSET(pDsObjectNames, pDsObjectNames->aObjects[0].offsetClass);
  TRACE(_T("Object path: %s, class: %s\n"), pszObjADsPath, pszClass);

  //
  // Create/contact the notification object.
  //
  HWND hNotifyObj;

  hr = ADsPropCreateNotifyObj(m_spDataObj, pszObjADsPath, &hNotifyObj);
  
  if (FAILED(hr))
  {
    return hr;
  }

  //
  // Create and initialize the general page
  //
  m_pProppageUIGeneral = new CSCPUIGeneral(hNotifyObj);
  m_pProppageUIGeneral->Init(pszObjADsPath, pszClass);

  //
  // Add the general page to the sheet
  //
  ((PROPSHEETPAGE*)&m_pProppageUIGeneral->m_psp)->lParam = (LPARAM)m_pProppageUIGeneral;
  if (!(*pAddPageProc)(CreatePropertySheetPage((PROPSHEETPAGE*)&m_pProppageUIGeneral->m_psp), (LPARAM)lParam))
  {
    return E_FAIL;
  }

  //
  // Create and initialize the binding information page
  //
  m_pProppageUIBindingInfo = new CSCPUIBindingInfo(hNotifyObj);
  m_pProppageUIBindingInfo->Init(pszObjADsPath, pszClass);

  //
  // Add the binding information page to the sheet
  //
  ((PROPSHEETPAGE*)&m_pProppageUIBindingInfo->m_psp)->lParam = (LPARAM)m_pProppageUIBindingInfo;
  if (!(*pAddPageProc)(CreatePropertySheetPage((PROPSHEETPAGE*)&m_pProppageUIBindingInfo->m_psp), (LPARAM)lParam))
  {
    return E_FAIL;
  }

  //
  // Create and initialize the keywords page
  //
  m_pProppageUIKeywords = new CSCPUIKeywords(hNotifyObj);
  m_pProppageUIKeywords->Init(pszObjADsPath, pszClass);

  //
  // Add the keywords page to the sheet
  //
  ((PROPSHEETPAGE*)&m_pProppageUIKeywords->m_psp)->lParam = (LPARAM)m_pProppageUIKeywords;
  if (!(*pAddPageProc)(CreatePropertySheetPage((PROPSHEETPAGE*)&m_pProppageUIKeywords->m_psp), (LPARAM)lParam))
  {
    return E_FAIL;
  }

  return S_OK;
}

STDMETHODIMP CSCP::ReplacePage(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, LPARAM lParam)
{
  //
  // This method is not used.  It should only be called if the pages are an extension for the Control Panel.
  //
  return E_FAIL;
}
