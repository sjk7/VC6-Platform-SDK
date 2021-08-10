//****************************************************************************
//  Module:     NMFT.EXE
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
// CLASS CFtNotify
//
//****************************************************************************

class CFtNotify : public RefCount, public CNotify, public INmChannelFtNotify
{
public:
	CFtNotify();
	~CFtNotify();

	// INmChannelNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
	HRESULT STDMETHODCALLTYPE MemberChanged(NM_MEMBER_NOTIFY uNotify, INmMember * pMember);

	// INmChannelFtNotify
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
// Global Variables
//
//****************************************************************************

extern INmManager    * g_pMgr;
extern INmConference * g_pConference;
extern INmChannelFt  * g_pChannelFt;
extern CFtNotify     * g_pNotifyFt;
extern INmMember     * g_pMember;
extern INmFt         * g_pFt;


//****************************************************************************
//
// Global Functions
//
//****************************************************************************

BOOL FInitNm(void);
VOID FreeNmObjects(void);
HRESULT SendFile(void);


