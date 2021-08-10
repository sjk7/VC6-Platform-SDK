//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCONF.CPP 
//  Content:    INmConference Routines
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

COBLIST * g_pListConference			= NULL;
COBLIST * g_pListConferenceNotify	= NULL;


//****************************************************************************
//
// INmConference * GetCurrentConference(void)
//
//****************************************************************************

INmConference * GetCurrentConference(void)
{
	if (NULL == g_pListConference)
		return NULL;

	return (INmConference *) g_pListConference->GetTail();
}


//****************************************************************************
//
// HRESULT HookConference(INmConference * pConference)
//
//****************************************************************************

HRESULT HookConference(INmConference * pConference)
{
	HRESULT		  hr		= NO_ERROR	;
	CConfNotify * pNotify	= NULL		;

	ASSERT(NULL != pConference);
	if	(NULL == pConference)
		return E_POINTER;

	pConference->AddRef();
	if	(NULL == AddNode(pConference, &g_pListConference))
	{
		ERROR_MSG(TEXT("AddNode failed HookConference, pNotify"));
		pConference -> Release();
		return E_FAIL;
	}

    // Connect to the conference object
    pNotify = new CConfNotify();
    if (NULL == pNotify)
    {
        hr = E_OUTOFMEMORY;
        ERROR_MSG(TEXT("Unable to allocate CConfNotify"));
    }
    else
    {
		hr = pNotify->Connect(pConference);
		if (FAILED(hr))
		{
			TRACE_MSG(TEXT("CConfNotify Failed (%s)"), GetHrSz(hr));
			pNotify->Release();
			pNotify = NULL;
		}
		else
		{
			if	(NULL != AddNode(pNotify, &g_pListConferenceNotify))
			{
				TRACE_MSG(TEXT("Conference Connection point established successfully"));
			}
			else
			{
				ERROR_MSG(TEXT("AddNode failed HookConference, pNotify"));
				pNotify -> Disconnect();
				pNotify -> Release();
				pNotify =  NULL;

				hr = E_FAIL;
			}
		}
	}

	if	SUCCEEDED(hr)
	{
		UpdateStatusIcon(ICO_PHONE);
	}

	return hr;
}


//****************************************************************************
//
// VOID FreeConferences(void)
//
//****************************************************************************

VOID FreeConferences(void)
{
	// Release all notify
	if (NULL != g_pListConferenceNotify)
	{
		while (!g_pListConferenceNotify->IsEmpty())
		{
			CConfNotify * pNotify = (CConfNotify *) g_pListConferenceNotify->RemoveHead();
			ASSERT(NULL != pNotify);
			if	(NULL == pNotify)
			{
				WARN_MSG(TEXT("FreeConferences, NULL == pNotify"));
				break;
			}

			OBJECT_MSG(TEXT("[%08X] conference notify released"), pNotify);
			pNotify->Disconnect();
			pNotify->Release();
		}
	}
	
	if (NULL != g_pListConference)
	{
		while (!g_pListConference->IsEmpty())
		{
			INmConference * pConference = (INmConference *) g_pListConference->RemoveHead();
			ASSERT(NULL != pConference);
			if	(NULL == pConference)
			{
				WARN_MSG(TEXT("FreeConferences, NULL == pNotify"));
				break;
			}

			OBJECT_MSG(TEXT("[%08X] conference released"), pConference);
			pConference->Release();
		}
	}

	UpdateStatusIcon(NULL);
}


//****************************************************************************
//
// VOID DoConferenceCreate(void)
//
// Create a local conference object
//
//****************************************************************************

VOID DoConferenceCreate(void)
{
	HRESULT			  hr			= NO_ERROR	;
	INmConference	* pConference	= NULL		;

	// Validate system
	if (NULL == g_pMgr)
	{
		ERROR_MSG(TEXT("No conference manager object"));
		return;
	}

	if (NULL != GetCurrentConference())
	{
		WARN_MSG(TEXT("Attempting to create second conference"));
	}

	// Create Local Conference
	BSTRING bstrName(gPref.pszConferenceName);
	BSTRING bstrPassword(gPref.pszPassword);

	if	(	((NULL == (BSTR) bstrName) && (NULL != gPref.pszConferenceName))
		||	((NULL == (BSTR) bstrPassword) && (NULL != gPref.pszPassword))
		)
		return;


	hr = g_pMgr->CreateConference(&pConference, bstrName, bstrPassword, gPref.dwNmch);
	if (SUCCEEDED(hr) && (NULL != pConference))
	{
		hr = pConference->Host();
		if (FAILED(hr))
		{
			WARN_MSG(TEXT("Failed to host conference"));
		}
	
		// Release here, because we always AddRef in INmManager.ConferenceCreated
		
		ASSERT(pConference == GetCurrentConference());
		pConference->Release();
	
		TRACE_MSG(TEXT("CreateConference succeeded"));
	}
	else
	{
		ERROR_MSG(TEXT("CreateConference failed HResult=%s"), GetHrSz(hr));
	}
}


//****************************************************************************
//
// VOID DoConferenceLeave(void)
//
//****************************************************************************

VOID DoConferenceLeave(void)
{
	HRESULT			  hr			= NO_ERROR	;
	INmConference	* pConference	= NULL		;

	pConference = GetCurrentConference();
	if (NULL == pConference)
	{
		ERROR_MSG(TEXT("No conference object"));
		return;
	}

	hr = pConference->Leave();
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("Conference Leave hresult=%s"), GetHrSz(hr));
	}
	else
	{
		TRACE_MSG(TEXT("Conference Leave successful..."));
	}
}


//****************************************************************************
//
// CLASS CConfNotify
//
//****************************************************************************

CConfNotify::CConfNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CConfNotify created"));
}

CConfNotify::~CConfNotify()
{
	OBJECT_MSG(TEXT("CConfNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CConfNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CConfNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CConfNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;

	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CConfNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmConferenceNotify)
	{
		*ppvObject = (INmConferenceNotify *)this;
		OBJECT_MSG(TEXT("CConfNotify::QueryInterface(): Returning INmConferenceNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CConfNotify::QueryInterface(): Called on unknown interface."));
	}

	if	SUCCEEDED(hr)
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

HRESULT STDMETHODCALLTYPE CConfNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmConferenceNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CConfNotify::Disconnect(void)
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
// HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
{
	LOG_MSG(RGB(255, 0, 255), TEXT("INmConference.NmUI CONFN=%s"), GetConfnSz(uNotify));
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
{
	STATE_MSG(TEXT("INmConference.StateChanged uState=%s"), GetConferenceStateSz(uState));

	switch (uState)
		{
	case NM_CONFERENCE_ACTIVE:
	{
		if (gPref.fAutoChat)
		{
			DoCreateDataChannel(GetCurrentConference());
		}
		break;
	}
	case NM_CONFERENCE_IDLE:
	{
		FreeDataChannel();
		FreeAllUsers();
		FreeChannels();
		break;
	}
	default:
		break;
		} /* switch (uState) */

	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	NOTIFY_MSG(TEXT("INmConference.MemberChanged uNotify=%d"), uNotify);
	DumpMemberInfo(pMember);

	switch (uNotify)
		{
	case NM_MEMBER_ADDED:
		AddMember(pMember);
		break;
	case NM_MEMBER_REMOVED:
		RemoveMember(pMember);
		break;
	default:
		break;
		}

	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel *pChannel)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel *pChannel)
{
	NOTIFY_MSG(TEXT("INmConference.ChannelChanged uNotify=%d"), uNotify);
	DumpChannelInfo(pChannel);
	static BOOL s_fShared = FALSE;
	static BOOL s_fCollaborated = FALSE;


	switch (uNotify)
		{
	case NM_CHANNEL_ADDED:
		HookChannel(pChannel);
		break;
	case NM_CHANNEL_REMOVED:
		UnHookChannel(pChannel);
		break;
	case NM_CHANNEL_UPDATED:
		UpdateChannelState(pChannel);
		break;
	default:
		break;
		}
		
	return S_OK;
}


