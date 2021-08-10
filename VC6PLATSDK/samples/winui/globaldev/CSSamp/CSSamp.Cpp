// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright  1994 - 2000  Microsoft Corporation.  All Rights Reserved.
//
// PROGRAM:    CSSAMP.cpp
//
// PURPOSE:    Demonstrate and test Uniscribe APIs
//
// PLATFORMS:  Windows 95, 98, NT 4, NT 5.
//

#include "precomp.hxx"

#define GLOBALS_HERE 1
#include "global.h"

////    Initialise
//
void Initialise() 
{
    InitStyles();
    InitText();
}

///    _tWinMain - Application entry point and dispatch loop
//
//
int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpszCmdLine,
  int nCmdShow
)
{
    MSG         msg = {0};
    HACCEL      hAccelTable = NULL;
    RECT        rc = {0};
    RECT        rcMain = {0};
    int         iRetValue = 1;
    BOOL        bSucess = TRUE;

    g_hInstance = hInstance;  // Global hInstance
    Initialise();

    // Create main text window
    g_hTextWnd = CreateTextWindow();

    // Add dialog box on leading side
    if(NULL == (g_hSettingsDlg = CreateDialog(g_hInstance,TEXT("Settings"),g_hTextWnd,(DLGPROC)SettingsDlgProc)))
    {
        iRetValue = 0;
        goto RETURN;
    }

    // Establish positon of text surface relative to the dialog
    GetWindowRect(g_hSettingsDlg, &rc);
    g_iSettingsWidth = rc.right - rc.left;
    g_iSettingsHeight = rc.bottom - rc.top;

    // Establish offset from main window to settings dialog
    GetWindowRect(g_hTextWnd, &rcMain);
    g_iMinWidth = rc.right - rcMain.left;
    g_iMinHeight = rc.bottom - rcMain.top;

    // Size main window to include dialog and text surface
    SetWindowPos(
        g_hTextWnd,
        NULL,
        0,0,
        g_iMinWidth * 29 / 10, g_iMinHeight,
        SWP_NOZORDER | SWP_NOMOVE);

    ShowWindow(g_hTextWnd, SW_SHOWNORMAL);
    InvalidateText();
    UpdateWindow(g_hTextWnd);

    // Main message loop
    if (g_bUnicodeWnd) 
    {
        hAccelTable = LoadAcceleratorsW(g_hInstance, APPNAMEW);

        while (0 != (bSucess = GetMessageW(&msg, (HWND) NULL, 0, 0))) 
        {
            if(bSucess == -1)
            {
                iRetValue = 1;
                goto RETURN;
            }
            if (g_hSettingsDlg == (HWND) NULL ||
                !IsDialogMessageW(g_hSettingsDlg, &msg) &&
                !TranslateAcceleratorW(g_hTextWnd, hAccelTable, &msg)) 
            {

                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }
    } 
    else 
    {
        hAccelTable = LoadAcceleratorsA(g_hInstance, APPNAMEA);
        while (0 != (bSucess = GetMessageA(&msg, (HWND) NULL, 0, 0))) 
        {
            if(bSucess == -1)
            {
                iRetValue = 1;
                goto RETURN;
            }
            if (g_hSettingsDlg == (HWND) NULL ||
                !IsDialogMessageA(g_hSettingsDlg, &msg) &&
                !TranslateAcceleratorA(g_hTextWnd, hAccelTable, &msg)) 
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
        }
    }

    iRetValue = (int)msg.wParam;

    RETURN:
    FreeStyles();
    
    return iRetValue;
}
