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
#ifndef __EXCEPTIONSUB_H__
#define __EXCEPTIONSUB_H__

#include "resource.h"       // main symbols

CComBSTR GuidToBstr(REFGUID guid);

class CComSpy;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:   CExceptionSub
Summary: Exception Event Subscriber 
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class ATL_NO_VTABLE CExceptionSub : 
	public CSysLCESub,
	public IComExceptionEvents
{
public:
	CExceptionSub(CComSpy * pSpy)
	{
		m_pSpy = pSpy;
	}

	CExceptionSub()
	{
		m_pSpy = NULL;
	}

	DECLARE_NOT_AGGREGATABLE(CExceptionSub)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CExceptionSub)
		COM_INTERFACE_ENTRY(IComExceptionEvents)
		COM_INTERFACE_ENTRY_CHAIN(CSysLCESub)
	END_COM_MAP()

	STDMETHODIMP GetEventType(EventEnum * e){*e = Exception;return S_OK;}
	STDMETHODIMP GetEventClass(LPGUID guid){*guid = CLSID_ComServiceEvents;return S_OK;}
	STDMETHODIMP GetInterface(IID* iid){*iid = IID_IComExceptionEvents;return S_OK;}

	STDMETHODIMP OnExceptionUser(
							 COMSVCSEVENTINFO * pInfo,
							 ULONG code,
							 ULONG64 addr,
							 LPCOLESTR pszStackTrace
							)
	{	
		m_pSpy -> AddEventToList(pInfo->perfCount, _TEXT("OnExceptionUser"), GuidToBstr(pInfo->guidApp));

		WCHAR szCode[16];
		wsprintfW(szCode, L"0x%08X", code);
		m_pSpy -> AddParamValueToList(L"code", szCode);

		WCHAR szAddress[32];
		wsprintfW(szAddress, L"0x%016X", addr);
		m_pSpy -> AddParamValueToList(L"Address", szAddress);

		m_pSpy -> AddParamValueToList(L"StackTrace", pszStackTrace);
		return S_OK;


		IF_AUDIT_DO(OnExceptionUser)(pInfo->perfCount,GuidToBstr(pInfo->guidApp),														
									  szCode,
									  szAddress,
									  pszStackTrace
									  );	
	}

};

#endif //__EXCEPTIONSUB_H__
