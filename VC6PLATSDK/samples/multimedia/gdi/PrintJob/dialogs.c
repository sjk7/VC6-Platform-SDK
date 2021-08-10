/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
*  PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   Dialogs.c
* 
*   PURPOSE:    Implements Dialog functions and exported callbacks
* 
*   FUNCTIONS:  
*       GetPrinterPath () - Asks user to type in the name of a printer.
*       GetPrinterDlgProc () - Dialog Procedure for the GetPrinterPath Dialog.
*       About () - Dialog Procedure for the About Dialog.
* 
******************************************************************************/


#define STRICT
#include <windows.h>    /* required for all Windows applications */
#include "resource.h"   /* Windows resource IDs */
#include "PrintJob.h"   /* For the application's window management functions */
#include "Dialogs.h"    /* Prototypes specific to this module */


/* 
 * Application globals 
 */
extern HINSTANCE g_hInst;          /* current instance of application*/


/* 
 * Convenience structure to pass a pre-allocated string buffer to/from a dialog 
 * This gives the dialog procedure the size of the allocated buffer so it can
 * ensure it does not write off the end of the buffer.
 */
typedef struct _stringstruct
{
    char *pszStr;       /* pointer to the buffer */
    short cSize;        /* size of the buffer */
} STRSIZE;


/******************************************************************************

  FUNCTION: GetPrinterDlgProc(HWND, UINT, WPARAM, LPARAM)

  PURPOSE:
    Message processing for the "Select Printer" dialog box.

  MESSSAGES:
    WM_INITDIALOG - initialize dialog box storing a pointer to a STRSIZE 
                    structure passed via LPARAM.
    WM_COMMAND    - processes the following commands:
        IDOK        
        IDCANCEL

  RETURNS:
    TRUE if message processed.
    FALSE if message not processed.


******************************************************************************/
LRESULT CALLBACK GetPrinterDlgProc(
                HWND hDlg,           /* window handle of the dialog box */
                UINT message,        /* type of message */
                WPARAM uParam,       /* message-specific information */
                LPARAM lParam)       /* "       "          " */
{
static  STRSIZE *pDlgParam;  /* keep the dialog's parameters around */

    switch (message) 
    {
        case WM_INITDIALOG:  /* message: initialize dialog box*/
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

            pDlgParam = (STRSIZE *)lParam;
            SetDlgItemText(hDlg, IDC_EDITSELECTPRINTER, pDlgParam->pszStr);

            return (TRUE);

        case WM_COMMAND:
            switch (LOWORD(uParam))
            {
                case IDOK:              /* "OK" button selected? */
                    GetDlgItemText(hDlg, IDC_EDITSELECTPRINTER, pDlgParam->pszStr, pDlgParam->cSize);
                    EndDialog(hDlg, TRUE);
                    return TRUE;

                case IDCANCEL:          /* Exit the dialog */
                    EndDialog(hDlg, FALSE);        
                    return (TRUE);
            }
            break;
    }
    return (FALSE); /* Didn't process the message */

} /* end of function GetPrinterDialogProc */


/******************************************************************************

  FUNCTION: GetPrinterPath

  PURPOSE:
    GetPrinterPath Displays a dialog box which asks a user for the name of a
    printer. Any string typed by the user is valid. 

  PARAMETERS:
    hWnd        - Handle of the window to own this dialog. Typically the main
                  application window.

    pszPrinter  - pointer to a character buffer in which to store the name of
                  the printer.
    cStrSize    - the size of the buffer pointed to by pszPrinter.

  RETURNS:
    TRUE if the user clicks the OK button.
    FALSE if the user cancels the Dialog.


******************************************************************************/
BOOL GetPrinterPath(
                HWND hWnd,          /* window handle to main window */
                char *pszPrinter,   /* string in which to store user's printer */
                short cchStrSize)     /* size of string */
{
    STRSIZE dlgParameters = {0};
	dlgParameters.pszStr = pszPrinter;
	dlgParameters.cSize = cchStrSize;

    return	(BOOL)	DialogBoxParam(g_hInst,              /* current instance of app */
					MAKEINTRESOURCE(IDD_SELECTPRINTER), /* dialog template */
					hWnd,                               /* parent of the dialog */
					(DLGPROC)GetPrinterDlgProc,         /* dialog procedure */
					(LPARAM)&dlgParameters);            /* the string for the printer's name */

} /* end of function GetPrinterPath */


/****************************************************************************

    FUNCTION: About(HWND, UINT, WPARAM, LPARAM)

    PURPOSE:  Processes messages for "About" dialog box

    MESSAGES:

        WM_INITDIALOG - initialize dialog box
        WM_COMMAND    - Input received

    COMMENTS:

        Display version information from the version section of the
        application resource.

        Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

LRESULT CALLBACK About(
                HWND hDlg,           // window handle of the dialog box
                UINT message,        // type of message
                WPARAM uParam,       // message-specific information
                LPARAM lParam)
{
    static  HFONT hfontDlg;
    LPSTR   lpVersion;
    DWORD   dwVerInfoSize;
    DWORD   dwVerHnd;
    UINT    uVersionLen;
    int     iRootLen;
    BOOL    bRetCode;
    int     i;
    char    szFullPath[256];
    char    szResult[256];
    char    szGetName[256];

    switch (message) {
        case WM_INITDIALOG:  // message: initialize dialog box
            // Center the dialog over the application window
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

            // Get version information from the application
            GetModuleFileName (g_hInst, szFullPath, sizeof(szFullPath));
            dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
            if (dwVerInfoSize) {
                    // If we were able to get the information, process it:
                    LPSTR   lpstrVffInfo;
                    HANDLE  hMem;
                    hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
                    lpstrVffInfo  = GlobalLock(hMem);
                    GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
                    lstrcpyn(szGetName, "\\StringFileInfo\\040904e4\\", 256);
                    iRootLen = lstrlen(szGetName);

                    // Walk through the dialog items that we want to replace:
                    for (i = IDC_FILEDESCRIPTION; i <= IDC_LEGALTRADEMARKS; i++) {
                            GetDlgItemText(hDlg, i, szResult, sizeof(szResult));
                            szGetName[iRootLen] = (char)0;
                            strncat (szGetName, szResult, 256 - strlen(szGetName));
                            uVersionLen   = 0;
                            lpVersion     = NULL;
                            bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
                                    (LPSTR)szGetName,
                                    (LPVOID)&lpVersion,
                                     &uVersionLen);

                            if ( bRetCode && uVersionLen && lpVersion) {
                                    // Replace dialog item text with version info
                                    lstrcpyn(szResult, lpVersion, 256);
                                    SetDlgItemText(hDlg, i, szResult);
                            }
                    }

                    GlobalUnlock(hMem);
                    GlobalFree(hMem);
            } // if (dwVerInfoSize)
            // Create a font to use
            hfontDlg = CreateFont(12, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0,
                    VARIABLE_PITCH | FF_SWISS, "");

            // Walk through the dialog items and change font
            for (i = IDC_FILEDESCRIPTION; i <= IDC_LEGALTRADEMARKS; i++)
                SendMessage (GetDlgItem (hDlg, i), WM_SETFONT, (WPARAM)hfontDlg, TRUE);

            return (TRUE);

        case WM_COMMAND:                      // message: received a command
            if (LOWORD(uParam) == IDOK        // "OK" box selected?
            || LOWORD(uParam) == IDCANCEL) {  // System menu close command?
                    EndDialog(hDlg, TRUE);        // Exit the dialog
                    DeleteObject (hfontDlg);
                    return (TRUE);
            }
            break;
    }
    return (FALSE); // Didn't process the message

    lParam; // This will prevent 'unused formal parameter' warnings

} /* end of function About */


/* end of source file Dialogs.c */
