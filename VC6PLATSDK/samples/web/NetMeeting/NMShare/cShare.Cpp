//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       CSHARE.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1997-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"

INmChannelAppShare * g_pChannelAppShare = NULL;
CAppShareNotify * g_pNotifyAppShare = NULL;


//****************************************************************************
//
// HRESULT HookChannel(INmChannel * pChannel)
//
//****************************************************************************

HRESULT HookChannel(INmChannel * pChannel)
{
	HRESULT hr = S_OK;
	CAppShareNotify * pNotify = NULL;
	INmChannelAppShare * pChannelAs = NULL;

	ASSERT(NULL != pChannel);

	if (NULL == pChannel)
	{
		hr = ERROR_INVALID_PARAMETER;
		return hr;
	}

	hr = pChannel->QueryInterface(IID_INmChannelAppShare, (void **)&pChannelAs);
	if (FAILED(hr))
	{
		// Not an app sharing channel
		return hr;
	}
	if (NULL != g_pChannelAppShare)
	{
		g_pChannelAppShare->Release();
		g_pChannelAppShare = NULL;
	}
	g_pChannelAppShare = pChannelAs;
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
			pNotify->Release();
		}
		else
		{
			g_pNotifyAppShare = pNotify;
		}
	}

	if (FAILED(hr))
	{
		g_pChannelAppShare->Release();
		g_pChannelAppShare = NULL;
	}
	else
	{
		DoEnumApps();
	}

	return hr;
}


//****************************************************************************
//
// HRESULT HookChannel(INmChannel * pChannel)
//
//****************************************************************************

VOID UnHookChannel(INmChannel * pChannel)
{
	if (NULL == pChannel)
		return;

	if (NULL == g_pChannelAppShare)
		return;

	if (S_OK != g_pChannelAppShare->IsSameAs(pChannel))
		return;

	FreeAppShareChannel();
}


//****************************************************************************
//
// VOID FreeAppShareChannel(void)
//
//****************************************************************************

VOID FreeAppShareChannel(void)
{
	// Release all notify
	if (NULL != g_pNotifyAppShare)
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
}

CAppShareNotify::~CAppShareNotify()
{
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
	if (NULL == ppvObject)
	{
		return E_POINTER;
	}

	HRESULT hr = S_OK;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
	}
	else if (riid == IID_INmChannelAppShareNotify)
	{
		*ppvObject = (INmChannelAppShareNotify *)this;
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
	}

	if (S_OK == hr)
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
// Methods from INmChannelNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CAppShareNotify::NmUI(CONFN uNotify)
{
	LPTSTR psz;

	switch (uNotify)
	{
		case CONFN_CLICK_CONTROL:
			psz = TEXT("Click: requesting control");
			break;
		case CONFN_CLICK_OBSCURE:
			psz = TEXT("Click: obscured area");
			break;
		case CONFN_CLICK_REMOTE_NOT_COLLABORATING:
			psz = TEXT("Click: Remote not collaborating");
			break;
		case CONFN_CLICK_LOCAL_NOT_COLLABORATING:
			psz = TEXT("Click: Local not collaborating");
			break;
		default:
			psz = TEXT("Unknown confn");
			break;
	}

	DisplayMsg(psz);

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CAppShareNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	PUSER pUser = PUserFromINmMember(pMember);
	if (NULL != pUser)
	{
//		UpdateUserChannel(pUser, (INmChannel *) (CNotify::GetPunk()), uNotify);
#ifdef DEBUG
		TCHAR szMsg[MAX_PATH + 1];
		ZeroMemory(szMsg,(MAX_PATH + 1) * sizeof(TCHAR));
		_sntprintf(szMsg,MAX_PATH,TEXT("%s changed sharing status"), pUser->pszName);
		
		//TCHAR szMsg[MAX_PATH];
		//wsprintf(szMsg, TEXT("%s changed sharing status"), pUser->pszName);
		DisplayMsg(szMsg);
#endif

		if (S_OK == pMember->IsSelf())
		{
			NM_SHARE_STATE uState;
			if (SUCCEEDED(pMember->GetShareState(&uState)))
			{
				SetMenuCheck(IDM_WORK_ALONE,  (NM_SHARE_WORKING_ALONE == uState));
				SetMenuCheck(IDM_COLLABORATE, (NM_SHARE_COLLABORATING == uState)
					|| (NM_SHARE_IN_CONTROL == uState));
				SetMenuCheck(IDM_IN_CONTROL,  (NM_SHARE_IN_CONTROL == uState));

#ifdef DEBUG
				switch (uState)
				{
					case NM_SHARE_WORKING_ALONE: DisplayMsg(TEXT("Working Alone"));       break;
					case NM_SHARE_COLLABORATING: DisplayMsg(TEXT("Collaborating"));       break;
					case NM_SHARE_IN_CONTROL:    DisplayMsg(TEXT("In Control"));          break;
					default:                     DisplayMsg(TEXT("Uknown Share State?")); break;
				}
#endif
			}
		}
		else
		{
#ifdef DEBUG
			NM_SHARE_STATE uState;
			if (SUCCEEDED(pMember->GetShareState(&uState)))
			{
				LPTSTR pszState = TEXT("?");
				switch (uState)
				{
					case NM_SHARE_WORKING_ALONE: pszState = TEXT("Working Alone");       break;
					case NM_SHARE_COLLABORATING: pszState = TEXT("Collaborating");       break;
					case NM_SHARE_IN_CONTROL:    pszState = TEXT("In Control");          break;
					default:                     pszState = TEXT("Uknown Share State?"); break;
				}

				BSTR  bstrName;
				if (SUCCEEDED(pMember->GetName(&bstrName)))
				{
					TCHAR sz[MAX_PATH + 1];
					ZeroMemory(sz,(MAX_PATH + 1) * sizeof(TCHAR));
					_sntprintf(sz,MAX_PATH,TEXT("%s is %s"), (LPTSTR) BTSTR(bstrName), pszState);


					//TCHAR sz[MAX_PATH];
					//wsprintf(sz, "%s is %s", (LPTSTR) BTSTR(bstrName), pszState);
					DisplayMsg(sz);
					SysFreeString(bstrName);
				}
			}
#endif
		}
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CAppShareNotify::StateChanged(NM_SHAPP_STATE uState, INmSharableApp *pApp)
{
	TCHAR szMsg[MAX_PATH + 1];
	ZeroMemory(szMsg,(MAX_PATH + 1) * sizeof(TCHAR));
	_sntprintf(szMsg,MAX_PATH,TEXT("%08X %s"), pApp,
		(NM_SHAPP_SHARED == uState) ? TEXT("Shared") : TEXT("not shared"));

	DisplayMsg(szMsg);
	UpdateApp(pApp);
	return S_OK;
}


VOID DoEnumApps(void)
{
	HRESULT hr = S_OK;
	ULONG cFetched = 0;
	IEnumNmSharableApp * pEnum = NULL;
	INmSharableApp * pApp = NULL;

	if (NULL == g_pChannelAppShare)
		return;

	hr = g_pChannelAppShare->EnumSharableApp(&pEnum);
	if (FAILED(hr))
	{
    	return;
	}

	for ( ; ; )
	{
		hr = pEnum->Next(1, &pApp, &cFetched);
		if (S_OK != hr)
			break;

		UpdateApp(pApp);
		pApp->Release();
	}

	pEnum->Release();
}


VOID DoWorkAlone(void)
{
	if (NULL == g_pChannelAppShare)
		return;

	HRESULT hr = g_pChannelAppShare->SetState(NM_SHARE_WORKING_ALONE);
}

VOID DoCollaborate(void)
{
	if (NULL == g_pChannelAppShare)
		return;

	HRESULT hr = g_pChannelAppShare->SetState(NM_SHARE_COLLABORATING);
}

VOID DoTakeControl(void)
{
	if (NULL == g_pChannelAppShare)
		return;

	HRESULT hr = g_pChannelAppShare->SetState(NM_SHARE_IN_CONTROL);
}

