//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CDATA.CPP
//  Content:    INmChannelData Routines
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

INmChannelAppShare	* g_pChannelAppShare	= NULL;
CAppShareNotify		* g_pNotifyAppShare		= NULL;

static BOOL fRobCheck = FALSE;

// From CKIM
VOID DoEnumApps(void)
{
	HRESULT				  hr		= NO_ERROR	;
	ULONG				  cFetched	= 0			;
	IEnumNmSharableApp	* pEnum		= NULL		;
	INmSharableApp		* pApp		= NULL		;

	if (NULL == g_pChannelAppShare)
		return;

	if(fRobCheck != FALSE)
	{
		MessageBox(NULL, TEXT("DoEnumApps: Error"), TEXT("Error!!!"), MB_OK);
	}

	fRobCheck = TRUE;

	hr = g_pChannelAppShare->EnumSharableApp(&pEnum); 

	if (FAILED(hr))
		return;

	while (1)
	{
		hr = pEnum->Next(1, &pApp, &cFetched);

		if	(NULL != pApp)
		{
			pApp->Release();
			pApp = NULL;
		}		
		
		if FAILED(hr)
			break;
	}

	pEnum->Release();

	fRobCheck = FALSE;
}


//****************************************************************************
//
// HRESULT HookAppShare(INmChannel * pChannel)
//
//****************************************************************************


HRESULT HookAppShare(INmChannel * pChannel)
{
	HRESULT			  hr		= NO_ERROR	;
	CAppShareNotify	* pNotify	= NULL		;

	ASSERT(NULL != pChannel);
	if	(NULL == pChannel)
	{
		ERROR_MSG(TEXT("HookAppShare: NULL == pChannel"));
		return E_POINTER;
	}

	//	Clean up any previous pointers [that were otherwise going to be overwritten]

	if	((NULL != g_pNotifyAppShare) || (NULL != g_pChannelAppShare))
	{
		ERROR_MSG(TEXT("HookAppShare: replacing existing App Sharing pointers"));
		FreeAs();
	}

	//	Get new app sharing channel

	hr = pChannel->QueryInterface(IID_INmChannelAppShare, (void **)&g_pChannelAppShare);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("HookAppShare:Unable to get Application Sharing Channel"));
		return hr;
	}

	if	(NULL == g_pChannelAppShare)
	{
		ERROR_MSG(TEXT("HookAppShare: QI Application Sharing Channel returned NULL"));
		return E_FAIL;
	}

	// keep QI ref around

    // Connect to the channel object

    pNotify = new CAppShareNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(g_pChannelAppShare);
		if (FAILED(hr))
		{
			ERROR_MSG(TEXT("CConfNotify Failed (%s)"), GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG(TEXT("AppSharing Connection point established successfully"));
			g_pNotifyAppShare = pNotify;
		}
	}

	if (FAILED(hr))
	{
		g_pChannelAppShare->Release();
		g_pChannelAppShare = NULL;
	}

	return hr;
}


//****************************************************************************
//
// VOID FreeAs(void)
//
//****************************************************************************

VOID FreeAs(void)
{
	if(NULL != g_pNotifyAppShare)
	{
		g_pNotifyAppShare->Disconnect();
		g_pNotifyAppShare->Release();
		g_pNotifyAppShare = NULL;
	}

	if (NULL != g_pChannelAppShare)
	{
		g_pChannelAppShare->Release();
		g_pChannelAppShare = NULL;
	}
}



//****************************************************************************
//
// CLASS CAppShareNotify
//
//****************************************************************************

CAppShareNotify::CAppShareNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CAppShareNotify created"));
}

CAppShareNotify::~CAppShareNotify()
{
	OBJECT_MSG(TEXT("CAppShareNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CAppShareNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CAppShareNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CAppShareNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;

	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CAppShareNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmChannelAppShareNotify)
	{
		*ppvObject = (INmChannelAppShareNotify *)this;
		OBJECT_MSG(TEXT("CAppShareNotify::QueryInterface(): Returning INmChannelAppShareNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CAppShareNotify::QueryInterface(): Called on unknown interface."));
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

HRESULT STDMETHODCALLTYPE CAppShareNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelAppShareNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CAppShareNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CAppShareNotify::NmUI(CONFN uNotify)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CAppShareNotify::NmUI(CONFN uNotify)
{
	NOTIFY_MSG(TEXT("CAppShareNotify::NmUI uNotify=%08X, pChannel=%08X"), uNotify, CNotify::GetPunk());
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CAppShareNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CAppShareNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	NOTIFY_MSG(TEXT("CAppShareNotify::MemberChanged uNotify=%d pMember=%08X, pChannel=%08X"), uNotify, pMember, CNotify::GetPunk());

	PUSER pUser = PUserFromINmMember(pMember);
	if (NULL != pUser)
	{
		UpdateUserChannel(pUser, (INmChannel *) (CNotify::GetPunk()), uNotify);
	}

	return S_OK;
}



//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CAppShareNotify::StateChanged(NM_SHAPP_STATE uState, INmSharableApp *pApp)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CAppShareNotify::StateChanged(NM_SHAPP_STATE uState, INmSharableApp *pApp)
{
	if	(NULL == pApp)
	{
		ERROR_MSG(TEXT("CAppShareNotify::StateChanged: NULL == pApp"));
		return E_POINTER;
	}

	TCHAR szState[MAX_PATH + 1];
	ZeroMemory(szState, MAX_PATH + 1);

	BSTR	bstrApp	= NULL;
	LPTSTR	pszApp	= NULL;

	HRESULT	hr		= NO_ERROR;

	// Get the new share state
	_tcsncpy(szState, uState == NM_SHAPP_SHARED ? TEXT("shared\0") : TEXT("not shared\0"), MAX_PATH);

	// Get the application information
	hr = pApp->GetName(&bstrApp);
	if(SUCCEEDED(hr))
	{
		pszApp = PszFromBstr(bstrApp);
		SysFreeString(bstrApp);
	}

	STATE_MSG(TEXT("CAppShareNotify::StateChanged received."));
	STATE_MSG(TEXT("New state for [%s] is %s"), pszApp, szState);
	
	FreePlpv(&pszApp);

	return S_OK;
}


