//****************************************************************************
//  Module:     NMFT.EXE
//  File:       MAIN.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1997-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"


//****************************************************************************
//
// Global variables.
//
//****************************************************************************

HINSTANCE ghInst        = NULL;   // Current Instance
HWND      ghwndMain     = NULL;   // Main Window
BOOL      g_fQuiet      = FALSE;  // 
TCHAR     g_szFile[MAX_PATH + 1]; //

CONST TCHAR g_szAppClassName[] = TEXT("NMFT Dialog");


//****************************************************************************
//
// BOOL ParseCmdLine(void)
//
//****************************************************************************

BOOL ParseCmdLine(void)
{
	LPTSTR pch = ::GetCommandLine();
	if (NULL == pch)
		return FALSE;

	// Work on a copy of the buffer
	TCHAR sz[MAX_PATH*2 + 1];

	ZeroMemory(sz, MAX_PATH*2 + 1);

	lstrcpyn(sz, pch, MAX_PATH*2 + 1);
	sz[MAX_PATH*2] = 0;

	pch = sz;

	BOOL	fInStr	= FALSE;
	BOOL	fInName	= FALSE;
	BOOL	fInApp	= TRUE;
	TCHAR	ch		= 0;
	LPTSTR	lpsz	= NULL;

	// walk through the command line, parsing filenames and options
	while (_T('\0') != (ch = *pch))
	{
		switch (ch)
		{
		case _T('\"'):      // Double quoted filename
			fInStr = !fInStr;
			if (fInStr)
			{
	 			lpsz = CharNext(pch);
	 			break;
 			}

		case _T(' '):       // Space usually terminates a filename
			if (fInStr)  // except in a long filename
				break;

		case _T('\0'):
			if (fInApp)
			{
				// Skip the application name (first string on command line)
				fInApp = FALSE;
				fInName = FALSE;
	 			lpsz = CharNext(pch);
				break;
			}
			
			if (!fInName)
			{
	 			lpsz = CharNext(pch);
				break; // ignore extra whitespace
			}

			{
				LPTSTR pchT = CharNext(pch);
				*pch = _T('\0'); // null terminate string
				fInName = FALSE;
				pch = pchT;
				continue; // continue loop
			}
			break;

		case _T('/'):      // Command line option
		{
			if (fInName || fInStr)
				break;

			pch = CharNext(pch);
			ch = *pch;
			if (_T('\0') == ch)
				return FALSE;

			if ((_T('Q') == ch) || (_T('q') == ch))
			{
				g_fQuiet = TRUE;
			}
			// TODO: other options

 			break;
		}

		default:        // Normal character
			fInName = TRUE;
			break;
		} /* switch (ch) */

		pch = CharNext(pch);
	}

	if ((NULL == lpsz) || (_T('\0') == *lpsz))
		return FALSE;

	ZeroMemory(g_szFile, MAX_PATH + 1);
	lstrcpyn(g_szFile, lpsz, MAX_PATH + 1);
	g_szFile[MAX_PATH] = 0;

	return TRUE;
}


//****************************************************************************
//
// BOOL FVerifyFile(void)
//
//****************************************************************************

BOOL FVerifyFile(void)
{
	// Check if filename was specified on command line
	if (ParseCmdLine())
		return TRUE;

	// Prompt the user to select a file
	if (FGetFileName(g_szFile))
		return TRUE;

	return FALSE;
}


//****************************************************************************
//
// BOOL FInitMain(void)
//
//****************************************************************************

BOOL FInitMain(void)
{
	TCHAR szTitle[MAX_PATH + 1];
	WNDCLASS  wc;

	ZeroMemory(szTitle, sizeof(TCHAR) * (MAX_PATH + 1));
	ZeroMemory(&wc, sizeof(WNDCLASS));

	ASSERT(NULL != ghInst);

	LoadString(ghInst, IDS_APP_TITLE, szTitle, MAX_PATH);

	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = DLGWINDOWEXTRA;
	wc.hInstance     = ghInst;
	wc.hIcon         = LoadIcon(ghInst, MAKEINTRESOURCE(ICO_MAIN));
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDM_APP);
	wc.lpszClassName = g_szAppClassName;

	// Register the window class and return FALSE if unsuccesful.
	if (!RegisterClass(&wc))
		return FALSE;

	ghwndMain = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_PROGRESS), 0, NULL);

	if (NULL == ghwndMain)
		return FALSE;

	if (!FInitNm())
	{
		// TODO: Display error message
		// Unable to initialize, no conference, etc.
		return FALSE;
	}

	if (!FVerifyFile())
		return FALSE;

	LPTSTR pszFile	= 0;
	GetFullPathName(g_szFile, MAX_PATH, g_szFile, &pszFile);

	if (!FFileExists(g_szFile))
	{
		TCHAR szMsg[2 * MAX_PATH + 1];

		ZeroMemory(szMsg, (2 * MAX_PATH + 1) * sizeof(TCHAR));

		_sntprintf(szMsg, 2 * MAX_PATH, TEXT("Unable to send the file\r\n%s"), g_szFile);
		MessageBox(NULL, szMsg, TEXT("NmFt Error"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	if (FAILED(SendFile()))
		return FALSE;

	return TRUE;
}


//****************************************************************************
//
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
//
// Main Windows entrypoint
//
//****************************************************************************

#ifdef _DEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
#else  // _DEBUG
int __cdecl main()
#endif // _DEBUG
{
#ifdef _DEBUG
	ghInst = hInstance;
#else
	ghInst = ::GetModuleHandle(NULL);
#endif // ! _DEBUG

	ZeroMemory(g_szFile, sizeof(TCHAR) * (MAX_PATH + 1));

	InitCommonControls();

 	if (FAILED(CoInitialize(NULL)))
		return 0;

	if (FInitMain() && !g_fQuiet)
	{
		MSG  msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	FreeNmObjects();
    CoUninitialize();

#ifndef DEBUG
	ExitProcess(0);
#endif

	return 0;
}

