/*+==========================================================================

File: TestDlg.cpp 

Summary: Implementation of CTestDlg

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
#include "TestDlg.h"

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C

Class: CTestDlg

Implementation of the ATL dialog class. We only use the OnInitDialog to set
up our timer and a method for our timer message
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 
/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Constructor

Summary: Create an instance of the LogWriter

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CTestDlg::CTestDlg() : m_nNumberWrites(0)
{
	// make our object
	HRESULT        hr;    
	IClassFactory *pCF;    
	
	hr=CoGetClassObject(CLSID_LogFile, CLSCTX_LOCAL_SERVER, NULL, IID_IClassFactory, (void **)&pCF);    
	_ASSERTE(SUCCEEDED(hr));

	hr=pCF->CreateInstance(NULL, IID_ILogFile, (void **) &m_pLF);    
	_ASSERTE(SUCCEEDED(hr));
	
	pCF->Release();    
		
	//CoCreateInstance(CLSID_LogFile, NULL, CLSCTX_INPROC_SERVER, IID_ILogFile, (void **) &m_pLF);
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: Destructor

Summary: Release our pointer

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CTestDlg::~CTestDlg()
{
	m_pLF->Release();
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: OnInitDialog

Summary: Grab our process ID and set up the timer to fire

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CTestDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// get our process id
	dwPID = GetCurrentProcessId();

	// set our timer to do the log writes
	SetTimer(NULL, 1000);

	return 1;  // Let the system set the focus
}

/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M

Method: OnTimer

Summary: Called when the WM_TIMER message is recieved. We only recive one so
		 when we get it, call the write method on our LogFile object

M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CTestDlg::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	_bstr_t msg = "Test String";
	WCHAR	buf[50];

	wsprintfW(buf, L"Message number %d\r\n", ++m_nNumberWrites);
	// move our buf into a BSTR
	msg = buf;
	m_pLF->Write(msg, dwPID);
	SetDlgItemInt(IDC_NUMBERWRITES, m_nNumberWrites);
	return 0;
}
