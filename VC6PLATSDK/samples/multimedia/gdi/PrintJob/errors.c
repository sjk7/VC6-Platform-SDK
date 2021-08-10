/******************************************************************************
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
* PARTICULAR PURPOSE.
* 
*  Copyright (C) 1999 - 2000  Microsoft Corporation.  All Rights Reserved.
* 
*   FILE:   Errors.C
* 
*   PURPOSE:    Implements an Error display box that conveniently shows
*       the user what Win32 Error was reported.
* 
*   FUNCTIONS:  
*       ErrorBox() - Displays a MessageBox() with a formatted version of
*                    the Win32 Error code passed in.
* 
******************************************************************************/

#define STRICT
#include <Windows.h>
#include "Errors.h"


/******************************************************************************

  FUNCTION: ErrorBox( DWORD, LPCSTR )

  PURPOSE:  Shows a Message Box withe a formatted string for the Win32
            error passed via DWORD. 

  COMMENTS:
            LPCSTR is the title of the Message Box().
            The MessageBox() contains a single OK button.

******************************************************************************/

void ErrorBox( DWORD dwError, LPCSTR lpszString )
{
#define MAX_MSG_BUF_SIZE 512
    char    *msgBuf;
    DWORD   cMsgLen;

    cMsgLen = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_ALLOCATE_BUFFER | 40,
                NULL, dwError,
                MAKELANGID(0, SUBLANG_ENGLISH_US),
                (LPTSTR) &msgBuf, MAX_MSG_BUF_SIZE,
                NULL);

    MessageBox( NULL, msgBuf, lpszString, MB_OK );

    LocalFree( msgBuf );
#undef MAX_MSG_BUF_SIZE
}

/* end of source file Errors.c */
