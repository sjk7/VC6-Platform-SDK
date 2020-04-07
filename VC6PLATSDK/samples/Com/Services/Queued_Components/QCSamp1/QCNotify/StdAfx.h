/*+==========================================================================
  File:      Stdafx.h
  Summary:   Standard header
  Classes:   None
-----------------------------------------------------------------------------

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

#if !defined(AFX_STDAFX_H__6DD1E6E0_28C1_11D2_B5B6_00C04FC340EE__INCLUDED_)
#define AFX_STDAFX_H__6DD1E6E0_28C1_11D2_B5B6_00C04FC340EE__INCLUDED_

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

#endif // !defined(AFX_STDAFX_H__6DD1E6E0_28C1_11D2_B5B6_00C04FC340EE__INCLUDED)
