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


class CBaseNode;                       // References
class CDataObject;


//---------------------------------------------------------------------------
extern HINSTANCE g_hInst;              // Global instance handle
extern ULONG     g_uObjectCount;       // Instance count for this object 
extern ULONG     g_uServerLocks;       // Server lock count for this object

//---------------------------------------------------------------------------
// Clipformats requiered by MMC

extern UINT g_cfDisplayName;      // DisplayName for our SnapIn node
extern UINT g_cfNodeType;         // GUID of the selected node
extern UINT g_cfSnapinClsid;      // Class ID of this SnapIn
extern UINT g_cfszNodeType;       // String version of namespace GUID

extern UINT g_cfBaseNodePtr;      // Retrieves BaseNode pointer 
extern UINT g_cfDataObjPtr;       // Retrieves pointer to CDataObject

//---------------------------------------------------------------------------
//  Global function prototypes

void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide );
void _fastcall CopyT2W( LPWSTR strDest, LPCTSTR strSource, size_t count);

void InitClipboardFormats();

HRESULT ExtractFromDataObject( LPDATAOBJECT ipDataObject,UINT cf,ULONG cb,HGLOBAL *phGlobal );

CBaseNode* ExtractBaseNodePtr( LPDATAOBJECT ipDataObject );
CDataObject* ExtractDataObjPtr( LPDATAOBJECT ipDataObject );

//---------------------------------------------------------------------------
//  Global Strings


static TCHAR*  gtszSNAPIN_NAME       = _T("Sample D (MMC 2.0) - ContextMenu");
static TCHAR*  gtszABOUT_NAME        = _T("Sample D (MMC 2.0) - ISnapinAbout");


static WCHAR*  gwszROOT_NODE_NAME    = L"Context Menu Sample";
static WCHAR*  gwszABOUT_DESCRIPTION = L"MMC SDK ContextMenu Sample";
static WCHAR*  gwszABOUT_PROVIDER    = L"Copyright © 1999 - 2001 Microsoft Corporation";
static WCHAR*  gwszABOUT_VERSION     = L"2.0";

static TCHAR*  gtszCLSID_DEVICENODE  = _T("{520F23F9-775D-4015-B437-98A24B9D085E}");


// We need to do this to get around MMC.IDL - it explicitly defines
// the clipboard formats as WCHAR types...
#define T_CCF_DISPLAY_NAME    _T("CCF_DISPLAY_NAME")
#define T_CCF_NODETYPE        _T("CCF_NODETYPE")
#define T_CCF_SZNODETYPE      _T("CCF_SZNODETYPE")
#define T_CCF_SNAPIN_CLASSID  _T("CCF_SNAPIN_CLASSID")

#define T_CCF_BASENODE_PTR    _T("CCF_BASENODE_PTR")
#define T_CCF_DATAOBJ_PTR     _T("CCF_DATAOBJ_PTR")

//---------------------------------------------------------------------------
// Constants

#define NODETYPE_STATIC                100   // Node Types
#define NODETYPE_DEVICE                200 
#define NODETYPE_FOLDER                300   
#define NODETYPE_RESULT                400   // Not used in this sample 


#define ATTRIBUTE_DATA_ARCHIVE         2     // Node Attributes
#define ATTRIBUTE_DATA_HIDDEN          4
#define ATTRIBUTE_DATA_LOCKED          8
#define ATTRIBUTE_DATA_READONLY        16
#define ATTRIBUTE_BACKUP_DEVICE        2048  


#define IMG_DEVICE_DEFAULT             0     // Image Indexes 
#define IMG_DEVICE_OFFLINE             1
#define IMG_DATA_FILE                  2
#define IMG_DRIVE_DEFAULT              3
#define IMG_DRIVE_OFFLINE              4
#define IMG_FOLDER_DEFAULT             5
#define IMG_CDROM_DEFAULT              6
#define IMG_REMOVABLE_MEDIA            7

#define IDM_NEW_DEVICE                 100   // CONTEXTMENU:  Menu defines
#define IDM_NEW_FOLDER                 200
#define IDM_TOGGLE_STATUS              300

#define STATUS_ONLINE                  1
#define STATUS_OFFLINE                 0

// Define some custom window messages so that objects running in
// different threads can send us commands.
//
#define WM_DEL_DEVICENODES             (WM_USER + 100)
#define WM_ADD_DEVICENODE              (WM_USER + 101)
#define WM_DEVICENODE_CLOSED           (WM_USER + 102)

// Defines interfaces which can be requested from IComponentData
// or IComponet's ::GetInterface method
//
#define REQUEST_ICONSOLENAMESPACE2     1000
#define REQUEST_ICONSOLE               1001
#define REQUEST_ICONSOLEVERB           1002
#define REQUEST_IRESULTDATA            1003
#define REQUEST_IHEADERCTRL2           1004


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
