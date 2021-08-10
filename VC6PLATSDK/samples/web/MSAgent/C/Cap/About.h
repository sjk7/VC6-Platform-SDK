#ifndef _About_h_
#define _About_h_


// Standard About Dialog

class AboutDlg {
public:
	AboutDlg();
   ~AboutDlg();

    void	DoModal(HWND hWndParent, short sAgentVersionMajor, short sAgentVersionMinor);


private:
	BOOL	OnInitDialog();


private:
	HWND	m_hWnd;
	HICON	m_hIcon;
	RECT	m_rcIcon;
	short	m_sAgentMajor;
	short	m_sAgentMinor;


private:
	friend BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif
