//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       CCONF.H
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


//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

class CMgrNotify : public RefCount, public CNotify, public INmManagerNotify
{
public:
	CMgrNotify();
	~CMgrNotify();

	// INmManagerNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN confn);
	HRESULT STDMETHODCALLTYPE ConferenceCreated(INmConference *pConference);
	HRESULT STDMETHODCALLTYPE CallCreated(INmCall *pCall);

	// ICNotify methods
	HRESULT STDMETHODCALLTYPE Connect (IUnknown *pUnk);
	HRESULT STDMETHODCALLTYPE Disconnect(void);

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObj);
};


//****************************************************************************
//
// CLASS CConfNotify 
//
//****************************************************************************

class CConfNotify : public RefCount, public CNotify, public INmConferenceNotify
{
public:
	CConfNotify();
	~CConfNotify();

	// INmConferenceNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE StateChanged(NM_CONFERENCE_STATE uState);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pfMember);
	HRESULT STDMETHODCALLTYPE ChannelChanged(NM_CHANNEL_NOTIFY uNotify, INmChannel *pChannel);

	// ICNotify methods
	HRESULT STDMETHODCALLTYPE Connect (IUnknown *pUnk);
	HRESULT STDMETHODCALLTYPE Disconnect(void);

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObj);
};



// Global Variables
extern INmManager * g_pMgr;
extern INmConference * g_pConference;

// Global Functions
HRESULT InitConfMgr(void);
VOID FreeConfMgr(void);
VOID FreeConference(void);
HRESULT HookConference(INmConference * pConference);


