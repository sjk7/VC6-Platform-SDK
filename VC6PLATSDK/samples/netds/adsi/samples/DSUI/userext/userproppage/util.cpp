//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       util.cpp
//
//--------------------------------------------------------------------------

#include "stdafx.h"
#include "util.h"

////////////////////////////////////////////////////////////////////

HRESULT _ClearAttribute(IADs* pIADs, BSTR bstrAttrName, BOOL bPostCommit) 
{
  ASSERT(pIADs != NULL);
	ASSERT(bstrAttrName != NULL);
  HRESULT hr = S_OK;

  VARIANT varVal;
  ::VariantInit(&varVal);

  // see if the attribute is there
  HRESULT hrFind = pIADs->Get(bstrAttrName, &varVal);
  if (SUCCEEDED(hrFind))
  {
    // found, need to clear the property
    if (bPostCommit)
    {
      // remove from the committed object
      hr = pIADs->PutEx(ADS_PROPERTY_CLEAR, bstrAttrName, varVal);
    }
    else
    {
      // remove from the cache of the temporary object
      IADsPropertyList* pPropList = NULL;
      hr = pIADs->QueryInterface(IID_IADsPropertyList, (void**)&pPropList);
      ASSERT(pPropList != NULL);
      if (SUCCEEDED(hr))
      {
        VARIANT v;
        ::VariantInit(&v);
        v.vt = VT_BSTR;
        v.bstrVal = ::SysAllocString(bstrAttrName);
        hr = pPropList->ResetPropertyItem(v);
        ::VariantClear(&v);
        pPropList->Release();
      }
    }
  }

  ::VariantClear(&varVal);
  return hr;
}


////////////////////////////////////////////////////////////////////

HRESULT SetStringAttribute(IADs* pIADs, LPCWSTR lpszAttr, LPCWSTR lpszVal, BOOL bPostCommit)
{
  ASSERT(pIADs != NULL);
  ASSERT(lpszAttr != NULL);

  TRACE(_T("SetStringAttribute() on bPostCommit = %s\n"), bPostCommit ? L"TRUE" : L"FALSE");
	TRACE(_T("\t'%s' = <%s>\n"), lpszAttr, lpszVal);

  HRESULT hr = S_OK;
  BSTR bstrAttr = ::SysAllocString(lpszAttr);
  VARIANT varVal;
  ::VariantInit(&varVal);
  varVal.vt = VT_BSTR;
  varVal.bstrVal = ::SysAllocString(lpszVal);

  if ( (lpszVal == NULL) || ((lpszVal != NULL) && (lpszVal[0] == NULL)) )
  {
    hr = _ClearAttribute(pIADs, bstrAttr, bPostCommit);
  }
  else
  {
    // set the value
    hr = pIADs->Put(bstrAttr, varVal);
  }  
  ::SysFreeString(bstrAttr);
  ::VariantClear(&varVal);
  return hr;
}

HRESULT GetStringAttribute(IADs* pIADs, LPCWSTR lpszAttr, CString& szVal)
{
  ASSERT(pIADs != NULL);
  VARIANT varVal;
  ::VariantInit(&varVal);

  BSTR bstrAttr = ::SysAllocString(lpszAttr);
  
  szVal.Empty();
  HRESULT hr = pIADs->Get(bstrAttr, &varVal);
  if (SUCCEEDED(hr))
  {
    if (varVal.vt == VT_BSTR)
      szVal = varVal.bstrVal;
    else
      hr = E_INVALIDARG;
  }
  VariantClear(&varVal);
  ::SysFreeString(bstrAttr);
  
  TRACE(_T("GetStringAttribute()lpszAttr = <%s>, (LPCWSTR)szVal = <%s>\n"), lpszAttr, szVal);
  return hr;
}



HRESULT SetByteArrayAsOctetString(IADs* pIADs, LPCWSTR lpszAttr, BYTE* pByteArray, DWORD dwSize)
{
  if (pByteArray == NULL)
  {
    CComBSTR bstrAttr = lpszAttr;
    return _ClearAttribute(pIADs, bstrAttr, FALSE);
  }

  HRESULT hr = S_OK;
  SAFEARRAYBOUND rgsabound[1];
  rgsabound[0].lLbound = 0;
  rgsabound[0].cElements = dwSize;

  SAFEARRAY* psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
  if (psa == NULL)
  {
    return E_OUTOFMEMORY;
  }

  CComVariant var;
  V_VT(&var) = VT_UI1|VT_ARRAY;
  V_ARRAY(&var) = psa;

  for (long idx = 0; (DWORD)idx < dwSize; idx++)
  {
    hr = SafeArrayPutElement(psa, &idx, (void*)&pByteArray[idx]);
    if (FAILED(hr))
    {
      return hr;
    }
  }

  hr = pIADs->Put((LPWSTR)lpszAttr, var);
  //SafeArrayDestroy(psa);

  return hr;
}

BOOL LoadFileAsByteArray(PWSTR pszPath, LPBYTE* ppByteArray, DWORD* pdwSize)
{
  CFile file;
  if (!file.Open(pszPath, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary))
  {
    AfxMessageBox(_T("Failed to open file."));
    return FALSE;
  }

  *pdwSize = file.GetLength();
  *ppByteArray = new BYTE[*pdwSize];
  ASSERT(*ppByteArray != NULL);

  UINT uiCount = file.Read(*ppByteArray, *pdwSize);
  ASSERT(uiCount == *pdwSize);

  return TRUE;
}

///////////////////////////////////////////////////////////////
// CThumbNailPhotoHolder

static LPCWSTR lpszPhotoInDS = _T("<photo stored in Active-Directory>");



HRESULT CThumbNailPhotoHolder::Read(IADs* pIADs)
{
  return E_FAIL;
}

HRESULT CThumbNailPhotoHolder::Read(IDirectoryObject* pDirObj)
{
  LPWSTR lpszAttrArray[] = { _T("thumbnailPhoto") };
  PADS_ATTR_INFO pAttrInfo;
  DWORD dwReturned = 0;

  // 
  // Get the thumbnailPhoto information from the object
  //
  HRESULT hr = pDirObj->GetObjectAttributes(lpszAttrArray, 1, &pAttrInfo, &dwReturned);
  if (FAILED(hr))
  {
    CString szMsg;
    szMsg.Format(_T("Failed to read Thumbnail Photo attribute, with hr = 0x%x\n"), hr);
    AfxMessageBox(szMsg);
    return hr;
  }

   
  if (dwReturned > 0)
  {
    ASSERT(pAttrInfo != NULL);
    //
    // Create a temporary bmp file in the temp directory
    //

    WCHAR szTempPath[MAX_PATH];
    ::GetTempPath(MAX_PATH, szTempPath);
    
    CString szPicturePath;
    ::GetTempFileName(szTempPath, _T("thumbnail"), 0x0, szPicturePath.GetBuffer(MAX_PATH));
    szPicturePath.ReleaseBuffer();

    CFile tempPhotoFile;
    if (!tempPhotoFile.Open(szPicturePath, 
        CFile::modeCreate | CFile::modeReadWrite |CFile::shareExclusive | CFile::typeBinary))
    {
      // Failed to open temp file, display error message
      AfxMessageBox(_T("Unable to display thumbnail photo."));
      return E_FAIL;
    }

    ASSERT(pAttrInfo->dwADsType == ADSTYPE_OCTET_STRING);

    //
    // Delete current picture if one exists
    //
    _Clear();

    //
    // Create a new byte array to hold the bitmap
    //
    m_dwPictureSize = pAttrInfo->pADsValues->OctetString.dwLength;
    m_pPictureArray = new BYTE[m_dwPictureSize];
    memcpy(m_pPictureArray, pAttrInfo->pADsValues->OctetString.lpValue, m_dwPictureSize);
    ASSERT(m_pPictureArray != NULL);

    //
    // Write the byte array to a temp file
    //
    tempPhotoFile.Write(m_pPictureArray, m_dwPictureSize);
    CString szPath = tempPhotoFile.GetFilePath();
    tempPhotoFile.Close();

    //
    // Show the picture path in the read-only edit box
    //
    ::SetWindowText(m_hWndFileNameEdit, lpszPhotoInDS);

    //
    // Display the picture in the static control
    //
    _DisplayPicture(szPath);

    //
    // Delete temp file after picture is displayed
    //
    CFile::Remove(szPath);

    //
    // Free the attribute memory
    //
    FreeADsMem(pAttrInfo);
  }

  return S_OK;
}


HRESULT CThumbNailPhotoHolder::Write(IADs* pIADs)
{
  //
  // Write the changes to the object
  //
  HRESULT hr = SetByteArrayAsOctetString(pIADs, 
                                  _T("thumbnailPhoto"), 
                                  m_pPictureArray,
                                  (m_pPictureArray != NULL) ? m_dwPictureSize : 0);

  _WriteHelper(hr);
  
  return hr;
}


HRESULT CThumbNailPhotoHolder::Write(IDirectoryObject* pDirObj)
{
  ADS_ATTR_INFO attrInfo[1];
  PWSTR rgpwzAttrNames[] = { _T("thumbnailPhoto")};
  ADSVALUE Value[1];

  //
  // Set the update/clear value
  //

  attrInfo[0].dwADsType = ADSTYPE_OCTET_STRING;
  attrInfo[0].pszAttrName = rgpwzAttrNames[0];
  
  Value[0].dwType = ADSTYPE_OCTET_STRING;
  Value[0].OctetString.dwLength = (m_pPictureArray != NULL) ? m_dwPictureSize : 0;
  Value[0].OctetString.lpValue = m_pPictureArray;

  attrInfo[0].pADsValues = &Value[0];
  attrInfo[0].dwNumValues = 1;
  attrInfo[0].dwControlCode = (m_pPictureArray != NULL) ? ADS_ATTR_UPDATE : ADS_ATTR_CLEAR;

  //
  // Write the changes to the object
  //
  DWORD dwModified = 0;
  HRESULT hr = pDirObj->SetObjectAttributes(attrInfo, 1, &dwModified);

  _WriteHelper(hr);

  return hr;
}


void CThumbNailPhotoHolder::_WriteHelper(HRESULT hr)
{
  if (FAILED(hr))
  {
    CString szMsg;
    szMsg.Format(_T("Failed to write Thumbnail Photo attribute, with hr = 0x%x\n"), hr);
    AfxMessageBox(szMsg);
  }
  else
  {
    //
    // Show the picture path in the read-only edit box
    //
    ::SetWindowText(m_hWndFileNameEdit, (m_pPictureArray != NULL) ? lpszPhotoInDS : NULL);
  }
}


BOOL CThumbNailPhotoHolder::Change(HWND hWndOwner)
{
  TCHAR szFileName[MAX_PATH] = _T("\0");
  OPENFILENAME OpenFileName;
  memset(&OpenFileName, 0, sizeof(OpenFileName));

  //
  // Fill in the OPENFILENAME structure
  //
  OpenFileName.lStructSize        = sizeof(OPENFILENAME);
  OpenFileName.hwndOwner          = hWndOwner;
  OpenFileName.hInstance          = AfxGetInstanceHandle();
  OpenFileName.lpstrFile          = szFileName;
  OpenFileName.nMaxFile           = sizeof(szFileName);
  OpenFileName.lpstrFilter        = _T("Bitmap Files (*.bmp)\0*.bmp");
  OpenFileName.lpstrTitle         = _T("Select bitmap file");
  OpenFileName.Flags              = OFN_EXPLORER;

  //
  // Open file browse dialog and retrieve the path and name of the bitmap to use.
  //
  if (GetOpenFileName(&OpenFileName))
  {
    //
    // Load the picture into a temporary byte array
    //
    BYTE* pNewPictureArray = NULL;
    DWORD dwNewPictureSize = 0x0;

    if (!LoadFileAsByteArray(szFileName, &pNewPictureArray, &dwNewPictureSize))
    {
      CString szMsg;
      szMsg.Format(_T("Failed to open file %s."), szFileName);
      AfxMessageBox(szMsg);
      return FALSE;
    }

    ASSERT(pNewPictureArray != NULL);

    ::SetWindowText(m_hWndFileNameEdit, szFileName);

    //
    // Display the picture in the static window
    //
    if (!_DisplayPicture(szFileName))
    {
      CString szMsg;
      szMsg.Format(_T("Failed to load file %s as a bitmap."), szFileName);
      AfxMessageBox(szMsg);

      if (pNewPictureArray != NULL)
        delete pNewPictureArray;
      return FALSE;

    }

    //
    // Update any existing picture information
    //
    _Clear();
    m_pPictureArray = pNewPictureArray;
    m_dwPictureSize = dwNewPictureSize;

    //
    // we have a new one
    //
    return TRUE;
  }

  //
  // no change
  //
  return FALSE;
}

BOOL CThumbNailPhotoHolder::Clear()
{
  if (m_pPictureArray == NULL)
    return FALSE;

  //
  // clear the picture array info
  //
  _Clear();

  //
  // clear the path info
  //
  ::SetWindowText(m_hWndFileNameEdit, NULL);

  //
  // clear the picture
  //
  _SetPictureControl(NULL);

  return TRUE;
}

BOOL CThumbNailPhotoHolder::_DisplayPicture(LPCWSTR lpszPath)
{
  //
  // Load and display the picture
  //
  HBITMAP hPicture = (HBITMAP)::LoadImage(NULL, lpszPath, IMAGE_BITMAP, 0, 0 , LR_LOADFROMFILE);
  if (hPicture == NULL)
  {
    return FALSE;
  }
  _SetPictureControl(hPicture);
  return TRUE;
}

