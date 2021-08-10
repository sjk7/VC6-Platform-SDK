/*---------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998 - 2000.  Microsoft Corporation.  All rights reserved.

logonnp.cpp
---------------------------------------------------------------*/


#define UNICODE
#define _UNICODE

#include <windows.h>
#include "npapi.h"
#include "npaux.h"

#ifdef DEBUG
BOOL WriteLogFile(LPTSTR String);
#endif

//
// The authentication type is only used here in a Unicode context
//
#define MSV1_0_AUTH_TYPE    L"MSV1_0:Interactive"

#ifdef DEBUG
// Change this define to a legal location
#define LOGFILE         TEXT("d:\\logonnp.log")
#endif

BOOL
WINAPI
DllMain(
       HANDLE hInst,
       DWORD dwReason,
       LPVOID lpReserved
       )
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {
      DisableThreadLibraryCalls(hInst);
   }

   return TRUE;
}


/****************************************************************************
   FUNCTION: NPGetCaps

   PURPOSE:  This entry point is called to query the provider.  The parameter
             is an index representing the query.  For a credential manager
             only the following index values apply:

             WNNC_SPEC_VERSION - What version of the provider specification
                was used in developing this provider?  The return value is
                the version number.

             WNNC_DRIVER_VERSION - The version of the provider.

             WNNC_START - Will the provider start? When? The return values
                are:

                    - 0 : Only return this if the provider will *not* start.
                    - Estimated Start time in milliseconds : This is how
                        long the provider is expected to take to start.
                    - 0xFFFFFFFF : Time to start is unknown.
                    - 1 : Provider is already started.

             A return value of 0 in other cases indicates that the query
             is not supported.

*******************************************************************************/
DWORD
WINAPI
NPGetCaps(
         DWORD nIndex
         )
{
   DWORD dwRes;

   switch (nIndex)
   {

   case WNNC_NET_TYPE:
      dwRes = WNNC_CRED_MANAGER; // credential manager
      break;

   case WNNC_SPEC_VERSION:
      dwRes = WNNC_SPEC_VERSION51;  // We are using version 5.1 of the spec.
      break;

   case WNNC_DRIVER_VERSION:
      dwRes = 1;  // This driver is version 1.
      break;

   case WNNC_START:
      dwRes = 1;  // We are already "started"
      break;

   default:
      dwRes = 0;  // We don't support anything else
      break;
   }

   return dwRes;

}


/****************************************************************************
   FUNCTION: NPLogonNotify

   PURPOSE:  This entry point is called when a user logs on.  If the user
             authentication fails here, the user will still be logged on
             to the local machine.

*******************************************************************************/
DWORD
WINAPI
NPLogonNotify (
              PLUID               lpLogonId,
              LPCWSTR             lpAuthentInfoType,
              LPVOID              lpAuthentInfo,
              LPCWSTR             lpPreviousAuthentInfoType,
              LPVOID              lpPreviousAuthentInfo,
              LPWSTR              lpStationName,
              LPVOID              StationHandle,
              LPWSTR              *lpLogonScript
              )
{
   PMSV1_0_INTERACTIVE_LOGON pAuthInfo;

   #ifdef DEBUG
   TCHAR szBuf[1024];

   // For debugging purposes only
   MessageBeep(0xFFFFFFFF);

   //
   // Write out some information about the logon attempt
   //
   wsprintf(szBuf, L"lpAuthentInfoType=%s lpStationName=%s\r\n",
            lpAuthentInfoType, lpStationName);

   WriteLogFile(szBuf);
   #endif


   //
   // If the primary authenticator is not MSV1_0, return success.
   // Why? Because this is the only auth info structure that we
   // understand and we don't want to interact with other types.
   //
   if ( lstrcmpiW (MSV1_0_AUTH_TYPE, lpAuthentInfoType) )
   {

      #ifdef DEBUG
      wsprintf(szBuf, L"Authenticator is not MSV1_0 - Returning.\n");

      WriteLogFile(szBuf);
      #endif

      SetLastError(NO_ERROR);
      return NO_ERROR;
   }

   //
   // Do something with the authentication information
   //
   pAuthInfo = (PMSV1_0_INTERACTIVE_LOGON) lpAuthentInfo;

   #ifdef DEBUG
   wsprintf(szBuf, L"LogonDomain=%s User=%s\r\n",
            pAuthInfo->LogonDomainName.Buffer,
            pAuthInfo->UserName.Buffer);

   WriteLogFile(szBuf);
   #endif

   //
   // Let's utilize the logon script capability to display
   // our logon information
   //

   // The Caller MUST free this memory
   *lpLogonScript = LocalAlloc(LPTR,1024);

   #ifdef DEBUG
   wsprintf(*lpLogonScript,L"notepad %s",LOGFILE);
   #endif

   return NO_ERROR;
}


/****************************************************************************
   FUNCTION: NPPasswordChangeNotify

   PURPOSE:  This function is used to notify a credential manager provider
             of a password change (or, more accurately, an authentication
             information change) for an account.

*******************************************************************************/
DWORD
WINAPI
NPPasswordChangeNotify (
                       LPCWSTR             lpAuthentInfoType,
                       LPVOID              lpAuthentInfo,
                       LPCWSTR             lpPreviousAuthentInfoType,
                       LPVOID              lpPreviousAuthentInfo,
                       LPWSTR              lpStationName,
                       LPVOID              StationHandle,
                       DWORD               dwChangeInfo
                       )
{

   return NO_ERROR;
}

#ifdef DEBUG
BOOL
WriteLogFile(
            LPTSTR String
            )
{
   HANDLE hFile;
   DWORD dwBytesWritten;

   hFile = CreateFile(
                     LOGFILE,
                     GENERIC_WRITE,
                     0,
                     NULL,
                     OPEN_ALWAYS,
                     FILE_FLAG_SEQUENTIAL_SCAN,
                     NULL
                     );

   if (hFile == INVALID_HANDLE_VALUE) return FALSE;

   //
   // Seek to the end of the file
   //
   SetFilePointer(hFile, 0, NULL, FILE_END);

   WriteFile(
            hFile,
            String,
            lstrlen(String)*sizeof(TCHAR),
            &dwBytesWritten,
            NULL
            );

   CloseHandle(hFile);

   return TRUE;
}
#endif
