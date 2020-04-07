/*+==========================================================================

File: FullServ.cpp

Summary:  Implements CFullServ and CAsyncFullServ methods.


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
#include "FullSvr.h"
#include "FullServ.h"

DWORD WINAPI WorkerFcn(LPVOID context);

/////////////////////////////////////////////////////////////////////////////
// CFullServ

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFullServ::Sum implementing IFullServ::Sum
  Summary:  synchronous implementation of the Sum method of IFullServ
  Args:     [in] i,j the numbers to sum 
			[out,retval] sum the result
  Returns:  HRESULT	- Always returns S_OK
  Note:		This method will never be called.  Because CreateCall creates
			call objects for AsyncIFullServ all calls to both IFullServ
			and AsyncIFullServ will be handled asynchronously with the Begin
			and Finish methods.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CFullServ::Sum(int i, int j, int * sum){
	*sum = i + j;
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFullServ::Work implementing ISample::Work
  Summary:  method used to compare scalability of sync and async implementation
			in scaledemo.  Simulates work before returning results
  Args:     [in] i,j the numbers to sum 
			[out,retval] sum the result
  Returns:  HRESULT	- Always returns S_OK
  Note:		Because CreateCall does not create call objects for AsyncISample
			this method will be used for all calls to both ISample
			and AsyncISample.  This method will be executed by an RPC thread
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CFullServ::Work(int i, int j,int * sum){

	for(int k = 0; k < 10000; k++){
		for(int l = 0; l < 10000; l++){
		}
	}
	
	*sum = i + j;
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CFullServ::CreateCall
  Summary:  method used by the stub to create call objects for asynchronous
			handeling of calls.  In this case call objects are CAsyncFullServ
			instances that implement AsyncIFullServ
  Args:     [in] riid1 the IID of an asynchronous interface for which the stub 
			needs a call object
			[in] pUnk a controlling unknown for aggregation with the call object
			[in] riid2 the call object interface to be placed in ppObj
			[out] ppObj the requested interface pointer
  Returns:  HRESULT
  Note:		CreateCall offers the opportunity to pass data between the objects
			implementing the synchronous and asynchronous interfaces.  In this
			case CFullServ passes a pointer to IFullServ to CAsyncFullServ
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CFullServ::CreateCall(REFIID riid1,
				   IUnknown * pUnk,
				   REFIID riid2,
				   IUnknown ** ppObj)
{
	HRESULT hr;
	IFullServ * pIFullServ;
	if (ppObj == NULL) return E_POINTER;

	//We only support one async interface: AsyncIFullServ + check for proper
	//aggregation
	if((riid1 != IID_AsyncIFullServ) || (pUnk && (riid2 != IID_IUnknown)))
		return E_INVALIDARG;

	//Obtain a pointer to the synchronous IFullServ interface
	hr = ((IFullServ * )this)->QueryInterface(IID_IFullServ,(void**)&pIFullServ);
	_ASSERT(SUCCEEDED(hr));

	//Create our object
	CComPolyObject<CAsyncFullServ>* pPolyFullServ = NULL;
	hr = CComPolyObject<CAsyncFullServ>::CreateInstance(pUnk,&pPolyFullServ);

	if(FAILED(hr)){
		pIFullServ->Release();
		return hr;
	}

	//Store pointer to the synchronous interface
	pPolyFullServ->m_contained.Init(pIFullServ);
	pIFullServ->Release();

	//Return requested interface
	hr = pPolyFullServ->QueryInterface(riid2,(void**)ppObj);

	return hr;
}


/////////////////////////////////////////////////////////////////////////////
// CFullServ

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CAsyncFullServ::Begin_Sum implementing AsyncIFullServ::Begin_Sum
  Summary:  This method is used to queue the [in] parameters for work by the
			system supplied thread pool.
  Args:     [in] i,j the numbers to sum
  Modifies: member vars m_i,m_j store params for later processing, m_hr stores
			a HRESULT for transmission back to the client
  Returns:  HRESULT - this result will not be seen by the client.  To return
			an error code to the client Begin must store an HRESULT call Signal()
			and let Finish return the HRESULT to the client
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CAsyncFullServ::Begin_Sum(int i, int j){

	HRESULT hr = S_OK;
	ISynchronize * pISynchronize;
	m_hr = S_OK;

	if(m_callInProgress) return RPC_S_CALLPENDING;

	m_callInProgress = TRUE;

	// Get and store ptr to ISynchronize
	hr = ((AsyncIFullServ *)this)->QueryInterface(IID_ISynchronize,
   						     (void**)&pISynchronize);
	_ASSERT(SUCCEEDED(hr));

	pISynchronize->Reset();

	//store [in] params
	m_i = i;
	m_j = j;

	//Queue CAsyncFullServ for processing by a worker thread
	if(!QueueUserWorkItem(WorkerFcn, this, WT_EXECUTEDEFAULT)){
		m_hr = E_FAIL;
		pISynchronize->Signal();
	}

	pISynchronize->Release();
	return S_OK;
}//RPC thread is returned to the RPC thread pool

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WorkerFcn
  Summary:  This function is called by a worker thread from the thread pool.  
			The function first simulates real work then calls the doSum method
  Args:     pContext a CAsyncFullServ instance that was queued for processing
			with QueueUserWorkItem
  Returns:  DWORD always returns 0
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
DWORD WINAPI WorkerFcn(LPVOID pContext){
    // This thread from the system thread pool does not have
    // a predetermined COM thread type. So this code calls
    // CoInitializeEx to setup a proper execution environment
    // (i.e. same apartment (MTA) as Begin_Sum call was dispatched in.)
    HRESULT hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);
	_ASSERT(SUCCEEDED(hr));

    CAsyncFullServ * pAsyncFullServ = (CAsyncFullServ *) pContext;

	//Simulate work
	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
		}
	}

	//Do the real Work of the function
	pAsyncFullServ->doSum();

    // Call CoUninitialize to return this thread to
    // the uninitialized COM state.
    CoUninitialize();
	return 0;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CAsyncFullServ::doSum
  Summary:  This method checks for call cancellation and then does the real
			work of Sum.  This method is executed by a worker thread 
  Args:     
  Modifies: member vars m_i,m_j store params for later processing, m_hr stores
			a HRESULT for transmission back to the client
  Returns:  HRESULT - always returns S_OK;
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CAsyncFullServ::doSum(){

	HRESULT hr;
	ISynchronize * pISynchronize;
	ICancelMethodCalls * pICancelMethodCalls = NULL;

	//Get ISynchronize
	hr = ((AsyncIFullServ *)this)->QueryInterface(IID_ISynchronize,
   						     (void**)&pISynchronize);
	_ASSERT(SUCCEEDED(hr));


	//Attempt to get pointer to ICancelMethod Calls
	hr = ((AsyncIFullServ *)this)->QueryInterface(IID_ICancelMethodCalls,
                                                      (void**)&pICancelMethodCalls);

	//Check for call cancellation
	if(SUCCEEDED(hr)){
		hr = pICancelMethodCalls->TestCancel();
		if(hr == RPC_E_CALL_CANCELED){
			m_hr = hr; //record call cancellation for Finish
			pICancelMethodCalls->Release();
			pISynchronize->Signal();
			pISynchronize->Release();
			return S_OK;
		}
	}

	//do the work of the function
	m_sum = m_i + m_j;

    // Work complete, signal the stub so that the Finish_Sum method is called.
	pISynchronize->Signal();
	pISynchronize->Release();
	if(pICancelMethodCalls) pICancelMethodCalls->Release();
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CAsyncFullServ::Finish_Sum implements AsyncIFullServ::Finish_Sum
  Summary:  If the call was successful to this point, Finish will return the 
			results of the call in the [out] params; otherwise Finish
			will return the error code to the client
  Args:     [out] sum 
  Returns:  HRESULT - the result of Begin or doSum
  Note:		This method is called when Begin or doSum call ISynchronize::Signal
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 
STDMETHODIMP CAsyncFullServ::Finish_Sum(int * sum){
	HRESULT hr;
	ISynchronize * pISynchronize;
	if(!m_callInProgress)
		return RPC_E_CALL_COMPLETE;
	m_callInProgress = FALSE;

	//Get ISynchronize
	hr = ((AsyncIFullServ *)this)->QueryInterface(IID_ISynchronize,
   						     (void**)&pISynchronize);
	_ASSERT(SUCCEEDED(hr));

	pISynchronize->Wait(COWAIT_WAITALL,INFINITE);
	
	pISynchronize->Release();
	
	//Check if call was canceled or if Begin failed
	if(FAILED(m_hr)){
		return m_hr; //Call failed or was canceled. m_sum is garbage
	}

	*sum = m_sum;
	return m_hr; //call was successful
}

