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
*   PURPOSE:    Declares Dialog functions and exported callbacks
* 
*   FUNCTIONS:  
*       GetPrinterPath () - Asks user to type in the name of a printer.
*       GetPrinterDlgProc () - Dialog Procedure for the GetPrinterPath Dialog.
*       About () - Dialog Procedure for the About Dialog.
* 
******************************************************************************/


BOOL    GetPrinterPath(
                HWND hWnd,          /* window handle of application window */
                char *pszPrinter,   /* pointer to buffer for the printer name */
                short cchStrSize);  /* size of pszPrinter in characters */

LRESULT CALLBACK GetPrinterDlgProc(
                HWND hDlg,           /* window handle of the dialog box */
                UINT message,        /* type of message */
                WPARAM uParam,       /* message-specific information */
                LPARAM lParam);      /* "       "          " */

LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);

/* end of header file Dialogs.h */