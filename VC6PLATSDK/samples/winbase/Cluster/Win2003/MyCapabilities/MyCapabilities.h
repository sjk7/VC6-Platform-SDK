//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyCapabilities.h
//
//  Description:
//      Declaration of the CMyCapabilities class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

//
// Categories and ClusCfg GUIDS
//
#include <ClusCfgGuids.h>

#include "resource.h"

//
// Store the warning state.
//
#pragma warning( push )

//
// Disable warning 4995. The text of the warning is below:
// 'wsprintf': name was marked as #pragma deprecated
//
#pragma warning( disable : 4995 )

// {96FCE880-4763-4287-A64B-53BD2AA99A04}
DEFINE_GUID( CLSID_MyCapabilities,
0x96fce880, 0x4763, 0x4287, 0xa6, 0x4b, 0x53, 0xbd, 0x2a, 0xa9, 0x9a, 0x4);

// {065CC8AF-D454-4f55-9413-9C4D975105ED}
DEFINE_GUID( TASKID_Minor_MyApp_Compat_Info, 
0x65cc8af, 0xd454, 0x4f55, 0x94, 0x13, 0x9c, 0x4d, 0x97, 0x51, 0x5, 0xed);

/////////////////////////////////////////////////////////////////////////////
//++
//
// CMyCapabilities class definition
//
//--
/////////////////////////////////////////////////////////////////////////////
class CMyCapabilities
    : public CComObjectRootEx<CComMultiThreadModel>
    , public CComCoClass<CMyCapabilities, &CLSID_MyCapabilities>
    , public IClusCfgCapabilities
    , public IClusCfgInitialize
{
private:
    //
    // Locale id.
    //
    LCID                m_lcid;

    //
    // Pointer to the callback interface.
    //
    IClusCfgCallback *  m_piccCallback;

protected:
    //
    // Constructor and destructor
    //
    CMyCapabilities( void );
    ~CMyCapabilities( void );

    //
    // HrGetApplicationCompatibilityInfo contains the logic to decide whether
    // or not "The App" is compatible with Clustering or not.
    //
    HRESULT HrGetApplicationCompatibilityInfo( BOOL * pfIsAppCompatible );

public:

    DECLARE_REGISTRY_RESOURCEID( IDR_MYCAPABILITIES )
    DECLARE_NOT_AGGREGATABLE( CMyCapabilities )

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP( CMyCapabilities )
        COM_INTERFACE_ENTRY( IClusCfgCapabilities )
        COM_INTERFACE_ENTRY( IClusCfgInitialize )
    END_COM_MAP()

    BEGIN_CATEGORY_MAP( CMyCapabilities )
        IMPLEMENTED_CATEGORY( CATID_ClusCfgCapabilities )
    END_CATEGORY_MAP()

    //
    // IClusCfgCapabilities methods
    //
    STDMETHOD( CanNodeBeClustered )( void );

    //
    // IClusCfgInitialize methods
    //
    STDMETHOD( Initialize )( IUnknown * punkCallbackIn, LCID lcidIn );

}; //*** class: CMyCapabilities

//
// Restore the warning state.
//
#pragma warning( pop )

