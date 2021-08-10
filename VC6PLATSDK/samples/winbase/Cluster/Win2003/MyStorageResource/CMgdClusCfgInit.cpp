//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      CMgdClusCfgInit.cpp
//
//  Description:
//      Implementation of the CMgdClusCfgInit class.
//
//  Header File:
//      CMgdClusCfgInit.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CMgdClusCfgInit.h"


//////////////////////////////////////////////////////////////////////////////
// CMgdClusCfgInit class
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::CMgdClusCfgInit
//
//  Description:
//      Constructor. Sets all member variables to default values.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMgdClusCfgInit::CMgdClusCfgInit( void )
{
    m_picccCallback = NULL;
    m_lcid = GetUserDefaultLCID();

    m_bstrNodeName = NULL;
    m_bstrDllName = NULL;
    m_bstrResTypeName = NULL;
    m_bstrDisplayName = NULL;

} //*** CMgdClusCfgInit::CMgdClusCfgInit


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::~CMgdClusCfgInit
//
//  Description:
//      Destructor. Frees all previously allocated memory and releases all
//      interface pointers.
//
//  Arguments:
//      None.
//
//  Return Value:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
CMgdClusCfgInit::~CMgdClusCfgInit( void )
{
    if ( m_picccCallback != NULL )
    {
        m_picccCallback->Release();
        m_picccCallback = NULL;
    } // if: m_picccCallback was used

    SysFreeString( m_bstrNodeName );
    SysFreeString( m_bstrDllName );
    SysFreeString( m_bstrResTypeName );
    SysFreeString( m_bstrDisplayName );

} //*** CMgdClusCfgInit::~CMgdClusCfgInit


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::Initialize
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
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMgdClusCfgInit::Initialize(
      IUnknown *    punkCallbackIn
    , LCID          lcidIn
    )
{
    HRESULT hr = S_OK;
    WCHAR   szComputerName[ MAX_PATH ];
    DWORD   cchComputerName = MAX_PATH;
    DWORD   dwError = ERROR_SUCCESS;

    m_lcid = lcidIn;

    if ( punkCallbackIn == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if: Callback pointer is invalid (NULL)

    //
    // Save the callback interface pointer.
    //

    hr = punkCallbackIn->TypeSafeQI( IClusCfgCallback, &m_picccCallback );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if: TypeSafeQI failed

    //
    // Save the computer name for use by SendStatusReport.
    //

    if ( GetComputerNameEx( ComputerNamePhysicalDnsHostname, szComputerName, &cchComputerName ) == 0 )
    {
        dwError = GetLastError();
        hr = HRESULT_FROM_WIN32( dwError );

        HrSendStatusReport(
              TASKID_Major_Find_Devices
            , TASKID_Minor_StorageResourceInitialize
            , 1
            , 1
            , 1
            , hr
            , IDS_ERROR_GETCOMPUTERNAME_FAILED
            , 0
            );
        goto Cleanup;
    } // if: GetComputerName failed

    m_bstrNodeName = SysAllocString( szComputerName );
    if ( m_bstrNodeName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    //
    // Get the dll name.
    //

    m_bstrDllName = SysAllocString( RESTYPE_DLL_NAME );
    if ( m_bstrDllName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    //
    // Get the resource type name.
    //

    m_bstrResTypeName = SysAllocString( RESTYPE_NAME );
    if ( m_bstrResTypeName == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    //
    // Load the resource type display name.
    //

    //
    // NOTE:    The resource type display name should be localized, but the resource type
    //          name should always remain the same.
    //

    hr = HrLoadStringIntoBSTR( _Module.m_hInstResource, IDS_RESTYPE_DISPLAYNAME, &m_bstrDisplayName );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    return hr;

} //*** CMgdClusCfgInit::Initialize


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::HrSendStatusReport
//
//  Description:
//      Wraps IClusCfgCallback::SendStatusReport.
//
//  Arguments:
//       clsidTaskMajorIn
//       clsidTaskMinorIn
//       ulMinIn
//       ulMaxIn
//       ulCurrentIn
//       hrStatusIn
//       idsDescriptionIn
//       idsReferenceIn 
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMgdClusCfgInit::HrSendStatusReport(
      CLSID     clsidTaskMajorIn
    , CLSID     clsidTaskMinorIn
    , ULONG     ulMinIn
    , ULONG     ulMaxIn
    , ULONG     ulCurrentIn
    , HRESULT   hrStatusIn
    , UINT      idsDescriptionIn
    , UINT      idsReferenceIn
    ...
    )
{
    HRESULT     hr = S_OK;
    BSTR        bstrDescription = NULL;
    BSTR        bstrReference = NULL;
    va_list     valist = NULL;

    va_start( valist, idsReferenceIn );
    hr = HrFormatStringWithVAListIntoBSTR( _Module.m_hInstResource, idsDescriptionIn, &bstrDescription, valist );
    va_end( valist );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( idsReferenceIn != 0 )
    {
        hr = HrLoadStringIntoBSTR( _Module.m_hInstResource, idsReferenceIn, &bstrReference );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if: valid reference string

    hr = SendStatusReport(
              clsidTaskMajorIn
            , clsidTaskMinorIn
            , ulMinIn
            , ulMaxIn
            , ulCurrentIn
            , hrStatusIn
            , bstrDescription
            , bstrReference
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    SysFreeString( bstrDescription );
    SysFreeString( bstrReference );

    return hr;

} //*** CMgdClusCfgInit::HrSendStatusReport


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::HrSendStatusReport
//
//  Description:
//      Wraps IClusCfgCallback::SendStatusReport.
//
//  Arguments:
//       clsidTaskMajorIn
//       clsidTaskMinorIn
//       ulMinIn
//       ulMaxIn
//       ulCurrentIn
//       hrStatusIn
//       pcszDescriptionIn
//       idsReferenceIn 
//       ...        optional parameters for pcszDescriptionIn
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMgdClusCfgInit::HrSendStatusReport(
      CLSID     clsidTaskMajorIn
    , CLSID     clsidTaskMinorIn
    , ULONG     ulMinIn
    , ULONG     ulMaxIn
    , ULONG     ulCurrentIn
    , HRESULT   hrStatusIn
    , LPCWSTR   pcszDescriptionIn
    , UINT      idsReferenceIn
    ...
    )
{
    HRESULT     hr = S_OK;
    BSTR        bstrDescription = NULL;
    BSTR        bstrReference = NULL;
    va_list     valist = NULL;

    va_start( valist, idsReferenceIn );
    hr = HrFormatStringWithVAListIntoBSTR( pcszDescriptionIn, &bstrDescription, valist );
    va_end( valist );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    if ( idsReferenceIn != 0 )
    {
        hr = HrLoadStringIntoBSTR( _Module.m_hInstResource, idsReferenceIn, &bstrReference );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if: valid reference string

    hr = SendStatusReport(
              clsidTaskMajorIn
            , clsidTaskMinorIn
            , ulMinIn
            , ulMaxIn
            , ulCurrentIn
            , hrStatusIn
            , bstrDescription
            , bstrReference
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    SysFreeString( bstrDescription );
    SysFreeString( bstrReference );

    return hr;

} //*** CMgdClusCfgInit::HrSendStatusReport


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::HrSendStatusReport
//
//  Description:
//      Wraps IClusCfgCallback::SendStatusReport.
//
//  Arguments:
//       clsidTaskMajorIn
//       clsidTaskMinorIn
//       ulMinIn
//       ulMaxIn
//       ulCurrentIn
//       hrStatusIn
//       pcszDescriptionIn
//       pcszReferenceIn
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP 
CMgdClusCfgInit::HrSendStatusReport(
      CLSID      clsidTaskMajorIn
    , CLSID      clsidTaskMinorIn
    , ULONG      ulMinIn
    , ULONG      ulMaxIn
    , ULONG      ulCurrentIn
    , HRESULT    hrStatusIn
    , LPCWSTR    pcszDescriptionIn
    , LPCWSTR    pcszReferenceIn
    ...
    )
{
    HRESULT     hr = S_OK;
    BSTR        bstrDescription = NULL;
    va_list     valist = NULL;

    va_start( valist, pcszReferenceIn );
    hr = HrFormatStringWithVAListIntoBSTR( pcszDescriptionIn, &bstrDescription, valist );
    va_end( valist );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = SendStatusReport(
              clsidTaskMajorIn
            , clsidTaskMinorIn
            , ulMinIn
            , ulMaxIn
            , ulCurrentIn
            , hrStatusIn
            , bstrDescription
            , pcszReferenceIn
            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    SysFreeString( bstrDescription );

    return hr;

} //*** CMgdClusCfgInit::HrSendStatusReport


//////////////////////////////////////////////////////////////////////////////
//++
//
//  CMgdClusCfgInit::SendStatusReport
//
//  Description:
//      Wraps IClusCfgCallback::SendStatusReport.
//
//  Arguments:
//       clsidTaskMajorIn
//       clsidTaskMinorIn
//       ulMinIn
//       ulMaxIn
//       ulCurrentIn
//       hrStatusIn
//       pcszDescriptionIn
//       pcszReferenceIn
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDMETHODIMP
CMgdClusCfgInit::SendStatusReport(
      CLSID     clsidTaskMajorIn
    , CLSID     clsidTaskMinorIn
    , ULONG     ulMinIn
    , ULONG     ulMaxIn
    , ULONG     ulCurrentIn
    , HRESULT   hrStatusIn
    , LPCWSTR   pcszDescriptionIn
    , LPCWSTR   pcszReferenceIn
    )
{
    HRESULT     hr = S_OK;
    FILETIME    ftTime;

    assert( m_picccCallback != NULL );
    assert( m_bstrNodeName != NULL );

    GetSystemTimeAsFileTime( &ftTime );

    if ( m_picccCallback != NULL )
    {
        hr = m_picccCallback->SendStatusReport(
                  m_bstrNodeName
                , clsidTaskMajorIn
                , clsidTaskMinorIn
                , ulMinIn
                , ulMaxIn
                , ulCurrentIn
                , hrStatusIn
                , pcszDescriptionIn
                , &ftTime
                , pcszReferenceIn
                );
        if ( FAILED( hr ) )
        {
            goto Cleanup;
        } // if:
    } // if: m_picccCallback != NULL

Cleanup:

    return hr;

} //*** CMgdClusCfgInit::SendStatusReport
