//////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2003 <company name>
//
//  Module Name:
//      StringUtils.cpp
//
//  Description:
//      Implementation of string manipulation routines.
//
//  Author:
//      <name> (<e-mail name>) Mmmm DD, 2003
//
//  Revision History:
//
//  Notes:
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "StringUtils.h"


//////////////////////////////////////////////////////////////////////////////
// String comparison routines
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//++
//
//  WrapCompareString
//
//  Description:
//      Wraps the call to CompareString
//
//  Arguments:
//      fCaseSensitive      TRUE for a case sensitive compare
//                          FALSE for a case insensitive compare
//      pcwszString1In      The first string.
//      cch1In              The count of characters in the first string.
//                          If -1 then it's assumed to be null-terminated.
//      pcwszString2In      The second string.
//      cchIn               The count of characters in the second string.
//                          If -1 then it's assumed to be null-terminated.
//  Return Value:
//       0  Strings are equal.
//     > 0  String1 greater than String2.
//     < 0  String1 less than String2.
//
//--
/////////////////////////////////////////////////////////////////////////////
int
WrapCompareString(
      BOOL      fCaseSensitive
    , LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    )
{
    int nRet;

    nRet = CompareStringW(
              LOCALE_SYSTEM_DEFAULT
            , fCaseSensitive ? 0 : NORM_IGNORECASE
            , pcwszString1In
            , static_cast< DWORD >( cch1In )
            , pcwszString2In
            , static_cast< DWORD >( cch2In )
            );

    return nRet - CSTR_EQUAL; // CSTR_LT < CSTR_EQUAL < CSTR_GT

} // *** WrapCompareString

//
// Full string compares.
//

int
IBSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    )
{
    return WrapCompareString(
                  FALSE
                , static_cast< LPCWSTR >( bstrString1In )
                , SysStringLen( bstrString1In )
                , static_cast< LPCWSTR >( bstrString2In )
                , SysStringLen( bstrString2In )
                );
} //*** IBSTRCompareW

int
BSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    )
{
    return WrapCompareString(
                  TRUE
                , static_cast< LPCWSTR >( bstrString1In )
                , SysStringLen( bstrString1In )
                , static_cast< LPCWSTR >( bstrString2In )
                , SysStringLen( bstrString2In )
                );
} //*** BSTRCompareW

int
IStringCompareW(
      LPCWSTR pcwszString1In
    , LPCWSTR pcwszString2In
    )
{
    return WrapCompareString(
                  FALSE
                , pcwszString1In
                , static_cast< size_t >( -1 )
                , pcwszString2In
                , static_cast< size_t >( -1 )
            );
} //*** IStringCompareW

int
StringCompareW(
      LPCWSTR pcwszString1In
    , LPCWSTR pcwszString2In
    )
{
    return WrapCompareString(
                  TRUE
                , pcwszString1In
                , static_cast< size_t >( -1 )
                , pcwszString2In
                , static_cast< size_t >( -1 )
                );
} //*** StringCompareW

int
IStringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    )
{
    return WrapCompareString(
                  FALSE
                , pcwszString1In
                , cch1In
                , pcwszString2In
                , cch2In
                );
} //*** IStringCompareW

int
StringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    )
{
    return WrapCompareString(
                  TRUE
                , pcwszString1In
                , cch1In
                , pcwszString2In
                , cch2In
                );
} //*** StringCompareW

//
// Partial string compares.  They use whichever one's length is shortest
// if both are specified or the NBSTR routines are used.
//

int
NIBSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    )
{
    size_t cchMin;
    
    cchMin = min( SysStringLen( bstrString1In ), SysStringLen( bstrString2In ) );

    return WrapCompareString(
                  FALSE
                , static_cast< LPCWSTR >( bstrString1In )
                , cchMin
                , static_cast< LPCWSTR >( bstrString2In )
                , cchMin
                );
} //*** NIBSTRCompareW

int
NBSTRCompareW(
      BSTR  bstrString1In
    , BSTR  bstrString2In
    )
{
    size_t cchMin;
    
    cchMin = min( SysStringLen( bstrString1In ), SysStringLen( bstrString2In ) );

    return WrapCompareString(
                  TRUE
                , static_cast< LPCWSTR >( bstrString1In )
                , cchMin
                , static_cast< LPCWSTR >( bstrString2In )
                , cchMin
                );
} //*** NBSTRCompareW

int
NIStringCompareW(
      LPCWSTR   pcwszString1In
    , LPCWSTR   pcwszString2In
    , size_t    cchIn
    )
{
    return WrapCompareString(
                  FALSE
                , pcwszString1In
                , cchIn
                , pcwszString2In
                , cchIn
                );
} //*** NIStringCompareW

int
NStringCompareW(
      LPCWSTR   pcwszString1In
    , LPCWSTR   pcwszString2In
    , size_t    cchIn
    )
{
    return WrapCompareString(
                  TRUE
                , pcwszString1In
                , cchIn
                , pcwszString2In
                , cchIn
                );
} //*** NIStringCompareW

int
NIStringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    )
{
    return WrapCompareString(
                  FALSE
                , pcwszString1In
                , min( cch1In, cch2In )
                , pcwszString2In
                , min( cch1In, cch2In )
                );
} //*** NIStringCompareW

int
NStringCompareW(
      LPCWSTR   pcwszString1In
    , size_t    cch1In
    , LPCWSTR   pcwszString2In
    , size_t    cch2In
    )
{
    return WrapCompareString(
                  TRUE
                , pcwszString1In
                , min( cch1In, cch2In )
                , pcwszString2In
                , min( cch1In, cch2In )
                );
} //*** NStringCompareW



//////////////////////////////////////////////////////////////////////////////
// Load string routines
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrLoadStringIntoBSTR
//
//  Description:
//      Retrieves the string resource idsIn from the string table and makes it
//      into a BSTR. If the BSTR is not NULL coming it, it will assume that
//      you are trying reuse an existing BSTR.
//
//  Arguments:
//      hInstanceIn
//          Handle to an instance of the module whose executable file
//          contains the string resource.  If not specified, defaults to
//          _Module_mhInstResource.
//
//      langidIn
//          Language ID of string table resource.
//
//      idsIn
//          Specifies the integer identifier of the string to be loaded.
//
//      pbstrInout
//          Pointer to the BSTR to receive the string. On a failure, the BSTR
//          may be the same or NULL.
//
//  Return Values:
//      S_OK
//          The call succeeded.
//
//      E_OUTOFMEMORY
//          Out of memory.
//
//      E_POINTER
//          pbstrInout is NULL.
//
//      Other HRESULTs
//          The call failed.
//
//  Remarks:
//      This routine uses LoadResource so that it can get the actual length
//      of the string resource.  If we didn't do this, we would need to call
//      LoadString and allocate memory in a loop.  Very inefficient!
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrLoadStringIntoBSTR(
      HINSTANCE hInstanceIn
    , LANGID    langidIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    )

{
    HRESULT hr              = S_OK;
    HRSRC   hrsrc           = NULL;
    HGLOBAL hgbl            = NULL;
    int     cch             = 0;
    PBYTE   pbStringData;
    PBYTE   pbStringDataMax;
    PBYTE   pbStringTable;
    int     cbStringTable;
    int     nTable;
    int     nOffset;
    int     idxString;

    assert( idsIn != 0 );
    assert( pbstrInout != NULL );

    if ( pbstrInout == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    if ( hInstanceIn == NULL )
    {
        hInstanceIn = _Module.m_hInstResource;
    } // if:

    //
    //  The resource Id specified must be converted to an index into
    //  a Windows StringTable.
    //

    nTable = idsIn / 16;
    nOffset = idsIn - (nTable * 16);

    //
    //  Internal Table Id's start at 1 not 0.
    //

    nTable++;

    //
    // Find the part of the string table where the string resides.
    //

    //
    //  Find the table containing the string.
    // First try to load the language specified.  If we can't find it we
    // try the "neutral" language.
    //

    hrsrc = FindResourceEx( hInstanceIn, RT_STRING, MAKEINTRESOURCE( nTable ), langidIn );
    if ( ( hrsrc == NULL ) && ( GetLastError() == ERROR_RESOURCE_LANG_NOT_FOUND ) )
    {
        hrsrc = FindResourceEx(
                      hInstanceIn
                    , RT_STRING
                    , MAKEINTRESOURCE( nTable )
                    , MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL )
                    );
    } // if: FindResourceEx failed

    if ( hrsrc == NULL )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto Cleanup;
    } // if:

    //
    //  Load the table.
    //

    hgbl = LoadResource( hInstanceIn, hrsrc );
    if ( hgbl == NULL )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto Cleanup;
    } // if:

    //
    //  Lock the table so we access its data.
    //

    pbStringTable = reinterpret_cast< PBYTE >( LockResource( hgbl ) );
    if ( pbStringTable == NULL )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto Cleanup;
    } // if:

    cbStringTable = SizeofResource( hInstanceIn, hrsrc );
    assert( cbStringTable != 0 );

    //
    //  Set the data pointer to the beginning of the table.
    //

    pbStringData = pbStringTable;
    pbStringDataMax = pbStringTable + cbStringTable;

    //
    // Skip strings in the block of 16 which are before the desired string.
    //

    for ( idxString = 0 ; idxString <= nOffset ; idxString++ )
    {
        assert( pbStringData != NULL );
        assert( pbStringData < pbStringDataMax );

        //
        //  Get the number of characters excluding the '\0'.
        //

        cch = * ( (USHORT *) pbStringData );

        //
        //  Found the string.
        //

        if ( idxString == nOffset )
        {
            if ( cch == 0 )
            {
                hr = HRESULT_FROM_WIN32( ERROR_RESOURCE_NAME_NOT_FOUND );
                goto Cleanup;
            } // if:

            //
            //  Skip over the string length to get the string.
            //

            pbStringData += sizeof( WCHAR );

            break;
        } // if: found the string

        //
        //  Add one to account for the string length.
        //  A string length of 0 still takes 1 WCHAR for the length portion.
        //

        cch++;

        //
        //  Skip over this string to get to the next string.
        //

        pbStringData += ( cch * sizeof( WCHAR ) );

    } // for: each string in the block of 16 strings in the table

    //
    //  Note: nStringLen is the number of characters in the string not including the '\0'.
    //

    //
    // If previously allocated free it before re-allocating it.
    //

    if ( *pbstrInout != NULL )
    {
        SysFreeString( *pbstrInout );
        *pbstrInout = NULL;
    } // if: string was allocated previously

    //
    // Allocate a BSTR for the string.
    //

    *pbstrInout = SysAllocStringLen( (OLECHAR *) pbStringData, cch );
    if ( *pbstrInout == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

Cleanup:

    return hr;

} //*** HrLoadStringIntoBSTR


//////////////////////////////////////////////////////////////////////////////
// Format string ID routines
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrFormatStringIntoBSTR
//
//  Description:
//      Format a string (specified by idsIn, a string resource ID) and
//      variable arguments into a BSTR using the FormatMessage() Win32 API.
//      If the BSTR is not NULL on entry, the BSTR will be reused.
//
//      Calls HrFormatStringWithVAListIntoBSTR to perform the actual work.
//
//  Arguments:
//      hInstanceIn
//          Handle to an instance of the module whose executable file
//          contains the string resource.
//
//      langidIn
//          Language ID of string table resource.
//
//      idsIn
//          Specifies the integer identifier of the string to be loaded.
//
//      pbstrInout
//          Pointer to the BSTR to receive the string. On a failure, the BSTR
//          may be the same or NULL.
//
//      ...
//          Arguments for substitution points in the status text message.
//          The FormatMessage() API is used for formatting the string, so
//          substitution points must of the form %1!ws! and not %ws.
//
//  Return Values:
//      S_OK
//          The call succeeded.
//
//      Other HRESULTs
//          The call failed.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrFormatStringIntoBSTR(
      HINSTANCE hInstanceIn
    , LANGID    langidIn
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
                        , langidIn
                        , idsIn
                        , pbstrInout
                        , valist
                        );

    va_end( valist );

    return hr;

} //*** HrFormatStringIntoBSTR

//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrFormatStringWithVAListIntoBSTR
//
//  Description:
//      Format a string (specified by idsIn, a string resource ID) and
//      variable arguments into a BSTR using the FormatMessage() Win32 API.
//      If the BSTR is not NULL on entry, the BSTR will be reused.
//
//  Arguments:
//      hInstanceIn
//          Handle to an instance of the module whose executable file
//          contains the string resource.
//
//      langidIn
//          Language ID of string table resource.
//
//      idsIn
//          Specifies the integer identifier of the string to be loaded.
//
//      pbstrInout
//          Pointer to the BSTR to receive the string. On a failure, the BSTR
//          may be the same or NULL.
//
//      valistIn
//          Arguments for substitution points in the status text message.
//          The FormatMessage() API is used for formatting the string, so
//          substitution points must of the form %1!ws! and not %ws.
//
//  Return Values:
//      S_OK
//          The call succeeded.
//
//      E_OUTOFMEMORY
//          Out of memory.
//
//      E_POINTER
//          pbstrInout is NULL.
//
//      Other HRESULTs
//          The call failed.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrFormatStringWithVAListIntoBSTR(
      HINSTANCE hInstanceIn
    , LANGID    langidIn
    , UINT      idsIn
    , BSTR *    pbstrInout
    , va_list   valistIn
    )
{
    HRESULT hr = S_OK;
    BSTR    bstrStringResource = NULL;
    DWORD   cch;
    LPWSTR  pwsz = NULL;

    assert( pbstrInout != NULL );

    if ( pbstrInout == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    //
    // Load the string resource.
    //

    hr = HrLoadStringIntoBSTR( hInstanceIn, langidIn, idsIn, &bstrStringResource );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Format the message with the arguments.
    //

    cch = FormatMessage(
                      ( FORMAT_MESSAGE_ALLOCATE_BUFFER
                      | FORMAT_MESSAGE_FROM_STRING )
                    , bstrStringResource
                    , 0
                    , 0
                    , (LPWSTR) &pwsz
                    , 0
                    , &valistIn
                    );
    if ( cch == 0 )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto Cleanup;
    } // if:

    //
    // If previously allocated free it before re-allocating it.
    //

    if ( *pbstrInout != NULL )
    {
        SysFreeString( *pbstrInout );
        *pbstrInout = NULL;
    } // if:

    //
    // Allocate a BSTR for the string.
    //

    *pbstrInout = SysAllocStringLen( pwsz, cch );
    if ( *pbstrInout == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

Cleanup:

    SysFreeString( bstrStringResource );
    LocalFree( pwsz );

    return hr;

} //*** HrFormatStringWithVAListIntoBSTR


//////////////////////////////////////////////////////////////////////////////
// Format string routines
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrFormatStringIntoBSTR
//
//  Description:
//      Format a string (specified by pcwszFmtIn) and variable arguments into
//      a BSTR using the FormatMessage() Win32 API.  If the BSTR is not NULL
//      on entry, the BSTR will be reused.
//
//      Calls HrFormatStringWithVAListIntoBSTR to perform the actual work.
//
//  Arguments:
//      pcwszFmtIn
//          Specifies the format string.
//
//      pbstrInout
//          Pointer to the BSTR to receive the string. On a failure, the BSTR
//          may be the same or NULL.
//
//      ...
//          Arguments for substitution points in the status text message.
//          The FormatMessage() API is used for formatting the string, so
//          substitution points must of the form %1!ws! and not %ws.
//
//  Return Values:
//      S_OK
//          The call succeeded.
//
//      Other HRESULTs
//          The call failed.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrFormatStringIntoBSTR(
      LPCWSTR   pcwszFmtIn
    , BSTR *    pbstrInout
    , ...
    )
{
    HRESULT hr = S_OK;
    va_list valist;

    va_start( valist, pbstrInout );

    hr = HrFormatStringWithVAListIntoBSTR( pcwszFmtIn, pbstrInout, valist );

    va_end( valist );

    return hr;

} //*** HrFormatStringIntoBSTR

//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrFormatStringWithVAListIntoBSTR
//
//  Description:
//      Format a string (specified by pcwszFmtIn) and variable arguments into
//      a BSTR using the FormatMessage() Win32 API.  If the BSTR is not NULL
//      on entry, the BSTR will be reused.
//
//  Arguments:
//      pcwszFmtIn
//          Specifies the format string.
//
//      pbstrInout
//          Pointer to the BSTR to receive the string. On a failure, the BSTR
//          may be the same or NULL.
//
//      valistIn
//          Arguments for substitution points in the status text message.
//          The FormatMessage() API is used for formatting the string, so
//          substitution points must of the form %1!ws! and not %ws.
//
//  Return Values:
//      S_OK
//          The call succeeded.
//
//      E_OUTOFMEMORY
//          Out of memory.
//
//      E_POINTER
//          pcwszFmtIn or pbstrInout is NULL.
//
//      Other HRESULTs
//          The call failed.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrFormatStringWithVAListIntoBSTR(
      LPCWSTR   pcwszFmtIn
    , BSTR *    pbstrInout
    , va_list   valistIn
    )
{
    HRESULT hr = S_OK;
    DWORD   cch;
    LPWSTR  pwsz = NULL;

    if (    ( pbstrInout == NULL )
        ||  ( pcwszFmtIn == NULL )
       )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    //
    // Format the message with the arguments.
    //

    cch = FormatMessage(
                      ( FORMAT_MESSAGE_ALLOCATE_BUFFER
                      | FORMAT_MESSAGE_FROM_STRING )
                    , pcwszFmtIn
                    , 0
                    , 0
                    , (LPWSTR) &pwsz
                    , 0
                    , &valistIn
                    );
    if ( cch == 0 )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto Cleanup;
    } // if:

    //
    // If previously allocated free it before re-allocating it.
    //

    if ( *pbstrInout != NULL )
    {
        SysFreeString( *pbstrInout );
        *pbstrInout = NULL;
    } // if:

    //
    // Allocate a BSTR for the string.
    //

    *pbstrInout = SysAllocStringLen( pwsz, cch );
    if ( *pbstrInout == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

Cleanup:

    LocalFree( pwsz );

    return hr;

} //*** HrFormatStringWithVAListIntoBSTR
