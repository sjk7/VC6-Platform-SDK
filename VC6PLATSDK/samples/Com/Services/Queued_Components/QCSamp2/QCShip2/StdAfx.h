// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__6DD1E6D3_28C1_11D2_B5B6_00C04FC340EE__INCLUDED_)
#define AFX_STDAFX_H__6DD1E6D3_28C1_11D2_B5B6_00C04FC340EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT


#define _WIN32_WINNT 0x0500
#define _ATL_APARTMENT_THREADED


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#include <crtdbg.h>
#include <comsvcs.h>
#include <stdlib.h>
#include <vector>
#include <comdef.h>

#endif // !defined(AFX_STDAFX_H__6DD1E6D3_28C1_11D2_B5B6_00C04FC340EE__INCLUDED)
