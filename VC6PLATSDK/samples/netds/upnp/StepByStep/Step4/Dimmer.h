// Dimmer.h : Declaration of the CDimmer

#ifndef __DIMMER_H_
#define __DIMMER_H_

#include "resource.h"       // main symbols
#import "C:\UPnPSample\SDKDimmer\DimmerDevice\StepByStep\Step2\Debug\upnphost.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#define NUM_TEMPLATE_UDNS_IN_DESCDOC 1	//This is equal to the number of devices (root or embedded) in the description doc
#define MAX_NOSERVICE_PER_DEVICE 1		//This  is equal to the maximum number of services in any device in the description doc

/////////////////////////////////////////////////////////////////////////////
// CDimmer
class ATL_NO_VTABLE CDimmer : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CDimmer, &CLSID_Dimmer>,
	//public IDispatchImpl<IDimmer, &IID_IDimmer, &LIBID_MYDEVICELib>,
	public IUPnPDeviceControl
{
private:
	//variables used internally are declared

	// String that stores the description doc that is passed by the Device Host during Intialize
	BSTR descriptionDoc;

	//table to hold mapping from template UDN's to the UDN's actually used by the DeviceHost when publishing the device
	BSTR UDNmapping[NUM_TEMPLATE_UDNS_IN_DESCDOC][2];

	//now for each of the Template UDN's we maintain a list of services in it and the IDispatch interface pointers
	//the serviceIDDeviceMap table maps between devices (root or embedded) and the service Id's in the device
	BSTR serviceIDDeviceMap[NUM_TEMPLATE_UDNS_IN_DESCDOC][MAX_NOSERVICE_PER_DEVICE];

	//this table maps between the services in the device (root or embedded) and the IDispatch pointers
	IDispatch* pDisPtrs[NUM_TEMPLATE_UDNS_IN_DESCDOC][MAX_NOSERVICE_PER_DEVICE];
 

public:
	CDimmer();
	~CDimmer();
	STDMETHODIMP CDimmer::Initialize(BSTR bstrXMLDesc,BSTR deviceID,BSTR bstrInitString);
	STDMETHODIMP CDimmer::GetServiceObject(BSTR bstrUDN,BSTR bstrServiceId,IDispatch **ppdispService);

DECLARE_REGISTRY_RESOURCEID(IDR_DIMMER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDimmer)
	//COM_INTERFACE_ENTRY(IDimmer)
	//COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUPnPDeviceControl)
END_COM_MAP()

};

#endif //__DIMMER_H_
