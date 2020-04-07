/*+==========================================================================
  File:      CAccount.cpp
  Summary:   Implementation of Object Pooled Account component
  Classes:   CAccount
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
#include "Account.h"
#include <comsvcs.h>
#include "CAccount.h"
#include <stdio.h>
#include <transact.h>

HRESULT CheckAmount (IObjectContext * pObjectContext, long lAmount, BSTR * s);

HRESULT GetConnection(WCHAR * sDSN, HENV  * phenv, HDBC * phdbc, HSTMT * phstmt, BOOL bUseObjectPool);

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetODBCError
  Summary:  Call SQLError to get the error from ODBC
  Args:     HENV henv		An ODBC environment handle
			HDBC hdbc		An ODBC database connection handle
			HSTMT hstmt		An ODBC statement handle
			BSTR* sErr		Output error string
  Returns:  void
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
void GetODBCError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR * sErr)
{
	WCHAR szSqlState[64];
	SDWORD NativeError;
	WCHAR szErr[512];
	SWORD cbErrorMsg;
	SQLError(henv, hdbc, hstmt, (SQLWCHAR *)szSqlState, &NativeError, (SQLWCHAR *)szErr, 511, &cbErrorMsg);
	*sErr = ::SysAllocString(szErr);
}



/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetConnection
  Summary:  Get the ODBC connection to SQL Server
  Args:     WCHAR* sDsn			ODBC DSN to connect to
			HENV* phEnv			An ODBC environment handle
			HDBC* phdbc			An ODBC database connection handle
			HSTMT* phstmt		An ODBC statement handle
			BOOL bUseObjectPool	flag whether we're using COM+ pooling or not
  Returns:  HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT GetConnection(WCHAR * sDsn, HENV  * phenv, HDBC * phdbc, HSTMT * phstmt, BOOL bUseObjectPool)
{


	RETCODE rc;
	HRESULT hr= S_OK;
	
	rc = SQLAllocEnv(phenv);
	ASSERT_SQL_SUCCESS(rc);
	if (bUseObjectPool)
	{
		rc = SQLSetEnvAttr(*phenv, SQL_ATTR_CONNECTION_POOLING, (void*)SQL_CP_OFF, 0);
		ASSERT_SQL_SUCCESS(rc);
	}
	rc = SQLAllocConnect(*phenv, phdbc);	
	if (SQL_FAILED(rc))
		return E_FAIL;
	WCHAR szConn[255];
	WORD nSize = 255;
	rc = SQLDriverConnect(*phdbc, NULL, (SQLWCHAR *)sDsn, SQL_NTS, (SQLWCHAR *)szConn, 255, (short *)&nSize, (UWORD)SQL_DRIVER_NOPROMPT);
	if (SQL_FAILED(rc))
	{
		SQLFreeEnv(*phenv);
		return E_FAIL;
	}
	rc = SQLAllocStmt(*phdbc, phstmt); // generic stmt
	if (SQL_FAILED(rc))
	{
		SQLFreeConnect(*phdbc);
		SQLFreeEnv(*phenv);

		return E_FAIL;
	}

	return S_OK;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::InterfaceSupportsErrorInfo
  Summary:  Confirms or denies that an error came from IAccount interface
  Args:     REFIID riid			Interface ID returned in error
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CAccount::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IAccount,
	};
	
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		// refer to guiddef.h
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::Construct
  Summary:  Called by the constructor activator
  Args:     IDispatch *pUnk		Used to obtain construction string
  Returns:  HRESULT
  Comments:	The construct string should look like
			"FILEDSN=OPBankSamples;DATABASE=pubs;UID=sa;PWD=;APP=OPBank"
			If '/NP' is in the string, COM+ pooling will not be active
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CAccount::Construct(IDispatch * pUnk)
{

	if (!pUnk)
		return E_UNEXPECTED;
	HRESULT hr;
	IObjectConstructString * pString = NULL;
	hr = pUnk -> QueryInterface(IID_IObjectConstructString, (void **)&pString);
	if (pString)
	{
		CComBSTR s;
		pString -> get_ConstructString(&s);		
		WCHAR * p = wcsstr(s.m_str, L"/NP");
		if (p)
		{
			m_bObjectPooled = FALSE;
			*p = NULL;
		}
		else
			m_bObjectPooled = TRUE;

		m_sDSN = s;
		pString -> Release();
		hr = GetConnection(m_sDSN.m_str, &m_henv, &m_hdbc, &m_hstmt, m_bObjectPooled);
		if (FAILED(hr))
		{
			BSTR sResult;
			GetODBCError(m_henv, m_hdbc, NULL, &sResult);			
			AtlReportError( CLSID_CUpdateReceipt, sResult, IID_IAccount, hr);
			SysFreeString(sResult);
			return hr;
		}
	}

	m_bConstructed = TRUE;
	
	return hr;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::Post
  Summary:  Modifies an account by a certain amount
  Args:     long lAccount		The account to modify
			long lAmount		Amount to modify the account by
			BSTR* pbstrResult	Informational string (NULL if error)
  Returns:  HRESULT				S_OK or E_FAIL
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CAccount::Post (IN long lAccount, IN long lAmount, OUT BSTR* pbstrResult) {

	HRESULT hr = S_OK;
	*pbstrResult = NULL;
	IObjectContext* pObjectContext = NULL;	

	if (!m_bConstructed)
	{
		m_sDSN = L"FILEDSN=OPBankSamples;DATABASE=pubs;UID=sa;PWD=;APP=OPBank";
		hr = GetConnection(m_sDSN.m_str, &m_henv, &m_hdbc, &m_hstmt, FALSE);
		if (FAILED(hr))
		{
			BSTR sResult;
			GetODBCError(m_henv, m_hdbc, NULL, &sResult);			
			AtlReportError( CLSID_CAccount, sResult, IID_IAccount, hr);
			SysFreeString(sResult);
			return hr;
		}
	}

	long lErrFlag = 0;
	hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext);
	if (!pObjectContext)
	{
		AtlReportError( CLSID_CAccount, "No Object Context", IID_IAccount, hr);
		return hr;
	}
		
	hr = CheckAmount(pObjectContext, lAmount, pbstrResult);
	if (FAILED(hr))
	{
		pObjectContext -> SetAbort();
		SafeRelease(pObjectContext);
		AtlReportError( CLSID_CAccount, *pbstrResult, IID_IAccount, hr);
		SysFreeString(*pbstrResult);
		return hr;
	}

	_ASSERTE(m_henv);
	hr = DoWork(lAccount, lAmount, pbstrResult);
	if (SUCCEEDED(hr))
	{
		pObjectContext -> SetComplete();
	}
	else
	{
		pObjectContext -> SetAbort();
		AtlReportError( CLSID_CAccount, *pbstrResult, IID_IAccount, hr);
		SysFreeString(*pbstrResult);
	}


	// (03.22.00 mdl) Release connection if object is not pooled.
	if (!m_bObjectPooled)
	{
		FinalRelease();
	}

	SafeRelease(pObjectContext);	
	return hr;
}



/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CheckAmount
  Summary:  
  Args:     IObjectContext* pObjectContext	Pointer to ObjectContext
			long lAmount					Amount to modify the account by
			BSTR* s							Informational string (NULL if error)
  Returns:  HRESULT							S_OK or E_FAIL
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
HRESULT CheckAmount(IObjectContext * pObjectContext, long lAmount, BSTR * s)
{
	
	if (!pObjectContext)
	{
		*s = ::SysAllocString(L"No Context");
		return E_FAIL;
	}
	// Check security for large transfers
	if (lAmount > 500 || lAmount < -500) 
	{
		BOOL bInRole;
		BSTR bstrRole;
	
		bstrRole = ::SysAllocString(L"Managers");
		HRESULT hr;
		hr = pObjectContext->IsCallerInRole (bstrRole, &bInRole);
		::SysFreeString(bstrRole);
		
		if (FAILED( hr )) 
		{
			*s = ::SysAllocString(L"IsCallerInRole() call failed!  Please add the 'Managers' Roll to the package.");
			return hr;
		}
		
		if (!bInRole) 
		{
			*s = ::SysAllocString(L"Need 'Managers' role for amounts over $500");
			return  E_FAIL;
		}
	}
	return S_OK;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::DoWork
  Summary:  Get current balance, check for overdraft, and update new balance
  Args:     long lAccount		The account to modify
			long lAmount		Amount to modify the account by
			BSTR* pbstrResult	Informational string
  Returns:  HRESULT				S_OK
								E_UNEXPECTED (ODBC Error)
								E_FAIL (other error, ie overdrawn)
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CAccount::DoWork(long lAccount, long lAmount, BSTR *pbstrResult)
{
		
	WCHAR szBuffer[512];
	RETCODE rc;
	long lBal = 0;
	long len = 0;
	HRESULT hr = S_OK;

	if (m_bShouldEnlist)
	{
		//
		// NOTE: I know I call SetComplete, so I don't have to set
		//	     the m_bShouldEnlist flag to FALSE after I enlist
		//
		hr = Enlist();
		if (FAILED(hr))
			return hr;
	}

	ZeroMemory(szBuffer, 512 * sizeof (WCHAR));
	wsprintf(szBuffer, L"update VcAccount set balance = balance + %ld where AccountNo = %ld", lAmount, lAccount);
	rc = SQLExecDirect(m_hstmt, szBuffer, SQL_NTS);
	if (SQL_FAILED(rc))
	{
		GetODBCError(m_henv, m_hdbc, m_hstmt, pbstrResult);
		return E_UNEXPECTED;

	}

	long nRowsAffected;
	rc = SQLRowCount( m_hstmt, &nRowsAffected);
	if (nRowsAffected == 0)
	{
		wsprintf (szBuffer, L"account %ld not on file. (VC++ ODBC)", lAccount);			
		*pbstrResult = SysAllocString(szBuffer);
		return E_FAIL;
	}

	wsprintf (szBuffer, L"SELECT Balance FROM VcAccount WHERE AccountNo = %ld", lAccount);
		

	rc = SQLExecDirect(m_hstmt, szBuffer, SQL_NTS);
	if (SQL_FAILED(rc))
	{
		GetODBCError(m_henv, m_hdbc, m_hstmt, pbstrResult);
		return E_UNEXPECTED;

	}
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) // only get the first one for now
	{

		rc = SQLGetData(m_hstmt, 1, SQL_C_LONG, &lBal, 0, &len); 		
	}						
		
	// Check for overdraw, then prepare return string
	if (lBal < 0) 
	{
	
		wsprintf (szBuffer, L"Error. Account %ld would be overdrawn by %ld.  Balance is still %ld",
				lAccount, -lBal, lBal - lAmount);		

		*pbstrResult = ::SysAllocString(szBuffer);
		return E_FAIL;
	}
		
	SQLFreeStmt(m_hstmt, SQL_CLOSE);	


	wsprintf (szBuffer, L"%s account %ld, balance is $%ld. (VC++ ODBC)",
			lAmount >= 0 ? L"Credit to" : L"Debit from", lAccount, lBal);

	*pbstrResult = SysAllocString(szBuffer);

	return S_OK;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::FinalRelease
  Summary:  Free up ODBC connection
  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CAccount::FinalRelease()
{
	if (m_hstmt)
		SQLFreeStmt(m_hstmt, SQL_DROP);
	if (m_hdbc)
	{
		SQLDisconnect(m_hdbc);	
		SQLFreeConnect(m_hdbc);
	}
	if (m_henv)
		SQLFreeEnv(m_henv);

	m_hstmt = 0;
	m_henv = 0;
	m_hdbc = 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::Activate
  Summary:  On activation, get the transaction (unit of work).  If the same
			transaction as before, no need to enlist.  Otherwise, set a flag
			to re-enlist in the transaction.  If configured not to use COM+
			pooling, immediately return.
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CAccount::Activate()
{

	//	should only do this when we are being activated in different 
	//	tx units of work
	m_bShouldEnlist = FALSE;

	if (!m_bObjectPooled)
		return S_OK;

	HRESULT hr;
	IObjectContext * pObjectContext = NULL;
	hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext);
	_ASSERTE(pObjectContext);
	GUID txUOW = GUID_NULL;
	IObjectContextInfo	* pObjTx = NULL;
	pObjectContext -> QueryInterface(IID_IObjectContextInfo, (void **)&pObjTx);
	if (pObjTx)
	{		
		pObjTx -> GetTransactionId (&txUOW);
		pObjTx -> Release();
	}
	pObjectContext -> Release();

	if (txUOW != m_txuow)
	{
		m_bShouldEnlist = TRUE;	
		m_txuow = txUOW;

	}

	return S_OK;

}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CAccount::Enlist
  Summary:  Enlists ODBC in the current transaction
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CAccount::Enlist()
{
	HRESULT hr;
	IObjectContext * pObjectContext = NULL;
	hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext);
	_ASSERTE(pObjectContext);
	
	IObjectContextInfo	* pObjTx = NULL;
	pObjectContext -> QueryInterface(IID_IObjectContextInfo, (void **)&pObjTx);
	pObjectContext -> Release();
	if (pObjTx)
	{
		ITransaction * pTx = NULL;
		pObjTx -> GetTransaction ((IUnknown **)&pTx);
		RETCODE rc ;
		if (pTx)
		{
			rc = SQLSetConnectOption(m_hdbc, SQL_ATTR_ENLIST_IN_DTC, (UDWORD)pTx);		
			if (SQL_FAILED(rc))
			{
#ifdef _DEBUG
				BSTR sErr;
				GetODBCError(m_henv, m_hdbc, m_hstmt, &sErr);								
				AtlTrace(L"Warning! Failed to enlist on caller tx in VCAccount!\n");
				AtlTrace(L"ODBC Error: ");
				AtlTrace(sErr);
				AtlTrace(L"\n");
				SysFreeString(sErr);
#endif
				hr = E_FAIL;
			}

			pTx -> Release();
		}

		pObjTx -> Release();
	}
	
	return hr;
}


