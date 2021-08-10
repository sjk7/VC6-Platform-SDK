//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       CMD.CPP
//  Content:    Main Command Routines
//        All functions in this file have the format:
//                VOID CmdXxx(void);
//
//  Copyright (c) Microsoft Corporation 1995-2002
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//****************************************************************************


#include "precomp.h"


//****************************************************************************
//
// VOID CmdMonitor(void)
//
//****************************************************************************

VOID CmdMonitor(void)
{
	if (NULL == g_pMgr)
	{
		if (FAILED(InitConfMgr()))
		{
			ERROR_MSG(TEXT("Failed to monitor incoming calls"));
		}
		else
		{
			TRACE_MSG(TEXT("Monitoring incoming calls"));
		}

	}
	else
	{
		FreeAllComObjects();
		//FreeConfMgr();
		ASSERT(NULL == g_pMgr);

	}

	BOOL fChecked = NULL != g_pMgr;
	SetToolbarCheck(IDM_MONITOR, fChecked);
	SetMenuCheck(IDM_MONITOR, fChecked);
}


//****************************************************************************
//
// VOID CmdConfStart(void)
//
//****************************************************************************

VOID CmdConfStart(void)
{
	if (!DlgNewConference())
		return;

	TRACE_MSG(TEXT("Starting conference [%s] nmch=%08X"), 
		(NULL != gPref.pszConferenceName) ?  gPref.pszConferenceName : TEXT("NULL"),
		gPref.dwNmch);
	DoConferenceCreate();
}


//****************************************************************************
//
// VOID CmdConfStop(void)
//
//****************************************************************************

VOID CmdConfStop(void)
{
	TRACE_MSG(TEXT("Stopping conference..."));
	DoConferenceLeave();
}


//****************************************************************************
//
// VOID CmdCall(void)
//
//****************************************************************************

VOID CmdCall(void)
{
	if (!DlgNewCall())
		return;
	DoCallCreate();
}

//****************************************************************************
//
// VOID CmdCallConf(void)
//
//****************************************************************************

VOID CmdCallConf(void)
{
	if (!DlgCallConf())
		return;
	DoCallConference();
}


//****************************************************************************
//
// VOID CmdCallAccept(void)
//
//****************************************************************************

VOID CmdCallAccept(void)
{
	DoHandleCall(TRUE);
}


//****************************************************************************
//
// VOID CmdCallReject(void)
//
//****************************************************************************

VOID CmdCallReject(void)
{
	DoHandleCall(FALSE);
}


//****************************************************************************
//
// VOID CmdCallCancel(void)
//
//****************************************************************************

VOID CmdCallCancel(void)
{
	DoCancelCall();
}


//****************************************************************************
//
// VOID CmdShare(void)
//
//****************************************************************************

VOID CmdShare(void)
{
	DlgShare();
}

VOID CmdSysLogOnOff(void)
{
	DlgLogOnOff();
}

VOID CmdShowLocal(void)
{
	DlgShowLocal();
}

//****************************************************************************
//
// VOID CmdLaunch(void)
//
//****************************************************************************

VOID CmdLaunch(void)
{
	DlgLaunch();
}

VOID CmdEject(void)
{
	DlgEject();
}

VOID CmdFtCancel(void)
{
	DoFtCancel();
}

VOID CmdDataEnable(void)
{
	if (NULL == g_pChannelData)
		return;

	DoActivateDataChannel(S_OK != g_pChannelData->IsActive());
}


VOID CmdChannelData(void)
{
	DoCreateDataChannel(GetCurrentConference());
}

VOID CmdChat(void)
{
	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH+1) * sizeof(TCHAR));

	// Get the text line
	SendMessage(ghwndChat, WM_GETTEXT, (WPARAM) MAX_PATH, (LPARAM) sz);
	SendMessage(ghwndChat, EM_SETSEL, (WPARAM) 0, (LPARAM)-1);
	SendMessage(ghwndChat, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");

	if (NULL != g_pChannelData)
	{
		INmMember * pMember = NULL;
		int iSel = SendMessage(ghwndUList, CB_GETCURSEL, 0, 0);
		if (CB_ERR != iSel)
		{
			PUSER pUser = (PUSER) SendMessage(ghwndUList, CB_GETITEMDATA, (WPARAM) iSel, 0);
			if (NULL != pUser)
				pMember = pUser->pMember;
		}
		DoSendChatMsg(sz, pMember);
	}

	SetFocus(ghwndChat);
}

VOID CmdAudio(void)
{
	DlgAudio();
}


VOID CmdSendFile(void)
{
	DlgSendFile();
}

VOID CmdSysInfo(void)
{
	DumpSysInfo();
}

VOID CmdConfInfo(void)
{
	DoEnumAll();
}

VOID CmdConfLeak(void)
{
	DoEnumMemberLeak();
}

VOID CmdConfAppLeak(void)
{
	DoSharableAppLeak();
}

VOID CmdOptions(void)
{
	DlgOptions();
}


VOID CmdUpdate(void)
{
	UpdateConfView();
}


VOID CmdTopMost(void)
{

	TCHAR szTitle[MAX_PATH+1];
	WNDCLASSEX  wc;
	HWND hwndTest;

	ZeroMemory(szTitle, sizeof(TCHAR) * (MAX_PATH + 1));
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	ASSERT(NULL != ghwndMain);
	ASSERT(NULL != ghInst);

//	ghAccelTable = LoadAccelerators(ghInst, MAKEINTRESOURCE(ID_APPACCEL));

	LoadString(ghInst, IDS_APP_TITLE, szTitle, MAX_PATH);

	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = ghInst;
	wc.hIcon         = LoadIcon(ghInst, MAKEINTRESOURCE(ICO_TOPMOST));
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = TEXT("NMTOPMOST");
	wc.hIconSm       = NULL;

	if(!RegisterClassEx(&wc))
		return;

	hwndTest = CreateWindowEx(
		WS_EX_TOPMOST,  // dwExStyle - extended styles
		TEXT("NMTOPMOST"),   // lpClassName - class name
		TEXT("szTitle"),     // window name
		WS_POPUP|WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, // x, y, dx, dy
		NULL, // parent window handle
		NULL, // menu handle
		ghInst, // instance of app
		NULL); // window creation data
		
	if (hwndTest == NULL)
		return;

	ShowWindow(hwndTest, SW_SHOWNORMAL);
	UpdateWindow(hwndTest);

}

//****************************************************************************
//
// VOID CmdViewSbar(void)
//
// Show/Hide the status bar
//
//****************************************************************************

VOID CmdViewSbar(void)
{
	gPref.fSbar = !gPref.fSbar;
	ShowHwnd(ghwndSbar, gPref.fSbar, IDM_VIEW_SBAR);
}


//****************************************************************************
//
// VOID CmdViewTbar(void)
//
//****************************************************************************

VOID CmdViewTbar(void)
{
	gPref.fTbar = !gPref.fTbar;
	ShowHwnd(ghwndTbar, gPref.fTbar, IDM_VIEW_TBAR);
}


//****************************************************************************
//
// VOID CmdViewChat(void)
//
//****************************************************************************

VOID CmdViewChat(void)
{
	gPref.fChat = !gPref.fChat;
	ShowWindow(ghwndSend, gPref.fChat ? SW_SHOW : SW_HIDE);
	ShowWindow(ghwndUList, gPref.fChat ? SW_SHOW : SW_HIDE);
	ShowHwnd(ghwndChat, gPref.fChat, IDM_VIEW_CHAT);
}


//****************************************************************************
//
// VOID CmdViewMsg(void)
//
//****************************************************************************

VOID CmdViewMsg(void)
{
	gPref.fMsg = !gPref.fMsg;
	ShowHwnd(ghwndMsg, gPref.fMsg, IDM_VIEW_MSG);
	SetToolbarCheck(IDM_VIEW_MSG, gPref.fMsg);
}


//****************************************************************************
//
// VOID CmdClear(void)
//
// Clear the message window
//
//****************************************************************************

VOID CmdClear(void)
{
	ClearLog();
}


//****************************************************************************
//
// VOID CmdClear(void)
//
// Shutdown the application.
//
//****************************************************************************

VOID CmdExit(void)
{
	WritePref();
	DestroyWindow(ghwndMain);
}


//****************************************************************************
//
// VOID CmdHelp(void)
//
// Bring up help for the application
//
//****************************************************************************

VOID CmdHelp(void)
{
	TCHAR  szFile[MAX_PATH + 1];

	ZeroMemory(szFile, (MAX_PATH + 1) * sizeof(TCHAR));
	
	GetModuleFileName(ghInst, szFile, MAX_PATH);

	// convert the app name to the help filename (foo.exe => foo.hlp)

	LPTSTR	tsz	= SzFindLastCh(szFile, _T('.'));
	if	(	(NULL != tsz)
		&&	(MAX_PATH - 4 > (tsz - szFile) / sizeof(TCHAR))
		&&	(tsz > szFile)
		)
	{
		_sntprintf(tsz, 4, TEXT(".hlp"));
		WinHelp(ghwndMain, szFile, HELP_CONTENTS, 0);
	}
}


//****************************************************************************
//
// VOID CmdFont(void)
//
// Change the font for the message window
//
//****************************************************************************

VOID CmdFont(void)
{
	CHOOSEFONT cf;
	LOGFONT    lf;
	HFONT      hfont;

	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	ZeroMemory(&lf, sizeof(LOGFONT));
	ZeroMemory(&hfont, sizeof(HFONT));
	
	lf = gPref.lf;

	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = ghwndMain;
	cf.lpLogFont = &lf;
	cf.iPointSize = 10;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;

	if (ChooseFont(&cf) != TRUE)
		return;

	hfont= CreateFontIndirect(cf.lpLogFont);
	if (NULL == hfont)
		return;

	MaybeDeleteObject((HGDIOBJ *) &ghfontEntry);
	ghfontEntry = hfont;
	SendMessage(ghwndMsg, WM_SETFONT,
		(WPARAM) ghfontEntry, MAKELPARAM(TRUE, 0));

	gPref.lf = lf;
}


//****************************************************************************
//
// VOID CmdAbout(void)
// 
// Display the about box
//
//****************************************************************************

VOID CmdAbout(void)
{
	TCHAR szVersion[MAX_PATH + 1];
	ZeroMemory(szVersion, sizeof(TCHAR) * (MAX_PATH + 1));

	LoadString(ghInst, IDS_VERSION, szVersion, MAX_PATH);

	ShellAbout(ghwndMain, szVersion, NULL, LoadIcon(ghInst, MAKEINTRESOURCE(ICO_MAIN)));
}

//****************************************************************************
//
// VOID CmdEnableAppSharing(void)
// 
// Enable appsharing if it isn't already Enabled
//
//****************************************************************************

typedef BOOL (WINAPI *LPFNDLLFUNC)(HWND);

VOID CmdEnableAppSharing(void)
{
	BOOL RetVal= IsSharingEnabled();

	if(FALSE == RetVal)
	{
		HINSTANCE	hDLL			= 0;
		LPFNDLLFUNC	lpfnDllFunc1	= 0;    // Function pointer
		TCHAR szDLL[MAX_PATH + 1];
		TCHAR szFunc[MAX_PATH + 1];
		int retVal					= 0;

		ZeroMemory(szDLL, (MAX_PATH + 1) * sizeof(TCHAR));
		ZeroMemory(szFunc, (MAX_PATH + 1)* sizeof(TCHAR));

		LoadString(ghInst, IDS_DLLNAME, szDLL, MAX_PATH);
		LoadString(ghInst, IDS_SETUPDD_FUNC, szFunc, MAX_PATH);

		// Load Library on the setupdd.dll
		hDLL = LoadLibrary(szDLL);

		if (hDLL != NULL)
		{
			lpfnDllFunc1 = (LPFNDLLFUNC)GetProcAddress(hDLL, szFunc);
			if (!lpfnDllFunc1)
			{
				// handle the error
				ERROR_MSG(TEXT("Could not find the %s function\r\n"), szFunc);
				retVal = FALSE;
			}
			else
			{
				TRACE_MSG(TEXT("Found the %s function\r\n"), szFunc);
			
				// call the function
				retVal = lpfnDllFunc1(ghwndMain);
				
				TRACE_MSG(TEXT("%s returns %s\r\n"), szFunc, (retVal ? "TRUE" : "FALSE"));

			}
			FreeLibrary(hDLL);

			::MessageBox(ghwndMain,TEXT("Attempt to enable sharing... COMPLETE - REBOOT NOW!"), TEXT("AppSharing Enabled"), MB_OK);
	
		}
		else
		{
			::MessageBox(ghwndMain, TEXT("Could not load Setupdd.dll"), TEXT("Error in Enabling Appsharing"), MB_OK);
		}

	}
	else
		::MessageBox(ghwndMain, TEXT("AppSharing Already Enabled"), TEXT("AppShare Status"), MB_OK);
	
}

//****************************************************************************
//
// VOID CmdIsSharingEnabled()
// 
//  TRUE- if AppSharing is enabled
//	FALSE- if AppSharing is not enabled
//
//****************************************************************************

VOID CmdIsSharingEnabled()
{
	BOOL RetVal= IsSharingEnabled();

	if(FALSE == RetVal)
		::MessageBox(ghwndMain, TEXT("AppSharing Is Not Enabled"), TEXT("AppShare Enable Status"), MB_OK);
	else
		::MessageBox(ghwndMain, TEXT("AppSharing Already Enabled"), TEXT("AppShare Enable Status"), MB_OK);
		
		
}

//****************************************************************************
//
// VOID OnStartup(void)
// 
// Perform any automatic startup commands
//
//****************************************************************************

VOID OnStartup(void)
{
	if (gPref.fAutoMonitor)
	{
		CmdMonitor();
	}

	if (gPref.fAutoHost)
	{
		DoConferenceCreate();
	}

	if (gPref.fAutoCall)
	{
		DoCallCreate();
	}
}


//****************************************************************************
//
// Main window command table definition.
// 
//****************************************************************************


static CMD _rgcmdMain[] =
{
	{IDM_MONITOR,             CmdMonitor},
	{IDM_SYSINFO,             CmdSysInfo},
	{IDM_EXIT,                CmdExit},

	{IDM_CONF_START,          CmdConfStart},
	{IDM_CONF_STOP,           CmdConfStop},
	{IDM_CONFINFO,            CmdConfInfo},
	{IDM_CONF_LEAK,           CmdConfLeak},
	{IDM_CONF_LEAK2,          CmdConfAppLeak},

	{IDM_VIEW_SBAR,           CmdViewSbar},
	{IDM_VIEW_TBAR,           CmdViewTbar},
	{IDM_VIEW_MSG,            CmdViewMsg},
	{IDM_VIEW_CHAT,           CmdViewChat},
	{IDM_VIEW_CLEAR,          CmdClear},
	{IDM_VIEW_FONT,           CmdFont},
	{IDM_OPTIONS,             CmdOptions},

	{IDM_LAUNCH,              CmdLaunch},
	{IDM_EJECT,               CmdEject},
	{IDM_UPDATE,              CmdUpdate},

	{IDM_CALL,                CmdCall},
	{IDM_CALL_CONF,           CmdCallConf},
	{IDM_CALL_ACCEPT,         CmdCallAccept},
	{IDM_CALL_REJECT,         CmdCallReject},
	{IDM_CALL_CANCEL,         CmdCallCancel},

	{IDM_CHANNEL_DATA,        CmdChannelData},
	{IDM_CHANNEL_AUDIO,       CmdAudio},
	{IDM_CHANNEL_FT,          CmdSendFile},
	{IDM_CHANNEL_SHARE,       CmdShare},

	{IDW_SEND,                CmdChat},
	{IDM_FT_CANCEL,           CmdFtCancel},
	{IDM_DATA_ENABLE,         CmdDataEnable},

	{IDM_HELP,                CmdHelp},
	{IDM_ABOUT,               CmdAbout},

	{IDM_TOPMOST,             CmdTopMost},
	{IDM_LOGONOFF,			  CmdSysLogOnOff},
	{IDM_SHOWLOCAL,			  CmdShowLocal},
	{IDM_ENABLE_APPSHARING,	  CmdEnableAppSharing},
	{IDM_IS_SHARING_ENABLED,   CmdIsSharingEnabled},
	{0, NULL}  // MUST be last entry in the table
};


//****************************************************************************
//
// LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
//
// Handle a WM_COMMAND message
// 
//****************************************************************************

LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	UINT wCmd = (UINT) GET_WM_COMMAND_ID(wparam, lparam);

	for (LPCMD lpcmd = _rgcmdMain; 0 != lpcmd->wCmd; lpcmd++)
	{
		if (wCmd == lpcmd->wCmd)
		{
			lpcmd->pfncmd();
			break;
		}
	}

	return 0L;
}


