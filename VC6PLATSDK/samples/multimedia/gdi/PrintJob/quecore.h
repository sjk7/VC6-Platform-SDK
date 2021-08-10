/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   QueCore.H
* 
*   PURPOSE:    Declares the core set of printer queue manipulation routines.
* 
*   COMMENTS:   These functions are located in PrintJob.C
*
*   FUNCTIONS:  
*       MakeJobStatusStr () - Converts status bits in dwStatus into a string.
*       Refresh() - Updates data structures and App window for the pQueue.
*       RefreshFromNotification() - Updates the data and App Window given the
*               pNotification.
*       UpdateWindowTitle() - Sets the Window title appropriately from the pPd.
* 
******************************************************************************/

/* helper funcitons */

void    MakeJobStatusStr(char *szBuffer, short cchChars, DWORD dwStatus);

/* operations on printer queue data */

void    Refresh(HWND hWnd, QUEUEDATA *pQueue);
BOOL    RefreshFromNotification(HWND hWnd, QUEUEDATA *pQueue, PRINTER_NOTIFY_INFO *pNotification);
void    UpdateWindowTitle(HWND hWnd, QUEUEDATA *pPd);

/* end of header file QueCore.h */
