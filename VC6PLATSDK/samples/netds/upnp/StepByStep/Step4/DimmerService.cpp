// DimmerService.cpp : Implementation of CDimmerService
#include "stdafx.h"
#include "MyDevice.h"
#include "DimmerService.h"

CDimmerService::CDimmerService()
{
	//set the default values for the state table variables power and dimLevel
    power = VARIANT_FALSE;
	dimnessLevel = 0;

	InitializeCriticalSection(&csSync);
   
	esEventingManager = NULL; // Make it NULL and this will be later set when the device host calls the Advise()
}



CDimmerService::~CDimmerService()
{
	//Cleanup before the service exits
    if (esEventingManager)
	{
        // we have to release the pointer to the Eventing Manager Interface on shutdown
        esEventingManager->Release();
        esEventingManager = NULL;
    }

	DeleteCriticalSection(&csSync);
}



HRESULT CDimmerService::get_Power(VARIANT_BOOL *pval)
{    
    // return the value of the state table variable Power
	EnterCriticalSection(&csSync);
    *pval = power;
	LeaveCriticalSection(&csSync);
    return S_OK;
}



HRESULT CDimmerService::get_dimLevel(LONG *dLevel)
{    
    // return the value of the state table variable dimLevel
	EnterCriticalSection(&csSync);
    *dLevel = dimnessLevel;
	LeaveCriticalSection(&csSync);
    return S_OK;
}



HRESULT CDimmerService::PowerOn()
{
    DISPID rgdispidChanges[1];
    
	EnterCriticalSection(&csSync);
    
	if(power!=VARIANT_TRUE)
	{ 
        power = VARIANT_TRUE;
		LeaveCriticalSection(&csSync);	

        // We have to send an event here indicating that the value of Power has changed
        if(esEventingManager)
		{
            // Send the event that power = TRUE through OnStateChanged API exposed by IUPnPEventSource 
            rgdispidChanges[0]=DISPID_POWER;
            esEventingManager->OnStateChanged(1, rgdispidChanges);
        }
    }
	else
		LeaveCriticalSection(&csSync);
    
	return S_OK;
}




HRESULT CDimmerService::PowerOff()
{
    DISPID rgdispidChanges[1];
    
	EnterCriticalSection(&csSync);
    if(power!=VARIANT_FALSE)
	{ 
        power = VARIANT_FALSE;
        // We have to send an event here since the value of a State table variable has changed
		LeaveCriticalSection(&csSync);
        
		if(esEventingManager)
		{
            // Send the event using the OnStateChanged API and indicate the the value of the State table variable Power
			//has changed
            rgdispidChanges[0]=DISPID_POWER;
            esEventingManager->OnStateChanged(1, rgdispidChanges);
        }
    }
	else
		LeaveCriticalSection(&csSync);
      
    return S_OK;
}



HRESULT CDimmerService::GetPowerValue(VARIANT_BOOL*powerVal)
{   
	EnterCriticalSection(&csSync);
	*powerVal = power;
	LeaveCriticalSection(&csSync);
        
	// We have no events to send for this action
    return S_OK;
}



HRESULT CDimmerService::SetDimLevel(LONG dLevel)
{
    DISPID rgdispidChanges[1];
    
	EnterCriticalSection(&csSync);
	dimnessLevel = dLevel;
	//the possible values for dimnessLevel are 0 - 100
	if (dimnessLevel>100) dimnessLevel=100;
	if(dimnessLevel <0) dimnessLevel=0;
	LeaveCriticalSection(&csSync);
        
	// We have to send an event here
	if(esEventingManager)
	{
            // Send the event using the OnStateChanged API to indicate that value of State table varaible dimLevel has
			//changed
            rgdispidChanges[0]=DISPID_DIMLEVEL;
            esEventingManager->OnStateChanged(1, rgdispidChanges);    
    }
	  
    return S_OK;
}


HRESULT CDimmerService::GetDimLevel(LONG *dLevel)
{   
	EnterCriticalSection(&csSync);
	*dLevel = dimnessLevel;
	LeaveCriticalSection(&csSync);
        
	// We have no events to send here as the state table has not changed     
    return S_OK;
}



HRESULT CDimmerService::GetConfigDetails(VARIANT_BOOL *powerVal,LONG *dLevel)
{
	EnterCriticalSection(&csSync);
	*dLevel = dimnessLevel;
	*powerVal = power;
	LeaveCriticalSection(&csSync);
        
	// We have no events to send here as the state table has not changed  
    return S_OK;
}


HRESULT CDimmerService::Advise (IUPnPEventSink *punkSubscriber)
{
    // We have to get query for the IUPnPEventSink Interface to send events later  using the OnStateChanged API
    
    HRESULT hr = S_OK;
    
	//query the pointer passed to the Advise function for the IUPnPEventSink Interface
    hr = punkSubscriber->QueryInterface(IID_IUPnPEventSink, (void **)&esEventingManager);
    if(FAILED(hr))
	{
        OutputDebugString(_TEXT("CDimmerService: Query Interface failed.Could not get pointer to IUPnPEventSink\n")); 
        return hr;
    }       
	
    return hr;
}



HRESULT CDimmerService::Unadvise(IUPnPEventSink *punkSubscriber)
{	
	//Device Host is not interested in receiving more events and so set the pointer to the IUPnPEventSink interface
	//to NULL
    if (esEventingManager)
	{
        // esEventingManager is already set by the advise
        esEventingManager->Release();
        esEventingManager = NULL; 
    }
	
    return S_OK;
}
