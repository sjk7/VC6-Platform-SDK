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
// ----------------------------------------------------------------------------
#define _WIN32_WINNT 0x0400
#define STRICT
#include <Windows.h>
#include <WindowsX.h>
#include <stdio.h>
#include <tchar.h>
#include <initguid.h>
#include "Resource.h"


HWND hWndDialog;

typedef struct params
{
	BOOL bInProcess;
	DWORD dwThreadType;
	DWORD dwObjectType;
	TCHAR szMachine[300];
} PARAMS;

HANDLE g_NotifyPrimarySTAEvent;

// {37824810-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_NoneCancelObject, 0x37824810, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);

// {37824811-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_STACancelObject, 0x37824811, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);

// {37824812-ADBA-11d1-B6FB-00A024A85A1F}
DEFINE_GUID(CLSID_MTACancelObject, 0x37824812, 0xadba, 0x11d1, 0xb6, 0xfb, 0x0, 0xa0, 0x24, 0xa8, 0x5a, 0x1f);



void
Message(LPTSTR szPrefix, HRESULT hr)
{
    LPTSTR   szMessage;
	TCHAR szDisplay[1000];

    if (hr == S_OK)
        {
		_stprintf(szDisplay, TEXT("%s"), szPrefix);
		MessageBox(hWndDialog, szDisplay, TEXT("Msg"),0);
        return;
        }

    if (HRESULT_FACILITY(hr) == FACILITY_WIN32)
        hr = HRESULT_CODE(hr);

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
        (LPTSTR)&szMessage,
        0,
        NULL );

    _stprintf(szDisplay, TEXT("%s: %s(%lx)"), szPrefix, szMessage, hr);
	MessageBox(hWndDialog, szDisplay, TEXT("Msg"),0);
    LocalFree(szMessage);
}  // Message


DWORD WINAPI ThreadProc(LPVOID lp)
{
    MULTI_QI    mq;
    COSERVERINFO csi, *pcsi=NULL;
	HRESULT hr = S_OK;
	IPersist *pPersist = NULL;
	HWND hwnd1=NULL, hwnd2=NULL, hwnd3=NULL;
	DWORD dwCls;
	PARAMS p = *(PARAMS*)lp;
	CLSID clsid;

        if (p.bInProcess)
	{
		if (COINIT_APARTMENTTHREADED == p.dwThreadType && (p.dwObjectType == 0))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_INPROC_STA2STA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_INPROC_STA2STA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_INPROC_STA2STA_CANCELCALL);
		}
		else if (COINIT_APARTMENTTHREADED == p.dwThreadType && (p.dwObjectType == 2))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_INPROC_STA2MTA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_INPROC_STA2MTA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_INPROC_STA2MTA_CANCELCALL);

		}
		else if (COINIT_MULTITHREADED == p.dwThreadType && (p.dwObjectType == 1))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_INPROC_MTA2STA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_INPROC_MTA2STA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_INPROC_MTA2STA_CANCELCALL);
		}
		dwCls = CLSCTX_INPROC_SERVER;	
		clsid = (p.dwObjectType == 0) ? CLSID_NoneCancelObject:
				((p.dwObjectType == 2) ? CLSID_MTACancelObject:CLSID_STACancelObject);
	}
	else
	{
		if (COINIT_APARTMENTTHREADED == p.dwThreadType && !(p.dwObjectType))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_OUTPROC_STA2STA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_OUTPROC_STA2STA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_OUTPROC_STA2STA_CANCELCALL);

		}
		else if (COINIT_APARTMENTTHREADED == p.dwThreadType && (p.dwObjectType))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_OUTPROC_STA2MTA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_OUTPROC_STA2MTA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_OUTPROC_STA2MTA_CANCELCALL);

		}
		else if (COINIT_MULTITHREADED == p.dwThreadType && !(p.dwObjectType))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_OUTPROC_MTA2STA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_OUTPROC_MTA2STA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_OUTPROC_MTA2STA_CANCELCALL);
		}
		else if (COINIT_MULTITHREADED == p.dwThreadType && (p.dwObjectType))
		{
			hwnd1 = GetDlgItem(hWndDialog, IDC_OUTPROC_MTA2MTA);
			hwnd2 = GetDlgItem(hWndDialog, IDC_OUTPROC_MTA2MTA_CANCELACT);
			hwnd3 = GetDlgItem(hWndDialog, IDC_OUTPROC_MTA2MTA_CANCELCALL);

		}
		if (lstrlen(p.szMachine))
		{
			memset(&csi, 0, sizeof(COSERVERINFO));
			csi.pwszName = p.szMachine;
			pcsi = &csi;
		}
		dwCls = CLSCTX_LOCAL_SERVER;	
		clsid = (p.dwObjectType) ? CLSID_MTACancelObject:CLSID_STACancelObject;
	}

	EnableWindow(hwnd1, FALSE);
	CoInitializeEx(NULL, p.dwThreadType);
	if FAILED(hr)
	{
		Message(TEXT("CoInitializeEx"), hr);
		goto cleanup;
	}

        hr = CoEnableCallCancellation(NULL);
	if FAILED(hr)
	{
		Message(TEXT("CoEnableCallCancellation"), hr);
		goto cleanup;
	}

        mq.pIID = &IID_IPersist;
	mq.pItf = NULL;
	mq.hr = S_OK;
	
	

	EnableWindow(hwnd2, TRUE);
	hr = CoCreateInstanceEx(clsid, NULL, dwCls, pcsi, 1, &mq);
	if FAILED(hr)
	{
		Message(TEXT("CoCreateInstanceEx"), hr);
		goto cleanup;
	}

	EnableWindow(hwnd2, FALSE);
	pPersist = (IPersist*)mq.pItf;
	
	if (!pPersist)
		goto cleanup;
	EnableWindow(hwnd3, TRUE);
	hr = pPersist->GetClassID(&clsid);
	if FAILED(hr)
	{
		Message(TEXT("Method"), hr);
		goto cleanup;
	}
	EnableWindow(hwnd3, FALSE);
	pPersist->Release();

        CoDisableCallCancellation(NULL);
	CoUninitialize();
cleanup:
	EnableWindow(hwnd1, TRUE);
	EnableWindow(hwnd2, FALSE);
	EnableWindow(hwnd3, FALSE);
	return hr;
}

void CANCEL_OnTimer(HWND hwnd, UINT nID)
{
	UNREFERENCED_PARAMETER(hwnd);
	UNREFERENCED_PARAMETER(nID);
	CoFreeUnusedLibraries();
}

//////////////////////////////////////////////////////////////


BOOL CANCEL_OnInitDialog(HWND hwnd,
   HWND hwndFocus, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	UNREFERENCED_PARAMETER(hwndFocus);
	hWndDialog = hwnd;
	EnableWindow(GetDlgItem(hwnd, IDC_INPROC_STA2STA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_INPROC_STA2STA_CANCELCALL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_INPROC_STA2MTA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_INPROC_STA2MTA_CANCELCALL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_INPROC_MTA2STA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_INPROC_MTA2STA_CANCELCALL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_STA2STA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_STA2MTA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_MTA2STA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_MTA2MTA_CANCELACT), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_STA2STA_CANCELCALL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_STA2MTA_CANCELCALL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_MTA2STA_CANCELCALL), FALSE);
	EnableWindow(GetDlgItem(hwnd, IDC_OUTPROC_MTA2MTA_CANCELCALL), FALSE);
	SetTimer(hwnd, 1, 5000, NULL);
	return(TRUE);
}


void CANCEL_OnCommand(HWND hwnd,
   int id, HWND hwndCtl, UINT codeNotify) {

	UNREFERENCED_PARAMETER(codeNotify);
	UNREFERENCED_PARAMETER(hwndCtl);
	static DWORD dwInProcSTA2STA;
	HANDLE hInProcSTA2STA;
	static DWORD dwInProcSTA2MTA;
	HANDLE hInProcSTA2MTA;
	static DWORD dwInProcMTA2STA;
	HANDLE hInProcMTA2STA;

	static DWORD dwOutProcSTA2STA;
	HANDLE hOutProcSTA2STA;
	static DWORD dwOutProcSTA2MTA;
	HANDLE hOutProcSTA2MTA;
	static DWORD dwOutProcMTA2STA;
	HANDLE hOutProcMTA2STA;
	static DWORD dwOutProcMTA2MTA;
	HANDLE hOutProcMTA2MTA;
	
	static PARAMS p;
	HRESULT hr;

	switch (id) {
	case IDC_INPROC_STA2STA:
		p.bInProcess = TRUE;
		p.dwThreadType = COINIT_APARTMENTTHREADED;
		p.dwObjectType = 0;
		hInProcSTA2STA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwInProcSTA2STA);
		if (!hInProcSTA2STA)
		{
			Message(TEXT("CreateThread"), GetLastError());
		}
		else
			CloseHandle(hInProcSTA2STA);
		break;
	case IDC_INPROC_STA2MTA:
		p.bInProcess = TRUE;
		p.dwThreadType = COINIT_APARTMENTTHREADED;
		p.dwObjectType = 2;
		hInProcSTA2MTA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwInProcSTA2MTA);
		if (!hInProcSTA2MTA)
		{
			Message(TEXT("CreateThread"),  GetLastError());
		}
		else
			CloseHandle(hInProcSTA2MTA);
		break;
	case IDC_INPROC_MTA2STA:
		p.bInProcess = TRUE;
		p.dwThreadType = COINIT_MULTITHREADED;
		p.dwObjectType = 1;
		hInProcMTA2STA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwInProcMTA2STA);
		if (!hInProcMTA2STA)
		{
			Message(TEXT("CreateThread"),  GetLastError());
		}
		else
			CloseHandle(hInProcMTA2STA);
		break;
	case IDC_OUTPROC_STA2STA:
		p.bInProcess = FALSE;
		p.dwThreadType = COINIT_APARTMENTTHREADED;
		p.dwObjectType = 0;
		GetDlgItemText(hwnd, IDC_MACHINE, p.szMachine, sizeof(p.szMachine));
		hOutProcSTA2STA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwOutProcSTA2STA);
		if (!hOutProcSTA2STA)
		{
			Message(TEXT("CreateThread"),  GetLastError());
		}
		else
			CloseHandle(hOutProcSTA2STA);
		break;
	case IDC_OUTPROC_STA2MTA:
		p.bInProcess = FALSE;
		p.dwThreadType = COINIT_APARTMENTTHREADED;
		p.dwObjectType = 1;
		GetDlgItemText(hwnd, IDC_MACHINE, p.szMachine, sizeof(p.szMachine));
		hOutProcSTA2MTA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwOutProcSTA2MTA);
		if (!hOutProcSTA2MTA)
		{
			Message(TEXT("CreateThread"), GetLastError());
		}
		else
			CloseHandle(hOutProcSTA2MTA);
		break;
	case IDC_OUTPROC_MTA2STA:
		p.bInProcess = FALSE;
		p.dwThreadType = COINIT_MULTITHREADED;
		p.dwObjectType = 0;
		GetDlgItemText(hwnd, IDC_MACHINE, p.szMachine, sizeof(p.szMachine));
		hOutProcMTA2STA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwOutProcMTA2STA);
		if (!hOutProcMTA2STA)
		{
			Message(TEXT("CreateThread"), GetLastError());
		}
		else
			CloseHandle(hOutProcMTA2STA);
		break;
	case IDC_OUTPROC_MTA2MTA:
		p.bInProcess = FALSE;
		p.dwThreadType = COINIT_MULTITHREADED;
		p.dwObjectType = 1;
		GetDlgItemText(hwnd, IDC_MACHINE, p.szMachine, sizeof(p.szMachine));
		hOutProcMTA2MTA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,(LPVOID)&p, 0,
			&dwOutProcMTA2MTA);
		if (!hOutProcMTA2MTA)
		{
			Message(TEXT("CreateThread"), GetLastError());
		}
		else
			CloseHandle(hOutProcMTA2MTA);
		break;
	case IDC_INPROC_STA2STA_CANCELACT:
	case IDC_INPROC_STA2STA_CANCELCALL:
		hr = CoCancelCall(dwInProcSTA2STA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }
		break;
	case IDC_INPROC_STA2MTA_CANCELACT:
	case IDC_INPROC_STA2MTA_CANCELCALL:
		hr = CoCancelCall(dwInProcSTA2MTA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }

		break;
	case IDC_INPROC_MTA2STA_CANCELACT:
	case IDC_INPROC_MTA2STA_CANCELCALL:
		hr = CoCancelCall(dwInProcMTA2STA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }
		break;
	case IDC_OUTPROC_STA2STA_CANCELACT:
	case IDC_OUTPROC_STA2STA_CANCELCALL:
		hr = CoCancelCall(dwOutProcSTA2STA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }
		break;
	case IDC_OUTPROC_STA2MTA_CANCELACT:
	case IDC_OUTPROC_STA2MTA_CANCELCALL:
		hr = CoCancelCall(dwOutProcSTA2MTA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }
		break;
	case IDC_OUTPROC_MTA2STA_CANCELACT:
	case IDC_OUTPROC_MTA2STA_CANCELCALL:
		hr = CoCancelCall(dwOutProcMTA2STA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }
		break;
	case IDC_OUTPROC_MTA2MTA_CANCELACT:
	case IDC_OUTPROC_MTA2MTA_CANCELCALL:
		hr = CoCancelCall(dwOutProcMTA2MTA, 0);
		if (FAILED(hr))
        {
			Message(TEXT("CoCancelCall"), hr);
			return;
        }
		break;

	case IDCANCEL:	
			// If the Escape key is hit, destroy the modeless
			// dialog box, terminating the application.
			DestroyWindow(hwnd);
			break;

   }
}


//////////////////////////////////////////////////////////////


INT_PTR WINAPI CANCEL_DlgProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
   switch (uMsg) {
      HANDLE_MSG(hwnd, WM_INITDIALOG, CANCEL_OnInitDialog);
      HANDLE_MSG(hwnd, WM_COMMAND, CANCEL_OnCommand);
      HANDLE_MSG(hwnd, WM_TIMER, CANCEL_OnTimer);
   }
   return(FALSE);
}


DWORD WINAPI PrimarySTAThreadProc(LPVOID lp)
{
	UNREFERENCED_PARAMETER(lp);
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if FAILED(hr)
	{
		Message(TEXT("CoInitializeEx"), hr);
		return hr;
	}
	SetEvent(g_NotifyPrimarySTAEvent);

	MSG msg;
	while (true==true)
	{
		if (WaitForSingleObject(g_NotifyPrimarySTAEvent, 0) == WAIT_OBJECT_0)
		{
			break;
		}
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	CoUninitialize();
    return hr;
}



//////////////////////////////////////////////////////////////



int WINAPI WinMain (HINSTANCE hinstExe,
   HINSTANCE hinstExePrev, LPSTR pszCmdLine, int nCmdShow) {
	
	UNREFERENCED_PARAMETER(nCmdShow);
	UNREFERENCED_PARAMETER(pszCmdLine);
	UNREFERENCED_PARAMETER(hinstExePrev);
	g_NotifyPrimarySTAEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (g_NotifyPrimarySTAEvent == NULL)
	{
		Message(TEXT("CreateEvent"), GetLastError());
		return -1;
	}
	DWORD dwPrimarySTA;
	HANDLE hPrimarySTA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PrimarySTAThreadProc,NULL, 0,
		&dwPrimarySTA);
	if (!hPrimarySTA)
	{
		Message(TEXT("CreateThread"), GetLastError());
		return -1;
	}
	WaitForSingleObject(g_NotifyPrimarySTAEvent, INFINITE);
	
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if FAILED(hr)
	{
		Message(TEXT("CoInitializeEx"), hr);
		return hr;
	}
 	hr = CoInitializeSecurity( NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY,
		NULL, EOAC_NONE, NULL );
    if (FAILED(hr))
        {
        Message(TEXT("CoInitializeSecurity"), hr);
        return hr;
        }

	// Create the appication's UI window
	DialogBox(hinstExe,
      MAKEINTRESOURCE(IDD_CANCEL_DIALOG), NULL, CANCEL_DlgProc);
	SetEvent(g_NotifyPrimarySTAEvent);
	WaitForSingleObject(hPrimarySTA, INFINITE);
	CloseHandle(hPrimarySTA);
	CoUninitialize();
    return(0);  // End the application
}

