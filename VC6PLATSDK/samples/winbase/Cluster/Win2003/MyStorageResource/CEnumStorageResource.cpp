//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CEnumStorageResource.cpp
//
//  Description:
//      This file contains the definition of the CEnumStorageResource class.
//
//      The class CEnumStorageResource is the enumeration of cluster storage
//      devices.  It implements the IEnumClusCfgManagedResources interface.
//
//  Header File:
//      CEnumStorageResource.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CEnumStorageResource.h"
#include "SIndexedDisk.h"
#include "WMIHelpers.h"
#include "PropList.h"
#include "InsertionSort.h"

#pragma warning( push )
#include <resapi.h>
#pragma warning( pop )


//////////////////////////////////////////////////////////////////////////////
// CEnumStorageResource class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::CEnumStorageResource
//
//  Description:
//      Constructor of the CEnumStorageResource class. This initializes
//      the m_cRef variable to 1 instead of 0 to account of possible
//      QueryInterface failure in DllGetClassObject.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CEnumStorageResource::CEnumStorageResource( void )
    : m_fLoadedDevices( FALSE )
{
    m_pIWbemServices = NULL;
    m_prgDisks = NULL;
    m_idxNext = 0;
    m_idxEnumNext = 0;
    m_bstrBootDevice = NULL;
    m_bstrSystemDevice = NULL;
    m_bstrBootLogicalDisk = NULL;
    m_bstrSystemLogicalDisk = NULL;
    m_bstrSystemWMIDeviceID = NULL;
    m_cDiskCount = 0;
    m_bstrCrashDumpLogicalDisk = NULL;

} //*** CEnumStorageResource::CEnumStorageResource


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::~CEnumStorageResource
//
//  Description:
//      Desstructor of the CEnumStorageResource class.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CEnumStorageResource::~CEnumStorageResource( void )
{
    ULONG   idx;

    if ( m_pIWbemServices != NULL )
    {
        m_pIWbemServices->Release();
    } // if:

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        //
        //  Sparse array so we need to check for NULL...
        //

        if ( (*m_prgDisks)[ idx ] != NULL )
        {
            ((*m_prgDisks)[ idx ])->Release();
        } // end if: is there a pointer at the index?
    } // for: each index in the array...

    HeapFree( GetProcessHeap(), 0, m_prgDisks );

    SysFreeString( m_bstrBootDevice );
    SysFreeString( m_bstrSystemDevice );
    SysFreeString( m_bstrBootLogicalDisk );
    SysFreeString( m_bstrSystemLogicalDisk );
    SysFreeString( m_bstrSystemWMIDeviceID );
    SysFreeString( m_bstrCrashDumpLogicalDisk );

} //*** CEnumStorageResource::~CEnumStorageResource


//////////////////////////////////////////////////////////////////////////////
// CEnumStorageResource -- IClusCfgInitialize interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::Initialize
//
//  Description:
//      Initialize this component.
//
//  Arguments:
//      punkCallbackIn
//          Interface on which to query for the IClusCfgCallback interface.
//
//      lcidIn
//          Locale ID.
//
//  Return Value:
//      S_OK            - Success
//      E_POINTER       - Expected pointer argument specified as NULL.
//      E_OUTOFMEMORY   - Error allocating memory.
//      Other HRESULTs.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::Initialize(
      IUnknown *    punkCallbackIn
    , LCID          lcidIn
    )
{
    HRESULT         hr = S_OK;
    IWbemServices * pIWbemServices = NULL;

    //
    // Initialize the base class.
    //

    hr = CMgdClusCfgInit::Initialize( punkCallbackIn, lcidIn );
    if ( FAILED( hr ) )
    {
        //
        //  Base class will log the error if possible.
        //

        goto Cleanup;
    } // if: base classs initialization failed

    //
    // Do custom initialization - get a handle to the WBEM service.
    //

    hr = HrInitializeWbemConnection( &pIWbemServices );
    if ( FAILED( hr ) )
    {
        STATUS_REPORT_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_InitWbem_Enum_StorageResource
                    , IDS_ERROR_WBEM_CONNECTION_FAILURE
                    , IDS_ERROR_WBEM_CONNECTION_FAILURE_REF
                    , hr
                    );
        goto Cleanup;
    } // if: HrInitializeWbemConnection failed

    hr = SetWbemServices( pIWbemServices );
    if ( FAILED( hr ) )
    {
        STATUS_REPORT_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_InitWbem_Enum_StorageResource
                    , IDS_ERROR_WBEM_CONNECTION_FAILURE
                    , IDS_ERROR_WBEM_CONNECTION_FAILURE_REF
                    , hr
                    );
        goto Cleanup;
    } // if: SetWbemServices failed

    hr = HrGetSystemDevice( &m_bstrSystemDevice );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrConvertDeviceVolumeToLogicalDisk( m_bstrSystemDevice, &m_bstrSystemLogicalDisk );
    if ( HRESULT_CODE( hr ) == ERROR_INVALID_FUNCTION )
    {

        //
        // System volume is an EFI volume on IA64 and won't have a logical disk.
        //

        hr = HrConvertDeviceVolumeToWMIDeviceID( m_bstrSystemDevice, &m_bstrSystemWMIDeviceID );
        assert( m_bstrSystemLogicalDisk == NULL );
        assert( m_bstrSystemWMIDeviceID != NULL );
    } // if:

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrGetBootLogicalDisk( &m_bstrBootLogicalDisk );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrIsLogicalDiskNTFS( m_bstrBootLogicalDisk );
    if ( hr == S_FALSE )
    {
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_Boot_Partition_Not_NTFS
                , IDS_WARN_BOOT_PARTITION_NOT_NTFS
                , IDS_WARN_BOOT_PARTITION_NOT_NTFS_REF
                , hr
                );
        hr = S_OK;
    } // if:

    hr = HrGetCrashDumpLogicalDisk( &m_bstrCrashDumpLogicalDisk );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    if ( pIWbemServices != NULL )
    {
        pIWbemServices->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::Initialize


//////////////////////////////////////////////////////////////////////////////
// CEnumStorageResource -- IWMIService interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::SetWbemServices
//
//  Description:
//      Set the WBEM services provider.
//
//  Arguments:
//    IN  IWbemServices  pIWbemServicesIn
//
//  Return Value:
//      S_OK
//          Success
//
//      E_POINTER
//          The pIWbemServicesIn param is NULL.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::SetWbemServices(
    IWbemServices * pIWbemServicesIn
    )
{
    HRESULT hr = S_OK;

    //
    // Make sure required arguments were specified.
    //

    if ( pIWbemServicesIn == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_SetWbemServices_Enum_StorageResource
            , IDS_ERROR_NULL_POINTER
            , IDS_ERROR_NULL_POINTER_REF
            , hr
            );
        goto Cleanup;
    } // if:

    m_pIWbemServices = pIWbemServicesIn;
    m_pIWbemServices->AddRef();

Cleanup:

    return hr;

} //*** CEnumStorageResource::SetWbemServices


//////////////////////////////////////////////////////////////////////////////
// CEnumStorageResource -- IEnumClusCfgManagedResources interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::Next
//
//  Description:
//      Get the next set of objects in the enumeration.
//
//  Arguments:
//      cNumberRequestedIn
//          Number of objects the caller is requesting to be returned.
//
//      rgpManagedResourceInfoOut
//          An array of pointers in which to return the objects from the
//          enumeration.
//
//      pcNumberFetchedOut
//          The number of objects returned in rgpManagedResourceInfoOut.
//
//  Return Value:
//      S_OK
//          The number of objects requested was returned.
//
//      S_FALSE
//          The number of objects requested was NOT returned.
//          pcNumberFetchedOut should be checked to determine the number of
//          objects that were actually returned.
//
//      E_POINTER
//          Required output arguments were not specified.
//
//      Other HRESULTs.
//
//  Remarks:
//
//  This is the entry point were the real work of this enumerator is done.
//  COM enumerators have few entry points so you will need to be careful
//  with loading them.  We have chosen to make this one a lazy load
//  enumerator so the first call to this method will load the data.
//
//  This method is one where you will place the code that know how to
//  find and load your resource (device) type.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::Next(
      ULONG                             cNumberRequestedIn
    , IClusCfgManagedResourceInfo **    rgpManagedResourceInfoOut
    , ULONG *                           pcNumberFetchedOut
    )
{
    HRESULT                         hr = S_FALSE;
    ULONG                           cFetched = 0;
    IClusCfgManagedResourceInfo *   pccsdi;
    IUnknown *                      punk;
    ULONG                           ulStop;

    //
    // Make sure required arguments were specified.
    //

    if ( rgpManagedResourceInfoOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_Next_Enum_StorageResource
            , IDS_ERROR_NULL_POINTER
            , IDS_ERROR_NULL_POINTER_REF
            , hr
            );
        goto Cleanup;
    } // if:

    //
    //  TODO:
    //
    //  Replace the following sample code with code that finds and loads your
    //  resources (device) of your resource type.
    //

    //
    // Load the enumeration if not already done.
    //

    if ( m_fLoadedDevices == FALSE )
    {
        hr = HrLoadEnum();
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if: enumeration not loaded yet

    //
    // Return the number of objects requested by the caller in the
    // caller's pointer array.
    //

    ulStop = min( cNumberRequestedIn, ( m_idxNext - m_idxEnumNext ) );

    for ( hr = S_OK; ( cFetched < ulStop ) && ( m_idxEnumNext < m_idxNext ); m_idxEnumNext++ )
    {
        //
        //  This is a sparse array...
        //

        punk = (*m_prgDisks)[ m_idxEnumNext ];
        if ( punk != NULL )
        {
            hr = punk->TypeSafeQI( IClusCfgManagedResourceInfo, &pccsdi );
            if ( FAILED( hr ) )
            {
                break;
            } // if:

            rgpManagedResourceInfoOut[ cFetched++ ] = pccsdi;
        } // if: entry found in the enumeration
    } // for: each resource to be returned to the caller

    //
    // If a failure occurs, release the objects that have already been added
    // to the caller's pointer array.
    //

    if ( FAILED( hr ) )
    {
        //
        //  Back up the enum index
        //

        m_idxEnumNext -= cFetched;

        while ( cFetched != 0 )
        {
            (rgpManagedResourceInfoOut[ --cFetched ])->Release();
            rgpManagedResourceInfoOut[ cFetched ] = NULL;
        } // for: each pointer in the out array

        goto Cleanup;
    } // if: failure occurred getting objects from the enumeration

    //
    //  If the number returned is less than the number requested then we must
    //  return S_FALSE -- even if we are out of data.  That is the contract
    //  that we have as a COM enumerator...
    //

    if ( cFetched < cNumberRequestedIn )
    {
        hr = S_FALSE;
    } // if:

Cleanup:

    if ( pcNumberFetchedOut != NULL )
    {
        *pcNumberFetchedOut = cFetched;
    } // if:

    return hr;

} //*** CEnumStorageResource::Next


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::Skip
//
//  Description:
//      Skip the specified number of objects in the enumeration.
//
//  Arguments:
//      cNumberToSkipIn - Number of objects to skip.
//
//  Return Value:
//      S_OK        - Operation completed successfully.
//      S_FALSE     - Fewer than the requested number of objects were skipped.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::Skip(
    ULONG cNumberToSkipIn
    )
{
    HRESULT hr = S_OK;

    m_idxEnumNext += cNumberToSkipIn;
    if ( m_idxEnumNext >= m_idxNext )
    {
        //
        //  Could not skip the full amount...  Set the enum index to the end
        //  of the data and return S_FALSE.
        //

        m_idxEnumNext = m_idxNext;
        hr = S_FALSE;
    } // if:

    return hr;

} //*** CEnumStorageResource::Skip


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::Reset
//
//  Description:
//      Reset to the beginning of the enumeration.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - Operation completed successfully.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::Reset( void )
{
    m_idxEnumNext = 0;

    return S_OK;

} //*** CEnumStorageResource::Reset


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::Clone
//
//  Description:
//      Perform a deep copy of the enumeration.
//
//  Arguments:
//      ppEnumClusCfgStorageDevicesOut
//          Pointer to clone of enumeration interface.
//
//  Return Value:
//      S_OK        - Operation completed successfully.
//      E_POINTER   - Required output argument not specified.
//      E_NOTIMPL   - Operation not implemented or supported.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::Clone(
    IEnumClusCfgManagedResources ** ppEnumClusCfgStorageDevicesOut
    )
{
    HRESULT hr = S_OK;

    //
    // Make sure required arguments were specified.
    //

    if ( ppEnumClusCfgStorageDevicesOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_Clone_Enum_StorageResource
            , IDS_ERROR_NULL_POINTER
            , IDS_ERROR_NULL_POINTER_REF
            , hr
            );
        goto Cleanup;
    } // if:

    //
    // TODO: perform a deep copy of the objects in the enumeration.
    //

    hr = E_NOTIMPL;

Cleanup:

    return hr;

} //*** CEnumStorageResource::Clone


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::Count
//
//  Description:
//      Return the count of items in the enumeration.
//
//  Arguments:
//      pnCountOut  - The number of items in the enumeration.
//
//  Return Value:
//      S_OK        - Operation completed successfully.
//      E_POINTER   - Required argument not specified.
//      Other HRESULTs.
//
//  Remarks:
//      This is not a standard COM enumerator method, but it is required of
//      ClusCfg plug in components.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CEnumStorageResource::Count( DWORD * pnCountOut )
{
    HRESULT hr = S_OK;

    //
    // Make sure required arguments were specified.
    //

    if ( pnCountOut == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    //
    // Load the enumeration if not already done.
    //

    if ( m_fLoadedDevices == FALSE )
    {
        hr = HrLoadEnum();
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if:

    //
    // Return the number of items in the enumeration.
    //

    *pnCountOut = m_cDiskCount;

Cleanup:

    return hr;

} //*** CEnumStorageResource::Count


//////////////////////////////////////////////////////////////////////////////
// CEnumStorageResource class -- Private Methods.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrGetDisks
//
//  Description:
//      Load the enumeration.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK            - Operation completed successfully.
//      E_OUTOFMEMORY   - Error allocating memory.
//      Other HRESULTs.
//
//  Remarks:
//      This method is an example of finding and processing physical disks
//      using WMI.  You are not expected to use this in your specific
//      ClusCfg managed resource plug in.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetDisks( void )
{
    HRESULT                 hr = S_OK;
    BSTR                    bstrClass;
    IEnumWbemClassObject *  piewcoDisks = NULL;
    ULONG                   ulReturned;
    IWbemClassObject *      piwcoDisk = NULL;

    //
    // Create the WMI class string for creating the enumeration.
    //

    bstrClass = SysAllocString( L"Win32_DiskDrive" );
    if ( bstrClass == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_HrGetDisks
            , IDS_ERROR_OUTOFMEMORY
            , IDS_ERROR_OUTOFMEMORY_REF
            , hr
            );
        goto Cleanup;
    } // if:

    //
    // Create the enumeration by querying WMI for objects of the specified class.
    //

    hr = m_pIWbemServices->CreateInstanceEnum( bstrClass, WBEM_FLAG_SHALLOW, NULL, &piewcoDisks );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Loop through the enumeration returned from WMI and add objects to our
    // enumeration if they meet our criteria.
    //

    for ( ; ; )
    {
        hr = piewcoDisks->Next( WBEM_INFINITE, 1, &piwcoDisk, &ulReturned );
        if ( ( hr == S_OK ) && ( ulReturned == 1 ) )
        {
            //
            // Log information about this item to the log file.
            //

            hr = HrLogDiskInfo( piwcoDisk );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            //
            // Find out if this is a SCSI disk or not.  Only add the disk
            // if it is a SCSI disk.
            //
            // TODO: Determine if this is valid for your storage resource.
            //

            hr = IsDiskSCSI( piwcoDisk );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if: failed to get SCSI info about disk

            //
            // Create a local copy of the disk info and add it to our array
            // if it is a SCSI disk.
            //

            if ( hr == S_OK )
            {
                hr = HrProcessWMIDiskObject( piwcoDisk );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if: failed to create and add disk to the array
            } // if: disk is SCSI

            piwcoDisk->Release();
            piwcoDisk = NULL;
        } // if: an object was returned
        else if ( ( hr == S_FALSE ) && ( ulReturned == 0 ) )
        {
            hr = S_OK;
            break;
        } // else if: no objects returned
        else
        {
            STATUS_REPORT_STRING_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_WQL_Disk_Qry_Next_Failed
                    , IDS_ERROR_WQL_QRY_NEXT_FAILED
                    , bstrClass
                    , IDS_ERROR_WQL_QRY_NEXT_FAILED_REF
                    , hr
                    );
            goto Cleanup;
        } // else: error getting next object
    } // for: ever

    //
    // Reset the enumeration index to the beginning and indicate that we have
    // loaded the enumeration.
    //

    m_idxEnumNext = 0;
    m_fLoadedDevices = TRUE;

Cleanup:

    if ( piwcoDisk != NULL )
    {
        piwcoDisk->Release();
    } // if:

    if ( piewcoDisks != NULL )
    {
        piewcoDisks->Release();
    } // if:

    SysFreeString( bstrClass );

    return hr;

} //*** CEnumStorageResource::HrGetDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrProcessWMIDiskObject
//
//  Description:
//      Create an CStorageResource object from the passed in WMI disk object
//      and add it to the array of punks.
//
//  Arguments:
//      pDiskIn         - WMI disk to create from.
//
//  Return Value:
//      S_OK            - Operation was successful.
//      E_OUTOFMEMORY   - Error allocating memory.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrProcessWMIDiskObject(
    IWbemClassObject * pDiskIn
    )
{
    assert( m_pIWbemServices != NULL );

    HRESULT             hr = S_FALSE;
    IUnknown *          punk = NULL;
    IWMIObject *        piwo = NULL;
    BOOL                fRetainObject = TRUE;

    //
    // Create an instance of the CStorageResource object.
    //

    hr = CoCreateInstance( CLSID_CStorageResource, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, reinterpret_cast< void ** >( &punk ) );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    assert( punk != NULL );

    //
    // Initialize the newly created object.
    //

    hr = HrSetInitialize( punk, GetCallback(), GetLCID() );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSetWbemServices( punk, m_pIWbemServices );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = punk->TypeSafeQI( IWMIObject, &piwo );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    assert( piwo != NULL );

    hr = piwo->SetWbemObject( pDiskIn, &fRetainObject );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( fRetainObject )
    {
        hr = HrAddObjectToArray( punk );
    } // if:

Cleanup:

    if ( piwo != NULL )
    {
        piwo->Release();
    } // if:

    if ( punk != NULL )
    {
        punk->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::HrProcessWMIDiskObject


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrPruneSystemDisks
//
//  Description:
//      Prune all system disks from the list.  System disks are disks that
//      are booted, are running the OS, have page files, have hibernation
//      files, or have crash dumps on them.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - Operation was successful.
//      Other HRESULTs.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrPruneSystemDisks( void )
{
    assert( m_bstrSystemLogicalDisk != NULL );
    assert( m_bstrBootLogicalDisk != NULL );

    HRESULT                 hr = S_OK;
    ULONG                   idx;
    ULONG                   ulSCSIBus;
    ULONG                   ulSCSIPort;
    IStorageProperties *    piccpdp = NULL;
    IUnknown *              punk = NULL;
    ULONG                   cRemoved = 0;
    ULONG                   cTemp = 0;
    BOOL                    fSystemAndBootTheSame;
    BOOL                    fPruneBus = FALSE;

    //
    //  Minor optimization when the system and boot disk are the same disk.
    //

    fSystemAndBootTheSame =   ( m_bstrSystemLogicalDisk != NULL )
                            ? ( m_bstrBootLogicalDisk[ 0 ] == m_bstrSystemLogicalDisk[ 0 ] )
                            : FALSE;

    //
    //  The system bus is usually not managed.  It is managed when a registry
    //  entry has been made to make it managed.  It is usually done when the
    //  system bus is a storage area network.
    //
    //  NB:
    //      This is only applicable to physical disks.  Your custom resource
    //      type will most likely not care about this.
    //

    hr = HrIsSystemBusManaged();
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    //  If the system bus is not managed then we need to prune the disks on those buses
    //  that contain system, boot, and pagefile disks.
    //

    fPruneBus = ( hr == S_FALSE );

    //
    //  Prune the disks on the system buses.  If the system disks are IDE they won't
    //  be in the list.
    //

    //
    //  Find the boot disk(s).  Could be a volume with more than one disk.
    //

    for ( ; ; )
    {
        hr = HrFindDiskWithLogicalDisk( m_bstrBootLogicalDisk[ 0 ], &idx );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        if ( hr == S_OK )
        {

            //
            //  Should we prune the whole bus, or just the boot disk itself?
            //  Typically we need to prune the entire bus, but when the
            //  special registry entry tells us not to then we only prune the
            //  spindles themselves.
            //

            if ( fPruneBus )
            {
                hr = HrGetSCSIInfo( idx, &ulSCSIBus, &ulSCSIPort );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                //
                //  Tell the UI that we are pruning the boot disk bus...
                //

                STATUS_REPORT( TASKID_Major_Find_Devices, TASKID_Minor_Pruning_Boot_Disk_Bus, IDS_INFO_PRUNING_BOOTDISK_BUS, hr );
                hr = HrPruneDisks(
                                  ulSCSIBus
                                , ulSCSIPort
                                , &TASKID_Minor_Pruning_Boot_Disk_Bus
                                , IDS_INFO_BOOTDISK_PRUNED
                                , IDS_INFO_BOOTDISK_PRUNED_REF
                                , &cTemp
                                );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                cRemoved += cTemp;
            } // if: prune all disks from the boot disk SCSI bus
            else
            {
                RemoveDiskFromArray( idx );
                cRemoved++;
            } // else: only prune boot disk

            continue;
        } // if:

        break;
    } // for: each volume in the logical disk

    //
    //  Prune the system disk bus if it is not the same as the boot disk bus.
    //

    if ( fSystemAndBootTheSame == FALSE )
    {
        if ( m_bstrSystemLogicalDisk != NULL )
        {
            assert( m_bstrSystemWMIDeviceID == NULL );
            hr = HrFindDiskWithLogicalDisk( m_bstrSystemLogicalDisk[ 0 ], &idx );
        } // if:
        else
        {
            assert( m_bstrSystemLogicalDisk == NULL );
            hr = HrFindDiskWithWMIDeviceID( m_bstrSystemWMIDeviceID, &idx );
        } // else:

        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        if ( hr == S_OK )
        {
            //
            //  Should we prune the whole bus, or just the system disk itself?
            //

            if ( fPruneBus )
            {
                hr = HrGetSCSIInfo( idx, &ulSCSIBus, &ulSCSIPort );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                //
                //  Tell the UI that we are pruning the system disk bus...
                //

                STATUS_REPORT( TASKID_Major_Find_Devices, TASKID_Minor_Pruning_System_Disk_Bus, IDS_INFO_PRUNING_SYSTEMDISK_BUS, hr );
                hr = HrPruneDisks(
                                  ulSCSIBus
                                , ulSCSIPort
                                , &TASKID_Minor_Pruning_System_Disk_Bus
                                , IDS_INFO_SYSTEMDISK_PRUNED
                                , IDS_INFO_SYSTEMDISK_PRUNED_REF
                                , &cTemp
                                );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                cRemoved += cTemp;
            } // if: prune system disk bus
            else
            {
                RemoveDiskFromArray( idx );
                cRemoved++;
            } // else: only prune the system disk
        } // if:
    } // if:

    //
    //  Now prune the busses that have page file disks on them.
    //

    hr = HrPrunePageFileDiskBuses( fPruneBus, &cTemp );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cRemoved += cTemp;

    //
    //  Now prune the bus that has a crash dump file disk.
    //

    hr = HrPruneCrashDumpBus( fPruneBus, &cTemp );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cRemoved += cTemp;

    //
    //  Now prune the off any remaining dynamic disks.  Dynamic disks cannot
    //  be physical disks.  There may be a different plug in component that
    //  managed those disks.
    //

    hr = HrPruneDynamicDisks( &cTemp );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cRemoved += cTemp;

    //
    //  Now prune the off any remaining GPT disks.  GPT disks are not
    //  compatible with clustering at this time.
    //

    hr = HrPruneGPTDisks( &cTemp );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cRemoved += cTemp;

    //
    //  Last ditch effort to properly set the managed state of the remaining disks.
    //

    for ( idx = 0; ( cRemoved < m_idxNext ) && ( idx < m_idxNext ); idx++ )
    {
        //
        //  Sparse array.
        //

        punk = (*m_prgDisks)[ idx ];    // don't ref
        if ( punk != NULL )
        {
            hr = punk->TypeSafeQI( IStorageProperties, &piccpdp );
            if ( FAILED( hr ) )
            {
                LOG_STATUS_REPORT( L"Could not query for the IStorageProperties interface.", hr );
                goto Cleanup;
            } // if:

            //
            //  Give the disk a chance to figure out for itself if it should be managed.
            //

            hr = piccpdp->CanBeManaged();
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            piccpdp->Release();
            piccpdp = NULL;
        } // if: index has a pointer
    } // for: each index in the array

    //
    //  Minor optimization.  If we removed all of the elements reset the enum next to 0.
    //

    if ( cRemoved == m_idxNext )
    {
        m_idxNext = 0;
    } // if:

    hr = S_OK;
    goto Cleanup;

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::HrPruneSystemDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::IsDiskSCSI
//
//  Description:
//      Determine if this disk is on a SCSI bus.
//
//  Arguments:
//      pDiskIn     - WBEM class object for the disk to query.
//
//  Return Value:
//      S_OK        - Disk is SCSI.
//      S_FALSE     - Disk is not SCSI.
//      Other HRESULTs.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::IsDiskSCSI(
    IWbemClassObject * pDiskIn
    )
{
    assert( pDiskIn != NULL );

    HRESULT hr;
    VARIANT var;

    VariantInit( &var );

    hr = HrGetWMIProperty( pDiskIn, L"InterfaceType", VT_BSTR, &var );
    if ( SUCCEEDED( hr ) )
    {
        if ( ( NStringCompareW( L"SCSI", RTL_NUMBER_OF( L"SCSI" ), var.bstrVal, SysStringLen( var.bstrVal ) ) == 0 ) )
        {
            hr = S_OK;
        } // if:
        else
        {
            hr = S_FALSE;
        } // else:
    } // if:

    VariantClear( &var );

    return hr;

} //*** CEnumStorageResource::IsDiskSCSI


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrAddObjectToArray
//
//  Description:
//      Add the passed in disk to the array of punks that holds the disks.
//
//  Arguments:
//      punkIn
//
//  Return Value:
//      S_OK            - Operation completed successfully.
//      E_OUTOFMEMORY   - Error allocating memory.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrAddObjectToArray(
    IUnknown * punkIn
    )
{
    assert( punkIn != NULL );

    HRESULT     hr = S_OK;
    IUnknown *  ((*prgpunks)[]) = NULL;

    //
    //  Grow the array to hold the passed in object.
    //

    prgpunks = (IUnknown *((*)[])) HEAPREALLOC( m_prgDisks, sizeof( IUnknown * ) * ( m_idxNext + 1 ), HEAP_ZERO_MEMORY );
    if ( prgpunks == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF( TASKID_Major_Find_Devices, TASKID_Minor_HrAddObjectToArray, IDS_ERROR_OUTOFMEMORY, IDS_ERROR_OUTOFMEMORY_REF, hr );
        goto Cleanup;
    } // if:

    m_prgDisks = prgpunks;

    (*m_prgDisks)[ m_idxNext++ ] = punkIn;
    punkIn->AddRef();
    m_cDiskCount += 1;

    goto Cleanup;

Cleanup:

    return hr;

} //*** CEnumStorageResource::HrAddObjectToArray


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrFixupDisks
//
//  Description:
//      Tweak the disks to better reflect how they are managed by this node.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrFixupDisks( void )
{
    HRESULT hr = S_OK;

    //
    //  If the cluster service is running then load any managed disk
    //  resources that we own.
    //

    hr = HrIsClusterServiceRunning();
    if ( hr == S_OK )
    {
        hr = HrEnumNodeResources( GetNodeName() );
    } // if: the cluster service is running on this node
    else if ( hr == S_FALSE )
    {
        hr = S_OK;
    } // else: cluster service is not running on this node

    return hr;

} //*** CEnumStorageResource::HrFixupDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrNodeResourceCallback
//
//  Description:
//      Called by CClusterUtils::HrEnumNodeResources() when it finds a
//      resource for this node.
//
//  Arguments:
//      hResourceIn
//          A physical disk resource that is owned by this node.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrNodeResourceCallback(
    HRESOURCE hResourceIn
    )
{
    HRESULT                 hr = S_OK;
    CLUS_SCSI_ADDRESS       csa;
    DWORD                   dwSignature;
    BOOL                    fIsQuorum;
    BSTR                    bstrResourceName = NULL;

    //
    //  NB:
    //
    //  Since this example is for physical disks we have used that string here.
    //  In your own plug in component you wll use your resource type here.
    //

    if ( ResUtilResourceTypesEqual( GetResTypeName(), hResourceIn ) == FALSE )
    {
        //
        //  If this resource is not a managed disk then we simply want to
        //  skip it.
        //

        hr = S_FALSE;
        goto Cleanup;
    } // if:

    hr = HrIsCoreResource( hResourceIn );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    fIsQuorum = ( hr == S_OK );

    hr = HrGetClusterDiskInfo( hResourceIn, &csa, &dwSignature );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrGetClusterProperties( hResourceIn, &bstrResourceName );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSetThisDiskToBeManaged( csa.TargetId, csa.Lun, fIsQuorum, bstrResourceName, dwSignature );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    goto Cleanup;

Cleanup:

    SysFreeString( bstrResourceName );

    return hr;


} //*** CEnumStorageResource::HrNodeResourceCallback


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrGetClusterDiskInfo
//
//  Description:
//
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetClusterDiskInfo(
      HRESOURCE             hResourceIn
    , CLUS_SCSI_ADDRESS *   pcsaOut
    , DWORD *               pdwSignatureOut
    )
{
    HRESULT                 hr = S_OK;
    DWORD                   sc;
    CClusPropValueList      cpvl;
    CLUSPROP_BUFFER_HELPER  cbhValue = { NULL };

    sc = cpvl.ScGetResourceValueList( hResourceIn, CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    sc = cpvl.ScMoveToFirstValue();
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:


    for ( ; ; )
    {
        cbhValue = cpvl;

        switch ( cbhValue.pSyntax->dw )
        {
            case CLUSPROP_SYNTAX_PARTITION_INFO :
            {
                break;
            } // case: CLUSPROP_SYNTAX_PARTITION_INFO

            case CLUSPROP_SYNTAX_DISK_SIGNATURE :
            {
                *pdwSignatureOut = cbhValue.pDiskSignatureValue->dw;
                break;
            } // case: CLUSPROP_SYNTAX_DISK_SIGNATURE

            case CLUSPROP_SYNTAX_SCSI_ADDRESS :
            {
                pcsaOut->dw = cbhValue.pScsiAddressValue->dw;
                break;
            } // case: CLUSPROP_SYNTAXscSI_ADDRESS

            case CLUSPROP_SYNTAX_DISK_NUMBER :
            {
                break;
            } // case: CLUSPROP_SYNTAX_DISK_NUMBER

        } // switch:

        sc = cpvl.ScMoveToNextValue();
        if ( sc == ERROR_SUCCESS )
        {
            continue;
        } // if:

        if ( sc == ERROR_NO_MORE_ITEMS )
        {
            break;
        } // if: error occurred moving to the next value

        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // for: each value in the value list

Cleanup:

    return hr;

} //*** CEnumStorageResource::HrGetClusterDiskInfo


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrSetThisDiskToBeManaged
//
//  Description:
//
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrSetThisDiskToBeManaged(
      ULONG ulSCSITidIn
    , ULONG ulSCSILunIn
    , BOOL  fIsQuorumIn
    , BSTR  bstrResourceNameIn
    , DWORD dwSignatureIn
    )
{
    HRESULT                         hr = S_OK;
    ULONG                           idx;
    IUnknown *                      punk = NULL;
    IClusCfgManagedResourceInfo *   piccmri = NULL;
    WCHAR                           sz[ 64 ];
    BSTR                            bstrUID = NULL;
    DWORD                           dwSignature;
    IStorageProperties *            piccpdp = NULL;

    UNREFERENCED_PARAMETER( dwSignatureIn );

    hr = StringCchPrintfW( sz, RTL_NUMBER_OF( sz ), L"%s SCSI Tid %ld, SCSI Lun %ld", GetDisplayName(), ulSCSITidIn, ulSCSILunIn );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    //  Find the disk that has the passes in TID and Lun and set it
    //  to be managed.
    //

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        punk = (*m_prgDisks)[ idx ];                                                        // don't ref
        if ( punk != NULL )
        {
            hr = punk->TypeSafeQI( IClusCfgManagedResourceInfo, &piccmri );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccmri->GetUID( &bstrUID );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( NIStringCompareW( bstrUID, SysStringLen( bstrUID ), sz, RTL_NUMBER_OF( sz ) ) == 0 )
            {
                hr = piccmri->TypeSafeQI( IStorageProperties, &piccpdp );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                hr = piccpdp->HrGetSignature( &dwSignature );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                hr = piccpdp->HrSetFriendlyName( bstrResourceNameIn );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                piccpdp->Release();
                piccpdp = NULL;

                //
                //  May want to do more with this later...
                //

                assert( dwSignatureIn == dwSignature );

                hr = piccmri->SetManaged( TRUE );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                hr = piccmri->SetQuorumResource( fIsQuorumIn );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:

                break;
            } // if:

            SysFreeString( bstrUID );
            bstrUID = NULL;
            piccmri->Release();
            piccmri = NULL;
        } // if:
    } // for:

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    if ( piccmri != NULL )
    {
        piccmri->Release();
    } // if:

    SysFreeString( bstrUID );

    return hr;

} //*** CEnumStorageResource::HrSetThisDiskToBeManaged


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrFindDiskWithLogicalDisk
//
//  Description:
//      Find the disk with the passed in logical disk ID.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.  Found the disk.
//
//      S_FALSE
//          Success.  Did not find the disk.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrFindDiskWithLogicalDisk(
    WCHAR   cLogicalDiskIn,
    ULONG * pidxDiskOut
    )
{
    assert( pidxDiskOut != NULL );

    HRESULT                             hr = S_OK;
    IStorageProperties *                piccpdp = NULL;
    ULONG                               idx;
    bool                                fFoundIt = false;
    IUnknown *                          punk;

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        punk = (*m_prgDisks)[ idx ];    // don't ref
        if ( punk != NULL )
        {
            hr = punk->TypeSafeQI( IStorageProperties, &piccpdp );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccpdp->IsThisLogicalDisk( cLogicalDiskIn );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( hr == S_OK )
            {
                fFoundIt = true;
                break;
            } // if:

            piccpdp->Release();
            piccpdp = NULL;
        } // if:
    } // for:

    if ( fFoundIt == FALSE )
    {
        hr = S_FALSE;
    } // if:

    if ( pidxDiskOut != NULL )
    {
        *pidxDiskOut = idx;
    } // if:

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::HrFindDiskWithLogicalDisk


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrGetSCSIInfo
//
//  Description:
//      Get the SCSI info for the disk at the passed in index.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetSCSIInfo(
    ULONG   idxDiskIn,
    ULONG * pulSCSIBusOut,
    ULONG * pulSCSIPortOut
    )
{
    assert( pulSCSIBusOut != NULL );
    assert( pulSCSIPortOut != NULL );

    HRESULT                             hr = S_OK;
    IStorageProperties *                piccpdp = NULL;

    hr = ((*m_prgDisks)[ idxDiskIn ])->TypeSafeQI( IStorageProperties, &piccpdp );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = piccpdp->HrGetSCSIBus( pulSCSIBusOut );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = piccpdp->HrGetSCSIPort( pulSCSIPortOut );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::HrGetSCSIInfo


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrPruneDisks
//
//  Description:
//      Get the SCSI info for the disk at the passed in index.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrPruneDisks(
      ULONG         ulSCSIBusIn
    , ULONG         ulSCSIPortIn
    , const GUID *  pcguidMajorIdIn
    , int           nMsgIdIn
    , int           nRefIdIn
    , ULONG *       pulRemovedOut
    )
{
    assert( pulRemovedOut != NULL );

    HRESULT                             hr = S_OK;
    IStorageProperties *                piccpdp = NULL;
    ULONG                               idx;
    IUnknown *                          punk;
    ULONG                               ulSCSIBus;
    ULONG                               ulSCSIPort;
    ULONG                               cRemoved = 0;

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        punk = (*m_prgDisks)[ idx ];                                                        // don't ref
        if ( punk != NULL )
        {
            hr = punk->TypeSafeQI( IStorageProperties, &piccpdp );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccpdp->HrGetSCSIBus( &ulSCSIBus );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccpdp->HrGetSCSIPort( &ulSCSIPort );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( ( ulSCSIBusIn == ulSCSIBus ) && ( ulSCSIPortIn == ulSCSIPort ) )
            {
                BSTR                            bstr = NULL;
                IClusCfgManagedResourceInfo *   piccmri = NULL;
                HRESULT                         hrTemp;
                CLSID   clsidMinorId;

                hrTemp = CoCreateGuid( &clsidMinorId );
                if ( FAILED( hrTemp ) )
                {
                    LOG_STATUS_REPORT( L"[MyStorageResource] Could not create a guid for a pruning disk minor task ID", S_OK );
                    clsidMinorId = IID_NULL;
                } // if:

                LogPrunedDisk( punk, ulSCSIBusIn, ulSCSIPortIn );

                ((*m_prgDisks)[ idx ])->TypeSafeQI( IClusCfgManagedResourceInfo, &piccmri );
                piccmri->GetName( &bstr );
                if ( piccmri != NULL )
                {
                    piccmri->Release();
                } // if:

                STATUS_REPORT_STRING_REF( *pcguidMajorIdIn, clsidMinorId, nMsgIdIn, bstr != NULL ? bstr : L"????", nRefIdIn, hr );
                RemoveDiskFromArray( idx );
                cRemoved++;
                SysFreeString( bstr );
            } // if:

            piccpdp->Release();
            piccpdp = NULL;
        } // if:
    } // for:

    if ( pulRemovedOut != NULL )
    {
        *pulRemovedOut = cRemoved;
    } // if:

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::HrPruneDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:LogPrunedDisk
//
//  Description:
//      Get the SCSI info for the disk at the passed in index.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
void
CEnumStorageResource::LogPrunedDisk(
    IUnknown *  punkIn,
    ULONG       ulSCSIBusIn,
    ULONG       ulSCSIPortIn
    )
{
    assert( punkIn != NULL );

    HRESULT                             hr = S_OK;
    IClusCfgManagedResourceInfo *       piccmri = NULL;
    IStorageProperties *                piccpdp = NULL;
    BSTR                                bstrName = NULL;
    BSTR                                bstrUID = NULL;
    BSTR                                bstr = NULL;

    hr = punkIn->TypeSafeQI( IClusCfgManagedResourceInfo, &piccmri );
    if ( SUCCEEDED( hr ) )
    {
        hr = piccmri->GetUID( &bstrUID );
        piccmri->Release();
    } // if:

    if ( FAILED( hr ) )
    {
        bstrUID = SysAllocString( L"<Unknown>" );
    } // if:

    hr = punkIn->TypeSafeQI( IStorageProperties, &piccpdp );
    if ( SUCCEEDED( hr ) )
    {
        hr = piccpdp->HrGetDeviceID( &bstrName );
        piccpdp->Release();
    } // if:

    if ( FAILED( hr ) )
    {
        bstrName = SysAllocString( L"<Unknown>" );
    } // if:

    hr = HrFormatStringIntoBSTR(
                  L"[MyStorageResource] Pruning SCSI disk '%1!ws!', on Bus '%2!d!' and Port '%3!d!'; at '%4!ws!'"
                , &bstr
                , bstrName
                , ulSCSIBusIn
                , ulSCSIPortIn
                , bstrUID
                );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    LOG_STATUS_REPORT( bstr, hr );

Cleanup:

    SysFreeString( bstrName );
    SysFreeString( bstrUID );
    SysFreeString( bstr );

} //*** CEnumStorageResource::LogPrunedDisk


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrIsLogicalDiskNTFS
//
//  Description:
//      Is the passed in logical disk NTFS?
//
//  Arguments:
//      bstrLogicalDiskIn
//
//  Return Value:
//      S_OK            - The disk is NTFS.
//      S_FALSE         - The disk is not NTFS.
//      E_OUTOFMEMORY   - Error allocating memory.
//      Other HRESULTs.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrIsLogicalDiskNTFS( BSTR bstrLogicalDiskIn )
{
    assert( bstrLogicalDiskIn != NULL );

    HRESULT             hr = S_OK;
    IWbemClassObject *  pLogicalDisk = NULL;
    BSTR                bstrPath = NULL;
    WCHAR               sz[ 64 ];
    VARIANT             var;
    size_t              cch;

    VariantInit( &var );

    cch = wcslen( bstrLogicalDiskIn );
    if ( cch > 3 )
    {
        hr = E_INVALIDARG;
        STATUS_REPORT_REF( TASKID_Major_Find_Devices, TASKID_Minor_HrIsLogicalDiskNTFS_InvalidArg, IDS_ERROR_INVALIDARG, IDS_ERROR_INVALIDARG_REF, hr );
        goto Cleanup;
    } // if:

    //
    //  truncate off any trailing \'s
    //
    if ( bstrLogicalDiskIn[ cch - 1 ] == L'\\' )
    {
        bstrLogicalDiskIn[ cch - 1 ] = '\0';
    } // if:

    //
    //  If we have just the logical disk without the trailing colon...
    //
    if ( wcslen( bstrLogicalDiskIn ) == 1 )
    {
        hr = StringCchPrintfW( sz, RTL_NUMBER_OF( sz ), L"Win32_LogicalDisk.DeviceID=\"%ws:\"", bstrLogicalDiskIn );
    } // if:
    else
    {
        hr = StringCchPrintfW( sz, RTL_NUMBER_OF( sz ), L"Win32_LogicalDisk.DeviceID=\"%ws\"", bstrLogicalDiskIn );
    } // else:

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    bstrPath = SysAllocString( sz );
    if ( bstrPath == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF( TASKID_Major_Find_Devices, TASKID_Minor_HrIsLogicalDiskNTFS, IDS_ERROR_OUTOFMEMORY, IDS_ERROR_OUTOFMEMORY_REF, hr );
    } // if:

    hr = m_pIWbemServices->GetObject( bstrPath, WBEM_FLAG_RETURN_WBEM_COMPLETE, NULL, &pLogicalDisk, NULL );
    if ( FAILED( hr ) )
    {
        STATUS_REPORT_STRING_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_WMI_Get_LogicalDisk_Failed
                , IDS_ERROR_WMI_GET_LOGICALDISK_FAILED
                , bstrLogicalDiskIn
                , IDS_ERROR_WMI_GET_LOGICALDISK_FAILED_REF
                , hr
                );
        goto Cleanup;
    } // if:

    hr = HrGetWMIProperty( pLogicalDisk, L"FileSystem", VT_BSTR, &var );
    if (FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    CharUpper( var.bstrVal );

    if ( NStringCompareW( var.bstrVal, SysStringLen( var.bstrVal ), L"NTFS", RTL_NUMBER_OF( L"NTFS" ) ) != 0 )
    {
        hr = S_FALSE;
    } // if:

Cleanup:

    if ( pLogicalDisk != NULL )
    {
        pLogicalDisk->Release();
    } // if:

    VariantClear( &var );

    SysFreeString( bstrPath );

    return hr;

} //*** CEnumStorageResource::HrIsLogicalDiskNTFS


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrLogDiskInfo
//
//  Description:
//      Write the info about this disk into the log.
//
//  Arguments:
//      pDiskIn
//
//  Return Value:
//      S_OK
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrLogDiskInfo( IWbemClassObject * pDiskIn )
{
    assert( pDiskIn != NULL );

    HRESULT hr = S_OK;
    VARIANT varDeviceID;
    VARIANT varSCSIBus;
    VARIANT varSCSIPort;
    VARIANT varSCSILun;
    VARIANT varSCSITid;
    BSTR    bstr = NULL;

    VariantInit( &varDeviceID );
    VariantInit( &varSCSIBus );
    VariantInit( &varSCSIPort );
    VariantInit( &varSCSILun );
    VariantInit( &varSCSITid );

    hr = HrGetWMIProperty( pDiskIn, L"DeviceID", VT_BSTR, &varDeviceID );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = IsDiskSCSI( pDiskIn );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Disk is SCSI...
    //
    if ( hr == S_OK )
    {
        hr = HrGetWMIProperty( pDiskIn, L"SCSIBus", VT_I4, &varSCSIBus );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrGetWMIProperty( pDiskIn, L"SCSITargetId", VT_I4, &varSCSITid );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrGetWMIProperty( pDiskIn, L"SCSILogicalUnit", VT_I4, &varSCSILun );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrGetWMIProperty( pDiskIn, L"SCSIPort", VT_I4, &varSCSIPort );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrFormatStringIntoBSTR(
                      L"[MyStorageResource] Found SCSI disk '%1!ws!' on Bus '%2!d!' and Port '%3!d!'; at TID '%4!d!' and LUN '%5!d!'"
                    , &bstr
                    , varDeviceID.bstrVal
                    , varSCSIBus.iVal
                    , varSCSIPort.iVal
                    , varSCSITid.iVal
                    , varSCSILun.iVal
                    );

        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        LOG_STATUS_REPORT( bstr, hr );
    } // if:
    else
    {
        HRESULT hrTemp;
        CLSID   clsidMinorId;

        hrTemp = CoCreateGuid( &clsidMinorId );
        if ( FAILED( hrTemp ) )
        {
            LOG_STATUS_REPORT( L"[MyStorageResource] Could not create a guid for a non-scsi disk minor task ID", S_OK );
            clsidMinorId = IID_NULL;
        } // if:

        //
        //  Reset hr to S_OK since we don't want a yellow bang in the UI.  Finding non-scsi disks is expected
        //  and should cause as little concern as possible.
        //
        hr = S_OK;
        STATUS_REPORT_REF( TASKID_Major_Find_Devices, TASKID_Minor_Non_SCSI_Disks, IDS_INFO_NON_SCSI_DISKS, IDS_INFO_NON_SCSI_DISKS_REF, hr );
        STATUS_REPORT_STRING_REF( TASKID_Minor_Non_SCSI_Disks, clsidMinorId, IDS_ERROR_FOUND_NON_SCSI_DISK, varDeviceID.bstrVal, IDS_ERROR_FOUND_NON_SCSI_DISK_REF, hr );
    } // else:

Cleanup:

    VariantClear( &varDeviceID );
    VariantClear( &varSCSIBus );
    VariantClear( &varSCSIPort );
    VariantClear( &varSCSILun );
    VariantClear( &varSCSITid );

    SysFreeString( bstr );

    return hr;

} //*** CEnumStorageResource::HrLogDiskInfo


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrFindDiskWithWMIDeviceID
//
//  Description:
//      Find the disk with the passed in WMI device ID.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.  Found the disk.
//
//      S_FALSE
//          Success.  Did not find the disk.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrFindDiskWithWMIDeviceID(
    BSTR    bstrWMIDeviceIDIn,
    ULONG * pidxDiskOut
    )
{
    assert( pidxDiskOut != NULL );

    HRESULT                             hr = S_OK;
    IStorageProperties *                piccpdp = NULL;
    ULONG                               idx;
    bool                                fFoundIt = false;
    IUnknown *                          punk;
    BSTR                                bstrDeviceID = NULL;

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        punk = (*m_prgDisks)[ idx ];    // don't ref
        if ( punk != NULL )
        {
            hr = punk->TypeSafeQI( IStorageProperties, &piccpdp );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccpdp->HrGetDeviceID( &bstrDeviceID );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( NBSTRCompareW( bstrWMIDeviceIDIn, bstrDeviceID ) == 0 )
            {
                fFoundIt = true;
                break;
            } // if:

            piccpdp->Release();
            piccpdp = NULL;

            SysFreeString( bstrDeviceID );
            bstrDeviceID = NULL;
        } // if:
    } // for:

    if ( fFoundIt == FALSE )
    {
        hr = S_FALSE;
    } // if:

    if ( pidxDiskOut != NULL )
    {
        *pidxDiskOut = idx;
    } // if:

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    SysFreeString( bstrDeviceID );

    return hr;

} //*** CEnumStorageResource::HrFindDiskWithWMIDeviceID


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrIsSystemBusManaged
//
//  Description:
//      Is the system bus managed by the cluster service?
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.  The system bus is managed.
//
//      S_FALSE
//          Success.  The system bus is not managed.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrIsSystemBusManaged( void )
{
    HRESULT hr = S_FALSE;
    DWORD   sc;
    HKEY    hKey = NULL;
    DWORD   dwData;
    DWORD   cbData = sizeof( dwData );
    DWORD   dwType;

    sc = RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"SYSTEM\\CURRENTCONTROLSET\\SERVICES\\ClusSvc\\Parameters", 0, KEY_READ, &hKey );
    if ( sc == ERROR_FILE_NOT_FOUND )
    {
        goto Cleanup;       // not yet a cluster node.  Return S_FALSE.
    } // if:

    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] RegOpenKeyEx() failed.", hr );
        goto Cleanup;
    } // if:

    sc = RegQueryValueEx( hKey, L"ManageDisksOnSystemBuses", NULL, &dwType, (LPBYTE) &dwData, &cbData );
    if ( sc == ERROR_FILE_NOT_FOUND )
    {
        goto Cleanup;       // value not found.  Return S_FALSE.
    } // if:

    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] RegQueryValueEx() failed.", hr );
        goto Cleanup;
    } // if:

    if (dwType != REG_DWORD)
    {
        HRESULT hrTemp = S_OK;
        hr = HRESULT_FROM_WIN32( ERROR_DATATYPE_MISMATCH );
        LOG_STATUS_REPORT_STRING( L"[MyStorageResource] RegQueryValueEx() invalid data type %1!d!.", dwType, hrTemp );
    }
    else if ( dwData > 0)
    {
        hr = S_OK;
    } // if:

Cleanup:

    if ( hKey != NULL )
    {
        RegCloseKey( hKey );
    } // if:

    return hr;

} //*** CEnumStorageResource::HrIsSystemBusManaged


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource:HrGetClusterProperties
//
//  Description:
//      Return the asked for cluster properties.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetClusterProperties(
      HRESOURCE hResourceIn
    , BSTR *    pbstrResourceNameOut
    )
{
    assert( hResourceIn != NULL );
    assert( pbstrResourceNameOut != NULL );

    HRESULT                 hr = S_OK;
    DWORD                   sc;
    DWORD                   cbBuffer;
    WCHAR *                 pwszBuffer = NULL;

    cbBuffer = 0;
    sc = ClusterResourceControl(
                        hResourceIn,
                        NULL,
                        CLUSCTL_RESOURCE_GET_NAME,
                        NULL,
                        NULL,
                        NULL,
                        cbBuffer,
                        &cbBuffer
                        );

    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    }

    // cbBuffer contains the byte count, not the char count.
    pwszBuffer = new WCHAR[(cbBuffer/sizeof(WCHAR))+1];

    if ( pwszBuffer == NULL )
    {
        hr = ERROR_OUTOFMEMORY;
        goto Cleanup;
    }

    sc = ClusterResourceControl(
                        hResourceIn,
                        NULL,
                        CLUSCTL_RESOURCE_GET_NAME,
                        NULL,
                        NULL,
                        pwszBuffer,
                        cbBuffer,
                        &cbBuffer
                        );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    }

    if ( wcslen( pwszBuffer ) == 0 )
    {
        LOG_STATUS_REPORT_STRING( L"The Name of a %1!ws! resource was empty!", GetResTypeName(), hr );
    }

    *pbstrResourceNameOut = SysAllocString( pwszBuffer );

    hr = S_OK;

Cleanup:

    delete [] pwszBuffer;

    return hr;

} //*** CEnumStorageResource::HrGetClusterProperties


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::RemoveDiskFromArray
//
//  Description:
//      Release the disk at the specified index in the array and decrease the disk count.
//
//  Arguments:
//      idxDiskIn - the index of the disk to remove; must be less than the array size.
//
//  Return Value:
//      None.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
void
CEnumStorageResource::RemoveDiskFromArray(
    ULONG idxDiskIn
    )
{
    assert( idxDiskIn < m_idxNext );

    ((*m_prgDisks)[ idxDiskIn ])->Release();
    (*m_prgDisks)[ idxDiskIn ] = NULL;

    m_cDiskCount -= 1;

} //*** CEnumStorageResource::RemoveDiskFromArray


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrLoadEnum
//
//  Description:
//      Load the enum and filter out any devices that don't belong.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULT errors.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrLoadEnum( void )
{
    HRESULT hr = S_OK;

    hr = HrGetDisks();
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrPruneSystemDisks();
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSortDisksByIndex();
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrIsNodeClustered();
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( hr == S_OK )
    {
        hr = HrFixupDisks();
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if:

    hr = S_OK;  // could have been S_FALSE

Cleanup:

    return hr;

} //*** CEnumStorageResource::HrLoadEnum


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrSortDisksByIndex
//
//  Description:
//      Sort a (possibly sparse) array of pointers to disk objects by their
//      WMI "Index" property.
//
//  Arguments:
//      ppunkDisksIn
//          A pointer to an array of (possibly null) IUnknown pointers to
//          objects that implement the IStorageProperties interface.
//
//      cArraySizeIn
//          The total number of pointers in the array, including NULLs.
//
//  Return Value:
//      S_OK            - Operation completed successfully.
//      E_OUTOFMEMORY   - Error allocating memory.
//      Other HRESULTs.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrSortDisksByIndex( void )
{
    HRESULT         hr = S_OK;
    SIndexedDisk *  prgIndexedDisks = NULL;
    size_t          idxCurrentDisk = 0;
    size_t          idxSortedDisk = 0;
    size_t          cDisks = 0;

    //
    //  Count the number of non-null pointers in the array
    //

    for ( idxCurrentDisk = 0; idxCurrentDisk < m_idxNext; ++idxCurrentDisk )
    {
        if ( (*m_prgDisks)[ idxCurrentDisk ] != NULL )
        {
            cDisks += 1;
        } // if:
    } // for:

    if ( cDisks < 2 ) // no sorting to do; also avoid calling new[] with zero array size
    {
        goto Cleanup;
    } // if:

    //
    //  Make a compact array of indexed disks
    //

    prgIndexedDisks = new SIndexedDisk[ cDisks ];
    if ( prgIndexedDisks == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    //
    //  Initialize the array of indexed disks
    //

    for ( idxCurrentDisk = 0; idxCurrentDisk < m_idxNext; ++idxCurrentDisk )
    {
        if ( (*m_prgDisks)[ idxCurrentDisk ] != NULL )
        {
            hr = prgIndexedDisks[ idxSortedDisk ].HrInit( (*m_prgDisks)[ idxCurrentDisk ] );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            idxSortedDisk += 1;
        } // if current disk pointer in original array is not null
    } // for each disk pointer in the original array

    InsertionSort( prgIndexedDisks, cDisks, SIndexedDiskLessThan() );

    //
    //  Copy the sorted pointers back into the original array, padding extra
    //  space with nulls
    //

    for ( idxCurrentDisk = 0; idxCurrentDisk < m_idxNext; ++idxCurrentDisk)
    {
        if ( idxCurrentDisk < cDisks)
        {
            (*m_prgDisks)[ idxCurrentDisk ] = prgIndexedDisks[ idxCurrentDisk ].punkDisk;
        } // if:
        else
        {
            (*m_prgDisks)[ idxCurrentDisk ] = NULL;
        } // else:
    } // for each slot in the original array

Cleanup:

    delete [] prgIndexedDisks;

    return hr;

} //*** CEnumStorageResource::HrSortDisksByIndex


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrPrunePageFileDiskBuses
//
//  Description:
//      Prune from the list of disks those that have pagefiles on them and
//      the other disks on those same SCSI busses.
//
//  Arguments:
//      fPruneBusIn
//
//      pcPrunedInout
//
//  Return Value:
//      S_OK        - Operation completed successfully.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrPrunePageFileDiskBuses(
      BOOL    fPruneBusIn
    , ULONG * pcPrunedInout
    )
{
    assert( pcPrunedInout != NULL );

    HRESULT         hr = S_OK;
    WCHAR           szPageFileDisks[ 26 ];
    int             cPageFileDisks = 0;
    int             idxPageFileDisk;
    ULONG           ulSCSIBus;
    ULONG           ulSCSIPort;
    ULONG           idx;
    ULONG           cPruned = 0;

    //
    //  Prune the bus with disks that have paging files.
    //

    hr = HrGetPageFileLogicalDisks( GetCallback(), szPageFileDisks, &cPageFileDisks );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( cPageFileDisks > 0 )
    {
        for ( idxPageFileDisk = 0; idxPageFileDisk < cPageFileDisks; idxPageFileDisk++ )
        {
            hr = HrFindDiskWithLogicalDisk( szPageFileDisks[ idxPageFileDisk ], &idx );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( hr == S_OK )
            {
                //
                //  Should we prune the whole bus, or just the system disk itself?
                //

                if ( fPruneBusIn )
                {
                    hr = HrGetSCSIInfo( idx, &ulSCSIBus, &ulSCSIPort );
                    if ( FAILED( hr ) )
                    {
                        goto Cleanup;
                    } // if:

                    STATUS_REPORT( TASKID_Major_Find_Devices, TASKID_Minor_Pruning_PageFile_Disk_Bus, IDS_INFO_PRUNING_PAGEFILEDISK_BUS, hr );
                    hr = HrPruneDisks(
                                      ulSCSIBus
                                    , ulSCSIPort
                                    , &TASKID_Minor_Pruning_PageFile_Disk_Bus
                                    , IDS_INFO_PAGEFILEDISK_PRUNED
                                    , IDS_INFO_PAGEFILEDISK_PRUNED_REF
                                    , &cPruned
                                    );
                    if ( FAILED( hr ) )
                    {
                        goto Cleanup;
                    } // if:
                } // if:
                else
                {
                    RemoveDiskFromArray( idx );
                    cPruned++;
                } // else:
            } // if:
        } // for:
    } // if:

    *pcPrunedInout = cPruned;
    hr = S_OK;

Cleanup:

    return hr;

} //*** CEnumStorageResource::HrPrunePageFileDiskBuses


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrPruneCrashDumpBus
//
//  Description:
//      Prune from the list of disks those that have pagefiles on them and
//      the other disks on those same SCSI busses.
//
//  Arguments:
//      fPruneBusIn
//
//      pcPrunedInout
//
//  Return Value:
//      S_OK        - Operation completed successfully.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrPruneCrashDumpBus(
      BOOL    fPruneBusIn
    , ULONG * pcPrunedInout
    )
{
    assert( pcPrunedInout != NULL );
    assert( m_bstrCrashDumpLogicalDisk != NULL );

    HRESULT hr = S_OK;
    ULONG   ulSCSIBus;
    ULONG   ulSCSIPort;
    ULONG   idx;
    ULONG   cPruned = 0;

    //
    //  Prune the bus with disks that have paging files.
    //

    hr = HrFindDiskWithLogicalDisk( m_bstrCrashDumpLogicalDisk[ 0 ], &idx );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( hr == S_OK )
    {
        //
        //  Should we prune the whole bus, or just the system disk itself?
        //

        if ( fPruneBusIn )
        {
            hr = HrGetSCSIInfo( idx, &ulSCSIBus, &ulSCSIPort );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            STATUS_REPORT( TASKID_Major_Find_Devices, TASKID_Minor_Pruning_CrashDump_Disk_Bus, IDS_INFO_PRUNING_CRASHDUMP_BUS, hr );
            hr = HrPruneDisks(
                              ulSCSIBus
                            , ulSCSIPort
                            , &TASKID_Minor_Pruning_CrashDump_Disk_Bus
                            , IDS_INFO_CRASHDUMPDISK_PRUNED
                            , IDS_INFO_CRASHDUMPDISK_PRUNED_REF
                            , &cPruned
                            );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:
        } // if:
        else
        {
            RemoveDiskFromArray( idx );
            cPruned++;
        } // else:
    } // if:

    *pcPrunedInout = cPruned;
    hr = S_OK;

Cleanup:

    return hr;

} //*** CEnumStorageResource::HrPruneCrashDumpBus


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrPruneDynamicDisks
//
//  Description:
//      Prune from the list of disks those that have dynamic partitions
//      on them.
//
//  Arguments:
//      pcPrunedInout
//
//  Return Value:
//      S_OK        - Operation completed successfully.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrPruneDynamicDisks(
    ULONG * pcPrunedInout
    )
{
    assert( pcPrunedInout != NULL );

    HRESULT                             hr = S_OK;
    ULONG                               idx;
    ULONG                               cPruned = 0;
    IStorageProperties *                piccpdp = NULL;
    HRESULT                             hrTemp;
    CLSID                               clsidMinorId;
    BSTR                                bstrDiskName = NULL;
    BSTR                                bstrDeviceName = NULL;

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        if ( (*m_prgDisks)[ idx ] != NULL )
        {
            hr = ((*m_prgDisks)[ idx ])->TypeSafeQI( IStorageProperties, &piccpdp );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccpdp->HrIsDynamicDisk();
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( hr == S_OK )
            {
                ((*m_prgDisks)[ idx ])->Release();
                (*m_prgDisks)[ idx ] = NULL;
                cPruned++;

                hrTemp = piccpdp->HrGetDiskNames( &bstrDiskName, &bstrDeviceName );
                if ( FAILED( hrTemp ) )
                {
                    LOG_STATUS_REPORT( L"Could not get the name of the disk", hrTemp );
                    bstrDiskName = NULL;
                    bstrDeviceName = NULL;
                } // if:

                hrTemp = CoCreateGuid( &clsidMinorId );
                if ( FAILED( hrTemp ) )
                {
                    LOG_STATUS_REPORT( L"Could not create a guid for a dynamic disk minor task ID", hrTemp );
                    clsidMinorId = IID_NULL;
                } // if:

                STATUS_REPORT_REF( TASKID_Major_Find_Devices, TASKID_Minor_Non_SCSI_Disks, IDS_INFO_NON_SCSI_DISKS, IDS_INFO_NON_SCSI_DISKS_REF, hr );
                STATUS_REPORT_STRING2_REF(
                          TASKID_Minor_Non_SCSI_Disks
                        , clsidMinorId
                        , IDS_ERROR_LDM_DISK
                        , bstrDeviceName != NULL ? bstrDeviceName : L"<unknown>"
                        , bstrDiskName != NULL ? bstrDiskName : L"<unknown>"
                        , IDS_ERROR_LDM_DISK_REF
                        , hr
                        );
            } // if:

            piccpdp->Release();
            piccpdp = NULL;

            SysFreeString( bstrDiskName );
            bstrDiskName = NULL;

            SysFreeString( bstrDeviceName );
            bstrDeviceName = NULL;
        } // end if:
    } // for:

    *pcPrunedInout = cPruned;
    hr = S_OK;

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    SysFreeString( bstrDiskName );
    SysFreeString( bstrDeviceName );

    return hr;

} //*** CEnumStorageResource::HrPruneDynamicDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrPruneGPTDisks
//
//  Description:
//      Prune from the list of disks those that have GPT partitions
//      on them.
//
//  Arguments:
//      pcPrunedInout
//
//  Return Value:
//      S_OK
//          Success.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrPruneGPTDisks(
    ULONG * pcPrunedInout
    )
{
    assert( pcPrunedInout != NULL );

    HRESULT                             hr = S_OK;
    ULONG                               idx;
    ULONG                               cPruned = 0;
    IStorageProperties *                piccpdp = NULL;
    HRESULT                             hrTemp;
    CLSID                               clsidMinorId;
    BSTR                                bstrDiskName = NULL;
    BSTR                                bstrDeviceName = NULL;

    for ( idx = 0; idx < m_idxNext; idx++ )
    {
        if ( (*m_prgDisks)[ idx ] != NULL )
        {
            hr = ((*m_prgDisks)[ idx ])->TypeSafeQI( IStorageProperties, &piccpdp );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            hr = piccpdp->HrIsGPTDisk();
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( hr == S_OK )
            {
                ((*m_prgDisks)[ idx ])->Release();
                (*m_prgDisks)[ idx ] = NULL;
                cPruned++;

                hrTemp = piccpdp->HrGetDiskNames( &bstrDiskName, &bstrDeviceName );
                if ( FAILED( hrTemp ) )
                {
                    LOG_STATUS_REPORT( L"Could not get the name of the disk", hrTemp );
                    bstrDiskName = NULL;
                    bstrDeviceName = NULL;
                } // if:

                hrTemp = CoCreateGuid( &clsidMinorId );
                if ( FAILED( hrTemp ) )
                {
                    LOG_STATUS_REPORT( L"Could not create a guid for a dynamic disk minor task ID", hrTemp );
                    clsidMinorId = IID_NULL;
                } // if:

                STATUS_REPORT_REF( TASKID_Major_Find_Devices, TASKID_Minor_Non_SCSI_Disks, IDS_INFO_NON_SCSI_DISKS, IDS_INFO_NON_SCSI_DISKS_REF, hr );
                STATUS_REPORT_STRING2_REF(
                          TASKID_Minor_Non_SCSI_Disks
                        , clsidMinorId
                        , IDS_INFO_GPT_DISK
                        , bstrDeviceName != NULL ? bstrDeviceName : L"<unknown>"
                        , bstrDiskName != NULL ? bstrDiskName : L"<unknown>"
                        , IDS_ERROR_LDM_DISK_REF
                        , hr
                        );
            } // if:

            piccpdp->Release();
            piccpdp = NULL;

            SysFreeString( bstrDiskName );
            bstrDiskName = NULL;

            SysFreeString( bstrDeviceName );
            bstrDeviceName = NULL;
        } // end if:
    } // for:

    *pcPrunedInout = cPruned;
    hr = S_OK;

Cleanup:

    if ( piccpdp != NULL )
    {
        piccpdp->Release();
    } // if:

    SysFreeString( bstrDiskName );
    SysFreeString( bstrDeviceName );

    return hr;

} //*** CEnumStorageResource::HrPruneGPTDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrConvertDeviceVolumeToLogicalDisk
//
//  Description:
//      Convert a device volume to a logical disk.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success.
//
//      Win32 Error
//          something failed.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrConvertDeviceVolumeToLogicalDisk(
      BSTR      bstrDeviceVolumeIn
    , BSTR *    pbstrLogicalDiskOut
    )
{
    assert( pbstrLogicalDiskOut != NULL );

    HRESULT     hr = S_OK;
    BOOL        fRet = FALSE;
    size_t      cchMountPoint = 0;
    WCHAR *     pwszMountPoint = NULL;
    WCHAR       szVolume[  MAX_PATH ];
    DWORD       sc = ERROR_SUCCESS;
    DWORD       cchPaths = 64;
    WCHAR *     pwszPaths = NULL;
    WCHAR *     pwszEOS = NULL;

    cchMountPoint = wcslen( g_szNameSpaceRoot ) + wcslen( bstrDeviceVolumeIn ) + 2;
    pwszMountPoint = new WCHAR[ cchMountPoint ];
    if ( pwszMountPoint == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    hr = StringCchCopyW( pwszMountPoint, cchMountPoint, g_szNameSpaceRoot );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = StringCchCatExW( pwszMountPoint, cchMountPoint, bstrDeviceVolumeIn, &pwszEOS, NULL, 0 );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    //  Append a trailing \ and re-terminate the string.
    //

    pwszEOS[ 0 ] = L'\\';
    pwszEOS[ 1 ] = L'\0';

    fRet = GetVolumeNameForVolumeMountPoint( pwszMountPoint, szVolume, RTL_NUMBER_OF( szVolume ) );
    if ( fRet == FALSE )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );

        LOG_STATUS_REPORT_STRING( L"[MyStorageResource] GetVolumeNameForVolumeMountPoint() failed.  Mount point is '%1!ws!'.", pwszMountPoint, hr );

        //
        //  GetVolumeNameForVolumeMountPoint() is no longer supported for IA64 EFI partitions.  If the error is
        //  ERROR_INVALID_FUNCTION then we should try to get the device number using an IOCTL.
        //
        if ( HRESULT_CODE( hr ) == ERROR_INVALID_FUNCTION )
        {
            LOG_STATUS_REPORT_STRING( L"[MyStorageResource] Device volume '%1!ws!' must be an IA64 EFI volume.", bstrDeviceVolumeIn, hr );
        } // if:

        goto Cleanup;
    } // if:

    pwszPaths = new WCHAR[ cchPaths ];
    if ( pwszPaths == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    //
    //  Since the device name that is passed in is for a volume there will never be more than
    //  one logical disk in the multisz pwszPaths.
    //

    fRet = GetVolumePathNamesForVolumeName( szVolume, pwszPaths, cchPaths, &cchPaths );
    if ( fRet == FALSE )
    {
        sc = GetLastError();
        if ( sc == ERROR_MORE_DATA )
        {
            cchPaths++;

            delete [] pwszPaths;
            pwszPaths = new WCHAR[ cchPaths ];
            if ( pwszPaths == NULL )
            {
                hr = E_OUTOFMEMORY;
                goto Cleanup;
            } // if:

            fRet = GetVolumePathNamesForVolumeName( szVolume, pwszPaths, cchPaths, &cchPaths );
        } // if:
    } // else:

    if ( fRet == FALSE )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT_STRING( L"[MyStorageResource] GetVolumePathNamesForVolumeName() failed. Volume is is '%1!ws!'.", szVolume, hr );
        goto Cleanup;
    } // if:

    *pbstrLogicalDiskOut = SysAllocString( pwszPaths );
    if ( *pbstrLogicalDiskOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

Cleanup:

    delete [] pwszPaths;

    delete [] pwszMountPoint;

    return hr;

} //*** CEnumStorageResource::HrConvertDeviceVolumeToLogicalDisk


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrConvertDeviceVolumeToWMIDeviceID
//
//  Description:
//      Since IA64 EFI partitions no longer support the call to
//      GetVolumeNameForVolumeMountPoint() to convert the device name
//      into a logical disk, since there will not longer be logical disks
//      for these partitions.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrConvertDeviceVolumeToWMIDeviceID(
      BSTR      bstrDeviceVolumeIn
    , BSTR *    pbstrWMIDeviceIDOut
    )
{
    HRESULT                 hr = S_OK;
    HANDLE                  hVolume = NULL;
    DWORD                   dwSize;
    DWORD                   sc;
    STORAGE_DEVICE_NUMBER   sdnDevNumber;
    BOOL                    fRet;
    size_t                  cchDevice;
    WCHAR *                 pwszDevice = NULL;
    WCHAR                   sz[ 64 ];

    cchDevice = wcslen( g_szNameSpaceRoot ) + wcslen( bstrDeviceVolumeIn ) + 2;
    pwszDevice = new WCHAR[ cchDevice ];
    if ( pwszDevice == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    hr = StringCchCopyW( pwszDevice, cchDevice, g_szNameSpaceRoot );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = StringCchCatW( pwszDevice, cchDevice, bstrDeviceVolumeIn );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // get handle to partition
    //

    hVolume = CreateFileW(
                        pwszDevice
                      , GENERIC_READ
                      , FILE_SHARE_READ
                      , NULL
                      , OPEN_EXISTING
                      , FILE_ATTRIBUTE_NORMAL
                      , NULL
                      );

    if ( hVolume == INVALID_HANDLE_VALUE )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    //
    // issue storage class ioctl to get drive and partition numbers
    // for this device
    //

    fRet = DeviceIoControl(
                          hVolume
                        , IOCTL_STORAGE_GET_DEVICE_NUMBER
                        , NULL
                        , 0
                        , &sdnDevNumber
                        , sizeof( sdnDevNumber )
                        , &dwSize
                        , NULL
                        );
    if ( fRet == FALSE )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    hr = StringCchPrintfW( sz, RTL_NUMBER_OF( sz ), g_szPhysicalDriveFormat, sdnDevNumber.DeviceNumber );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    *pbstrWMIDeviceIDOut = SysAllocString( sz );
    if ( *pbstrWMIDeviceIDOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

Cleanup:

    if ( hVolume != NULL )
    {
        CloseHandle( hVolume );
    } // if:

    delete [] pwszDevice;

    return hr;

} //*** CEnumStorageResource::HrConvertDeviceVolumeToWMIDeviceID


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrGetPageFileLogicalDisks
//
//  Description:
//      Mark the drives that have paging files on them.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetPageFileLogicalDisks(
      IClusCfgCallback *    picccIn
    , WCHAR                 szLogicalDisksOut[ 26 ]
    , int *                 pcLogicalDisksOut
    )
{
    HRESULT                 hr = S_FALSE;
    IEnumWbemClassObject *  pPagingFiles = NULL;
    BSTR                    bstrClass;
    ULONG                   ulReturned;
    IWbemClassObject *      pPagingFile = NULL;
    VARIANT                 var;
    int                     idx;

    UNREFERENCED_PARAMETER( picccIn );

    bstrClass = SysAllocString( L"Win32_PageFile" );
    if ( bstrClass == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    hr = m_pIWbemServices->CreateInstanceEnum( bstrClass, WBEM_FLAG_SHALLOW, NULL, &pPagingFiles );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    VariantInit( &var );

    for ( idx = 0; idx < sizeof( szLogicalDisksOut ); idx++ )
    {
        hr = pPagingFiles->Next( WBEM_INFINITE, 1, &pPagingFile, &ulReturned );
        if ( ( hr == S_OK ) && ( ulReturned == 1 ) )
        {
            VariantClear( &var );

            hr = HrGetWMIProperty( pPagingFile, L"Drive", VT_BSTR, &var );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            CharUpper( var.bstrVal );

            szLogicalDisksOut[ idx ] = var.bstrVal[ 0 ];

            pPagingFile->Release();
            pPagingFile = NULL;
        } // if:
        else if ( ( hr == S_FALSE ) && ( ulReturned == 0 ) )
        {
            hr = S_OK;
            break;
        } // else if:
        else
        {
            goto Cleanup;
        } // else:
    } // for:

    if ( pcLogicalDisksOut != NULL )
    {
        *pcLogicalDisksOut = idx;
    } // if:

Cleanup:

    VariantClear( &var );

    SysFreeString( bstrClass );

    if ( pPagingFile != NULL )
    {
        pPagingFile->Release();
    } // if:

    if ( pPagingFiles != NULL )
    {
        pPagingFiles->Release();
    } // if:

    return hr;

} //*** CEnumStorageResource::HrGetPageFileLogicalDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrGetSystemDevice
//
//  Description:
//      Returns the system device.  The system drive is the drive that was
//      booted and has ntldr.exe on it.
//
//  Arguments:
//
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetSystemDevice( BSTR * pbstrSystemDeviceOut )
{
    assert( pbstrSystemDeviceOut != NULL );

    HRESULT hr = S_OK;
    DWORD   sc;
    HKEY    hKey = NULL;
    WCHAR * pwszSystemDevice = NULL;
    DWORD   cbSystemDevice = 0;
    DWORD   dwType;

    sc = RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"System\\Setup", 0, KEY_READ, &hKey );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] RegOpenKeyEx() failed.", hr );
        goto Cleanup;
    } // if:

    sc = RegQueryValueEx( hKey, L"SystemPartition", NULL, NULL, NULL, &cbSystemDevice );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] RegQueryValueEx() failed.", hr );
        goto Cleanup;
    } // if:

    pwszSystemDevice = new WCHAR[ cbSystemDevice / sizeof( WCHAR ) ];
    if ( pwszSystemDevice == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    sc = RegQueryValueEx( hKey, L"SystemPartition", NULL, &dwType, (BYTE *) pwszSystemDevice, &cbSystemDevice );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] RegQueryValueEx() failed.", hr );
        goto Cleanup;
    } // if:

    if (dwType != REG_SZ)
    {
        hr = ERROR_DATATYPE_MISMATCH;
        LOG_STATUS_REPORT_STRING( L"[MyStorageResource] RegQueryValueEx() invalid type %1!d!", dwType, hr );
        goto Cleanup;
    } // if:

    *pbstrSystemDeviceOut = SysAllocString( pwszSystemDevice );
    if ( *pbstrSystemDeviceOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

Cleanup:

    delete [] pwszSystemDevice;

    if ( hKey != NULL )
    {
        RegCloseKey( hKey );
    } // if:

    return hr;

} //*** CEnumStorageResource::HrGetSystemDevice


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrGetBootLogicalDisk
//
//  Description:
//      Returns the boot logical disk.  The boot disk is where the OS is
//      installed.
//
//  Arguments:
//      pbstrBootLogicalDiskOut
//
//  Return Value:
//      S_OK
//      Other HRESULT errors.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetBootLogicalDisk(
    BSTR * pbstrBootLogicalDiskOut
    )
{
    assert( pbstrBootLogicalDiskOut != NULL );

    HRESULT hr = S_OK;
    DWORD   sc;
    WCHAR   szWindowsDir[ MAX_PATH ];
    WCHAR   szVolume[ MAX_PATH ];
    BOOL    fRet;

    sc = GetWindowsDirectoryW( szWindowsDir, RTL_NUMBER_OF( szWindowsDir ) );
    if ( sc == 0 )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] GetWindowsDirectory() failed.", hr );
        goto Cleanup;
    } // if:

    fRet = GetVolumePathName( szWindowsDir, szVolume, RTL_NUMBER_OF( szVolume ) );
    if ( fRet == FALSE )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] GetVolumePathName() failed.", hr );
        goto Cleanup;
    } // if:

    *pbstrBootLogicalDiskOut = SysAllocString( szVolume );
    if ( *pbstrBootLogicalDiskOut == NULL )
    {
        hr = E_OUTOFMEMORY;
    } // if:

Cleanup:

    return hr;

} //*** CEnumStorageResource::HrGetBootLogicalDisk


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CEnumStorageResource::HrGetCrashDumpLogicalDisk
//
//  Description:
//      Returns the logical disk of the system crash dump file.
//
//  Arguments:
//      pbstrCrashDumpLogicalDiskOut
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs as errors.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CEnumStorageResource::HrGetCrashDumpLogicalDisk(
    BSTR * pbstrCrashDumpLogicalDiskOut
    )
{
    assert( pbstrCrashDumpLogicalDiskOut != NULL );

    HRESULT hr = S_OK;
    DWORD   sc;
    HKEY    hKey = NULL;
    WCHAR * pwszDumpFile = NULL;
    WCHAR * pwszExpandedDumpFile = NULL;
    DWORD   cbDumpFile = 0;
    DWORD   cchExpandedDumpFile = 0;
    BSTR    bstr = NULL;
    DWORD   dwType;

    sc = RegOpenKeyEx( HKEY_LOCAL_MACHINE, L"System\\CurrentControlSet\\Control\\CrashControl", 0, KEY_READ, &hKey );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] [HrGetCrashDumpLogicalDisk] RegOpenKeyEx() failed.", hr );
        goto Cleanup;
    } // if:

    sc = RegQueryValueEx( hKey, L"DumpFile", NULL, NULL, NULL, &cbDumpFile );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] [HrGetCrashDumpLogicalDisk] RegQueryValueEx() failed.", hr );
        goto Cleanup;
    } // if:

    pwszDumpFile = new WCHAR[ cbDumpFile / sizeof( WCHAR ) ];
    if ( pwszDumpFile == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    sc = RegQueryValueEx( hKey, L"DumpFile", NULL, &dwType, (BYTE *) pwszDumpFile, &cbDumpFile );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        LOG_STATUS_REPORT( L"[MyStorageResource] [HrGetCrashDumpLogicalDisk] RegQueryValueEx() failed.", hr );
        goto Cleanup;
    } // if:

    if ( ( dwType != REG_SZ ) && ( dwType != REG_EXPAND_SZ ) )
    {
        hr = ERROR_DATATYPE_MISMATCH;
        LOG_STATUS_REPORT_STRING( L"[MyStorageResource] RegQueryValueEx() invalid type %1!d!", dwType, hr );
        goto Cleanup;
    } // if:

    cchExpandedDumpFile = ExpandEnvironmentStrings( pwszDumpFile, NULL, 0 );
    if ( cchExpandedDumpFile > 0 )
    {
        pwszExpandedDumpFile = new WCHAR[ cchExpandedDumpFile ];
        if( pwszExpandedDumpFile == NULL )
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        } // if:
        cchExpandedDumpFile = ExpandEnvironmentStrings( pwszDumpFile, pwszExpandedDumpFile, cchExpandedDumpFile );
    } // if: success

    if ( cchExpandedDumpFile == 0 )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto Cleanup;
    } // if:

    bstr = SysAllocString( pwszExpandedDumpFile );
    if ( bstr == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    *pbstrCrashDumpLogicalDiskOut = bstr;
    bstr = NULL;

Cleanup:

    SysFreeString( bstr );

    delete [] pwszExpandedDumpFile;
    delete [] pwszDumpFile;

    if ( hKey != NULL )
    {
        RegCloseKey( hKey );
    } // if:

    return hr;

} //*** CEnumStorageResource::HrGetCrashDumpLogicalDisk
