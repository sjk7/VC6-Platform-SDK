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
#include <ocidl.h>

#include <stdio.h>
#include "proxy.h"
#include "CEvent.h"
#include "..\Server\debug.h"
#include "..\Server\CUnknown.h"

typedef ICallFactory *LPCALLFACTORY;
typedef AsyncITest   *LPASYNCITEST;
typedef ISynchronize *LPSYNCHRONIZE;



#if defined(_ASYNC_COM_)
#pragma message(">>> Compiling for Asynchronous COM")
#else
#pragma message(">>> Compiling for Synchronous COM")
#endif


main(int argc, char* argv[])
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	_ASSERT(SUCCEEDED(hr));


	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_ANONYMOUS, NULL, EOAC_NONE, 0);
	_ASSERT(SUCCEEDED(hr));
	

	LPCLASSFACTORY pCF = NULL;

/*
 * If you choose try run the server from a remote machine you can either hard code this in the
 * registry or set the below manifest constants to match your own environment. Make certain
 * to give the below user the rights to both "Launch" and "Access" the server. Since this
 * sample is showing how to achive a form of asychronous events the security is set to none
 * to simplify the callback.
 */	
// #define _COSERVERINFO_ 
#if defined(_COSERVERINFO_)	

#define DOMAIN		L"domain"
#define MACHINE		L"machine"
#define USER		L"com_stud"
#define PASSWORD	L"com_stud" 

	COSERVERINFO* pserverInfo = static_cast<COSERVERINFO*>(alloca(sizeof(COSERVERINFO)+sizeof(COAUTHINFO)));
	COAUTHIDENTITY authIdentity;
	SETDEFSERVERINFO(pserverInfo, MACHINE)
	SETAUTHIDENTITY(authIdentity, USER, PASSWORD, DOMAIN);
	pserverInfo->pAuthInfo->pAuthIdentityData = &authIdentity;
#pragma message(">>> Overriding registry using COSERVERINFO to fetch object")
	hr = CoGetClassObject(CLSID_AsyncTest, CLSCTX_SERVER, pserverInfo, IID_IClassFactory, (PVOID*)&pCF);
#else	// default
#pragma message(">>> using default registry settings to fetch object")
	hr = CoGetClassObject(CLSID_AsyncTest, CLSCTX_SERVER, NULL, IID_IClassFactory, (PVOID*)&pCF);
#endif // _COSERVERINFO_

	_ASSERT(SUCCEEDED(hr) && pCF);

	LPTEST pTest = NULL;
	hr = pCF->CreateInstance(NULL, IID_ITest, (PVOID*)&pTest);
	_ASSERT(SUCCEEDED(hr) && pTest);
	RELEASEINTERFACE(pCF);


#if defined(_EVENTSINK_)
// Set up event sink
	LPCONNECTIONPOINTCONTAINER pCPC = NULL;
	LPCONNECTIONPOINT pCP = NULL;
	hr = pTest->QueryInterface(IID_IConnectionPointContainer, (PVOID*)&pCPC);
	_ASSERT(SUCCEEDED(hr) && pCPC);

	hr = pCPC->FindConnectionPoint(IID_AppEvents, &pCP);
	_ASSERT(SUCCEEDED(hr) && pCP);
	RELEASEINTERFACE(pCPC);

	DWORD dwCookie;
	CEvent *lpevent = new CEvent;
	hr = pCP->Advise(lpevent, &dwCookie);
	_ASSERT(SUCCEEDED(hr));
#endif

	BSTR  bstr = NULL;

#if defined(_ASYNC_COM_)	
	LPCALLFACTORY pCallF = NULL;
	LPASYNCITEST  pAsyncTest = NULL;
	LPSYNCHRONIZE pSync = NULL;
	hr = pTest->QueryInterface(IID_ICallFactory, (PVOID*)&pCallF);
	_ASSERT(SUCCEEDED(hr) && (pCallF != NULL));

	hr = pCallF->CreateCall(IID_AsyncITest, NULL, IID_AsyncITest, (LPUNKNOWN*)&pAsyncTest);
	_ASSERT(SUCCEEDED(hr) && (pAsyncTest != NULL));

	bstr = SysAllocString(L"Synchronous::Hello World");
	_ASSERT(bstr);
	printf("[Blocking call]\tPassing  %S to server\n", bstr);
/*
 *	The first call will block till the server completes the call. Since in this case the server
 *	supports the asychronous interface COM will call that method in preferance to the synchronous
 *	method. This allows the server to handle other tasks such as handling such as other clients while 
 *	waiting the for method to finish. Note that this particular method takes one [in/out] parameter which
 *	will be used by both the Begin/Finish methods.
 */
	hr = pTest->Test1(bstr);
	printf("Server returned %S\n", bstr);
	_ASSERT(SUCCEEDED(hr));
	SysFreeString(bstr);

	bstr = SysAllocString(L"Asynchronous::Hello World");
	printf("[Asynchronous call]\tCalling Begin_Test1(%S) to server\n", bstr);
/*
 *	This is an asychronously call. The call to Begin_Test1 will return immediately after the parameters
 *	have been marshaled into the RPC buffer. The return code in this case in from the communication layer
 *	not the server. The client is able to free any parameters passed in and continue with other work.
 *	The client however can not make another call on the same call object until Finish_Test1 returns.
 */
	hr = pAsyncTest->Begin_Test1(bstr);
 	_ASSERT(SUCCEEDED(hr));
	SysFreeString(bstr);

/*
 *	Fetch the ISynchronize interface from the proxy so that client can periodically check whether the server
 *	has completed the call will continuing with its' other work.
 */
	hr = pAsyncTest->QueryInterface(IID_ISynchronize, reinterpret_cast<PVOID*>(&pSync));
	_ASSERT(SUCCEEDED(hr) && pSync);
	
	DWORD startTime, elapseTime;
	printf("Working...\n");
	startTime = elapseTime = GetTickCount();
	while ((hr = pSync->Wait(0, 1000)) == RPC_S_CALLPENDING || elapseTime - startTime >= 20000)
	{
		elapseTime = GetTickCount();
		printf("Working...\n");
	}
	RELEASEINTERFACE(pSync);
	bstr = SysAllocString(L"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	hr = pAsyncTest->Finish_Test1(bstr);
	printf("Elapsed time to complete call is %d sec\n", (elapseTime - startTime)/1000);
	_ASSERT(SUCCEEDED(hr));
	printf("Server returned %S\n", bstr);
	SysFreeString(bstr);

/*
 *	This next call is also invoked asynchronously by the client. What makes this different from the above call is 
 *	this method call requires two parameters. These will split up so that all [in] parameters are passed in the 
 *	Begin_Test2 call and [out] parameters to the Finish_Test2 call.
 */ 
	bstr = SysAllocString(L"Asynchronous::Hello World");
	printf("[Asynchronous call]\tCalling Begin_Test2(%S) to server\n", bstr);
	hr = pAsyncTest->Begin_Test2(bstr);
 	_ASSERT(SUCCEEDED(hr));
	SysFreeString(bstr);

	hr = pAsyncTest->QueryInterface(IID_ISynchronize, reinterpret_cast<PVOID*>(&pSync));
	_ASSERT(SUCCEEDED(hr) && pSync);
	
	printf("Working...\n");
	startTime = elapseTime = GetTickCount();
	while ((hr = pSync->Wait(0, 1000)) == RPC_S_CALLPENDING || elapseTime - startTime >= 20000)
	{
		elapseTime = GetTickCount();
		printf("Working...\n");
	}
	RELEASEINTERFACE(pSync);
	hr = pAsyncTest->Finish_Test2(&bstr);
	printf("Elapsed time to complete call is %d sec\n", (elapseTime - startTime)/1000);
	_ASSERT(SUCCEEDED(hr));
	printf("Server returned %S\n", bstr);
	SysFreeString(bstr);


/*
 *	This next call simply calls the Finish_Test2 call without polling. This would be done in the case where the client
 *	could proceed no further without getting the result back from the client. The client will block in the Finish_Test2
 *	method until the server signals that it's done.
 */
	bstr = SysAllocString(L"Asynchronous::Hello World");
	printf("[Asynchronous call]\tCalling Begin_Test2(%S) to server\n", bstr);
	hr = pAsyncTest->Begin_Test2(bstr);
 	_ASSERT(SUCCEEDED(hr));

	printf("**\n** Rather than test to see when the call object is signalled as above;\n** here I call the Finish method which will block until the method is signaled\n**\n");
	hr = pAsyncTest->Finish_Test2(&bstr);
	_ASSERT(SUCCEEDED(hr));
	printf("Server returned %S\n", bstr);
	SysFreeString(bstr);

	RELEASEINTERFACE(pAsyncTest);
	RELEASEINTERFACE(pCallF);
#else
	bstr = SysAllocString(L"Synchronous::Hello World");
	_ASSERT(bstr);
	printf("Passing  %S to server\n", bstr);
	hr = pTest->Test1(bstr);
	printf("Server returned %S\n", bstr);
	_ASSERT(SUCCEEDED(hr));
	SysFreeString(bstr);
#endif // _ASYNC_COM_

#if defined(_EVENTSINK_)
	hr = pCP->Unadvise(dwCookie);
	_ASSERT(SUCCEEDED(hr));
	RELEASEINTERFACE(pCP);
#endif

	RELEASEINTERFACE(pTest);
	CoUninitialize();
	return 0;
}
