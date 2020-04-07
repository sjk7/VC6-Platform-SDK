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
#include "CAsyncTest.h"
#include "CAsyncXXX.h"
#include "Debug.h"

#include "stdio.h"

#include <process.h>

CAsyncTest::CAsyncTest(CAsyncXXX<CServer, ITest, CAsyncTest> *pA) 
		: m_lpAsyncXXX(pA), m_state(CallNone), m_hResult(S_OK)
{
	_ASSERT(m_lpAsyncXXX != NULL);
	DEBUGTRACE(_T("CAsyncTest ctor"));
}

CAsyncTest::~CAsyncTest()
{
	DEBUGTRACE(_T("CAsyncTest dtor"));
}

bool __stdcall CAsyncTest::Init()
{
	return true;
}

CAsyncTest::threadParam* g_pthdParam;



/*
 * The following method can be used as a boilerplate for Begin_XXX of the asynchronous interface.
 * There are several items to be noted here
 *
 *	1) You must track the asynchronous inteface state. In particular each call object can only serve one call at a time.
 *	
 *	2) No assuptions can be made on whether the ISynchronize interface is in the signaled or not signaled state.
 *
 *	3) Any information that is passed in which needs to persist past this call needs to be saved; for example one may pass
 *	in an IID requesting a specific interface. 
 *	
 *	4) Save the HRESULT that is returned by this method for the case where the caller ignores the return code and calls
 *	the Finish_XXX method blindly.
 *
 * Depending on how quickly you can complete the call you may choose to handle the request synchronous. If this is the case
 * after you've done whatever processing required call ISynchronize::Signal() so that COM will know to call your Finish_XXX
 * method immediately.
 */
HRESULT __stdcall CAsyncTest::Begin_Test1(BSTR bstr)
{
	CHECKPOINTER(bstr);
	DEBUGTRACE(_T("In AsyncTest::Begin_Test1. string is %S"), bstr);
	printf("In AsyncTest::Begin_Test1. string is %S\n", bstr);
	
	// Make certain that the call object is not servicing another call
	if (m_state != CallNone)
		return (m_hResult = RPC_S_CALLPENDING);


	// Save state and set the ISynchronize interface to the non-signaled state
	m_state = CallPending;
	m_lpAsyncXXX->Reset();

/*
 *	Procedure specific implementation. Here I save the BSTR parameter passed in
 *	and pass the processing off to a callback function in the case of a STA
 *	object or a different thread in the case of a MTA object
 */

 // TODO test to see if client has called ICancelMethods::Cancel()
	g_pthdParam =  new threadParam(10000, this, Test1, SysAllocString(bstr));
#if defined(_APARTMENT_)
	g_pthdParam->id = SetTimer(NULL, 0, g_pthdParam->wait, CAsyncTest::TimerProc);
#else
	_beginthread((void(__cdecl*)(void*))ThreadProc, 0, g_pthdParam);
#endif

	// Save hresult
	return (m_hResult = S_OK);
}


/*
 * The following method can be used as a boilerplate for Finish_XXX of the asynchronous interface.
 * There are several items to be noted here
 *
 *	1) You must track the asynchronous inteface state. In particular Begin_XXX must have been called and returned
 *	a success code.
 *
 *	2) If the client calls Finish_XXX prior to the completion of the work; you need to call ISynchronize::Wait() 
 *	and block until the work is done.
 */
HRESULT __stdcall CAsyncTest::Finish_Test1(BSTR bstr)
{
	CHECKPOINTER(bstr);
	DEBUGTRACE(_T("In AsyncTest::Finish_Test1"));
	
	if (m_state == CallNone)
		return (m_hResult = RPC_E_CALL_COMPLETE);	// Begin_XXX was never called
	else if (m_state == CallPending)
		m_lpAsyncXXX->Wait(0, INFINITE);			// Call not yet completed. Block till ISynchronize::Signal()
	else if (FAILED(m_hResult))
		return m_hResult;							// Begin_XXX returned an error

	_ASSERT(m_state == CallDone);
	HRESULT hr = SysReAllocString(&bstr, g_pthdParam->data);	// Fill in any [out] parameters
	_ASSERT(SUCCEEDED(hr));
	printf("In AsyncTest::Finish_Test1 string is %S\n", bstr);
	m_state = CallNone;								//	Set the state back to free so that it can be reused
	return S_OK;
}


HRESULT __stdcall CAsyncTest::Begin_Test2(BSTR bstrIn)
{
	CHECKPOINTER(bstrIn);
	DEBUGTRACE(_T("In AsyncTest::Begin_Test2. string is %S"), bstrIn);
	printf("In AsyncTest::Begin_Test2. string is %S\n", bstrIn);
	
	if (m_state != CallNone)
		return RPC_S_CALLPENDING;

	m_state = CallPending;
	m_lpAsyncXXX->Reset();

	g_pthdParam =  new threadParam(10000, this, Test2, SysAllocString(bstrIn));
#if defined(_APARTMENT_)
	g_pthdParam->id = SetTimer(NULL, 0, g_pthdParam->wait, CAsyncTest::TimerProc);
#else
	_beginthread((void(__cdecl*)(void*))ThreadProc, 0, g_pthdParam);
#endif
	return S_OK;
}
HRESULT __stdcall CAsyncTest::Finish_Test2(BSTR *lpbstrOut)
{
	CHECKPOINTER(lpbstrOut);
	DEBUGTRACE(_T("In AsyncTest::Finish_Test2"));
	
	if (m_state == CallNone)
		return RPC_E_CALL_COMPLETE;
	else if (m_state == CallPending)
		return RPC_S_CALLPENDING;

	_ASSERT(m_state == CallDone);
	*lpbstrOut = g_pthdParam->data;
	printf("In AsyncTest::Finish_Test2 string is %S\n", *lpbstrOut);
	m_state = CallNone;
	return S_OK;
}



/*
 *	This is a simple example of a "worker" thread or callback which a Begin_XXX will call to finish the
 *	method asynchronously. Much of this function will be specific to the method that the client calls
 *	however there are two items of interest here.
 *
 *		1) ISynchronize::Signal() needs to be called after the work is completed. This call is only valid
 *		to call in the same apartment as the Begin_XXX method. Which means if this is a STA object either
 *		the "worker" thread must really be a callback method as I've done below via the Windows API SetTimer()
 *		or the thread must use some form of IPC to signal to the same thread that the Begin_XXX method was called
 *
 *		2) Set the state to "completed" so that Finish_XXX will know the work is done.
 *
 */
#if defined(_APARTMENT_)
void CALLBACK CAsyncTest::TimerProc(HWND, UINT, UINT_PTR, DWORD)
{
	DEBUGTRACE(_T("In CAsyncTest::TimerProc"));
	printf("In CAsyncTest::TimerProc\n");

	KillTimer(NULL, g_pthdParam->id);
	g_pthdParam->func == Test1 ?
		g_pthdParam->pA->m_lpAsyncXXX->GetISync()->Test1(g_pthdParam->data) :
		g_pthdParam->pA->m_lpAsyncXXX->GetISync()->Test2(NULL, &g_pthdParam->data);
	g_pthdParam->pA->m_state = CAsyncTest::CallDone;
	g_pthdParam->pA->m_lpAsyncXXX->Signal();

	DEBUGTRACE(_T("Leaving CAsyncTest::TimerProc"));
	printf("Leaving CAsyncTest::TimerProc\n");
}
#else
void __cdecl CAsyncTest::ThreadProc(threadParam *pthdParam)
{
	DEBUGTRACE(_T("In CAsyncTest::ThreadProc"));
	printf("In CAsyncTest::ThreadProc\n");

	CoInitializeEx(0, COINIT_MULTITHREADED);
	Sleep(g_pthdParam->wait);
	g_pthdParam->func == Test1 ?
		g_pthdParam->pA->m_lpAsyncXXX->GetISync()->Test1(g_pthdParam->data) :
		g_pthdParam->pA->m_lpAsyncXXX->GetISync()->Test2(g_pthdParam->data, &g_pthdParam->data);
	g_pthdParam->pA->m_state = CAsyncTest::CallDone;
	g_pthdParam->pA->m_lpAsyncXXX->SignalEvent();
	CoUninitialize();
}
#endif
