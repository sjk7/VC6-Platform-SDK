// Filename: stdafx.h
//
// Description: Include file for standard system include files,
//				or project specific include files that are used frequently,
//				but are changed infrequently
//
// This file is provided as part of the Microsoft Transaction Server Samples
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 - 2000 Microsoft Corporation, All rights reserved

#define _ATL_STATIC_REGISTRY

#if !defined(AFX_STDAFX_H__AA22C995_FD72_11D0_B5DC_00C04FB957D8__INCLUDED_)
#define AFX_STDAFX_H__AA22C995_FD72_11D0_B5DC_00C04FB957D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#if !defined(_WIN32_WINNT)
#define _WIN32_WINNT 0x0500
#endif // !defined(_WIN32_WINNT)

#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>


#define THROW_ERR(exp) if (FAILED (hr = (exp))) throw hr

inline BSTR TCHAR2BSTR (TCHAR* szBuf) {

	WCHAR* wszBuf;

#ifndef UNICODE
	wszBuf = new WCHAR [512];
	MultiByteToWideChar( CP_ACP, 0, szBuf, -1, wszBuf, 512 );
#else
	wszBuf = szBuf;
#endif
	
	BSTR bstrNew = ::SysAllocString (wszBuf);

#ifndef UNICODE
	delete [] wszBuf;
#endif

	return bstrNew;
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AA22C995_FD72_11D0_B5DC_00C04FB957D8__INCLUDED)

