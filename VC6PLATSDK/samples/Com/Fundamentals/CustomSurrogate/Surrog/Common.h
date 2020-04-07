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

#ifndef _WIN32_WINNT
#define _WIN32_WINNT  0x0402
#endif

#include <windows.h>
#include <assert.h>

#define MAX_GUIDSTR_LEN 40

const CHAR szClsidKeyName[] = "CLSID";
const CHAR szAppidValueName[] = "AppID";

#ifndef __ISurrogate_INTERFACE_DEFINED__
#error "You need SP2-Compliant SDK headers to compile this file."
#endif

