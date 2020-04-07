/*+==========================================================================

File: ComSyncTest.h

Summary: Declaration of the CComSyncTest

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

#ifndef __COMSYNCTEST_H_
#define __COMSYNCTEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CComSyncTest
class ATL_NO_VTABLE CComSyncTest : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CComSyncTest, &CLSID_ComSyncTest>,
	public IDispatchImpl<ISyncTest, &IID_ISyncTest, &LIBID_COMSYNCOBJECTLib>
{
public:
	CComSyncTest()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMSYNCTEST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CComSyncTest)
	COM_INTERFACE_ENTRY(ISyncTest)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISyncTest
public:
	STDMETHOD(Exercise)(void);
};

#endif //__COMSYNCTEST_H_
