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
#ifndef __METHODSUB_H__
#define __METHODSUB_H__

#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

typedef list<LONGLONG> TimeStack;
typedef map<ULONG64, TimeStack *> TimeMap;
class CComSpy;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:   CMethodSub
Summary: Method Events Subscriber 
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class ATL_NO_VTABLE CMethodSub : 
	public CSysLCESub,
	public IComMethodEvents
{
public:

	TimeMap m_map;
	CMethodSub(CComSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CMethodSub()
	{
		m_pSpy = NULL;
	}

	DECLARE_NOT_AGGREGATABLE(CMethodSub)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CMethodSub)
		COM_INTERFACE_ENTRY(IComMethodEvents)
		COM_INTERFACE_ENTRY_CHAIN(CSysLCESub)
	END_COM_MAP()

	STDMETHODIMP GetEventType(EventEnum * e){*e = Method;return S_OK;}
	STDMETHODIMP GetEventClass(LPGUID guid){*guid = CLSID_ComServiceEvents;return S_OK;}
	STDMETHODIMP GetInterface(IID* iid){*iid = IID_IComMethodEvents;return S_OK;}

	STDMETHOD(OnMethodCall)(COMSVCSEVENTINFO * pInfo, ULONG64 oid, REFCLSID cid, REFIID rid, ULONG iMeth);
	STDMETHOD(OnMethodReturn)(COMSVCSEVENTINFO * pInfo, ULONG64 oid, REFCLSID cid, REFIID rid, ULONG iMeth, HRESULT hr);
	STDMETHOD(OnMethodException)(COMSVCSEVENTINFO * pInfo, ULONG64 oid, REFCLSID cid, REFIID rid, ULONG iMeth);

	HRESULT GetClsidOfTypeLib2 (IID * piid, UUID * puuidClsid);
	HRESULT GetMethodName (REFIID riid, int iMeth, _TCHAR** ppszMethodName);

};
#endif //__METHODSUB_H__


