//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       RTNS.CPP
//  Content:    General utility routines
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

//****************************************************************************
//
// VOID SizeMsgWindow(int dx, int dy)
//
//****************************************************************************

VOID SizeMsgWindow(int dx, int dy)
{
	RECT	rc		= {0, 0, 0, 0};
	int		xLeft	= 0;
	int		yTop	= 0;
	int		d		= 0;
	int		dyLView	= 0;

	xLeft = 0;
	yTop = 3;
	dy -= 3;

	if (gPref.fTbar)
	{
		// adjust for Toolbar
		GetClientRect(ghwndTbar, &rc);
		d = (rc.bottom - rc.top);
		yTop += d;
		dy -= d;
	}

	if (gPref.fSbar)
	{
		// adjust for status bar
		GetClientRect(ghwndSbar, &rc);
		d = (rc.bottom - rc.top);
		dy -= d;
	}

	if (gPref.fChat)
	{
		// adjust for status bar
		GetClientRect(ghwndChat, &rc);
		d = (rc.bottom - rc.top);
		dy -= d;
		MoveWindow(ghwndChat, xLeft, yTop + dy, dx-(DXP_SEND+DXP_ULIST), d, TRUE);
		MoveWindow(ghwndSend, xLeft+dx-(DXP_SEND+DXP_ULIST), yTop + dy, DXP_SEND, DYP_SEND, TRUE);
		MoveWindow(ghwndUList, xLeft+dx-DXP_ULIST, yTop + dy, DXP_ULIST, DYP_ULIST, TRUE);
	}

	dyLView = dy;
	if (gPref.fMsg)
	{
		dyLView = dyLView / 2;
		MoveWindow(ghwndMsg, xLeft, yTop+dyLView, dx, dyLView, TRUE);
	}

	MoveWindow(ghwndLView, xLeft, yTop, dx, dyLView, TRUE);
}

//****************************************************************************
//
// VOID RecalcMsgWindow(void)
//
//****************************************************************************

VOID RecalcMsgWindow(void)
{
	RECT rc	= {0,0,0,0};

	GetClientRect(ghwndMain, &rc);
	SizeMsgWindow(rc.right, rc.bottom);
}


//****************************************************************************
//
// VOID ShowHwnd(HWND hwnd, BOOL fShow, int idm)
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
