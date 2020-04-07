// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////
// 
// CustSur.cpp  
//
// Custom Surrogate sample WinMain.  
// 
// Order of events:
// 
// 1. Initialize COM libraries
// 2. Initialize security context based on AppID of the inproc CLSID being requested
// 3. Instantiate the surrogate object and register it with COM
// 4. Call our surrogate object's ISurrogate::LoadDllServer() for the first CLSID
//    that we will be hosting (this is passed to us via szCmdParam upon entry)
// 5. Pump messages until WM_QUIT
// 6. Uninitialize COM libraries and return.
// 
////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "csur.h"


HRESULT GetAppIDFromClsid(LPSTR szClsid, IID & AppID);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR szCmdParam, int)
{
	// 1. register with COM as STA
	// 
	// Note: when initializing OLE as COINIT_MULTITHREADED, use a semaphore or
	// other mechanism to convey termination condition for WinMain() instead of 
	// PostQuitMessage(0) in the ISurrogate::FreeSurrogate() call.  WinMain() will
	// be called on a different thread from the surrogate object and PostQuitMessage()
	// will only terminate the surrogate object thread, not WinMain()'s.  
	HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	assert(hr == S_OK);
	
	OutputDebugString("CoInitializeEx() called.");

	// 2. get the AppID associated with the requested CLSID and initialize security
	// based on it.
	IID appid;

	CHAR szCLSID[39];
	strncpy(szCLSID, szCmdParam, 39);
	szCLSID[38] = 0;
	hr = GetAppIDFromClsid(szCLSID, appid);

	assert(hr == S_OK);

    hr = CoInitializeSecurity((PSECURITY_DESCRIPTOR*)&appid, 
									-1, NULL, NULL, 0, 0, NULL, EOAC_APPID, NULL);
	assert(hr == S_OK);

	OutputDebugString("CoInitializeSecurity() called.");

	// 3. register the surrogate object
	CSurrogate sur;
	hr = CoRegisterSurrogate(&sur);
	assert(hr == S_OK);
	OutputDebugString("CoRegisterSurrogate() called.");

	// 4. we were passed the clsid for whom this surrogate exe was loaded by SCM 
	// we now need to explicitly call ISurrogate::LoadDllServer() on that clsid
	OLECHAR wszGUID[39];
	mbstowcs(wszGUID, szCmdParam, 39);
	wszGUID[38]=0;
	CLSID clsid;
	hr = CLSIDFromString(wszGUID, &clsid);
	assert(hr == S_OK);
	
	hr = sur.LoadDllServer(clsid);
	assert(hr == S_OK);

	OutputDebugString("LoadDllServer() called.");

	// 5. the message pump: we can do custom behaviour here, too.

	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
		DispatchMessage(&msg);

	// 6. Uninitialize COM libraries and return.
	CoUninitialize();
	OutputDebugString("CoUninitialize() called.");
	return 0;

}

// 
// Look up the AppID associated with the requested CLSID and return it to the caller
//
HRESULT GetAppIDFromClsid(LPSTR szClsid, IID & AppID)
{
    HKEY hkHKCR_CLSID = NULL;
    HKEY hkObjClsid = NULL;
    CHAR szAppid[MAX_GUIDSTR_LEN + 1];
    WCHAR wszAppid[MAX_GUIDSTR_LEN + 1];
    DWORD dwAppidSize = sizeof(szAppid);
    HRESULT hr = E_FAIL;

    // open HKEY_CLASSES_ROOT/CLSID
    if(RegOpenKeyExA(HKEY_CLASSES_ROOT, szClsidKeyName,	0, KEY_READ, &hkHKCR_CLSID) != ERROR_SUCCESS)
		return FALSE;

    // open the key for the requested CLSID
    if(RegOpenKeyExA(hkHKCR_CLSID, szClsid, 0, KEY_READ,	&hkObjClsid) != ERROR_SUCCESS)
		goto cleanup_and_exit;

    // read the appid value
    if(RegQueryValueExA(hkObjClsid, szAppidValueName, NULL, NULL, (LPBYTE)szAppid, &dwAppidSize) != ERROR_SUCCESS)
		goto cleanup_and_exit;

    // we're done with the registry, close the keys
    RegCloseKey(hkObjClsid);
    hkObjClsid = NULL;

    RegCloseKey(hkHKCR_CLSID);
    hkHKCR_CLSID = NULL;

    // now convert the appid string from the registry into
    // a unicode string
    if(!(MultiByteToWideChar(CP_ACP, 0, szAppid, lstrlenA(szAppid) + 1,	wszAppid, MAX_GUIDSTR_LEN + 1)))
		goto cleanup_and_exit;

	// use the unicode appid string to create a guid
    hr = IIDFromString(wszAppid,&AppID);

    if(FAILED(hr))
		goto cleanup_and_exit;

	// couldn't find the security descriptor so return "file not found".
    if(hr == MAKE_SCODE(SEVERITY_ERROR, FACILITY_WIN32, ERROR_FILE_NOT_FOUND))
		hr = S_OK;
    
cleanup_and_exit:

    // close open keys
    if(hkObjClsid)
		RegCloseKey(hkObjClsid);

    if(hkHKCR_CLSID)
		RegCloseKey(hkHKCR_CLSID);

    return hr;

}

