//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyMemberSetChangeListener.h
//
//  Description:
//      Declaration of the CMyMemberSetChangeListener class.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

//
// Categories and ClusCfg GUIDS
//
#include <ClusCfgServer.h>
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

// {7CD2EBBF-0958-4513-A58F-0B0B098A6119}
DEFINE_GUID( CLSID_MyMemberSetChangeListener, 
0x7cd2ebbf, 0x958, 0x4513, 0xa5, 0x8f, 0xb, 0xb, 0x9, 0x8a, 0x61, 0x19 );

// {2A483627-8BCE-48ea-9613-4CA2F53489FA}
DEFINE_GUID( TASKID_Minor_MyMemberSetChange_Info, 
0x2a483627, 0x8bce, 0x48ea, 0x96, 0x13, 0x4c, 0xa2, 0xf5, 0x34, 0x89, 0xfa );

/////////////////////////////////////////////////////////////////////////////
//++
//
// CMyMemberSetChangeListener class definition
//
//--
/////////////////////////////////////////////////////////////////////////////
class CMyMemberSetChangeListener
    : public CComObjectRootEx<CComMultiThreadModel>
    , public CComCoClass<CMyMemberSetChangeListener, &CLSID_MyMemberSetChangeListener>
    , public IClusCfgMemberSetChangeListener
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
    CMyMemberSetChangeListener( void );
    ~CMyMemberSetChangeListener( void );

public:

    DECLARE_REGISTRY_RESOURCEID( IDR_MYMEMBERSETCHANGELISTENER )
    DECLARE_NOT_AGGREGATABLE( CMyMemberSetChangeListener )

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP( CMyMemberSetChangeListener )
        COM_INTERFACE_ENTRY( IClusCfgMemberSetChangeListener )
        COM_INTERFACE_ENTRY( IClusCfgInitialize )
    END_COM_MAP()

    BEGIN_CATEGORY_MAP( CMyMemberSetChangeListener )
        IMPLEMENTED_CATEGORY( CATID_ClusCfgMemberSetChangeListeners )
    END_CATEGORY_MAP()

    //
    // IClusCfgMemberSetChangeListener methods
    //
    STDMETHOD( Notify ) ( IUnknown * punkIn );

    //
    //  IClusCfgInitialize methods
    //
    STDMETHOD( Initialize )(
          IUnknown *   punkCallbackIn
        , LCID         lcidIn
        );

}; //*** class: CMyMemberSetChangeListener

//
// Restore the warning state.
//
#pragma warning( pop )

