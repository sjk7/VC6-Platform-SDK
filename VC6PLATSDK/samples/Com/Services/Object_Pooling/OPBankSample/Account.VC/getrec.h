/*+==========================================================================
  File:      GetRec.h
  Summary:   Header for Object Pooled Get Receipt component
  Classes:   CGetReceipt
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

#if !defined(AFX_GETRECEIPT_H__A81260B3_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
#define AFX_GETRECEIPT_H__A81260B3_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_


#include "resource.h"       // main symbols

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class:	CGetReceipt
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

class CGetReceipt : 
	public CComDualImpl<IGetReceipt, &IID_IGetReceipt, &LIBID_ACCOUNT>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CGetReceipt,&CLSID_CGetReceipt>
{
public:
	CGetReceipt() {}
BEGIN_COM_MAP(CGetReceipt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IGetReceipt)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_GetReceipt)

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IGetReceipt
public:
	STDMETHOD (GetNextReceipt) (OUT long* plReceiptNo);
};

#endif // !defined(AFX_GETRECEIPT_H__A81260B3_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
