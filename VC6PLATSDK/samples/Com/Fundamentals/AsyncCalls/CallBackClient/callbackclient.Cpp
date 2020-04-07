/*+==========================================================================

File: CallBackClient.cpp

Summary:  Demonstrates aggregation of the call object in order to recieve a 
		  callback on non-blocking method call completion

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

#include "stdafx.h"
#include "CallBackClient.h"
#include "FullSvr.h"
#include <iostream.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	HRESULT hr;
	ISynchronize * pISynchronize;

	//Create an STA
	hr = CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);
	_ASSERT(SUCCEEDED(hr));

	//Create the call back component
	CComObject<CCallBack> * pCallBackObj = NULL;
	hr = CComObject<CCallBack>::CreateInstance(&pCallBackObj);
	_ASSERT(SUCCEEDED(hr));
	
	//Get ISynchronize from our callback object
	hr = pCallBackObj->QueryInterface(IID_ISynchronize,(void**)&pISynchronize);


	//Start the non-blocking method call
	hr = pCallBackObj->StartCall(2,3);
	if(FAILED(hr)){
		cerr<<"StartCall Failed"<<endl;
	} else {
		//Enter message loop waiting for callback
		pISynchronize->Wait(0,INFINITE);
	}
	
	pISynchronize->Release();
	CoUninitialize();
	
	cout<<endl<<"Press Enter to continue..\n \n"<<endl;
	_getch();

	return 0;
}

//ATL unlock method.  Called during destruction of CCallBack
CExeModule _Module;
LONG CExeModule::Unlock()
{
    return 0;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CCallBack::StartCall
  Summary:  Starts a non-blocking method call and aggregates the call object
  Args:     [in] i,j the numbers to sum 
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CCallBack::StartCall(int i, int j){

	HRESULT hr = S_OK;
	ICallFactory * pICallFactory = NULL;
	IUnknown * pIUnknown = NULL;
	AsyncIFullServ * pAsyncIFullServ = NULL;
	
	//Create FullServ
	hr = CoCreateInstance(CLSID_FullServ,NULL,CLSCTX_SERVER,IID_IUnknown,(void**)&pIUnknown);
	if(FAILED(hr))
		return hr;
	
	//Get ICallFactory
	hr = pIUnknown->QueryInterface(IID_ICallFactory,(void**)&pICallFactory);
	if(FAILED(hr))
		goto CleanUp;

	//Create and aggregate the call object
	hr = pICallFactory->CreateCall(IID_AsyncIFullServ,GetControllingUnknown(),IID_IUnknown,(IUnknown**)&m_pCallObjUnk);
	if(FAILED(hr))
		goto CleanUp;
	
	//Get the Async interface and begin the call
	hr = QueryInterface(IID_AsyncIFullServ,(void**)&pAsyncIFullServ);
	if(FAILED(hr))
		goto CleanUp;

	hr = pAsyncIFullServ->Begin_Sum(i,j);

	if(SUCCEEDED(hr))
	cout<<"Call sent to the server"<<endl;

	//Release all but the call object's unk
CleanUp:
	if(pIUnknown) pIUnknown->Release();
	if(pICallFactory) pICallFactory->Release();
	if(pAsyncIFullServ) pAsyncIFullServ->Release();
	return hr;
}

/////////////////////////////////////////////////////////
//ISynchronize

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CCallBack::Reset implementing ISynchronize::Reset
  Summary:  Passes through reset call to the contained synch object
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CCallBack::Reset(){
	return smartPtrISynchronize->Reset();
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CCallBack::Wait implementing ISynchronize::Wait
  Summary:  Passes through wait call to the contained synch object
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CCallBack::Wait(DWORD flags,DWORD timeout){
	return smartPtrISynchronize->Wait(flags,timeout);
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CCallBack::Signal implementing ISynchronize::Signal
  Summary:  Passes through signal call to the contained synch object
			then does the work of the call back. This method is the clients
			call back on completion of the non-blocking method call
  Note:		The client must pass through the signal call before continuing
			with the call back.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CCallBack::Signal(){
	smartPtrISynchronize->Signal();
	CallBack();
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CCallBack::CallBack
  Summary:  upon recieving the call back this function finishes the non-blocking
			method call and displays the results
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CCallBack::CallBack(){

	HRESULT hr;
	AsyncIFullServ * pAsyncIFullServ;
	int i;

	cout<<"Recieved a Call Back"<<endl;

	//Get Async interface
	hr = QueryInterface(IID_AsyncIFullServ,(void**)&pAsyncIFullServ);
	_ASSERT(SUCCEEDED(hr));

	//Finish the call
	hr = pAsyncIFullServ->Finish_Sum(&i);
	if(FAILED(hr)){
		cerr<<"Finish_Sum failed"<<endl;
	}else{
		cout<<"Sum of 2 and 3 is: "<<i<<endl;
	}
	
	pAsyncIFullServ->Release();

	return S_OK;
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: QueryFunc
  Summary:  this function acts as a hook into CCallBack's QueryInterface.  
			This function simply passes the call to CCallBack::MyQuery
  Args:     pv - CCallBack
  Returns:  DWORD always returns 0
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT WINAPI QueryFunc(void* pv, REFIID riid, LPVOID* ppv, DWORD_PTR dw){
	UNREFERENCED_PARAMETER(dw);
	return ((CCallBack *)pv)->MyQuery(riid,ppv);
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CCallBack::MyQuery
  Summary:  CCallBack aggregates the call object, and therfore needs to pass
			QI calls to m_pCallObjUnk.  However, the call object isn't created
			until StartCall executes.  Therefore we use MyQuery to pass the QI
			calls to m_pCallObjUnk only when it is non-null
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
//Pass QI to the call object if it has been created
STDMETHODIMP CCallBack::MyQuery(REFIID riid, LPVOID* ppv){
	
	if(!m_pCallObjUnk)
		return E_NOINTERFACE;

	return m_pCallObjUnk->QueryInterface(riid,ppv);
}
