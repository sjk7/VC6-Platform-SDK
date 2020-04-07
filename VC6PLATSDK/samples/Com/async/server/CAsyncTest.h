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
#if !defined(__CAsyncTest__)
#define __CAsyncTest__

#include <objidl.h>
#include "proxy.h"

class  CServer;
struct ITest;

template<class T, class ISyncFace, class IAsyncFace> class  CAsyncXXX;

class CAsyncTest : public AsyncITest
{
protected:
	CAsyncXXX<CServer, ITest, CAsyncTest>	*m_lpAsyncXXX;		// Back pointer 
	CAsyncTest() {};
	enum  {CallNone, CallDone, CallPending};					// Flags used track call progress
	enum  {Test1, Test2};										// Used by either TimerProc or ThreadProc to designate which 
																// asynchronous method to call
	DWORD m_state;												// State variable that can be set to CallNone/Done/Pending
	HRESULT m_hResult;											// State variable used to hold hresult returned by Begin_XXX
public:
	struct threadParam
	{
		threadParam(DWORD w, CAsyncTest* p, DWORD method, BSTR s) : wait(w), id(0), pA(p), func(method), data(s){}

		UINT wait; 
		UINT_PTR id;
		CAsyncTest* pA; 
		DWORD func;
		BSTR data;
	};
protected:
	CAsyncTest(CAsyncXXX<CServer, ITest, CAsyncTest> *pA);
	virtual ~CAsyncTest();

#if defined(_APARTMENT_)
	static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
#else
	static void __cdecl ThreadProc(threadParam *pthdParam);
#endif

public:
	bool __stdcall Init();
private:
	// AsyncTest
	virtual HRESULT __stdcall Begin_Test1(BSTR bstr);
	virtual HRESULT __stdcall Finish_Test1(BSTR bstr);
	virtual HRESULT __stdcall Begin_Test2(BSTR bstrIn);
	virtual HRESULT __stdcall Finish_Test2(BSTR *lpbstrOut);
};
#endif // __CAsyncTest__
