/*+==========================================================================

File: CrmFilesWorker.cpp



Summary: 

	This is a sample Compensating Resource Manager (CRM) that creates and deletes files.

	The CRM Worker provides an interface for creating or deleting files.

	The CRM Compensator implements ICrmCompensator to receive transaction outcome notifications.

	The CRM Compensator also implements ICrmFormatLogRecords to support monitoring.

	This CRM can be installed in a server application or in a library application. 

	The CRM Worker requires a transaction. The CRM Compensator should not have a transaction.

Classes:


	CCrmFilesWorker


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


#include "stdafx.h"
#include "CrmFiles.h"
#include "CrmFilesWorker.h"

#include <time.h>

#pragma warning(disable: 4189)	// local variable is initialized but not referenced


/////////////////////////////////////////////////////////////////////////////
// CCrmFilesWorker

// IObjectControl Methods

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::Activate()

Summary: IObjectControl Method. Allows an object to perform context-specific
		 initialization whenever it's activated. This method is called by 
		 COM+ before any other methods are called on the object.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmFilesWorker::Activate(void)
{
	ATLTRACE(_T("CCrmFilesWorker::Activate = %08lX, %d\r\n"), this, m_id);

	m_pICrmLogControl = NULL;

	return S_OK;

} // CCrmFilesWorker::Activate


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::Deactivate()

Summary: IObjectControl Method. Allows an object to perform whatever cleanup
		 is necessary before it's recycled or destroyed. This method is
		 called by COM+ whenever an object is deactivated.

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


void STDMETHODCALLTYPE CCrmFilesWorker::Deactivate(void)
{
	ATLTRACE(_T("CCrmFilesWorker::Deactivate = %08lX, %d\r\n"), this, m_id);

    if (m_pICrmLogControl) 
    {
        m_pICrmLogControl->Release();
    }

    m_pICrmLogControl = NULL;

} // CCrmFilesWorker::Deactivate

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::CanBePooled()

Summary: IObjectControl Method. Allows an object to notify COM+ of whether it
		 can be pooled for reuse.

Returns: BOOL

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


BOOL STDMETHODCALLTYPE CCrmFilesWorker::CanBePooled(void)
{
	ATLTRACE(_T("CCrmFilesWorker::CanBePooled = %08lX, %d\r\n"), this, m_id);

	return TRUE;

} // CCrmFilesWorker::CanBePooled



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::InternalAddRef()

Summary: Internal AddRef, uncomment if you want to see InternalAddRef Trace
		 messages.

Returns: ULONG


M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

/***** /
ULONG CCrmFilesWorker::InternalAddRef()
{
	DWORD dwBefore = m_dwRef;
	
	DWORD dwAfter = CComObjectRootEx<CComMultiThreadModel>::InternalAddRef();

	ATLTRACE(_T("CCrmFilesWorker::InternalAddRef, b = %d, a = %d\r\n"), dwBefore, dwAfter);

	return (ULONG)dwAfter;

} // CCrmFilesWorker::InternalAddRef


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::InternalRelease()

Summary: Internal Release, uncomment if you want to see InternalRelease Trace
		 messages.

Returns: ULONG

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

/***** /
ULONG CCrmFilesWorker::InternalRelease()
{
	DWORD dwBefore = m_dwRef;
	
	DWORD dwAfter = CComObjectRootEx<CComMultiThreadModel>::InternalRelease();

	ATLTRACE(_T("CCrmFilesWorker::InternalRelease, b = %d, a = %d\r\n"), dwBefore, dwAfter);

	return (ULONG)dwAfter;

} // CCrmFilesWorker::InternalRelease
/ *****/


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::CCrmFilesWorker()

Summary: Constructor

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

CCrmFilesWorker::CCrmFilesWorker() :
 m_pICrmLogControl(NULL)
{
	srand((unsigned)time(NULL));

	m_id = rand();

	ATLTRACE(_T("CCrmFilesWorker constructor = %08lX, %d\r\n"), this, m_id);

} // CCrmFilesWorker constructor


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::~CCrmFilesWorker()

Summary: Destructor

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


CCrmFilesWorker::~CCrmFilesWorker()
{
	ATLTRACE(_T("CCrmFilesWorker destructor = %08lX, %d\r\n"), this, m_id);

    if (m_pICrmLogControl) 
    {
        m_pICrmLogControl->Release();
    }

    m_pICrmLogControl = NULL;

} // CCrmFilesWorker destructor


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::GetCrmLogControl()

Summary: This creates the CRM Clerk and calls RegisterCompensator on it.

Returns: HRESULT 

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesWorker::GetCrmLogControl(void)
{
    HRESULT hr = S_OK;
    
    _ASSERTE(NULL == m_pICrmLogControl);

	hr = CoCreateInstance(
				__uuidof(CRMClerk), 
				NULL, 
				CLSCTX_INPROC_SERVER, 
				__uuidof(ICrmLogControl), 
				(void **)&m_pICrmLogControl);

	_ASSERTE(S_OK == hr);
	_ASSERTE(m_pICrmLogControl);

	// try to register our CRM Compensator (try 5X if recovery is in progress)

    for (int i = 0; i < 5; i++)
    {
        hr = m_pICrmLogControl->RegisterCompensator(
                                    L"CrmFilesCompensator.CrmFilesCompensator.1",
                                    L"description goes here",
									CRMREGFLAG_ALLPHASES);

        if (XACT_E_RECOVERYINPROGRESS == hr)
        {
            Sleep(1000);

            continue;       // try again
        }

        break;
    }

    _ASSERTE(hr == S_OK);

    return hr;

} // CCrmFilesWorker::GetCrmLogControl



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::CreateFile(BSTR bstrFileName)

Summary: Record that we are creating a file to the log, then create the file. 

Returns: HRESULT 

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmFilesWorker::CreateFile(BSTR bstrFileName)
{
    HRESULT hr = S_OK;

	if (NULL == m_pICrmLogControl)
    {
        hr = GetCrmLogControl();

        _ASSERTE(S_OK == hr);

        if (hr != S_OK)
        {
            return hr;
        }
    }

    _ASSERTE(m_pICrmLogControl);

    // does the file already exist?

    // We must do this because if the file already exists we will fail to create it. The transaction
    // will then abort, and as part of the abort we delete the file that we think we created -
    // so in this case we might end up deleting a file that we did not create.
    
	HANDLE hFile = ::CreateFileW( 
                        bstrFileName,	            // pointer to name of the file 
				        GENERIC_WRITE,	            // access (read-write) mode 
				        0L,	                        // share mode 
				        NULL,	                    // pointer to security descriptor 
				        OPEN_EXISTING,              // how to create 
				        FILE_ATTRIBUTE_NORMAL,	    // file attributes 
				        NULL); 	                    // handle to file with attributes to copy  

	if (INVALID_HANDLE_VALUE != hFile)
	{
        // file already exists

        CloseHandle(hFile);

    	hr = m_pICrmLogControl->ForceTransactionToAbort();
        
        return hr;
	}	

    // WRITE AHEAD - log that we are about to create the file

    CrmFilesCreateFileLogRecord cfr;

    cfr.CommandType = ct_CreateFile;

	_ASSERTE(bstrFileName != NULL);

	cfr.dwSourceSize = (DWORD) wcslen(bstrFileName);

    BLOB blobs[2];

    blobs[0].pBlobData = (BYTE *)&cfr;
    
    blobs[0].cbSize = sizeof(cfr);
    
    // avoid copying the file name

    blobs[1].pBlobData = (BYTE *)bstrFileName;

    // wcslen returns # of chars in string, we need # of bytes
	_ASSERTE(bstrFileName != NULL);

    UINT uNumChars = (UINT) wcslen(bstrFileName);

    blobs[1].cbSize = uNumChars * sizeof(WCHAR);

    // write the "create file" log record

    hr = m_pICrmLogControl->WriteLogRecord(
                                blobs,
                                2);
    _ASSERTE(S_OK == hr);

    // force the log to ensure this log record is durable in the log
     
    hr = m_pICrmLogControl->ForceLog();

    _ASSERTE(S_OK == hr);

    // TRY TO CREATE THE FILE

	hFile = ::CreateFileW( 
                    bstrFileName,				// pointer to name of the file 
				    GENERIC_WRITE,	            // access (read-write) mode 
				    0L,	                        // share mode 
				    NULL,	                    // pointer to security descriptor 
				    CREATE_NEW,	                // how to create 
				    FILE_ATTRIBUTE_NORMAL,	    // file attributes 
				    NULL); 	                    // handle to file with attributes to copy  

	if (INVALID_HANDLE_VALUE == hFile)
	{
        DWORD dwErr = GetLastError();

    	hr = m_pICrmLogControl->ForceTransactionToAbort();
        
        return hr;
	}

	CloseHandle(hFile);

	return S_OK;

} // CCrmFilesWorker::CreateFile


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesWorker::DeleteFile(BSTR bstrFileName)

Summary: Record that we are deleting a file to the log, then rename the file. 
		 The compensator will actually delete the file if the Transaction
		 commits. 

Returns: HRESULT 

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmFilesWorker::DeleteFile(BSTR bstrFileName)
{
    HRESULT hr = S_OK;

	if (NULL == m_pICrmLogControl)
    {
        hr = GetCrmLogControl();

        _ASSERTE(S_OK == hr);

    }

    _ASSERTE(m_pICrmLogControl);

    // does the file exist?

    // We must do this because MoveFileEx has the unfortunate effect that it will create the 
    // destination file even if the source file does not exist. If we allowed this to occur,
    // then during compensation we might put back a file that never originally existed.
    
	HANDLE hFile = ::CreateFileW( 
                        bstrFileName,				// pointer to name of the file 
				        GENERIC_WRITE,	            // access (read-write) mode 
				        0L,	                        // share mode 
				        NULL,	                    // pointer to security descriptor 
				        OPEN_EXISTING,              // how to create 
				        FILE_ATTRIBUTE_NORMAL,	    // file attributes 
				        NULL); 	                    // handle to file with attributes to copy  

	if (INVALID_HANDLE_VALUE == hFile)
	{
        DWORD dwErr = GetLastError();

    	hr = m_pICrmLogControl->ForceTransactionToAbort();
        
        return hr;
	}

	CloseHandle(hFile);
     
    // file exists - there is a window here in which it might be deleted by someone else

    WCHAR wszTempFile[MAX_PATH];

    ZeroMemory(wszTempFile, MAX_PATH * sizeof(WCHAR));

    // the file name itself will be unique, so use it

    lstrcatW(wszTempFile, bstrFileName); 

    lstrcatW(wszTempFile, L".crmtemp"); 

    // WRITE AHEAD - log that we are about to delete (rename) the file

    CrmFilesDeleteFileLogRecord dfr;

    dfr.CommandType = ct_DeleteFile;

	_ASSERTE(bstrFileName != NULL);
    dfr.dwSourceSize = (DWORD) wcslen(bstrFileName);

	_ASSERTE(wszTempFile != NULL);
    dfr.dwTempSize = (DWORD) wcslen(wszTempFile);

    BLOB blobs[3];

    blobs[0].pBlobData = (BYTE *)&dfr; 
    
    blobs[0].cbSize = sizeof(dfr);

    // avoid copying the source file name

    blobs[1].pBlobData = (BYTE *)bstrFileName;

    // wcslen returns # of chars in string, we need # of bytes

	_ASSERTE(bstrFileName != NULL);
    UINT uNumChars = (UINT) wcslen(bstrFileName);

    blobs[1].cbSize = uNumChars * sizeof(WCHAR); 

    // avoid copying the temp file name

    blobs[2].pBlobData = (BYTE *)wszTempFile;

	_ASSERTE(wszTempFile != NULL);
    uNumChars = (UINT) wcslen(wszTempFile);

    blobs[2].cbSize = uNumChars * sizeof(WCHAR); 

    // write the "delete file" log record

    hr = m_pICrmLogControl->WriteLogRecord(
                                blobs,
                                3);
    _ASSERTE(S_OK == hr);

    // force the log to ensure this log record is durable in the log
     
    hr = m_pICrmLogControl->ForceLog();

    _ASSERTE(S_OK == hr);

    // TRY TO RENAME THE FILE TO A CRM###.TMP FILE

    DWORD dwFlags = MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED | MOVEFILE_WRITE_THROUGH;
     
    BOOL fRc = MoveFileExW(
                    bstrFileName, 
					wszTempFile,
                    dwFlags);

    if (!fRc)
    {
        DWORD dwErr = GetLastError();

    	hr = m_pICrmLogControl->ForceTransactionToAbort();
        
        return hr;
    }

	return hr;

} // CCrmFilesWorker::DeleteFile


