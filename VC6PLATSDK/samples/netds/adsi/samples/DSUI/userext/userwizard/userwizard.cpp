//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       userwizard.cpp
//
//--------------------------------------------------------------------------

// dscreate.cpp : Implementation of DLL Exports.

#include "stdafx.h"

// initguid.h requires this.
//
#include <objbase.h>

// this redefines the DEFINE_GUID() macro to do allocation.
//
#include <initguid.h>

//#include <dsshell.h>

#include <dsadmin.h>

#include "resource.h"
#include "userwizard.h"
#include "WizExt.h"

// {C03793D3-A7C8-11d1-B940-00A0C9A06D2D}
static const GUID CLSID_WizExtUser = 
{ 0xc03793d3, 0xa7c8, 0x11d1, { 0xb9, 0x40, 0x0, 0xa0, 0xc9, 0xa0, 0x6d, 0x2d } };

CMyWizExtModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
  OBJECT_ENTRY(CLSID_WizExtUser,      CWizExtUser)
END_OBJECT_MAP()

class CMyWizExtApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
};

CMyWizExtApp theApp;

BOOL CMyWizExtApp::InitInstance()
{
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CMyWizExtApp::ExitInstance()
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


