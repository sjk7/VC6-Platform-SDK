//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCONF.H 
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


//****************************************************************************
//
// Global Variables
//
//****************************************************************************

extern COBLIST * g_pListConference;
extern COBLIST * g_pListConferenceNotify;


//****************************************************************************
//
// Global Functions
//
//****************************************************************************

INmConference * GetCurrentConference(void);
VOID DoConferenceCreate(void);
VOID DoConferenceLeave(void);
VOID FreeConferences(void);
HRESULT HookConference(INmConference * pConference);

