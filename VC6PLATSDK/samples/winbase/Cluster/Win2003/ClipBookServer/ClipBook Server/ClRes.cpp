/////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2003 <company name>
//
//  Module Name:
//      ClRes.cpp
//
//  Description:
//      Entry point module for resource type DLL.
//
//  Author:
//      <name> (<e-mail name>) Mmmm DD, 2003
//
//  Revision History:
//
//  Notes:
//
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "ClRes.h"
#include "CMgdResType.h"

//
// Main ATL COM module
//
CComModule _Module;

//
// List of all COM classes supported by this DLL
//
BEGIN_OBJECT_MAP( ObjectMap )
    OBJECT_ENTRY( CLSID_ClipBookServer, CMgdResType )
END_OBJECT_MAP()

//
// Global data.
//

// Event Logging routine.
PLOG_EVENT_ROUTINE g_pfnLogEvent = NULL;

// Resource Status routine for pending Online and Offline calls.
PSET_RESOURCE_STATUS_ROUTINE g_pfnSetResourceStatus = NULL;

// Handle to Service Control Manager set by the first Open resource call.
SC_HANDLE g_schSCMHandle = NULL;

//
// Function prototypes.
//

BOOL WINAPI DllMain(
      HINSTANCE hInstanceIn
    , DWORD     nReasonIn
    , LPVOID    ReservedIn
    );

STDAPI
DllCanUnloadNow( void );

STDAPI
DllGetClassObject(
      REFCLSID  rclsidIn
    , REFIID    riidIn
    , LPVOID *  ppvOut
    );

STDAPI
DllRegisterServer( void );

STDAPI
DllUnregisterServer( void );

DWORD WINAPI Startup(
      LPCWSTR                       pwszResourceTypeIn
    , DWORD                         nMinVersionSupportedIn
    , DWORD                         nMaxVersionSupportedIn
    , PSET_RESOURCE_STATUS_ROUTINE  pfnSetResourceStatusIn
    , PLOG_EVENT_ROUTINE            pfnLogEventIn
    , PCLRES_FUNCTION_TABLE *       pFunctionTableOut
    );


/////////////////////////////////////////////////////////////////////////////
//++
//
//  DllMain
//
//  Description:
//      Main DLL entry point.
//
//  Arguments:
//      hInstanceIn
//          DLL instance handle.
//
//      nReasonIn
//          Reason for being called.
//
//      ReservedIn
//          Reserved argument.
//
//  Return Value:
//      TRUE
//          Success.
//
//      FALSE
//          Failure.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL WINAPI
DllMain(
      HINSTANCE   hInstanceIn
    , DWORD       nReasonIn
    , LPVOID      ReservedIn
    )
{
    BOOL    fSuccess = TRUE;

    //
    // Perform global initialization.
    //

    switch ( nReasonIn )
    {
        case DLL_PROCESS_ATTACH:
            _Module.Init( ObjectMap, hInstanceIn );
            DisableThreadLibraryCalls( hInstanceIn );
            break;

        case DLL_PROCESS_DETACH:
            _Module.Term();
            break;

    } // switch: nReason

    //
    // Pass this request off to the resource type-specific routines.
    //

    fSuccess = ClipBookServerDllMain( hInstanceIn, nReasonIn, ReservedIn );

    return fSuccess;

} //*** DllMain


//////////////////////////////////////////////////////////////////////////////
//++
//
//  DllCanUnloadNow
//
//  Description:
//      Used to determine whether or not this DLL can be unloaded
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Yes.
//
//      S_FALSE
//          No.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllCanUnloadNow( void )
{
    return ( _Module.GetLockCount() == 0 ) ? S_OK : S_FALSE;

} //*** DllCanUnloadNow


//////////////////////////////////////////////////////////////////////////////
//++
//
//  DllGetClassObject
//
//  Description:
//      Returns a class factory to create an object of the requested type
//
//  Arguments:
//      rclsidIn
//      riidIn
//      ppvOut
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllGetClassObject(
      REFCLSID    rclsidIn
    , REFIID      riidIn
    , LPVOID *    ppvOut
    )
{
    return _Module.GetClassObject( rclsidIn, riidIn, ppvOut );

} //*** DllGetClassObject


//////////////////////////////////////////////////////////////////////////////
//++
//
//  DllRegisterServer
//
//  Description:
//      Adds entries to the system registry
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllRegisterServer( void )
{
    //
    //  registers object, typelib and all interfaces in typelib
    //

    return _Module.RegisterServer( TRUE );

} //*** DllRegisterServer


//////////////////////////////////////////////////////////////////////////////
//++
//
//  DllUnRegisterServer
//
//  Description:
//      Removes entries to the system registry
//
//  Arguments:
//      None.
//
//  Return Value:
//      S_OK
//          Success.
//
//      Other HRESULTs
//          Failure.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllUnregisterServer( void )
{
    return _Module.UnregisterServer( TRUE );

} //*** DllUnregisterServer


/////////////////////////////////////////////////////////////////////////////
//++
//
//  Startup
//
//  Description:
//      Startup the resource DLL. This routine verifies that at least one
//      currently supported version of the resource DLL is between
//      nMinVersionSupported and nMaxVersionSupported. If not, then the
//      resource DLL should return ERROR_REVISION_MISMATCH.
//
//      If more than one version of the resource DLL interface is supported
//      by the resource DLL, then the highest version (up to
//      nMaxVersionSupported) should be returned as the resource DLL's
//      interface. If the returned version is not within range, then startup
//      fails.
//
//      The Resource Type is passed in so that if the resource DLL supports
//      more than one Resource Type, it can pass back the correct function
//      table associated with the Resource Type.
//
//  Arguments:
//      pwszResourceTypeIn
//          Type of resource requesting a function table.
//
//      nMinVersionSupportedIn
//          Minimum resource DLL interface version supported by the cluster
//          software.
//
//      nMaxVersionSupportedIn
//          Maximum resource DLL interface version supported by the cluster
//          software.
//
//      pfnSetResourceStatusIn
//          Pointer to a routine that the resource DLL should call to update
//          the state of a resource after the Online or Offline routine
//          have returned a status of ERROR_IO_PENDING.
//
//      pfnLogEventIn
//          Pointer to a routine that handles the reporting of events from
//          the resource DLL.
//
//      pFunctionTableOut
//          Returns a pointer to the function table defined for the version
//          of the resource DLL interface returned by the resource DLL.
//
//  Return Value:
//      ERROR_SUCCESS
//          The operation was successful.
//
//      ERROR_CLUSTER_RESNAME_NOT_FOUND
//          The resource type name is unknown by this DLL.
//
//      ERROR_REVISION_MISMATCH
//          The version of the cluster service doesn't match the version of
//          the DLL.
//
//      Win32 error code
//          The operation failed.
//
//--
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI
Startup(
      LPCWSTR                         pwszResourceTypeIn
    , DWORD                           nMinVersionSupportedIn
    , DWORD                           nMaxVersionSupportedIn
    , PSET_RESOURCE_STATUS_ROUTINE    pfnSetResourceStatusIn
    , PLOG_EVENT_ROUTINE              pfnLogEventIn
    , PCLRES_FUNCTION_TABLE *         pFunctionTableOut
    )
{
    DWORD   sc = ERROR_CLUSTER_RESNAME_NOT_FOUND;

    //
    // Save the function pointers if they haven't been saved yet.
    //

    if ( g_pfnLogEvent == NULL )
    {
        g_pfnLogEvent = pfnLogEventIn;
        g_pfnSetResourceStatus = pfnSetResourceStatusIn;
    } // if: function pointers specified

    //
    // Call the resource type-specific Startup routine.
    //

    if ( NIStringCompareW( pwszResourceTypeIn, RESTYPE_NAME, RTL_NUMBER_OF( RESTYPE_NAME ) ) == 0 )
    {
        sc = ClipBookServerStartup(
                  pwszResourceTypeIn
                , nMinVersionSupportedIn
                , nMaxVersionSupportedIn
                , pfnSetResourceStatusIn
                , pfnLogEventIn
                , pFunctionTableOut
                );
    } // if: ClipBook Server resource type

    return sc;

} //*** Startup
