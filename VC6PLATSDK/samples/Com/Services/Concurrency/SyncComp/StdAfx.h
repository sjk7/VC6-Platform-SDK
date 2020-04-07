// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__247FF7E1_F38D_11D2_A10A_0080C71F306F__INCLUDED_)
#define AFX_STDAFX_H__247FF7E1_F38D_11D2_A10A_0080C71F306F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <atlbase.h>
extern CComModule				_Module;
extern IGlobalInterfaceTable*   g_pGIT;

#include <atlcom.h>
#include <atlwin.h>
#include <stdio.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__247FF7E1_F38D_11D2_A10A_0080C71F306F__INCLUDED)
