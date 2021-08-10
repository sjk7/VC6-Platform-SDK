//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       GLOBAL.H
//  Content:    
//              
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H


//-------------------------------------------------------
// Useful macros

#define ARRAY_ELEMENTS(rg)      (sizeof(rg) / sizeof(rg[0]))

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


VOID TraceMsg(LPTSTR ptszFormat,...);
VOID ErrorMsg(LPTSTR ptszFormat,...);
VOID WarnMsg(LPTSTR ptszFormat,...);
#define WARN_MSG   ::WarnMsg
#define ERROR_MSG  ::ErrorMsg

#define TRACE_MSG  (!gPref.fMsgTrace)   ? (void) 0 : ::TraceMsg
#define OBJECT_MSG (!gPref.fMsgObjects) ? (void) 0 : ::TraceMsg
#define NOTIFY_MSG (!gPref.fMsgNotify)  ? (void) 0 : ::TraceMsg
#define STATE_MSG  (!gPref.fMsgState)   ? (void) 0 : ::TraceMsg

#define LOGOFF 0
#define LOGON  1

VOID LogMsg(COLORREF cv, LPTSTR pszFormat,...);
#define LOG_MSG ::LogMsg

// no debug messages:
// inline void WINAPI Trace(LPCTSTR, ...) { }
// #define TRACE_MSG     1 ? (void)0 : ::TraceMsg
// #define WARN_MSG      1 ? (void)0 : ::TraceMsg
// #define ERROR_MSG     1 ? (void)0 : ::TraceMsg

#ifndef NEEDDEBUG
LPCTSTR GetHrSz(HRESULT hr);
LPCTSTR GetConfnSz(CONFN confn);
LPCTSTR GetNmchSz(ULONG uch);
LPCTSTR GetCallStateSz(NM_CALL_STATE uState);
LPCTSTR GetConferenceStateSz(NM_CONFERENCE_STATE uState);
LPCTSTR GetCollaborationStateSz(NM_SHARE_STATE uState);
VOID DumpCallInfo(INmCall * pCall);
VOID DumpAllCalls(void);
VOID DumpMemberInfo(INmMember * pMember);
VOID DumpConferenceInfo(INmConference * pConference);
VOID DumpChannelInfo(INmChannel * pChannel);
#else
#define GetHrSz(hr)       TEXT("")
#define GetConfnSz(confn) TEXT("")
#define GetNmchSz(uch)    TEXT("")
#define GetCallStateSz(uState)  TEXT("")
#define GetConferenceStateSz(uState) TEXT("")
#define DumpCallInfo(pCall);
#define DumpMemberInfo(pMember);
#define DumpConferenceInfo(pConference);
#define DumpChannelInfo(pChannel);
#endif





//-------------------------------------------------------------------------
// Functions for handling main window messages.  The message-dispatching
// mechanism expects all message-handling functions to have the following
// prototype:
//
// Function pointer prototype for message handling functions.
//     LRESULT FunctionName(HWND, UINT, WPARAM, LPARAM);

typedef LRESULT (*PFNMSG)(HWND, UINT, WPARAM, LPARAM);

// This structure maps messages to message handling functions.
typedef struct _MSD
{
	UINT   uMsg;
	PFNMSG pfnmsg;
} MSD;                 // MeSsage Dispatch structure
typedef MSD * LPMSD;


//-------------------------------------------------------------------------
// Functions for handling main window commands--ie. functions for
// processing WM_COMMAND messages based on the wParam value.
// The message-dispatching mechanism expects all command-handling
// functions to have the following prototype:

typedef VOID (*PFNCMD)(VOID);

// This structure maps command IDs to command handling functions.
typedef struct _CMD
{
	UINT     wCmd;
	PFNCMD pfncmd;
} CMD;                 // CoMmand Dispatch structure
typedef CMD * LPCMD;

//-------------------------------------------------------------------------
// Preferences
typedef struct _PREF
{ 
	BOOL    fConfirm;           // Confirm before receiving files
	BOOL    fSbar;              // Show status bar
	BOOL    fTbar;              // Show tool bar
	BOOL    fMsg;               // Show message window
	BOOL    fChat;              // Show Chat Window

	LOGFONT lf;                 // Font to use for main message window
	WINDOWPLACEMENT wpMain;
	PTCHAR  pszAddr;            // Default Address information (machine name, ip addr)
	NM_ADDR_TYPE nmAddrType;    // Address Type (pszUserAddr)

	DWORD   dwNmch;             // Allowable channel types
	PTCHAR  pszConferenceName;  // Conference Name
	PTCHAR  pszPassword;        // Conference password
	PTCHAR  pszFileName;        // File name

	int     iInit;              // Initialize option (NM_INIT_NORMAL)

	BOOL    fAutoMonitor;
	BOOL    fAutoHost;
	BOOL    fAutoCall;
	BOOL    fAutoChat;

	BOOL    fMsgTrace;
	BOOL    fMsgObjects;
	BOOL    fMsgNotify;
	BOOL    fMsgState;


	NM_CALL_TYPE nmCallType;
} PREF;


// List column information

typedef struct _tagCol {
	UINT  dwWidth;
	LPTSTR lpsz;
} COL;
typedef COL * LPCOL;

// Generic int, string array
typedef struct {
	DWORD  dw;
	LPTSTR psz;
} DWSTR;



//-------------------------------------------------------------------------
// Special resource constants
#define IDW_MSG   100
#define IDW_LVIEW 101
#define IDW_SBAR  102
#define IDW_TBAR  103
#define IDW_CHAT  104
#define IDW_SEND  105

// toolbar constants
#define NUMIMAGES       29
#define IMAGEWIDTH      16
#define IMAGEHEIGHT     16
#define BUTTONWIDTH     16
#define BUTTONHEIGHT    16

#define STATUSICONSIZE  16

// status bar parts
#define IDSBP_MSG        0
#define IDSBP_USERCOUNT  1
#define IDSBP_ICON       2

// See _rgColMember
#define ILV_NAME    0
#define ILV_VERSION 1
#define ILV_CAPS    2
#define ILV_AUDIO   3
#define ILV_FT      4
#define ILV_AS      5
#define ILV_MCU     6
#define ILV_LOCAL   7
#define ILV_ADDR    8
#define ILV_ID      9

#define DXP_SEND   60   // Width of the "Send" button
#define DYP_SEND   25   // Height of the "Send" button
#define DXP_ULIST  120  // Width of the chat user list
#define DYP_ULIST  90   // Height of the list when dropped down



//-------------------------------------------------------------------------
// Global Function Prototypes.


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

VOID DlgExit(HWND, WORD, WORD, HWND);

// from util.cpp
BOOL  GetIniBool(LPTSTR szEntry, BOOL f);
DWORD GetIniInt(LPTSTR szEntry, DWORD dwDefault);
LPTSTR GetIniStr(LPTSTR szEntry, LPTSTR szDefault);
VOID GetIniHex(LPTSTR szEntry, LPVOID lpv, int cb);
VOID WriteIniBool(LPTSTR szEntry, BOOL f);
VOID WriteIniInt(LPTSTR szEntry, DWORD dw);
VOID WriteIniStr(LPTSTR szEntry, LPTSTR sz);
VOID WriteIniHex(LPTSTR szEntry, LPVOID lpv, int cb);
VOID CenterWindow(HWND hwndChild, HWND hwndParent);
LPVOID LpvAlloc(int cb);
LPTSTR PszAlloc(int cch);
VOID FreePlpv(LPVOID plpv);
VOID UpdateHdlgIdText(HWND hdlg, int id, LPVOID lpv);
VOID UpdateHdlgIdInt(HWND hdlg, int id, LPINT lpint);
TCHAR ChFromHex(LPTSTR lpch);
VOID GetDlgItemsRc(HWND hdlg, int id1, int id2, LPRECT prc);
VOID HexToData(LPTSTR lpchSrc, LPVOID lpchDest, int cb);
VOID DataToHex(LPTSTR lpchSrc, LPTSTR lpchDest, int cb);
VOID SetMenuCheck(UINT idm, BOOL fCheck);
VOID MaybeDeleteObject(HGDIOBJ * phgdi);
int GetRadioButton(HWND hdlg, int idrFirst, int idrLast);
VOID GetDlgItemPsz(HWND hdlg, UINT id, LPTSTR *ppsz);

VOID GuidToSz(GUID * pguid, LPTSTR sz);
VOID SzToGuid(LPTSTR sz, GUID * pguid);
LPTSTR SzFindLastCh(LPTSTR lpsz, TCHAR ch);


// from rtns.cpp
VOID SizeStatus(int dxClient, int dy);
VOID SizeMsgWindow(int dx, int dy);
VOID RecalcMsgWindow(void);
VOID ShowHwnd(HWND hwnd, BOOL fShow, int idm);

// from dlg.cpp
BOOL DlgNewConference(VOID);
BOOL DlgNewCall(VOID);
BOOL DlgCallConf(VOID);
BOOL DlgSendFile(VOID);
BOOL DlgOptions(VOID);
BOOL DlgAudio(VOID);
BOOL DlgShare(VOID);
BOOL DlgLaunch(VOID);
BOOL DlgEject(VOID);
VOID InitializeUserList(HWND hwndCombo, BOOL fEveryone);
VOID DrawUserItem(LPDRAWITEMSTRUCT lpdis);
BOOL DlgLogOnOff(VOID);
BOOL DlgShowLocal(VOID);


// from init.cpp
BOOL FInitApp(LPTSTR lpszCmd, int nCmdShow);
VOID FreeAllComObjects(void);
VOID ReadPref(void);
VOID WritePref(void);

// from dlg.cpp
VOID DisplayStatus(BOOL fShow);
VOID DisplayDlg(BOOL fShow, HWND * phdlg, int id, int idm);


// from sbar.cpp
BOOL FCreateSbar(void);
VOID UpdateStatusIcon(DWORD dwId);
VOID UpdateStatusBar(LPTSTR lpsz, WORD wPart, WORD wFlags);
VOID StatusMsg(LPTSTR sz);
VOID WriteIniTbar(void);
VOID SetToolbarCheck(int idm, BOOL fCheck);


// from tbar.cpp
BOOL FCreateTbar(void);

// from cmd.cpp
VOID RecalcMsgWindow(void);
VOID ShowHwnd(HWND hwnd, BOOL fShow, int idm);
VOID OnStartup(void);

// from msg.cpp
INT MsgBoxIMbd(int iMbd);
INT MsgBoxIMbdDw(int iMbd, DWORD dw);
INT MsgBoxIMbdSz(int iMbd, LPTSTR lpsz);

// from util.cpp
VOID Log(COLORREF cv, LPTSTR lpsz);
VOID ClearLog(void);
VOID LogTestStart(LPTSTR sz);
VOID LogTestStop(LPTSTR sz);
VOID LogTestCancel(LPTSTR sz);
VOID LogResult(LPTSTR sz, DWORD dwTest, DWORD dwResult);
VOID InitDbg(void);
LPTSTR ConfErrToSz(DWORD dwError, LPTSTR sz);
BOOL FGetFileName(LPTSTR szFileName);
BOOL FGetDirectory(LPTSTR szDir);

VOID DoEnumChannelMember(INmChannel * pChannel);
VOID DoEnumConferenceMember(INmConference * pConference);
VOID DoEnumAll(void);
VOID DoEnumMemberLeak(void);
VOID DoSharableAppLeak(void);
VOID DoEnumApps(void);

BOOL IsSharingEnabled(VOID);



#define SetPropResult(hdlg, f)  SetWindowLong(GetParent(hdlg), DWL_MSGRESULT, f)

//-------------------------------------------------------------------------
// Global Variables

extern HINSTANCE ghInst;          // The current instance handle
extern HACCEL    ghAccelTable;    // Menu accelerators
extern PREF      gPref;           // User preferences
extern HWND      ghwndMain;       // Main Window
extern HMENU     ghMenu;          // Main Menu
extern HWND      ghdlgStatus;     // Modeless Status Dialog
extern HWND      ghwndSbar;       // Status bar
extern HWND      ghwndTbar;       // Toolbar
extern HWND      ghwndMsg;        // Message Window
extern HWND      ghwndLView;      // Main List View
extern HWND      ghwndChat;       // Chat Edit control
extern HWND      ghwndSend;       // Send Button
extern HWND      ghwndUList;      // User List
extern HFONT     ghfontEntry;     // Font for message Window

extern int       gdxWndMin;       // maximum width of window
extern int       gdyWndMin;       // maximum width of window

extern TCHAR gszAppName[];
extern TCHAR gszIniName[];


#endif /* GLOBAL_H */
