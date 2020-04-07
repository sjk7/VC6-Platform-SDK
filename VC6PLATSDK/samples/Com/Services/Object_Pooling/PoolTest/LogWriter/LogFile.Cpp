/*+==========================================================================

File: LogFile.cpp

Summary: Implementation of CLogFile

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
#include "LogWriter.h"
#include "LogFile.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CLogFile

CLogFile is a poolable object that opens a file on creation and closes
it on destruction. During the Write method it sets the done bit to allow COM+
to pool this object so it can be shared among several different applications
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Destructor

Summary: Close the file that was opened for this class

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CLogFile::~CLogFile()
{
	// close the file
	CloseHandle(m_hFile);
}

// interface IObjectControl

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Activate

Summary: COM+ tells us when we have been activated. We need to setup our
		 object for this context

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CLogFile::Activate()
{
	IObjectContext* pObjectContext;

	// get our context
	HRESULT hr = GetObjectContext(&pObjectContext);
	if (FAILED(hr))
		return hr;

	// now get the ContextState
	hr = pObjectContext->QueryInterface(IID_IContextState, (void **)&m_pContextState);
	if (FAILED(hr))
	{
		pObjectContext->Release();
		return hr;
	}
	return hr;

}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Deactivate

Summary: COM+ tells us when we are being deactivated. Remove any context state
		 we have. We don't close the file here since it's state is maintained
		 througout all contexts

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
void CLogFile::Deactivate()
{
	m_pContextState->Release();
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: CanBePooled

Summary: COM+ asks us if our object can be pooled

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CLogFile::CanBePooled()
{
	// we can be pooled
	return TRUE;
}

// interface IObjectConstruct
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Construct

Summary: This method is called by COM+ with the value specified in the COM+
		 explorer for this object. This is where we open our file for logging

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

HRESULT CLogFile::Construct(IDispatch * pCtorObj)
{
	// first we need to get the IObjectConstructString from the IDispatch
	// passed in

	IObjectConstructString	*pOCS = NULL;
	HRESULT hr = pCtorObj->QueryInterface(IID_IObjectConstructString, (void **)&pOCS);
	if FAILED(hr)
		return hr;

	// get the construction string
	BSTR	bstrLogFileName;
	hr = pOCS->get_ConstructString(&bstrLogFileName);
	if FAILED(hr)
	{
		// free our file name string
		SysFreeString(bstrLogFileName);
		pOCS->Release();
		return hr;
	}
	
	// if we didn't get a value then default
	if (!bstrLogFileName)
		return E_FAIL;

	// open the file
	m_hFile = CreateFile(bstrLogFileName, 
							GENERIC_WRITE, 
							FILE_SHARE_READ, 
							NULL, 
							OPEN_ALWAYS,  
							FILE_ATTRIBUTE_NORMAL, 
							NULL);
	if (m_hFile == INVALID_HANDLE_VALUE)
	{
		// free our file name string
		SysFreeString(bstrLogFileName);
		pOCS->Release();
		return E_FAIL;
	}

	// if we have a new file the size will be zero so write out the Unicode
	// byte order 
	DWORD dwSize = GetFileSize(m_hFile, NULL); 
	DWORD dwBytesWritten = 0;
	ULONG dwUnicodeByteOrder = 0xFEFF;	// Unicode stream header
	if (dwSize == 0)
	{
		if (!WriteFile(m_hFile, &dwUnicodeByteOrder, 2, &dwBytesWritten, NULL))
		{
			// free our file name string
			SysFreeString(bstrLogFileName);
			pOCS->Release();
			return E_FAIL;
		}
	}

	// free our file name string
	SysFreeString(bstrLogFileName);

	pOCS->Release();

	return S_OK;
}

// interface ILogFile

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Write

Summary: Write out the buffer passed in and the ID into the log file. It also
		 adds the date and time to the log entry.

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
STDMETHODIMP CLogFile::Write(BSTR buf, DWORD dwID)
{

	HRESULT hr = S_OK;

	DWORD dwPos = 0;
	DWORD dwBytesWritten = 0;
	_bstr_t newBuf;
	DWORD dwBufLen = 0;
		
	// get the local date and time
	int nSize = GetDateFormat(NULL, 0, NULL, NULL, NULL, 0);
	WCHAR* sBuffer = new WCHAR[nSize];
	GetDateFormatW(NULL, 0, NULL, NULL, sBuffer, nSize);
	newBuf = sBuffer;
	delete [] sBuffer;
	
	newBuf += L" ";

	nSize = GetTimeFormat(NULL, 0, NULL, NULL, NULL, 0);
	sBuffer = new WCHAR[nSize];
	GetTimeFormatW(NULL, 0, NULL, NULL, sBuffer, nSize);
	newBuf += sBuffer;
	delete [] sBuffer;


	// put the proc ID and the text passed in on
	sBuffer = new WCHAR[200];
	wsprintfW(sBuffer, L" : ProcID = %#08x : ", dwID);
	newBuf += sBuffer;
	delete [] sBuffer;
	newBuf += buf;

	dwBufLen = SysStringByteLen(newBuf);

    dwPos = SetFilePointer(m_hFile, 0, NULL, FILE_END); 
    if (!WriteFile(m_hFile, (wchar_t *)newBuf, dwBufLen, &dwBytesWritten, NULL))
	{
		hr = E_FAIL;
	}

    m_pContextState->SetDeactivateOnReturn(TRUE);

	return hr;
}
