// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------
#include <olectl.h>
#include "DComServer.h"
#include "CEnumXXX.h"
#include "proxy.h"
#include "Debug.h"

class CEnumConnections : 
	public CEnumXXX<CEnumConnections, CONNECTDATA, IEnumConnections>
{
private:
	CEnumConnections();
	CEnumConnections(const CEnumConnections&);
	CEnumConnections& operator=(const CEnumConnections&);
	CEnumConnections* operator&();
	CEnumConnections* operator&() const;

public:
	bool __stdcall Copy(CONNECTDATA* connLeft, CONNECTDATA &connRight);
	void __stdcall FinalRelease();
	CEnumConnections(LPUNKNOWN lpUnk, DWORD nCount);
	~CEnumConnections();
};


class CEnumConnectionPoints : 
	public CEnumXXX<CEnumConnectionPoints, LPCONNECTIONPOINT, IEnumConnectionPoints>
{
private:
	CEnumConnectionPoints();
	CEnumConnectionPoints(const CEnumConnectionPoints&);
	CEnumConnectionPoints& operator=(const CEnumConnectionPoints&);
	CEnumConnectionPoints* operator&();
	CEnumConnectionPoints* operator&() const;

public:
	bool __stdcall Copy(LPCONNECTIONPOINT* lpCPLeft, LPCONNECTIONPOINT lpCPRight);
	virtual void __stdcall FinalRelease();
	CEnumConnectionPoints(LPUNKNOWN lpUnk, DWORD nCount);
	~CEnumConnectionPoints();
};

/*
 * CEnumConnectionPoints::AddRef() will call ConnectionPointContainer::AddRef() to ensure that
 * CEnumConnectionPoints::Next() is able to return valid "sinks" owned by ConnectionPointContainer
 * This is reversed in CEnumConnectionPoints::Release()
 
 * Since CConnectionPointContainer owns the interface CConnectionPoint it
 * will AddRef itself whenever it gives out this interface such as in 
 * CConnectionPointContainer::FindConnectionPoint(). The other place where
 * CConnectionPoint can be given out is in CEnumConnectionPoints::Next().
 
 *	~CConnectionPointContainer() is where the array of CConnectionPoint is
 * freed. CConnectionPoint::Release() will not free itself since it must
 * maintain a back pointer to CConnectionPointContainer in order to insure
 * that CConnectionPoint::GetConnectionPointContainer() can return the
 * CConnectionPointContainer. And CConnectionPointContainer must maintain a
 * back pointer to CConnectionPoint in order for CConnectionPointContainer::FindConnectionPoint()
 * to be able to return a valid pointer. This catch 22 means that one of these
 * interfaces must be god and own the other.
 
CHECKCHECK: NoExternalConnection is nosense

 * In CConnectionPoint::Release when the refcount drops to zero it will
 * signal this to CConnectPointContainer via NoExternalConnection. If 
 * NoExternalConnection finds CConnectionPointContainers refcount to be
 * zero then it will delete CConnectionPoint and then itself. 
 * CConnectionPoint::Release can not free itself since 
 * CConnectPointContainer holds on a array of these CConnectionPoints
 */
CConnectionPointContainer::CConnectionPointContainer() : m_cookie(0), m_cCP(0), m_prgEventIID(NULL), m_prgCP(NULL)
{
	DEBUGTRACE(_T("In CConnectionPointContainer ctor"));
}


bool __stdcall CConnectionPointContainer::Init(EventID& events)
{	
	m_cCP = events.cEventID;
	m_prgCP = new CConnectionPoint*[m_cCP];
	m_prgEventIID = new IID[m_cCP];
	for (DWORD i = 0; i < m_cCP; i++)
	{
#if 0
		LPOLESTR lpstr;
		StringFromIID(events.EventIDs[i], &lpstr);
		DEBUGTRACE(_T("passing [%S] to CConnectionPoint ctor"), lpstr);
		CoTaskMemFree(lpstr);
#endif
		CConnectionPoint *cp = new CConnectionPoint(this, events.EventIDs[i]);
		_ASSERT(cp);
		m_prgCP[i] = cp;
		m_prgEventIID[i] = events.EventIDs[i];
	}
	return true;
}

/* Since CConnectionPointContainer maintainers ownership of the CConnnectionPoint pointers rather
 * than the usual method where each class owns itself we need to explicitly delete these when
 * destroying itself
 */
CConnectionPointContainer::~CConnectionPointContainer()
{
	DEBUGTRACE(_T("In CConnectionPointContainer dtor"));
	for (DWORD i = 0; i < m_cCP; i++)
		delete m_prgCP[i];
	delete [] m_prgEventIID;
	delete [] m_prgCP;
}


/*
 * Helper function to give the COM object the ConnectionPoint for a specific IID. 
 * Typically the object would then use this connection point interface to access
 * the SignalEvent method of the connection point to notify the sink that a 
 * specific event of interest has occured.
 *
 *
 * Note the ConnectionPoint interface returned from this method can only be use 
 * for a "One" use scenario.
 *
 * i.e. cpc->GetConnectionPont(iid)->SignalEvent(...)
 * 
 * If for some reason you must keep this interface around for a length of time you
 * must addref the returned interface.
 */
CConnectionPoint* __stdcall CConnectionPointContainer::GetConnectionPoint(REFIID iid)
{
/*
 * TODO: What this code should be doing is searching through a list of supported source IID's
 */
	if (iid == IID_AppEvents)
		return m_prgCP[0];

	return NULL;
}

HRESULT __stdcall CConnectionPointContainer::EnumConnectionPoints(LPENUMCONNECTIONPOINTS *ppenum)
{
	DEBUGTRACE(_T("In IConnectionPointContainer::EnumConnectionPoints"));

	CHECKPOINTER(ppenum);
	LPCONNECTIONPOINT *elemlist = new LPCONNECTIONPOINT[m_cCP];
	for (DWORD i = 0; i < m_cCP; i++)
		elemlist[i] = m_prgCP[i]; // only a shallow copy is needed

	CEnumConnectionPoints *penum = CEnumConnectionPoints::Create(this, m_cCP, elemlist); // elemlist is now owned by CEnumConnectionPoints
	_ASSERT(penum);
	HRESULT hr = penum->QueryInterface(IID_IEnumConnectionPoints, reinterpret_cast<PVOID*>(ppenum));
	return hr;
}


HRESULT __stdcall CConnectionPointContainer::FindConnectionPoint(REFIID iid, LPCONNECTIONPOINT *ppCP)
{
	DEBUGTRACE(_T("In IConnectionPointContainer::FindConnectionPoint"));
	CHECKPOINTER(ppCP);
	
	*ppCP = NULL;
	for (DWORD i = 0; i < m_cCP; i++)
		if (m_prgEventIID[i] == iid)
		{
			*ppCP = m_prgCP[i];
			(*ppCP)->AddRef();
			return S_OK;
		}

	return CONNECT_E_NOCONNECTION;
}

	// CEnumConnectionPoints

CEnumConnectionPoints::CEnumConnectionPoints(LPUNKNOWN lpUnk, DWORD nCount) :
	CEnumXXX<CEnumConnectionPoints, LPCONNECTIONPOINT, IEnumConnectionPoints>(lpUnk, IID_IEnumConnectionPoints, nCount)
{
	DEBUGTRACE(_T("In CEnumConnectionPoints ctor"));
}


CEnumConnectionPoints::~CEnumConnectionPoints()
{
	DEBUGTRACE(_T("In CEnumConnectionPoints dtor"));
}

bool __stdcall CEnumConnectionPoints::Copy(LPCONNECTIONPOINT* lpCPLeft, LPCONNECTIONPOINT lpCPRight)
{
	DEBUGTRACE(_T("In CEnumConnectionPoints::Copy"));
	// data will have already been verified during creation no need to do so here
	*lpCPLeft = lpCPRight;
	(*lpCPLeft)->AddRef();
	return true;
}

void __stdcall CEnumConnectionPoints::FinalRelease() 
{
	DEBUGTRACE(_T("In CEnumConnectionPoints::FinalRelease()"));
	CEnumXXX<CEnumConnectionPoints, LPCONNECTIONPOINT, IEnumConnectionPoints>::FinalRelease();
}



	// CConnectionPoint
CConnectionPoint::CConnectionPoint(CConnectionPointContainer *pCPC, IID iid) : 
	m_cookie(0), m_cRef(0), m_pCPC(pCPC), m_iid(iid), m_Adviselimit(2)
{
	DEBUGTRACE(_T("In CConnectionPoint ctor"));
#if 0
	LPOLESTR lpstr;
	StringFromIID(m_iid, &lpstr);
	DEBUGTRACE(_T("[%S] was passed in to CConnectionPoint ctor"), lpstr);
	CoTaskMemFree(lpstr);
#endif
	_ASSERT(m_pCPC);
	for (DWORD i = 0; i < m_Adviselimit; i++)
		m_lpEventSink[i] = NULL;
}

CConnectionPoint::~CConnectionPoint()
{
	DEBUGTRACE(_T("In CConnectionPoint dtor"));
}
	// IUnknown
HRESULT __stdcall CConnectionPoint::QueryInterface(REFIID iid, PVOID *ppObj)
{
	CHECKPOINTER(ppObj);
	
	if (iid == IID_IUnknown || iid == IID_IConnectionPoint)
		*ppObj = this;
	else
	{
		*ppObj = NULL;
		return E_NOINTERFACE;
	}

	if (*ppObj) 
		reinterpret_cast<LPUNKNOWN>(*ppObj)->AddRef();
	
	return S_OK;
}

ULONG __stdcall CConnectionPoint::AddRef()
{
	DEBUGTRACE(_T("In IConnectionPoint::AddRef refcounts = %i"), m_cRef+1);
/*
 * Need to AddRef ConnectionPointContainer since it is what determines
 * the lifetime of CConnectionPoint interface. This will be countered 
 * CConnectionPoint::Release()
 */
	m_pCPC->AddRef();
	return InterlockedIncrement(reinterpret_cast<PLONG>(&m_cRef));
}

/* Note this class can not delete itself since CConnectionPointContainer
 * owns it. Instead what this will do is release all refcounts it added
 * on CConnectionPointContainer. These are added as a result of a 
 * container setting up an event sink in Advise and will normally be 
 * released when the container releases the sink in Unadvise. However for
 * those nasty containers which call Unadvise prior to releasing their 
 * hold on this interface will do so for them.
 */
ULONG __stdcall CConnectionPoint::Release()
{
	_ASSERT(m_cRef > 0); // not thread safe
	DEBUGTRACE(_T("In IConnectionPoint::Release refcounts = %i"), m_cRef-1);

	if (InterlockedDecrement(reinterpret_cast<PLONG>(&m_cRef)) == 0)
	{
		FinalRelease();
		return 0;
	}
	m_pCPC->Release();	// Release strong lock added in by the AddRef()
	return m_cRef;
}

void __stdcall CConnectionPoint::FinalRelease()
{
#if 0 // HACK till I get the list for sinks interfaces
	_ASSERT(m_cookie == 0);
#endif
	m_pCPC->Release();	// Release strong lock added in by the AddRef()
}

/*
 *
 * Helper function used by the object which defined the source to notify the sink that
 * an event has occurred. The source needs to provide the IID of the source, the DISPID 
 * to fire and the DISPARAMS to pass to the sink
 *
 */
#if 0
bool __stdcall CConnectionPoint::SignalEvent(DISPID dispid, DISPPARAMS* params)
{
/*
 * TODO:
 * 1) Verify the DISPID (optional?)
 * 2) Run through the table of connections sinks calling calling each of them
 */
	_ASSERT(params);
	if (m_cookie == 0) // No sink has been set up
		return false;

	HRESULT hr;

	for (DWORD i = 0; i < m_cookie; i++)
		hr = m_lpEventSink[i]->Invoke(dispid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD,
			params, NULL, NULL, NULL);

	return SUCCEEDED(hr) ? true : false;
}
#endif


/*
 *
 * SignalEvent is a very limited simple example of how to use COM "automatic completion" to achieve asynchronous events. 
 * In other words the caller of event does not have to what till the callee has finished processing the event. This 
 * allows the caller to fire off events to multiple calles without blocking. Unlike sychronous COM interfaces there is 
 * no guarentee that a method call will reach the callee. 
 *
 * As a consequence of recycling the Call factory, events which have [out] parameters are not valid.
 *
 * Note that the event interface is _not_ a dispinterface. The reason for this madness is that type library marshaling is not
 * supported in NT 5. This will also mean each "sink" will need to at least trivally implement all events on an interface
 *
 */
bool __stdcall CConnectionPoint::SignalEvent()
{
	if (m_cookie == 0) // No sink has been set up
		return false;

	HRESULT hr;
	LPCALLFACTORY pCallF = NULL;
	AsyncAppEvents*  pAsyncTest = NULL;
	LPSYNCHRONIZE pSync = NULL;

	for (DWORD i = 0; i < m_cookie; i++)
	{
		hr = m_lpEventSink[i]->QueryInterface(IID_ICallFactory, (PVOID*)&pCallF);
		_ASSERT(SUCCEEDED(hr) && pCallF);
		hr = pCallF->CreateCall(IID_AsyncAppEvents, NULL, IID_AsyncAppEvents, (LPUNKNOWN*)&pAsyncTest);
		_ASSERT(SUCCEEDED(hr) && pAsyncTest);
		hr = pAsyncTest->Begin_Beep(~0);
		RELEASEINTERFACE(pAsyncTest);
		RELEASEINTERFACE(pCallF);
	}
	
	return SUCCEEDED(hr) ? true : false;
}

	// IConnectionPoint
HRESULT __stdcall CConnectionPoint::GetConnectionInterface(IID *pIID)
{
	DEBUGTRACE(_T("In IConnectionPoint::GetConnectionInterface"));
	CHECKPOINTER(pIID);
	
	*pIID = m_iid;
	return S_OK;
}

HRESULT __stdcall CConnectionPoint::GetConnectionPointContainer(LPCONNECTIONPOINTCONTAINER *ppCPC)
{
	DEBUGTRACE(_T("In IConnectionPoint::GetConnectionPointContainer"));
	CHECKPOINTER(ppCPC);
	
	HRESULT hr = m_pCPC->QueryInterface(IID_IConnectionPointContainer, reinterpret_cast<PVOID*>(ppCPC));
	return hr;
}

/*
 * Note lpUnk is a _in_ parameter this interface will automatically be freed upon exit
 */
HRESULT __stdcall CConnectionPoint::Advise(LPUNKNOWN lpUnk, LPDWORD pdwCookie)
{

	DEBUGTRACE(_T("In IConnectionPoint::Advise"));
	CHECKPOINTER(pdwCookie && lpUnk);

	if (m_cookie >= m_Adviselimit)
		return CONNECT_E_ADVISELIMIT;

	HRESULT hr =lpUnk->QueryInterface(m_iid, reinterpret_cast<PVOID*>(&m_lpEventSink[m_cookie]));
	if (FAILED(hr))
		return hr == E_NOINTERFACE ? CONNECT_E_CANNOTCONNECT : hr;

	// TODO Add to connection to list 
	*pdwCookie = m_cookie++; // Running count of # of event sinks
	return S_OK;
}

HRESULT __stdcall CConnectionPoint::Unadvise(DWORD dwCookie)
{
	DEBUGTRACE(_T("In IConnectionPoint::Unadvise"));

	// TODO Remove from list. If cookie does not match return E_UNEXPEC; otherwise do ...
	// decrement # of event sinks attached to the list

	RELEASEINTERFACE(m_lpEventSink[dwCookie]);
	return S_OK;
}

HRESULT __stdcall CConnectionPoint::EnumConnections(LPENUMCONNECTIONS *ppenum)
{
	DEBUGTRACE(_T("In IConnectionPoint::EnumConnections"));
	CHECKPOINTER(ppenum);

	CONNECTDATA* elemlist = new CONNECTDATA[m_cookie]; // m_cookie is running total of connections to this ConnectionPoint
	for (DWORD i = 0; i < m_cookie; i++)
	{
		elemlist[i].dwCookie = i;
		elemlist[i].pUnk = m_lpEventSink[i];
	}
	
	CEnumConnections *penum = CEnumConnections::Create(this, m_cookie, elemlist);
	HRESULT hr = penum->QueryInterface(IID_IEnumConnections, reinterpret_cast<PVOID*>(ppenum));
	return hr;
}


	// CEnumConnections
CEnumConnections::CEnumConnections(LPUNKNOWN lpUnk, DWORD nCount) :
	CEnumXXX<CEnumConnections, CONNECTDATA, IEnumConnections>(lpUnk, IID_IEnumConnections, nCount)

{
	DEBUGTRACE(_T("In CEnumConnections ctor"));
}

CEnumConnections::~CEnumConnections()
{
	DEBUGTRACE(_T("In CEnumConnections dtor"));
}

bool __stdcall CEnumConnections::Copy(CONNECTDATA* connLeft, CONNECTDATA& connRight)
{
	DEBUGTRACE(_T("In CEnumConnections::Copy"));
	// data will have already been verified during creation no need to do so here
	*connLeft = connRight;
	(*connLeft).pUnk->AddRef();
	return true;
}

void __stdcall CEnumConnections::FinalRelease()
{
	DEBUGTRACE(_T("In CEnumConnections::FinalRelease()"));
	CEnumXXX<CEnumConnections, CONNECTDATA, IEnumConnections>::FinalRelease();
}

