/*+==========================================================================

File: CrmFilesCompensator.cpp

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
// CrmFilesCompensator.cpp : Implementation of CCrmFilesCompensator


#include "stdafx.h"
#include "CrmFiles.h"
#include "CrmFilesCompensator.h"


#pragma warning(disable: 4100)	// unreferenced formal parameter
#pragma warning(disable: 4189)	// local variable is initialized but not referenced


/////////////////////////////////////////////////////////////////////////////
// CCrmFilesCompensator

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::SetLogControl()

Summary: Delivers an ICrmLogControl Interface to the CRM Compensator so that
		 it can write further log records during transaction completion.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::SetLogControl( 
    /* [in] */ ICrmLogControl __RPC_FAR *pLogControl)
{
    m_pICrmLogControl = pLogControl;

    _ASSERTE(m_pICrmLogControl);

    return S_OK;

} // CCrmFilesCompensator::SetLogControl

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::BeginPrepare()

Summary: Notifies the CRM Compensator of the prepare phase of the transaction
		 completion and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::BeginPrepare( void)
{
    // do nothing

    return S_OK;

} // CCrmFilesCompensator::BeginPrepare


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::PrepareRecord()

Summary: Delivers a log record in forward order during the prepare phase. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::PrepareRecord( 
    /* [in] */ CrmLogRecordRead crmLogRec,
    /* [retval][out] */ BOOL __RPC_FAR *pfForget)
{
    _ASSERTE(pfForget);

    *pfForget = FALSE;

    // do nothing

    return S_OK;

} // CCrmFilesCompensator::PrepareRecord


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::EndPrepare()

Summary: Notifies the CRM Compensator that it has had all the log records 
		 available during the prepare phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::EndPrepare( 
    /* [retval][out] */ BOOL __RPC_FAR *pfOkToPrepare)
{
    // always vote yes

    _ASSERTE(pfOkToPrepare);

    *pfOkToPrepare = TRUE;

    return S_OK;

} // CCrmFilesCompensator::EndPrepare


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::BeginCommit()

Summary: Notifies the CRM Compensator of the commit phase of the transaction 
		 completion and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::BeginCommit( 
    /* [in] */ BOOL fRecovery)
{
    // do nothing

    return S_OK;

} // CCrmFilesCompensator::BeginCommit


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::CommitRecord()

Summary: Delivers a log record in forward order during the commit phase. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::CommitRecord( 
    /* [in] */ CrmLogRecordRead crmLogRec,
    /* [retval][out] */ BOOL __RPC_FAR *pfForget)
{
    _ASSERTE(pfForget);

    *pfForget = FALSE;

    HRESULT hr = S_OK;

    hr = ProcessLogRecord(crmLogRec);

    _ASSERTE(S_OK == hr);

    if (ct_DeleteFile == m_CommandType)
    {
        // clean up temp file

        BOOL fRc = DeleteFileW(m_wszTempFileName);

        // NOTE: we do not care whether this succeeds or not... worst case we leave temp files around
    }

    // no cleanup required for "create file"

    // OPTIONAL - forget this record

     *pfForget = TRUE;

    // NOTE: this forget is not forced - could force on next record if required

    return S_OK;

} // CCrmFilesCompensator::CommitRecord


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::EndCommit()

Summary: Notifies the CRM Compensator that it has delivered all the log
		 records available during the commit phase.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::EndCommit( void)
{
    // do nothing

    return S_OK;

} // CCrmFilesCompensator::EndCommit


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::BeginAbort()

Summary: Notifies the CRM Compensator of the abort phase of the transaction
		 completion, and that records are about to be delivered.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::BeginAbort( 
    /* [in] */ BOOL fRecovery)
{
    // do nothing

    return S_OK;

} // CCrmFilesCompensator::BeginAbort


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::AbortRecord()

Summary: Delivers a log record to the CRM Compensator during the abort phase. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::AbortRecord( 
    /* [in] */ CrmLogRecordRead crmLogRec,
    /* [retval][out] */ BOOL __RPC_FAR *pfForget)
{
    _ASSERTE(pfForget);

    *pfForget = FALSE;

    HRESULT hr = S_OK;

    hr = ProcessLogRecord(crmLogRec);

    _ASSERTE(S_OK == hr);

    if (ct_DeleteFile == m_CommandType)
    {
        // put back the original file

        // is it there already?
        
        WIN32_FIND_DATAW FindFileData;
        
        HANDLE hSearch = FindFirstFileW(
                                m_wszSourceFileName,
                                &FindFileData);

        bool fSourceFileExists = (INVALID_HANDLE_VALUE != hSearch);

        hSearch = FindFirstFileW(
                            m_wszTempFileName,
                            &FindFileData);

        bool fTempFileExists = (INVALID_HANDLE_VALUE != hSearch);

        if (!fSourceFileExists)
        {
            _ASSERTE(fTempFileExists);      // it had better exist, otherwise something is hosed

            // was not found, so move (rename) the temp file back
            
            DWORD dwFlags = MOVEFILE_WRITE_THROUGH;
     
            BOOL fRc = MoveFileExW(
                            m_wszTempFileName, 
					        m_wszSourceFileName,
                            dwFlags);

            _ASSERTE(fRc);

        }

        // clean up temp file

        BOOL fRc = DeleteFileW(m_wszTempFileName);

        // NOTE: we do not care whether this succeeds or not... worst case we leave temp files around

    }

    else
    {
        _ASSERTE(ct_CreateFile == m_CommandType);

        // delete the file we created

        // does it exist?

        WIN32_FIND_DATAW FindFileData;
        
        HANDLE hSearch = FindFirstFileW(
                                m_wszSourceFileName,
                                &FindFileData);

        if (INVALID_HANDLE_VALUE != hSearch)
        {
            // the file exists, so we must delete it

            BOOL fRc = DeleteFileW(m_wszSourceFileName);

            // IGNORE ERRORS

            // allow for the case where we wrote the log record, but did not create the file

        }
    }

    // OPTIONAL - forget this record

     *pfForget = TRUE;

    // NOTE: this forget is not forced - could force on next record if required

    return S_OK;

} // CCrmFilesCompensator::AbortRecord


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::EndAbort()

Summary: Notifies the CRM Compensator that it has received all the log 
		 records available during the abort phase.  

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesCompensator::EndAbort( void)
{
    // do nothing

    return S_OK;

} // CCrmFilesCompensator::EndAbort


///// ICrmFormatLogRecords

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::ProcessLogRecord(CrmLogRecordRead crmLogRec)

Summary: Process the raw log record into a form that is meaningful for this
		 CRM Compensator

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

HRESULT CCrmFilesCompensator::ProcessLogRecord(CrmLogRecordRead crmLogRec)
{
    ZeroMemory(&m_wszSourceFileName, MAX_PATH * sizeof(WCHAR));

    ZeroMemory(&m_wszTempFileName, MAX_PATH * sizeof(WCHAR));

    // what kind of log record did we get?

    // initially assume a "create file" log record

    CrmFilesCreateFileLogRecord * pCreateFileRec = (CrmFilesCreateFileLogRecord *)crmLogRec.blobUserData.pBlobData;
    
    m_CommandType = pCreateFileRec->CommandType;

    if (ct_CreateFile == m_CommandType)
    {
        WCHAR * pName = (WCHAR *)(pCreateFileRec + 1);      // skip over header

		_ASSERTE(pName != NULL);
        wcsncpy(m_wszSourceFileName, pName, pCreateFileRec->dwSourceSize);                
    }

    else
    {
        _ASSERTE(ct_DeleteFile == m_CommandType);

        CrmFilesDeleteFileLogRecord * pDeleteFileRec = (CrmFilesDeleteFileLogRecord *)pCreateFileRec;
         
        // get the source name
        
        WCHAR * pName = (WCHAR *)(pDeleteFileRec + 1);      // skip over header
		_ASSERTE(pName != NULL);
        wcsncpy(m_wszSourceFileName, pName, pDeleteFileRec->dwSourceSize);

        // get the temp name
        
        pName += pDeleteFileRec->dwSourceSize;              // skip over source name
		_ASSERTE(pName != NULL);
        wcsncpy(m_wszTempFileName, pName, pDeleteFileRec->dwTempSize);
    }

    return S_OK;

} // CCrmFilesCompensator::ProcessLogRecord


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::GetColumnCount(long __RPC_FAR *plColumnCount)

Summary: The purpose of this interface is to format the log records in a 
		 viewable format. It can be used for monitoring

Returns: HRESULT, plColumnCount returns the max # of columns in the formatted
		 record

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmFilesCompensator::GetColumnCount( 
    /* [out] */ long __RPC_FAR *plColumnCount)
{
	_ASSERTE(plColumnCount);

	*plColumnCount = 3;

	return S_OK;

} // CCrmFilesCompensator::GetColumnCount


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::GetColumnHeaders(LPVARIANT pHeaders)

Summary: Return the column headers as an array of variants

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmFilesCompensator::GetColumnHeaders( 
    /* [out] */ LPVARIANT pHeaders)
{
	_ASSERTE(pHeaders);

	_variant_t vCols[3] = { L"Command Type", L"Source File", L"Temp File" };

	MakeVariantArray(3, vCols, pHeaders);

	return S_OK;

} // CCrmFilesCompensator::GetColumnHeaders


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::MakeVariantArray(
									int				i_iNumVariants, 
									_variant_t		*i_vArray, 
									LPVARIANT		i_pVarSafeArray)

Summary: Create a variant array 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


void CCrmFilesCompensator::MakeVariantArray
(
	int				i_iNumVariants, 
	_variant_t		*i_vArray, 
	LPVARIANT		i_pVarSafeArray
)
{
    SAFEARRAYBOUND sab;

    sab.cElements = i_iNumVariants;
    
    sab.lLbound = 1;                    // VB convention

    SAFEARRAY * pSa;

    pSa = SafeArrayCreate(VT_VARIANT, 1, &sab);
    
    _ASSERTE(pSa);
    
    VARIANT * pSaVars = NULL;

    SafeArrayAccessData(pSa, (PVOID*)&pSaVars);
    
    _ASSERTE(pSaVars);

    // copy from the original array to the SafeArray

	for (int i = 0; i < i_iNumVariants; i++)
	{        		  
		// put them in the SafeArray

		pSaVars[i] = i_vArray[i];
	}

    // done filling the SafeArray, put it in a variant

    SafeArrayUnaccessData(pSa);

    _ASSERTE(i_pVarSafeArray);
       
    i_pVarSafeArray->vt = VT_ARRAY | VT_VARIANT;      // array of variants

    i_pVarSafeArray->parray = pSa;
    		
} // CCrmFilesCompensator::MakeVariantArray


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::GetColumn( 
							[in]  CrmLogRecordRead CrmLogRec,
							[out] LPVARIANT pFormattedLogRecord)

Summary: Given the unformatted record, return a formatted record as an array
		 of variants

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmFilesCompensator::GetColumn( 
    /* [in] */ CrmLogRecordRead CrmLogRec,
    /* [out] */ LPVARIANT pFormattedLogRecord)
{
	HRESULT hr = S_OK;

    hr = ProcessLogRecord(CrmLogRec);

	_ASSERTE(S_OK == hr);

	_variant_t vFields[3];

	if (ct_CreateFile == m_CommandType)
	{
		vFields[0] = L"CreateFile";

		vFields[2] = L"<None>";
	}
	else
	{
		vFields[0] = L"DeleteFile";

		vFields[2] = _variant_t(m_wszTempFileName);
	}

	vFields[1] = _variant_t(m_wszSourceFileName);

	MakeVariantArray(3, vFields, pFormattedLogRecord);

	return S_OK;

} // CCrmFilesCompensator::GetColumn


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesCompensator::GetColumnVariants( 
							    [in]  VARIANT LogRecord,
								[out] LPVARIANT pFormattedLogRecord)

Summary: Return a single formatted record given the unformatted record as an 
		 array of variants


Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT STDMETHODCALLTYPE CCrmFilesCompensator::GetColumnVariants( 
    /* [in] */ VARIANT LogRecord,
    /* [out] */ LPVARIANT pFormattedLogRecord)
{
	_ASSERTE(!"NOT IMPLEMENTED");

	return E_FAIL;

} // CCrmFilesCompensator::GetColumnVariants

