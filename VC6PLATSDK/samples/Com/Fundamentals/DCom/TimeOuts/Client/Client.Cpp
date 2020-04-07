/*+==========================================================================

File: client.cpp

Summary:  Produced by VS6 MFC Wizard. Implements the Client.Exe Application.

Look in this module to see how Non-Blocking Method Calls and Call Cancellation
are used to implement DCOM Timeouts.

----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/
// client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"


#include "..\server\server_i.c"
#include "..\PingResp\PingResp_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	//{{AFX_MSG_MAP(CClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientApp construction

CClientApp::CClientApp()
{
	pDlg = NULL;
	pMonitor = NULL;
	pMonitorCallFactory = NULL;
	pMonitorResponder = NULL;
	nFail = 0;
	// Place all significant initialization in InitInstance
}

CClientApp::~CClientApp(){
//		if (pMonitorCallFactory) pMonitorCallFactory->Release();
//		if (pMonitor) pMonitor->Release();
        if (pDlg) delete pDlg;
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CClientApp object

CClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientApp initialization

BOOL CClientApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	AfxOleInit();

	pDlg = new CClientDlg;
	m_pMainWnd = pDlg;
	if (!pDlg->Create(IDD_CLIENT_DIALOG,NULL)){
		AfxMessageBox(_T("Can't Create Dialog!"));
		return FALSE;
	}
	

	return TRUE;
}


HRESULT CClientApp::DoAPing(IPingResponder *pResp, DWORD dwTimeout){
	AsyncIPingResponder *pAsyncResp = NULL;
	ISynchronize* pAsyncSync = NULL;
	ICallFactory* pResponderCallFactory = NULL;
	ICancelMethodCalls* pCancel = NULL;

	HRESULT hr = E_FAIL;
	__try {
		hr = pResp->QueryInterface(IID_ICallFactory, (void**)&pResponderCallFactory);
		if (FAILED(hr)) return hr;

		hr = pResponderCallFactory->CreateCall(IID_AsyncIPingResponder,NULL,IID_AsyncIPingResponder,(IUnknown**)&pAsyncResp);
		if (FAILED(hr)) return hr;
		
		hr = pAsyncResp->Begin_Ping();
		if (FAILED(hr)) return hr;
		pDlg->m_lPings++;

		// Timeout the Ping...
		hr = pAsyncResp->QueryInterface(IID_ISynchronize,(void**)&pAsyncSync);
		if (FAILED(hr)) return hr;

		// The HRESULT from this wait is what determines whether DoAPing fails!
		hr = pAsyncSync->Wait(0, dwTimeout);

		if (hr != S_OK){
			// Ping didn't complete in time. Cancel the call to cleanup
			// any resources consumed by the call.
			HRESULT hr2 = S_OK;
			hr2 = pAsyncResp->QueryInterface(IID_ICancelMethodCalls, (void**)&pCancel);
		    ASSERT(SUCCEEDED(hr2));
		    hr2 = pCancel->Cancel(0);
		    ASSERT(SUCCEEDED(hr2));
		    pCancel->Release();
		    pCancel = NULL;
			pDlg->m_lPingFailures++;
		}

		// Complete the Ping Call ignoring its results
		pAsyncResp->Finish_Ping();

	}
	__finally{
		// All these releases will cleanup any debris left from the ping
		if (pCancel) pCancel->Release();
		if (pAsyncResp) pAsyncResp->Release();
		if (pAsyncSync) pAsyncSync->Release();
		if (pResponderCallFactory) pResponderCallFactory->Release();
	}
	return hr;
}

BOOL CClientApp::OnIdle(LONG lCount)
{
	AsyncIMonitorServer *pAsyncMonitor = NULL;
	ISynchronize* pAsyncSync = NULL;
	ICancelMethodCalls* pCancel = NULL;
	HRESULT hr = E_FAIL;

	CWinApp::OnIdle(lCount);
	
	__try {
	if ((lCount == 0) && pMonitorCallFactory){

		// Time to make Non-Blocking Call to get data
		hr = pMonitorCallFactory->CreateCall(IID_AsyncIMonitorServer,NULL,IID_AsyncIMonitorServer,(IUnknown**)&pAsyncMonitor);
		if (FAILED(hr)){
			AfxMessageBox(_T("OOPS! Creating of Call Instance Object Failed"));
			return FALSE;
		}

		// Start Call
		pDlg->m_lTries++;

		hr = pAsyncMonitor->Begin_GetData();
		if (SUCCEEDED(hr)) {

		  hr = pAsyncMonitor->QueryInterface(IID_ISynchronize,(void**)&pAsyncSync);
		  ASSERT(SUCCEEDED(hr));
		  //
		  // There are two different mechanisms shown here:
		  //	A) As long as the server system responsds to a ping
		  //       let the call complete in as long as it likes.
		  //
		  //	B) Enforce a strict timeout. The call must complete within
		  //	   the CALLTIMEOUT interval.
		  //

		  if (pDlg->m_bUsePing){
			  // Use the pinging technique...
			  HRESULT hr2 = S_OK;
			
			  // Keep call going as long as pinging succeeds
			  while (hr2 == S_OK) {
				hr = pAsyncSync->Wait(0, CALLTIMEOUTWHENPINGING);
				if (hr != S_OK){
					hr2 = DoAPing(pMonitorResponder, PINGTIMEOUT);
					
				} else {
					hr2 = (HRESULT)-1; //Call Completed
				}
			  }

			  // Evaluate the results of pinging or call
			  if (hr != S_OK){
				  // Call didn't complete and we got here because DoAPing failed
				  // Just cancel call
				  pDlg->m_lTimeouts++;
				  hr = pAsyncMonitor->QueryInterface(IID_ICancelMethodCalls, (void**)&pCancel);
				  ASSERT(SUCCEEDED(hr));
				  hr = pCancel->Cancel(0);
				  ASSERT(SUCCEEDED(hr));
				  pCancel->Release();
				  pCancel = NULL;
			  }
			
		  } else {
			  // Apply Strict Timeouts
				hr = pAsyncSync->Wait(0,CALLTIMEOUT);
				if (hr != S_OK){
					// Timeout happened before Call Completed
					// Cancel call which will cause Finish_GetData
					//   to return RPC_E_CALLCANCELED
					pDlg->m_lTimeouts++;
					hr = pAsyncMonitor->QueryInterface(IID_ICancelMethodCalls, (void**)&pCancel);
					ASSERT(SUCCEEDED(hr));
					hr = pCancel->Cancel(0);
					ASSERT(SUCCEEDED(hr));
					pCancel->Release();
					pCancel = NULL;
				}
		  }
		
		  pAsyncSync->Release();
		  pAsyncSync = NULL;
		} else {
			pDlg->m_lFails++;
		}
		// Complete Call
        long iNewData;
		hr = pAsyncMonitor->Finish_GetData(&iNewData);
		if (SUCCEEDED(hr)) {
            pDlg->m_iData = iNewData;       // Believe new data
			nFail = 0;						// State data Ok...
        } else {
			nFail++;
        }
		if (nFail > 3) nFail=3;		// To keep the UI happy

		

		pAsyncMonitor->Release();
		pAsyncMonitor = NULL;

		// Update Status Text on Dialog based upon nFail
		if (nFail == 0){
			pDlg->m_cGood.ModifyStyle(0,WS_VISIBLE,0);
			pDlg->m_cWarning.ModifyStyle(WS_VISIBLE,0,0);
			pDlg->m_cBad.ModifyStyle(WS_VISIBLE,0,0);
		} else if (nFail <= 2){
			pDlg->m_cGood.ModifyStyle(WS_VISIBLE,0,0);
			pDlg->m_cWarning.ModifyStyle(0,WS_VISIBLE,0);
			pDlg->m_cBad.ModifyStyle(WS_VISIBLE,0,0);
		} else {
			pDlg->m_cGood.ModifyStyle(WS_VISIBLE,0,0);
			pDlg->m_cWarning.ModifyStyle(WS_VISIBLE,0,0);
			pDlg->m_cBad.ModifyStyle(0,WS_VISIBLE,0);
		}

		pDlg->Invalidate(TRUE);
		pDlg->UpdateData(FALSE);
		pDlg->UpdateWindow();

		pDlg->SetTimer(47,MONITORPOLLDELAY,NULL);
		

	}
	}
	__finally {
		if (pCancel) pCancel->Release();
		if (pAsyncSync) pAsyncSync->Release();
		if (pAsyncMonitor) pAsyncMonitor->Release();
    }

	return FALSE;
}

