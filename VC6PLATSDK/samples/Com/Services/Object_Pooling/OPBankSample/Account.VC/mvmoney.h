/*+==========================================================================
  File:      mvmoney.h
  Summary:   Header for Move Money component
  Classes:   CMoveMoney
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


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:	CMoveMoney
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

class CMoveMoney : 
	public CComDualImpl<IMoveMoney, &IID_IMoveMoney, &LIBID_ACCOUNT>, 
	public CComDualImpl<IMoveMoneyOptions, &IID_IMoveMoney, &LIBID_ACCOUNT>, 
	public ISupportErrorInfo,
	public CComObjectRoot,	
	public CComCoClass<CMoveMoney,&CLSID_CMoveMoney>
{

private:

		DWORD m_clsctxAccount;
		BOOL m_bUseComPlus;

public:
	CMoveMoney() 
	{
		m_clsctxAccount = CLSCTX_ALL;
		m_bUseComPlus = FALSE;
	
	}
BEGIN_COM_MAP(CMoveMoney)
	COM_INTERFACE_ENTRY2(IDispatch, IMoveMoney)
	COM_INTERFACE_ENTRY(IMoveMoney)
	COM_INTERFACE_ENTRY(IMoveMoneyOptions)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT( )
HRESULT FinalConstruct()
{
	return S_OK;
}

DECLARE_REGISTRY_RESOURCEID(IDR_MoveMoney)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMoveMoney
public:
	STDMETHOD(Perform)(
		IN long lPrimeAccount,
		IN long lSecondAccount,
		IN long lAmount,
		IN long lTranType,
		OUT BSTR* pbstrResult);

	STDMETHODIMP SetAccountClsctx(long clsctx)
	{
		m_clsctxAccount = clsctx;
		return S_OK;
	}

	STDMETHODIMP UseComPlus()
	{
		m_bUseComPlus = TRUE;
		return S_OK;
	}
};
