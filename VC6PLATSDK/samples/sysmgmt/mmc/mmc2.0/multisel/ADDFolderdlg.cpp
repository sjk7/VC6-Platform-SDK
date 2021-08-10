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
//
//  AddDeviceDlg.cpp:  Implementation of the CAddDeviceDlg class.   
//



#include "AddFolderDlg.h"
#include "Globals.h"
#include "Resource.h"        // Control IDs
#include "BaseNode.h"        // NODE_PROPERTIES struct

/////////////////////////////////////////////////////////////////////////////
//  Construction-Destruction

//---------------------------------------------------------------------------
//
CAddFolderDlg::CAddFolderDlg( ULONG nTemplate, HWND pParentWnd ) 
             : CBaseDialog( nTemplate )
{
  _ASSERT( NULL != pParentWnd );
  m_hParentWnd = pParentWnd;

}

CAddFolderDlg::~CAddFolderDlg()
{
}

/////////////////////////////////////////////////////////////////////////////
//  Message handlers


//---------------------------------------------------------------------------
LRESULT CAddFolderDlg::OnInitDialog( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
  LRESULT lResult = 0;

  HWND hArchiveCtrl  = GetDlgItem( hDlg, IDC_ARCHIVE_ATTR  ); 
  HWND hHiddenCtrl   = GetDlgItem( hDlg, IDC_HIDDEN_ATTR   );
  HWND hLockedCtrl   = GetDlgItem( hDlg, IDC_LOCKED_ATTR   );
  HWND hReadOnlyCtrl = GetDlgItem( hDlg, IDC_READONLY_ATTR );
  HWND hFldrNameCtrl = GetDlgItem( hDlg, IDC_FLDRNAME_EDIT );
  
  lResult = SendMessage( hArchiveCtrl,  BM_SETCHECK, BST_UNCHECKED, 0 );    
  lResult = SendMessage( hHiddenCtrl,   BM_SETCHECK, BST_UNCHECKED, 0 );    
  lResult = SendMessage( hLockedCtrl,   BM_SETCHECK, BST_UNCHECKED, 0 );    
  lResult = SendMessage( hReadOnlyCtrl, BM_SETCHECK, BST_UNCHECKED, 0 );    

  lResult = SetWindowText( hFldrNameCtrl, _T("") ); 
  SetFocus( hFldrNameCtrl );

  return 0;
}

//---------------------------------------------------------------------------
LRESULT CAddFolderDlg::OnOK( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
  LRESULT          lResult = 0;
  NODE_PROPERTIES  NodeProps;

  ZeroMemory( &NodeProps, sizeof(NODE_PROPERTIES) );  

  HWND hArchiveCtrl  = GetDlgItem( hDlg, IDC_ARCHIVE_ATTR  ); 
  HWND hHiddenCtrl   = GetDlgItem( hDlg, IDC_HIDDEN_ATTR   );
  HWND hLockedCtrl   = GetDlgItem( hDlg, IDC_LOCKED_ATTR   );
  HWND hReadOnlyCtrl = GetDlgItem( hDlg, IDC_READONLY_ATTR );
  HWND hFldrNameCtrl = GetDlgItem( hDlg, IDC_FLDRNAME_EDIT );

  if( BST_CHECKED == SendMessage( hArchiveCtrl, BM_GETCHECK, 0, 0 ) )
    NodeProps.dwAttributes |= ATTRIBUTE_DATA_ARCHIVE;

  if( BST_CHECKED == SendMessage( hHiddenCtrl, BM_GETCHECK, 0, 0 ) )
    NodeProps.dwAttributes |= ATTRIBUTE_DATA_HIDDEN;

  if( BST_CHECKED == SendMessage( hLockedCtrl, BM_GETCHECK, 0, 0 ) )
    NodeProps.dwAttributes |= ATTRIBUTE_DATA_LOCKED;

  if( BST_CHECKED == SendMessage( hReadOnlyCtrl, BM_GETCHECK, 0, 0 ) )
    NodeProps.dwAttributes |= ATTRIBUTE_DATA_READONLY;

  // Convert to wide characters here for all platforms.  This is the node name
  TCHAR szBuff[ MAX_NAME_LEN ] = {0};
  GetWindowText( hFldrNameCtrl, szBuff, MAX_NAME_LEN );
  CopyT2W( NodeProps.szNodeName, szBuff, MAX_NAME_LEN);
  // Probably a good idea to check for NULL name strings here

  // This message passes the user supplied info to the Static Node
  SendMessage( m_hParentWnd, WM_ADDNEW_NODE, (WPARAM)&NodeProps, 0 );

  // Now tell the parent node we are deleting ourselves so the 
  // context menu option can be enabled
  SendMessage( m_hParentWnd, WM_DIALOG_CLOSED, 0, 0 );

  // Call the base class to shut down the dialog
  CBaseDialog::OnOK( hDlg, wParam, lParam ); 
  return 0;
}

/////////////////////////////////////////////////////////////////////////////
//  Virtual function implementations

//---------------------------------------------------------------------------
BOOL CAddFolderDlg::ProcessMessage
(
  HWND     hDlg,           //[in] Handle to dialog box
  UINT     uMsg,           //[in] Message
  WPARAM   wParam,         //[in] First message parameter
  LPARAM   lParam          //[in] Second message parameter
)
{
  LRESULT lResult = 0;

  switch( uMsg )
  {
    case WM_INITDIALOG:
      lResult = OnInitDialog( hDlg, wParam, lParam );
      break;

    case WM_DESTROY:
      lResult = OnDestroy( hDlg, wParam, lParam );
      break;

    case WM_NCDESTROY:
      lResult = OnNcDestroy( hDlg, wParam, lParam );
      break;

    case WM_CLOSE:
      // Not overriding WM_CLOSE and IDCANCEL so we must send 
      // WM_DIALOG_CLOSED before calling the base class or else
      // the context menu will stay grayed
      SendMessage( m_hParentWnd, WM_DIALOG_CLOSED, 0, 0 );
      lResult = OnClose( hDlg, wParam, lParam );
      break;

    case WM_COMMAND:
      switch( wParam )
      {
        case IDOK:
          lResult = OnOK( hDlg, wParam, lParam );
          break;

        case IDCANCEL:
          SendMessage( m_hParentWnd, WM_DIALOG_CLOSED, 0, 0 );
          lResult = OnCancel( hDlg, wParam, lParam );
          break;

        default:
          break;
      }
    default:
      break;
  }
  return (BOOL)lResult;
} 



