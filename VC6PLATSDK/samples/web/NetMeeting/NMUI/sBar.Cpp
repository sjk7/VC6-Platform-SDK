//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       SBAR.CPP       
//  Content:    Status Bar Routines
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

TBBUTTON _rgtbb[] =
{
    {0,   0,                      TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0,  0, 0},
    {28,  IDM_MONITOR,            TBSTATE_ENABLED, TBSTYLE_CHECK,  0, 0,  1, 0},
    {10,  IDM_CONF_START,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  2, 0},
    {6,   IDM_CONF_STOP,          TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  3, 0},
    {4,   IDM_VIEW_CLEAR,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  4, 0},
    {5,   IDM_CALL,               TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  5, 0},
    {1,   IDM_VIEW_MSG,           TBSTATE_ENABLED, TBSTYLE_CHECK,  0, 0,  6, 0},
    {0,   IDM_VIEW_CLEAR,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  7, 0},
    {6,   IDM_VIEW_FONT,          TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  8, 0},
    {10,  IDM_CHANNEL_DATA,       TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0,  9, 0},
    {11,  IDM_CHANNEL_AUDIO,      TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 10, 0},
    {26,  IDM_CHANNEL_FT,         TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 12, 0},
    {14,  IDM_CHANNEL_SHARE,      TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 13, 0},
    {3,   IDM_FT_CANCEL,          TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 14, 0},

};

// default ordering of toolbar buttons
static TCHAR _szBtnDefault[] = TEXT("0100020304000500060007");

static TCHAR _szToolbar[] = TEXT("Toolbar");


//****************************************************************************
//
// LPTBBUTTON _GetDefaultTbb(DWORD * pcTbb, BOOL fReset)
//
//****************************************************************************

LPTBBUTTON _GetDefaultTbb(DWORD * pcTbb, BOOL fReset)
{
	if	(NULL == pcTbb)
	{
		ERROR_MSG(TEXT("_GetDefaultTbb: NULL == pcTbb"));
		return 0;
	}

	DWORD	iBtn	= 0;
	DWORD	cBtn	= 0;
	LPTSTR	lpsz	= 0;
	LPTSTR	lpch	= 0;
	LPTBBUTTON pttb	= 0;

	if (fReset)
		lpsz = _szBtnDefault;
	else
		lpsz = GetIniStr(_szToolbar, _szBtnDefault);

	if	(NULL == lpsz)
		return NULL;

	lpch = lpsz;
	cBtn = lstrlen(lpsz) / 2;

	pttb = (LPTBBUTTON) LpvAlloc(sizeof(TBBUTTON) * cBtn);
	if (NULL == pttb)
		return NULL;
	for (iBtn = 0; iBtn < cBtn; iBtn++)
	{
		CopyMemory(pttb + iBtn, &_rgtbb[ChFromHex(lpch)], sizeof(TBBUTTON));
		lpch += 2;
	}

	if (!fReset)
		FreePlpv(&lpsz);

	*pcTbb = cBtn;
	return pttb;
}

//****************************************************************************
//
// VOID ResetToolbar(void)
//
// Reset the toolbar to the initial defaults
//
//****************************************************************************

VOID ResetToolbar(void)
{
	DWORD cBtn	= 0;
	DWORD iBtn	= 0;

	LPTBBUTTON ptbb	= NULL;

	ptbb = _GetDefaultTbb(&cBtn, TRUE /* fReset */);
	if (NULL == ptbb)
		return;

	iBtn = SendMessage(ghwndTbar, TB_BUTTONCOUNT, 0, 0);
	while (iBtn != 0)
	{
		SendMessage(ghwndTbar, TB_DELETEBUTTON, (WPARAM) --iBtn, 0);
	}

	SendMessage(ghwndTbar, TB_ADDBUTTONS, (WPARAM) cBtn, (LPARAM) ptbb);

	FreePlpv(&ptbb);
}

//****************************************************************************
//
// BOOL FCreateTbar(void)
//
// Create the toolbar
//
//****************************************************************************

BOOL FCreateTbar(void)
{
	DWORD		cBtn	= 0;
	LPTBBUTTON	ptbb	= 0;

	ptbb = _GetDefaultTbb(&cBtn, FALSE /* fReset */);
	if (NULL == ptbb)
		return FALSE;

	ghwndTbar = CreateToolbarEx(ghwndMain,
		WS_CHILD | CCS_ADJUSTABLE |
			TBSTYLE_TOOLTIPS | TBSTYLE_ALTDRAG, // | TBSTYLE_WRAPABLE 
		IDW_TBAR,
		NUMIMAGES,
		ghInst,
		IDC_TOOLBAR,
		ptbb,
		cBtn,
		BUTTONWIDTH,
		BUTTONHEIGHT,
		IMAGEWIDTH,
		IMAGEHEIGHT,
		sizeof(TBBUTTON));

	FreePlpv(&ptbb);

	return (ghwndTbar != NULL);
}

//****************************************************************************
//
// LRESULT MsgNotifyTbar(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
//
//****************************************************************************

LRESULT MsgNotifyTbar(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
	LPTOOLTIPTEXT	lpToolTipText	=(LPTOOLTIPTEXT) lparam;
	static TCHAR szBuffer[MAX_PATH + 1];

	if	(NULL == lparam)
	{
		ERROR_MSG(TEXT("MsgNotifyTbar: NULL == lparam"));
		return 0;
	}

	switch (lpToolTipText->hdr.code)
		{
	case TTN_NEEDTEXT:
	{
		ZeroMemory(szBuffer, sizeof(TCHAR) * (MAX_PATH + 1));
		int cb	= 0;

		cb = LoadString(ghInst, lpToolTipText->hdr.idFrom,   // string ID == command ID
			szBuffer, MAX_PATH);
		if (cb == 0)
		{
			szBuffer[0] = '\0';
		}

		lpToolTipText->lpszText = szBuffer;
		return 1;
	}
	case TBN_QUERYINSERT:
		return 1; // allow insert
	case TBN_QUERYDELETE:
		return 1; // allow delete
	case TBN_RESET:
		ResetToolbar();
		return 1;
	case TBN_GETBUTTONINFO:
	{
		LPTBNOTIFY ptbn = (LPTBNOTIFY) lparam;
		int iBtn = ptbn->iItem+1;

		if (iBtn >= (ARRAY_ELEMENTS(_rgtbb)))
			return 0; // all button data has been passed to the control

		LoadString(ghInst, _rgtbb[iBtn].idCommand, ptbn->pszText, ptbn->cchText);
//?		ptbn->tbButton = _rgtbb[iBtn];
		return 1;

	}
	case TBN_CUSTHELP:
		break;
	case TBN_TOOLBARCHANGE:
		break; // changes handled when exiting
	default:
		break;
		}

	return 0;
}

//****************************************************************************
//
// VOID SetToolbarCheck(int idm, BOOL fCheck)
//
// Change the status of a toolbar command to be checked
//
//****************************************************************************

VOID SetToolbarCheck(int idm, BOOL fCheck)
{
	SendMessage(ghwndTbar, TB_CHECKBUTTON,
		(WPARAM) idm, (LPARAM) MAKELONG(fCheck, 0));
}

//****************************************************************************
//
// VOID CmdToolbar(HWND hwnd, WORD wCmd, WORD wNotify, HWND hwndCtrl)
//
//****************************************************************************

VOID CmdToolbar(HWND hwnd, WORD wCmd, WORD wNotify, HWND hwndCtrl)
{
	SendMessage(ghwndTbar, TB_CUSTOMIZE, 0, 0);
}


//****************************************************************************
//
// VOID WriteIniTbar(void)
//
//****************************************************************************

VOID WriteIniTbar(void)
{
	int			iBtn	= 0;
	int			cBtn	= 0;
	LPTSTR		lpsz	= 0;
	LPTSTR		lpch	= 0;
	TBBUTTON	tbb;

	if (NULL == ghwndTbar)
		return; // no toolbar?

	cBtn = SendMessage(ghwndTbar, TB_BUTTONCOUNT, 0, 0);
	if (0 == cBtn)
		return;

	lpsz = (LPTSTR) LpvAlloc((cBtn*2 + 1) * sizeof(TCHAR));
	if (NULL == lpsz)
		return;
	ZeroMemory(lpsz, (cBtn*2 + 1) * sizeof(TCHAR));

	lpch = lpsz;
	for (iBtn = 0; iBtn < cBtn; iBtn++)
	{
		SendMessage(ghwndTbar, TB_GETBUTTON, (WPARAM) iBtn, (LPARAM) (LPTBBUTTON) &tbb);
		_sntprintf(lpch, 2, TEXT("%02X"), LOBYTE(tbb.dwData));
		lpch += 2;
	}
	WriteIniStr(_szToolbar, lpsz);
	FreePlpv(&lpsz);	
}


//****************************************************************************
//
// BOOL FCreateSbar(void)
//
// Create the status bar.
//
//****************************************************************************

BOOL FCreateSbar(void)
{
	ghwndSbar = CreateWindow(STATUSCLASSNAME, NULL,
		WS_CHILD | SBARS_SIZEGRIP,
		0, 0, 0, 0,
		ghwndMain, (HMENU) IDW_SBAR, ghInst, NULL);

	return (ghwndSbar != NULL);
}


//****************************************************************************
//
// VOID UpdateStatusBar(LPTSTR lpsz, WORD wPart, WORD wFlags)
//
// Update the text for part of the status bar
//
//****************************************************************************

VOID UpdateStatusBar(LPTSTR lpsz, WORD wPart, WORD wFlags)
{
    SendMessage(ghwndSbar, SB_SETTEXT, wPart | wFlags, (LPARAM) lpsz);
}


//****************************************************************************
//
// VOID StatusMsg(LPTSTR sz)
//
//****************************************************************************

VOID StatusMsg(LPTSTR sz)
{
	UpdateStatusBar(sz, IDSBP_MSG, 0);
}


//****************************************************************************
//
// VOID UpdateStatusIcon(DWORD dwId)
//
//****************************************************************************

VOID UpdateStatusIcon(DWORD dwId)
{
	static DWORD m_idIconStatus = 0;
	static HICON m_hIconStatus = 0;

	if (dwId == m_idIconStatus)
		return;

	HICON hIcon = (HICON) LoadImage(ghInst,
				MAKEINTRESOURCE(dwId), IMAGE_ICON,
				STATUSICONSIZE, STATUSICONSIZE,
				LR_DEFAULTCOLOR | LR_SHARED);
	if (NULL == hIcon)
	{
		return;
	}

	m_idIconStatus = dwId;
	m_hIconStatus = hIcon;
	SendMessage(ghwndSbar, SB_SETTEXT, 
			IDSBP_ICON | SBT_OWNERDRAW, (LPARAM) m_hIconStatus);
}


//****************************************************************************
//
// LRESULT MsgMenuSelect(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
//
// Change the status bar text to display the menu help.
//
//****************************************************************************

LRESULT MsgMenuSelect(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
	TCHAR  szBuffer[MAX_PATH + 1];
	UINT   nStringID = 0;
	UINT   fuFlags = GET_WM_MENUSELECT_FLAGS(wparam, lparam) & 0xffff;
	UINT   uCmd    = GET_WM_MENUSELECT_CMD(wparam, lparam);
	HMENU  hMenu   = GET_WM_MENUSELECT_HMENU(wparam, lparam);

	ZeroMemory(szBuffer, sizeof(TCHAR)*(MAX_PATH + 1));

	if (fuFlags == 0xffff && hMenu == NULL)     // Menu has been closed
	{
		return 0;
//		nStringID = IDS_DESCRIPTION;
	}
	else if (fuFlags & MFT_SEPARATOR)           // Ignore separators
	{
		nStringID = 0;
	}
	else if (fuFlags & MF_POPUP)                // Popup menu
	{
		if (fuFlags & MF_SYSMENU)               // System menu
			nStringID = IDS_SYSMENU;
	}
	else                                        // Must be a command item
	{
		nStringID = uCmd;               // String ID == Command ID
	}

	// Load the string if we have an ID
	if (nStringID != 0)
	{
		LoadString(ghInst, nStringID, szBuffer, MAX_PATH);
	}

	// Finally... send the string to the status bar
	UpdateStatusBar(szBuffer, IDSBP_MSG, 0);

	return 0;
}

