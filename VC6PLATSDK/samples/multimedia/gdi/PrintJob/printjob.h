/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
*  PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   PrintJob.H
* 
*   PURPOSE:    Declares exported functions and exported callbacks
*	            See PrintJob.C for general comments
* 
******************************************************************************/



/* windows callbacks */

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/* window management */

BOOL    CenterWindow (HWND hwndChild, HWND hwndParent);


/* end of header file PrintJob.H */