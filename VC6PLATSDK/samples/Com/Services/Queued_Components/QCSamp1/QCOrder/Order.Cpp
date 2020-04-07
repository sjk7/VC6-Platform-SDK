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
-----------------------------------------------------------------------------

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
#include "..\DataSourceNames.h"	// ADO Data Source Names, userid, password
#include <adoid.h>		// ADO OLEDBSDK 
#include <adoint.h>		// ADO OLEDBSDK
#include "QCOrder.h"
#include "Order.h"
#include "..\QCOrder\processFlags.h"
#include "..\QCShip\QCShip.h"

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

	_RPT1(_CRT_WARN, "QCSamp1 %d Order\n", m_lOrderId);
		
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
		pwszDisplayName = L"queue:/new:QCShip.Ship";
	else
		pwszDisplayName = L"new:QCShip.Ship";

	CComPtr<IUnknown> punkShip;

	HRESULT hr = CoGetObject(pwszDisplayName, 0, IID_IUnknown, (void **) &punkShip);
	if (SUCCEEDED(hr))
	{
		if (lFlags & processFlagLateBound)
			hr = InvokeShipIDispatch(punkShip, lFlags);
		else
			hr = InvokeShipVtable(punkShip, lFlags);	
	}
	return hr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  THIS IS A PRIVATE MEMBER FUNCTION

  Method:   COrder::InvokeShipIDispatch
  Summary:  Creates a Ship object to send to the shipping department
  Args:     IUnknown *	punkShip - IUnknown * to Shipping object
			long		lFlags	- flag longword with option bits   
  Modifies: None
  Returns:  HRESULT from the underlying requests
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

HRESULT COrder::InvokeShipIDispatch(IUnknown * punkShip, long lFlags)
{
	HRESULT hr = S_OK;

	CComQIPtr<IDispatch, &IID_IDispatch> pIDispatch(punkShip);
	
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

	// Call Process method

	if (SUCCEEDED(hr))
	{
		const int nNames = 2;			// number of names to look up

		OLECHAR *	rgszNames[nNames] = {	OLESTR("Process"),		// method name
											OLESTR("lFlags") };		// parm name
		DISPID		dispId[nNames];

		hr = pIDispatch->GetIDsOfNames(	IID_NULL, rgszNames, nNames, 
										LOCALE_SYSTEM_DEFAULT, dispId);
		if (SUCCEEDED(hr))
		{
			const int nArgs = nNames - 1;	// number of arguments

			CComVariant varData[nArgs];		// just the parameters 
			varData[0] = lFlags;

			DISPPARAMS	dispparams = {varData, &dispId[1], nArgs, 0};

			hr = pIDispatch->Invoke(dispId[0], IID_NULL, LOCALE_USER_DEFAULT, 
									DISPATCH_METHOD, &dispparams, NULL, NULL, NULL);
		}
	}
	return hr;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  THIS IS A PRIVATE MEMBER FUNCTION

  Method:   COrder::InvokeShipVtable
  Summary:  Creates a Ship object to send to the shipping department
  Args:     IUnknown *	punkShip - IUnknown * to Shipping object
			long		lFlags	- flag longword with option bits 
  Modifies: None
  Returns:  HRESULT from the underlying requests
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

HRESULT COrder::InvokeShipVtable(IUnknown * punkShip, long lFlags)
{
	HRESULT hr = S_OK;

	CComQIPtr<IShip, &IID_IShip> pShip(punkShip);

	if (!pShip) hr = E_NOINTERFACE;

	if (SUCCEEDED(hr)) hr = pShip->put_CustomerId(m_lCustomerId);
			
	if (SUCCEEDED(hr)) hr = pShip->put_OrderId(m_lOrderId);

	for (int ix = 0; ix < m_veclItemId.size() && SUCCEEDED(hr); ix++)
	{
		hr = pShip->LineItem(m_veclItemId[ix], m_veclQuantity[ix]);
	}

	if (SUCCEEDED(hr)) hr = pShip->Process(lFlags);

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
