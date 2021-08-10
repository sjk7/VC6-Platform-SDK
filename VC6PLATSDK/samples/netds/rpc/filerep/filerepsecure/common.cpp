/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    Server System Service

    FILE: common.cpp

    PURPOSE: Provides common file replication service routine definitions.

*/

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "common.h"

HANDLE hProcessHeap = NULL;

VOID * AutoHeapAlloc(size_t dwBytes) {
    if (hProcessHeap == NULL) {
        hProcessHeap = GetProcessHeap();
    }
    return HeapAlloc(hProcessHeap, 0, dwBytes);
}

VOID AutoHeapFree(VOID * lpMem) {
    DWORD status;
    ASSERTE(hProcessheap != NULL);
    status = HeapFree(hProcessHeap, 0, lpMem);
    ASSERTE(status);
}

// end common.cpp
