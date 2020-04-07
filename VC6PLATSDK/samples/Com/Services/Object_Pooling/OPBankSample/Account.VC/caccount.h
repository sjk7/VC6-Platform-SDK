/*+==========================================================================
  File:      CAccount.h
  Summary:   Header for Object Pooled Account component
  Classes:   CAccount
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

#include "resource.h"       // main symbols
#include <comsvcs.h>

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:	CAccount
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

interface IObjectContext;

class CAccount : 
	public CComDualImpl<IAccount, &IID_IAccount, &LIBID_ACCOUNT>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public IObjectConstruct,
	public IObjectControl, 
	public CComCoClass<CAccount,&CLSID_CAccount>
{
private:

	HENV m_henv;
	HDBC m_hdbc;
	HSTMT m_hstmt;
	CComBSTR m_sDSN;
	BOOL m_bConstructed;
	BOOL m_bShouldEnlist;
	GUID m_txuow;
	BOOL m_bObjectPooled;
public:
	CAccount() 
	{
		m_henv = 0;
		m_hdbc = 0;
		m_hstmt= 0;
		m_bConstructed = FALSE;
		m_bShouldEnlist = FALSE;
		m_txuow = GUID_NULL;
		m_bObjectPooled = FALSE;
	}
	~CAccount()
	{
	}

	HRESULT Enlist();

	void FinalRelease();

	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_PROTECT_FINAL_CONSTRUCT( )

BEGIN_COM_MAP(CAccount)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAccount)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IObjectConstruct)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

HRESULT FinalConstruct()
{	
	return S_OK;
}
DECLARE_REGISTRY_RESOURCEID(IDR_Account)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAccount
public:
	HRESULT DoWork(long lAccount, long lAmount, BSTR *pbstrResult);
	STDMETHOD(Post)(
		IN long lAccount,
		IN long lAmount,
		OUT BSTR* pbstrResult);
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
		// nothing to do
	}
	
};
