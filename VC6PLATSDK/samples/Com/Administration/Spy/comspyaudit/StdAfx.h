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
#if !defined(AFX_STDAFX_H__AFCF0619_1429_11D1_B1B8_00AA00BA3258__INCLUDED_)
#define AFX_STDAFX_H__AFCF0619_1429_11D1_B1B8_00AA00BA3258__INCLUDED_

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

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__AFCF0619_1429_11D1_B1B8_00AA00BA3258__INCLUDED)
