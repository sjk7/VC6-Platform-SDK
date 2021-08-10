//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CCALL.H 
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
// CLASS CCallNotify
//
//****************************************************************************

class CCallNotify : public RefCount, public CNotify, public INmCallNotify
{
public:
	CCallNotify();
	~CCallNotify();

	// INmCallNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE StateChanged(NM_CALL_STATE uState);
	HRESULT STDMETHODCALLTYPE Failed(ULONG uError);
	HRESULT STDMETHODCALLTYPE Accepted(INmConference *pConference);

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

extern COBLIST * g_pListCall;
extern COBLIST * g_pListCallNotify;


//****************************************************************************
//
// Global Routines
//
//****************************************************************************

HRESULT HookCall(INmCall * pCall);
VOID DoCallCreate(void);
VOID DoCallConference(void);
VOID DoCancelCall(void);
VOID DoHandleCall(BOOL fAccept);
VOID FreeCalls(void);
INmCall * GetCurrentCall(void);

