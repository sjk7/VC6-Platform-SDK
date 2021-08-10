//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       MSG.CPP
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

// from cmd.cpp
VOID CmdExit(void);
LRESULT MsgCmdMain(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam);

// from tbar.cpp
LRESULT MsgNotifyTbar(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);
LRESULT MsgMenuSelect(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);


//****************************************************************************
//
// Handle a WM_DESTROY message
//
//****************************************************************************

LRESULT MsgDestroy(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam)
{
	FreeAllComObjects();
	PostQuitMessage(0);
	return 0;
}


//****************************************************************************
//
// LRESULT MsgCreate(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgCreate(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lParam)
{
	return 0;
}


//****************************************************************************
//
// Handle a WM_CLOSE message
//
//****************************************************************************

LRESULT MsgClose(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	FreeAllComObjects();
	CmdExit();
	return 0;
}


//****************************************************************************
//
// Handle a WM_SIZE message
//
//****************************************************************************

LRESULT MsgSize(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	int dxClient = LOWORD(lparam);  // width of client area
	int dyClient = HIWORD(lparam);  // height of client area

	SizeMsgWindow(dxClient, dyClient);
	SizeStatus(dxClient, 0);
	SendMessage(ghwndSbar, uMsg, wparam, lparam);
	
	return 0;
}


//****************************************************************************
//
// Handle a WM_GETMINMAXINFO message
//
//****************************************************************************

LRESULT MsgGetMinMax(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	LPMINMAXINFO lpminmax = (LPMINMAXINFO) lparam;

	if (gdxWndMin == 0 || gdyWndMin == 0)
		return 0;

	if	(NULL == lpminmax)
	{
		ERROR_MSG(TEXT("MsgGetMinMax: NULL == lpminmax"));
		return 0;
	}

	lpminmax->ptMinTrackSize.x = gdxWndMin;
	lpminmax->ptMinTrackSize.y = gdyWndMin;

	return 0;
}

//****************************************************************************
//
// LRESULT MsgDrawItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgDrawItem(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDW_MSG:
	{
		LPDRAWITEMSTRUCT	lpdi	= (LPDRAWITEMSTRUCT)lParam;
		TCHAR *				tsz		= 0;
		
		if	(NULL == lpdi)
		{
			ERROR_MSG(TEXT("MsgDrawItem: NULL == lpdi"));
			break;
		}

		COLORREF cv = SendMessage(ghwndMsg, LB_GETITEMDATA, (WPARAM)lpdi->itemID, (LPARAM)0);
		SetTextColor(lpdi->hDC, cv);
		
		int nLen = SendMessage(ghwndMsg, LB_GETTEXTLEN, (WPARAM) lpdi->itemID, 0);

		if	(	(0 < nLen)
			&&	(NULL != (tsz = new TCHAR[nLen + 1]))
			)
		{
			ZeroMemory(tsz, nLen + 1);

			SendMessage(ghwndMsg, LB_GETTEXT, (WPARAM)lpdi->itemID, (LPARAM) tsz);
			DrawText(lpdi->hDC, tsz, -1, &lpdi->rcItem, DT_LEFT | DT_SINGLELINE);

			delete [] tsz;
			tsz = 0;
		}
		break;
	}
	case IDW_SBAR:
	{
		if	(NULL == lParam)
		{
			ERROR_MSG(TEXT("MsgDrawItem: NULL == lParam"));
			break;
		}

		if (0 != (((LPDRAWITEMSTRUCT) lParam)->itemData))
		{
			DrawIconEx(	((LPDRAWITEMSTRUCT) lParam)->hDC, 
				((LPDRAWITEMSTRUCT) lParam)->rcItem.left, 
				((LPDRAWITEMSTRUCT) lParam)->rcItem.top, 
				(HICON) (((LPDRAWITEMSTRUCT) lParam)->itemData),
				STATUSICONSIZE, STATUSICONSIZE, 0, NULL, DI_NORMAL);
		}
		break;
	}

	case IDL_USERS:
	{
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;
	}

	default:
		break;
	} /* switch */                                                          

	return 0;
}


//****************************************************************************
//
// LRESULT MsgNotify(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT MsgNotify(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if	(NULL == lParam)
	{
		ERROR_MSG(TEXT("MsgNotify: NULL == MsgNotify"));
		return 0;
	}

    switch (((LPNMHDR) lParam)->idFrom)
        {
    case IDW_TBAR:
        return MsgNotifyTbar(hwnd, uMsg, wParam, lParam);
    default:
        // It might still be for the toolbar (tooltips)
        return MsgNotifyTbar(hwnd, uMsg, wParam, lParam);
        }

    return 0;
}


////////////////////////////////////////////////////////////////////////////
// Main window message table definition.
static MSD _rgmsdMain[] =
{
	{WM_COMMAND,       MsgCmdMain},
	{WM_NOTIFY,        MsgNotify},
	{WM_CREATE,        MsgCreate},
	{WM_DESTROY,       MsgDestroy},
	{WM_CLOSE,         MsgClose},
	{WM_SIZE,          MsgSize},
	{WM_MENUSELECT,    MsgMenuSelect},
	{WM_GETMINMAXINFO, MsgGetMinMax},
	{WM_DRAWITEM,      MsgDrawItem},
		
	{0, NULL}  // MUST be the last entry
};


//****************************************************************************
//
// Main Window proc
//
//****************************************************************************

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if	(NULL == _rgmsdMain)
	{
		ERROR_MSG(TEXT("WndProc: NULL == _rgmsdMain"));
		return 0;
	}

	for (LPMSD lpmsd = _rgmsdMain; 0 != lpmsd->uMsg; lpmsd++)
	{
		if (lpmsd->uMsg == uMsg)
		{
			return lpmsd->pfnmsg(hwnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}



