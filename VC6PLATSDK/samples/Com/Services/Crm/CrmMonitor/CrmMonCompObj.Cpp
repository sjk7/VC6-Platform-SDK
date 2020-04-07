/*+==========================================================================

File: CrmMonCompObj.cpp



Summary: 

	This is a sample of how to use the monitoring interfaces for the Compensating Resource Manager (CRM).

	The following interfaces are used -

	  ICrmMonitor
	  ICrmMonitorLogRecords
	  ICrmMonitorClerks

	  ICrmFormatLogRecords

	This sample shows how CRM clerks in a specified transaction can be found and queried.

	This component should be installed in the application to be monitored. It does not require a transaction.

	This file is part of the Microsoft COM Technology Samples.

Classes: 
	CCrmMonComp

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
// CrmMonCompObj.cpp : Implementation of CCrmMonComp

#include "stdafx.h"
#include "CrmMonComp.h"
#include "CrmMonCompObj.h"

/////////////////////////////////////////////////////////////////////////////
// CCrmMonComp

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::FinalConstruct()

Summary: Final Construct

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmMonComp::FinalConstruct()
{
	HRESULT hr = S_OK;

	hr = CoCreateInstance(
			__uuidof(CRMRecoveryClerk), 
			NULL, 
			CLSCTX_INPROC_SERVER, 
			__uuidof(ICrmMonitor), 
			(void **)&m_pICrmMonitor);

	_ASSERTE(S_OK == hr);
	_ASSERTE(m_pICrmMonitor);

	return CoCreateFreeThreadedMarshaler(
		GetControllingUnknown(), &m_pUnkMarshaler.p);

} // CCrmMonComp::FinalConstruct


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::FinalRelease()

Summary: Final Release

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


void CCrmMonComp::FinalRelease()
{
	if (m_pICrmMonitorClerks)
	{
		m_pICrmMonitorClerks->Release();

		m_pICrmMonitorClerks = NULL;
	}

	// clean up clerks array

	for (int i = 0; i < m_vecClerks.size(); i++)
	{
		CLERK_ENTRY * pce = m_vecClerks[i];

		_ASSERTE(pce);

		pce->m_pICrmMonitorLogRecords->Release();

		delete pce;
	}

	_ASSERTE(m_pICrmMonitor);

	m_pICrmMonitor->Release();

	m_pUnkMarshaler.Release();

} // CCrmMonComp::FinalRelease


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::put_TransactionUOW(VARIANT newVal)

Summary: Put the Transaction Property

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::put_TransactionUOW(VARIANT newVal)
{
	HRESULT hr = VariantCopy(&m_vTxUOWRequired, &newVal);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::put_TransactionUOW


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_FindClerks(long * plNumberOfClerks)

Summary: Get the number of clerks

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::get_FindClerks(long * plNumberOfClerks)
{
	_ASSERTE(plNumberOfClerks);

	long lNumberOfClerks = 0;

	*plNumberOfClerks = lNumberOfClerks;

	HRESULT hr = S_OK;

	_ASSERTE(m_pICrmMonitor);

	if (m_pICrmMonitorClerks)
	{
		m_pICrmMonitorClerks->Release();

		m_pICrmMonitorClerks = NULL;
	}

    hr = m_pICrmMonitor->GetClerks(&m_pICrmMonitorClerks);

    _ASSERTE(S_OK == hr);
    _ASSERTE(m_pICrmMonitorClerks);

	// how many clerks?

	long lClerkCount = 0;

	hr = m_pICrmMonitorClerks->get_Count(&lClerkCount);

    _ASSERTE(S_OK == hr);

	ATLTRACE(_T("lClerkCount = %d\r\n"), lClerkCount);

	if (0 == lClerkCount)
	{
		return S_OK;
	}

	// find and hold the clerk(s) we are looking for

	for (long lIndex = 0; lIndex < lClerkCount; lIndex++)
	{
		_variant_t vIndex = lIndex;

		_variant_t vTxUOWClerk;

		hr = m_pICrmMonitorClerks->TransactionUOW(vIndex, &vTxUOWClerk);

		_ASSERTE(S_OK == hr);

		if (vTxUOWClerk != m_vTxUOWRequired) continue; // not found

		// found it

		ATLTRACE(_T("found clerk # %d\r\n"), lIndex);

		// get the clerk CLSID

		_variant_t vClerkClsid;

		hr = m_pICrmMonitorClerks->Item(vIndex, &vClerkClsid);

		_ASSERTE(S_OK == hr);

		// get the clerk from the recovery clerk

		_variant_t vClerk;

		hr = m_pICrmMonitor->HoldClerk(vClerkClsid, &vClerk);

		// clerk may have gone

		if (E_FAIL == hr)
		{
			ATLTRACE(_T("clerk # %d has gone\r\n"), lIndex);

			continue;
		}

		_ASSERTE(S_OK == hr);

		lNumberOfClerks++;

		_variant_t vActivityId;

		if (1 == lNumberOfClerks)
		{
			// first time, get the activity id

			hr = m_pICrmMonitorClerks->ActivityId(vIndex, &vActivityId);

			_ASSERTE(S_OK == hr);

			m_vActivityId = vActivityId;
		}

		// activity id should be same for all clerks

		_ASSERTE(m_vActivityId == vActivityId);

		IUnknown * punkClerk = (IUnknown *)vClerk;

		_ASSERTE(punkClerk);

		ICrmMonitorLogRecords * pICrmMonitorLogRecords = NULL;

		hr = punkClerk->QueryInterface(
								__uuidof(ICrmMonitorLogRecords),
								(void **)&pICrmMonitorLogRecords);

		_ASSERTE(S_OK == hr);
		_ASSERTE(pICrmMonitorLogRecords);

		punkClerk->Release();

		// put this clerk on the list

		CLERK_ENTRY * pce = new CLERK_ENTRY;

		_ASSERTE(pce);

		pce->m_vIndex = vIndex;

		pce->m_pICrmMonitorLogRecords = pICrmMonitorLogRecords;

		m_vecClerks.push_back(pce);
	}

	*plNumberOfClerks = lNumberOfClerks;

	_ASSERTE(m_vecClerks.size() == lNumberOfClerks);

	return S_OK;

} // CCrmMonComp::FindClerks


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_FindClerks(long * plNumberOfClerks)

Summary: Set the clerk to the given number 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::SetClerk(long lClerkNumber)
{
	long lNumClerks = (long) m_vecClerks.size();

	if ((lClerkNumber < 0) || (lClerkNumber >= lNumClerks))
	{
		ATLTRACE(_T("ERROR: no such clerk, %d, %d\r\n"), lClerkNumber, lNumClerks);

		return E_FAIL;
	}

	m_lClerkNumber = lClerkNumber;

	return S_OK;

} // CCrmMonComp::SetClerk


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_TransactionState(VARIANT * pVal)

Summary: Get the state of the current transaction. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmMonComp::get_TransactionState(VARIANT * pVal)
{
	_ASSERTE(pVal);

	long lNumClerks = (long) m_vecClerks.size();

	if (0 == lNumClerks)
	{
		ATLTRACE(_T("ERROR: no clerks\r\n"));

		return E_FAIL;
	}

	HRESULT hr = S_OK;

	// get the transaction state from the 1st clerk only - should be same for all clerks

	CLERK_ENTRY * pce = m_vecClerks.front();

	_ASSERTE(pce);

	ICrmMonitorLogRecords * pICrmMonitorLogRecords = pce->m_pICrmMonitorLogRecords;

	_ASSERTE(pICrmMonitorLogRecords);

	CrmTransactionState txs;

	hr = pICrmMonitorLogRecords->get_TransactionState(&txs);

	_ASSERTE(S_OK == hr);

	ATLTRACE(_T("txs = %d\r\n"), txs);

	_variant_t vTxState = L"Unknown";

	switch (txs)
	{
		case TxState_Active: vTxState = _variant_t("Active"); break;

		case TxState_Committed: vTxState = _variant_t("Committed"); break;
		
		case TxState_Aborted: vTxState = _variant_t("Aborted"); break;
		
		case TxState_Indoubt: vTxState = _variant_t("Indoubt"); break;

		default: 
			
			_ASSERTE(!"ERROR: unknown transaction state");

			return E_FAIL;

			break;
	};

	hr = VariantCopy(pVal, &vTxState);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::get_TransactionState



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_ActivityId(VARIANT * pVal)

Summary: Get the current Activity ID

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmMonComp::get_ActivityId(VARIANT * pVal)
{
	_ASSERTE(pVal);

	long lNumClerks = (long) m_vecClerks.size();

	if (0 == lNumClerks)
	{
		ATLTRACE(_T("ERROR: no clerks\r\n"));

		return E_FAIL;
	}

	HRESULT hr = VariantCopy(pVal, &m_vActivityId);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::get_ActivityId


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_ProgId(VARIANT * pVal)

Summary: Get the current Prog ID

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmMonComp::get_ProgId(VARIANT * pVal)
{
	_ASSERTE(pVal);

	long lNumClerks = (long) m_vecClerks.size();

	if (0 == lNumClerks)
	{
		ATLTRACE(_T("ERROR: no clerks\r\n"));

		return E_FAIL;
	}

	HRESULT hr = S_OK;

	CLERK_ENTRY * pce = m_vecClerks[m_lClerkNumber];

	_ASSERTE(pce);

	_variant_t vProgId = L"Unknown ProgId";

	hr = m_pICrmMonitorClerks->ProgIdCompensator(pce->m_vIndex, &vProgId);

	_ASSERTE(S_OK == hr);

	hr = VariantCopy(pVal, &vProgId);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::get_ProgId


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_Description(VARIANT * pVal)

Summary: Calls ICRMMonitorClerks::Description.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::get_Description(VARIANT * pVal)
{
	_ASSERTE(pVal);

	long lNumClerks = (long) m_vecClerks.size();

	if (0 == lNumClerks)
	{
		ATLTRACE(_T("ERROR: no clerks\r\n"));

		return E_FAIL;
	}

	HRESULT hr = S_OK;

	CLERK_ENTRY * pce = m_vecClerks[m_lClerkNumber];

	_ASSERTE(pce);

	_variant_t vDescription = L"Unknown Description";

	hr = m_pICrmMonitorClerks->Description(pce->m_vIndex, &vDescription);
	
	_ASSERTE(S_OK == hr);

	hr = VariantCopy(pVal, &vDescription);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::get_Description


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_NumberOfLogRecords(VARIANT * pVal)

Summary: Gets number of log records

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::get_NumberOfLogRecords(long * pVal)
{
	_ASSERTE(pVal);

	long lNumClerks = (long) m_vecClerks.size();

	if (0 == lNumClerks)
	{
		ATLTRACE(_T("ERROR: no clerks\r\n"));

		return E_FAIL;
	}

	HRESULT hr = S_OK;

	CLERK_ENTRY * pce = m_vecClerks[m_lClerkNumber];

	_ASSERTE(pce);

	ICrmMonitorLogRecords * pICrmMonitorLogRecords = pce->m_pICrmMonitorLogRecords;

	_ASSERTE(pICrmMonitorLogRecords);

	hr = pICrmMonitorLogRecords->get_Count(pVal);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::get_NumberOfLogRecords


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::AbortTransaction()

Summary: Aborts the transaction

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmMonComp::AbortTransaction()
{
	long lNumClerks = (long) m_vecClerks.size();

	if (0 == lNumClerks)
	{
		ATLTRACE(_T("ERROR: no clerks\r\n"));

		return E_FAIL;
	}

	HRESULT hr = S_OK;

	// transaction will be same for all clerks - get 1st clerk

	CLERK_ENTRY * pce = m_vecClerks.front();

	_ASSERTE(pce);

	ICrmMonitorLogRecords * pICrmMonitorLogRecords = pce->m_pICrmMonitorLogRecords;

	_ASSERTE(pICrmMonitorLogRecords);

	ICrmLogControl * pICrmLogControl = NULL;

	hr = pICrmMonitorLogRecords->QueryInterface(
										__uuidof(ICrmLogControl),
										(void **)&pICrmLogControl);

	_ASSERTE(S_OK == hr);
	_ASSERTE(pICrmLogControl);

	hr = pICrmLogControl->ForceTransactionToAbort();

	if (hr != S_OK)
	{
		ATLTRACE(_T("ForceTransactionToAbort, hr = %08lX\r\n"), hr);
	}

	pICrmLogControl->Release();

	return S_OK;

} // CCrmMonComp::AbortTransaction


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::SetRecord(long lRecordNumber)

Summary: Set the record number

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::SetRecord(long lRecordNumber)
{
	m_lRecordNumber = lRecordNumber;

	return S_OK;

} // CCrmMonComp::SetRecord


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::CreateCompensator(void)

Summary: Creates a CRM compensator 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmMonComp::CreateCompensator(void)
{
	HRESULT hr = S_OK;

	// find the Prog Id

	_variant_t vProgId;

	hr = get_ProgId(&vProgId);

	if (hr != S_OK) return hr;

	// convert the Prog Id to a CLSID

	_bstr_t bstrProgId = vProgId;

	CLSID clsidCompensator;

	hr = CLSIDFromProgID((LPCOLESTR)bstrProgId, &clsidCompensator);

	if (S_OK != hr)
	{
		// attempt to convert stringized CLSID 

		hr = CLSIDFromString((LPOLESTR)bstrProgId, &clsidCompensator);
	}

	if (hr != S_OK) return hr;

	// create the compensator - it should be there

	IUnknown * punkCompensator = NULL;

	hr = CoCreateInstance(
			clsidCompensator, 
			NULL, 
			CLSCTX_ALL, 
			__uuidof(IUnknown), 
			(void **)&punkCompensator);

	_ASSERTE(S_OK == hr);
	_ASSERTE(punkCompensator);

	// does the compensator support ICrmFormatLogRecords?

	hr = punkCompensator->QueryInterface(
				__uuidof(ICrmFormatLogRecords), 
				(void **)&m_pICrmFormatLogRecords);

	punkCompensator->Release();

	if (E_NOINTERFACE == hr)
	{
		m_pICrmFormatLogRecords = NULL;

		return S_OK;
	}

	_ASSERTE(S_OK == hr);
	_ASSERTE(m_pICrmFormatLogRecords);

	return S_OK;

} // CCrmMonComp::CreateCompensator


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_ColumnHeaders(VARIANT * pVal)

Summary: Gets the header format info if available. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::get_ColumnHeaders(VARIANT * pVal)
{
	_ASSERTE(pVal);

	HRESULT hr = S_OK;

	hr = CreateCompensator();

	if (hr != S_OK) return hr;

	// assume compensator cannot provide format info

	_variant_t vHeaders = L"<no column headers available>";

	if (m_pICrmFormatLogRecords)
	{
		// compensator can provide format info

		hr = m_pICrmFormatLogRecords->GetColumnHeaders(&vHeaders);

		_ASSERTE(S_OK == hr);

		m_pICrmFormatLogRecords->Release();

		m_pICrmFormatLogRecords = NULL;
	}

	hr = VariantCopy(pVal, &vHeaders);

	_ASSERTE(S_OK == hr);

	return S_OK;

} // CCrmMonComp::get_ColumnHeaders


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmMonComp::get_FormattedRecord(VARIANT * pVal)

Summary: Gets a formatted record

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmMonComp::get_FormattedRecord(VARIANT * pVal)
{
	_ASSERTE(pVal);

	HRESULT hr = S_OK;

	hr = CreateCompensator();

	if (hr != S_OK) return hr;

	// assume compensator cannot provide record format info

	_variant_t vRecords = L"<no record details available>";

	if (!m_pICrmFormatLogRecords)
	{
		// compensator cannot provide record format info

		hr = VariantCopy(pVal, &vRecords);

		_ASSERTE(S_OK == hr);

		return S_OK;
	}

	// get the required record

	CLERK_ENTRY * pce = m_vecClerks[m_lClerkNumber];

	_ASSERTE(pce);
	_ASSERTE(pce->m_pICrmMonitorLogRecords);

	// is the record requested available?

	long lCount = 0;

	hr = get_NumberOfLogRecords(&lCount);

	if (hr != S_OK) return hr;

	if (m_lRecordNumber >= lCount)
	{
		ATLTRACE(_T("ERROR: no such log record\r\n"));

		return E_FAIL;
	}

	// do we have structured or unstructured records?

	VARIANT_BOOL vbStructuredRecs = VARIANT_FALSE;

	hr = pce->m_pICrmMonitorLogRecords->get_StructuredRecords(&vbStructuredRecs);

	_ASSERTE(S_OK == hr);

	BOOL fStructured = (VARIANT_TRUE == vbStructuredRecs);

	if (fStructured)
	{
		// get the record

		_variant_t vIndexNumber = (_variant_t)m_lRecordNumber;

		_variant_t vLogRecord;

		hr = pce->m_pICrmMonitorLogRecords->GetLogRecordVariants(
												vIndexNumber,
												&vLogRecord);
		_ASSERTE(S_OK == hr);

		// format the record

		hr = m_pICrmFormatLogRecords->GetColumnVariants(vLogRecord, &vRecords);

		_ASSERTE(S_OK == hr);
	}

	else
	{
		// is unstructured record here

		// get the record

		CrmLogRecordRead CrmLogRec;

		hr = pce->m_pICrmMonitorLogRecords->GetLogRecord(
												(DWORD)m_lRecordNumber,
												&CrmLogRec);
		_ASSERTE(S_OK == hr);

		// format the record

		hr = m_pICrmFormatLogRecords->GetColumn(CrmLogRec, &vRecords);

		_ASSERTE(S_OK == hr);
	}

	m_pICrmFormatLogRecords->Release();

	m_pICrmFormatLogRecords = NULL;

	hr = VariantCopy(pVal, &vRecords);

	_ASSERTE(S_OK == hr);

	return S_OK;
	
} // CCrmMonComp::get_FormattedRecord

