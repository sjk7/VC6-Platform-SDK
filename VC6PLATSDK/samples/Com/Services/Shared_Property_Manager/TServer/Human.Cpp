// Filename: Human.cpp
//
// Description:  Implementation of CHuman
// This file contains the code that handles the interaction between two
// human players.
//
// This file is provided as part of the Microsoft Transaction Server Samples
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 - 2000 Microsoft Corporation, All rights reserved

#include "stdafx.h"
#include "tServer.h"
#include "Human.h"

#include <mtx.h>
//#include <mtxspm.h>


STDMETHODIMP CHuman::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IHuman,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CHuman::EnterNewGame (IN BSTR bstrLocalName, OUT VARIANT* pvGameID, OUT VARIANT* pvName,
								   OUT VARIANT* pvOrder) {
	
	HRESULT hr = S_OK;
	
	IObjectContext* pObjectContext = NULL;
	
	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	
	ISharedProperty* spmPropCounter = NULL;
	ISharedProperty* spmPropFirstName = NULL;
	ISharedProperty* spmPropSecondName = NULL;
	ISharedProperty* spmPropState = NULL;

	pvGameID->vt = VT_I4;
	pvName->vt = VT_BSTR;
	pvOrder->vt = VT_I4;

	long lGameID = 0;
	long lOrder = 0;

	try {
		
		// Get the object context
		THROW_ERR ( hr = GetObjectContext (&pObjectContext) );
		if (pObjectContext == NULL) {
			THROW_ERR ( E_FAIL );
		}
		
		// Create the SharedPropertyGroupManager
		THROW_ERR ( pObjectContext->CreateInstance (CLSID_SharedPropertyGroupManager, IID_ISharedPropertyGroupManager, (void**)&spmMgr) );
		
		// Create the SharedPropertyGroup
		LONG lIsolationMode = LockMethod;
		LONG lReleaseMode = Process;
		VARIANT_BOOL bExists = VARIANT_FALSE;
		THROW_ERR ( spmMgr->CreatePropertyGroup (L"TicTacToe", &lIsolationMode, &lReleaseMode, &bExists, &spmGroup) );

		// Create SharedProperties
		CComVariant vCounter;

		THROW_ERR ( spmGroup->CreateProperty (L"Counter", &bExists, &spmPropCounter) );
		THROW_ERR ( spmPropCounter->get_Value (&vCounter) );

		CComVariant vSecondName;
		CComVariant vState;

		TCHAR szBuf [512];
		BSTR bstrSecondName;
		BSTR bstrFirstName;
		BSTR bstrState;

		// Find first open two-human game
		if (vCounter.lVal == 0) {
			vCounter.lVal = 1;
		} else {
			long lScan = 1;
			bool bFlag = false;
			while (lScan < vCounter.lVal && !bFlag) {
				
				wsprintf (szBuf, _T("%dState"), lScan);
				bstrState = TCHAR2BSTR (szBuf);
				THROW_ERR ( spmGroup->CreateProperty (bstrState, &bExists, &spmPropState) );
				::SysFreeString (bstrState);

				THROW_ERR ( spmPropState->get_Value (&vState) );

				if (vState.lVal < 2) {

					// Found a game
					bFlag = true;
				} else
					lScan ++;

				THROW_ERR ( spmPropState->Release() );
			}

			vCounter.lVal = lGameID = lScan;
		}

		wsprintf (szBuf, _T("%dSecondName"), vCounter.lVal);
		bstrSecondName = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dState"), vCounter.lVal);
		bstrState = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dFirstName"), vCounter.lVal);
		bstrFirstName = TCHAR2BSTR (szBuf);

		THROW_ERR ( spmGroup->CreateProperty (bstrFirstName, &bExists, &spmPropFirstName) );
		THROW_ERR ( spmGroup->CreateProperty (bstrSecondName, &bExists, &spmPropSecondName) );
		THROW_ERR ( spmGroup->CreateProperty (bstrState, &bExists, &spmPropState) );

		::SysFreeString (bstrFirstName);
		::SysFreeString (bstrSecondName);
		::SysFreeString (bstrState);

		// Get current state
		THROW_ERR ( spmPropState->get_Value (&vState) );

		// State table
		// ===========
		// 0 - No one in game
		// 1 - One player lurking
		// 2 - Second player joined
		// 3 - First player's turn
		// 4 - Second player's turn
		
		// Is this the first time this property has been accessed?
		if (!bExists)
			vState.lVal = 0;
		
		// Is there someone lurking already?
		if (vState.lVal == 1) {
			
			CComVariant vFirstName;

			// Get opponent's name
			THROW_ERR ( spmPropFirstName->get_Value (&vFirstName) );

			// Submit own name
			CComVariant vSecondName2;
			vSecondName2.vt = VT_BSTR;

			vSecondName2.bstrVal = ::SysAllocString (bstrLocalName);
			THROW_ERR ( spmPropSecondName->put_Value (vSecondName2) );
			::SysFreeString (vSecondName2.bstrVal);

			// Update state
			vState.lVal = 2;
			THROW_ERR ( spmPropState->put_Value (vState) );

			// Assign gameID
			lGameID = vCounter.lVal;

			// Initialize the game screen array
			InitArray();
			THROW_ERR ( SaveArray(lGameID) );

			// Prepare return values
			pvName->bstrVal = ::SysAllocString (vFirstName.bstrVal);
			pvOrder->lVal = 2;
			pvGameID->lVal = lGameID;
		
		} else {
			
			CComVariant vFirstName;
			vFirstName.vt = VT_BSTR;

			// Update first name
			vFirstName.bstrVal = ::SysAllocString (bstrLocalName);
			THROW_ERR ( spmPropFirstName->put_Value (vFirstName) );
			::SysFreeString (vFirstName.bstrVal);

			// Update counter for next game
			vCounter.lVal = vCounter.lVal + 1;
			THROW_ERR ( spmPropCounter->put_Value (vCounter) );

			// Update state
			vState.lVal = 1;
			THROW_ERR ( spmPropState->put_Value (vState) );

			// Assign gameID
			lGameID = vCounter.lVal - 1;
	
			// Prepare return values
			pvName->bstrVal = ::SysAllocString (L"No one");
			pvOrder->lVal = 1;
			pvGameID->lVal = lGameID;
		}

		// We're finished and happy
		pObjectContext->SetComplete();
	
	} catch (HRESULT hr) {
		
		// Create an ErrorInfo object
		ICreateErrorInfo* pCreateErrInfo = NULL;
		IErrorInfo* pErrInfo = NULL;
		
		CreateErrorInfo (&pCreateErrInfo);
		pCreateErrInfo->QueryInterface (IID_IErrorInfo, (LPVOID FAR*) &pErrInfo);
		
		// Fill in error information
		TCHAR szErr [512];
		wsprintf (szErr, _T("Error %d occurred in Human::EnterNewGame()"), hr);
		BSTR bstrDesc = TCHAR2BSTR (szErr);

		pCreateErrInfo->SetGUID (IID_IComputer);
		pCreateErrInfo->SetSource (L"Computer");
		pCreateErrInfo->SetDescription (bstrDesc);
		::SysFreeString (bstrDesc);
		
		// Confirm error information
		SetErrorInfo (0, pErrInfo);
		
		// Clean up the error objects
		if (pCreateErrInfo)
			pCreateErrInfo->Release();
		
		if (pErrInfo)
			pErrInfo->Release();
		
		// Indicate our unhappiness
		if (pObjectContext)
			pObjectContext->SetAbort();
		
		hr = E_FAIL;
	}

	if (pObjectContext)
		pObjectContext->Release();
	
	if (spmMgr)
		spmMgr->Release();
	
	if (spmGroup)
		spmGroup->Release();
	
	if (spmPropCounter)
		spmPropCounter->Release();

	if (spmPropFirstName)
		spmPropFirstName->Release();

	if (spmPropSecondName)
		spmPropSecondName->Release();

	if (spmPropState)
		spmPropState->Release();
	
	return hr;
}


STDMETHODIMP CHuman::NewMove (IN long lGameID, IN long lOrder, IN long lX, IN long lY, OUT VARIANT* pvWin) {

	// Win protocol
	// ============
	// 0  -> move did not end game
	// 1  -> player won
	// -1 -> remote player won (won't occur in this function)
	// 2  -> player's move tied the game
	// -2 -> remote player's move tied the game (won't occur in this function)

	HRESULT hr = S_OK;

	IObjectContext* pObjectContext = NULL;

	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	
	ISharedProperty* spmPropState = NULL;
	ISharedProperty* spmPropX = NULL;
	ISharedProperty* spmPropY = NULL;
	ISharedProperty* spmPropWin = NULL;

	pvWin->vt = VT_I4;

	long lWin = 0;


	try {
		
		// Get the object context
		THROW_ERR ( hr = GetObjectContext(&pObjectContext) );
		if (pObjectContext == NULL) {
			THROW_ERR ( E_FAIL );
		}
		
		// Create the SharedPropertyGroupManager
		THROW_ERR ( pObjectContext->CreateInstance (CLSID_SharedPropertyGroupManager, 
			IID_ISharedPropertyGroupManager, (void**)&spmMgr) );
		
		// Create the SharedPropertyGroup
		LONG lIsolationMode = LockMethod;
		LONG lReleaseMode = Process;
		VARIANT_BOOL bExists = VARIANT_FALSE;
		THROW_ERR ( spmMgr->CreatePropertyGroup (L"TicTacToe", &lIsolationMode, &lReleaseMode,
			&bExists, &spmGroup) );

		// Create SharedProperties
		BSTR bstrState;
		BSTR bstrX;
		BSTR bstrY;
		BSTR bstrWin;
		TCHAR szBuf[512];
		wsprintf (szBuf, _T("%dState"), lGameID);
		bstrState = TCHAR2BSTR (szBuf);	
		wsprintf (szBuf, _T("%dX"), lGameID);
		bstrX = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dY"), lGameID);
		bstrY = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dWin"), lGameID);
		bstrWin = TCHAR2BSTR (szBuf);

		THROW_ERR ( spmGroup->CreateProperty (bstrState, &bExists, &spmPropState) );
		THROW_ERR ( spmGroup->CreateProperty (bstrX, &bExists, &spmPropX) );
		THROW_ERR ( spmGroup->CreateProperty (bstrY, &bExists, &spmPropY) );
		THROW_ERR ( spmGroup->CreateProperty (bstrWin, &bExists, &spmPropWin) );

		::SysFreeString (bstrState);
		::SysFreeString (bstrX);
		::SysFreeString (bstrY);
		::SysFreeString (bstrWin);

		CComVariant vState;
		CComVariant vX;
		CComVariant vY;
		CComVariant vWin;
		vState.vt = VT_I4;
		vX.vt = VT_I4;
		vY.vt = VT_I4;
		vWin.vt = VT_I4;

		// Load screen data
		THROW_ERR ( LoadArray(lGameID) );
		
		// Save player's move to local storage and to Spam
		plField[lX][lY] = lOrder;
		
		vX.lVal = lX;
		vY.lVal = lY;
		THROW_ERR ( spmPropX->put_Value (vX) );
		THROW_ERR ( spmPropY->put_Value (vY) );

		// Submit new state
		if (lOrder == 1)
			vState.lVal = 4;
		else
			vState.lVal = 3;

		THROW_ERR ( spmPropState->put_Value (vState) );

		// Commit move to global storage
		THROW_ERR ( SaveArray (lGameID) );

		// Check for win
		if (IsWin (lOrder)) {

			// Player wins
			lWin = 1;

			// Other player loses
			vWin.lVal = - 1;
			THROW_ERR ( spmPropWin->put_Value (vWin) );
		}

		else if (HowManyTurns() == 9) {
			
			// Player ties on his move
			lWin = 2;

			// Other player ties on opponent's move
			vWin.lVal = - 2;
			THROW_ERR ( spmPropWin->put_Value (vWin) );
		}

		// Prepare return values
		pvWin->lVal = lWin;

		// We're happy and finished
		pObjectContext->SetComplete();

	} catch (HRESULT hr) {
		
		// Create an ErrorInfo object
		ICreateErrorInfo* pCreateErrInfo = NULL;
		IErrorInfo* pErrInfo = NULL;
		
		CreateErrorInfo (&pCreateErrInfo);
		pCreateErrInfo->QueryInterface (IID_IErrorInfo, (LPVOID FAR*) &pErrInfo);
		
		// Fill in error information
		TCHAR szErr [512];
		wsprintf (szErr, _T("Error %d occurred in Human::NewMove()"), hr);		
		BSTR bstrDesc = TCHAR2BSTR (szErr);
		pCreateErrInfo->SetGUID (IID_IComputer);
		pCreateErrInfo->SetSource (L"Computer");
		pCreateErrInfo->SetDescription (bstrDesc);
		::SysFreeString (bstrDesc);
		
		// Confirm error information
		SetErrorInfo (0, pErrInfo);
		
		// Clean up the error objects
		if (pCreateErrInfo)
			pCreateErrInfo->Release();
		
		if (pErrInfo)
			pErrInfo->Release();
		
		// Indicate our unhappiness
		if (pObjectContext)
			pObjectContext->SetAbort();
		
		hr = E_FAIL;
	}
	
	if (pObjectContext)
		pObjectContext->Release();
	
	if (spmMgr)
		spmMgr->Release();
	
	if (spmGroup)
		spmGroup->Release();

	if (spmPropState)
		spmPropState->Release();

	if (spmPropX)
		spmPropX->Release();

	if (spmPropY)
		spmPropY->Release();

	if (spmPropWin)
		spmPropWin->Release();

	return hr;

}


STDMETHODIMP CHuman::GetNewMove (IN long lGameID, IN long lOrder, OUT VARIANT* pvName,
								 OUT VARIANT* pvFoeX, OUT VARIANT* pvFoeY, OUT VARIANT* pvWin,
								 OUT VARIANT* pvUpdate) {

	// Win protocol
	// ============
	// 0  -> move did not end game
	// 1  -> player won (won't occur in this function)
	// -1 -> remote player won 
	// 2  -> player's move tied the game (won't occur in this function)
	// -2 -> remote player's move tied the game 

	HRESULT hr = S_OK;

	IObjectContext* pObjectContext = NULL;

	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	ISharedProperty* spmPropState = NULL;
	ISharedProperty* spmPropX = NULL;
	ISharedProperty* spmPropY = NULL;
	ISharedProperty* spmPropWin = NULL;
	ISharedProperty* spmPropSecondName = NULL;

	pvName->vt = VT_BSTR;
	pvFoeX->vt = VT_I4;
	pvFoeY->vt = VT_I4;
	pvWin->vt = VT_I4;
	pvUpdate->vt = VT_I4;

	long lWin = 0;
	long lUpdate = 0;
	long lX = 0;
	long lY = 0;


	try {

		// Get the object context
		THROW_ERR ( hr = GetObjectContext(&pObjectContext) );
		if (pObjectContext == NULL) {
			THROW_ERR ( E_FAIL );
		}
		
		// Create the SharedPropertyGroupManager
		THROW_ERR ( pObjectContext->CreateInstance (CLSID_SharedPropertyGroupManager,
			IID_ISharedPropertyGroupManager, (void**)&spmMgr) );
		
		// Create the SharedPropertyGroup
		LONG lIsolationMode = LockMethod;
		LONG lReleaseMode = Process;
		VARIANT_BOOL bExists = VARIANT_FALSE;
		THROW_ERR ( spmMgr->CreatePropertyGroup (L"TicTacToe", &lIsolationMode, &lReleaseMode,
			&bExists, &spmGroup) );

		// Create SharedProperties
		BSTR bstrState;
		BSTR bstrX;
		BSTR bstrY;
		BSTR bstrWin;
		BSTR bstrSecondName;
		TCHAR szBuf[512];
		wsprintf (szBuf, _T("%dState"), lGameID);
		bstrState = TCHAR2BSTR (szBuf);	
		wsprintf (szBuf, _T("%dX"), lGameID);
		bstrX = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dY"), lGameID);
		bstrY = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dWin"), lGameID);
		bstrWin = TCHAR2BSTR (szBuf);
		wsprintf (szBuf, _T("%dSecondName"), lGameID);
		bstrSecondName = TCHAR2BSTR (szBuf);

		THROW_ERR ( spmGroup->CreateProperty (bstrState, &bExists, &spmPropState) );
		THROW_ERR ( spmGroup->CreateProperty (bstrX, &bExists, &spmPropX) );
		THROW_ERR ( spmGroup->CreateProperty (bstrY, &bExists, &spmPropY) );
		THROW_ERR ( spmGroup->CreateProperty (bstrWin, &bExists, &spmPropWin) );
		THROW_ERR ( spmGroup->CreateProperty (bstrSecondName, &bExists, &spmPropSecondName) );

		::SysFreeString (bstrState);
		::SysFreeString (bstrX);
		::SysFreeString (bstrY);
		::SysFreeString (bstrWin);
		::SysFreeString (bstrSecondName);

		// Get state and move parameters
		CComVariant vState;
		CComVariant vX;
		CComVariant vY;
		CComVariant vWin;
		CComVariant vSecondName;
		THROW_ERR ( spmPropState->get_Value (&vState) );
		THROW_ERR ( spmPropX->get_Value (&vX) );
		THROW_ERR ( spmPropY->get_Value (&vY) );
		THROW_ERR ( spmPropWin->get_Value (&vWin) );
		THROW_ERR ( spmPropSecondName->get_Value (&vSecondName) );

		switch (vState.lVal) {

		case (0):
		
			// Shouldn't happen
			THROW_ERR ( E_FAIL);
			break;

		case (1):

			// Still waiting for next player to join
			lUpdate = 0;
			break;

		case (2):

			// Other player just joined
			if (lOrder == 1) {
				lUpdate = 2;
				pvName->bstrVal = ::SysAllocString (vSecondName.bstrVal);

				// It's now the first player's turn
				vState.lVal = 3;
				THROW_ERR ( spmPropState->put_Value (vState) );
			}
			
			break;

		case (3):
		case (4):

			long lTemp;
			if (vState.lVal == 3)
				lTemp = 1;
			else
				lTemp = 2;

			// Has other player moved?
			if (lOrder == lTemp) {

				// Other player has moved
				lX = vX.lVal;
				lY = vY.lVal;
				lWin = vWin.lVal;
				lUpdate = 1;

			} else {

				// Waiting for other player to move
				lUpdate = 0;
			}

			break;

		default:
		
			// Shouldn't happen
			THROW_ERR ( E_FAIL );
			break;
		}

		// Prepare return values
		pvFoeX->lVal = lX;
		pvFoeY->lVal = lY;
		pvWin->lVal = lWin;
		pvUpdate->lVal = lUpdate;
		
		// We are finished and happy
		pObjectContext->SetComplete();

	} catch (HRESULT hr) {

		// Create an ErrorInfo object
		ICreateErrorInfo* pCreateErrInfo = NULL;
		IErrorInfo* pErrInfo = NULL;
		
		CreateErrorInfo (&pCreateErrInfo);
		pCreateErrInfo->QueryInterface (IID_IErrorInfo, (LPVOID FAR*) &pErrInfo);
		
		// Fill in error information
		TCHAR szErr [512];
		wsprintf (szErr, _T("Error %d occurred in Human::GetNewMove()"), hr);
		BSTR bstrDesc = TCHAR2BSTR (szErr);
		pCreateErrInfo->SetGUID (IID_IComputer);
		pCreateErrInfo->SetSource (L"Computer");
		pCreateErrInfo->SetDescription (bstrDesc);
		::SysFreeString (bstrDesc);

		// Confirm error information
		SetErrorInfo (0, pErrInfo);
		
		// Clean up the error objects
		if (pCreateErrInfo)
			pCreateErrInfo->Release();
		
		if (pErrInfo)
			pErrInfo->Release();
		
		// Indicate our unhappiness
		if (pObjectContext)
			pObjectContext->SetAbort();
		
		hr = E_FAIL;
	}

	if (pObjectContext)
		pObjectContext->Release();
	
	if (spmMgr)
		spmMgr->Release();
	
	if (spmGroup)
		spmGroup->Release();

	if (spmPropState)
		spmPropState->Release();

	if (spmPropX)
		spmPropX->Release();

	if (spmPropY)
		spmPropY->Release();

	if (spmPropWin)
		spmPropWin->Release();

	if (spmPropSecondName)
		spmPropSecondName->Release();

	return hr;
}


bool CHuman::IsWin (long lPlayer) {
	
	bool bWin = false;

	for (int i = 0; i < 3; i ++) {
		if (plField [i][0] == plField [i][1] && plField [i][1] == plField [i][2] && plField [i][0] == lPlayer)
			bWin = true;
		if (plField [0][i] == plField [1][i] && plField [1][i] == plField [2][i] && plField [0][i] == lPlayer)
			bWin = true;
	}
	
	if (plField [0][0] == plField [1][1] && plField [1][1] == plField [2][2] && plField [1][1] == lPlayer)
		bWin = true;
	if (plField [2][0] == plField [1][1] && plField [1][1] == plField [0][2] && plField [1][1] == lPlayer)
		bWin = true;

	return bWin;
}


long CHuman::HowManyTurns () {

	long lTurns = 0;
	
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j ++) {
			if (plField[i][j] > 0) {
				lTurns ++;
			}
		}
	}

	return lTurns;
}


HRESULT CHuman::LoadArray (long lGameID) {
	
	HRESULT hr = S_OK;

	IObjectContext* pObjectContext = NULL;

	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	ISharedProperty* spmPropField[3][3];

	// Get context
	hr = GetObjectContext(&pObjectContext);

	// Create the SharedPropertyGroupManager
	hr = pObjectContext->CreateInstance (CLSID_SharedPropertyGroupManager, IID_ISharedPropertyGroupManager, (void**)&spmMgr);
	
	// Create the SharedPropertyGroup
	LONG lIsolationMode = LockMethod;
	LONG lReleaseMode = Process;
	VARIANT_BOOL bExists = VARIANT_FALSE;
	hr = spmMgr->CreatePropertyGroup (L"TicTacToe", &lIsolationMode, &lReleaseMode, &bExists, &spmGroup);
	
	// Load the field SharedProperties
	TCHAR szBuf [512];
	BSTR bstrField;
	CComVariant vField;

	for (long i = 0; i < 3; i ++ ) {
		for (long j = 0; j < 3; j ++) {
	
			wsprintf (szBuf, _T("%dField%d%d"), lGameID, i, j);
			bstrField = TCHAR2BSTR (szBuf);
			hr = spmGroup->CreateProperty (bstrField, &bExists, &spmPropField[i][j]);
			::SysFreeString (bstrField);

			hr = spmPropField[i][j]->get_Value (&vField);
			plField[i][j] = vField.lVal;
		}
	}

	if (pObjectContext)
		pObjectContext->Release();
	
	if (spmMgr)
		spmMgr->Release();
	
	if (spmGroup)
		spmGroup->Release();
	
	for (i = 0; i < 3; i ++) {
		for (long j = 0; j < 3; j ++) {
			if (spmPropField[i][j]) {
				spmPropField[i][j]->Release();
			}
		}
	}

	return hr;
}


HRESULT CHuman::SaveArray (long lGameID) {

	HRESULT hr = S_OK;

	IObjectContext* pObjectContext = NULL;
		
	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	ISharedProperty* spmPropField[3][3];

	// Get context
	hr = GetObjectContext(&pObjectContext);

	// Create the SharedPropertyGroupManager
	hr = pObjectContext->CreateInstance (CLSID_SharedPropertyGroupManager, IID_ISharedPropertyGroupManager, (void**)&spmMgr);
	
	// Create the SharedPropertyGroup
	LONG lIsolationMode = LockMethod;
	LONG lReleaseMode = Process;
	VARIANT_BOOL bExists = VARIANT_FALSE;
	hr = spmMgr->CreatePropertyGroup (L"TicTacToe", &lIsolationMode, &lReleaseMode, &bExists, &spmGroup);
	
	// Save the field shared properties
	TCHAR szBuf [512];
	BSTR bstrField;
	CComVariant vField;
	vField.vt = VT_I4;

	for (long i = 0; i < 3; i ++ ) {
		for (long j = 0; j < 3; j ++) {
	
			wsprintf (szBuf, _T("%dField%d%d"), lGameID, i, j);
			bstrField = TCHAR2BSTR (szBuf);
			hr = spmGroup->CreateProperty (bstrField, &bExists, &spmPropField[i][j]);
			::SysFreeString (bstrField);

			vField.lVal = plField[i][j];
			hr = spmPropField[i][j]->put_Value (vField);
		}
	}

	if (pObjectContext)
		pObjectContext->Release();
	
	if (spmMgr)
		spmMgr->Release();
	
	if (spmGroup)
		spmGroup->Release();
	
	for (i = 0; i < 3; i ++) {
		for (long j = 0; j < 3; j ++) {
			if (spmPropField[i][j]) {
				spmPropField[i][j]->Release();
			}
		}
	}

	return hr;
}