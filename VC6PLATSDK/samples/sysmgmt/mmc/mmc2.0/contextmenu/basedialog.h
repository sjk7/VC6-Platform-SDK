/////////////////////////////////////////////////////////////////////////////
//
//  This source code is only intended as a supplement to existing
//  Microsoft documentation. 
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
//  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
//  PURPOSE.
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//  BaseDialog.h:  Interface for the CBaseDialog class.  This is the base
//                 class for modeless dialogs.
//


#ifndef _CLASS_BASEDIALOG_
#define _CLASS_BASEDIALOG_

#include <Windows.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//---------------------------------------------------------------------------
class CBaseDialog  
{
  private:
    HWND     m_hWnd;         // Handle from CreateDialogParam
    ULONG    m_nTemplate;    // Dialog template ID
    DLGPROC  m_DlgProc;      // Points to Dialog Proc      
    DWORD    m_dwFlags;      // Create flags

  public:
    CBaseDialog( ULONG nTemplate = 0 );
    virtual ~CBaseDialog();

    virtual HWND Create( HINSTANCE hInstance, HWND hWndParent, DWORD dwFlags = 0 );

  protected:
    static BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    virtual LRESULT OnInitDialog( HWND hDlg, WPARAM wParam, LPARAM lParam );
    virtual LRESULT OnOK( HWND hDlg, WPARAM wParam, LPARAM lParam );
    virtual LRESULT OnCancel( HWND hDlg, WPARAM wParam, LPARAM lParam );
    virtual LRESULT OnNcDestroy( HWND hDlg, WPARAM wParam, LPARAM lParam );
    virtual LRESULT OnDestroy( HWND hDlg, WPARAM wParam, LPARAM lParam );
    virtual LRESULT OnClose( HWND hDlg, WPARAM wParam, LPARAM lParam );

  public:
    virtual BOOL ProcessMessage( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0; 

};


#endif //_CLASS_BASEDIALOG_
