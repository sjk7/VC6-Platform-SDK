//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      WmiHelpers.cpp
//
//  Description:
//      This file contains the implementation of WMI help functions.
//
//  Header File:
//      WmiHelpers.h
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WMIHelpers.h"


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrGetWMIProperty
//
//  Description:
//      Get a named property from a WMI object.
//
//  Arguments:
//      pWMIObjectIn
//          WMI object to retrieve the property from.
//
//      pcszPropertyNameIn
//          Name of the property to retrieve.
//
//      ulPropertyTypeIn
//          Expected property type.
//
//      pVariantOut
//          VARIANT to receive the property.
//
//  Return Value:
//      S_OK
//          Success.
//
//      E_PROPTYPEMISMATCH
//          Property type didn't match what caller specified.
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
HrGetWMIProperty(
      IWbemClassObject *    pWMIObjectIn
    , LPCWSTR               pcszPropertyNameIn
    , ULONG                 ulPropertyTypeIn
    , VARIANT *             pVariantOut
    )
{
    assert( pWMIObjectIn != NULL );
    assert( pcszPropertyNameIn != NULL );
    assert( pVariantOut != NULL );

    HRESULT hr;
    BSTR    bstrProp = NULL;

    VariantClear( pVariantOut );

    bstrProp = SysAllocString( pcszPropertyNameIn );
    if ( bstrProp == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    hr = pWMIObjectIn->Get( bstrProp, 0L, pVariantOut, NULL, NULL );
    if ( FAILED( hr ) )
    {
        //
        //  The SendStatusReport mechanism does not work in these helper
        //  functions.  It is an exercise left up to the reader as to how
        //  best to log errors from this function...
        //
        //  It is expected that most implementers of a ClusCfg managed
        //  resource will not use this function as it is here for
        //  demonstration purposes only...
        //

        //LOG_STATUS_REPORT_STRING( L"[MyStorageResource] Could not get the value for WMI property '%1!ws!'.", bstrProp, hr );
        goto Cleanup;
    } // if:

    //
    //  For reasons only known to WMI, boolean properties are of type VT_NULL instead of
    //  VT_BOOL when they are not set or false...
    //

    //
    //  Added the special case check for signature.  We know that signature will be NULL
    //  when the spindle is under ClusDisk control...
    //

    if (    ( ulPropertyTypeIn != VT_BOOL )
        &&  ( NIStringCompareW( bstrProp, SysStringLen( bstrProp ), L"Signature", RTL_NUMBER_OF( L"Signature" ) ) != 0 ) )
    {
        if ( pVariantOut->vt != ulPropertyTypeIn )
        {
            //LOG_STATUS_REPORT_STRING3( L"[MyStorageResource] Variant type for WMI Property '%1!ws!' was supposed to be '%2!d!', but was '%3!d!' instead.", pcszPropertyNameIn, ulPropertyTypeIn, pVariantOut->vt, hr );
            hr = E_PROPTYPEMISMATCH;
        } // if:
    } // if:

Cleanup:

    SysFreeString( bstrProp );

    return hr;

} //*** HrGetWMIProperty


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrSetWbemServices
//
//  Description:
//      Set the WBemServices object into the passed in punk.
//
//  Arguments:
//      punkIn
//          Interface pointer of the object to call SetWbemServices on.
//
//      pIWbemServicesIn
//          Interface pointer to pass in the SetWbemServices call.
//
//  Return Value:
//      S_OK
//          Success
//
//      Other
//          An error occurred.
//
//  Remarks:
//      If the punkIn object doesn't support the IWMIServices interface
//      S_OK is returned.
//
//--
//////////////////////////////////////////////////////////////////////////////
HRESULT
HrSetWbemServices(
      IUnknown *        punkIn
    , IWbemServices *   pIWbemServicesIn
    )
{
    assert( punkIn != NULL );

    HRESULT         hr;
    IWMIServices *  piws = NULL;

    if ( punkIn == NULL )
    {
        hr = E_POINTER;
        goto Cleanup;
    } // if:

    hr = punkIn->TypeSafeQI( IWMIServices, &piws );
    if ( SUCCEEDED( hr ) )
    {
        hr = piws->SetWbemServices( pIWbemServicesIn );
        piws->Release();
    } // if:
    else if ( hr == E_NOINTERFACE )
    {
        hr = S_OK;
    } // else if:

Cleanup:

    return hr;

} //*** HrSetWbemServices


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrSetBlanket
//
//  Description:
//      Adjusts the security blanket on a IWbemServices pointer.
//
//  Arguments:
//      pIWbemServicesIn
//          Object on which to set teh security blanket.
//
//  Return Value:
//      S_OK
//          Success.
//
//      S_FALSE
//          pIWbemServices was NULL.
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
HrSetBlanket( 
    IWbemServices * pIWbemServicesIn
    )
{
    assert( pIWbemServicesIn != NULL );

    HRESULT hr = S_FALSE;

    if ( pIWbemServicesIn )
    {
        IClientSecurity *   pCliSec;

        hr = pIWbemServicesIn->TypeSafeQI( IClientSecurity, &pCliSec );
        if ( SUCCEEDED( hr ) )
        {
            hr = pCliSec->SetBlanket(
                            pIWbemServicesIn,
                            RPC_C_AUTHN_WINNT,
                            RPC_C_AUTHZ_NONE,
                            NULL,
                            RPC_C_AUTHN_LEVEL_CONNECT,
                            RPC_C_IMP_LEVEL_IMPERSONATE,
                            NULL,
                            EOAC_NONE
                            );

            pCliSec->Release();
        } // if:
    } // if:

    return hr;

} //*** HrSetBlanket


//////////////////////////////////////////////////////////////////////////////
//++
//
//  HrInitializeWbemConnection
//
//  Description:
//      Initialize a connection to the WbemLocator and returns a pointer
//      to a WBEM services object.
//
//  Arguments:
//      pIWbemServicesOut
//          Upon success will contain the interface pointer to the services object.
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
HrInitializeWbemConnection(
    IWbemServices ** pIWbemServicesOut
    )
{
    assert( pIWbemServicesOut != NULL );

    HRESULT         hr = S_OK;
    IWbemLocator *  pIWbemLocator = NULL;
    BSTR            bstrNameSpace = NULL;

    hr = CoCreateInstance( CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *) &pIWbemLocator );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    bstrNameSpace = SysAllocString( L"\\\\.\\root\\cimv2" );
    if ( bstrNameSpace == NULL )
    {
        hr = E_OUTOFMEMORY;
        goto Cleanup;
    } // if:

    hr = pIWbemLocator->ConnectServer(
                            bstrNameSpace,
                            NULL,                   // using current account for simplicity
                            NULL,                   // using current password for simplicity
                            NULL,                   // locale
                            0L,                     // securityFlags, reserved must be 0
                            NULL,                   // authority (domain for NTLM)
                            NULL,                   // context
                            pIWbemServicesOut
                            );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

    hr = HrSetBlanket( *pIWbemServicesOut );
    if ( FAILED( hr ) )
    {
        goto Cleanup;
    } // if:

Cleanup:

    SysFreeString( bstrNameSpace );

    if ( pIWbemLocator != NULL )
    {
        pIWbemLocator->Release();
    } // if:

    return hr;

} //*** HrInitializeWbemConnection

