//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       APPLET.CPP
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
#include "iapplet.c"

//****************************************************************************
//
// Global Varaiables
//
//****************************************************************************

//
// The Applet object
//
CApplet *g_pApplet = NULL;


//
// Create and initialize the applet object.
//
HRESULT InitApplet(void)
{
    //
    // Make sure we are clean in the beginning.
    //
    ASSERT(NULL == g_pApplet);
    ASSERT(NULL == g_pSession);

	if(NULL != g_pApplet || NULL != g_pSession)
	{
		return E_POINTER;
	}

    //
    // Create the IApplet interface.
    //
    IApplet* pIApplet = NULL;
    HRESULT hr = ::CoCreateInstance(
                        CLSID_NmApplet,
                        NULL,
                        CLSCTX_LOCAL_SERVER,
                        IID_IApplet,
                        (void **) &pIApplet);
    if (SUCCEEDED(hr))
    {
        ASSERT(NULL != pIApplet);

        //
        // Initialize the IApplet interface.
        //
        hr = pIApplet->Initialize();
        if (SUCCEEDED(hr))
        {
            //
            // Create the Applet object, which is a wrapper of the IApplet
            // interface, and also implements the IAppletNotify notification
            // sink.
            //
            g_pApplet = new CApplet(pIApplet);
            if (NULL != g_pApplet)
            {
                //
                // Hook up the notification sink.
                //
                hr = g_pApplet->Advise();
                ASSERT(S_OK == hr);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }
    }
    return hr;
}


//
// Deinitialize and release the applet object.
//
void FreeApplet(void)
{
    HRESULT hr = NO_ERROR;
    if (NULL != g_pSession)
    {
        hr = g_pSession->UnAdvise();
        ASSERT(S_OK == hr);

        g_pSession->Release();
        g_pSession = NULL;
    }

    if (NULL != g_pApplet)
    {
        hr = g_pApplet->UnAdvise();
        ASSERT(S_OK == hr);

        g_pApplet->Release();
        g_pApplet = NULL;
    }
}


//****************************************************************************
//
// CLASS CApplet
//
//****************************************************************************


//****************************************************************************
//
// Constructor
//
//****************************************************************************

CApplet::CApplet(IApplet *pIApplet)
:
    CRefCount(),
    m_pIApplet(pIApplet),
    m_dwCookie(0)
{
    ASSERT(NULL != m_pIApplet);
}


//****************************************************************************
//
// Destructor
//
//****************************************************************************

CApplet::~CApplet(void)
{
    ASSERT(NULL != m_pIApplet);
    m_pIApplet->Release();
}


//****************************************************************************
//
// Methods from IUnknown
//
//****************************************************************************

ULONG STDMETHODCALLTYPE
CApplet::AddRef(void)
{
    return CRefCount::AddRef();
}

ULONG STDMETHODCALLTYPE
CApplet::Release(void)
{
    return CRefCount::Release();
}

HRESULT STDMETHODCALLTYPE
CApplet::QueryInterface(REFIID riid, void * *ppvObject)
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
    else if (riid == IID_IAppletNotify)
    {
        *ppvObject = (IAppletNotify *)this;
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
// Methods from IAppletNotify
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE
CApplet::PermitToJoinSessionIndication
(
    AppletConfID        nConfID,
    BOOL                fPermissionGranted
)
{
    HRESULT hr = NO_ERROR;

    if (fPermissionGranted)
    {
        //
        // A new conference just starts.
        //

        //
        // We only support one session per applet for now.
        //
        ASSERT(NULL == g_pSession);

		if(NULL != g_pSession)
		{
			return E_POINTER;
		}
        //
        // Create the IAppletSession interface.
        //
        IAppletSession *pISession = NULL;
        hr = m_pIApplet->CreateSession(&pISession, nConfID);
        if (S_OK == hr)
        {
            //
            // Create the Applet Session object, which is a wrapper of
            // the IAppletSession interface, and implements
            // the IAppletSessionNotify notification sink.
            //
            g_pSession = new CAppletSession(this, pISession);
            if (NULL != g_pSession)
            {
                //
                // Hook up the notification sink.
                //
                hr = g_pSession->Advise();
                ASSERT(S_OK == hr);

                //
                // Join the conference now.
                //
                hr = g_pSession->Join();
                ASSERT(S_OK == hr);
            }
        }
        else
        {
            ASSERT(S_OK == hr);
        }
    }
    else
    {
        //
        // The conference is exiting.
        //

        if (NULL != g_pSession)
        {
            //
            // Make sure this is the conference which I am in now.
            //
            ASSERT(nConfID == g_pSession->GetConfID());

            //
            // Leave the conference as directed.
            //
            hr = g_pSession->Leave();
            ASSERT(S_OK == hr);

            //
            // Unhook the notification sink.
            //
            hr = g_pSession->UnAdvise();
            ASSERT(S_OK == hr);

            g_pSession->Release();
            g_pSession = NULL;
        }
    }

    return S_OK;
}


HRESULT STDMETHODCALLTYPE
CApplet::AutoJoinSessionIndication
(
    IAppletSession     *pSession,
    HRESULT             hrResult,
    AppletUserID        uidMyself,
    AppletNodeID        nidMyself,
    AppletSessionID     sidMyself,
    AppletEntityID      eidMyself,
    ULONG               cDynamicChannels,
    AppletChannelID     aDynamicChannels[]
)
{
    //
    // We do not register auto-join; therefore,
    // we will not receive this indication.
    //

    //
    // In case of using auto join, the code to handle this notification
    // should be very similar to that in CAppletSession::JoinSessionConfirm.
    //

    return S_OK;
}


