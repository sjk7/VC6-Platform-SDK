// Dimmer.cpp : Implementation of CDimmer
#include "stdafx.h"
#include "MyDevice.h"
#include "Dimmer.h"
#include "DimmerService.h"

/////////////////////////////////////////////////////////////////////////////
//  CDimmer : Implementation
////////////////////////////////////////////////////////////////////////////
 CDimmer:: CDimmer()
{
	//initialise variables
	INT i,j;

	//initialise the table mapping the template UDN's to the UDN's used by the device host.
	//there is only one entry in this table since the device has only a RootDevice and no embedded devices
	UDNmapping[0][0] = SysAllocString(L"RootDevice");
	UDNmapping[0][1] =NULL;


	//initialise the table mapping between the devices and the services ID's of the services it hosts
	//i.e. Row 0 contains services IDs for the RootDevice and Row1 for embedded device 1 if present etc.
	//The sample device just has a Rootdevice and no embedded devices
	serviceIDDeviceMap[0][0] = SysAllocString(L"upnp:id:DimmerService1.0");

	//the array pDisPtrs holds the IDispatch Interface pointers for the services supported by the device
	for(i=0;i<NUM_TEMPLATE_UDNS_IN_DESCDOC;i++)
		for(j=0;j<MAX_NOSERVICE_PER_DEVICE;j++)
			pDisPtrs[i][j]=NULL;
				
}



 CDimmer::~ CDimmer()
{
	INT i,j;
	for(i=0;i<NUM_TEMPLATE_UDNS_IN_DESCDOC;i++)
		for(j=0;j<MAX_NOSERVICE_PER_DEVICE;j++)
			if(pDisPtrs[i][j]!=NULL)
			{
				pDisPtrs[i][j]->Release();
				pDisPtrs[i][j]=NULL;
			}

	
	//free the strings allocated for the table mapping the template UDN to real UDN
	SysFreeString(UDNmapping[0][0]);

	//free the strings allocated for the table mapping devices to Service ID's
	SysFreeString(serviceIDDeviceMap[0][0]);

} 



STDMETHODIMP  CDimmer::Initialize(BSTR bstrXMLDesc,BSTR deviceID,BSTR bstrInitString)
{
	//We create an instance of our service and store it for future use
	HRESULT hr = S_OK;
	HANDLE fHandle=NULL;
	DWORD numBytesWritten=0;
	IUPnPRegistrar *pReg = NULL;
	CHAR *pDescDoc=NULL;
	INT i;

	OutputDebugString(TEXT("CDimmerDCO: Entering Initialize\n"));
	//CComObject<UPNPDimmerService> *pUPNPDimmerService;
	CComObject<CDimmerService> *pUPNPDimmerService;

	//if the description doc passed to the Initialize function is NULL return an error
	if(bstrXMLDesc==NULL)
	{
		OutputDebugString(TEXT("CDimmerDCO: bstrXMLDesc is null\n"));
		return E_FAIL;
	}


	//Now create Service Objects for the services hosted by the device and store it in the pDispPtrs table 
	//We get the Service Object IDispatch pointer for the RootDevice's dimming service and store it in Location 0,0
	hr=S_OK;
	pUPNPDimmerService=NULL;
	OutputDebugString(TEXT("CDimmerDCO: Creating the service object\n"));
	//hr = CComObject<UPNPDimmerService>::CreateInstance(&pUPNPDimmerService);
	hr = CComObject<CDimmerService>::CreateInstance(&pUPNPDimmerService);
	
	if(FAILED(hr)){
		OutputDebugString(TEXT("CDimmerDCO: Cannot create the service object\n"));
		return E_FAIL;
	}

	//if we could not create the service object for the Dimmer Service return an Error
	if(pUPNPDimmerService==NULL) {
		OutputDebugString(TEXT("CDimmerDCO: The service object is null\n"));
		return E_FAIL;
	}

	//Now get the pointer to the IDispatch interface using the QueryInterface function

	OutputDebugString(TEXT("CDimmerDCO: Querying the IDispatch for the service object\n"));
	hr = pUPNPDimmerService->QueryInterface(IID_IDispatch,(LPVOID *) &pDisPtrs[0][0]);
	if(!SUCCEEDED(hr))
	{
		OutputDebugString(TEXT("CDimmerDCO: Can't get IDispatch interface from the service object\n"));
		return E_FAIL;
	}

	
	//now create a table mapping the template UDN's to the actual published UDN's we use BSTR's since
	//the function GetUniqueDeviceName() takes in BSTR's as parameters
	hr = S_OK;
		
	OutputDebugString(TEXT("CDimmerDCO: Creating the registrar object\n"));
	hr = CoCreateInstance(		CLSID_UPnPRegistrar,
								NULL,
								CLSCTX_SERVER,
								IID_IUPnPRegistrar,
								(LPVOID *) &pReg);

	if(!SUCCEEDED(hr))
	{
		OutputDebugString(TEXT("CDimmerDCO: Can't create the registrar object\n"));
		return E_FAIL;
	}
	
	for(i=0;i<NUM_TEMPLATE_UDNS_IN_DESCDOC;i++)
	{
		hr=S_OK;
		hr = pReg->GetUniqueDeviceName(deviceID,UDNmapping[i][0],&UDNmapping[i][1]);
		if(!SUCCEEDED(hr))
		{
			pReg->Release();
			OutputDebugString(TEXT("CDimmerDCO: Can't get the unique device names\n"));
			return E_FAIL;
		}
	}

	pReg->Release();
	OutputDebugString(TEXT("CDimmerDCO: Exiting the Initialize\n"));
	return hr;

}

STDMETHODIMP  CDimmer::GetServiceObject(BSTR bstrUDN,BSTR bstrServiceId,IDispatch **ppdispService)
{ 
	// Look at the Service for which the pointer is asked and return it in the IDispatch pointer
	INT i;
	INT foundDevice=-1;
	INT foundService=-1;

	for(i=0;i<NUM_TEMPLATE_UDNS_IN_DESCDOC;i++)
		if(_tcscmp(bstrUDN,UDNmapping[i][1])==0)
			foundDevice=i;

	if(foundDevice==-1)
		return E_FAIL;
	
	//else find the service in this particular device
	for(i=0;i<MAX_NOSERVICE_PER_DEVICE;i++)
		if(_tcscmp(serviceIDDeviceMap[foundDevice][i],bstrServiceId)==0)
			foundService=i;

	if(foundService==-1)
		return E_FAIL;

	if(pDisPtrs[foundDevice][foundService]==NULL) return E_FAIL;

	pDisPtrs[foundDevice][foundService]->AddRef();
	*ppdispService = pDisPtrs[foundDevice][foundService];
	return S_OK;
}

