#include "Hello2.h"
#include "AgtSvr_i.c"
#include "Notify.h"


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
// This sample demonstrates the simplest Microsoft Agent application that
// uses a notification sink.
//
//==========================================================================


static const LPWSTR kpwzCharacterOld = L"\\program files\\microsoft agent\\characters\\genie.acs";
static const LPTSTR kpszAppTitle = _T("Microsoft Agent Samples");

extern long g_lDone = 0;


extern "C" int PASCAL WinMain(HINSTANCE hInst,
							  HINSTANCE hInstPrev,
							  LPSTR lpCmdLine,
							  int nCmdShow) {

	HRESULT				hRes;
	_TCHAR				szError[256];
	VARIANT				vPath;
	BSTR				bszSpeak;
	MSG					msg;
	long				lCharID;
	long				lRequestID;
	long				lNotifySinkID = -1;
	IAgentEx		   *pAgentEx;
	IAgentCharacterEx  *pCharacterEx = NULL;
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

		VariantInit(&vPath);

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

		// Try to load the default character

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

		hRes = pCharacterEx->Speak(bszSpeak, NULL, &g_lDone);

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

	// Clean up

	if (pCharacterEx) {

		// Release the character interface

		pCharacterEx->Release();

		// Unload the character.  NOTE:  releasing the character
		// interface does NOT make the character go away.  You must
		// call Unload.

		pAgentEx->Unload(lCharID);
	}
	
	// Release objects

	if (pSink) {

		if (lNotifySinkID != -1)
			pAgentEx->Unregister(lNotifySinkID);

		pSink->Release();
	}

	pAgentEx->Release();

	VariantClear(&vPath);

	CoUninitialize();

	return 0;
}
