// Filename: Computer.cpp
//
// Description:  Implementation of CComputer
// This file contains the code that handles the interaction between a human
// player and a computer player.
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
#include "Computer.h"

#include <mtx.h>
//#include <mtxspm.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CComputer::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IComputer,
	};
	
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


STDMETHODIMP CComputer::AddNewGame (IN VARIANT_BOOL bEasy, OUT VARIANT* pvGameID, OUT VARIANT* pvOrder,
									OUT VARIANT* pvX, OUT VARIANT* pvY) {
	
	HRESULT hr = S_OK;
	
	IObjectContext* pObjectContext = NULL;
	
	ISharedPropertyGroupManager* spmMgr = NULL;
	ISharedPropertyGroup* spmGroup = NULL;
	
	ISharedProperty* spmPropCounter = NULL;
	ISharedProperty* spmPropState = NULL;
	
	pvGameID->vt = VT_I4;
	pvOrder->vt = VT_I4;
	pvX->vt = VT_I4;
	pvY->vt = VT_I4;
	
	long lGameID = 0;
	long lOrder = 0;
	long lNewX = 0;
	long lNewY = 0;
	
	
	try {
		
		// Get the object context
		THROW_ERR ( hr = GetObjectContext(&pObjectContext) );
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
		
		// Create the counter properties
		THROW_ERR ( spmGroup->CreateProperty (L"Counter", &bExists, &spmPropCounter) );
		
		// Obtain the current value of the counter
		CComVariant vCounter;		
		THROW_ERR ( spmPropCounter->get_Value (&vCounter) );
		
		// Assign gameID
		if (vCounter.lVal == 0)
			vCounter.lVal = 1;
		
		lGameID = vCounter.lVal;
		
		// Update the counter
		vCounter.lVal ++;
		THROW_ERR ( spmPropCounter->put_Value (vCounter) );
		
		// Set the state variable
		TCHAR szBuf [512];
		BSTR bstrState;
		
		wsprintf (szBuf, _T("%dState"), lGameID);
		bstrState = TCHAR2BSTR (szBuf);
		THROW_ERR ( spmGroup->CreateProperty (bstrState, &bExists, &spmPropState) );
		
		CComVariant vState;
		vState.vt = VT_I4;
		vState.lVal = 4;
		THROW_ERR ( spmPropState->put_Value (vState) );
		
		// Initialize the array
		InitArray();
		THROW_ERR ( SaveArray(lGameID) );
		
		// Assign order randomly
		srand ((unsigned) time (NULL));
		lOrder = rand() % 2 + 1;
		
		// Get computer's first move if player's order is 2
		if (lOrder == 2) {
			GetMove (lGameID, bEasy, lNewX, lNewY);
			plField [lNewX][lNewY] = 2;
			SaveArray(lGameID);
		}
		
		// Prepare return values
		pvX->lVal = lNewX;
		pvY->lVal = lNewY;
		pvOrder->lVal = lOrder;
		pvGameID->lVal = lGameID;
		
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
		wsprintf (szErr, _T("Error %d occurred in Computer::AddNewGame()"), hr);
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
	
	if (spmPropState)
		spmPropState->Release();
	
	return hr;
}


STDMETHODIMP CComputer::NewMove (IN long lGameID, IN VARIANT_BOOL bEasy, IN long lX, IN long lY,
								 OUT VARIANT* pvMyX, OUT VARIANT* pvMyY, OUT VARIANT* pvWin) {
	// Win protocol
	// ============
	// 0  -> moves did not end game
	// 1  -> player won
	// -1 -> computer won
	// 2  -> player's move tied the game
	// -2 -> computer's move tied the game
	
	HRESULT hr = S_OK;
	
	pvMyX->vt = VT_I4;
	pvMyY->vt = VT_I4;
	pvWin->vt = VT_I4;
	
	long lTurns = 0;
	long lWin = 0;
	long lNewX = 0;
	long lNewY = 0;
	
	IObjectContext* pObjectContext = NULL;
	
	
	try {
		
		// Get the object context
		THROW_ERR ( hr = GetObjectContext(&pObjectContext) );
		if (pObjectContext == NULL) {
			THROW_ERR ( E_FAIL );
		}
		
		THROW_ERR ( LoadArray(lGameID) ); 
		
		// Enter new move
		plField [lX][lY] = 1;
		
		// Check for player's win
		if (IsWin (1)) {
			
			// Player won
			lWin = 1;
			
		} else {
			
			// Check for fullness
			lTurns = HowManyTurns();
			
			if (lTurns == 9) {
				
				// Tie
				lWin = - 2;
				
			} else {
				
				// Get computer's move
				GetMove (lGameID, bEasy, lNewX, lNewY);
				plField[lNewX][lNewY] = 2;
				
				// Check for computer win
				if (IsWin(2))
					
					lWin = - 1;
				
				else
					
					// Check for fullness			
					if (lTurns == 8)
						lWin = 2;
			}
		}
		
		// Save array
		THROW_ERR ( SaveArray(lGameID) );
		
		// Set return values
		pvMyX->lVal = lNewX;
		pvMyY->lVal = lNewY;
		pvWin->lVal = lWin;
		
		// We're finished and happy		
		pObjectContext->SetComplete();
		
	} catch (HRESULT hr) {
		
		// Create an ErrorInfo object
		ICreateErrorInfo* pCreateErrInfo = NULL;
		IErrorInfo* pErrInfo = NULL;
		
		CreateErrorInfo (&pCreateErrInfo);
		pCreateErrInfo->QueryInterface (IID_IErrorInfo, (LPVOID FAR*) &pErrInfo);
		
		// Fill in error information
		TCHAR szErr[512];
		wsprintf (szErr, _T("Error %d occurred in Computer::NewMove()"), hr);
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
	
	return hr;
}


void CComputer::GetMove (long lGameID, VARIANT_BOOL bEasy, long& lX, long& lY) {
	
	long lFlag = 0;
	long lNewX = 0;
	long lNewY = 0;
	
	// Perhaps there's only possible move
	if (HowManyTurns() == 8) {
		
		// Scan for open tile
		long i,j;
		for (i = 0; i < 3; i ++) {
			for (j = 0; j < 3; j ++) {
				if (plField[i][j] == 0) {
					lNewX = i;
					lNewY = j;
					lFlag = 1;
				}
			}
		}
	}
	
	// Check for win
	if (lFlag == 0)
		lFlag = LineScan (2, lNewX, lNewY);
	
	// Check for block
	if (lFlag == 0)
		lFlag = LineScan (1, lNewX, lNewY);
	
	// Else create a new move
	if (lFlag == 0) {
		
		// Prepare random seed
		srand ((unsigned) time (NULL));
		
		// Decide intelligence level
		if (!bEasy) {
			
			// Place in center if it's open
			if (plField[1][1] == 0) {
				lNewX = 1;
				lNewY = 1;
				lFlag = 1;
				
			} else {
				
				// Place on corner, if opponent placed first move in center
				long lTurns = HowManyTurns();
				if (lTurns == 1 && plField[1][1] > 0) {
					lNewX = (rand() % 2 == 0) ? 0:2;
					lNewY = (rand() % 2 == 0) ? 0:2;
					lFlag = 1;
				} else {
					
					// Place on opposite tile, if opponent's second
					// move was placed on diagonal
					if (lTurns == 2) {
						if (plField[0][0] == 1) {
							lNewX = 2;
							lNewY = 2;
							lFlag = 1;
						}
						
						if (plField[0][2] == 1) {
							lNewX = 2;
							lNewY = 0;
							lFlag = 1;
						}
						
						if (plField[2][0] == 1) {
							lNewX = 0;
							lNewY = 2;
							lFlag = 1;
						}
						
						if (plField[2][2] == 1) {
							lNewX = 0;
							lNewY = 0;
							lFlag = 1;
						}
					}
				}
			}
			
			// Else find most intelligent move
			if (lFlag == 0) {
				
				float value = 0;
				float maxValue = 0;
				
				for (long i = 0; i < 3; i ++) {
					for (long j = 0; j < 3; j ++) {
						
						// Evaluate tile
						value = Evaluate (i, j);
						
						// Randomize equal choices
						if (value == maxValue && rand() % 2 == 0) {
							
							lNewX = i;
							lNewY = j;
							
						} else {
							
							if (value > maxValue) {
								maxValue = value;
								lNewX = i;
								lNewY = j;
							}
						}
					}
				}
			}
			
		} else {
			
			// Choose a random slot
			while (lFlag == 0) {
				
				lNewX = rand() % 3;
				lNewY = rand() % 3;
				
				if (plField [lNewX][lNewY] == 0)
					lFlag = 1;
			}
		}
	}
	
	// Prepare return values
	lX = lNewX;
	lY = lNewY;
}

float CComputer::Evaluate (long lX, long lY) {
	
	long lNewX, lNewY, lNewX2, lNewY2;
	float fEval1, fEval2, fEval3;
	
	if (plField[lX][lY] != 0) {
		
		lX = - 100;
		lY = - 100;
		return - 100;
	} else {
		
		// Evaluate defensive options
		plField[lX][lY] = 1;
		fEval2 = (float) (LineScan (1, lNewX, lNewY) / 3);
		
		// Evaluate offensive options
		plField[lX][lY] = 2;
		fEval1 = (float) LineScan (2, lNewX, lNewY);
		
		// Evaluate opponent's follow-up
		if (fEval1 > 0) {
			plField[lNewX][lNewY] = 1;
			fEval3 = (float) (LineScan (1, lNewX2, lNewY2) * 0.9);
			plField[lNewX][lNewY] = 0;
		} else
			fEval3 = 0;
		
		// Restore tiles and return final evaluation
		plField[lX][lY] = 0;
		return fEval1 + fEval2 - fEval3;
	}
}


bool CComputer::IsWin (long lPlayer) {
	
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


long CComputer::HowManyTurns () {
	
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


long CComputer::LineScan (long lPlayer, long& lX, long& lY) {
	
	long lCounter = 0;
	lX = - 100;
	lY = - 100;
	
	// Horizontal lines
	for (int i = 0; i < 3; i ++) {
		
		if (plField [1][i] == lPlayer && plField [0][i] == lPlayer && plField[2][i] == 0) {
			lX = 2;
			lY = i;
			lCounter ++;
		}
		
		if (plField [0][i] == lPlayer && plField [2][i] == lPlayer && plField[1][i] == 0) {
			lX = 1;
			lY = i;
			lCounter ++;
		}
		
		if (plField [1][i] == lPlayer && plField [2][i] == lPlayer && plField[0][i] == 0) {
			lX = 0;
			lY = i;
			lCounter ++;
		}
	}
	
	// Vertical lines
	for (i = 0; i < 3; i ++) {
		
		if (plField [i][1] == lPlayer && plField [i][0] == lPlayer && plField[i][2] == 0) {
			lX = i;
			lY = 2;
			lCounter ++;
		}
		
		if (plField [i][0] == lPlayer && plField [i][2] == lPlayer && plField[i][1] == 0) {
			lX = i;
			lY = 1;
			lCounter ++;
		}
		
		if (plField [i][1] == lPlayer && plField [i][2] == lPlayer && plField[i][0] == 0) {
			lX = i;
			lY = 0;
			lCounter ++;
		}
	}
	
	// Diagonals
	if (plField [1][1] == lPlayer && plField [0][0] == lPlayer && plField[2][2] == 0) {
		lX = 2;
		lY = 2;
		lCounter ++;
	}
	
	if (plField [1][1] == lPlayer && plField [2][0] == lPlayer && plField[0][2] == 0) {
		lX = 0;
		lY = 2;
		lCounter ++;
	}
	
	if (plField [1][1] == lPlayer && plField [0][2] == lPlayer && plField[2][0] == 0) {
		lX = 2;
		lY = 0;
		lCounter ++;
	}
	
	if (plField [1][1] == lPlayer && plField [2][2] == lPlayer && plField[0][0] == 0) {
		lX = 0;
		lY = 0;
		lCounter ++;
	}
	
	if (plField [0][0] == lPlayer && plField [2][2] == lPlayer && plField[1][1] == 0) {
		lX = 1;
		lY = 1;
		lCounter ++;
	}
	if (plField [0][2] == lPlayer && plField [2][0] == lPlayer && plField[1][1] == 0) {
		lX = 1;
		lY = 1;
		lCounter ++;
	}
	
	return lCounter;
}


HRESULT CComputer::LoadArray (long lGameID) {
	
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


HRESULT CComputer::SaveArray (long lGameID) {
	
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
	
	// Save the field SharedProperties
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