// DimmerService.h : Declaration of the CDimmerService

#ifndef __DIMMERSERVICE_H_
#define __DIMMERSERVICE_H_

#include "resource.h"       // main symbols
#import "C:\UPnPSample\SDKDimmer\DimmerDevice\StepByStep\Step2\Debug\upnphost.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// CDimmerService
class ATL_NO_VTABLE CDimmerService : 
	public CComObjectRootEx<CComMultiThreadModel>,
	//public CComCoClass<CDimmerService, &CLSID_DimmerService>,
	//public IDispatchImpl<IDimmerService, &IID_IDimmerService, &LIBID_MYDEVICELib>,
	public IUPnPEventSource,
    public IDispatchImpl<IUPnPService_DimmingService_SCPD, &IID_IUPnPService_DimmingService_SCPD, &LIBID_MYDEVICELib>
	//public IUPnPService_DimmingService_SCPD
{
public:
	CDimmerService()
	{
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_DIMMERSERVICE)

//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDimmerService)
	//COM_INTERFACE_ENTRY(IDimmerService)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUPnPEventSource)
	COM_INTERFACE_ENTRY(IUPnPService_DimmingService_SCPD)
END_COM_MAP()

// IDimmerService
public:
// IUPnPEventSource
	STDMETHOD(Advise)(IUPnPEventSink * pesSubscriber)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Unadvise)(IUPnPEventSink * pesSubscriber)
	{
		return E_NOTIMPL;
	}
// IUPnPService_DimmingService_SCPD
	STDMETHOD(get_Power)(VARIANT_BOOL * pPower)
	{
		if (pPower == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(get_dimLevel)(LONG * pdimLevel)
	{
		if (pdimLevel == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(PowerOn)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(PowerOff)()
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetPowerValue)(VARIANT_BOOL * ppowerVall)
	{
		if (ppowerVall == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(SetDimLevel)(LONG dLevel)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetDimLevel)(LONG * pdLevel)
	{
		if (pdLevel == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
	STDMETHOD(GetConfigDetails)(VARIANT_BOOL * ppowerVal, LONG * pdLevel)
	{
		if (ppowerVal == NULL)
			return E_POINTER;
			
		if (pdLevel == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
};

#endif //__DIMMERSERVICE_H_
