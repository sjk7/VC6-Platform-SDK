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
#include "BaseNode.h"

//---------------------------------------------------------------------------
// MMC's requiered clipboard formats

CLIPFORMAT g_cfDisplayName = 0;      // DisplayName for our SnapIn node
CLIPFORMAT g_cfNodeType    = 0;      // GUID of the selected node
CLIPFORMAT g_cfszNodeType  = 0;      // String representation of namespace GUID
CLIPFORMAT g_cfSnapinClsid = 0;      // Class ID of this SnapIn

//---------------------------------------------------------------------------
//  Custom clipboard formats

CLIPFORMAT g_cfBaseNodePtr = 0;
CLIPFORMAT g_cfDataObjPtr  = 0;


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
  SIZE_T nLen = wcslen( szWide ) +1;
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

void _fastcall Ansi2Unicode( CHAR* pszAnsi, WCHAR** ppszWide )
{
  SIZE_T ulSize = strlen( pszAnsi ) +1;                           
  *ppszWide = (WCHAR*)CoTaskMemAlloc( ulSize * sizeof(WCHAR) );  
  MultiByteToWideChar( CP_ACP, 0, pszAnsi, ulSize, *ppszWide, ulSize );
} 


void _fastcall CopyBuffer( WCHAR* szAnsi, WCHAR** ppszWide )
{
  SIZE_T ulSize = wcslen( szAnsi ) +1;                                 
  *ppszWide = (WCHAR*)CoTaskMemAlloc( ulSize * sizeof(WCHAR) );           
  wcscpy( *ppszWide, szAnsi ); 
}


//---------------------------------------------------------------------------
//  copies a string ( like strncpy )
//  in non-unicode version coverts ansi-to-unicode first.
//
void _fastcall CopyT2W( LPWSTR strDest, LPCTSTR strSource, size_t count)
{
#ifndef _UNICODE

	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, strSource, -1, strDest, count );

#else

	wcsncpy( strDest, strSource, count ); 

#endif

	if ( count > 0 )
		strDest[ count - 1 ] = 0;
}

//---------------------------------------------------------------------------
//
void InitClipboardFormats()
{
  g_cfDisplayName  = (CLIPFORMAT)RegisterClipboardFormat( T_CCF_DISPLAY_NAME );
  g_cfNodeType     = (CLIPFORMAT)RegisterClipboardFormat( T_CCF_NODETYPE );
  g_cfszNodeType   = (CLIPFORMAT)RegisterClipboardFormat( T_CCF_SZNODETYPE );
  g_cfSnapinClsid  = (CLIPFORMAT)RegisterClipboardFormat( T_CCF_SNAPIN_CLASSID );

  g_cfBaseNodePtr  = (CLIPFORMAT)RegisterClipboardFormat( T_CCF_BASENODE_PTR );
  g_cfDataObjPtr   = (CLIPFORMAT)RegisterClipboardFormat( T_CCF_DATAOBJ_PTR );

}

//---------------------------------------------------------------------------
//  Extracts data based on the passed-in clipboard format
//
HRESULT ExtractFromDataObject
(
  LPDATAOBJECT ipDataObject,   // [in]  Points to data object
  CLIPFORMAT   cfClipFormat,   // [in]  Clipboard format to use
  ULONG        nByteCount,     // [in]  Number of bytes to allocate
  HGLOBAL      *phGlobal       // [out] Points to the data we want 
)
{
  _ASSERT( NULL != ipDataObject );

            *phGlobal = NULL;
  HRESULT   hResult   = S_FALSE;
  STGMEDIUM StgMedium = { TYMED_HGLOBAL,  NULL  };
  FORMATETC FormatEtc = { cfClipFormat, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };

  do 
	{
    // Allocate memory for the stream           
    StgMedium.hGlobal = ::GlobalAlloc( GMEM_SHARE, nByteCount );

		if( NULL == StgMedium.hGlobal )
    {
      hResult = E_OUTOFMEMORY;
      break;
    }

    // Attempt to get data from the object
    hResult = ipDataObject->GetDataHere( &FormatEtc, &StgMedium );
    if( FAILED(hResult) )
    {
      break;       
    }
    // StgMedium now has the data we need 
    *phGlobal = StgMedium.hGlobal;
    StgMedium.hGlobal = NULL;

  } while (0); 

  if( FAILED(hResult) && StgMedium.hGlobal )
  {
    HGLOBAL hRetVal = ::GlobalFree(StgMedium.hGlobal);   
    _ASSERT( NULL == hRetVal );         // Must return NULL
  }
  return hResult;

} 


//---------------------------------------------------------------------------
//  This helper returns the current BaseNode object on the custom
//  g_cfBaseNodePtr clipboard format
// 
CBaseNode* ExtractBaseNodePtr
(
  LPDATAOBJECT ipDataObject      // [in] IComponent pointer 
)
{
  LPBASENODE  pNode   = NULL;
  HGLOBAL     hGlobal = NULL;
  HRESULT     hResult = S_FALSE;

  hResult = ExtractFromDataObject( ipDataObject,
                                   g_cfBaseNodePtr,
                                   sizeof(LPBASENODE),
                                   &hGlobal
                                 );
  if( SUCCEEDED(hResult) )
  {
    pNode = *(LPBASENODE*)(hGlobal);
    HGLOBAL hRetVal = GlobalFree(hGlobal);   
    _ASSERT( NULL == hRetVal );        // Must return NULL
  }

  return pNode;

} 

//---------------------------------------------------------------------------
//  Converts an IDataObject pointer to a CDataObject pointer by 
//  retrieving a "this" pointer using a custom clipboard format.
// 
CDataObject* ExtractDataObjPtr
(
  LPDATAOBJECT ipDataObject      //[in] IDataObject pointer 
)
{
  _ASSERT( 0 != g_cfDataObjPtr );

  HGLOBAL      hGlobal = NULL;
  HRESULT      hResult = S_OK;
  CDataObject* pDO     = NULL;

  hResult = ExtractFromDataObject( ipDataObject,
                                   g_cfDataObjPtr, 
                                   sizeof(CDataObject **),
                                   &hGlobal
                                 );

  if( SUCCEEDED(hResult) )
  {
    pDO = *(CDataObject **)(hGlobal);
    _ASSERT( NULL != pDO );    

    HGLOBAL hRetVal = GlobalFree(hGlobal);   
    _ASSERT( NULL == hRetVal );       // Must return NULL
  }

  return pDO;

} 

//---------------------------------------------------------------------------
//  MMC_HELP:  This is where we get the path to the Snap-in's help
//  file.  In this sample we are assuming the help file is in the
//  same directory at the Snap-in.  This is the recommended procedure
//  for Snap-ins
//
LPOLESTR GetHelpFilePath()
{
  // First we need a temp buffer
  DWORD  dwTempSize = (MAX_PATH) * sizeof(TCHAR);  
  LPTSTR pszTempPath = (LPTSTR)CoTaskMemAlloc( dwTempSize );

  // Get the path to the help file in TCHAR
  GetModuleFileName( g_hInst, pszTempPath, dwTempSize );
  PathRemoveFileSpec( pszTempPath );
  _tcscat( pszTempPath, _T("\\Ppage.chm") );  

  // Convert to wide string if we're on Win9X, copy to buffer on NT
  LPOLESTR pszHelpPath = NULL;
  T2W( pszTempPath, &pszHelpPath );   

  CoTaskMemFree( pszTempPath );

  return pszHelpPath;  
}

