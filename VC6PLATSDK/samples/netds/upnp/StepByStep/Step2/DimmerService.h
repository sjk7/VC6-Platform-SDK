// DimmerService.h : Declaration of the CDimmerService

#ifndef __DIMMERSERVICE_H_
#define __DIMMERSERVICE_H_

#include "resource.h"       // main symbols
#import "C:\UPnPSample\SDKDimmer\DimmerDevice\StepByStep\Step2\Debug\upnphost.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

/////////////////////////////////////////////////////////////////////////////
// CDimmerService
class ATL_NO_VTABLE CDimmerService : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDimmerService, &CLSID_DimmerService>,
	public IDispatchImpl<IDimmerService, &IID_IDimmerService, &LIBID_MYDEVICELib>,
	public IUPnPEventSource
{
public:
	CDimmerService()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DIMMERSERVICE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDimmerService)
	COM_INTERFACE_ENTRY(IDimmerService)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUPnPEventSource)
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
};

#endif //__DIMMERSERVICE_H_
