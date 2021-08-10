/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Server System Service

    FILE: Service.h

    PURPOSE: Provides file replication service function declarations.

    FUNCTIONS:

    COMMENTS: These funtions may be used by the main service routines
        as well as by the client and server file replication RPC routines.

*/

#pragma once

#include <windows.h>
#include <crtdbg.h>

// Macro for printing out error message and exiting the program if an 
// error occured during an RPC library call.
#define EXIT_IF_FAIL(x, string){ \
        ((x) != RPC_S_OK) ? _tprintf(TEXT("%s failed with error %d\n"), \
        TEXT(string), (x)), exit(EXIT_FAILURE) : 0;}

// Make sure the ASSERTE macro is defined.
#ifndef ASSERTE
#define ASSERTE _ASSERTE
#endif

// Size for short message strings.
#define MSG_SIZE (256)

VOID * AutoHeapAlloc(size_t dwBytes);

VOID AutoHeapFree(VOID * lpMem);

// end common.h
