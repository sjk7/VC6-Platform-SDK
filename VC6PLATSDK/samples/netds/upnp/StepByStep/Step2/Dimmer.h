// Dimmer.h : Declaration of the CDimmer

#ifndef __DIMMER_H_
#define __DIMMER_H_

#include "resource.h"       // main symbols
#import "C:\UPnPSample\SDKDimmer\DimmerDevice\StepByStep\Step2\Debug\upnphost.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// CDimmer
class ATL_NO_VTABLE CDimmer : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDimmer, &CLSID_Dimmer>,
	public IDispatchImpl<IDimmer, &IID_IDimmer, &LIBID_MYDEVICELib>,
	public IUPnPDeviceControl
{
public:
	CDimmer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DIMMER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDimmer)
	COM_INTERFACE_ENTRY(IDimmer)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUPnPDeviceControl)
END_COM_MAP()

// IDimmer
public:
// IUPnPDeviceControl
	STDMETHOD(Initialize)(BSTR bstrXMLDesc, BSTR bstrDeviceIdentifier, BSTR bstrInitString)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetServiceObject)(BSTR bstrUDN, BSTR bstrServiceId, IDispatch * * ppdispService)
	{
		if (ppdispService == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
};

#endif //__DIMMER_H_
