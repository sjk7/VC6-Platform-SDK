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
#include <CommCtrl.h>                  // Needed for button styles...
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

extern UINT g_cfMS_Snapins;       // MULTISELECT: New clipformats MMC is
extern UINT g_cfMS_Objects;       // go to ask us for.
extern UINT g_cfMS_IsMsObj;

extern UINT g_cfMS_Cookies;

//---------------------------------------------------------------------------
//  Global function prototypes

void _fastcall Unicode2Ansi( CHAR** pszAnsi, WCHAR* szWide );
void _fastcall CopyT2W( LPWSTR strDest, LPCTSTR strSource, size_t count);

void InitClipboardFormats();

DWORD  IsCompositeDataObject( LPDATAOBJECT ipDataObject );

HRESULT ExtractFromDataObject( LPDATAOBJECT ipDataObject,UINT cf,ULONG cb,HGLOBAL *phGlobal );

CBaseNode* ExtractBaseNodePtr( LPDATAOBJECT ipDataObject );
CDataObject* ExtractDataObjPtr( LPDATAOBJECT ipDataObject );

//---------------------------------------------------------------------------
//  Global Strings


static TCHAR*  gtszSNAPIN_NAME       = _T("Sample M (MMC 2.0) - MultiSelect");
static TCHAR*  gtszABOUT_NAME        = _T("Sample M (MMC 2.0) - ISnapinAbout");


static WCHAR*  gwszROOT_NODE_NAME    = L"MultiSelect Sample";
static WCHAR*  gwszABOUT_DESCRIPTION = L"MMC SDK MultiSelect Sample";
static WCHAR*  gwszABOUT_PROVIDER    = L"Copyright © 1999 - 2001 Microsoft Corporation";
static WCHAR*  gwszABOUT_VERSION     = L"2.0";

// We need to do this to get around MMC.IDL - it explicitly defines
// the clipboard formats as WCHAR types...
#define T_CCF_DISPLAY_NAME    _T("CCF_DISPLAY_NAME")
#define T_CCF_NODETYPE        _T("CCF_NODETYPE")
#define T_CCF_SZNODETYPE      _T("CCF_SZNODETYPE")
#define T_CCF_SNAPIN_CLASSID  _T("CCF_SNAPIN_CLASSID")

#define T_CCF_BASENODE_PTR    _T("CCF_BASENODE_PTR")
#define T_CCF_DATAOBJ_PTR     _T("CCF_DATAOBJ_PTR")


// MULTISELECT: Define required clipboard formats
#define T_CCF_MULTI_SELECT_SNAPINS          _T("CCF_MULTI_SELECT_SNAPINS")
#define T_CCF_OBJECT_TYPES_IN_MULTI_SELECT  _T("CCF_OBJECT_TYPES_IN_MULTI_SELECT")
#define T_CCF_MMC_MULTISELECT_DATAOBJECT    _T("CCF_MMC_MULTISELECT_DATAOBJECT")

#define T_CCF_MULTISELECT_COOKIES           _T("CCF_MULTISELECT_COOKIES")

//---------------------------------------------------------------------------
// Constants

#define NODETYPE_STATIC                100   // Node Types
#define NODETYPE_DEVICE                200 
#define NODETYPE_FOLDER                300   
#define NODETYPE_RESULT                400   
#define NODETYPE_VFILE                 500


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

#define IDM_NEW_DEVICE                 100   // Menu defines
#define IDM_NEW_FOLDER                 200
#define IDM_TOGGLE_STATUS              300
#define IDM_NEW_VIRTFILE               400
#define IDM_CLEAR_ATTRIBS              500

#define STATUS_ONLINE                  1
#define STATUS_OFFLINE                 0

// Define some custom window messages so that objects running in
// different threads can send us commands.
//
#define WM_DELETE_NODE                 (WM_USER + 100)
#define WM_ADDNEW_NODE                 (WM_USER + 101)
#define WM_DIALOG_CLOSED               (WM_USER + 102)
#define WM_ADD_VIRTUALFILE             (WM_USER + 103)
#define WM_VIRTUALFILE_CLOSED          (WM_USER + 104)

// Defines interfaces which can be requested from IComponentData
// or CComponent's ::GetInterface method
//
#define REQUEST_ICONSOLENAMESPACE      1000
#define REQUEST_ICONSOLE               1001
#define REQUEST_ICONSOLEVERB           1002
#define REQUEST_IRESULTDATA            1003
#define REQUEST_IHEADERCTRL            1004
#define REQUEST_ICONTROLBAR            1005  
#define REQUEST_ISTATICTOOLBAR         1006
#define REQUEST_IDEVICETOOLBAR         1007
#define REQUEST_IVFILETOOLBAR          1008


/////////////////////////////////////////////////////////////////////////////
//  IExtendControlbar:  Create button structs which map the menu commands.

static MMCBUTTON StaticToolButtons[] =
{
 { 0, IDM_NEW_DEVICE, TBSTATE_ENABLED, TBSTYLE_BUTTON, L"Device", L"New Device" }
};


static MMCBUTTON DeviceToolButtons[] =
{
 { 0, IDM_NEW_FOLDER, TBSTATE_ENABLED, TBSTYLE_BUTTON, L"Folder", L"Create New Folder" },
 { 1, IDM_TOGGLE_STATUS, TBSTATE_ENABLED, TBSTYLE_BUTTON, L"Toggle", L"Toggle Device Status" }
};


static MMCBUTTON VFileToolButtons[] =
{
 { 0, IDM_CLEAR_ATTRIBS, TBSTATE_ENABLED, TBSTYLE_BUTTON, L"Clear", L"Clear Attributes" }
};


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
