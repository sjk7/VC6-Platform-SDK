//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      StdAfx.cpp
//
//  Description:
//
//  Header File:
//      StdAfx.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#pragma warning( push, 3 )

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

#include "MyStorageResource_i.c"
#pragma warning( pop )


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrSetInitialize
//
//  Description:
//      Initialize the passed in object.
//
//  Arguments:
//      punkIn
//          Interface to object to initialize.
//
//      picccIn
//          Callback interface.
//
//      lcidIn
//          Locale ID.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrSetInitialize(
      IUnknown *            punkIn
    , IClusCfgCallback *    picccIn
    , LCID                  lcidIn
    )
{
    assert( punkIn != NULL );

    HRESULT                 hr;
    IClusCfgInitialize *    pcci = NULL;
    IUnknown *              punkCallback = NULL;

    //
    // Make sure required arguments were specified.
    //

    if ( punkIn == NULL )
    {
        hr = E_INVALIDARG;
        goto Cleanup;
    } // if:

    //
    // If a callback interface was specified, get an IUnknown pointer
    // to pass to the specified object.
    //

    if ( picccIn != NULL )
    {
        hr = picccIn->TypeSafeQI( IUnknown, &punkCallback );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if: callback interface was specified

    //
    // Query the object for the IClusCfgInitialize interface and call
    // the Initialize method if successful.
    //

    hr = punkIn->TypeSafeQI( IClusCfgInitialize, &pcci );
    if ( SUCCEEDED( hr ) )
    {
        hr = pcci->Initialize( punkCallback, lcidIn );
        pcci->Release();
    } // if:
    else if ( hr == E_NOINTERFACE )
    {
        hr = S_OK;
    } // else if:

Cleanup:

    if ( punkCallback != NULL )
    {
        punkCallback->Release();
    } // if:

    return hr;

} //*** HrSetInitialize

