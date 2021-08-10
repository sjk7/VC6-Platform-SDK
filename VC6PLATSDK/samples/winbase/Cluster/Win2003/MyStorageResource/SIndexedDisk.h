//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      SIndexedDisk.h
//
//  Implementation Files:
//      SIndexedDisk.cpp
//
//  Description:
//      This file contains the declaration of the SIndexedDisk structure.
//
//      This is a helper for CEnumStorageResource, but has its own file
//      due to the one-class-per-file restriction.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////////
// Constant Declarations
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  struct SIndexedDisk
//
//  Description:
//      The SIndexedDisk structure associates a pointer to a disk object with
//      the disk object's Index property.
//
//--
//////////////////////////////////////////////////////////////////////////////
struct SIndexedDisk
{
    SIndexedDisk( void );
    // accept default destructor, copy constructor, and assignment operator

    DWORD       idxDisk;
    IUnknown *  punkDisk;

    HRESULT HrInit( IUnknown * punkDiskIn );

}; //*** struct SIndexedDisk


inline SIndexedDisk::SIndexedDisk( void )
    : idxDisk( 0 )
    , punkDisk( NULL )
{
} //*** SIndexedDisk::SIndexedDisk


//////////////////////////////////////////////////////////////////////////////
//++
//
//  struct SIndexedDiskLessThan
//
//  Description:
//      The SIndexedDiskLessThan function object provides a comparison
//      operation to arrange SIndexedDisk objects in ascending order when used
//      with generic sort algorithms or sorted containers.
//
//      Although a simple function pointer would work, making it a function
//      object allows the compiler to inline the comparison operation.
//
//--
//////////////////////////////////////////////////////////////////////////////

struct SIndexedDiskLessThan
{
    bool operator()( const SIndexedDisk & rLeftIn, const SIndexedDisk & rRightIn ) const
    {
        return ( rLeftIn.idxDisk < rRightIn.idxDisk );
    }

}; //*** struct SIndexedDiskLessThan


