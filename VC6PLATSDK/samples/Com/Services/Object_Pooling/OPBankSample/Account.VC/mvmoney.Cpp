/*+==========================================================================
  File:      mvmoney.cpp
  Summary:   Implementation of Move Money component
  Classes:   CMoveMoney
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
#include "MvMoney.h"
#include "GetRec.h"

#include <comsvcs.h>

extern HRESULT CheckAmount (IObjectContext * pObjectContext, long lAmount, BSTR * s);


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CMoveMoney::InterfaceSupportsErrorInfo
  Summary:  Confirms or denies that an error came from IMoveMoney interface
  Args:     REFIID riid			Interface ID returned in error
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CMoveMoney::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMoveMoney,
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
  Function: CMoveMoney::Perform
  Summary:  Moves money from one account to another
  Args:     long lPrimeAccount		The primary account
			long lSecondAccount		The secondary account
			long lAmount			Amount to transfer
			long lTranType			Transaction type (debit or credit)
			BSTR* pbstrResult		Informational string (NULL if error)
  Returns:  HRESULT					S_OK or E_FAIL
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
//	Perform: modifies the specified account by the specified amount
//
//	pvResult: a BSTR giving information.  NOTE: this is set to NULL when an error occurs
//
//	returns:  S_OK or E_FAIL

STDMETHODIMP CMoveMoney::Perform (IN long lPrimeAccount, IN long lSecondAccount, IN long lAmount, 
								  IN long lTranType, OUT BSTR* pbstrResult) {
	
	if (!pbstrResult)
		return E_POINTER;


	HRESULT hr = S_OK;
	IObjectContext* pObjectContext = NULL;	

	*pbstrResult = NULL;	
	hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext);
	if (!pObjectContext)
	{
		AtlReportError( CLSID_CMoveMoney, L"No Object Context", IID_IAccount, hr);
		return hr;
	}
		
/*---------------------------------------------------------------------------------------------
*
*	This check in the original MoveMoney is kind of silly -- we merely delegate to the Accont
*	object, which is going to make exactly the same check...
*
*
*	hr = CheckAmount(pObjectContext, lAmount, pbstrResult);
*	if (FAILED(hr))
*	{
*		pObjectContext -> SetAbort();
*		SafeRelease(pObjectContext);
*		AtlReportError( CLSID_CMoveMoney, *pbstrResult, IID_IAccount, hr);
*		if (pbstrResult)
*			SysFreeString(*pbstrResult);
*		return hr;
*	}
*-----------------------------------------------------------------------------------------*/

	IAccount* pObjAccount = NULL;

	IGetReceipt* pObjGetReceipt = NULL;


	if (m_bUseComPlus)
	{

		hr = CoCreateInstance(CLSID_CAccount, NULL, m_clsctxAccount, IID_IAccount, (void**)&pObjAccount);
	}
	else
	{
		// Create the account object using our context
		hr =  CoCreateInstance(CLSID_CAccount, NULL, CLSCTX_ALL, IID_IAccount, (void**)&pObjAccount);
	}
	
	if (FAILED(hr))
	{

		pObjectContext -> SetAbort();
		SafeRelease(pObjectContext);
		AtlReportError(CLSID_CMoveMoney, L"Unable to create account instance", IID_IAccount, hr);
		return hr;
	}

	// Call the post function based on the transaction type
	switch ( lTranType )
	{
		case (1):	// debit
			hr =  pObjAccount->Post (lPrimeAccount, 0 - lAmount, pbstrResult) ;
			break;
		case (2):	// credit
			hr = pObjAccount->Post (lPrimeAccount, lAmount, pbstrResult);
			break;
		case (3):	// transfer
		{

			BSTR s1 = 0;
			BSTR s2 = 0;
			WCHAR szBuf [512];
			ZeroMemory(szBuf, 512 * sizeof(WCHAR));

			// Do the credit
			hr = pObjAccount->Post (lSecondAccount, lAmount, &s1);
			if (SUCCEEDED(hr))
			{
				// Then do the debit
				hr = pObjAccount->Post (lPrimeAccount, 0 - lAmount, &s2);
				if (SUCCEEDED(hr))
				{				
					wsprintf(szBuf, L"%s;%s", s1, s2);					
				}
				else
				{
					wsprintf(szBuf, L"Post to account %ld failed.  Error: %s", lPrimeAccount, s2);					
				}
			}
			else
			{
				wsprintf(szBuf, L"Post to account %ld failed.  Error: %s", lSecondAccount, s1);
				
			}
			::SysFreeString(s1);
			::SysFreeString(s2);

			_ASSERTE(*szBuf);
			*pbstrResult = SysAllocString(szBuf);
			break;
		}
		default:
			*pbstrResult = SysAllocString(L"Invalid Transaction Type"); 
			hr = E_FAIL;			
	}


	if (hr == S_OK) // all go up to here -- get a receipt
	{

		WCHAR szBuffer [512];
		// Get Receipt Number for the transaction
		hr = CoCreateInstance (CLSID_CGetReceipt, NULL, CLSCTX_ALL, IID_IGetReceipt, (void**)&pObjGetReceipt);
		if (pObjGetReceipt)
		{
			long lngReceiptNo;
			hr = pObjGetReceipt->GetNextReceipt(&lngReceiptNo);
			if (hr == S_OK)
			{

				// Tag receipt information onto return string
				wsprintf (szBuffer, _T("; Receipt No:  %li"), lngReceiptNo);
				BSTR bstrTemp = SysAllocString(szBuffer);
				TCHAR szBuffer2 [512];
				lstrcpyn(szBuffer2, *pbstrResult, lstrlen(*pbstrResult) );
				wcsncat(szBuffer2, bstrTemp, lstrlen(bstrTemp));
				::SysFreeString (bstrTemp);
				::SysFreeString (*pbstrResult);
				*pbstrResult = SysAllocString(szBuffer2);
			}

			pObjGetReceipt -> Release();
			pObjGetReceipt = NULL;
		}
		else
		{
			wsprintf(szBuffer, L"Failed to create the receipt object.  hr = %hX", hr);
			::SysFreeString (*pbstrResult);
			*pbstrResult = SysAllocString(L"Invalid Transaction Type"); 
		}
	}


	if (FAILED(hr))
	{
		pObjectContext -> SetAbort();
		AtlReportError(CLSID_CMoveMoney, *pbstrResult, IID_IAccount, hr);
		::SysFreeString(*pbstrResult);
		*pbstrResult = NULL;
	}
	else
	{
 		// We are finished and happy
		pObjectContext->SetComplete();
	}


	// Release resources
	if (pObjAccount)
		pObjAccount->Release();
	
	if (pObjectContext)
		pObjectContext->Release();

	return hr;
}
