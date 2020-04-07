/*+==========================================================================

File: clientDlg.h

Summary:  Produced and maintained by VS6 MFC Wizards.
          Defines Dialogs used in client.exe.

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

#if !defined(AFX_CLIENTDLG_H__146DF855_4D72_11D2_9672_00AA00B913AC__INCLUDED_)
#define AFX_CLIENTDLG_H__146DF855_4D72_11D2_9672_00AA00B913AC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CButton	m_ctlStart;
	CStatic	m_cWarning;
	CStatic	m_cGood;
	CStatic	m_cBad;
	long	m_iData;
	long	m_lPings;
	long	m_lTimeouts;
	long	m_lTries;
	BOOL	m_bUsePing;
	long	m_lFails;
	CString	m_cRSN;
	long	m_lPingFailures;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnUsePing();
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__146DF855_4D72_11D2_9672_00AA00B913AC__INCLUDED_)
