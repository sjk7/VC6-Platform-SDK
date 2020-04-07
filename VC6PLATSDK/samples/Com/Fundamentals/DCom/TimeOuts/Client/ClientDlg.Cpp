/*+==========================================================================

File: clientDlg.cpp

Summary:  Produced and maintained by VS6 MFC Wizards.
          Implements responses to Dialog-generate Win32 Events
          in client.exe.

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
// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_iData = 0;
	m_lPings = 0;
	m_lTimeouts = 0;
	m_lTries = 0;
	m_bUsePing = FALSE;
	m_lFails = 0;
	m_cRSN = _T("");
	m_lPingFailures = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDSTART, m_ctlStart);
	DDX_Control(pDX, IDC_WARNING, m_cWarning);
	DDX_Control(pDX, IDC_GOOD, m_cGood);
	DDX_Control(pDX, IDC_BAD, m_cBad);
	DDX_Text(pDX, IDC_LASTVALUE, m_iData);
	DDX_Text(pDX, IDC_PINGS, m_lPings);
	DDX_Text(pDX, IDC_TIMEOUTS, m_lTimeouts);
	DDX_Text(pDX, IDC_TRIES, m_lTries);
	DDX_Check(pDX, IDC_USEPING, m_bUsePing);
	DDX_Text(pDX, IDC_FAILS, m_lFails);
	DDX_Text(pDX, IDC_RSN, m_cRSN);
	DDX_Text(pDX, IDC_PINGFAILS, m_lPingFailures);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_USEPING, OnUsePing)
	ON_BN_CLICKED(IDSTART, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CClientDlg::OnOK()
{
	CDialog::OnOK();

	// Exit the monitor loop
	DestroyWindow();
}

void CClientDlg::OnUsePing()
{
	m_bUsePing = !m_bUsePing;
}

void CClientDlg::OnStart()
{
        WCHAR* pTemp = NULL;
	HRESULT hr = E_FAIL;


	
	if (theApp.pMonitor){
		// Disconnect from the Server
		if (theApp.pMonitorCallFactory) {
			theApp.pMonitorCallFactory->Release();
			theApp.pMonitorCallFactory = NULL;
		}
		
		if (theApp.pMonitorResponder){
			theApp.pMonitorResponder->Release();
			theApp.pMonitorResponder = NULL;
		}

		theApp.pMonitor->Release();
		theApp.pMonitor = NULL;
		
		m_ctlStart.SetWindowText(_T("Start"));
	} else {
		// Capture Remote Server Name
		UpdateData(TRUE);

                // Obtain the Remote Server Name
		COSERVERINFO	cos;
		cos.dwReserved1 = 0;
		cos.dwReserved2 = 0;
		cos.pAuthInfo = NULL;
#ifdef _UNICODE
                cos.pwszName = m_cRSN.GetBuffer(0);
#else
                int cchWide = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,m_cRSN.GetBuffer(0),-1,NULL,0);
                if (cchWide == 0)
                {
                  // Error Case
                  AfxMessageBox(_T("MultiByteToWideChar Failed on RemoteServer Name getting Length! Using local machine."));

                } else {
                  pTemp = new WCHAR[cchWide+1];
                  if (pTemp)
                  {
                    cchWide = MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,m_cRSN.GetBuffer(0),-1,pTemp,cchWide);
                    if (cchWide == 0)
                    {
                      AfxMessageBox(_T("MultiByteToWideChar Failed on RemoteServer Name copying string!"));
                      delete pTemp;
                      pTemp = NULL;
                    }
                  }
                }
                cos.pwszName = pTemp;
#endif

		// Need MultiQI for CoCreateInstanceEx
		MULTI_QI mqi;
		mqi.pIID = &IID_IMonitorServer;
		mqi.pItf = NULL;
		mqi.hr = E_FAIL;

		// Connect to server
		hr = CoCreateInstanceEx(CLSID_MonitorServer, NULL, CLSCTX_LOCAL_SERVER|CLSCTX_REMOTE_SERVER, &cos, 1, &mqi);
		if (FAILED(hr) || FAILED(mqi.hr)){
			AfxMessageBox(_T("Please Register Server, proxystub DLL on local machine, and specified Remote Server!"));
			OnOK();
			if (pTemp) delete pTemp;
                        return;
		}

		theApp.pMonitor = (IMonitorServer*)mqi.pItf;

		// Make sure IMonitorServer supports Non-Blocking Calls
	
		hr = theApp.pMonitor->QueryInterface(IID_ICallFactory, (void**)&theApp.pMonitorCallFactory);
		if (FAILED(hr)){
			AfxMessageBox(_T("IMonitorServer doesn't support Non-Blocking Calls! Executing on Windows 2000?"));
			theApp.pMonitor->Release();
			theApp.pMonitor = NULL;
			OnOK();
			if (pTemp) delete pTemp;
			return;
		}

		hr = theApp.pMonitor->GetPingResponder(&theApp.pMonitorResponder);
		if (FAILED(hr)){
			AfxMessageBox(_T("IMonitorServer doesn't support PingResponder! Please Register PingResp.dll on local system and Remote Server."));
			theApp.pMonitorCallFactory->Release();
			theApp.pMonitorCallFactory = NULL;

			theApp.pMonitor->Release();
			theApp.pMonitor = NULL;
			OnOK();
			if (pTemp) delete pTemp;
			return;
		}

                if (pTemp) delete pTemp;

                m_ctlStart.SetWindowText(_T("Stop"));
		
		// Reset Statistics
		m_iData = 0;
		m_lPings = 0;
		m_lTimeouts = 0;
		m_lTries = 0;
		m_lFails = 0;
		m_lPingFailures = 0;

                // Start OnIdle processing in CClientApp
		SetTimer(47,MONITORPOLLDELAY,NULL);
	}
}
