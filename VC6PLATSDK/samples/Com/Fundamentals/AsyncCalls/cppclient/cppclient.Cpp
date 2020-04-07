// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
#include "stdafx.h"
#include <iostream.h>
#include <conio.h>
#include "FullSvr.h"
#include "FullSvr_i.c"

int main(int argc, char* argv[])
{

	HRESULT hr;
	int i;
	AsyncIFullServ * pAsyncIFullServ = NULL;
	ICallFactory   * pICallFactory = NULL;
	ISynchronize   * pISynchronize = NULL;
	IUnknown       * pIUnknown = NULL;

	//Create an STA
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	//Create the server object
	hr = CoCreateInstance(CLSID_FullServ,NULL,CLSCTX_LOCAL_SERVER,IID_IUnknown,(void**)&pIUnknown);
	if(FAILED(hr)){
		cerr<<"CoCreateInstance failed"<<endl;
		goto CleanUp;
	}

	//Get a pointer to ICallFactory
	hr = pIUnknown->QueryInterface(IID_ICallFactory,(void **)&pICallFactory);
	if(FAILED(hr)){
		cerr<<"Query for ICallFactory failed."<<endl;
		goto CleanUp;
	}

	//Create the call object and get a pointer to the async interface
	hr = pICallFactory->CreateCall(IID_AsyncIFullServ,NULL,IID_AsyncIFullServ,(IUnknown**)&pAsyncIFullServ);
	if(FAILED(hr)){
		cerr<<"Unable to create Call Object."<<endl;
		goto CleanUp;
	}

	//Get a pointer to ISynchronize
	hr = pAsyncIFullServ->QueryInterface(IID_ISynchronize,(void**)&pISynchronize);
	if(FAILED(hr)){
		cerr<<"Query for ISynchronize failed."<<endl;
		goto CleanUp;
	}

	//Begin the non-blocking call
	hr = pAsyncIFullServ->Begin_Sum(2,3);
	if(FAILED(hr)){
		cerr<<"Begin_Sum failed.  Call was not sent succesfully to the server"<<endl;
		//this failed call will be cleaned up by releasing the call object
		goto CleanUp;
	}

	cout<<"Waiting for call completion."<<endl;
	//Wait for call completion
	hr = pISynchronize->Wait(0,INFINITE);
	if(FAILED(hr)){
		cerr<<"Wait failed"<<endl;
		goto CleanUp;
	}

	//Finish the call and retrieve the results
	hr = pAsyncIFullServ->Finish_Sum(&i);
	if(FAILED(hr)){
		cerr<<"Finish_Sum failed."<<hr<<endl;
		goto CleanUp;
	}

	cout<<"Sum of 2 and 3 is: "<< i <<endl;

//Release all allocated resources
CleanUp:

	if(pAsyncIFullServ) pAsyncIFullServ->Release();
	if(pISynchronize)   pISynchronize->Release();
	if(pIUnknown)       pIUnknown->Release();
	if(pICallFactory)   pICallFactory->Release();

	CoUninitialize();


	cout<<endl<<"Press Enter to continue..\n \n"<<endl;
	_getch();

	return 0;
}
