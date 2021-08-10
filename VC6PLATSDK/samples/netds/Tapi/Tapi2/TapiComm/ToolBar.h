// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1995 - 2000 Microsoft Corporation.  All Rights Reserved.
//
// PURPOSE:
//    Contains declarations for the toolbar module.
//

//-------------------------------------------------------------------------
#define IDM_TOOLBAR         500 // ID for the toolbar.
#define IDB_BMP             700 // Bitmap ID for the toolbar.

// Global variable for Toolbar window
extern HWND hWndToolbar;

// Function protoptype for Creating Toolbar
BOOL CreateTBar(HWND);
void EnableMakeCall(HWND hWnd, BOOL bEnable);
void EnableHangupCall(HWND hWnd, BOOL bEnable);
