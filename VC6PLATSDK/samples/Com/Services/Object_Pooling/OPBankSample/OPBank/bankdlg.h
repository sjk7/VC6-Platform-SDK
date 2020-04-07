/*+==========================================================================
  File:      BankDlg.h
  Summary:   Header for bank client
  Classes:   CBankDlg
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

#ifndef __BANKDLG_H_
#define __BANKDLG_H_

#include "resource.h"       // main symbols
#include "linkable.h"

#define WM_SHOWRESULTS	WM_USER+1 // Devstudio deletes this if I put it in REsOURCE.H
#define WM_SHOWERROR	WM_USER+2 // Devstudio deletes this if I put it in REsOURCE.H

typedef enum
{
	CoInitMTA = 0,
	CoInitSTA,
	CoInitRandom
} EnumCoInit;

// (04.26.00 mdl) Include support for Delphi.
typedef enum
{
	VC = 0,
	VB,
	Java,
	Delphi,
} BankLang;

struct THREADDATA
{

	int nTestType;
	EnumCoInit	eCoInit;
	int nIters;
	BOOL bRandom;
	BOOL bChatty;
	int nFrom;
	int nTo;
	int nTranType;
	int nAmount;
	int nThreads; 
	BOOL bCreatePerIteration;
	BankLang eLang;	

};

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class: CThreadData
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

class CThreadData : public CLinkable
{

	THREADDATA m_td;

public:
		CThreadData()
		{
			ZeroMemory(&m_td, sizeof(m_td));
		}
		CThreadData(THREADDATA * pData)
		{
			memcpy(&m_td, pData, sizeof(m_td));
		}


		THREADDATA * GetThreadData(){return &m_td;}
	
};

struct CREATEDATA
{

	int nRows;
	HWND hWndResults;
	HWND hWndStopButton;
	BOOL bStop;
	BOOL bDone;
	int nTotalRows;
	BOOL bChatty;

};



struct RESULTDATA
{
	LPOLESTR sString;
	DWORD dwThreadId;
};	


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
Class: CBankDlg
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/ 

class CBankDlg : 
	public CDialogImpl<CBankDlg>
{

private:
		CThreadData * m_pCurrentThreadData;
		CREATEDATA m_cd;
		HANDLE m_hCreateThread;
		void ConsumeAllMessages();
		void DoWork(CThreadData * pData, int nTestType);
		int m_nSuiteIndex;
		int m_nTotalTests;
		CListHeader m_list;
		void UpdateStatus(CThreadData * pData, int nCurItem);
		HMENU m_hMenu;
		void SetDescription(THREADDATA *pData);
		int m_nMaxRowLength;
		HANDLE  m_hFile;
		int m_nMsgs;
		

public:
	
	BOOL LoadAll();
	BOOL SaveAll();	
	void SetThreadData(THREADDATA * pTd);
	void GetThreadData(THREADDATA * pTd);
	CBankDlg();
	~CBankDlg();

	enum { IDD = IDD_BANKDLG };

// (04.26.00 mdl) Include support for Delphi.
BEGIN_MSG_MAP(CBankDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnOK)
	COMMAND_ID_HANDLER(IDC_SUBMIT, OnGo)
	COMMAND_ID_HANDLER(IDC_CREATE_ROWS, OnCreateRows)
	COMMAND_ID_HANDLER(IDC_CREATE_TABLES, OnCreateTables)
	COMMAND_ID_HANDLER(IDC_VIEW_PREV, OnViewPrev)
	COMMAND_ID_HANDLER(IDC_VIEW_NEXT, OnViewNext)
	COMMAND_ID_HANDLER(IDC_ADD, OnAdd)
	COMMAND_ID_HANDLER(IDC_REMOVE, OnRemove)
	COMMAND_ID_HANDLER(IDM_KILL_THREADS, OnKillThreads)

	COMMAND_ID_HANDLER(ID_ASSERT_ON_ERRORS, OnAssertOnErrors)
	COMMAND_ID_HANDLER(IDM_OPTION_ODBC_STOP, OnStopOnODBCErrors)
	COMMAND_ID_HANDLER(IDM_RANDOM, OnRandom)
	COMMAND_ID_HANDLER(IDM_OPTION_CREATE_ITERATION, OnSelectCreatePerIteration)
	COMMAND_ID_HANDLER(IDM_OPTION_CHATTY, OnSelectChattyDisplay)
	COMMAND_RANGE_HANDLER(ID_MM_TRANSFER, ID_MM_CREDIT, OnSelectMoveMoney)
	COMMAND_RANGE_HANDLER(ID_AC_DEBIT, ID_AC_CREDIT, OnSelectAccount)
	COMMAND_RANGE_HANDLER(ID_LANG_C, ID_LANG_DELPHI, OnSelectLanguage)
	COMMAND_RANGE_HANDLER(ID_COINIT_MTA, ID_COINIT_RANDOM, OnSelectCoInit)


	COMMAND_ID_HANDLER(IDM_RETRY, OnRetryOnErrors)			
	COMMAND_ID_HANDLER(IDM_COPY, OnCopy)			
	COMMAND_ID_HANDLER(IDM_COPYALL, OnCopyAll)			
	COMMAND_ID_HANDLER(IDM_COPYERRORS, OnCopyErrors)			

	COMMAND_ID_HANDLER(IDC_STOP, OnStop)			
	COMMAND_ID_HANDLER(IDC_RUN_SUITE, OnRunSuite)		
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SHOWRESULTS, OnShowResults)
	MESSAGE_HANDLER(WM_SHOWERROR, OnShowError)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_INITMENU, OnInitMenu)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShowResults(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShowError(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnInitMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnViewNext(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnViewPrev(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnRemove(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnKillThreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAssertOnErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStopOnODBCErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelectCreatePerIteration(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelectChattyDisplay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	
	LRESULT OnSelectMoveMoney(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelectAccount(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelectLanguage(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSelectCoInit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnRetryOnErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnRandom(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);	
	LRESULT OnGo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnStop(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	
	LRESULT OnCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCopyAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCopyErrors(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCreateRows(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCreateTables(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRunSuite(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	

};

#endif //__BANKDLG_H_
