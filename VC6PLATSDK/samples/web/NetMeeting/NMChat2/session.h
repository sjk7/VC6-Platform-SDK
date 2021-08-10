//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       SESSION.H
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

#ifndef _SESSION_H_
#define _SESSION_H_


//****************************************************************************
//
// CLASS CAppletSession
//
//****************************************************************************

class CAppletSession : public CRefCount, public IAppletSessionNotify
{
public:

	CAppletSession(CApplet *pApplet, IAppletSession *pISession);
	~CAppletSession(void);

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void * *ppvObj);

	// IAppletSessionNotify
    HRESULT STDMETHODCALLTYPE JoinSessionConfirm(
                    HRESULT            hrResult,
                    AppletUserID       uidMyself,
                    AppletNodeID       nidMyself,
                    AppletSessionID    sidMyself,
                    AppletEntityID     eidMyself,
                    ULONG              cDynamicChannels,
                    AppletChannelID aDynamicChannels[]);

    HRESULT STDMETHODCALLTYPE LeaveSessionIndication(
                    AppletReason   eReason,
                    AppletUserID   uidLeave);

    HRESULT STDMETHODCALLTYPE SendDataIndication(
                    BOOL               fUniformSend,
                    AppletUserID       uidInitiator,
                    AppletChannelID    nChannelID,
                    AppletPriority     eDataPriority,
                    AppletOctetString  Data);

    HRESULT STDMETHODCALLTYPE RosterReportIndication(
                    ULONG              cRosters,
                    AppletRoster **apAppRosters);

    HRESULT STDMETHODCALLTYPE InquireRosterConfirm(
                    HRESULT            hrResult,
                    ULONG              cRosters,
                    AppletRoster **apAppRosters);

    HRESULT STDMETHODCALLTYPE InvokeAppletConfirm(
                    AppletRequestTag   nReqTag,
                    HRESULT            hrResult);

    HRESULT STDMETHODCALLTYPE RegistryConfirm(
                    AppletRegistryCommand      eCommand,
                    HRESULT                    hrResult,
                    AppletRegistryKey         *pRegistryKey,
                    AppletRegistryItem        *pRegistryItem,
                    AppletRegistryEntryOwner  *pEntryOwner,
                    AppletModificationRights   eRights);

    HRESULT STDMETHODCALLTYPE AllocateHandleConfirm(
                    HRESULT                hrResult,
                    ULONG                  nFirstHandle,
                    ULONG                  cHandles);

    HRESULT STDMETHODCALLTYPE ChannelConfirm(
                    AppletChannelCommand   eCommand,
                    HRESULT                hrResult,
                    AppletChannelID        nChannelID);

    HRESULT STDMETHODCALLTYPE ChannelIndication(
                    AppletChannelCommand   eCommand,
                    AppletChannelID        nChannelID,
                    AppletReason           eReason,
                    AppletUserID           uidManager);

    HRESULT STDMETHODCALLTYPE TokenConfirm(
                    AppletTokenCommand     eCommand,
                    HRESULT                hrResult,
                    AppletTokenID          nTokenID);

    HRESULT STDMETHODCALLTYPE TestTokenConfirm(
                    AppletTokenID          nTokenID,
                    AppletTokenStatus      eStatus);

    HRESULT STDMETHODCALLTYPE TokenIndication(
                    AppletTokenCommand     eCommand,
                    AppletReason           eReason,
                    AppletTokenID          nTokenID,
                    AppletUserID           uidInitiator);

    AppletConfID    GetConfID(void) { return m_nConfID; }
    HRESULT         Join(void) { return m_pISession->Join(&m_JoinSessionReq); }
    HRESULT         Leave(void) { ::UiRemoveMember(NULL); return m_pISession->Leave(); }
    HRESULT         Advise(void) { return m_pISession->Advise((IAppletSessionNotify *) this, &m_dwCookie); }
    HRESULT         UnAdvise(void) { return m_pISession->UnAdvise(m_dwCookie); }
    HRESULT         SendData(AppletChannelID, ULONG cbBufSize, BYTE *pBuffer);

    void SetMember(INmMember *pIMember);
    void RemoveMember(INmMember *);

    HRESULT InvokeApplet(void);

private:

    void BuildJoinSessionStructure(void);
    void SetMember(AppletRecord *);
    LPTSTR GetMemberName(AppletUserID uid);

private:

    CApplet                *m_pApplet;
    IAppletSession         *m_pISession; 
    DWORD                   m_dwCookie;
    AppletConfID            m_nConfID;
    AppletUserID            m_uidMyself;
    AppletNodeID            m_nidMyself;
    AppletSessionID         m_sidMyself;
    AppletEntityID          m_eidMyself;
    LPSTR                   m_pszMyName;
    AppletChannelID         m_nDynamicMulticastChannel;
    BOOL                    m_fTopProvider;

    ULONG                   m_cMembers;
    CMember                *m_apMembers[MAX_MEMBERS];

    // space to hold the join session request
    AppletSessionRequest    m_JoinSessionReq;
    AppletRegistryKey       m_DynChnlRegKey;
};


class CMember
{
public:

    CMember(INmMember *);
    CMember(AppletRecord *);
    ~CMember(void);

    void SetMember(INmMember *, BOOL fFirstTime = FALSE);
    void SetMember(AppletRecord *, BOOL fFirstTime = FALSE);

    BOOL IsSameUID(AppletUserID uid) { return (uid == m_uidMember); }
    BOOL IsEmptyUID(void) { return (0 == m_uidMember); }

    BOOL IsSameMemberID(AppletNodeID nid) { return (nid == m_nidMember); }
    BOOL IsEmptyMember(void) { return (NULL == m_pszMemberName); }

    LPTSTR GetName(void) { return m_pszMemberName; }

    AppletUserID GetUID(void) { return m_uidMember; }

    BOOL IsInRoster(void) { return m_fInRoster; }
    void SetInRosterFlag(void) { m_fInRoster = TRUE; }
    void ClearInRosterFlag(void) { m_fInRoster = FALSE; }

private:

    void Initialize(void);

private:

    BOOL            m_fInRoster;
    LPTSTR          m_pszMemberName;
    AppletNodeID    m_nidMember;
    AppletUserID    m_uidMember;
    AppletEntityID  m_eidMember;
};



extern CAppletSession *g_pSession;

HRESULT RegisterStandardAppletInvokeInfo(AppletLongString *pKey);
HRESULT RegisterNonStandardAppletInvokeInfo(void);


typedef struct
{
    BOOL                fValid;
    AppletConfID        nConfID;
    AppletNodeID        nidInitiator;
}
    INVOKE_INFO;

BOOL GetInvokeInfo(INVOKE_INFO *);

extern INVOKE_INFO g_InvokeInfo;

#endif // _SESSION_H_

