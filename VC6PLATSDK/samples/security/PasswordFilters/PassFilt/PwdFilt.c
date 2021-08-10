/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1995 - 2000.  Microsoft Corporation.  All rights reserved.

   Module Name:

       pwdfilt.c

   Abstract:

       This module illustrates how to implement password change
       notification and password filtering in Windows NT 4.0.

       Password change notification is useful for synchronization of
       non-Windows NT account databases.

       Password change filtering is useful for enforcing quality or
       strength of passwords in an Windows NT account database.

       This sample illustrates one approach to enforcing additional
       password quality.

   --*/

#include <windows.h>
#include <ntsecapi.h> 

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS  ((NTSTATUS)0x00000000L)
#endif

NTSTATUS
NTAPI
PasswordChangeNotify(
                    PUNICODE_STRING UserName,
                    ULONG RelativeId,
                    PUNICODE_STRING Password
                    )
/*++

Routine Description:

    This (optional) routine is notified of a password change.

Arguments:

    UserName - Name of user whose password changed

    RelativeId - RID of the user whose password changed

    NewPassword - Cleartext new password for the user

Return Value:

    STATUS_SUCCESS only - errors from packages are ignored.

--*/
{

#ifdef DEBUG
    LPWSTR String = NULL;
    DWORD cbString = 0;

    cbString = Password->Length + UserName->Length + (256*sizeof(WCHAR));

    String = HeapAlloc(GetProcessHeap(), 0, cbString);

    if( String != NULL )
    {

        //
        // don't display the password in the debugger unless absolutely
        // necessary -- assume everyone has access to a remote debug session.
        //

#if 0
        swprintf(String,
            L"Password for account %.*ls (rid 0x%x) changed to %.*ls\n",
            UserName->Length / sizeof(WCHAR),
            UserName->Buffer,
            RelativeId,
            Password->Length / sizeof(WCHAR),
            Password->Buffer
            );
#else
        swprintf(String,
            L"Password for account %.*ls (rid 0x%x) changed\n",
            UserName->Length / sizeof(WCHAR),
            UserName->Buffer,
            RelativeId
            );
#endif

        OutputDebugStringW( String );

        ZeroMemory(String, cbString);
        HeapFree(GetProcessHeap(), 0, String);
    }
#endif

    return STATUS_SUCCESS;
}

BOOL
NTAPI
PasswordFilter(
              PUNICODE_STRING UserName,
              PUNICODE_STRING FullName,
              PUNICODE_STRING Password,
              BOOL SetOperation
              )
/*++

Routine Description:

    This (optional) routine is notified of a password change.

Arguments:

    UserName - Name of user whose password changed

    FullName - Full name of the user whose password changed

    NewPassword - Cleartext new password for the user

    SetOperation - TRUE if the password was SET rather than CHANGED

Return Value:

    TRUE if the specified Password is suitable (complex, long, etc).
     The system will continue to evaluate the password update request
     through any other installed password change packages.

    FALSE if the specified Password is unsuitable. The password change
     on the specified account will fail.

--*/
{
   BOOL bComplex = FALSE; // assume the password in not complex enough
   DWORD cchPassword;
   PWORD CharType;
   DWORD i;
   DWORD dwNum = 0;
   DWORD dwUpper = 0;
   DWORD dwLower = 0;


   //
   // check if the password is complex enough for our liking by
   // checking that at least two of the four character types are
   // present.
   //

   CharType = HeapAlloc(GetProcessHeap(), 0, Password->Length);
   if (CharType == NULL) return FALSE;

   cchPassword = Password->Length / sizeof(WCHAR);

   if (GetStringTypeW(
                     CT_CTYPE1,
                     Password->Buffer,
                     cchPassword,
                     CharType
                     ))
   {

      for (i = 0 ; i < cchPassword ; i++)
      {

         //
         // keep track of what type of characters we have encountered
         //

         if (CharType[i] & C1_DIGIT)
         {
            dwNum = 1;
            continue;
         }

         if (CharType[i] & C1_UPPER)
         {
            dwUpper = 1;
            continue;
         }

         if (CharType[i] & C1_LOWER)
         {
            dwLower = 1;
            continue;
         }

         if (!(CharType[i] & (C1_ALPHA | C1_DIGIT) ))
         {

            //
            // any other character types make the password complex
            //

            dwNum = 2;

            break;
         }
      } // for

      //
      // Indicate whether we encountered enough password complexity
      //

      if ( (dwNum + dwUpper + dwLower) >= 2 )
         bComplex = TRUE;

      ZeroMemory( CharType, Password->Length );
   } // if

   HeapFree(GetProcessHeap(), 0, CharType);

   return bComplex;
}

BOOL
NTAPI
InitializeChangeNotify(
                      void
                      )
/*++

Routine Description:

    This (optional) routine is called when the password change package
    is loaded.

Arguments:

Return Value:

    TRUE if initialization succeeded.

    FALSE if initialization failed. This DLL will be unloaded by the
     system.

--*/
{

   #ifdef DEBUG
   OutputDebugString( TEXT("Initialize Change Notify called!\n") );
   #endif

   //
   // initialize any critical sections associated with password change
   // events, etc.
   //

   return TRUE;
}

