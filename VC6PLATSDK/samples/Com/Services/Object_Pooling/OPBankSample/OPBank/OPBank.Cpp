/*+==========================================================================
  File:      OPBank.cpp
  Summary:   Implementation of WinMain
-----------------------------------------------------------------------------

This file is part of the Microsoft COM+ Samples.

Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation. See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

==========================================================================+*/


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f OPBankps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "OPBank.h"


#ifndef DBNTWIN32
#define DBNTWIN32
#include <SQL.h>
#include <SQLEXT.h>
#endif

#include "bankdlg.h"
extern HACCEL g_hAccel;

BOOL g_bUnattended = FALSE;
WCHAR  * g_szLogFile = NULL;


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Function: CExeModule::Unlock()
  Summary:  This is an EXE server, so override ATL's default Unlock
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LONG CExeModule::Unlock()
{
	LONG l = CComModule::Unlock();
	if (l == 0)
	{
#if _WIN32_WINNT >= 0x0400
		if (CoSuspendClassObjects() == S_OK)
			PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
#else
		PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
#endif
	}
	return l;
}

CExeModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: FindOneOf
  Summary:  return string if match found
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: _tWinMain
  Summary:  WinMain -- main windows entry point
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
	HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
	lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	HRESULT hRes = CoInitialize(NULL);
//  If you are running on NT 4.0 or higher you can use the following call
//	instead to make the EXE free threaded.
//  This means that calls come in on a random RPC thread
//	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	_ASSERTE(SUCCEEDED(hRes));
	_Module.Init(ObjectMap, hInstance);
	_Module.dwThreadID = GetCurrentThreadId();
	TCHAR szTokens[] = _T("-/");

	int nRet = 0;
	BOOL bRun = TRUE;
	LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_OPBank, FALSE);
			nRet = _Module.UnregisterServer();
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_OPBank, TRUE);
			nRet = _Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}	

		lpszToken = FindOneOf(lpszToken, szTokens);
	}

	TCHAR * p = lpCmdLine;

	while (*p != '-' && *p)
		p++;

	while (*p)
	{

		switch (*p)
		{

			case 'u':
			case 'U':
				g_bUnattended = TRUE;
				if (!g_szLogFile)
				{
					g_szLogFile = new WCHAR[64];
					lstrcpy(g_szLogFile, L"C:\\vcbank.log");
				}
				break;
			case 'f':
			case 'F':
				{
				
					if (g_szLogFile)
					{
						delete [] g_szLogFile;
						g_szLogFile = NULL;
					}
					p+=2; // skip "f:" or "f "
					TCHAR * q = p;
					while (*q  && *q != ' ')
						q++;

					int nChars =  q-p+1;
					g_szLogFile = new WCHAR[nChars];
					_ASSERTE(p!= NULL);
					lstrcpyn(g_szLogFile, p, nChars);			
					p = q;
				}
				break;
			default:
				break;
		}
		
		p++;
	}

	if (bRun)
	{
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
			REGCLS_MULTIPLEUSE);
		_ASSERTE(SUCCEEDED(hRes));

		CBankDlg dlg;
		HWND hWnd = dlg.Create(NULL);
		if (hWnd)
		{
			g_hAccel = LoadAccelerators(_Module.m_hInst, MAKEINTRESOURCE(IDR_ACCELERATORS));
			_ASSERTE(g_hAccel);
			ShowWindow(hWnd, SW_SHOWNORMAL);
			MSG msg;
			while (GetMessage(&msg, 0, 0, 0))
			{
				if (!TranslateAccelerator(hWnd, g_hAccel, &msg))
				{
					if (!IsDialogMessage(hWnd, &msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}					
							
			}
		}
		else
		{
			MessageBox(NULL, L"Unable to load dialog!", L"C Bank", MB_ICONSTOP);
		}
		_Module.RevokeClassObjects();
	}

	if (g_szLogFile)
		delete [] g_szLogFile;

	CoUninitialize();
	return nRet;
}