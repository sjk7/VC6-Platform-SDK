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

INmChannelData	* g_pChannelData	= NULL;
CDataNotify		* g_pNotifyData		= NULL;

//****************************************************************************
//
// HRESULT HookData(INmChannel * pChannel)
//
//****************************************************************************

HRESULT HookData(INmChannel * pChannel)
{
	ASSERT(NULL != pChannel);
	if	(NULL == pChannel)
	{
		ERROR_MSG(TEXT("NULL == pChannel"));
		return E_POINTER;
	}

	HRESULT		  hr		= NO_ERROR	;
	CDataNotify * pNotify	= NULL		;

	if (NULL != g_pChannelData)
	{
		ERROR_MSG(TEXT("HookData: replacing existing g_pChannelData"));

		g_pChannelData->Release();
		g_pChannelData = NULL;
	}

	if	(NULL != g_pNotifyData)
	{
		g_pNotifyData -> Disconnect();
		g_pNotifyData -> Release();
		g_pNotifyData =  NULL;
	}

	hr = pChannel->QueryInterface(IID_INmChannelData, (void **)&g_pChannelData);
	if FAILED(hr)
	{
		ERROR_MSG(TEXT("HookData:Unable to get Data Channel"));
		return hr;
	}

	if	(NULL == g_pChannelData)
	{
		ERROR_MSG(TEXT("HookData:QI returned a NULL pointer"));
		return E_POINTER;
	}

	// keep QI ref around

    // Connect to the channel object

    pNotify = new CDataNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(g_pChannelData);
		if (FAILED(hr))
		{
			ERROR_MSG(TEXT("CConfNotify Failed (%s)"), GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG(TEXT("Data Connection point established successfully"));
			g_pNotifyData = pNotify;
		}
	}

	if (FAILED(hr))
	{
		g_pChannelData->Release();
		g_pChannelData = NULL;
	}

	return hr;
}


//****************************************************************************
//
// VOID FreeDataChannel(void)
//
//****************************************************************************

VOID FreeDataChannel(void)
{
	// Release all notify
	if	(NULL != g_pNotifyData)
	{
		OBJECT_MSG(TEXT("[%08X] data notify released"), g_pNotifyData);
		g_pNotifyData->Disconnect();
		g_pNotifyData->Release();
		g_pNotifyData = NULL;
	}
	
	if	(NULL != g_pChannelData)
	{
		OBJECT_MSG(TEXT("[%08X] data channel released"), g_pChannelData);
		g_pChannelData->Release();
		g_pChannelData = NULL;
	}
}


//****************************************************************************
//
// CLASS CDataNotify
//
//****************************************************************************

CDataNotify::CDataNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CDataNotify created"));
}

CDataNotify::~CDataNotify()
{
	OBJECT_MSG(TEXT("CDataNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CDataNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CDataNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CDataNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;

	HRESULT	hr	= NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CDataNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmChannelDataNotify)
	{
		*ppvObject = (INmChannelDataNotify *)this;
		OBJECT_MSG(TEXT("CDataNotify::QueryInterface(): Returning INmChannelDataNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CDataNotify::QueryInterface(): Called on unknown interface."));
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

HRESULT STDMETHODCALLTYPE CDataNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelDataNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CDataNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CDataNotify::NmUI(CONFN uNotify)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CDataNotify::NmUI(CONFN uNotify)
{
	NOTIFY_MSG(TEXT("CDataNotify::NmUI uNotify=%08X, pChannel=%08X"), uNotify, CNotify::GetPunk());
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CDataNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CDataNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	NOTIFY_MSG(TEXT("CDataNotify::MemberChanged uNotify=%d pMember=%08X, pChannel=%08X"), uNotify, pMember, CNotify::GetPunk());

	PUSER pUser = PUserFromINmMember(pMember);
	if (NULL != pUser)
	{
		UpdateUserChannel(pUser, (INmChannel *) (CNotify::GetPunk()), uNotify);
	}

	return S_OK;
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CDataNotify::DataSent(INmMember *pMember, ULONG uSize, LPBYTE pb)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CDataNotify::DataSent(INmMember *pMember, ULONG uSize, LPBYTE pb)
{
	LPTSTR	psz		= NULL;
	NOTIFY_MSG(TEXT("CDataNotify::DataSent uSize=%08X"), uSize);

#ifdef NMUI_CHAT_PROTOCOL
	ASSERT(uSize > CB_NMUI_HDR);
	if	(uSize <= CB_NMUI_HDR)
	{
		ERROR_MSG(TEXT("DataSent: [uSize <= CB_NMUI_HDR]"));
		return E_FAIL;
	}

	psz = (LPTSTR) (pb + *(LPDWORD) pb);  // skip past header
#else
	psz = (LPTSTR) pb;
#endif /* NMUI_CHAT_PROTOCOL */

	DisplayChatMsg(pMember, psz, MSG_SENT);
	return S_OK;
}


//****************************************************************************
//
// HRESULT STDMETHODCALLTYPE CDataNotify::DataReceived(INmMember *pMember, ULONG uSize, LPBYTE pb, ULONG dwFlags)
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CDataNotify::DataReceived(INmMember *pMember, ULONG uSize, LPBYTE pb, ULONG dwFlags)
{
	LPTSTR psz	= NULL;
	NOTIFY_MSG(TEXT("CDataNotify::DataReceived uSize=%08X"), uSize);

#ifdef NMUI_CHAT_PROTOCOL
	ASSERT(uSize > CB_NMUI_HDR);
	if	(uSize <= CB_NMUI_HDR)
	{
		ERROR_MSG(TEXT("DataReceived : [uSize <= CB_NMUI_HDR]"));
		return E_FAIL;
	}
	psz = (LPTSTR) (pb + *(LPDWORD) pb);  // skip past header
#else
	psz = (LPTSTR) pb;
#endif /* NMUI_CHAT_PROTOCOL */

	if (dwFlags & NM_DF_SEGMENT_BEGIN)
	{
		DisplayChatMsg(pMember, psz, MSG_RECEIVED, dwFlags);
	}
	else
	{
		WARN_MSG(TEXT("Partial data received"));
	}

	return S_OK;
}


//****************************************************************************
//
// VOID DisplayChatMsg(INmMember * pMember, PTCHAR pszMsg, int msgType, DWORD dwFlags)
//
//****************************************************************************

VOID DisplayChatMsg(INmMember * pMember, PTCHAR pszMsg, int msgType, DWORD dwFlags)
{
	COLORREF cv	= RGB(0, 0, 0);

	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

	PUSER pUser = PUserFromINmMember(pMember);

	switch (msgType)
		{
	case MSG_SENT:
	{
		cv = RGB(127, 0, 127);
		if (NULL == pUser)
		{
			lstrcpyn(sz, TEXT("Msg to Everyone\0"), MAX_PATH+1);
			sz[MAX_PATH] = 0;
		}
		else
		{
			_sntprintf(sz, MAX_PATH, TEXT("Whisper to %s"), pUser -> pszName);
		}
		break;
	}
	case MSG_RECEIVED:
	{
		cv = RGB(255, 0, 255);
		if (NULL == pUser)
		{
			lstrcpyn(sz, TEXT("Message from ????\0"), MAX_PATH+1);
			sz[MAX_PATH] = 0;
		}
		else if (dwFlags & NM_DF_PRIVATE)
		{
			_sntprintf(sz, MAX_PATH, TEXT("Whisper from %s\0"), pUser -> pszName);
		}
		else if (dwFlags & NM_DF_BROADCAST)
		{
			_sntprintf(sz, MAX_PATH, TEXT("Message from %s\0"), pUser -> pszName);
		}
		break;
	}
	default:
		cv = RGB(0, 0, 0);
		break;
		}

	Log(RGB(0, 0, 0), sz);

#ifdef NMUI_CHAT_PROTOCOL
#ifndef UNICODE
	// Convert UNICODE to ANSI
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR) pszMsg, -1, sz, MAX_PATH, NULL, NULL);
	pszMsg = sz;
#endif /* UNICODE */
#endif /* NMUI_CHAT_PROTOCOL */

	Log(cv, pszMsg);
}


//****************************************************************************
//
// VOID DoSendChatMsg(LPTSTR psz, INmMember * pMember)
//
//****************************************************************************

VOID DoSendChatMsg(LPTSTR psz, INmMember * pMember)
{
	HRESULT	hr	= NO_ERROR;
	UINT	cb	= lstrlen(psz) + 1; // include final null

	if ((1 == cb) || (NULL == g_pChannelData) || (MAX_PATH + 1 < cb) )
	{
		return;
	}

#ifdef NMUI_CHAT_PROTOCOL

	BYTE buffer[CB_NMUI_HDR + (MAX_PATH + 1) * sizeof(WCHAR)];
	ZeroMemory(buffer, CB_NMUI_HDR + (MAX_PATH + 1) * sizeof(WCHAR));

#ifdef UNICODE
	lstrcpyn((LPTSTR) &buffer[CB_NMUI_HDR], psz, MAX_PATH+1);
	buffer[CB_NMUI_HDR + MAX_PATH] = 0;
#else
	cb = MultiByteToWideChar(CP_ACP, 0, psz, cb, (LPWSTR) &buffer[CB_NMUI_HDR], MAX_PATH);
	cb *= 2; // adjust for UNICODE
#endif /* !UNICODE */

	// Add special prefix
	cb += CB_NMUI_HDR;
	ZeroMemory(buffer, CB_NMUI_HDR);
	* ((LPDWORD) buffer) = CB_NMUI_HDR;

	psz = (LPTSTR) buffer;
	
#else
	cb++; // include final null
#endif /* NMUI_CHAT_PROTOCOL */

	if ((NULL != pMember) && (S_OK == pMember->IsSelf()))
		pMember = NULL; // local machine = everyone

	hr = g_pChannelData->SendData(pMember, cb, (LPBYTE) psz, 0);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("DoSendChatMsg: SendData failed: %s"), GetHrSz(hr));
	}
}


//****************************************************************************
//
// VOID DoCreateDataChannel(INmConference * pConference)
//
//****************************************************************************

VOID DoCreateDataChannel(INmConference * pConference)
{
	INmChannelData	* pChannelData	= NULL;
	HRESULT			  hr			= NO_ERROR;
	
	if (NULL == pConference)
	{
		WARN_MSG(TEXT("No conference."));
		return;
	}
	
	if (NULL != g_pChannelData)
	{
		WARN_MSG(TEXT("Data channel already exists"));
	}

	hr = pConference->CreateDataChannel(&pChannelData, g_guidNMUIChat);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("CreateDataChannel: Failed hr=%s"), GetHrSz(hr));
		return;
	}

	if (NULL == g_pChannelData)
	{
		ERROR_MSG(TEXT("DoCreateDataChannel: Failed to hook"));
	}
	else
	{
		// The AddRef was done in the hook code.
		pChannelData->Release();
	}

	TRACE_MSG(TEXT("Created Data Channel"));
}


//****************************************************************************
//
// VOID DoActivateDataChannel(BOOL fActive)
//
//****************************************************************************

VOID DoActivateDataChannel(BOOL fActive)
{
	HRESULT hr	= NO_ERROR;

	if (NULL == g_pChannelData)
		return;

	hr = g_pChannelData->IsActive();
	TRACE_MSG(TEXT("Data channel is %s"), (S_OK == hr) ? "Active" : "Inactive");
	
	hr = g_pChannelData->SetActive(fActive);
	TRACE_MSG(TEXT("Data channel SetActive Result=%s"), GetHrSz(hr));
}

