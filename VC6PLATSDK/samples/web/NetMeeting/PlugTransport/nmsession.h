//****************************************************************************
//  Module:     PLUGTRANSPORT.EXE     
//  File:       NMSESSION.H
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



#ifndef _NM_SESSION_H_
#define _NM_SESSION_H_

#define WM_CONNECTING	WM_USER + 1
#define WM_CONNECTED	WM_USER + 2
#define WM_DISCONNECTED WM_USER + 3

#define PLUGABLE_PORT_NUMBER    522  // ULS server port number
#define WM_PLUGABLE_SOCKET      (WM_APP + 0x601)

#define NAMEMAXLENGTH           64
#define CONNIDMAXLENGTH         64

class Conf;
class CPluggableTransport;

//****************************************************************************
//
// CLASS CCallNotify
//
//****************************************************************************

class CCallNotify : 
	public INmCallNotify, 
	public RefCount, 
	public CNotify 
{
private:
	Conf *m_pConf; // Back pointer to Conf object
	CCallNotify(); // prevent default construction
public:
	CCallNotify(Conf *);
	virtual ~CCallNotify();
	
	// from IUnknown
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);

	// Sink connection methods
	HRESULT Connect(IUnknown *pUnkOuter);
	HRESULT Disconnect(void);
	
	// Main sink notification methods
	HRESULT STDMETHODCALLTYPE StateChanged( NM_CALL_STATE uState);
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE Failed(ULONG uError);
	HRESULT STDMETHODCALLTYPE Accepted(INmConference *pConference);
};


//****************************************************************************
//
// CLASS CConfNotify
//
//****************************************************************************

class CConfNotify : 
	public INmConferenceNotify, 
	public RefCount, 
	public CNotify
{
private:
	CConfNotify();  // Prevents default construction.
	Conf *m_pConf;	// Back pointer to Conf object
public:
	CConfNotify(Conf *);
	virtual ~CConfNotify();

	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);
	
	HRESULT Connect(IUnknown *pUnkOuter);
	HRESULT Disconnect(void);

	HRESULT STDMETHODCALLTYPE StateChanged(NM_CONFERENCE_STATE uState);
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember);
	HRESULT STDMETHODCALLTYPE ChannelChanged(NM_CHANNEL_NOTIFY uNotify,INmChannel *pChannel);

};

//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

class CMgrNotify : 
	public INmManagerNotify, 
	public RefCount, 
	public CNotify  
{
private:
	CMgrNotify();	// Prevent default construction
	Conf *m_pConf;	// Back pointer to Conf object

public:
	CMgrNotify(Conf *);
	virtual ~CMgrNotify();

	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObject);

	HRESULT Connect(IUnknown *pUnkOuter);
	HRESULT Disconnect(void);

	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE ConferenceCreated(INmConference *pConference);
	HRESULT STDMETHODCALLTYPE CallCreated(INmCall *pCall);
};

//****************************************************************************
//
// CLASS Conf
//
//****************************************************************************

class Conf  
{
private:
	CMgrNotify*		m_pMgrNotify;
	CCallNotify*	m_pCallNotify;
	CConfNotify*	m_pConfNotify;
	INmConference*	m_pINmConf;
	INmManager* 	m_pINmMgr;
	INmCall*		m_pINmCall;
	HWND 			m_hWnd;
    BOOL 			m_bInCall;

public:
	Conf(HWND);
	virtual ~Conf();

	HRESULT Initialize(void);
	HRESULT Uninitialize(void);
    HRESULT Call(CPluggableTransport *pPlugTrans);
	HRESULT CallCreated(INmCall *pCall);
	HRESULT ConferenceCreated(INmConference *);
	HRESULT CallRejected();
	HRESULT CallAccepted();
	HRESULT HangUp();
	HRESULT RemoteHungup();
	HRESULT RejectCall();
	HRESULT AcceptCall();
    BOOL    InCall();
    INmManager * GetNmManager();
};


#endif // _NM_SESSION_H_
