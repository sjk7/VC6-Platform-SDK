//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  EmptyVolumeCache.cpp
//
//      Implementation of the CEmptyVolumeCache class.
//
//////////////////////////////////////////////////////////////////////

#include "Cleanup.h"
#include "EmptyVolumeCache.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEmptyVolumeCache::CEmptyVolumeCache()
{
    m_nRefCount = 0;
    nDllRefCount++;
}

CEmptyVolumeCache::~CEmptyVolumeCache()
{
    nDllRefCount--;
}

/////////////////////////////////////////////////////////////////////
//  IUnknown Methods
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CEmptyVolumeCache::QueryInterface(REFIID riid, LPVOID *ppvObject)
{
    HRESULT hr = E_NOINTERFACE;

    *ppvObject = NULL;
    if (IsEqualIID (riid, IID_IUnknown) ||
        IsEqualIID (riid, IID_IEmptyVolumeCache) ||
        IsEqualIID (riid, IID_IEmptyVolumeCache2))
    {
        *ppvObject = (LPVOID)(LPUNKNOWN) this;
    }

    if (*ppvObject != NULL)
    {
        ((LPUNKNOWN)*ppvObject)->AddRef ();
        hr = S_OK;
    }
    return hr;
}

STDMETHODIMP_(ULONG) CEmptyVolumeCache::AddRef()
{
    m_nRefCount++;
    return m_nRefCount;
}

STDMETHODIMP_(ULONG) CEmptyVolumeCache::Release()
{
    if (--m_nRefCount == 0)
    {
        delete this;
        return 0;
    }
    return m_nRefCount;
}


/////////////////////////////////////////////////////////////////////
//  IEmptyVolumeCache Methods
//
//  STDMETHODIMP Deactivate (DWORD dwFlags)
//  STDMETHODIMP GetSpaceUsed (DWORDLONG *pdwSpaceUsed, 
//                             IEmptyVolumeCacheCallback *picb)
//  STDMETHODIMP Initialize (HKEY hKey, LPCWSTR pcwszVolume, 
//                           LPWSTR *ppwszDisplayName, 
//                           LPWSTR *ppwszDescription, 
//                           DWORD *pdwFlags)
//  STDMETHODIMP Purge (DWORDLONG *pdwSpaceToFree, 
//                      IEmptyVolumeCacheCallback *picb)
//  STDMETHODIMP ShowProperties (HWND hWnd)
//
/////////////////////////////////////////////////////////////////////

STDMETHODIMP CEmptyVolumeCache::Deactivate (LPDWORD pdwFlags)
{
    //
    //  The disk cleanup manager is shutting down. Set any 
    //  appropriate flags and return
    //
    *pdwFlags = 0;
    return S_OK;
}


STDMETHODIMP CEmptyVolumeCache::GetSpaceUsed (DWORDLONG *pdwSpaceUsed, 
                                              IEmptyVolumeCacheCallBack *picb)
{
    //
    //  Determine the amount of disk space our cleanup handler can
    //  free. 
    //
    //  In this sample, we will make up a bogus size by determining
    //  the total size of the files in the Windows directory. 
    //
    //  bUpdateProgress is used to determine if GetSpaceUsed should
    //  call IEmptyVolumeCacheCallback::ScanProgress. If picb is 
    //  NULL, ScanProgress is not called.
    //
    BOOL bUpdateProgress = (picb != NULL);
    WIN32_FIND_DATA wfd;
    HANDLE hFind = NULL;
    HRESULT hResult = S_FALSE;
    TCHAR szWindowsDir[MAX_PATH];
    *pdwSpaceUsed = 0;

    GetWindowsDirectory (szWindowsDir, MAX_PATH);
    PathAppend (szWindowsDir, TEXT("*.*"));

    if ((hFind = FindFirstFile (szWindowsDir, &wfd)) == INVALID_HANDLE_VALUE)
        goto done;

    do
    {
        hResult = S_OK;
        if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))   
        {
            *pdwSpaceUsed += MAKEDWORDLONG(wfd.nFileSizeHigh, wfd.nFileSizeLow);
            if (bUpdateProgress)
                hResult = picb->ScanProgress (*pdwSpaceUsed, 0, NULL);
        }
    } while (FindNextFile (hFind, &wfd) && hResult == S_OK);

    if (hResult == S_OK)
        if (bUpdateProgress)
            picb->ScanProgress (*pdwSpaceUsed, EVCCBF_LASTNOTIFICATION, NULL);
    FindClose (hFind);

done:
    return hResult;
}


STDMETHODIMP CEmptyVolumeCache::Initialize (HKEY hKey, LPCWSTR pcwszVolume, 
                                            LPWSTR *ppwszDisplayName, 
                                            LPWSTR *ppwszDescription, 
                                            DWORD *pdwFlags)
{
    //
    //  The disk cleanup handler is being initialized. Allocate
    //  memory for the Display Name and Description strings using
    //  the task's memory allocator. These strings will be freed by
    //  the disk cleanup manager. Also, set any appropriate flags
    //  for the disk cleanup handler.
    //
    //  If the EVCF_SETTINGSMODE flag is set, Initialize/InitializeEx
    //  is responsible for deleting files.
    //
    HRESULT hResult = NOERROR;

    //
    //  We may need to delete the files here if EVCF_SETTINGSMODE is set.
    //
    if (*pdwFlags & EVCF_SETTINGSMODE)
    {
        DWORDLONG dwSpaceUsed = 0;

        GetSpaceUsed (&dwSpaceUsed, NULL);
        Purge (dwSpaceUsed, NULL);
    }

    //
    //  Load the Display Name text
    //
    *ppwszDisplayName = (LPWSTR) CoTaskMemAlloc (MAX_DISPLAY_LEN * sizeof (WCHAR));
    if (*ppwszDisplayName)
    {
#ifdef UNICODE
        LoadString (hDllInstance, IDS_DISPLAY, *ppwszDisplayName, MAX_DISPLAY_LEN);
#else
        CHAR szDisplayName[MAX_DISPLAY_LEN];
        LoadString (hDllInstance, IDS_DISPLAY, szDisplayName, MAX_DISPLAY_LEN);
        MultiByteToWideChar (CP_ACP, 0, szDisplayName, -1, *ppwszDisplayName, MAX_DISPLAY_LEN);
#endif
    }


    //
    //  Load the Description text
    //
    *ppwszDescription = (LPWSTR) CoTaskMemAlloc (MAX_DESCRIPTION_LEN * sizeof (WCHAR));
    if (*ppwszDescription)
    {
#ifdef UNICODE
        LoadString (hDllInstance, IDS_DESCRIPTION, *ppwszDescription, MAX_DESCRIPTION_LEN);
#else
        CHAR szDisplayName[MAX_DESCRIPTION_LEN];
        LoadString (hDllInstance, IDS_DESCRIPTION, szDisplayName, MAX_DESCRIPTION_LEN);
        MultiByteToWideChar (CP_ACP, 0, szDisplayName, -1, *ppwszDescription, MAX_DESCRIPTION_LEN);
#endif
    }

    *pdwFlags = EVCF_HASSETTINGS | EVCF_ENABLEBYDEFAULT;

    return hResult;
}


STDMETHODIMP CEmptyVolumeCache::Purge (DWORDLONG dwSpaceToFree, 
                                       IEmptyVolumeCacheCallBack *picb)
{
    //
    //  Delete unneeded files. 
    //
    //  In this sample, we do not delete any files. However, we 
    //  report that we actually did something by calling
    //  IEmptyVolumeCacheCallback::PurgeProgress.
    //
    //  bUpdateProgress is used to determine if GetSpaceUsed should
    //  call IEmptyVolumeCacheCallback::PurgeProgress. If picb is 
    //  NULL, PurgeProgress is not called.
    //
    BOOL bUpdateProgress = (picb != NULL);

    if (bUpdateProgress)
        picb->PurgeProgress (dwSpaceToFree, 0, EVCCBF_LASTNOTIFICATION, NULL);
    return S_OK;
}


STDMETHODIMP CEmptyVolumeCache::ShowProperties (HWND hWnd)
{
    //
    //  Display the Properties dialog for this disk cleanup handler.
    //  If the cleanup handler does not support a Properties dialog
    //  do not specify EVCF_HASSETTINGS in Initialize/InitializeEx.
    //
    //  In this sample we just create a message box to tell the user
    //  that there are no properties to set.
    MessageBox (hWnd,
                TEXT("There are no actual properties to display here."),
                TEXT("Properties"),
                MB_OK | MB_ICONINFORMATION);
    return S_OK;
}



/////////////////////////////////////////////////////////////////////
//  IEmptyVolumeCache2 Methods
//
//  STDMETHODIMP InitializeEx (HKEY hKey, LPCWSTR pcwszVolume, 
//                             LPCWSTR pcwszKeyName, 
//                             LPWSTR *ppwszDisplayName,
//                             LPWSTR *ppwszDescription,
//                             LPWSTR *ppwszBtnText,
//                             DWORD *pdwFlags)
//
/////////////////////////////////////////////////////////////////////

STDMETHODIMP CEmptyVolumeCache::InitializeEx (HKEY hKey, LPCWSTR pcwszVolume, 
                                              LPCWSTR pcwszKeyName, 
                                              LPWSTR *ppwszDisplayName,
                                              LPWSTR *ppwszDescription,
                                              LPWSTR *ppwszBtnText,
                                              DWORD *pdwFlags)
{
    HRESULT hResult = Initialize (hKey, pcwszVolume, ppwszDisplayName, ppwszDescription, pdwFlags);

    //
    //  Load the button text
    //
    *ppwszBtnText = (LPWSTR) CoTaskMemAlloc (MAX_DESCRIPTION_LEN * sizeof (WCHAR));
    if (*ppwszBtnText)
    {
#ifdef UNICODE
        LoadString (hDllInstance, IDS_BUTTONTEXT, *ppwszBtnText, MAX_BUTTONTEXT_LEN);
#else
        CHAR szDisplayName[MAX_BUTTONTEXT_LEN];
        LoadString (hDllInstance, IDS_BUTTONTEXT, szDisplayName, MAX_BUTTONTEXT_LEN);
        MultiByteToWideChar (CP_ACP, 0, szDisplayName, -1, *ppwszBtnText, MAX_BUTTONTEXT_LEN);
#endif
    }

    return hResult;
}
