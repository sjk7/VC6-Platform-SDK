/*+==========================================================================

File: CrmDebugCompensator.h



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

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CCrmDebugCompensator

	This is the CRM Compensator. After the transaction is completed this
	object is created and given the log from the transaction. It can then 
	commit or abort the transaction. This compensator prints trace
	messages. 

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
	
// CrmDebugCompensator.h : Declaration of the CCrmDebugCompensator

#ifndef __CRMDEBUGCOMPENSATOR_H_
#define __CRMDEBUGCOMPENSATOR_H_

#include "resource.h"       // main symbols

#include "comsvcs.h"

/////////////////////////////////////////////////////////////////////////////
// CCrmDebugCompensator
class ATL_NO_VTABLE CCrmDebugCompensator : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCrmDebugCompensator, &CLSID_CrmDebugCompensator>,
	public ICrmDebugCompensator,
   	public ICrmCompensator,
   	public ICrmCompensatorVariants
{
public:
	CCrmDebugCompensator()
	{
		m_pUnkMarshaler = NULL;
	}

	/***** /

	// for debugging refcount problems

	ULONG InternalAddRef();

	ULONG InternalRelease();

	/ *****/

DECLARE_REGISTRY_RESOURCEID(IDR_CRMDEBUGCOMPENSATOR)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCrmDebugCompensator)
	COM_INTERFACE_ENTRY(ICrmDebugCompensator)
	COM_INTERFACE_ENTRY(ICrmCompensator)
	COM_INTERFACE_ENTRY(ICrmCompensatorVariants)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
END_COM_MAP()

	HRESULT FinalConstruct();

	void FinalRelease();

	CComPtr<IUnknown> m_pUnkMarshaler;


// ICrmCompensator
	
    HRESULT STDMETHODCALLTYPE SetLogControl( 
        /* [in] */ ICrmLogControl __RPC_FAR *pLogControl);
    
    HRESULT STDMETHODCALLTYPE BeginPrepare(void);
    
    HRESULT STDMETHODCALLTYPE PrepareRecord( 
        /* [in] */ CrmLogRecordRead crmLogRec,
        /* [retval][out] */ BOOL __RPC_FAR *pfForget);
    
    HRESULT STDMETHODCALLTYPE EndPrepare( 
        /* [retval][out] */ BOOL __RPC_FAR *pfOkToPrepare);
    
    HRESULT STDMETHODCALLTYPE BeginCommit( 
        /* [in] */ BOOL fRecovery);
    
    HRESULT STDMETHODCALLTYPE CommitRecord( 
        /* [in] */ CrmLogRecordRead crmLogRec,
        /* [retval][out] */ BOOL __RPC_FAR *pfForget);
    
    HRESULT STDMETHODCALLTYPE EndCommit(void);
    
    HRESULT STDMETHODCALLTYPE BeginAbort( 
        /* [in] */ BOOL fRecovery);
    
    HRESULT STDMETHODCALLTYPE AbortRecord( 
        /* [in] */ CrmLogRecordRead crmLogRec,
        /* [retval][out] */ BOOL __RPC_FAR *pfForget);
    
    HRESULT STDMETHODCALLTYPE EndAbort(void);
      
// ICrmCompensatorVariants

    HRESULT STDMETHODCALLTYPE SetLogControlVariants( 
        /* [in] */ ICrmLogControl __RPC_FAR *pLogControl);
    
    HRESULT STDMETHODCALLTYPE BeginPrepareVariants(void);
    
    HRESULT STDMETHODCALLTYPE PrepareRecordVariants( 
        /* [in] */ VARIANT __RPC_FAR *pLogRecord,
        /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbForget);
    
    HRESULT STDMETHODCALLTYPE EndPrepareVariants( 
        /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOkToPrepare);
    
    HRESULT STDMETHODCALLTYPE BeginCommitVariants( 
        /* [in] */ VARIANT_BOOL bRecovery);
    
    HRESULT STDMETHODCALLTYPE CommitRecordVariants( 
        /* [in] */ VARIANT __RPC_FAR *pLogRecord,
        /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbForget);
    
    HRESULT STDMETHODCALLTYPE EndCommitVariants(void);
    
    HRESULT STDMETHODCALLTYPE BeginAbortVariants( 
        /* [in] */ VARIANT_BOOL bRecovery);
    
    HRESULT STDMETHODCALLTYPE AbortRecordVariants( 
        /* [in] */ VARIANT __RPC_FAR *pLogRecord,
        /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbForget);
    
    HRESULT STDMETHODCALLTYPE EndAbortVariants(void);

// ICrmDebugCompensator
public:
};

#endif //__CRMDEBUGCOMPENSATOR_H_
