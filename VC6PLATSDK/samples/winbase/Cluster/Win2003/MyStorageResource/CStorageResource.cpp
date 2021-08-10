//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CStorageResource.cpp
//
//  Description:
//      Implementation for the ClusCfg Managed Resource class - this demonstrates how
//      to implement the IClusCfgManagedResourceInfo and
//      IClusCfgManagedResourceCfg interfaces.
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WMIHelpers.h"
#include "CStorageResource.h"
#include "CPartitionInfo.h"
#include "proplist.h"

//
// Instead of requiring the DDK to be installed the following information has been 
// copied from ntddscsi.h.  If you have the DDK installed uncomment the include.
//

#pragma warning( push )
#include <ntddscsi.h>
#pragma warning( pop )


//////////////////////////////////////////////////////////////////////////////
// CStorageResource class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::CStorageResource
//
//  Description:
//      Constructor of the CStorageResource class. Initializes all variables.
//
//  Arguments:
//
//  Return Value:
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CStorageResource::CStorageResource( void )
{
    m_bstrName = NULL;
    m_bstrDescription = NULL;
    m_bstrFriendlyName = NULL;
    m_bstrDeviceID = NULL;

    m_fIsQuorumCapable = FALSE;
    m_fIsQuorumResource = FALSE;
    m_fIsMultiNodeCapable = FALSE;
    m_fIsManaged = FALSE;
    m_fIsManagedByDefault = FALSE;
    m_fIsDynamicDisk = FALSE;
    m_fIsGPTDisk = FALSE;

    m_ulSCSIBus = 0;
    m_ulSCSITid = 0;
    m_ulSCSIPort = 0;
    m_ulSCSILun = 0;

    m_idxDevice = 0;
    m_idxNextPartition = 0;
    m_idxEnumPartitionNext = 0;
    m_cPartitions = 0;
    m_dwSignature = 0;

    m_pIWbemServices = NULL;
    m_prgPartitions = NULL;

} //*** CStorageResource::CStorageResource


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::~CStorageResource
//
//  Description:
//      Destructor of the CStorageResource class. Free's all used buffers
//
//  Arguments:
//
//  Return Value:
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CStorageResource::~CStorageResource( void )
{
    ULONG   idx = 0;

    SysFreeString( m_bstrName );
    SysFreeString( m_bstrDeviceID );
    SysFreeString( m_bstrDescription );
    SysFreeString( m_bstrFriendlyName );

    for ( idx = 0; idx < m_idxNextPartition; idx++ )
    {
        ((*m_prgPartitions)[ idx ])->Release();
    } // for:

    HeapFree( GetProcessHeap(), 0, m_prgPartitions );

    if ( m_pIWbemServices != NULL )
    {
        m_pIWbemServices->Release();
    } // if:

} //*** CStorageResource::~CStorageResource


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IClusCfgManagedResourceInfo interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::GetDriveLetterMappings
//
//  Description:
//      Gets Drive Letter Mappings of this resource.
//
//  Arguments:
//    pdlmDriveLetterMappingsOut - Array to fill in with how drive letters are used.
//
//  Return Value:
//      S_FALSE     - Not supported
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::GetDriveLetterMappings(
    SDriveLetterMapping * pdlmDriveLetterMappingsOut
    )
{
    HRESULT                 hr = S_FALSE;
    IClusCfgPartitionInfo * piccpi = NULL;
    ULONG                   idx;

    if ( pdlmDriveLetterMappingsOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetDriveLetterMappings_StorageResource
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    for ( idx = 0; idx < m_idxNextPartition; idx++ )
    {
        hr = ( ((*m_prgPartitions)[ idx ])->TypeSafeQI( IClusCfgPartitionInfo, &piccpi ) );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = piccpi->GetDriveLetterMappings( pdlmDriveLetterMappingsOut );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        piccpi->Release();
        piccpi = NULL;
    } // for:

Cleanup:

    if ( piccpi != NULL )
    {
        piccpi->Release();
    } // if:

    return hr;

} //*** CStorageResource::GetDriveLetterMappings


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetDriveLetterMappings
//
//  Description:
//      Sets Drive Letter Mappings of this resource. Unsupported
//
//  Arguments:
//    dlmDriveLetterMappingsIn  - Drive letter mappings.
//
//  Return Value:
//      S_FALSE     - Not supported
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetDriveLetterMappings(
    SDriveLetterMapping dlmDriveLetterMappingsIn
    )
{
    HRESULT hr = E_NOTIMPL;

    UNREFERENCED_PARAMETER( dlmDriveLetterMappingsIn );

    return hr;

} //*** CStorageResource::SetDriveLetterMappings


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::GetName
//
//  Description:
//      Gets name of this resource.
//
//  Arguments:
//    pbstrNameOut  - Name of resource.
//
//  Return Value:
//      S_OK            - Success
//      E_POINTER       - Expected pointer argument specified as NULL.
//      E_OUTOFMEMORY   - Out of memory.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::GetName(
    BSTR * pbstrNameOut
    )
{
    HRESULT hr = S_OK;

    if ( pbstrNameOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetName_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    //
    //  Prefer the "friendly" name over the WMI name -- if we have it...
    //
    if ( m_bstrFriendlyName != NULL )
    {
        *pbstrNameOut = SysAllocString( m_bstrFriendlyName );
    } // if:
    else
    {
        LOG_STATUS_REPORT_STRING2(
                  L"There is not a \"friendly name\" for the %1!ws! resource '%2!ws!'."
                , GetResTypeName()
                , m_bstrName
                , hr
                );
        *pbstrNameOut = SysAllocString( m_bstrName );
    } // else:

    if (*pbstrNameOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetName_Memory
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
    } // if:

Cleanup:

    return hr;

} //*** CStorageResource::GetName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetName
//
//  Description:
//      Sets name of this resource.
//
//  Arguments:
//    pwszNameIn    - New name to give to the resource.
//
//  Return Value:
//      S_OK            - Success
//      E_INVALIDARD    - Expected pointer argument specified as NULL.
//      E_OUTOFMEMORY   - Out of memory.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetName(
    LPCWSTR pwszNameIn
    )
{
    HRESULT hr = S_OK;
    BSTR    bstr = NULL;

    if ( pwszNameIn == NULL )
    {
        hr = E_INVALIDARG;
        goto Cleanup;
    } // if:

    bstr = SysAllocString( pwszNameIn );
    if ( bstr == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_SetName_StorageResource
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
        goto Cleanup;
    } // if:

    SysFreeString( m_bstrName );
    m_bstrName = bstr;

    //
    // Since we got asked from the outside to set a new name, this should actually be reflected in
    // the friendly name, too, since that, ultimately, gets preference over the real name
    //
    hr = HrSetFriendlyName( pwszNameIn );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    return hr;

} //*** CStorageResource::SetName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::GetUID
//
//  Description:
//      Gets a unique ID for this resource.
//
//  Arguments:
//    pbstrUIDOut   - Unique ID being returned.
//
//  Return Value:
//      S_OK            - Success
//      E_POINTER       - Expected pointer argument specified as NULL.
//      E_OUTOFMEMORY   - Out of memory.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::GetUID(
    BSTR * pbstrUIDOut
    )
{
    HRESULT hr = S_OK;
    WCHAR   sz[ 256 ];

    if ( pbstrUIDOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_StorageResource_GetUID_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if: incoming UID buffer was invalid (NULL)

    //
    // TODO: Retrieve the unique ID for this resource. If this same resource
    //       is going to be detected on other nodes of the cluster make sure
    //       that each of those resources have the same UID, otherwise a new
    //       resource will be generated for each UID.
    //

    hr = StringCchPrintfW(
              sz
            , RTL_NUMBER_OF( sz )
            , L"%s SCSI Tid %ld, SCSI Lun %ld"
            , GetDisplayName()
            , m_ulSCSITid
            , m_ulSCSILun
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    *pbstrUIDOut = SysAllocString( sz );
    if ( *pbstrUIDOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_StorageResource_GetUID_Memory
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
    } // if:

Cleanup:

    return hr;

} //*** CStorageResource::GetUID


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::IsManaged
//
//  Description:
//      Queries whether this resource is managed or not.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - Resource is managed.
//      S_FALSE - Resource is not managed.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::IsManaged( void )
{
    HRESULT hr = S_OK;

    if ( m_fIsManaged == FALSE )
    {
        hr = S_FALSE;
    } // if: this resource is not managed

    return hr;

} //*** CStorageResource::IsManaged


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::IsManagedByDefault
//
//  Description:
//      Queries whether this resource is managed by default or not.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - Resource is managed by default.
//      S_FALSE - Resource is not managed by default.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::IsManagedByDefault( void )
{
    HRESULT hr = S_OK;

    if ( m_fIsManagedByDefault == FALSE )
    {
        hr = S_FALSE;
    } // if: this resource is not managed by default

    return hr;

} //*** CStorageResource::IsManagedByDefault


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetManaged
//
//  Description:
//      Sets whether this resource is managed or not.
//
//  Arguments:
//      fIsManagedIn    - TRUE = managed, FALSE = not managed
//
//  Return Value:
//      S_OK    - Success
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetManaged(
    BOOL fIsManagedIn
    )
{
    HRESULT hr = S_OK;

    m_fIsManaged = fIsManagedIn;

    LOG_STATUS_REPORT_STRING3(
                          L"%1!ws! resource '%2!ws!' '%3!ws!"
                        , GetResTypeName()
                        , ( m_bstrFriendlyName != NULL ) ? m_bstrFriendlyName : m_bstrName
                        , m_fIsManaged ? L"is managed" : L"is not managed"
                        , hr
                        );
    return hr;

} //*** CStorageResource::SetManaged


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetManagedByDefault
//
//  Description:
//      Sets whether this resource is managed by default or not.
//
//  Arguments:
//      fIsManagedByDefaultIn   - TRUE = managed, FALSE = not managed
//
//  Return Value:
//      S_OK    - Success
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetManagedByDefault(
    BOOL fIsManagedByDefaultIn
    )
{
    HRESULT hr = S_OK;

    m_fIsManagedByDefault = fIsManagedByDefaultIn;

    LOG_STATUS_REPORT_STRING3(
                          L"%1!ws! resource '%2!ws!' '%3!ws!"
                        , GetResTypeName()
                        , ( m_bstrFriendlyName != NULL ) ? m_bstrFriendlyName : m_bstrName
                        , fIsManagedByDefaultIn ? L"is manageable" : L"is not manageable"
                        , hr
                        );

    return hr;

} //*** CStorageResource::SetManagedByDefault


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::IsQuorumCapable
//
//  Description:
//      Queries whether this resource is suitable as a quorum resource or not.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - Resource can become quorum.
//      S_FALSE - Resource cannot become quorum.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::IsQuorumCapable( void )
{
    HRESULT hr = S_OK;

    if ( m_fIsQuorumCapable == FALSE )
    {
        hr = S_FALSE;
    } // if:

    return hr;

} //*** CStorageResource::IsQuorumCapable


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetQuorumCapable
//
//  Description:
//      Sets whether the resource is quorum capable or not.  Unsupported.
//
//  Arguments:
//      fIsQuorumCapableIn      - TRUE = quorum capable, FALSE = not qourum capable
//
//
//  Return Value:
//      S_OK
//          Success
//
//      HRESULT_FROM_WIN32( ERROR_NOT_QUORUM_CAPABLE )
//          Resource cannot become quorum.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetQuorumCapable(
    BOOL fIsQuorumCapableIn
    )
{
    HRESULT hr = S_OK;

    m_fIsQuorumCapable = fIsQuorumCapableIn;

    return hr;

} //*** CStorageResource::IsQuorumCapable


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::IsQuorumResource
//
//  Description:
//      Queries whether this resource is currently the quorum resource or not.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - This is the quorum resource.
//      S_FALSE - This is not the quorum resource.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::IsQuorumResource( void )
{
    HRESULT hr = S_FALSE;

    if ( m_fIsQuorumResource )
    {
        hr = S_OK;
    } // if:

    return hr;

} //*** CStorageResource::IsQuorumResource


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetQuorumResource
//
//  Description:
//      Sets this resource's quorum status.
//
//  Arguments:
//      fIsQuorumResourceIn
//          TRUE = quorum resource
//          FALSE = not quorum resource.
//
//  Return Value:
//      S_OK
//          Success
//
//      HRESULT_FROM_WIN32( ERROR_NOT_QUORUM_CAPABLE )
//          Resource cannot become quorum.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetQuorumResource(
    BOOL fIsQuorumResourceIn
    )
{
    HRESULT hr = S_OK;

    //
    //  Since no accurate determination can be made about a disk's quorum capability
    //  when the node that it's on does not hold the SCSI reservation and have access
    //  to the media we must blindly accept the input given...
    //

    m_fIsQuorumResource = fIsQuorumResourceIn;

    LOG_STATUS_REPORT_STRING3(
                          L"Setting %1!ws! resource '%2!ws!' '%3!ws!' the quorum device."
                        , GetResTypeName()
                        , ( m_bstrFriendlyName != NULL ) ? m_bstrFriendlyName : m_bstrDeviceID
                        , m_fIsQuorumResource ? L"to be" : L"to not be"
                        , hr
                        );
    return hr;

} //*** CStorageResource::SetQuorumResource


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IClusCfgVerifyQuorum interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::IsMultiNodeCapable
//
//  Description:
//      Called to determine if this quorum-capable resource allows other
//      nodes to be added to the cluster to create a multi-node cluster.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    - Resource can be used by more than one node.
//      S_FALSE - Resource can be used by one node only.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::IsMultiNodeCapable( void )
{
    HRESULT hr = S_OK;

    if ( m_fIsMultiNodeCapable == FALSE )
    {
        hr = S_FALSE;
    } // if: this resource can be used by one node only

    return hr;

} //*** CStorageResource::IsMultiNodeCapable


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetMultiNodeCapable
//
//  Description:
//      Sets whether this quorum-capable resource can be used by more than
//      one node.
//
//  Arguments:
//      fMultiNodeCapableIn
//          TRUE = multi-node capable
//          FALSE = only single-node capable
//
//  Return Value:
//      S_OK    - Multi-node capable
//      S_FALSE - Not multi-node capable
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetMultiNodeCapable(
    BOOL fMultiNodeCapableIn
    )
{
    HRESULT hr = S_FALSE;

    UNREFERENCED_PARAMETER( fMultiNodeCapableIn );

    return hr;

} //*** CStorageResource::SetMultiNodeCapable


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::PrepareToHostQuorumResource
//
//  Description:
//      This method is called when the implementing managed resource
//      is the quorum resource.  This gives the implementer a chance
//      to do anything required to ensure that this node can
//      indeed host the quorum resource.
//
//      This method will be called after the SetResourcePrivateData()
//      method of the IClusCfgManagedResourceData interface has been
//      called. This allows the implementer to get the latest state data
//      from a running instance of their resource.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK    Success.
//      Other HRESULTs
//
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::PrepareToHostQuorumResource( void )
{
    HRESULT hr = S_OK;

    return hr;

} //*** CStorageResource::PrepareToHostQuorumResource


//////////////////////////////////////////////////////////////////////////////
//
//  CStorageResource::Cleanup
//
//  Description:
//      This method is called when a cluster configuration task is
//      shutting down.  The reason for the shut down is passed in
//      the cccrReasonIn parameter.
//
//      It is expected that any lingering changes made in
//      PrepareToHostQuorumResource() would be undone when the
//      reason code in not a success code.
//
//  Arguments:
//      cccrReasonIn
//          The reason that this method was called.  See
//          EClusCfgCleanupReason for the complete list of possbile
//          reason codes.
//
//  Return Values:
//      S_OK    - Success.
//      Other HRESULTs
//
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::Cleanup(
    EClusCfgCleanupReason cccrReasonIn
    )
{
    HRESULT hr = S_OK;

    UNREFERENCED_PARAMETER( cccrReasonIn );

    return hr;

} //*** CStorageResource::Cleanup


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IClusCfgManagedResourceCfg interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::PreCreate
//
//  Description:
//      The PreCreate method is called by the post configuration manager to
//      determine the requirements of the resource. Querying the
//      punkServicesIn allows the managed resource to use services provided
//      by the manager.
//
//  Arguments:
//      punkServicesIn
//          Interface used to query back for interfaces that provide cluster
//          configuration services, e.g. IClusCfgResourcePreCreate.
//
//  Return Value:
//      S_OK    - Success
//      Other HRESULTs
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::PreCreate(
    IUnknown * punkServicesIn
    )
{
    HRESULT                     hr = S_OK;
    IClusCfgResourcePreCreate * piccrpc = NULL;
    BSTR                        bstr = m_bstrFriendlyName != NULL ? m_bstrFriendlyName : m_bstrName;
    CLSID                       CLSID_Restype = RESTYPE_StorageResource;

    //
    // First, query for the IClusCfgResourcePreCreate interface which will
    // provide all services that we need.
    //

    hr = punkServicesIn->TypeSafeQI( IClusCfgResourcePreCreate, &piccrpc );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Then, set the resource type of this managed resource.
    //
    hr = piccrpc->SetType( &CLSID_Restype );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = piccrpc->SetClassType( (LPCLSID) &RESCLASSTYPE_StorageDevice );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

#if 0 // test code only
    hr = piccrpc->SetDependency( (LPCLSID) &IID_NULL, dfSHARED );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:
#endif // test code only

Cleanup:

    if ( piccrpc != NULL )
    {
        piccrpc->Release();
        piccrpc = NULL;
    } // if:

    STATUS_REPORT_STRING2(
              TASKID_Major_Configure_Resources
            , TASKID_Minor_StorageResource_PreCreate
            , IDS_INFO_DISK_PRECREATE
            , GetDisplayName()
            , bstr
            , hr
            );

    return hr;

} //*** CStorageResource::PreCreate


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Create
//
//  Description:
//      Called to have the component create a new resource instance.
//
//  Arguments:
//      punkServicesIn
//          Interface used to query back for interfaces that provide cluster
//          configuration services, e.g. IClusCfgResourceCreate.
//
//  Return Value:
//      S_OK    - Success
//      Other HRESULTs
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::Create(
    IUnknown * punkServicesIn
    )
{
    HRESULT hr = S_OK;
    IClusCfgResourceCreate *    piccrc = NULL;
    BSTR *                      pbstrName = m_bstrFriendlyName != NULL ? &m_bstrFriendlyName : &m_bstrName;
    CClusPropList               cpl;
    BSTR                        bstrDescription = NULL;

    //
    // TODO: Add any code here to set default values for resource private
    // data.
    //

    hr = punkServicesIn->TypeSafeQI( IClusCfgResourceCreate, &piccrc );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( m_dwSignature != 0 )
    {
        //
        // Set the private signature property on the resource.
        //

        LOG_STATUS_REPORT_STRING2(
                  L"Setting signature to '%1!u!' on resource '%2!ws!'."
                , m_dwSignature
                , *pbstrName
                , hr
                );
        hr = piccrc->SetPropertyDWORD( L"Signature", m_dwSignature );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if:
    
    //
    // Set the description to indicate that this is the code that created the resource.
    //

    hr = HrFormatStringIntoBSTR(
              IDS_RESOURCE_DESCRIPTION
            , &bstrDescription
            , L"MyStorageResource.dll"
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cpl.ScAddProp( L"Description", bstrDescription, NULL );
    LOG_STATUS_REPORT_STRING2(
              L"Setting description '%1!ws!' on resource '%2!ws!'."
            , bstrDescription
            , *pbstrName
            , hr
            );
    hr = piccrc->SendResourceControl(
              CLUSCTL_RESOURCE_SET_COMMON_PROPERTIES
            , cpl.Plist()
            , cpl.CbPropList()
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    STATUS_REPORT_STRING2(
              TASKID_Major_Configure_Resources
            , TASKID_Minor_StorageResource_Create
            , IDS_INFO_DISK_CREATE
            , GetDisplayName()
            , *pbstrName
            , hr
            );

    SysFreeString( bstrDescription );

    if ( piccrc != NULL )
    {
        piccrc->Release();
    } // if:

    return hr;

} //*** CStorageResource::Create


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::PostCreate
//
//  Description:
//      Called to allow the component to configure a newly-created resource
//      after all resources have been created.
//
//  Arguments:
//    punkServicesIn
//          Interface used to query back for interfaces that provide cluster
//          configuration services, e.g. IClusCfgResourcePostCreate
//
//  Return Value:
//      S_OK    - Success
//      Other HRESULTs
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::PostCreate(
    IUnknown * punkServicesIn
    )
{
    HRESULT hr = S_OK;

    //
    // TODO: Add any code here for any post create actions that may be
    // necessary for the managed resource.
    //
    UNREFERENCED_PARAMETER( punkServicesIn );

    return hr;

} //*** CStorageResource::PostCreate

//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Evict
//
//  Description:
//      Called after the node has been evicted from the cluster to allow the
//      component to perform any operations required to cleanup the
//      application's cluster support.
//
//  Arguments:
//      punkServicesIn
//          Interface used to query back for interfaces that provide cluster
//          configuration services.
//
//  Return Value:
//      S_OK    - Success
//      Other HRESULTs
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::Evict(
    IUnknown * punkServicesIn
    )
{
    HRESULT hr = S_OK;

    //
    // TODO: Add any code here that might be necessary on evicting a node
    // from a cluster.
    //
    UNREFERENCED_PARAMETER( punkServicesIn );

    return hr;

} //*** CStorageResource::Evict


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IClusCfgManagedResourceData interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::GetResourcePrivateData
//
//  Description:
//      Get an already managed resource's private state data.  This
//      data will then be passed to the instances of that resource on all
//      nodes that are being added to the cluster.
//
//  Arguments:
//      pbBufferOut
//          Pointer to a buffer to contain the resource's private state data.
//
//      pcbBufferInout
//          On input it is the size of the buffer.  On output it is the size
//          of the data.
//
//  Return Value:
//      S_OK
//          Success.
//
//      S_FALSE
//          Success, but no data available
//
//      ERROR_MORE_DATA as an HRESULT
//          When the passed in buffer is too small to hold the data.
//          pcbBufferOutIn will contain the size required.
//
//      Other HRESULTs.
//          The call failed.
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::GetResourcePrivateData(
      BYTE *    pbBufferOut
    , DWORD *   pcbBufferInout
    )
{
    HRESULT hr = S_FALSE;

    pcbBufferInout = 0;
    UNREFERENCED_PARAMETER( pbBufferOut );

    return hr;

} //*** CStorageResource::GetResourcePrivateData


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetResourcePrivateData
//
//  Description:
//      Set the private resource data into this instance of a managed
//      resource.
//
//  Arguments:
//      pcbBufferIn
//          Pointer to a buffer containing the resource's private data.
//
//      cbBufferIn
//          The length in bytes of the data buffer.
//
//  Return Values:
//      S_OK
//          Success.
//
//      Other HRESULTs.
//          The call failed.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetResourcePrivateData(
      const BYTE *   pcbBufferIn
    , DWORD          cbBufferIn
    )
{
    HRESULT hr = S_OK;

    UNREFERENCED_PARAMETER( pcbBufferIn );
    UNREFERENCED_PARAMETER( cbBufferIn );

    return hr;

} //*** CStorageResource::SetResourcePrivateData


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IWMIService interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetWbemServices
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
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::SetWbemServices(
    IWbemServices * pIWbemServicesIn
    )
{
    HRESULT hr = S_OK;

    if ( pIWbemServicesIn == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_SetWbemServices_StorageResource
                , IDS_ERROR_NULL_POINTER
                , hr
                );
        goto Cleanup;
    } // if:

    m_pIWbemServices = pIWbemServicesIn;
    m_pIWbemServices->AddRef();

Cleanup:

    return hr;

} //*** CStorageResource::SetWbemServices


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IWMIObject interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::SetWbemObject
//
//  Description:
//      Set the disk information information provider.
//
//  Arguments:
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
STDMETHODIMP
CStorageResource::SetWbemObject(
      IWbemClassObject *    pDiskIn
    , BOOL *                pfRetainObjectOut
    )
{
    assert( pDiskIn != NULL );
    assert( pfRetainObjectOut != NULL );

    HRESULT hr = S_FALSE;
    VARIANT var;
    CLSID   clsidMinorId;

    m_fIsQuorumCapable = TRUE;
    m_fIsMultiNodeCapable = TRUE;

    VariantInit( &var );

    hr = HrGetWMIProperty( pDiskIn, L"Name", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrCreateFriendlyName( var.bstrVal );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"DeviceID", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_bstrDeviceID = SysAllocString( var.bstrVal );
    if (m_bstrDeviceID == NULL )
    {
        goto OutOfMemory;
    } // if:

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"Description", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_bstrDescription = SysAllocString( var.bstrVal );
    if ( m_bstrDescription == NULL  )
    {
        goto OutOfMemory;
    } // if:

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"SCSIBus", VT_I4, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_ulSCSIBus = var.lVal;

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"SCSITargetId", VT_I4, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_ulSCSITid = var.lVal;

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"SCSIPort", VT_I4, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_ulSCSIPort = var.lVal;

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"SCSILogicalUnit", VT_I4, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_ulSCSILun = var.lVal;

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"Index", VT_I4, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_idxDevice = var.lVal;

    VariantClear( &var );

    hr = HrGetWMIProperty( pDiskIn, L"Signature", VT_I4, &var );
    if ( hr == WBEM_E_NOT_FOUND )
    {
        //
        //  If the signature is not found then log it and let everything continue.
        //

        LOG_STATUS_REPORT_STRING2(
                  L"%1!ws! resource '%2!ws!' does not have a signature property."
                , GetResTypeName()
                , m_bstrName
                , hr
                );
        var.lVal = 0L;
        hr = S_OK;
    } // if:

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    //  Did we actually get a value?  Could be VT_NULL to indicate that it is empty.
    //  We only want VT_I4 values...
    //

    if ( var.vt == VT_I4 )
    {
        m_dwSignature = (DWORD) var.lVal;
    } // else if:

    LOG_STATUS_REPORT_STRING3(
              L"%1!ws! resource '%2!ws!' has signature %3!x!."
            , GetResTypeName()
            , m_bstrName
            , m_dwSignature
            , hr
            );

    if ( FAILED( hr ) )
    {
        STATUS_REPORT_STRING2_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_StorageResource_Signature
                , IDS_ERROR_DISK_SIGNATURE
                , GetDisplayName()
                , m_bstrName
                , IDS_ERROR_DISK_SIGNATURE_REF
                , hr
                );
        goto Cleanup;
    } // if:

    VariantClear( &var );

    hr = HrGetPartitionInfo( pDiskIn, pfRetainObjectOut );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    //  HrGetPartitionInfo() returns S_FALSE when it cannot get the partition info for a disk.
    //  This is usually caused by the disk already being under ClusDisk control.  This is not
    //  an error, it just means we cannot query the partition or logical drive info.
    //
    if ( hr == S_OK )
    {
        hr = HrCreateFriendlyName();
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        //
        //  Since we have partition info we also have a signature and need to see if this
        //  disk is cluster capable.

        hr = HrIsClusterCapable();
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        //
        //  If the disk is not cluster capable then we don't want the enumerator
        //  to keep it.
        //
        if ( hr == S_FALSE )
        {
            HRESULT hrTemp;

            STATUS_REPORT(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_StorageResource_Cluster_Capable
                    , IDS_INFO_DISK_CLUSTER_CAPABLE
                    , hr
                    );

            hrTemp = CoCreateGuid( &clsidMinorId );
            if ( FAILED( hrTemp ) )
            {
                LOG_STATUS_REPORT(
                          L"Could not create a guid for a not cluster capable disk minor task ID"
                        , hrTemp
                        );
                clsidMinorId = IID_NULL;
            } // if:

            *pfRetainObjectOut = FALSE;
            STATUS_REPORT_STRING_REF(
                      TASKID_Minor_StorageResource_Cluster_Capable
                    , clsidMinorId
                    , IDS_INFO_DISK_NOT_CLUSTER_CAPABLE
                    , m_bstrFriendlyName
                    , IDS_INFO_DISK_NOT_CLUSTER_CAPABLE_REF
                    , hr
                    );
            LOG_STATUS_REPORT_STRING2(
                      L"The %1!ws! resource '%2!ws!' is not cluster capable"
                    , GetResTypeName()
                    , m_bstrFriendlyName
                    , hr
                    );
        } // if:
    } // if:

    goto Cleanup;

OutOfMemory:

    hr = E_OUTOFMEMORY;
    STATUS_REPORT(
              TASKID_Major_Find_Devices
            , TASKID_Minor_SetWbemObject_StorageResource
            , IDS_ERROR_OUTOFMEMORY
            , hr
            );

Cleanup:

    VariantClear( &var );

    return hr;

} //*** CStorageResource::SetWbemObject


//////////////////////////////////////////////////////////////////////////////
// CStorageResource -- IEnumClusCfgPartitions interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Next
//
//  Description:
//
//
//  Arguments:
//
//  Return Value:
//      S_OK
//          Success
//
//      E_POINTER
//          The rgpPartitionInfoOut param is NULL.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::Next(
      ULONG                       cNumberRequestedIn
    , IClusCfgPartitionInfo **    rgpPartitionInfoOut
    , ULONG *                     pcNumberFetchedOut
    )
{
    HRESULT                 hr = S_FALSE;
    ULONG                   cFetched = 0;
    ULONG                   idx;
    IClusCfgPartitionInfo * piccpi = NULL;

    if ( rgpPartitionInfoOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_Next_StorageResource
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    if ( pcNumberFetchedOut != NULL )
    {
        *pcNumberFetchedOut = 0;
    } // if:

    if ( m_prgPartitions == NULL )
    {
        LOG_STATUS_REPORT_MINOR_STRING(
                  TASKID_Minor_StorageResource_No_Partitions
                , L"The %1!ws! resource type not have a partitions enumerator"
                , GetDisplayName()
                , hr
                );
        goto Cleanup;
    } // if:

    cFetched = min( cNumberRequestedIn, ( m_idxNextPartition - m_idxEnumPartitionNext ) );

    for ( idx = 0; idx < cFetched; idx++, m_idxEnumPartitionNext++ )
    {
        hr = ((*m_prgPartitions)[ m_idxEnumPartitionNext ])->TypeSafeQI( IClusCfgPartitionInfo, &piccpi );
        if ( FAILED( hr ) )
        {
            LOG_STATUS_REPORT( L"CStorageResource::Next() could not query for IClusCfgPartitionInfo.", hr );
            break;
        } // if:

        rgpPartitionInfoOut[ idx ] = piccpi;
    } // for:

    if ( FAILED( hr ) )
    {
        ULONG   idxStop = idx;

        m_idxEnumPartitionNext -= idx;

        for ( idx = 0; idx < idxStop; idx++ )
        {
            (rgpPartitionInfoOut[ idx ])->Release();
        } // for:

        cFetched = 0;
        goto Cleanup;
    } // if:

    if ( pcNumberFetchedOut != NULL )
    {
        *pcNumberFetchedOut = cFetched;
    } // if:

    if ( cFetched < cNumberRequestedIn )
    {
        hr = S_FALSE;
    } // if:

Cleanup:

    return hr;

} //*** CStorageResource::Next


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Skip
//
//  Description:
//
//
//  Arguments:
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
STDMETHODIMP
CStorageResource::Skip(
    ULONG cNumberToSkipIn
    )
{
    HRESULT hr = S_OK;

    m_idxEnumPartitionNext += cNumberToSkipIn;
    if ( m_idxEnumPartitionNext > m_idxNextPartition )
    {
        m_idxEnumPartitionNext = m_idxNextPartition;
        hr = S_FALSE;
    } // if:

    return hr;

} //*** CStorageResource::Skip


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Reset
//
//  Description:
//
//
//  Arguments:
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
STDMETHODIMP
CStorageResource::Reset( void )
{
    HRESULT hr = S_OK;

    m_idxEnumPartitionNext = 0;

    return hr;

} //*** CStorageResource::Reset


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Clone
//
//  Description:
//
//
//  Arguments:
//
//  Return Value:
//      S_OK
//          Success
//
//      E_POINTER
//          The ppEnumClusCfgPartitionsOut param is NULL.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::Clone(
    IEnumClusCfgPartitions ** ppEnumClusCfgPartitionsOut
    )
{
    HRESULT hr = S_OK;

    if ( ppEnumClusCfgPartitionsOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_Clone_StorageResource
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    hr = E_NOTIMPL;

Cleanup:

    return hr;

} //*** CStorageResource::Clone


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::Count
//
//  Description:
//
//
//  Arguments:
//
//  Return Value:
//      S_OK
//          Success
//
//      E_POINTER
//          The pnCountOut param is NULL.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::Count(
    DWORD * pnCountOut
    )
{
    HRESULT hr = S_OK;

    if ( pnCountOut == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    *pnCountOut = m_cPartitions;

Cleanup:

    return hr;

} //*** CStorageResource::Count


//////////////////////////////////////////////////////////////////////////////
// CStorageResource class -- IStorageProperties interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::IsThisLogicalDisk
//
//  Description:
//
//  Arguments:
//      None.
//
//  Return Value:
//
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::IsThisLogicalDisk(
    WCHAR cLogicalDiskIn
    )
{
    HRESULT                         hr = S_FALSE;
    ULONG                           idx;
    IPartitionProperties *          pipp = NULL;

    for ( idx = 0; idx < m_idxNextPartition; idx++ )
    {
        hr = ( ((*m_prgPartitions)[ idx ])->TypeSafeQI( IPartitionProperties, &pipp ) );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = pipp->HrIsThisLogicalDisk( cLogicalDiskIn );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        if ( hr == S_OK )
        {
            break;
        } // if:

        pipp->Release();
        pipp = NULL;
    } // for:

Cleanup:

    if ( pipp != NULL )
    {
        pipp->Release();
    } // if:

    return hr;

} //*** CStorageResource::IsThisLogicalDisk


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetSCSIBus
//
//  Description:
//
//  Arguments:
//      None.
//
//  Return Value:
//
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrGetSCSIBus(
    ULONG * pulSCSIBusOut
    )
{
    HRESULT hr = S_OK;

    if ( pulSCSIBusOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetSCSIBus
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    *pulSCSIBusOut = m_ulSCSIBus;

Cleanup:

    return hr;

} //*** CStorageResource::HrGetSCSIBus


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetSCSIPort
//
//  Description:
//
//  Arguments:
//      None.
//
//  Return Value:
//
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrGetSCSIPort(
    ULONG * pulSCSIPortOut
    )
{
    HRESULT hr = S_OK;

    if ( pulSCSIPortOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetSCSIPort
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    *pulSCSIPortOut = m_ulSCSIPort;

Cleanup:

    return hr;

} //*** CStorageResource::HrGetSCSIPort


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetDeviceID
//
//  Description:
//
//  Arguments:
//      None.
//
//  Return Value:
//
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrGetDeviceID(
    BSTR * pbstrDeviceIDOut
    )
{
    assert( m_bstrDeviceID != NULL );

    HRESULT hr = S_OK;

    if ( pbstrDeviceIDOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetDeviceID_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    *pbstrDeviceIDOut = SysAllocString( m_bstrDeviceID );
    if ( *pbstrDeviceIDOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetDeviceID_Memory
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
    } // if:

Cleanup:

    return hr;

} //*** CStorageResource::HrGetDeviceID


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetSignature
//
//  Description:
//
//  Arguments:
//      None.
//
//  Return Value:
//
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrGetSignature(
    DWORD * pdwSignatureOut
    )
{
    assert( m_dwSignature != 0 );

    HRESULT hr = S_OK;

    if ( pdwSignatureOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetSignature_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    *pdwSignatureOut = m_dwSignature;

Cleanup:

    return hr;

} //*** CStorageResource::HrGetSignature


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrSetFriendlyName
//
//  Description:
//
//  Arguments:
//
//  Return Value:
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrSetFriendlyName(
    LPCWSTR pcszFriendlyNameIn
    )
{
    HRESULT hr = S_OK;
    BSTR    bstr = NULL;

    if ( pcszFriendlyNameIn == NULL )
    {
        hr = E_INVALIDARG;
        goto Cleanup;
    } // if:

    bstr = SysAllocString( pcszFriendlyNameIn );
    if ( bstr == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrSetFriendlyName_StorageResource
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
        goto Cleanup;
    } // if:

    SysFreeString( m_bstrFriendlyName );
    m_bstrFriendlyName = bstr;

    LOG_STATUS_REPORT_STRING2(
              L"Setting %1!ws! resource friendly name to '%2!ws!'."
            , GetResTypeName()
            , m_bstrFriendlyName
            , hr
            );

Cleanup:

    return hr;

} //*** CStorageResource::HrSetFriendlyName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetDeviceIndex
//
//  Description:
//
//  Arguments:
//
//  Return Value:
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrGetDeviceIndex(
    DWORD * pidxDeviceOut
    )
{
    HRESULT hr = S_OK;

    if ( pidxDeviceOut == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    *pidxDeviceOut = m_idxDevice;

Cleanup:

    return hr;

} //*** CStorageResource::HrGetDeviceIndex


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::CanBeManaged
//
//  Description:
//
//  Arguments:
//
//  Return Value:
//      S_OK
//          The device is managed.
//
//      S_FALSE
//          The device is not managed.
//
//      Win32 error as HRESULT when an error occurs.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::CanBeManaged( void )
{
    HRESULT                         hr = S_OK;
    ULONG                           idx;
    IPartitionProperties *          pipp = NULL;

    //
    //  Turn off the manageable state because this disk may already be managed by
    //  another node, or it may be RAW.
    //

    m_fIsManagedByDefault = FALSE;

    //
    //  A disk must have at least one NTFS partition in order to be a quorum
    //  resource.
    //

    m_fIsQuorumCapable = FALSE;
    m_fIsMultiNodeCapable = FALSE;

    //
    //  If this disk has no partitions then it may already be managed by
    //  another node, or it may be RAW.
    //

    if ( m_idxNextPartition == 0 )
    {
        hr = S_FALSE;
        goto Cleanup;
    } // if:

    //
    //  Enum the partitions and set the quorum capable flag if an NTFS
    //  partition is found.
    //

    for ( idx = 0; idx < m_idxNextPartition; idx++ )
    {
        hr = ( ((*m_prgPartitions)[ idx ])->TypeSafeQI( IPartitionProperties, &pipp ) );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = pipp->HrIsNTFS();
        if ( hr == S_OK )
        {
            m_fIsQuorumCapable = TRUE;
            m_fIsMultiNodeCapable = TRUE;
            m_fIsManagedByDefault = TRUE;
            break;
        } // if:

        pipp->Release();
        pipp = NULL;
    } // for:

Cleanup:

    LOG_STATUS_REPORT_STRING3(
          L"%1!ws! resource '%2!ws!' %3!ws! quorum capable."
        , GetResTypeName()
        , ( ( m_bstrFriendlyName != NULL ) ? m_bstrFriendlyName : m_bstrName )
        , ( ( m_fIsQuorumCapable == TRUE ) ? L"is" : L"is NOT" )
        , hr
        );

    if ( FAILED( hr ) )
    {
        LOG_STATUS_REPORT( L"CStorageResource::CanBeManaged failed.", hr );
    } // if:

    if ( pipp != NULL )
    {
        pipp->Release();
    } // if:

    return hr;

} //*** CStorageResource::CanBeManaged


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrIsDynamicDisk
//
//  Description:
//      Is this disk a "dynamic" disk?  Dynamic disks are those disks that
//      contain LDM partitions.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          This is a dynamic disk.
//
//      S_FALSE
//          This is not a dynamic disk.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrIsDynamicDisk( void )
{
    HRESULT hr = S_OK;

    if ( m_fIsDynamicDisk == FALSE )
    {
        hr = S_FALSE;
    } // if:

    return hr;

} //*** CStorageResource::HrIsDynamicDisk


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrIsGPTDisk
//
//  Description:
//      Is this disk a "GPT" disk?  GPT disks are those disks that
//      contain GPT partitions.
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          This is a GPT disk.
//
//      S_FALSE
//          This is not a GPT disk.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrIsGPTDisk( void )
{
    HRESULT hr = S_OK;

    if ( m_fIsGPTDisk == FALSE )
    {
        hr = S_FALSE;
    } // if:

    return hr;

} //*** CStorageResource::HrIsGPTDisk


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetDiskNames
//
//  Description:
//      Get the names of this disk, both its friendly and device names.
//
//  Arguments:
//      pbstrDiskNameOut
//
//      pbstrDeviceNameOut
//
//  Return Value:
//      S_OK
//          Success;
//
//      E_OUTOFMEMORY
//
//      E_POINTER
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResource::HrGetDiskNames(
      BSTR * pbstrDiskNameOut
    , BSTR * pbstrDeviceNameOut
    )
{
    assert( m_bstrName != NULL );
    assert( m_bstrFriendlyName != NULL );

    assert( pbstrDiskNameOut != NULL );
    assert( pbstrDeviceNameOut != NULL );

    HRESULT hr = S_OK;
    BSTR    bstr = NULL;

    if ( ( pbstrDiskNameOut == NULL ) || ( pbstrDeviceNameOut == NULL ) )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    bstr = SysAllocString( m_bstrFriendlyName );
    if ( bstr == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    *pbstrDiskNameOut = bstr;
    bstr = NULL;

    bstr = SysAllocString( m_bstrName );
    if ( bstr == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    *pbstrDeviceNameOut = bstr;
    bstr = NULL;

Cleanup:

    SysFreeString( bstr );

    return hr;

} //*** CStorageResource::HrGetDiskNames


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource::HrGetPartitionInfo
//
//  Description:
//      Gather the partition information.
//
//  Arguments:
//      None.
//
//  Return Value:
//
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrGetPartitionInfo(
      IWbemClassObject *    pDiskIn
    , BOOL *                pfRetainObjectOut
    )
{
    assert( pDiskIn != NULL );
    assert( pfRetainObjectOut != NULL );

    HRESULT                 hr;
    VARIANT                 var;
    VARIANT                 varDiskName;
    WCHAR                   szBuf[ 256 ];
    IEnumWbemClassObject *  pPartitions = NULL;
    IWbemClassObject *      pPartition = NULL;
    ULONG                   ulReturned;
    BSTR                    bstrQuery = NULL;
    BSTR                    bstrWQL = NULL;
    DWORD                   cPartitions;

    UNREFERENCED_PARAMETER( pfRetainObjectOut );

    bstrWQL = SysAllocString( L"WQL" );
    if ( bstrWQL == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetPartitionInfo
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
        goto Cleanup;
    } // if:

    VariantInit( &var );
    VariantInit( &varDiskName );

    //
    //  Need to enum the partition(s) of this disk to determine if it is booted
    //  bootable.
    //
    hr = HrGetWMIProperty( pDiskIn, L"DeviceID", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = StringCchPrintfW(
                  szBuf
                , RTL_NUMBER_OF( szBuf )
                , L"Associators of {Win32_DiskDrive.DeviceID='%ws'} where AssocClass=Win32_DiskDriveToDiskPartition"
                , var.bstrVal
                );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    bstrQuery = SysAllocString( szBuf );
    if ( bstrQuery == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetPartitionInfo
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
        goto Cleanup;
    } // if:

    hr = m_pIWbemServices->ExecQuery(
              bstrWQL
            , bstrQuery
            , WBEM_FLAG_FORWARD_ONLY
            , NULL
            , &pPartitions
            );
    if ( FAILED( hr ) )
    {
        STATUS_REPORT_STRING_REF(
                TASKID_Major_Find_Devices
                , TASKID_Minor_WMI_DiskDrivePartitions_Qry_Failed
                , IDS_ERROR_WMI_DISKDRIVEPARTITIONS_QRY_FAILED
                , var.bstrVal
                , IDS_ERROR_WMI_DISKDRIVEPARTITIONS_QRY_FAILED_REF
                , hr
                );
        goto Cleanup;
    } // if:

    for ( cPartitions = 0; ; cPartitions++ )
    {
        hr = pPartitions->Next( WBEM_INFINITE, 1, &pPartition, &ulReturned );
        if ( ( hr == S_OK ) && ( ulReturned == 1 ) )
        {

            hr = HrIsPartitionLDM( pPartition );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            //
            //  If the partition is logical disk manager (LDM)  then
            //  we cannot accept this disk therefore cannot manage it.
            //

            if ( hr == S_OK )
            {
                m_fIsDynamicDisk = TRUE;
            } // if:

            hr = HrIsPartitionGPT( pPartition );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( hr == S_OK )
            {
                m_fIsGPTDisk = TRUE;
            } // if:

            hr = HrCreatePartitionInfo( pPartition );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            pPartition->Release();
            pPartition = NULL;
        } // if:
        else if ( ( hr == S_FALSE ) && ( ulReturned == 0 ) )
        {
            break;
        } // else if:
        else
        {
            STATUS_REPORT_STRING_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_WQL_Partition_Qry_Next_Failed
                    , IDS_ERROR_WQL_QRY_NEXT_FAILED
                    , bstrQuery
                    , IDS_ERROR_WQL_QRY_NEXT_FAILED_REF
                    , hr
                    );
            goto Cleanup;
        } // else:
    } // for:

    //
    //  The enumerator can be empty because we cannot read the partition info from
    //  clustered disks.  If the enumerator was empty retain the S_FALSE, otherwise
    //  return S_OK if count is greater than 0.
    //

    if ( cPartitions > 0 )
    {
        hr = S_OK;
    } // if:
    else
    {
        LOG_STATUS_REPORT_STRING2(
                  L"The %1!ws! resource '%2!ws!' does not have any partitions and will not be managed."
                , GetResTypeName()
                , var.bstrVal
                , hr
                );
        m_fIsManagedByDefault = FALSE;
    } // else:

Cleanup:

    VariantClear( &var );
    VariantClear( &varDiskName );

    SysFreeString( bstrQuery );
    SysFreeString( bstrWQL );

    if ( pPartition != NULL )
    {
        pPartition->Release();
    } // if:

    if ( pPartitions != NULL )
    {
        pPartitions->Release();
    } // if:

    return hr;

} //*** CStorageResource::HrGetPartitionInfo


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrCreatePartitionInfo
//
//  Description:
//      Create a partition info from the passes in WMI partition.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success
//
//      S_FALSE
//          The file system was not NTFS.
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrCreatePartitionInfo(
    IWbemClassObject * pPartitionIn
    )
{
    assert( m_bstrDeviceID != NULL );

    HRESULT                     hr = S_OK;
    IUnknown *                  punk = NULL;
    IWMIObject *                pimswo = NULL;
    IPartitionProperties *      pipp = NULL;
    BOOL                        fRetainObject = TRUE;

    hr = CoCreateInstance(
              CLSID_CPartitionInfo
            , NULL
            , CLSCTX_INPROC_SERVER
            , IID_IUnknown
            , reinterpret_cast< void ** >( &punk )
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = punk->TypeSafeQI( IPartitionProperties, &pipp );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = pipp->HrSetDeviceID( m_bstrDeviceID );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

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

    hr = punk->TypeSafeQI( IWMIObject, &pimswo );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = pimswo->SetWbemObject( pPartitionIn, &fRetainObject );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( fRetainObject )
    {
        hr = HrAddPartitionToArray( punk );
    } // if:

Cleanup:

    if ( pipp != NULL )
    {
        pipp->Release();
    } // if:

    if ( pimswo != NULL )
    {
        pimswo->Release();
    } // if:

    if ( punk != NULL )
    {
        punk->Release();
    } // if:

    return hr;

} //*** CStorageResource::HrCreatePartitionInfo


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrAddPartitionToArray
//
//  Description:
//      Add the passed in partition to the array of punks that holds the
//      partitions.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrAddPartitionToArray(
    IUnknown * punkIn
    )
{
    HRESULT     hr = S_OK;
    IUnknown *  ((*prgpunks)[]) = NULL;

    prgpunks = (IUnknown *((*)[])) HEAPREALLOC(
                      m_prgPartitions
                    , sizeof( IUnknown * ) * ( m_idxNextPartition + 1 )
                    , HEAP_ZERO_MEMORY
                    );
    if ( prgpunks == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrAddPartitionToArray
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
        goto Cleanup;
    } // if:

    m_prgPartitions = prgpunks;

    (*m_prgPartitions)[ m_idxNextPartition++ ] = punkIn;
    punkIn->AddRef();
    m_cPartitions += 1;

Cleanup:

    return hr;

} //*** CStorageResource::HrAddPartitionToArray


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrCreateFriendlyName
//
//  Description:
//      Create a cluster friendly name.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success
//
//      S_FALSE
//          Success, but a friendly name could not be created.
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrCreateFriendlyName( void )
{
    HRESULT                         hr = S_FALSE;
    WCHAR *                         pwsz = NULL;
    WCHAR *                         pwszTmp = NULL;
    DWORD                           cch;
    DWORD                           idx;
    IPartitionProperties *          pipp = NULL;
    BSTR                            bstrName = NULL;
    BOOL                            fFoundLogicalDisk = FALSE;
    BSTR                            bstr = NULL;
    BSTR                            bstrDisk = NULL;

    if ( m_idxNextPartition == 0 )
    {
        goto Cleanup;
    } // if:

    hr = HrLoadStringIntoBSTR( IDS_DISK, &bstrDisk );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cch = (UINT) wcslen( bstrDisk ) + 1;

    pwsz = new WCHAR[ cch ];
    if ( pwsz == NULL )
    {
        goto OutOfMemory;
    } // if:

    hr = StringCchCopyW( pwsz, cch, bstrDisk );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    for ( idx = 0; idx < m_idxNextPartition; idx++ )
    {
        hr = ((*m_prgPartitions)[ idx ])->TypeSafeQI( IPartitionProperties, &pipp );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = pipp->HrGetFriendlyName( &bstrName );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        if ( hr == S_FALSE )
        {
            continue;
        } // if:

        fFoundLogicalDisk = TRUE;

        cch += (UINT) wcslen( bstrName ) + 1;

        pwszTmp = new WCHAR[ cch ];
        if ( pwszTmp == NULL )
        {
            goto OutOfMemory;
        } // if:

        hr = StringCchCopyW( pwszTmp, cch, pwsz );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        delete [] pwsz;

        pwsz = pwszTmp;
        pwszTmp = NULL;

        hr = StringCchCatW( pwsz, cch, bstrName );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        SysFreeString( bstrName );
        bstrName = NULL;

        pipp->Release();
        pipp = NULL;
    } // for:

    if ( !fFoundLogicalDisk )
    {
        // Ensure that that the caller doesn't fail since this is not a fatal error.
        hr = S_OK;
        goto Cleanup;
    } // if:

    bstr = SysAllocString( pwsz );
    if ( bstr == NULL )
    {
        goto OutOfMemory;
    } // if:

    SysFreeString( m_bstrFriendlyName );
    m_bstrFriendlyName = bstr;
    bstr = NULL;

    goto Cleanup;

OutOfMemory:

    hr = E_OUTOFMEMORY;
    STATUS_REPORT(
              TASKID_Major_Find_Devices
            , TASKID_Minor_HrCreateFriendlyName_VOID
            , IDS_ERROR_OUTOFMEMORY
            , hr
            );

Cleanup:

    if ( pipp != NULL )
    {
        pipp->Release();
    } // if:

    delete [] pwsz;
    delete [] pwszTmp;

    SysFreeString( bstrName );
    SysFreeString( bstrDisk );
    SysFreeString( bstr );

    return hr;

} //*** CStorageResource::HrCreateFriendlyName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrCreateFriendlyName
//
//  Description:
//      Convert the WMI disk name into a more freindly version.
//      Create a cluster friendly name.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          Success
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrCreateFriendlyName(
    BSTR bstrNameIn
    )
{
    HRESULT hr = S_OK;
    WCHAR * pwsz = NULL;
    BSTR    bstr = NULL;

    //
    //  Disk names in WMI start with "\\.\".  As a better and easy
    //  friendly name I am just going to trim these leading chars
    //  off.
    //
    pwsz = bstrNameIn + wcslen( L"\\\\.\\" );

    bstr = SysAllocString( pwsz );
    if ( bstr == NULL )
    {
        hr =  E_OUTOFMEMORY;
        STATUS_REPORT(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrCreateFriendlyName_BSTR
                , IDS_ERROR_OUTOFMEMORY
                , hr
                );
        goto Cleanup;
    } // if:

    SysFreeString( m_bstrName );
    m_bstrName = bstr;

Cleanup:

    return hr;

} //*** CStorageResource::HrCreateFriendlyName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrIsPartitionGPT
//
//  Description:
//      Is the passed in partition a GPT partition.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          The partition is a GPT partition.
//
//      S_FALSE
//          The partition is not GPT.
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//      If the type property of a Win32_DiskPartition starts with "GPT"
//      then the whole spindle has GPT partitions.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrIsPartitionGPT(
    IWbemClassObject * pPartitionIn
    )
{
    HRESULT hr = S_OK;
    VARIANT var;
    WCHAR   szData[ 4 ];
    BSTR    bstrGPT = NULL;

    VariantInit( &var );

    hr = HrLoadStringIntoBSTR( IDS_GPT, &bstrGPT );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrGetWMIProperty( pPartitionIn, L"Type", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    //  Get the fist three characters.  When the spindle has GPT partitions then
    //  these characters will be "GPT".  I am unsure if this will be localized.
    //

    hr = StringCchCopyNW( szData, RTL_NUMBER_OF( szData ), var.bstrVal, 3 );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    CharUpper( szData );

    if ( NStringCompareW( szData, RTL_NUMBER_OF( szData ), bstrGPT, SysStringLen( bstrGPT ) ) != 0 )
    {
        hr = S_FALSE;
    } // if:

Cleanup:

    VariantClear( &var );

    SysFreeString( bstrGPT );

    return hr;

} //*** CStorageResource::HrIsPartitionGPT


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrIsPartitionLDM
//
//  Description:
//      Is the passed in partition an LDM partition.
//
//  Arguments:
//
//
//  Return Value:
//      S_OK
//          The partition is an LDM partition.
//
//      S_FALSE
//          The partition is not LDM.
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//      If the type property of a Win32_DiskPartition is "logical disk
//      manager" then this disk is an LDM disk.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrIsPartitionLDM(
    IWbemClassObject * pPartitionIn
    )
{
    HRESULT hr = S_OK;
    VARIANT var;
    BSTR    bstrLDM = NULL;

    VariantInit( &var );

    hr = HrLoadStringIntoBSTR( IDS_LDM, &bstrLDM );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrGetWMIProperty( pPartitionIn, L"Type", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    CharUpper( var.bstrVal );

    if ( NBSTRCompareW( var.bstrVal, bstrLDM ) != 0 )
    {
        hr = S_FALSE;
    } // if:

Cleanup:

    VariantClear( &var );

    SysFreeString( bstrLDM );

    return hr;

} //*** CStorageResource::HrIsPartitionLDM


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResource:HrIsClusterCapable
//
//  Description:
//      Is this disk cluster capable?
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          The disk is cluster capable.
//
//      S_FALSE
//          The disk is not cluster capable.
//
//      E_OUTOFMEMORY
//          Couldn't allocate memeory.
//
//  Remarks:
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResource::HrIsClusterCapable( void )
{
    //
    // TODO: Determine whether this disk is cluster-capable.  You may need to
    //       send an IOCTL to the disk/miniport to determine this.
    //

//
//  WARNING - this is clusdisk/physical disk specific from ddk\inc\scsi.h
//

#define FILE_DEVICE_SCSI 0x0000001b
#define IOCTL_SCSI_MINIPORT_NOT_QUORUM_CAPABLE     ( ( FILE_DEVICE_SCSI << 16 ) + 0x0520 )

    HRESULT         hr = S_FALSE;
    HANDLE          hSCSIPort = NULL;
    DWORD           dwSize;
    BOOL            fRet;
    WCHAR           szSCSIPort[ 32 ];
    SRB_IO_CONTROL  srb;

    hr = StringCchPrintfW(
              szSCSIPort
            , RTL_NUMBER_OF( szSCSIPort )
            , L"\\\\.\\Scsi%d:"
            , m_ulSCSIPort
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // get handle to disk
    //

    hSCSIPort = CreateFileW(
                          szSCSIPort
                        , GENERIC_READ | GENERIC_WRITE
                        , FILE_SHARE_READ | FILE_SHARE_WRITE
                        , NULL
                        , OPEN_EXISTING
                        , FILE_ATTRIBUTE_NORMAL
                        , NULL
                        );
    if ( hSCSIPort == INVALID_HANDLE_VALUE )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        LOG_STATUS_REPORT_STRING( L"Failed to open device %1!ws!.", szSCSIPort, hr );
        goto Cleanup;
    } // if:

#define CLUSDISK_SRB_SIGNATURE "CLUSDISK"

    ZeroMemory( &srb, sizeof( srb ) );

    srb.HeaderLength = sizeof( srb );

    assert( sizeof( srb.Signature ) <= sizeof( CLUSDISK_SRB_SIGNATURE ) );
    CopyMemory( srb.Signature, CLUSDISK_SRB_SIGNATURE, sizeof( srb.Signature ) );

    srb.ControlCode = IOCTL_SCSI_MINIPORT_NOT_QUORUM_CAPABLE;

    //
    // issue mini port ioctl to determine whether the disk is cluster capable
    //

    fRet = DeviceIoControl(
                          hSCSIPort
                        , IOCTL_SCSI_MINIPORT
                        , &srb
                        , sizeof( srb )
                        , NULL
                        , 0
                        , &dwSize
                        , NULL
                        );
    if ( !fRet )
    {
        hr = S_OK;
    } // if:

Cleanup:

    if ( FAILED( hr ) )
    {
        CLSID   clsidMinorId;
        HRESULT hrTemp;

        hrTemp = CoCreateGuid( &clsidMinorId );
        if ( FAILED( hrTemp ) )
        {
            LOG_STATUS_REPORT( L"Could not create a guid for a not cluster capable disk minor task ID", hrTemp );
            clsidMinorId = IID_NULL;
        } // if:

        STATUS_REPORT_STRING2_REF(
                  TASKID_Minor_StorageResource_Cluster_Capable
                , clsidMinorId
                , IDS_ERROR_DISK_CLUSTER_CAPABLE
                , m_bstrFriendlyName
                , m_ulSCSIPort
                , IDS_ERROR_DISK_CLUSTER_CAPABLE_REF
                , hr
                );
    } // if:

    if ( hSCSIPort != NULL )
    {
        CloseHandle( hSCSIPort );
    } // if:

    return hr;

} //*** CStorageResource::HrIsClusterCapable
