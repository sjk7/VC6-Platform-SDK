//==============================================================================
// Filename: ADOComponent.h
//
// Description: Declaration of the CADOComponent
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



#ifndef __ADOCOMPONENT_H_
#define __ADOCOMPONENT_H_

#include "resource.h"       // main symbols
#include <comsvcs.h>

/////////////////////////////////////////////////////////////////////////////
// CADOComponent
class ATL_NO_VTABLE CADOComponent : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CADOComponent, &CLSID_ADOComponent>,
	public IObjectControl,
	public IDispatchImpl<IADOComponent, &IID_IADOComponent, &LIBID_ADOKBLib>
{
public:
	CADOComponent()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ADOCOMPONENT)
DECLARE_NOT_AGGREGATABLE(CADOComponent)

BEGIN_COM_MAP(CADOComponent)
	COM_INTERFACE_ENTRY(IADOComponent)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();

	CComPtr<IObjectContext> m_spObjectContext;

// IADOComponent
public:
	STDMETHOD(SimpleQuery)(/*[in, out]*/ VARIANT * returnval);
};

#endif //__ADOCOMPONENT_H_
