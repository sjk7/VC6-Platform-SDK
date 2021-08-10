/*++

Copyright (c) Microsoft Corporation


--*/
// GenericUCP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GenericUCP.h"
#include "GenericUCPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CComModule _Module;

/////////////////////////////////////////////////////////////////////////////
// CGenericUCPApp

BEGIN_MESSAGE_MAP(CGenericUCPApp, CWinApp)
	//{{AFX_MSG_MAP(CGenericUCPApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenericUCPApp construction

CGenericUCPApp::CGenericUCPApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGenericUCPApp object

CGenericUCPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGenericUCPApp initialization

BOOL CGenericUCPApp::InitInstance()
{
	
	AfxInitRichEdit();

	AfxEnableControlContainer();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}


	if(CoInitialize(NULL)!=S_OK){
		TRACE(_T("CoInitialize failed\n"));
		return FALSE; // Return if COM initialization failed
	}

	// Standard initialization
	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CGenericUCPDlg dlg;
	m_pMainWnd = &dlg;

	dlg.DoModal();


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


int CGenericUCPApp::ExitInstance()
{
	CoUninitialize();// Uninitialize the COM
	return 0;
}
