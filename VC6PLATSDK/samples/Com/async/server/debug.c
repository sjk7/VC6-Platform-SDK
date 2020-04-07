// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

#define	ANSI
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include "debug.h"


void AddToMessageLog(LPWSTR lpszSourceName, LPWSTR lpszMsg, WORD ErrorLogType);
void ReportError(LPTSTR lpstrMessage, DWORD errno);

//#define _WRITE_TO_EVENT_LOG_

#if defined(_WRITE_TO_EVENT_LOG_)
extern LPWSTR appSource;
#endif


LPSTR WINAPI UniCode2Ansi(LPSTR lpa, LPCWSTR lpw, int nChars)
{
	_ASSERT(lpw != NULL);
	_ASSERT(lpa != NULL);
	// verify that no illegal character present
	// since lpa was allocated based on the size of lpw
	// don't worry about the number of chars
	lpa[0] = '\0';
	WideCharToMultiByte(CP_ACP, 0, lpw, -1, lpa, nChars, NULL, NULL);
	return lpa;
}

LPWSTR WINAPI Ansi2Unicode(LPWSTR lpw, LPCSTR lpa, int nChars)
{
	_ASSERT(lpa != NULL);
	_ASSERT(lpw != NULL);
	// verify that no illegal character present
	// since lpw was allocated based on the size of lpa
	// don't worry about the number of chars
	lpw[0] = L'\0';
	MultiByteToWideChar(CP_ACP, 0, lpa, -1, lpw, nChars);
	return lpw;
}

#if defined(_DEBUG)
void _cdecl DebugTrace(LPCTSTR lpszFormat, ...)
{
	va_list	args;
	TCHAR szBuffer[512];
	int cb;

	va_start(args, lpszFormat);

	cb = _vstprintf(szBuffer, lpszFormat, args);
#if defined(_WRITE_TO_EVENT_LOG_)
#if !defined(_UNICODE)
	{	
	CHAR_CONVERSION;
	AddToMessageLog(appSource, A2W(szBuffer), EVENTLOG_INFORMATION_TYPE);
	}
#else
	AddToMessageLog(appSource, szBuffer, EVENTLOG_INFORMATION_TYPE);
#endif // _UNICODE
#else  // _WRITE_TO_EVENT_LOG_
	OutputDebugString(szBuffer);
	OutputDebugString(_T("\r\n"));
#endif // _WRITE_TO_EVENT_LOG_
	return;
}
#endif // _DEBUG

void ReportError(LPTSTR lpstrMessage, DWORD errno)
{
	LPTSTR lpstrError, ErrorMessage;
	DWORD cbLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|
								FORMAT_MESSAGE_FROM_SYSTEM,
								NULL,
								errno, 
								LANG_USER_DEFAULT, 
								(LPSTR)&lpstrError, 
								0, 
								NULL);
	ErrorMessage = LocalAlloc(LPTR, cbLen+lstrlen(lpstrMessage)+3);
	wsprintf(ErrorMessage, "%s: %s", lpstrMessage, lpstrError);
#if defined(_WRITE_TO_EVENT_LOG_)
#if !defined(_UNICODE)	
	{
	CHAR_CONVERSION;
	AddToMessageLog(appSource, A2W(ErrorMessage),EVENTLOG_ERROR_TYPE);
	}
#else // _UNICODE
	AddToMessageLog(appSource, ErrorMessage,EVENTLOG_ERROR_TYPE);
#endif // _UNICODE
#else  // _WRITE_TO_EVENT_LOG_
	OutputDebugString(ErrorMessage);
	OutputDebugString(_T("\r\n"));
#endif // _WRITE_TO_EVENT_LOG_
	LocalFree(lpstrError);
	LocalFree(ErrorMessage);
}


static BOOL g_fKey = FALSE;
static TCHAR g_KeyName[] = 
	_T("System\\CurrentControlSet\\Services\\EventLog\\Application\\COM");

void AddToMessageLog(LPWSTR lpszSourceName, LPWSTR lpszMsg, WORD ErrorLogType)
{
	HKEY hkey;
    HANDLE  hEventSource;
    HANDLE hToken;
	TOKEN_USER *puser;
	PSID psid = NULL;
	DWORD cb = 0;

    // Use event logging to log the error.
    //

	if (!g_fKey)
	{
		RegCreateKey(HKEY_LOCAL_MACHINE, g_KeyName, &hkey);
		RegFlushKey(hkey);
		RegCloseKey(hkey);
		g_fKey = TRUE;
	}

	if (OpenThreadToken(GetCurrentThread(), TOKEN_READ, TRUE, &hToken) 
		|| OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken))
	{
		GetTokenInformation(hToken, TokenUser, NULL, cb, &cb);
		puser = LocalAlloc(LPTR, cb);
		if (puser && GetTokenInformation(hToken, TokenUser, puser, cb, &cb))
			psid = puser->User.Sid;
	}
	
	hEventSource = RegisterEventSource(NULL, _T("COM"));

    if (hEventSource != NULL) 
	{
		ReportEventW(hEventSource, // handle of event source
			ErrorLogType,		  // event type
            0,                    // event category
            0,                    // event ID
            psid,                 // current user's SID
            1,                    // strings in lpszStrings
            0,                    // no bytes of raw data
            (LPCWSTR*)&lpszMsg,    // array of error strings
            NULL);                // no raw data

        DeregisterEventSource(hEventSource);
    }
	if (puser)
		LocalFree(puser);

	return;   
}
