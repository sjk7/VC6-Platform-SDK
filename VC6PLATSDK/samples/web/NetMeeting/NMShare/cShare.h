//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       CSHARE.H
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
	HRESULT STDMETHODCALLTYPE StateChanged(NM_SHAPP_STATE uNotify, INmSharableApp *pApp);

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

HRESULT HookChannel(INmChannel * pChannel);
VOID UnHookChannel(INmChannel * pChannel);
VOID FreeAppShareChannel(void);

// from cHwnd.cpp
VOID UpdateApp(INmSharableApp * pApp);
VOID UpdateAppList(void);
VOID DoEnumApps(void);
VOID FreeAllApps(void);

VOID DoWorkAlone(void);
VOID DoCollaborate(void);
VOID DoTakeControl(void);

