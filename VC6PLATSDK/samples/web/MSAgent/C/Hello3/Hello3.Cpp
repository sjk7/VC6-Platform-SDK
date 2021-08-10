#include "Hello3.h"
#include "AgtSvr_i.c"
#include "Notify.h"
#include <malloc.h>


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
// This sample demonstrates loading 2 characters and synchronizing
// their actions.
//
//==========================================================================


// Constant character filenames. Agent 2.0 will look in the %msagent%\chars
// directory for these files.

static const LPWSTR kpwzGenie = L"genie.acs";
static const LPWSTR kpwzMerlin = L"merlin.acs";

// Common version 1.5 path for characters

static const LPWSTR kpwzOldPath = L"\\Program Files\\Microsoft Agent\\characters\\";

// App Title

static const LPTSTR kpszAppTitle = _T("Microsoft Agent Samples");

// Globals

extern long g_lDone = 0;


HRESULT LoadCharacter(IAgentEx *pAgentEx, 
					  LPWSTR pwzFilename, 
					  long *plCharacterID, 
					  IAgentCharacterEx **ppCharacterEx) {

	VARIANT	vPath;
	HRESULT	hRes;
	long	lRequestID;
	LPWSTR	pwzPath;

	// Create a VARIANT for the filename/path

	VariantInit(&vPath);
	vPath.vt = VT_BSTR;
	vPath.bstrVal = SysAllocString(pwzFilename);

	if (vPath.bstrVal == NULL)
		return E_OUTOFMEMORY;

	// Load the character using it's filename only. NOTE: Agent 2.0
	// will look in the %msagent%\chars directory for these files.

	hRes = pAgentEx->Load(vPath, plCharacterID, &lRequestID);

	VariantClear(&vPath);

	// Did we load it successfully?

	if (FAILED(hRes)) {

		// Try to load the character from the directory used 
		// in most version 1.5 applications.

		// First, allocate a buffer on the stack for the full pathname.
		// NOTE: _alloca does NOT return NULL on failure. It raises an
		// exception so be sure to wrap this in a try/catch or __try/__except
		// block.

		__try {

			pwzPath = (LPWSTR)_alloca((wcslen(kpwzOldPath) + wcslen(pwzFilename) + 1) * sizeof(WCHAR));

		}
		__except(EXCEPTION_EXECUTE_HANDLER) {

			return E_OUTOFMEMORY;
		}

		// Build the pathname

		wcscpy(pwzPath, kpwzOldPath);
		wcscat(pwzPath, pwzFilename);

		vPath.vt = VT_BSTR;
		vPath.bstrVal = SysAllocString(pwzPath);

		if (vPath.bstrVal == NULL)
			return E_OUTOFMEMORY;

		// Try to load the character from the common 1.5 path

		hRes = pAgentEx->Load(vPath, plCharacterID, &lRequestID);

		VariantClear(&vPath);

		// Did we load it?

		if (FAILED(hRes))
			return hRes;
	}

	// Get the IAgentCharacterEx interface

	return pAgentEx->GetCharacterEx(*plCharacterID, ppCharacterEx);
}


extern "C" int PASCAL WinMain(HINSTANCE hInst,
							  HINSTANCE hInstPrev,
							  LPSTR lpCmdLine,
							  int nCmdShow) {

	HRESULT				hRes;
	_TCHAR				szError[256];
	BSTR				bszSpeak;
	MSG					msg;
	long				lGenieID;
	long				lMerlinID;
	long				lRequestID;
	long				lWaitID;
	long				lNotifySinkID = -1;
	IAgentEx		   *pAgentEx;
	IAgentCharacterEx  *pGenie = NULL;
	IAgentCharacterEx  *pMerlin = NULL;
	AgentNotifySink	   *pSink = NULL;
	
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
				   MB_OK | MB_ICONERROR);
	
		CoUninitialize();

		return -1;
	}

	__try {

		// Create a notify sink

		pSink = new AgentNotifySink;

		if (pSink == NULL) {
			hRes = E_OUTOFMEMORY;
			__leave;
		}

		// AddRef it

		pSink->AddRef();

		// And register it with Microsoft Agent

		hRes = pAgentEx->Register((IUnknown *)pSink, &lNotifySinkID);

		if (FAILED(hRes))
			__leave;

		// Load Genie

		hRes = LoadCharacter(pAgentEx, kpwzGenie, &lGenieID, &pGenie);

		if (FAILED(hRes))
			__leave;

		// And Merlin

		hRes = LoadCharacter(pAgentEx, kpwzMerlin, &lMerlinID, &pMerlin);

		if (FAILED(hRes))
			__leave;

		// Set their language ids

		hRes = pGenie->SetLanguageID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

		if (FAILED(hRes))
			__leave;

		hRes = pMerlin->SetLanguageID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

		if (FAILED(hRes))
			__leave;

		// Position them

		hRes = pGenie->MoveTo(0, 100, 0, &lRequestID);

		if (FAILED(hRes))
			__leave;

		hRes = pMerlin->MoveTo(200, 100, 0, &lRequestID);

		if (FAILED(hRes))
			__leave;

		// Show them

		hRes = pGenie->Show(FALSE, &lRequestID);

		if (FAILED(hRes))
			__leave;

		hRes = pMerlin->Show(FALSE, &lRequestID);

		if (FAILED(hRes))
			__leave;

		// Have Genie gesture towards Merlin

		hRes = pGenie->GestureAt(150, 100, &lRequestID);

		if (FAILED(hRes))
			__leave;

		// And have Genie say hello to Merlin

		bszSpeak = SysAllocString(L"Hi there Merlin.");

		hRes = pGenie->Speak(bszSpeak, NULL, &lWaitID);

		SysFreeString(bszSpeak);

		if (FAILED(hRes))
			__leave;

		// Make Merlin wait for Genie to finish speaking

		hRes = pMerlin->Wait(lWaitID, &lRequestID);

		if (FAILED(hRes))
			__leave;

		// Have Merlin gesture towards Genie

		hRes = pMerlin->GestureAt(0, 100, &lRequestID);

		if (FAILED(hRes))
			__leave;

		// And then speak back to Genie

		bszSpeak = SysAllocString(L"Hi Genie. See you later");

		hRes = pMerlin->Speak(bszSpeak, NULL, &g_lDone);

		SysFreeString(bszSpeak);

		if (FAILED(hRes))
			__leave;

		// Start the message loop.  A WM_QUIT message will be posted
		// when we get the RequestComplete notification from Microsoft Agent.

		while (GetMessage(&msg, NULL, 0, 0) > 0)
			DispatchMessage(&msg);

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

	// Release the character interfaces.  NOTE:  releasing the character
	// interface does NOT make the character go away.  You must
	// call Unload.

	if (pGenie) {
		pGenie->Release();
		pAgentEx->Unload(lGenieID);
	}
	
	if (pMerlin) {
		pMerlin->Release();
		pAgentEx->Unload(lMerlinID);
	}
	
	// Release objects

	if (pSink) {

		if (lNotifySinkID != -1)
			pAgentEx->Unregister(lNotifySinkID);

		pSink->Release();
	}

	pAgentEx->Release();

	CoUninitialize();

	return 0;
}
