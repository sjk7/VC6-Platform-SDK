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

#include "Globals.h"

//---------------------------------------------------------------------------
// MMC's requiered clipboard formats

UINT g_cfDisplayName = 0;      // DisplayName for our SnapIn node
UINT g_cfNodeType    = 0;      // GUID of the selected node
UINT g_cfszNodeType  = 0;      // String representation of namespace GUID
UINT g_cfSnapinClsid = 0;      // Class ID of this SnapIn


// Global variables

HINSTANCE g_hInst = NULL;      // Our global instance handle
ULONG g_uObjectCount = 0;      // Global object count
ULONG g_uServerLocks = 0;      // Global lock count


//---------------------------------------------------------------------------
//  This is the fast, simple way to convert unicode to ansi.  It does NOT
//  handle multibyte ansi strings and is not localized.  But it should be
//  fine for registry entries
//  NOTE:  The caller is responsible for freeing the memory.
//
void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide )
{
  LONG nLen = wcslen( szWide ) +1;
  *pszAnsi = (char*)CoTaskMemAlloc( nLen );   
  char* pCounter = *pszAnsi;

  while( *szWide )
  {
    *pCounter = LOBYTE(*szWide);
    pCounter++; 
    szWide++;   
  }
  *pCounter = NULL;
}


//---------------------------------------------------------------------------
//
void InitClipboardFormats()
{
  g_cfDisplayName  = RegisterClipboardFormat( T_CCF_DISPLAY_NAME );
  g_cfNodeType     = RegisterClipboardFormat( T_CCF_NODETYPE );
  g_cfszNodeType   = RegisterClipboardFormat( T_CCF_SZNODETYPE );
  g_cfSnapinClsid  = RegisterClipboardFormat( T_CCF_SNAPIN_CLASSID );

}
