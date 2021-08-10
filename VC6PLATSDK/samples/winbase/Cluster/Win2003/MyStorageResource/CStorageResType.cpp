//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CStorageResType.cpp
//
//  Description:
//      Implementation for the ClusCfg Managed Resource Type class - this
//      demonstrates how to implement the IClusCfgResourceTypeInfo interface.
//
//  Header File:
//      CStorageResType.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CStorageResType.h"


//////////////////////////////////////////////////////////////////////////////
// Define's
//////////////////////////////////////////////////////////////////////////////

//
// Some defaults for resource type creation.
//

#define CLUSTER_RESTYPE_DEFAULT_LOOKS_ALIVE     (  5 * 1000 )
#define CLUSTER_RESTYPE_DEFAULT_IS_ALIVE        ( 60 * 1000 )


//////////////////////////////////////////////////////////////////////////////
// CStorageResType -- IClusCfgResourceTypeInfo interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResType::CommitChanges
//
//  Description:
//      Components implement the CommitChanges interface to create or delete
//      resource types according to the state of the local computer.
//
//  Arguments:
//      punkClusterInfoIn
//          Interface for querying for other interfaces to get information
//          about the cluster (IClusCfgClusterInfo).
//
//      punkResTypeServicesIn
//          Interface for querying for the IClusCfgResourceTypeCreate
//          interface on.
//
//  Return Value:
//      S_OK
//          Success.
//
//      E_POINTER
//          Expected pointer argument specified as NULL.
//
//      E_UNEXPECTED
//          Unexpected commit mode.
//
//      Other HRESULTs
//          Failure.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResType::CommitChanges(
      IUnknown *    punkClusterInfoIn
    , IUnknown *    punkResTypeServicesIn
    )
{
    assert( punkClusterInfoIn != NULL );
    assert( punkResTypeServicesIn != NULL );

    HRESULT                         hr = S_OK;
    IClusCfgClusterInfo *           pccci = NULL;
    IClusCfgResourceTypeCreate *    pccrtc = NULL;
    ECommitMode                     ecm = cmUNKNOWN;

    hr = HrSendStatusReport(
          TASKID_Major_Configure_Resource_Types
        , TASKID_Minor_StorageResourceType_CommitChanges
        , 0
        , 6
        , 0
        , hr
        , IDS_CONFIGURING_RESTYPE
        , 0
        , GetDisplayName()
        );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Validate arguments
    //

    if ( ( punkClusterInfoIn == NULL ) || ( punkResTypeServicesIn == NULL ) )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if: one of the arguments is NULL

    hr = HrSendStatusReport(
          TASKID_Major_Configure_Resource_Types
        , TASKID_Minor_StorageResourceType_CommitChanges
        , 0
        , 6
        , 1
        , hr
        , IDS_CONFIGURING_RESTYPE
        , 0
        , GetDisplayName()
        );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Find out what event caused this call.
    //

    hr = punkClusterInfoIn->TypeSafeQI( IClusCfgClusterInfo, &pccci );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSendStatusReport(
          TASKID_Major_Configure_Resource_Types
        , TASKID_Minor_StorageResourceType_CommitChanges
        , 0
        , 6
        , 2
        , hr
        , IDS_CONFIGURING_RESTYPE
        , 0
        , GetDisplayName()
        );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = pccci->GetCommitMode( &ecm );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if: we could not determine the commit mode

    hr = HrSendStatusReport(
          TASKID_Major_Configure_Resource_Types
        , TASKID_Minor_StorageResourceType_CommitChanges
        , 0
        , 6
        , 3
        , hr
        , IDS_CONFIGURING_RESTYPE
        , 0
        , GetDisplayName()
        );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = S_OK;

    //
    //  Check if we are creating a cluster or adding nodes to an existing cluster.
    //

    if ( ( ecm == cmCREATE_CLUSTER ) || ( ecm == cmADD_NODE_TO_CLUSTER ) )
    {
        //
        //  We are either creating a cluster on this node or adding it to a
        //  cluster.  We need to register our resource type and the associated
        //  Cluadmin extension dll.
        //

        //
        // First, register our resource type.
        //

        hr = punkResTypeServicesIn->TypeSafeQI( IClusCfgResourceTypeCreate, &pccrtc );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = pccrtc->Create(
                          GetResTypeName()
                        , GetDisplayName()
                        , GetDllName()
                        , CLUSTER_RESTYPE_DEFAULT_LOOKS_ALIVE
                        , CLUSTER_RESTYPE_DEFAULT_IS_ALIVE
                        );

        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrSendStatusReport(
              TASKID_Major_Configure_Resource_Types
            , TASKID_Minor_StorageResourceType_CommitChanges
            , 0
            , 6
            , 4
            , hr
            , IDS_CONFIGURED_RESTYPE
            , 0
            , GetResTypeName()
            , GetDisplayName()
            , GetDllName()
            );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

/*
        //
        // TODO:    If your resource type has a Cluadmin extension dll register it
        //          with the cluster here.

        hr = pccrtc->RegisterAdminExtensions(
                          GetDisplayName()
                        , 1
                        , &CLSID_CoMyResDllEx
                        );

        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrSendStatusReport(
              TASKID_Major_Configure_Resource_Types
            , TASKID_Minor_StorageResourceType_CommitChanges
            , 0
            , 6
            , 5
            , hr
            , IDS_CONFIGURED_EXTENSION
            , 0
            , GetDisplayName()
            );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
*/

    } // if: we are either forming or joining ( but not both )
    else
    {
        //
        // Check for invalid commit modes.
        //

        if ( ( ecm == cmUNKNOWN ) || ( ecm >= cmMAX ) )
        {
            hr = E_UNEXPECTED;
            goto Cleanup;
        } // if: invalid commit mode

        assert( ecm == cmCLEANUP_NODE_AFTER_EVICT );

        //
        // If we are here, then this node has been evicted.
        //

        //
        // TODO: Add code to cleanup your resource type after the
        // local node has been evicted from the cluster.
        //
        // If your resource has a different configuration when it's part of
        // cluster then this is where you return it to stand-alone server mode.
        //

        hr = S_OK;

    } // else: we are not forming nor joining

    //
    // Success.
    //

    HrSendStatusReport(
          TASKID_Major_Configure_Resource_Types
        , TASKID_Minor_StorageResourceType_CommitChanges
        , 0
        , 6
        , 6
        , hr
        , IDS_CONFIGURING_RESTYPE
        , 0
        , GetDisplayName()
        );

Cleanup:

    if ( pccci != NULL )
    {
        pccci->Release();
        pccci = NULL;
    } // if:

    if ( pccrtc != NULL )
    {
        pccrtc->Release();
        pccrtc = NULL;
    } // if:

    if ( FAILED( hr ) )
    {
        HrSendStatusReport(
              TASKID_Major_Configure_Resource_Types
            , TASKID_Minor_StorageResourceType_CommitChanges
            , 0
            , 6
            , 6
            , hr
            , IDS_CONFIGURING_RESTYPE_FAILED
            , 0
            , GetDisplayName()
            );
    } // if: FAILED

    return hr;

} //*** CStorageResType::CommitChanges


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResType::GetTypeGUID
//
//  Description:
//      Retrieves the globally unique identifier of this resource type.
//
//  Arguments:
//      pguidGUIDOut
//          Upon success will point to the resource type's (static) GUID.
//
//  Return Value:
//      S_OK
//          Success.
//
//      E_POINTER
//          Expected pointer argument specified as NULL.
//
//      Other HRESULTs
//          Failure.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResType::GetTypeGUID(
    GUID * pguidGUIDOut
    )
{
    assert( pguidGUIDOut != NULL );

    HRESULT hr = S_OK;

    if ( pguidGUIDOut == NULL )
    {
        hr = E_POINTER;
    } // if: the output pointer is NULL
    else
    {
        *pguidGUIDOut = RESTYPE_StorageResource;
    } // else: the output pointer is valid

    return hr;

} //*** CStorageResType::GetTypeGUID


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResType::GetTypeName
//
//  Description:
//      Retrieves the resource type name of this resource type.
//
//  Arguments:
//      pbstrTypeNameOut
//          Upon success will point to an allocated BSTR containing the type name.
//
//  Return Value:
//      S_OK
//          Success.
//
//      E_POINTER
//          Expected pointer argument specified as NULL.
//
//      E_OUTOFMEMORY
//          Out of memory.
//
//      Other HRESULTs
//          Failure.
//
//  Remarks:
//      If S_OK is returned the caller needs to call SysFreeString on pbstrTypeNameOut.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CStorageResType::GetTypeName(
    BSTR* pbstrTypeNameOut
    )
{
    assert( pbstrTypeNameOut != NULL );

    HRESULT hr = S_OK;

    if ( pbstrTypeNameOut == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if: the output pointer is NULL

    *pbstrTypeNameOut = SysAllocString( GetResTypeName() );
    if ( *pbstrTypeNameOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if: memory for the resource type name could not be allocated

Cleanup:

    return hr;

} //*** CStorageResType::GetTypeName


/////////////////////////////////////////////////////////////////////////////
// CStorageResType -- IClusCfgStartupListener interface.
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CStorageResType::Notify
//
//  Description:
//      This method is called to inform a component that the cluster service
//      has started on this computer.
//
//      This component is registered for the cluster service startup notification
//      as a part of the cluster service upgrade (clusocm.inf). This method creates
//      the required resource type and associates the cluadmin extension dll then
//      deregisters itself from this notification.
//
//  Arguments:
//      IUnknown * punkIn
//          The component that implements this Punk may also provide services
//          that are useful to the implementor of this method. For example,
//          this component usually implements the IClusCfgResourceTypeCreate
//          interface.
//
//  Return Values:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CStorageResType::Notify(
    IUnknown * punkIn
    )
{
    HRESULT                         hr = S_OK;
    IClusCfgResourceTypeCreate *    piccrtc = NULL;
    //const GUID *                    guidAdminEx = &CLSID_CoMyResDllEx
    ICatRegister *                  pcrCatReg = NULL;
    CATID                           rgCatId[ 1 ];

    hr = HrSendStatusReport(
                  TASKID_Major_Client_And_Server_Log
                , IID_NULL
                , 1
                , 1
                , 1
                , hr
                , L"Startup Notify called for resource type '%1!ws!'."
                , (LPCWSTR) NULL
                , GetResTypeName()
                );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = punkIn->TypeSafeQI( IClusCfgResourceTypeCreate, &piccrtc );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    //
    // Create the resource type.
    //

    hr = piccrtc->Create(
                      GetResTypeName()
                    , GetDisplayName()
                    , GetDllName()
                    , 5 *  1000
                    , 60 * 1000
                    );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSendStatusReport(
                  TASKID_Major_Client_And_Server_Log
                , IID_NULL
                , 1
                , 1
                , 1
                , hr
                , L"Successfully created resource type '%1!ws!'."
                , (LPCWSTR) NULL
                , GetResTypeName()
                );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

/*
    //
    // TODO:    If your resource type has a Cluadmin extension dll register it
    //          with the cluster here.

    //
    // Register the cluadmin extensions.
    //

    hr = piccrtc->RegisterAdminExtensions(
                      GetResTypeName()
                    , 1
                    , guidAdminEx
                    );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSendStatusReport(
                  TASKID_Major_Client_And_Server_Log
                , IID_NULL
                , 1
                , 1
                , 1
                , hr
                , L"Successfully registered Cluster Administrator extensions for resource type '%1!ws!'."
                , (LPCWSTR) NULL
                , GetResTypeName()
                );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:
*/

    //
    // Unregister from StartupListener notifications.
    //

    hr = CoCreateInstance(
              CLSID_StdComponentCategoriesMgr
            , NULL
            , CLSCTX_INPROC_SERVER
            , __uuidof( pcrCatReg )
            , reinterpret_cast< void ** >( &pcrCatReg )
            );

    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if: CoCreate failed

    rgCatId[ 0 ] = CATID_ClusCfgStartupListeners;

    hr = pcrCatReg->UnRegisterClassImplCategories( CLSID_CStorageResType, RTL_NUMBER_OF( rgCatId ), rgCatId );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if: deregister failed

    pcrCatReg->Release();
    pcrCatReg = NULL;

    hr = HrSendStatusReport(
                  TASKID_Major_Client_And_Server_Log
                , IID_NULL
                , 1
                , 1
                , 1
                , hr
                , L"Successfully unregistered the '%1!ws!' resource type from StartupListener notifications."
                , (LPCWSTR) NULL
                , GetResTypeName()
                );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    if ( piccrtc != NULL )
    {
        piccrtc->Release();
    } // if:

    if ( pcrCatReg != NULL )
    {
        pcrCatReg->Release();
    } // if:

    return hr;

} //*** CStorageResType::Notify
