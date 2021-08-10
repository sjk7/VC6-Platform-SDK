/*	
	Copyright (c) 1998 - 2000 by Microsoft Corporation

	THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
	AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
	NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
	MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
	LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
	FOREGOING LIMITATION MAY NOT APPLY.

	This software may be copied and distributed royalty-free subject to
	the following conditions:

	1. You must copy all software without modification and must include
	   all pages, if the software is distributed without inclusion in your
	   software product. If you are incorporating the software in
	   conjunction with and as a part of your software product which adds
	   substantial value, you may modify and include portions of the
	   software.

	2. You must place all copyright notices and other protective
	   disclaimers and notices contained on the software on all copies of
	   the software and your software product.

	3. Unless the software is incorporated in your software product which
	   adds substantial value, you may not distribute this software for
	   profit.

	4. You may not use Microsoft's name, logo, or trademarks to market
	   your software product.

	5. You agree to indemnify, hold harmless, and defend Microsoft and its
	   suppliers from and against any claims or lawsuits, including
	   attorneys' fees, that arise or result from the use or distribution
	   of your software product and any modifications to the software.		
*/


#include "stdafx.h"
#include "MainDlg.h"
#include "Error.h"

// Globals

extern HINSTANCE	 g_hInst = NULL;
extern MainDlg		*g_pMainDlg = NULL;

// Application Title

extern const LPTSTR kpszAppTitle = _T("Microsoft Agent Character Previewer");


// WinMain

extern "C" int PASCAL WinMain(HINSTANCE hInst,
							  HINSTANCE hInstPrev,
							  LPTSTR pszCmdLine,
							  int nCmdShow) {
	MSG msg;
	HRESULT hRes;

	g_hInst = hInst;

	// Initialize COM

	CoInitialize(NULL);

	// Create an instance of our main dialog class

	g_pMainDlg = new MainDlg;

	if (g_pMainDlg == NULL)
		return -1;

	// And initialize it

	hRes = g_pMainDlg->Init();

	if (FAILED(hRes)) {
		delete g_pMainDlg;
		SystemError(NULL, hRes, FALSE);
		return -1;
	}

	// Show the window

	ShowWindow(g_pMainDlg->m_hWnd, SW_SHOW);

	// See if we got a filename on the command line

	if (lstrlen(pszCmdLine) > 0) {
		
		// Sometimes associating a file encloses it in
		// double quotes.

		if (pszCmdLine[0] == '"')
			pszCmdLine = _tcsinc(pszCmdLine);
		
		if (pszCmdLine[_tcslen(pszCmdLine)-1] == '"')
			pszCmdLine[_tcslen(pszCmdLine)-1] = 0;

		// Load the character specified on the command line.
		// This allows someone to associate this program with
		// character files so that they can double click them
		// and start this application.

		g_pMainDlg->LoadCharacter(pszCmdLine);
	}

	// Standard message loop

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		if (TranslateAccelerator(g_pMainDlg->m_hWnd, g_pMainDlg->m_hAccel, &msg))
			continue;
		if (IsDialogMessage(g_pMainDlg->m_hWnd, &msg))
			continue;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Clean up

	delete g_pMainDlg;

	CoUninitialize();

	return 0;
}
