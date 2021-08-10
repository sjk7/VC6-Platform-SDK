//****************************************************************************
//  Module:     NMCHAT.EXE
//  File:       APPLET.H
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

#ifndef _APPLET_H_
#define _APPLET_H_

//****************************************************************************
//
// CLASS CApplet
//
//****************************************************************************

class CApplet : public CRefCount, public IAppletNotify
{
public:

	CApplet(IApplet *pIApplet);
	~CApplet(void);

	// IUnknown methods
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void * *ppvObj);

	// IAppletNotify
    HRESULT STDMETHODCALLTYPE PermitToJoinSessionIndication(
                    AppletConfID   nConfID,
                    BOOL           fPermissionGranted);
    HRESULT STDMETHODCALLTYPE AutoJoinSessionIndication(
                    IAppletSession    *pSession,
                    HRESULT            hrResult,
                    AppletUserID       uidMyself,
                    AppletNodeID       nidMyself,
                    AppletSessionID    sidMyself,
                    AppletEntityID     eidMyself,
                    ULONG              cDynamicChannels,
                    AppletChannelID aDynamicChannels[]);

    HRESULT Advise(void) { return m_pIApplet->Advise((IAppletNotify *) this, &m_dwCookie); }
    HRESULT UnAdvise(void) { return m_pIApplet->UnAdvise(m_dwCookie); }

private:

    IApplet            *m_pIApplet;
    DWORD               m_dwCookie;
};

extern CApplet *g_pApplet;
HRESULT InitApplet(void);
void FreeApplet(void);

#endif // _APPLET_H_

