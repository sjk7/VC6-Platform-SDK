//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       util.h
//
//--------------------------------------------------------------------------

#ifndef _UTIL_H
#define _UTIL_H

#define BYTE_OFFSET(base, offset) (((LPBYTE)base)+offset)

HRESULT SetStringAttribute(IADs* pIADs, LPCWSTR lpszAttr, LPCWSTR lpszVal, BOOL bPostCommit=FALSE);
HRESULT GetStringAttribute(IADs* pIADs, LPCWSTR lpszAttr, CString& szVal);



HRESULT SetByteArrayAsOctetString(IADs* pIADs, LPCWSTR lpszAttr, BYTE* pByteArray, DWORD dwSize);

BOOL LoadFileAsByteArray(PWSTR pszPath, LPBYTE* ppByteArray, DWORD* pdwSize);


///////////////////////////////////////////////////////////////
// CThumbNailPhotoHolder

class CThumbNailPhotoHolder
{
public:
  CThumbNailPhotoHolder()
  {
    m_hWndFileNameEdit = NULL;
    m_hWndPictureControl = NULL;

    m_pPictureArray = NULL;
    m_dwPictureSize = 0x0;
  }
  ~CThumbNailPhotoHolder()
  {
    _Clear();
  }

  // public interface
  void Initialize(HWND hWndFileNameEdit, HWND hWndPictureControl)
  {
    ASSERT(::IsWindow(hWndFileNameEdit));
    ASSERT(::IsWindow(hWndPictureControl));

    m_hWndFileNameEdit = hWndFileNameEdit;
    m_hWndPictureControl = hWndPictureControl;
  }

  HRESULT Read(IADs* pIADs);
  HRESULT Write(IADs* pIADs);

  HRESULT Read(IDirectoryObject* pDirObj);
  HRESULT Write(IDirectoryObject* pDirObj);

  BOOL Change(HWND hWndOwner);
  BOOL Clear();


private:

  // helper functions
  void _Clear()
  {
    if (m_pPictureArray != NULL)
    {
      ASSERT(m_dwPictureSize != NULL);
      delete m_pPictureArray;
      m_pPictureArray = NULL;
      m_dwPictureSize = 0x0;
    }
  }
  void _SetPictureControl(HBITMAP hBitmap)
  {
    ::SendMessage(m_hWndPictureControl, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)hBitmap);
    if (hBitmap != NULL)
      return;
    ::ShowWindow(m_hWndPictureControl, FALSE);
    ::ShowWindow(m_hWndPictureControl, TRUE);
  }

  BOOL _DisplayPicture(LPCWSTR lpszPath);

  void _WriteHelper(HRESULT hr);

  // member variables
  HWND m_hWndFileNameEdit;
  HWND m_hWndPictureControl;

  BYTE*                     m_pPictureArray;
  DWORD                     m_dwPictureSize;
};





#endif // _UTIL_H