/*+==========================================================================
  File:      QCNotify.cpp
  Summary:   Implementation of DLL exports
  Classes:   None
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995 - 2000 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include <adoid.h>		// ADO
#include "QCNotify.h"

#include "QCNotify_i.c"
#include "Notify.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Notify, CONotify)
END_OBJECT_MAP()

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllMain
  Summary:  Main QCNotify DLL entry point
  Args:     HINSTANCE hInstance		An instance identifier
			DWORD dwReason			Reason DLL loaded
			LPVOID                  Reserved 
  Returns:  BOOL - always TRUE
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllCanUnloadNow
  Summary:  Is this DLL in use or can it be unloaded
  Args:     None
  Returns:  S_OK    Can be unloaded
            S_FALSE Still in use
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllGetClassObject
  Summary:  Returns a class factory to create an object of the requested type
  Args:     REFCLSID rclsid     Class ID
            REFIID riid         Interface ID
            LPVOID *ppv         Returned class factory
  Returns:  Status from GetClassObject
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllRegisterServer
  Summary:  Adds entries to the system registry
  Args:     None
  Returns:  Status from RegisterServer
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllUnregisterServer
  Summary:  Removes entries from the system registry
  Args:     None
  Returns:  Status from UnregisterServer
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}


