/*+==========================================================================

File: Main.h

Summary: Declaration of CMain

----------------------------------------------------------------------------
This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
==========================================================================+*/
// Main.h : Declaration of the CMain

#ifndef __MAIN_H_
#define __MAIN_H_

#include "windows.h"
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMain
class CMain : 
	public CDialogImpl<CMain>
{
private:
	enum {
		eSTA = STA_OFFSET,
		eFree = FREE_OFFSET,
		eCOMPlus = COMSYNC_OFFSET
	} e_compType;

	DWORD	volatile m_dwMaxTime, m_dwMinTime; // volatile due to compares in code
	DWORD   m_dwTotalIters, m_dwTotalTime;
	DWORD	m_curThreadCount;
	int		m_iIters;			
	DWORD	m_iCookie;		
	BOOL	m_bStop;

public:
	CMain()
	{
		m_dwMaxTime = m_dwMinTime = m_dwTotalIters = m_dwTotalTime = 0 ;
		m_curThreadCount = 0;
		m_bStop = 0;
	}

	~CMain()
	{
	}

	enum { IDD = IDD_MAIN };

BEGIN_MSG_MAP(CMain)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	COMMAND_HANDLER(IDC_RADIO_COMSYNC, BN_CLICKED, OnClickedRadio_COMPlusSync)
	COMMAND_HANDLER(IDC_RADIO_FREE, BN_CLICKED, OnClickedRadio_Free)
	COMMAND_HANDLER(IDC_RADIO_STA, BN_CLICKED, OnClickedRadio_STA)
	COMMAND_HANDLER(IDC_START, BN_CLICKED, OnClickedStart)
	MESSAGE_HANDLER(WM_TIMER, OnTimer)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// TODO : Add Code for message handler. Call DefWindowProc if necessary.
		return 0;
	}

	LRESULT OnClickedRadio_COMPlusSync(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		e_compType = eCOMPlus;
		return 0;
	}
	LRESULT OnClickedRadio_Free(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		e_compType = eFree;
		return 0;
	}
	LRESULT OnClickedRadio_STA(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		e_compType = eSTA;
		return 0;
	}
	LRESULT OnClickedStart(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void UpdateCounters(DWORD lDelta);
	static LRESULT ThreadStart(LPVOID lp);
	void UpdateUI(void);
};

#endif //__MAIN_H_
