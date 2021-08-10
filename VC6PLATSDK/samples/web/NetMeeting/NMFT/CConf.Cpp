//****************************************************************************
//  Module:     NMFT.EXE
//  File:       CCONF.CPP
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

// Global Varaiables
INmManager    * g_pMgr  = NULL;         // The Conference Manager
INmConference * g_pConference = NULL;   // The Current Conference
INmChannelFt  * g_pChannelFt = NULL;    // The File Transfer Channel
CFtNotify     * g_pNotifyFt = NULL;     // The File Transfer Notify Hook
INmMember     * g_pMember = NULL;       // The destination
INmFt         * g_pFt = NULL;           // The File Transfer Object


// Local Application Guid : {3582DED0-9CCF-11d0-8B26-00A0C91BC90E}
const GUID g_guidApp = 
{0x3582ded0, 0x9ccf, 0x11d0, { 0x8b, 0x26, 0x0, 0xa0, 0xc9, 0x1b, 0xc9, 0xe} };


//****************************************************************************
//
// HRESULT InitConfMgr(void)
//
//****************************************************************************

HRESULT InitConfMgr(void)
{
	HRESULT			hr	= NULL;
	LPCLASSFACTORY	pcf	= NULL;

	// Notify the system we want to use the conferencing services
	// by creating a conference manager object

	hr = CoGetClassObject(CLSID_NmManager, CLSCTX_INPROC, NULL, IID_IClassFactory, (void**)&pcf);
	
	if (SUCCEEDED(hr))
	{
		if	(NULL == pcf)
			return E_POINTER;
		
		// Get the conference manager object
		hr = pcf->CreateInstance(NULL, IID_INmManager, (void**)&g_pMgr);
		if (SUCCEEDED(hr))
		{
			hr	= E_POINTER;
			if	(NULL != g_pMgr)
			{
				ULONG uchCaps	= NMCH_ALL;
				ULONG uOptions	= 0;

				hr = g_pMgr->Initialize(&uOptions, &uchCaps);
			}
		}

		pcf->Release();
		pcf = NULL;
	}

	return hr;
}


//****************************************************************************
//
// HRESULT GetActiveConference(void)
//
//****************************************************************************

HRESULT GetActiveConference(void)
{
	HRESULT				  hr	= NO_ERROR	;
	IEnumNmConference	* pEnum	= NULL		;

	if (NULL == g_pMgr)
	{
		return E_FAIL;
	}

	hr = g_pMgr->EnumConference(&pEnum);
	if (SUCCEEDED(hr))
	{
		if	(NULL == pEnum)
			return E_POINTER;

		hr = pEnum->Next(1, &g_pConference, NULL);
		if SUCCEEDED(hr)
		{
			hr	= E_POINTER;
			if	(NULL != g_pConference)
			{
				NM_CONFERENCE_STATE confState;
				hr = g_pConference->GetState(&confState);
				if (SUCCEEDED(hr))
				{
					hr = (NM_CONFERENCE_ACTIVE == confState) ? S_OK : S_FALSE;
				}
			}
		}

		pEnum->Release();
		pEnum = NULL;
	}

	return hr;
}


//****************************************************************************
//
// VOID FreeFtChannel(void)
//
//****************************************************************************

VOID FreeFtChannel(void)
{
	if (NULL != g_pFt)
	{
		g_pFt->Release();
		g_pFt = NULL;
	}

	// Release all notify
	if (NULL != g_pNotifyFt)
	{
		g_pNotifyFt->Disconnect();
		g_pNotifyFt->Release();
		g_pNotifyFt = NULL;
	}
	
	if (NULL != g_pChannelFt)
	{
		g_pChannelFt->Release();
		g_pChannelFt = NULL;
	}
}


//****************************************************************************
//
// HRESULT GetFtChannel(void)
//
//****************************************************************************

HRESULT GetFtChannel(void)
{
	HRESULT			  hr		= NO_ERROR	;
	BOOL			  fFound	= FALSE		;
	ULONG			  nmch		= 0			;
	INmChannel		* pChannel	= NULL		;
	IEnumNmChannel	* pEnum		= NULL		;

	if (NULL == g_pConference)
	{
		return E_FAIL;
	}

	// TODO: Check if active and in data conference

	hr = g_pConference->EnumChannel(&pEnum);
	if (SUCCEEDED(hr))
	{
		if	(NULL == pEnum)
			return E_FAIL;

		while (SUCCEEDED(hr) && !fFound)
		{
			hr = pEnum->Next(1, &pChannel, NULL);
			
			if FAILED(hr)
				break;
			
			if	(NULL == pChannel)
			{
				hr = E_FAIL;
				break;
			}

			hr = pChannel->GetNmch(&nmch);
			
			if (SUCCEEDED(hr) && (NMCH_FT == nmch))
			{
				hr = pChannel->QueryInterface(IID_INmChannelFt, (PVOID *) &g_pChannelFt);
				fFound = ((S_OK == hr) && (NULL != g_pChannelFt));
			}

			pChannel->Release();
			pChannel = NULL;
		}

		pEnum->Release();
		pEnum = NULL;
	}

	return fFound ? S_OK : hr;
}


//****************************************************************************
//
// HRESULT HookFtChannel(void)
//
//****************************************************************************

HRESULT HookFtChannel(void)
{
	HRESULT		  hr		= NO_ERROR	;
	CFtNotify	* pNotify	= NULL		;

	ASSERT(NULL != g_pChannelFt);
	if	(NULL == g_pChannelFt)
		return E_FAIL;

    // Connect to the channel object
    pNotify = new CFtNotify();
    if (pNotify == NULL)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = pNotify->Connect(g_pChannelFt);
		if (SUCCEEDED(hr))
		{
			g_pNotifyFt = pNotify;
		}
		else
		{
			pNotify -> Release();
			pNotify =  NULL;
		}
	}

	if (FAILED(hr))
	{
		FreeFtChannel();
	}

	return hr;
}


//****************************************************************************
//
// HRESULT SendFile(void)
//
//****************************************************************************

HRESULT SendFile(void)
{
	HRESULT hr	= NO_ERROR;

	if (NULL == g_pChannelFt)
	{
		return E_FAIL;
	}

	BSTRING bstrFile(g_szFile);
	hr = g_pChannelFt->SendFile(&g_pFt, g_pMember, bstrFile, 0);
	return hr;
}


HWND ghwndProgress = NULL;

VOID UpdateProgress(CONFN uNotify)
{
	HRESULT hr	= NO_ERROR;

	if ((NULL == g_pFt) || (NULL == ghwndMain))
	{
		return;
	}

	NM_FT_STATE uState;
	hr = g_pFt->GetState(&uState);


	switch (uNotify)
		{
	case CONFN_FT_STARTED:
	{
		TCHAR szMsg[MAX_PATH + 1];

		ZeroMemory(szMsg, MAX_PATH + 1);

		// Fill out "Sending <filename>"

		_sntprintf(szMsg, MAX_PATH, TEXT("Sending %s"), (NULL != g_szFile) ? g_szFile : TEXT("<Null>"));
		SetDlgItemText(ghwndMain, IDE_SEND, szMsg);

		ULONG uBytes	= 0;
		if (FAILED(g_pFt->GetSize(&uBytes)))
			uBytes = 0;

		// Fill out "to <user> (x bytes)"

		SetDlgItemText(ghwndMain, IDE_DEST, szMsg);

		ghwndProgress = GetDlgItem(ghwndMain, IDC_PROGRESS);
		ASSERT(NULL != ghwndProgress);

		SendMessage(ghwndProgress, PBM_SETPOS, 0, 0);
		ShowWindow(ghwndMain, SW_SHOW);
		SetFocus(GetDlgItem(ghwndMain, IDCANCEL));
		break;
	}

	case CONFN_FT_PROGRESS:
	{
		ULONG uPercent		= 0 ;
		ULONG uBytesCurr	= 0	;
		ULONG uBytesTotal	= 0	;

		if (FAILED(g_pFt->GetBytesTransferred(&uBytesCurr)) ||
			FAILED(g_pFt->GetSize(&uBytesTotal)))
		{
			return;
		}

		if (0 == uBytesTotal)
			uPercent = 100;
		else
			uPercent = uBytesCurr * 100 / uBytesTotal;

		SendMessage(ghwndProgress, PBM_SETPOS, uPercent, 0);
		break;
	}
	
	case CONFN_FT_COMPLETE:
	case CONFN_FT_CANCELED:
	{
		SetDlgItemText(ghwndMain, IDCANCEL, TEXT("Close"));
		break;
	}

	default:
		return;
		}
}


//****************************************************************************
//
// CLASS CNotify
//
//****************************************************************************


//****************************************************************************
//
// Constructor
//
//****************************************************************************

CFtNotify::CFtNotify() : RefCount(), CNotify()
{
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CFtNotify::~CFtNotify()
{
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CFtNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CFtNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CFtNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if	(NULL == ppvObject)
		return E_POINTER;

	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
	}
	else if (riid == IID_INmChannelFtNotify)
	{
		*ppvObject = (INmChannelFtNotify *)this;
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
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

HRESULT STDMETHODCALLTYPE CFtNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmChannelFtNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CFtNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CFtNotify::NmUI(CONFN uNotify)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFtNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CFtNotify::FtUpdate(CONFN uNotify, INmFt * pFt)
{
	if (NULL != pFt)
	{
		UpdateProgress(uNotify);
	}

	if	((CONFN_FT_COMPLETE == uNotify) || (CONFN_FT_CANCELED == uNotify))
	{
		PostMessage(ghwndMain, WM_QUIT, 0, 0);
	}

	return S_OK;
}



//****************************************************************************
//
// VOID FreeNmObjects(void)
//
//****************************************************************************

VOID FreeNmObjects(void)
{
	FreeFtChannel();

	// Release conference
	if (NULL != g_pConference)
	{
		g_pConference->Release();
		g_pConference = NULL;
	}

	// Release conference manager
	if (NULL != g_pMgr)
	{
		g_pMgr->Release();
		g_pMgr = NULL;
	}
}


//****************************************************************************
//
// BOOL FInitNm(void)
//
//****************************************************************************

BOOL FInitNm(void)
{
	if (S_OK != InitConfMgr())
		return FALSE;

	if (S_OK != GetActiveConference())
		return FALSE;

	if (S_OK != GetFtChannel())
		return FALSE;

	if (S_OK != HookFtChannel())
		return FALSE;

	return TRUE;
}

