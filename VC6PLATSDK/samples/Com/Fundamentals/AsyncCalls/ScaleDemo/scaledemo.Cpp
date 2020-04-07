/*+==========================================================================

File:	  scaleDemo.cpp

Summary:  This demo is designed to show the greater scalability offered
		  by a server that handles calls asynchronously.

----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/
// scaleDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <conio.h>
#include <time.h>
#include "FullSvr.h"
#include "FullSvr_i.c"

const int NUM_CONCURRENT_CALLS = 15;

//Arrays for our call objects
AsyncIFullServ * callObjFullArray[NUM_CONCURRENT_CALLS];
AsyncISample * callObjSampleArray[NUM_CONCURRENT_CALLS];


int main(int argc, char* argv[])
{

	HRESULT hr;
	int i,j;
	IUnknown       * pIUnknown = NULL;
	ICallFactory   * pICallFactory = NULL;
	clock_t start,finish;

	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){
		callObjFullArray[i]   = NULL;
		callObjSampleArray[i] = NULL;
	}

	//Create an STA
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	//Create the server object
	hr = CoCreateInstance(CLSID_FullServ,NULL,CLSCTX_LOCAL_SERVER,IID_IUnknown,(void**)&pIUnknown);
	if(FAILED(hr)){
		cout<<"CCI failed"<<endl;
		goto CleanUp;
	}

	//Get ICallFactory
	hr = pIUnknown->QueryInterface(IID_ICallFactory,(void **)&pICallFactory);
	if(FAILED(hr)){
		cerr<<"Query for ICallFactory failed."<<endl;
		goto CleanUp;
	}

	//Create all call objects
	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){

		//Create the call objects for AsyncIFullServ
		hr = pICallFactory->CreateCall(IID_AsyncIFullServ,NULL,IID_AsyncIFullServ,(IUnknown**)&callObjFullArray[i]);
		if(FAILED(hr)){
			cerr<<"Unable to create call object for AsyncIFullServ"<<endl;
			goto CleanUp;
		}
		
		//Create the call objects for AsyncISample
		hr = pICallFactory->CreateCall(IID_AsyncISample,NULL,IID_AsyncISample,(IUnknown**)&callObjSampleArray[i]);
		if(FAILED(hr)){
			cerr<<"Unable to create a call object for AsyncISample"<<endl;
			goto CleanUp;
		}
	}
	
	//Begin all calls on AsyncIFullServ
	cout<<"Starting calls to AsyncIFullServ."
		<<endl<<"These calls are handled asynchronously on the server."<<endl;
	start = clock();
	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){

		hr = callObjFullArray[i]->Begin_Sum(2,3);

		if(FAILED(hr)){
			cerr<<"Begin failed on AsyncIFullServ"<<endl;
			goto CleanUp;
		}
	}

	//Finish all calls on AsyncIFullServ
	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){
		
		hr = callObjFullArray[i]->Finish_Sum(&j);
		if(FAILED(hr)){
			cerr<<"Finish failed on AsyncIFullServ"<<endl;
			goto CleanUp;
		}
	}

	finish = clock();
	cout<<"Done"<<endl<<"Time elapsed: "<<(finish - start)<<"ms"<<endl;


	cout<<endl<<"Starting calls to AsyncISample."
		<<endl<<"These calls are handled synchronously on the server. This can take a while."<<endl;
	start = clock();

	//Begin all calls on AsyncISample
	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){

		hr = callObjSampleArray[i]->Begin_Work(2,3);

		if(FAILED(hr)){
			cerr<<"Begin failed on AsyncIFullServ"<<endl;
			goto CleanUp;
		}

	}

	//Finish all calls on AsyncISample
	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){

		callObjSampleArray[i]->Finish_Work(&j);

		if(FAILED(hr)){
			cerr<<"Finish failed on AsyncISample"<<endl;
			goto CleanUp;
		}

	}
	finish = clock();
	cout<<"Done"<<endl<<"Time elapsed: "<<(finish - start)<<"ms"<<endl;

CleanUp: //Release all references

	for(i = 0; i < NUM_CONCURRENT_CALLS; i++){
		if(callObjFullArray[i]) callObjFullArray[i]->Release();
		if(callObjSampleArray[i]) callObjSampleArray[i]->Release();
	}

	if(pIUnknown)       pIUnknown->Release();
	if(pICallFactory)   pICallFactory->Release();

	CoUninitialize();

	cout<<endl<<"Press Enter to continue..\n \n"<<endl;
	_getch();

	return 0;
}