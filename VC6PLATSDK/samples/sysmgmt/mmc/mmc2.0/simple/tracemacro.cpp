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

  TCHAR  szEventStr[22];
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
    case 0x8001:
      _tcscpy( szEventStr, _T("MMCN_ACTIVATE       ") );
      break;

    case 0x8002:
      _tcscpy( szEventStr, _T("MMCN_ADD_IMAGES     ") );
      break;

    case 0x8003:
      _tcscpy( szEventStr, _T("MMCN_BTN_CLICK      ") );
      break;

    case 0x8004:
      _tcscpy( szEventStr, _T("MMCN_CLICK          ") );
      break;

    case 0x8005:
      _tcscpy( szEventStr, _T("MMCN_COLUMN_CLICK   ") );
      break;

    case 0x8006:
      _tcscpy( szEventStr, _T("MMCN_CONTEXTMENU    ") );
      break;

    case 0x8007:
      _tcscpy( szEventStr, _T("MMCN_CUTORMOVE      ") );
      break;

    case 0x8008:
      _tcscpy( szEventStr, _T("MMCN_DBLCLICK       ") );
      break;

    case 0x8009:
      _tcscpy( szEventStr, _T("MMCN_DELETE         ") );
      break;

    case 0x800A:
      _tcscpy( szEventStr, _T("MMCN_DESELECT_ALL   ") );
      break;

    case 0x800B:
      _tcscpy( szEventStr, _T("MMCN_EXPAND         ") );
      break;

    case 0x800C:
      _tcscpy( szEventStr, _T("MMCN_HELP           ") );
      break;

    case 0x800D:
      _tcscpy( szEventStr, _T("MMCN_MENU_BTNCLICK  ") );
      break;

    case 0x800E:
      _tcscpy( szEventStr, _T("MMCN_MINIMIZED      ") );
      break;

    case 0x800F:
      _tcscpy( szEventStr, _T("MMCN_PASTE          ") );
      break;
      
    case 0x8010:
      _tcscpy( szEventStr, _T("MMCN_PROPERTY_CHANGE") );
      break;

    case 0x8011:
      _tcscpy( szEventStr, _T("MMCN_QUERY_PASTE    ") );
      break;

    case 0x8012:
      _tcscpy( szEventStr, _T("MMCN_REFRESH        ") );
      break;

    case 0x8013:
      _tcscpy( szEventStr, _T("MMCN_REMOVE_CHILDREN") );
      break;

    case 0x8014:
      _tcscpy( szEventStr, _T("MMCN_RENAME         ") );
      break;
 
    case 0x8015:
      _tcscpy( szEventStr, _T("MMCN_SELECT         ") );
      break;

    case 0x8016:
      _tcscpy( szEventStr, _T("MMCN_SHOW           ") );
      break;
      
    case 0x8017:
      _tcscpy( szEventStr, _T("MMCN_VIEW_CHANGE    ") );
      break;

    case 0x8018:
      _tcscpy( szEventStr, _T("MMCN_SNAPINHELP     ") );
      break;
      
    case 0x8019:
      _tcscpy( szEventStr, _T("MMCN_CONTEXTHELP    ") );
      break;

    case 0x801A:
      _tcscpy( szEventStr, _T("MMCN_INITOCX        ") );
      break;

    case 0x8021:
      _tcscpy( szEventStr, _T("MMCN_EXPANDSYNC     ") );
      break;

    default:
      _stprintf( szEventStr, _T("0x%X"), Event );
      break;
  }

#endif
} //end MapEvent()
