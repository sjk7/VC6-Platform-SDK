//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       CDATA.H
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
// CLASS CDataNotify
//
//****************************************************************************

class CDataNotify : public RefCount, public CNotify, public INmChannelDataNotify
{
public:
	CDataNotify();
	~CDataNotify();

	// INmChannelDataNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember);
	HRESULT STDMETHODCALLTYPE DataSent(INmMember *pMember, ULONG uSize, LPBYTE pb);
	HRESULT STDMETHODCALLTYPE DataReceived(INmMember *pMember, ULONG uSize, LPBYTE pb, ULONG dwFlags);

	// ICNotify methods
	HRESULT STDMETHODCALLTYPE Connect (IUnknown *pUnk);
	HRESULT STDMETHODCALLTYPE Disconnect(void);

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, PVOID *ppvObj);
};


// Global Variables
extern INmChannelData * g_pChannelData;
extern CDataNotify    * g_pNotifyData;

// Global Routines
HRESULT HookData(INmChannelData * pChannel);
VOID DoCreateDataChannel(INmConference *pConference);
VOID FreeDataChannel(void);
VOID CheckDataChannel(void);

