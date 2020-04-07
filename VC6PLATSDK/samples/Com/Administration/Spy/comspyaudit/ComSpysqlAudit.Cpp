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
#include "stdafx.h"
#include "ComSpyAudit.h"
#ifndef DBNTWIN32
#define DBNTWIN32
#include <SQL.h>
#include <SQLEXT.h>
#include <ODBCINST.h>
#endif // DBNTWIN32 
#include <ODBCINST.h>
#include "ComSpySqlAudit.h"

LPTSTR sTables[] = {
_T("SecurityEvents"),		//IComSecurityEvents,IComIdentityEvents
_T("MethodEvents"),			//IComMethodEvents
_T("ObjectEvents"),			//IComObjectEvents, IComInstanceEvents,IComObjectConstructionEvents
_T("AppEvents"),			//IComAppEvents
_T("ResourceEvents"),		//IComResourceEvents
_T("ThreadEvents"),			//IComThreadEvents
_T("TransactionEvents"),	//IComTransactionEvents
_T("ObjectPoolEvents"),		//IComObjectPoolEvents,IComObjectPoolEvents2
_T("ActivityEvents"),		//IComActivityEvents
_T("QCEvents"),				//IComQCEvents
_T("ExceptionEvents"),		//IComExceptionEvents
_T("CRMEvents"),			//IComCRMEvents
_T("LBEvents")				//ILBEvents
};

//for testing table existance
LPTSTR sCreateTable = 
_T("CREATE TABLE dbo.%s (Ct int NOT NULL )");

////
STDMETHODIMP CComSpySqlAudit::Init(LPCOLESTR sDSN, LPCOLESTR sUser, LPCOLESTR sPw)
{
	CComBSTR msg;
	RETCODE rc;

	if (m_henv || m_hstmt || m_hdbc)
		return E_UNEXPECTED; //did you call Init() twice?
	
	rc = SQLAllocEnv( &m_henv );
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO)
    {
        msg = L"CComSpySqlAudit::Init() - SQLAllocEnv failed!\n";
		goto Exit;
    }
    

    //Allocate the Connection handle 
    rc = SQLAllocConnect( m_henv, &m_hdbc );
   
    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
        msg = L"CComSpySqlAudit::Init() - SQLAllocConnect failed!\n";
		goto Exit;		
    }
    

	SQLSetConnectOption(m_hdbc, SQL_LOGIN_TIMEOUT, 5);
    
    rc = SQLConnect( m_hdbc, (SQLWCHAR *)sDSN,  SQL_NTS, 
							 (SQLWCHAR *)sUser, SQL_NTS,
							 (SQLWCHAR *)sPw,   SQL_NTS );

    if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
        msg = L"CComSpySqlAudit::Init() - SQLConnect failed!\n";
		goto Exit;
    }

	
    //Allocate the statement handle 
    rc = SQLAllocStmt( m_hdbc, &m_hstmt);
	if( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {     	
        msg = L"CComSpySqlAudit::Init() - SQLConnect failed!\n";
		goto Exit;
    }
	//
	//	verify the table existence
	//
	{	
		TCHAR sSQL[1024];
		for (int i=0; i<sizeof(sTables)/sizeof(sTables[0]); i++)
		{
			ZeroMemory(sSQL, 1024 * sizeof(TCHAR));
			wsprintf(sSQL, sCreateTable, sTables[i]);
			rc = SQLExecDirect(m_hstmt, sSQL, lstrlen(sSQL));
			if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
			{
				// this means the table is not in the db
				
				//Clean up the table just created and exit 
				ZeroMemory(sSQL, 1024 * sizeof(TCHAR));
				wsprintf(sSQL, _T("drop table %s"), sTables[i]);
				rc = SQLExecDirect(m_hstmt, sSQL, lstrlen(sSQL));
				msg = L"Table ";										
				msg.Append(sTables[i]);
				msg.Append(L" is not in the Database.");  
				
				goto Exit;
			}
		}	
	}
		
	return S_OK;

Exit:	   	
		
	ATLTRACE(msg);
	ATLTRACE(_T("\n"));
	
	if (m_hstmt)
	{
		SQLFreeStmt( m_hstmt, SQL_DROP );    
	}

	if (m_hdbc)
	{
	   rc = SQLDisconnect( m_hdbc);
	   SQLFreeConnect( m_hdbc);
	   if (m_henv)
		 SQLFreeEnv( m_henv );
	}

	m_hdbc = m_hstmt  = m_henv = NULL;
	
	return E_FAIL;	
	
}


void CComSpySqlAudit::GetError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR *msg)
{
		WCHAR szSqlState[64];
		SDWORD NativeError;
		WCHAR szErr[512];
		SWORD cbErrorMsg;
		SQLError(henv, hdbc, hstmt, szSqlState, &NativeError, szErr, 511, &cbErrorMsg);
		*msg = SysAllocString(szErr);
}
