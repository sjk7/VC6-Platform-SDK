//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CClusterUtils.cpp
//
//  Description:
//      This file contains the implementation of the CClusterUtils class.
//
//  Header File:
//      CClusterUtils.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CClusterUtils.h"


//////////////////////////////////////////////////////////////////////////////
// CClusterUtils class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils::HrIsGroupOwnedByThisNode
//
//  Description:
//      Is the cluster group hGroupIn owned by node bstrNodeNameIn?
//
//  Arguments:
//      hGroupIn
//          A handle to a cluster group.
//
//      bstrNodeNameIn
//          Node name to compare against the group's owning node name.
//
//  Return Value:
//      S_OK
//          The group is owned by the node.
//
//      S_FALSE
//          The group is not owned by the node.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrIsGroupOwnedByThisNode(
      HGROUP  hGroupIn
    , BSTR    bstrNodeNameIn
    )
{
    assert( hGroupIn != NULL );
    assert( bstrNodeNameIn != NULL );

    HRESULT             hr = S_OK;
    DWORD               sc = ERROR_SUCCESS;
    WCHAR *             pwszNodeName = NULL;
    DWORD               cchNodeName = 33;
    CLUSTER_GROUP_STATE cgs;

    pwszNodeName = new WCHAR[ cchNodeName ];
    if ( pwszNodeName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    cgs = GetClusterGroupState( hGroupIn, pwszNodeName, &cchNodeName );
    sc = GetLastError();
    if ( sc == ERROR_MORE_DATA )
    {
        delete [] pwszNodeName;
        pwszNodeName = NULL;
        cchNodeName++;

        pwszNodeName = new WCHAR[ cchNodeName ];
        if ( pwszNodeName == NULL )
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        } // if:

        cgs = GetClusterGroupState( hGroupIn, pwszNodeName, &cchNodeName );
    } // if: the pwszNodeName buffer wasn't big enough

    if ( cgs == ClusterGroupStateUnknown )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if: GetClusterGroupState failed

    if ( NIStringCompareW(
                  bstrNodeNameIn
                , SysStringLen( bstrNodeNameIn )
                , pwszNodeName
                , cchNodeName
                )
         == 0
       )
    {
        hr = S_OK;
    } // if: Node names match so this group is owned by that node.
    else
    {
        hr = S_FALSE;
    } // else: Node names do not match and the group is owned by another node.

Cleanup:

    delete [] pwszNodeName;

    return hr;

} //*** CClusterUtils::HrIsGroupOwnedByThisNode


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils:HrIsNodeClustered
//
//  Description:
//      Is this node a member of a cluster?
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          The node is clustered.
//
//      S_FALSE
//          The node is NOT clustered.
//
//      Other
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrIsNodeClustered( void )
{
    HRESULT hr = S_FALSE;
    DWORD   sc = ERROR_SUCCESS;
    DWORD   dwClusterState;

    //
    // Get the cluster state of the local node.
    // Ignore the case where the service does not exist so that
    // EvictCleanup can do its job.
    //

    sc = GetNodeClusterState( NULL, &dwClusterState );
    if ( ( sc != ERROR_SUCCESS ) && ( sc != ERROR_SERVICE_DOES_NOT_EXIST ) )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if : GetNodeClusterState failed

    if ( ( dwClusterState == ClusterStateRunning ) || ( dwClusterState == ClusterStateNotRunning ) )
    {
        hr = S_OK;
    } // if:

Cleanup:

    return hr;

} //*** CClusterUtils::HrIsNodeClustered


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils:HrEnumNodeResources
//
//  Description:
//      Enumerate the resources owned by this node.
//
//  Arguments:
//      bstrNodeNameIn
//          aa
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrEnumNodeResources(
    BSTR bstrNodeNameIn
    )
{
    assert( bstrNodeNameIn != NULL );

    HRESULT     hr = S_FALSE;
    DWORD       sc = ERROR_SUCCESS;
    DWORD       idx = 0;
    HCLUSTER    hCluster = NULL;
    HCLUSENUM   hEnum = NULL;
    DWORD       dwType;
    WCHAR *     pwszGroupName = NULL;
    DWORD       cchGroupName = 33;
    HGROUP      hGroup = NULL;

    hCluster = OpenCluster( NULL );
    if ( hCluster == NULL )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    hEnum = ClusterOpenEnum( hCluster, CLUSTER_ENUM_GROUP );
    if ( hEnum == NULL )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    pwszGroupName = new WCHAR[ cchGroupName ];
    if ( pwszGroupName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    for ( idx = 0; ; )
    {
        sc = ClusterEnum( hEnum, idx, &dwType, pwszGroupName, &cchGroupName );
        if ( sc == ERROR_SUCCESS )
        {
            //
            // Process the current group.  See if it is owned by this
            // node and if so load its resources.
            //
            hGroup = OpenClusterGroup( hCluster, pwszGroupName );
            if ( hGroup == NULL )
            {
                sc = GetLastError();
                hr = HRESULT_FROM_WIN32( sc );
                goto Cleanup;
            } // if:

            hr = HrIsGroupOwnedByThisNode( hGroup, bstrNodeNameIn );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            if ( hr == S_OK )
            {
                hr = HrLoadGroupResources( hCluster, hGroup );
                if ( FAILED( hr ) )
                {
                    goto Cleanup;
                } // if:
            } // if:

            CloseClusterGroup( hGroup );
            hGroup = NULL;

            idx++;
            continue;
        } // if: ClusterEnum succeeded

        if ( sc == ERROR_MORE_DATA )
        {
            //
            // Allocate a bigger buffer and try again.
            //
            delete [] pwszGroupName;
            pwszGroupName = NULL;
            cchGroupName++;

            pwszGroupName = new WCHAR[ cchGroupName ];
            if ( pwszGroupName == NULL )
            {
                hr = E_OUTOFMEMORY;
                goto Cleanup;
            } // if:

            continue;
        } // if: pwszGroupName wasn't big enough

        if ( sc == ERROR_NO_MORE_ITEMS )
        {
            //
            // Enum is complete.
            //
            hr = S_OK;
            break;
        } // if:

        hr = HRESULT_FROM_WIN32( sc );
        break;
    } // for: each group in the enum

Cleanup:

    if ( hGroup != NULL )
    {
        CloseClusterGroup( hGroup );
    } // if:

    if ( hEnum != NULL )
    {
        ClusterCloseEnum( hEnum );
    } // if:

    if ( hCluster != NULL )
    {
        CloseCluster( hCluster );
    } // if:

    delete [] pwszGroupName;

    return hr;

} //*** CClusterUtils::HrEnumNodeResources


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils::HrLoadGroupResources
//
//  Description:
//      For each resource in the group pass its handle to HrNodeResourceCallback.
//
//  Arguments:
//      hClusterIn
//          Handle to the cluster.
//
//      hGroupIn
//          Handle to the group whose resources we're enumerating.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrLoadGroupResources(
      HCLUSTER    hClusterIn
    , HGROUP      hGroupIn
    )
{
    assert( hClusterIn != NULL );
    assert( hGroupIn != NULL );

    HRESULT     hr = S_OK;
    DWORD       sc = ERROR_SUCCESS;
    HGROUPENUM  hEnum = NULL;
    WCHAR *     pwszResourceName = NULL;
    DWORD       cchResourceName = 33;
    DWORD       dwType;
    DWORD       idx = 0;
    HRESOURCE   hResource = NULL;

    hEnum = ClusterGroupOpenEnum( hGroupIn, CLUSTER_GROUP_ENUM_CONTAINS );
    if ( hEnum == NULL )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    pwszResourceName = new WCHAR[ cchResourceName ];
    if ( pwszResourceName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    for ( idx = 0; ; )
    {
        sc = ClusterGroupEnum( hEnum, idx, &dwType, pwszResourceName, &cchResourceName );
        if ( sc == ERROR_SUCCESS )
        {
            //
            // Process the current resource.  Open it and pass a handle 
            // to HrNodeResourceCallback for further processing.
            //
            hResource = OpenClusterResource( hClusterIn, pwszResourceName );
            if ( hResource == NULL )
            {
                sc = GetLastError();
                hr = HRESULT_FROM_WIN32( sc );
                goto Cleanup;
            } // if:

            hr = HrNodeResourceCallback( hResource );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            CloseClusterResource( hResource );
            hResource = NULL;

            idx++;
            continue;
        } // if:

        if ( sc == ERROR_MORE_DATA )
        {
            //
            // Allocate a bigger buffer and try again.
            //
            delete [] pwszResourceName;
            pwszResourceName = NULL;
            cchResourceName++;

            pwszResourceName = new WCHAR[ cchResourceName ];
            if ( pwszResourceName == NULL )
            {
                hr = E_OUTOFMEMORY;
                goto Cleanup;
            } // if:

            continue;
        } // if:

        if ( sc == ERROR_NO_MORE_ITEMS )
        {
            //
            // Enum is complete.
            //
            hr = S_OK;
            break;
        } // if:

        hr = HRESULT_FROM_WIN32( sc );
        break;
    } // for:

Cleanup:

    if ( hResource != NULL )
    {
        CloseClusterResource( hResource );
    } // if:

    if ( hEnum != NULL )
    {
        ClusterGroupCloseEnum( hEnum );
    } // if:

    delete [] pwszResourceName;

    return hr;

} //*** CClusterUtils::HrLoadGroupResources


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils:HrGetQuorumResourceName
//
//  Description:
//      Retrieve the quorum resource's name.
//
//  Arguments:
//      pbstrQuorumResourceNameOut
//          Pointer to receive the allocated BSTR containing the quorum resource name.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrGetQuorumResourceName(
    BSTR * pbstrQuorumResourceNameOut
    )
{
    assert( pbstrQuorumResourceNameOut != NULL );

    HRESULT     hr = S_OK;
    HCLUSTER    hCluster = NULL;
    DWORD       sc = ERROR_SUCCESS;
    WCHAR *     pwszResourceName = NULL;
    DWORD       cchResourceName = 33;
    WCHAR *     pwszDeviceName = NULL;
    DWORD       cchDeviceName = 33;
    DWORD       cbQuorumLog;

    hCluster = OpenCluster( NULL );
    if ( hCluster == NULL )
    {
        sc = GetLastError();
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    pwszResourceName = new WCHAR[ cchResourceName ];
    if ( pwszResourceName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    pwszDeviceName = new WCHAR[ cchDeviceName ];
    if ( pwszDeviceName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    //
    // Try to get the quorum resource name.  We need to pass in the device name
    // buffer as well or the call will fail.
    //
    sc = GetClusterQuorumResource(
              hCluster
            , pwszResourceName
            , &cchResourceName
            , pwszDeviceName
            , &cchDeviceName
            , &cbQuorumLog
            );
    if ( sc == ERROR_MORE_DATA )
    {
        //
        //  At least one of the buffers wasn't big enough.  Reallocate and try again.
        //
        delete [] pwszResourceName;
        pwszResourceName = NULL;
        cchResourceName++;

        delete [] pwszDeviceName;
        pwszDeviceName = NULL;
        cchDeviceName++;

        pwszResourceName = new WCHAR[ cchResourceName ];
        if ( pwszResourceName == NULL )
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        } // if:

        pwszDeviceName = new WCHAR[ cchDeviceName ];
        if ( pwszDeviceName == NULL )
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        } // if:

        sc = GetClusterQuorumResource(
                  hCluster
                , pwszResourceName
                , &cchResourceName
                , pwszDeviceName
                , &cchDeviceName
                , &cbQuorumLog
                );
    } // if:

    if ( sc == ERROR_SUCCESS )
    {
        //
        // Allocate a BSTR and copy the WCHAR string into it.
        //
        *pbstrQuorumResourceNameOut = SysAllocString( pwszResourceName );
        if ( *pbstrQuorumResourceNameOut == NULL )
        {
            hr = E_OUTOFMEMORY;
            goto Cleanup;
        } // if:
    } // if: GetClusterQuorumResource succeeded.
    else
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // else: GetClusterQuorumResource failed.

    hr = S_OK;

Cleanup:

    if ( hCluster != NULL )
    {
        CloseCluster( hCluster );
    } // if:

    delete [] pwszResourceName;
    delete [] pwszDeviceName;

    return hr;

} //*** CClusterUtils::HrGetQuorumResourceName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils::HrIsClusterServiceRunning
//
//  Description:
//      Is this node a member of a cluster and is the serice running?
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          The node is clustered and the serivce is running.
//
//      S_FALSE
//          The node is not clustered, or the serivce is not running.
//
//      Other 
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrIsClusterServiceRunning( void )
{
    HRESULT hr = S_FALSE;
    DWORD   sc = ERROR_SUCCESS;
    DWORD   dwClusterState;

    //
    // Get the cluster state of the node.
    // Ignore the case where the service does not exist so that
    // EvictCleanup can do its job.
    //

    sc = GetNodeClusterState( NULL, &dwClusterState );
    if ( ( sc != ERROR_SUCCESS ) && ( sc != ERROR_SERVICE_DOES_NOT_EXIST ) )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if : GetClusterState() failed

    if ( dwClusterState == ClusterStateRunning )
    {
        hr = S_OK;
    } // if:

Cleanup:

    return hr;

} //*** CClusterUtils::HrIsClusterServiceRunning


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CClusterUtils::HrIsCoreResource
//
//  Description:
//      Determines whether the resource is a core resource.
//
//  Arguments:
//      hResourceIn
//          Handle of the resource to test.
//
//  Return Value:
//      S_OK
//          Resource is a core resource.
//
//      S_FALSE
//          Resource is not a core resource.
//
//      Other
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CClusterUtils::HrIsCoreResource(
    HRESOURCE hResourceIn
    )
{
    assert( hResourceIn != NULL );

    HRESULT hr = S_FALSE;
    DWORD   sc = ERROR_SUCCESS;
    DWORD   dwFlags = 0;
    DWORD   cb = 0;

    //
    // If the resource has the CLUS_FLAG_CORE flag set then it is a core resource.
    //
    sc = ClusterResourceControl(
              hResourceIn
            , NULL
            , CLUSCTL_RESOURCE_GET_FLAGS
            , NULL
            , 0
            , &dwFlags
            , sizeof( dwFlags )
            , &cb
            );
    if ( sc != ERROR_SUCCESS )
    {
        hr = HRESULT_FROM_WIN32( sc );
        goto Cleanup;
    } // if:

    if ( dwFlags & CLUS_FLAG_CORE )
    {
        hr = S_OK;
    } // if:

Cleanup:

    return hr;

} //*** CClusterUtils::HrIsCoreResource
