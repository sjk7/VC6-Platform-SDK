//****************************************************************************
//  Module:     NMSHARE.EXE     
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


//****************************************************************************
//
// VOID ClearText(void)
//
//****************************************************************************

VOID ClearText(void)
{
	SendMessage(ghwndMsg, LB_RESETCONTENT, 0, 0);
}


//****************************************************************************
//
// VOID DisplayMsg(LPTSTR pszMsg)
//
//****************************************************************************

VOID DisplayMsg(LPTSTR pszMsg)
{
	SendMessage(ghwndMsg, LB_ADDSTRING, 0, (LPARAM) pszMsg);
	PostMessage(ghwndMsg, WM_VSCROLL, SB_BOTTOM, 0);
}


#ifdef NOTUSED

//****************************************************************************
//
// VOID SizeStatus(int dxClient, int dy)
//
//****************************************************************************

VOID SizeStatus(int dxClient, int dy)
{
	int rgdxp[3];

	rgdxp[2] = dxClient;
	dxClient -= 50;
	rgdxp[1] = dxClient;
	dxClient -= 75;
	rgdxp[0] = dxClient;
	SendMessage(ghwndSbar, SB_SETPARTS, (WPARAM) 3, (LPARAM) rgdxp);
}
#endif


//****************************************************************************
//
// VOID SizeMsgWindow(int dx, int dy)
//
//****************************************************************************

VOID SizeMsgWindow(int dx, int dy)
{
	int dyT = dy;
	int dxLeft = XP_LEFT;

	if (gPref.fMsgWindow)
	{
		dyT = dy / 2;
		MoveWindow(ghwndMsg, XP_LEFT, dy - dyT, dx, dyT, TRUE);
		dy -= (YP_TOP + dyT);
	}


	if (gPref.fUserList)
	{
		MoveWindow(ghwndUser, XP_LEFT, YP_TOP, DXP_USER, dyT, TRUE);
		dxLeft += DXP_USER;
		dx -= DXP_USER;
	}

	MoveWindow(ghwndApp, dxLeft, YP_TOP, dx, dy, TRUE);
}


//****************************************************************************
//
// VOID RecalcMsgWindow(void)
//
//****************************************************************************

VOID RecalcMsgWindow(void)
{
	RECT rc;

	GetClientRect(ghwndMain, &rc);
	SizeMsgWindow(rc.right, rc.bottom);
}


//****************************************************************************
//
// VOID ShowHwnd(HWND hwnd, BOOL fShow, int idm)
//
// Show/Hide a window
//
//****************************************************************************

VOID ShowHwnd(HWND hwnd, BOOL fShow, int idm)
{
	if (IsWindow(hwnd))
	{
		ShowWindow(hwnd, fShow ? SW_SHOW : SW_HIDE);
		SetMenuCheck(idm, fShow);
		RecalcMsgWindow();
	}
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
// VOID MaybeDeleteObject(HGDIOBJ * phgdi)
//
// Check usage count, delete if we can
//
//****************************************************************************

VOID MaybeDeleteObject(HGDIOBJ * phgdi)
{
	if (*phgdi == hgdiNil)
		return;

	DeleteObject(*phgdi);
	*phgdi = hgdiNil;	
}


//****************************************************************************
//
// VOID SetMenuCheck(UINT idm, BOOL fCheck)
//
// Set the menu item's check mark.
//
//****************************************************************************

VOID SetMenuCheck(UINT idm, BOOL fCheck)
{
	CheckMenuItem(ghMenu, idm,
		fCheck ? (MF_CHECKED  | MF_BYCOMMAND) : (MF_UNCHECKED | MF_BYCOMMAND));
}


