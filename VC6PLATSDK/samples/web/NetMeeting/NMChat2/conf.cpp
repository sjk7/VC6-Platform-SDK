//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       CONF.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1999-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"
#include "imsconf2.c"

//****************************************************************************
//
// Global Varaiables
//
//****************************************************************************

//
// The Conference Manager
//
INmManager     *g_pMgr  = NULL;

//
// Notifications for the Manager
//
CMgrNotify     *g_pMgrNotify = NULL;

//
// The Current Conference
//
INmConference  *g_pConference = NULL;

//
// Notifications for the Conference
//
CConfNotify    *g_pConferenceNotify = NULL;

//
// TRUE when the conference is active
//
BOOL            g_fActiveConference = FALSE;


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

CMgrNotify::CMgrNotify()
:
    CRefCount(),
    CNotify()
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

ULONG STDMETHODCALLTYPE
CMgrNotify::AddRef(void)
{
    return CRefCount::AddRef();
}


ULONG STDMETHODCALLTYPE
CMgrNotify::Release(void)
{
    return CRefCount::Release();
}

HRESULT STDMETHODCALLTYPE
CMgrNotify::QueryInterface(REFIID riid, void * *ppvObject)
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

    if (S_OK == hr)
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

    //
    // Notify the system we want to use the conferencing services
    // by creating a conference manager object
    //
    hr = CoGetClassObject(CLSID_NmManager,
                          CLSCTX_INPROC,
                          NULL,
                          IID_IClassFactory,
                          (void**)&pcf);
    if (SUCCEEDED(hr))
    {
        //
        // Get the conference manager object
        //
        hr = pcf->CreateInstance(NULL, IID_INmManager, (void**)&g_pMgr);
        if (SUCCEEDED(hr))
        {
            //
            // Connect to the conference manager object
            //
            g_pMgrNotify = new CMgrNotify();
            if (NULL != g_pMgrNotify)
            {
                hr = g_pMgrNotify->Connect(g_pMgr);
                if (SUCCEEDED(hr))
                {
                    ULONG uchCaps = NMCH_ALL;
                    ULONG uOptions = 0;
                    hr = g_pMgr->Initialize(&uOptions, &uchCaps);
					if (SUCCEEDED (hr))
					{
						INmSysInfo* spSysInfo=NULL;

						hr=g_pMgr->GetSysInfo(&spSysInfo);
	
						if (SUCCEEDED(hr))
						{
							BSTR bstrVer = NULL;
							hr = spSysInfo->GetProperty(NM_SYSPROP_BUILD_VER, &bstrVer);
							::SysFreeString(bstrVer);
							if (hr != S_OK)
							{
								MessageBox(NULL,"This sample needs Windows Netmeeting3.0","Wrong Version",MB_OK);
								return E_FAIL;
							}
						}
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
// void FreeConfMgr(void)
//
//****************************************************************************

void FreeConfMgr(void)
{
    //
    // Release conference manager notify
    //
    if (NULL != g_pMgrNotify)
    {
        g_pMgrNotify->Disconnect();
        g_pMgrNotify->Release();
        g_pMgrNotify = NULL;
    }

    //
    // Release conference manager
    //
    if (NULL != g_pMgr)
    {
        g_pMgr->Release();
        g_pMgr = NULL;
    }
}


//****************************************************************************
//
// void FreeConference(void)
//
//****************************************************************************

void FreeConference(void)
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

HRESULT STDMETHODCALLTYPE
CMgrNotify::Connect(IUnknown *pUnk)
{
    return CNotify::Connect(pUnk, IID_INmManagerNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE
CMgrNotify::Disconnect(void)
{
    return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from INmManagerNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE
CMgrNotify::NmUI(CONFN confn)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE
CMgrNotify::CallCreated(INmCall *pCall)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE
CMgrNotify::ConferenceCreated(INmConference *pConference)
{
    ASSERT(NULL != pConference);
    if(NULL == pConference)
	{
		return E_POINTER;
	}
	
	pConference->AddRef();

    ASSERT(NULL == g_pConference);
	if(NULL != g_pConference)
	{
		return E_POINTER;
	}

    g_pConference = pConference;

    //
    // Connect to the conference object
    //
    ASSERT(NULL == g_pConferenceNotify)
    g_pConferenceNotify = new CConfNotify();
    if (NULL != g_pConferenceNotify)
    {
        HRESULT hr = g_pConferenceNotify->Connect(pConference);
        if (FAILED(hr))
        {
            g_pConferenceNotify->Release();
            g_pConferenceNotify = NULL;
        }
    }

    return S_OK;
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

CConfNotify::CConfNotify()
:
    CRefCount(),
    CNotify()
{
    m_cIMembers = 0;
    ::ZeroMemory(m_apIMembers, sizeof(m_apIMembers));
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CConfNotify::~CConfNotify()
{
    ReleaseIMemberArray();
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE
CConfNotify::AddRef(void)
{
    return CRefCount::AddRef();
}


ULONG STDMETHODCALLTYPE
CConfNotify::Release(void)
{
    return CRefCount::Release();
}

HRESULT STDMETHODCALLTYPE
CConfNotify::QueryInterface(REFIID riid, void * *ppvObject)
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

HRESULT STDMETHODCALLTYPE
CConfNotify::Connect(IUnknown *pUnk)
{
    return CNotify::Connect(pUnk, IID_INmConferenceNotify, (IUnknown *)this);
}

HRESULT STDMETHODCALLTYPE
CConfNotify::Disconnect(void)
{
    return CNotify::Disconnect();
}


//****************************************************************************
//
// Methods from IConfNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE
CConfNotify::NmUI(CONFN uNotify)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE
CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
{
    if (NULL == g_pConference)
	{
        return S_OK;
	}

    switch (uState)
    {
		case NM_CONFERENCE_ACTIVE:
		{
			g_fActiveConference = TRUE;
			break;
		}
		case NM_CONFERENCE_INITIALIZING:
		{
			break; // can't do anything just yet
		}
		case NM_CONFERENCE_WAITING:
		{
			::UiDisplaySysMsg(TEXT("Waiting in Host Mode"));
			g_fActiveConference = FALSE;
			break;
		}
		case NM_CONFERENCE_IDLE:
		{
			::UiDisplaySysMsg(TEXT("No conference"));
			g_fActiveConference = FALSE;
			::FreeConference();
			break;
		}
    }

    return S_OK;
}

HRESULT STDMETHODCALLTYPE
CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pIMember)
{
    if(NULL == pIMember)
	{
		return E_POINTER;
	}
	
	switch (uNotify)
    {
		case NM_MEMBER_ADDED:
		case NM_MEMBER_UPDATED:
		{
			//
			// We do not need to remember myself.
			//
			if (S_OK != pIMember->IsSelf())
			{
				//
				// Make sure the data conference is available now.
				//
				ULONG nCaps = 0;
				HRESULT hr = pIMember->GetNmchCaps(&nCaps);
				ASSERT(S_OK == hr);

				if (nCaps & NMCH_DATA)
				{
					//
					// If we have not create the applet seesion, then
					// we need to remember these member pointers.
					//
					if (NULL != g_pSession)
					{
						//
						// Notify the session object of this member.
						//
						g_pSession->SetMember(pIMember);
					}
					else
					{
						//
						// Remember the member pointer. However, it is possible
						// the member already exists in the array. Need to check
						// for duplicate.
						//
						BOOL fFound = FALSE;
						for (ULONG i = 0; i < m_cIMembers; i++)
						{
							if (pIMember == m_apIMembers[m_cIMembers++])
							{
								fFound = TRUE;
								break;
							}
						}
						if (! fFound)
						{
							//
							// Remember this member...
							//
							pIMember->AddRef();
							m_apIMembers[m_cIMembers++] = pIMember;
						}
					}
				}
			}
			break;
		}
		case NM_MEMBER_REMOVED:
		{
			//
			// We do not need to remember myself.
			//
			if (S_OK != pIMember->IsSelf())
			{
				//
				// It is possible that the session is already gone.
				//
				if (NULL != g_pSession)
				{
					//
					// Notify the session object of this leaving member.
					//
					g_pSession->RemoveMember(pIMember);
				}
			}
			break;
		}
		default:
		{
			break;
		}
	}

    return S_OK;
}

HRESULT STDMETHODCALLTYPE
CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel *pChannel)
{
    return S_OK;
}


void CConfNotify::ReleaseIMemberArray(void)
{
    //
    // Clean up the cached member array, which is created before
    // the session object is created.
    //
    for (ULONG i = 0; i < m_cIMembers; i++)
    {
        ASSERT(NULL != m_apIMembers[i]);
        m_apIMembers[i]->Release();
        m_apIMembers[i] = NULL;
    }
    m_cIMembers = 0;
}




//****************************************************************************
//
// CLASS CRefCount
//
//****************************************************************************


//****************************************************************************
//
// Constructor
//
//****************************************************************************

CRefCount::CRefCount(void)
{
    m_cRef = 1;
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CRefCount::~CRefCount(void)
{
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE
CRefCount::AddRef(void)
{
   ASSERT(m_cRef >= 0);

   ::InterlockedIncrement(&m_cRef);

   return (ULONG) m_cRef;
}


ULONG STDMETHODCALLTYPE
CRefCount::Release(void)
{
    if (0 == ::InterlockedDecrement(&m_cRef))
    {
        delete this;
        return 0;
    }

    ASSERT(m_cRef > 0);
    return (ULONG) m_cRef;
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

CNotify::CNotify()
:
    m_pcnpcnt(NULL),
    m_pcnp(NULL),
    m_dwCookie(0),
    m_pUnk(NULL)
{
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CNotify::~CNotify()
{
    Disconnect(); // Make sure we're disconnected
}


//****************************************************************************
//
// HRESULT CNotify::Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN)
//
//****************************************************************************

HRESULT CNotify::Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN)
{
    if(NULL == pUnk || NULL == pUnkN)
	{
		return E_POINTER;
	}
	
	ASSERT(0 == m_dwCookie);
	if(m_dwCookie != 0)
	{
		return HRESULT_FROM_WIN32(ERROR_ALREADY_INITIALIZED);
	}
	
    //
    // Get the connection container
    //
    HRESULT hr = pUnk->QueryInterface(IID_IConnectionPointContainer,
                                      (void **)&m_pcnpcnt);
    if (SUCCEEDED(hr))
    {
        //
        // Find an appropriate connection point
        //
        hr = m_pcnpcnt->FindConnectionPoint(riid, &m_pcnp);
        if (SUCCEEDED(hr))
        {
            ASSERT(NULL != m_pcnp);
            //
            // Connect the sink object
            //
            hr = m_pcnp->Advise((IUnknown *)pUnkN, &m_dwCookie);
        }
    }

    if (FAILED(hr))
    {
        m_dwCookie = 0;
    }
    else
    {
        //
        // Keep around for caller
        //
        m_pUnk = pUnk;
    }

    return hr;
}


//****************************************************************************
//
// HRESULT CNotify::Disconnect (void)
//
//****************************************************************************

HRESULT CNotify::Disconnect (void)
{
    if (0 != m_dwCookie)
    {
        //
        // Disconnect the sink object
        //
        m_pcnp->Unadvise(m_dwCookie);
        m_dwCookie = 0;

        m_pcnp->Release();
        m_pcnp = NULL;

        m_pcnpcnt->Release();
        m_pcnpcnt = NULL;

        m_pUnk = NULL;
    }

    return S_OK;
}

