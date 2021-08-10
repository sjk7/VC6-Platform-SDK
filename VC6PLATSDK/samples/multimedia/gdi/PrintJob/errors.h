/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   Errors.H
* 
*   PURPOSE:    Implements an Error display box that conveniently shows
*       the user what Win32 Error was reported.
* 
*   FUNCTIONS:  
*       ErrorBox() - Displays a MessageBox() with a formatted version of
*                    the Win32 Error code passed in. Handy, but not 
*                    terribly user friendly.
* 
******************************************************************************/

void ErrorBox( DWORD dwError, LPCSTR lpszString );

/* end of header file Errors.h */

