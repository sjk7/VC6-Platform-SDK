//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CStorageResType.h
//
//  Description:
//      This file contains the declaration of the CStorageResType class.
//
//  Implementation Files:
//      CStorageResType.cpp
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CMgdClusCfgInit.h"


//////////////////////////////////////////////////////////////////////////////
//++
//
//  class CStorageResType
//
//  Description:
//      The CStorageResType class is an implementation of the
//      IClusCfgResourceTypeInfo interface.
//
//--
//////////////////////////////////////////////////////////////////////////////
class CStorageResType
    : public IClusCfgResourceTypeInfo
    , public IClusCfgStartupListener
    , public CMgdClusCfgInit
    , public CComCoClass< CStorageResType, &CLSID_CStorageResType >
{
public:
    CStorageResType( void ) {}
    virtual ~CStorageResType( void ) {}

BEGIN_COM_MAP( CStorageResType )
    COM_INTERFACE_ENTRY( IClusCfgResourceTypeInfo )
    COM_INTERFACE_ENTRY( IClusCfgStartupListener )
    COM_INTERFACE_ENTRY( IClusCfgInitialize )
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE( CStorageResType )

BEGIN_CATEGORY_MAP( CStorageResType )
    IMPLEMENTED_CATEGORY( CATID_ClusCfgResourceTypes )
    IMPLEMENTED_CATEGORY( CATID_ClusCfgStartupListeners )
END_CATEGORY_MAP()

#pragma warning( push, 3 )
#pragma warning( disable : 4995 ) // warning C4995: '<x>': name was marked as #pragma deprecated
DECLARE_REGISTRY_RESOURCEID(IDR_CStorageResType)
#pragma warning( pop )

    //
    //  IClusCfgResourceTypeInfo interface
    //

    STDMETHOD( CommitChanges )( IUnknown * punkClusterInfoIn, IUnknown * punkResTypeServicesIn );
    STDMETHOD( GetTypeGUID )( GUID * pguidGUIDOut );
    STDMETHOD( GetTypeName )( BSTR * pbstrTypeNameOut );

    //
    //  IClusCfgStartupListener methods
    //

    STDMETHOD( Notify )( IUnknown * punkIn );

private:

    //
    //  Private copy constructor to avoid copying.
    //

    CStorageResType( const CStorageResType & rSrcIn );

    //
    //  Private assignment operator to avoid copying.
    //

    const CStorageResType & operator = ( const CStorageResType & rSrcIn );

}; //*** class CStorageResType
