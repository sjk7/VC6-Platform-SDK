/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1995 - 2000.  Microsoft Corporation.  All rights reserved.

Module Name:
    proto.h

Abstract:
    prototypes

Environment:
    Internet

--*/

BOOL
HttpGetSocket(
    char * Verb,
    char * Server,
    char * URL,
    BOOL   DisplayHeaders,
    DWORD  ClientDataSize,
    PSTR   pszUserName,
    PSTR   pszPassword,
    PSTR   pszStore,
    PSTR   pszPref );
