//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CSHARE.H
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
// CLASS CAppShareNotify
//
//****************************************************************************

class CAppShareNotify : public RefCount, public CNotify, public INmChannelAppShareNotify
{
public:
	CAppShareNotify();
	~CAppShareNotify();

	// INmChannelAppShareNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember);
	HRESULT STDMETHODCALLTYPE StateChanged(NM_SHAPP_STATE uState, INmSharableApp *pApp);

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

extern INmChannelAppShare * g_pChannelAppShare;
extern CAppShareNotify    * g_pNotifyAppShare;


//****************************************************************************
//
// Global Routines
//
//****************************************************************************

HRESULT HookAppShare(INmChannel * pAppShare);
VOID DoCreateAppShareChannel(INmConference *pConference);
VOID FreeAppShareChannel(void);


//****************************************************************************
//
// msgType values
//
//****************************************************************************




