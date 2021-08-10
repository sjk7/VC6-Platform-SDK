//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CPartitionInfo.h
//
//  Description:
//      This file contains the declaration of the CPartitionInfo
//      class.
//
//      The class CPartitionInfo represents a disk partition.
//      It implements the IClusCfgPartitionInfo interface.
//
//  Implementation Files:
//      CPartitionInfo.cpp
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CMgdClusCfgInit.h"


//////////////////////////////////////////////////////////////////////////////
// Constant Declarations
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  class CPartitionInfo
//
//  Description:
//      The class CPartitionInfo represents a disk partition.
//
//  Interfaces:
//      IClusCfgPartitionInfo
//      IWMIService
//      IWMIObject
//      IPartitionProperties
//      IClusCfgInitialize
//--
//////////////////////////////////////////////////////////////////////////////
class CPartitionInfo
    : public IClusCfgPartitionInfo
    , public IWMIServices
    , public IWMIObject
    , public IPartitionProperties
    , public CMgdClusCfgInit
    , public CComCoClass< CPartitionInfo, &CLSID_CPartitionInfo >
{
public:

BEGIN_COM_MAP( CPartitionInfo )
    COM_INTERFACE_ENTRY( IClusCfgPartitionInfo )
    COM_INTERFACE_ENTRY( IWMIServices )
    COM_INTERFACE_ENTRY( IWMIObject )
    COM_INTERFACE_ENTRY( IClusCfgInitialize )
    COM_INTERFACE_ENTRY( IPartitionProperties )
END_COM_MAP();

DECLARE_NOT_AGGREGATABLE( CPartitionInfo )

#pragma warning( push, 3 )
#pragma warning( disable : 4995 ) // warning C4995: '<x>': name was marked as #pragma deprecated
DECLARE_REGISTRY_RESOURCEID( IDR_CPartitionInfo )
#pragma warning( pop )

private:

    //
    // Private member functions and data
    //

    LONG                m_cRef;
    LCID                m_lcid;
    IWbemServices *     m_pIWbemServices;
    BSTR                m_bstrName;
    BSTR                m_bstrUID;
    BSTR                m_bstrDescription;
    IUnknown *          ((*m_prgLogicalDisks)[]);
    ULONG               m_idxNextLogicalDisk;
    ULONG               m_ulPartitionSize;
    BSTR                m_bstrDiskDeviceID;

    //
    //  Private copy constructor to prevent copying of this COM object.
    //

    CPartitionInfo( const CPartitionInfo & nodeSrc );

    //
    //  Private assignment operator to prevent copying of this COM object.
    //

    const CPartitionInfo & operator = ( const CPartitionInfo & nodeSrc );

    HRESULT HrAddLogicalDiskToArray( IWbemClassObject * pDiskIn );
    HRESULT HrGetLogicalDisks( IWbemClassObject * pPartitionIn );
    HRESULT HrLogLogicalDiskInfo( IWbemClassObject * pLogicalDiskIn, BSTR bstrDeviceIDIn );

public:

    //
    //  Public constructor & destructor.
    //

    CPartitionInfo( void );
    virtual ~CPartitionInfo( void );

    //
    // IWMIServices Interface
    //

    STDMETHOD( SetWbemServices )( IWbemServices * pIWbemServicesIn );

    //
    // IWMIObject Interfaces
    //

    STDMETHOD( SetWbemObject )( IWbemClassObject * pPartitionIn, BOOL * pfRetainObjectOut );

    //
    // IClusCfgManagedResourceInfo Interface
    //

    STDMETHOD( GetUID )( BSTR * pbstrUIDOut );
    STDMETHOD( GetName )( BSTR * pbstrNameOut );
    STDMETHOD( SetName )( LPCWSTR bstrNameIn );
    STDMETHOD( GetDescription )( BSTR * pbstrDescriptionOut );
    STDMETHOD( SetDescription )( LPCWSTR bstrDescriptionIn );
    STDMETHOD( GetDriveLetterMappings )( SDriveLetterMapping * pdlmDriveLetterUsageOut );
    STDMETHOD( SetDriveLetterMappings )( SDriveLetterMapping dlmDriveLetterMappingIn );
    STDMETHOD( GetSize )( ULONG * pcMegaBytes );

    //
    // IPartitionProperties Interface
    //

    STDMETHOD( HrIsThisLogicalDisk )( WCHAR cLogicalDisk );
    STDMETHOD( HrIsNTFS )( void );
    STDMETHOD( HrGetFriendlyName )( BSTR * pbstrNameOut );
    STDMETHOD( HrSetDeviceID )( BSTR bstrDeviceIDIn );

}; //*** class CPartitionInfo

