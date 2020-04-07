/*+==========================================================================

File: client.h

Summary:  Produced by VS6 MFC Wizard. Main Header file for Client.exe Application

Look in this module to see definitions used in client.cpp to implement DCOM
timeouts.

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

#if !defined(AFX_CLIENT_H__146DF853_4D72_11D2_9672_00AA00B913AC__INCLUDED_)
#define AFX_CLIENT_H__146DF853_4D72_11D2_9672_00AA00B913AC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "clientDlg.h"
#include "..\server\server.h"

/////////////////////////////////////////////////////////////////////////////
// CClientApp:
// See client.cpp for the implementation of this class
//

class CClientApp : public CWinApp
{
public:
	CClientApp();
	~CClientApp();

	CClientDlg	*pDlg;
	IMonitorServer *pMonitor;
	ICallFactory* pMonitorCallFactory;
	IPingResponder* pMonitorResponder;
	int nFail;

	HRESULT DoAPing(IPingResponder* pResp, DWORD dwTimeout);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CClientApp theApp;

#define MONITORPOLLDELAY (1*1000)
#define CALLTIMEOUT (4*1000)
#define CALLTIMEOUTWHENPINGING (2*1000)
#define PINGTIMEOUT (1*1000)

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_H__146DF853_4D72_11D2_9672_00AA00B913AC__INCLUDED_)
