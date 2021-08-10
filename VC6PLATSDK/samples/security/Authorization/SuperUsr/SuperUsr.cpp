/*
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998 - 2002.  Microsoft Corporation.  All rights reserved.


This code sample requires the following import library:
    advapi32.lib
*/

#define UNICODE
#define _UNICODE
#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <aclapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <strsafe.h> // for proper buffer handling

#define MAX_PID_DIGITS 6

#define CheckAndLocalFree(ptr) \
            if (ptr != NULL) \
            { \
               LocalFree(ptr); \
               ptr = NULL; \
            }

BOOL EnableDebugPriv(void);
BOOL ModifySecurity(HANDLE hToken, DWORD dwAccess, PSECURITY_DESCRIPTOR *pOldSD);
BOOL ResetSecurity(HANDLE hToken, PSECURITY_DESCRIPTOR pSid);
void __cdecl MyPrintf(LPCTSTR lpszFormat, ...);
BOOL BuildAdministratorsExplicitAccess(EXPLICIT_ACCESS *pExplicitAccess, DWORD dwAccess);

void _tmain(int argc, TCHAR *argv[])
{
   HANDLE hProc = NULL;
   HANDLE hToken = NULL;
   HANDLE hOldToken = NULL;
   TCHAR szCmdExe[] = { _T("cmd.exe") } ;
   PROCESS_INFORMATION pi = { NULL, NULL, 0, 0 };
   PSECURITY_DESCRIPTOR pOldSD = NULL;
   STARTUPINFO si;
   DWORD SystemPID;
   BOOL fResult;
   CHAR szPID[MAX_PID_DIGITS];
   DWORD dwPID;
   HRESULT hr;
   int n;

   if (argc != 2)
   {
      MyPrintf(_T("Usage: SuperUsr <System PID>\n"));
      return;
   }

   __try
   {  
      hr = StringCchLength(argv[1], MAX_PID_DIGITS, (size_t *)&dwPID);
      if (FAILED(hr))
      {
         MyPrintf(_T("StringCbLength failed with %X\n"), hr);
         __leave;
      }

#ifdef UNICODE
      n = WideCharToMultiByte(0, 0, argv[1], -1, szPID, dwPID + 1, NULL, NULL);
      if (n == 0)
      {
         MyPrintf(_T("WideCharToMultiByte failed with %d\n"), GetLastError());
         __leave;
      }
#else
      hr = StringCchCopy(szPID, dwPID + 1, argv[1]);
      if (FAILED(hr))
      {
         MyPrintf(_T("StringCchCopy failed with %X\n"), hr);
         __leave;
      }
#endif

      SystemPID = (DWORD)atoi(szPID);

      fResult = EnableDebugPriv();
      if(!fResult)
      {
         MyPrintf(_T("You probably don't have the SE_DEBUG_NAME privilege.\n"));
         MyPrintf(_T("You are probably not a member of the administrator group.\n"));
         __leave;
      }

      hProc = OpenProcess(PROCESS_ALL_ACCESS,
                          FALSE,
                          SystemPID);
      if (!hProc)     
      {
         MyPrintf(_T("OpenProcess failed with %d.\n"), GetLastError());
         __leave;
      }

      //
      // Open the process token with this access
      // so that we can modify the DACL and add
      // TOKEN_DUPLICATE & TOKEN_ASSIGN_PRIMARY
      // rights for this user
      //
      fResult = OpenProcessToken(hProc,
                                 READ_CONTROL|WRITE_DAC,
                                 &hOldToken);
      if (!fResult)
      {
         MyPrintf(_T("OpenProcessToken failed with %d.\n"), GetLastError());
         __leave;
      }
      
      fResult = ModifySecurity(hOldToken,
                               TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_QUERY,
                               &pOldSD);
      if (!fResult)
      {
         __leave;
      }
            
      fResult = OpenProcessToken(hProc,
                                 TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_QUERY,
                                 &hToken);
      if (!fResult)
      {
         MyPrintf(_T("OpenProcessToken failed with %d.\n"), GetLastError());
         __leave;
      }

      // Reset the security to the old permissions
      // We still retain the modified permissions
      // because we haven't closed the handle
      ResetSecurity(hOldToken, pOldSD);

      //
      // setup STARTUPINFO structure
      //
      ZeroMemory(&si, sizeof(STARTUPINFO));
      si.cb = sizeof(STARTUPINFO);

      //
      // winsta0\default is the interactive user's 
      // desktop.  Setting lpDesktop to winsta0\default
      // tells CreateProcessAsUser to launch 
      // cmd.exe in the interactive user's desktop.
      //
      si.lpDesktop = _T("winsta0\\default");

      fResult = CreateProcessAsUser(hToken,
                                    NULL,
                                    szCmdExe,
                                    NULL, // default process attributes
                                    NULL, // default thread attributes
                                    FALSE, // don't inherit handles
                                    CREATE_NEW_CONSOLE,
                                    NULL,  // inherit environment
                                    NULL,  // same directory
                                    &si,
                                    &pi );
      if (!fResult)
      {
         MyPrintf(_T("CreateProcessAsUser failed with %d.\n"), GetLastError());
      }
      else
      {
         MyPrintf(_T("\"SuperUsr\" mode console started!\n"));
      }
   }
   __finally
   {
      // Cleanup
      if (pi.hThread != NULL) CloseHandle(pi.hThread);
      if (pi.hProcess != NULL) CloseHandle(pi.hProcess);    
      if (hProc != NULL) CloseHandle(hProc);
      if (hToken != NULL) CloseHandle(hToken);      
      if (hOldToken != NULL) CloseHandle(hOldToken);
      CheckAndLocalFree(pOldSD);
   }
}

BOOL EnableDebugPriv(void)
{
   TOKEN_PRIVILEGES tp;
   HANDLE hToken = NULL;   
   BOOL fReturn = FALSE;
   BOOL fResult;
   LUID luid;

   __try
   {
      fResult = OpenProcessToken(GetCurrentProcess(),
                                 TOKEN_ADJUST_PRIVILEGES,
                                 &hToken);
      if (!fResult)
      {
         MyPrintf(_T("OpenProcessToken failed with %d.\n"), GetLastError());
         __leave;
      }

      // Lookup Debug Privilege Luid
      fResult = LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);
      if (!fResult)
      {
         MyPrintf(_T("LookupPrivilegeValue failed with %d.\n"), GetLastError());
         __leave;
      }

      tp.PrivilegeCount           = 1;
      tp.Privileges[0].Luid       = luid;
      tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // Enable privilege
      fResult = AdjustTokenPrivileges(hToken,
                                      FALSE,
                                      &tp,
                                      sizeof(TOKEN_PRIVILEGES),
                                      NULL,
                                      NULL);
      if (!fResult || GetLastError() != ERROR_SUCCESS)
      {
         MyPrintf(_T("AdjustTokenPrivileges failed with %d.\n"), GetLastError());         
         __leave;
      }

      fReturn = TRUE;
   }
   __finally
   {
      // Cleanup
      if (hToken != NULL) CloseHandle(hToken);
   }

   return(fReturn);
}

BOOL ModifySecurity(HANDLE hToken, DWORD dwAccess, PSECURITY_DESCRIPTOR *pOldSD)
{
   PSECURITY_DESCRIPTOR pSD = NULL;
   PSECURITY_DESCRIPTOR pAbsSD = NULL; 
   PACL pNewAcl = NULL;
   DWORD dwAclSize = 0, dwSaclSize = 0;
   DWORD dwSidOwnLen = 0, dwSidPrimLen = 0;
   DWORD dwSDLength = 0;
   DWORD dwSDLengthNeeded;
   EXPLICIT_ACCESS explicitaccess;   
   DWORD dwResult;
   PACL pAcl;   
   PACL pacl;   
   BOOL fDaclPresent,fDaclDefaulted;
   BOOL fResult;
   BOOL fReturn = FALSE;

   __try
   {
      explicitaccess.Trustee.ptstrName = NULL;

      // Get size of security descriptor
      fResult = GetKernelObjectSecurity(hToken,
                                        DACL_SECURITY_INFORMATION,
                                        NULL,
                                        0,
                                        &dwSDLengthNeeded);
      if (!fResult)
      {
         if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
         {
            // Allocate memory for security descriptor
            pSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSDLengthNeeded);
            if (!pSD)
            {
               MyPrintf(_T("Unable to allocate memory for security descriptor.\n"));
               __leave;
            }

            *pOldSD = pSD;

            // Get Security Descriptor from token
            fResult = GetKernelObjectSecurity(hToken,
                                        DACL_SECURITY_INFORMATION,
                                        pSD,
                                        dwSDLengthNeeded,
                                        &dwSDLengthNeeded);
            if (!fResult)
            {
               MyPrintf(_T("GetKernelObjectSecurity failed with %d.\n"), GetLastError());
               __leave;
            }            
         }
         else
         {
            MyPrintf(_T("GetKernelObjectSecurity failed with %d.\n"), GetLastError());
            __leave;
         }
      }

      // Get pointer to the DACL
      fResult = GetSecurityDescriptorDacl(pSD,
                                          &fDaclPresent,
                                          &pAcl,
                                          &fDaclDefaulted);
      if (!fResult)
      {
         MyPrintf(_T("GetSecurityDescriptorDacl failed with %d.\n"), GetLastError());
         __leave;
      }
      
      // Build Administrators EXPLICIT_ACCESS Structure
      fResult = BuildAdministratorsExplicitAccess(&explicitaccess, dwAccess);
      if (!fResult)
      {
         __leave;
      }
      
      // Add the entry to the ACL
      dwResult = SetEntriesInAcl(1,
                                 &explicitaccess,
                                 pAcl,
                                 &pNewAcl);
      if (dwResult != ERROR_SUCCESS)
      {
         MyPrintf(_T("SetEntriesInAcl failed with %d.\n"), GetLastError());
         __leave;
      }
      
      // Get Sizes for Absolute Security Descriptor
      // We only need dwSDLength and dwAclSize.
      // The SACL, SID owner, and SID primary group
      // are not present.
      fResult = MakeAbsoluteSD(pSD, 
                               NULL, 
                               &dwSDLength,
                               NULL, 
                               &dwAclSize,
                               NULL, 
                               &dwSaclSize,
                               NULL, 
                               &dwSidOwnLen,
                               NULL, 
                               &dwSidPrimLen);
      if (!fResult)
      {
         if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
         {
            // Allocate memory for absolute Security Descriptor
            pAbsSD = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR, dwSDLength);
            if (!pAbsSD)
            {
               MyPrintf(_T("Unable to allocate memory for Absolute SID.\n"));
               __leave;
            }

            // Allocate memory for DACL
            pacl = (PACL)LocalAlloc(LPTR, dwAclSize);
            if (!pacl)
            {
               MyPrintf(_T("Unable to allocate memory for DACL.\n"));
               __leave;
            }
         }
         else
         {
            MyPrintf(_T("MakeAbsoluteSD failed with %d.\n"), GetLastError());
            __leave;
         }
      }

      // Create absolute Security Descriptor
      fResult = MakeAbsoluteSD(pSD, 
                               pAbsSD, 
                               &dwSDLength,
                               pacl, 
                               &dwAclSize,
                               NULL, 
                               &dwSaclSize,
                               NULL, 
                               &dwSidOwnLen,
                               NULL, 
                               &dwSidPrimLen);
      if (!fResult)
      {
         MyPrintf(_T("MakeAbsoluteSD failed with %d.\n"), GetLastError());
         __leave;
      }

      // Add the new DACL to the SD
      fResult = SetSecurityDescriptorDacl(pAbsSD,
                                          fDaclPresent,
                                          pNewAcl,
                                          fDaclDefaulted);
      if (!fResult)
      {
         MyPrintf(_T("SetSecurityDescriptorDacl failed with %d.\n"), GetLastError());
         __leave;
      }

      // Add the new SD to the token
      fResult = SetKernelObjectSecurity(hToken,
                                        DACL_SECURITY_INFORMATION,
                                        pAbsSD);
      if (!fResult)
      {
         MyPrintf(_T("SetKernelObjectSecurity failed with %d.\n"), GetLastError());
         __leave;
      }

      fReturn = TRUE;
   }
   __finally
   {
      // Cleanup
      if (explicitaccess.Trustee.ptstrName != NULL) 
      {
         FreeSid(explicitaccess.Trustee.ptstrName);
      }     
      CheckAndLocalFree(pAbsSD);
      CheckAndLocalFree(pacl);
      CheckAndLocalFree(pNewAcl);
      if (!fReturn)
      {
         CheckAndLocalFree(pSD);
         *pOldSD = NULL;
      }
   }

   return fReturn;
}

BOOL BuildAdministratorsExplicitAccess(EXPLICIT_ACCESS *pExplicitAccess, DWORD dwAccess)
{
   SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY; 
   PSID pSid = NULL;   
   BOOL fResult;

   // Create "Administrators" SID
   fResult = AllocateAndInitializeSid(&SystemSidAuthority, 
                                       2, 
                                       SECURITY_BUILTIN_DOMAIN_RID, 
                                       DOMAIN_ALIAS_RID_ADMINS,
                                       0, 
                                       0, 
                                       0, 
                                       0, 
                                       0, 
                                       0, 
                                       &pSid);
   if (!fResult)
   {
      MyPrintf(_T("AllocateAndInitializeSid failed with %d.\n"), GetLastError());
      return FALSE;
   }

   pExplicitAccess->grfAccessMode = GRANT_ACCESS;
   pExplicitAccess->grfAccessPermissions = dwAccess;
   pExplicitAccess->grfInheritance = 0;
   
   // Build the Trustee with the SID
   BuildTrusteeWithSid(&(pExplicitAccess->Trustee), pSid);

   return TRUE;   
}

void __cdecl MyPrintf(LPCTSTR lpszFormat, ...)
{
   TCHAR szOutput[2048];
   va_list v1 = NULL;
   HRESULT hr = S_OK;

   va_start(v1, lpszFormat);
   hr = StringCbVPrintf(szOutput, sizeof(szOutput), lpszFormat, v1);
   if (SUCCEEDED(hr))
   {
      OutputDebugString(szOutput);
      _tprintf(szOutput);
   }
   else
   {
      _tprintf(_T("StringCbVPrintf failed with %X\n"), hr);
   }
}

BOOL ResetSecurity(HANDLE hToken, PSECURITY_DESCRIPTOR pSD)
{   
   BOOL fResult;

   // Add the new SD to the token
   fResult = SetKernelObjectSecurity(hToken,
                                     DACL_SECURITY_INFORMATION,
                                     pSD);
   if (!fResult)
   {
      MyPrintf(_T("SetKernelObjectSecurity failed with %d.\n"), GetLastError());
      return FALSE;
   }

   return TRUE;
}