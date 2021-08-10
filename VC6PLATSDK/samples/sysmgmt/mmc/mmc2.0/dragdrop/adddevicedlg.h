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
//  AddDeviceDlg.h:  Header for the CAddDeviceDlg class.  This is a 
//                   modeless dialog class used to add device nodes.  
//


#ifndef _CLASS_ADDDEVICEDLG_
#define _CLASS_ADDDEVICEDLG_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "BaseDialog.h"


//---------------------------------------------------------------------------
class CAddDeviceDlg : public CBaseDialog  
{
  public:
    CAddDeviceDlg( ULONG nTemplate, HWND hParentWnd );
    ~CAddDeviceDlg();

  
  public:
    BOOL ProcessMessage( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam ); 


  // Messages we will be handling
  private:
    LRESULT OnInitDialog( HWND hDlg, WPARAM wParam, LPARAM lParam );
    LRESULT OnOK( HWND hDlg, WPARAM wParam, LPARAM lParam );

  private:
    HWND    m_hParentWnd;


};

#endif //_CLASS_ADDDEVICEDLG_