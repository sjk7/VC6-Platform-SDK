//****************************************************************************
//  Module:     NMSHARE.EXE     
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
// Global Variables
//
//****************************************************************************


HINSTANCE ghInst       = NULL;          // Current Instance
HACCEL    ghAccelTable = NULL;          // Menu accelerators
HMENU     ghMenu       = NULL;          // Main Menu
HWND      ghwndMain    = NULL;          // Main Window
HWND      ghwndSbar    = NULL;          // Status Bar
HWND      ghwndMsg     = hwndNil;       // Message window
HWND      ghwndApp     = hwndNil;       // Application List
HWND      ghwndUser    = hwndNil;       // User List
HFONT     ghfontMsg    = hfontNil;      // Font for messages
PREF      gPref;


TCHAR gszAppTitle[]     = TEXT("NetMeeting Sharing Test Application");

// string constants (no change for international)
TCHAR gszAppClassName[] = TEXT("NMSHARE");
TCHAR gszAppName[]      = TEXT("NmShare");

// List column information

typedef struct _tagCol {
	UINT  dwWidth;
	LPTSTR lpsz;
} COL;
typedef COL * LPCOL;


// See ILV_*
static COL _rgColMsg[] = {
	{70,  TEXT("INmApp")},
	{70,  TEXT("Hwnd")},
	{70,  TEXT("Status")},
	{400, TEXT("Name")},
};


//****************************************************************************
//
// BOOL FInitPref(void)
//
// Initialize user preferences
//
//****************************************************************************

BOOL FInitPref(void)
{
	ClearStruct(&gPref);
	gPref.fMsgWindow = TRUE;
	gPref.fUserList = TRUE;
	return TRUE;
}


//****************************************************************************
//
// BOOL FCreateAppWindow(void)
//
// Create the application list window
//
//****************************************************************************

BOOL FCreateAppWindow(void)
{
	ghwndApp = CreateWindow(TEXT("SysListView32"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LVS_REPORT,
		0, 0, 0, 0,
		ghwndMain, (HMENU) IDW_APP, ghInst, NULL);
	if (ghwndApp == NULL)
		return FALSE;

	// Initialize column data
	{
		int   iCol = 0;
		LPCOL lpCol = NULL;
		LV_COLUMN lvc;

		lpCol = _rgColMsg;
		ClearStruct(&lvc);
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		for (iCol = 0; iCol < ARRAY_ELEMENTS(_rgColMsg); iCol++)
		{
			lvc.iSubItem = iCol;
			lvc.cx = lpCol->dwWidth;
			lvc.pszText = lpCol->lpsz;
			if (ListView_InsertColumn(ghwndApp, iCol, &lvc) == -1)
				return FALSE;
			lpCol++;
		}
	}

	return TRUE;
}


//****************************************************************************
//
// BOOL FCreateUserList(void)
//
// Create a listbox for the users
//
//****************************************************************************

BOOL FCreateUserList(void)
{
	ghwndUser = CreateWindow(TEXT("SysListView32"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,
		0, 0, DXP_USER, 0,
		ghwndMain, (HMENU) IDW_USER, ghInst, NULL);

	if (NULL == ghwndUser)
		return FALSE;

	// Initialize column data
	{
		LV_COLUMN lvc;

		ClearStruct(&lvc);
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		lvc.iSubItem = 0;
		lvc.cx = DXP_USER;
		lvc.pszText = TEXT("Users");
		if (ListView_InsertColumn(ghwndUser, 0, &lvc) == -1)
			return FALSE;
	}

	return TRUE;
}


//****************************************************************************
//
// BOOL FCreateMsgWindow(void)
//
// Create the main message window
//
//****************************************************************************

BOOL FCreateMsgWindow(void)
{
	ghwndMsg = CreateWindow(TEXT("LISTBOX"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | WS_CLIPSIBLINGS |
		LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT | LBS_HASSTRINGS,
		0, 0, 0, 0,
		ghwndMain, (HMENU) IDW_MSG, ghInst, NULL);
	if (NULL == ghwndMsg)
		return FALSE;

	// set the font for the window
	ghfontMsg = CreateFontIndirect(&gPref.lf);
	if (ghfontMsg == hfontNil)
		return TRUE;

	SendMessage(ghwndMsg, WM_SETFONT, (WPARAM) ghfontMsg, MAKELPARAM(TRUE, 0));

	return TRUE;
}


//****************************************************************************
//
// BOOL FInitMain(void)
//
// Initialize the window data and register the window class
//
//****************************************************************************

BOOL FInitMain(void)
{
	TCHAR szTitle[MAX_PATH + 1];
	WNDCLASS  wc;

	ASSERT(NULL != ghInst);

	ZeroMemory(szTitle,(MAX_PATH + 1) * sizeof(TCHAR));

	ghAccelTable = LoadAccelerators(ghInst, MAKEINTRESOURCE(ID_APPACCEL));

	LoadString(ghInst, IDS_APP_TITLE, szTitle, CCHMAX(szTitle));

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = ghInst;
	wc.hIcon         = LoadIcon(ghInst, MAKEINTRESOURCE(ICO_MAIN));
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDM_APP);
	wc.lpszClassName = gszAppClassName;

	// Register the window class and return FALSE if unsuccesful.
	if (!RegisterClass(&wc))
		return FALSE;

	// Create a main window for this application instance.
	ghwndMain = CreateWindow(gszAppClassName, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 400, 300,
		NULL, NULL, ghInst, NULL);
	if (ghwndMain == NULL)
		return FALSE;

	ghMenu = GetMenu(ghwndMain);
	return (NULL != ghMenu);
}


//****************************************************************************
//
// BOOL FInitApp(LPSTR lpszCmd, int nCmdShow)
//
// Initialize the application after checking command line, etc.
//
//****************************************************************************

BOOL FInitApp(LPSTR lpszCmd, int nCmdShow)
{
	InitCommonControls();

 	if (FAILED(CoInitialize(NULL)))
		return FALSE;

	if (!FInitPref())
		return FALSE;

	if (!FInitMain())
		return FALSE;

	if (!FCreateMsgWindow())
		return FALSE;

	if (!FCreateUserList())
		return FALSE;

	if (!FCreateAppWindow())
		return FALSE;

	ASSERT(NULL != ghwndMain);
	ShowWindow(ghwndMain, nCmdShow);
	UpdateWindow(ghwndMain);

	return S_OK == InitConfMgr();
}


//****************************************************************************
//
// VOID TerminateApp(void)
//
//****************************************************************************

VOID TerminateApp(void)
{
	// Release all objects to which this app has a reference
	FreeAllApps();
	FreeAppShareChannel();
	FreeAllUsers();
	FreeConference();
	FreeConfMgr();

    // Uninitialize OLE
    CoUninitialize();
}


//****************************************************************************
//
// int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR  lpszCmd, int nCmdShow)
//
//****************************************************************************

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR  lpszCmd, int nCmdShow)
{
	ghInst = hInstance;

	if (FInitApp(lpszCmd, nCmdShow))
	{
		MSG  msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, ghAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	TerminateApp();

	return 0;
}

