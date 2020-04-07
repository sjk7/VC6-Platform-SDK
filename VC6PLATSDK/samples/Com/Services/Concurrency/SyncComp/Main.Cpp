/*+==========================================================================

File: Main.cpp

Summary: Implementation of CMain which handles all of the work for the client

Classes: CMain
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

#include "stdafx.h"
#include "Main.h"

#ifdef _DEBUG_OBJECTS
#import "STAObject\Debug\STAObject.dll" no_namespace 
#import "FreeObject\Debug\FreeObject.dll" no_namespace exclude("ISyncTest")
#import "ComSyncObject\Debug\ComSyncObject.dll" no_namespace exclude("ISyncTest")
#else
#import "STAObject\ReleaseMinSize\STAObject.dll" no_namespace 
#import "FreeObject\ReleaseMinSize\FreeObject.dll" no_namespace exclude("ISyncTest")
#import "ComSyncObject\ReleaseMinSize\ComSyncObject.dll" no_namespace exclude("ISyncTest")
#endif

#define IDT_UIUPDATE 500		// just a timer ID

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CMain

CMain is the class associated with the MAIN dialog. This class handles all the 
messages and the thread handling.

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: ThreadStart

Summary: This is the startup routine for the threads. This method calls into
		 the standard Interface of the desired object and measures and records
		 the time required for each call.

Args: 'this' pointer for easy reference back into ourselves

Returns: 0

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMain::ThreadStart(LPVOID lp)
{
	CMain			*pThis;
	HRESULT			hRes = S_OK;
	LARGE_INTEGER	llTick1, llTick2, llFreq;
	DWORD			lDeltaTick = 0;
	ISyncTestPtr	pSyncTest;
	int				iIter;

	// cast our incoming void pointer to our class
	pThis = (CMain*)lp;

	// increment the number of running threads
	InterlockedIncrement((LONG *)&pThis->m_curThreadCount);

	hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	_ASSERTE(SUCCEEDED(hRes));
	
	// get the interface of the created object from the GIT
	hRes = g_pGIT->GetInterfaceFromGlobal(pThis->m_iCookie, __uuidof(ISyncTest), (void **)&pSyncTest);
	_ASSERTE(SUCCEEDED(hRes));

	// get the frequency of our counter
	QueryPerformanceFrequency(&llFreq);

	// call the Exercise function the number of times desired
	for (iIter = 0;iIter < pThis->m_iIters; iIter++) 
	{
		// watch for a signal to stop
		if (pThis->m_bStop)
			break;

		// get the starting tick
		QueryPerformanceCounter(&llTick1);

		// make a call into the object
		hRes = pSyncTest->Exercise();
	    _ASSERTE(SUCCEEDED(hRes));

		// get the ending tick
		QueryPerformanceCounter(&llTick2);

		// calculate our elapsed time in ms
		lDeltaTick = (DWORD) ((float)(llTick2.LowPart - llTick1.LowPart) / llFreq.LowPart * 1000);

		// update all of our counters
		pThis->UpdateCounters(lDeltaTick);
	}

	// decrement the number of threads
	InterlockedDecrement((LONG *)&pThis->m_curThreadCount);

	CoUninitialize();

	return 0;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: UpdateCounters

Summary: Updates all of the counters used to update our UI using thread safe methods

Args: DWORD lDelta - the amount of time the last call required

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CMain::UpdateCounters(DWORD lDelta)
{
	DWORD curValue;

	// update the counters used by the UI

	InterlockedIncrement((LONG*)&m_dwTotalIters);
	InterlockedExchangeAdd((LONG*)&m_dwTotalTime, lDelta);

	// compare and change our values.
	// this is where we need m_dwMaxTime and m_dwMinTime to be volatile
	curValue = m_dwMaxTime;
	if (lDelta > curValue) 
	{
		InterlockedCompareExchange((LONG*)&m_dwMaxTime, lDelta, curValue);
	}
	else 
	{
		curValue = m_dwMinTime;
		if (lDelta <= curValue) 
		{
			InterlockedCompareExchange((LONG*)&m_dwMinTime, lDelta, curValue);
		}
	}
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: OnInitDialog

Summary: Setup the controls on the dialog

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMain::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// start with the STA radio button checked
	SendDlgItemMessage(IDC_RADIO_STA, BM_SETCHECK, BST_CHECKED);
	e_compType = eSTA;

	// set up some default threads and iterations
	SendDlgItemMessage(IDC_THREADCOUNT, EM_LIMITTEXT, 4);
	SetDlgItemText(IDC_THREADCOUNT, _T("50"));

	SendDlgItemMessage(IDC_ITERCOUNT, EM_LIMITTEXT, 6);
	SetDlgItemText(IDC_ITERCOUNT, _T("1000"));

	// Center ourselves
	CenterWindow();

	return 1;  // Let the system set the focus
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: OnClickedStart

Summary: This routine performs all of the thread creation and waits for them to 
		 finish while pumping messages. It also sets up the timer that indicates 
		 that we should update our UI.

		 This function also serves as the Cancel button if the correct flag is set.

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMain::OnClickedStart(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	int iThread, iMaxThread;
	HANDLE *aThread;
	HRESULT hRes = S_OK;
	MSG	msg;
	int iCountSignled = 0;
	DWORD result = 0;
	static BOOL bButtonCancel = FALSE;

	// check and see if we are a Start or Cancel
	if (bButtonCancel == TRUE) 
	{
		// we are cancel so increment our variable. Our threads are watching this value
		// and will terminate when it isn't zero
		InterlockedIncrement((LONG*)&m_bStop);
	}
	else 
	{
		// make our button a cancel
		SetDlgItemText(IDC_START, "Cancel");
		bButtonCancel = TRUE;
		// clear our stop indicator
		m_bStop = 0;

		// get an hourglass
	    HCURSOR cOld=SetCursor(LoadCursor(NULL, IDC_WAIT));

		// disable our radio buttons
		::EnableWindow(GetDlgItem(IDC_RADIO_COMSYNC), FALSE);
		::EnableWindow(GetDlgItem(IDC_RADIO_FREE), FALSE);
		::EnableWindow(GetDlgItem(IDC_RADIO_STA), FALSE);
	
		// set our timer to do the UI updates
		SetTimer(IDT_UIUPDATE, 1000);

		// reset all of the counters
		m_dwMaxTime = m_dwTotalIters = 0;
		m_dwTotalTime = 0;
		m_dwMinTime = MAXDWORD;
		m_curThreadCount = 0;

		// get the Thread count and the number of iterations
		iMaxThread = GetDlgItemInt(IDC_THREADCOUNT, NULL, FALSE);
		m_iIters = GetDlgItemInt(IDC_ITERCOUNT, NULL, FALSE);

		// set up our thread calling arrary for the handles
		aThread = new HANDLE[iMaxThread];

		// -----------
		// get the correct COM object and register it in the GIT
		// -----------
		ISyncTestPtr	pSyncTest;

		// depending on the select depends on what object we create
		switch (e_compType) 
		{
			case eSTA:
				pSyncTest.CreateInstance(__uuidof(STATest));
				break;
			case eFree: 
				pSyncTest.CreateInstance(__uuidof(FreeTest));
				break;
			case eCOMPlus:
				pSyncTest.CreateInstance(__uuidof(ComSyncTest));
				break;
		}

		// register our object in the GIT
		hRes = g_pGIT->RegisterInterfaceInGlobal(pSyncTest, __uuidof(ISyncTest), &m_iCookie);
		_ASSERTE(SUCCEEDED(hRes));

		// spin up all of the threads - we start suspended so we have a better chance of getting 
		// all the threads running at one time
		for (iThread = 0; iThread < iMaxThread; iThread++) 
		{
			aThread[iThread] = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) ThreadStart, (LPVOID) this, CREATE_SUSPENDED , NULL);
		}

		// let all the threads start
		for (iThread = 0; iThread < iMaxThread; iThread++) 
		{
			ResumeThread(aThread[iThread]);
		}

		// wait for the threads to be done but keep pumping message
		while (iMaxThread > 0) 
		{
			// wait for a message or a thread to exit
			result = WaitForMultipleObjects((iMaxThread > MAXIMUM_WAIT_OBJECTS) ? MAXIMUM_WAIT_OBJECTS : iMaxThread, aThread, FALSE, 250);
			// pump any messages that have built up
			while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) 
			{
				DispatchMessage(&msg);
			}
			// if we failed just ASSERT we shouldn't be failing
			if (result == WAIT_FAILED) 
			{
				result = GetLastError();
				_ASSERTE(FALSE);
			}
			else
			// -----------
			// if one of our objects completed then close that handle and remove
			// that handle from the array of handles to wait on
			// -----------
			if (result < WAIT_OBJECT_0 + iMaxThread) 
			{
				// move the last handle we were waiting on into the spot we just finished

				// make sure we close the handle before we lose it
				CloseHandle(aThread[result-WAIT_OBJECT_0]);
				// replace the handle of the thread that just ended with the last one in the list
				aThread[result-WAIT_OBJECT_0] = aThread[iMaxThread - 1];
				// we have one less thread to watch
				iMaxThread--;
			}
		}

		// Stop the timer and update our UI one last time
		KillTimer(IDT_UIUPDATE);
		UpdateUI();
		
		// remove our object from the GIT
		hRes = g_pGIT->RevokeInterfaceFromGlobal(m_iCookie);
		_ASSERTE(SUCCEEDED(hRes));

		// clean up
		delete[] aThread;

		// enable our radio buttons
		::EnableWindow(GetDlgItem(IDC_RADIO_COMSYNC), TRUE);
		::EnableWindow(GetDlgItem(IDC_RADIO_FREE), TRUE);
		::EnableWindow(GetDlgItem(IDC_RADIO_STA), TRUE);

		// put cursor back
	    cOld=SetCursor(LoadCursor(NULL, IDC_WAIT));

		// put our button back
		bButtonCancel = FALSE;
		SetDlgItemText(IDC_START, "Start");
	}

	return 0;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: OnTimer

Summary: this is called by the MessageMap in response to the WM_TIMER message.
		 we just pass onto our UpdateUI function

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMain::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// just forward the call
	UpdateUI();
	return 0;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: UpdateUI

Summary: This updates all the information text boxes on the dialog

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CMain::UpdateUI(void)
{
	// we just need to update the UI when our timer fires
	
	TCHAR szBuffer[40];

	// update the UI
	SetDlgItemInt(IDC_MAXTIMEBASE + e_compType, m_dwMaxTime);
	SetDlgItemInt(IDC_MINTIMEBASE + e_compType, m_dwMinTime);

	_snprintf(szBuffer, 40, "%4.2f", (float) m_dwTotalTime / m_dwTotalIters);
	SetDlgItemText(IDC_AVGTIMEBASE + e_compType, szBuffer);
	
	_snprintf(szBuffer, 40, "%ld", m_dwTotalIters);
	SetDlgItemText(IDC_ITERTOTAL, szBuffer);

	SetDlgItemInt(IDC_THREADRUNNING, m_curThreadCount);

}