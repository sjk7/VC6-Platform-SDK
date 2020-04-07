//==============================================================================
//
// This file is part of the Microsoft COM+ Samples
//
// Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved
//
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation.  See these other
// materials for detailed information reagrding Microsoft code samples.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
//==============================================================================

#include "stdafx.h"
#include "Account.h"
#include "CAccount.h"
#include <stdio.h>
#include <comsvcs.h>
#include <adoid.h>
#include <adoint.h>
#include <comdef.h>
#include <string>

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CAccount::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAccount,
	};
	
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (  *arr[i] == riid )
			return S_OK;
	}
	return S_FALSE;
}

//F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
//
// Function: Post
//
// Modifies the specified account by the specified amount
//
// Args:	lAcocunt: Account to particptae in bank transaction
//			lAmount:  Amount of transaction
//			pbstrResult: Return String contains new balance. NULL of error occurs
//     
// Returns:  S_OK or E_FAIL
//
//F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-
STDMETHODIMP CAccount::Post (IN long lAccount, IN long lAmount, OUT BSTR* pbstrResult) 
{
	if( pbstrResult == 0 )
	{
		return E_POINTER;
	}

	HRESULT hr = S_OK;

	*pbstrResult = NULL;

	long lErrFlag = 0;
	TCHAR* pErrMsg = NULL;

	// See if we have sufficient funds
	// We're ignoring the rollover case here.
	if( ( d_acctBalance + lAmount ) < 0 )
	{
		// Error checking code removed for brevity
		ICreateErrorInfo * pCreateErrorInfo = NULL;
		CreateErrorInfo( &pCreateErrorInfo );
		pCreateErrorInfo->SetDescription( OLESTR( "Insufficient funds to perform transaction" ) );
		pCreateErrorInfo->SetGUID( __uuidof( IAccount ) );

		IErrorInfo* pErrorInfo = 0;
		pCreateErrorInfo->QueryInterface( IID_IErrorInfo, reinterpret_cast< void** >( &pErrorInfo ) );

		SetErrorInfo(NULL, static_cast< IErrorInfo* >( pErrorInfo) );
		return E_FAIL;
	}

	// Perform the transaction
	d_acctBalance += lAmount;

	// Generate a transaction description
	// Let the compiler choose the correct string template
	// based on UNICODE settings.  ( don't use std::string or std::wstring )
	std::basic_string< TCHAR > description;
		
	if( lAmount < 0 )
	{
		TCHAR txtBuffer[ 1024 ];
		wsprintf( txtBuffer
			    , TEXT( "Debit from account %d, balance is $%d" )
			    , lAccount
				, d_acctBalance );

		description = txtBuffer;
	}
	else
	{
		TCHAR txtBuffer[ 1024 ];
		wsprintf( txtBuffer
			    , TEXT( "Credit from account %d, balance is $%d" )
			    , lAccount
				, d_acctBalance );

		description = txtBuffer;
	}

	description += " (VC++)";
	// Set up our out param and then we're done ( with the required stuff )
	*pbstrResult = SysAllocString( _bstr_t( description.c_str( ) ) );


	// Because everything went well, we want to notify interested clients
	// that a sucessful post occured.
	// We don't particularly care whether the event went out in this sample,
	// so we'll go as far as we can.  On error, we'll silently fail and
	// return success to the client ( because the POST was a success )
		
	HRESULT eventHR;

	IMTSLocator* mtsLocator = 0;
	eventHR = CoCreateInstance( CLSID_CoMTSLocator
		                      , NULL
							  , CLSCTX_ALL
							  , __uuidof( IMTSLocator )
							  , reinterpret_cast< void** >( &mtsLocator ) );

	if( SUCCEEDED( eventHR ) )
	{
		// In order to dispatch a User Event, we need to locate the object that
		// will do this for us.  The MTSLocator object does this. 
		IUnknown* eventDispatcher = 0;
		eventHR = mtsLocator->GetEventDispatcher( &eventDispatcher );

		if( SUCCEEDED( eventHR ) )
		{
			// We need to get the correct interface....
			IMtsEvents* mtsEvents = 0;
			eventHR = eventDispatcher->QueryInterface( __uuidof( IMtsEvents )
				                                     , reinterpret_cast< void** >( &mtsEvents ) );

			if( SUCCEEDED( eventHR ) )
			{
				// And now that we have it, we can publish on the UserEvents event.
				// it simply takes a variant, which makes it very flexable.  We'll
				// stuff a string in there.
				VARIANT param;
				param.vt = VT_BSTR;
				param.bstrVal = _bstr_t( description.c_str( ) );
				mtsEvents->PostEvent( &param );
					
				mtsEvents->Release( );
				mtsEvents = 0;
			}
			eventDispatcher->Release( );
			eventDispatcher = 0;				
		}

		mtsLocator->Release( );
		eventDispatcher = 0;
	}		

	return S_OK;
}