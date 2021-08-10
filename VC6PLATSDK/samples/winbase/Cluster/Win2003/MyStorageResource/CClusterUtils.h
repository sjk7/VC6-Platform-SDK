//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CClusterUtils.h
//
//  Description:
//      This file contains the declaration of the CClusterUtils class.
//
//  Implementation Files:
//      CClusterUtils.cpp
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
//  class CClusterUtils
//
//  Description:
//      The CClusterUtils class contains utility functions for 
//      dealing with cluster resources.
//
//  Interfaces:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
class CClusterUtils
{
private:

    //
    // Private member functions and data
    //

    //
    //  Private copy constructor to prevent copying.
    //

    CClusterUtils( const CClusterUtils & nodeSrc );

    //
    //  Private assignment operator to prevent copying.
    //

    const CClusterUtils & operator = ( const CClusterUtils & nodeSrc );

protected:

    //
    //  constructors and destructors
    //

    CClusterUtils( void ) {};
    virtual ~CClusterUtils( void ) {};

public:

    HRESULT HrIsGroupOwnedByThisNode( HGROUP hGroupIn, BSTR bstrNodeNameIn );
    HRESULT HrIsNodeClustered( void );
    HRESULT HrEnumNodeResources( BSTR bstrNodeNameIn );
    HRESULT HrLoadGroupResources( HCLUSTER hClusterIn, HGROUP hGroupIn );
    HRESULT HrGetQuorumResourceName( BSTR * pbstrQuorumResourceNameOut );
    HRESULT HrIsClusterServiceRunning( void );
    HRESULT HrIsCoreResource( HRESOURCE hResourceIn );

    virtual HRESULT HrNodeResourceCallback( HRESOURCE hResourceIn ) = 0;

}; //*** class CClusterUtils
