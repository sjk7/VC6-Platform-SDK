// Filename: stdafx.h
//
// Description: include file for standard system include files,
//				or project specific include files that are used frequently,
//				but are changed infrequently
//
// This file is provided as part of the Microsoft Transaction Server
// Software Development Kit
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT 
// WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES 
// OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR 
// PURPOSE.
//
// Copyright (C) 1997 Microsoft Corporation, All rights reserved

#if 0
#if defined(_ATL_NO_DEBUG_CRT)
#include <svcerr.h>
#define _ASSERTE(x) ASSERT(x)
#endif // defined(_ATL_NO_DEBUG_CRT)
#endif


#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#ifndef DBNTWIN32
#define DBNTWIN32
#include <SQL.h>
#include <SQLEXT.h>
#endif
#define THROW_ERR(exp,str) {if (FAILED (hr = (exp))) {lErrFlag = 0; pErrMsg = _T(str); throw hr;}}
#define THROW_STR(str) { hr = APP_ERROR; lErrFlag = 1; pErrMsg = str; throw hr;}
#define RETHROW_ERR(exp) { if (FAILED(hr = (exp))) {lErrFlag = 2; throw hr;}}

#define APP_ERROR 0x80004100

extern void GetError(HENV henv, HDBC hdbc, HSTMT hstmt, BSTR * sErr);

#define SafeRelease(x) { if (x){x->Release();x=NULL;}}


#define SQL_FAILED(rc)  ( (rc) != SQL_SUCCESS && (rc) != SQL_SUCCESS_WITH_INFO)



#define ASSERT_SQL_SUCCESS(rc) { _ASSERTE(rc==SQL_SUCCESS || rc==SQL_SUCCESS_WITH_INFO);}

