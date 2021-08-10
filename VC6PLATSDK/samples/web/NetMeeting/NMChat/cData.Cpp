//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       CDATA.CPP
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

INmChannelData * g_pChannelData	= NULL;
CDataNotify * g_pNotifyData		= NULL;

//****************************************************************************
//
// VOID DisplayMsg(LPTSTR pszMsg, INmMember * pMember)
//
//****************************************************************************

VOID DisplayMsg(LPTSTR pszMsg, INmMember * pMember)
{
#ifdef NM2_CHAT_PROTOCOL
#ifndef UNICODE
	// Convert UNICODE to ANSI
	char sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(char));

	WideCharToMultiByte(CP_ACP, 0, (LPWSTR) pszMsg, -1, sz, MAX_PATH, NULL, NULL);
	pszMsg = sz;
#endif /* UNICODE */
#endif /* NM2_CHAT_PROTOCOL */

	DisplaySysMsg(pszMsg, pMember);
}


//****************************************************************************
//
// VOID DisplaySysMsg(LPTSTR pszMsg, INmMember * pMember)
//
//****************************************************************************

VOID DisplaySysMsg(LPTSTR pszMsg, INmMember * pMember)
{
	LPTSTR pszUser = NULL;

	if (NULL != pMember)
	{
		PUSER pUser = PUserFromINmMember(pMember);
		if (NULL != pUser)
		{
			pszUser = pUser->pszName;
		}
	}

	if (NULL == pszUser)
	{
		pszUser = TEXT("");
	}

	DisplayMessage(pszMsg, pszUser);
}


//****************************************************************************
//
// VOID DisplayMessage(LPTSTR pszMsg, LPTSTR pszUser)
//
//****************************************************************************

VOID DisplayMessage(LPTSTR pszMsg, LPTSTR pszUser)
{
	int iItem = 0;
	LV_ITEM  lvItem;

	ClearStruct(&lvItem);						// Zero's memory
	lvItem.iItem = 0x0FFFFFFF;
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;
	lvItem.pszText = pszUser;
	lvItem.cchTextMax = lstrlen(lvItem.pszText);
	iItem = ListView_InsertItem(ghwndMsg, &lvItem);

	{
		TCHAR sz[MAX_PATH + 1];
		ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);

		_sntprintf(sz, MAX_PATH, TEXT("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond); 
		ListView_SetItemText(ghwndMsg, iItem, ILV_TIME, sz);
	}
	
	ListView_SetItemText(ghwndMsg, iItem, ILV_TEXT, pszMsg);	
}


//****************************************************************************
//
// HRESULT HookData(INmChannelData * pChannelData)
//
//****************************************************************************

HRESULT HookData(INmChannelData * pChannelData)
{
	HRESULT hr				= NO_ERROR;
	CDataNotify * pNotify	= NULL;

	ASSERT(NULL != pChannelData);
	ASSERT(NULL == g_pChannelData);

	if(NULL == pChannelData)
	{
		return E_POINTER;
	}

	if(NULL != g_pChannelData)
	{
		return E_POINTER;
	}

	g_pChannelData = pChannelData;

    // Connect to the channel object
    pNotify = new CDataNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(pChannelData);
		if (SUCCEEDED(hr))
		{
			g_pNotifyData = pNotify;
		}
	}

	if (FAILED(hr))
	{
		FreeDataChannel();
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
	if (NULL != g_pNotifyData)
	{
		g_pNotifyData->Disconnect();
		g_pNotifyData->Release();
		g_pNotifyData = NULL;
	}
	
	if (NULL != g_pChannelData)
	{
		g_pChannelData->Release();
		g_pChannelData = NULL;
	}
}


//****************************************************************************
//
// CLASS CDataNotify
//
//****************************************************************************


//****************************************************************************
//
// Constructor
//
//****************************************************************************

CDataNotify::CDataNotify() : RefCount(), CNotify()
{
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CDataNotify::~CDataNotify()
{
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
	if(NULL == ppvObject)
	{
		return E_POINTER;
	}

	HRESULT hr = S_OK;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
	}
	else if (riid == IID_INmChannelDataNotify)
	{
		*ppvObject = (INmChannelDataNotify *)this;
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
	}

	if(SUCCEEDED(hr))
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
// Methods from INmChannelNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CDataNotify::NmUI(CONFN uNotify)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDataNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	if (NM_MEMBER_ADDED == uNotify)
	{
		AddMember(pMember);
	}
	else if (NM_MEMBER_REMOVED == uNotify)
	{
		RemoveMember(pMember);
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDataNotify::DataSent(INmMember *pMember, ULONG uSize, LPBYTE pb)
{
	LPTSTR psz = NULL;

#ifdef NM2_CHAT_PROTOCOL
	ASSERT(uSize > CB_NM2_HDR);
	if(uSize <= CB_NMUI_HDR)
	{
		return E_FAIL;
	}

	psz = (LPTSTR) (pb + *(LPDWORD) pb);  // skip past header
#else
	psz = (LPTSTR) pb;
#endif /* NM2_CHAT_PROTOCOL */

	DisplayMsg(psz, g_pMemberLocal);

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDataNotify::DataReceived(INmMember *pMember, ULONG uSize, LPBYTE pb, ULONG dwFlags)
{
	LPTSTR psz = NULL;

	// Warning : Doesn't handle broken packets
	// TODO: Check dwFlags & NM_DF_SEGMENT_END

#ifdef NM2_CHAT_PROTOCOL
	ASSERT(uSize > CB_NM2_HDR);
	if(uSize <= CB_NMUI_HDR)
	{
		return E_FAIL;
	}

	psz = (LPTSTR) (pb + *(LPDWORD) pb);  // skip past header
#else
	psz = (LPTSTR) pb;
#endif /* NM2_CHAT_PROTOCOL */

	DisplayMsg(psz, pMember);

	return S_OK;
}

/*  C H E C K  D A T A  C H A N N E L  */
/*-------------------------------------------------------------------------
    %%Function: CheckDataChannel

    Check if the data channel can be created.
-------------------------------------------------------------------------*/
VOID CheckDataChannel(void)
{
	ULONG id						= 0;
	HRESULT hr						= NO_ERROR;
	INmChannelData * pChannelData	= NULL;

	if (NULL != g_pChannelData)
	{
		return; // already created
	}

	if (NULL == g_pMemberLocal)
	{
		return; // we're not in the conference yet
	}

	if (FAILED(g_pMemberLocal->GetID(&id)))
	{
		return;
	}

	if (0 == id)
	{
		return; // no local data id
	}

#ifdef NM2_CHAT_PROTOCOL
	hr = g_pConference->CreateDataChannel(&pChannelData, g_guidNM2Chat);
#else
	hr = g_pConference->CreateDataChannel(&pChannelData, g_guidApp);
#endif /* NM2_CHAT_PROTOCOL */

	if(SUCCEEDED(hr))
	{
		hr = HookData(pChannelData);  // Real hook is g_pChannelData
	}

	DisplaySysMsg((SUCCEEDED(hr)) ? TEXT("Chat Started") : TEXT("Chat failed to start!"), NULL);
}

