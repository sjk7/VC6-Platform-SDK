//////////////////////////////////////////////////////////////////////////////
//
//  Module Name:
//      Dll.cpp
//
//  Description:
//      Implementation of DLL Exports.
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#include "MyCapabilities.h"

CComModule _Module;

BEGIN_OBJECT_MAP( ObjectMap )
OBJECT_ENTRY( CLSID_MyCapabilities, CMyCapabilities )
END_OBJECT_MAP()


/////////////////////////////////////////////////////////////////////////////
//++
//
// DllMain
//
// Description:
//      DLL entry point.
//
//--
/////////////////////////////////////////////////////////////////////////////
extern "C"
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/ )
{
    if ( dwReason == DLL_PROCESS_ATTACH )
    {
        _Module.Init( ObjectMap, hInstance ); // no typelib
        DisableThreadLibraryCalls( hInstance );
    }
    else if ( dwReason == DLL_PROCESS_DETACH )
    {
        _Module.Term();
    }
    return TRUE;    // ok

} //*** DllMain

/////////////////////////////////////////////////////////////////////////////
//++
//
// DllCanUnloadNow
//
// Description:
//      Used to determine whether the DLL can be unloaded by OLE.
//
//--
/////////////////////////////////////////////////////////////////////////////
STDAPI DllCanUnloadNow( void )
{
    return ( _Module.GetLockCount()==0 ) ? S_OK : S_FALSE;

} //*** DllCanUnloadNow

/////////////////////////////////////////////////////////////////////////////
//++
//
// DllGetClassObject
//
// Description:
//      Returns a class factory to create an object of the requested type.
//
//--
/////////////////////////////////////////////////////////////////////////////
STDAPI DllGetClassObject( REFCLSID rclsid, REFIID riid, LPVOID * ppv )
{
    return _Module.GetClassObject( rclsid, riid, ppv );

} //*** DllGetClassObject

/////////////////////////////////////////////////////////////////////////////
//++
//
// DllRegisterServer
//
// Description:
//      Adds entries to the system registry.
//
//--
/////////////////////////////////////////////////////////////////////////////
STDAPI DllRegisterServer( void )
{
    // registers object; FALSE => no typelib
    return _Module.RegisterServer( FALSE );

} //*** DllRegisterServer

/////////////////////////////////////////////////////////////////////////////
//++
//
// DllUnregisterServer
//
// Description:
//      Removes entries from the system registry.
//
//--
/////////////////////////////////////////////////////////////////////////////
STDAPI DllUnregisterServer( void )
{
    return _Module.UnregisterServer( FALSE ); // FALSE => no typelib

} //*** DllUnregisterServer


