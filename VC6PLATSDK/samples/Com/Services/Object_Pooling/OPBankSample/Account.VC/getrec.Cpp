/*+==========================================================================
  File:      GetRec.cpp
  Summary:   Implementation of Object Pooled Account component (get receipt)
  Classes:   CGetReceipt
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

#include "stdafx.h"
#include "Account.h"
#include <comsvcs.h>
#include "GetRec.h"
#include "UpdRec.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CGetReceipt::InterfaceSupportsErrorInfo
  Summary:  Confirms or denies that an error came from IGetReceipt interface
  Args:     REFIID riid			Interface ID returned in error
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CGetReceipt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGetReceipt,
	};
	
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		// refer to guiddef.h
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CGetReceipt::GetNextReceipt
  Summary:  Returns the next available receipt number
  Args:     long* plReceiptNo
  Returns:  HRESULT				S_OK or E_FAIL
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
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
	BSTR sErr = NULL;
	LONG lIsolationMode = LockMethod;
	LONG lReleaseMode = Process;
	CComVariant vMaxNum;
	VARIANT_BOOL bExists = VARIANT_FALSE;


	hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext);
	if (!pObjectContext)
	{
		sErr = SysAllocString(L"No Object Context in GetNextReceipt");
		goto end;
	}


	// Create the SharedPropertyGroupManager
	hr = CoCreateInstance (CLSID_SharedPropertyGroupManager, NULL, CLSCTX_ALL, IID_ISharedPropertyGroupManager, (void**)&spmMgr);
	if (FAILED(hr))
	{
		sErr = SysAllocString(L"Failed to create CLSID_SharedPropertyGroupManager");
		goto end;
	}

		
	// Create the SharedPropertyGroup
	
	hr = spmMgr->CreatePropertyGroup (L"Receipt", &lIsolationMode, &lReleaseMode, &bExists, &spmGroup);
	if (FAILED(hr))
	{
		sErr = SysAllocString(L"Failed to create 'Receipt' group in SPM");
		goto end;
	}
		
	
	// Create the two shared properties
	hr = spmGroup->CreateProperty (L"Next", &bExists, &spmPropNextReceipt);
	if (FAILED(hr))
	{
		sErr = SysAllocString(L"Failed to create 'Next' property in SPM");
		goto end;
	}

	hr = spmGroup->CreateProperty (L"MaxNum", &bExists, &spmPropMaxNum);
	if (FAILED(hr))
	{
		sErr = SysAllocString(L"Failed to create 'MaxNum' property in SPM");
		goto end;
	}

	
	// Obtain their current values
	hr = spmPropNextReceipt->get_Value (&vNextReceipt);
	_ASSERTE(hr==S_OK);
	hr = spmPropMaxNum->get_Value (&vMaxNum);
	_ASSERTE(hr==S_OK);
	
	// Does MaxNum require an update?
	if (vNextReceipt.lVal >= vMaxNum.lVal) 
	{
		
		// Create an UpdateReceipt object
		hr = CoCreateInstance (CLSID_CUpdateReceipt, NULL, CLSCTX_ALL, IID_IUpdateReceipt,	(void**)&pObjUpdateReceipt);
		if (FAILED(hr))
		{
			sErr = SysAllocString(L"Failed to create UpdateReceipt object");
			goto end;

		}
		
		// Update NextReceipt
		hr = pObjUpdateReceipt->Update (&vNextReceipt.lVal);
		if (FAILED(hr))
			goto end; // ErrorInfo populated

		// Update NextReceipt shared property
		hr = spmPropNextReceipt->put_Value (vNextReceipt);
		_ASSERTE(hr==S_OK);
		
		// Update MaxNum shared property
		vMaxNum.lVal = vNextReceipt.lVal + 100;
		hr = spmPropMaxNum->put_Value (vMaxNum);
		_ASSERTE(hr == S_OK);
	}

	// Increment NextReceipt shared property
	vNextReceipt.lVal ++;
	hr = spmPropNextReceipt->put_Value (vNextReceipt);
	_ASSERTE(hr==S_OK);
	*plReceiptNo = vNextReceipt.lVal;
end:

	if (sErr)
	{

		AtlReportError( CLSID_CGetReceipt, sErr, IID_IGetReceipt, hr);
		if (pObjectContext)
			pObjectContext -> SetAbort();
		SysFreeString(sErr);

	}

	else
	{
		// We're finished and happy
		pObjectContext->SetComplete();

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