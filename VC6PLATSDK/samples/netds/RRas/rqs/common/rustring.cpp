//+--------------------------------------------------------------------------
//
//  File:       RuString.cpp
//
//  Synopsis:   String helper functions
//
//  Copyright   (c) Microsoft Corporation.  All rights reserved.
//
//---------------------------------------------------------------------------
#ifndef _UNICODE  
#define _UNICODE
#endif

#include "rasutil.h"
#include "RuString.h"

//+----------------------------------------------------------------------------
//
//  Synopsis:   worker fn for WideChar -> Multibyte conversions
//
//-----------------------------------------------------------------------------
static HRESULT
RuStringWideToNarrowInternal(
    IN      PWSTR   psz,
    IN OUT  PSTR *  ppszansi,
    IN      UINT    cchansi,
    IN      UINT    CodePage
)
{
    HRESULT hr = S_OK;

    if (cchansi == 0)
    {
        // we allocate memory
        cchansi = WideCharToMultiByte(CodePage, 0, psz, -1, NULL, 0, NULL, NULL);
        *ppszansi = (PSTR) RuAlloc(cchansi * sizeof(CHAR), FALSE);
    }

    if (!WideCharToMultiByte(CodePage, 0, psz, -1, *ppszansi, cchansi, NULL, NULL))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
//  Synopsis:   Converts Unicode to Ansi with alloc
//
//-----------------------------------------------------------------------------
PSTR
RuStringDupWtoA(
    IN      PWSTR   psz
)
{
    PSTR    pszansi = NULL;
    HRESULT hr = RuStringWideToNarrowInternal(psz, &pszansi, 0, CP_ACP);
    return ((hr == S_OK) ? pszansi : NULL);
}


//+----------------------------------------------------------------------------
//
//  Synopsis:   worker fn for Multibyte -> WideChar conversions
//
//-----------------------------------------------------------------------------
static HRESULT
RuStringNarrowToWideInternal(
    IN      PSTR    pszansi,
    IN      UINT    CodePage,
    IN OUT  PWSTR * ppsz,
    IN      UINT    cch
)
{
    HRESULT hr = S_OK;

    if (cch == 0)
    {
        // we allocate memory
        cch = MultiByteToWideChar(CodePage, 0, pszansi, -1, NULL, 0);
        *ppsz = (PWSTR) RuAlloc(cch * sizeof(WCHAR), FALSE);
    }

    if (!MultiByteToWideChar(CodePage, 0, pszansi, -1, *ppsz, cch))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

//+----------------------------------------------------------------------------
//
//  Synopsis:   Converts Ansi to Unicode with alloc
//
//-----------------------------------------------------------------------------
PWSTR
RuStringDupAtoW(
    IN      PSTR    pszansi
)
{
    PWSTR psz = NULL;
    HRESULT hr = RuStringNarrowToWideInternal(pszansi, CP_ACP, &psz, 0);
    return ((hr == S_OK) ? psz : NULL);
}


