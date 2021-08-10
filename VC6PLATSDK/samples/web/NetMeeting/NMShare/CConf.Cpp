//****************************************************************************
//  Module:     NMSHARE.EXE     
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
INmManager * g_pMgr  = NULL;             // The Conference Manager
CMgrNotify * g_pMgrNotify = NULL;        // Notifications for the Manager
INmConference * g_pConference = NULL;    // The Current Conference
CConfNotify * g_pConferenceNotify =NULL; // Notifications for the Conference

// Local Application Guid : {D29A8C52-774F-11d0-8B1D-00A0C91BC90E}
const GUID g_guidApp = 
{ 0xd29a8c52, 0x774f, 0x11d0, { 0x8b, 0x1d, 0x0, 0xa0, 0xc9, 0x1b, 0xc9, 0xe} };


//****************************************************************************
//
// HRESULT InitConfMgr(void)
//
//****************************************************************************
HRESULT InitConfMgr(void)
{
	HRESULT hr;
	LPCLASSFACTORY pcf;

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
					//*** Do we need to verify that it initialized properly? ***
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
	if (NULL == ppvObject)
	{
		return E_POINTER;
	}

	HRESULT hr = S_OK;

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
	ASSERT(NULL == g_pConference);
	ASSERT(NULL == g_pChannelAppShare);

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
	if (NULL == pConference)
	{
		return E_POINTER;
	}

	HRESULT hr = S_OK;

	ASSERT(NULL != pConference);
	ASSERT(NULL == g_pConference);
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

CConfNotify::CConfNotify() : RefCount(), CNotify()
{
}

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
	if (NULL == ppvObject)
	{
		return E_POINTER;
	}
	
	HRESULT hr = S_OK;

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
		return S_OK; // weird

	switch (uState)
	{
		case NM_CONFERENCE_ACTIVE:
			DisplayMsg(TEXT("Conference is active"));
			break;

		case NM_CONFERENCE_INITIALIZING:
			break; // can't do anything just yet

		case NM_CONFERENCE_WAITING:
			DisplayMsg(TEXT("Waiting in Host Mode"));
			break;

		case NM_CONFERENCE_IDLE:
			FreeAppShareChannel();
			FreeAllUsers();
			FreeConference();
			DisplayMsg(TEXT("No conference"));
			break;
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember)
{
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

HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel *pChannel)
{
	switch (uNotify)
	{
		case NM_CHANNEL_ADDED:
			HookChannel(pChannel);
			break;
		case NM_CHANNEL_REMOVED:
			UnHookChannel(pChannel);
			break;
		default:
			break;
	}
		
	return S_OK;
}




