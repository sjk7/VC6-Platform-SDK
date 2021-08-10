//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      StdAfx.h
//
//  Description:
//      Project-wide include file.
//
//  Implementation Files:
//      StdAfx.cpp
//
//////////////////////////////////////////////////////////////////////////////

#pragma once


//////////////////////////////////////////////////////////////////////////////
// Project-wide pragmas
//////////////////////////////////////////////////////////////////////////////

#pragma warning( disable : 4127 )   // C4127: conditional expression is constant (BEGIN_COM_MAP)
#pragma warning( disable : 4505 )   // C4505: unreferenced local function has been removed
#pragma warning( disable : 4514 )   // C4514: unreferenced inline function has been removed
#pragma warning( disable : 4701 )   // C4701: local variable 'cchDestCurrent' may be used without having been initialized
#pragma warning( disable : 4710 )   // C4710: function not expanded


//////////////////////////////////////////////////////////////////////////////
// External Include Files
//////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif

#ifndef UNICODE
#define UNICODE
#endif

#pragma warning( push, 3 )

#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
#include <Windows.h>

extern CComModule _Module;

#include <atlcom.h>

//
// These two include files contain all ClusCfg interface definitions and CATIDs.
//

#include <ClusCfgServer.h>
#include <ClusCfgGuids.h>

#include <clusapi.h>
#include <assert.h>
#include <WBemCli.h>

//
// MyStorageResource.h is generated from MyStorageResource.idl.
//

#include "MyStorageResource.h"

#pragma warning( pop )


#pragma warning( push, 3 )
#include <strsafe.h>
#pragma warning( pop )


//////////////////////////////////////////////////////////////////////////////
// Local Includes Files
//////////////////////////////////////////////////////////////////////////////

#include "StringUtils.h"
#include "resource.h"
#include "guids.h"
#include "common.h"
#include "StringUtils.h"


//////////////////////////////////////////////////////////////////////////////
// Define's
//////////////////////////////////////////////////////////////////////////////

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

//
// Custom error code used by the WMI code.
//
const HRESULT   E_PROPTYPEMISMATCH = HRESULT_FROM_WIN32( ERROR_CLUSTER_PROPERTY_DATA_TYPE_MISMATCH );

//
//  HeapReAlloc does not follow the same rules as the CRT realloc() when
//  reallocating a NULL pointer.  This macro simulates the CRT behavior and
//  removes the need for the initial alloc of an empty buffer from the code.
//

#define HEAPREALLOC( _pvMem, _uBytes, _uFlags )     ( ( _pvMem == NULL ) \
                                                    ? HeapAlloc( GetProcessHeap(), _uFlags, _uBytes ) \
                                                    : HeapReAlloc( GetProcessHeap(), _uFlags, _pvMem, _uBytes ) )


//////////////////////////////////////////////////////////////////////////////
// Globals
//////////////////////////////////////////////////////////////////////////////

//
// This is the name of the cluster resource type that we use for this sample.
//

//
// TODO: Change this to match your new resource type name.  The resource type
//       display name is localizable and is located in the project's RC file.
//

#define RESTYPE_NAME L"Physical Disk"

//
// This is the name of the cluster resource type dll.
//

//
// TODO: Change this to the name of the accompanying resource dll.
//

#define RESTYPE_DLL_NAME L"clusres.dll"


//////////////////////////////////////////////////////////////////////////////
// Function Declarations
//////////////////////////////////////////////////////////////////////////////

HRESULT HrSetInitialize( IUnknown * punkIn, IClusCfgCallback * picccIn, LCID lcidIn );
