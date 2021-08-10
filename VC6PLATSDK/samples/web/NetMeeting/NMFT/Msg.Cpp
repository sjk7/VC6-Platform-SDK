//****************************************************************************
//  Module:     NMFT.EXE
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

typedef LRESULT (*PFNMSG)(HWND, UINT, WPARAM, LPARAM);

// This structure maps messages to message handling functions.
typedef struct _MSD
{
	UINT   uMsg;
	PFNMSG pfnmsg;
} MSD;                 // MeSsage Dispatch structure
typedef MSD * LPMSD;


VOID CmdClose(void)
{
	DestroyWindow(ghwndMain);
}


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
	CmdClose();
	return 0;
}


//****************************************************************************
//
// LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WORD wCmd = GET_WM_COMMAND_ID(wParam, lParam);
	switch (wCmd)
		{
	case IDCANCEL:
	{
		if (NULL != g_pFt)
		{
			g_pFt->Cancel();
			CmdClose();
		}
		break;
	}

	default:
		break;
		} /* switch wCmd */

	return 0L;
}



////////////////////////////////////////////////////////////////////////////
// Main window message table definition.
static MSD _rgmsdMain[] =
{
	{WM_COMMAND,       MsgCmdMain},
	{WM_DESTROY,       MsgDestroy},
	{WM_CLOSE,         MsgClose},
		
	{0, NULL}  // MUST be the last entry
};


//****************************************************************************
//
// LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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



