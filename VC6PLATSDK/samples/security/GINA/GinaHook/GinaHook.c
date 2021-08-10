/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.

 Copyright (C) 1996 - 2000.  Microsoft Corporation.  All rights reserved.

 Module:   Ginahook.c

 Abstract: See ReadMe.txt for more detail information about this sample.

 Revision: August 6, 1999.

-------------------------------------------------------------------------------*/

#define _WIN32_WINNT 0x0400

#include <windows.h>
#include <winwlx.h>

#include "Ginahook.h"
#include "GinaDlg.h"

//
// Location of the real MSGINA.
//

#define REALGINA_PATH      TEXT("MSGINA.DLL")
#define GINASTUB_VERSION   (WLX_VERSION_1_3) // Highest version supported at
                                             // this point. Remember to modify
                                             // this as support for newer version
                                             // is added to this program.
//
// Winlogon function dispatch table.
//
static PVOID g_pWinlogon = NULL;
static DWORD g_dwVersion = WLX_VERSION_1_3;

//
// Pointers to the real MSGINA functions.
//

static PFWLXNEGOTIATE            pfWlxNegotiate;
static PFWLXINITIALIZE           pfWlxInitialize;
static PFWLXDISPLAYSASNOTICE     pfWlxDisplaySASNotice;
static PFWLXLOGGEDOUTSAS         pfWlxLoggedOutSAS;
static PFWLXACTIVATEUSERSHELL    pfWlxActivateUserShell;
static PFWLXLOGGEDONSAS          pfWlxLoggedOnSAS;
static PFWLXDISPLAYLOCKEDNOTICE  pfWlxDisplayLockedNotice;
static PFWLXWKSTALOCKEDSAS       pfWlxWkstaLockedSAS;
static PFWLXISLOCKOK             pfWlxIsLockOk;
static PFWLXISLOGOFFOK           pfWlxIsLogoffOk;
static PFWLXLOGOFF               pfWlxLogoff;
static PFWLXSHUTDOWN             pfWlxShutdown;

//
// New for version 1.1
//

static PFWLXSTARTAPPLICATION     pfWlxStartApplication  = NULL;
static PFWLXSCREENSAVERNOTIFY    pfWlxScreenSaverNotify = NULL;

//
// New for version 1.2 - No new GINA interface was added, except
//                       a new function in the dispatch table.
//

//
// New for version 1.3
//

static PFWLXNETWORKPROVIDERLOAD   pfWlxNetworkProviderLoad  = NULL;
static PFWLXDISPLAYSTATUSMESSAGE  pfWlxDisplayStatusMessage = NULL;
static PFWLXGETSTATUSMESSAGE      pfWlxGetStatusMessage     = NULL;
static PFWLXREMOVESTATUSMESSAGE   pfWlxRemoveStatusMessage  = NULL;


//
// Hook into the real MSGINA.
//

BOOL MyInitialize (HINSTANCE hDll, DWORD dwWlxVersion)
{
   //
   // Get pointers to all of the WLX functions in the real MSGINA.
   //
   pfWlxInitialize = 
      (PFWLXINITIALIZE) GetProcAddress(hDll, "WlxInitialize");
   if (!pfWlxInitialize) 
   {
      return FALSE;
   }

   pfWlxDisplaySASNotice =
      (PFWLXDISPLAYSASNOTICE) GetProcAddress(hDll, "WlxDisplaySASNotice");
   if (!pfWlxDisplaySASNotice) 
   {
      return FALSE;
   }

   pfWlxLoggedOutSAS = 
      (PFWLXLOGGEDOUTSAS) GetProcAddress(hDll, "WlxLoggedOutSAS");
   if (!pfWlxLoggedOutSAS) 
   {
      return FALSE;
   }

   pfWlxActivateUserShell =
      (PFWLXACTIVATEUSERSHELL) GetProcAddress(hDll, "WlxActivateUserShell");
   if (!pfWlxActivateUserShell) 
   {
      return FALSE;
   }

   pfWlxLoggedOnSAS =
      (PFWLXLOGGEDONSAS) GetProcAddress(hDll, "WlxLoggedOnSAS");
   if (!pfWlxLoggedOnSAS) 
   {
      return FALSE;
   }

   pfWlxDisplayLockedNotice =
      (PFWLXDISPLAYLOCKEDNOTICE) GetProcAddress(hDll, "WlxDisplayLockedNotice");
   if (!pfWlxDisplayLockedNotice) 
   {
      return FALSE;
   }

   pfWlxIsLockOk = 
      (PFWLXISLOCKOK) GetProcAddress(hDll, "WlxIsLockOk");
   if (!pfWlxIsLockOk) 
   {
      return FALSE;
   }

   pfWlxWkstaLockedSAS =
       (PFWLXWKSTALOCKEDSAS) GetProcAddress(hDll, "WlxWkstaLockedSAS");
   if (!pfWlxWkstaLockedSAS) 
   {
      return FALSE;
   }

   pfWlxIsLogoffOk = 
      (PFWLXISLOGOFFOK) GetProcAddress(hDll, "WlxIsLogoffOk");
   if (!pfWlxIsLogoffOk) 
   {
      return FALSE;
   }

   pfWlxLogoff = 
      (PFWLXLOGOFF) GetProcAddress(hDll, "WlxLogoff");
   if (!pfWlxLogoff) 
   {
      return FALSE;
   }

   pfWlxShutdown = 
      (PFWLXSHUTDOWN) GetProcAddress(hDll, "WlxShutdown");
   if (!pfWlxShutdown) 
   {
      return FALSE;
   }

   //
   // Load functions for version 1.1 as necessary.
   //
   if (dwWlxVersion > WLX_VERSION_1_0)
   {
      pfWlxStartApplication = 
         (PFWLXSTARTAPPLICATION) GetProcAddress(hDll, "WlxStartApplication");
      if (!pfWlxStartApplication)
      {
         return FALSE;
      }

      pfWlxScreenSaverNotify = 
         (PFWLXSCREENSAVERNOTIFY) GetProcAddress(hDll, "WlxScreenSaverNotify");
      if (!pfWlxScreenSaverNotify)
      {
         return FALSE;
      }
   }

   //
   // Load functions for version 1.3 as necessary.
   //
   if (dwWlxVersion > WLX_VERSION_1_2)
   {
      pfWlxNetworkProviderLoad = 
         (PFWLXNETWORKPROVIDERLOAD) 
            GetProcAddress(hDll, "WlxNetworkProviderLoad");
      if (!pfWlxNetworkProviderLoad)
      {
         return FALSE;
      }

      pfWlxDisplayStatusMessage =
         (PFWLXDISPLAYSTATUSMESSAGE) 
            GetProcAddress(hDll, "WlxDisplayStatusMessage");
      if (!pfWlxDisplayStatusMessage)
      {
         return FALSE;
      }

      pfWlxGetStatusMessage =
         (PFWLXGETSTATUSMESSAGE)
            GetProcAddress(hDll, "WlxGetStatusMessage");
      if (!pfWlxGetStatusMessage)
      {
         return FALSE;
      }

      pfWlxRemoveStatusMessage =
         (PFWLXREMOVESTATUSMESSAGE)
            GetProcAddress(hDll, "WlxRemoveStatusMessage");
      if (!pfWlxRemoveStatusMessage)
      {
         return FALSE;
      }
   }

   //
   // Load functions for newer version here...
   //

   //
   // Everything loaded OK.
   //
   return TRUE;
}


BOOL 
WINAPI 
WlxNegotiate (DWORD   dwWinlogonVersion,
              DWORD * pdwDllVersion)
{
   HINSTANCE hDll;
   DWORD dwWlxVersion = GINASTUB_VERSION;

   //
   // Load MSGINA.DLL.
   //
   if (!(hDll = LoadLibrary(REALGINA_PATH))) 
   {
      return FALSE;
   }

   //
   // Get pointers to WlxNegotiate function in the real MSGINA.
   //
   pfWlxNegotiate = (PFWLXNEGOTIATE) GetProcAddress(hDll, "WlxNegotiate");
   if (!pfWlxNegotiate) 
   {
      return FALSE;
   }
 
   //
   // Handle older version of Winlogon.
   //
   if (dwWinlogonVersion < dwWlxVersion)
   {
      dwWlxVersion = dwWinlogonVersion;
   }

   //
   // Negotiate with MSGINA for version that we can support.
   //
   if (!pfWlxNegotiate(dwWlxVersion, &dwWlxVersion))
   {
      return FALSE;
   }
   
   //
   // Load the rest of the WLX functions from the real MSGINA.
   //
   if (!MyInitialize(hDll, dwWlxVersion))
   {
      return FALSE;
   }

   //
   // Inform Winlogon which version to use.
   //
   *pdwDllVersion = g_dwVersion = dwWlxVersion;
   
   return TRUE;
}


BOOL
WINAPI
WlxInitialize (LPWSTR  lpWinsta,
               HANDLE  hWlx,
               PVOID   pvReserved,
               PVOID   pWinlogonFunctions,
               PVOID * pWlxContext)
{

   //
   // Save pointer to dispatch table.
   // 
   // Note that g_pWinlogon will need to be properly casted to the 
   // appropriate version when used to call function in the dispatch 
   // table.
   //
   // For example, assuming we are at WLX_VERSION_1_3, we would call
   // WlxSasNotify() as follows:
   //
   // ((PWLX_DISPATCH_VERSION_1_3) g_pWinlogon)->WlxSasNotify(hWlx, MY_SAS);
   //
   g_pWinlogon = pWinlogonFunctions;

   //
   // Now hook the WlxDialogBoxParam() dispatch function.
   //
   HookWlxDialogBoxParam(g_pWinlogon, g_dwVersion);

   return pfWlxInitialize(lpWinsta,
                          hWlx,
                          pvReserved,
                          pWinlogonFunctions,
                          pWlxContext);
}


VOID
WINAPI
WlxDisplaySASNotice (PVOID pWlxContext)
{
   pfWlxDisplaySASNotice(pWlxContext);
}


int
WINAPI
WlxLoggedOutSAS (PVOID                pWlxContext,
                 DWORD                dwSasType,
                 PLUID                pAuthenticationId,
                 PSID                 pLogonSid,
                 PDWORD               pdwOptions,
                 PHANDLE              phToken,
                 PWLX_MPR_NOTIFY_INFO pMprNotifyInfo,
                 PVOID *              pProfile)
{
   int iRet;

   iRet = pfWlxLoggedOutSAS(pWlxContext,
                            dwSasType,
                            pAuthenticationId,
                            pLogonSid,
                            pdwOptions,
                            phToken,
                            pMprNotifyInfo,
                            pProfile);

   if(iRet == WLX_SAS_ACTION_LOGON) 
   {
      //
      // Copy pMprNotifyInfo and pLogonSid for later use.
      //

      // pMprNotifyInfo->pszUserName
      // pMprNotifyInfo->pszDomain
      // pMprNotifyInfo->pszPassword
      // pMprNotifyInfo->pszOldPassword
   }

   return iRet;
}


BOOL
WINAPI
WlxActivateUserShell (PVOID pWlxContext,
                      PWSTR pszDesktopName,
                      PWSTR pszMprLogonScript,
                      PVOID pEnvironment)
{
   return pfWlxActivateUserShell(pWlxContext,
                                 pszDesktopName,
                                 pszMprLogonScript,
                                 pEnvironment);
}


int
WINAPI
WlxLoggedOnSAS (PVOID pWlxContext,
                DWORD dwSasType,
                PVOID pReserved)
{
   return pfWlxLoggedOnSAS(pWlxContext, 
                           dwSasType, 
                           pReserved);
}


VOID
WINAPI
WlxDisplayLockedNotice (PVOID pWlxContext)
{
   pfWlxDisplayLockedNotice(pWlxContext);
}


BOOL
WINAPI
WlxIsLockOk (PVOID pWlxContext)
{
   return pfWlxIsLockOk(pWlxContext);
}


int
WINAPI
WlxWkstaLockedSAS (PVOID pWlxContext,
                   DWORD dwSasType)
{
   return pfWlxWkstaLockedSAS(pWlxContext, dwSasType);
}


BOOL
WINAPI
WlxIsLogoffOk (PVOID pWlxContext)
{
   BOOL bSuccess;

   bSuccess = pfWlxIsLogoffOk(pWlxContext);

   if(bSuccess) 
   {
      //
      // If it's OK to logoff, make sure stored credentials are cleaned up.
      //
   }

   return bSuccess;
}


VOID
WINAPI
WlxLogoff (PVOID pWlxContext)
{
   pfWlxLogoff(pWlxContext);
}


VOID
WINAPI
WlxShutdown(PVOID pWlxContext,
            DWORD ShutdownType)
{
   pfWlxShutdown(pWlxContext, ShutdownType);
}


//
// New for version 1.1
//

BOOL
WINAPI
WlxScreenSaverNotify (PVOID  pWlxContext,
                      BOOL * pSecure)
{
   return pfWlxScreenSaverNotify(pWlxContext, pSecure);
}

BOOL
WINAPI
WlxStartApplication (PVOID pWlxContext,
                     PWSTR pszDesktopName,
                     PVOID pEnvironment,
                     PWSTR pszCmdLine)
{
   return pfWlxStartApplication(pWlxContext,
                                pszDesktopName,
                                pEnvironment,
                                pszCmdLine);
}


//
// New for version 1.3
//

BOOL
WINAPI
WlxNetworkProviderLoad (PVOID                pWlxContext,
                        PWLX_MPR_NOTIFY_INFO pNprNotifyInfo)
{
   return pfWlxNetworkProviderLoad(pWlxContext, pNprNotifyInfo);
}


BOOL
WINAPI
WlxDisplayStatusMessage (PVOID pWlxContext,
                         HDESK hDesktop,
                         DWORD dwOptions,
                         PWSTR pTitle,
                         PWSTR pMessage)
{
   return pfWlxDisplayStatusMessage(pWlxContext,
                                    hDesktop,
                                    dwOptions,
                                    pTitle,
                                    pMessage);
}


BOOL
WINAPI
WlxGetStatusMessage (PVOID   pWlxContext,
                     DWORD * pdwOptions,
                     PWSTR   pMessage,
                     DWORD   dwBufferSize)
{
   return pfWlxGetStatusMessage(pWlxContext,
                                pdwOptions,
                                pMessage,
                                dwBufferSize);
}


BOOL
WINAPI
WlxRemoveStatusMessage (PVOID pWlxContext)
{
   return pfWlxRemoveStatusMessage(pWlxContext);
}
