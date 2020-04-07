/*+==========================================================================

File: FreeTest.h

Summary: Declaration of the CFreeTest

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

#ifndef __FREETEST_H_
#define __FREETEST_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFreeTest
class ATL_NO_VTABLE CFreeTest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFreeTest, &CLSID_FreeTest>,
	public IDispatchImpl<ISyncTest, &IID_ISyncTest, &LIBID_FREEOBJECTLib>
{
public:
	CFreeTest()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FREETEST)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFreeTest)
	COM_INTERFACE_ENTRY(ISyncTest)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISyncTest
public:
	STDMETHOD(Exercise)(void);
};

#endif //__FREETEST_H_
