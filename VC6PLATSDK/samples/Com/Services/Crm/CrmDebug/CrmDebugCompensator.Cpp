/*+==========================================================================

File: CrmDebugCompensator.cpp



Summary: 
	
	This is a sample CRM Compensator for the Compensating Resource Manager (CRM).

	It can be used as a substitute for your own CRM Compensator while developing your CRM.

	It simply outputs debug messages for all CRM Compensator notifications.

	It implements both ICrmCompensator and ICrmCompensatorVariants.

	This file is part of the Microsoft COM Technology Samples.


Classes: 

	CCrmDebugCompensator


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

// CrmDebugCompensator.cpp : Implementation of CCrmDebugCompensator

#include "stdafx.h"
#include "CrmDebug.h"
#include "CrmDebugCompensator.h"


/////////////////////////////////////////////////////////////////////////////
// CCrmDebugCompensator




/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::InternalAddRef()

Summary: Internal AddRef, uncomment if you want to see InternalAddRef Trace
		 messages.

Returns: ULONG


M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


/***** /
ULONG CCrmDebugCompensator::InternalAddRef()
{
	DWORD dwBefore = m_dwRef;
	
	DWORD dwAfter = CComObjectRootEx<CComMultiThreadModel>::InternalAddRef();

	ATLTRACE(_T("CCrmDebugCompensator::InternalAddRef, b = %d, a = %d\r\n"), dwBefore, dwAfter);

	return (ULONG)dwAfter;

} // CCrmDebugCompensator::InternalAddRef


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::InternalRelease()

Summary: Internal Release, uncomment if you want to see InternalRelease Trace
		 messages.

Returns: ULONG

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


/***** /
ULONG CCrmDebugCompensator::InternalRelease()
{
	DWORD dwBefore = m_dwRef;
	
	DWORD dwAfter = CComObjectRootEx<CComMultiThreadModel>::InternalRelease();

	ATLTRACE(_T("CCrmDebugCompensator::InternalRelease, b = %d, a = %d\r\n"), dwBefore, dwAfter);

	return (ULONG)dwAfter;

} // CCrmDebugCompensator::InternalRelease


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::FinalConstruct()

Summary: Final construct

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmDebugCompensator::FinalConstruct()
{
	ATLTRACE(_T("CCrmDebugCompensator::FinalConstruct\n"));

	return CoCreateFreeThreadedMarshaler(
		GetControllingUnknown(), &m_pUnkMarshaler.p);

} // CCrmDebugCompensator::FinalConstruct


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::FinalRelease()

Summary: Final release

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


void CCrmDebugCompensator::FinalRelease()
{
	ATLTRACE(_T("CCrmDebugCompensator::FinalRelease\n"));

	m_pUnkMarshaler.Release();

} // CCrmDebugCompensator::FinalRelease

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::SetLogControl()

Summary: Display Trace message.

		 Delivers an ICrmLogControl Interface to the CRM Compensator so that
		 it can write further log records during transaction completion.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

// ICrmCompensator
	
HRESULT CCrmDebugCompensator::SetLogControl( 
    /* [in] */ ICrmLogControl __RPC_FAR *pLogControl)
{
	ATLTRACE(_T("CCrmDebugCompensator::SetLogControl\n"));

	_ASSERTE(pLogControl);

	return S_OK;

} // CCrmDebugCompensator::SetLogControl


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::BeginPrepare()

Summary: Display Trace message.

		 Notifies the CRM Compensator of the prepare phase of the transaction
		 completion and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::BeginPrepare(void)
{
	ATLTRACE(_T("CCrmDebugCompensator::BeginPrepare\n"));

	return S_OK;

} // CCrmDebugCompensator::BeginPrepare

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::PrepareRecord()

Summary: Display Trace message. 

		 Delivers a log record in forward order during the prepare phase. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::PrepareRecord( 
    /* [in] */ CrmLogRecordRead crmLogRec,
    /* [retval][out] */ BOOL __RPC_FAR *pfForget)
{
	ATLTRACE(_T("CCrmDebugCompensator::PrepareRecord\n"));

	_ASSERTE(pfForget);

	return S_OK;

} // CCrmDebugCompensator::PrepareRecord

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::EndPrepare()

Summary: Display Trace message. 

		 Notifies the CRM Compensator that it has had all the log records 
		 available during the prepare phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::EndPrepare( 
    /* [retval][out] */ BOOL __RPC_FAR *pfOkToPrepare)
{
	ATLTRACE(_T("CCrmDebugCompensator::EndPrepare\n"));

	_ASSERTE(pfOkToPrepare);

	*pfOkToPrepare = TRUE;

	return S_OK;

} // CCrmDebugCompensator::EndPrepare

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::BeginCommit()

Summary: Display Trace message. 

		 Notifies the CRM Compensator of the commit phase of the transaction 
		 completion and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::BeginCommit( 
    /* [in] */ BOOL fRecovery)
{
	ATLTRACE(_T("CCrmDebugCompensator::BeginCommit\n"));

	return S_OK;

} // CCrmDebugCompensator::BeginCommit

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::CommitRecord()

Summary: Display Trace message. 

		 Delivers a log record in forward order during the commit phase. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::CommitRecord( 
    /* [in] */ CrmLogRecordRead crmLogRec,
    /* [retval][out] */ BOOL __RPC_FAR *pfForget)
{
	ATLTRACE(_T("CCrmDebugCompensator::CommitRecord\n"));

	_ASSERTE(pfForget);

	return S_OK;

} // CCrmDebugCompensator::CommitRecord

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::EndCommit()

Summary: Display Trace message.

		 Notifies the CRM Compensator that it has delivered all the log
		 records available during the commit phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::EndCommit(void)
{
	ATLTRACE(_T("CCrmDebugCompensator::EndCommit\n"));

	return S_OK;

} // CCrmDebugCompensator::EndCommit

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::BeginAbort()

Summary: Display Trace message.

		 Notifies the CRM Compensator of the abort phase of the transaction
		 completion, and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::BeginAbort( 
    /* [in] */ BOOL fRecovery)
{
	ATLTRACE(_T("CCrmDebugCompensator::BeginAbort\n"));

	return S_OK;

} // CCrmDebugCompensator::BeginAbort


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::AbortRecord()

Summary: Display Trace message. 

		 Delivers a log record to the CRM Compensator during the abort phase. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::AbortRecord( 
    /* [in] */ CrmLogRecordRead crmLogRec,
    /* [retval][out] */ BOOL __RPC_FAR *pfForget)
{
	ATLTRACE(_T("CCrmDebugCompensator::AbortRecord\n"));

	_ASSERTE(pfForget);

	return S_OK;

} // CCrmDebugCompensator::AbortRecord

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::EndAbort()

Summary: Display Trace message. 

		 Notifies the CRM Compensator that it has received all the log 
		 records available during the abort phase.  

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::EndAbort(void)
{
	ATLTRACE(_T("CCrmDebugCompensator::EndAbort\n"));

	return S_OK;

} // CCrmDebugCompensator::EndAbort

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::SetLogControlVariants()

Summary: Display Trace message.

		 Delivers an ICrmLogControl interface to the CRM Compensator.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


      
// ICrmCompensatorVariants

HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::SetLogControlVariants( 
    /* [in] */ ICrmLogControl __RPC_FAR *pLogControl)
{
	ATLTRACE(_T("CCrmDebugCompensator::SetLogControlVariants\n"));

	_ASSERTE(pLogControl);

	return S_OK;

} // CCrmDebugCompensator::SetLogControlVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::BeginPrepareVariants()

Summary: Display Trace message. 

		 Notifies the CRM Compensator of the prepare phase of the transaction
		 completion and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::BeginPrepareVariants(void)
{
	ATLTRACE(_T("CCrmDebugCompensator::BeginPrepareVariants\n"));

	return S_OK;

} // CCrmDebugCompensator::BeginPrepareVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::PrepareRecordVariants()

Summary: Display Trace message. 

		 Delivers a log record to the CRM Compensator during the prepare phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::PrepareRecordVariants( 
    /* [in] */ VARIANT __RPC_FAR *pLogRecord,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbForget)
{
	ATLTRACE(_T("CCrmDebugCompensator::PrepareRecordVariants\n"));

	_ASSERTE(pbForget);

	return S_OK;

} // CCrmDebugCompensator::PrepareRecordVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::EndPrepareVariants()

Summary: Display Trace message. 

		 Notifies the CRM Compensator that it has had all the log records
		 available during the prepare phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::EndPrepareVariants( 
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOkToPrepare)
{
	ATLTRACE(_T("CCrmDebugCompensator::EndPrepareVariants\n"));

	_ASSERTE(pbOkToPrepare);

	*pbOkToPrepare = VARIANT_TRUE;

	return S_OK;

} // CCrmDebugCompensator::EndPrepareVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::BeginCommitVariants()

Summary: Display Trace message. 

		 Notifies the CRM Compensator of the commit phase (phase 2) of the 
		 transaction completion, and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::BeginCommitVariants( 
    /* [in] */ VARIANT_BOOL bRecovery)
{
	ATLTRACE(_T("CCrmDebugCompensator::BeginCommitVariants\n"));

	return S_OK;

} // CCrmDebugCompensator::BeginCommitVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::CommitRecordVariants()

Summary: Display Trace message. 

		 Delivers a log record to the CRM Compensator during the commit phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::CommitRecordVariants( 
    /* [in] */ VARIANT __RPC_FAR *pLogRecord,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbForget)
{
	ATLTRACE(_T("CCrmDebugCompensator::CommitRecordVariants\n"));

	_ASSERTE(pbForget);

	return S_OK;

} // CCrmDebugCompensator::CommitRecordVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::EndCommitVariants()

Summary: Display Trace message. 

		 Notifies the CRM Compensator that it has delivered all the log
		 records available during the commit phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::EndCommitVariants(void)
{
	ATLTRACE(_T("CCrmDebugCompensator::EndCommitVariants\n"));

	return S_OK;

} // CCrmDebugCompensator::EndCommitVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::BeginAbortVariants()

Summary: Display Trace message. 

		 Notifies the CRM Compensator of the abort phase of the transaction
		 completion, and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::BeginAbortVariants( 
    /* [in] */ VARIANT_BOOL bRecovery)
{
	ATLTRACE(_T("CCrmDebugCompensator::BeginAbortVariants\n"));

	return S_OK;

} // CCrmDebugCompensator::BeginAbortVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::AbortRecordVariants()

Summary: Display Trace message. 

		 Delivers a log record to the CRM Compensator during the abort phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::AbortRecordVariants( 
    /* [in] */ VARIANT __RPC_FAR *pLogRecord,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbForget)
{
	ATLTRACE(_T("CCrmDebugCompensator::AbortRecordVariants\n"));

	_ASSERTE(pbForget);

	return S_OK;

} // CCrmDebugCompensator::AbortRecordVariants

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmDebugCompensator::EndAbortVariants()

Summary: Display Trace message. 

		 Notifies the CRM Compensator that it has received all the log 
		 records available during the abort phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



HRESULT STDMETHODCALLTYPE CCrmDebugCompensator::EndAbortVariants(void)
{
	ATLTRACE(_T("CCrmDebugCompensator::EndAbortVariants\n"));

	return S_OK;

} // CCrmDebugCompensator::EndAbortVariants

