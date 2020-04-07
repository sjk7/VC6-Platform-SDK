// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

#include <objbase.h>

#include "Registry.h"
#include "CFactory.h"
#include "Debug.h"

extern CLSID g_clsid;
extern LPOLESTR g_progID;

CHAR_CONVERSION;


////////////////////////////////////////////////////////
//
// Internal helper functions prototypes
//

// Set the given key and its value.
BOOL setKeyAndValue(LPCTSTR szKey,
                    LPCTSTR szSubkey,
                    LPCTSTR szValue = NULL,
					LPCTSTR szName=NULL);

// Convert a CLSID into a char string.
void CLSIDtochar(const CLSID& clsid, 
                 LPTSTR szCLSID,
                 int length);

// Delete szKeyChild and all of its descendents.
LONG recursiveDeleteKey(HKEY hKeyParent, LPCTSTR szKeyChild);

////////////////////////////////////////////////////////
//
// Constants
//

// Size of a CLSID as a string
const int CLSID_STRING_SIZE = 39;

/////////////////////////////////////////////////////////
//
// Public function implementation
//

//
// Register the component in the registry.
//
HRESULT RegisterServer(HMODULE hModule,            // DLL module handle
					   CFactoryData& classData)
{

	// Get server location.
	HRESULT hr;
	char szModule[512];
	DWORD dwResult =
		::GetModuleFileName(hModule, 
		                    szModule,
		                    sizeof(szModule)/sizeof(char));

//checkcheck
	g_clsid = *classData.m_pCLSID;
	g_progID = const_cast<LPOLESTR>(classData.m_szProgID);

	_ASSERT(dwResult != 0);

	// Convert the CLSID into a char.
	char szCLSID[CLSID_STRING_SIZE];
	CLSIDtochar(*classData.m_pCLSID, szCLSID, sizeof(szCLSID));

	// Build the key CLSID\\{...}
	char szKey[64];
	strcpy(szKey, "CLSID\\");
	strcat(szKey, szCLSID);
  
	// Add the CLSID to the registry.
	setKeyAndValue(szKey, NULL, classData.m_RegistryName);

	// Add the server filename subkey under the CLSID key.
	switch (classData.server)
	{
		case REMOTE:
		// TODO: add AppID entries
		// fall through
		case LOCAL:
			setKeyAndValue(szKey, "LocalServer32", szModule);	
			break;
		case CONTROL:
			// Add "Control" key for Insert Dialog box
			setKeyAndValue(szKey, "Control");
			// fall through
		case INPROC:
			setKeyAndValue(szKey, "InprocServer32", szModule);
			// Add threading model
			setKeyAndValue(szKey, "InprocServer32", classData.threadingModel, "ThreadingModel");
			break;
	}

	// Add the ProgID subkey under the CLSID key.
	setKeyAndValue(szKey, "ProgID", W2A(classData.m_szProgID));

	// Add the version-independent ProgID subkey under CLSID key.
	setKeyAndValue(szKey, "VersionIndependentProgID",
	               W2A(classData.m_szVerIndProgID));

	// Add the GUID for the typelib
	if (classData.m_pLIBID != &CLSID_NULL)
	{
		char typelib[CLSID_STRING_SIZE];
		CLSIDtochar(*classData.m_pLIBID, typelib, sizeof(typelib));
		setKeyAndValue(szKey, "TypeLib", typelib);
		setKeyAndValue(szKey, "Programmable");
		hr = RegisterLibrary(hModule, *classData.m_pLIBID, "Student.tlb");
		if (FAILED(hr))
			return hr;
	}

	if (classData.m_fProxy)
	{
		hr = RegisterProxy(hModule);
		if (FAILED(hr))
			return hr;
	}


	// Add "attributes" designating what this object: is, can do, needs
	char buffer[80];
	HKEY hKey;
	long lResult;

	if (classData.m_oleMisc != 0)
		setKeyAndValue(szKey, "MiscStatus", itoa(classData.m_oleMisc, buffer, 10));
	
	if (classData.m_oleVerbs != 0)
	{
		strcpy(buffer, szKey);
		strcat(szKey, "\\Verb");
		lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT ,
	                              szKey, 
	                              0, NULL, REG_OPTION_NON_VOLATILE,
	                              KEY_ALL_ACCESS, NULL, 
	                              &hKey, NULL);

		if (lResult != ERROR_SUCCESS)
			OutputDebugString("Error creating verb\n");
		RegCloseKey(hKey);
		LPSTR end, begin = const_cast<char*>(classData.m_oleVerbs);
		if (begin)
			do 
			{
				signed char lVerb = *begin++;
				end = strchr(begin, '.');
				*end++ = NULL;
				char verb[5];
				itoa(lVerb, verb, 10);
				wsprintf(buffer, "%s,%c,%c",begin, *end, *(end+2));
				setKeyAndValue(szKey, verb, buffer);
				begin = end+4;
			} while (*begin);
	}

	if (classData.m_szname != 0)
	{
	// Add names to be displayed in menus, dialogs, ....
		strcpy(szKey, "CLSID\\");
		strcat(szKey, szCLSID);
		strcat(szKey, "\\AuxUserType");
		lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT ,
	                         szKey, 
	                         0, NULL, REG_OPTION_NON_VOLATILE,
	                         KEY_ALL_ACCESS, NULL, 
	                         &hKey, NULL);

		RegCloseKey(hKey);
		setKeyAndValue(szKey, "2", classData.m_szname);
		setKeyAndValue(szKey, "3", classData.m_szAppName);
	}
	// Add the version-independent ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(W2A(classData.m_szVerIndProgID), NULL, classData.m_RegistryName); 
	setKeyAndValue(W2A(classData.m_szVerIndProgID), "CLSID", szCLSID);
	setKeyAndValue(W2A(classData.m_szVerIndProgID), "CurVer", W2A(classData.m_szProgID));

	// Add the versioned ProgID subkey under HKEY_CLASSES_ROOT.
	setKeyAndValue(W2A(classData.m_szProgID), NULL, classData.m_RegistryName); 
	setKeyAndValue(W2A(classData.m_szProgID), "CLSID", szCLSID);

	return S_OK ;
}


//
// Remove the component from the registry.
//
HRESULT UnregisterServer(HMODULE hModule,            // DLL module handle
					   CFactoryData& classData)
{
	HRESULT hr;


	g_clsid = *classData.m_pCLSID;
	g_progID = const_cast<LPOLESTR>(classData.m_szProgID);

	// Convert the CLSID into a char.
	char szCLSID[CLSID_STRING_SIZE];
	CLSIDtochar(*classData.m_pCLSID, szCLSID, sizeof(szCLSID));

	// Build the key CLSID\\{...}
	char szKey[64];
	strcpy(szKey, "CLSID\\");
	strcat(szKey, szCLSID);
  
	// Delete the CLSID Key - CLSID\{...}
	LONG lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, szKey) ;
	_ASSERT((lResult == ERROR_SUCCESS) ||
	       (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

	// Delete the version-independent ProgID Key.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, W2A(classData.m_szVerIndProgID));
	_ASSERT((lResult == ERROR_SUCCESS) ||
	       (lResult == ERROR_FILE_NOT_FOUND)); // Subkey may not exist.

	// Delete the ProgID key.
	lResult = recursiveDeleteKey(HKEY_CLASSES_ROOT, W2A(classData.m_szProgID));
	_ASSERT((lResult == ERROR_SUCCESS) ||
	       (lResult == ERROR_FILE_NOT_FOUND)) ; // Subkey may not exist.

	// Delete the typelibrary
	if (classData.m_pLIBID != &CLSID_NULL)
	{
		DWORD Major = HIWORD(classData.m_LibVersion);
		DWORD Minor = LOWORD(classData.m_LibVersion);
		LCID  lcid = classData.m_lcid;
		hr = UnRegisterTypeLib( *classData.m_pLIBID, 
					HIWORD(classData.m_LibVersion), LOWORD(classData.m_LibVersion), classData.m_lcid, SYS_WIN32);
		if (FAILED(hr))
			return hr;
	}

	// Delete the ProxyStub entry for the custom interface
	if (classData.m_fProxy)
	{
		hr = UnRegisterProxy(hModule);
		if (FAILED(hr))
			return hr;
	}

	return S_OK;
}



///////////////////////////////////////////////////////////
//
// Internal helper functions
//

// Convert a CLSID to a char string.
void CLSIDtochar(const CLSID& clsid,
                 LPTSTR szCLSID,
                 int length)
{
	_ASSERT(length >= CLSID_STRING_SIZE) ;
	// Get CLSID
	LPOLESTR wszCLSID = NULL ;
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID) ;
	_ASSERT(SUCCEEDED(hr)) ;

	// Covert from wide characters to non-wide.
	wcstombs(szCLSID, wszCLSID, length) ;

	// Free memory.
	CoTaskMemFree(wszCLSID) ;
}

//
// Delete a key and all of its descendents.
//
LONG recursiveDeleteKey(HKEY hKeyParent,        // Parent of key to delete
                        LPCTSTR lpszKeyChild)	// Key to delete
{
	// Open the child.
	HKEY hKeyChild ;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0,
	                         KEY_ALL_ACCESS, &hKeyChild) ;
	if (lRes != ERROR_SUCCESS)
	{
		return lRes ;
	}

	// Enumerate all of the decendents of this child.
	FILETIME time ;
	char szBuffer[256] ;
	DWORD dwSize = 256 ;
	while (RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL,
	                    NULL, NULL, &time) == S_OK)
	{
		// Delete the decendents of this child.
		lRes = recursiveDeleteKey(hKeyChild, szBuffer) ;
		if (lRes != ERROR_SUCCESS)
		{
			// Cleanup before exiting.
			RegCloseKey(hKeyChild) ;
			return lRes;
		}
		dwSize = 256 ;
	}

	// Close the child.
	RegCloseKey(hKeyChild) ;

	// Delete this child.
	return RegDeleteKey(hKeyParent, lpszKeyChild) ;
}

//
// Create a key and set its value.
//   - This helper function was borrowed and modifed from
//     Kraig Brockschmidt's book Inside OLE.
//
BOOL setKeyAndValue(LPCTSTR szKey,
                    LPCTSTR szSubkey,
                    LPCTSTR szValue,
					LPCTSTR szName)
{
	HKEY hKey;
	char szKeyBuf[1024] ;

	// Copy keyname into buffer.
	strcpy(szKeyBuf, szKey) ;

	// Add subkey name to buffer.
	if (szSubkey != NULL)
	{
		strcat(szKeyBuf, "\\") ;
		strcat(szKeyBuf, szSubkey ) ;
	}

	// Create and open key and subkey.
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT ,
	                              szKeyBuf, 
	                              0, NULL, REG_OPTION_NON_VOLATILE,
	                              KEY_ALL_ACCESS, NULL, 
	                              &hKey, NULL) ;
	if (lResult != ERROR_SUCCESS)
	{
		return FALSE ;
	}

	// Set the Value.
	if (szValue != NULL)
	{
		RegSetValueEx(hKey, szName, 0, REG_SZ, 
		              (BYTE *)szValue, 
		              static_cast<DWORD>(strlen(szValue)+1)) ;
	}

	RegCloseKey(hKey) ;
	return TRUE ;
}


HRESULT RegisterLibrary(HMODULE hModule, // Application module handle
						const GUID& pLibIID,
						LPCSTR  szPath)
{
	HRESULT hr = E_FAIL;
	LPTYPELIB ptypeLib;
	OLECHAR FileName[MAX_PATH];
	
	if (szPath)
	{
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szPath, -1, FileName, (sizeof FileName)/(sizeof FileName[0]));
		hr = LoadTypeLibEx(FileName, REGKIND_REGISTER, &ptypeLib);
	}

/* 
 * try and load the typelibrary from the applications' resources
 */
	if (FAILED(hr))
	{
		char AppName[MAX_PATH];
		GetModuleFileName(hModule, AppName, sizeof(AppName));
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, AppName, -1, FileName, (sizeof FileName)/(sizeof FileName[0]));
		DEBUGTRACE(_T("LoadRegTypeLib failed, loading typelib from filename [%S]\n"), FileName);
		hr = LoadTypeLibEx(FileName, REGKIND_REGISTER, &ptypeLib);
/*
 * If that fails then resort to loading the typelibrary as a seperate file
 * this will only look for a typelibrary with the same name as the application
 */
		if (FAILED(hr))
		{
			LPSTR p = NULL;
			if((p = strchr(AppName, '.')) == NULL)
			{
				DEBUGTRACE(_T("Unable to append a TLB extention to app bombing out [%X]\n"), hr);
				return hr;
			}

			*p = NULL;
			strcat(AppName, ".tlb");
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, AppName, -1, FileName, (sizeof FileName)/(sizeof FileName[0]));
			DEBUGTRACE(_T("LoadRegTypeLib failed, loading typelib from filename [%S]\n"), FileName);
			hr = LoadTypeLibEx(FileName, REGKIND_REGISTER, &ptypeLib);
			if (FAILED(hr))
			{
				DEBUGTRACE(_T("LoadTypeLib failed bombing out [%X]\n"), hr);
				return hr;
			}
		}
	}
	RELEASEINTERFACE(ptypeLib);
	return hr;
}


HRESULT RegisterProxy(HMODULE hModule, // Application module handle
					  LPCSTR szPath)
{
	HRESULT hr = E_FAIL;
	HINSTANCE hLib;
	HRESULT (__stdcall *DllRegisterServer)(void);

	char FileName[MAX_PATH];
	
	if (szPath)
		hLib = LoadLibrary(szPath);
	else
	{
		GetModuleFileName(hModule, FileName, sizeof(FileName));
		LPSTR p = NULL;
		if((p = strrchr(FileName, '\\')) == NULL)
		{
				DEBUGTRACE(_T("Unable to find path to proxystub bombing out [%X]\n"), hr);
				return E_FAIL;
		}
		*p = NULL;
		strcat(FileName, "\\Proxy.Dll");
		hLib = LoadLibrary(FileName);
	}
	if (!hLib)
		return HRESULT_FROM_WIN32(GetLastError());
	DllRegisterServer = (HRESULT(__stdcall*)())GetProcAddress(hLib, "DllRegisterServer");
	if (!DllRegisterServer)
		return HRESULT_FROM_WIN32(GetLastError());

	hr = (*DllRegisterServer)();
	FreeLibrary(hLib);
	return hr;
}


HRESULT UnRegisterProxy(HMODULE hModule, // Application module handle
						LPCSTR szPath)
{
	HRESULT hr = E_FAIL;
	HINSTANCE hLib;
	HRESULT (__stdcall *DllUnregisterServer)(void);

	char FileName[MAX_PATH];
	
	if (szPath)
		hLib = LoadLibrary(szPath);
	else
	{
		GetModuleFileName(hModule, FileName, sizeof(FileName));
		LPSTR p = NULL;
		if((p = strrchr(FileName, '\\')) == NULL)
		{
				DEBUGTRACE(_T("Unable to find path to proxystub bombing out [%X]\n"), hr);
				return E_FAIL;
		}
		*p = NULL;
		strcat(FileName, "\\Proxy.Dll");
		hLib = LoadLibrary(FileName);
	}
	if (!hLib)
		return HRESULT_FROM_WIN32(GetLastError());
	DllUnregisterServer = (HRESULT(__stdcall*)())GetProcAddress(hLib, "DllUnregisterServer");
	if (!DllUnregisterServer)
		return HRESULT_FROM_WIN32(GetLastError());

	hr = (*DllUnregisterServer)();
	FreeLibrary(hLib);
	return hr;
}
