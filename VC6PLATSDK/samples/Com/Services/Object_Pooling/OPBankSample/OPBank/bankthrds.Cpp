/*+==========================================================================
  File:      bankthrds.cpp
  Summary:   Thread routines for Bank client
  Classes:   None
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

#define MSG_BUF_SIZE	256

#include "BankDlg.h"
#include "stdio.h"


#include <fstream.h>

#include "commctrl.h"
#include "stdlib.h"

#include "..\account.vc\account_i.c"
#include "..\account.vc\account.h"

#define SQL_FAILED(rc)  ( (rc) != SQL_SUCCESS && (rc) != SQL_SUCCESS_WITH_INFO)
#define ASSERT_SQL_SUCCESS(rc) { _ASSERTE(rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO);}

//
//	execute these queries to create the schema
//
static LPOLESTR sCreateSchema[] = 
{
	L"if exists (select * from sysobjects where id = object_id('dbo.VcAccount') and sysstat & 0xf = 3)	drop table dbo.VcAccount",
	L"CREATE TABLE dbo.VcAccount (AccountNo int IDENTITY (1, 1) NOT NULL ,Balance int NULL, Name char (255) NULL, CONSTRAINT PK___1__17 PRIMARY KEY  CLUSTERED(AccountNo))",
	L"if exists (select * from sysobjects where id = object_id('dbo.Receipt') and sysstat & 0xf = 3)	drop table dbo.Receipt",
	L"CREATE TABLE dbo.Receipt (NextReceipt int NULL)"
};

//
//	execute these queries (and check SQLRowCount()) to verify schema
//	
static LPOLESTR sCheckSchema[] = 
{
	L"select * from sysobjects where id = object_id('dbo.VcAccount') and sysstat & 0xf = 3",	
	L"select * from sysobjects where id = object_id('dbo.Receipt') and sysstat & 0xf = 3)"	
};

HRESULT GetConnection(HENV  * phEnv, HDBC * phdbc, HSTMT * phstmt);
HRESULT GetRowCount(HSTMT hstmt, long * pRowCount);
HRESULT FreeConnection(HENV henv, HDBC hdbc, HSTMT hstmt);
HRESULT VerifySchema(HSTMT hstmt);
HRESULT CreateSchema(HSTMT hstmt);
HRESULT CreateRows(long nRows, HSTMT hstmt);
LARGE_INTEGER g_PerfFreq;
void ShowResults(BSTR sString, BOOL bError);
extern long g_nRows;
extern BOOL g_bRetry;


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: RandInt
  Summary:  Return a random integer with 0 <= i < max
			This routine is thread-safe, and returns different random number
			streams for each thread.
			In 48-bit arithmentic, set seed = seed * multiplier + increment
			Then, take the upper-most 32 bits and multiply by ulMax.
			The overflow into the next DWORD is the return value.
  Args:     unsigned long ulMax		Max integer size
  Returns:  unsigned long
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
static const unsigned long g_ulTlsRandomHigh = TlsAlloc();
static const unsigned long g_ulTlsRandomLow = TlsAlloc();
static const __int64 g_llMultiplier = 0x5DEECE66D;
static const __int64 g_llIncrement = 0xB;
union UnionInt64 { __int64 n; unsigned long l[2]; unsigned short i[4]; };

unsigned long RandInt (unsigned long ulMax)
{

	UnionInt64 seed;
	seed.l[1] = (unsigned long) TlsGetValue (g_ulTlsRandomHigh);
	seed.l[0] = (unsigned long) TlsGetValue (g_ulTlsRandomLow);

	if (seed.n == 0)
	{
		// initialize random number stream
		seed.l[1] = GetCurrentThreadId();
		seed.l[0] = GetTickCount();
		seed.n ^= g_llMultiplier;
		seed.i[3] = 0;
	}

	seed.n = seed.n * g_llMultiplier + g_llIncrement;
	seed.i[3] = 0;	// clear high 16 bits;

	TlsSetValue (g_ulTlsRandomHigh, (void*) seed.l[1]);
	TlsSetValue (g_ulTlsRandomLow, (void*) seed.l[0]);

	// shift so that high DWORD is zero, low DWORD contains most significant bits
	seed.i[0] = seed.i[1];
	seed.i[1] = seed.i[2];
	seed.i[2] = 0;

	seed.n *= ulMax;
	return seed.l[1];
}


extern HWND g_hWndResults;
extern HWND g_hWndSubmit;	
extern HWND g_hWndStop;
extern HWND g_hDlg;
extern BOOL g_bStop;
extern BOOL g_bAssertOnErrors;
extern BOOL g_bStopOnODBCErrors;


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateObject
  Summary:  All calls to create a COM object end up here
  Args:     REFCLSID clsid		Class ID to create
			DWORD clsctx		clsctx to create object
			REFIID iid			Interface ID
			void **ppv			Reference to interface
			DWORD *pdwTime		Time is ms to do the create
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT CreateObject(REFCLSID clsid, DWORD clsctx, REFIID iid, void **ppv, DWORD * pdwTime)
{

	HRESULT hr = E_FAIL;	
	LARGE_INTEGER stop;	
	LARGE_INTEGER start;		
	LARGE_INTEGER total;	

	QueryPerformanceCounter( &start);
	hr = CoCreateInstance(clsid, NULL, clsctx, iid, ppv);
	QueryPerformanceCounter( &stop);		
	total.QuadPart = 1000*(stop.QuadPart-start.QuadPart)/g_PerfFreq.QuadPart;
	if (total.HighPart != 0)
		ShowResults(SysAllocString(L"Overflow in performance counters!"), TRUE);

	*pdwTime  = total.LowPart;

	return hr;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetOdbcError
  Summary:  Call SQLError to get the error from ODBC
  Args:     HENV henv		An ODBC environment handle
			HDBC hdbc		An ODBC database connection handle
			HSTMT hstmt		An ODBC statement handle
			BSTR* sErr		Output error string
  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
void GetOdbcError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR * sErr)
{
		WCHAR szSqlState[64];
		SDWORD NativeError;
		WCHAR szErr[512];
		SWORD cbErrorMsg;
		SQLError(henv, hdbc, hstmt, (SQLWCHAR *)szSqlState, &NativeError, (SQLWCHAR *)szErr, 511, &cbErrorMsg);
		*sErr = ::SysAllocString(szErr);
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ShowResults
  Summary:  Show the results in a listview (not thread safe)
  Args:     BSTR sString	String to display
			BOOL bError		Is this an error?	
  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
void ShowResults(BSTR sString, BOOL bError)
{	
		
	
	if (bError)
	{	
		::PostMessage(g_hDlg, WM_SHOWERROR, (WPARAM)GetCurrentThreadId() , (LPARAM)sString);		
	}
	else
	{
		::PostMessage(g_hDlg, WM_SHOWRESULTS, (WPARAM)GetCurrentThreadId() , (LPARAM)sString);
	}
	
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function:	CreateRowsThread
  Summary:	Populates the database with rows
  Args:		LPVOID v		Number of rows to create
			BOOL bError		Is this an error?	
  Returns:	DWORD
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
DWORD WINAPI CreateRowsThread( LPVOID v)
{

	CreateRows((long)v, NULL);
	return S_OK;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function:	MoveMoneyThread
  Summary:	Transfers money from one account to another
  Args:		LPVOID v		Thread data
  Returns:	DWORD
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
DWORD WINAPI MoveMoneyThread( LPVOID v)
{

	THREADDATA * pTd = (THREADDATA *)v;	
	HRESULT hr;
	BOOL bLocalStop = FALSE;
	BSTR s;	
	EnumCoInit eCoInit = pTd -> eCoInit;
	if (eCoInit == CoInitRandom)
	{
		eCoInit = (EnumCoInit)RandInt(2);

	}
	switch (eCoInit)	
	{
	case CoInitMTA:
		s = SysAllocString(L"Initializing COM (MTA)");
		ShowResults(s, FALSE);
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		break;
	case CoInitSTA:	
		s = SysAllocString(L"Initializing COM (STA)");
		ShowResults(s, FALSE);
		hr = CoInitialize(NULL);
		break;
	default:
		_ASSERTE(0);

	}
	WCHAR sz[MSG_BUF_SIZE];

	if (hr)
	{
		wsprintf(sz, L"CoInitialize or CoInitializeEx failed.  hr = %Hx", hr);		
		ShowResults(SysAllocString(sz), TRUE);
		CoUninitialize();
		return hr;
	}

	CLSID clsid = CLSID_CMoveMoney;
	IID   iid = IID_IMoveMoney;
	switch (pTd -> eLang)
	{
	case VB:	
		hr = CLSIDFromProgID(L"Bank.IMoveMoney", &clsid);
		if (FAILED(hr))
		{
			//ShowResults(SysAllocString(L"VB Account Not registered.  Using VC Account."), TRUE);
			clsid = CLSID_CMoveMoney;
		}
		break;
	case VC:
		break;
	case Java:
		ShowResults(SysAllocString(L"Java not supported (yet).  Using VC Account."), TRUE);
		break;
    // (04.26.00 mdl) Included support for Delphi.
	case Delphi:
        hr = CLSIDFromProgID(L"DelphiBank.MoveMoney", &clsid);
		IIDFromString(L"{A8C18C7A-4D78-475B-A5E7-96F73DB2CE8D}", &iid);
		if (FAILED(hr))
		{
			ShowResults(SysAllocString(L"Delphi MoveMoney Not registered.  Using VC Account."), TRUE);
			clsid = CLSID_CMoveMoney;
			iid = IID_IMoveMoney;
		} 
        break;
	default:
		_ASSERTE(0);	
	}

	int nCount = 0;

	BSTR sResult = 0;
	
	int nFrom = pTd -> nFrom;
	int nTo = pTd -> nTo;
	
	DWORD liStartTime = GetTickCount();	
	

	IErrorInfo * pInfo = NULL;
	nCount = 0;			
	IMoveMoney * pMove = NULL;
	DWORD dwTime;
	LARGE_INTEGER stop;	
	LARGE_INTEGER start;		
	while (g_bStop == FALSE && (nCount < pTd -> nIters)  && bLocalStop == FALSE )
	{
			
		if (pMove == NULL)
		{
			if (pTd -> bChatty)
			{				
				ShowResults(SysAllocString(L"Creating MoveMoney"), FALSE);
			}

				
			// (04.26.00 mdl) Modified to use variable vs. fixed iid.
			//hr = CreateObject(clsid, CLSCTX_ALL, IID_IMoveMoney, (void **)&pMove, &dwTime);
			hr = CreateObject(clsid, CLSCTX_ALL, iid, (void **)&pMove, &dwTime);			
			if (pTd -> bChatty)
			{
				wsprintf(sz, L"CoCreateInstance took %d ms", dwTime);
				ShowResults(SysAllocString(sz), FALSE);
			}			
			if (hr)
			{

				wsprintf(sz, L"Failed to create the move money component! HRESULT: %lX", hr);				
				ShowResults(SysAllocString(sz), TRUE);
				if (g_bAssertOnErrors)
					_ASSERTE(0);
				if (g_bRetry == FALSE) // don't exit for Wolfpack
					break; // exit thread if create fails
				else
				{
					ShowResults(SysAllocString(L"Waiting for 100 ms"), FALSE);
					Sleep(100);
				}
			}
		}

		if (pMove) // may be NULL w/ Wolfpack failover
		{
			IMoveMoneyOptions * pOptions = NULL;
			hr = pMove -> QueryInterface(IID_IMoveMoneyOptions, (void **)&pOptions);
			if (pOptions)
			{
				pOptions -> UseComPlus();
				pOptions -> SetAccountClsctx(CLSCTX_ALL);
				pOptions -> Release();
			}
			
			if (pTd -> bRandom)
			{
				nFrom = 0;
				nTo = 0;
				nFrom = RandInt(g_nRows);					 					
				nFrom++; // we want 1 --> nRows
				nTo = RandInt(g_nRows); 
				nTo++;
				if (nFrom > nTo) //always move from lowest to highest to stop deadlocks
				{
					int nTemp = nTo;
					nTo = nFrom;
					nFrom = nTemp;
				}
			}
			
			QueryPerformanceCounter( &start);				
			hr = pMove -> Perform(nFrom, nTo, pTd -> nAmount, pTd -> nTranType, &sResult);
			QueryPerformanceCounter( &stop);			
			if (pTd -> bChatty)
			{
				wsprintf(sz, L"MoveMoney Perform took %d ms",  1000*(stop.QuadPart-start.QuadPart)/g_PerfFreq.QuadPart);	
				ShowResults(SysAllocString(sz), FALSE);
			}		
			if (hr)
			{					
				GetErrorInfo(NULL, &pInfo);
				if( pInfo ) 
				{
					pInfo -> GetDescription(&sResult);
					pInfo -> Release();
				}
				if (g_bAssertOnErrors)
					_ASSERTE(0);
				if (hr == E_UNEXPECTED && g_bStopOnODBCErrors) // E_UNEXPECTED returned on ODBC errors
				{
					if (!g_bRetry)
						bLocalStop = TRUE;
					else // retry for wolfpack
					{
						if (pMove)
						{
							pMove -> Release();
							pMove = NULL;
						}
					}
				}
				else	// non-ODBC error, stop all threads
				{
					if (!g_bRetry)
						g_bStop = TRUE;
					else // retry for wolfpack
					{
						if (pMove)
						{
							pMove -> Release();
							pMove = NULL;
						}
					}
				}
				*sz = NULL;									
				if (!sResult)
				{
					if (hr == E_ACCESSDENIED)
						sResult = ::SysAllocString(L"Call failed due to security violation ");
					else
						sResult = ::SysAllocString(L"Call failed ");

				}
				wsprintf(sz, L"%s HRESULT: 0x%lx", sResult, hr);
				ShowResults(SysAllocString(sz), TRUE);
				SysFreeString(sResult); // not posting it
				sResult = NULL;
			}
			else 
			{
				if (pTd -> bChatty) 
					ShowResults(sResult, FALSE);
			}
			
			
			


			if (pTd -> bCreatePerIteration && pMove)
			{
				pMove -> Release();
				pMove = NULL;
			}
		}

		nCount++;				
	}
	
	if (pMove)
	{
		pMove -> Release();
		pMove = NULL;
	}


	float t = (GetTickCount() - (float)liStartTime)  / 1000;
	_snwprintf(sz, MSG_BUF_SIZE, L"Done.  Time: %2.4f seconds for %ld iterations", t, nCount);		
	ShowResults(SysAllocString(sz), FALSE);
	CoUninitialize();
	return 0;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function:	AccountThread
  Summary:	Changes the balance on an account
  Args:		LPVOID v		Thread data
  Returns:	DWORD
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
DWORD WINAPI AccountThread( LPVOID v)
{
	THREADDATA * pTd = (THREADDATA *)v;	
	HRESULT hr;
	BOOL bLocalStop = FALSE;
	BSTR s;	
	EnumCoInit eCoInit = pTd -> eCoInit;
	if (eCoInit == CoInitRandom)
	{
		eCoInit = (EnumCoInit)RandInt(2);

	}
	switch (eCoInit)	
	{
	case CoInitMTA:
		s = SysAllocString(L"Initializing COM (MTA)");
		ShowResults(s, FALSE);
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		break;
	case CoInitSTA:	
		s = SysAllocString(L"Initializing COM (STA)");
		ShowResults(s, FALSE);
		hr = CoInitialize(NULL);
		break;
	default:
		_ASSERTE(0);

	}

	WCHAR sz[MSG_BUF_SIZE];
	if (hr)
	{
		wsprintf(sz, L"CoInitialize or CoInitializeEx failed.  hr = %Hx", hr);		
		ShowResults(SysAllocString(sz), TRUE);
		CoUninitialize();
		return hr;
	}

	CLSID clsid = CLSID_CAccount;
	IID iid = IID_IAccount;
	switch (pTd -> eLang)
	{
	case VB:	
		hr = CLSIDFromProgID(L"Bank.IAccount", &clsid);
		if (FAILED(hr))
		{
			//ShowResults(SysAllocString(L"VB Account Not registered.  Using VC Account."), TRUE);
			clsid = CLSID_CAccount;
		}
		break;
	case VC:
		break;
	case Java:
		ShowResults(SysAllocString(L"Java not supported (yet).  Using VC Account."), TRUE);
		break;
	// (04.26.00 mdl) Included support for Delphi.
	case Delphi:
        hr  = CLSIDFromProgID(L"DelphiBank.Account", &clsid);
		IIDFromString(L"{4D237DC1-041A-11D4-81A3-005004D0FBC3}", &iid);
		if (FAILED(hr))
		{
			ShowResults(SysAllocString(L"Delphi Account Not registered.  Using VC Account."), TRUE);
			clsid = CLSID_CAccount;
			iid = IID_IAccount;
		}
        break;
	default:
		_ASSERTE(0);	
	}

	int nCount = 0;

	
	BSTR sResult = 0;

	int nFrom = pTd -> nFrom;
	int nTo = pTd -> nTo;
	
	
	DWORD liStartTime = GetTickCount();
	IAccount * pAccount = NULL;		
	IErrorInfo * pInfo = NULL;
	nCount = 0;
	DWORD dwTime;
	LARGE_INTEGER stop;	
	LARGE_INTEGER start;		
	while (g_bStop == FALSE && (nCount < pTd -> nIters) && bLocalStop == FALSE)
	{
		
		if (!pAccount)
		{
			if (pTd -> bChatty)
			{
				s = SysAllocString(L"Creating Account");
				ShowResults(s, FALSE);
			}
			// (04.26.00 mdl) Modified to use variable vs. fixed iid.
			//hr = CreateObject(clsid, CLSCTX_ALL, IID_IAccount, (void **)&pAccount, &dwTime);						
			hr = CreateObject(clsid, CLSCTX_ALL, iid, (void **)&pAccount, &dwTime);						
			if (pTd -> bChatty)
			{
				wsprintf(sz, L"CoCreateInstance took %d ms", dwTime);
				ShowResults(SysAllocString(sz), FALSE);
			}
			
			if (hr)
			{

				wsprintf(sz, L"Failed to create the account component! HRESULT: %lX", hr);
				ShowResults(SysAllocString(sz), TRUE);				
				if (g_bAssertOnErrors)
					_ASSERTE(0);
				if (g_bRetry == FALSE) // don't exit for Wolfpack
					break; // exit thread if create fails
				else
				{
					ShowResults(SysAllocString(L"Waiting for 100 ms"), FALSE);
					Sleep(100);
				}


			}
			
		}
		if (pAccount)
		{
		
			int nAmount = pTd -> nAmount;
			if (pTd -> nTranType == DEBIT)
				nAmount = -1  * nAmount;

			if (pTd -> bRandom)
			{
				if (!g_nRows)
				{
					ShowResults(SysAllocString(L"Put in a valid number of rows you dweeb!"), TRUE);
					g_bStop = TRUE;						
				}
				else
				{
					nTo = RandInt(g_nRows); // nTo==nFrom legal?					
					nTo++;
				}
			}
			QueryPerformanceCounter( &start);				
			hr = pAccount -> Post(nTo, nAmount, &sResult);
			QueryPerformanceCounter( &stop);	
			if (pTd -> bChatty)
			{
				wsprintf(sz, L"Account Post took %d ms", 1000*(stop.QuadPart-start.QuadPart)/g_PerfFreq.QuadPart);
				ShowResults(SysAllocString(sz), FALSE);
			}
			if (hr)
			{					
				GetErrorInfo(NULL, &pInfo);
				if( pInfo ) 
				{
					pInfo -> GetDescription(&sResult);
					pInfo -> Release();
				}
				if (g_bAssertOnErrors)
					_ASSERTE(0);
				if (hr == E_UNEXPECTED && g_bStopOnODBCErrors) // E_UNEXPECTED returned on ODBC errors
				{
					if (!g_bRetry)
							bLocalStop = TRUE;
					else // retry for wolfpack
					{
						if (pAccount)
						{
							pAccount -> Release();
							pAccount = NULL;
						}
					}
					
				}
				else	// non-ODBC error
				{
					if (!g_bRetry)
						g_bStop = TRUE;
					else // retry for wolfpack
					{
						if (pAccount)
						{
							pAccount -> Release();
							pAccount = NULL;
						}
					}

				}
				if (!sResult || SysStringLen(sResult) == 0)
				{
					SysFreeString(sResult);
					if (hr == E_ACCESSDENIED)
						sResult = ::SysAllocString(L"Call failed due to security violation ");
					else
						sResult = ::SysAllocString(L"Call failed ");
				}
				wsprintf(sz, L"%s HRESULT: 0x%lx", sResult, hr);
				ShowResults(SysAllocString(sz), TRUE);
				SysFreeString(sResult); // not posting it				
				
			}
			else
			{
			
				if (pTd -> bChatty)
				{
					ShowResults(sResult, FALSE);
				}
			}
	
			if (pTd -> bCreatePerIteration && pAccount)
			{
				pAccount -> Release();
				pAccount = NULL;
			}
		}

		nCount++;				
	}

	if (pAccount)
	{
		pAccount -> Release();
		pAccount = NULL;
	}
	
	float t = (GetTickCount() - (float)liStartTime)  / 1000;
	_snwprintf(sz,MSG_BUF_SIZE, L"Done.  Time: %2.4f seconds for %ld iterations", t, nCount);		
	ShowResults(SysAllocString(sz), FALSE);
	CoUninitialize();
	return 0;

			
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function:	CreateSchemaThread
  Summary:	Creates the database in SQL Server
  Args:		LPVOID v		Reserved
  Returns:	DWORD
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
DWORD WINAPI CreateSchemaThread( LPVOID v)
{
	HENV henv = 0;
	HDBC hdbc = 0;
	HSTMT hstmt = 0;	
	HRESULT hr= S_OK;
	BSTR sErr = NULL;
	WORD nSize = 255;
	hr = GetConnection(&henv, &hdbc, &hstmt);
	if (FAILED(hr))
	{		
		ShowResults(SysAllocString(L"Done -- failed to get connection"), FALSE);
		return -1;
	}
		
	CreateSchema(hstmt);


	if (hr != S_OK)
	{
		GetOdbcError(henv, hdbc, hstmt, &sErr);
		ShowResults(sErr, TRUE);
	}
	else
	{ 		
		ShowResults(SysAllocString(L"Done creating schema"), FALSE);
	}


	if (hstmt)
	{
		SQLFreeStmt(hstmt, SQL_DROP);
	}
	if (hdbc)
	{
		SQLDisconnect(hdbc);	
		SQLFreeConnect(hdbc);
	}
	if (henv)
		SQLFreeEnv(henv);

	return 0;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetConnection
  Summary:  Get the ODBC connection to SQL Server
  Args:     WCHAR* sDsn			ODBC DSN to connect to
			HENV* phEnv			An ODBC environment handle
			HDBC* phdbc			An ODBC database connection handle
			HSTMT* phstmt		An ODBC statement handle
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT GetConnection(HENV  * phEnv, HDBC * phdbc, HSTMT * phstmt)
{
	WCHAR * sDsn = L"FILEDSN=OPBankSamples;DATABASE=pubs;UID=sa;PWD=;APP=VC Bank";
	RETCODE rc;
	HRESULT hr= S_OK;
	BSTR sErr = NULL;
	rc = SQLAllocEnv(&*phEnv);
	ASSERT_SQL_SUCCESS(rc);	
	BSTR s;
	s = SysAllocString(L"Getting Connection");
	ShowResults(s, FALSE);
	rc = SQLAllocConnect(*phEnv, phdbc);	
	if (SQL_FAILED(rc))
	{
		GetOdbcError(*phEnv, *phdbc, *phstmt, &sErr);
		ShowResults(sErr, TRUE);		
		return (DWORD)E_FAIL;
	}
	WCHAR szConn[255];
	WORD nSize = 255;	
	rc = SQLDriverConnect(*phdbc, NULL, (SQLWCHAR *)sDsn, SQL_NTS, (SQLWCHAR *)szConn, 255, (short *)&nSize, (UWORD)SQL_DRIVER_NOPROMPT);
	if (SQL_FAILED(rc))
	{
		GetOdbcError(*phEnv, *phdbc, *phstmt, &sErr);
		ShowResults(sErr, TRUE);		
		SQLFreeEnv(*phEnv);
		return (DWORD)E_FAIL;
	}
	rc = SQLAllocStmt(*phdbc, phstmt); // generic stmt
	if (SQL_FAILED(rc))
	{
		GetOdbcError(*phEnv, *phdbc, *phstmt, &sErr);
		ShowResults(sErr, TRUE);		
		SQLFreeConnect(*phdbc);
		SQLFreeEnv(*phEnv);
		return (DWORD)E_FAIL;
	}

	return S_OK;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetRowCount
  Summary:  Get the number of existing account rows in the database
  Args:     HSTMT hstmt			An ODBC statement handle
			long *pRowCount		Number of rows in database
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT GetRowCount(HSTMT hstmt, long * pRowCount)
{
	
	HRESULT hr;
	HENV henv = 0;
	HDBC hdbc = 0;
	
	BOOL bGotConnection = FALSE;
	if (!hstmt)
	{
		hr = GetConnection(&henv, &hdbc, &hstmt);
		bGotConnection = TRUE;
		if (hr)
			return hr;
	}

	//
	//	get the current number of rows
	//
	
	int nRows = 0;
	long len = 0;
	RETCODE rc;	
	ShowResults(SysAllocString(L"Getting Current Row Count"), FALSE);
	rc = SQLExecDirect(hstmt, L"select max(AccountNo) from VcAccount", SQL_NTS);
	while (SQLFetch(hstmt) == SQL_SUCCESS) // only get the first one for now
	{

		rc = SQLGetData(hstmt, 1, SQL_C_LONG, &nRows, 0, &len); 		
		if (SQL_FAILED(rc))
		{
			BSTR sErr;
			GetOdbcError(henv, hdbc, hstmt, &sErr);			
			ShowResults(sErr, TRUE);
		}
	}	

	*pRowCount = nRows;
	if (bGotConnection)
	{
		FreeConnection(henv, hdbc, hstmt);
	}
	else
	{
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}

	return S_OK;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: FreeConnection
  Summary:  Free the ODBC connection to SQL Server
  Args:     HENV henv			An ODBC environment handle
			HDBC hdbc			An ODBC database connection handle
			HSTMT hstmt			An ODBC statement handle
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT FreeConnection(HENV henv, HDBC hdbc, HSTMT hstmt)
{
	ShowResults(SysAllocString(L"Freeing Connection"), FALSE);

	if (hstmt)
		SQLFreeStmt(hstmt, SQL_DROP);
	if (hdbc)
	{
		SQLDisconnect(hdbc);	
		SQLFreeConnect(hdbc);
	}
	if (henv)
		SQLFreeEnv(henv);
	return S_OK;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: VerifySchema
  Summary:  Verify that the database tables exist
  Args:     HENV henv			An ODBC environment handle
			HDBC hdbc			An ODBC database connection handle
			HSTMT hstmt			An ODBC statement handle
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT VerifySchema(HSTMT hstmt)
{
	HRESULT hr = S_OK;
	BOOL bGotConnection = FALSE;
	HENV henv = 0;
	HDBC hdbc = 0;
	if (!hstmt)
	{
		hr = GetConnection(&henv, &hdbc, &hstmt);
		bGotConnection = TRUE;
		if (hr)
			return hr;
	}

	ShowResults(SysAllocString(L"Verifying schema"), FALSE);
	int i;
	RETCODE rc;
	long nRowCount = 0;
	for (i=0;i< sizeof(sCheckSchema) / sizeof(sCheckSchema[0]); i++)
	{
		rc = SQLExecDirect(hstmt, sCheckSchema[i], SQL_NTS);
		if (SQL_FAILED(rc))
		{
			hr = E_FAIL;
			break;			
		}

		rc = SQLRowCount(hstmt, &nRowCount);
		if (nRowCount != 1)
		{
			hr = E_FAIL;
			break;
		}
	}


	if (bGotConnection)
	{
		FreeConnection(henv, hdbc, hstmt);
	}
	else
	{
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}

	return hr;

}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateRows
  Summary:  Inserts rows into the account table
  Args:     long nRows			Account number to populate up to
			HSTMT hstmt			An ODBC statement handle
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT CreateRows(long nRows, HSTMT hstmt)
{
	
	HENV henv = 0;
	HDBC hdbc = 0;
	HRESULT hr;
	BSTR sErr;
	BOOL bGotConnection = FALSE;
	RETCODE rc;

	if (!hstmt)
	{
		hr = GetConnection(&henv, &hdbc, &hstmt);
		bGotConnection = TRUE;
		if (hr)
			return hr;
	}

	//
	//	get the current rowcount
	//

	long nCurRows = 0;

	hr = GetRowCount(hstmt, &nCurRows);
	if (FAILED(hr))
		return hr;
	
	WCHAR szSQL[64];
	wsprintf(szSQL, L"Current Row count is %d", nCurRows+1);
	ShowResults(SysAllocString(szSQL), FALSE);
	wsprintf(szSQL, L"setting rowcount to be %d", nRows);
	ShowResults(SysAllocString(szSQL), FALSE);
	if (nCurRows <= nRows)
	{
		int i;		
		for (i=nCurRows+1; i<=nRows; i++)
		{
			wsprintf(szSQL, L"insert into VcAccount values (%i, '')", 100000);
			rc = SQLExecDirect(hstmt, szSQL, SQL_NTS);
			if (SQL_FAILED(rc))
			{
				GetOdbcError(0,0,hstmt,&sErr);
				ShowResults(sErr, TRUE);
				break;
			}
		}
	}
	else
	{
		ShowResults(SysAllocString(L"truncating rows"), FALSE);
		wsprintf(szSQL, L"delete from VcAccount where AccountNo > %d", nRows);
		rc = SQLExecDirect(hstmt, szSQL, SQL_NTS);
		if (SQL_FAILED(rc))
		{
			GetOdbcError(0,0,hstmt,&sErr);
			ShowResults(sErr, TRUE);
		}
	}


	ShowResults(SysAllocString(L"Done setting row count"), FALSE);	
	if (bGotConnection)
	{
		FreeConnection(henv, hdbc, hstmt);
	}
	else
	{
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}
	
	return S_OK;
	
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateSchema
  Summary:  Create the database tables
  Args:     HSTMT hstmt			An ODBC statement handle
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT CreateSchema(HSTMT hstmt)
{
	HENV henv = 0;
	HDBC hdbc = 0;
	HRESULT hr;
	int i;
	RETCODE rc;
	BOOL bGotConnection = FALSE;

	if (!hstmt)
	{
		hr = GetConnection(&henv, &hdbc, &hstmt);
		bGotConnection = TRUE;
		if (hr)
			return hr;
	}	
	ShowResults(SysAllocString(L"Creating schema"), FALSE);
	for (i=0; i< sizeof(sCreateSchema)/sizeof(sCreateSchema[0]); i++)
	{
		rc = SQLExecDirect(hstmt, sCreateSchema[i], SQL_NTS);
		if (SQL_FAILED(rc))
		{
			_ASSERTE(0);
			ShowResults(SysAllocString(L"Failed to create schema!"), TRUE);
			break;
		}
	}

	//
	//	we always need to add a row to the receipt table

	SQLExecDirect(hstmt, L"insert into receipt values(0)", SQL_NTS);
	
	if (bGotConnection)
	{
		FreeConnection(henv, hdbc, hstmt);
	}
	else
	{
		SQLFreeStmt(hstmt, SQL_CLOSE);
	}

	return S_OK;
}

