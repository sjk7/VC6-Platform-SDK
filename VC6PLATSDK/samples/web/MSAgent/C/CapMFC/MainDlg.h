// CapMFCDlg.h : header file
//
//{{AFX_INCLUDES()
#include "acex.h"
//}}AFX_INCLUDES

#if !defined(AFX_CAPMFCDLG_H__AB8FEB9A_3841_11D2_8512_00C04FA34A14__INCLUDED_)
#define AFX_CAPMFCDLG_H__AB8FEB9A_3841_11D2_8512_00C04FA34A14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCapMFCDlg dialog

class CCapMFCDlg : public CDialog
{
// Construction
public:
	CCapMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCapMFCDlg)
	enum { IDD = IDD_CAPMFC_DIALOG };
	CStatic	m_YLabel;
	CStatic	m_XLabel;
	CButton	m_PositionLabel;
	CEdit	m_MoveY;
	CEdit	m_MoveX;
	CButton	m_Move;
	CButton	m_BalloonEnabled;
	CButton	m_BalloonSizeToText;
	CButton	m_BalloonAutoPace;
	CButton	m_BalloonAutoHide;
	CButton	m_Speak;
	CButton	m_SpeechOutputLabel;
	CEdit	m_SpeakText;
	CButton	m_Sfx;
	CButton	m_Stop;
	CButton	m_StopBeforePlay;
	CButton	m_Play;
	CButton	m_AnimationsLabel;
	CListBox	m_Animations;
	CAgentCtlEx	m_Agent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCapMFCDlg)
	public:
	virtual void OnFinalRelease();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCapMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT uIndex, BOOL bSysMenu);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnActivateApp(BOOL bActive, DWORD hTask);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileExit();
	afx_msg void OnFileOpen();
	afx_msg void OnPlay();
	afx_msg void OnDblclkAnimations();
	afx_msg void OnStop();
	afx_msg void OnSfx();
	afx_msg void OnSpeak();
	afx_msg void OnChangeSpeakText();
	afx_msg void OnSetFocusSpeakText();
	afx_msg void OnBalloonUse();
	afx_msg void OnMove();
	afx_msg void OnSetFocusMoveX();
	afx_msg void OnSetFocusMoveY();
	afx_msg void OnMoveAgent(LPCTSTR CharacterID, short x, short y, short Cause);
	afx_msg void OnSetFocusAnimations();
	afx_msg void OnCommandAgent(LPDISPATCH UserInput);
	afx_msg void OnAgentPropertyChange();
	afx_msg void OnHelpAbout();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	LoadCharacter(CString pszFilename);
	void	OnRecentFile(UINT uFile);
	void	UpdateRecentFiles(LPCTSTR pszFilename);
	void	MakeEllipsisPath(LPCTSTR pszPath, LPTSTR pszEllipsisPath, UINT cchMaxEllipsisPath);

private:
	LPCTSTR	m_pszCurCharID;
	BOOL	m_bHasMRUSeparator;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPMFCDLG_H__AB8FEB9A_3841_11D2_8512_00C04FA34A14__INCLUDED_)
