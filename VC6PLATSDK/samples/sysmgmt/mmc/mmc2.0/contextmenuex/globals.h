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

#include <TChar.h>
#include <Mmc.h>
#include <CrtDbg.h>
#include "Guids.h"

class CDataObject;


//---------------------------------------------------------------------------
extern HINSTANCE g_hInst;              // Global instance handle
extern ULONG     g_uObjectCount;       // Instance count for this object 
extern ULONG     g_uServerLocks;       // Server lock count for this object


#define MAX_OBJECT_PATH      255

#define IDM_QUERY_ATTRIBS    2000

//---------------------------------------------------------------------------
//  Global function prototypes

void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide );

//---------------------------------------------------------------------------
//  Global Strings


static TCHAR*  gtszSNAPIN_NAME   = _T("Sample D1 (MMC 2.0) - ContextMenuEx");

// This string is used under \Nodetypes\Extensions\View to identify the object.
static TCHAR*  gtszOBJECT_NAME   = _T("MMC SDK Custom ContextMenu Extension"); 


//CONTEXTMENUX:  GUID strings for nodes which we access in the registry. 
static TCHAR*  gtszDEVICE_GUID   = _T("{520F23F9-775D-4015-B437-98A24B9D085E}");
static TCHAR*  gtszCTXMENUX_GUID = _T("{6568A231-D647-4E60-BB38-B8B3878B9DDF}");


/////////////////////////////////////////////////////////////////////////////
// Helper classes and macros

#define BYTE_SIZE(string)          ((_tcslen(string)+1) * sizeof(TCHAR))

#define BREAK_ON_ERROR( hResult )  if( S_OK != hResult ) continue

// Useful only for debugging.  Never use modal dialogs in release builds!!
#define MsgBox(wszMsg, wszTitle) ::MessageBox(NULL, wszMsg, wszTitle, MB_OK)


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
} 

//---------------------------------------------------------------------------
template<class TYPE>
inline void SAFE_FREE_BITMAP( TYPE*& pObj )
{
  if( NULL != pObj ) 
  { 
    BOOL bStatus = DeleteObject( pObj );
    pObj = NULL;
  } 
  else 
  { 
    OutputDebugString(_T("Attempted to delete NULL Bitmap handle.\n")); 
  }
} 

//---------------------------------------------------------------------------
template<class TYPE>
inline void SAFE_FREE_ICON( TYPE*& pObj )
{
  if( NULL != pObj ) 
  { 
    BOOL bStatus = DestroyIcon( pObj );
    pObj = NULL;
  } 
  else 
  { 
    OutputDebugString(_T("Attempted to delete NULL Icon handle.\n")); 
  }
} 

//---------------------------------------------------------------------------
//  W2T converts a wide character string to unicode if _UNICODE is not
//  defined.  If it is defined then the sting is copied to another buffer.
//  
#ifndef _UNICODE
#define W2T( szAnsiPtr, szWide )   Unicode2Ansi( szAnsiPtr, szWide )
#else
#define W2T( szAnsiPtr, szWide )                                 \
        *szAnsiPtr = (WCHAR*)CoTaskMemAlloc(BYTE_SIZE(szWide) ); \
        CopyMemory( *szAnsiPtr, szWide, BYTE_SIZE(szWide) )

#endif //_UNICODE


#endif //_MMC_GLOBALS_H
