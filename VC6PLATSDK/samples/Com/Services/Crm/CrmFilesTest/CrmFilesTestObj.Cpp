/*+==========================================================================

File: CrmFilesTestObj.cpp



Summary: 

	Test driver component for CrmFiles CRM, VC, VB and VJ versions.

	Should be installed in a COM+ application and requires a transaction.

	This file is part of the Microsoft COM Technology Samples.

Classes: 

	
	  CCrmFilesTest


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
// CrmFilesTestObj.cpp : Implementation of CCrmFilesTest

#include "stdafx.h"
#include "CrmFilesTest.h"
#include "CrmFilesTestObj.h"

/////////////////////////////////////////////////////////////////////////////
// CCrmFilesTest

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::Activate()

Summary: IObjectControl Method. Allows an object to perform context-specific
		 initialization whenever it's activated. This method is called by 
		 COM+ before any other methods are called on the object.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesTest::Activate()
{
	ATLTRACE(_T("CCrmFilesTest::Activate\r\n"));

	m_lLanguage = 0;	// VC is default

	m_pICrmFilesWorkerCurrent = NULL;

	for (int i = 0; i < crm_Total; i++)
	{
		m_pICrmFilesWorker[i] = NULL;
	}

	HRESULT hr = CoGetObjectContext(IID_IObjectContext, (void**)&m_spObjectContext);
	if (SUCCEEDED(hr))
		return S_OK;
	return hr;

} // CCrmFilesTest::Activate


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::CanBePooled()

Summary: IObjectControl Method. Allows an object to notify COM+ of whether it
		 can be pooled for reuse.

Returns: BOOL

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


BOOL CCrmFilesTest::CanBePooled()
{
	ATLTRACE(_T("CCrmFilesTest::CanBePooled\r\n"));

	return TRUE;

} // CCrmFilesTest::CanBePooled
 

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::Deactivate()

Summary: IObjectControl Method. Allows an object to perform whatever cleanup
		 is necessary before it's recycled or destroyed. This method is
		 called by COM+ whenever an object is deactivated.

Returns: void

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


void CCrmFilesTest::Deactivate()
{
	ATLTRACE(_T("CCrmFilesTest::Deactivate\r\n"));

	// release any CRMs we might have

	for (int i = 0; i < crm_Total; i++)
	{
		if (NULL == m_pICrmFilesWorker[i]) continue;

		m_pICrmFilesWorker[i]->Release();

		m_pICrmFilesWorker[i] = NULL;
	}

	m_spObjectContext.Release();

} // CCrmFilesTest::Deactivate


///// ICrmFilesTest

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::put_FileName(BSTR newVal)

Summary: ICrmFilesTest Method. Puts the FileName property.

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmFilesTest::put_FileName(BSTR newVal)
{
	ATLTRACE(_T("CCrmFilesTest::put_FileName\r\n"));

	m_bstrFileName = newVal;

	return S_OK;

} // CCrmFilesTest::put_FileName


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::CreateFile()

Summary: ICrmFilesTest Method. Tells the Crm Worker to create the file 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmFilesTest::CreateFile()
{
	ATLTRACE(_T("CCrmFilesTest::CreateFile\r\n"));

	HRESULT hr = S_OK;

	hr = GetCorrectCRM();

	if (hr != S_OK) return hr;
	
	hr = m_pICrmFilesWorkerCurrent->CreateFile(m_bstrFileName);

	return hr;

} // CCrmFilesTest::CreateFile



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::DeleteFile()

Summary: ICrmFilesTest Method. Tells the Crm Worker to delete the file 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmFilesTest::DeleteFile()
{
	ATLTRACE(_T("CCrmFilesTest::DeleteFile\r\n"));

	HRESULT hr = S_OK;

	hr = GetCorrectCRM();

	if (hr != S_OK) return hr;
	
	hr = m_pICrmFilesWorkerCurrent->DeleteFile(m_bstrFileName);

	return hr;

} // CCrmFilesTest::DeleteFile


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::Commit()

Summary: ICrmFilesTest Method. Commits the transaction. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/



STDMETHODIMP CCrmFilesTest::Commit()
{
	ATLTRACE(_T("CCrmFilesTest::Commit\r\n"));

	IObjectContext * pContext = m_spObjectContext;

	HRESULT hr = pContext->SetComplete();

	_ASSERTE((S_OK == hr) || (CONTEXT_E_ABORTED == hr));

	return S_OK;

} // CCrmFilesTest::Commit



/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::Abort()

Summary: ICrmFilesTest Method. Aborts the transaction. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmFilesTest::Abort()
{
	ATLTRACE(_T("CCrmFilesTest::Abort\r\n"));

	IObjectContext * pContext = m_spObjectContext;

	HRESULT hr = pContext->SetAbort();

	_ASSERTE((S_OK == hr) || (CONTEXT_E_ABORTED == hr));

	return S_OK;

} // CCrmFilesTest::Abort


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::put_Language(long newVal)

Summary: ICrmFilesTest Method. Sets the language property. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


STDMETHODIMP CCrmFilesTest::put_Language(long newVal)
{
	ATLTRACE(_T("CCrmFilesTest::put_Language\r\n"));

	m_lLanguage = newVal;

	return S_OK;

} // CCrmFilesTest::put_Language


///// private functions


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CCrmFilesTest::put_Language(long newVal)

Summary: Creates the correct CRM depending on the language we are using. 

Returns: HRESULT

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/


HRESULT CCrmFilesTest::GetCorrectCRM(void)
{
	ATLTRACE(_T("CCrmFilesTest::GetCorrectCRM\r\n"));

	// if we already have the required CRM, select it

	if (m_pICrmFilesWorker[m_lLanguage])
	{
		m_pICrmFilesWorkerCurrent = m_pICrmFilesWorker[m_lLanguage];

		return S_OK;
	}

	// need to create a new CRM Worker

	HRESULT hr = S_OK;

	const wchar_t* pszProgID = NULL;
    CLSID clsid;

	switch (m_lLanguage)
	{
		case 0:	// VC

			pszProgID = L"CrmFilesWorker.CrmFilesWorker.1";
			hr = CLSIDFromProgID(pszProgID, &clsid);

			break;

		case 1:	// VB

			pszProgID = L"CrmFilesVB.CrmFilesWorkerVB";
			hr = CLSIDFromProgID(pszProgID, &clsid);

			break;

		case 2:	// VJ

			pszProgID = L"crmfilesvj.Worker";
			hr = CLSIDFromProgID(pszProgID, &clsid);

			break;

		default:

			_ASSERTE("ERROR: unknown language type");

			break;

	}; // switch

    _ASSERTE(S_OK == hr);

    // get the CrmFiles CRM Worker

	#if 0
		// don't use smart pointer so we don't have to catch com errors
		IObjectContext * pContext = m_spObjectContext;
	#endif

    hr = CoCreateInstance(
                        clsid,
						 NULL, CLSCTX_ALL,
                        __uuidof(ICrmFilesWorker),
                        (void **)&m_pICrmFilesWorker[m_lLanguage]);

    _ASSERTE(S_OK == hr);
    _ASSERTE(m_pICrmFilesWorker[m_lLanguage]);

	m_pICrmFilesWorkerCurrent = m_pICrmFilesWorker[m_lLanguage];

	return S_OK;

} // CCrmFilesTest::GetCorrectCRM
