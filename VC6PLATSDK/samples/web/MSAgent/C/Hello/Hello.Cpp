#ifndef STRICT
#define STRICT
#endif


//==========================================================================
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1997 - 2000 Microsoft Corporation.  All Rights Reserved.
//
//--------------------------------------------------------------------------
//
// This sample demonstrates the simplest Microsoft Agent application
//
//==========================================================================


#include <windows.h>
#include <tchar.h>
#include "AgtSvr.h"
#include "AgtSvr_i.c"


static const LPWSTR kpwzCharacterOld = L"\\program files\\microsoft agent\\characters\\genie.acs";
static const LPTSTR kpszAppTitle = _T("Microsoft Agent Samples");


extern "C" int PASCAL WinMain(HINSTANCE hInst,
							  HINSTANCE hInstPrev,
							  LPSTR lpCmdLine,
							  int nCmdShow) {

	HRESULT				hRes;
	_TCHAR				szError[256];
	VARIANT				vPath;
	BSTR				bszSpeak;
	long				lCharID;
	long				lRequestID;
	IAgentEx		   *pAgentEx;
	IAgentCharacterEx  *pCharacterEx = NULL;
	
	// Initialize COM

    if (FAILED(CoInitialize(NULL))) {
		MessageBox(NULL, 
				   _T("There was an error initializing COM."), 
				   kpszAppTitle, 
				   MB_OK | MB_ICONERROR);
        return -1;
	}

	// Create an instance of the Agent 2.0 server. NOTE: by
	// asking for an IAgentEx interface we know we will get
	// at least Agent 2.0. The CLSID also changed between
	// 1.5 and 2.0 so we know we won't get the 1.5 server.

	hRes = CoCreateInstance(CLSID_AgentServer,
							NULL,
							CLSCTX_SERVER,
							IID_IAgentEx,
							(LPVOID *)&pAgentEx);
	if (FAILED(hRes)) {

		wsprintf(szError, _T("There was an error initializing Microsoft Agent, code = 0x%x"), hRes);

		MessageBox(NULL, 
				   szError, 
				   kpszAppTitle, 
				   MB_OK | MB_ICONERROR | MB_TOPMOST);
	
		CoUninitialize();

		return -1;
	}

	__try {

		// First try to load the default character

		VariantInit(&vPath);
		vPath.vt = VT_EMPTY;

		hRes = pAgentEx->Load(vPath, &lCharID, &lRequestID);

		if (FAILED(hRes)) {

			// There's no default character. See if we can load the
			// character from the directory used in most version 1.5
			// applications.

			vPath.vt = VT_BSTR;
			vPath.bstrVal = SysAllocString(kpwzCharacterOld);

			if (vPath.bstrVal == NULL) {
				hRes = E_OUTOFMEMORY;
				__leave;
			}

			hRes = pAgentEx->Load(vPath, &lCharID, &lRequestID);

			// Did we successfully load a character?

			if (FAILED(hRes))
				__leave;
		}

		// Get the IAgentCharacterEx interface

		hRes = pAgentEx->GetCharacterEx(lCharID, &pCharacterEx);

		if (FAILED(hRes))
			__leave;

		// Set the language of the character

		hRes = pCharacterEx->SetLanguageID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

		if (FAILED(hRes))
			__leave;

		// Show the character.  The first parameter tells Microsoft
		// Agent to show the character by playing an animation.

		hRes = pCharacterEx->Show(FALSE, &lRequestID);

		if (FAILED(hRes))
			__leave;

		// Make the character speak

		bszSpeak = SysAllocString(L"Hello World!");

		hRes = pCharacterEx->Speak(bszSpeak, NULL, &lRequestID);

		SysFreeString(bszSpeak);

		if (FAILED(hRes))
			__leave;

		// This is a very simplistic sample.  Sleep for 10 seconds
		// and then die. 

		Sleep(10000);

	}
	__finally {

		if (FAILED(hRes)) {

			wsprintf(szError, _T("An error occurred in Microsoft Agent, code = 0x%x"), hRes);

			MessageBox(NULL, 
					   szError, 
					   kpszAppTitle, 
					   MB_OK | MB_ICONERROR | MB_TOPMOST);
		}
	}

	// Clean up

	if (pCharacterEx) {

		// Release the character interface

		pCharacterEx->Release();

		// Unload the character.  NOTE:  releasing the character
		// interface does NOT make the character go away.  You must
		// call Unload.

		pAgentEx->Unload(lCharID);
	}
	
	// Release the Agent

	pAgentEx->Release();

	VariantClear(&vPath);

	CoUninitialize();

	return 0;
}
