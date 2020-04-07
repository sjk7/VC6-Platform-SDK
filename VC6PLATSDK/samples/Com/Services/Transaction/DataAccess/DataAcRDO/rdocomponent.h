//==============================================================================
// Filename: RDOComponent.h 
//
// Description: Declaration of the CRDOComponent
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



#ifndef __RDOCOMPONENT_H_
#define __RDOCOMPONENT_H_

#include "resource.h"       // main symbols
#include <comsvcs.h>

/////////////////////////////////////////////////////////////////////////////
// CRDOComponent
class ATL_NO_VTABLE CRDOComponent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CRDOComponent, &CLSID_RDOComponent>,
	public IObjectControl,
	public IDispatchImpl<IRDOComponent, &IID_IRDOComponent, &LIBID_RDOKBLib>
{
public:
	CRDOComponent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_RDOCOMPONENT)
DECLARE_NOT_AGGREGATABLE(CRDOComponent)

BEGIN_COM_MAP(CRDOComponent)
	COM_INTERFACE_ENTRY(IRDOComponent)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();

	CComPtr<IObjectContext> m_spObjectContext;

// IRDOComponent
public:
	STDMETHOD(SimpleQuery)(/*[in, out]*/ VARIANT * returnval);
};

#endif //__RDOCOMPONENT_H_
