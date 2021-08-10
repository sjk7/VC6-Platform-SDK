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
#include "CapMFC.h"
#include "MainDlg.h"

// NOTE: see stdafx.h for inclusion of ClassWizard generated
// AgentControl headers.


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Registry

#define MAX_RECENT_FILES		4
#define MAX_RECENT_FILENAME		32
#define ID_RECENT_FILE_0		900

extern	LPCTSTR kpszRegRoot = _T("Software\\Microsoft\\Microsoft Agent\\Tools\\Character Previewer");
static	LPCTSTR kpszRecentFilesSubkey = _T("Software\\Microsoft\\Microsoft Agent\\Tools\\Character Previewer\\Recent Files");
static	LPCTSTR kpszRecentFilesItem = _T("File");

// Static strings

static	LPCTSTR kpszAgentCharacterTitle = _T("Microsoft Agent");
static	LPCTSTR kpszAgentCharacterOptions = _T("Advanced Character Options");
static  LPCTSTR kpszFileTypes = _T("Agent Character Storage (*.acs)|*.acs|Agent Character File (*.acf)|*.acf||");
static	LPCTSTR kpszID1 = _T("Character1");
static	LPCTSTR kpszID2 = _T("Character2");
static	LPCTSTR	kpszCommandProperties = _T("Properties");

extern const LPTSTR kpszAppTitle;


// Standard MFC About Dialog

class CAboutDlg : public CDialog {
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {

	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}


BOOL CAboutDlg::OnInitDialog() {

	_TCHAR	szExe[_MAX_PATH];
	_TCHAR	szVersion[256];
	DWORD	dwVersionSize;
	DWORD	dwTemp;
	void   *pData;
	void   *pVerInfo;
	UINT	uVerInfoSize;

	CDialog::OnInitDialog();
	
	// Add the version number to the dialog

	GetModuleFileName(NULL, szExe, _MAX_PATH);

	dwVersionSize = GetFileVersionInfoSize(szExe, &dwTemp);

	// There better be version data

	_ASSERT(dwVersionSize != 0);

	try {
		pData = _alloca(dwVersionSize);
	}
	catch (...) {
		pData = NULL;
	}

	if (pData) {

		GetFileVersionInfo(szExe, 0, dwVersionSize, pData);

		if (VerQueryValue(pData, _T("\\"), &pVerInfo, &uVerInfoSize)) {
			wsprintf(szVersion, 
					 _T("%d.%.2d.%d.%d"), 
					 HIWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionMS),
					 LOWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionMS),
					 HIWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionLS),
					 LOWORD(((VS_FIXEDFILEINFO *)pVerInfo)->dwFileVersionLS));
			::SetDlgItemText(m_hWnd, IDC_VERSION, szVersion);
		}
	}

	return TRUE;
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX) {

	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// Main Dialog

CCapMFCDlg::CCapMFCDlg(CWnd* pParent) : CDialog(CCapMFCDlg::IDD, pParent) {

	//{{AFX_DATA_INIT(CCapMFCDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pszCurCharID = NULL;
	m_bHasMRUSeparator = FALSE;
}


void CCapMFCDlg::DoDataExchange(CDataExchange* pDX) {

	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CCapMFCDlg)
	DDX_Control(pDX, IDC_Y_LABEL, m_YLabel);
	DDX_Control(pDX, IDC_X_LABEL, m_XLabel);
	DDX_Control(pDX, IDC_POSITION_LABEL, m_PositionLabel);
	DDX_Control(pDX, IDC_MOVE_Y, m_MoveY);
	DDX_Control(pDX, IDC_MOVE_X, m_MoveX);
	DDX_Control(pDX, IDC_MOVE, m_Move);
	DDX_Control(pDX, IDC_BALLOON_USE, m_BalloonEnabled);
	DDX_Control(pDX, IDC_BALLOON_SIZETOTEXT, m_BalloonSizeToText);
	DDX_Control(pDX, IDC_BALLOON_AUTOPACE, m_BalloonAutoPace);
	DDX_Control(pDX, IDC_BALLOON_AUTOHIDE, m_BalloonAutoHide);
	DDX_Control(pDX, IDC_SPEAK, m_Speak);
	DDX_Control(pDX, IDC_SPEECHOUTPUT_LABEL, m_SpeechOutputLabel);
	DDX_Control(pDX, IDC_SPEAKTEXT, m_SpeakText);
	DDX_Control(pDX, IDC_SFX, m_Sfx);
	DDX_Control(pDX, IDC_STOP, m_Stop);
	DDX_Control(pDX, IDC_STOPBEFOREPLAY, m_StopBeforePlay);
	DDX_Control(pDX, IDC_PLAY, m_Play);
	DDX_Control(pDX, IDC_ANIMATIONS_LABEL, m_AnimationsLabel);
	DDX_Control(pDX, IDC_ANIMATIONS, m_Animations);
	DDX_Control(pDX, IDC_AGENT, m_Agent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCapMFCDlg, CDialog)
	//{{AFX_MSG_MAP(CCapMFCDlg)
	ON_WM_DROPFILES()
	ON_WM_ACTIVATEAPP()
	ON_WM_INITMENUPOPUP()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_LBN_DBLCLK(IDC_ANIMATIONS, OnDblclkAnimations)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_SFX, OnSfx)
	ON_BN_CLICKED(IDC_SPEAK, OnSpeak)
	ON_EN_CHANGE(IDC_SPEAKTEXT, OnChangeSpeakText)
	ON_EN_SETFOCUS(IDC_SPEAKTEXT, OnSetFocusSpeakText)
	ON_BN_CLICKED(IDC_BALLOON_USE, OnBalloonUse)
	ON_BN_CLICKED(IDC_MOVE, OnMove)
	ON_EN_SETFOCUS(IDC_MOVE_X, OnSetFocusMoveX)
	ON_EN_SETFOCUS(IDC_MOVE_Y, OnSetFocusMoveY)
	ON_LBN_SETFOCUS(IDC_ANIMATIONS, OnSetFocusAnimations)
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CCapMFCDlg::OnInitDialog() {

	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	// We don't want the Agent control to throw exceptions. We'd 
	// rather have HRESULTs returned. If you want to use exception
	// handling instead, remove/comment the next line.

	m_Agent.SetRaiseRequestErrors(FALSE);
	
	// Initialize the MRU menu

	UpdateRecentFiles(NULL);

	return TRUE;
}


void CCapMFCDlg::OnDropFiles(HDROP hDropInfo) {

	TCHAR szFilename[_MAX_PATH];

	// Handle drag and drop

	::DragQueryFile(hDropInfo, 0, szFilename, _MAX_PATH);
	::DragFinish(hDropInfo);
	
	LoadCharacter(szFilename);
}


void CCapMFCDlg::OnSysCommand(UINT nID, LPARAM lParam) {

	COleVariant vFast;

	vFast.vt = VT_BOOL;
	vFast.boolVal = VARIANT_TRUE;

	// If the dialog is getting minimized, hide the character. If it's
	// being restore, show it.

	switch (nID) {
		case SC_MINIMIZE:
			if (m_pszCurCharID)
				m_Agent.GetCharacters().Character(m_pszCurCharID).Hide(vFast);
			break;

		case SC_RESTORE:
			if (m_pszCurCharID)
				m_Agent.GetCharacters().Character(m_pszCurCharID).Show(vFast);
			break;
	}

	CDialog::OnSysCommand(nID, lParam);
}


void CCapMFCDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT uIndex, BOOL bSysMenu) {

	CDialog::OnInitMenuPopup(pPopupMenu, uIndex, bSysMenu);

	// We're not going to allow the dialog to be sized or
	// maximized, so disable those menu items on the context
	// menu.

	if (bSysMenu) {
		pPopupMenu->EnableMenuItem(SC_MAXIMIZE, MF_GRAYED);
		pPopupMenu->EnableMenuItem(SC_MINIMIZE, IsIconic() ? MF_GRAYED : MF_ENABLED);
		pPopupMenu->EnableMenuItem(SC_RESTORE, IsIconic() ? MF_ENABLED : MF_GRAYED);
		pPopupMenu->EnableMenuItem(SC_SIZE, MF_GRAYED);
	}
}


void CCapMFCDlg::OnActivateApp(BOOL bActive, DWORD hTask) {

	_TCHAR szText[256];
	CAgentCtlCharacterEx Character;
	COleVariant vFast;

	vFast.vt = VT_BOOL;
	vFast.boolVal = VARIANT_TRUE;

	// If we don't have a character loaded, we're done

	if (m_pszCurCharID == NULL)
		return;

	Character = m_Agent.GetCharacters().Character(m_pszCurCharID);

	// If we're being deactivated, and the foreground
	// window is an Agent character, we don't want to
	// hide the character.

	if (!bActive) {

		// Get the window title text for the foreground window.
		// NOTE: Microsoft Agent character's window titles are
		// always "Microsoft Agent"

		if (::GetWindowText(::GetForegroundWindow(), szText, 256) > 0) {

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

		if (!Character.GetHasOtherClients())
			Character.Hide(vFast);
	}
	else {

		// Is the window minimized?

		if (!IsIconic()) {

			// We want to show the character on activation but there's
			// a special case. If the user hid the character we could get
			// a WM_ACTIVATEAPP message after the character window hides.
			// In that case, we sure don't want to show the character. So
			// check the visibility cause of the character. If the user hid
			// it, we won't show it.

			if ((Character.GetVisibilityCause() == UserHid) ||
				(Character.GetVisibilityCause() == UserHidViaCharacterMenu))
				return;

			Character.Show(vFast);
		}
	}
}


void CCapMFCDlg::OnPaint() {

	// If you add a minimize button to your dialog, you will need the code below
	// to draw the icon.  For MFC applications using the document/view model,
	// this is automatically done for you by the framework.

	if (IsIconic()) {

		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);

		CRect rect;

		GetClientRect(&rect);

		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon

		dc.DrawIcon(x, y, m_hIcon);
	}
	else {

		CDialog::OnPaint();
	}
}


HCURSOR CCapMFCDlg::OnQueryDragIcon() {

	return (HCURSOR) m_hIcon;
}


void CCapMFCDlg::OnFileExit() {

	ShowWindow(SW_HIDE);
	PostQuitMessage(0);	
}


void CCapMFCDlg::OnFileOpen() {

	CString psz;
	psz.Empty();
	LoadCharacter(psz);	
}


void CCapMFCDlg::OnHelpAbout() {

	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CCapMFCDlg::LoadCharacter(CString pszFilename) {

	HRESULT					hRes;
	BOOL					bHasAnims;
	CString					szFilename;
	_TCHAR				   *pchFilename;
	CAgentCtlRequest		AgentRequest;
	CAgentCtlCharacterEx	Character;
	LPCTSTR					kpszNewID;
	_TCHAR					szTemp[256];
	UINT					uBalloonStyle;
	COleVariant				vEmpty;
	DWORD					dwRetrieved;
	VARIANT					vAnimName;
	IUnknown			   *punkAnimNames;
	IEnumVARIANT		   *pevAnimNames;

	// If no filename was specified, bring up the common
	// open dialog to get one from the user.

	if (pszFilename.IsEmpty()) {

		CFileDialog fd(TRUE, _T(".acs"), NULL, OFN_HIDEREADONLY, kpszFileTypes, this);

		if (fd.DoModal() == IDCANCEL)
			return;

		szFilename = fd.GetPathName();
		pszFilename = szFilename;
	}

	SetCursor(LoadCursor(NULL, IDC_WAIT));

	// Construct a VARIANT to hold the filename

	COleVariant v(pszFilename);

	// Load the new character. NOTE: we don't release the
	// existing character until we're sure we've successfully
	// loaded the new one.

	if (m_pszCurCharID == NULL)
		kpszNewID = kpszID1;
	else if (m_pszCurCharID == kpszID1)
		kpszNewID = kpszID2;
	else
		kpszNewID = kpszID1;

	AgentRequest = m_Agent.GetCharacters().Load(kpszNewID, v);

	// Did we successfully load the character? NOTE: if it's the
	// same character as we already have loaded we'll get the
	// error code AGENTERR_CHARACTERALREADYLOADED.

	if (AgentRequest.GetStatus() != RequestSuccess) {
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		return;
	}

	// Unload the previous character if we have one

	if (m_pszCurCharID)
		m_Agent.GetCharacters().Unload(m_pszCurCharID);

	// Save the new id

	m_pszCurCharID = kpszNewID;
	Character = m_Agent.GetCharacters().Character(m_pszCurCharID);

	// Reset the contents of the animation list box

	m_Animations.ResetContent();

	// Add it to the MRU menu

	UpdateRecentFiles(pszFilename);

	// Get the last visibility cause of the character. If
	// it's never been shown we'll position it. Otherwise,
	// we'll leave it alone and assume it's where the user
	// or another app wants it.

	if (Character.GetVisibilityCause() == NeverShown) {

		CRect rcWindow;

		// Get the window rect

		GetWindowRect(&rcWindow);

		// Make sure we'll fit to the right (NOTE: a production
		// quality app would handle multi-monitor!!!)

		if ((rcWindow.right + Character.GetWidth()) > GetSystemMetrics(SM_CXSCREEN))
			rcWindow.right = rcWindow.left + Character.GetWidth();

		// Move it (non-animated)

		Character.MoveTo((short)rcWindow.right, (short)rcWindow.top, vEmpty);
	}

	// Add commands

	CString pszCommand;
	pszCommand.LoadString(IDS_COMMAND_PROPERTIES);
	COleVariant vCommand(pszCommand);

	Character.GetCommands().Add(kpszCommandProperties, vCommand, vEmpty, vEmpty, vEmpty);

	// Show the character (animated)

	Character.Show(vEmpty);

	// Populate the listbox with the character's animation names.
	// This is a little tricky since MFC does not generate a wrapper
	// for the Enum method of IAgentCtlAnimationNames. So we'll have
	// to get the IUnknown ourself via GetProperty.

	Character.GetAnimationNames().GetProperty(DISPID_NEWENUM, VT_UNKNOWN, (void *)&punkAnimNames);

	// We've got the IUnknown, now query for IEnumVARIANT

	hRes = punkAnimNames->QueryInterface(IID_IEnumVARIANT, (LPVOID *)&pevAnimNames);

	// We're done with the IUnknown no matter what

	punkAnimNames->Release();

	// Did we get IEnumVARIANT?

	if (SUCCEEDED(hRes)) {

		while (TRUE) {

			// Get the next animation name

			if (pevAnimNames->Next(1, &vAnimName, &dwRetrieved) != NOERROR)
				break;

			// Hmmmm

			_ASSERT(dwRetrieved > 0);
			_ASSERT(vAnimName.vt == VT_BSTR);
			_ASSERT(vAnimName.bstrVal != NULL);

			CString pszAnimName(vAnimName.bstrVal);

			// Add it to the list box

			m_Animations.AddString((LPCTSTR)pszAnimName);

			// And clean up

			VariantClear(&vAnimName);
		}

		pevAnimNames->Release();
	}

	// Do we have any animations?

	bHasAnims = (m_Animations.GetCount() > 0);

	if (bHasAnims)
		m_Animations.SetCurSel(0);

	// Enable/Disable controls

	m_Play.EnableWindow(bHasAnims);
	m_StopBeforePlay.EnableWindow(bHasAnims);
	m_Stop.EnableWindow(bHasAnims);
	m_Sfx.EnableWindow(bHasAnims);
	m_Speak.EnableWindow(bHasAnims && (m_SpeakText.GetWindowTextLength() > 0));
	m_SpeakText.EnableWindow(bHasAnims);
	m_SpeechOutputLabel.EnableWindow(bHasAnims);
	m_BalloonEnabled.EnableWindow(bHasAnims);

	m_AnimationsLabel.EnableWindow(bHasAnims);

	// Sound Effects

	m_Sfx.SetCheck(Character.GetSoundEffectsOn());

	// Update the balloon buttons

	uBalloonStyle = 0;

	if (bHasAnims) {

		uBalloonStyle = Character.GetBalloon().GetStyle();

		m_BalloonEnabled.SetCheck(uBalloonStyle & BALLOON_STYLE_BALLOON_ON);
		m_BalloonSizeToText.SetCheck(uBalloonStyle & BALLOON_STYLE_SIZETOTEXT);
		m_BalloonAutoPace.SetCheck(uBalloonStyle & BALLOON_STYLE_AUTOPACE);
		m_BalloonAutoHide.SetCheck(uBalloonStyle & BALLOON_STYLE_AUTOHIDE);
	}

	m_BalloonSizeToText.EnableWindow(bHasAnims && (uBalloonStyle & BALLOON_STYLE_BALLOON_ON));
	m_BalloonAutoPace.EnableWindow(bHasAnims && (uBalloonStyle & BALLOON_STYLE_BALLOON_ON));
	m_BalloonAutoHide.EnableWindow(bHasAnims && (uBalloonStyle & BALLOON_STYLE_BALLOON_ON));

	m_Move.EnableWindow(bHasAnims);
	m_MoveX.EnableWindow(bHasAnims);
	m_MoveY.EnableWindow(bHasAnims);
	m_PositionLabel.EnableWindow(bHasAnims);
	m_XLabel.EnableWindow(bHasAnims);
	m_YLabel.EnableWindow(bHasAnims);

	// Call our OnPropertyChange function. This will sync 
	// our dialog with Agent properties.

	OnAgentPropertyChange();

	m_Animations.SetFocus();

	// Set the text of the title bar

	pchFilename = _tcsrchr(pszFilename, '\\');

	if (pchFilename)
		pchFilename = _tcsinc(pchFilename);
	else
		pchFilename = (LPTSTR)(LPCTSTR)pszFilename;

    ZeroMemory(szTemp, sizeof(szTemp));
    _tcsncpy(szTemp, pchFilename, (sizeof(szTemp) / sizeof(szTemp[0])) - (_tcslen(kpszAppTitle) + 4));
    _tcscat(szTemp, _T(" - "));
    _tcscat(szTemp, kpszAppTitle);

	SetWindowText(szTemp);

	// Update the "Animations" group box text with the character's
	// name.

	CString szTemplate;

	szTemplate.LoadString(IDS_ANIMATIONS_LABEL);

	_ASSERT(szTemplate.GetLength() + Character.GetName().GetLength() < 256);

	wsprintf(szTemp, szTemplate, Character.GetName());

	m_AnimationsLabel.SetWindowText(szTemp);

	SetCursor(LoadCursor(NULL, IDC_ARROW));
}


void CCapMFCDlg::OnFinalRelease() {

	// If we have a character, unload it now

	if (m_pszCurCharID)
		m_Agent.GetCharacters().Unload(m_pszCurCharID);
	
	CDialog::OnFinalRelease();
}


void CCapMFCDlg::MakeEllipsisPath(LPCTSTR pszPath, LPTSTR pszEllipsisPath, UINT cchMaxEllipsisPath) {

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


void CCapMFCDlg::UpdateRecentFiles(LPCTSTR pszFilename) {

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

		dwSize = _MAX_PATH * sizeof(_TCHAR);

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

	hMenuFile = GetMenu()->GetSubMenu(0)->m_hMenu;

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


void CCapMFCDlg::OnRecentFile(UINT uFile) {

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

	if (lRes != ERROR_SUCCESS)
		return;

	// Query the value for the specified item

	wsprintf(szValueName, _T("%s%d"), kpszRecentFilesItem, uFile);

	dwSize = _MAX_PATH * sizeof(_TCHAR);

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


void CCapMFCDlg::OnPlay() {

	// We'd better have a character at this point

	_ASSERT(m_pszCurCharID);

	int iCurSel;
	CAgentCtlCharacterEx Character;
	COleVariant vEmpty;

	// Get the current selection

	iCurSel = m_Animations.GetCurSel();

	// Is there one?

	if (iCurSel == LB_ERR)
		return;

	// Shortcut to the character

	Character = m_Agent.GetCharacters().Character(m_pszCurCharID);

	// Stop the character if the button is checked

	if (m_StopBeforePlay.GetCheck())
		Character.StopAll(vEmpty);

	// Play the animation

	CString pszAnim;
	m_Animations.GetText(iCurSel, pszAnim);

	Character.Play(pszAnim);

	m_Animations.SetFocus();
}


void CCapMFCDlg::OnDblclkAnimations() {

	OnPlay();	
}


void CCapMFCDlg::OnStop() {

	_ASSERT(m_pszCurCharID);

	COleVariant vEmpty;

	m_Agent.GetCharacters().Character(m_pszCurCharID).StopAll(vEmpty);
}


void CCapMFCDlg::OnSfx() {

	_ASSERT(m_pszCurCharID);

	m_Agent.GetCharacters().Character(m_pszCurCharID).SetSoundEffectsOn(m_Sfx.GetCheck());
}


void CCapMFCDlg::OnSpeak() {

	_ASSERT(m_pszCurCharID);
	
	// We should never be in here if there's no text

	_ASSERT(m_SpeakText.GetWindowTextLength() > 0);

	CAgentCtlCharacterEx Character;
	COleVariant vEmpty;
	COleVariant vText;
	CString pszText;
	UINT uBalloonFlags;

	// Shortcut to the character

	Character = m_Agent.GetCharacters().Character(m_pszCurCharID);

	// Set the balloon style if we have the interface

	uBalloonFlags = 0;

	if (m_BalloonEnabled.GetCheck())
		uBalloonFlags |= BALLOON_STYLE_BALLOON_ON;

	if (m_BalloonSizeToText.GetCheck())
		uBalloonFlags |= BALLOON_STYLE_SIZETOTEXT;

	if (m_BalloonAutoPace.GetCheck())
		uBalloonFlags |= BALLOON_STYLE_AUTOPACE;

	if (m_BalloonAutoHide.GetCheck())
		uBalloonFlags |= BALLOON_STYLE_AUTOHIDE;

	Character.GetBalloon().SetStyle((long)uBalloonFlags);

	// Should we stop the character?

	if (m_StopBeforePlay.GetCheck())
		Character.StopAll(vEmpty);

	// Speak the text

	m_SpeakText.GetWindowText(pszText);
	vText = pszText;

	Character.Speak(vText, vEmpty);

	// Reselect the text and set the focus back to the 
	// edit field.

	m_SpeakText.SetSel(0, -1);
	m_SpeakText.SetFocus();
}


void CCapMFCDlg::OnChangeSpeakText() {

	BOOL bEnable;

	// Enable the Speak button if there are animations and text
	// in the speak text edit field.

	bEnable = (m_Animations.GetCount() > 0) && (m_SpeakText.GetWindowTextLength() > 0);

	// If we're enabling and the button isn't already enabled,
	// enable it and make it the default button. If we're disabling
	// and the button is enabled, disable it and turn off it's
	// default button status.

	if (bEnable && !m_Speak.IsWindowEnabled()) {
		m_Speak.EnableWindow(TRUE);
		SendMessage(DM_SETDEFID, IDC_SPEAK, 0);
	}
	else if (!bEnable && m_Speak.IsWindowEnabled()) {
		m_Speak.EnableWindow(FALSE);
		SendMessage(DM_SETDEFID, 0, 0);
	}
}


void CCapMFCDlg::OnBalloonUse() {

	BOOL bCheck;

	bCheck = m_BalloonEnabled.GetCheck();

	m_BalloonSizeToText.EnableWindow(bCheck);
	m_BalloonAutoPace.EnableWindow(bCheck);
	m_BalloonAutoHide.EnableWindow(bCheck);
}


void CCapMFCDlg::OnMove() {

	_ASSERT(m_pszCurCharID);

	int iX;
	int iY;
	BOOL bConvert;
	CAgentCtlCharacterEx Character;
	COleVariant vEmpty;

	iX = GetDlgItemInt(IDC_MOVE_X, &bConvert, TRUE);

	if (!bConvert || (iX > 32767) || (iX < -32767))
		return;

	iY = GetDlgItemInt(IDC_MOVE_Y, &bConvert, TRUE);

	if (!bConvert || (iY > 32767) || (iY < -32767))
		return;

	// Shortcut to the character

	Character = m_Agent.GetCharacters().Character(m_pszCurCharID);

	// Should we stop the character?

	if (m_StopBeforePlay.GetCheck())
		Character.StopAll(vEmpty);

	Character.MoveTo((short)iX, (short)iY, vEmpty);
}


void CCapMFCDlg::OnSetFocusSpeakText() {

	if (m_SpeakText.GetWindowTextLength() > 0)
		SendMessage(DM_SETDEFID, IDC_SPEAK, 0);
}


void CCapMFCDlg::OnSetFocusMoveX() {

	SendMessage(DM_SETDEFID, IDC_MOVE, 0);
}


void CCapMFCDlg::OnSetFocusMoveY() {

	SendMessage(DM_SETDEFID, IDC_MOVE, 0);
}


void CCapMFCDlg::OnSetFocusAnimations() {

	SendMessage(DM_SETDEFID, IDC_PLAY, 0);
}


BOOL CCapMFCDlg::OnCommand(WPARAM wParam, LPARAM lParam) {

	WORD wID;

	wID = LOWORD(wParam);

	// First check for a recent file command

	if ((wID >= ID_RECENT_FILE_0) && (wID < ID_RECENT_FILE_0+MAX_RECENT_FILES)) {
		OnRecentFile(wID - ID_RECENT_FILE_0 + 1);
		return TRUE;
	}
	
	return CDialog::OnCommand(wParam, lParam);
}


BEGIN_EVENTSINK_MAP(CCapMFCDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CCapMFCDlg)
	ON_EVENT(CCapMFCDlg, IDC_AGENT, 22 /* Move */, OnMoveAgent, VTS_BSTR VTS_I2 VTS_I2 VTS_I2)
	ON_EVENT(CCapMFCDlg, IDC_AGENT, 17 /* Command */, OnCommandAgent, VTS_DISPATCH)
	ON_EVENT(CCapMFCDlg, IDC_AGENT, 31 /* AgentPropertyChange */, OnAgentPropertyChange, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void CCapMFCDlg::OnMoveAgent(LPCTSTR CharacterID, short x, short y, short Cause) {

	// Update the position fields

	SetDlgItemInt(IDC_MOVE_X, x, TRUE);
	SetDlgItemInt(IDC_MOVE_Y, y, TRUE);
}

void CCapMFCDlg::OnCommandAgent(LPDISPATCH UserInput) {

	CAgentCtlUserInput userInput(UserInput);
	CAgentCtlCharacterEx Character;
	CAgentCtlPropertySheet PropertySheet;
	COleVariant vEmpty;

	if (userInput.GetName() == kpszCommandProperties) {

		// Get the property sheet

		PropertySheet = m_Agent.GetPropertySheet();

		// Show it

		PropertySheet.SetVisible(TRUE);

		// Get the character

		_ASSERT(m_pszCurCharID);

		Character = m_Agent.GetCharacters().Character(m_pszCurCharID);

		// Stop it

		Character.StopAll(vEmpty);

		// Gesture at the property sheet

		Character.GestureAt(PropertySheet.GetLeft() + (PropertySheet.GetWidth() / 2),
						    PropertySheet.GetTop() + (PropertySheet.GetHeight() / 2));
	}
}


void CCapMFCDlg::OnAgentPropertyChange() {

	CAgentCtlCharacterEx Character;
	BOOL bUseBalloon;

	// The user has changed an Agent property via the
	// Advanced Characters Property Sheet. Update any
	// of our own fields to reflect the change.

	m_Sfx.EnableWindow(m_Agent.GetAudioOutput().GetSoundEffects());

	Character = m_Agent.GetCharacters().Character(m_pszCurCharID);
	
	m_BalloonEnabled.EnableWindow(Character.GetBalloon().GetEnabled());

	bUseBalloon = m_BalloonEnabled.IsWindowEnabled() && m_BalloonEnabled.GetCheck();

	m_BalloonSizeToText.EnableWindow(bUseBalloon);
	m_BalloonAutoPace.EnableWindow(bUseBalloon);
	m_BalloonAutoHide.EnableWindow(bUseBalloon);
}
