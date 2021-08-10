//****************************************************************************
//  Module:     NMFT.EXE
//  File:       UTIL.CPP
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


static TCHAR _szFilter[] = TEXT("All Files\0*.*\0Text Files (*.txt)\0*.TXT\0");
static TCHAR _szPickMsg[] = TEXT("Select a file to send");


//****************************************************************************
//
// BOOL FGetFileName(LPTSTR szFileName)
//
//****************************************************************************

BOOL FGetFileName(LPTSTR szFileName)
{
	OPENFILENAME ofn;

	if	(NULL == szFileName)
		return FALSE;

	szFileName[0] = 0;

	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize   = sizeof(OPENFILENAME);
	ofn.hwndOwner     = ghwndMain;
	ofn.hInstance     = (HINSTANCE) ghInst;
	ofn.lpstrFilter   = _szFilter;
	ofn.nFilterIndex  = 1L;
	ofn.lpstrFile     = szFileName;
	ofn.nMaxFile      = MAX_PATH; // really max characters for szFileName
	ofn.lpstrTitle    = _szPickMsg;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;

	return GetOpenFileName(&ofn);
}


//****************************************************************************
//
// BOOL FFileExists(LPCTSTR szFile)
//
//****************************************************************************

BOOL FFileExists(LPCTSTR szFile)
{
	HANDLE hFile	= 0;

	if ((NULL == szFile) || (_T('\0') == *szFile))
		return FALSE;

	UINT uErrorMode = SetErrorMode(SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS);
	hFile = CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetErrorMode(uErrorMode); // Restore error mode

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	CloseHandle(hFile);
	return TRUE;
}


//****************************************************************************
//
// LPVOID LpvAlloc(int cb)
//
// Return a pointer to an allocated array of bytes
//
//****************************************************************************

LPVOID LpvAlloc(int cb)
{
	return LocalAlloc(LMEM_FIXED, cb);
}


//****************************************************************************
//
// LPTSTR PszAlloc(int cch)
//
//****************************************************************************

LPTSTR PszAlloc(int cch)
{
	return (LPTSTR) LocalAlloc(LMEM_FIXED, sizeof(TCHAR) * (cch+1));
}


//****************************************************************************
//
// VOID FreePlpv(LPVOID plpv)
//
// Free the data pointed to by plpv and set *plpv to NULL
//
//****************************************************************************

VOID FreePlpv(LPVOID plpv)
{
	if ((plpv == NULL) || (*(VOID FAR * FAR *)plpv == NULL)) {
		return;
	}

	LocalFree(*(VOID FAR * FAR *)plpv);
	*(VOID FAR * FAR *)plpv = NULL;
}


//****************************************************************************
//
// LPCTSTR StrChr(LPCTSTR pcsz, TCHAR ch)
//
//****************************************************************************

LPCTSTR StrChr(LPCTSTR pcsz, TCHAR ch)
{
    LPCTSTR pcszFound = NULL;

    if (pcsz)
    {
        while (*pcsz)
        {
            if (*pcsz == ch)
            {
                pcszFound = pcsz;
                break;
            }

            pcsz = CharNext(pcsz);
        }
    }

    return pcszFound;
}

