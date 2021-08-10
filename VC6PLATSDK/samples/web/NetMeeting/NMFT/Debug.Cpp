//****************************************************************************
//  Module:     NMFT.EXE
//  File:       DEBUG.CPP
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1997-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#include "precomp.h"


#ifdef DEBUG /* The whole file! */


//****************************************************************************
//
// VOID FAR PASCAL AssertProc(LPSTR lpszMsg, LPSTR lpszAssert, LPSTR lpszFile, UINT line)
//
//****************************************************************************

VOID FAR PASCAL AssertProc(LPTSTR lpszMsg, LPTSTR lpszAssert, LPTSTR lpszFile, UINT line)
{
	int  id	= 0;
	TCHAR szBuffer[1024]; // a big buffer

	ZeroMemory(szBuffer, 1024);

	_sntprintf(szBuffer, 1023, TEXT("Assert: %s\nFile %s, Line %d"),
		(lpszMsg && *lpszMsg) ? lpszMsg : lpszAssert,
		lpszFile ? lpszFile : TEXT(""), line);

	OutputDebugString(szBuffer);

	do {
		id = MessageBox(NULL, szBuffer, TEXT("NmUi Assert"),
					MB_ICONHAND | MB_ABORTRETRYIGNORE | MB_SYSTEMMODAL);

		switch (id)
		{
		case IDRETRY:
			DebugBreak();
			break;
		case IDABORT:
			FatalAppExit(0, szBuffer);
			break;
		case IDIGNORE:
		default:
			break;
		}
	} while (id == IDRETRY);
}



#endif /* DEBUG - the whole file! */

