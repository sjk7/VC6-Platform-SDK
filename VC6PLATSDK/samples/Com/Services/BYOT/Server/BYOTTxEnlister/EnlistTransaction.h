// EnlistTransaction.h : Declaration of the CEnlistTransaction

#ifndef __ENLISTTRANSACTION_H_
#define __ENLISTTRANSACTION_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEnlistTransaction
class ATL_NO_VTABLE CEnlistTransaction : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CEnlistTransaction, &CLSID_EnlistTransaction>,
	public ISupportErrorInfo,
	public IDispatchImpl<IEnlistTransaction, &IID_IEnlistTransaction, &LIBID_TXENLISTERLib>
{
public:
	CEnlistTransaction()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ENLISTTRANSACTION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEnlistTransaction)
	COM_INTERFACE_ENTRY(IEnlistTransaction)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IEnlistTransaction
public:
	STDMETHOD(CreateInstance)(/*[in]*/ BSTR bstrProgId, /*[out]*/ IDispatch** ppDispatch);
	STDMETHOD(EnlistTransaction)(/*[in]*/ BSTR bstrTipUrl);

protected:

	CComBSTR m_bstrTipUrl;
};

#endif //__ENLISTTRANSACTION_H_
