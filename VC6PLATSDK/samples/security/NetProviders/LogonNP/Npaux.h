/*---------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1998 - 2000.  Microsoft Corporation.  All rights reserved.

npaux.h
---------------------------------------------------------------*/

#if !defined (INC_NPAUX_H)
#define INC_NPAUX_H

//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

typedef struct _UNICODE_STRING
{
   USHORT Length;
   USHORT MaximumLength;
   #ifdef MIDL_PASS
   [size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
   #else // MIDL_PASS
   PWSTR  Buffer;
   #endif // MIDL_PASS
} UNICODE_STRING;
typedef UNICODE_STRING *PUNICODE_STRING;
   #define UNICODE_NULL ((WCHAR)0) // winnt


typedef enum _MSV1_0_LOGON_SUBMIT_TYPE
{
   Dummy
} MSV1_0_LOGON_SUBMIT_TYPE, *PMSV1_0_LOGON_SUBMIT_TYPE;


typedef struct _MSV1_0_INTERACTIVE_LOGON
{
   MSV1_0_LOGON_SUBMIT_TYPE MessageType;
   UNICODE_STRING LogonDomainName;
   UNICODE_STRING UserName;
   UNICODE_STRING Password;
} MSV1_0_INTERACTIVE_LOGON, *PMSV1_0_INTERACTIVE_LOGON;

#endif

