// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1999  Microsoft Corporation.  All Rights Reserved.
//
// Module Name: lspguid.cpp
//
// Description:
//
//    This module simply defines the LSPs DLL name and the GUID 
//    under which the LSPs provider (dummy) entry is installed under.
//
//    You can generate multiple LSPs to layer over one another by
//    changing the LSPs name (e.g. lsp2.dll) and the GUID (to another
//    unique value). The lsp.def file must also be updated to indicate
//    the LSP name as well as the makefile (to output a lsp2.dll instead
//    of lsp.dll). Note that the instlsp.exe generated will only install
//    lsp2.dll so it must be kept seperate from the installer generated
//    for the original LSP.
//
#include "provider.h"
#include <windows.h>

//
// Initialize the LSP's provider path
//
WCHAR *ProviderPath = L"%SYSTEMROOT%\\system32\\lsp.dll";

//
// This is the hardcoded guid for our dummy (hidden) catalog entry
//
GUID ProviderGuid = { //c5fabbd0-9736-11d1-937f-00c04fad860d
    0xc5fabbd0,
    0x9736,
    0x11d1,
    {0x93, 0x7f, 0x00, 0xc0, 0x4f, 0xad, 0x86, 0x0d}
};
