//****************************************************************************
//  Module:     NMCHAT.EXE
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
INmManager    *	g_pMgr				= NULL;  // The Conference Manager
CMgrNotify    *	g_pMgrNotify		= NULL;  // Notifications for the Manager
INmConference * g_pConference		= NULL;  // The Current Conference
CConfNotify   *	g_pConferenceNotify	= NULL;	 // Notifications for the Conference
BOOL			g_fActiveConference	= FALSE; // TRUE when the conference is active

// Local Application Guid : {D29A8C50-774F-11d0-8B1D-00A0C91BC90E}
const GUID g_guidApp = 
{ 0xd29a8c51, 0x774f, 0x11d0, { 0x8b, 0x1d, 0x0, 0xa0, 0xc9, 0x1b, 0xc9, 0xe} };

// NetMeeting 2.0 chat guid: {340F3A60-7067-11D0-A041-444553540000}
const GUID g_guidNM2Chat =
{ 0x340f3a60, 0x7067, 0x11d0, { 0xa0, 0x41, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };


//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

//****************************************************************************
//
// Constructor
//
//****************************************************************************

CMgrNotify::CMgrNotify() : RefCount(), CNotify()
{
}

//****************************************************************************
//
// Destructor
//
//****************************************************************************

CMgrNotify::~CMgrNotify()
{
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CMgrNotify::AddRef(void)
{
	return RefCount::AddRef();
}


ULONG STDMETHODCALLTYPE CMgrNotify::Release(void)
{
	return RefCount::Release();
}

HRESULT STDMETHODCALLTYPE CMgrNotify::QueryInterface(REFIID riid, PVOID *ppvObject)
{
	if(NULL == ppvObject)
	{
		return E_POINTER;
	}
	
	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
	}
	else if (riid == IID_INmManagerNotify)
	{
		*ppvObject = (INmManagerNotify *)this;
	}
	else
	{
		hr = E_NOINTERFACE;
		*ppvObject = NULL;
	}

	if (SUCCEEDED(hr))
	{
		AddRef();
	}

	return hr;
}


//****************************************************************************
//
// HRESULT InitConfMgr(void)
//
//****************************************************************************

HRESULT InitConfMgr(void)
{
	HRESULT hr			= NO_ERROR;
	LPCLASSFACTORY pcf	= NULL;

    // Notify the system we want to use the conferencing services
    // by creating a conference manager object
    hr = CoGetClassObject(CLSID_NmManager,
                          CLSCTX_INPROC,
                          NULL,
                          IID_IClassFactory,
                          (void**)&pcf);
    if (SUCCEEDED(hr))
    {
        // Get the conference manager object
        hr = pcf->CreateInstance(NULL, IID_INmManager, (void**)&g_pMgr);
	    if (SUCCEEDED(hr))
        {
            // Connect to the conference manager object
            g_pMgrNotify = new CMgrNotify();
            if (NULL != g_pMgrNotify)
            {
                hr = g_pMgrNotify->Connect(g_pMgr);
			    if (SUCCEEDED(hr))
                {
                	ULONG uchCaps = NMCH_ALL;
                	ULONG uOptions = 0;
					hr = g_pMgr->Initialize(&uOptions, &uchCaps);
					if(FAILED(hr))
					{
						return hr;
					}
				}
            }
        }

        pcf->Release();
    }

	return hr;
}


//****************************************************************************
//
// VOID FreeConfMgr(void)
//
//****************************************************************************

VOID FreeConfMgr(void)
{
	// Release conference manager notify
	if (NULL != g_pMgrNotify)
	{
		g_pMgrNotify->Disconnect();
		g_pMgrNotify->Release();
		g_pMgrNotify = NULL;
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
// VOID FreeConference(void)
//
//****************************************************************************

VOID FreeConference(void)
{
	if (NULL != g_pConferenceNotify)
	{
		g_pConferenceNotify->Disconnect();
		g_pConferenceNotify->Release();
		g_pConferenceNotify = NULL;
	}

	if (NULL != g_pConference)
	{
		g_pConference->Release();
		g_pConference = NULL;
	}
}


//****************************************************************************
//
// Methods from ICNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::Connect(IUnknown *pUnk)
{
	return CNotify::Connect(pUnk, IID_INmManagerNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE CMgrNotify::Disconnect(void)
{
	return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from INmManagerNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::NmUI(CONFN confn)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMgrNotify::CallCreated(INmCall *pCall)
{
	return S_OK;
}

// As soon as a conference is available, create the data channel
HRESULT STDMETHODCALLTYPE CMgrNotify::ConferenceCreated(INmConference *pConference)
{
	if(NULL == pConference)
	{
		return E_POINTER;
	}

	HookConference(pConference);

	return S_OK;
}


//****************************************************************************
//
// HRESULT HookConference(INmConference * pConference)
//
//****************************************************************************

HRESULT HookConference(INmConference * pConference)
{
	HRESULT hr = NO_ERROR;

	ASSERT(NULL != pConference);
	ASSERT(NULL == g_pConference);
	
	if(NULL == pConference)
	{
		return E_POINTER;
	}

	if(NULL != g_pConference)
	{
		return E_POINTER;
	}

	g_pConference = pConference;

	pConference->AddRef();

    // Connect to the conference object
    ASSERT(NULL == g_pConferenceNotify)
    g_pConferenceNotify = new CConfNotify();
    if (NULL == g_pConferenceNotify)
    {
        hr = E_OUTOFMEMORY;
    }
    else
    {
		hr = g_pConferenceNotify->Connect(pConference);
		if (FAILED(hr))
		{
			g_pConferenceNotify->Release();
			g_pConferenceNotify = NULL;
		}
	}

	return hr;
}


//****************************************************************************
//
// CLASS CConfNotify
//
//****************************************************************************

//****************************************************************************
//
// Constructor
//
//****************************************************************************

CConfNotify::CConfNotify() : RefCount(), CNotify()
{
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CConfNotify::~CConfNotify()
{
}


//****************************************************************************
//
// Methods from IUnknown
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
	if(NULL == ppvObject)
	{
		return E_POINTER;
	}
	
	HRESULT hr = NO_ERROR;

	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown *)this;
	}
	else if (riid == IID_INmConferenceNotify)
	{
		*ppvObject = (INmConferenceNotify *)this;
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

HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
{
	if (NULL == g_pConference)
		return S_OK;

	switch (uState)
	{
		case NM_CONFERENCE_ACTIVE:
		{
			g_fActiveConference = TRUE;
			CheckDataChannel();
			break;
		}
		case NM_CONFERENCE_INITIALIZING:
		{
			break; // can't do anything just yet
		}
		case NM_CONFERENCE_WAITING:
		{	
			DisplaySysMsg(TEXT("Waiting in Host Mode"), NULL);
			g_fActiveConference = FALSE;
			FreeDataChannel();
			break;
		}
		case NM_CONFERENCE_IDLE:
		{
			DisplaySysMsg(TEXT("No conference"), NULL);
			g_fActiveConference = FALSE;
			FreeDataChannel();
			FreeConference();
			break;
		}
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
	switch (uNotify)
	{
		case NM_MEMBER_ADDED:
		{
			if (S_OK == pMember->IsSelf())
			{
				ASSERT(NULL == g_pMemberLocal);
				g_pMemberLocal = pMember;
				g_pMemberLocal->AddRef();
			}
			break;
		}

		case NM_MEMBER_REMOVED:
		{
			if (g_pMemberLocal == pMember)
			{
				g_pMemberLocal->Release();
				g_pMemberLocal = NULL;
			}
			break;
		}

		default:
		case NM_MEMBER_UPDATED:
		{
			// Check if the data channel should be added
			if (g_fActiveConference && (g_pMemberLocal == pMember) )
			{
				CheckDataChannel();
			}
			break;
		}
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel *pChannel)
{
	return S_OK;
}




