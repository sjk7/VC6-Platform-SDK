//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyEvictListener.h
//
//  Description:
//      Declaration of the CMyEvictListener class.
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

// {8097F026-7E96-4afa-B317-B35D8F88CFF7}
DEFINE_GUID(CLSID_MyEvictListener, 
0x8097f026, 0x7e96, 0x4afa, 0xb3, 0x17, 0xb3, 0x5d, 0x8f, 0x88, 0xcf, 0xf7);

/////////////////////////////////////////////////////////////////////////////
//++
//
// CMyEvictListener class definition
//
//--
/////////////////////////////////////////////////////////////////////////////
class CMyEvictListener
    : public CComObjectRootEx<CComMultiThreadModel>
    , public CComCoClass<CMyEvictListener, &CLSID_MyEvictListener>
    , public IClusCfgEvictListener
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
    IClusCfgCallback * m_piccCallback;

protected:
    //
    // Constructor and destructor
    //
    CMyEvictListener( void );
    ~CMyEvictListener( void );

public:

    DECLARE_REGISTRY_RESOURCEID( IDR_MYEVICTLISTENER )
    DECLARE_NOT_AGGREGATABLE( CMyEvictListener )

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP( CMyEvictListener )
        COM_INTERFACE_ENTRY( IClusCfgEvictListener )
        COM_INTERFACE_ENTRY( IClusCfgInitialize )
    END_COM_MAP()

    BEGIN_CATEGORY_MAP( CMyEvictListener )
        IMPLEMENTED_CATEGORY( CATID_ClusCfgEvictListeners )
    END_CATEGORY_MAP()

    //
    // IClusCfgEvictListener methods
    //
    STDMETHOD( EvictNotify ) ( LPCWSTR pcszNodeNameIn );

    //
    //  IClusCfgInitialize methods
    //
    STDMETHOD( Initialize )(
          IUnknown *   punkCallbackIn
        , LCID         lcidIn
        );

}; //*** class: CMyEvictListener

//
// Restore the warning state.
//
#pragma warning( pop )
