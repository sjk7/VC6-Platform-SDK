//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      MyStorageResource.cpp
//
//  Description:
//      Main DLL code. Contains ATL stub code
//
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Include Files
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CEnumStorageResource.h"
#include "CStorageResource.h"
#include "CStorageResType.h"
#include "CPartitionInfo.h"

//
// Main ATL COM module
//

CComModule _Module;

//
// List of all COM classes supported by this DLL
//

BEGIN_OBJECT_MAP( ObjectMap )
    OBJECT_ENTRY( CLSID_CEnumStorageResource,   CEnumStorageResource )
    OBJECT_ENTRY( CLSID_CStorageResource,       CStorageResource )
    OBJECT_ENTRY( CLSID_CStorageResType,        CStorageResType )
    OBJECT_ENTRY( CLSID_CPartitionInfo,         CPartitionInfo )
END_OBJECT_MAP()


//////////////////////////////////////////////////////////////////////////////
//++
//
//  DllMain
//
//  Description:
//      Main DLL entry point function
//
//  Arguments:
//      IN  HINSTANCE   hInstance
//      IN  DWORD       dwReason
//      IN  LPVOID
//
//  Return Value:
//      TRUE    Success
//
//--
//////////////////////////////////////////////////////////////////////////////
extern "C"
BOOL
WINAPI
DllMain(
      HINSTANCE   hInstance
    , DWORD       dwReason
    , LPVOID      pvReserved
    )
{
    UNREFERENCED_PARAMETER( pvReserved );

    if ( dwReason == DLL_PROCESS_ATTACH )
    {
        _Module.Init( ObjectMap, hInstance, &LIBID_MyStorageResourceLib );
        DisableThreadLibraryCalls( hInstance );
    } // if: we are being loaded
    else if ( dwReason == DLL_PROCESS_DETACH )
    {
        _Module.Term();
    } // else: we are being unloaded

    return TRUE;    // ok

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
//      S_OK        Yes
//      S_FALSE     No
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
//      S_OK    Success
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllGetClassObject(
    REFCLSID    rclsidIn,
    REFIID      riidIn,
    LPVOID *    ppvOut
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
//      S_OK    Success
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllRegisterServer( void )
{
    // registers object, typelib and all interfaces in typelib
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
//      S_OK    Success
//
//  Remarks:
//      None.
//
//--
//////////////////////////////////////////////////////////////////////////////
STDAPI
DllUnregisterServer( void )
{
    return _Module.UnregisterServer( TRUE );

} //*** DllUnregisterServer
