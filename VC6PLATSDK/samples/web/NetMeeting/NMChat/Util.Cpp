//****************************************************************************
//  Module:     NMCHAT.EXE
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
// VOID SendText(void)
//
// Send the line of text in the edit control.
//
//****************************************************************************

VOID SendText(void)
{
	UINT  cb = 0;
	TCHAR sz[MAX_PATH + 1];
	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

#ifdef NM2_CHAT_PROTOCOL
	BYTE   buffer[CB_NM2_HDR + (MAX_PATH + 1) * sizeof(WCHAR)];
	ZeroMemory(buffer, CB_NMUI_HDR + (MAX_PATH + 1) * sizeof(WCHAR));

	// Get the text line
	cb = SendMessage(ghwndEdit, WM_GETTEXT, (WPARAM) MAX_PATH, (LPARAM) sz);
	SendMessage(ghwndEdit, EM_SETSEL, (WPARAM) 0, (LPARAM)-1);
	SendMessage(ghwndEdit, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");

	if ((0 != cb) && (NULL != g_pChannelData))
	{
		INmMember * pMember = GetSelectedMember();
		if ((pMember != NULL) && (S_OK == pMember->IsSelf()))
		{
			// Local Member => Everyone => Broadcast
			pMember = NULL;
		}

		cb++; // include final null
#ifdef UNICODE
		lstrcpyn((LPTSTR) &buffer[CB_NM2_HDR], sz, MAX_PATH + 1);
#else
		cb = MultiByteToWideChar(CP_ACP, 0, sz, cb, (LPWSTR) &buffer[CB_NM2_HDR], MAX_PATH);
		cb *= 2; // adjust for UNICODE
#endif /* !UNICODE */

		// Add special prefix
		cb += CB_NM2_HDR;
		ZeroMemory(buffer, CB_NM2_HDR);
		* ((LPDWORD) buffer) = CB_NM2_HDR;

		g_pChannelData->SendData(pMember, cb, buffer, 0);
	}
	
#else
	// Get the text line
	cb = SendMessage(ghwndEdit, WM_GETTEXT, (WPARAM) CCHMAX(sz), (LPARAM) sz);
	SendMessage(ghwndEdit, EM_SETSEL, (WPARAM) 0, (LPARAM)-1);
	SendMessage(ghwndEdit, WM_SETTEXT, (WPARAM) 0, (LPARAM) "");

	if ((0 != cb) && (NULL != g_pChannelData))
	{
		INmMember * pMember = GetSelectedMember();
		if ((pMember != NULL) && (S_OK == pMember->IsSelf()))
		{
			// Local Member => Everyone => Broadcast
			pMember = NULL;
		}

		cb++; // include final null
		g_pChannelData->SendData(pMember, cb, (LPBYTE) sz, 0);
	}
#endif /* NM2_CHAT_PROTOCOL */
}


//****************************************************************************
//
// VOID ClearText(void)
//
//****************************************************************************

VOID ClearText(void)
{
	ListView_DeleteAllItems(ghwndMsg);
}


//****************************************************************************
//
// VOID SizeMsgWindow(int dx, int dy)
//
//****************************************************************************

VOID SizeMsgWindow(int dx, int dy)
{
	MoveWindow(ghwndEdit, XP_LEFT, dy - DYP_EDIT, dx, DYP_EDIT, TRUE);
	dy -= (YP_TOP + DYP_EDIT);

	MoveWindow(ghwndUser, XP_LEFT, YP_TOP, DXP_USER, dy, TRUE);
	dx -= DXP_USER;

	MoveWindow(ghwndMsg, XP_LEFT + DXP_USER, YP_TOP, dx, dy, TRUE);
}


//****************************************************************************
//
// VOID RecalcMsgWindow(void)
//
//****************************************************************************

VOID RecalcMsgWindow(void)
{
	RECT rc = {0,0,0,0};

	GetClientRect(ghwndMain, &rc);
	SizeMsgWindow(rc.right, rc.bottom);
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


//****************************************************************************
//
// LPTSTR PszAlloc(int cch)
//
//****************************************************************************

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
	if ((plpv == NULL) || (*(VOID FAR * FAR *)plpv == NULL))
	{
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
	if(NULL == phgdi || NULL == *phgdi)
	{
		return;
	}

	DeleteObject(*phgdi);
	*phgdi = NULL;	
}

