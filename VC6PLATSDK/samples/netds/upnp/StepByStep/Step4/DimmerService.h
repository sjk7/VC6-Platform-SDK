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
	CDimmerService();
	~CDimmerService();
	 // IUPnPService_DimmingService_SCPD methods (i.e. Dimming Service Methods)
    STDMETHOD (get_Power) (VARIANT_BOOL *pval);
	STDMETHOD (get_dimLevel) (LONG *dLevel);

    STDMETHOD (PowerOn) ();
    STDMETHOD (PowerOff) ();

    STDMETHOD (GetPowerValue) (VARIANT_BOOL *powerVal);

	STDMETHOD (SetDimLevel) (LONG dLevel);
	STDMETHOD (GetDimLevel) (LONG *dLevel);
	STDMETHOD (GetConfigDetails) (VARIANT_BOOL *powerVal,LONG *dLevel);

	 // IUPnPEventSource methods
    STDMETHOD (Advise) (IUPnPEventSink *punkSubscriber);
    STDMETHOD (Unadvise) (IUPnPEventSink *punkSubscriber);

private:
    VARIANT_BOOL power;
	LONG dimnessLevel;
    IUPnPEventSink *esEventingManager;

	//to synchronise between multiple requests for the same action
    CRITICAL_SECTION csSync;
//DECLARE_REGISTRY_RESOURCEID(IDR_DIMMERSERVICE)

//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDimmerService)
	//COM_INTERFACE_ENTRY(IDimmerService)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUPnPEventSource)
	COM_INTERFACE_ENTRY(IUPnPService_DimmingService_SCPD)
END_COM_MAP()


};

#endif //__DIMMERSERVICE_H_
