#ifndef _AgentNotifySink_h_
#define _AgentNotifySink_h_


#include "Hello2.h"


class AgentNotifySink : public IAgentNotifySinkEx {
public:
	AgentNotifySink()	: m_cRefs(0) {}
   ~AgentNotifySink()	{}

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
	STDMETHODIMP Click(long dwCharID, short fwKeys, long X, long Y);
	STDMETHODIMP DblClick(long dwCharID, short fwKeys, long X, long Y);
	STDMETHODIMP DragStart(long dwCharID, short fwKeys, long X, long Y);
	STDMETHODIMP DragComplete(long dwCharID, short fwKeys, long X, long Y);
	STDMETHODIMP RequestStart(long dwRequestID);
	STDMETHODIMP RequestComplete(long dwRequestID, long hrStatus);
	STDMETHODIMP BookMark(long dwBookMarkID);
    STDMETHODIMP Idle(long dwCharID, long bStart);
	STDMETHODIMP Move(long dwCharID, long X, long Y, long lCause);
	STDMETHODIMP Size(long dwCharID, long lWidth, long lHeight);
	STDMETHODIMP BalloonVisibleState(long dwCharID, long bVisible);

	STDMETHODIMP HelpComplete(long dwCharID, long dwCommandID, long dwCause);
	STDMETHODIMP ListeningState(long dwCharacterID, long bListenState, long dwCause);
	STDMETHODIMP DefaultCharacterChange(BSTR bszGUID);
	STDMETHODIMP AgentPropertyChange();
	STDMETHODIMP ActiveClientChange(long dwCharID, long lStatus);


private:
	ULONG	m_cRefs;
};


#endif
