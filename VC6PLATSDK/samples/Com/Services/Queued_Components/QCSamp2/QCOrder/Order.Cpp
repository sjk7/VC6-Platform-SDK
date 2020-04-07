/*+==========================================================================
  File:      Order.cpp
  Summary:   Implementation of COrder class
  Classes:   Implemented: COrder
			 Used: ADO  CLSID_ADOConnection
			 Used: COM+ ObjectContext
  Methods:   put_CustomerId
			 put_OrderId
			 LineItem
			 ProcessOrder
  Origin:    Implementation of case study in Queued Components specification
----------------------------------------------------------------------------
  Copyright 1992 - 2000 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE
==========================================================================+*/ 

#include "stdafx.h"
#include "..\DataSourceNames.h"	// ADO Data Source Names, userid, password
#include <adoid.h>		// ADO OLEDBSDK 
#include <adoint.h>		// ADO OLEDBSDK
#include "QCOrder.h"
#include "Order.h"
#include "..\QCOrder\processFlags.h"
#include "..\QCShip2\QCShip2.h"

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COrder::put_CustomerId
  Summary:  property put for CustomerId property
  Args:     long lCustomerId			A customer identifier
  Modifies: class member variable m_lCustomerId
  Returns:  HRESULT	- Always returns S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP COrder::put_CustomerId(long lCustomerId)
{
	m_lCustomerId = lCustomerId;
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COrder::put_OrderId
  Summary:  property put for OrderId property
  Args:     long lOrderId			An order identifier
  Modifies: class member variable m_lOrderId
  Returns:  HRESULT	- Always returns S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP COrder::put_OrderId(long lOrderId)
{
	m_lOrderId = lOrderId;
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COrder::LineItem
  Summary:  Adds a single item to an order
  Args:     long lItemId			An item identifier (e.g. stock number)
			long lQuantity			Quantity of the item ordered
  Modifies: class members m_veclItemId and m_veclQuantity 
  Returns:  HRESULT	- Always returns S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP COrder::LineItem(long lItemId, long lQuantity)
{
	m_veclItemId.push_back(lItemId);
	m_veclQuantity.push_back(lQuantity);
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   COrder::Process
  Summary:  Adds order to Order Entry table.
			Sends order to shipping department.
  Args:     long	lFlags - option flags - see constants in IDL file
  Modifies: Rows in order entry database (DSN = QCSampOrder)
			Issues COM+ SetComplete or SetAbort depending on request success
  Returns:  HRESULT	- returns failure from embedded function requests or S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP COrder::Process(long lFlags)
{
	HRESULT hr = S_OK;

	_RPT1(_CRT_WARN, "QCSamp2 %d Order\n", m_lOrderId);
		
	if (lFlags & processFlagWriteDB) hr = WriteOrderDB();

	if (SUCCEEDED(hr)) hr = InvokeShip(lFlags);
	
	// Invoke SetComplete or SetAbort depending on our success

	// We may be able to replace this with an "autodone" attribute

	CComPtr<IObjectContext> pIObjectContext;

	if (SUCCEEDED(CoGetObjectContext(IID_IObjectContext, (void**)&pIObjectContext)))
	{
		if (SUCCEEDED(hr))	pIObjectContext->SetComplete();
		else				pIObjectContext->SetAbort();
	}

	return hr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  THIS IS A PRIVATE MEMBER FUNCTION

  Method:   COrder::InvokeShip
  Summary:  Creates a Ship object to send to the shipping department
  Args:     long	lFlags - option flags
  Modifies: None
  Returns:  HRESULT from the underlying requests
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

HRESULT COrder::InvokeShip(long lFlags)
{
	LPWSTR pwszDisplayName;
	
	if (lFlags & processFlagQueuedComponents)
		pwszDisplayName = L"queue:/new:QCShip2.Ship2";
	else
		pwszDisplayName = L"new:QCShip2.Ship2";

	CComPtr<IUnknown> punkShip2;

	HRESULT hr = CoGetObject(pwszDisplayName, 0, IID_IUnknown, (void **) &punkShip2);
	if (SUCCEEDED(hr))
	{
		if (lFlags & processFlagLateBound)
			hr = InvokeShipIDispatch(punkShip2, lFlags);
		else
			hr = InvokeShipVtable(punkShip2, lFlags);	
	}
	return hr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  THIS IS A PRIVATE MEMBER FUNCTION

  Method:   COrder::InvokeShipIDispatch
  Summary:  Creates a Ship2 object to send to the shipping department
  Args:     IUnknown *	punkShip2 - IUnknown * to Shipping object
			long		lFlags	- flag longword with option bits   
  Modifies: None
  Returns:  HRESULT from the underlying requests
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

HRESULT COrder::InvokeShipIDispatch(IUnknown * punkShip2, long lFlags)
{
	HRESULT hr = S_OK;
	LPWSTR pwszDisplayName;
	CComQIPtr<IDispatch, &IID_IDispatch> pIDispatch(punkShip2);
	CComPtr<IUnknown> punkNotify;
	
	if (!pIDispatch) hr = E_NOINTERFACE;

	// Set CustomerId property

	if (SUCCEEDED(hr))
	{
		const int nNames = 1;		// number of names

		OLECHAR *	rgszNames[nNames] = { OLESTR("CustomerId") };
		DISPID		dispId[nNames];

		hr = pIDispatch->GetIDsOfNames( IID_NULL, rgszNames, nNames, 
										LOCALE_SYSTEM_DEFAULT, dispId);
		if (SUCCEEDED(hr))
		{
			CComVariant	varData(m_lCustomerId);
			DISPID		dispidPut = DISPID_PROPERTYPUT;
			DISPPARAMS	dispparams = {&varData, &dispidPut, 1, 1};
	
			hr = pIDispatch->Invoke(dispId[0], IID_NULL, LOCALE_USER_DEFAULT, 
									DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);
		}
	}

	// Set OrderId property

	if (SUCCEEDED(hr))
	{
		const int nNames = 1;	

		OLECHAR *	rgszNames[nNames] = { OLESTR("OrderId") };
		DISPID		dispId[nNames];

		hr = pIDispatch->GetIDsOfNames(	IID_NULL, rgszNames, nNames, 
										LOCALE_SYSTEM_DEFAULT, dispId);
		if (SUCCEEDED(hr))
		{
			CComVariant	varData(m_lOrderId);
			DISPID		dispidPut = DISPID_PROPERTYPUT;
			DISPPARAMS	dispparams = {&varData, &dispidPut, 1, 1};
	
			hr = pIDispatch->Invoke(dispId[0], IID_NULL, LOCALE_USER_DEFAULT, 
									DISPATCH_PROPERTYPUT, &dispparams, NULL, NULL, NULL);
		}
	}

	// Call LineItem method once for each line item

	if (SUCCEEDED(hr))
	{
		const int nNames = 3;			// number of names to look up

		OLECHAR *	rgszNames[nNames] = {	OLESTR("LineItem"),		// method name
											OLESTR("lItemId"),		// parm name
											OLESTR("lQuantity") };	// parm name
		DISPID		dispId[nNames];

		hr = pIDispatch->GetIDsOfNames(	IID_NULL, rgszNames, nNames, 
										LOCALE_SYSTEM_DEFAULT, dispId);

		for (int ix = 0; ix < m_veclItemId.size() && SUCCEEDED(hr); ix++)
		{
			const int nArgs = nNames - 1;		// number of arguments

			CComVariant varData[nArgs];			// number of arguments
			varData[0] = m_veclItemId[ix];
			varData[1] = m_veclQuantity[ix];

			DISPPARAMS dispparams = {varData, &dispId[1], nArgs, nArgs};
	
			hr = pIDispatch->Invoke(dispId[0], IID_NULL, LOCALE_USER_DEFAULT, 
									DISPATCH_METHOD, &dispparams, NULL, NULL, NULL);
		}
	}

	// Create Notify callback object
	if (SUCCEEDED(hr))
	{
		if (lFlags & processFlagQueuedComponents)
			pwszDisplayName = L"queue:/new:QCNotify.Notify";
		else
			pwszDisplayName = L"new:QCNotify.Notify";
		
		hr = CoGetObject(pwszDisplayName, NULL, IID_IUnknown, (void**)&punkNotify);
	}


	// Call Process method

	if (SUCCEEDED(hr))
	{
		const int nNames = 3;			// number of names to look up

		OLECHAR *	rgszNames[nNames] = {	OLESTR("Process"),		// method name
											OLESTR("lFlags"),		// parm name
											OLESTR("punkNotify")};	// parm name
		DISPID		dispId[nNames];

		hr = pIDispatch->GetIDsOfNames(	IID_NULL, rgszNames, nNames, 
										LOCALE_SYSTEM_DEFAULT, dispId);
		if (SUCCEEDED(hr))
		{
			const int nArgs = nNames - 1;	// number of arguments

/*
			VARIANTARG varData[nArgs];		// just the parameters 
			varData[0].vt = VT_I4; varData[0].lVal = lFlags;
			varData[1].vt = VT_UNKNOWN; (varData[1].punkVal = punkNotify)->AddRef();
			DISPPARAMS	dispparams = {varData, &dispId[1], nArgs, nArgs};
*/

			VARIANTARG varData[nArgs];		// just the parameters 
			varData[1].vt = VT_I4; varData[1].lVal = lFlags;
			varData[0].vt = VT_UNKNOWN; (varData[0].punkVal = punkNotify)->AddRef();
			DISPPARAMS	dispparams = {varData, 0, nArgs, 0};

			UINT foo;
			hr = pIDispatch->Invoke(dispId[0], IID_NULL, LOCALE_USER_DEFAULT, 
									DISPATCH_METHOD, &dispparams, NULL, NULL, &foo);

			VariantClear(&varData[0]);
			VariantClear(&varData[1]);
		}
	}
	return hr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  THIS IS A PRIVATE MEMBER FUNCTION

  Method:   COrder::InvokeShipVtable
  Summary:  Creates a Ship2 object to send to the shipping department
  Args:     IUnknown *	punkShip2 - IUnknown * to Shipping object
			long		lFlags	- flag longword with option bits 
  Modifies: None
  Returns:  HRESULT from the underlying requests
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

HRESULT COrder::InvokeShipVtable(IUnknown * punkShip2, long lFlags)
{
	HRESULT hr = S_OK;
	LPWSTR pwszDisplayName;
	CComQIPtr<IShip2, &IID_IShip2> pShip2(punkShip2);
	CComPtr<IUnknown> punkNotify;

	if (!pShip2) hr = E_NOINTERFACE;

	if (SUCCEEDED(hr)) hr = pShip2->put_CustomerId(m_lCustomerId);
			
	if (SUCCEEDED(hr)) hr = pShip2->put_OrderId(m_lOrderId);

	for (int ix = 0; ix < m_veclItemId.size() && SUCCEEDED(hr); ix++)
	{
		hr = pShip2->LineItem(m_veclItemId[ix], m_veclQuantity[ix]);
	}

	if (SUCCEEDED(hr))
	{
		if (lFlags & processFlagQueuedComponents)
			pwszDisplayName = L"queue:/new:QCNotify.Notify";
		else
			pwszDisplayName = L"new:QCNotify.Notify";
		
		hr = CoGetObject(pwszDisplayName, NULL, IID_IUnknown, (void**)&punkNotify);
	}

	if (SUCCEEDED(hr)) hr = pShip2->Process(lFlags, punkNotify);

	return hr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  THIS IS A PRIVATE MEMBER FUNCTION

  Method:   COrder::WriteOrderDB
  Summary:  Writes the order into the Order Entry table.
  Args:     None
  Modifies: Order Entry table
  Returns:  HRESULT from the underlying requests.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

HRESULT COrder::WriteOrderDB()
{
	CComPtr<ADOConnection> pADOConnection;

	HRESULT hr = CoCreateInstance(	CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER,
									IID_IADOConnection, (void **) &pADOConnection);
	if (SUCCEEDED(hr))
	{
		// Connect to the database.  name constants are in DataSourceNames.h
		
		hr = pADOConnection->Open(	_bstr_t(pszOrderDSN), _bstr_t(pszUserId),
									_bstr_t(pszPassword), adOpenUnspecified);

		// Write one row per line item
		for (int ix = 0; ix < m_veclItemId.size() && SUCCEEDED(hr); ix++)
		{
			TCHAR szSQLStmt[512];

			LPCTSTR const pszPrototypeInsertStmt =
					_T("insert into QCSampleOrder ")
					_T("	(order_id, cust_id, line_no, item_id, quantity) ")
					_T("	values(%ld, %ld, %ld, %ld, %ld)");

			wsprintf(	szSQLStmt,
						pszPrototypeInsertStmt,
						m_lOrderId,
						m_lCustomerId,
						ix,
						m_veclItemId[ix],
						m_veclQuantity[ix]);
		
			hr = pADOConnection->Execute(_bstr_t(szSQLStmt), NULL, adCmdText, NULL);
			// hr tested in for loop
		}
	}
	return hr;
}
