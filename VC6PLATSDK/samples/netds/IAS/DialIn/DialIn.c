/*++

Copyright 1999 - 2000 Microsoft Corporation

Module Name:

   dialin.c

Abstract:

   This module implements the DLL exports for a RADIUS extension DLL.

   The sample extension processes all Access-Requests destined for the
   WindowsNT authentication provider and verifies that the user has been
   granted the dial-in privilege.

--*/

#include <windows.h>
#include <malloc.h>
#include <authif.h>
#include <rassapi.h>
#include <lmerr.h>

/*
 *  The UNC name of the localhost.
 */
WCHAR theLocalServer[UNCLEN + 1];

/*
 *  Finds an attribute of the desired type.
 */
CONST RADIUS_ATTRIBUTE*
WINAPI
FindAttribute(
    IN CONST RADIUS_ATTRIBUTE *pAttrs,
    IN DWORD dwAttrType
    )
{
   for ( ; pAttrs->dwAttrType != ratMinimum; ++pAttrs)
   {
      if (pAttrs->dwAttrType == dwAttrType) { return pAttrs; }
   }

   return NULL;
}

/*
 *  Initialize the extension.
 */
DWORD
WINAPI
RadiusExtensionInit( VOID )
{
   DWORD cbData;

   /* theLocalServer must be in UNC format. */
   wcscpy(theLocalServer, L"\\\\");

   /* Append the computer name. */
   cbData = UNCLEN - 1;
   if (!GetComputerNameW(theLocalServer + 2, &cbData))
   {
      return GetLastError();
   }

   return NO_ERROR;
}

/*
 *  Process a request.
 */
DWORD
WINAPI
RadiusExtensionProcess(
    IN CONST RADIUS_ATTRIBUTE *pAttrs,
    OUT OPTIONAL PRADIUS_ACTION pfAction
    )
{
   CONST RADIUS_ATTRIBUTE *p;
   PWSTR domain, username;
   int nChar;
   DWORD error;
   WCHAR buffer[UNCLEN + 1], *accountServer;
   RAS_USER_0 ru0;

   /* Only process Access-Requests. */
   p = FindAttribute(pAttrs, ratCode);
   if (p == NULL || p->dwValue != 1) 
   { 
      return NO_ERROR; 
   }

   /* If it's not destined for the WindowsNT provider, we're not interested. */
   p = FindAttribute(pAttrs, ratProvider);
   if (p == NULL || p->dwValue != rapWindowsNT)
   {
      return NO_ERROR;
   }

   /* Find the Stripped-User-Name attribute. */
   p = FindAttribute(pAttrs, ratStrippedUserName);

   /* Make sure we found an attribute and it's the right data type. */
   if (p == NULL || p->fDataType != rdtString)
   {
      return ERROR_INVALID_DATA;
   }

   /* Allocate a buffer for the UNICODE string. */
   domain = (PWSTR)_alloca((p->cbDataLength + 1) * sizeof(WCHAR));

   /* Convert to UNICODE. */
   nChar = MultiByteToWideChar(
               CP_ACP,
               0,
               p->lpValue,
               p->cbDataLength,
               domain,
               p->cbDataLength + 1
               );
   if (nChar == 0)
   {
      return GetLastError();
   }
   domain[nChar] = L'\0';

   /* Look for the delimiter in "domain\username". */
   username = wcschr(domain, L'\\');

   accountServer = theLocalServer;

   if (username)
   {
      /* We found a delimiter, so null it out and advance. */
      *username++ = L'\0';

      /* Is this the local computer? */
      if (_wcsicmp(domain, theLocalServer + 2))
      {
         /* No, so we have to find a DC. */
         error = RasAdminGetUserAccountServer(
                     domain,
                     NULL,
                     buffer
                     );
         if (error != NO_ERROR)
         {
            return error;
         }

         accountServer = buffer;
      }
   }
   else
   {
      /* No delimiter, so the whole thing is the username. */
      username = domain;
   }

   /* Retrieve the dial-in info for this user. */
   error = RasAdminUserGetInfo(
               accountServer,
               username,
               &ru0
               );

   /* If the user doesn't exist, it's not an error, but we always reject. */
   if (error == NERR_UserNotFound)
   {
      *pfAction = raReject;
      return NO_ERROR;
   }

   /* Any other error and we bail. */
   if (error != NO_ERROR)
   {
      return error;
   }

   /* Is the dial-in bit set? */
   if ((ru0.bfPrivilege & RASPRIV_DialinPrivilege) == 0)
   {
      /* No, so reject. */
      *pfAction = raReject;
   }

   return NO_ERROR;
}
