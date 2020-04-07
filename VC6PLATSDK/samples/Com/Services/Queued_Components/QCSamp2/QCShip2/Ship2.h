/*+==========================================================================
  File:      Ship2.h
  Summary:   Declaration of COShip2 class
  Classes:   Declared: COShip2
  Origin:    Implementation of case study in Queued Components specification
----------------------------------------------------------------------------
  Copyright 1992 - 2000 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE
==========================================================================+*/ 

#ifndef __SHIP2_H_
#define __SHIP2_H_

#include "resource.h"       // main symbols
#include "..\QCNotify\QCNotify.h"

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: COShip2
  Summary:     Writes order to shipping database.
			   Assigns shipping status to each line item.
			   Creates Notify object to inform requestor of shipping status.
  Interfaces:  IUnknown				Standard COM object feature interface
               IDispatch			Automation interface
	           IShip2				Represents an order
  Aggregation: Not supported
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/  

class ATL_NO_VTABLE COShip2 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COShip2, &CLSID_Ship2>,
	public IDispatchImpl<IShip2, &IID_IShip2, &LIBID_QCSHIP2Lib>
{
public:
	COShip2() : m_lCustomerId(0), m_lOrderId(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SHIP2)
DECLARE_NOT_AGGREGATABLE(COShip2)

BEGIN_COM_MAP(COShip2)
	COM_INTERFACE_ENTRY(IShip2)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public: // IOrder
	STDMETHOD(Process)(long lFlags, IUnknown *punk);
	STDMETHOD(LineItem)(long lItemId, long lQuantity);
	STDMETHOD(put_OrderId)(long lOrderId);
	STDMETHOD(put_CustomerId)(long lCustomerId);

private:
	long					m_lCustomerId;
	long					m_lOrderId;
	std::vector<long>		m_veclItemId;
	std::vector<long>		m_veclQuantity;
	std::vector<ShipStatus>	m_vecShipStatus;

	HRESULT		WriteShipDB();
	HRESULT		NotifyRequestor(long lFlags, IUnknown *punkNotify);
	HRESULT		InvokeNotifyIDispatch(IUnknown * punk, long lFlags);
	HRESULT		InvokeNotifyVtable(IUnknown * punk, long lFlags);
	ShipStatus	RandomShipStatus();
};

#endif //__SHIP2_H_
