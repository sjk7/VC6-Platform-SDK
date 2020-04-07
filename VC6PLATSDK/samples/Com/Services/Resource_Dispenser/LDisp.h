	
// LDisp.h : Declaration of the CLDisp

#ifndef __LDISP_H_
#define __LDISP_H_

#include "resource.h"       // main symbols
#include <mtxdm.h>

/////////////////////////////////////////////////////////////////////////////
// CLDisp
class ATL_NO_VTABLE CLDisp : 
	public IDispenserDriver,
	public CComObjectRootEx<CComMultiThreadModel>,  //Should be multi-threaded.
	public CComCoClass<CLDisp, &CLSID_LDisp>,
	public ILDisp
{
private:
	IHolder * m_pHolder; 
	IDispenserManager* m_pDispMan;
	CComAutoCriticalSection m_cs;




public:
		DECLARE_PROTECT_FINAL_CONSTRUCT();
			DECLARE_CLASSFACTORY_SINGLETON(CLDisp);

	CLDisp()
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LDISP)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CLDisp)
	COM_INTERFACE_ENTRY(ILDisp)
	COM_INTERFACE_ENTRY(IDispenserDriver)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

	HRESULT FinalConstruct()
	{
		//Get a pointer to the dispenser manager, and register
		//this dispenser with it.
		HRESULT hr;
		hr = GetDispenserManager(&m_pDispMan);
		IDispenserDriver * pDriver;
		hr = GetUnknown()->QueryInterface(IID_IDispenserDriver, (void **)&pDriver);
		hr = m_pDispMan->RegisterDispenser(pDriver,L"LDispenser", &m_pHolder);

		//aggregate the free threaded marshaler.
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
	}

	void FinalRelease()
	{
		//de-aggregate the free threaded marshaller
		m_pUnkMarshaler.Release();
	}

	CComPtr<IUnknown> m_pUnkMarshaler;

// ILDisp
public:
	STDMETHOD(DeAlloc)(/*[in]*/long JAustin);
	STDMETHOD(Alloc)(/*[in,out]*/ long * pJAustin);

//IDispenserDriver
public:
	STDMETHOD(CreateResource)(const RESTYPID ResTypId,
									RESID * pResId,
									TIMEINSECS* SecsFreeBeforeDestroy);
	STDMETHOD(RateResource)(const RESTYPID ResTypId,
							const RESID ResId,
								const BOOL fRequiresTransactionEnlistment,
								RESOURCERATING* pRating);
	STDMETHOD(EnlistResource)(const RESID ResId, const TRANSID TransId);
	STDMETHOD(ResetResource)(const RESID ResId);
	STDMETHOD(DestroyResource)(const RESID ResId);
	STDMETHOD(DestroyResourceS)(constSRESID ResId);
};

#endif //__LDISP_H_
