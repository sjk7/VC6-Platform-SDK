//****************************************************************************
//  Module:     NMCHAT.EXE
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
HWND      ghwndMsg     = hwndNil;       // Message window
HWND      ghwndEdit    = hwndNil;       // Edit Control
HWND      ghwndUser    = hwndNil;       // User List
HFONT     ghfontMsg    = hfontNil;      // Font for messages


TCHAR gszAppTitle[]     = TEXT("NetMeeting Chat Test Application");

// string constants (no change for international)
TCHAR gszAppClassName[] = TEXT("NMCHAT");
TCHAR gszAppName[]      = TEXT("NmChat");

// List column information

typedef struct _tagCol {
	UINT  dwWidth;
	LPTSTR lpsz;
} COL;
typedef COL * LPCOL;


// See ILV_*
static COL _rgColMsg[] = {
	{DXP_USER,  TEXT("Name")},
	{80,  TEXT("Time")},
	{400, TEXT("Message")},
};


//****************************************************************************
//
// BOOL FCreateMsgWindow(void)
//
// Create the main message listview
//
//****************************************************************************

BOOL FCreateMsgWindow(void)
{
	ghwndMsg = CreateWindow(TEXT("SysListView32"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | LVS_REPORT,
		0, 0, 0, 0,
		ghwndMain, (HMENU) IDW_USER, ghInst, NULL);
	if (ghwndMsg == NULL)
	{
		return FALSE;
	}

	// Initialize column data
	{
		int   iCol		= 0;
		LPCOL lpCol		= _rgColMsg;
		LV_COLUMN lvc;

		ClearStruct(&lvc);						// Zero's memory
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		for (iCol = 0; iCol < ARRAY_ELEMENTS(_rgColMsg); iCol++)
		{
			lvc.iSubItem = iCol;
			lvc.cx = lpCol->dwWidth;
			lvc.pszText = lpCol->lpsz;
			if (ListView_InsertColumn(ghwndMsg, iCol, &lvc) == -1)
			{
				return FALSE;
			}
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
		ghwndMain, (HMENU) IDW_MSG, ghInst, NULL);

	if (NULL == ghwndUser)
	{
		return FALSE;
	}

	// Initialize column data
	{
		LV_COLUMN lvc;

		ClearStruct(&lvc);						// Zero's memory
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		lvc.iSubItem = 0;
		lvc.cx = DXP_USER;
		lvc.pszText = TEXT("Send To");
		if (ListView_InsertColumn(ghwndUser, 0, &lvc) == -1)
		{
			return FALSE;
		}
	}

	return TRUE;
}


WNDPROC lpProcEdit = NULL;
LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//****************************************************************************
//
// LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ((uMsg == WM_CHAR) && (VK_RETURN == wParam))
	{
		SendText();
		return 0L;
	}

	return CallWindowProc(lpProcEdit, hwnd, uMsg, wParam, lParam);
}


//****************************************************************************
//
// BOOL FCreateEditWindow(void)
//
//****************************************************************************

BOOL FCreateEditWindow(void)
{
	ghwndEdit = CreateWindow(TEXT("EDIT"), NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		0, 0, 0, DYP_EDIT,
		ghwndMain, (HMENU) IDW_EDIT, ghInst, NULL);
	if (ghwndEdit == NULL)
	{
		return FALSE;
	}

	// set the font for the window

	lpProcEdit = (WNDPROC) GetWindowLong(ghwndEdit, GWL_WNDPROC);
	SetWindowLong(ghwndEdit, GWL_WNDPROC, (LONG)(WNDPROC) SubClsEdit);

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
	WNDCLASS  wc;
	TCHAR szTitle[MAX_PATH + 1];

	ZeroMemory(&wc, sizeof(WNDCLASS));
	ZeroMemory(szTitle, (MAX_PATH + 1) * sizeof(TCHAR));

	ASSERT(NULL != ghInst);

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
	{
		return FALSE;
	}

	// Create a main window for this application instance.
	ghwndMain = CreateWindow(gszAppClassName, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, 400, 300,
		NULL, NULL, ghInst, NULL);
	if (ghwndMain == NULL)
	{
		return FALSE;
	}

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
	{
		return FALSE;
	}

	if (!FInitMain())
	{
		return FALSE;
	}

	if (!FCreateMsgWindow())
	{
		return FALSE;
	}

	if (!FCreateUserList())
	{
		return FALSE;
	}

	if (!FCreateEditWindow())
	{
		return FALSE;
	}

	ASSERT(NULL != ghwndMain);

// DO I NEED A CHECK HERE for if(NULL == ghwndMain)? 

	ShowWindow(ghwndMain, nCmdShow);
	UpdateWindow(ghwndMain);

	SetFocus(ghwndEdit);

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
	FreeDataChannel();
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
// Main Windows entrypoint
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

