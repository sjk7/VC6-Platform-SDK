//==============================================================================
// Filename: UpdateReceipt.h
//
// Description: Declaration of UpdateReceipt
//
// This file is part of the Microsoft COM+ Samples
//
// Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved
//
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation.  See these other
// materials for detailed information reagrding Microsoft code samples.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
//==============================================================================


#if !defined(AFX_UPDATERECEIPT_H__A81260B9_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
#define AFX_UPDATERECEIPT_H__A81260B9_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUpdateReceipt

class CUpdateReceipt : 
	public IDispatchImpl<IUpdateReceipt, &IID_IUpdateReceipt, &LIBID_ACCOUNT>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CUpdateReceipt,&CLSID_CUpdateReceipt>
{
public:
	CUpdateReceipt() {}
BEGIN_COM_MAP(CUpdateReceipt)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUpdateReceipt)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CUpdateReceipt) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_UpdateReceipt)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IUpdateReceipt
public:
	STDMETHOD (Update) (OUT long* plReceiptNo);
};

#endif // !defined(AFX_UPDATERECEIPT_H__A81260B9_DDC8_11D0_B5A0_00C04FB957D8__INCLUDED_)
