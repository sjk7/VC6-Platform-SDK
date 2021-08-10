/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1997 - 2000.  Microsoft Corporation.  All rights reserved

Module Name:

    helper.c

Abstract:

    This module contains helper functions used by check_sd.

    ConvertSid()            - converts a binary SID to textual form.
    DisplayError()          - displays error code and message for an
                              API failure
    Privilege()             - enables or disables a privilege.  the
                              function will first check to see if the
                              thread is impersonating, if it is the
                              privilege is enabled in the impersonation
                              token if not, the privilege is enabled in
                              the process token
    LookupAccountOtherSid() - there are certain builtin accounts on Windows NT
                              which do not have a mapped account name.
                              LookupAccountSid will return the error
                              ERROR_NONE_MAPPED.  This function generates SIDs
                              for the following accounts that are not mapped:
                              * ACCOUNT OPERATORS
                              * SYSTEM OPERATORS
                              * PRINTER OPERATORS
                              * BACKUP OPERATORS

                              the other SID it creates is a LOGON SID, it has
                              a prefix of S-1-5-5.  a LOGON SID is a unique
                              identifier for a user's logon session.

Changes:

    Change System to Server Operators in LookupAccountOtherSid 16-Aug-98

--*/

#include "check_sd.h"
#include <tchar.h>
#include <stdio.h>

BOOL ConvertSid(PSID pSid, LPTSTR pszSidText, LPDWORD dwBufferLen)
{
     DWORD                     dwSubAuthorities;
     DWORD                     dwSidRev = SID_REVISION;
     DWORD                     dwCounter;
     DWORD                     dwSidSize;
     PSID_IDENTIFIER_AUTHORITY psia;

     //
     // test if Sid passed in is valid
     //
     if(!IsValidSid(pSid))
          return FALSE;

     //
     // obtain SidIdentifierAuthority
     //
     psia = GetSidIdentifierAuthority(pSid);

     //
     // obtain sidsubauthority count
     //
     dwSubAuthorities =* GetSidSubAuthorityCount(pSid);

     //
     // compute buffer length
     // S-SID_REVISION- + identifierauthority- + subauthorities- + NULL
     //
     dwSidSize = (15 + 12 + (12 * dwSubAuthorities) + 1) * sizeof(TCHAR);

     //
     // check provided buffer length.
     // If not large enough, indicate proper size and setlasterror
     //
     if (*dwBufferLen < dwSidSize){
          *dwBufferLen = dwSidSize;
          SetLastError(ERROR_INSUFFICIENT_BUFFER);
          return FALSE;
         }

     //
     // prepare S-SID_REVISION-
     //
     dwSidSize=wsprintf(pszSidText, TEXT("S-%lu-"), dwSidRev );

     //
     // prepare SidIdentifierAuthority
     //
     if ( (psia->Value[0] != 0) || (psia->Value[1] != 0) ){
          dwSidSize += wsprintf(pszSidText + lstrlen(pszSidText),
          TEXT("0x%02hx%02hx%02hx%02hx%02hx%02hx"),
          (USHORT)psia->Value[0],
          (USHORT)psia->Value[1],
          (USHORT)psia->Value[2],
          (USHORT)psia->Value[3],
          (USHORT)psia->Value[4],
          (USHORT)psia->Value[5]);
         }
     else{
          dwSidSize += wsprintf(pszSidText + lstrlen(pszSidText),
                               TEXT("%lu"),
                               (ULONG)(psia->Value[5]      )   +
                               (ULONG)(psia->Value[4] <<  8)   +
                               (ULONG)(psia->Value[3] << 16)   +
                               (ULONG)(psia->Value[2] << 24)   );
         }

     //
     // loop through SidSubAuthorities
     //
     for (dwCounter=0 ; dwCounter < dwSubAuthorities ; dwCounter++){
          dwSidSize+=wsprintf(pszSidText + dwSidSize, TEXT("-%lu"),
               *GetSidSubAuthority(pSid, dwCounter));
         }

     return TRUE;
}

void DisplayError(DWORD dwError, LPTSTR pszAPI)
{
     LPVOID lpvMessageBuffer;

     if (!FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                   NULL, dwError,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
                   (LPTSTR)&lpvMessageBuffer, 0, NULL))
	 {
	      printf ("FormatMessage failed: 0x%x\n", GetLastError());
		  return;
	 }

     //
     //... now display this string
     //
     _tprintf(TEXT("ERROR: API        = %s.\n"), pszAPI);
     _tprintf(TEXT("       error code = %d.\n"), dwError);
     _tprintf(TEXT("       message    = %s\n"), (LPTSTR)lpvMessageBuffer);

     //
     // Free the buffer allocated by the system
     //
     if (LocalFree(lpvMessageBuffer))
		 printf ("LocalFree failed: 0x%x\n", GetLastError());

     ExitProcess(0);
}

BOOL Privilege(LPTSTR pszPrivilege, BOOL bEnable)
{
     HANDLE           hToken;
     TOKEN_PRIVILEGES tp;

     //
     // obtain the token, first check the thread and then the process
     //
     if (!OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, TRUE, &hToken)){
          if (GetLastError() == ERROR_NO_TOKEN){
               if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
                    return FALSE;
          }
          else
               return FALSE;
	 }

     //
     // get the luid for the privilege
     //
     if (!LookupPrivilegeValue(NULL, pszPrivilege, &tp.Privileges[0].Luid))
          return FALSE;

     tp.PrivilegeCount = 1;

     if (bEnable)
          tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
     else
          tp.Privileges[0].Attributes = 0;

     //
     // enable or disable the privilege
     //
     if (!AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0))
          return FALSE;

     if (!CloseHandle(hToken))
          return FALSE;

     return TRUE;
}

void LookupAccountOtherSid(PSID psidCheck, LPTSTR pszName, LPDWORD pcbName, LPTSTR pszDomain, LPDWORD pcbDomain, PSID_NAME_USE psnu)
{
     int                      i;
     PSID                     psid[UNKNOWNSIDS];
     PSID                     psidLogonSid;
     SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
     TCHAR                    szName[UNKNOWNSIDS][18] = {TEXT("ACCOUNT OPERATORS"), TEXT("SERVER OPERATORS"), TEXT("PRINTER OPERATORS"), TEXT("BACKUP OPERATORS")};

     //
     // name should be bigger than 18, builtin should be greater than 8
     //

     //
     // create account operators
     //
     if (!AllocateAndInitializeSid(&sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ACCOUNT_OPS, 0, 0, 0, 0, 0, 0, &psid[0]))
          DisplayError(GetLastError(), TEXT("AllocateAndInitializeSid"));

     //
     // create system operators
     //
     if (!AllocateAndInitializeSid(&sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_SYSTEM_OPS, 0, 0, 0, 0, 0, 0, &psid[1]))
          DisplayError(GetLastError(), TEXT("AllocateAndInitializeSid"));

     //
     // create printer operators
     //
     if (!AllocateAndInitializeSid(&sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_PRINT_OPS, 0, 0, 0, 0, 0, 0, &psid[2]))
          DisplayError(GetLastError(), TEXT("AllocateAndInitializeSid"));

     //
     // create backup operators
     //
     if (!AllocateAndInitializeSid(&sia, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_BACKUP_OPS, 0, 0, 0, 0, 0, 0, &psid[3]))
          DisplayError(GetLastError(), TEXT("AllocateAndInitializeSid"));

     //
     // create a logon SID
     //
     if (!AllocateAndInitializeSid(&sia, 2, 0x00000005, 0, 0, 0, 0, 0, 0, 0, &psidLogonSid))
          DisplayError(GetLastError(), TEXT("AllocateAndInitializeSid"));

     *psnu =  SidTypeAlias;

     for (i = 0; i < 4; i++){
          if (EqualSid(psidCheck, psid[i])){
			   if (!lstrcpy(pszName, szName[i]))
			        DisplayError(GetLastError(), TEXT("lstrcpy"));

               if (!lstrcpy(pszDomain, TEXT("BUILTIN")))
			        DisplayError(GetLastError(), TEXT("lstrcpy"));
               break;
          }
     }

     if (EqualPrefixSid(psidCheck, psidLogonSid)){
		 if (!lstrcpy(pszName, TEXT("LOGON SID")))
	          DisplayError(GetLastError(), TEXT("_tcsncpy"));
     }

     //
     // free the sids
     //
     for (i=0;i<4;i++){
          FreeSid(psid[i]);
     }

     FreeSid(psidLogonSid);
}