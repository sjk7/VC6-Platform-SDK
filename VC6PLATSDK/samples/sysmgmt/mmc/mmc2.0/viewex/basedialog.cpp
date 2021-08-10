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
//  BaseDialog.cpp: implementation of the CBaseDialog class.
//

#include "BaseDialog.h"
#include "Globals.h"



/////////////////////////////////////////////////////////////////////////////
// Construction/Destruction

//---------------------------------------------------------------------------
CBaseDialog::CBaseDialog( ULONG nTemplate )
{
  _ASSERT( NULL != nTemplate );

  m_nTemplate = nTemplate;
  m_hWnd      = NULL;          // Handle returned by CreateDialogParam 
  m_DlgProc   = DlgProc;       // Point to default dialog proc
  m_dwFlags   = 0;
}

//---------------------------------------------------------------------------
CBaseDialog::~CBaseDialog()
{
}

//---------------------------------------------------------------------------
//  Use CreateDialogParam rather than CreateDialog so that we can later
//  retrieve the 'this' pointer which we will need to point back to the 
//  particular instance of this class.
//
HWND CBaseDialog::Create
( 
  HINSTANCE  hInstance,      //[in] Global instance handle 
  HWND       hWndParent,     //[in] Handle to parent window
  DWORD      dwFlags         //[in] Create flags - not used
)
{
  _ASSERT( NULL != hInstance );

  m_dwFlags = dwFlags;
  m_hWnd = CreateDialogParam( hInstance,
                              MAKEINTRESOURCE(m_nTemplate),
                              hWndParent,
                              m_DlgProc,
                              (LPARAM)this
                            );

  BOOL bReturn = ShowWindow( m_hWnd, SW_SHOW );  // Should return 0

  return m_hWnd;
}


/////////////////////////////////////////////////////////////////////////////
//  Message Handlers

//---------------------------------------------------------------------------
LRESULT CBaseDialog::OnInitDialog( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
  return 1;
}

//---------------------------------------------------------------------------
//  This is the first message sent by the DetroyWindow() function.
//  It is sent after the window is removed from the screen, but it should
//  be assumed that any child windows still exist.
//
LRESULT CBaseDialog::OnDestroy( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
  return 1;
}

//---------------------------------------------------------------------------
//  This is sent after WM_DESTROY, and informs the app that the non-client
//  area is being destroyed.  This is where allocated resources should be
//  cleaned up.
//
LRESULT CBaseDialog::OnNcDestroy( HWND hDlg, WPARAM wParam, LPARAM lParam )
{
  m_hWnd = NULL;             // Since this is a modeless-only dialog 
  delete this;               // class we delete ourselves here

  return 1;
}

//---------------------------------------------------------------------------
LRESULT CBaseDialog::OnOK( HWND hDlg, WPARAM wParam, LPARAM lParam )
{ 
  return DestroyWindow( m_hWnd);
}

//---------------------------------------------------------------------------
LRESULT CBaseDialog::OnCancel( HWND hDlg, WPARAM wParam, LPARAM lParam )
{ 
  return DestroyWindow( m_hWnd);
}

//---------------------------------------------------------------------------
LRESULT CBaseDialog::OnClose( HWND hDlg, WPARAM wParam, LPARAM lParam )
{ 
  return DestroyWindow( m_hWnd);
}


/////////////////////////////////////////////////////////////////////////////
//  Dialog Procedures

//---------------------------------------------------------------------------
//  Since this is a static function we can't use a 'this' pointer or call
//  the base class directly.  There may be multiple base classes using 
//  this method.  We get around this by storing the 'this' pointer in the
//  lParam of CreateDialogParam.  When we get WM_INITDIALOG we get this 
//  pointer back in the lParam.  Now we can use SetWindowLongPtr to store
//  it, and later retireve it with GetWindowLongPtr.  Once we have a 
//  valid 'this' pointer we can cast it back to the base class and then
//  call the base class's ProcessMessage function.
//
BOOL CALLBACK CBaseDialog::DlgProc
(
  HWND     hDlg,           //[in] Handle to dialog box
  UINT     uMsg,           //[in] Message
  WPARAM   wParam,         //[in] First message parameter
  LPARAM   lParam          //[in] Second message parameter
)
{
  BOOL bReturn = FALSE;
  if( WM_INITDIALOG == uMsg )
  {
    SetWindowLongPtr(hDlg, GWL_USERDATA, lParam);  
  }

  CBaseDialog* pThis = reinterpret_cast<CBaseDialog*>(GetWindowLongPtr(hDlg, GWL_USERDATA));
  if( NULL != pThis )
  {
    bReturn = pThis->ProcessMessage( hDlg, uMsg, wParam, lParam );  
  }

  return bReturn;
}

//---------------------------------------------------------------------------
//  This is the instance specific method used to process messages.  The
//  DialogProc delegates this responsibiliy to each instance of the class.
//  This is a pure virtual function.  The code below is provided to cut
//  and paste into the derived class's implementation.
/*
BOOL CBaseDialog::ProcessMessage
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
      lResult = OnClose( hDlg, wParam, lParam );

    case WM_COMMAND:
      switch( wParam )
      {
        case IDOK:
          lResult = OnOK( hDlg, wParam, lParam );
          break;

        case IDCANCEL:
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
*/
