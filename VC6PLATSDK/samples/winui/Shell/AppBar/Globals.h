// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 2000  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     globals.h   
//
//  PURPOSE:    contains variables and prototypes global to the application
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//////////////////////////////////////////////////////////////////////////////
// Constants and Enumerations

typedef enum tagVERSION {WINNT, WIN32S, WIN95} VERSION;

#define APPBAR_CALLBACK     WM_USER + 1010


//////////////////////////////////////////////////////////////////////////////
// Global Variables

extern HINSTANCE g_hInstance;                                   // initproc.c
extern VERSION version;                                         // main.c


//////////////////////////////////////////////////////////////////////////////
// Prototypes

void ErrorHandlerEx(INT, LPSTR);                               // main.c
int DebugMsg(const TCHAR *pFmt, ...);                           // main.c
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);       // wndproc.c
BOOL InitApplication(HINSTANCE);                                // main.c
BOOL InitInstance(HINSTANCE, int);                              // main.c
void ShowOptions(HWND hwndParent);                              // propsheet.c
void SlideWindow(HWND, LPRECT);                                 // util.c


//////////////////////////////////////////////////////////////////////////////
// Macros

#define ErrorHandler() ErrorHandlerEx(__LINE__, __FILE__)


/* BOOL Cls_OnMoving(HWND hwnd, WPARAM fwSide, LPRECT lprc) */
#define HANDLE_WM_MOVING(hwnd, wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((hwnd), (wParam), (LPRECT)(lParam))
#define FORWARD_WM_MOVING(hwnd, fwSide, lprc) \
    (BOOL)(DWORD)(fn)((hwnd), WM_MOVING, (WPARAM)(fwSide), (LPARAM)(LPRECT)(lprc))

#endif
