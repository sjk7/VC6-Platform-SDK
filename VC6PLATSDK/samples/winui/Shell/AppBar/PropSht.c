// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993 - 2000  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:     PropSheet.c
//
//  PURPOSE:    Handles retrieving application properties from the user.
//
//  PLATFORMS:  Windows 95, Windows 98, Windows 2000, Windows NT 4.0
//
//  FUNCTIONS:  
//      ShowOptions()           - Creates the property sheet
//      OptionsPageProc()       - Options page callback procedure
//      Options_OnInitDialog()  - Initialize the options page
//      Options_OnDestroy()     - Handles cleaning up the option page
//      Options_OnCommand()     - Updates the picture in response to commands
//      Options_OnNotify()      - Handles property sheet notifications      
//

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include "globals.h"
#include "resource.h"
#include "appbar.h"


//////////////////////////////////////////////////////////////////////////////
// Global variables visible only to this file

static POPTIONS pOptions;       // Appbar options used throughout the options
                                // property page.
static HWND hwndAppbar;         // Appbar window handle


//////////////////////////////////////////////////////////////////////////////
// Local Prototypes

BOOL CALLBACK OptionsPageProc(HWND hwnd, UINT uMsg, WPARAM wParam, 
                              LPARAM lParam);
void Options_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
BOOL Options_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Options_OnDestroy(HWND hwnd);
LRESULT Options_OnNotify(HWND hwnd, int idFrom, LPNMHDR pnmhdr);



//
//  FUNCTION:   ShowOptions(HWND)
//
//  PURPOSE:    Creates and displays the appbar's property sheet.
//
//  PARAMETERS:
//      hwndParent - Handle to the parent window for the prop sheet.
//

void ShowOptions(HWND hwndParent)
{
    PROPSHEETPAGE psp[2];
    PROPSHEETHEADER psh;

    // Store the window handle of the appbar so we can send it commands
    // when the options change
    hwndAppbar = hwndParent;

    // Initialize the memory
    ZeroMemory(psp, sizeof(PROPSHEETPAGE) * 2);

    // Fill out the property sheet pages
    psp[0].dwSize      = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags     = PSP_USETITLE;
    psp[0].hInstance   = g_hInstance;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_OPTIONS);
    psp[0].pszTitle    = TEXT("AppBar Options");
    psp[0].pfnDlgProc  = (DLGPROC)OptionsPageProc;
    psp[0].lParam      = (LPARAM)((POPTIONS)GetAppbarData(hwndParent));

    // Now fill out the property sheet header
    psh.dwSize = sizeof(PROPSHEETHEADER);
    psh.dwFlags = PSH_PROPSHEETPAGE | PSH_PROPTITLE;
    psh.hwndParent = hwndParent;
    psh.hInstance = g_hInstance;
    psh.pszCaption = TEXT("AppBar");
    psh.nPages = 1;
    psh.ppsp = psp;

    // Finally display the property sheet
    PropertySheet(&psh);
    return;
}


//
//  FUNCTION:   OptionsPageProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:    Dispatches messages for the options property page.
//

BOOL CALLBACK OptionsPageProc(HWND hwnd, UINT uMsg, WPARAM wParam, 
                              LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            return (BOOL)HANDLE_WM_INITDIALOG(hwnd, wParam, 
                                              lParam, Options_OnInitDialog);

        case WM_COMMAND:
            HANDLE_WM_COMMAND(hwnd, wParam, lParam, 
                              Options_OnCommand);
            return (TRUE);

        case WM_DESTROY:
            HANDLE_WM_DESTROY(hwnd, wParam, lParam, 
                              Options_OnDestroy);
            return (TRUE);
            
        case WM_NOTIFY:
            HANDLE_WM_NOTIFY(hwnd, wParam, lParam, Options_OnNotify);
            return (TRUE);

    }          

    return (0);
}


//
//  FUNCTION:   Options_OnInitDialog(HWND, HWND, LPARAM)
//
//  PURPOSE:    Handles initialization of the property page.
//
//  PARAMETERS:
//      hwnd      - Handle of the property page window.
//      hwndFocus - Child window that will receive focus if the function
//                  returns TRUE.
//      lParam    - Will contain a pointer to the appbar OPTIONS struct.
//
//  RETURN VALUE:
//      Returns TRUE to set the focus to the child window contained in the
//      hwndFocus parameter.  Returns FALSE to set the focus ourselves.
//

BOOL Options_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    PROPSHEETPAGE *ppsp;
    RECT rc;
    HBITMAP hbmpBase;
    HBITMAP hbmpAppbar;
    HBITMAP hbmpWindow;
    APPBARDATA abd;
    HWND hwndAutohide;

    // Get the pointer to the OPTIONS struct from the lParam
    ppsp = (PROPSHEETPAGE *)lParam;
    pOptions = (POPTIONS)ppsp->lParam;

    // Load and set the picture for the base image
    hbmpBase = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BASE));
    if (!hbmpBase)
    {
        ErrorHandler();
        EndDialog(hwnd, 0);
    }

    SendDlgItemMessage(hwnd, IDC_PICTURE, STM_SETIMAGE, IMAGE_BITMAP, 
                       (LPARAM) hbmpBase);
    
    // Set the pictures for the rest of the static controls, move them
    // into position, and hide them
    hbmpAppbar = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_APPBAR));
    hbmpWindow = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_WINDOW));
    if (!hbmpAppbar || !hbmpWindow)
    {
        ErrorHandler();
        EndDialog(hwnd, 0);
    }

    SendDlgItemMessage(hwnd, IDC_APPBAR, STM_SETIMAGE, IMAGE_BITMAP, 
                       (LPARAM) hbmpAppbar);
    SendDlgItemMessage(hwnd, IDC_WINDOW, STM_SETIMAGE, IMAGE_BITMAP, 
                       (LPARAM) hbmpWindow);

    // Get the position of the picture and convert to client coordiates
    GetWindowRect(GetDlgItem(hwnd, IDC_PICTURE), &rc);
    ScreenToClient(hwnd, (LPPOINT)&rc);

    SetWindowPos(GetDlgItem(hwnd, IDC_APPBAR), GetDlgItem(hwnd, IDC_PICTURE),
                 rc.left + 2, rc.top + 69, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);

    SetWindowPos(GetDlgItem(hwnd, IDC_WINDOW), GetDlgItem(hwnd, IDC_APPBAR),
                 rc.left + 212, rc.top + 69, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE);

    // Set the values of the controls based on the values in OPTIONS
    Button_SetCheck(GetDlgItem(hwnd, IDC_AUTOHIDE), pOptions->fAutoHide);
    Button_SetCheck(GetDlgItem(hwnd, IDC_ONTOP), pOptions->fOnTop);

    if (pOptions->fAutoHide)
        ShowWindow(GetDlgItem(hwnd, IDC_APPBAR), SW_HIDE);
    if (pOptions->fOnTop)
        ShowWindow(GetDlgItem(hwnd, IDC_WINDOW), SW_HIDE); 
        
    // Check the autohide window for this side.  Since only one appbar can be 
    // auto hidden on each side of the screen, we should disable this check box
    // if we can't autohide.
    abd.cbSize = sizeof(APPBARDATA);
    abd.hWnd = hwndAppbar;
    abd.uEdge = pOptions->uSide;
    
    hwndAutohide = (HWND) SHAppBarMessage(ABM_GETAUTOHIDEBAR, &abd);
    if ((hwndAutohide != NULL) && (hwndAutohide != hwndAppbar))
        EnableWindow(GetDlgItem(hwnd, IDC_AUTOHIDE), FALSE);

    return (FALSE);
}


//
//  FUNCTION:   Options_OnCommand(HWND, int, HWND, UINT)
//
//  PURPOSE:    Handles the command messages for the options page.
//
//  PARAMETERS:
//      hwnd        - handle of the window receiving the message
//      id          - identifier of the command
//      hwndCtl     - handle of the control sending the message)
//      codeNotify  - specifies the notification code if the message is from
//                    a control
//
//  COMMENTS:
//      codeNotify is 1 if from an accelerator, 0 if from a menu.
//      If the message is not from a control hwndCtl is NULL.
//

void Options_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
        case IDC_AUTOHIDE:
            // First let the property sheet know somethings changed
            PropSheet_Changed(GetParent(hwnd), hwnd);

            // Now update the picture
            if (Button_GetCheck(hwndCtl))
                ShowWindow(GetDlgItem(hwnd, IDC_APPBAR), SW_HIDE);
            else
                ShowWindow(GetDlgItem(hwnd, IDC_APPBAR), SW_SHOW);
            
            break;
            
        case IDC_ONTOP:
            // First let the property sheet know somethings changed
            PropSheet_Changed(GetParent(hwnd), hwnd);

            // Now update the picture
            if (Button_GetCheck(hwndCtl))
                ShowWindow(GetDlgItem(hwnd, IDC_WINDOW), SW_HIDE);
            else
                ShowWindow(GetDlgItem(hwnd, IDC_WINDOW), SW_SHOW);
            
            break;
    }
}


//
//  FUNCTION:   Options_OnDestroy(HWND)
//
//  PURPOSE:    Clean up the GDI objects we created in the OnInitDialog.
//
//  PARAMETERS:
//      hwnd    - Handle of the options property page.
//

void Options_OnDestroy(HWND hwnd)
{
    HBITMAP hbmp;

    hbmp = (HBITMAP) SendDlgItemMessage(hwnd, IDC_PICTURE, STM_GETIMAGE, 
                                        IMAGE_BITMAP, 0L);
    if (hbmp)
        DeleteObject(hbmp);

    hbmp = (HBITMAP) SendDlgItemMessage(hwnd, IDC_APPBAR, STM_GETIMAGE, 
                                        IMAGE_BITMAP, 0L);
    if (hbmp)
        DeleteObject(hbmp);

    hbmp = (HBITMAP) SendDlgItemMessage(hwnd, IDC_WINDOW, STM_GETIMAGE, 
                                        IMAGE_BITMAP, 0L);
    if (hbmp)
        DeleteObject(hbmp);                             
}


//
//  FUNCTION:   Options_OnNotify(HWND, int, LPNMHDR)
//
//  PURPOSE:    Handles updating the appbar states when the user either presses
//              the "Apply" button or the "OK" button.
//
//  PARAMETERS:
//      hwnd    - handle of the window receiving the notification
//      idCtl   - identifies the control sending the notification
//      pnmh    - points to a NMHDR struct with more inforamation regarding the
//                notification
//
//  RETURN VALUE:
//      Always zero.
//

LRESULT Options_OnNotify(HWND hwnd, int idFrom, LPNMHDR pnmhdr)
{              
    BOOL fCheck;

    switch (pnmhdr->code)
    {
        case PSN_APPLY:
            // Check to see if the options have changed.  If so, send 
            // the appropriate command to the appbar
            fCheck = (BOOL) Button_GetCheck(GetDlgItem(hwnd, IDC_AUTOHIDE));
            if (pOptions->fAutoHide != fCheck)
            {
                if (AppBar_SetAutoHide(hwndAppbar, fCheck))
                    pOptions->fAutoHide = fCheck;
            }

            // If the Always-On-Top setting has changed update the appbar state
            fCheck = (BOOL) Button_GetCheck(GetDlgItem(hwnd, IDC_ONTOP));
            if (pOptions->fOnTop != fCheck)
            {
                pOptions->fOnTop = fCheck;
                AppBar_SetAlwaysOnTop(hwndAppbar, fCheck);
            }

            SetDlgMsgResult(hwnd, WM_NOTIFY, PSNRET_NOERROR);
            break;
    }

    return (0);
}
    
    
