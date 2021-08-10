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

#if !defined(AFX_STDAFX_H__501092D7_8966_11D1_B93C_00A0C9A06D2D__INCLUDED_)
#define AFX_STDAFX_H__501092D7_8966_11D1_B93C_00A0C9A06D2D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define STRICT

#include <afxwin.h>
#include <afxdisp.h>
#include "afxdlgs.h"



#define _ATL_APARTMENT_THREADED

#include <activeds.h>
#include <dsadmin.h>

#include <atlbase.h>

#if ( _ATL_VER >= 0x0300 )
#define _ATL_NO_UUIDOF 
#endif




class CMyUIExtModule : public CComModule
{
public:
	HRESULT WINAPI UpdateRegistryCLSID(const CLSID& clsid, BOOL bRegister);
};

#define DECLARE_REGISTRY_CLSID() \
static HRESULT WINAPI UpdateRegistry(BOOL bRegister) \
{ \
		return _Module.UpdateRegistryCLSID(GetObjectCLSID(), bRegister); \
}

extern CMyUIExtModule _Module;

#include <atlcom.h>

#include <activeds.h> // Active Directory Services Interfaces

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__501092D7_8966_11D1_B93C_00A0C9A06D2D__INCLUDED)
