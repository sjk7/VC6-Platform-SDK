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
#include "About.h"
#include "resource.h"
#include <malloc.h>


AboutDlg::AboutDlg() {

	m_hIcon = NULL;
}


AboutDlg::~AboutDlg() {

}


void AboutDlg::DoModal(HWND hWndParent, short sAgentVersionMajor, short sAgentVersionMinor) {

	HWND hWndFocus;

	m_sAgentMajor = sAgentVersionMajor;
	m_sAgentMinor = sAgentVersionMinor;

	hWndFocus = GetFocus();

	DialogBoxParam(GetModuleHandle(NULL), 
				   MAKEINTRESOURCE(IDD_ABOUT),
				   hWndParent,
				   (DLGPROC)DlgProc,
				   (long)this);

	if (hWndFocus)
		SetFocus(hWndFocus);
}


BOOL AboutDlg::OnInitDialog() {

	_TCHAR	szExe[_MAX_PATH];
	_TCHAR	szVersion[256];
	DWORD	dwVersionSize;
	DWORD	dwTemp;
	void   *pData;
	void   *pVerInfo;
	UINT	uVerInfoSize;

	// Load the application icon

	m_hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APP));

	GetWindowRect(GetDlgItem(m_hWnd, IDC_ICONPOS), &m_rcIcon);
	ScreenToClient(m_hWnd, (POINT *)&m_rcIcon);

	GetModuleFileName(NULL, szExe, _MAX_PATH);

	dwVersionSize = GetFileVersionInfoSize(szExe, &dwTemp);

	// There better be version data

	_ASSERT(dwVersionSize != 0);

	__try {
		pData = _alloca(dwVersionSize);
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {
		pData = NULL;
	}

	if (pData) {

		GetFileVersionInfo(szExe, 0, dwVersionSize, pData);

		if (VerQueryValue(pData, _T("\\"), &pVerInfo, &uVerInfoSize)) {
			wsprintf(szVersion, 
					 _T("%d.%.2d.%d.%d"), 
					 HIWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionMS),
					 LOWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionMS),
					 HIWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionLS),
					 LOWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionLS));
			SetDlgItemText(m_hWnd, IDC_VERSION, szVersion);
		}
	}

	// Microsoft Agent Version

	wsprintf(szVersion, _T("%d.%.2d"), m_sAgentMajor, m_sAgentMinor);
	SetDlgItemText(m_hWnd, IDC_AGENTVERSION, szVersion);

	return TRUE;
}


BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	AboutDlg *pDlg;

	pDlg = (AboutDlg *)GetWindowLong(hWnd, GWLP_USERDATA);

	switch (uMsg) {
		case WM_INITDIALOG:
			pDlg = (AboutDlg *)lParam;
			SetWindowLong(hWnd, GWLP_USERDATA, (long)pDlg);
			pDlg->m_hWnd = hWnd;
			return pDlg->OnInitDialog();


		case WM_COMMAND:
			if ((wParam == IDCANCEL) || (wParam == IDOK)) {
				EndDialog(hWnd, wParam);
				return TRUE;
			}
			break;


		case WM_SYSCOMMAND:
			if ((wParam & 0xFFF0) == SC_CLOSE) {
				EndDialog(hWnd, IDOK);
				return TRUE;
			}			
			break;


		case WM_PAINT:
			PAINTSTRUCT ps;
			HBRUSH hbr;

			BeginPaint(hWnd, &ps);

			hbr = CreateSolidBrush(GetSysColor(COLOR_3DFACE));

			DrawIconEx(ps.hdc, 
					   pDlg->m_rcIcon.left,
					   pDlg->m_rcIcon.top,
					   pDlg->m_hIcon, 
					   GetSystemMetrics(SM_CXICON), 
					   GetSystemMetrics(SM_CYICON), 
					   0, 
					   hbr, 
					   DI_NORMAL);

			DeleteObject(hbr);

			EndPaint(hWnd, &ps);
			break;
	}

	return FALSE;
}

