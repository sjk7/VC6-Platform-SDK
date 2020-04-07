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
#if !defined(__CCONNECTIONPOINT__)
#define __CCONNECTIONPOINT__

#include <objidl.h>
#include <ocidl.h>

typedef struct EventID {
	DWORD cEventID;
	const IID*  EventIDs;
} *LPEVENTID;

class CConnectionPoint;

class CConnectionPointContainer : public IConnectionPointContainer
{
protected:
	CConnectionPointContainer();
	virtual ~CConnectionPointContainer();
private:
	// IConnectionPointContainer
	virtual HRESULT __stdcall EnumConnectionPoints(LPENUMCONNECTIONPOINTS *ppenum);
	virtual HRESULT __stdcall FindConnectionPoint(REFIID id, LPCONNECTIONPOINT *ppCP);

public:
	CConnectionPoint* __stdcall GetConnectionPoint(REFIID iid);
	bool __stdcall Init(EventID& events);
private:
	// state variables
	DWORD m_cookie;
	DWORD m_cCP;
	CConnectionPoint** m_prgCP;
	IID* m_prgEventIID;
};

class CConnectionPoint : public IConnectionPoint
{
public:
	CConnectionPoint(CConnectionPointContainer *pCPC, IID iid);
	virtual ~CConnectionPoint();


	// IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, PVOID *ppv);
    virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
	virtual void __stdcall FinalRelease();

private:
	virtual HRESULT __stdcall GetConnectionInterface(IID *pIID);
	virtual HRESULT __stdcall GetConnectionPointContainer(LPCONNECTIONPOINTCONTAINER *ppCPC);
	virtual HRESULT __stdcall Advise(LPUNKNOWN lpUnk, LPDWORD pdwCookie);
	virtual HRESULT __stdcall Unadvise(DWORD dwCookie);
	virtual HRESULT __stdcall EnumConnections(LPENUMCONNECTIONS *ppenum);

public:
	bool __stdcall SignalEvent(DISPID dispid, DISPPARAMS *params);
	bool __stdcall SignalEvent();
private:	
	// state variables
	ULONG  m_cRef;
	DWORD  m_cookie;
	IID m_iid;
	const DWORD m_Adviselimit;
/*
 * hackhack: I currently only let two sinks attach to this connectionpoint.
 * I need to set up some type of list to hold an arbritary # of sinks
 */

//	LPDISPATCH m_lpEventSink[2];
	AppEvents* m_lpEventSink[2]; //hackhack

	CConnectionPointContainer* m_pCPC;
};
#endif // __CCONNECTIONPOINT__
