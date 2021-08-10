#ifndef _Notify_h_
#define _Notify_h_


#include "AgtSvr.h"

class MainDlg;


// Agent Notify Sink Implementation

class AgentNotifySink : public IAgentNotifySinkEx {
public:
	AgentNotifySink(MainDlg *pMainDlg) : m_cRefs(0), m_pMainDlg(pMainDlg) {}
   ~AgentNotifySink() {}

    STDMETHODIMP QueryInterface(REFIID, LPVOID FAR *);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

	STDMETHODIMP GetTypeInfoCount(UINT *);
	STDMETHODIMP GetTypeInfo(UINT, LCID, ITypeInfo **);
	STDMETHODIMP GetIDsOfNames(REFIID, OLECHAR **, UINT, LCID, DISPID *);
	STDMETHODIMP Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);

    STDMETHODIMP Command(long dwCommandID, IUnknown * punkUserInput);
    STDMETHODIMP ActivateInputState(long dwCharID, long bActivated);
    STDMETHODIMP Restart();
    STDMETHODIMP Shutdown();
    STDMETHODIMP VisibleState(long dwCharID, long bVisible, long lCause);
	STDMETHODIMP Click(long dwCharID, short fwKeys, long x, long y);
	STDMETHODIMP DblClick(long dwCharID, short fwKeys, long x, long y);
	STDMETHODIMP DragStart(long dwCharID, short fwKeys, long x, long y);
	STDMETHODIMP DragComplete(long dwCharID, short fwKeys, long x, long y);
	STDMETHODIMP RequestStart(long dwRequestID);
	STDMETHODIMP RequestComplete(long dwRequestID, long hrStatus);
	STDMETHODIMP BookMark(long dwBookMarkID);
    STDMETHODIMP Idle(long dwCharID, long bStart);
	STDMETHODIMP Move(long dwCharID, long x, long y, long lCause);
	STDMETHODIMP Size(long dwCharID, long lWidth, long lHeight);
	STDMETHODIMP BalloonVisibleState(long dwCharID, long bVisible);

	STDMETHODIMP HelpComplete(long dwCharID, long dwCommandID, long dwCause);
	STDMETHODIMP ListeningState(long dwCharID, long bListening, long dwCause);
	STDMETHODIMP Suspend();
	STDMETHODIMP DefaultCharacterChange(BSTR bszGUID);
	STDMETHODIMP AgentPropertyChange();
	STDMETHODIMP ActiveClientChange(long dwCharID, long bActive);

private:
	ULONG		 m_cRefs;
	MainDlg		*m_pMainDlg;
};


#endif
