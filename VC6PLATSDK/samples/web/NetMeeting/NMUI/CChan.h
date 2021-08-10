//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCHAN.H 
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
// CLASS CChannelNotify
//
//****************************************************************************

class CChannelNotify : public RefCount, public CNotify, public INmChannelNotify
{
public:
	CChannelNotify();
	~CChannelNotify();

	// INmChannelNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember);

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

extern COBLIST * g_pListChannel;
extern COBLIST * g_pListChannelNotify;


//****************************************************************************
//
// Global Routines
//
//****************************************************************************

HRESULT HookChannel(INmChannel * pChannel);
VOID UnHookChannel(INmChannel * pChannel);
VOID UpdateChannelState(INmChannel * pChannel);
VOID FreeChannels(void);
VOID FreeFt(void);
VOID FreeAs(void);

VOID SendFile(INmMember * pMember);
VOID DoFtCancel(void);

