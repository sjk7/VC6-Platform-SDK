//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CStorageResource.h
//
//  Implementation Files:
//      CStorageResource.cpp
//
//  Description:
//      Header file for the CStorageResource class
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//
// Definition of the ClusCfg Managed Resource Type that this Resource belongs to
//

#include "CStorageResType.h"
#include "CMgdClusCfgInit.h"

//////////////////////////////////////////////////////////////////////////////
// Behavior Define's
//////////////////////////////////////////////////////////////////////////////

//
// Available dependency modes are:
// - dfEXCLUSIVE
// - dfSHARED
//

#define MYRES_DEPENDENCY_MODE dfSHARED


//////////////////////////////////////////////////////////////////////////////
//++
//
//  class CStorageResource
//
//  Description:
//      The CStorageResource class is an implementation of the
//      IClusCfgManagedResourceInfo and IClusCfgManagedResourceCfg interfaces.
//
//  Note:
//      Although this sample does not contain a quorum capable resource, the
//      IClusCfgVerifyQuorum interface is implemented for demonstration
//
//  Note 2:
//      Although this sample does not include any resource private data, the
//      IClusCfgManagedResourceData interface is implemented for demonstration
//
//--
//////////////////////////////////////////////////////////////////////////////
class CStorageResource
    : public IClusCfgManagedResourceCfg
    , public IClusCfgManagedResourceInfo
    , public IClusCfgVerifyQuorum
    , public IClusCfgManagedResourceData
    , public IEnumClusCfgPartitions
    , public IWMIServices
    , public IWMIObject
    , public IStorageProperties
    , public CMgdClusCfgInit
    , public CComCoClass< CStorageResource, &CLSID_CStorageResource >
{
public:
    CStorageResource( void );
    virtual ~CStorageResource( void );

BEGIN_COM_MAP( CStorageResource )
    COM_INTERFACE_ENTRY( IClusCfgManagedResourceInfo )
    COM_INTERFACE_ENTRY( IClusCfgInitialize )
    COM_INTERFACE_ENTRY( IClusCfgManagedResourceCfg )
    COM_INTERFACE_ENTRY( IClusCfgVerifyQuorum )
    COM_INTERFACE_ENTRY( IClusCfgManagedResourceData )
    COM_INTERFACE_ENTRY( IEnumClusCfgPartitions )
    COM_INTERFACE_ENTRY( IWMIServices )
    COM_INTERFACE_ENTRY( IWMIObject )
    COM_INTERFACE_ENTRY( IStorageProperties )
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE( CStorageResource )

#pragma warning( push, 3 )
#pragma warning( disable : 4995 ) // warning C4995: '<x>': name was marked as #pragma deprecated
DECLARE_REGISTRY_RESOURCEID( IDR_CStorageResource )
#pragma warning( pop )

    //
    // IClusCfgManagedResourceInfo interface
    //

    STDMETHOD( GetUID )( BSTR * pbstrUIDOut );
    STDMETHOD( GetName )( BSTR * pbstrNameOut );
    STDMETHOD( SetName )( LPCWSTR pwszNameIn );
    STDMETHOD( IsManaged )( void );
    STDMETHOD( SetManaged )( BOOL fIsManagedIn );
    STDMETHOD( IsQuorumResource )( void );
    STDMETHOD( SetQuorumResource )( BOOL fIsQuorumDeviceIn );
    STDMETHOD( IsQuorumCapable )( void );
    STDMETHOD( SetQuorumCapable )( BOOL fIsQuorumCapableIn );
    STDMETHOD( GetDriveLetterMappings )( SDriveLetterMapping * pdlmDriveLetterMappingsOut );
    STDMETHOD( SetDriveLetterMappings )( SDriveLetterMapping dlmDriveLetterMappingsIn );
    STDMETHOD( IsManagedByDefault )( void );
    STDMETHOD( SetManagedByDefault )( BOOL fIsManagedByDefaultIn );

    //
    // IClusCfgManagedResourceCfg interface
    //

    STDMETHOD( PreCreate )( IUnknown * punkServicesIn );
    STDMETHOD( Create )( IUnknown * punkServicesIn );
    STDMETHOD( PostCreate )( IUnknown * punkServicesIn );
    STDMETHOD( Evict )( IUnknown * punkServicesIn );

    //
    // IClusCfgVerifyQuorum interface
    //

    STDMETHOD( IsMultiNodeCapable )( void );
    STDMETHOD( SetMultiNodeCapable )( BOOL fMultiNodeCapableIn );
    STDMETHOD( PrepareToHostQuorumResource )( void );
    STDMETHOD( Cleanup )( EClusCfgCleanupReason cccrReasonIn );

    //
    // IClusCfgManagedResourceData interface
    //

    STDMETHOD( GetResourcePrivateData )( BYTE * pbBufferOut, DWORD * pcbBufferInout );
    STDMETHOD( SetResourcePrivateData )( const BYTE * pcbBufferIn, DWORD cbBufferIn );

    //
    // IWMIServices Interface
    //

    STDMETHOD( SetWbemServices )( IWbemServices * pIWbemServicesIn );

    //
    // IWMIObject Interface
    //

    STDMETHOD( SetWbemObject )( IWbemClassObject * pDiskIn, BOOL * pfRetainObjectOut );

    //
    // IEnumClusCfgPartitions Interface
    //

    STDMETHOD( Next )( ULONG cNumberRequestedIn, IClusCfgPartitionInfo ** rgpPartitionInfoOut, ULONG * pcNumberFetchedOut );
    STDMETHOD( Skip )( ULONG cNumberToSkipIn );
    STDMETHOD( Reset )( void );
    STDMETHOD( Clone )( IEnumClusCfgPartitions ** ppEnumClusCfgPartitionsOut );
    STDMETHOD( Count )( DWORD * pnCountOut );

    //
    // IStorageProperties Interface
    //

    STDMETHOD( IsThisLogicalDisk )( WCHAR cLogicalDiskIn );
    STDMETHOD( HrGetSCSIBus )( ULONG * pulSCSIBusOut );
    STDMETHOD( HrGetSCSIPort )( ULONG * pulSCSIPortOut );
    STDMETHOD( CanBeManaged )( void );
    STDMETHOD( HrGetDeviceID )( BSTR * pbstrDeviceIDOut );
    STDMETHOD( HrGetSignature )( DWORD * pdwSignatureOut );
    STDMETHOD( HrSetFriendlyName )( LPCWSTR pcszFriendlyNameIn );
    STDMETHOD( HrGetDeviceIndex )( DWORD * pidxDeviceOut );
    STDMETHOD( HrIsDynamicDisk )( void );
    STDMETHOD( HrIsGPTDisk )( void );
    STDMETHOD( HrGetDiskNames )( BSTR * pbstrDiskNameOut, BSTR * pbstrDeviceNameOut );

private:

    BSTR                m_bstrName;
    BSTR                m_bstrDescription;
    BSTR                m_bstrFriendlyName;
    BSTR                m_bstrDeviceID;

    BOOL                m_fIsQuorumCapable;
    BOOL                m_fIsQuorumResource;
    BOOL                m_fIsMultiNodeCapable;
    BOOL                m_fIsManaged;
    BOOL                m_fIsManagedByDefault;
    BOOL                m_fIsDynamicDisk;
    BOOL                m_fIsGPTDisk;

    ULONG               m_ulSCSIBus;
    ULONG               m_ulSCSITid;
    ULONG               m_ulSCSIPort;
    ULONG               m_ulSCSILun;

    DWORD               m_idxDevice;
    DWORD               m_idxNextPartition;
    DWORD               m_idxEnumPartitionNext;
    DWORD               m_cPartitions;
    DWORD               m_dwSignature;

    IWbemServices *     m_pIWbemServices;
    IUnknown *          ((*m_prgPartitions)[]);

    //
    // Private copy constructor to avoid copying.
    //

    CStorageResource( const CStorageResource & rSrcIn );

    //
    // Private assignment operator to avoid copying.
    //

    const CStorageResource & operator = ( const CStorageResource & rSrcIn );

    //
    // Helper functions.
    //

    HRESULT HrGetPartitionInfo( IWbemClassObject * pDiskIn, BOOL * pfRetainObjectOut );
    HRESULT HrCreatePartitionInfo( IWbemClassObject * pPartitionIn );
    HRESULT HrAddPartitionToArray( IUnknown * punkIn );
    HRESULT HrCreateFriendlyName( void );
    HRESULT HrCreateFriendlyName( BSTR bstrNameIn );
    HRESULT HrIsPartitionGPT( IWbemClassObject * pPartitionIn );
    HRESULT HrIsPartitionLDM( IWbemClassObject * pPartitionIn );
    HRESULT HrIsClusterCapable( void );

}; //*** class CStorageResource
