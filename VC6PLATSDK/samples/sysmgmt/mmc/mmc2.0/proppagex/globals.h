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

//---------------------------------------------------------------------------
// XPROPPAGE: Stuff we need to support clipformats from the Property Page
//            sample which we are extending 

#define T_CCF_ATTRIB_PTR     _T("CCF_ATTRIB_PTR")

extern UINT g_cfNodeAttrPtr;           // Points to NODE_ATTRIBS struct

#define MAX_OBJECT_PATH      255

typedef struct _tag_NODE_ATTRIB_       // Clipformat points to this data
{
  WCHAR  szObjectPath[MAX_OBJECT_PATH];

} NODE_ATTRIBS; 

#define ATTRIBUTE_DATA_COMPRESSED      64
#define ATTRIBUTE_DATA_ENCRYPTED       128   


//---------------------------------------------------------------------------
//  Global function prototypes

void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide );

//---------------------------------------------------------------------------
//  Global Strings


static TCHAR*  gtszSNAPIN_NAME       = _T("Sample G1 (MMC 2.0) - Property PageX");

//XPROPPAGE:  GUID string for nodes which we extend. 
static TCHAR*  gtszVFILE_GUID        = _T("{F0091C49-C869-4941-A81C-C719AD8174CC}");
static TCHAR*  gtszPROPPAGEX_GUID    = _T("{489F991A-9A75-4553-885B-6EE881C50A26}");


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
