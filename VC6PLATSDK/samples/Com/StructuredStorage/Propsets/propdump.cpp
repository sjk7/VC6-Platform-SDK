
//+============================================================================
//
//  Sample:     PropDump.cpp
//
//  To Build:   cl /GX enumall.cpp
//
//  This sample is a program which dumps all the properties in all property
//  sets of a storage file.
//
//+============================================================================


#define UNICODE
#define _UNICODE

#include <stdio.h>
#include <windows.h>

#pragma comment( lib, "ole32.lib" )

//+----------------------------------------------------------------------------
//
//  ConvertVarTypeToString
//  
//  Generate a string for a given PROPVARIANT variable type (VT). 
//  For the given vt, write the string to pwszType, which is a buffer of
//  size cchType characters.
//
//+----------------------------------------------------------------------------

void
ConvertVarTypeToString( VARTYPE vt, WCHAR *pwszType, ULONG cchType )
{
    const WCHAR *pwszModifier;

    // Make sure the output string will be terminated
    // (wcsncpy doesn't guarantee termination)

    pwszType[ cchType-1 ] = L'\0';
    --cchType;

    // Stringize the basic type

    switch( vt & VT_TYPEMASK )
    {
    case VT_EMPTY:
        wcsncpy( pwszType, L"VT_EMPTY", cchType );
        break;
    case VT_NULL:
        wcsncpy( pwszType, L"VT_NULL", cchType );
        break;
    case VT_I2:
        wcsncpy( pwszType, L"VT_I2", cchType );
        break;
    case VT_I4:
        wcsncpy( pwszType, L"VT_I4", cchType );
        break;
    case VT_I8:
        wcsncpy( pwszType, L"VT_I8", cchType );
        break;
    case VT_UI2:
        wcsncpy( pwszType, L"VT_UI2", cchType );
        break;
    case VT_UI4:
        wcsncpy( pwszType, L"VT_UI4", cchType );
        break;
    case VT_UI8:
        wcsncpy( pwszType, L"VT_UI8", cchType );
        break;
    case VT_R4:
        wcsncpy( pwszType, L"VT_R4", cchType );
        break;
    case VT_R8:
        wcsncpy( pwszType, L"VT_R8", cchType );
        break;
    case VT_CY:
        wcsncpy( pwszType, L"VT_CY", cchType );
        break;
    case VT_DATE:
        wcsncpy( pwszType, L"VT_DATE", cchType );
        break;
    case VT_BSTR:
        wcsncpy( pwszType, L"VT_BSTR", cchType );
        break;
    case VT_ERROR:
        wcsncpy( pwszType, L"VT_ERROR", cchType );
        break;
    case VT_BOOL:
        wcsncpy( pwszType, L"VT_BOOL", cchType );
        break;
    case VT_VARIANT:
        wcsncpy( pwszType, L"VT_VARIANT", cchType );
        break;
    case VT_DECIMAL:
        wcsncpy( pwszType, L"VT_DECIMAL", cchType );
        break;
    case VT_I1:
        wcsncpy( pwszType, L"VT_I1", cchType );
        break;
    case VT_UI1:
        wcsncpy( pwszType, L"VT_UI1", cchType );
        break;
    case VT_INT:
        wcsncpy( pwszType, L"VT_INT", cchType );
        break;
    case VT_UINT:
        wcsncpy( pwszType, L"VT_UINT", cchType );
        break;
    case VT_VOID:
        wcsncpy( pwszType, L"VT_VOID", cchType );
        break;
    case VT_SAFEARRAY:
        wcsncpy( pwszType, L"VT_SAFEARRAY", cchType );
        break;
    case VT_USERDEFINED:
        wcsncpy( pwszType, L"VT_USERDEFINED", cchType );
        break;
    case VT_LPSTR:
        wcsncpy( pwszType, L"VT_LPSTR", cchType );
        break;
    case VT_LPWSTR:
        wcsncpy( pwszType, L"VT_LPWSTR", cchType );
        break;
    case VT_RECORD:
        wcsncpy( pwszType, L"VT_RECORD", cchType );
        break;
    case VT_FILETIME:
        wcsncpy( pwszType, L"VT_FILETIME", cchType );
        break;
    case VT_BLOB:
        wcsncpy( pwszType, L"VT_BLOB", cchType );
        break;
    case VT_STREAM:
        wcsncpy( pwszType, L"VT_STREAM", cchType );
        break;
    case VT_STORAGE:
        wcsncpy( pwszType, L"VT_STORAGE", cchType );
        break;
    case VT_STREAMED_OBJECT:
        wcsncpy( pwszType, L"VT_STREAMED_OBJECT", cchType );
        break;
    case VT_STORED_OBJECT:
        wcsncpy( pwszType, L"VT_BLOB_OBJECT", cchType );
        break;
    case VT_CF:
        wcsncpy( pwszType, L"VT_CF", cchType );
        break;
    case VT_CLSID:
        wcsncpy( pwszType, L"VT_CLSID", cchType );
        break;
    default:
        _snwprintf( pwszType, cchType, L"Unknown (%d)", vt & VT_TYPEMASK );
        break;
    }

    // Adjust cchType for the characters we just added

    cchType -= wcslen(pwszType);

    // Add the type modifiers if present

    if( vt & VT_VECTOR )
    {
        pwszModifier = L" | VT_VECTOR";        
        wcsncat( pwszType, pwszModifier, cchType );
        cchType -= wcslen( pwszModifier );
    }

    if( vt & VT_ARRAY )
    {
        pwszModifier = L" | VT_ARRAY";        
        wcsncat( pwszType, pwszModifier, cchType );
        cchType -= wcslen( pwszModifier );
    }

    if( vt & VT_RESERVED )
    {
        pwszModifier = L" | VT_RESERVED";        
        wcsncat( pwszType, pwszModifier, cchType );
        cchType -= wcslen( pwszModifier );
    }

}


//+----------------------------------------------------------------------------
//
//  ConvertValueToString
//  
//  Generate a string for the value in a given PROPVARIANT structure.
//  The most common types are supported (that is, those that can be displayed
//  with printf).  For other types, only an ellipses "..." is displayed.
//
//  The property to string-ize is in propvar, the resulting string goes
//  into pwszValue, which is a buffer with room for cchValue characters
//  (including the string terminator).
//
//+----------------------------------------------------------------------------

void
ConvertValueToString( const PROPVARIANT &propvar,
                      WCHAR *pwszValue,
                      ULONG cchValue )
{
    // Make sure the output string will be terminated

    pwszValue[ cchValue - 1 ] = L'\0';
    --cchValue;

    // Based on the type, put the value into pwszValue as a string.

    switch( propvar.vt )
    {
    case VT_EMPTY:
        wcsncpy( pwszValue, L"", cchValue );
        break;
    case VT_NULL:
        wcsncpy( pwszValue, L"", cchValue );
        break;
    case VT_I2:
        _snwprintf( pwszValue, cchValue, L"%i", propvar.iVal );
        break;
    case VT_I4:
    case VT_INT:
        _snwprintf( pwszValue, cchValue, L"%li", propvar.lVal );
        break;
    case VT_I8:
        _snwprintf( pwszValue, cchValue, L"%I64i", propvar.hVal );
        break;
    case VT_UI2:
        _snwprintf ( pwszValue, cchValue, L"%u", propvar.uiVal );
        break;
    case VT_UI4:
    case VT_UINT:
        _snwprintf ( pwszValue, cchValue, L"%lu", propvar.ulVal );
        break;
    case VT_UI8:
        _snwprintf ( pwszValue, cchValue, L"%I64u", propvar.uhVal );
        break;
    case VT_R4:
        _snwprintf ( pwszValue, cchValue, L"%f", propvar.fltVal );
        break;
    case VT_R8:
        _snwprintf ( pwszValue, cchValue, L"%lf", propvar.dblVal );
        break;
    case VT_BSTR:
        _snwprintf ( pwszValue, cchValue, L"\"%s\"", propvar.bstrVal );
        break;
    case VT_ERROR:
        _snwprintf ( pwszValue, cchValue, L"0x%08X", propvar.scode );
        break;
    case VT_BOOL:
        _snwprintf ( pwszValue, cchValue, L"%s",
                     VARIANT_TRUE == propvar.boolVal ? L"True" : L"False" );
        break;
    case VT_I1:
        _snwprintf ( pwszValue, cchValue, L"%i", propvar.cVal );
        break;
    case VT_UI1:
        _snwprintf ( pwszValue, cchValue, L"%u", propvar.bVal );
        break;
    case VT_VOID:
        wcsncpy( pwszValue, L"", cchValue );
        break;
    case VT_LPSTR:
        if( 0 >_snwprintf ( pwszValue, cchValue, L"\"%hs\"", propvar.pszVal ))
            // String is too big for pwszValue
            wcsncpy( pwszValue, L"...", cchValue );
        break;
    case VT_LPWSTR:
        if( 0 > _snwprintf ( pwszValue, cchValue, L"\"%s\"", propvar.pwszVal ))
            // String is too big for pwszValue
            wcsncpy( pwszValue, L"...", cchValue );
        break;
    case VT_FILETIME:
        _snwprintf ( pwszValue, cchValue, L"%08x:%08x",
                     propvar.filetime.dwHighDateTime,
                     propvar.filetime.dwLowDateTime );
        break;
    case VT_CLSID:
        pwszValue[0] = L'\0';
        StringFromGUID2( *propvar.puuid, pwszValue, cchValue );
        break;
    default:
        wcsncpy( pwszValue, L"...", cchValue );
        break;
    }

}


//+----------------------------------------------------------------------------
//
//  DisplayProperty
//
//  Dump the ID, name, type, and value of a property.
//
//+----------------------------------------------------------------------------

void
DisplayProperty( const PROPVARIANT &propvar, const STATPROPSTG &statpropstg )
{
    WCHAR wsz[ MAX_PATH + 1 ];

    ConvertVarTypeToString( statpropstg.vt, wsz, sizeof(wsz)/sizeof(wsz[0]) );

    wprintf( L"   ----------------------------------------------------\n"
             L"   PropID = %-5d VarType = %-23s",
             statpropstg.propid, wsz );

    if( NULL != statpropstg.lpwstrName )
        wprintf( L" Name = %s", statpropstg.lpwstrName );

    ConvertValueToString( propvar, wsz, sizeof(wsz)/sizeof(wsz[0]) );

    wprintf( L"\n   Value = %s\n", wsz ); 

}


//+----------------------------------------------------------------------------
//
//  DisplayPropertySet
//
//  Dump all the properties into a given property set.
//
//+----------------------------------------------------------------------------

void
DisplayPropertySet( FMTID fmtid,
                    const WCHAR *pwszStorageName,
                    IPropertyStorage *pPropStg )
{
    IEnumSTATPROPSTG *penum = NULL;
    HRESULT hr = S_OK;
    STATPROPSTG statpropstg;
    PROPVARIANT propvar;
    PROPSPEC propspec;
    PROPID propid;
    WCHAR *pwszFriendlyName = NULL;

    // This string will hold a string-ized FMTID.  It needs
    // to be 38 characters, plus the terminator
    // character.  But just to be safe we'll make
    // it a little bigger.
    WCHAR wszFMTID[ 64 ] = { L"" };

    PropVariantInit( &propvar );
    memset( &statpropstg, 0, sizeof(statpropstg) );

    try
    {
        // Display the ID of the property set

        StringFromGUID2( fmtid,
                         wszFMTID,
                         sizeof(wszFMTID)/sizeof(wszFMTID[0]) );
        wprintf( L"\n Property Set %s\n", wszFMTID );

        // If this is one of common property sets, show which one.

        if( FMTID_SummaryInformation == fmtid )
            wprintf( L"   (SummaryInformation property set)\n" );
        else if( FMTID_DocSummaryInformation == fmtid )
            wprintf( L"   (DocumentSummaryInformation property set)\n" );
        else if( FMTID_UserDefinedProperties == fmtid )
            wprintf( L"   (UserDefined property set)\n" );

        // Also display the name of the storage that contains
        // this property set

        wprintf( L"   in \"%s\":\n", pwszStorageName );

        // If this property set has a friendly name, display it now.
        // (Property names are stored in the special dictionary
        // property - the name of the property set is indicated by naming
        // the dictionary property itself.)

        propid = PID_DICTIONARY;
        pwszFriendlyName = NULL;

        hr = pPropStg->ReadPropertyNames( 1, &propid, &pwszFriendlyName );
        if( S_OK == hr )
        {
            wprintf( L"   (Friendly name is \"%s\")\n\n", pwszFriendlyName );
            CoTaskMemFree( pwszFriendlyName );
            pwszFriendlyName = NULL;
        }
        else
            wprintf( L"\n" );

        // Get a property enumerator

        hr = pPropStg->Enum( &penum );
        if( FAILED(hr) ) throw L"Failed IPropertyStorage::Enum";

        // Get the first property in the enumeration

        hr = penum->Next( 1, &statpropstg, NULL );

        // Loop through and display each property.  The ‘Next'
        // call above (and at the bottom of the while loop)
        // will return S_OK if it returns another property,
        // S_FALSE if there are no more properties,
        // and anything else is an error.

        while( S_OK == hr )
        {

            // Read the property out of the property set

            PropVariantInit( &propvar );
            propspec.ulKind = PRSPEC_PROPID;
            propspec.propid = statpropstg.propid;

            hr = pPropStg->ReadMultiple( 1, &propspec, &propvar );
            if( FAILED(hr) ) throw L"Failed IPropertyStorage::ReadMultiple";

            // Display the property value, type, etc.

            DisplayProperty( propvar, statpropstg );

            // Free buffers that were allocated during the read and
            // by the enumerator.

            PropVariantClear( &propvar );
            CoTaskMemFree( statpropstg.lpwstrName );
            statpropstg.lpwstrName = NULL;

            // Move to the next property in the enumeration

            hr = penum->Next( 1, &statpropstg, NULL );
        }
        if( FAILED(hr) ) throw L"Failed IEnumSTATPROPSTG::Next";
    }
    catch( LPCWSTR pwszErrorMessage )
    {
        wprintf( L"Error in DumpPropertySet: %s (hr = %08x)\n",
                 pwszErrorMessage, hr );
    }

    if( NULL != penum )
        penum->Release();

    if( NULL != statpropstg.lpwstrName )
        CoTaskMemFree( statpropstg.lpwstrName );

    PropVariantClear( &propvar );
}


//+----------------------------------------------------------------------------
//
//  DisplayPropertySetsInStorage
//
//  Dump the property sets in the top level of a given storage.
//
//+----------------------------------------------------------------------------

void
DisplayPropertySetsInStorage( const WCHAR *pwszStorageName, 
                              IPropertySetStorage *pPropSetStg )
{
    IEnumSTATPROPSETSTG *penum = NULL;
    HRESULT hr = S_OK;
    IPropertyStorage *pPropStg = NULL;
    STATPROPSETSTG statpropsetstg;

    try
    {
        // Get a property-set enumerator (which only enumerates the property
        // sets at this level of the storage, not its children).

        hr = pPropSetStg->Enum( &penum );
        if( FAILED(hr) ) throw L"failed IPropertySetStorage::Enum";

        // Get the first property set in the enumeration.
        // (The field we're interested in is
        // statpropsetstg.fmtid, so that we can open the
        // property set.)

        memset( &statpropsetstg, 0, sizeof(statpropsetstg) );
        hr = penum->Next( 1, &statpropsetstg, NULL );

        // Loop through all the property sets

        while( S_OK == hr )
        {
            // Open the property set

            hr = pPropSetStg->Open( statpropsetstg.fmtid,
                                    STGM_READ | STGM_SHARE_EXCLUSIVE,
                                    &pPropStg );
            if( FAILED(hr) ) throw L"failed IPropertySetStorage::Open";

            // Display the properties in the property set

            DisplayPropertySet( statpropsetstg.fmtid,
                                pwszStorageName,
                                pPropStg );

            pPropStg->Release();
            pPropStg = NULL;

            // Get the FMTID of the next property set in the enumeration.

            hr = penum->Next( 1, &statpropsetstg, NULL );

        }
        if( FAILED(hr) ) throw L"Failed IEnumSTATPROPSETSTG::Next";

        // Special-case handling for the UserDefined property set:
        // This property set actually lives inside the well-known
        // DocumentSummaryInformation property set.  It is the only
        // property set which is allowed to live inside another
        // (and exists for legacy compatibility).  It does not get
        // included in a normal enumeration, so we have to check for
        // it explicitely.  We'll handle it by looking for it when
        // we reach the end of the enumerator.

        hr = pPropSetStg->Open( FMTID_UserDefinedProperties,
                                STGM_READ | STGM_SHARE_EXCLUSIVE,
                                &pPropStg );
        if( SUCCEEDED(hr) )
        {
            DisplayPropertySet( FMTID_UserDefinedProperties,
                                pwszStorageName,
                                pPropStg );
            pPropStg = NULL;
        }

    }
    catch( LPCWSTR pwszErrorMessage )
    {
        wprintf( L"Error in DumpPropertySetsInStorage: %s (hr = %08x)\n",
                 pwszErrorMessage, hr );
    }

    if( NULL != pPropStg )
        pPropStg->Release();
    if( NULL != penum )
        penum->Release();
}


//+----------------------------------------------------------------------------
//
//  DisplayStorageTree
//
//  Dump all the property sets in the given storage and recursively in
//  all its children.
//
//+----------------------------------------------------------------------------

void
DisplayStorageTree( const WCHAR *pwszStorageName, IStorage *pStg )
{
    IPropertySetStorage *pPropSetStg = NULL;
    IStorage *pStgChild = NULL;
    WCHAR *pwszChildStorageName = NULL;
    IEnumSTATSTG *penum = NULL;
    HRESULT hr = S_OK;
    STATSTG statstg;

    memset( &statstg, 0, sizeof(statstg) );

    try
    {
        // Dump the property sets at this storage level

        hr = pStg->QueryInterface( IID_IPropertySetStorage,
                                   reinterpret_cast<void**>(&pPropSetStg) );
        if( FAILED(hr) )
            throw L"Failed IStorage::QueryInterface(IID_IPropertySetStorage)";

        DisplayPropertySetsInStorage( pwszStorageName, pPropSetStg );

        // Get an enumerator for this storage.

        hr = pStg->EnumElements( NULL, NULL, NULL, &penum );
        if( FAILED(hr) ) throw L"failed IStorage::Enum";

        // Get the name of the first element (stream/storage)
        // in the enumeration.  As usual, ‘Next' will return
        // S_OK if it returns an element of the enumerator,
        // S_FALSE if there are no more elements, and an
        // error otherwise.

        hr = penum->Next( 1, &statstg, 0 );

        // Loop through all the direct children of this storage.

        while( S_OK == hr )
        {
            // Check if this is a storage that isn't a property set
            // (since we already displayed the property sets above).
            // You can tell if a stream/storage is a property set
            // because the first character of it's name is the
            // ‘\005' reserved character.

            if( STGTY_STORAGE == statstg.type
                &&
                L'\005' != statstg.pwcsName[0] )
            {
                // Yes, this is a normal storage, not a propset.
                // Open the storage.

                ULONG cchChildStorageName;

                hr = pStg->OpenStorage( statstg.pwcsName,
                                        NULL,
                                        STGM_READ | STGM_SHARE_EXCLUSIVE,
                                        NULL, 0,
                                        &pStgChild );
                if( FAILED(hr) ) throw L"failed IStorage::OpenStorage";

                // Compose a name of the form "Storage\ChildStorage\..."
                // for display purposes.  First, allocate it.

                cchChildStorageName = wcslen(pwszStorageName)
                                        + wcslen(statstg.pwcsName)
                                        + 2  // For the two "\" chars
                                        + 1; // For the string terminator

                pwszChildStorageName = new WCHAR[ cchChildStorageName ];
                if( NULL == pwszChildStorageName )
                {
                    hr = HRESULT_FROM_WIN32(ERROR_NOT_ENOUGH_MEMORY);
                    throw L"couldn't allocate memory";
                }

                // Terminate the name

                pwszChildStorageName[ cchChildStorageName-1 ] = L'\0';
                --cchChildStorageName;

                // Build the name.

                wcsncpy( pwszChildStorageName, pwszStorageName,
                         cchChildStorageName );
                cchChildStorageName -= wcslen(pwszStorageName);

                wcsncat( pwszChildStorageName, L"\\",
                         cchChildStorageName );
                cchChildStorageName -= 2;

                wcsncat( pwszChildStorageName, statstg.pwcsName,
                         cchChildStorageName );

                // Dump all the property sets under this child storage.

                DisplayStorageTree( pwszChildStorageName, pStgChild );

                pStgChild->Release();
                pStgChild = NULL;

                delete pwszChildStorageName;
                pwszChildStorageName = NULL;
            }

            // Move on to the next element in the enumeration of this storage.

            CoTaskMemFree( statstg.pwcsName );
            statstg.pwcsName = NULL;

            hr = penum->Next( 1, &statstg, 0 );
        }
        if( FAILED(hr) ) throw L"failed IEnumSTATSTG::Next";
    }
    catch( LPCWSTR pwszErrorMessage )
    {
        wprintf( L"Error in DumpStorageTree: %s (hr = %08x)\n",
                 pwszErrorMessage, hr );
    }

    // Clean up before returning.

    if( NULL != statstg.pwcsName )
        CoTaskMemFree( statstg.pwcsName );
    if( NULL != pStgChild )
        pStgChild->Release();
    if( NULL != pStg )
        pStg->Release();
    if( NULL != penum )
        penum->Release();
    if( NULL != pwszChildStorageName )
        delete pwszChildStorageName;
    
}


//+----------------------------------------------------------------------------
//
//  wmain
//
//  Dump all the property sets in a file which is a storage.
//
//+----------------------------------------------------------------------------

extern "C" void wmain( int cArgs, WCHAR *rgwszArgs[] )
{
    HRESULT hr = S_OK;
    IStorage *pStg = NULL;

    // Display usage information if necessary.

    if( 1 == cArgs
        ||
        0 == wcscmp( L"-?", rgwszArgs[1] )
        ||
        0 == wcscmp( L"/?", rgwszArgs[1] ))
    {
        printf( "\n"
                "Purpose:  Enumerate all properties in all\n"
                "          property sets for a storage file\n"
                "Usage:    PropDump <filename>\n"
                "E.g.:     PropDump word.doc\n"
                "\n" );
        exit(0);
    }

    // Open the root storage.

    hr = StgOpenStorageEx( rgwszArgs[1],
                           STGM_READ | STGM_SHARE_DENY_WRITE,
                           STGFMT_ANY,
                           0,
                           NULL,
                           NULL,
                           IID_IStorage,
                           reinterpret_cast<void**>(&pStg) );

    // Dump all the properties in all the property sets within this
    // storage.

    if( FAILED(hr) )
    {
        wprintf( L"Error:  couldn't open storage \"%s\" (hr = %08x)\n",
                 rgwszArgs[1], hr );
    }
    else
    {
        printf( "\nDisplaying all property sets ...\n" );
        DisplayStorageTree( rgwszArgs[1], pStg );
        pStg->Release();
    }


}
