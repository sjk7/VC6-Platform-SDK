/*+==========================================================================

File: STATest.h

Summary: Declaration of the CSTATest

----------------------------------------------------------------------------
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

#ifndef __STATEST_H_
#define __STATEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSTATest
class ATL_NO_VTABLE CSTATest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSTATest, &CLSID_STATest>,
	public IDispatchImpl<ISyncTest, &IID_ISyncTest, &LIBID_STAOBJECTLib>
{
public:
	CSTATest()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STATEST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSTATest)
	COM_INTERFACE_ENTRY(ISyncTest)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISyncTest
public:
	STDMETHOD(Exercise)(void);
};

#endif //__STATEST_H_
