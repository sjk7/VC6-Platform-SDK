//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      WMIHelpers.h
//
//  Description:
//      This file contains the declaration of the WMI helper functions.
//
//  Implementation Files:
//      WMIHelpers.cpp
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"


//////////////////////////////////////////////////////////////////////////////
// Function Declarations
//////////////////////////////////////////////////////////////////////////////

HRESULT
HrGetWMIProperty(
      IWbemClassObject *    pWMIObjectIn
    , LPCWSTR               pcszPropertyNameIn
    , ULONG                 ulPropertyTypeIn
    , VARIANT *             pVariantOut
    );

HRESULT
HrSetWbemServices(
      IUnknown *        punkIn
    , IWbemServices *   pIWbemServicesIn
    );

HRESULT
HrInitializeWbemConnection(
    IWbemServices ** pIWbemServicesOut
    );

HRESULT
HrSetBlanket(
    IWbemServices * pIWbemServicesIn
    );
