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

#ifndef _MMC_GLOBALS_H
#define _MMC_GLOBALS_H

#include <Tchar.h>
#include <Mmc.h>
#include <CrtDbg.h>


#pragma warning(4:4267)   // convertion from size_t to smaller type
#pragma warning(4:4244)   // sizeof returns to INT

extern HINSTANCE g_hInst;              // Global instance handle
extern ULONG     g_uObjectCount;       // Instance count for this object 
extern ULONG     g_uServerLocks;       // Server lock count for this object

//---------------------------------------------------------------------------
// Clipformats requiered by MMC

extern UINT g_cfDisplayName;      // DisplayName for our SnapIn node
extern UINT g_cfNodeType;         // GUID of the selected node
extern UINT g_cfSnapinClsid;      // Class ID of this SnapIn
extern UINT g_cfszNodeType;       // String version of namespace GUID


//---------------------------------------------------------------------------
//
void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide );

void InitClipboardFormats();

//---------------------------------------------------------------------------
//  Global Strings

// These strings are Unicode or Ansi depending on the target platform
//
static TCHAR*  gtszSNAPIN_NAME       = _T("Sample A (MMC 2.0) - Simple");


// These strings are used by the console, so they're Unicode on all platforms
//
static WCHAR*  gwszROOT_NODE_NAME    = L"Simple Root Node";


// We need to do this to get around MMC.IDL - it explicitly defines
// the clipboard formats as WCHAR types...
#define T_CCF_DISPLAY_NAME    _T("CCF_DISPLAY_NAME")
#define T_CCF_NODETYPE        _T("CCF_NODETYPE")
#define T_CCF_SZNODETYPE      _T("CCF_SZNODETYPE")
#define T_CCF_SNAPIN_CLASSID  _T("CCF_SNAPIN_CLASSID")




//---------------------------------------------------------------------------
// Constants

#define NODETYPE_STATIC      100;


/////////////////////////////////////////////////////////////////////////////
// Helper classes and macros

#define BYTE_SIZE(string)          ((_tcslen(string)+1) * sizeof(TCHAR))

#define BREAK_ON_ERROR( hResult )  if( S_OK != hResult ) continue


//---------------------------------------------------------------------------
template<class TYPE>
inline void SAFE_RELEASE( TYPE*& pObj )
{
  if( NULL != pObj ) 
  { 
    pObj->Release(); 
    pObj = NULL; 
  } 
  else 
  { 
    OutputDebugString(_T("Attempted to release NULL Com pointer.\n")); 
  }
} // end SAFE_RELEASE()



//---------------------------------------------------------------------------
//  W2T converts a wide character string to unicode if _UNICODE is not
//  defined.  If it is defined then the sting is copied to another buffer.
//  
#ifndef _UNICODE
#define W2T( pszAnsi, szWide )   Unicode2Ansi( pszAnsi, szWide )
#else
#define W2T( szAnsiPtr, szWide )                                              \
        *szAnsiPtr = (WCHAR*)CoTaskMemAlloc(BYTE_SIZE(szWide)+sizeof(TCHAR)); \
        CopyMemory( *szAnsiPtr, szWide, BYTE_SIZE(szWide)+sizeof(TCHAR) )
#endif


#endif // _MMC_GLOBALS_H
