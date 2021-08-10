//****************************************************************************
//  Module:     NMUI.EXE     
//  File:       DLG.CPP
//  Content:    Dialog Box Procedures
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

#define NM_NT_DISPLAY_DRIVER_KEY	_T("System\\CurrentControlSet\\Services\\mnmdd")
#define REGVAL_NM_NT_DISPLAY_DRIVER_ENABLED	_T("Start")
#define NT_DRIVER_START_DISABLED	0x4
#define	REGVAL_INSTALL_DIR					TEXT("InstallationDirectory")


DWSTR _rgCallType[] = {
	{NM_CALL_DEFAULT, TEXT("Default")},
	{NM_CALL_T120,    TEXT("T120")},
	{NM_CALL_H323,    TEXT("H323")},
};

DWSTR _rgAddrType[] = {
	{NM_ADDR_UNKNOWN,      TEXT("Unknown")},
	{NM_ADDR_IP,           TEXT("IP")},
	{NM_ADDR_MACHINENAME,  TEXT("Machine name")},
	{NM_ADDR_PSTN,         TEXT("PSTN")},
	{NM_ADDR_ULS,          TEXT("ULS")},
	{NM_ADDR_H323_GATEWAY, TEXT("H323 Gateway")},
	{6,					   TEXT("callto")},
};

VOID InitLBox(HWND hwndCombo, DWSTR *pdwstr, UINT cElt, DWORD dwDefault)
{
	DWORD	dwIndex	= 0;
	DWORD	iSel	= 0;

	ASSERT(NULL != hwndCombo);
	if	(NULL == hwndCombo)
	{
		ERROR_MSG(TEXT("InitLBox: NULL == hwndCombo"));
		return;
	}

	if	(NULL == pdwstr)
	{
		ERROR_MSG(TEXT("InitLBox: NULL == pdwstr"));
		return;
	}

	for ( ; cElt > 0; cElt--, pdwstr++)
	{
		dwIndex = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) pdwstr->psz); 
		SendMessage(hwndCombo, CB_SETITEMDATA, dwIndex, (LPARAM) pdwstr->dw);
		if (pdwstr->dw == dwDefault)
		{
			iSel = dwIndex;
		}
	}

	SendMessage(hwndCombo, CB_SETCURSEL, dwDefault, 0);
}


//****************************************************************************
//
// DWORD GetLBoxDw(HWND hwndCombo)
//
//****************************************************************************

DWORD GetLBoxDw(HWND hwndCombo)
{
	if	(NULL == hwndCombo)
	{
		ERROR_MSG(TEXT("GetLBoxDw: NULL == hwndCombo"));
		return 0;
	}

	int iSel = SendMessage(hwndCombo, CB_GETCURSEL, 0, 0);
	if (CB_ERR == iSel)
		return 0;

	return SendMessage(hwndCombo, CB_GETITEMDATA, (WPARAM) iSel, 0);
}


//****************************************************************************
//
// VOID InitUserLBox(HWND hdlg, BOOL fEveryone)
//
//****************************************************************************

VOID InitUserLBox(HWND hdlg, BOOL fEveryone)
{
	HWND hwndCombo = GetDlgItem(hdlg, IDL_USERS);
	
	ASSERT(NULL != hwndCombo);
	if	(NULL == hwndCombo)
	{
		ERROR_MSG(TEXT("InitUserLBox: NULL == hwndCombo"));
		return;
	}

	InitializeUserList(hwndCombo, fEveryone);
}


//****************************************************************************
//
// VOID InitializeUserList(HWND hwndCombo, BOOL fEveryone)
//
//****************************************************************************

VOID InitializeUserList(HWND hwndCombo, BOOL fEveryone)
{
	if (NULL == g_pListUser)
		return;

	if	(NULL == hwndCombo)
	{
		ERROR_MSG(TEXT("InitializeUserList: hwndCombo == NULL"));
		return;
	}

	POSITION pos = g_pListUser->GetHeadPosition();
	while (NULL != pos)
	{
		POSITION posSav = pos;
		PUSER pUser = (PUSER) g_pListUser->GetNext(pos);
		AddUserToUList(pUser, hwndCombo, fEveryone);
	}

	SendMessage(hwndCombo, CB_SETCURSEL, 0, 0); 
}


//****************************************************************************
//
// VOID AddUserToUList(PUSER pUser, HWND hwndCombo, BOOL fEveryone)
//
//****************************************************************************

VOID AddUserToUList(PUSER pUser, HWND hwndCombo, BOOL fEveryone)
{
	DWORD dwIndex	= 0;

	ASSERT(NULL != pUser);
	if	(NULL == pUser)
	{
		ERROR_MSG(TEXT("AddUserToUList: NULL == pUser"));
		return;
	}

	if	(NULL == hwndCombo)
	{
		ERROR_MSG(TEXT("AddUserToUList: NULL == hwndCombo"));
		return;
	}

	if (fEveryone && (S_OK == pUser->pMember->IsSelf()))
	{
		dwIndex = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) TEXT("<all>")); 
	}
	else
	{
		dwIndex = SendMessage(hwndCombo, CB_ADDSTRING, 0, (LPARAM) pUser->pszName); 
	}
	SendMessage(hwndCombo, CB_SETITEMDATA, dwIndex, (LPARAM) pUser); 
}


//****************************************************************************
//
// VOID RemoveUserFromUList(PUSER pUser, HWND hwndCombo)
//
//****************************************************************************

VOID RemoveUserFromUList(PUSER pUser, HWND hwndCombo)
{
	ASSERT(NULL != pUser);
	if	(NULL == pUser)
	{
		ERROR_MSG(TEXT("RemoveUserFromList: NULL == pUser"));
		return;
	}

	if (!IsWindow(hwndCombo))
	{
		ERROR_MSG(TEXT("RemoveUserFromUList: invalid hwnd combo?"));
		return;
	}

	for (DWORD dwIndex = 0; ; dwIndex++)
	{
		DWORD dw = SendMessage(hwndCombo, CB_GETITEMDATA, dwIndex, 0);
		if (CB_ERR == dw)
		{
			break;
		}
		if (pUser == (PUSER) dw)
		{
			SendMessage(hwndCombo, CB_DELETESTRING, (WPARAM)dwIndex, 0); 
			return;
		}
	}

	ERROR_MSG(TEXT("RemoveUserFromUList: Unable to delete [%s]"), pUser->pszName);
}


//****************************************************************************
//
// VOID DrawUserItem(LPDRAWITEMSTRUCT lpdis)
//
//****************************************************************************

VOID DrawUserItem(LPDRAWITEMSTRUCT lpdis)
{
	if	(NULL == lpdis)
	{
		ERROR_MSG(TEXT("DrawUserItem: NULL == lpdis"));
		return;
	}

	if (lpdis->itemID == -1)
		return; 

	PUSER		pUser	= (PUSER) lpdis->itemData;
	COLORREF	cvText	= RGB(0, 0, 0);
	COLORREF	cvBack	= RGB(0, 0, 0);

	cvText = SetTextColor(lpdis->hDC, GetSysColor((lpdis->itemState & ODS_SELECTED)
		? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT)); 

	cvBack = SetBkColor(lpdis->hDC, GetSysColor((lpdis->itemState & ODS_SELECTED)
		? COLOR_HIGHLIGHT : COLOR_WINDOW)); 

	if (NULL == pUser->pszName)
	{
		ExtTextOut(lpdis->hDC, lpdis->rcItem.left+2, lpdis->rcItem.top+2, 
			ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
			TEXT("? user\0"), 6, NULL); 
	}
	else
	{
		ExtTextOut(lpdis->hDC, lpdis->rcItem.left+2, lpdis->rcItem.top+2, 
			ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
			pUser->pszName, lstrlen(pUser->pszName), NULL); 
	}

	SetTextColor(lpdis->hDC, cvText); 
	SetBkColor(lpdis->hDC, cvBack); 
 
	if (lpdis->itemState & ODS_FOCUS)
	{
		DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
	}
}
   

//****************************************************************************
//
// LRESULT CALLBACK ConferenceDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK ConferenceDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		SetDlgItemText(hdlg, IDE_NAME, gPref.pszConferenceName);
		SetDlgItemText(hdlg, IDE_PASSWORD, gPref.pszPassword);

		{ // check channel types
			DWORD dwFlag = 0x01;
			for (int id = IDC_NMCH_FIRST; id <= IDC_NMCH_LAST; id++)
			{
				CheckDlgButton(hdlg, id, 0 != (gPref.dwNmch & dwFlag));
				dwFlag <<= 1;
			}
		}

		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			GetDlgItemPsz(hdlg, IDE_NAME, &gPref.pszConferenceName);
			GetDlgItemPsz(hdlg, IDE_PASSWORD, &gPref.pszPassword);

			{ // check media types
				DWORD dwFlag = 0x01;
				gPref.dwNmch = 0;
				for (int id = IDC_NMCH_FIRST; id <= IDC_NMCH_LAST; id++)
				{
					if (IsDlgButtonChecked(hdlg, id))
						gPref.dwNmch |= dwFlag;
					dwFlag <<= 1;
				}
			}

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgNewConference(VOID)
//
//****************************************************************************

BOOL DlgNewConference(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_CONFERENCE),
		ghwndMain, (DLGPROC)ConferenceDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK SendFileDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK SendFileDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hwnd;
	
		CenterWindow(hdlg, ghwndMain);

		hwnd = GetDlgItem(hdlg, IDC_USERNAME);
	
		InitUserLBox(hdlg, TRUE);
		
		// Set the default filename
		SetDlgItemText(hdlg, IDE_FILENAME, gPref.pszFileName);
		
		return TRUE;
	}

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		{
			INmMember * pMember = NULL;
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				if (NULL != pUser)
				{
					pMember = pUser->pMember;
					if (S_OK == pMember->IsSelf())
						pMember = NULL; // everyone
				}
			}
			GetDlgItemPsz(hdlg, IDE_FILENAME, &gPref.pszFileName);

			SendFile(pMember);
			EndDialog(hdlg, 0);
			return TRUE;
		}

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;
		
		case IDB_BROWSE:
		{
			TCHAR szFileName[MAX_PATH + 1];
			ZeroMemory(szFileName, sizeof(TCHAR) * (MAX_PATH + 1));

			// Get the file name
			if (!FGetFileName(szFileName))		//	FGetFileName assumes buffer size is MAX_PATH
				return FALSE;
			
			SetDlgItemText(hdlg, IDE_FILENAME, szFileName);
			return TRUE;
		}

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}

//****************************************************************************
//
// BOOL DlgSendFile(VOID)
//
//****************************************************************************

BOOL DlgSendFile(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_SENDFILE),
		ghwndMain, (DLGPROC)SendFileDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK CallConfDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK CallConfDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		SetDlgItemText(hdlg, IDE_ADDR,       gPref.pszAddr);
		SetDlgItemText(hdlg, IDE_CONFERENCE, gPref.pszConferenceName);
		SetDlgItemText(hdlg, IDE_PASSWORD,   gPref.pszPassword);

		InitLBox(GetDlgItem(hdlg, IDL_ADDR_TYPE),
			_rgAddrType, ARRAY_ELEMENTS(_rgAddrType), gPref.nmAddrType);
		InitLBox(GetDlgItem(hdlg, IDL_CALL_TYPE),
			_rgCallType, ARRAY_ELEMENTS(_rgCallType), gPref.nmCallType);
		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			GetDlgItemPsz(hdlg, IDE_ADDR,       &gPref.pszAddr);
			GetDlgItemPsz(hdlg, IDE_CONFERENCE, &gPref.pszConferenceName);
			GetDlgItemPsz(hdlg, IDE_PASSWORD,   &gPref.pszPassword);

			gPref.nmAddrType = (NM_ADDR_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_ADDR_TYPE));
			gPref.nmCallType = (NM_CALL_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_CALL_TYPE));

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgCallConf(VOID)
//
//****************************************************************************

BOOL DlgCallConf(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_CALL_CONF),
		ghwndMain, (DLGPROC)CallConfDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK CallDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK CallDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		SetDlgItemText(hdlg, IDE_ADDR, gPref.pszAddr);
		InitLBox(GetDlgItem(hdlg, IDL_ADDR_TYPE),
			_rgAddrType, ARRAY_ELEMENTS(_rgAddrType), gPref.nmAddrType);
		InitLBox(GetDlgItem(hdlg, IDL_CALL_TYPE),
			_rgCallType, ARRAY_ELEMENTS(_rgCallType), gPref.nmCallType);
		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			GetDlgItemPsz(hdlg, IDE_ADDR, &gPref.pszAddr);

			gPref.nmAddrType = (NM_ADDR_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_ADDR_TYPE));
			gPref.nmCallType = (NM_CALL_TYPE) GetLBoxDw(GetDlgItem(hdlg, IDL_CALL_TYPE));

			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgNewCall(VOID)
//
//****************************************************************************

BOOL DlgNewCall(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_CALL),
		ghwndMain, (DLGPROC)CallDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK OptionsDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK OptionsDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		CenterWindow(hdlg, ghwndMain);

		CheckDlgButton(hdlg, IDC_MONITOR, gPref.fAutoMonitor);

		CheckDlgButton(hdlg, IDC_HOST, gPref.fAutoHost);
		SetDlgItemText(hdlg, IDE_CONFERENCE_NAME, gPref.pszConferenceName);

		CheckDlgButton(hdlg, IDC_CALL_USER, gPref.fAutoCall);
		SetDlgItemText(hdlg, IDE_USER_NAME, gPref.pszAddr);

		CheckDlgButton(hdlg, IDC_AUTO_CHAT, gPref.fAutoChat);

		CheckDlgButton(hdlg, IDC_MSG_TRACE,   gPref.fMsgTrace);
		CheckDlgButton(hdlg, IDC_MSG_OBJECTS, gPref.fMsgObjects);
		CheckDlgButton(hdlg, IDC_MSG_NOTIFY,  gPref.fMsgNotify);
		CheckDlgButton(hdlg, IDC_MSG_STATE,   gPref.fMsgState);

		CheckRadioButton(hdlg, IDR_INIT_NORMAL, IDR_INIT_BACKGROUND,
			gPref.iInit + IDR_INIT_NORMAL);
		return TRUE;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
			gPref.fAutoMonitor= IsDlgButtonChecked(hdlg, IDC_MONITOR);

			gPref.fAutoHost   = IsDlgButtonChecked(hdlg, IDC_HOST);
			GetDlgItemPsz(hdlg, IDE_CONFERENCE_NAME, &gPref.pszConferenceName);

			gPref.fAutoCall   = IsDlgButtonChecked(hdlg, IDC_CALL_USER);
			GetDlgItemPsz(hdlg, IDE_USER_NAME, &gPref.pszAddr);

			gPref.fAutoChat   = IsDlgButtonChecked(hdlg, IDC_AUTO_CHAT);

			gPref.fMsgTrace   = IsDlgButtonChecked(hdlg, IDC_MSG_TRACE);
			gPref.fMsgObjects = IsDlgButtonChecked(hdlg, IDC_MSG_OBJECTS);
			gPref.fMsgNotify  = IsDlgButtonChecked(hdlg, IDC_MSG_NOTIFY);
			gPref.fMsgState   = IsDlgButtonChecked(hdlg, IDC_MSG_STATE);

			if (IsDlgButtonChecked(hdlg, IDR_INIT_NORMAL))
				gPref.iInit = NM_INIT_NORMAL;
			else if (IsDlgButtonChecked(hdlg, IDR_INIT_CONTROL))
				gPref.iInit = NM_INIT_CONTROL;
			else if (IsDlgButtonChecked(hdlg, IDR_INIT_NO_LAUNCH))
				gPref.iInit = NM_INIT_NO_LAUNCH;
			else if (IsDlgButtonChecked(hdlg, IDR_INIT_BACKGROUND))
				gPref.iInit = NM_INIT_BACKGROUND;


			EndDialog(hdlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgOptions(VOID)
//
//****************************************************************************

BOOL DlgOptions(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_OPTIONS),
		ghwndMain, (DLGPROC)OptionsDlgProc));
}


//****************************************************************************
//
// VOID UpdateAudioSettings(HWND hdlg)
//
//****************************************************************************

VOID UpdateAudioSettings(HWND hdlg)
{
	int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
	if (CB_ERR == iSel)
		return;

	PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
		CB_GETITEMDATA, (WPARAM) iSel, 0);

	if	(NULL == pUser)
	{
		ERROR_MSG(TEXT("UpdateAudioSettings: NULL == pUser"));
		return;
	}

	INmChannelAudio * pChannel = pUser->m_pChannelAudio;
	if (NULL != pChannel)
	{
		NM_AUDIO_STATE uState;
		if (SUCCEEDED(pChannel->GetState(&uState)))
		{
			TRACE_MSG(TEXT("Audio State is %d"), uState);
		}
		
		DWORD dwLevel	= 0;
		if (SUCCEEDED(pChannel->GetProperty(NM_AUDPROP_LEVEL, &dwLevel)))
		{
			SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETPOS, TRUE,
								dwLevel );

			SetDlgItemInt(hdlg, IDE_LEVEL, dwLevel, FALSE);
		}
		
		CheckDlgButton(hdlg, IDC_ACTIVE,
			(S_OK == pChannel->IsActive()) ? BST_CHECKED : BST_UNCHECKED);

		DWORD fPause = FALSE;
		pChannel->GetProperty(NM_AUDPROP_PAUSE, &fPause);
		CheckDlgButton(hdlg, IDC_PAUSE, fPause ? BST_CHECKED : BST_UNCHECKED);
	}
}


//****************************************************************************
//
// LRESULT CALLBACK AudioDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK AudioDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HRESULT hr	= NO_ERROR;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);

		InitUserLBox(hdlg, FALSE);
		
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETRANGEMIN, FALSE,
			0 );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETRANGEMAX, FALSE,
			NM_MAX_AUDIO_LEVEL );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETTICFREQ, 
			8096, 0 );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETPAGESIZE, 
			0, 8096 );
		SendDlgItemMessage (hdlg, IDC_LEVEL, TBM_SETLINESIZE, 
			0, 256 );

		UpdateAudioSettings(hdlg);
		return TRUE;
	}
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;

		case IDB_UPDATE:
		{
			UpdateAudioSettings(hdlg);
			return TRUE;
		}
		
		case IDC_ACTIVE:
		{
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
	
				if	(NULL == pUser)
				{
					ERROR_MSG(TEXT("AudioDlgProc (IDC_ACTIVE): NULL == pUser"));
				}
				else
				{
					INmChannelAudio * pChannel = pUser->m_pChannelAudio;
					if (NULL != pChannel)
					{
						// Flip the active state
						BOOL fActive = (S_OK != pChannel->IsActive());
						hr = pChannel->SetActive(fActive);
						TRACE_MSG(TEXT("SetActive result=%s"), GetHrSz(hr));
					}
				}
			}
			return TRUE;
		}

		case IDC_PAUSE:
		{
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);

				if	(NULL == pUser)
				{
					ERROR_MSG(TEXT("AudioDlgProc (IDC_PAUSE): NULL == pUser"));
				}
				else
				{
					INmChannelAudio * pChannel = pUser->m_pChannelAudio;
					if (NULL != pChannel)
					{
						// Flip the pause state
						DWORD fPause = IsDlgButtonChecked(hdlg, IDC_PAUSE);
						hr = pChannel->SetProperty(NM_AUDPROP_PAUSE, fPause);
						TRACE_MSG(TEXT("SetProperty result=%s"), GetHrSz(hr));
					}
				}
			}
			return TRUE;
		}

		default:
			return TRUE;
		} /* switch (cmd) */

	case WM_HSCROLL:
	{
		DWORD dwLevel = SendDlgItemMessage( hdlg, IDC_LEVEL,
					TBM_GETPOS, 0, 0 );
		SetDlgItemInt(hdlg, IDE_LEVEL, dwLevel, FALSE);

		if (TB_ENDTRACK == LOWORD(wParam))
		{
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);

				if	(NULL == pUser)
				{
					ERROR_MSG(TEXT("AudioDlgProc (WM_HSCROLL): NULL == pUser"));
				}
				else
				{
					INmChannelAudio * pChannel = pUser->m_pChannelAudio;
					if (NULL != pChannel)
					{
						hr = pChannel->SetProperty(NM_AUDPROP_LEVEL, dwLevel);
						TRACE_MSG(TEXT("SetProperty result=%s"), GetHrSz(hr));
					}
				}
			}
		}
		return TRUE;
	}

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgAudio(VOID)
//
//****************************************************************************

BOOL DlgAudio(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_AUDIO),
		ghwndMain, (DLGPROC)AudioDlgProc));
}


//****************************************************************************
//
// Application sharing
//
//****************************************************************************

#define ILV_AS_HWND   0
#define ILV_AS_STATUS 1
#define ILV_AS_NAME   2

static COL _rgColShare[] = {
	{70,  TEXT("Hwnd")},
	{70,  TEXT("Status")},
	{120, TEXT("Name")},
};


//****************************************************************************
//
// VOID FreeShareList(HWND hwnd)
//
//****************************************************************************

VOID FreeShareList(HWND hwnd)
{
	for (int iItem = 0; ; iItem++)
	{
		LV_ITEM lvi;
		ZeroMemory(&lvi, sizeof(LV_ITEM));
		
		lvi.mask = LVIF_PARAM;
		lvi.iItem = iItem;

		if (!ListView_GetItem(hwnd, &lvi))
			break;

		INmSharableApp * pApp = (INmSharableApp *) lvi.lParam;
		ASSERT(NULL != pApp);
		if	(NULL == pApp)
		{
			ERROR_MSG(TEXT("FreeShareList: NULL == pApp"));
			break;
		}

		pApp->Release();
		pApp = NULL;
	}

	ListView_DeleteAllItems(hwnd);
}


//****************************************************************************
//
// VOID UpdateShareList(HWND hwnd)
//
//****************************************************************************

VOID UpdateShareList(HWND hwnd)
{
	LV_ITEM				  lvItem				;
	HRESULT				  hr		= NO_ERROR	;
	ULONG				  cFetched	= 0			;
	IEnumNmSharableApp	* pEnum		= NULL		;
	INmSharableApp		* pApp		= NULL		;
	NM_SHAPP_STATE		  uState				;
	HWND				  hwndApp	= 0			;
	int					  iItem		= 0			;
	BSTR				  bstr		= NULL		;
	LPTSTR				  psz		= NULL		;
	TCHAR				  sz[MAX_PATH + 1]		;

	ZeroMemory(sz, (MAX_PATH + 1) * sizeof(TCHAR));

	FreeShareList(hwnd);

	if (NULL == g_pChannelAppShare)
		return;

	ZeroMemory(&lvItem, sizeof(LV_ITEM));
	lvItem.mask = LVIF_PARAM | LVIF_TEXT;

	hr = g_pChannelAppShare->EnumSharableApp(&pEnum);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("UpdateShareList: EnumSharableApp returned 0x%08X"), hr);
    	return;
	}

	if	(NULL == pEnum)
	{
		ERROR_MSG(TEXT("UpdateShareList: EnumSharableApp returned a Null Ptr"));
		return;
	}

	for ( ; ; )
	{
		hr = pEnum->Next(1, &pApp, &cFetched);
		if FAILED(hr)
			break;

		if	(NULL == pApp)
		{
			ERROR_MSG(TEXT("UpdateShareList: NULL == pApp"));
			break;
		}

		hr = pApp->GetHwnd(&hwndApp);
		_sntprintf(sz, MAX_PATH, TEXT("%08X"), hwndApp);

		lvItem.pszText		= sz;
		lvItem.cchTextMax	= lstrlen(sz);
		lvItem.lParam		= (LPARAM) pApp;
		iItem				= ListView_InsertItem(hwnd, &lvItem);

		hr = pApp->GetState(&uState);
		ListView_SetItemText(hwnd, iItem, ILV_AS_STATUS,
			(NM_SHAPP_SHARED == uState) ? TEXT("Shared") : TEXT("Not Shared"));

		hr = pApp->GetName(&bstr);
		psz = PszFromBstr(bstr);
		SysFreeString(bstr);

		//	Store item to ListView (pApp will be released when removed from ListView)
		ListView_SetItemText(hwnd, iItem, ILV_AS_NAME, psz);
		FreePlpv(&psz);
	}

	pEnum->Release();
	pEnum = NULL;
}


//****************************************************************************
//
// VOID InitShareList(HWND hdlg)
//
//****************************************************************************

VOID InitShareList(HWND hdlg)
{
	HWND hwnd = GetDlgItem(hdlg, IDL_APP);
	
	ASSERT(NULL != hwnd);
	if	(NULL == hwnd)
	{
		ERROR_MSG(TEXT("InitShareList: NULL == hwnd"));
		return;
	}


	// Initialize column data
	{
		int			iCol	= 0				;
		LPCOL		lpCol	= _rgColShare	;
		LV_COLUMN	lvc						;

		ZeroMemory(&lvc, sizeof(LV_COLUMN));
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt  = LVCFMT_LEFT;

		for (iCol = 0; iCol < ARRAY_ELEMENTS(_rgColShare); iCol++)
		{
			lvc.iSubItem = iCol;
			lvc.cx = lpCol->dwWidth;
			lvc.pszText = lpCol->lpsz;
			if (ListView_InsertColumn(hwnd, iCol, &lvc) == -1)
				return;
			lpCol++;
		}
	}

	UpdateShareList(hwnd);
}


//****************************************************************************
//
// LRESULT CALLBACK ShareDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK ShareDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);
		InitShareList(hdlg);
		return TRUE;
	}
	
	case WM_COMMAND:
	{
		UINT wCmd = GET_WM_COMMAND_ID(wParam, lParam);
		switch (wCmd)
		{
		case IDOK:
		case IDCANCEL:
			FreeShareList(GetDlgItem(hdlg, IDL_APP));
			EndDialog(hdlg, 1);
			return TRUE;

		case IDB_UPDATE:
			UpdateShareList(GetDlgItem(hdlg, IDL_APP));
			break;

		case IDB_SHARE:
		case IDB_UNSHARE:
		{
			HRESULT			hr		= NO_ERROR;
			NM_SHAPP_STATE	uState;
			HWND			hwndLv	= GetDlgItem(hdlg, IDL_APP);

			int iItem = ListView_GetNextItem(hwndLv, -1, LVNI_ALL | LVNI_SELECTED);
			if (-1 == iItem)
				break;

			LV_ITEM lvi;
			ZeroMemory(&lvi, sizeof(LV_ITEM));

			lvi.iItem = iItem;
			lvi.mask = LVIF_PARAM;
			if (!ListView_GetItem(hwndLv, &lvi))
				break;

			INmSharableApp * pApp = (INmSharableApp *) lvi.lParam;
			ASSERT(NULL != pApp);
			if	(NULL == pApp)
			{
				ERROR_MSG(TEXT("ShareDlgProc: NULL == pApp"));
				break;
			}

			hr = pApp->GetState(&uState);
			if (FAILED(hr))
			{
				ERROR_MSG(TEXT("Invalid hwnd? hr=%s"), GetHrSz(hr));
				break;
			}
			STATE_MSG(TEXT("Current app share state is %s"), (uState==NM_SHAPP_SHARED) ? "shared" : (uState == NM_SHAPP_NOT_SHARED) ? "not shared": "unknown");
			hr = pApp->SetState((IDB_SHARE == wCmd) ? NM_SHAPP_SHARED : NM_SHAPP_NOT_SHARED);
			return TRUE;
		}

		case IDB_COLLAB:
		case IDB_UNCOLLAB:
		{
			HRESULT			hr		= NO_ERROR;
			NM_SHARE_STATE	uState;

			if	(NULL == g_pChannelAppShare)
			{
				ERROR_MSG(TEXT("ShareDlgProc: NULL == g_pChannelAppShare"));
				break;
			}

			hr = g_pChannelAppShare->GetState(&uState);
			if (FAILED(hr))
			{
				ERROR_MSG(TEXT("Invalid hwnd? hr=%s"), GetHrSz(hr));
				break;
			}

			STATE_MSG(TEXT("Current app collaboration status is %s"), GetCollaborationStateSz(uState));

			{
				// set the state
				switch(uState)
				{
				case NM_SHARE_WORKING_ALONE:
				case NM_SHARE_COLLABORATING:
					hr = g_pChannelAppShare->SetState(NM_SHARE_IN_CONTROL);
					break;

				case NM_SHARE_IN_CONTROL:
					hr = g_pChannelAppShare->SetState(NM_SHARE_WORKING_ALONE);
					break;

				case NM_SHARE_UNKNOWN:
					TRACE_MSG(TEXT("Cannot collaborate"));

				}
			}

			return TRUE;
		}


		default:
			return TRUE;
		} /* switch (cmd) */
	}

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgShare(VOID)
//
//****************************************************************************

BOOL DlgShare(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_SHARE),
		ghwndMain, (DLGPROC)ShareDlgProc));
}


//****************************************************************************
//
// VOID _InitGuidLBox(HWND hwnd)
//
//****************************************************************************

VOID _InitGuidLBox(HWND hwnd)
{
	HRESULT		  hr		= NO_ERROR	;
	DWORD		  dwIndex	= 0			;
	INmSysInfo	* pSysInfo	= NULL		;

	GUID		  guid;
	ZeroMemory(&guid, sizeof(GUID));

	TCHAR		  szGuid[MAX_PATH + 1];
	ZeroMemory(szGuid, (MAX_PATH + 1)*sizeof(TCHAR));

	if	(NULL == g_pMgr)
	{
		ERROR_MSG(TEXT("_InitGuidLBox: NULL == g_pMgr"));
		return;
	}

	hr = g_pMgr->GetSysInfo(&pSysInfo);
	if (FAILED(hr))
	{
		ERROR_MSG(TEXT("GetSysInfo Failed hr=%s"), GetHrSz(hr));
		return;
	}

	if	(NULL == pSysInfo)
	{
		ERROR_MSG(TEXT("GetSysInfo returned a Null Ptr"));
		return;
	}

	// TODO: use INmMgr::GetNmApp to enumerate local items

	GuidToSz((GUID *)&g_guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 

	ZeroMemory(szGuid, (MAX_PATH + 1) * sizeof(TCHAR));
	GuidToSz((GUID *)&g_guidNMUIChat, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 

	memset(&guid, 0x00, sizeof(GUID));
	GuidToSz((GUID *)&guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 
	
	memset(&guid, 0x11, sizeof(GUID));
	GuidToSz((GUID *)&guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 
	
	memset(&guid, 0x22, sizeof(GUID));
	GuidToSz((GUID *)&guid, szGuid);
	dwIndex = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM) szGuid); 

	SendMessage(hwnd, CB_SETCURSEL, 0, 0); 
	pSysInfo->Release();
}


//****************************************************************************
//
// LRESULT CALLBACK LaunchDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK LaunchDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);

		InitUserLBox(hdlg, TRUE);
		_InitGuidLBox(GetDlgItem(hdlg, IDL_GUID));
		return TRUE;
	}
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		{
			// Get the Member
			INmMember * pMember = NULL;
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				if (NULL != pUser)
				{
					pMember = pUser->pMember;
					if (S_OK == pMember->IsSelf())
						pMember = NULL; // everyone
				}
			}

			// Get the Guid
			GUID	guid;
			ZeroMemory(&guid, sizeof(GUID));

			TCHAR	szGuid[MAX_PATH + 1];
			ZeroMemory(szGuid, sizeof(TCHAR) * (MAX_PATH + 1));
			
			GetDlgItemText(hdlg, IDL_GUID, szGuid, MAX_PATH);
			SzToGuid(szGuid, &guid);

			INmConference * pConference = GetCurrentConference();
			HRESULT	hr	= NO_ERROR;

			if (NULL == pConference)
			{
				hr = E_FAIL;
			}
			else
			{
				hr = pConference->LaunchRemote(guid, pMember);
			}

			if (FAILED(hr))
			{
				ERROR_MSG(TEXT("LaunchRemote Failed hr=%s"), GetHrSz(hr));
			}
			else
			{
				EndDialog(hdlg, 1);
			}
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hdlg, 0);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgLaunch(VOID)
//
//****************************************************************************

BOOL DlgLaunch(VOID)
{
	if (NULL == GetCurrentConference())
		return FALSE;

	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_LAUNCH),
		ghwndMain, (DLGPROC)LaunchDlgProc));
}


//****************************************************************************
//
// LRESULT CALLBACK EjectDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK EjectDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);

		InitUserLBox(hdlg, FALSE);
		return TRUE;
	}
	
	case WM_DRAWITEM: 
		DrawUserItem((LPDRAWITEMSTRUCT) lParam);
		break;

	case WM_COMMAND:
		switch (GET_WM_COMMAND_ID(wParam, lParam))
		{
		case IDOK:
		{
			// Get the Member
			INmMember * pMember = NULL;
			int iSel = SendDlgItemMessage(hdlg, IDL_USERS, CB_GETCURSEL, 0, 0);
			if (CB_ERR != iSel)
			{
				PUSER pUser = (PUSER) SendDlgItemMessage(hdlg, IDL_USERS,
					CB_GETITEMDATA, (WPARAM) iSel, 0);
				if (NULL != pUser)
					pMember = pUser->pMember;
			}

			if (NULL != pMember)
			{
				HRESULT hr = pMember->Eject();

				if (FAILED(hr))
				{
					ERROR_MSG(TEXT("Eject Failed hr=%s"), GetHrSz(hr));
				}
			}

			EndDialog(hdlg, 1);
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hdlg, 0);
			return TRUE;

		default:
			return TRUE;
		} /* switch (cmd) */

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgEject(VOID)
//
//****************************************************************************

BOOL DlgEject(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_EJECT),
		ghwndMain, (DLGPROC)EjectDlgProc));
}



//****************************************************************************
//
// LRESULT CALLBACK ShowLocalDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK ShowLocalDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HRESULT		  hr		= NO_ERROR;

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		
		INmSysInfo * pSysInfo	= NULL;
		
		CenterWindow(hdlg, ghwndMain);

		if	(NULL == g_pMgr)
		{
			ERROR_MSG(TEXT("ShowLocalDlgProc: NULL == g_pMgr"));
		}
		else
		{
			hr = g_pMgr->GetSysInfo(&pSysInfo);
			if(FAILED(hr))
				ERROR_MSG(TEXT("GetSysInfo failed (%s)"), GetHrSz(hr));
			else if (NULL == pSysInfo)
				ERROR_MSG(TEXT("ShowLocalDlgProc: NULL == pSysInfo"));
		}

		CheckRadioButton(hdlg, IDC_SHOW_CHAT, IDC_FINDSOMEONE, IDC_SHOW_CHAT);

		if	(NULL != pSysInfo)
		{
			pSysInfo -> Release();
			pSysInfo =  NULL;
		}

		return TRUE;
	}
	case WM_COMMAND:
	{
		UINT		wCmd		= GET_WM_COMMAND_ID(wParam, lParam);
		NM_APPID	AppID;
		INmObject	* pObject	= NULL;	

		switch (wCmd)
		{
		case IDOK:

			if	(NULL == g_pMgr)
			{
				ERROR_MSG(TEXT("ShowLocalDlgProc: NULL == g_pMgr"));
				return FALSE;
			}

			hr = g_pMgr->QueryInterface(IID_INmObject, (void**) &pObject);
			
			ASSERT(NULL != pObject);

			if	(FAILED(hr) || (NULL == pObject))
			{
				ERROR_MSG(TEXT("ShowLocalDlgProc: QI FAILED [hr=%08X ptr=%p]"), hr, pObject);
				return FALSE;
			}

			if(IsDlgButtonChecked(hdlg, IDC_SHOW_FT))
				AppID = NM_APPID_FILE_TRANSFER;
			else if(IsDlgButtonChecked(hdlg, IDC_SHOW_CHAT))
				AppID = NM_APPID_CHAT;
			else if(IsDlgButtonChecked(hdlg, IDC_SHOW_WB))
				AppID = NM_APPID_WHITEBOARD;
			else if(IsDlgButtonChecked(hdlg, IDC_SHOW_T126WB))
				AppID = NM_APPID_T126_WHITEBOARD;
			else if(IsDlgButtonChecked(hdlg, IDC_SHOW_AS))
				AppID = NM_APPID_APPSHARING;
			else if(IsDlgButtonChecked(hdlg, IDC_FINDSOMEONE))
			{
				hr = pObject->CallDialog(NULL, 0);
				EndDialog(hdlg, 1);

				pObject->Release();
				pObject = NULL;

				return TRUE;
			}

			hr = pObject->ShowLocal(AppID);
			if(FAILED(hr))
				ERROR_MSG(TEXT("ShowLocal failed (%s)"), GetHrSz(hr));
			
			pObject -> Release();
			pObject =  NULL;

			// fall through so the dialog goes away!!!
			
		case IDCANCEL:
			EndDialog(hdlg, 1);
			return TRUE;


		default:
			return TRUE;
		} // switch (cmd) 
		
	}

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgShowLocal(VOID)
//
//****************************************************************************

BOOL DlgShowLocal(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_SHOWLOCAL),
		ghwndMain, (DLGPROC)ShowLocalDlgProc));
}




//****************************************************************************
//
// LRESULT CALLBACK LogOnOffDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
//
//****************************************************************************

LRESULT CALLBACK LogOnOffDlgProc(HWND hdlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		CenterWindow(hdlg, ghwndMain);
//		InitShareList(hdlg);
		return TRUE;
	}
	
	case WM_COMMAND:
	{
		UINT wCmd = GET_WM_COMMAND_ID(wParam, lParam);
		switch (wCmd)
		{
		case IDOK:
		case IDCANCEL:
//			FreeShareList(GetDlgItem(hdlg, IDL_APP));
			EndDialog(hdlg, 1);
			return TRUE;

//		case IDB_UPDATE:
//			UpdateShareList(GetDlgItem(hdlg, IDL_APP));
//			break;

		case IDB_SHARE:
		case IDB_UNSHARE:
		{
			HRESULT			hr		= NO_ERROR;
			NM_SHAPP_STATE	uState;
			HWND			hwndLv	= GetDlgItem(hdlg, IDL_APP);
			int				iItem	= ListView_GetNextItem(hwndLv, -1, LVNI_ALL | LVNI_SELECTED);

			if (-1 == iItem)
				break;

			LV_ITEM lvi;
			ZeroMemory(&lvi, sizeof(LV_ITEM));

			lvi.iItem = iItem;
			lvi.mask = LVIF_PARAM;
			if (!ListView_GetItem(hwndLv, &lvi))
				break;

			INmSharableApp * pApp = (INmSharableApp *) lvi.lParam;
			ASSERT(NULL != pApp);
			if	(NULL == pApp)
			{
				ERROR_MSG(TEXT("LogOnOffDlgProc: NULL == pApp"));
				break;
			}

			hr = pApp->GetState(&uState);
			if (FAILED(hr))
			{
				ERROR_MSG(TEXT("Invalid hwnd? hr=%s"), GetHrSz(hr));
				break;
			}
			STATE_MSG(TEXT("Current app share state is %s"), (uState==NM_SHAPP_SHARED) ? "shared" : (uState == NM_SHAPP_NOT_SHARED) ? "not shared": "unknown");
			hr = pApp->SetState((IDB_SHARE == wCmd) ? NM_SHAPP_SHARED : NM_SHAPP_NOT_SHARED);
			return TRUE;
		}

		case IDB_COLLAB:
		case IDB_UNCOLLAB:
		{
			HRESULT			hr		= NO_ERROR;
			NM_SHARE_STATE	uState;

			if	(NULL == g_pChannelAppShare)
			{
				ERROR_MSG(TEXT("LogOnOffDlgProc: NULL == g_pChannelAppShare"));
				break;
			}

			hr = g_pChannelAppShare->GetState(&uState);
			if (FAILED(hr))
			{
				ERROR_MSG(TEXT("Invalid hwnd? hr=%s"), GetHrSz(hr));
				break;
			}

			STATE_MSG(TEXT("Current app collaboration status is %s"), GetCollaborationStateSz(uState));

			{
				// set the state
				switch(uState)
				{
				case NM_SHARE_WORKING_ALONE:
				case NM_SHARE_COLLABORATING:
					hr = g_pChannelAppShare->SetState(NM_SHARE_IN_CONTROL);
					break;

				case NM_SHARE_IN_CONTROL:
					hr = g_pChannelAppShare->SetState(NM_SHARE_WORKING_ALONE);
					break;

				case NM_SHARE_UNKNOWN:
					TRACE_MSG(TEXT("Cannot collaborate"));

				}
			}

			return TRUE;
		}


		default:
			return TRUE;
		} // switch (cmd) 
	}

	default:
		break;
	} /* switch (uMsg) */

	return FALSE;
}


//****************************************************************************
//
// BOOL DlgLogOnOff(VOID)
//
//****************************************************************************

BOOL DlgLogOnOff(VOID)
{
	return (0 == DialogBox(ghInst, MAKEINTRESOURCE(IDD_LOGONOFF),
		ghwndMain, (DLGPROC)LogOnOffDlgProc));
}

BOOL IsSharingEnabled(VOID)
{
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);

	if(FALSE == ::GetVersionEx(&osvi))
	{
		return TRUE;
	}

    if((VER_PLATFORM_WIN32_NT == osvi.dwPlatformId) && (4 >= osvi.dwMajorVersion))
    {
		if(NT_DRIVER_START_DISABLED == GetRegDWORD(HKEY_LOCAL_MACHINE, NM_NT_DISPLAY_DRIVER_KEY, REGVAL_NM_NT_DISPLAY_DRIVER_ENABLED, 0))
		{
			return FALSE;
		}
	}

	return TRUE;

}