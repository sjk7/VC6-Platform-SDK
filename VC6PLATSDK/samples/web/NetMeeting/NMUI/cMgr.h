//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CMGR.H
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
// CLASS CMgrNotify 
//
//****************************************************************************

class CMgrNotify : public RefCount, public CNotify, public INmManagerNotify
{
public:
	CMgrNotify();
	~CMgrNotify();

	// INmManagerNotify
	HRESULT STDMETHODCALLTYPE NmUI(CONFN uNotify);
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
// Global Variables
//
//****************************************************************************

extern INmManager * g_pMgr;

extern const GUID g_guid;
extern const GUID g_guidNMUIChat;


//****************************************************************************
//
// Global Functions
//
//****************************************************************************

HRESULT InitConfMgr(void);
VOID FreeConfMgr(void);
INmConference * GetCurrentConference(void);
VOID DumpSysInfo(void);
VOID DumpLaunchInfo(void);

VOID SysLogOnOff(int iDirection);


