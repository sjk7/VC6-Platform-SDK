/*+==========================================================================
  File:      UpdRec.cpp
  Summary:   Implementation of Update Receipt component
  Classes:   CUpdateReceipt
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
#include "UpdRec.h"
#include <transact.h>

HRESULT GetConnection(WCHAR * sDSN, HENV  * phenv, HDBC * phdbc, HSTMT * phstmt, BOOL bUseObjectPool);
extern void GetODBCError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR * sErr);


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CUpdateReceipt::Construct
  Summary:  Called by the constructor activator
  Args:     IDispatch *pUnk		Used to obtain construction string
  Returns:  HRESULT
  Comments:	The construct string should look like
			"FILEDSN=OPBankSamples;DATABASE=pubs;UID=sa;PWD=;APP=OPBank"
			If '/NP' is in the string, COM+ pooling will not be active
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CUpdateReceipt::Construct(IDispatch * pUnk)
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
  Function: CUpdateReceipt::InterfaceSupportsErrorInfo
  Summary:  Confirms or denies that an error came from IAccount interface
  Args:     REFIID riid			Interface ID returned in error
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CUpdateReceipt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IUpdateReceipt,
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
  Function: CUpdateReceipt::Update
  Summary:  Once GetReceipt has issued 100 receipts, update the database to
			preallocate another 100 receipts for use by GetReceipt
  Args:     long *plReceiptNo	First receipt number in new block
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CUpdateReceipt::Update (OUT long* plReceiptNo) 
{
	
	HRESULT hr = S_OK;
	IObjectContext* pObjectContext = NULL;
	
	RETCODE rc;
	BSTR sErr = 0;
	long len = 0;
	if (!m_bConstructed)
	{
		m_sDSN = L"FILEDSN=OPBankSamples;DATABASE=pubs;UID=sa;PWD=;APP=OPBank";
		hr = GetConnection(m_sDSN.m_str, &m_henv, &m_hdbc, &m_hstmt, m_bObjectPooled);
		if (FAILED(hr))
		{
			BSTR sResult;
			GetODBCError(m_henv, m_hdbc, NULL, &sResult);			
			AtlReportError( CLSID_CAccount, sResult, IID_IAccount, hr);
			SysFreeString(sResult);
			return hr;
		}
	}
	
	hr = CoGetObjectContext(IID_IObjectContext, (void**)&pObjectContext);
	if (!pObjectContext)
	{
		sErr = SysAllocString(L"No Object Context");
		goto end;
	}
	
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
	
	*plReceiptNo = 0;
	
	rc = SQLExecDirect(m_hstmt, L"Update Receipt set NextReceipt = NextReceipt + 100", SQL_NTS);
	if (SQL_FAILED(rc))
	{
		GetODBCError(m_henv, m_hdbc, m_hstmt, &sErr);
		hr = E_FAIL;
		goto end;

	}
	
	// Obtain the desired recordset with an SQL query
	rc = SQLExecDirect(m_hstmt, L"SELECT NextReceipt FROM Receipt", SQL_NTS);
	if (SQL_FAILED(rc))
	{
		GetODBCError(m_henv, m_hdbc, m_hstmt, &sErr);
		hr = E_FAIL;
		goto end;

	}
	while (SQLFetch(m_hstmt) == SQL_SUCCESS) // only get the first one for now
	{

		rc = SQLGetData(m_hstmt, 1, SQL_C_LONG, plReceiptNo, 0, &len); 		
	}				
	
	SQLFreeStmt(m_hstmt, SQL_CLOSE);	
	pObjectContext -> SetComplete();

end:

	if (sErr)
	{
		AtlReportError( CLSID_CUpdateReceipt, sErr, IID_IUpdateReceipt, hr);
		SysFreeString(sErr);
		pObjectContext -> SetAbort();
	}
	
	// (03.22.00 mdl) Release connection if object is not pooled.
	if (!m_bObjectPooled)
	{
		FinalRelease();
	}

	SafeRelease(pObjectContext);	
	return hr;

	
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CUpdateReceipt::FinalRelease
  Summary:  Free up ODBC connection
  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CUpdateReceipt::FinalRelease()
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
  Function: CUpdateReceipt::Activate
  Summary:  On activation, get the transaction (unit of work).  If the same
			transaction as before, no need to enlist.  Otherwise, set a flag
			to re-enlist in the transaction.  If configured not to use COM+
			pooling, immediately return.
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CUpdateReceipt::Activate()
{

	//
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
  Function: CUpdateReceipt::Enlist
  Summary:  Enlists ODBC in the current transaction
  Returns:  HRESULT
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CUpdateReceipt::Enlist()
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