//****************************************************************************
//  Module:     NMUI.EXE
//  File:       CFT.H 
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
// CLASS CFileTransferNotify
//
//****************************************************************************

class CFileTransferNotify : public RefCount, public CNotify, public INmChannelFtNotify
{
public:
	CFileTransferNotify();
	~CFileTransferNotify();

	// INmChannelNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember *pMember);
	HRESULT STDMETHODCALLTYPE FtUpdate(CONFN uNotify, INmFt *pFt);

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
// Global Routines
//
//****************************************************************************

HRESULT HookFileTransfer(INmChannel * pChannel);

VOID SendFile(INmMember * pMember);
VOID DoFtCancel(void);

