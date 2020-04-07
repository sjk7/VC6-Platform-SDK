/*+==========================================================================
  File:      Driver.cpp
  Summary:   Test client for Queued Components sample order entry application
  Classes:   None
  Functions: main
  Origin:    
----------------------------------------------------------------------------
  Copyright 1992 - 2000 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE
==========================================================================+*/ 

#include "stdafx.h"
#include "..\DataSourceNames.h"	// Data source names, userid, password
#include <iostream>
#include <initguid.h>
#include <adoid.h>				// ADO
#include <adoint.h>				// ADO
#include "..\QCOrder\processFlags.h"
#include "..\QCOrder\QCOrder.h"

// constants

const int nLineItemsPerOrder	= 5;
const int nOrdersPerDriver		= 100;
const int nSleepMilliseconds	= 250;		// database keys based on integral seconds

// Forward function declarations

HRESULT	CreateOrder(long lOrderId, long lFlags);

HRESULT CheckHR(HRESULT hr, LPCSTR pszVerb);

HRESULT ExecSQLStmt(LPCWSTR pszDSN, LPCWSTR pszSQLStmt);

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: main		main entry point
  Args:     none
  Returns:  int			HRESULT from any error or 0
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
 
int __cdecl main()
{
	long lFlags = 0;	// no database, vtable binding, not queued calls
//	lFlags |= processFlagLateBound;			// Invoke components via Automation (IDispatch)
//	lFlags |= processFlagWriteDB;			// Write to Order & Shipping tables
	lFlags |= processFlagQueuedComponents;	// Queued calls to Ship and Notify

	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED); // init COM library
	CheckHR(hr, "CoInitializeEx");

	if (SUCCEEDED(hr))
	{
		if (lFlags & processFlagWriteDB)
		{
			ExecSQLStmt(pszOrderDSN,		// Create Order table
						L"create table QCSampleOrder "
						L"  (order_id  int, "
						L"   cust_id   int, "
						L"   line_no   int, "
						L"   item_id   int, "
						L"   quantity  int, "
						L"   ship_status varchar(25) )" );
			// Accept error - table may already exist

			ExecSQLStmt(pszShipDSN,			// Create ship table
						L"create table QCSampleShip "
						L"  (order_id int, "
						L"   cust_id  int, "
						L"   line_no  int, "
						L"   item_id  int, "
						L"   quantity int, "
						L"   ship_status_enum int )" );
			// Accept error - table may already exist
		}

		for (int ix = 0; ix < nOrdersPerDriver && SUCCEEDED(hr); ix++)
		{
			long lOrderId = time(NULL);
			hr = CreateOrder(lOrderId, lFlags);	
			Sleep(nSleepMilliseconds);			// Wait between orders
		}

		CoUninitialize();
	}
	return hr;
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CreateOrder	Create a single order
  Args:     long		lOrderId - a unique order identifier
  Returns:  int			HRESULT from any error or S_OK
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/

HRESULT CreateOrder(long lOrderId, long lFlags)
{
	_COM_SMARTPTR_TYPEDEF(IOrder, _uuidof(IOrder));

	IOrderPtr pOrder;

	HRESULT hr = pOrder.CreateInstance(_uuidof(Order));
	CheckHR(hr, "CoCreateInstance CLSID_Order");

	if (SUCCEEDED(hr))
	{
		hr = pOrder->put_OrderId(lOrderId);
		CheckHR(hr, "put_OrderId");
	}

	if (SUCCEEDED(hr))
	{
		hr = pOrder->put_CustomerId( (lOrderId % 1000) * (rand() % 1000) );
		CheckHR(hr, "put_CustomerId");
	}
		
	for (int ix = 1; ix <= nLineItemsPerOrder && SUCCEEDED(hr); ix++)
	{
		// Derive ItemId and quantity from time of day
		hr = pOrder->LineItem(lOrderId % 100 + ix, lOrderId % 10 + 2 * ix);
		CheckHR(hr, "LineItem");
	}

	if (SUCCEEDED(hr))
	{
		_RPT1(_CRT_WARN, "QCSamp2 %d Driver\n", lOrderId); 
		hr = pOrder->Process(lFlags);	// process the complete order
		CheckHR(hr, "Process");
	}
	return hr;
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: CheckHR		Tests HRESULT for an exceptional condition
  Args:     HRESULT		hr - the HRESULT to test
			LPCSTR		pszVerb - string describing function that failed
  Returns:  HRESULT		returns value of input HRESULT
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/

HRESULT CheckHR(HRESULT hr, LPCSTR pszVerb)
{
	if (hr != S_OK)
	{
		std::cerr << pszVerb << " hr 0x" << std::hex << hr << '\n';
		_RPTF2(FAILED(hr) ? _CRT_ERROR : _CRT_WARN, "%s hr 0x%x\n", pszVerb, hr); 
	}
	return hr;
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: ExecSQLStmt Execute a single SQL statement using ADO
  Args:     LPCWSTR		pszDSN Data Source Name
			LPCWSTR		pszSQLStmt SQL statement to be executed
  Returns:  HRESULT		results from underlying functions
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/

HRESULT ExecSQLStmt(LPCWSTR pszDSN, LPCWSTR pszSQLStmt)
{
	CComPtr<ADOConnection> pADOConnection;

	HRESULT hr = CoCreateInstance(	CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER,
									IID_IADOConnection, (void **) &pADOConnection);
	CheckHR(hr, "CoCreateInstance CLSID_CADOConnection");

	if (SUCCEEDED(hr))
	{
		hr = pADOConnection->Open(	_bstr_t(pszDSN), _bstr_t(pszUserId),
									_bstr_t(pszPassword), adOpenUnspecified);
		CheckHR(hr, "pADOConnection->Open");
	}

	if (SUCCEEDED(hr))
		hr = pADOConnection->Execute(_bstr_t(pszSQLStmt), NULL, adCmdText, NULL);

	return hr;
}
