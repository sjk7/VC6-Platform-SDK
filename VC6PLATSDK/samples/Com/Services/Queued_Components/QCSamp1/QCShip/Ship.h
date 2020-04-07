/*+==========================================================================
  File:      Ship.h
  Summary:   Declaration of COShip class
  Classes:   Declared: COShip
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

#ifndef __SHIP_H_
#define __SHIP_H_

#include "resource.h"       // main symbols
#include "..\QCNotify\QCNotify.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  ObjectClass: COShip
  Summary:     Writes order to shipping database.
			   Assigns shipping status to each line item.
			   Creates Notify object to inform requestor of shipping status.
  Interfaces:  IUnknown				Standard COM object feature interface
               IDispatch			Automation interface
	           IShip				Represents an order
  Aggregation: Not supported
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/  

class ATL_NO_VTABLE COShip : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COShip, &CLSID_Ship>,
	public IDispatchImpl<IShip, &IID_IShip, &LIBID_QCSHIPLib>
{
public:
	COShip() : m_lCustomerId(0), m_lOrderId(0)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SHIP)
DECLARE_NOT_AGGREGATABLE(COShip)

BEGIN_COM_MAP(COShip)
	COM_INTERFACE_ENTRY(IShip)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public: // IOrder
	STDMETHOD(Process)(long lFlags);
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
	HRESULT		NotifyRequestor(long lFlags);
	HRESULT		InvokeNotifyIDispatch(IUnknown * punk, long lFlags);
	HRESULT		InvokeNotifyVtable(IUnknown * punk, long lFlags);
	ShipStatus	RandomShipStatus();
};

#endif //__SHIP_H_
