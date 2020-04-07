/*+==========================================================================
  File:      Notify.cpp
  Summary:   Implementation of CONotify class
  Classes:   Implemented: CONotify
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
#include <adoid.h>		// ADO from OLEDBSDK
#include <adoint.h>		// ADO from OLEDBSDK
#include "QCNotify.h"	// MIDL output from QCNotify.idl
#include "Notify.h"		// Class header
#include "..\QCOrder\processFlags.h"	// process flag descriptions

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CONotify::put_CustomerId
  Summary:  property put for CustomerId property
  Args:     long lCustomerId			A customer identifier.
  Modifies: class member variable m_lCustomerId
  Returns:  HRESULT	- Always returns S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP CONotify::put_CustomerId(long lCustomerId)
{
	m_lCustomerId = lCustomerId;
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CONotify::put_OrderId
  Summary:  property put for OrderId property
  Args:     long lOrderId			An order identifier.
  Modifies: class member variable m_lOrderId
  Returns:  HRESULT	- Always returns S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP CONotify::put_OrderId(long lOrderId)
{
	m_lOrderId = lOrderId;
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CONotify::LineItem
  Summary:  Adds a single item to an order
  Args:     long lItemId			An item identifier (e.g. stock number)
			long lQuantity			Quantity of the item ordered
			ShipStatus shipStatus	Shipping Status (see QCSamp1.idl) 
  Modifies: class members m_veclItemId, m_veclQuantity, m_vecShipStatus 
  Returns:  HRESULT	- Always returns S_OK
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP CONotify::LineItem(long lItemId, long lQuantity, ShipStatus shipStatus)
{
	_ASSERTE(shipStatus >= ssShipped && shipStatus <= ssUnrecognizedItem);

	m_veclItemId.push_back(lItemId);
	m_veclQuantity.push_back(lQuantity);
	m_vecShipStatus.push_back(shipStatus);
	return S_OK;
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CONotify::Process
  Summary:  Updates order entry database with shipping status strings.
  Args:     long	lFlags - option flag bits
  Modifies: Rows in order entry database (DSN = QCSampOrder)
			Issues COM+ SetComplete or SetAbort depending on request success.
  Returns:  HRESULT	- returns failure from embedded function requests or S_OK.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/ 

STDMETHODIMP CONotify::Process(long lFlags)
{
	HRESULT hr = S_OK;

	_RPT1(_CRT_WARN, "QCSamp1 %d Notify\n", m_lOrderId);

	if (lFlags & processFlagWriteDB)
	{
		CComPtr<ADOConnection> pADOConnection;

		hr = CoCreateInstance(	CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER,
								IID_IADOConnection, (void **) &pADOConnection);
		if (SUCCEEDED(hr))
		{
			// Constants for Data Source Names, userid, password are in DataSourceName.h

			hr = pADOConnection->Open(	_bstr_t(pszOrderDSN), _bstr_t(pszUserId),
										_bstr_t(pszPassword), adOpenUnspecified);

			TCHAR szSQLStmt[512];

			// The elements in this array correspond to the ShipStatus enumeration
			LPCTSTR const apszShipStatus[] =
			{
				_T("Not yet processed"),
				_T("Shipped"),
				_T("Back Ordered"),
				_T("Not Stocked"),
				_T("Unrecognized Item ID")
			};

			LPCTSTR const pszPrototypeSQLStmt =
				_T("update QCSampleOrder set ship_status = \'%s\' ")
				_T(" where order_id = %ld ")
				_T("   and cust_id  = %ld ")
				_T("   and line_no  = %ld ")
				_T("   and item_id  = %ld ")
				_T("   and quantity = %ld ");

			for (int ix = 0; ix < m_veclItemId.size() && SUCCEEDED(hr); ix++)
			{
				wsprintf(	szSQLStmt,
							pszPrototypeSQLStmt,
							apszShipStatus[m_vecShipStatus[ix]],
							m_lOrderId,
							m_lCustomerId,
							ix,
							m_veclItemId[ix],
							m_veclQuantity[ix]);

				hr = pADOConnection->Execute(_bstr_t(szSQLStmt), NULL, adCmdText, NULL);
			}
		}
	}
	// Invoke SetComplete or SetAbort depending on our success

	CComPtr<IObjectContext> pIObjectContext;

	if (SUCCEEDED(CoGetObjectContext(IID_IObjectContext, (void**)&pIObjectContext)))
	{
		if (SUCCEEDED(hr))	pIObjectContext->SetComplete();
		else				pIObjectContext->SetAbort();
	}

	return hr;
}
