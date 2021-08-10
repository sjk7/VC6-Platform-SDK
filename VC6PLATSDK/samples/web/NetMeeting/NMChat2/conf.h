//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       CONF.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1999-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#ifndef _CONF_H_
#define _CONF_H_

//****************************************************************************
//
// CLASS CRefCount
//
//****************************************************************************

class CRefCount
{
public:

   CRefCount();
   // Virtual destructor defers to destructor of derived class.
   virtual ~CRefCount();

   // IUnknown methods

   ULONG STDMETHODCALLTYPE AddRef(void);
   ULONG STDMETHODCALLTYPE Release(void);

private:

    LONG m_cRef;
};


//****************************************************************************
//
// CLASS CNotify
//
// Notification sink
//
//****************************************************************************

class CNotify
{
private:
    DWORD  m_dwCookie;
    IUnknown * m_pUnk;
    IConnectionPoint           * m_pcnp;
    IConnectionPointContainer  * m_pcnpcnt;
public:
    CNotify(void);
    ~CNotify();

    HRESULT Connect(IUnknown *pUnk, REFIID riid, IUnknown *pUnkN);
    HRESULT Disconnect(void);

    IUnknown * GetPunk() {return m_pUnk;}
};


//****************************************************************************
//
// CLASS CMgrNotify
//
//****************************************************************************

class CMgrNotify : public CRefCount, public CNotify, public INmManagerNotify
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
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void * *ppvObj);
};


//****************************************************************************
//
// CLASS CConfNotify 
//
//****************************************************************************

class CConfNotify : public CRefCount, public CNotify, public INmConferenceNotify
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
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void * *ppvObj);

    void ReleaseIMemberArray(void);
    ULONG GetIMemberCount(void) { return m_cIMembers; }
    INmMember **GetIMemberArray(void) { return &m_apIMembers[0]; }

private:

    ULONG           m_cIMembers;
    INmMember      *m_apIMembers[MAX_MEMBERS];
};


// Global Variables
extern CConfNotify * g_pConferenceNotify;

// Global Functions
HRESULT InitConfMgr(void);
void FreeConfMgr(void);
void FreeConference(void);

extern CConfNotify * g_pConferenceNotify;

#endif // _CONF_H_

