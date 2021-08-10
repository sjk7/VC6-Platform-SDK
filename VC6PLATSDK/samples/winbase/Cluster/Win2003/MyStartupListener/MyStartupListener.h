//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyStartupListener.h
//
//  Description:
//      Declaration of the CMyStartupListener class.
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

// {BA3DE790-AD13-432b-A1DB-4905F6C7A336}
DEFINE_GUID( CLSID_MyStartupListener, 
0xba3de790, 0xad13, 0x432b, 0xa1, 0xdb, 0x49, 0x5, 0xf6, 0xc7, 0xa3, 0x36);

/////////////////////////////////////////////////////////////////////////////
//++
//
// CMyStartupListener class definition
//
//--
/////////////////////////////////////////////////////////////////////////////
class CMyStartupListener
    : public CComObjectRootEx<CComMultiThreadModel>
    , public CComCoClass<CMyStartupListener, &CLSID_MyStartupListener>
    , public IClusCfgStartupListener
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
    CMyStartupListener( void );
    ~CMyStartupListener( void );

public:

    DECLARE_REGISTRY_RESOURCEID( IDR_MYSTARTUPLISTENER )
    DECLARE_NOT_AGGREGATABLE( CMyStartupListener )

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP( CMyStartupListener )
        COM_INTERFACE_ENTRY( IClusCfgStartupListener )
        COM_INTERFACE_ENTRY( IClusCfgInitialize )
    END_COM_MAP()

    BEGIN_CATEGORY_MAP( CMyStartupListener )
        IMPLEMENTED_CATEGORY( CATID_ClusCfgStartupListeners )
    END_CATEGORY_MAP()

    //
    // IClusCfgStartupListener methods
    //
    STDMETHOD( Notify ) ( IUnknown * punkIn );

    //
    //  IClusCfgInitialize methods
    //
    STDMETHOD( Initialize )(
          IUnknown *   punkCallbackIn
        , LCID         lcidIn
        );

}; //*** class: CMyStartupListener

//
// Restore the warning state.
//
#pragma warning( pop )

