/*+==========================================================================

File: CrmFilesCompensator.h


Summary: 

	This is a sample Compensating Resource Manager (CRM) that creates and deletes files.

	The CRM Worker provides an interface for creating or deleting files.

	The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications.

	The CRM Compensator also implements ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library application. 

	The CRM Worker requires a transaction. The CRM Compensator should not have a transaction.


Classes:

	CCrmFilesCompensator

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

#ifndef __CRMFILESCOMPENSATOR_H_
#define __CRMFILESCOMPENSATOR_H_

#include "resource.h"			// main symbols

#include <comsvcs.h>			// CRM interfaces

#include "comdef.h"				// for _variant_t etc.

#include "CrmFilesWorker.h"		// for CrmFilesCommandType


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CCrmFilesCompensator

	This is the CRM Compensator. After the transaction is completed this
	object is created and given the log from the transaction. It can then 
	commit or abort the transaction. 

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/////////////////////////////////////////////////////////////////////////////
// CCrmFilesCompensator
class ATL_NO_VTABLE CCrmFilesCompensator : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCrmFilesCompensator, &CLSID_CrmFilesCompensator>,
   	public IDispatchImpl<ICrmFilesCompensator, &IID_ICrmFilesCompensator, &LIBID_CRMFILESLib>,
   	public ICrmCompensator,
	public ICrmFormatLogRecords
{
public:
	CCrmFilesCompensator() :
     m_pICrmLogControl(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CRMFILESCOMPENSATOR)
DECLARE_NOT_AGGREGATABLE(CCrmFilesCompensator)

BEGIN_COM_MAP(CCrmFilesCompensator)
	COM_INTERFACE_ENTRY(ICrmFilesCompensator)
   	COM_INTERFACE_ENTRY(ICrmCompensator)
   	COM_INTERFACE_ENTRY(ICrmFormatLogRecords)
    COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ICrmFilesCompensator
public:

// ICrmCompensator
public:

    HRESULT STDMETHODCALLTYPE SetLogControl( 
        /* [in] */ ICrmLogControl __RPC_FAR *pLogControl);
    
    HRESULT STDMETHODCALLTYPE BeginPrepare( void);
    
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
    
    HRESULT STDMETHODCALLTYPE EndCommit( void);
    
    HRESULT STDMETHODCALLTYPE BeginAbort( 
        /* [in] */ BOOL fRecovery);
    
    HRESULT STDMETHODCALLTYPE AbortRecord( 
        /* [in] */ CrmLogRecordRead crmLogRec,
        /* [retval][out] */ BOOL __RPC_FAR *pfForget);
    
    HRESULT STDMETHODCALLTYPE EndAbort( void);

// NOTE: This is an optional interface that the compensator can implement to help with
// monitoring the log records

// ICrmFormatLogRecords
public:

    HRESULT STDMETHODCALLTYPE GetColumnCount( 
        /* [out] */ long __RPC_FAR *plColumnCount);
    
    HRESULT STDMETHODCALLTYPE GetColumnHeaders( 
        /* [out] */ LPVARIANT pHeaders);
    
    HRESULT STDMETHODCALLTYPE GetColumn( 
        /* [in] */ CrmLogRecordRead CrmLogRec,
        /* [out] */ LPVARIANT pFormattedLogRecord);
    
    HRESULT STDMETHODCALLTYPE GetColumnVariants( 
        /* [in] */ VARIANT LogRecord,
        /* [out] */ LPVARIANT pFormattedLogRecord);
    
private:

    // process the raw log record into a form that is meaningful for this CRM Compensator

    HRESULT ProcessLogRecord(CrmLogRecordRead crmLogRec);

	void MakeVariantArray
	(
		int				i_iNumVariants, 
		_variant_t		*i_vArray, 
		LPVARIANT		i_pVarSafeArray
	);

private:

    ICrmLogControl              *m_pICrmLogControl;

    CrmFilesCommandType         m_CommandType;

    WCHAR                       m_wszSourceFileName[MAX_PATH];

    WCHAR                       m_wszTempFileName[MAX_PATH];

};

#endif //__CRMFILESCOMPENSATOR_H_
