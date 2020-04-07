/*+==========================================================================
  File:      UpdRec.h
  Summary:   Header for Object Pooled Update Receipt component
  Classes:   CUpdateReceipt
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

#if !defined(AFX_UPDATERECEIPT_H__A81260B9_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
#define AFX_UPDATERECEIPT_H__A81260B9_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_

#include "resource.h"       // main symbols
#include "comsvcs.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:	CUpdateReceipt
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

class CUpdateReceipt : 
	public CComDualImpl<IUpdateReceipt, &IID_IUpdateReceipt, &LIBID_ACCOUNT>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public IObjectConstruct,
	public IObjectControl,
	public CComCoClass<CUpdateReceipt,&CLSID_CUpdateReceipt>
{
private:
		CComBSTR m_sDSN;
		HENV m_henv;
		HDBC m_hdbc;
		HSTMT m_hstmt;
		BOOL m_bConstructed;
		GUID m_txuow;
		BOOL m_bShouldEnlist;
		BOOL m_bObjectPooled;
		HRESULT Enlist();

public:
	CUpdateReceipt() 
	{
		m_henv = 0;
		m_hdbc = 0;
		m_hstmt= 0;
		m_bConstructed = FALSE;
		m_txuow = GUID_NULL;
		m_bObjectPooled = FALSE;
	}

	BEGIN_COM_MAP(CUpdateReceipt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectConstruct)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IUpdateReceipt)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

void FinalRelease();


DECLARE_REGISTRY_RESOURCEID(IDR_UpdateReceipt)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUpdateReceipt

public:
	STDMETHOD (Update) (OUT long* plReceiptNo);

//IObjectConstruct
	STDMETHODIMP Construct(IDispatch * pUnk);

// IObjectControl

	STDMETHODIMP_(BOOL) CanBePooled()
	{
		return TRUE;
	}

	STDMETHODIMP Activate();

	STDMETHODIMP_(void) Deactivate()
	{		
	}
	

};

#endif // !defined(AFX_UPDATERECEIPT_H__A81260B9_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
