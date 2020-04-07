// ByotTransObj.h : Declaration of the CByotTransObj

#ifndef __BYOTTRANSOBJ_H_
#define __BYOTTRANSOBJ_H_

#include "resource.h"       // main symbols

extern CRITICAL_SECTION g_cs;

/////////////////////////////////////////////////////////////////////////////
// CByotTransObj
class ATL_NO_VTABLE CByotTransObj : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CByotTransObj, &CLSID_ByotTransObj>,
	public ISupportErrorInfo,
	public IDispatchImpl<IByotTransaction, &IID_IByotTransaction, &LIBID_BYOTTRANSACTIONLib>
{
public:
	CByotTransObj()
	{
	}


DECLARE_REGISTRY_RESOURCEID(IDR_BYOTTRANSOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CByotTransObj)
	COM_INTERFACE_ENTRY(IByotTransaction)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IByotTransaction
public:
	STDMETHOD(get_TipURL)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(AbortTransaction)();
	STDMETHOD(CommitTransaction)();
	STDMETHOD(BeginTransaction)();

protected:

};

#endif //__BYOTTRANSOBJ_H_
