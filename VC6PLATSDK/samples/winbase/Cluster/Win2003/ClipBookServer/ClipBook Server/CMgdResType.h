/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2003 <company name>
//
//  Module Name:
//      CMgdResType.h
//
//  Description:
//      Header file for the CMgdResType class.
//
//  Author:
//      <name> (<e-mail name>) Mmmm DD, 2003
//
//  Revision History:
//
//  Notes:
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "clres.h"
#include "CMgdClusCfgInit.h"

//////////////////////////////////////////////////////////////////////////////
//++
//
//  class CMgdResType
//
//  Description:
//      The CMgdResType class is an implementation of the
//      IClusCfgResourceTypeInfo interface.
//
//--
//////////////////////////////////////////////////////////////////////////////
class CMgdResType
    : public IClusCfgResourceTypeInfo
    , public IClusCfgStartupListener
    , public CMgdClusCfgInit
    , public CComCoClass<CMgdResType,&CLSID_ClipBookServer>
{
public:
    CMgdResType( void ) {}
    virtual ~CMgdResType( void ) {}

BEGIN_COM_MAP( CMgdResType )
    COM_INTERFACE_ENTRY( IClusCfgResourceTypeInfo )
    COM_INTERFACE_ENTRY( IClusCfgStartupListener )
    COM_INTERFACE_ENTRY( IClusCfgInitialize )
END_COM_MAP()
DECLARE_NOT_AGGREGATABLE( CMgdResType )

BEGIN_CATEGORY_MAP( CMgdResType )
    IMPLEMENTED_CATEGORY( CATID_ClusCfgResourceTypes )
    IMPLEMENTED_CATEGORY( CATID_ClusCfgStartupListeners )
END_CATEGORY_MAP()

DECLARE_NOT_AGGREGATABLE( CMgdResType )

#pragma warning( push, 3 )
#pragma warning( disable : 4995 ) // warning C4995: '<x>': name was marked as #pragma deprecated
DECLARE_REGISTRY_RESOURCEID(IDR_CMgdResType)
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

    CMgdResType( const CMgdResType & rSrcIn );

    //
    //  Private assignment operator to avoid copying.
    //

    const CMgdResType & operator = ( const CMgdResType & rSrcIn );

}; //*** class CMgdResType
