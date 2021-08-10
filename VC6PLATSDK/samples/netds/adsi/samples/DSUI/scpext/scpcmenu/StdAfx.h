//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 2000
//
//  File:       StdAfx.h
//
//--------------------------------------------------------------------------

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__2448D9F3_1829_11D2_97B7_00A0C9A06D2D__INCLUDED_)
#define AFX_STDAFX_H__2448D9F3_1829_11D2_97B7_00A0C9A06D2D__INCLUDED_



#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>
#include "afxdlgs.h"



#define _ATL_APARTMENT_THREADED

#include <xstring>
#include <vector>
#include <list>

using namespace std;


#include <activeds.h>
#include <dsadmin.h>

#include <atlbase.h>

#if ( _ATL_VER >= 0x0300 )
#define _ATL_NO_UUIDOF 
#endif



using namespace ATL;

class CSCPContextMenuModule : public CComModule
{
public:
	HRESULT WINAPI UpdateRegistryCLSID(const CLSID& clsid, BOOL bRegister);
};

#define DECLARE_REGISTRY_CLSID() \
static HRESULT WINAPI UpdateRegistry(BOOL bRegister) \
{ \
		return _Module.UpdateRegistryCLSID(GetObjectCLSID(), bRegister); \
}

extern CSCPContextMenuModule _Module;

#include <atlcom.h>

#include <shellapi.h>
#include <dlgs.h>

#if ( _ATL_VER >= 0x0300 )
  #include <atlwin.h>
#else
  #include <atlwin21.h>
  #include <atldlgs.h>
#endif


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2448D9F3_1829_11D2_97B7_00A0C9A06D2D__INCLUDED)
