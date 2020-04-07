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
#ifndef __TXSUB_H_
#define __TXSUB_H_

#include "resource.h"       // main symbols

class CComSpy;

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:   CTxSub
Summary: Transaction Events Subscriber 
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
class ATL_NO_VTABLE CTxSub : 
	public CSysLCESub,
	public IComTransactionEvents
{
public:

	CTxSub(CComSpy * pSpy)
	{
		m_pSpy = pSpy;
	}
	CTxSub()
	{
		m_pSpy = NULL;
	}

	DECLARE_NOT_AGGREGATABLE(CTxSub)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(CTxSub)
		COM_INTERFACE_ENTRY(IComTransactionEvents)
		COM_INTERFACE_ENTRY_CHAIN(CSysLCESub)
	END_COM_MAP()

	STDMETHODIMP GetEventType(EventEnum * e){*e = Transaction;return S_OK;}
	STDMETHODIMP GetEventClass(LPGUID guid){*guid = CLSID_ComServiceEvents;return S_OK;}
	STDMETHODIMP GetInterface(IID* iid){*iid = IID_IComTransactionEvents;return S_OK;}

public:
	STDMETHOD (OnTransactionStart)(COMSVCSEVENTINFO * pInfo, REFGUID guidTx, REFGUID tsid, BOOL bRoot);
	STDMETHOD (OnTransactionPrepare)(COMSVCSEVENTINFO * pInfo, REFGUID guidTx, BOOL bVoteYes);
	STDMETHOD (OnTransactionAbort)(COMSVCSEVENTINFO * pInfo, REFGUID guidTx);
	STDMETHOD (OnTransactionCommit)(COMSVCSEVENTINFO * pInfo, REFGUID guidTx);


};

#endif //__TXSUB_H_
