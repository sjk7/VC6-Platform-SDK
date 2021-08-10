//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      SIndexedDisk.cpp
//
//  Description:
//      This file contains the definition of the SIndexedDisk class.
//
//      The SIndexedDisk structure associates a pointer to a disk object with
//      the disk object's Index property.
//
//  Header File:
//      SIndexedDisk.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SIndexedDisk.h"

//****************************************************************************
//
// SIndexedDisk class
//
//****************************************************************************


//////////////////////////////////////////////////////////////////////////////
//++
//
//  SIndexedDisk::HrInit
//
//  Description:
//      Initialize this instance from a disk object; punkDiskIn must
//      support the IStorageProperties interface.
//
//  Arguments:
//      punkDiskIn
//          The disk object for initialization.
//
//  Return Values:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
SIndexedDisk::HrInit(
    IUnknown * punkDiskIn
    )
{
    HRESULT                 hr = S_OK;
    IStorageProperties *    pisdp = NULL;

    if ( punkDiskIn == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    }

    //
    // QI for IStorageProperties.
    //

    hr = punkDiskIn->TypeSafeQI( IStorageProperties, &pisdp );

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    }

    //
    // Get index from IStorageProperties.
    //

    hr = pisdp->HrGetDeviceIndex( &idxDisk );

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    }

    punkDisk = punkDiskIn;

Cleanup:

    if ( pisdp != NULL )
    {
        pisdp->Release();
    }

    return hr;

} //*** SIndexedDisk::HrInit

