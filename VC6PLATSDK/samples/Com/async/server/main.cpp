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

#include <windows.h>
#include <iostream>

#include "DCOMServer.h"
#include "CFactory.h"
#include "Debug.h"

#if defined(_ASYNC_COM_)
#pragma message(">>> Compiling for Asynchronous COM")
#else
#pragma message(">>> Compiling for Synchronous COM")
#endif
  
using namespace std; 

HMODULE g_hModule;
CLSID g_clsid;
LPOLESTR g_progID;
// Event handle used to signal main thread to exit upon shutdown
HANDLE g_CloseEvent;

// index to TLS
DWORD g_dwTLS;


extern "C" 
{
	LPWSTR appSource = CServer::GetProgID();
}
CHAR_CONVERSION; // A2W, W2A helpers

extern int g_cFactoryDataEntries;
extern CFactoryData g_FactoryDataArray[];

typedef enum {EMPTY,REGISTER,UNREGISTER} SERVERFLAGS;
SERVERFLAGS UpdateRegistery(char* argv);


main(int argc, char* argv[])
{

// TODO: ADD path to server
	cout << "Server side of Asynchronous test" << endl;

#if defined(_APARTMENT_)
#pragma message(">>> Compiling for the Apartment Threaded Apartment")
	HRESULT hr = CoInitialize(NULL);
#else // Free Threaded Apartment
#pragma message(">>> Compiling for the Free Threaded Apartment")
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	g_CloseEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	_ASSERT(g_CloseEvent);
#endif // _APARTMENT_
	_ASSERT(SUCCEEDED(hr));
	g_dwTLS = TlsAlloc();

/*
 * Callbacks require the process level security to be non-authenicated
 */
	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_ANONYMOUS , NULL, EOAC_NONE, 0);
	_ASSERT(SUCCEEDED(hr));

	if (argc > 1 && UpdateRegistery(argv[1]) == REGISTER)
	{
		hr = CFactory::RegisterAll();
		if (FAILED(hr))
			MessageBox(NULL, "Could not registry app", W2A(CServer::GetProgID()), MB_OK);
		else
			MessageBox(NULL, "application has been registered", W2A(CServer::GetProgID()), MB_OK);
		goto END;
	}
	else if(argc > 1 && UpdateRegistery(argv[1]) == UNREGISTER)
	{
		hr = CFactory::UnregisterAll();
		if (FAILED(hr))
			MessageBox(NULL, "Error unregistering app", W2A(CServer::GetProgID()), MB_OK);
		else
			MessageBox(NULL, "application has been unregistered", W2A(CServer::GetProgID()), MB_OK);
		goto END;
	}
	

	cout << "Registering classfactories" << endl;
	// Register all ClassFactories
	int i;
	DWORD *dwCookies;
	dwCookies = new DWORD[g_cFactoryDataEntries];
	DEBUGTRACE(_T("Register all ClassFactories"));
	for (i = 0; i < g_cFactoryDataEntries; i++)
	{
		const CFactoryData* pData = &g_FactoryDataArray[i] ;

		LPUNKNOWN pCF =  new CFactory(pData) ;
		if (pCF == NULL)
		{
			DEBUGTRACE(_T("Error allocating memory for classfactory"));
			goto END;
		}
		hr = CoRegisterClassObject(*pData->m_pCLSID,
							  pCF,
							  pData->server == LOCAL ? CLSCTX_LOCAL_SERVER : CLSCTX_SERVER,
							  REGCLS_MULTIPLEUSE|REGCLS_SUSPENDED,
							  &dwCookies[i]);
		_ASSERT(SUCCEEDED(hr));
	}

	hr = CoResumeClassObjects();
	_ASSERT(SUCCEEDED(hr));

	DEBUGTRACE(_T("Class Factories have been registered ready to handling in comming"));

	cout << "Server ready..." << endl;

#if defined(_APARTMENT_)
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);
#else // Free Threaded Apartment
	WaitForSingleObject(g_CloseEvent, INFINITE);
#endif // _APARTMENT_

	DEBUGTRACE(_T("Cleaning up and exiting process"));
	for (i = 0; i < g_cFactoryDataEntries; i++)
		CoRevokeClassObject(dwCookies[i]);

#if !defined(_APARTMENT_)
	CloseHandle(g_CloseEvent);
#endif
	delete [] dwCookies;
	CoUninitialize();
	return 0;
END:
	CoUninitialize();
	return 0;
}

SERVERFLAGS UpdateRegistery(char* argv)
{
	char *p = strtok(argv, "-/");
	while (p)
	{
		if (stricmp(p, "RegServer")==0)
			return REGISTER;
		else if (stricmp(p, "UnregServer")==0)
			return UNREGISTER;
		p = strtok(NULL, "-/");
	}
	return EMPTY;
}
