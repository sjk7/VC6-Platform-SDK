/*	
	Copyright (c) 1998 by Microsoft Corporation

	THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
	AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
	NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
	MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
	LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
	FOREGOING LIMITATION MAY NOT APPLY.

	This software may be copied and distributed royalty-free subject to
	the following conditions:

	1. You must copy all software without modification and must include
	   all pages, if the software is distributed without inclusion in your
	   software product. If you are incorporating the software in
	   conjunction with and as a part of your software product which adds
	   substantial value, you may modify and include portions of the
	   software.

	2. You must place all copyright notices and other protective
	   disclaimers and notices contained on the software on all copies of
	   the software and your software product.

	3. Unless the software is incorporated in your software product which
	   adds substantial value, you may not distribute this software for
	   profit.

	4. You may not use Microsoft's name, logo, or trademarks to market
	   your software product.

	5. You agree to indemnify, hold harmless, and defend Microsoft and its
	   suppliers from and against any claims or lawsuits, including
	   attorneys' fees, that arise or result from the use or distribution
	   of your software product and any modifications to the software.		
*/


#include "stdafx.h"
#include "MainDlg.h"
#include "About.h"
#include "Error.h"
#include "StrConv.h"
#include "resource.h"
#include "Notify.h"


// Registry

#define MAX_RECENT_FILES		4
#define MAX_RECENT_FILENAME		32
#define ID_RECENT_FILE_0		900

extern	LPCTSTR kpszRegRoot = _T("Software\\Microsoft\\Microsoft Agent\\Tools\\Character Previewer");
static	LPCTSTR kpszRecentFilesSubkey = _T("Software\\Microsoft\\Microsoft Agent\\Tools\\Character Previewer\\Recent Files");
static	LPCTSTR kpszRecentFilesItem = _T("File");

// Static strings

static  LPCTSTR kpszFileTypes = _T("Agent Character Storage (*.acs)\0*.acs\0Agent Character File (*.acf)\0*.acf\0\0");
static	LPCTSTR kpszAgentCharacterTitle = _T("Microsoft Agent");
static	LPCTSTR kpszAgentCharacterOptions = _T("Advanced Character Options");
static	LPCTSTR kpszWindowClass = _T("CAP");

// Globals

extern HINSTANCE g_hInst;
extern MainDlg	*g_pMainDlg;
extern const LPTSTR kpszAppTitle;


// Main Dialog Class

MainDlg::MainDlg() {

	m_hWnd = NULL;
	m_hAccel = NULL;
	m_pAgent = NULL;
	m_pSink = NULL;
	m_pCharacter = NULL;
	m_pBalloon = NULL;
	m_lCharacterID = -1;
	m_lSinkID = -1;
	m_lCmdPropertiesID = -1;
	m_bHasMRUSeparator = FALSE;
	m_bAddedCommands = FALSE;
}


HRESULT MainDlg::Init() {

	// We should only call this once

	_ASSERT(m_pAgent == NULL);

	WNDCLASS wndClass;
	HRESULT hRes;

	// Initialize the Microsoft Agent server

	hRes = CoCreateInstance(CLSID_AgentServer,
							NULL,
							CLSCTX_SERVER,
							IID_IAgentEx,
							(LPVOID *)&m_pAgent);

	// Uh oh!!!

	if (FAILED(hRes))
		return hRes;

	// Create a notify sink object. NOTE: we want to
	// control it's lifetime so we AddRef it.

	m_pSink = new AgentNotifySink(this);

	if (m_pSink == NULL)
		return E_OUTOFMEMORY;

	m_pSink->AddRef();

	// And register it with Microsoft Agent

	hRes = m_pAgent->Register(m_pSink, &m_lSinkID);

	if (FAILED(hRes))
		return hRes;

	// Create/register a window class

	ZeroMemory(&wndClass, sizeof(WNDCLASS));

	wndClass.lpfnWndProc = WndProc;
	wndClass.cbWndExtra = DLGWINDOWEXTRA;
	wndClass.hInstance = g_hInst;
	wndClass.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_APP));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	wndClass.lpszClassName = kpszWindowClass;

	RegisterClass(&wndClass);

	// Create the Main dialog window. NOTE: specifying a NULL
	// DlgProc tells the system to use the DlgProc specified
	// by the class assigned to the dialog in the dialog's 
	// resource.

	m_hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_CAP), NULL, NULL);

	if (m_hWnd == NULL)
		return HRESULT_FROM_WIN32(GetLastError());

	// Stuff the C++ class into window long data

	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
	
	// Initialize the dialog

	OnInitDialog();

	return NOERROR;
}


BOOL MainDlg::OnInitDialog() {

	// Subclass controls (as necessary). This allows us
	// to control the default button state.

	m_wpListBox = (WNDPROC)SetWindowLongPtr(GetDlgItem(m_hWnd, IDC_ANIMATIONS), 
										 GWLP_WNDPROC, 
										 (LONG_PTR)ListBoxWndProc); 

	m_wpSpeakText = (WNDPROC)SetWindowLongPtr(GetDlgItem(m_hWnd, IDC_SPEAKTEXT), 
										   GWLP_WNDPROC, 
										   (LONG_PTR)SpeakTextWndProc); 

	m_wpMoveX = (WNDPROC)SetWindowLongPtr(GetDlgItem(m_hWnd, IDC_MOVE_X), 
									   GWLP_WNDPROC, 
									   (LONG_PTR)MoveXWndProc); 

	m_wpMoveY = (WNDPROC)SetWindowLongPtr(GetDlgItem(m_hWnd, IDC_MOVE_Y), 
									   GWLP_WNDPROC, 
									   (LONG_PTR)MoveYWndProc); 

	// Load the accelerator table

	m_hAccel = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_ACCELERATORS));

	// Initialize the MRU menu

	UpdateRecentFiles(NULL);

	// Set the focus to the empty list box

	SetFocus(GetDlgItem(m_hWnd, IDC_ANIMATIONS));

	return TRUE;
}


void MainDlg::OnDestroy() {

	// Release the balloon interface

	if (m_pBalloon) {
		m_pBalloon->Release();
		m_pBalloon = NULL;
	}

	// Unload/Release the character

	if (m_pCharacter) {

		_ASSERT(m_pAgent);
		_ASSERT(m_lCharacterID != -1);

		m_pAgent->Unload(m_lCharacterID);
		m_pCharacter->Release();
		m_pCharacter = NULL;
	}

	// Release our Agent interface

	if (m_pAgent) {

		if (m_pSink) {

			_ASSERT(m_lSinkID != -1);

			m_pAgent->Unregister(m_lSinkID);
			m_pSink->Release();
			m_pSink = NULL;
		}

		m_pAgent->Release();
		m_pAgent = NULL;
	}
}


BOOL MainDlg::OnInitMenuPopup(HMENU hMenu, UINT uPos, BOOL bSysMenu) {

	// We're not going to allow the dialog to be sized or
	// maximized, so disable those menu items on the context
	// menu.

	if (bSysMenu) {
		EnableMenuItem(hMenu, SC_MAXIMIZE, MF_GRAYED);
		EnableMenuItem(hMenu, SC_MINIMIZE, IsIconic(m_hWnd) ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, SC_RESTORE, IsIconic(m_hWnd) ? MF_ENABLED : MF_GRAYED);
		EnableMenuItem(hMenu, SC_SIZE, MF_GRAYED);
		return TRUE;
	}
	else
		return FALSE;
}


void MainDlg::LoadCharacter(LPCTSTR pszFilename) {

	_ASSERT(m_pAgent);

	HRESULT				hRes;
	OPENFILENAME		ofn;
	_TCHAR				szFilename[_MAX_PATH];
	_TCHAR				szTemp[256];
	_TCHAR			   *pchFilename;
	VARIANT				vFilename;
	VARIANT				vAnimName;
	DWORD				dwRetrieved;
	BOOL				bHasAnims;
	BOOL				bUseSfx;
	UINT				uBalloonStyle;
	BSTR				bszName;
	long				lReqID;
	long				lCharID;
	long				lVisibilityCause;
	IAgentCharacterEx  *pCharacter;
	IUnknown		   *punkAnimNames;
	IEnumVARIANT	   *pevAnimNames;

	USES_CONVERSION;

	// If no filename was specified, bring up the common
	// open dialog to get one from the user.

	if (pszFilename == NULL) {

		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		szFilename[0] = 0;

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = m_hWnd;
		ofn.lpstrDefExt = _T(".acs");
		ofn.Flags = OFN_HIDEREADONLY;
		ofn.lpstrFilter = kpszFileTypes;
		ofn.lpstrFile = szFilename;
		ofn.nMaxFile = _MAX_PATH;

		if (!GetOpenFileName(&ofn))
			return;

		pszFilename = szFilename;
	}

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Construct a VARIANT to hold the filename

	VariantInit(&vFilename);
	vFilename.bstrVal = SysAllocString(T2W(pszFilename));
	vFilename.vt = VT_BSTR;

	// Load the new character. NOTE: we don't release the
	// existing character until we're sure we've successfully
	// loaded the new one.

	hRes = m_pAgent->Load(vFilename, &lCharID, &lReqID);

	// Clean up the VARIANT

	VariantClear(&vFilename);

	// Did we successfully load the character? NOTE: if it's the
	// same character as we already have loaded we'll get the
	// error code AGENTERR_CHARACTERALREADYLOADED.

	if (SUCCEEDED(hRes)) {

		// Get the IAgentCharacterEx interface

		hRes = m_pAgent->GetCharacterEx(lCharID, &pCharacter);
	}

	if (FAILED(hRes)) {
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return;
	}

	// Release the previous balloon interface

	if (m_pBalloon) {
		m_pBalloon->Release();
		m_pBalloon = NULL;
	}

	// Unload the previous character if we have one

	if (m_pCharacter) {
		m_pAgent->Unload(m_lCharacterID);
		m_pCharacter->Release();
	}

	// We'll need to reload our commands. We do this only
	// on a right click for better character load performance.

	m_bAddedCommands = FALSE;

	// Assign our member variables

	m_lCharacterID = lCharID;
	m_pCharacter = pCharacter;

	// Query for the balloon interface

	m_pCharacter->QueryInterface(IID_IAgentBalloonEx, (LPVOID *)&m_pBalloon);

	// Reset the contents of the animation list box

	SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_RESETCONTENT, 0, 0);

	// Add it to the MRU menu

	UpdateRecentFiles(pszFilename);

	// Turn off the Auto-Popup menu. Then we'll add our commands
	// the first time the user right clicks the character.

	m_pCharacter->SetAutoPopupMenu(FALSE);

	// Get the last visibility cause of the character. If
	// it's never been shown we'll position it. Otherwise,
	// we'll leave it alone and assume it's where the user
	// or another app wants it.

	if (SUCCEEDED(m_pCharacter->GetVisibilityCause(&lVisibilityCause))) {

		if (lVisibilityCause == NeverShown) {

			RECT rcWindow;
			long lWidth;
			long lHeight;

			// Get the window rect

			GetWindowRect(m_hWnd, &rcWindow);

			// And the size of the character

			if (SUCCEEDED(m_pCharacter->GetSize(&lWidth, &lHeight))) {

				// Make sure we'll fit to the right (NOTE: a production
				// quality app would handle multi-monitor!!!)

				if ((rcWindow.right + lWidth) > GetSystemMetrics(SM_CXSCREEN))
					rcWindow.right = rcWindow.left - lWidth;
			}

			// Move it (non-animated)

			m_pCharacter->MoveTo((short)rcWindow.right, (short)rcWindow.top, 0, &lReqID);
		}
	}

	// Show the character

	m_pCharacter->Show(FALSE, &lReqID);

	// Get the IUnknown for the animation name enumerator

	if (SUCCEEDED(m_pCharacter->GetAnimationNames(&punkAnimNames))) {

		// Then query for IEnumVARIANT

		if (SUCCEEDED(punkAnimNames->QueryInterface(IID_IEnumVARIANT, (LPVOID *)&pevAnimNames))) {

			while (TRUE) {

				// Get the next animation name

				hRes = pevAnimNames->Next(1, &vAnimName, &dwRetrieved);

				// Was there one?

				if (hRes != NOERROR)
					break;

				// Hmmmm

				_ASSERT(dwRetrieved > 0);
				_ASSERT(vAnimName.vt == VT_BSTR);
				_ASSERT(vAnimName.bstrVal != NULL);

				// Add it to the list box

				SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_ADDSTRING, 0, (LPARAM)W2T(vAnimName.bstrVal));

				// And clean up

				VariantClear(&vAnimName);
			}

			pevAnimNames->Release();
		}

		punkAnimNames->Release();
	}

	// Do we have any animations?

	bHasAnims = (SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_GETCOUNT, 0, 0) > 0);

	if (bHasAnims)
		SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_SETCURSEL, 0, 0);

	// Enable/Disable controls

	EnableWindow(GetDlgItem(m_hWnd, IDC_PLAY), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_STOP), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_SFX), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_STOPBEFOREPLAY), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_SPEAK), bHasAnims && (GetWindowTextLength(GetDlgItem(m_hWnd, IDC_SPEAKTEXT)) > 0));
	EnableWindow(GetDlgItem(m_hWnd, IDC_SPEAKTEXT), bHasAnims);

	EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_USE), bHasAnims);

	EnableWindow(GetDlgItem(m_hWnd, IDC_MOVE_X), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_MOVE_Y), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_MOVE), bHasAnims);

	EnableWindow(GetDlgItem(m_hWnd, IDC_ANIMATIONS_LABEL), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_SPEECHOUTPUT_LABEL), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_POSITION_LABEL), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_X_LABEL), bHasAnims);
	EnableWindow(GetDlgItem(m_hWnd, IDC_Y_LABEL), bHasAnims);

	// Sound Effects

	if (SUCCEEDED(m_pCharacter->GetSoundEffectsOn((long *)&bUseSfx)))
		CheckDlgButton(m_hWnd, IDC_SFX, bUseSfx);
	else
		CheckDlgButton(m_hWnd, IDC_SFX, FALSE);

	// Update the balloon buttons

	uBalloonStyle = 0;

	if (m_pBalloon && bHasAnims) {

		if (SUCCEEDED(m_pBalloon->GetStyle((long *)&uBalloonStyle))) {

			CheckDlgButton(m_hWnd, IDC_BALLOON_USE, uBalloonStyle & BALLOON_STYLE_BALLOON_ON);
			CheckDlgButton(m_hWnd, IDC_BALLOON_SIZETOTEXT, uBalloonStyle & BALLOON_STYLE_SIZETOTEXT);
			CheckDlgButton(m_hWnd, IDC_BALLOON_AUTOPACE, uBalloonStyle & BALLOON_STYLE_AUTOPACE);
			CheckDlgButton(m_hWnd, IDC_BALLOON_AUTOHIDE, uBalloonStyle & BALLOON_STYLE_AUTOHIDE);
		}
	}

	EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_SIZETOTEXT), bHasAnims && (uBalloonStyle & BALLOON_STYLE_BALLOON_ON));
	EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_AUTOPACE), bHasAnims && (uBalloonStyle & BALLOON_STYLE_BALLOON_ON));
	EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_AUTOHIDE), bHasAnims && (uBalloonStyle & BALLOON_STYLE_BALLOON_ON));

	// Call our OnPropertyChange function. This will sync 
	// our dialog with Agent properties.

	OnPropertyChange();

	// Force a WM_SETFOCUS to the animation list box. The
	// subclassed listbox correctly sets the play button's
	// highlight state.

	SetFocus(NULL);
	SetFocus(GetDlgItem(m_hWnd, IDC_ANIMATIONS));

	// Set the text of the title bar

	pchFilename = _tcsrchr(pszFilename, '\\');

	if (pchFilename)
		pchFilename = _tcsinc(pchFilename);
	else
		pchFilename = (LPTSTR)pszFilename;

    ZeroMemory(szTemp, sizeof(szTemp));
    _tcsncpy(szTemp, pchFilename, (sizeof(szTemp) / sizeof(szTemp[0])) - (_tcslen(kpszAppTitle) + 4));
    _tcscat(szTemp, _T(" - "));
    _tcscat(szTemp, kpszAppTitle);

	SetWindowText(m_hWnd, szTemp);

	// Update the "Animations" group box text with the character's
	// name.

	if (SUCCEEDED(m_pCharacter->GetName(&bszName))) {

		_TCHAR szTemplate[64];
		_TCHAR szLabel[256];

		LoadString(GetModuleHandle(NULL), IDS_ANIMATIONS_LABEL, szTemplate, 64);

		_ASSERT(_tcslen(W2T(bszName)) < 192);

		wsprintf(szLabel, szTemplate, W2T(bszName));

		SetWindowText(GetDlgItem(m_hWnd, IDC_ANIMATIONS_LABEL), szLabel);

		SysFreeString(bszName);
	}

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void MainDlg::MakeEllipsisPath(LPCTSTR pszPath, LPTSTR pszEllipsisPath, UINT cchMaxEllipsisPath) {

	// This function takes a full path and truncates to a fixed
	// specified size using ellipses as necessary. It's main goal
	// is to keep the first directory in the path and the filename
	// intact and use ellipsis in the middle.
	// 
	// NOTE: cchMaxEllipsisPath is NOT the size of the pszEllipsisPath
	// buffer (in characters). It is simply the maximum number of 
	// characters to allow in the path so we'd better have room for at
	// least that many.

	_ASSERT(!IsBadWritePtr(pszEllipsisPath, (cchMaxEllipsisPath+1) * sizeof(_TCHAR)));
	_ASSERT(cchMaxEllipsisPath <= _MAX_PATH);

	_TCHAR	szPathCopy[_MAX_PATH];
	_TCHAR *pchEndDir;
	LPCTSTR pchFilename;
	UINT	uPathPartLen;
	UINT	uFilenameLen;

	// If the specified path fits, then just copy it and return

	if ((UINT)lstrlen(pszPath) < cchMaxEllipsisPath) {
		lstrcpy(pszEllipsisPath, pszPath);
		return;
	}

	// See if the filename alone is too big

	pchFilename = _tcsrchr(pszPath, '\\');

	if (pchFilename != NULL)
		pchFilename = _tcsinc(pchFilename);
	else
		pchFilename = pszPath;

	_ASSERT(pchFilename);

	uFilenameLen = lstrlen(pchFilename);
		
	if (uFilenameLen >= cchMaxEllipsisPath) {
		lstrcpyn(pszEllipsisPath, pchFilename, cchMaxEllipsisPath-2);
		lstrcat(pszEllipsisPath, _T("..."));
		return;
	}

	// Save a local copy of the specified path

	lstrcpy(szPathCopy, pszPath);

	pchEndDir = szPathCopy;

	// See if it's a UNC name

	if (_tcsncmp(pchEndDir, _T("\\\\"), 2) == 0) {
		pchEndDir = _tcsinc(pchEndDir);
		pchEndDir = _tcsinc(pchEndDir);
		pchEndDir = _tcschr(pchEndDir, '\\');
	}
	else {
		pchEndDir = _tcschr(pchEndDir, '\\');
		if (pchEndDir) {
			pchEndDir = _tcsinc(pchEndDir);
			pchEndDir = _tcschr(pchEndDir, '\\');
		}
	}

	if (pchEndDir != NULL)
		pchEndDir = _tcsinc(pchEndDir);

	// If we couldn't find the first directory component, give up
	// and just return the filename only.

	if (pchEndDir == NULL) {
		lstrcpy(pszEllipsisPath, pchFilename);
		return;
	}
	
	*pchEndDir = 0;

	uPathPartLen = min((UINT)lstrlen(szPathCopy), cchMaxEllipsisPath - uFilenameLen - 4);

	lstrcpyn(pszEllipsisPath, szPathCopy, uPathPartLen+1);
	lstrcat(pszEllipsisPath, _T("...\\"));
	lstrcat(pszEllipsisPath, pchFilename);
}


void MainDlg::UpdateRecentFiles(LPCTSTR pszFilename) {

	// This function updates our recent file list if a filename
	// is specified or initializes the file menu with existing
	// filenames from the registry.

	LONG	lRes;
	HKEY	hKeyMRU;
	HMENU	hMenuFile;
	DWORD	dwSize;
	DWORD	dwDisposition;
	DWORD	dwRetType;
	int		iNumExisting = 0;
	int		iFind = -1;
	int		iCount;
	int		iFileExitPos;
	_TCHAR	szValueName[256];
	_TCHAR	rgszExisting[MAX_RECENT_FILES][_MAX_PATH];
	_TCHAR	szEllipsisText[_MAX_PATH];
	_TCHAR	szMenuItemText[_MAX_PATH];
	
	// Open/Create the registry key

	lRes = RegCreateKeyEx(HKEY_CURRENT_USER, 
						  kpszRecentFilesSubkey,
					      0, 
					      _T(""),
					      REG_OPTION_NON_VOLATILE,
					      KEY_ALL_ACCESS,
					      NULL,
					      &hKeyMRU,
					      &dwDisposition);
	
	if (lRes != ERROR_SUCCESS)
		return;

	// Get all of the current entries

	for (int i=0; i < MAX_RECENT_FILES; i++) {

		// Format the value string

		wsprintf(szValueName, _T("%s%d"), kpszRecentFilesItem, i+1);

		// Get the next value

		dwSize = _MAX_PATH;

		lRes = RegQueryValueEx(hKeyMRU,
							   szValueName,
							   NULL,
							   &dwRetType,
							   (LPBYTE)rgszExisting[iNumExisting],
							   &dwSize);

		// Was it there?

		if (lRes == ERROR_SUCCESS) {

			// If a filename was specified, see if it matches this one

			if (pszFilename) {

				if (lstrcmpi(pszFilename, rgszExisting[iNumExisting]) == 0) {

					// If the specified file is the first file we find,
					// then we're done.

					if (iNumExisting == 0) {
						RegCloseKey(hKeyMRU);
						return;
					}

					iFind = iNumExisting;
				}
			}

			++iNumExisting;
		}
	}

	// If no filename was specified, and we don't have any
	// existing files, we're done.

	if ((pszFilename == NULL) && (iNumExisting == 0))
		return;

	// If a file was specified, we have to update the registry

	if (pszFilename) {

		// Write the new filename to the registry

		wsprintf(szValueName, _T("%s%d"), kpszRecentFilesItem, 1);
		dwSize = (_tcslen(pszFilename)+1) * sizeof(_TCHAR);
		RegSetValueEx(hKeyMRU, szValueName, 0, REG_SZ, (LPBYTE)pszFilename, dwSize);

		// If we previously had the maximum number of files, and
		// the new one is not one of them, we disregard the last
		// one.

		if ((iNumExisting == MAX_RECENT_FILES) && (iFind < 0))
			--iNumExisting;

		// Now, write the remaining items

		iCount = 1;

		for (i=0; i < iNumExisting; i++) {
			if (i != iFind) {
				wsprintf(szValueName, _T("%s%d"), kpszRecentFilesItem, ++iCount);
				dwSize = (_tcslen(rgszExisting[i])+1) * sizeof(_TCHAR);
				RegSetValueEx(hKeyMRU, szValueName, 0, REG_SZ, (LPBYTE)rgszExisting[i], dwSize);
			}
		}
	}

	// Get the File submenu

	hMenuFile = GetSubMenu(GetMenu(m_hWnd), 0);

	// Delete any existing recent file entries

	for (i=0; i < MAX_RECENT_FILES; i++)
		DeleteMenu(hMenuFile, ID_RECENT_FILE_0+i, MF_BYCOMMAND);

	// Where's the Exit item?

	iFileExitPos = GetMenuItemCount(hMenuFile) - 1;

	// Create an ellipsis path from the specified filename and
	// insert it into the menu.

	if (pszFilename) {
		MakeEllipsisPath(pszFilename, szEllipsisText, MAX_RECENT_FILENAME);
		wsprintf(szMenuItemText, _T("&%d %s"), 1, szEllipsisText);
		InsertMenu(hMenuFile, iFileExitPos-1, MF_BYPOSITION, ID_RECENT_FILE_0, szMenuItemText);
		iCount = 1;
	}
	else {
		iCount = 0;
	}

	// Then do the same for the remaining items

	for (i=0; i < iNumExisting; i++) {
		if (i != iFind) {
			MakeEllipsisPath(rgszExisting[i], szEllipsisText, MAX_RECENT_FILENAME);
			wsprintf(szMenuItemText, _T("&%d %s"), iCount+1, szEllipsisText);
			InsertMenu(hMenuFile, iFileExitPos-1+iCount, MF_BYPOSITION, ID_RECENT_FILE_0+iCount, szMenuItemText);
			++iCount;
		}
	}

	// Delete/Insert the separator as appropriate

	if ((iNumExisting == 0) && (pszFilename == NULL)) {
		if (m_bHasMRUSeparator) {
			DeleteMenu(hMenuFile, iFileExitPos-2, MF_BYPOSITION);
			m_bHasMRUSeparator = FALSE;
		}
	}
	else {
		if (!m_bHasMRUSeparator) {
			InsertMenu(hMenuFile, ID_RECENT_FILE_0, MF_BYCOMMAND | MF_SEPARATOR, 0, NULL);
			m_bHasMRUSeparator = TRUE;
		}
	}

	// We're done with the registry

	RegCloseKey(hKeyMRU);
}


void MainDlg::OnRecentFile(UINT uFile) {

	// Hmmm

	_ASSERT((uFile >= 1) && (uFile <= MAX_RECENT_FILES));

	LONG	lRes;
	DWORD	dwRetType;
	DWORD	dwSize;
	_TCHAR	szValueName[256];
	_TCHAR	szFile[_MAX_PATH];
	HKEY	hKeyMRU;

	// Open the Recent Files subkey

	lRes = RegOpenKeyEx(HKEY_CURRENT_USER,
						kpszRecentFilesSubkey,
						0,
						KEY_ALL_ACCESS,
						&hKeyMRU);

	if (lRes != ERROR_SUCCESS) {
		SystemError(m_hWnd, (HRESULT)HRESULT_FROM_WIN32(lRes), TRUE);
		return;
	}

	// Query the value for the specified item

	wsprintf(szValueName, _T("%s%d"), kpszRecentFilesItem, uFile);

	dwSize = _MAX_PATH;

	lRes = RegQueryValueEx(hKeyMRU,
						   szValueName,
						   NULL,
						   &dwRetType,
						   (LPBYTE)szFile,
						   &dwSize);

	// If we found it, Load the character.

	if ((lRes == ERROR_SUCCESS) && (dwRetType == REG_SZ))
		LoadCharacter(szFile);

	RegCloseKey(hKeyMRU);
}


BOOL MainDlg::OnSysCommand(WPARAM wParam) {

	UINT uCmdType;
	long lReqID;

	uCmdType = wParam & 0xFFF0;

	switch (uCmdType) {
		case SC_CLOSE:
			ShowWindow(m_hWnd, SW_HIDE);
			PostQuitMessage(0);
			return TRUE;

		case SC_MINIMIZE:
			if (m_pCharacter)
				m_pCharacter->Hide(TRUE, &lReqID);
			return FALSE;

		case SC_RESTORE:
			if (m_pCharacter)
				m_pCharacter->Show(TRUE, &lReqID);
			return FALSE;
	}

	return FALSE;
}


void MainDlg::OnDropFiles(HDROP hDrop) {

	_TCHAR szFilename[_MAX_PATH];

	// Make sure only one file was dropped

	if (DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0) > 1)
		return;

	// Get the dropped filename

	DragQueryFile(hDrop, 0, szFilename, _MAX_PATH);

	// And load it

	LoadCharacter(szFilename);
}


void MainDlg::OnSpeak() {

	_ASSERT(m_pCharacter);

	int				iLen;
	long			lReqID;
	LPTSTR			pszTemp;
	BSTR			bszTemp;
	UINT			uBalloonFlags;

	USES_CONVERSION;

	// Get the length of the text to speak

	iLen = GetWindowTextLength(GetDlgItem(m_hWnd, IDC_SPEAKTEXT));

	// We should never be in here if there's no text

	_ASSERT(iLen > 0);

	// Set the balloon style if we have the interface

	if (m_pBalloon) {

		uBalloonFlags = 0;

		if (IsDlgButtonChecked(m_hWnd, IDC_BALLOON_USE))
			uBalloonFlags |= BALLOON_STYLE_BALLOON_ON;

		if (IsDlgButtonChecked(m_hWnd, IDC_BALLOON_SIZETOTEXT))
			uBalloonFlags |= BALLOON_STYLE_SIZETOTEXT;

		if (IsDlgButtonChecked(m_hWnd, IDC_BALLOON_AUTOPACE))
			uBalloonFlags |= BALLOON_STYLE_AUTOPACE;

		if (IsDlgButtonChecked(m_hWnd, IDC_BALLOON_AUTOHIDE))
			uBalloonFlags |= BALLOON_STYLE_AUTOHIDE;

		m_pBalloon->SetStyle((long)uBalloonFlags);
	}

	// Allocate a buffer on the stack

	pszTemp = (LPTSTR)_alloca((iLen + 1) * sizeof(_TCHAR));

	// No need to check for NULL. It wouldn't do us any good
	// anyway since _alloca raises an exception if it fails.
	// Production quality code would wrap this in a __try/__except
	// block.

	GetDlgItemText(m_hWnd, IDC_SPEAKTEXT, pszTemp, iLen + 1);

	// Speak the text

	bszTemp = SysAllocString(T2W(pszTemp));

	if (bszTemp) {

		// Stop the character if the button is checked

		if (IsDlgButtonChecked(m_hWnd, IDC_STOPBEFOREPLAY))
			m_pCharacter->StopAll(STOP_TYPE_ALL);

		m_pCharacter->Speak(bszTemp, NULL, &lReqID);

		SysFreeString(bszTemp);
	}
}


void MainDlg::OnCharacterMove(long x, long y) {

	// Update the position fields

	SetDlgItemInt(m_hWnd, IDC_MOVE_X, x, TRUE);
	SetDlgItemInt(m_hWnd, IDC_MOVE_Y, y, TRUE);
}


void MainDlg::OnCharacterRightClick(long x, long y) {

	_ASSERT(m_pCharacter);

	_TCHAR			szCommand[256];
	BSTR			bszCommand;
	IAgentCommands *pCommands;

	USES_CONVERSION;

	// If we've already added them, the AutoPopup feature will
	// do everything for us.

	if (m_bAddedCommands)
		return;

	m_bAddedCommands = TRUE;

	// Turn AutoPopup back on

	m_pCharacter->SetAutoPopupMenu(TRUE);

	// Query for the IAgentCommands interface

	if (SUCCEEDED(m_pCharacter->QueryInterface(IID_IAgentCommands, (LPVOID *)&pCommands))) {

		// Load our command strings and add them

		LoadString(GetModuleHandle(NULL), IDS_COMMAND_PROPERTIES, szCommand, 256);
	
		bszCommand = SysAllocString(T2W(szCommand));

		if (bszCommand) {

			pCommands->Add(bszCommand, NULL, TRUE, TRUE, &m_lCmdPropertiesID);

			SysFreeString(bszCommand);
		}

		// The AutoPopup menu feature was previously off. So we have
		// to show the popup menu ourself.

		m_pCharacter->ShowPopupMenu((short)x, (short)y);

		// We're done with the IAgentCommands interface

		pCommands->Release();
	}
}


void MainDlg::OnCharacterCommand(long lID) {

	_ASSERT(m_pAgent);
	_ASSERT(m_pCharacter);

	if (lID == m_lCmdPropertiesID) {

		IAgentPropertySheet *pPropSheet;
		RECT rc;
		long lReqID;

		// Query for the IAgentPropertySheet interface

		if (SUCCEEDED(m_pAgent->QueryInterface(IID_IAgentPropertySheet, (LPVOID *)&pPropSheet))) {

			// Show the property sheet

			pPropSheet->SetVisible(TRUE);

			// Get it's rect

			if (SUCCEEDED(pPropSheet->GetPosition(&rc.left, &rc.top)) &&
				SUCCEEDED(pPropSheet->GetSize(&rc.right, &rc.bottom))) {

				rc.right += rc.left;
				rc.bottom += rc.top;

				// Stop the character

				m_pCharacter->StopAll(STOP_TYPE_ALL);

				// And gesture at the property sheet

				m_pCharacter->GestureAt((short)(rc.left + (rc.right - rc.left) / 2),
										(short)(rc.top + (rc.bottom - rc.top) / 2),
										&lReqID);
			}

			pPropSheet->Release();
		}
	}
}


void MainDlg::OnPropertyChange() {

	_ASSERT(m_pAgent);
	_ASSERT(m_pBalloon);

	// The user has changed an Agent property via the
	// Advanced Characters Property Sheet. Update any
	// of our own fields to reflect the change.

	IAgentAudioOutputPropertiesEx *pAudio;
	BOOL bTemp;
	BOOL bUseBalloon;

	if (SUCCEEDED(m_pAgent->QueryInterface(IID_IAgentAudioOutputPropertiesEx, (LPVOID *)&pAudio))) {

		if (SUCCEEDED(pAudio->GetUsingSoundEffects((long *)&bTemp)))
			EnableWindow(GetDlgItem(m_hWnd, IDC_SFX), bTemp);

		pAudio->Release();
	}

	if (SUCCEEDED(m_pBalloon->GetEnabled((long *)&bTemp))) {

		EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_USE), bTemp);

		bUseBalloon = IsWindowEnabled(GetDlgItem(m_hWnd, IDC_BALLOON_USE)) &&
					  IsDlgButtonChecked(m_hWnd, IDC_BALLOON_USE);

		EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_SIZETOTEXT), bUseBalloon);
		EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_AUTOPACE), bUseBalloon);
		EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_AUTOHIDE), bUseBalloon);
	}
}


BOOL MainDlg::OnCommand(WPARAM wParam, LPARAM lParam) {

	WORD wID;

	wID = LOWORD(wParam);

	// First check for a recent file command

	if ((wID >= ID_RECENT_FILE_0) && (wID < ID_RECENT_FILE_0+MAX_RECENT_FILES)) {
		OnRecentFile(wID - ID_RECENT_FILE_0 + 1);
		return TRUE;
	}

	switch (wID) {
		case ID_FILE_OPENCHARACTER:
			LoadCharacter(NULL);
			return TRUE;

		case ID_FILE_EXIT:
			ShowWindow(m_hWnd, SW_HIDE);
			PostQuitMessage(0);
			return TRUE;

		case ID_HELP_ABOUT:

			_ASSERT(m_pAgent);

			short sMajor;
			short sMinor;
			AboutDlg about;

			m_pAgent->GetVersion(&sMajor, &sMinor);

			about.DoModal(m_hWnd, sMajor, sMinor);

			return TRUE;
	}

	return FALSE;
}


void MainDlg::OnButtonClick(UINT uID) {

	// We'd better have a character

	_ASSERT(m_pCharacter);

	int		iCurSel;
	int		iLen;
	LPTSTR	pszTemp;
	BSTR	bszTemp;
	long	lReqID;
	BOOL	bCheck;
	BOOL	bConvert;
	int		iX;
	int		iY;

	USES_CONVERSION;

	switch (uID) {
		case IDC_PLAY:

			// Get the current selection

			iCurSel = (int)SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_GETCURSEL, 0, 0);

			if (iCurSel == LB_ERR)
				return;

			// Get the length of the text

			iLen = (int)SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_GETTEXTLEN, (WPARAM)iCurSel, 0);

			if (iLen == LB_ERR)
				return;

			// Allocate a buffer on the stack

			pszTemp = (LPTSTR)_alloca((iLen + 1) * sizeof(_TCHAR));

			// No need to check for NULL. It wouldn't do us any good
			// anyway since _alloca raises an exception if it fails.
			// Production quality code would wrap this in a __try/__except
			// block.

			SendDlgItemMessage(m_hWnd, IDC_ANIMATIONS, LB_GETTEXT, (WPARAM)iCurSel, (LPARAM)pszTemp);

			// Stop the character if the button is checked

			if (IsDlgButtonChecked(m_hWnd, IDC_STOPBEFOREPLAY))
				m_pCharacter->StopAll(STOP_TYPE_ALL);

			// Play the animation

			bszTemp = SysAllocString(T2W(pszTemp));

			if (bszTemp) {

				m_pCharacter->Play(bszTemp, &lReqID);

				SysFreeString(bszTemp);
			}

			SetFocus(GetDlgItem(m_hWnd, IDC_ANIMATIONS));

			break;


		case IDC_SPEAK:

			OnSpeak();

			SendDlgItemMessage(m_hWnd, IDC_SPEAKTEXT, EM_SETSEL, 0, (LPARAM)-1);
			SetFocus(GetDlgItem(m_hWnd, IDC_SPEAKTEXT));

			break;


		case IDC_MOVE:

			iX = GetDlgItemInt(m_hWnd, IDC_MOVE_X, &bConvert, TRUE);

			if (!bConvert || (iX > 32767) || (iX < -32767))
				break;

			iY = GetDlgItemInt(m_hWnd, IDC_MOVE_Y, &bConvert, TRUE);

			if (!bConvert || (iY > 32767) || (iY < -32767))
				break;

			if (IsDlgButtonChecked(m_hWnd, IDC_STOPBEFOREPLAY))
				m_pCharacter->StopAll(STOP_TYPE_ALL);

			m_pCharacter->MoveTo((short)iX, (short)iY, 1000, &lReqID);

			break;


		case IDC_STOP:

			m_pCharacter->StopAll(STOP_TYPE_ALL);

			break;


		case IDC_SFX:

			m_pCharacter->SetSoundEffectsOn(IsDlgButtonChecked(m_hWnd, IDC_SFX));
			break;


		case IDC_BALLOON_USE:

			bCheck = IsDlgButtonChecked(m_hWnd, IDC_BALLOON_USE);

			EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_SIZETOTEXT), bCheck);
			EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_AUTOPACE), bCheck);
			EnableWindow(GetDlgItem(m_hWnd, IDC_BALLOON_AUTOHIDE), bCheck);

			break;
	}
}


void MainDlg::OnActivateApp(BOOL bActive) {

	_TCHAR	szText[256];
	long	lOtherClients;
	long	lReqID;
	long	lVisibilityCause;

	// If we don't have a character loaded, we're done

	if (m_pCharacter == NULL)
		return;

	// If we're being deactivated, and the foreground
	// window is an Agent character, we don't want to
	// hide the character.

	if (!bActive) {

		// Get the window title text for the foreground window.
		// NOTE: Microsoft Agent character's window titles are
		// always "Microsoft Agent"

		if (GetWindowText(GetForegroundWindow(), szText, 256) > 0) {

			if (lstrcmpi(szText, kpszAgentCharacterTitle) == 0)
				return;

			// Check to see if it's the Agent Character Property
			// Sheet. NOTE: this currently only works on English
			// systems. A more robust way to do this would be to
			// use the process id of the window that is getting
			// focus, and make sure that it's not AgentSvr.exe.

			if (lstrcmpi(szText, kpszAgentCharacterOptions) == 0)
				return;			
		}

		// If the character has other clients, we're not going
		// to hide it.

		if (FAILED(m_pCharacter->HasOtherClients(&lOtherClients)))
			lOtherClients = FALSE;

		if (!lOtherClients)
			m_pCharacter->Hide(TRUE, &lReqID);
	}
	else {

		// Is the window minimized?

		if (!IsIconic(m_hWnd)) {

			// We want to show the character on activation but there's
			// a special case. If the user hid the character we could get
			// a WM_ACTIVATEAPP message after the character window hides.
			// In that case, we sure don't want to show the character. So
			// check the visibility cause of the character. If the user hid
			// it, we won't show it.

			if (SUCCEEDED(m_pCharacter->GetVisibilityCause(&lVisibilityCause))) {
				if (lVisibilityCause == UserHid)
					return;
			}

			m_pCharacter->Show(TRUE, &lReqID);
		}
	}
}


LRESULT	CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	MainDlg *pDlg;

	pDlg = (MainDlg *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	switch (uMsg) {
		case WM_ACTIVATEAPP:
			pDlg->OnActivateApp((BOOL)wParam);
			break;

		case WM_COMMAND:
			switch (HIWORD(wParam)) {

				// First check for 0.  This is BN_CLICKED.  If lParam is 0
				// then it's a menu item selection.  If lParam is 1, it's
				// an accelerator key.  Otherwise, assume it's a button click.

				case 0:
					if ((lParam == 0) || (lParam == 1)) {
						if (!pDlg->OnCommand(wParam, lParam))
							return DefDlgProc(hWnd, uMsg, wParam, lParam);
					}
					else
						pDlg->OnButtonClick(LOWORD(wParam));
					
					break;

				case 1:
					if (!pDlg->OnCommand(wParam, lParam))
						return DefDlgProc(hWnd, uMsg, wParam, lParam);

					break;

				case EN_CHANGE:

					if (LOWORD(wParam) == IDC_SPEAKTEXT) {
						
						BOOL bEnable;

						// Enable the Speak button if there are animations and text
						// in the speak text edit field.

						bEnable = (SendDlgItemMessage(pDlg->m_hWnd, IDC_ANIMATIONS, LB_GETCOUNT, 0, 0) > 0) &&
								  (GetWindowTextLength(GetDlgItem(pDlg->m_hWnd, IDC_SPEAKTEXT)) > 0);

						// If we're enabling and the button isn't already enabled,
						// enable it and make it the default button. If we're disabling
						// and the button is enabled, disable it and turn off it's
						// default button status.

						if (bEnable && !IsWindowEnabled(GetDlgItem(pDlg->m_hWnd, IDC_SPEAK))) {
							EnableWindow(GetDlgItem(pDlg->m_hWnd, IDC_SPEAK), TRUE);
							SendMessage(pDlg->m_hWnd, DM_SETDEFID, IDC_SPEAK, 0);
						}
						else if (!bEnable && IsWindowEnabled(GetDlgItem(pDlg->m_hWnd, IDC_SPEAK))) {
							EnableWindow(GetDlgItem(pDlg->m_hWnd, IDC_SPEAK), FALSE);
							SendMessage(pDlg->m_hWnd, DM_SETDEFID, 0, 0);
						}
					}

					break;
			}
			break;

		case WM_DESTROY:
			pDlg->OnDestroy();
			break;

		case WM_DROPFILES:
			pDlg->OnDropFiles((HDROP)wParam);
			break;

		case WM_INITMENUPOPUP:
			if (!pDlg->OnInitMenuPopup((HMENU)wParam, (UINT)LOWORD(lParam), (BOOL)HIWORD(lParam)))
				return DefDlgProc(hWnd, uMsg, wParam, lParam);
			break;
		
		case WM_SYSCOMMAND:
			if (!pDlg->OnSysCommand(wParam))
				DefDlgProc(hWnd, uMsg, wParam, lParam);
			break;

		default:
			return DefDlgProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}


LRESULT	CALLBACK ListBoxWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	_ASSERT(g_pMainDlg);

	switch (uMsg) {
		case WM_SETFOCUS:
			if (g_pMainDlg->m_pCharacter)
				SendMessage(GetParent(hWnd), DM_SETDEFID, IDC_PLAY, 0);
			break;

		case WM_LBUTTONDBLCLK:
			if (g_pMainDlg->m_pCharacter)
				g_pMainDlg->OnButtonClick(IDC_PLAY);
			return 0;
	}

	return CallWindowProc(g_pMainDlg->m_wpListBox, hWnd, uMsg, wParam, lParam);
}


LRESULT	CALLBACK SpeakTextWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	_ASSERT(g_pMainDlg);

	switch (uMsg) {
		case WM_SETFOCUS:
			_ASSERT(g_pMainDlg->m_pCharacter);
			if (GetWindowTextLength(hWnd) > 0)
				SendMessage(GetParent(hWnd), DM_SETDEFID, IDC_SPEAK, 0);
			break;
	}

	return CallWindowProc(g_pMainDlg->m_wpSpeakText, hWnd, uMsg, wParam, lParam);
}


LRESULT	CALLBACK MoveXWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	_ASSERT(g_pMainDlg);

	switch (uMsg) {
		case WM_SETFOCUS:
			_ASSERT(g_pMainDlg->m_pCharacter);
			SendMessage(GetParent(hWnd), DM_SETDEFID, IDC_MOVE, 0);
			break;
	}

	return CallWindowProc(g_pMainDlg->m_wpMoveX, hWnd, uMsg, wParam, lParam);
}


LRESULT	CALLBACK MoveYWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	_ASSERT(g_pMainDlg);

	switch (uMsg) {
		case WM_SETFOCUS:
			_ASSERT(g_pMainDlg->m_pCharacter);
			SendMessage(GetParent(hWnd), DM_SETDEFID, IDC_MOVE, 0);
			break;
	}

	return CallWindowProc(g_pMainDlg->m_wpMoveY, hWnd, uMsg, wParam, lParam);
}
