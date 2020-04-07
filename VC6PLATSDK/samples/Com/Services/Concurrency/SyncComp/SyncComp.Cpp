/*+==========================================================================

File: SyncComp.cpp

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

#include "stdafx.h"
#include "resource.h"
#include "main.h"

CComModule _Module;

// a global intereface for getting our COM object between threads
IGlobalInterfaceTable*      g_pGIT;
   
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

	// get the GIT
	hRes = CoCreateInstance(CLSID_StdGlobalInterfaceTable,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            IID_IGlobalInterfaceTable,
                            (void **)&g_pGIT);
    _ASSERTE(SUCCEEDED(hRes));

	// show our dialog
	CMain dlg;
	dlg.DoModal();

	// we are done with the GIT
	g_pGIT->Release();

	CoUninitialize();

    _Module.Term();
    return 0;
}
