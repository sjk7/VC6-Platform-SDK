//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CCALL.CPP
//  Content:    INmCall Routines
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"

COBLIST * g_pListCall		= NULL;
COBLIST * g_pListCallNotify = NULL;


//****************************************************************************
//
// INmCall * GetCurrentCall(void)
//
//****************************************************************************

INmCall * GetCurrentCall(void)
{
	if (NULL == g_pListCall)
		return NULL;

	return (INmCall *) g_pListCall->GetTail();
}


//****************************************************************************
//
// HRESULT HookCall(INmCall * pCall)
//
// Hook into notification callback for the call
//
//****************************************************************************

HRESULT HookCall(INmCall * pCall)
{
	HRESULT			hr		= NO_ERROR;
	CCallNotify *	pNotify	= NULL;

	ASSERT(NULL != pCall);
	if	(NULL == pCall)
	{
		return E_POINTER;
	}

	pCall->AddRef();
	if	(NULL == AddNode(pCall, &g_pListCall))
	{
		pCall -> Release();
		return E_FAIL;
	}

    // Connect to the conference object
    pNotify = new CCallNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(pCall);
		if (FAILED(hr))
		{
			ERROR_MSG(TEXT("CConfNotify Failed (%s)"), GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG(TEXT("Call Connection point established successfully"));
			if	(NULL == AddNode(pNotify, &g_pListCallNotify))
			{
				ERROR_MSG(TEXT("AddNode Failed in Hook Call"));
				pNotify -> Disconnect();
				pNotify -> Release();
				return E_FAIL;
			}
		}
	}

	return hr;
}


//****************************************************************************
//
// VOID FreeCalls(void)
//
//****************************************************************************

VOID FreeCalls(void)
{
	// Release all notify
	if (NULL != g_pListCallNotify)
	{
		while (!g_pListCallNotify->IsEmpty())
		{
			CCallNotify * pNotify = (CCallNotify *) g_pListCallNotify->RemoveHead();
			ASSERT(NULL != pNotify);
			if	(NULL == pNotify)
				break;

			OBJECT_MSG(TEXT("[%08X] call notify released"), pNotify);
			pNotify->Disconnect();
			pNotify->Release();
		}
	}
	
	if (NULL != g_pListCall)
	{
		while (!g_pListCall->IsEmpty())
		{
			INmCall * pCall = (INmCall *) g_pListCall->RemoveHead();
			ASSERT(NULL != pCall);
			if	(NULL == pCall)
				break;

			OBJECT_MSG(TEXT("[%08X] call released"), pCall);
			pCall->Release();
		}
	}
}


//****************************************************************************
//
// CLASS CCallNotify
//
//****************************************************************************

CCallNotify::CCallNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CCallNotify created"));
}

CCallNotify::~CCallNotify()
{
	OBJECT_MSG(TEXT("CCallNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CCallNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CCallNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CCallNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	HRESULT hr = S_OK;

	if	(NULL == ppvObject)
		return E_POINTER;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CCallNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmCallNotify)
	{
		*ppvObject = (INmCallNotify *)this;
		OBJECT_MSG(TEXT("CCallNotify::QueryInterface(): Returning INmCallNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CCallNotify::QueryInterface(): Called on unknown interface."));
	}

	if SUCCEEDED(hr)
	{
		AddRef();
	}

	return hr;
}



//****************************************************************************
//
// Methods from ICNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmCallNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CCallNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::StateChanged(NM_CALL_STATE uState)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::StateChanged(NM_CALL_STATE uState)
{
	INmCall *	pINmCall	= (INmCall *) CNotify::GetPunk();

	STATE_MSG(TEXT("CCallNotify::StateChanged uState=%s"), GetCallStateSz(uState));

	if	(NULL != pINmCall)
	{
		DumpCallInfo((INmCall *) CNotify::GetPunk());
		STATE_MSG(TEXT("Call direction is %d"), ((INmCall *)CNotify::GetPunk())->IsIncoming());
	}
	else
	{
		WARN_MSG(TEXT("CCallNotify::StateChanged when pINmCall == NULL"));
	}

	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::Failed(ULONG uError)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Failed(ULONG uError)
{
	LOG_MSG(RGB(255, 0, 0), TEXT("CCallNotify::Failed uError=%08X"), uError);
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::Accepted(INmConference * pConference)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Accepted(INmConference * pConference)
{
	NOTIFY_MSG(TEXT("CCallNotify::Accepted"));
	DumpConferenceInfo(pConference);
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CCallNotify::NmUI(CONFN uNotify)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::NmUI(CONFN uNotify)
{
	LOG_MSG(RGB(255, 0, 255), TEXT("CCallNotify::NmUI uNotify=%s"), GetConfnSz(uNotify));
	return S_OK;
}


//****************************************************************************
//
// VOID DoCallConference(void)
//
//****************************************************************************

VOID DoCallConference(void)
{
	HRESULT			  hr			= E_FAIL	;
	INmCall			* pCall			= NULL		;

	BSTRING			  bstrAddr(gPref.pszAddr);
	BSTRING			  bstrConference(gPref.pszConferenceName);
	BSTRING			  bstrPassword(gPref.pszPassword);
	
	if	(	(	(NULL == bstrAddr.GetLPBSTR())			&& (NULL != gPref.pszAddr)		)
		||	(	(NULL == bstrConference.GetLPBSTR())	&& (NULL != gPref.pszConferenceName)	)
		||	(	(NULL == bstrPassword.GetLPBSTR())		&& (NULL != gPref.pszPassword)	)
		)
	{
		return;
	}

	// Validate system

	if (NULL == g_pMgr)
	{
		ERROR_MSG(TEXT("No conference manager object"));
		return;
	}

	if (NULL != GetCurrentConference())
	{
		WARN_MSG(TEXT("can't join conferences!"));
	}

	hr = g_pMgr->CallConference(&pCall, gPref.nmCallType, gPref.nmAddrType, bstrAddr, bstrConference, bstrPassword);

	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("CallConference failed HResult=%s"), GetHrSz(hr));
	}
	else
	{
		ASSERT(pCall == GetCurrentCall());

		if	(NULL != pCall)
		{
			pCall->Release();
			TRACE_MSG(TEXT("CallConference succeeded"));
		}
		else
		{
			ERROR_MSG(TEXT("CallConference returned a null pointer"));
		}
	}
}


//****************************************************************************
//
// VOID DoCallCreate(void)
//
//****************************************************************************

VOID DoCallCreate(void)
{
	HRESULT			  hr			= E_FAIL	;	
	INmCall			* pCall			= NULL		;
	INmConference	* pConference	= NULL		;

	BSTRING   bstrAddr(gPref.pszAddr);
	if	((NULL == bstrAddr.GetLPBSTR()) && (NULL != gPref.pszAddr))
		return;

	// Validate system
	if (NULL == g_pMgr)
	{
		ERROR_MSG(TEXT("No conference manager object"));
		return;
	}

	pConference	= GetCurrentConference();
	if (NULL == pConference)
	{
		TRACE_MSG(TEXT("using no conference"));
	}

	hr = g_pMgr->CreateCall(&pCall, gPref.nmCallType, gPref.nmAddrType, bstrAddr, pConference);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("CreateCall failed HResult=%s"), GetHrSz(hr));
	}
	else
	{
		ASSERT(pCall == GetCurrentCall());
		
		if	(NULL != pCall)
		{
			pCall->Release();
			TRACE_MSG(TEXT("CreateCall succeeded"));
		}
		else
		{
			ERROR_MSG(TEXT("CreateCall returned a NULL pointer"));
		}
	}
}


//****************************************************************************
//
// VOID DoHandleCall(BOOL fAccept)
//
//****************************************************************************

VOID DoHandleCall(BOOL fAccept)
{
	HRESULT	  hr	= E_FAIL;
	INmCall	* pCall = GetCurrentCall();

	if (NULL == pCall)
	{
		TRACE_MSG(TEXT("No call to handle?"));
		return;
	}

	if (fAccept)
	{
		hr = pCall->Accept();
	}
	else
	{
		hr = pCall->Reject();
	}

	TRACE_MSG(TEXT("Call result = %s"), GetHrSz(hr));
}


//****************************************************************************
//
// VOID DoCancelCall(void)
//
//****************************************************************************

VOID DoCancelCall(void)
{
	HRESULT	  hr	= E_FAIL;
	INmCall	* pCall = GetCurrentCall();

	if (NULL == pCall)
	{
		TRACE_MSG(TEXT("No call to destroy?"));
		return;
	}

	hr = pCall->Cancel();
	TRACE_MSG(TEXT("Call Cancel result = %s"), GetHrSz(hr));

	// Free just the single call - watch the notify proc
	FreeCalls();
}

