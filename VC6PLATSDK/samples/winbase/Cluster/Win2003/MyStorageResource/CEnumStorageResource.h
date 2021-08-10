//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CEnumStorageResource.h
//
//  Implementation Files:
//      CEnumStorageResource.cpp
//
//  Description:
//      This file contains the declaration of the CEnumStorageResource class.
//
//      The class CEnumStorageResource is the enumeration of cluster
//      storage devices. It implements the IEnumClusCfgManagedResources
//      interface.
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CStorageResource.h"
#include "CMgdClusCfgInit.h"
#include "CClusterUtils.h"


//////////////////////////////////////////////////////////////////////////////
// Constant Declarations
//////////////////////////////////////////////////////////////////////////////

const WCHAR   g_szNameSpaceRoot[]             = { L"\\\\?\\GLOBALROOT" };
const WCHAR   g_szPhysicalDriveFormat[]       = { L"\\\\.\\PHYSICALDRIVE%lu\0" };


//////////////////////////////////////////////////////////////////////////////
//++
//
//  class CEnumStorageResource
//
//  Description:
//      The class CEnumStorageResource is the enumeration of the managed
//      phyical disks.  This is an example of finding disks and getting
//      them managed by a cluster.
//
//  Interfaces:
//      IEnumClusCfgManagedResources
//      IWMIService
//      IClusCfgInitialize
//
//--
//////////////////////////////////////////////////////////////////////////////
class CEnumStorageResource
    : public IEnumClusCfgManagedResources
    , public IWMIServices
    , public CClusterUtils
    , public CMgdClusCfgInit
    , public CComCoClass< CEnumStorageResource, &CLSID_CEnumStorageResource >
{
public:

BEGIN_COM_MAP( CEnumStorageResource )
    COM_INTERFACE_ENTRY( IEnumClusCfgManagedResources )
    COM_INTERFACE_ENTRY( IClusCfgInitialize )
    COM_INTERFACE_ENTRY( IWMIServices )
END_COM_MAP()

BEGIN_CATEGORY_MAP( CEnumStorageResource )
    IMPLEMENTED_CATEGORY( CATID_EnumClusCfgManagedResources )
END_CATEGORY_MAP()

DECLARE_NOT_AGGREGATABLE( CEnumStorageResource )

#pragma warning( push, 3 )
#pragma warning( disable : 4995 ) // warning C4995: '<x>': name was marked as #pragma deprecated
DECLARE_REGISTRY_RESOURCEID( IDR_CEnumStorageResource )
#pragma warning( pop )

    //
    // Constructors and destructors
    //

    CEnumStorageResource( void );

    virtual ~CEnumStorageResource( void );

private:

    //
    // Private member functions and data
    //

    BOOL                m_fLoadedDevices;               // Has this enum been loaded?
    IWbemServices *     m_pIWbemServices;               // Pointer to the WMI services.
    IUnknown *          ((*m_prgDisks)[]);              // Sparse array of punk ponters to hold the disks.
    ULONG               m_idxNext;                      // The index of the next open punk pointer in the array.
    ULONG               m_idxEnumNext;                  // Then index of the COM enumeration.
    BSTR                m_bstrBootDevice;               // Name of the boot device.
    BSTR                m_bstrSystemDevice;             // Name of the system device.
    BSTR                m_bstrBootLogicalDisk;          // Logical disk ID of the boot device.
    BSTR                m_bstrSystemLogicalDisk;        // Logical disk ID of the system device.
    BSTR                m_bstrSystemWMIDeviceID;        // Name that of the system device in WMI.
    BSTR                m_bstrCrashDumpLogicalDisk;     // Name of the logical disk that has the crash dumps on it.
    DWORD               m_cDiskCount;                   // Number of devices (disks) in this enumerator.

    //
    // Private copy constructor to prevent copying of this COM object.
    //

    CEnumStorageResource( const CEnumStorageResource & nodeSrc );

    //
    // Private assignment operator to prevent copying of this COM object.
    //

    const CEnumStorageResource & operator = ( const CEnumStorageResource & nodeSrc );

    //
    // All of these private methods are simply to demonstrate finding and
    // dealing with physical disks.
    //

    HRESULT HrGetDisks( void );
    HRESULT HrProcessWMIDiskObject( IWbemClassObject * pDiskIn );
    HRESULT HrAddObjectToArray( IUnknown * punkIn );
    HRESULT HrPruneSystemDisks( void );
    HRESULT IsDiskSCSI( IWbemClassObject * pDiskIn );
    HRESULT HrFixupDisks( void );
    HRESULT HrGetClusterDiskInfo( HRESOURCE hResourceIn, CLUS_SCSI_ADDRESS * pcsaOut, DWORD * pdwSignatureOut );
    HRESULT HrSetThisDiskToBeManaged( ULONG ulSCSITidIn, ULONG ulSCSILunIn, BOOL fIsQuorumIn, BSTR bstrResourceNameIn, DWORD dwSignatureIn );
    HRESULT HrFindDiskWithLogicalDisk( WCHAR cLogicalDiskIn, ULONG * pidxDiskOut );
    HRESULT HrGetSCSIInfo( ULONG idxDiskIn, ULONG * pulSCSIBusOut, ULONG * pulSCSIPortOut );
    HRESULT HrPruneDisks( ULONG ulSCSIBusIn, ULONG ulSCSIPortIn, const GUID * pcguidMajorIdIn, int nMsgIdIn, int nRefIdIn, ULONG * pulRemovedOut );
    void    LogPrunedDisk( IUnknown * punkIn, ULONG ulSCSIBusIn, ULONG ulSCSIPortIn );
    HRESULT HrIsLogicalDiskNTFS( BSTR bstrLogicalDiskIn );
    HRESULT HrLogDiskInfo( IWbemClassObject * pDiskIn );
    HRESULT HrFindDiskWithWMIDeviceID( BSTR bstrWMIDeviceIDIn, ULONG * pidxDiskOut );
    HRESULT HrIsSystemBusManaged( void );
    HRESULT HrGetClusterProperties( HRESOURCE hResourceIn, BSTR * pbstrResourceNameOut );
    void    RemoveDiskFromArray( ULONG idxDiskIn );
    HRESULT HrLoadEnum( void );
    HRESULT HrSortDisksByIndex( void );
    HRESULT HrPrunePageFileDiskBuses( BOOL fPruneBusIn, ULONG * pcPrunedInout );
    HRESULT HrPruneCrashDumpBus( BOOL fPruneBusIn, ULONG * pcPrunedInout );
    HRESULT HrPruneDynamicDisks( ULONG * pcPrunedInout );
    HRESULT HrPruneGPTDisks( ULONG * pcPrunedInout );
    HRESULT HrConvertDeviceVolumeToLogicalDisk( BSTR bstrDeviceVolumeIn, BSTR * pbstrLogicalDiskOut );
    HRESULT HrConvertDeviceVolumeToWMIDeviceID( BSTR bstrDeviceVolumeIn, BSTR * pbstrWMIDeviceIDOut );
    HRESULT HrGetPageFileLogicalDisks( IClusCfgCallback * picccIn, WCHAR szLogicalDisksOut[ 26 ], int * pcLogicalDisksOut );
    HRESULT HrGetSystemDevice( BSTR * pbstrSystemDeviceOut );
    HRESULT HrGetBootLogicalDisk( BSTR * pbstrBootDeviceOut );
    HRESULT HrGetCrashDumpLogicalDisk( BSTR * pbstrCrashDumpLogicalDiskOut );

public:

    //
    // CClusterUtils
    //

    HRESULT HrNodeResourceCallback( HRESOURCE hResourceIn );

    //
    // IWMIServices Interfaces
    //

    STDMETHOD( SetWbemServices )( IWbemServices * pIWbemServicesIn );

    //
    // IClusCfgInitialize is an optional interface.  By not implementing it
    // your component will not be able to send status reports to the UIO and
    // log files, and it won't know the users locale.
    //

    //
    // IClusCfgInitialize interface (overridden from CMgdClusCfgInit)
    //

    STDMETHOD( Initialize )( IUnknown * punkCallbackIn, LCID lcidIn );

    //
    // The following interfaces and methods must be implemented by any
    // component that is a ClusCfg plug in component.

    //
    // IEnumClusCfgManagedResources Interfaces
    //

    STDMETHOD( Next )( ULONG cNumberRequestedIn, IClusCfgManagedResourceInfo ** rgpManagedResourceInfoOut, ULONG * pcNumberFetchedOut );
    STDMETHOD( Skip )( ULONG cNumberToSkipIn );
    STDMETHOD( Reset )( void );
    STDMETHOD( Clone )( IEnumClusCfgManagedResources ** ppEnumClusCfgStorageDevicesOut );
    STDMETHOD( Count )( DWORD * pnCountOut );

}; //*** class CEnumStorageResource
