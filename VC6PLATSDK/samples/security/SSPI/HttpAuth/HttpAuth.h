/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1996 - 2000.  Microsoft Corporation.  All rights reserved.


Module Name:

    httpauth.h

Abstract:

    Functions for authentication sequence ( Basic & NTLM )

--*/

BOOL AddAuthorizationHeader(PSTR pch, PSTR pchSchemes, PSTR pchAuthData, PSTR pchUserName, PSTR pchPassword, BOOL *pfNeedMoreData );
BOOL InitAuthorizationHeader();
void TerminateAuthorizationHeader();
BOOL IsInAuthorizationSequence();
BOOL ValidateAuthenticationMethods( PSTR pszMet, PSTR pszPref );
