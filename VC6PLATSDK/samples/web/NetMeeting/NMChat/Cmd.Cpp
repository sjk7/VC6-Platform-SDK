//****************************************************************************
//  Module:     NMCHAT.EXE
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


//****************************************************************************
//
// VOID CmdOptions(void)
//
//****************************************************************************

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

	ZeroMemory(&lf, sizeof(LOGFONT));
	ZeroMemory(&hfont, sizeof(HFONT));

	lf = gPref.lf;

	ClearStruct(&cf);						// Zero's memory
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = ghwndMain;
	cf.lpLogFont = &lf;
	cf.iPointSize = 10;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;

	if (ChooseFont(&cf) != TRUE)
	{
		return;
	}

	hfont= CreateFontIndirect(cf.lpLogFont);
	if (hfont == hfontNil)
	{
		return;
	}

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
	TCHAR szVersion[MAX_PATH + 1];
	ZeroMemory(szVersion, (MAX_PATH + 1) * sizeof(TCHAR));

	LoadString(ghInst, IDS_VERSION, szVersion, CCHMAX(szVersion));

	ShellAbout(ghwndMain, szVersion, NULL, LoadIcon(ghInst, MAKEINTRESOURCE(ICO_MAIN)));
}


//****************************************************************************
//
// Main window command table definition.
//
//****************************************************************************

static CMD _rgcmdMain[] =
{
	{IDM_EXIT,                CmdExit},

	{IDM_VIEW_CLEAR,          CmdClear},
	{IDM_VIEW_FONT,           CmdFont},
	{IDM_OPTIONS,             CmdOptions},

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


