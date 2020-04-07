/*+==========================================================================

File: CrmMonCompObj.h



Summary:	This is a sample of how to use the monitoring interfaces for the Compensating Resource Manager (CRM).

			The following interfaces are used -

			  ICrmMonitor
			  ICrmMonitorLogRecords
			  ICrmMonitorClerks
			  ICrmFormatLogRecords

			This sample shows how CRM clerks in a specified transaction can be found and queried.

			This component should be installed in the application to be monitored. It does not require a transaction.


Classes: CCrmMonComp


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

#ifndef __CRMMONCOMP_H_
#define __CRMMONCOMP_H_

#include "resource.h"       // main symbols

#include "comdef.h"			// for _variant_t

#include <comsvcs.h>		// CRM interfaces

// STL

#include <vector>
using namespace std;
#pragma warning(disable:4786)
// warning C4786: identifier was truncated to '255' characters in the browser information

struct CLERK_ENTRY
{
	_variant_t					m_vIndex;

	ICrmMonitorLogRecords		*m_pICrmMonitorLogRecords;
};

typedef vector<CLERK_ENTRY *> VEC_CLERKS;		        // array of held clerks

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CCrmMonComp

	This is a monitor for the CRM. It captures a snapshot of the current
	state of the CRMs and holds a specific CRM clerk.

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/////////////////////////////////////////////////////////////////////////////
// CCrmMonComp
class ATL_NO_VTABLE CCrmMonComp : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCrmMonComp, &CLSID_CrmMonComp>,
	public ICrmMonComp
{
public:
	CCrmMonComp() :
	 m_pICrmMonitor(NULL)
	,m_pICrmMonitorClerks(NULL)
	,m_lClerkNumber(0)
	,m_lRecordNumber(0)
	,m_pICrmFormatLogRecords(NULL)
	{
		m_pUnkMarshaler = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CRMMONCOMP)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCrmMonComp)
	COM_INTERFACE_ENTRY(ICrmMonComp)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

	HRESULT FinalConstruct();

	void FinalRelease();

	CComPtr<IUnknown> m_pUnkMarshaler;

// ICrmMonComp
public:
	STDMETHOD(get_FormattedRecord)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_ColumnHeaders)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetRecord)(/*[in]*/ long lRecordNumber);
	STDMETHOD(AbortTransaction)();
	STDMETHOD(get_NumberOfLogRecords)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_ProgId)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_ActivityId)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_TransactionState)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(SetClerk)(/*[in]*/ long lClerkNumber);
	STDMETHOD(get_FindClerks)(/*[out, retval]*/ long * plNumberOfClerks);
	STDMETHOD(put_TransactionUOW)(/*[in]*/ VARIANT newVal);

private:

	HRESULT CreateCompensator(void);

private:

	ICrmMonitor					*m_pICrmMonitor;

	ICrmMonitorClerks			*m_pICrmMonitorClerks;

	_variant_t					m_vTxUOWRequired;

	VEC_CLERKS					m_vecClerks;

	_variant_t					m_vActivityId;

	long						m_lClerkNumber;

	long						m_lRecordNumber;

	ICrmFormatLogRecords		*m_pICrmFormatLogRecords;

};

#endif //__CRMMONCOMP_H_
