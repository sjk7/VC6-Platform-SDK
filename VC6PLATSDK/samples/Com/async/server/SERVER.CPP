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
#include "CFactory.h"
#include "DCOMServer.h"
///////////////////////////////////////////////////////////
//
// Server.cpp
//
// This file contains the component server code.
// The FactoryDataArray contains the components that 
// can be served.
//

// Each component derived from CUnknown defines a static function
// for creating the component with the following prototype. 
// HRESULT CreateInstance(IUnknown* pUnknownOuter, 
//                        CUnknown** ppNewComponent) ;
// This function is used to create the component.
//

//
// The following array contains the data used by CFactory
// to create components. Each element in the array contains
// the CLSID, the pointer to the creation function, and the name
// of the component to place in the Registry.
//


#define _OLEIVERB_PRIMARY		0
#define _OLEIVERB_SHOW			FF	
#define _OLEIVERB_OPEN			FE
#define _OLEIVERB_HIDE			FD
#define _OLEIVERB_PROPERTIES	F9
// MACRO's used to combine and extract the OLE verb and name

#define MAKEINTS1(s) #s
#define MAKEINTS2(iVerb) MAKEINTS1(\x ## iVerb)
#define MAKEINTVERB(iVerb, lpstrName) MAKEINTS2(iVerb) lpstrName
#define MAKEINTI(i) i

#define MAKEVERSION(M, m) ((DWORD)(WORD)(m) | (DWORD)(WORD)(M) << 16) // M=Major, m=minor

#if defined(_EVENTSINK_)
#pragma message("Build for asynchronous Event sinks")
#endif

CFactoryData g_FactoryDataArray[] =
{
	{	
		MAKEVERSION(1, 0),						// Version of CFactoryData
		LOCAL,									// Type of COM server
		NULL,									// Threading model
		&CLSID_AsyncTest,						// CLSID for object
		CServer::CreateInstance,				// Helper function for ICF::CreateInstance()
		"Async COM - Work in Progress",			// Friendly Name
		L"ASYNC_SVR.1",							// ProgID
		L"ASYNC_SVR",							// Version-independent ProgID
		NULL,									// Short User type
		NULL,									// Appliction name			
#if defined(_EVENTSINK_)
		&LIBID_Async_Lib,						// TypeLibrary
		MAKELCID(								// LCID of typelib
			MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT),
		MAKEVERSION(1, 0),						// Version of typelib
#else
		&CLSID_NULL,							// TypeLibrary
		0,										// LCID of typelib
		0,										// Version of typelib
#endif
		true,									// True for custom interface
		0,										// Verbs
		0										// MISC	bits
	}

} ;

int g_cFactoryDataEntries
	= sizeof(g_FactoryDataArray) / sizeof(CFactoryData) ;

