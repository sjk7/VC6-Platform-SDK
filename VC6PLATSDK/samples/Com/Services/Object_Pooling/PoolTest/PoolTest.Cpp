/*+==========================================================================

File: PoolTest.cpp 

Summary: Implementation of WinMain

----------------------------------------------------------------------------
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

// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f PoolTestps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "PoolTest.h"
#include "testdlg.h"

CComModule _Module;

// dummy object map for ATL
BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int /*nShowCmd*/)
{
    
    HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    _ASSERTE(SUCCEEDED(hRes));

    _Module.Init(NULL, hInstance);

	// show our dialog
	CTestDlg *dlg = new CTestDlg;
	dlg->DoModal();
	delete dlg;

	CoUninitialize();

    _Module.Term();
    return 0;
}
