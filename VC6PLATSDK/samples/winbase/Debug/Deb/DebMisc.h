
/******************************************************************************\
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1993 - 2000.  Microsoft Corporation.  All rights reserved.

*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/


#ifndef DEBMISC_H

 #define DEBMISC_H

 #ifndef DEBDEBUG_H
   #include "DEBDebug.H"
 #endif

 #ifndef DEBMAIN_H
   #include "DEBMain.H"
 #endif

 //-- function prototypes
 BOOL          StartDebuggee( LPTSTR, HWND );
 BOOL          AttachToDebuggee( DWORD, HWND );
 BOOL CALLBACK EnumProcessListFunc( HWND, LPARAM );
 BOOL          GetDebuggeeFileName( LPTSTR, HWND );
 BOOL          ChooseNewFont( HWND );
 BOOL          ChooseNewBackColor( HWND );
 BOOL          MakeCommonDebugEventString( LPTSTR, DWORD, LPDEBUG_EVENT);
 HWND          CreateTextButtonBar( HWND, LPINT );
 HWND          CreateIconWindow( HWND, LPCTSTR );
 BOOL          GetPrivateProfileSettings( LPCTSTR, LPCTSTR, PPROFILE );
 BOOL          WritePrivateProfileSettings( LPCTSTR, LPCTSTR, PPROFILE );
 BOOL          WritePrivateProfileInt( LPCTSTR, LPCTSTR, INT, LPCTSTR );
 BOOL          UpdateMenuSettings( HWND );
 BOOL          OutOfMemoryMessageBox( HWND );
 BOOL          MaxDebuggeesMessageBox( HWND );
 BOOL          ErrorMessageBox( LPCTSTR, LPCTSTR, LPCTSTR, INT );
 WNDPROC       SubclassWindow( HWND, WNDPROC );
 LRESULT       SendWmSizeMessage( HWND );
 UINT          GetPathFromFullPathName( LPCTSTR, LPTSTR, UINT );
 BOOL          CopyListBoxToClipboard( HWND, LONG );
 LRESULT       ListBoxInsert( HWND, LPLONG, LPCTSTR );
 LRESULT       ListBoxPrintF( HWND, LPCTSTR, ... );
 LPTSTR        StringPrintF( LPTSTR, DWORD, LPCTSTR, ...  );
 BOOL          StringAppendF( LPTSTR, DWORD, LPCTSTR, ... );

#endif // DEBMISC_H
