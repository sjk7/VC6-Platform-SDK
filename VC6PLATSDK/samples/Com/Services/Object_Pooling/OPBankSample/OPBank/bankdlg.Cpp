/*+==========================================================================
  File:      bankdlg.cpp
  Summary:   Implementation of Bank client
  Classes:   CBankDlg
-----------------------------------------------------------------------------

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
#ifndef DBNTWIN32
#define DBNTWIN32
#include <SQL.h>
#include <SQLEXT.h>
#endif

#include "BankDlg.h"
#include "..\account.vc\Account.h"
#define IID_DEFINED
#include "..\account.vc\Account_i.c"
#include "stdio.h"

#include <fstream.h>

#include "commctrl.h"
#include "stdlib.h"
#define NUMBER_OF_COLUMNS 4 // number of columns in our listview
#define FILE_VERSION	18
#define ERROR_COLUMN	2


//
// globals go here
//

HWND g_hWndResults = NULL;
HWND g_hWndSubmit = NULL;	
HWND g_hWndStop = NULL;
HWND g_hDlg = NULL;
BOOL g_bStop = FALSE;
BOOL g_bAssertOnErrors = FALSE;
BOOL g_bStopOnODBCErrors = FALSE;
BOOL g_bRetry = FALSE;
long g_nRows = 500;
HANDLE * g_pHandles = NULL;	
int g_nThreadsRunning = 0;
HACCEL	g_hAccel = NULL;
extern LARGE_INTEGER g_PerfFreq;

extern void ShowResults(BSTR sString, BOOL bError);
extern HRESULT GetRowCount(HSTMT hstmt, long * pRowCount);
extern DWORD WINAPI CreateRowsThread( LPVOID v);
extern DWORD WINAPI CreateSchemaThread( LPVOID v);
extern HRESULT VerifySchema(HSTMT hstmt);
extern HRESULT CreateSchema(HSTMT hstmt);
extern HRESULT CreateRows(long nRows, HSTMT hstmt);
extern DWORD WINAPI MoveMoneyThread( LPVOID v);
extern DWORD WINAPI AccountThread( LPVOID v);

extern DWORD WINAPI CreateRowsThread( LPVOID v);
extern HRESULT GetConnection(HENV  * phEnv, HDBC * phdbc, HSTMT * phstmt);
extern HRESULT FreeConnection(HENV henv, HDBC hdbc, HSTMT hstmt);
extern BOOL g_bUnattended;
extern WCHAR  * g_szLogFile;


THREADDATA g_pSuite[] = 
{
	
//	Test		eCoInit		iters	random	chatty	from	to	trantype	amount	threads	bCreatePerIteration, Language,	
	MOVEMONEY,	CoInitMTA,			5,		TRUE,	TRUE,	1,		2,	TRANSFER,	5,		5,		FALSE,				VC,	
	MOVEMONEY,	CoInitSTA,			5,		TRUE,	TRUE,	1,		2,	TRANSFER,	5,		1,		TRUE,				VC,	
	ACCOUNT,	CoInitMTA,			5,		TRUE,	TRUE,	1,		2,	DEBIT,		5,		1,		FALSE,				VC,	
	ACCOUNT, 	CoInitRandom,		5,		TRUE,	TRUE,	1,		2,	CREDIT,		5,		5,		FALSE,				VC	
	
};



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::CBankDlg
  Summary:  CBankDlg constructor
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CBankDlg::CBankDlg()
{
	
	
	m_nSuiteIndex = -1;	
	m_nTotalTests = sizeof(g_pSuite)/ sizeof(g_pSuite[0]);
	m_hCreateThread = NULL;	
	m_cd.bDone = TRUE; // the create data thread is not running
	m_hMenu = NULL;
	QueryPerformanceFrequency ( &g_PerfFreq);
	m_nMaxRowLength = 0;
	m_hFile = NULL;
	m_nMsgs = 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::CBankDlg
  Summary:  CBankDlg destructor
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CBankDlg::~CBankDlg()
{
	
	
	if (m_hFile)
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}

	SaveAll();

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnInitDialog
  Summary:  Initialize dialog
  Args:     UINT uMsg
			WPARAM wParam
			LPARAM lParam
			BOOL bHandled
  Returns:  LRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//
	// set global Variables
	//
	

	g_hWndResults = GetDlgItem(IDC_RESULTS);
	g_hWndSubmit = GetDlgItem(IDC_SUBMIT);	
	g_hWndStop = GetDlgItem(IDC_STOP);
	g_hDlg = m_hWnd;

	//
	//	we always want the list to be Full Row Select --
	//	note: this only works if the user has IE 3.0 installed
	//
	DWORD dwStyle = ListView_GetExtendedListViewStyle(g_hWndResults);
	dwStyle |= LVS_EX_FULLROWSELECT;
	ListView_SetExtendedListViewStyle(g_hWndResults, dwStyle);
	
	
	m_cd.nRows = GetDlgItemInt(IDC_ROWS);
	m_cd.hWndResults = GetDlgItem(IDC_RESULTS);
	m_cd.hWndStopButton = GetDlgItem(IDC_CREATE_ROWS);
		

	//
	//	create the columns in our list 
	//
	
	LV_COLUMN col;
	memset(&col,NULL, sizeof(col));
	col.mask = LVCF_TEXT|LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.cx = 40;	
	col.pszText = L"Count";
	col.cchTextMax  = lstrlen(col.pszText);
	ListView_InsertColumn(m_cd.hWndResults, 0, &col);

	
	memset(&col,NULL, sizeof(col));
	col.mask = LVCF_TEXT|LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.cx = 60;	
	col.pszText = L"ThreadId";
	col.cchTextMax  = lstrlen(col.pszText);
	ListView_InsertColumn(m_cd.hWndResults, 1, &col);

	memset(&col,NULL, sizeof(col));
	col.mask = LVCF_TEXT|LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.cx = 60;	
	col.pszText = L"Error?";
	col.cchTextMax  = lstrlen(col.pszText);
	ListView_InsertColumn(m_cd.hWndResults, 2, &col);

	memset(&col,NULL, sizeof(col));
	col.mask = LVCF_TEXT|LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.cx = 600;	
	col.pszText = L"Result";
	col.cchTextMax  = lstrlen(col.pszText);
	ListView_InsertColumn(m_cd.hWndResults, 3, &col);

	LoadAll();
	m_pCurrentThreadData = (CThreadData *)m_list.First();
	m_nSuiteIndex = 0 ;			
	UpdateStatus(m_pCurrentThreadData, m_nSuiteIndex);		
	bHandled=TRUE;	
	SetDlgItemInt(IDC_ROWS, g_nRows);
	m_hMenu = LoadMenu(_Module.m_hInst, MAKEINTRESOURCE(IDR_MENU));

	if (g_bUnattended)
	{
		m_hFile = CreateFile(g_szLogFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	}
 

	return 1;  // Let the system set the focus
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnOK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{	
	return OnClose(WM_CLOSE, 0, 0L, bHandled);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnRandom
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnRandom(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	pTd -> bRandom = 1 - pTd -> bRandom;	
	::EnableWindow(GetDlgItem(IDC_FROM), !pTd -> bRandom);
	::EnableWindow(GetDlgItem(IDC_TO), !pTd -> bRandom);	
	SetDescription(pTd);
	bHandled = TRUE;
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnKillThreads
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnKillThreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	g_bStop = TRUE;
	for (int i = 0; i< g_nThreadsRunning; i++)
	{
		TerminateThread(g_pHandles[i] ,666);
	}	
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSelectMoveMoney
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSelectMoveMoney(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	pTd -> nTestType = MOVEMONEY;
	switch (wID)
	{
	case ID_MM_CREDIT:
		pTd -> nTranType = CREDIT;
		break;
	case ID_MM_DEBIT:
		pTd -> nTranType = DEBIT;
		break;
	case ID_MM_TRANSFER:
		pTd -> nTranType = TRANSFER;
		break;
	default:
		_ASSERTE(0);
	}

	SetDescription(pTd);

	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSelectAccount
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSelectAccount(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	pTd -> nTestType = ACCOUNT;	
	switch (wID)
	{
	case ID_AC_DEBIT:
		pTd -> nTranType = DEBIT;
		break;
	case ID_AC_CREDIT:
		pTd -> nTranType = CREDIT;
		break;	
	default:
		_ASSERTE(0);
	}

	SetDescription(pTd);
	return 0;
	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSelectLanguage
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSelectLanguage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	switch (wID)
	{
	case ID_LANG_C:
		pTd -> eLang = VC;
		break;
	case ID_LANG_VB:
		pTd -> eLang = VB;
		break;
	case ID_LANG_JAVA:
		pTd -> eLang = Java;
		break;
	// (04.26.00 mdl) Include support for Delphi.
	case ID_LANG_DELPHI:
		pTd -> eLang = Delphi;
		break;
	default:
		_ASSERTE(0);
	}

	SetDescription(pTd);
	return 0;
	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSelectCreatePerIteration
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSelectCreatePerIteration(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	pTd -> bCreatePerIteration = 1 - pTd -> bCreatePerIteration;	
	bHandled = TRUE;
	SetDescription(pTd);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSelectChattyDisplay
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSelectChattyDisplay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	pTd -> bChatty = 1 - pTd -> bChatty;	
	bHandled = TRUE;
	SetDescription(pTd);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnRetryOnErrors
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnRetryOnErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = TRUE;
	g_bRetry = 1 - g_bRetry;
	return 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSelectCoInit
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSelectCoInit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	pTd -> nTestType = MOVEMONEY;
	switch (wID)
	{
	case ID_COINIT_MTA:
		pTd -> eCoInit = CoInitMTA;
		break;
	case ID_COINIT_STA:
		pTd -> eCoInit = CoInitSTA;
		break;
	case ID_COINIT_RANDOM:
		pTd -> eCoInit = CoInitRandom;
		break;
	default:
		_ASSERTE(0);
	}

	SetDescription(pTd);

	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnAssertOnErrors
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnAssertOnErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	g_bAssertOnErrors = 1 - g_bAssertOnErrors;		
	SetDescription(m_pCurrentThreadData -> GetThreadData());
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnStopOnODBCErrors
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnStopOnODBCErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	g_bStopOnODBCErrors = 	1 - g_bStopOnODBCErrors;
	SetDescription(m_pCurrentThreadData -> GetThreadData());
	return 0;
}



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnRunSuite
  Summary:	Run through several scenarios:
			1.	Account Debit in STA
			2.	MoveMoney	in STA
			3. 	Account Debit in MTA
			4. 	MoveMoney	in MTA
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnRunSuite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	//
	//	save current settings
	//	
	GetThreadData(m_pCurrentThreadData -> GetThreadData());

	::EnableWindow(GetDlgItem(IDC_SUBMIT), FALSE);
	::EnableWindow(GetDlgItem(IDC_STOP), TRUE);
	::EnableWindow(GetDlgItem(IDC_RUN_SUITE), FALSE);
	ListView_DeleteAllItems(g_hWndResults);
	SaveAll();
	CThreadData * pThreadData = (CThreadData *)m_list.First();			
	int index = 0;
	WCHAR sz[64];

	// (03.22.00 mdl) Add overall timing information for test suite.
	DWORD liStartTime = GetTickCount();	

	while ( pThreadData != (CThreadData *)&m_list)
	{
				
		UpdateStatus(pThreadData, index);
		index++;
		wsprintf(sz, L"Running Suite Test %d", index);
		ShowResults(SysAllocString(sz), FALSE);
		// Perform test based on selected language.
		DoWork(pThreadData, pThreadData -> GetThreadData() -> nTestType);	
		if (g_bStop)
			break;

		pThreadData = ( CThreadData * )pThreadData -> Next();
	}	
		
	// (03.22.00 mdl) Report total time for test.
	float t = (GetTickCount() - (float)liStartTime)  / 1000;
	swprintf(sz, L"Test suite complete.  Elapsed time: %2.4f seconds", t);
	ShowResults(SysAllocString(sz), FALSE);

	
	UpdateStatus(m_pCurrentThreadData, m_nSuiteIndex);

	::EnableWindow(GetDlgItem(IDC_RUN_SUITE), TRUE);
	::EnableWindow(GetDlgItem(IDC_SUBMIT), TRUE);
	::EnableWindow(GetDlgItem(IDC_STOP), FALSE);
	
	ShowResults(SysAllocString(L"Finished Running Test Suite."), FALSE);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::ConsumeAllMessages
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CBankDlg::ConsumeAllMessages()
{
	MSG msg;

	while ( PeekMessage( &msg, m_hWnd, 0, 0, PM_REMOVE ) )
	{
		if (!TranslateAccelerator(m_hWnd, g_hAccel, &msg))
		{
			if (!::IsDialogMessage(m_hWnd, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

	}

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnClose
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	g_bStop = TRUE;

	for (int i = 0; i< g_nThreadsRunning; i++)
	{
		TerminateThread(g_pHandles[i] ,666);
	}
	PostQuitMessage(0);
	EndDialog(0);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::DoWork
  Summary:	Start doing the actual work here...
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CBankDlg::DoWork(CThreadData * pData, int nTestType)
{
	
	POINT pt;
	::SetClassLong(m_hWnd, GCL_HCURSOR, (long)LoadCursor(NULL, IDC_APPSTARTING));
	GetCursorPos(&pt);
	SetCursorPos(pt.x, pt.y);

	g_bStop = FALSE;

	
	DWORD dwThreadId;	
	_ASSERTE(g_hWndResults);		
	switch (nTestType)
	{
				
		case MOVEMONEY:		
		{
			g_nThreadsRunning = (pData -> GetThreadData()) -> nThreads;
			g_pHandles = new HANDLE[g_nThreadsRunning];
			for (int i=0; i<g_nThreadsRunning; i++)
			{
				g_pHandles[i] = CreateThread( NULL, 0, MoveMoneyThread, (void *)pData -> GetThreadData(), NULL, &dwThreadId);
			}
			break;
		}
		case ACCOUNT:
		{
			g_nThreadsRunning = (pData -> GetThreadData()) -> nThreads;
			g_pHandles = new HANDLE[g_nThreadsRunning];
			for (int i=0; i<g_nThreadsRunning; i++)
			{
				g_pHandles[i] = CreateThread( NULL, 0, AccountThread, (void *)pData -> GetThreadData(), NULL, &dwThreadId);
			}
			break;
		}
		case VERIFY_SCHEMA:
			g_nThreadsRunning = 1;
			g_pHandles = new HANDLE[g_nThreadsRunning];
			*g_pHandles = CreateThread( NULL, 0, CreateSchemaThread, (void *)NULL, NULL, &dwThreadId);
			break;
		case CREATEROWS:
			g_nThreadsRunning = 1;
			g_pHandles = new HANDLE[g_nThreadsRunning];
			g_nRows = GetDlgItemInt(IDC_ROWS);
			*g_pHandles = CreateThread( NULL, 0, CreateRowsThread, (void *)g_nRows, NULL, &dwThreadId);
			break;
		
		default:
			_ASSERTE(0);
	}
	
	DWORD dwRet;
	int nFinishedThead = 0;		
	while (nFinishedThead <  g_nThreadsRunning)
	{
		//
		//	we wait until all threads are signaled, but we wait for them one at a time
		//	(a thread is signaled when it exits, and stays that way)...here we wait
		//	for the first thread to exit, and then wait on the second. if it has already
		//	exited, MsgWaitForMultipleObjects emmediately returns, and we wait for the next thread
		//	and so on
		//		
		dwRet = MsgWaitForMultipleObjects(1, g_pHandles + nFinishedThead, FALSE, INFINITE, QS_ALLINPUT);	
		if (dwRet == WAIT_OBJECT_0)
		{
			//
			//	 a thread finished
			//
			nFinishedThead++;				
		}
		else 
		{				
			ConsumeAllMessages();				
		}			
	}

	ConsumeAllMessages();				// there may be messages in the Q that haven't been processed since the last thread exited
	g_nThreadsRunning = 0;
	delete [] g_pHandles;
	
	g_pHandles = NULL;
	HCURSOR hCur = LoadCursor(NULL, IDC_ARROW);
	SetClassLong(m_hWnd, GCL_HCURSOR, (long)hCur);
	SetCursor(hCur);
	GetCursorPos(&pt);
	SetCursorPos(pt.x, pt.y);


}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnStop
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	g_bStop = TRUE;
	::EnableWindow(GetDlgItem(IDC_STOP), FALSE);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnGo
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnGo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	SaveAll();
	
	//
	//	save current settings
	//	
	GetThreadData(m_pCurrentThreadData -> GetThreadData());


	ListView_DeleteAllItems(g_hWndResults);
	::EnableWindow(GetDlgItem(IDC_SUBMIT), FALSE);
	::EnableWindow(GetDlgItem(IDC_STOP), TRUE);
	::EnableWindow(GetDlgItem(IDC_RUN_SUITE), FALSE);
	
	DoWork(m_pCurrentThreadData, m_pCurrentThreadData -> GetThreadData() -> nTestType);

	::EnableWindow(GetDlgItem(IDC_SUBMIT), TRUE);
	::EnableWindow(GetDlgItem(IDC_STOP), FALSE);
	::EnableWindow(GetDlgItem(IDC_RUN_SUITE), TRUE);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnDestroy
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE; // continue processing
	return 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnCreateRows
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnCreateRows(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SaveAll();
	
	//
	//	save current settings
	//	
	GetThreadData(m_pCurrentThreadData -> GetThreadData());


	ListView_DeleteAllItems(g_hWndResults);
	::EnableWindow(GetDlgItem(IDC_SUBMIT), FALSE);
	::EnableWindow(GetDlgItem(IDC_STOP), TRUE);
	::EnableWindow(GetDlgItem(IDC_RUN_SUITE), FALSE);
	
	DoWork(m_pCurrentThreadData, CREATEROWS);

	::EnableWindow(GetDlgItem(IDC_SUBMIT), TRUE);
	::EnableWindow(GetDlgItem(IDC_STOP), FALSE);
	::EnableWindow(GetDlgItem(IDC_RUN_SUITE), TRUE);	
	
	return 0;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CBankDlg::GetThreadData
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CBankDlg::GetThreadData(THREADDATA * pTd)
{
	if (!pTd)
	{
		_ASSERTE(0);
		return;
	}
	
	//
	//	get all settings from current settings except for the new UI elements
	//

	if (pTd != m_pCurrentThreadData -> GetThreadData())
	{
		memcpy(pTd, m_pCurrentThreadData -> GetThreadData(), sizeof *pTd);
	}
	pTd -> nFrom = GetDlgItemInt(IDC_FROM);
	pTd -> nTo = GetDlgItemInt(IDC_TO);		
	pTd -> nIters = GetDlgItemInt(IDC_ITERS);
	pTd -> nAmount = GetDlgItemInt(IDC_AMOUNT);
	pTd -> nThreads = GetDlgItemInt(IDC_THREADS);

	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::SetThreadData
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CBankDlg::SetThreadData(THREADDATA * pTd)
{

	if (!pTd)
	{
		_ASSERTE(0);
		return;
	}
	
	SetDlgItemInt(IDC_FROM, pTd -> nFrom );
	SetDlgItemInt(IDC_TO, pTd -> nTo);
	SetDlgItemInt(IDC_ITERS, pTd -> nIters);
	SetDlgItemInt(IDC_AMOUNT, pTd -> nAmount);
	SetDlgItemInt(IDC_THREADS, pTd -> nThreads);

	::EnableWindow(GetDlgItem(IDC_FROM), !pTd -> bRandom);
	::EnableWindow(GetDlgItem(IDC_TO), !pTd -> bRandom);

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnInitMenu
  Summary:	Allows us to update the UI in the menus
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnInitMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HMENU hMenu = (HMENU)wParam;

	THREADDATA * pTd = m_pCurrentThreadData -> GetThreadData();
	
	CheckMenuItem(hMenu, ID_MM_TRANSFER,  
				  (pTd -> nTestType == MOVEMONEY &&  pTd -> nTranType == TRANSFER) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_MM_DEBIT,  
				  (pTd -> nTestType == MOVEMONEY &&  pTd -> nTranType == DEBIT) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_MM_CREDIT,  
				  (pTd -> nTestType == MOVEMONEY &&  pTd -> nTranType == CREDIT) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_AC_DEBIT,  
				  (pTd -> nTestType == ACCOUNT &&  pTd -> nTranType == DEBIT) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, IDM_RETRY,  
				  (g_bRetry == TRUE) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_AC_CREDIT,  
				  (pTd -> nTestType == ACCOUNT &&  pTd -> nTranType == CREDIT) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_COINIT_MTA,  (pTd -> eCoInit == CoInitMTA) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_COINIT_STA,  (pTd -> eCoInit == CoInitSTA) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_COINIT_RANDOM,  (pTd -> eCoInit == CoInitRandom) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_LANG_C,  (pTd -> eLang == VC) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 
	
	CheckMenuItem(hMenu, ID_LANG_VB,  (pTd -> eLang == VB) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_LANG_JAVA,  (pTd -> eLang == Java) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	// (04.26.00 mdl) Include support for Delphi.
	CheckMenuItem(hMenu, ID_LANG_DELPHI,  (pTd -> eLang == Delphi) ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, ID_ASSERT_ON_ERRORS, g_bAssertOnErrors ? 
			  	  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, IDM_OPTION_ODBC_STOP, g_bStopOnODBCErrors ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, IDM_OPTION_CHATTY,  pTd -> bChatty ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, IDM_OPTION_CREATE_ITERATION, pTd -> bCreatePerIteration ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	CheckMenuItem(hMenu, IDM_RANDOM,    pTd -> bRandom ? 
				  MF_BYCOMMAND|MF_CHECKED : MF_BYCOMMAND|MF_UNCHECKED); 

	EnableMenuItem(hMenu, IDM_KILL_THREADS,  g_nThreadsRunning ? 
				  MF_BYCOMMAND | MF_ENABLED  : MF_BYCOMMAND | MF_GRAYED); 
	bHandled = TRUE;
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSize
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	
	int fwSizeType = wParam;      // resizing flag 
	int nWidth = LOWORD(lParam);  // width of client area 
	int nHeight = HIWORD(lParam); // height of client area 
	bHandled = FALSE;
	
	RECT rect;
	::GetWindowRect(g_hWndResults, &rect);
	
	ScreenToClient(&rect);
	
	::MoveWindow(g_hWndResults, 0, rect.top , nWidth, nHeight - rect.top, TRUE);
	return 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnShowResults
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnShowResults(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	
	if (m_hFile)
	{
		USES_CONVERSION;
		WCHAR buf[1024];
		ZeroMemory(buf, 1024 * sizeof(WCHAR));
		wsprintf(buf, L"%d\t%ld\t\t%s\r\n", m_nMsgs++, (long)wParam, (BSTR)lParam);
		DWORD dwWritten=0;
		DWORD dwSize = lstrlen(buf);
		WriteFile(m_hFile, buf, dwSize*sizeof(WCHAR), &dwWritten, NULL);
	}
	int nCount = ListView_GetItemCount(g_hWndResults); 
	LV_ITEM item;	
	WCHAR sz[8];

	wsprintf(sz, L"%ld", nCount);
	memset(&item, NULL, sizeof(item));
	item.mask = LVIF_TEXT;
	item.iItem = nCount;
	item.pszText = sz;
	item.cchTextMax = lstrlen(sz);

	ListView_InsertItem(g_hWndResults, &item);	
	wsprintf(sz,L"%ld", (DWORD)wParam);	
	ListView_SetItemText(g_hWndResults, nCount, 1, sz);
	BSTR sString = (BSTR)lParam;
	int nLen = SysStringLen(sString);
	if (nLen > m_nMaxRowLength)
		m_nMaxRowLength = nLen;
	ListView_SetItemText(g_hWndResults, nCount, 3, sString);
	ListView_EnsureVisible(g_hWndResults, nCount, FALSE);		
	SysFreeString(sString);	
	return 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnShowError
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnShowError(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;

	if (m_hFile)
	{
		USES_CONVERSION;
		WCHAR buf[1024];
		ZeroMemory(buf, 1024 * sizeof(WCHAR));
		wsprintf(buf, L"%d\t%ld\tY\t%s\r\n", m_nMsgs++, (long)wParam, (BSTR)lParam);
		DWORD dwWritten=0;
		DWORD dwSize = lstrlen(buf);
		WriteFile(m_hFile, buf, dwSize*sizeof(WCHAR), &dwWritten, NULL);
	}

	int nCount = ListView_GetItemCount(g_hWndResults); 
	LV_ITEM item;	
	WCHAR sz[8];

	wsprintf(sz, L"%ld", nCount);
	memset(&item, NULL, sizeof(item));
	item.mask = LVIF_TEXT;
	item.iItem = nCount;
	item.pszText = sz;
	item.cchTextMax = lstrlen(sz);

	ListView_InsertItem(g_hWndResults, &item);	
	wsprintf(sz,L"%ld", (DWORD)wParam);	
	ListView_SetItemText(g_hWndResults, nCount, 1, sz);
	ListView_SetItemText(g_hWndResults, nCount, 2, L"Y");
	BSTR sString = (BSTR)lParam;
	int nLen = SysStringLen(sString);
	if (nLen > m_nMaxRowLength)
		m_nMaxRowLength = nLen;
	ListView_SetItemText(g_hWndResults, nCount, 3, sString);
	ListView_EnsureVisible(g_hWndResults, nCount, FALSE);		
	SysFreeString(sString);
	return 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnViewNext
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnViewNext(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	//
	//	save current settings
	//
	GetThreadData(m_pCurrentThreadData -> GetThreadData());
	
	if (m_nSuiteIndex < m_nTotalTests - 1)
	{
		m_nSuiteIndex++;		
		m_pCurrentThreadData = (CThreadData *)m_pCurrentThreadData -> Next();
		UpdateStatus(m_pCurrentThreadData, m_nSuiteIndex);
	}
	else
	{
		MessageBeep(0);
	}

	bHandled = TRUE;
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnViewPrev
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnViewPrev(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{

	//
	//	save current settings
	//	
	GetThreadData(m_pCurrentThreadData -> GetThreadData());

	if (m_nSuiteIndex > 0)
	{
		m_nSuiteIndex--;
		m_pCurrentThreadData = (CThreadData *)m_pCurrentThreadData -> Previous();
		UpdateStatus(m_pCurrentThreadData, m_nSuiteIndex);
	}
	else
	{
		MessageBeep(0);
	}
	bHandled = TRUE;
	return 0;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::SaveAll
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CBankDlg::SaveAll()
{

	g_nRows = GetDlgItemInt(IDC_ROWS);

	char szDir[MAX_PATH];
	ZeroMemory(szDir, MAX_PATH * sizeof(char));
	GetWindowsDirectoryA(szDir, MAX_PATH);
	strncat(szDir, "\\vcbank.dat", sizeof("\\vcbank.dat"));
	ofstream of( szDir, ios::out | ios::binary , filebuf::sh_none    );

	int version = FILE_VERSION;
	of.write((BYTE*)&version, sizeof(version));
	of.write((BYTE*)&m_nTotalTests, sizeof(m_nTotalTests));
	of.write((BYTE*)&g_bAssertOnErrors, sizeof(g_bAssertOnErrors));
	of.write((BYTE*)&g_bStopOnODBCErrors, sizeof(g_bStopOnODBCErrors));
	of.write((BYTE*)&g_nRows, sizeof(g_nRows));
	of.write((BYTE*)&g_bRetry, sizeof(g_bRetry));

	int nWidth = 0;
	for (int i=0;i<NUMBER_OF_COLUMNS; i++)
	{
		nWidth = ListView_GetColumnWidth(g_hWndResults, i);
		of.write((BYTE*)&nWidth, sizeof(int));
	}


	WINDOWPLACEMENT wp;
	ZeroMemory(&wp, sizeof wp);
	wp.length = sizeof(wp);
	GetWindowPlacement(&wp);
	
	of.write((BYTE *)&wp, sizeof wp);

	CThreadData * pThreadData = NULL;
	CLinkable* pLinkable  = m_list.First();		
	while ( pLinkable != &m_list)
	{
		pThreadData = ( CThreadData * )pLinkable;			
		of.write((BYTE *)pThreadData -> GetThreadData(), sizeof(THREADDATA));
		pLinkable = pLinkable -> Next();
	}	
	
	return TRUE;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::LoadAll
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CBankDlg::LoadAll()
{

	char szDir[MAX_PATH];
	ZeroMemory(szDir, MAX_PATH * sizeof(char));
	GetWindowsDirectoryA(szDir, MAX_PATH);
	strncat(szDir, "\\vcbank.dat", sizeof("\\vcbank.dat"));
	ifstream ifs( szDir, ios::in | ios::binary , filebuf::sh_none    );

	int version = 0;

	ifs.read((BYTE *)&version, sizeof(version));

	CThreadData * pData = NULL;
	if (version != FILE_VERSION)
	{
		// use defaults
		
		g_nRows = 0;

		int i;
		for (i=0; i<m_nTotalTests; i++)
		{
			pData = new CThreadData(&g_pSuite[i]);			
			m_list.InsertLast(pData);
		}

	ShowWindow(SW_SHOWNORMAL);		
	SetDlgItemInt(IDC_ROWS, 100);
	DoWork(pData, VERIFY_SCHEMA);
	DoWork(pData, CREATEROWS);

		return TRUE;
	}

	
	ifs.read((BYTE *)&m_nTotalTests, sizeof(m_nTotalTests));
	ifs.read((BYTE *)&g_bAssertOnErrors, sizeof(g_bAssertOnErrors));
	ifs.read((BYTE *)&g_bStopOnODBCErrors, sizeof(g_bStopOnODBCErrors));
	ifs.read((BYTE *)&g_nRows, sizeof(g_nRows));
	ifs.read((BYTE *)&g_bRetry, sizeof(BOOL));

	int nWidth;
	int i; 

	for (i=0;i<NUMBER_OF_COLUMNS; i++)
	{
		ifs.read((BYTE*)&nWidth, sizeof(int));
		ListView_SetColumnWidth(g_hWndResults, i, nWidth);		
	}

	WINDOWPLACEMENT wp;
	ZeroMemory(&wp, sizeof wp);
	wp.length = sizeof(wp);		
	ifs.read((BYTE *)&wp, sizeof wp);	
	SetWindowPlacement(&wp);

	THREADDATA td;

	for (i=0; i< (int)m_nTotalTests; i++)
	{
		ifs.read((char *)&td, sizeof(THREADDATA));
		pData = new CThreadData(&td);
		m_list.InsertLast(pData);		
	}

	return TRUE;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnSave
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	SaveAll();

	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnAdd
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	
	CThreadData * pData = new CThreadData();
	GetThreadData(pData -> GetThreadData());
	m_list.InsertLast(pData);
	m_pCurrentThreadData = pData;
	m_nTotalTests++;	
	m_nSuiteIndex = m_nTotalTests - 1;
	UpdateStatus(m_pCurrentThreadData, m_nSuiteIndex);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::UpdateStatus
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CBankDlg::UpdateStatus(CThreadData * pData, int nCurItem)
{
	if (m_nTotalTests != 0)
	{
		SetThreadData(pData -> GetThreadData());
		WCHAR sz[32];
		wsprintf(sz, L"Test %d of %d", nCurItem+1, m_nTotalTests);
		SetDlgItemText(IDC_SUITE_STATUS, sz);
		SetDescription(pData -> GetThreadData());
	}
	else
	{
		THREADDATA td;
		ZeroMemory(&td, sizeof(td));
		SetThreadData(&td);
		SetDlgItemText(IDC_SUITE_STATUS, L"Test 0 of 0");
		SetDescription(NULL);
	}
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnRemove
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnRemove(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	bHandled = TRUE;
	
	if (m_nTotalTests == 0)
	{
		MessageBeep(0);
		return 0;
	}
	if (m_nSuiteIndex != m_nTotalTests - 1) // not removing the last one
	{	
		CThreadData * pData = (CThreadData * )m_pCurrentThreadData -> Next();
		m_pCurrentThreadData -> Remove();
		m_pCurrentThreadData = pData;		
	}
	else // removing the last one
	{
		CThreadData * pData = (CThreadData * )m_pCurrentThreadData -> Previous();
		m_pCurrentThreadData -> Remove();
		m_pCurrentThreadData = pData;
		m_nSuiteIndex--;
	}
	
	m_nTotalTests--;
	UpdateStatus(m_pCurrentThreadData, m_nSuiteIndex);
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnCreateTables
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnCreateTables(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::SetDescription
  Summary:	Builds a textual description of a test and displays it
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CBankDlg::SetDescription(THREADDATA *pData)
{
	if (!pData)
	{
		SetDlgItemText(IDC_DESCRIPTION, L"");
		return;
	}

	WCHAR sz[1024];
	ZeroMemory(sz, 1024*sizeof WCHAR);
	
	switch (pData -> eLang)
	{
	case VC:
		_tcsncat(sz, L"C++ ", sizeof(L"C++ "));
		break;
	case VB:
		_tcsncat(sz, L"VB ", sizeof(L"VB "));
		break;
	case Java:
		_tcsncat(sz, L"Java ", sizeof(L"Java "));
		break;
	// (04.26.00 mdl) Include support for Delphi.
	case Delphi:
		_tcsncat(sz, L"Delphi ", sizeof(L"Delphi "));
		break;
	default:
		_ASSERTE(0);
	}

	BOOL bMoveMoney = FALSE;
	switch (pData -> nTestType)
	{
	case MOVEMONEY:
		_tcsncat(sz, L"MoveMoney ", sizeof(L"MoveMoney "));
		bMoveMoney = TRUE;
		break;
	case ACCOUNT:
		_tcsncat(sz, L"Account ", sizeof(L"Account "));
		break;
	}

	switch (pData -> nTranType)
	{
	case DEBIT:
		_tcsncat(sz, L"Debit ", sizeof(L"Debit "));
		break;
	case CREDIT: 
		_tcsncat(sz, L"Credit ", sizeof(L"Credit "));
		break;
	case TRANSFER:
		_tcsncat(sz, L"Transfer ", sizeof(L"Transfer "));
		break;
	default:
		_ASSERTE(0);
	}
	
	switch (pData -> eCoInit)
	{	
	case CoInitMTA:
		_tcsncat(sz, L"in the MTA", sizeof(L"in the MTA"));
		break;
	case CoInitSTA:		
		_tcsncat(sz, L"in the STA", sizeof(L"in the STA"));
		break;
	case CoInitRandom:
		_tcsncat(sz, L"in Random Apartments ", sizeof(L"in Random Apartments "));
		break;
	default:
		_ASSERTE(0);
				
	}
	
	_tcsncat(sz, L".  ", sizeof(L".  "));
	if (pData -> bChatty)
		_tcsncat(sz, L"Chatty Mode ", sizeof(L"Chatty Mode "));
	else
		_tcsncat(sz, L"Quiet Mode ", sizeof(L"Quiet Mode "));

	if (pData -> bCreatePerIteration)
		_tcsncat(sz, L"doing a CCI Per iteration ", sizeof(L"doing a CCI Per iteration "));
	else
		_tcsncat(sz, L"Using JIT ", sizeof(L"Using JIT "));
		
	if (pData -> bRandom)
		_tcsncat(sz, L"with Random Account Numbers", sizeof(L"with Random Account Numbers"));
	else
		_tcsncat(sz, L"with Accounts numbers specified ", sizeof(L"with Accounts numbers specified "));


	
	SetDlgItemText(IDC_DESCRIPTION, sz);
	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnCopy
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	UINT nSel = ListView_GetSelectedCount( g_hWndResults); 
	
	int nChars = (nSel + 1)* (m_nMaxRowLength + 32);

	
	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE , sizeof(WCHAR) * nChars);
	WCHAR * buf = (WCHAR *)GlobalLock(hMem);
	ZeroMemory(buf, nChars * sizeof(WCHAR));
	WCHAR * p = buf;
	int nItem = -1;
	int nCol;
	int nLen = 0;

	for (nCol=0;nCol<NUMBER_OF_COLUMNS; nCol++)
	{
		

	}

	for (;;)
	{
		nItem = ListView_GetNextItem(g_hWndResults, nItem, LVNI_ALL | LVNI_SELECTED);
		if (nItem == -1)
			break;
		for (nCol=0;nCol<NUMBER_OF_COLUMNS; nCol++)
		{
			ListView_GetItemText( g_hWndResults, nItem, nCol, p, nChars); 
			nLen = lstrlen(p);
			nChars -= nLen;
			_ASSERTE(nChars > 0);
			p += nLen;
			*p++ = '\t';						
			nChars--;
		}

		*p++ = '\r';
		*p++ = '\n';
		nChars -= 2;
		_ASSERTE(nChars>0);

	}
	
	BOOL bRet =	::OpenClipboard(NULL);
	if (bRet)
	{
		GlobalUnlock(hMem);
		SetClipboardData(CF_UNICODETEXT, hMem);
		CloseClipboard();
	}
		
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnCopyAll
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnCopyAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	UINT nCount = ListView_GetItemCount( g_hWndResults); 
	
	int nChars = nCount * (m_nMaxRowLength + 32);
	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE , sizeof(WCHAR) * nChars);
	WCHAR * buf = (WCHAR *)GlobalLock(hMem);
	ZeroMemory(buf, nChars * sizeof(WCHAR));
	WCHAR * p = buf;
	UINT nItem = -1;
	int nCol;
	UINT nLen = 0;
	for (nItem = 0; nItem < nCount; nItem++)
	{
		for (nCol=0;nCol<NUMBER_OF_COLUMNS; nCol++)
		{
			ListView_GetItemText( g_hWndResults, nItem, nCol, p, nChars); 
			nLen = lstrlen(p);
			nChars -= nLen;
			_ASSERTE(nChars > 0);
			p += nLen;
			*p++ = '\t';						
			nChars--;
		}

		*p++ = '\r';
		*p++ = '\n';
		nChars -= 2;
		_ASSERTE(nChars>0);

	}
	
	BOOL bRet =	::OpenClipboard(NULL);
	if (bRet)
	{
		GlobalUnlock(hMem);
		SetClipboardData(CF_UNICODETEXT, hMem);
		CloseClipboard();
	}
		
	return 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CBankDlg::OnCopyErrors
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CBankDlg::OnCopyErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	UINT nCount = ListView_GetItemCount( g_hWndResults); 	
	int nChars = nCount * (m_nMaxRowLength + 32);
	HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE|GMEM_DDESHARE , sizeof(WCHAR) * nChars);
	WCHAR * buf = (WCHAR *)GlobalLock(hMem);
	ZeroMemory(buf, nChars * sizeof(WCHAR));
	WCHAR * p = buf;
	UINT nItem = -1;
	int nCol;
	UINT nLen = 0;
	int nErrors = 0;
	for (nItem = 0; nItem < nCount; nItem++)
	{
		ListView_GetItemText( g_hWndResults, nItem, ERROR_COLUMN, p, nChars); 
		if (*p)
		{
			*p = NULL;
			nErrors++;
			for (nCol=0;nCol<NUMBER_OF_COLUMNS; nCol++)
			{
				ListView_GetItemText( g_hWndResults, nItem, nCol, p, nChars); 
				nLen = lstrlen(p);
				nChars -= nLen;
				_ASSERTE(nChars > 0);
				p += nLen;
				*p++ = '\t';						
				nChars--;
			}

			*p++ = '\r';
			*p++ = '\n';
			nChars -= 2;
			_ASSERTE(nChars>0);
		}

	}
	

	GlobalUnlock(hMem);
	if (nErrors == 0)
	{
		GlobalFree(hMem);
	}
	else
	{

		BOOL bRet =	::OpenClipboard(NULL);
		if (bRet)
		{	
			SetClipboardData(CF_UNICODETEXT, hMem);
			CloseClipboard();
		}
	}
		
	return 0;	
}

