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
#if !defined(__CSERVER__)
#define __CSERVER__

#include <windows.h>
#include "CUnknown.h"
#include "proxy.h"
#include "CConnectionpt.h"


typedef ISynchronize *LPSYNCHRONIZE;
typedef ICallFactory *LPCALLFACTORY;

extern "C" const CLSID CLSID_AsyncTest;
extern CLSID g_clsid;
extern LPOLESTR g_progID;


class CServer	 : public CUnknown,
				   public ITest
#if defined(_ASYNC_COM_)
				   ,public ICallFactory
#endif
#if defined(_EVENTSINK_)
				   ,public CConnectionPointContainer
#endif
				   
{
public:	
	// Creation
	static HRESULT _stdcall CreateInstance(IUnknown* pUnknownOuter,
	                              CUnknown** ppNewComponent) ;

private:
	// Declare the delegating IUnknown.
	DECLARE_IUNKNOWN

	// IUnknown
	virtual HRESULT __stdcall 
		NondelegatingQueryInterface(const IID& iid, void** ppv);
	
	// Initialization
 	virtual HRESULT __stdcall Init(const CFactoryData *pData);


	// Notify derived classes that we are releasing.
	virtual void __stdcall FinalRelease();

	// Constructor
	CServer(IUnknown* pUnknownOuter);

	// Destructor
	~CServer();

private:
	// state variables

/*
 * ITest 
 *
 */
	HRESULT __stdcall Test1(BSTR bstr);
	HRESULT __stdcall Test2(BSTR bstrIn, BSTR *lpbstrOut);


#if defined(_ASYNC_COM_)
/*
 * ICallFactory
 *
 */
    HRESULT __stdcall CreateCall(REFIID riid, LPUNKNOWN pUnkCtrl, REFIID riid2, LPUNKNOWN *ppv);
#endif

public:

// accessor functions
	static LPOLESTR GetProgID() {return g_progID;}
	static CLSID GetCLSID() {return g_clsid;}
};

#endif // __CSERVER__
