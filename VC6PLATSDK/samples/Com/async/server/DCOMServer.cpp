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
#include "DCOMServer.h"
#include "CFactory.h"
#include "CAsyncTest.h"
#include "CAsyncXXX.h"
#include "Registry.h"
#include "Debug.h"
 

// Event handle used to signal main thread to exit upon shutdown
extern HANDLE g_CloseEvent;


//
// Constructor
//
#pragma warning(disable : 4355)
CServer::CServer(IUnknown* pUnknownOuter): 
	CUnknown(pUnknownOuter, "CServer")
{
	DEBUGTRACE(_T("In CServer ctor"));
}

//
// Destructor
//
CServer::~CServer()
{
	DEBUGTRACE(_T("In CServer dtor"));
}

void __stdcall 
CServer::FinalRelease()
{
#if !defined(_DLL_SERVER_)		
	if (CoReleaseServerProcess() == 0) // Last reference to server time to cleanup and exit
#if defined(_APARTMENT_)
		PostQuitMessage(0);
#else	// Free Threaded
		SetEvent(g_CloseEvent);
#endif // _APARTMENT_
#endif // _DLL_SERVER_
	return;
}


HRESULT __stdcall 
	CServer::NondelegatingQueryInterface(const IID& iid, void** ppv)
{ 
	CHECKPOINTER(ppv);	
#if defined(_ASYNC_COM_)
	if (iid == IID_ICallFactory)
	{
		return FinishQI(static_cast<LPCALLFACTORY>(this), iid, ppv);
	}
#endif //_ASYNC_COM_
	if (iid == IID_ITest)
	{
		return FinishQI(static_cast<LPTEST>(this), iid, ppv);
	}
#if defined(_EVENTSINK_)
	else if (iid == IID_IConnectionPointContainer)
	{
		return FinishQI(static_cast<LPCONNECTIONPOINTCONTAINER>(this), iid, ppv) ;
	}
#endif
	return CUnknown::NondelegatingQueryInterface(iid, ppv);
}



///////////////////////////////////////////////////////////
//
// Creation function used by CFactory
//
HRESULT CServer::CreateInstance(IUnknown* pUnknownOuter,
                           CUnknown** ppNewComponent) 
{
	*ppNewComponent = new CServer(pUnknownOuter) ;
	DEBUGTRACE(_T("In CServer::CreateInstance\n")) ;
	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// Initialize the component and create the contained component.
//

#if defined(_EVENTSINK_)
EventID g_EventIDs = 
{ 1, {{&IID_AppEvents}}};
#endif

HRESULT __stdcall
CServer::Init(const CFactoryData *pData)
{
#if defined(_EVENTSINK_)
	CConnectionPointContainer::Init(g_EventIDs);
#endif

#if !defined(_DLL_SERVER_)		
	CoAddRefServerProcess();
#endif // _DLL_SERVER_
	return S_OK ;
}

 

#if defined(_ASYNC_COM_)
/*
 * ICallFactory
 *
 */
HRESULT __stdcall 
CServer::CreateCall(REFIID riid1, LPUNKNOWN pUnkCtrl, REFIID riid2, LPUNKNOWN *ppv)
{
	DEBUGTRACE(_T("In ICallFactory::CreateCall"));
	CHECKPOINTER(ppv);
	if (riid1 != IID_AsyncITest)
		return E_NOINTERFACE;

#if 0
//testtest
	{
	LPSYNCHRONIZE   lpSync = NULL;
	HRESULT hr = pUnkCtrl->QueryInterface(IID_ISynchronize, reinterpret_cast<PVOID*>(&lpSync));
	_ASSERT(SUCCEEDED(hr) && lpSync);
	hr = lpSync->Reset();	// this succeeds
	RELEASEINTERFACE(lpSync);
	}
//testtest
#endif
#pragma warning(disable : 4355)
	*ppv = CAsyncXXX<CServer, ITest, CAsyncTest>::Create(pUnkCtrl, riid1, riid2, this, this);

	return *ppv != NULL ? S_OK : E_OUTOFMEMORY;
}
#endif //_ASYNC_COM_


/*
 * ITest
 *
 */

#include <stdio.h>
HRESULT __stdcall 
CServer::Test1(BSTR bstr)
{
	DEBUGTRACE(_T("In CServer::Test1:  string is = %S"), bstr);
	printf("In CServer::Test1:  string is = %S\n", bstr);
	printf("Send asynchronous signal to client\n");
#if defined(_EVENTSINK_)
	HRESULT hr = CConnectionPointContainer::GetConnectionPoint(IID_AppEvents)->SignalEvent();
	_ASSERT(SUCCEEDED(hr));
#endif
	printf("Leaving CServer::Test1\n");
	return SysReAllocString(&bstr, L"Good bye") != 0 ? S_OK : E_OUTOFMEMORY ;
}


HRESULT __stdcall 
CServer::Test2(BSTR bstrIn, BSTR *lpbstrOut)
{
	DEBUGTRACE(_T("In CServer::Test2:  string is = %S"), bstrIn);
	CHECKPOINTER(lpbstrOut);
	if (bstrIn)
		printf("In CServer::Test2:  string is = %S\n", bstrIn);
	*lpbstrOut = SysAllocString(L"Synchronous: Good bye");
	return S_OK;
}
