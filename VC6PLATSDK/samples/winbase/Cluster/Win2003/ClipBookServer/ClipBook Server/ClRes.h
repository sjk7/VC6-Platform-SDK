/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2003 <company name>
//
//  Module Name:
//      ClRes.h
//
//  Implementation File:
//      ClRes.cpp
//
//  Description:
//      Main header file for the resource DLL for ClipBook Server (ClipBook Server).
//
//  Author:
//      <name> (<e-mail name>) Mmmm DD, 2003
//
//  Revision History:
//
//  Notes:
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Include Files
/////////////////////////////////////////////////////////////////////////////

#define UNICODE 1
#define _UNICODE 1
#define _ATL_APARTMENT_THREADED
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif

#pragma warning( disable : 4127 )   // conditional expression is constant (BEGIN_COM_MAP)
#pragma warning( disable : 4505 )   // unreferenced local function has been removed
#pragma warning( disable : 4511 )   // copy constructor could not be generated
#pragma warning( disable : 4514 )   // unreferenced inline function has been removed
#pragma warning( disable : 4710 )   // function not expanded / function '<x>' not inlined

#pragma warning( push )

//
// ATL includes
//
#include <atlbase.h>

extern CComModule _Module;

#include <atlcom.h>

//
// These two include files contain all ClusCfg interface definitions and CATIDs
//
#include <ClusCfgServer.h>
#include <ClusCfgGuids.h>

//
// MgdResource.h is generated from MgdResource.idl.
//
#include "MgdResource.h"
#include "resource.h"

#include <windows.h>
#include <clusapi.h>
#include <resapi.h>
#include <stdio.h>
#include <strsafe.h>
#include <assert.h>
#pragma warning( pop )

#include "StringUtils.h"
#include "guids.h"

/////////////////////////////////////////////////////////////////////////////
// ClipBook Server Definitions
/////////////////////////////////////////////////////////////////////////////

//
// This is the name of the cluster resource type.
//

#define RESTYPE_NAME        L"ClipBook Server"

//
// This is the dll name.
//

#define RESTYPE_DLL_NAME    L"ClipBook Server.dll"

//
// This is the name of the service this resource type controls.
//

#define CLIPBOOKSERVER_SVCNAME   L"ClipSrv"

BOOL WINAPI ClipBookServerDllMain(
      HINSTANCE hDllHandleIn
    , DWORD     nReasonIn
    , LPVOID    ReservedIn
    );

DWORD WINAPI ClipBookServerStartup(
      LPCWSTR                       pwszResourceTypeIn
    , DWORD                         nMinVersionSupportedIn
    , DWORD                         nMaxVersionSupportedIn
    , PSET_RESOURCE_STATUS_ROUTINE  pfnSetResourceStatusIn
    , PLOG_EVENT_ROUTINE            pfnLogEventIn
    , PCLRES_FUNCTION_TABLE *       pFunctionTableOut
    );

/////////////////////////////////////////////////////////////////////////////
// General Definitions
/////////////////////////////////////////////////////////////////////////////

#define RESOURCE_TYPE_IP_ADDRESS    L"IP Address"
#define RESOURCE_TYPE_NETWORK_NAME  L"Network Name"

#define DBG_PRINT printf

/////////////////////////////////////////////////////////////////////////////
// Global Variables and Prototypes
/////////////////////////////////////////////////////////////////////////////

//
// Event Logging routine.
//

extern PLOG_EVENT_ROUTINE g_pfnLogEvent;

//
// Resource Status routine for pending Online and Offline calls.
//

extern PSET_RESOURCE_STATUS_ROUTINE g_pfnSetResourceStatus;

//
// Handle to Service Control Manager set by the first Open resource call.
//

extern SC_HANDLE g_schSCMHandle;


/////////////////////////////////////////////////////////////////////////////
// Macro Definitions
/////////////////////////////////////////////////////////////////////////////

#ifndef RTL_NUMBER_OF
#define RTL_NUMBER_OF(A) (sizeof(A)/sizeof((A)[0]))
#endif

//
// COM Macros to gain type checking.
//

#if !defined( TypeSafeParams )
#define TypeSafeParams( _interface, _ppunk ) \
    IID_##_interface, reinterpret_cast< void ** >( static_cast< _interface ** >( _ppunk ) )
#endif // !defined( TypeSafeParams )

#if !defined( TypeSafeQI )
#define TypeSafeQI( _interface, _ppunk ) \
    QueryInterface( TypeSafeParams( _interface, _ppunk ) )
#endif // !defined( TypeSafeQI )
