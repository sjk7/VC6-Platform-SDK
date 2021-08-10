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
//  AddVFileDlg.h:   Header for the CAddVFileDlg class.  This is a 
//                   modeless dialog class used to add Virtual Files.  
//


#ifndef _CLASS_ADDVFILEDLG_
#define _CLASS_ADDVFILEDLG_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "BaseDialog.h"


//---------------------------------------------------------------------------
class CAddVFileDlg : public CBaseDialog  
{
  public:
    CAddVFileDlg( ULONG nTemplate, HWND hParentWnd );
    ~CAddVFileDlg();

  
  public:
    BOOL ProcessMessage( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam ); 


  // Messages we will be handling
  private:
    LRESULT OnInitDialog( HWND hDlg, WPARAM wParam, LPARAM lParam );
    LRESULT OnOK( HWND hDlg, WPARAM wParam, LPARAM lParam );

  private:
    HWND    m_hParentWnd;


};

#endif //_CLASS_ADDVFILEDLG_