/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    security.h

Abstract:

    Functions to handle communication with the security package

Revision History:

--*/

BOOL InitPackage (
	TCHAR *lpPackageName, 
	BOOL fVerbose
	);

BOOL TermPackage ();

BOOL InitSession (DWORD dwKey);

BOOL TermSession (DWORD dwKey);

BOOL GenClientContext (
	DWORD dwKey,
	BYTE *pIn,
	DWORD cbIn,
	BYTE **pOut,
	DWORD *pcbOut,
	BOOL *pfDone,
        ULONG *pAttribs,
        CHAR *pszTarget
	);

BOOL GenServerContext (
	DWORD dwKey,
	BYTE *pIn,
	DWORD cbIn,
	BYTE **pOut,
	DWORD *pcbOut,
	BOOL *pfDone,
	ULONG *pAttribs
	);

BOOL ImpersonateContext (DWORD dwKey);

BOOL RevertContext (DWORD dwKey);

BOOL EncryptThis (
         DWORD dwKey, 
         PBYTE pMessage, 
         ULONG cbMessage,
         BYTE ** ppOutput,
         LPDWORD pcbOutput
	);

PBYTE DecryptThis(
         DWORD dwKey, 
         PBYTE achData, 
         LPDWORD pcbMessage
	);

BOOL 
SignThis (
         DWORD dwKey, 
         PBYTE pMessage, 
         ULONG cbMessage,
         BYTE ** ppOutput,
         LPDWORD pcbOutput
	);

PBYTE VerifyThis(
          DWORD dwKey, 
          PBYTE pBuffer, 
          LPDWORD pcbMessage
	);

void PrintHexDump(DWORD length, PBYTE buffer);



