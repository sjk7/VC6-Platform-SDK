//==============================================================================
// Filename: GetReceipt.cpp
//
// Description: Implementation of CGetReceipt
//
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
#include "GetReceipt.h"
#include "UpdateReceipt.h"

#include <comsvcs.h>


/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CGetReceipt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGetReceipt,
	};
	
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
//
// Function:	GetNextReceipt
//
// This function uses Shared Properties to get the next receipt value 
//
// Args:	ReceiptNo:	Receipt number for this transction     
//
// Returns:  S_OK or E_FAIL
//
//F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-

STDMETHODIMP CGetReceipt::GetNextReceipt (OUT long* plReceiptNo) {
	
	HRESULT hr = S_OK;
	
	IObjectContext* pObjectContext = NULL;
	
	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	ISharedProperty* spmPropNextReceipt = NULL;
	ISharedProperty* spmPropMaxNum = NULL;
	
	IUpdateReceipt* pObjUpdateReceipt = NULL;

	CComVariant vNextReceipt;

	long lErrFlag = 0;
	TCHAR* pErrMsg = NULL;


	try {
		
		// First of all, get the object context
		THROW_ERR (CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext), "GetObjectContext" );

		// Create the SharedPropertyGroupManager
		THROW_ERR ( CoCreateInstance (CLSID_SharedPropertyGroupManager, NULL, CLSCTX_ALL, 
			IID_ISharedPropertyGroupManager, (void**)&spmMgr), "CreateInstance(CLSID_SharedPropertyGroupManager)" );
		
		// Create the SharedPropertyGroup
		LONG lIsolationMode = LockMethod;
		LONG lReleaseMode = Process;
		VARIANT_BOOL bExists = VARIANT_FALSE;
		THROW_ERR ( spmMgr->CreatePropertyGroup (L"Receipt", &lIsolationMode, &lReleaseMode, &bExists, &spmGroup),
			"CreatePropertyGroup" );
		
		// Create the two shared properties
		THROW_ERR ( spmGroup->CreateProperty (L"Next", &bExists, &spmPropNextReceipt), "CreateProperty(Next)" );
		THROW_ERR ( spmGroup->CreateProperty (L"MaxNum", &bExists, &spmPropMaxNum), "CreateProperty(MaxNum)" );
		
		// Obtain their current values
		CComVariant vMaxNum;
		THROW_ERR ( spmPropNextReceipt->get_Value (&vNextReceipt), "spmPropNextReceipt->get_Value" );
		THROW_ERR ( spmPropMaxNum->get_Value (&vMaxNum), "spmPropMaxNum->get_Value" );
		
		// Does MaxNum require an update?
		if (vNextReceipt.lVal >= vMaxNum.lVal) {
			
			// Create an UpdateReceipt object
			THROW_ERR( CoCreateInstance (CLSID_CUpdateReceipt, NULL, CLSCTX_ALL, IID_IUpdateReceipt,
				(void**)&pObjUpdateReceipt), "CreateInstance(CLSID_CUpdateReceipt)" );
			
			// Update NextReceipt
			RETHROW_ERR ( pObjUpdateReceipt->Update (&vNextReceipt.lVal) );

			// Update NextReceipt shared property
			THROW_ERR ( spmPropNextReceipt->put_Value (vNextReceipt), "spmPropNextReceipt->put_Value" );
			
			// Update MaxNum shared property
			vMaxNum.lVal = vNextReceipt.lVal + 100;
			THROW_ERR ( spmPropMaxNum->put_Value (vMaxNum), "spmPropMaxNum->put_Value" );
		}

		// Increment NextReceipt shared property
		vNextReceipt.lVal ++;
		THROW_ERR ( spmPropNextReceipt->put_Value (vNextReceipt), "spmPropNextReceipt->put_Value" );
		*plReceiptNo = vNextReceipt.lVal;
		hr = S_OK;

		// We're finished and happy
		pObjectContext->SetComplete();
		
	} catch (HRESULT hr) {
		
		//
		//	ErrorInfo is saved here because the following ADO cleanup code 
		//	may clear it.
		//
		IErrorInfo * pErrorInfo = NULL;
		GetErrorInfo(NULL, &pErrorInfo);

		// Fill in error information
		switch (lErrFlag) {
		
		// Unknown error occurred in this object
		case (0):
			TCHAR szErr [512];
			wsprintf (szErr, _T("Error 0x%x from CGetReceipt calling %s."), hr, pErrMsg);
			pErrMsg = szErr;
			// Fall through
		
		// An application error occurred in this object
		case (1):
			//
			//	we are going to put our own error in TLS, so if there is one there, clear it
			//
			if (pErrorInfo)
				pErrorInfo -> Release();
			
			AtlReportError( CLSID_CGetReceipt, pErrMsg, IID_IGetReceipt, hr);
			break;

		case (2):	// An error occurred in a called object
			//
			//	put the error back in TLS
			//
			SetErrorInfo(NULL, pErrorInfo);
			break;
		
		// Will never reach here
		default:
			break;
		}

		// Indicate our unhappiness
		if (pObjectContext)
			pObjectContext->SetAbort();
	}
	
	// Resource cleanup
	if (pObjectContext)
		pObjectContext->Release();
	
	if (spmMgr)
		spmMgr->Release();
	
	if (spmGroup)
		spmGroup->Release();
	
	if (spmPropNextReceipt)
		spmPropNextReceipt->Release();
	
	if (spmPropMaxNum)
		spmPropMaxNum->Release();
	
	if (pObjUpdateReceipt)
		pObjUpdateReceipt->Release();
	
	return hr;
}