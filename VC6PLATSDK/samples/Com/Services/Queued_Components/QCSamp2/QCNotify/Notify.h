/*+==========================================================================
  File:      Notify.h
  Summary:   Declaration of CONotify class
  Classes:   Declared: CONotify
  Origin:    Implementation of case study in Queued Components specification
----------------------------------------------------------------------------
  Copyright 1992 - 2000 Microsoft Corporation, All rights reserved.

    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
    ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
    PARTICULAR PURPOSE
==========================================================================+*/ 

#ifndef __NOTIFY_H_
#define __NOTIFY_H_

#include "resource.h"       // main symbols

/*O+O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O+++O
  ObjectClass: CONotify
  Summary:  Updates shipping status column of Order Entry database
  Interfaces:  IUnknown				Standard COM object feature interface
               IDispatch			Automation interface
	           INotify				Represents an order
  Aggregation: Not supported
O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O---O-O*/  

class ATL_NO_VTABLE CONotify : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CONotify, &CLSID_Notify>,
	public IDispatchImpl<INotify, &IID_INotify, &LIBID_QCNOTIFYLib>
{
public:
	CONotify() : m_lCustomerId(0), m_lOrderId(0)	// ctor
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_NOTIFY)
DECLARE_NOT_AGGREGATABLE(CONotify)

BEGIN_COM_MAP(CONotify)
	COM_INTERFACE_ENTRY(INotify)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

public: // IOrder interface
	STDMETHOD(Process)(long lFlags);
	STDMETHOD(LineItem)(long lItemId, long lQuantity, ShipStatus shipStatus);
	STDMETHOD(put_OrderId)(long lOrderId);
	STDMETHOD(put_CustomerId)(long lCustomerId);

private: // Member variables
	long					m_lCustomerId;
	long					m_lOrderId;
	std::vector<long>		m_veclItemId;
	std::vector<long>		m_veclQuantity;
	std::vector<ShipStatus>	m_vecShipStatus;
};

#endif //__NOTIFY_H_
