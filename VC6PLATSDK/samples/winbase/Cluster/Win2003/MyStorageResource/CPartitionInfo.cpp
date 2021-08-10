//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CPartitionInfo.cpp
//
//  Description:
//      This file contains the definition of the CPartitionInfo class.
//
//      The class CPartitionInfo represents a disk partition.
//      It implements the IClusCfgPartitionInfo interface.
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WMIHelpers.h"
#include "CPartitionInfo.h"


//////////////////////////////////////////////////////////////////////////////
// CPartitionInfo class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::CPartitionInfo
//
//  Description:
//      Constructor of the CPartitionInfo class. This initializes
//      the m_cRef variable to 1 instead of 0 to account of possible
//      QueryInterface failure in DllGetClassObject.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CPartitionInfo::CPartitionInfo( void )
    : m_cRef( 1 )
{
    m_pIWbemServices = NULL;
    m_bstrName = NULL;
    m_bstrDescription = NULL;
    m_bstrUID = NULL;
    m_prgLogicalDisks = NULL;
    m_idxNextLogicalDisk = 0;
    m_ulPartitionSize = 0;
    m_bstrDiskDeviceID = NULL;

} //*** CPartitionInfo::CPartitionInfo


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::~CPartitionInfo
//
//  Description:
//      Desstructor of the CPartitionInfo class.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CPartitionInfo::~CPartitionInfo( void )
{
    ULONG   idx;

    SysFreeString( m_bstrName );
    SysFreeString( m_bstrDescription );
    SysFreeString( m_bstrUID );
    SysFreeString( m_bstrDiskDeviceID );

    for ( idx = 0; idx < m_idxNextLogicalDisk; idx++ )
    {
        ((*m_prgLogicalDisks)[ idx ])->Release();
    } // for:

    HeapFree( GetProcessHeap(), 0, m_prgLogicalDisks );

    if ( m_pIWbemServices != NULL )
    {
        m_pIWbemServices->Release();
    } // if:

} //*** CPartitionInfo::~CPartitionInfo


//////////////////////////////////////////////////////////////////////////////
// CPartitionInfo -- IWMIService interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::SetWbemServices
//
//  Description:
//      Set the WBEM services provider.
//
//  Arguments:
//      pIWbemServicesIn
//          IWbemServices pointer to save.
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
CPartitionInfo::SetWbemServices(
    IWbemServices * pIWbemServicesIn
    )
{
    HRESULT hr = S_OK;

    if ( pIWbemServicesIn == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_SetWbemServices_Partition
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

} //*** CPartitionInfo::SetWbemServices


//////////////////////////////////////////////////////////////////////////////
// CPartitionInfo -- IWMIObject interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::SetWbemObject
//
//  Description:
//      Initialize this component by querying WMI for the properties.
//
//  Arguments:
//      pPartitionIn
//          WMI disk partition object to associate with this object.
//
//      pfRetainObjectOut
//          If set to true the object will be added to the storage resource array.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other.
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CPartitionInfo::SetWbemObject(
      IWbemClassObject *    pPartitionIn
    , BOOL *                pfRetainObjectOut
    )
{
    assert( pPartitionIn != NULL );
    assert( pfRetainObjectOut != NULL );

    HRESULT     hr = S_OK;
    VARIANT     var;
    ULONGLONG   ull = 0;
    int         cch = 0;

    VariantInit( &var );

    hr = HrGetWMIProperty( pPartitionIn, L"Description", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_bstrDescription = SysAllocString( var.bstrVal );
    if ( m_bstrDescription == NULL )
    {
        goto OutOfMemory;
    } // if:

    VariantClear( &var );

    hr = HrGetWMIProperty( pPartitionIn, L"DeviceID", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_bstrUID = SysAllocString( var.bstrVal );
    if ( m_bstrUID == NULL )
    {
        goto OutOfMemory;
    } // if:

    VariantClear( &var );

    hr = HrGetWMIProperty( pPartitionIn, L"Name", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    m_bstrName = SysAllocString( var.bstrVal );
    if ( m_bstrName == NULL )
    {
        goto OutOfMemory;
    } // if:

    VariantClear( &var );

    hr = HrGetWMIProperty( pPartitionIn, L"Size", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    cch = swscanf( var.bstrVal, L"%I64u", &ull );
    assert( cch > 0 );

    m_ulPartitionSize = (ULONG) ( ull / ( 1024 * 1024 ) );

    hr = HrGetLogicalDisks( pPartitionIn );

    *pfRetainObjectOut = true;

    goto Cleanup;

OutOfMemory:

    hr = E_OUTOFMEMORY;
    STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_SetWbemObject_Partition
            , IDS_ERROR_OUTOFMEMORY
            , IDS_ERROR_OUTOFMEMORY_REF
            , hr
            );

Cleanup:

    VariantClear( &var );

    return hr;

} //*** CPartitionInfo::SetWbemObject


//////////////////////////////////////////////////////////////////////////////
// CPartitionInfo -- IClusCfgManagedResourceInfo interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::GetUID
//
//  Description:
//      Retrieve the UID of the object.
//
//  Arguments:
//      pbstrUIDOut
//          Upon success will point to an allocated BSTR containing the UID.
//
//  Return Value:
//      S_OK
//          Success.  pbstrUIDOut contains the UID.
//
//      S_FALSE
//          There is no UID associated with this object.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      If S_OK is returned the caller needs to call SysFreeString on pbstrUIDOut.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::GetUID( BSTR * pbstrUIDOut )
{
    HRESULT hr = S_OK;

    if ( pbstrUIDOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_PartitionInfo_GetUID_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    //
    //  If we don't have a UID then simply return S_FALSE to
    //  indicate that we have no data.
    //

    if ( m_bstrUID == NULL )
    {
        hr = S_FALSE;
        goto Cleanup;
    } // if:

    *pbstrUIDOut = SysAllocString( m_bstrUID );
    if ( *pbstrUIDOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_PartitionInfo_GetUID_Memory
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
    } // if:

Cleanup:

    return hr;

} //*** CPartitionInfo::GetUID


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::GetName
//
//  Description:
//      Retrive the name of the partition.
//
//  Arguments:
//      pbstrNameOut
//          Upon success will point to an allocated BSTR containing the name.
//
//  Return Value:
//      S_OK
//          Success.  psbstrNameOut contains the name.
//
//      S_FALSE
//          There is no name associated with this object.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      If S_OK is returned the caller needs to call SysFreeString on pbstrNameOut.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::GetName(
    BSTR * pbstrNameOut
    )
{
    HRESULT hr = S_OK;

    if ( pbstrNameOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_PartitionInfo_GetName_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    //
    //  If we don't have a name then simply return S_FALSE to
    //  indicate that we have no data.
    //

    if ( m_bstrName == NULL )
    {
        hr = S_FALSE;
        goto Cleanup;
    } // if:

    *pbstrNameOut = SysAllocString( m_bstrName );
    if (*pbstrNameOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetName_Memory
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
    } // if:

Cleanup:

    return hr;

} //*** CPartitionInfo::GetName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::SetName
//
//  Description:
//      Sets the name of the object.
//
//  Arguments:
//      pcszNameIn
//          Name to assign.
//
//  Return Value:
//      E_NOTIMPL
//          This function is not implemented.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::SetName(
    LPCWSTR pcszNameIn
    )
{
    HRESULT hr = E_NOTIMPL;

    UNREFERENCED_PARAMETER( pcszNameIn );

    return hr;

} //*** CPartitionInfo::SetName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::GetDescription
//
//  Description:
//      Retrieve the description of the object.
//
//  Arguments:
//      pbstrDescriptionOut
//          Upon success will point to an allocated BSTR containing the description.
//
//  Return Value:
//      S_OK
//          Success.  pbstrDescriptionOut contains the description.
//
//      S_FALSE
//          There is no description associated with this object.
//
//  Remarks:
//      If S_OK is returned the caller needs to call SysFreeString on pbstrDescriptionOut.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::GetDescription(
    BSTR * pbstrDescriptionOut
    )
{
    HRESULT hr = S_OK;

    if ( pbstrDescriptionOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_PartitionInfo_GetDescription_Pointer
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    if ( m_bstrDescription == NULL )
    {
        hr = S_FALSE;
        goto Cleanup;
    } // if:

    *pbstrDescriptionOut = SysAllocString( m_bstrDescription );
    if (*pbstrDescriptionOut == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_PartitionInfo_GetDescription_Memory
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
    } // if:

Cleanup:

    return hr;

} //*** CPartitionInfo::GetDescription


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::SetDescription
//
//  Description:
//      Sets the description of the object.
//
//  Arguments:
//      pcszDescriptionIn   
//          Description to assign.
//
//  Return Value:
//      E_NOTIMPL
//          This function is not implemented.
//
//      E_INVALIDARG
//          pcszDescriptionIn is NULL.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::SetDescription(
    LPCWSTR pcszDescriptionIn
    )
{
    HRESULT hr;

    if ( pcszDescriptionIn == NULL )
    {
        hr = E_INVALIDARG;
    } // if:
    else
    {
        hr = E_NOTIMPL;
    } // else:

    return hr;

} //*** CPartitionInfo::SetDescription


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::GetDriveLetterMappings
//
//  Description:
//      Retrieve the associated drive letters of this partition.
//
//  Arguments:
//      pdlmDriveLetterMappingOut
//          Upon success will contain all of the mappings for this partition.
//
//  Return Value:
//      S_OK
//          Success.
//
//      S_FALSE
//          There are no drive letters associated with this partition.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::GetDriveLetterMappings(
    SDriveLetterMapping * pdlmDriveLetterMappingOut
    )
{
    HRESULT             hr = S_FALSE;
    IWbemClassObject *  pLogicalDisk = NULL;
    VARIANT             var;
    ULONG               idx;
    int                 idxDrive;

    VariantInit( & var );

    if ( pdlmDriveLetterMappingOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetDriveLetterMappings_Partition
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    for ( idx = 0; idx < m_idxNextLogicalDisk; idx++ )
    {
        hr = ((*m_prgLogicalDisks)[ idx ])->TypeSafeQI( IWbemClassObject, &pLogicalDisk );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        VariantClear( &var );

        hr = HrGetWMIProperty( pLogicalDisk, L"Name", VT_BSTR, &var );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        CharUpper( var.bstrVal );

        idxDrive = var.bstrVal[ 0 ] - 'A';

        VariantClear( &var );

        hr = HrGetWMIProperty( pLogicalDisk, L"DriveType", VT_I4, &var );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        pdlmDriveLetterMappingOut->dluDrives[ idxDrive ] = (EDriveLetterUsage) var.iVal;

        pLogicalDisk->Release();
        pLogicalDisk = NULL;
    } // for:

Cleanup:

    VariantClear( &var );

    if ( pLogicalDisk != NULL )
    {
        pLogicalDisk->Release();
    } // if:

    return hr;

} //*** CPartitionInfo::GetDriveLetterMappings


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::SetDriveLetterMappings
//
//  Description:
//      Set the drive letters associated with this partition.
//
//  Arguments:
//      dlmDriveLetterMappingIn
//          Contains all of the drive letters to associate with this partition.
//
//  Return Value:
//      E_NOTIMPL
//          This function is not implemented.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::SetDriveLetterMappings(
    SDriveLetterMapping dlmDriveLetterMappingIn
    )
{
    HRESULT hr = E_NOTIMPL;

    UNREFERENCED_PARAMETER( dlmDriveLetterMappingIn );

    return hr;

} //*** CPartitionInfo::SetDriveLetterMappings


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::GetSize
//
//  Description:
//      Retrieve the size (in megabytes) of this partition.
//
//  Arguments:
//      pcMegaBytes
//          On success will contain the size in megabytes.
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
STDMETHODIMP
CPartitionInfo::GetSize(
    ULONG * pcMegaBytes
    )
{
    HRESULT hr = S_OK;

    if ( pcMegaBytes == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetSize
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    *pcMegaBytes = m_ulPartitionSize;

Cleanup:

    return hr;

} //*** CPartitionInfo::GetSize


//////////////////////////////////////////////////////////////////////////////
// CPartitionInfo -- IPartitionProperties interface.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::HrIsThisLogicalDisk
//
//  Description:
//      Does this partition have the passed in logical disk?
//
//  Arguments:
//      cLogicalDiskIn
//          The drive letter to check for.
//
//  Return Value:
//      S_OK
//          Success, the partition has the logical disk.
//
//      S_FALSE
//          Success, the partition does not have the logical disk.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::HrIsThisLogicalDisk(
    WCHAR cLogicalDiskIn
    )
{
    HRESULT             hr = S_FALSE;
    DWORD               idx;
    IWbemClassObject *  piwco = NULL;
    VARIANT             var;
    bool                fFoundIt = false;

    VariantInit( &var );

    if ( m_idxNextLogicalDisk == 0 )
    {
        goto Cleanup;
    } // if:

    for ( idx = 0; idx < m_idxNextLogicalDisk; idx++ )
    {
        hr = ((*m_prgLogicalDisks)[ idx ])->TypeSafeQI( IWbemClassObject, &piwco );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrGetWMIProperty( piwco, L"DeviceID", VT_BSTR, &var );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        if ( cLogicalDiskIn == var.bstrVal[ 0 ] )
        {
            fFoundIt = true;
            break;
        } // if:

        VariantClear( &var );

        piwco->Release();
        piwco = NULL;
    } // for:

    if ( !fFoundIt )
    {
        hr = S_FALSE;
    } // if:

Cleanup:

    VariantClear( &var );

    if ( piwco != NULL )
    {
        piwco->Release();
    } // if:

    return hr;

} //*** CPartitionInfo::HrIsThisLogicalDisk


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::HrIsNTFS
//
//  Description:
//      Is this an NTFS partition?
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success, the partition is NTFS.
//
//      S_FALSE
//          Success, the partition is not NTFS.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::HrIsNTFS( void )
{
    HRESULT             hr = S_FALSE;
    VARIANT             var;
    ULONG               idx;
    IWbemClassObject *  piwco = NULL;

    VariantInit( &var );

    for ( idx = 0; idx < m_idxNextLogicalDisk; idx++ )
    {
        hr = ((*m_prgLogicalDisks)[ idx ])->TypeSafeQI( IWbemClassObject, &piwco );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        VariantClear( &var );

        hr = HrGetWMIProperty( piwco, L"FileSystem", VT_BSTR, &var );
        if ( ( hr == E_PROPTYPEMISMATCH ) && ( var.vt == VT_NULL ) )
        {
            VariantClear( &var );

            hr = S_FALSE;
            HrGetWMIProperty( piwco, L"DeviceID", VT_BSTR, &var );
            STATUS_REPORT_STRING_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_Disk_No_File_System
                    , IDS_ERROR_DISK_NO_FILE_SYSTEM
                    , var.bstrVal
                    , IDS_ERROR_DISK_NO_FILE_SYSTEM_REF
                    , hr
                    );
            break;
        } // if:
        else if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // else if:

        if ( NIStringCompareW( var.bstrVal, SysStringLen( var.bstrVal ), L"NTFS", RTL_NUMBER_OF( L"NTFS" ) ) != 0 )
        {
            VariantClear( &var );

            hr = S_FALSE;
            HrGetWMIProperty( piwco, L"DeviceID", VT_BSTR, &var );
            STATUS_REPORT_STRING_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_Disk_Not_NTFS
                    , IDS_WARN_DISK_NOT_NTFS
                    , var.bstrVal
                    , IDS_WARN_DISK_NOT_NTFS_REF
                    , hr
                    );
            break;
        } // if:

        piwco->Release();
        piwco = NULL;
    } // for:

Cleanup:

    VariantClear( &var );

    if ( piwco != NULL )
    {
        piwco->Release();
    } // if:

    return hr;

} //*** CPartitionInfo::HrIsNTFS


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::HrGetFriendlyName
//
//  Description:
//      Get the friendly name of this partition.  This name will be the
//      logical disk names of all logical disks on this partition.
//
//  Arguments:
//      pbstrNameOut
//          Upon success will point to an allocated BSTR containing the name.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other
//          An error occurred.
//
//  Remarks:
//      If S_OK is returned the caller needs to call SysFreeString on pbstrNameOut.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CPartitionInfo::HrGetFriendlyName(
    BSTR * pbstrNameOut
    )
{
    HRESULT             hr = S_FALSE;
    DWORD               idx;
    IWbemClassObject *  piwco = NULL;
    WCHAR *             pwsz = NULL;
    WCHAR *             pwszTmp = NULL;
    DWORD               cch = 0;
    VARIANT             var;

    VariantInit( &var );

    if ( m_idxNextLogicalDisk == 0 )
    {
        goto Cleanup;
    } // if:

    if ( pbstrNameOut == NULL )
    {
        hr = E_POINTER;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_GetFriendlyName
                , IDS_ERROR_NULL_POINTER
                , IDS_ERROR_NULL_POINTER_REF
                , hr
                );
        goto Cleanup;
    } // if:

    for ( idx = 0; idx < m_idxNextLogicalDisk; idx++ )
    {
        hr = ((*m_prgLogicalDisks)[ idx ])->TypeSafeQI( IWbemClassObject, &piwco );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = HrGetWMIProperty( piwco, L"DeviceID", VT_BSTR, &var );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        cch += ( UINT ) wcslen( var.bstrVal ) + 2;                      // a space and the '\0'

        pwszTmp = (WCHAR *) HEAPREALLOC( pwsz, sizeof( WCHAR ) * cch, HEAP_ZERO_MEMORY );
        if ( pwszTmp == NULL  )
        {
            goto OutOfMemory;
        } // if:

        pwsz = pwszTmp;
        pwszTmp = NULL;

        hr = StringCchCatW( pwsz, cch, L" " );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        hr = StringCchCatW( pwsz, cch, var.bstrVal );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:

        VariantClear( &var );

        piwco->Release();
        piwco = NULL;
    } // for:

    *pbstrNameOut = SysAllocString( pwsz );
    if ( *pbstrNameOut == NULL )
    {
        goto OutOfMemory;
    } // if:

    goto Cleanup;

OutOfMemory:

    hr = E_OUTOFMEMORY;
    STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_HrGetFriendlyName
            , IDS_ERROR_OUTOFMEMORY
            , IDS_ERROR_OUTOFMEMORY_REF
            , hr
            );

Cleanup:

    VariantClear( &var );

    if ( piwco != NULL )
    {
        piwco->Release();
    } // if:

    if ( pwsz != NULL )
    {
        HeapFree( GetProcessHeap(), 0, pwsz );
    } // if:

    if ( pwszTmp != NULL )
    {
        HeapFree( GetProcessHeap(), 0, pwszTmp );
    } // if:

    return hr;

} //*** CPartitionInfo::HrGetFriendlyName


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo::HrSetDeviceID
//
//  Description:
//      Sets the device ID of this object.
//
//  Arguments:
//      bstrDeviceIDIn
//          Device ID to assign.
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
CPartitionInfo::HrSetDeviceID(
    BSTR    bstrDeviceIDIn      // = NULL
    )
{
    HRESULT hr = S_OK;

    if ( bstrDeviceIDIn != NULL )
    {
        m_bstrDiskDeviceID = SysAllocString( bstrDeviceIDIn );
        if ( m_bstrDiskDeviceID == NULL )
        {
            hr = E_OUTOFMEMORY;
        } // if:
    } // if:

    return hr;

} //*** CPartitionInfo::HrSetDeviceID


//////////////////////////////////////////////////////////////////////////////
// CPartitionInfo class -- Private Methods.
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo:HrAddLogicalDiskToArray
//
//  Description:
//      Add the passed in logical disk to the array of punks that holds the
//      logical disks.
//
//  Arguments:
//      pLogicalDiskIn
//          Logical disk to add to the array.
//
//  Return Value:
//      S_OK
//          Success
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
CPartitionInfo::HrAddLogicalDiskToArray(
    IWbemClassObject * pLogicalDiskIn
    )
{
    HRESULT     hr = S_OK;
    IUnknown *  punk;
    IUnknown *  ((*prgpunks)[]) = NULL;

    prgpunks = (IUnknown *((*)[])) HEAPREALLOC( m_prgLogicalDisks, sizeof( IUnknown * ) * ( m_idxNextLogicalDisk + 1 ), HEAP_ZERO_MEMORY );
    if ( prgpunks == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrAddLogicalDiskToArray
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
        goto Cleanup;
    } // else:

    m_prgLogicalDisks = prgpunks;

    hr = pLogicalDiskIn->TypeSafeQI( IUnknown, &punk );
    if ( SUCCEEDED( hr ) )
    {
        (*m_prgLogicalDisks)[ m_idxNextLogicalDisk++ ] = punk;
    } // if:

Cleanup:

    return hr;

} //*** CPartitionInfo::HrAddLogicalDiskToArray


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo:HrGetLogicalDisks
//
//  Description:
//      Get the logical disks for the passed in partition.
//
//  Arguments:
//      pPartitionIn
//          WMI partition object to query on.
//
//  Return Value:
//      S_OK
//          Success
//
//      S_FALSE
//          The file system was not NTFS.
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
CPartitionInfo::HrGetLogicalDisks(
    IWbemClassObject * pPartitionIn
    )
{
    HRESULT                 hr;
    VARIANT                 var;
    WCHAR                   szBuf[ 256 ];
    IEnumWbemClassObject *  pLogicalDisks = NULL;
    IWbemClassObject *      pLogicalDisk = NULL;
    ULONG                   ulReturned;
    BSTR                    bstrQuery = NULL;
    BSTR                    bstrWQL = NULL;

    VariantInit( &var );

    bstrWQL = SysAllocString( L"WQL" );
    if ( bstrWQL == NULL )
    {
        hr = E_OUTOFMEMORY;
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetLogicalDisks
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
        goto Cleanup;
    } // if:

    //
    //  Need to enum the logical disk(s) of this partition to determine if it is booted
    //  bootable.
    //
    hr = HrGetWMIProperty( pPartitionIn, L"DeviceID", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = StringCchPrintfW(
                      szBuf
                    , RTL_NUMBER_OF( szBuf )
                    , L"Associators of {Win32_DiskPartition.DeviceID='%ws'} where AssocClass=Win32_LogicalDiskToPartition"
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
        STATUS_REPORT_REF(
                  TASKID_Major_Find_Devices
                , TASKID_Minor_HrGetLogicalDisks
                , IDS_ERROR_OUTOFMEMORY
                , IDS_ERROR_OUTOFMEMORY_REF
                , hr
                );
        goto Cleanup;
    } // if:

    hr = m_pIWbemServices->ExecQuery( bstrWQL, bstrQuery, WBEM_FLAG_FORWARD_ONLY, NULL, &pLogicalDisks );
    if ( FAILED( hr ) )
    {
        STATUS_REPORT_REF(
              TASKID_Major_Find_Devices
            , TASKID_Minor_WMI_Logical_Disks_Qry_Failed
            , IDS_ERROR_WMI_DISKS_QRY_FAILED
            , IDS_ERROR_WMI_DISKS_QRY_FAILED_REF
            , hr
            );
        goto Cleanup;
    } // if:

    for ( ; ; )
    {
        hr = pLogicalDisks->Next( WBEM_INFINITE, 1, &pLogicalDisk, &ulReturned );
        if ( ( hr == S_OK ) && ( ulReturned == 1 ) )
        {
            HrLogLogicalDiskInfo( pLogicalDisk, var.bstrVal );
            hr = HrAddLogicalDiskToArray( pLogicalDisk );
            if ( FAILED( hr ) )
            {
                goto Cleanup;
            } // if:

            pLogicalDisk->Release();
            pLogicalDisk = NULL;
        } // if:
        else if ( ( hr == S_FALSE ) && ( ulReturned == 0 ) )
        {
            hr = S_OK;
            break;
        } // else if:
        else
        {
            STATUS_REPORT_STRING_REF(
                      TASKID_Major_Find_Devices
                    , TASKID_Minor_HrGetLogicalDisks_Next
                    , IDS_ERROR_WQL_QRY_NEXT_FAILED
                    , bstrQuery
                    , IDS_ERROR_WQL_QRY_NEXT_FAILED_REF
                    , hr
                    );
            goto Cleanup;
        } // else:
    } // for:

Cleanup:

    VariantClear( &var );

    SysFreeString( bstrQuery );
    SysFreeString( bstrWQL );

    if ( pLogicalDisk != NULL )
    {
        pLogicalDisk->Release();
    } // if:

    if ( pLogicalDisks != NULL )
    {
        pLogicalDisks->Release();
    } // if:

    return hr;

} //*** CPartitionInfo::HrGetLogicalDisks


/////////////////////////////////////////////////////////////////////////////
//++
//
//  CPartitionInfo:HrLogLogicalDiskInfo
//
//  Description:
//      Log the info about the passed in logical disk.
//
//  Arguments:
//      pLogicalDiskIn
//          The logical disk to log info about.
//
//      bstrDeviceIDIn
//          The device ID of the current partition to which this logical disk
//          belongs.
//
//  Return Value:
//      S_OK
//          Success
//
//      Other
//          An error occurred.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
CPartitionInfo::HrLogLogicalDiskInfo(
      IWbemClassObject *    pLogicalDiskIn
    , BSTR                  bstrDeviceIDIn
    )
{
    assert( m_bstrDiskDeviceID != NULL );
    assert( pLogicalDiskIn != NULL );
    assert( bstrDeviceIDIn != NULL );

    HRESULT hr = S_OK;
    VARIANT var;

    VariantInit( &var );

    if ( ( pLogicalDiskIn == NULL ) || ( bstrDeviceIDIn == NULL ) )
    {
        hr = E_INVALIDARG;
        goto Cleanup;
    } // if:

    hr = HrGetWMIProperty( pLogicalDiskIn, L"Name", VT_BSTR, &var );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    LOG_STATUS_REPORT_STRING4(
                  L"Found %1!ws! resource \"%2!ws!\" with partition \"%3!ws!\" which has the logical disk \"%3!ws!\"."
                , GetResTypeName()
                , m_bstrDiskDeviceID
                , bstrDeviceIDIn
                , var.bstrVal
                , hr
                );

Cleanup:

    VariantClear( &var );

    return hr;

} //*** CPartitionInfo::HrLogLogicalDiskInfo
