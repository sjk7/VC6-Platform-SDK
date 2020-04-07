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

BOOL UtilAllocMem (PVOID *ppv, DWORD cb);
void UtilFreeMem (PVOID pv);
BOOL GetUserSidFromToken (HANDLE hToken, PSID *ppSid);
BOOL GetGroupSidFromToken (HANDLE hToken, PSID *ppSid);
BOOL CreateAppSecurityDescriptor(PSECURITY_DESCRIPTOR *ppsd);
BOOL FreeAppSecurityDescriptor (PSECURITY_DESCRIPTOR psd);
void ErrorMessage(HWND hwnd, LPCTSTR szFunction, HRESULT hr);

// EOF =======================================================================
