//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCHAT.CPP
//  Content:    INmChannel Routines
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

COBLIST * g_pListChannel		= NULL;
COBLIST * g_pListChannelNotify	= NULL;


//****************************************************************************
//
// HRESULT HookChannel(INmChannel * pChannel)
//
// Hook into notification callback for the channel
// 
//****************************************************************************

HRESULT HookChannel(INmChannel * pChannel)
{
	HRESULT			 hr			= E_FAIL;
	CChannelNotify * pNotify	= NULL	;
	ULONG			 uch		= 0		;

	pChannel->GetNmch(&uch);
	TRACE_MSG(TEXT("[%08X] - Channel=[%s] Added"), pChannel, GetNmchSz(uch));

	ASSERT(NULL != pChannel);
	if	(NULL == pChannel)
	{
		return E_POINTER;
	}

	pChannel->AddRef();
	if	(NULL == AddNode(pChannel, &g_pListChannel))
	{
		pChannel -> Release();
		return E_FAIL;
	}

    pNotify = new CChannelNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(pChannel);
		if (FAILED(hr))
		{
			WARN_MSG(TEXT("CConfNotify Failed (%s)"), GetHrSz(hr));
			pNotify->Release();
		}
		else
		{
			OBJECT_MSG(TEXT("Conference Connection point established successfully"));
			if	(NULL == AddNode(pNotify, &g_pListChannelNotify))
			{
				ERROR_MSG(TEXT("AddNode failed in HookChannel"));
				pNotify->Disconnect();
				pNotify->Release();
				return E_FAIL;
			}
		}
	}

	if (SUCCEEDED(hr))
	{
		if (SUCCEEDED(pChannel->GetNmch(&uch)))
		{
			switch (uch)
				{
			case NMCH_SHARE:
				HookAppShare(pChannel);
				break;
			
			case NMCH_DATA:
				HookData(pChannel);
				break;

			case NMCH_FT:
				HookFileTransfer(pChannel);
				break;

			default:
				break;
				}
		}
	}

	return hr;
}


//****************************************************************************
//
// VOID UnHookChannel(INmChannel * pChannel)
//
//****************************************************************************

VOID UnHookChannel(INmChannel * pChannel)
{
	if	(NULL == pChannel)
	{
		WARN_MSG(TEXT("NULL == pChannel"));
		return;
	}

	POSITION pos		= 0;
	POSITION posSav		= 0;
	IUnknown * pUnk		= pChannel;
	ULONG uch			= 0;

	pChannel->GetNmch(&uch);
	TRACE_MSG(TEXT("[%08X] - Channel=[%s] Removed"), pChannel, GetNmchSz(uch));

	// Search for the notify object responsible for this channel
	ASSERT(NULL != g_pListChannelNotify);

	if	(NULL != g_pListChannelNotify)
	{
		for (pos = g_pListChannelNotify->GetHeadPosition(); NULL != pos; )
		{
			posSav = pos;
			CChannelNotify * pNotify = (CChannelNotify *) g_pListChannelNotify->GetNext(pos);
			ASSERT(NULL != pNotify);
			if	(NULL == pNotify)
			{
				WARN_MSG(TEXT("NULL == pNotify"));
				break;
			}

			if (S_OK == pChannel->IsSameAs((INmChannel *) pNotify->GetPunk()))
			{
				g_pListChannelNotify->RemoveAt(posSav);
				pNotify->Disconnect();
				pNotify->Release();
				break;
			}
		}
	}

	// Search for the channel in the list
	ASSERT(NULL != g_pListChannel);
	if	(NULL != g_pListChannel)
	{
		for (pos = g_pListChannel->GetHeadPosition(); NULL != pos; )
		{
			posSav = pos;
			if (S_OK == pChannel->IsSameAs((INmChannel *) g_pListChannel->GetNext(pos)))
			{
				g_pListChannel->RemoveAt(posSav);
				pChannel->Release();
				break;
			}
		}
	}
	
	if	(g_pChannelData)
	{
		g_pChannelData->Release();
		g_pChannelData = NULL;
	}

	OBJECT_MSG(TEXT("Channel connection point removed"));
}


//****************************************************************************
//
// VOID UpdateChannelState(INmChannel * pChannel)
//
//****************************************************************************

VOID UpdateChannelState(INmChannel * pChannel)
{
	if	(NULL == pChannel)
	{
		WARN_MSG(TEXT("NULL == pChannel"));
		return;
	}

	HRESULT	hr			= NO_ERROR	;
	ULONG	nmch		= 0			;
	BOOL	fActive		= FALSE		;
	ULONG	cMember		= 0			;

	hr = pChannel->GetNmch(&nmch);
	if (FAILED(hr))
	{
		return;
	}
	fActive = S_OK == pChannel->IsActive();
	
	if	FAILED(hr = pChannel->GetMemberCount(&cMember))
	{
		WARN_MSG(TEXT("GetMemberCount returned error code %08X"), hr);
	}

	TRACE_MSG(TEXT("%s channel %08X is %s with %d members"), GetNmchSz(nmch), pChannel, 
								fActive ? TEXT("Active") : TEXT("Inactive"), cMember);
	
	switch (nmch)
	{
	case NMCH_DATA:
	{
		INmChannelData * pChannelData	= NULL;
		hr = pChannel->QueryInterface(IID_INmChannelData, (void **)&pChannelData);
		if (FAILED(hr) || (NULL == pChannelData))
			return;
		if (pChannelData != g_pChannelData)
		{
			WARN_MSG(TEXT("second data channel?"));
		}
		SetMenuCheck(IDM_CHANNEL_DATA, fActive);
		pChannelData->Release();
		break;
	}
	case NMCH_AUDIO:
	case NMCH_VIDEO:
		break;
	
	case NMCH_SHARE:
	{
		if (fActive)
			break;
		FreeAs();
		break;
	}
	default:
		break;
	}
}


//****************************************************************************
//
// VOID FreeChannels(void)
//
//****************************************************************************

VOID FreeChannels(void)
{
	// Release all notify
	if (NULL != g_pListChannelNotify)
	{
		while (!g_pListChannelNotify->IsEmpty())
		{
			CChannelNotify * pNotify = (CChannelNotify *) g_pListChannelNotify->RemoveHead();
			ASSERT(NULL != pNotify);
			if	(NULL == pNotify)
			{
				WARN_MSG(TEXT("NULL == pNotify in FreeChannels"));
				break;
			}

			OBJECT_MSG(TEXT("[%08X] channel notify released"), pNotify);
			pNotify->Disconnect();
			pNotify->Release();
		}
	}
	
	if (NULL != g_pListChannel)
	{
		while (!g_pListChannel->IsEmpty())
		{
			INmChannel * pChannel = (INmChannel *) g_pListChannel->RemoveHead();
			ASSERT(NULL != pChannel);
			if	(NULL == pChannel)
			{
				WARN_MSG(TEXT("NULL == pNotify in FreeChannels"));
				break;
			}
			OBJECT_MSG(TEXT("[%08X] channel released"), pChannel);
			pChannel->Release();
		}
	}
}


//****************************************************************************
//
// CLASS CChannelNotify
//
//****************************************************************************

CChannelNotify::CChannelNotify() : RefCount(), CNotify()
{
	OBJECT_MSG(TEXT("CChannelNotify created"));
}

CChannelNotify::~CChannelNotify()
{
	OBJECT_MSG(TEXT("CChannelNotify destroyed"));
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CChannelNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CChannelNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CChannelNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;
	
	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
		OBJECT_MSG(TEXT("CChannelNotify::QueryInterface(): Returning IUnknown."));
	}
	else if (riid == IID_INmChannelNotify)
	{
		*ppvObject = (INmChannelNotify *)this;
		OBJECT_MSG(TEXT("CChannelNotify::QueryInterface(): Returning INmChannelNotify."));
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
		OBJECT_MSG(TEXT("CChannelNotify::QueryInterface(): Called on unknown interface."));
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

HRESULT STDMETHODCALLTYPE CChannelNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CChannelNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CChannelNotify::NmUI(CONFN uNotify)
{
	NOTIFY_MSG(TEXT("CChannelNotify::NmUI uNotify=%08X, pChannel=%08X"), uNotify, CNotify::GetPunk());
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CChannelNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	if	(NULL == pMember)
	{
		WARN_MSG(TEXT("NULL == pMember"));
		return E_POINTER;
	}

	NOTIFY_MSG(TEXT("CChannelNotify::MemberChanged uNotify=%d pMember=%08X, pChannel=%08X"), uNotify, pMember, CNotify::GetPunk());
	PUSER pUser = PUserFromINmMember(pMember);
	
	if	(NULL == pUser)
	{
		WARN_MSG(TEXT("NULL == pUser"));
		return E_POINTER;
	}

	pMember->GetNmchCaps(&pUser->uchCaps);
	pMember->GetID(&pUser->uId);

	UpdateUserChannel(pUser, (INmChannel *) (CNotify::GetPunk()), uNotify);

	return S_OK;
}

