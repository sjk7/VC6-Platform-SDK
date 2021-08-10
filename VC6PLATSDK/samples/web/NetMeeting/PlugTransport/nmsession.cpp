//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       NMSESSION.CPP
//  Content:    
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


//***********************
//FUNCTION DECLARATIONS
//***********************

BSTR LPSTR2BSTR(LPSTR pszString);
BOOL BSTR2LPSTR(BSTR bstrConnID, LPSTR pszConnID);


//**********************************
//
// CLASS Conf
//
//**********************************

//****************************************************************************
//
//    FUNCTION:   Conf::Conf(HWND hWnd)
//
//    PURPOSE:    Construction

//    COMMENTS:
//       
//        
//
//****************************************************************************

Conf::Conf(HWND hWnd)
{
    m_pMgrNotify    = NULL;
    m_pCallNotify   = NULL;
    m_pConfNotify   = NULL;

    m_pINmMgr       = NULL;
    m_pINmConf      = NULL;
    m_pINmCall      = NULL;
    m_bInCall       = FALSE;

    // Get the handler to the application window
    m_hWnd = hWnd;
}


//****************************************************************************
//
//    FUNCTION:   Conf::~Conf()
//
//    PURPOSE:    Destruction

//    COMMENTS:
//      
//        
//
//****************************************************************************

Conf::~Conf()
{
    // Assert that everything has been tidied up - i.e. Uninitialize was called
    //
    ASSERT(m_pMgrNotify == NULL);
    ASSERT(m_pCallNotify == NULL);
    ASSERT(m_pConfNotify == NULL);
    ASSERT(m_pINmMgr == NULL);
    ASSERT(m_pINmConf == NULL);
    ASSERT(m_pINmCall == NULL);

}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::Initialize()
//
//    PURPOSE:    Initiate NetMeeting, obtain a pointer to INmManager, 
//                connect the MgrNotify sink object and initialize INmManager.
//
//    COMMENTS:
//                      
//
//****************************************************************************

HRESULT Conf::Initialize()
{
    HRESULT hr          = S_OK;
    ULONG   uOptions    = NM_INIT_CONTROL;                  // Don't display the NetMeeting UI
    ULONG   uCaps       = NMCH_DATA | NMCH_FT | NMCH_SHARE; // data only conference

    // Create Sink Objects.
    // During construction, AddRef occurs
    m_pMgrNotify = new CMgrNotify(this);  
    if (m_pMgrNotify == NULL)
    {
        return E_OUTOFMEMORY;
    }
    
    m_pCallNotify = new CCallNotify(this);
    if (m_pCallNotify == NULL)
    {
        return E_OUTOFMEMORY;
    }
    
    m_pConfNotify = new CConfNotify(this);
    if (m_pConfNotify == NULL)
    {
        return E_OUTOFMEMORY;
    }

    hr = CoCreateInstance(CLSID_NmManager,NULL,CLSCTX_INPROC_SERVER,IID_INmManager,(VOID **)&m_pINmMgr);
    if (FAILED(hr))
    {
        return hr;
    }
    
    hr = m_pMgrNotify->Connect(m_pINmMgr);
    if (FAILED(hr))
    {
        return hr;
    }
 
    hr = m_pINmMgr->Initialize(&uOptions,&uCaps);
    if (FAILED(hr))
    {
        return hr;
    }

    return hr;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::Uninitialize()
//
//    PURPOSE:    Disconnect MgrNotify sink object and release the interface INmManager
//
//    COMMENTS:
//
//        
//        
//        
//
//****************************************************************************

HRESULT Conf::Uninitialize()
{
    if (NULL != m_pMgrNotify)
        m_pMgrNotify->Disconnect();

    if (NULL != m_pINmMgr)
    {
        m_pINmMgr->Release();
        m_pINmMgr = NULL;
    }

    if (m_pMgrNotify != NULL)
    {
        m_pMgrNotify->Release();  
        m_pMgrNotify = NULL;
    }

    if (m_pCallNotify != NULL)
    {
        m_pCallNotify->Release();
        m_pCallNotify = NULL;
    }

    if (m_pConfNotify != NULL)
    {
        m_pConfNotify->Release();
        m_pConfNotify = NULL;
    }

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::Call(CPluggableTransport *pPlugTrans)
//
//    PURPOSE:    Make the call using the already created transport connection
//
//    COMMENTS:
//    
//
//****************************************************************************

HRESULT Conf::Call(CPluggableTransport *pPlugTrans)
{
    HRESULT hr          = S_OK;
    BSTR    bstrName    = NULL;

    if (NULL == pPlugTrans)
        return E_FAIL;

    if (NULL == m_pINmMgr)
        return E_FAIL;
    
    if (FALSE == pPlugTrans->InConnection())
        return E_FAIL;

    // get the BSTR form of the connection ID
    bstrName = LPSTR2BSTR(pPlugTrans->GetConnectionID());
    if (NULL == bstrName)
        return E_OUTOFMEMORY;
    
    // make the call
    hr = m_pINmMgr->CreateCall(&m_pINmCall, NM_CALL_DEFAULT, NM_ADDR_T120_TRANSPORT, bstrName, NULL);
    if (FAILED(hr))
    {
        // Call object sometimes needs to be released.
        if (NULL != m_pINmCall)
        {
            m_pCallNotify->Disconnect();
            m_pINmCall->Release();
            m_pINmCall = NULL;
        }
    }

    SysFreeString(bstrName);
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::HangUp()
//
//    PURPOSE:   Leave the conference

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT Conf::HangUp()
{
    HRESULT hr = S_OK;

    // if call hungup before Call accepted or rejected, release INmCall and 
    // disconnect CallNotify sink
    if (NULL != m_pINmCall)
    {
        hr = m_pINmCall->Cancel();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pINmCall->Cancel failed."),TEXT("Error"),MB_OK);
        }

        if (NULL != m_pCallNotify)
        {
            hr = m_pCallNotify->Disconnect();
            if (FAILED(hr))
            {
                MessageBox(NULL,TEXT("m_pCallNotify->Disconnect failed."),TEXT("Error"),MB_OK);
            }
        }
        
        m_pINmCall->Release();
        m_pINmCall=NULL;
    }
    else
    {
        if (NULL != m_pINmConf)
        {
            hr = m_pINmConf->Leave();
            if (FAILED(hr))
            {
                MessageBox(NULL,TEXT("m_pINmConf->Leave failed."),TEXT("Error"),MB_OK);
            }
        }
    }


    // Release INmConf and disconnect the ConfNotify sink
    if (NULL != m_pINmConf)
    {
        if (NULL != m_pConfNotify)
        {
            hr = m_pConfNotify->Disconnect();
            if (FAILED(hr))
            {
                MessageBox(NULL,TEXT("m_pConfNotify->Disconnect failed."),TEXT("Error"),MB_OK);
            }
        }
        
        m_pINmConf->Release();
        m_pINmConf=NULL;
    }
    
    m_bInCall = false;

    // update the UI
    if (m_hWnd)
    {
        SendMessage(m_hWnd,WM_DISCONNECTED,0,0);
    }

    return hr;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::CallCreated(INmCall * pCall)
//
//    PURPOSE:    Callback from the MgrNotify sink object

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT Conf::CallCreated(INmCall * pCall)
{
    HRESULT hr  = S_OK;
    
    if (NULL == pCall)
    {
        return E_POINTER;
    }

    ASSERT(m_pINmCall == NULL);
    if (m_pINmCall != NULL)
    {
        MessageBox(NULL,TEXT("m_pINmCall is not NULL, and we have a new call!"),TEXT("Error"),MB_OK);
        m_pINmCall->Release();
    }
    
    m_pINmCall = pCall;
    m_pINmCall->AddRef();

    if (NULL != m_pCallNotify)
    {
        hr = m_pCallNotify->Connect(pCall);
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pCallNotify->Connect failed."),TEXT("Error"),MB_OK);
            return hr;
        }
    }
    
    m_bInCall = true;

    // update the UI
    if (m_hWnd)
        SendMessage(m_hWnd,WM_CONNECTING,0,0);

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::AcceptCall()
//
//    PURPOSE:    Accept the incoming call

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT Conf::AcceptCall()
{
    if (m_pINmCall == NULL)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_READY);
    }

    return m_pINmCall->Accept();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::RejectCall()  
//
//    PURPOSE:    Reject the incoming call

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT Conf::RejectCall()  
{
    if (m_pINmCall == NULL)
    {
        return HRESULT_FROM_WIN32(ERROR_NOT_READY);
    }

    return m_pINmCall->Reject();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::ConferenceCreated(INmConference *pINmConf)
//
//    PURPOSE:    Callback from the MgrNotify sink object that 
//                a new conference has been created
//
//    COMMENTS:
//      
//
//****************************************************************************

HRESULT Conf::ConferenceCreated(INmConference *pINmConf)
{    
    HRESULT hr = S_OK;
    
    if (pINmConf == NULL)
    {
        return E_POINTER;
    }

    ASSERT(m_pINmConf == NULL);
    if (m_pINmConf != NULL)
    {
        MessageBox(NULL,TEXT("m_pINmConf is not NULL, and we have a new conf!"),TEXT("Error"),MB_OK);
        m_pINmConf->Release();
    }

    //Add Conference notification sink to handle channels.
    m_pINmConf = pINmConf;
    m_pINmConf->AddRef();

    if (m_pConfNotify != NULL)
    {
        hr = m_pConfNotify->Connect(pINmConf);
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConfNotify->Connect failed."),TEXT("Error"),MB_OK);
            return hr;
        }
    }
    
    m_bInCall = true;

    if (m_hWnd)
    {
        SendMessage(m_hWnd,WM_CONNECTED,0,0);
    }

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::CallAccepted()  
//
//    PURPOSE:    Callback from the CallNotify sink object that 
//                the new call has been accepted

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT Conf::CallAccepted()  
{
    HRESULT hr = S_OK;
    
    // Release INmCall, and let send window message that a user has connected
    if (NULL != m_pINmCall)
    {
        m_pINmCall->Release();
        m_pINmCall=NULL;
    }

    if (m_pCallNotify != NULL)
    {
        hr = m_pCallNotify->Disconnect();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pCallNotify->Disconnect failed."),TEXT("Error"),MB_OK);
        }
    }
    
    m_bInCall = true;

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::CallRejected() 
//
//    PURPOSE:    Callback from the CallNotify sink object that 
//                the new call has been rejected

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT Conf::CallRejected() 
{
    HRESULT hr = S_OK;
    // Release INmCall, INmConf, disconnect CallNotify and ConfNotify
    // sink objects, and send message to main window that the user has 
    // disconnected.    
    if (NULL != m_pINmCall)
    {
        if (NULL != m_pCallNotify)
        {
            hr = m_pCallNotify->Disconnect();
            if (FAILED(hr))
            {
                MessageBox(NULL,TEXT("m_pCallNotify->Disconnect failed."),TEXT("Error"),MB_OK);
            }
        }
        
        m_pINmCall->Release();
        m_pINmCall=NULL;
    }

    if (NULL != m_pINmConf)
    {
        m_pINmConf->Release();
        m_pINmConf=NULL;
    }

    if (NULL != m_pConfNotify)
    {
        hr = m_pConfNotify->Disconnect();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConfNotify->Disconnect failed."),TEXT("Error"),MB_OK);
        }
    }
    
    m_bInCall = false;

    if (m_hWnd)
        SendMessage(m_hWnd,WM_DISCONNECTED,0,0);

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT Conf::RemoteHungup()
//
//    PURPOSE:    Callback from the ConfNotify sink object 
//                that a member has left the conference

//    COMMENTS:
//       
//        
//
//****************************************************************************

HRESULT Conf::RemoteHungup()
{    
    HRESULT hr = S_OK;

    // Release INmConf, disconnect ConfNotify sink object, and send message to 
    // main window that the remote node has disconnected.
    if (NULL != m_pINmConf)
    {
        m_pINmConf->Release();
        m_pINmConf = NULL;
    }

    if (NULL != m_pConfNotify)
    {
        hr = m_pConfNotify->Disconnect();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConfNotify->Disconnect failed."),TEXT("Error"),MB_OK);
        }
    }
    
    m_bInCall = false;

    if (m_hWnd)
    {
        SendMessage(m_hWnd,WM_DISCONNECTED,0,0);
    }
    
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   BOOL Conf::InCall()
//
//    PURPOSE: 
//
//    COMMENTS:
//       
//
//****************************************************************************

BOOL Conf::InCall()
{    
    return m_bInCall;
}


//****************************************************************************
//
//    FUNCTION:   INmManager * Conf::GetNmManager()
//
//    PURPOSE: 
//
//    COMMENTS:
//      
//        
//
//****************************************************************************

INmManager * Conf::GetNmManager()
{
    return m_pINmMgr;
}



//****************************************************************************
//
// CLASS CCallNotify
//
//****************************************************************************

//****************************************************************************
//
//    FUNCTION:   CCallNotify::CCallNotify()
//
//    PURPOSE:    Construction

//    COMMENTS:     
//
//****************************************************************************

CCallNotify::CCallNotify()
{
    m_pConf = NULL;
}


//****************************************************************************
//
//    FUNCTION:   CCallNotify::CCallNotify(Conf *pConf)
//
//    PURPOSE:    Construction

//    COMMENTS:       
//
//****************************************************************************

CCallNotify::CCallNotify(Conf *pConf)
{
    m_pConf = pConf;
}

//****************************************************************************
//
//    FUNCTION:   CCallNotify::~CCallNotify()
//
//    PURPOSE:    Destruction

//    COMMENTS:
//
//        
//****************************************************************************

CCallNotify::~CCallNotify()
{}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE CCallNotify::AddRef()
//
//    PURPOSE:    method from IUnknown
//
//    COMMENTS:
//              
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CCallNotify::AddRef()
{
    return RefCount::AddRef();
}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE CCallNotify::Release()
//
//    PURPOSE:    Method from IUnknown
//
//    COMMENTS:
//      
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CCallNotify::Release()
{
    return RefCount::Release();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CCallNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
//
//    PURPOSE:    Method from IUnknown

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
{
    if (ppvObject == NULL)
    {
        return E_POINTER;
    }
    
    *ppvObject = NULL;
    
    if (riid == IID_IUnknown)
        *ppvObject = (PVOID *)this;
    else if (riid == IID_INmCallNotify)
        *ppvObject = (PVOID *)this;
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}

//****************************************************************************
//
//    FUNCTION:   HRESULT CCallNotify::Connect(IUnknown * pUnkOuter)
//
//    PURPOSE:    Sink connect method
//
//    COMMENTS:
//       
//
//****************************************************************************

HRESULT CCallNotify::Connect(IUnknown * pUnkOuter)
{
    return CNotify::Connect(pUnkOuter, IID_INmCallNotify, (IUnknown *)this);
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CCallNotify::Disconnect()
//
//    PURPOSE:    Sink disconnect method
//
//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CCallNotify::Disconnect()
{
    return CNotify::Disconnect();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CCallNotify::Failed(ULONG uError)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:   
//
//    
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Failed(ULONG uError)
{
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:  HRESULT STDMETHODCALLTYPE CCallNotify::Accepted(INmConference *pConference) 
//
//    PURPOSE:   Sink notification method
//
//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::Accepted(INmConference *pConference)
{
    return S_OK;
}

//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CCallNotify::NmUI(CONFN uNotify)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::NmUI(CONFN uNotify)
{
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CCallNotify::StateChanged(NM_CALL_STATE uState)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CCallNotify::StateChanged(NM_CALL_STATE uState)
{
    HRESULT hr = S_OK;
    
    if (NULL == m_pConf)
    {
        return E_FAIL;
    }
    
    switch (uState)
    {
    case NM_CALL_RING:
    
        // Query whether to accept the call and notify my Conf object the result.
        if (MessageBox(NULL,TEXT("Accept incoming call?"),TEXT("Call"),MB_YESNO|MB_TASKMODAL)== IDYES)
        {
            hr = m_pConf->AcceptCall();
            if (FAILED(hr))
            {
                MessageBox(NULL,TEXT("m_pConf->AcceptCall failed."),TEXT("Error"),MB_OK);
            }
        }
        
        else
        {
            hr = m_pConf->RejectCall();
            if (FAILED(hr))
            {
                MessageBox(NULL,TEXT("m_pConf->RejectCall failed."),TEXT("Error"),MB_OK);
            }
        }
        break;

    case NM_CALL_REJECTED:

        // Notify my Conf object that the call was rejected.
        hr = m_pConf->CallRejected();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConf->CallRejected failed."),TEXT("Error"),MB_OK);
        }
        
        break;

    case NM_CALL_ACCEPTED:

        // Notify my Conf object that the call was accepted
        hr = m_pConf->CallAccepted();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConf->CallAccepted failed."),TEXT("Error"),MB_OK);
        }
        break;
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
//    FUNCTION:   CConfNotify::CConfNotify()
//
//    PURPOSE:    Construction
//
//    COMMENTS:
//      
//
//****************************************************************************

CConfNotify::CConfNotify()
{
    m_pConf = NULL;
}


//****************************************************************************
//
//    FUNCTION:   CConfNotify::CConfNotify(Conf *pConf)
//
//    PURPOSE:    Construction

//    COMMENTS:
//      
//
//****************************************************************************

CConfNotify::CConfNotify(Conf *pConf)
{
    m_pConf = pConf;
}


//****************************************************************************
//
//    FUNCTION:   CConfNotify::~CConfNotify()
//
//    PURPOSE:    Destruction

//    COMMENTS:
//
//        
//        
//        
//
//****************************************************************************

CConfNotify::~CConfNotify()
{}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE CConfNotify::AddRef()
//
//    PURPOSE:    Method from IUnknown

//    COMMENTS:
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CConfNotify::AddRef()
{
    return RefCount::AddRef();
}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE CConfNotify::Release()
//
//    PURPOSE:    Method from IUnknown

//    COMMENTS:
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CConfNotify::Release()
{
    return RefCount::Release();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CConfNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
//
//    PURPOSE:    Method from IUnknown

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
{
    if (ppvObject == NULL)
    {
        return E_POINTER;
    }
    
    *ppvObject = NULL;
    
    if (riid == IID_IUnknown)
        *ppvObject = (PVOID *)this;
    else if (riid == IID_INmConferenceNotify)
        *ppvObject = (PVOID *)this;
    else
        return E_NOINTERFACE;

    AddRef();

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CConfNotify::Connect(IUnknown * pUnkOuter)
//
//    PURPOSE:    Sink connect method

//    COMMENTS:       
//
//****************************************************************************

HRESULT CConfNotify::Connect(IUnknown * pUnkOuter)
{
    return CNotify::Connect(pUnkOuter, IID_INmConferenceNotify, (IUnknown *)this);
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CConfNotify::Disconnect()
//
//    PURPOSE:    Sink disconnect method 

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CConfNotify::Disconnect()
{
    return CNotify::Disconnect();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel * pChannel)
//
//    PURPOSE:    Sink notification method
//
//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel * pChannel)
{
    HRESULT hr  = S_OK;
    ULONG   uCh = 0;

    if (pChannel == NULL)
    {
        return E_POINTER;
    }

    // When notified that a channel has been added add code to handle it.
    // We don't need the code below for this app. I keep it to make it easier
    // if somebody needs to handle a channel
    if (uNotify == NM_CHANNEL_ADDED)
    {
        hr = pChannel->GetNmch(&uCh);
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("pChannel->GetNmch failed."),TEXT("Error"),MB_OK);
        }
    }

    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember)
//
//    PURPOSE:    Sink notification method
//
//    COMMENTS:
//
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember)
{
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::NmUI(CONFN uNotify)
{
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
//
//    PURPOSE:    Sink notification method
//
//    COMMENTS:
//     
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CConfNotify::StateChanged(NM_CONFERENCE_STATE uState)
{
    HRESULT hr = S_OK;
    
    // Notify my Conf object that the remote hungup.
    if ((uState == NM_CONFERENCE_IDLE) && (m_pConf != NULL))
    {
        hr = m_pConf->RemoteHungup();
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConf->RemoteHungup failed."),TEXT("Error"),MB_OK);
        }
    }

    return S_OK;
}



//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

//****************************************************************************
//
//    FUNCTION:   CMgrNotify::CMgrNotify()
//
//    PURPOSE:    Construction

//    COMMENTS:
//    
//
//****************************************************************************

CMgrNotify::CMgrNotify()
{
    m_pConf = NULL;
}


//****************************************************************************
//
//    FUNCTION:   CMgrNotify::CMgrNotify(Conf * pConf)
// 
//    PURPOSE:    Construction

//    COMMENTS:
//      
//
//****************************************************************************

CMgrNotify::CMgrNotify(Conf * pConf)
{
    m_pConf = pConf;
}


//****************************************************************************
//
//    FUNCTION:   CMgrNotify::~CMgrNotify()
//
//    PURPOSE:    Destruction

//    COMMENTS:
//       
//
//****************************************************************************

CMgrNotify::~CMgrNotify()
{}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE CMgrNotify::AddRef()
//
//    PURPOSE:    Method from IUnknown 

//    COMMENTS:
//      
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CMgrNotify::AddRef()
{
    return RefCount::AddRef();
}


//****************************************************************************
//
//    FUNCTION:   ULONG STDMETHODCALLTYPE CMgrNotify::Release()
//
//    PURPOSE:    Method from IUnknown 

//    COMMENTS:
//     
//
//****************************************************************************

ULONG STDMETHODCALLTYPE CMgrNotify::Release()
{
    return RefCount::Release();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CMgrNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
//
//    PURPOSE:    Method from IUnknown 

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::QueryInterface(REFIID riid, PVOID * ppvObject)
{
    if (ppvObject == NULL)
    {
        return E_POINTER;
    }
    
    *ppvObject = NULL;
    
    if (riid == IID_IUnknown)
        *ppvObject = (PVOID *)this;
    else if (riid == IID_INmManagerNotify)
        *ppvObject = (PVOID *)this;
    else
        return E_NOINTERFACE;

    AddRef();
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CMgrNotify::Connect(IUnknown * pUnkOuter)
//
//    PURPOSE:    Sink connect method

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT CMgrNotify::Connect(IUnknown * pUnkOuter)
{
    return CNotify::Connect(pUnkOuter, IID_INmManagerNotify, (IUnknown *)this);
}


//****************************************************************************
//
//    FUNCTION:   HRESULT CMgrNotify::Disconnect()
//
//    PURPOSE:    Sink disconnect method

//    COMMENTS:
//       
//
//****************************************************************************

HRESULT CMgrNotify::Disconnect()
{
    return CNotify::Disconnect();
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CMgrNotify::CallCreated(INmCall * pCall)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::CallCreated(INmCall * pCall)
{
    HRESULT hr = S_OK;
    // Notify my Conf object that a Call object was created
    if (m_pConf != NULL)
    {
        hr = m_pConf->CallCreated(pCall);
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConf->CallCreated failed."),TEXT("Error"),MB_OK);
        }
    }
    
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CMgrNotify::ConferenceCreated(INmConference * pConference)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:
//      
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::ConferenceCreated(INmConference * pConference)
{
    HRESULT hr = S_OK;
    // Notify my Conf object that a Conference object was created
    if (m_pConf != NULL)
    {
        hr = m_pConf->ConferenceCreated(pConference); 
        if (FAILED(hr))
        {
            MessageBox(NULL,TEXT("m_pConf->ConferenceCreated failed."),TEXT("Error"),MB_OK);
        }
    }
    
    return S_OK;
}


//****************************************************************************
//
//    FUNCTION:   HRESULT STDMETHODCALLTYPE CMgrNotify::NmUI(CONFN uNotify)
//
//    PURPOSE:    Sink notification method

//    COMMENTS:
//     
//
//****************************************************************************

HRESULT STDMETHODCALLTYPE CMgrNotify::NmUI(CONFN uNotify)
{
    return S_OK;
}
