//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 1999 - 2000  Microsoft Corporation.  All rights reserved.
//
//  EmptyVolumeCache.h
//
//      Interface for the CEmptyVolumeCache class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _EMPTYVOLUMECAHCE_H_INCLUDED
#define _EMPTYVOLUMECAHCE_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEmptyVolumeCache : public IEmptyVolumeCache2
{
public:
    // Constructor/Destructor
    CEmptyVolumeCache ();
    ~CEmptyVolumeCache ();

    // IUnknown methods
    STDMETHODIMP QueryInterface (REFIID riid, LPVOID *ppvObject);
    STDMETHODIMP_(ULONG) AddRef (VOID);
    STDMETHODIMP_(ULONG) Release (VOID);

    // IEmptyVolumeCache methods
    STDMETHODIMP Deactivate (LPDWORD pdwFlags);
    STDMETHODIMP GetSpaceUsed (DWORDLONG *pdwSpaceUsed, IEmptyVolumeCacheCallBack *picb);
    STDMETHODIMP Initialize (HKEY hKey, LPCWSTR pcwszVolume, LPWSTR *ppwszDisplayName, 
                             LPWSTR *ppwszDescription, DWORD *pdwFlags);
    STDMETHODIMP Purge (DWORDLONG dwSpaceToFree, IEmptyVolumeCacheCallBack *picb);
    STDMETHODIMP ShowProperties (HWND hWnd);

    // IEmptyVolumeCache2 methods
    STDMETHODIMP InitializeEx (HKEY hKey, LPCWSTR pcwszVolume, LPCWSTR pcwszKeyName,
                               LPWSTR *ppwszDisplayName, LPWSTR *ppwszDescription, 
                               LPWSTR *ppwszBtnText, DWORD *pdwFlags);

private:
    ULONG m_nRefCount;
};

#endif // _EMPTYVOLUMECAHCE_H_INCLUDED