//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       SCPCMenu.cpp
//
//--------------------------------------------------------------------------

// dsshexten.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "initguid.h"

#include <dsadmin.h>
#include "SCPCMenu.h"

#include "dsmenu.h"

/////////////////////////////////////////////////////////////////////////////////

// {2CE182CC-DD9D-11d2-AB28-01C04F68FA4A}
static const CLSID CLSID_SCPContextMenu = 
  {	0x2ce182cc, 0xdd9d, 0x11d2, { 0xab, 0x28, 0x01, 0xc0, 0x4f, 0x68, 0xfa, 0x4a } };



CSCPContextMenuModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
  OBJECT_ENTRY(CLSID_SCPContextMenu, CContextMenu)
END_OBJECT_MAP()

class CSCPCMenuApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CSCPCMenuApp theApp;

BOOL CSCPCMenuApp::InitInstance()
{
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CSCPCMenuApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

BOOL x = TRUE;
STDAPI DllRegisterServer(void)
{
    return _Module.RegisterServer(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}



