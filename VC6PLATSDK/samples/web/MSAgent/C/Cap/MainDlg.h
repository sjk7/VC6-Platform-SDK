#ifndef _MainDlg_h_
#define _MainDlg_h_


class AgentNotifySink;


// Main Dialog class

class MainDlg {
public:
	MainDlg();

    HRESULT	Init();
	void	LoadCharacter(LPCTSTR pszFilename);


public:
	HWND	m_hWnd;
	HACCEL	m_hAccel;


private:
	void	OnActivateApp(BOOL bActive);
	BOOL	OnCommand(WPARAM wParam, LPARAM lParam);
	void	OnDestroy();
	void	OnButtonClick(UINT uID);
	void	OnDropFiles(HDROP hDrop);
	void	OnRecentFile(UINT uFile);
	BOOL	OnInitDialog();
	BOOL	OnInitMenuPopup(HMENU hMenu, UINT uPos, BOOL bSysMenu);
	BOOL	OnSysCommand(WPARAM wParam);
	

private:
	void	UpdateRecentFiles(LPCTSTR pszFilename);
	void	MakeEllipsisPath(LPCTSTR pszPath, LPTSTR pszEllipsisPath, UINT cchMaxEllipsisPath);
	void	OnSpeak();
	void	OnCharacterMove(long x, long y);
	void	OnCharacterRightClick(long x, long y);
	void	OnCharacterCommand(long lID);
	void	OnPropertyChange();


private:
	BOOL	m_bHasMRUSeparator;
	BOOL	m_bAddedCommands;


private:
	WNDPROC	m_wpListBox;
	WNDPROC m_wpSpeakText;
	WNDPROC m_wpMoveX;
	WNDPROC m_wpMoveY;


private:
	IAgentEx			*m_pAgent;
	IAgentCharacterEx	*m_pCharacter;
	IAgentBalloonEx		*m_pBalloon;
	AgentNotifySink		*m_pSink;
	long				 m_lCharacterID;
	long				 m_lSinkID;
	long				 m_lCmdPropertiesID;


private:
	friend class AgentNotifySink;
	friend  LRESULT	CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend  LRESULT	CALLBACK ListBoxWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend  LRESULT	CALLBACK SpeakTextWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend  LRESULT	CALLBACK MoveXWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend  LRESULT	CALLBACK MoveYWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif
