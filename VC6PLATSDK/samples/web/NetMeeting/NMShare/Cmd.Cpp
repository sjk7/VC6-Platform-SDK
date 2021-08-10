//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       CMD.CPP
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


VOID CmdOptions(void)
{
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
	ClearText();
}


//****************************************************************************
//
// VOID CmdExit(void)
//
// Shutdown the application.
//
//****************************************************************************

VOID CmdExit(void)
{
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
#ifdef NOTUSED
	CHOOSEFONT cf;
	LOGFONT    lf;
	HFONT      hfont;

	lf = gPref.lf;

	ClearStruct(&cf);
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = ghwndMain;
	cf.lpLogFont = &lf;
	cf.iPointSize = 10;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;

	if (ChooseFont(&cf) != TRUE)
		return;

	hfont= CreateFontIndirect(cf.lpLogFont);
	if (hfont == hfontNil)
		return;

	MaybeDeleteObject((HGDIOBJ *) &ghfontEntry);
	ghfontEntry = hfont;
	SendMessage(ghwndMsg, WM_SETFONT,
		(WPARAM) ghfontEntry, MAKELPARAM(TRUE, 0));

	gPref.lf = lf;
#endif
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
	TCHAR szVersion[MAX_PATH];

	LoadString(ghInst, IDS_VERSION, szVersion, CCHMAX(szVersion));

	ShellAbout(ghwndMain, szVersion, NULL, LoadIcon(ghInst, MAKEINTRESOURCE(ICO_MAIN)));
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


VOID CmdViewMsg(void)
{
	gPref.fMsgWindow = !gPref.fMsgWindow;
	ShowHwnd(ghwndMsg, gPref.fMsgWindow, IDM_VIEW_MSG);
}


VOID CmdViewUsers(void)
{
	gPref.fUserList = !gPref.fUserList;
	ShowHwnd(ghwndUser, gPref.fUserList, IDM_VIEW_USERLIST);
}

VOID CmdRefresh(void)
{
	DoEnumApps();
}

VOID CmdWorkAlone(void)
{
	DoWorkAlone();
}

VOID CmdCollaborate(void)
{
	DoCollaborate();
}

VOID CmdInControl(void)
{
	DoTakeControl();
}


//****************************************************************************
//
// Main window command table definition.
//
//****************************************************************************

static CMD _rgcmdMain[] =
{
	{IDM_EXIT,                CmdExit},
	
	{IDM_WORK_ALONE,          CmdWorkAlone},
	{IDM_COLLABORATE,         CmdCollaborate},
	{IDM_IN_CONTROL,          CmdInControl},

	{IDM_VIEW_CLEAR,          CmdClear},
	
	{IDM_VIEW_SBAR,           CmdViewSbar},
	{IDM_VIEW_MSG,            CmdViewMsg},
	{IDM_VIEW_USERLIST,       CmdViewUsers},
	{IDM_REFRESH,             CmdRefresh},

	{IDM_HELP,                CmdHelp},
	{IDM_ABOUT,               CmdAbout},

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


