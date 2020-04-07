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

#include "stdafx.h"
/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllMain
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 

BOOL WINAPI DllMain(HMODULE hModule,DWORD dwReason,LPVOID lpReserved){
	UNREFERENCED_PARAMETER(lpReserved);
	if (dwReason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(hModule);
	};
	return TRUE;
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: GetCallObject
  Summary:  This function passes non automation compliant parameters through
			to the call factory
  Args:     The call factory and the arguments to CreateCall
  Returns:  HRESULT - the result of CreateCall
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
extern "C" __declspec(dllexport) __stdcall GetCallObject(ICallFactory* pCf,
					REFIID riid1,
					IUnknown* pUnkOuter,
					REFIID riid2,
					IUnknown** ppv ) {
	return  pCf->CreateCall(riid1,pUnkOuter,riid2,ppv);
}

/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WaitCallObject
  Summary:  Allows the VB client to call ISynchronize::Wait on the call object
  Returns:  HRESULT - the result of Wait
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/ 
extern "C" __declspec(dllexport) __stdcall WaitCallObject(ISynchronize* pSync,
							DWORD dwMilli){
    return pSync->Wait(0, dwMilli);
}
