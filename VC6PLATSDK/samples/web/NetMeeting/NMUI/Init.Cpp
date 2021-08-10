//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       INIT.CPP
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

#include "precomp.h"

// string constants (no change for international)

TCHAR gszAppClassName[] = TEXT("NMUI");
TCHAR gszAppName[]      = TEXT("NmUi");
TCHAR gszIniName[]      = TEXT("NmUi.ini");

// Section Names
TCHAR gszMainWnd[]  = TEXT("MainWnd");
TCHAR gszSbar[]     = TEXT("SBar");
TCHAR gszTbar[]     = TEXT("TBar");
TCHAR gszChat[]     = TEXT("Chat");
TCHAR gszMsg[]      = TEXT("Messages");
TCHAR gszMsgFont[]  = TEXT("Message Font");
TCHAR gszAddr[]     = TEXT("Addr");
TCHAR gszAddrType[] = TEXT("AddrType");
TCHAR gszConferenceName[] = TEXT("Conference Name");
TCHAR gszFileName[] = TEXT("Filename");

TCHAR gszIniCallType[] = TEXT("CallType");

TCHAR gszIniAutoMonitor[] = TEXT("AutoMonitor");
TCHAR gszIniAutoHost[]    = TEXT("AutoHost");
TCHAR gszIniAutoCall[]    = TEXT("AutoCall");
TCHAR gszIniAutoChat[]    = TEXT("AutoChat");

TCHAR gszIniInit[]        = TEXT("Init");

TCHAR gszIniMsgTrace[]    = TEXT("Trace Msgs");
TCHAR gszIniMsgObjects[]  = TEXT("Object Msgs");
TCHAR gszIniMsgNotify[]   = TEXT("Notify Msgs");
TCHAR gszIniMsgState[]    = TEXT("State change Msgs");

// See ILV_*
static COL _rgColMember[] = {
	{80, TEXT("Name")},
	{40, TEXT("Ver")},
	{60, TEXT("Caps")},
	{60, TEXT("Audio")},
	{60, TEXT("Ft")},
	{90, TEXT("App Sharing")},
	{40, TEXT("MCU")},
	{40, TEXT("Local")},
	{80, TEXT("IP Addr")},
	{80, TEXT("ID")},
};


//****************************************************************************
//
// VOID ReadPref(void)
//
// Reads the current preferences from the NmUi.ini file.
//
//****************************************************************************

VOID ReadPref(void)
{
	ZeroMemory(&gPref, sizeof(PREF));

	gPref.fSbar       = GetIniBool(gszSbar, TRUE);
	gPref.fTbar       = GetIniBool(gszTbar, TRUE);
	gPref.fMsg        = GetIniBool(gszMsg, TRUE);
	gPref.fChat       = GetIniBool(gszChat, TRUE);

	gPref.pszConferenceName = GetIniStr(gszConferenceName, TEXT("NmUi Conference"));
	
	gPref.pszAddr    = GetIniStr(gszAddr, TEXT("User 1"));
	gPref.nmAddrType = (NM_ADDR_TYPE) GetIniInt(gszAddrType, NM_ADDR_UNKNOWN);
	gPref.nmCallType = (NM_CALL_TYPE) GetIniInt(gszIniCallType, (int) NM_CALL_DEFAULT);
	
	GetIniHex(gszMainWnd, &gPref.wpMain, sizeof(WINDOWPLACEMENT));
	GetIniHex(gszMsgFont, &gPref.lf, sizeof(LOGFONT));

	gPref.fAutoMonitor= GetIniBool(gszIniAutoMonitor, FALSE);
	gPref.fAutoHost   = GetIniBool(gszIniAutoHost, FALSE);
	gPref.fAutoCall   = GetIniBool(gszIniAutoCall, FALSE);
	gPref.fAutoChat   = GetIniBool(gszIniAutoChat, FALSE);

	gPref.fMsgTrace   = GetIniBool(gszIniMsgTrace, TRUE);
	gPref.fMsgObjects = GetIniBool(gszIniMsgObjects, FALSE);
	gPref.fMsgNotify  = GetIniBool(gszIniMsgNotify, TRUE);
	gPref.fMsgState   = GetIniBool(gszIniMsgState, TRUE);

	gPref.iInit       = GetIniInt(gszIniInit, NM_INIT_NORMAL);

	gPref.pszFileName = GetIniStr(gszFileName, TEXT("C:\\autoexec.bat"));
}


//****************************************************************************
//
// VOID WritePref(void)
//
// Write the current preferences
//
//****************************************************************************

VOID WritePref(void)
{
	WriteIniBool(gszSbar, gPref.fSbar);
	WriteIniBool(gszTbar, gPref.fTbar);
	WriteIniBool(gszMsg, gPref.fMsg);
	WriteIniBool(gszChat, gPref.fChat);

	WriteIniStr(gszConferenceName, gPref.pszConferenceName);
	FreePlpv(&gPref.pszConferenceName);

	WriteIniStr(gszFileName, gPref.pszFileName);
	FreePlpv(&gPref.pszFileName);

	WriteIniStr(gszAddr, gPref.pszAddr);
	FreePlpv(&gPref.pszAddr);
	WriteIniInt(gszAddrType, (int) gPref.nmAddrType);
	WriteIniInt(gszIniCallType, (int) gPref.nmCallType);

	if (NULL != ghwndMain)
	{
		gPref.wpMain.length = sizeof(WINDOWPLACEMENT);
		GetWindowPlacement(ghwndMain, &gPref.wpMain);
	}
	WriteIniHex(gszMainWnd, &gPref.wpMain, sizeof(WINDOWPLACEMENT));

	WriteIniHex(gszMsgFont, &gPref.lf, sizeof(LOGFONT));

	WriteIniTbar();

	WriteIniBool(gszIniAutoMonitor, gPref.fAutoMonitor);
	WriteIniBool(gszIniAutoHost,    gPref.fAutoHost);
	WriteIniBool(gszIniAutoCall,    gPref.fAutoCall);
	WriteIniBool(gszIniAutoChat,    gPref.fAutoChat);

	WriteIniInt(gszIniInit,        gPref.iInit);
	
	WriteIniBool(gszIniMsgTrace,    gPref.fMsgTrace);
	WriteIniBool(gszIniMsgObjects,  gPref.fMsgObjects);
	WriteIniBool(gszIniMsgNotify,   gPref.fMsgNotify);
	WriteIniBool(gszIniMsgState,    gPref.fMsgState);
}


//****************************************************************************
//
// BOOL FCreateLView(void)
//
//****************************************************************************

BOOL FCreateLView(void)
{
	ghwndLView = CreateWindow(TEXT("SysListView32"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | WS_CLIPSIBLINGS | LVS_REPORT,
		0, 0, 0, 0,
		ghwndMain, (HMENU) IDW_LVIEW, ghInst, NULL);
	if (ghwndLView == NULL)
		return FALSE;

	ListView_SetExtendedListViewStyle(ghwndLView, LVS_EX_FULLROWSELECT);

	// Initialize column data
	{
		int			iCol	= 0;
		LPCOL		lpCol	= _rgColMember;
		LV_COLUMN lvc;

		ZeroMemory(&lvc, sizeof(LV_COLUMN));
		
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_LEFT;
		for (iCol = 0; iCol < ARRAY_ELEMENTS(_rgColMember); iCol++)
		{
			lvc.iSubItem = iCol;
			lvc.cx = lpCol->dwWidth;
			lvc.pszText = lpCol->lpsz;
			if (ListView_InsertColumn(ghwndLView, iCol, &lvc) == -1)
				return FALSE;
			lpCol++;
		}
	}

	return TRUE;
}


//****************************************************************************
//
// BOOL FCreateMsgWindow(void)
//
// Create the main message window
//
//****************************************************************************

BOOL FCreateMsgWindow(void)
{
	ghwndMsg = CreateWindow(TEXT("LISTBOX"), NULL,
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | WS_CLIPSIBLINGS |
		LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS ,
		0, 0, 0, 0,
		ghwndMain, (HMENU) IDW_MSG, ghInst, NULL);
	if (ghwndMsg == NULL)
		return FALSE;

	// set the font for the window
	ghfontEntry = CreateFontIndirect(&gPref.lf);
	if (NULL == ghfontEntry)
		return TRUE;

	SendMessage(ghwndMsg, WM_SETFONT, (WPARAM) ghfontEntry, MAKELPARAM(TRUE, 0));

	return TRUE;
}


WNDPROC lpProcEdit = NULL;
VOID CmdChat(void);
LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT FAR PASCAL SubClsEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ((uMsg == WM_CHAR) && (VK_RETURN == wParam))
	{
		CmdChat();
		return 0L;
	}

	return CallWindowProc(lpProcEdit, hwnd, uMsg, wParam, lParam);
}


//****************************************************************************
//
// BOOL FCreateChatWindow(void)
//
//****************************************************************************

BOOL FCreateChatWindow(void)
{
	ghwndChat = CreateWindow(TEXT("EDIT"), NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS |  WS_TABSTOP |
			ES_AUTOHSCROLL,
		0, 0, DXP_SEND, DYP_SEND,
		ghwndMain, (HMENU) IDW_CHAT, ghInst, NULL);
	if (ghwndChat == NULL)
		return FALSE;

	// set the font for the window

	ghwndSend = CreateWindow(TEXT("BUTTON"), TEXT("Send To"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_TABSTOP |
			BS_DEFPUSHBUTTON,
		0, 0, DXP_SEND, DYP_SEND,
		ghwndMain, (HMENU) IDW_SEND, ghInst, NULL);
	if (ghwndSend == NULL)
		return FALSE;

	lpProcEdit = (WNDPROC) GetWindowLongPtr(ghwndChat, GWLP_WNDPROC);
	SetWindowLongPtr(ghwndChat, GWLP_WNDPROC, (LONG)(WNDPROC) SubClsEdit);

	ghwndUList = CreateWindow(TEXT("COMBOBOX"), TEXT("Everyone"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | WS_VSCROLL | WS_TABSTOP |
			CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED,
		0, 0, DXP_ULIST, DYP_ULIST,
		ghwndMain, (HMENU) IDL_USERS, ghInst, NULL);
	if (ghwndUList == NULL)
		return FALSE;

	return TRUE;
}


//****************************************************************************
//
// BOOL FInitMain(void)
//
// Initialize the window data and register the window class
//
//****************************************************************************

BOOL FInitMain(void)
{
	TCHAR szTitle[MAX_PATH + 1];
	WNDCLASS  wc;

	ZeroMemory(szTitle, sizeof(TCHAR) * (MAX_PATH + 1));
	ZeroMemory(&wc, sizeof(wc));

	ASSERT(NULL != ghInst);
	if (NULL == ghInst)
	{
		ERROR_MSG(TEXT("FInitMain: NULL == ghInst"));
		return FALSE;
	}

	ghAccelTable = LoadAccelerators(ghInst, MAKEINTRESOURCE(ID_APPACCEL));

	LoadString(ghInst, IDS_APP_TITLE, szTitle, MAX_PATH);

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = ghInst;
	wc.hIcon         = LoadIcon(ghInst, MAKEINTRESOURCE(ICO_MAIN));
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName  = MAKEINTRESOURCE(IDM_APP);
	wc.lpszClassName = gszAppClassName;

	// Register the window class and return FALSE if unsuccesful.
	if (!RegisterClass(&wc))
		return FALSE;

	// MAIN WINDOW
	// Create a main window for this application instance.
	ghwndMain = CreateWindow(gszAppClassName, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, ghInst, NULL);
	if (ghwndMain == NULL)
		return FALSE;

	ghMenu = GetMenu(ghwndMain);
	if (NULL == ghMenu)
		return FALSE;

	if (!FCreateSbar() || !FCreateTbar() ||
		!FCreateLView() || !FCreateMsgWindow() || !FCreateChatWindow())
		return FALSE;

	ShowHwnd(ghwndTbar, gPref.fTbar, IDM_VIEW_TBAR);
	ShowHwnd(ghwndSbar, gPref.fSbar, IDM_VIEW_SBAR);

	if (gPref.wpMain.length != 0)
		SetWindowPlacement(ghwndMain, &gPref.wpMain);

	return TRUE;
}


//****************************************************************************
//
// BOOL FInitApp(LPSTR lpszCmd, int nCmdShow)
//
// Initialize the application after checking command line, etc.
//
//****************************************************************************

BOOL FInitApp(LPSTR lpszCmd, int nCmdShow)
{
	InitCommonControls();


 	if (FAILED(CoInitialize(NULL)))
		return FALSE;

	ReadPref();

	if (!FInitMain())
		return FALSE;

	ASSERT(NULL != ghwndMain);
	ShowWindow(ghwndMain, nCmdShow);
	UpdateWindow(ghwndMain);

	TRACE_MSG(TEXT("System Initialized"));

	OnStartup();
	return TRUE;
}


//****************************************************************************
//
// VOID FreeAllComObjects(void)
//
//****************************************************************************

extern INmChannelFt * g_pChannelFt;

extern CFileTransferNotify * g_pNotifyFileTransfer;

VOID FreeAllComObjects(void)
{
	// Release all objects to which this app has a reference
	FreeAs();

	if(NULL != g_pNotifyFileTransfer)
	{
		g_pNotifyFileTransfer->Disconnect();
		g_pNotifyFileTransfer->Release();
		g_pNotifyFileTransfer = NULL;
	}

	if(NULL != g_pChannelFt)
	{
		g_pChannelFt->Release();
		g_pChannelFt = NULL;
	}

	FreeFt();

	FreeDataChannel();
	FreeAllUsers();
	FreeChannels();
	FreeCalls();
	FreeConferences();
	FreeConfMgr();
}


