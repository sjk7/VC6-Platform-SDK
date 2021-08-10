//****************************************************************************
//  Module:     NMFT.EXE
//  File:       GLOBAL.H
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

#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef DEBUG
VOID FAR PASCAL AssertProc(LPTSTR lpszMsg, LPTSTR lpszAssert, LPTSTR lpszFile, UINT line);

#define DEBASSERT(exp,szMsg)  \
	if (!(exp))                                                      \
	{                                                                \
		static TCHAR _szAssert[] = TEXT(#exp) ;   \
		static TCHAR _szMsg[]    = szMsg;   \
		AssertProc(_szMsg,_szAssert,TEXT(__FILE__),__LINE__); \
	}

#define ASSERT(f)       DEBASSERT(f, TEXT("(") TEXT(#f) TEXT(")"))
#define AssertSz(f,sz)  DEBASSERT(f, sz)
#define NotReached()    DEBASSERT(FALSE, TEXT("NotReached declaration was reached!"))
#else
#define ASSERT(f)
#define AssertSz(f, sz)
#define NotReached()
#endif



//****************************************************************************
//
// Global Function Prototypes.
//
//****************************************************************************

// from msg.cpp
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID CmdClose(void);

// from util.cpp
BOOL FGetFileName(LPTSTR szFileName);
BOOL FFileExists(LPCTSTR szFile);
LPVOID LpvAlloc(int cb);
LPTSTR PszAlloc(int cch);
VOID FreePlpv(LPVOID plpv);
LPCTSTR StrChr(LPCTSTR pcsz, TCHAR ch);


//****************************************************************************
//
// Global variables.
//
//****************************************************************************

extern HINSTANCE ghInst;          // The current instance handle
extern HWND   ghwndMain;          // Main Window
extern const GUID g_guidApp;      // Our NmFt Guid
extern TCHAR  g_szFile[MAX_PATH + 1]; //
extern BOOL   g_fQuiet;           // if TRUE, no progress dialog

#endif /* GLOBAL_H */
