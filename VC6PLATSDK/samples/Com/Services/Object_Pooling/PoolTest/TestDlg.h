/*+==========================================================================

File: TestDlg.h 

Summary: Declaration of the CTestDlg

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

#ifndef __TESTDLG_H_
#define __TESTDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <initguid.h>

#include "LogWriter\LogWriter_i.c"
#include "LogWriter\LogWriter.h"


/////////////////////////////////////////////////////////////////////////////
// CTestDlg
class CTestDlg : 
	public CDialogImpl<CTestDlg>
{
public:
	CTestDlg();
	~CTestDlg();
	
	enum { IDD = IDD_TESTDLG };

BEGIN_MSG_MAP(CTestDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	int	m_nNumberWrites;
	ILogFile *m_pLF;
	DWORD dwPID;
};

#endif //__TESTDLG_H_
