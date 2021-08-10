//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       MAIN.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
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

HWND      ghwndSbar    = NULL;			// Status bar window
HWND      ghwndTbar    = NULL;			// Toolbar window
HWND      ghwndMsg     = NULL;			// Message window
HWND      ghwndChat    = NULL;			// Chat Edit Control
HWND      ghwndSend    = NULL;			// Send Button
HWND      ghwndUList   = NULL;			// User List
HWND      ghwndLView   = NULL;			// Main List View	
HWND      ghwndEntry   = NULL;			// szEntry Edit control
HFONT     ghfontEntry  = NULL;			// Font for edit control

PREF      gPref;                        // User preferences
int       gdxWndMin    = 325;           // maximum size of window
int       gdyWndMin    = 250;           // maximum size of window





VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	DoEnumApps();
}

//****************************************************************************
//
// Main Windows entrypoint
//
//****************************************************************************

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR  lpszCmd, int nCmdShow)
{
	ghInst = hInstance;

	if (FInitApp(lpszCmd, nCmdShow))
	{

		MSG  msg = {0,0,0,0,0,0};
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (!TranslateAccelerator(msg.hwnd, ghAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

    // Uninitialize OLE
    CoUninitialize();

	return 0;
}


