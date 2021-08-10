/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1997 - 2000.  Microsoft Corporation.  All rights reserved

Module Name:

    check_sd.h

Abstract:

    This module contains the declarations for the functions used in the check_sd
    sample.  The declarations are grouped based on the modules they are located in.

--*/

#ifndef _CHECKSD_
#define _CHECKSD_

#define STRICT

//
// undefine this if you want to build for UNICODE
//
//#define UNICODE
//#define _UNICODE

#include <windows.h>

//
// access for network shares.  these are based on the values set by
// explorer
//
#define READ        0x000001BF
#define CHANGE      0x000000A9
#define WRITE       0x00000040

//
// helper definitions, helper.c
//
#define UNKNOWNSIDS 4

//
// helper functions, helper.c
//
BOOL ConvertSid(PSID pSid, LPTSTR pszSidText, LPDWORD dwBufferLen);
void DisplayError(DWORD dwError, LPTSTR pszAPI);
BOOL Privilege(LPTSTR pszPrivilege, BOOL bEnable);
void LookupAccountOtherSid(PSID psidCheck, LPTSTR pszName, LPDWORD pcbName, LPTSTR pszDomain, LPDWORD pcbDomain, PSID_NAME_USE psnu);

//
// functions for obtaining information from a security descriptor, sd.c
//
DWORD DumpAclInfo(PACL pacl, BOOL bDacl);
void  DumpControl(PSECURITY_DESCRIPTOR psd);
void  DumpDacl(PSECURITY_DESCRIPTOR psd, TCHAR c, BOOL bDacl);
void  DumpOwnerGroup(PSECURITY_DESCRIPTOR psd, BOOL bOwner);
void  DumpSD(PSECURITY_DESCRIPTOR psd, TCHAR c);
void  DumpSDInfo(PSECURITY_DESCRIPTOR psd);

//
// functions for obtaining a security descriptor for a variety of securable objects,
// secobjects.c
//
void DumpFile(LPTSTR pszFile, TCHAR c);
void DumpKernelObject(LPTSTR pszObject, TCHAR c);
void DumpNetShare(LPTSTR pszShare);
void DumpPrinter(LPTSTR pszPrinter);
void DumpRegistryKey(LPTSTR pszKey);
void DumpService(LPTSTR pszServer, LPTSTR pszService);
void DumpUserObject(LPTSTR pszObject, TCHAR c);

#endif // _CHECKSD_
