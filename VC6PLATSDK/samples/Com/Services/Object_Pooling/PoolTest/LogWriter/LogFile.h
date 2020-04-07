/*+==========================================================================

File: LogFile.h

Summary: Declaration of CLogFile

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

#ifndef __LOGFILE_H_
#define __LOGFILE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLogFile
class ATL_NO_VTABLE CLogFile : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLogFile, &CLSID_LogFile>,
	public IDispatchImpl<ILogFile, &IID_ILogFile, &LIBID_LOGWRITERLib>,
	public IObjectControl,
	public IObjectConstruct
{
public:
	CLogFile()
	{
	}

	~CLogFile();

DECLARE_REGISTRY_RESOURCEID(IDR_LOGFILE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLogFile)
	COM_INTERFACE_ENTRY(ILogFile)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IObjectConstruct)
END_COM_MAP()

private:
// ILogFile
	STDMETHOD(Write)(/*[in]*/ BSTR buf, /*[in]*/ DWORD dwID);

// IObjectControl
	STDMETHOD(Activate)();
	STDMETHOD_(VOID, Deactivate)();
	STDMETHOD_(BOOL, CanBePooled)();

// IObjectConstruct
	STDMETHOD(Construct)(IDispatch * pCtorObj);

// private vars
	HANDLE	m_hFile;
	IContextState* m_pContextState;
	
};

#endif //__LOGFILE_H_
