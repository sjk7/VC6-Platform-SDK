/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Server System Service

    FILE: common.h

    PURPOSE: Provides common file replication service declarations.

*/

#pragma once

#include <windows.h>
#include <crtdbg.h>

// Macro for printing out error message and exiting the program if an 
// error occured during an RPC library call.
#define EXIT_IF_FAIL(x, string){ \
        ((x) != RPC_S_OK) ? _tprintf(TEXT("%s failed with error %d\n"), \
        TEXT(string), (x)), exit(EXIT_FAILURE) : 0;}

#define RPC_EEINFO_EXIT_IF_FAIL(x, string){ \
        ((x) != RPC_S_OK) ? PrintProcFailureEEInfo(string, x), \
        exit(EXIT_FAILURE) : 0;}

// Make sure the ASSERTE macro is defined.
#ifndef ASSERTE
#define ASSERTE _ASSERTE
#endif

// Size for short message strings.
#define MSG_SIZE (256)

VOID GetEEInfoText(TCHAR *Msg, UINT BuffSize, UINT *MsgSize);

VOID PrintProcFailureEEInfo(LPTSTR ProcName, DWORD ErrCode);

VOID * AutoHeapAlloc(size_t dwBytes);

VOID AutoHeapFree(VOID * lpMem);

// end common.h
