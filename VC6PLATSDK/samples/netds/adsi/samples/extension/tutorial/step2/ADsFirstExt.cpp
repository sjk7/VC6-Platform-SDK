// ADsFirstExt.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f ADsFirstExtps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "ADsFirstExt.h"

#include "ADsFirstExt_i.c"
#include "HelloWorld.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_HelloWorld, HelloWorld)
END_OBJECT_MAP()

class CADsFirstExtApp : public CWinApp
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADsFirstExtApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CADsFirstExtApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


STDAPI RegisterADsExt(void);
STDAPI UnRegisterADsExt(void);

BEGIN_MESSAGE_MAP(CADsFirstExtApp, CWinApp)
	//{{AFX_MSG_MAP(CADsFirstExtApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CADsFirstExtApp theApp;

BOOL CADsFirstExtApp::InitInstance()
{
    _Module.Init(ObjectMap, m_hInstance, &LIBID_ADSFIRSTEXTLib);
    return CWinApp::InitInstance();
}

int CADsFirstExtApp::ExitInstance()
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

STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
	if ( SUCCEEDED(_Module.RegisterServer(TRUE) ) )
	{
         return RegisterADsExt();
	}
    return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	UnRegisterADsExt();
    return _Module.UnregisterServer(TRUE);
}

STDAPI RegisterADsExt(void)
{
	HRESULT hr;
	HKEY hKey;
	DWORD dwDisposition;
	

	hr = RegCreateKeyEx( HKEY_LOCAL_MACHINE,
		                 _T("SOFTWARE\\Microsoft\\ADs\\Providers\\LDAP\\Extensions\\User\\{E1E3EDF8-48D1-11D2-B22B-0000F87A6B50}"),
						 0,
						 NULL,
						 REG_OPTION_NON_VOLATILE,
						 KEY_WRITE,
						 NULL,
						 &hKey,
						 &dwDisposition );

	if ( !SUCCEEDED(hr) )
	{
		return hr;
	}
     

	///////////////////////////////////////////
	// Interface
	//////////////////////////////////////////// 
	const wchar_t szIf[] = L"{E1E3EDF7-48D1-11D2-B22B-0000F87A6B50}\0\0";


	hr = RegSetValueEx( hKey, _T("Interfaces"), 0, REG_BINARY, (const BYTE *) szIf, sizeof(szIf));
	
	RegCloseKey(hKey);

	return hr;
}


STDAPI UnRegisterADsExt(void)
{

	LONG lResult;
	lResult = RegDeleteKey(  HKEY_LOCAL_MACHINE,        
		_T("SOFTWARE\\Microsoft\\ADs\\Providers\\LDAP\\Extensions\\User\\{E1E3EDF8-48D1-11D2-B22B-0000F87A6B50}") );

	if ( lResult ==	ERROR_SUCCESS )
	{
		return S_OK;

	}

    return E_FAIL;
}