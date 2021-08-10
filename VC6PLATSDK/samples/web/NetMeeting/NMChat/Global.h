//****************************************************************************
//  Module:     NMCHAT.EXE
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

// #define NM2_CHAT_PROTOCOL  // Define this to use the NM 2.0 chat protocol
#ifdef NM2_CHAT_PROTOCOL
#define CB_NM2_HDR   8     // NetMeeting 2.0 chat protocol has an 8 byte header
#endif


//-------------------------------------------------------
// Useful constants

#define chNull   ('\0')
#define lpNil    (NULL)

#define hwndNil      ((HWND) NULL)
#define hfontNil     ((HFONT) NULL)
#define hgdiNil      ((HGDIOBJ) NULL)


//-------------------------------------------------------
// Useful macros

#define ClearStruct(lpv)		ZeroMemory((LPVOID) (lpv), sizeof(*(lpv)))
#define InitStruct(lpv)        {ClearStruct(lpv); (* (LPDWORD) lpv) = sizeof(*(lpv));}

#define SetEmptySz(sz)			( *(sz) = _T('\0') )
#define FEmptySz(sz)            (((sz) == NULL) || (*(sz) == _T('\0')))

#define ARRAY_ELEMENTS(rg)      (sizeof(rg) / sizeof(rg[0]))
#define CCHMAX(sz)              (sizeof(sz) / sizeof(TCHAR))


#ifdef DEBUG
VOID FAR PASCAL AssertProc(LPTSTR lpszMsg, LPTSTR lpszAssert, LPTSTR lpszFile, UINT line);

#define DEBASSERT(exp,szMsg)  \
	if (!(exp))                                                      \
	{                                                                \
		static char _szAssert[] = #exp ;   \
		static char _szMsg[]    = szMsg;   \
		AssertProc(_szMsg,_szAssert,__FILE__,__LINE__); \
	}

#define ASSERT(f)       DEBASSERT(f, "(" #f ")")
#define AssertSz(f,sz)  DEBASSERT(f, sz)
#define NotReached()    DEBASSERT(FALSE, "NotReached declaration was reached!")
#else
#define ASSERT(f)
#define AssertSz(f, sz)
#define NotReached()
#endif


//****************************************************************************
//
// Functions for handling main window messages.  The message-dispatching
// mechanism expects all message-handling functions to have the following
// prototype:
//
// Function pointer prototype for message handling functions:
// LRESULT FunctionName(HWND, UINT, WPARAM, LPARAM);
//
//****************************************************************************



typedef LRESULT (*PFNMSG)(HWND, UINT, WPARAM, LPARAM);

// This structure maps messages to message handling functions.
typedef struct _MSD
{
	UINT   uMsg;
	PFNMSG pfnmsg;
} MSD;                 // MeSsage Dispatch structure
typedef MSD * LPMSD;


//****************************************************************************
//
// Functions for handling main window commands--ie. functions for
// processing WM_COMMAND messages based on the wParam value.
// The message-dispatching mechanism expects all command-handling
// functions to have the following prototype:
//
//****************************************************************************

typedef VOID (*PFNCMD)(VOID);

// This structure maps command IDs to command handling functions.
typedef struct _CMD
{
	UINT     wCmd;
	PFNCMD pfncmd;
} CMD;                 // CoMmand Dispatch structure
typedef CMD * LPCMD;


//****************************************************************************
//
// Special resource constants
//
//****************************************************************************

#define IDW_MSG   100
#define IDW_USER  101
#define IDW_EDIT  102

// See _rgColMember
#define ILV_NAME    0
#define ILV_TIME    1
#define ILV_TEXT    2

const int DYP_EDIT   = 30;  // Fixed Height of Edit control
const int DXP_USER   = 80;  // Fixed Width of User List
const int YP_TOP     = 3;
const int XP_LEFT    = 0;


//****************************************************************************
//
// Global Function Prototypes.
//
//****************************************************************************

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


// from util.cpp
LPVOID LpvAlloc(int cb);
LPTSTR PszAlloc(int cch);
VOID FreePlpv(LPVOID plpv);
VOID MaybeDeleteObject(HGDIOBJ * phgdi);
VOID SizeMsgWindow(int dx, int dy);
VOID RecalcMsgWindow(void);

VOID SendText(void);
VOID ClearText(void);
VOID DisplayMsg(LPTSTR pszMsg, INmMember * pMember);
VOID DisplaySysMsg(LPTSTR pszMsg, INmMember * pMember);
VOID DisplayMessage(LPTSTR pszMsg, LPTSTR pszUser);


//****************************************************************************
//
// Global Variables
//
//****************************************************************************

extern HINSTANCE ghInst;          // The current instance handle
extern HACCEL    ghAccelTable;    // Menu accelerators
extern HWND      ghwndMain;       // Main Window
extern HMENU     ghMenu;          // Main Menu
extern HWND      ghwndMsg;        // Message Window
extern HWND      ghwndUser;       // User List
extern HWND      ghwndEdit;       // Edit control
extern HFONT     ghfontEntry;     // Font for message Window

extern const GUID g_guidApp;      // Our NmChat Guid
extern const GUID g_guidNM2Chat;  // NM 2.0 Chat guid

#endif /* GLOBAL_H */
