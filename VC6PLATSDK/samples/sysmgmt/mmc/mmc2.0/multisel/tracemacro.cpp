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
#include "TraceMacro.h"
#include <StdIo.h>             // Needed for sprintf on Win98


//---------------------------------------------------------------------------
//  Function implementations
//

//---------------------------------------------------------------------------
//  Provides trace output for HRESULTs in hex.                                      
//
VOID Trace_HR  
( 
  LPCTSTR pszClass,        //[in] Class name for message
  LPCTSTR pszFunction,     //[in] Function name for message
  HRESULT hr               //[in] HRESULT to display as a value
)
{
#ifdef _DEBUG

  TCHAR  szBuffer[512];
  TCHAR  szFormat[] = _T("%s::%s-> Returned 0x%X\n");
  INT    nChars     = 0;

  nChars = _stprintf( szBuffer, szFormat, pszClass, pszFunction, hr );
  _ASSERTE( nChars < sizeof(szBuffer) );

  OutputDebugString( szBuffer );

#endif
} //end Trace_HR() 


//---------------------------------------------------------------------------
//  Provides trace output for user defined numeric values in the form:
//    "CClassName::MyFunctionName-> UserDefinedValueString = 99"                                     
//
VOID Trace_Value  
( 
  LPCTSTR pszClass,        //[in] Class name for message
  LPCTSTR pszFunction,     //[in] Function name for message
  LPCTSTR pszValueName,    //[in] Value name for message
  LONG    nValue           //[in] Numeric value for message
)
{
#ifdef _DEBUG

  TCHAR  szBuffer[512];
  TCHAR  szFormat[] = _T("%s::%s-> %s = %u\n");
  INT    nChars     = 0;

  nChars = _stprintf( szBuffer,
                      szFormat,
                      pszClass,
                      pszFunction,
                      pszValueName,
                      nValue
                    );
  _ASSERTE( nChars < sizeof(szBuffer) );

  OutputDebugString( szBuffer );

#endif
} //end Trace_Value() 

//---------------------------------------------------------------------------
//  Provides trace output for user defined numeric values in the form:
//    "CClassName::MyFunctionName-> UserDefinedValueString = 99"                                     
//
VOID Trace_Pointer  
( 
  LPCTSTR pszClass,        //[in] Class name for message
  LPCTSTR pszFunction,     //[in] Function name for message
  LPCTSTR pszObject,       //[in] Action which was taken
  ULONG   ulValue          //[in] Numeric value for message
)
{
#ifdef _DEBUG

  TCHAR  szBuffer[512];
  TCHAR  szFormat[] = _T("%s::%s-> %s = 0x%X\n");
  INT    nChars     = 0;

  nChars = _stprintf( szBuffer,
                      szFormat,
                      pszClass,
                      pszFunction,
                      pszObject,
                      ulValue
                    );
  _ASSERTE( nChars < sizeof(szBuffer) );

  OutputDebugString( szBuffer );

#endif
} //end Trace_Pointer() 


//---------------------------------------------------------------------------
//  Provides trace output which shows the class name, function name, and
//  a string which maps to an MMC notification.
//
VOID Trace_Event
( 
  LPCTSTR pszClass,        //[in] Class name for message
  LPCTSTR pszFunction,     //[in] Event name for message
  LONG    nEvent           //[in] Event code to map to string
)
{
#ifdef _DEBUG

  TCHAR  szEventStr[64];
  TCHAR  szBuffer[512];
  TCHAR  szFormat[] = _T("%s::%s-> Event = %s\n");
  INT    nChars     = 0;

  MapEvent( nEvent, szEventStr );

  nChars = _stprintf( szBuffer,
                      szFormat,
                      pszClass,
                      pszFunction,
                      szEventStr
                    );
  _ASSERTE( nChars < sizeof(szBuffer) );
  
  OutputDebugString( szBuffer );

#endif
} //end Trace_Event()

//---------------------------------------------------------------------------
//  Provides trace output which shows the class name and function name 
//
VOID Trace_Start
( 
  LPCTSTR pszClass,        //[in] Class name for message
  LPCTSTR pszFunction      //[in] Event name for message
)
{
#ifdef _DEBUG

  TCHAR  szBuffer[512];
  TCHAR  szFormat[] = _T("%s::%s-> Started \n");
  INT    nChars     = 0;

  nChars = _stprintf( szBuffer,
                      szFormat,
                      pszClass,
                      pszFunction
                    );
  _ASSERTE( nChars < sizeof(szBuffer) );
  
  OutputDebugString( szBuffer );

#endif
} //end Trace_Start()



//---------------------------------------------------------------------------
// Provides human readable output for notifications
//
VOID MapEvent( LONG Event, LPTSTR szEventStr )
{
#ifdef _DEBUG

  switch( Event )
  {
    case MMCN_ACTIVATE:
      _tcscpy( szEventStr, _T("MMCN_ACTIVATE          ") );
      break;

    case MMCN_ADD_IMAGES:
      _tcscpy( szEventStr, _T("MMCN_ADD_IMAGES        ") );
      break;

    case MMCN_BTN_CLICK:
      _tcscpy( szEventStr, _T("MMCN_BTN_CLICK         ") );
      break;

    case MMCN_CLICK:
      _tcscpy( szEventStr, _T("MMCN_CLICK             ") );
      break;

    case MMCN_COLUMN_CLICK:
      _tcscpy( szEventStr, _T("MMCN_COLUMN_CLICK       ") );
      break;

    case MMCN_CONTEXTMENU:
      _tcscpy( szEventStr, _T("MMCN_CONTEXTMENU        ") );
      break;

    case MMCN_CUTORMOVE:
      _tcscpy( szEventStr, _T("MMCN_CUTORMOVE          ") );
      break;

    case MMCN_DBLCLICK:
      _tcscpy( szEventStr, _T("MMCN_DBLCLICK           ") );
      break;

    case MMCN_DELETE:
      _tcscpy( szEventStr, _T("MMCN_DELETE             ") );
      break;

    case MMCN_DESELECT_ALL:
      _tcscpy( szEventStr, _T("MMCN_DESELECT_ALL       ") );
      break;

    case MMCN_EXPAND:
      _tcscpy( szEventStr, _T("MMCN_EXPAND             ") );
      break;

    case MMCN_HELP:
      _tcscpy( szEventStr, _T("MMCN_HELP               ") );
      break;

    case MMCN_MENU_BTNCLICK:
      _tcscpy( szEventStr, _T("MMCN_MENU_BTNCLICK      ") );
      break;

    case MMCN_MINIMIZED:
      _tcscpy( szEventStr, _T("MMCN_MINIMIZED          ") );
      break;

    case MMCN_PASTE:
      _tcscpy( szEventStr, _T("MMCN_PASTE              ") );
      break;
      
    case MMCN_PROPERTY_CHANGE:
      _tcscpy( szEventStr, _T("MMCN_PROPERTY_CHANGE    ") );
      break;

    case MMCN_QUERY_PASTE:
      _tcscpy( szEventStr, _T("MMCN_QUERY_PASTE        ") );
      break;

    case MMCN_REFRESH:
      _tcscpy( szEventStr, _T("MMCN_REFRESH            ") );
      break;

    case MMCN_REMOVE_CHILDREN:
      _tcscpy( szEventStr, _T("MMCN_REMOVE_CHILDREN    ") );
      break;

    case MMCN_RENAME:
      _tcscpy( szEventStr, _T("MMCN_RENAME             ") );
      break;
 
    case MMCN_SELECT:
      _tcscpy( szEventStr, _T("MMCN_SELECT             ") );
      break;

    case MMCN_SHOW:
      _tcscpy( szEventStr, _T("MMCN_SHOW               ") );
      break;
      
    case MMCN_VIEW_CHANGE:   
      _tcscpy( szEventStr, _T("MMCN_VIEW_CHANGE        ") );
      break;

    case MMCN_SNAPINHELP:
      _tcscpy( szEventStr, _T("MMCN_SNAPINHELP         ") );
      break;
      
    case MMCN_CONTEXTHELP:
      _tcscpy( szEventStr, _T("MMCN_CONTEXTHELP        ") );
      break;

    case MMCN_INITOCX:
      _tcscpy( szEventStr, _T("MMCN_INITOCX            ") );
      break;

    // MMC Version 1.1 notifications
    case MMCN_FILTER_CHANGE:
      _tcscpy( szEventStr, _T("MMCN_FILTER_CHANGE      ") );
      break;

    case MMCN_FILTERBTN_CLICK:
      _tcscpy( szEventStr, _T("MMCN_FILTERBTN_CLICK    ") );
      break;

    case MMCN_RESTORE_VIEW:
      _tcscpy( szEventStr, _T("MMCN_RESTORE_VIEW       ") );
      break;

    case MMCN_PRINT:
      _tcscpy( szEventStr, _T("MMCN_PRINT              ") );
      break;

    case MMCN_PRELOAD:
      _tcscpy( szEventStr, _T("MMCN_PRELOAD            ") );
      break;

    case MMCN_LISTPAD:
      _tcscpy( szEventStr, _T("MMCN_LISTPAD            ") );
      break;

    case MMCN_EXPANDSYNC:
      _tcscpy( szEventStr, _T("MMCN_EXPANDSYNC         ") );
      break;

    // MMC Version 1.2 notifications 
    case MMCN_COLUMNS_CHANGED:
      _tcscpy( szEventStr, _T("MMCN_COLUMNS_CHANGED    ") );
      break;
    
    default:
      _stprintf( szEventStr, _T("0x%X"), Event );
      break;
  }

#endif
} //end MapEvent()
