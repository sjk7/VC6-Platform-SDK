//****************************************************************************
//  Module:     NMSHARE.EXE     
//  File:       MSG.CPP
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

// from cmd.cpp
VOID CmdExit(void);
LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



//****************************************************************************
//
// LRESULT MsgDestroy(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
// Handle a WM_DESTROY message
//
//****************************************************************************

LRESULT MsgDestroy(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
	return 0;
}


//****************************************************************************
//
// LRESULT MsgClose(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
// Handle a WM_CLOSE message
//
//****************************************************************************

LRESULT MsgClose(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	FreeAllUsers();
	CmdExit();
	return 0;
}


//****************************************************************************
//
// LRESULT MsgSize(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
// Handle a WM_SIZE message
//
//****************************************************************************

LRESULT MsgSize(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int dxClient = LOWORD(lParam);  // width of client area
	int dyClient = HIWORD(lParam);  // height of client area

	SizeMsgWindow(dxClient, dyClient);
	return 0;
}


//****************************************************************************
//
// LRESULT MsgGetMinMax(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgGetMinMax(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPMINMAXINFO lpminmax = (LPMINMAXINFO) lParam;

	lpminmax->ptMinTrackSize.x = 325;
	lpminmax->ptMinTrackSize.y = 250;

	return 0;
}


//****************************************************************************
//
// LRESULT MsgNotify(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgNotify(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (((LPNMHDR) lParam)->idFrom)
    {
		case IDW_APP:
			return MsgNotifyAppList(hwnd, uMsg, wParam, lParam);
		default:
    		break;
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////
// Main window message table definition.
static MSD _rgmsdMain[] =
{
	{WM_COMMAND,       MsgCmdMain},
	{WM_DESTROY,       MsgDestroy},
	{WM_CLOSE,         MsgClose},
	{WM_SIZE,          MsgSize},
	{WM_GETMINMAXINFO, MsgGetMinMax},
	{WM_NOTIFY,        MsgNotify},
		
	{0, NULL}  // MUST be the last entry
};


//****************************************************************************
//
// LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
// Main Window proc
//
//****************************************************************************

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	for (LPMSD lpmsd = _rgmsdMain; 0 != lpmsd->uMsg; lpmsd++)
	{
		if (lpmsd->uMsg == uMsg)
		{
			return lpmsd->pfnmsg(hwnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

