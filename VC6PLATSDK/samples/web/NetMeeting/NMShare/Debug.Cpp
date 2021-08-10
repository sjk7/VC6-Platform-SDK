//****************************************************************************
//  Module:     NMSHARE.EXE     
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

VOID FAR PASCAL AssertProc(LPSTR lpszMsg, LPSTR lpszAssert, LPSTR lpszFile, UINT line)
{
	int  id;

	TCHAR szBuffer[1025];
	ZeroMemory(szBuffer,1025 * sizeof(TCHAR));
	_sntprintf(szBuffer,1024,TEXT("Assert: %s\nFile %s, Line %d"),
		(lpszMsg && *lpszMsg) ? lpszMsg  : lpszAssert,
		lpszFile ? lpszFile : "", line);
	

	OutputDebugString(szBuffer);

	do {
		id = MessageBox(NULL, (LPSTR)szBuffer, TEXT("NmChat Assert"),
					MB_ICONHAND | MB_ABORTRETRYIGNORE | MB_SYSTEMMODAL);

		switch (id)
		{
			case IDRETRY:
				DebugBreak();
				break;
			case IDABORT:
				FatalAppExit(0, (LPSTR)szBuffer);
				break;
			case IDIGNORE:
			default:
				break;
		}
	} while (id == IDRETRY);
}



#endif /* DEBUG - the whole file! */

