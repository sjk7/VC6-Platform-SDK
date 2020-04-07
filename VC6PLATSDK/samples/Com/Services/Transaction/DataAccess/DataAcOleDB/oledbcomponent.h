//==============================================================================
// Filename: OLEDBComponent.h
//
// Description: Declaration of the COLEDBComponent
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




#ifndef __OLEDBCOMPONENT_H_
#define __OLEDBCOMPONENT_H_
#include "resource.h"       // main symbols
#include <comsvcs.h>

#define UNICODE
#define DBINITCONSTANTS // Initialize OLE constants...
#define INITGUID        // ...once in each app

/////////////////////////////////////////////////////////////////////////////
// COLEDBComponent
class ATL_NO_VTABLE COLEDBComponent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<COLEDBComponent, &CLSID_OLEDBComponent>,
	public IObjectControl,
	//public IOLEDBComponent
	public IDispatchImpl<IOLEDBComponent, &IID_IOLEDBComponent, &LIBID_OLEDBKBLib>
	
	{
public:
	COLEDBComponent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_OLEDBCOMPONENT)
DECLARE_NOT_AGGREGATABLE(COLEDBComponent)

BEGIN_COM_MAP(COLEDBComponent)
	COM_INTERFACE_ENTRY(IOLEDBComponent)
	COM_INTERFACE_ENTRY(IObjectControl)
END_COM_MAP()

// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();

	CComPtr<IObjectContext> m_spObjectContext;

// IOLEDBComponent
public:
	STDMETHOD(SimpleQuery)(/*[in, out]*/ BSTR * returnval);
};

#endif //__OLEDBCOMPONENT_H_
