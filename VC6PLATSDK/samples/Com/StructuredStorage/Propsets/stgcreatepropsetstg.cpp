
//+============================================================================
//
//  StgCreatePropSetStg.cpp
//
//  This sample shows how the StgCreatePropSetStg API can be used
//  to create an IPropertySetStorage on top of any given IStorage.
//  This API is new to Windows 2000 Professional.
//
//  To Build:   cl /GX StgCreatePropSetStg.cpp
//
//+============================================================================


#define UNICODE
#define _UNICODE
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <ole2.h>

#pragma comment( lib, "ole32.lib" )

IPropertyStorage*
CreatePropertySetInStorage( IStorage *pStg, const FMTID &fmtid )
{
    HRESULT hr = S_OK;
    IPropertySetStorage *pPropSetStg = NULL;
    IPropertyStorage *pPropStg = NULL;

    try
    {
        hr = StgCreatePropSetStg( pStg, 0 /*reserved*/, &pPropSetStg );
        if( FAILED(hr) ) throw L"Failed StgCreatePropSetStg (%08x)";

        hr = pPropSetStg->Create( fmtid, NULL,
		        PROPSETFLAG_DEFAULT,
		        STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
		        &pPropStg );
        if( FAILED(hr) ) throw L"Failed IPropertySetStorage::Create (%08x)";

        // Success.  The caller must now call Release on pPropStg
    }
    catch( const WCHAR *pwszError )
    {
        wprintf( L"Error: %s (%08x)\n", pwszError, hr );
    }

    if( NULL != pPropSetStg )
        pPropSetStg->Release();

    return( pPropStg );
}


extern "C" void wmain()
{
    HRESULT hr = S_OK;
    IStorage *pStg = NULL;
    IPropertyStorage *pPropStg = NULL;

    try
    {
        // Create an object with an IStorage interface.  It is not necessary
        // that it be a system-provided storage, such as what is obtained by
        // this call.  Any object implementing IStorage will do.

        hr = StgCreateStorageEx( NULL,  // Just create a temporary storage
                                 STGM_CREATE
                                    | STGM_READWRITE
                                    | STGM_SHARE_EXCLUSIVE,
                                 STGFMT_STORAGE,
                                 0, NULL, NULL,
                                 IID_IStorage,
                                 reinterpret_cast<void**>(&pStg) );
        if( FAILED(hr) ) throw L"Failed StgCreateStorageEx";

        // Now get and use an IPropertySetStorage representing this IStorage.

        pPropStg = CreatePropertySetInStorage( pStg, FMTID_SummaryInformation );
        if( NULL == pPropStg ) throw L"Failed CreatePropertySetInStorage";

        //-----
        // Here we could call IPropertyStorage methods such as WriteMultiple and
        // ReadMultiple using the pPropStg pointer.
        //-----

        printf( "Success\n" );
    }
    catch( const WCHAR *pwszError )
    {
        wprintf( L"Error: %s (%08x)\n", pwszError, hr );
    }

    if( NULL != pPropStg )
        pPropStg->Release();
    if( NULL != pStg )
        pStg->Release();

}
