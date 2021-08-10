//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2003 <company name>
//
//  Module Name:
//      StringUtils.h
//
//  Description:
//      Declaration of string manipulation routines.
//
//  Author:
//      <name> (<e-mail name>) Mmmm DD, 2003
//
//  Revision History:
//
//  Notes:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ClRes.h"

/////////////////////////////////////////////////////////////////////////////
// Custom string compare function declarations. Used to replace lstrcmp*
/////////////////////////////////////////////////////////////////////////////

//
// Full string compares.
//

int
IBSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    );

int
BSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    );

int
IStringCompareW(
      LPCWSTR pcwszString1In
    , LPCWSTR pcwszString2In
    );

int
StringCompareW(
      LPCWSTR pcwszString1In
    , LPCWSTR pcwszString2In
    );

int
IStringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    );

int
StringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    );

//
// Partial string compares.  They use whichever one's length is shortest
// if both are specified or the NBSTR routines are used.
//

int
NIBSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    );

int
NBSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    );

int
NIStringCompareW(
      LPCWSTR   pcwszString1In
    , LPCWSTR   pcwszString2In
    , size_t    cchIn
    );

int
NStringCompareW(
      LPCWSTR   pcwszString1In
    , LPCWSTR   pcwszString2In
    , size_t    cchIn
    );

int
NIStringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    );

int
NStringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    );


//////////////////////////////////////////////////////////////////////////////
// Load string routines
//////////////////////////////////////////////////////////////////////////////

HRESULT
HrLoadStringIntoBSTR(
      HINSTANCE hInstanceIn
    , LANGID    langidIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    );

inline
HRESULT
HrLoadStringIntoBSTR(
      UINT      idsIn
    , BSTR *    pbstrInout
    )
{
    return HrLoadStringIntoBSTR(
                          NULL
                        , MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL )
                        , idsIn
                        , pbstrInout
                        );
} //*** HrLoadStringIntoBSTR

inline
HRESULT
HrLoadStringIntoBSTR(
      HINSTANCE hInstanceIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    )

{
    return HrLoadStringIntoBSTR(
                          hInstanceIn
                        , MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL )
                        , idsIn
                        , pbstrInout
                        );

} //*** HrLoadStringIntoBSTR

//////////////////////////////////////////////////////////////////////////////
// Format string ID routines
//////////////////////////////////////////////////////////////////////////////

HRESULT
HrFormatStringIntoBSTR(
      HINSTANCE hInstanceIn
    , LANGID    langidIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    , ...
    );

HRESULT
HrFormatStringWithVAListIntoBSTR(
      HINSTANCE hInstanceIn
    , LANGID    langidIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    , va_list   valistIn
    );

inline
HRESULT
HrFormatStringIntoBSTR(
      HINSTANCE hInstanceIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    , ...
    )
{
    HRESULT hr;
    va_list valist;

    va_start( valist, pbstrInout );

    hr = HrFormatStringWithVAListIntoBSTR(
                  hInstanceIn
                , MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL )
                , idsIn
                , pbstrInout
                , valist
                );

    va_end( valist );

    return hr;

} //*** HrFormatStringIntoBSTR

inline
HRESULT
HrFormatStringIntoBSTR(
      UINT      idsIn
    , BSTR *    pbstrInout
    , ...
    )
{
    HRESULT hr;
    va_list valist;

    va_start( valist, pbstrInout );

    hr = HrFormatStringWithVAListIntoBSTR(
                  NULL
                , MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL )
                , idsIn
                , pbstrInout
                , valist
                );

    va_end( valist );

    return hr;

} //*** HrFormatStringIntoBSTR

inline
HRESULT
HrFormatStringWithVAListIntoBSTR(
      HINSTANCE hInstanceIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    , va_list   valistIn
    )
{
    return HrFormatStringWithVAListIntoBSTR(
                  hInstanceIn
                , MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL )
                , idsIn
                , pbstrInout
                , valistIn
                );

} //*** HrFormatStringWithVAListIntoBSTR

//////////////////////////////////////////////////////////////////////////////
// Format string routines
//////////////////////////////////////////////////////////////////////////////

HRESULT
HrFormatStringIntoBSTR(
      LPCWSTR   pcwszFmtIn
    , BSTR *    pbstrInout
    , ...
    );

HRESULT
HrFormatStringWithVAListIntoBSTR(
      LPCWSTR   pcwszFmtIn
    , BSTR *    pbstrInout
    , va_list   valistIn
    );
