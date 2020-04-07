/*+==========================================================================

File: CrmFilesWorker.h



Summary: 

	This is a sample Compensating Resource Manager (CRM) that creates and deletes files.

	The CRM Worker provides an interface for creating or deleting files.

	The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications.

	The CRM Compensator also implements ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library application. 

	The CRM Worker requires a transaction. The CRM Compensator should not have a transaction.

	This file is part of the Microsoft COM Technology Samples.

Classes: CCrmFilesWorker


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


#ifndef __CRMFILESWORKER_H_
#define __CRMFILESWORKER_H_

#include "resource.h"       // main symbols

#include <comsvcs.h>


/////////////////////////////////////////////////////////////////////////////


typedef enum { ct_DeleteFile, ct_CreateFile } CrmFilesCommandType;

// fully pack all log record structures

#pragma pack(1)

typedef struct tagCrmFilesCreateFileLogRecord
{
    CrmFilesCommandType         CommandType;

    // NOTE: size is # WCHARs
         
    DWORD                       dwSourceSize;
  
    // source file name goes here

} CrmFilesCreateFileLogRecord;


typedef struct tagCrmFilesDeleteFileLogRecord
{
    CrmFilesCommandType         CommandType;
       
    // NOTE: size is # WCHARs

    DWORD                       dwSourceSize;

    DWORD                       dwTempSize;

    // source file name goes here

    // temp file name goes here

} CrmFilesDeleteFileLogRecord;

#pragma pack()  // back to default

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CCrmFilesWorker

	This is the CRM Worker. All work done on the resource during the transaction
	is done through this object. In this program, the resource is the file
	system, specifically the actions of creating or deleting files. 

C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

// CCrmFilesWorker
class ATL_NO_VTABLE CCrmFilesWorker : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CCrmFilesWorker, &CLSID_CrmFilesWorker>,
	public IObjectControl,
   	public IDispatchImpl<ICrmFilesWorker, &IID_ICrmFilesWorker, &LIBID_CRMFILESLib>
{
public:

    // constructor
	CCrmFilesWorker();

    // destructor
	~CCrmFilesWorker();
    
	/***** /
	ULONG InternalAddRef();

	ULONG InternalRelease();
	/ *****/

DECLARE_REGISTRY_RESOURCEID(IDR_CRMFILESWORKER)

BEGIN_COM_MAP(CCrmFilesWorker)
	COM_INTERFACE_ENTRY(ICrmFilesWorker)
	COM_INTERFACE_ENTRY(IObjectControl)
    COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ICrmFilesWorker
public:
	STDMETHOD(DeleteFile)(/*[in]*/ BSTR bstrFileName);
	STDMETHOD(CreateFile)(/*[in]*/ BSTR bstrFileName);

// IObjectControl
public:

    HRESULT STDMETHODCALLTYPE Activate(void);
    
    void STDMETHODCALLTYPE Deactivate(void);
    
    BOOL STDMETHODCALLTYPE CanBePooled(void);

private:

    HRESULT GetCrmLogControl(void);

private:

    ICrmLogControl              *m_pICrmLogControl;

	int							m_id;

};

#endif //__CRMFILESWORKER_H_
