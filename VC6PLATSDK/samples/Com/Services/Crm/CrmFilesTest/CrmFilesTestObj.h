/*+==========================================================================

File: CrmFilesTestObj.h



Summary: 

	Test driver component for CrmFiles CRM, VC, VB and VJ versions.

	Should be installed in a COM+ application and requires a transaction.

	This file is part of the Microsoft COM Technology Samples.


Classes: what classes are in this file



Functions: (optional) 

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
// CrmFilesTestObj.h : Declaration of the CCrmFilesTest


#ifndef __CRMFILESTEST_H_
#define __CRMFILESTEST_H_

#include "resource.h"       // main symbols
#include <comsvcs.h>

#include "comdef.h"			// _bstr_t, etc

// ICrmFilesWorker - interface for the create file/delete file CRM Worker 
#include "CrmFiles.h"		

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CCrmFilesTest

	This is the component that drives the sample. It should be installed into 
	COM+ explorer as part of it's own application. It requires transactions. 
	This component creates the worker object and does work on it. Then
	commits	or aborts its transaction.

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/////////////////////////////////////////////////////////////////////////////
// CCrmFilesTest
class ATL_NO_VTABLE CCrmFilesTest : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCrmFilesTest, &CLSID_CrmFilesTest>,
	public IObjectControl,
	public IDispatchImpl<ICrmFilesTest, &IID_ICrmFilesTest, &LIBID_CRMFILESTESTLib>
{
public:
	CCrmFilesTest() :
	 m_lLanguage(0)
	,m_pICrmFilesWorkerCurrent(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CRMFILESTEST)
DECLARE_NOT_AGGREGATABLE(CCrmFilesTest)

BEGIN_COM_MAP(CCrmFilesTest)
	COM_INTERFACE_ENTRY(ICrmFilesTest)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();

	CComPtr<IObjectContext> m_spObjectContext;

// ICrmFilesTest
public:
	STDMETHOD(put_Language)(/*[in]*/ long newVal);
	STDMETHOD(Abort)();
	STDMETHOD(Commit)();
	STDMETHOD(DeleteFile)();
	STDMETHOD(CreateFile)();
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);

private:

	HRESULT GetCorrectCRM(void);

private:

	enum { crm_VC, crm_VB, crm_VJ, crm_Total };

	long						m_lLanguage;

	_bstr_t						m_bstrFileName;

	ICrmFilesWorker				*m_pICrmFilesWorkerCurrent;

	ICrmFilesWorker				*m_pICrmFilesWorker[crm_Total];	
};

#endif //__CRMFILESTEST_H_
