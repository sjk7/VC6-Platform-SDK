/*
    Copyright Microsoft Corp. 1992 - 2001

    Server Profiling Routines

    FILE: Prof.cpp
    
    PURPOSE: Routines for profiling server system services.
    
    FUNCTIONS:
        ProfOpenLog - Opens the profile log file and prepares to
    take timings.
	ProfRecordTime - Records the time of an event.
	ProfCloseLog - Writes the profiling data to the file
    and closes it.

    COMMENTS: See the header file for function info.
        These routines depend on the existence of a high-resolution
    performance counter.

*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>

#include "Prof.h"
#include "Service.h"
#include "common.h"

// Handle to the profile log file.
HANDLE hProfLog = NULL;

// Counters for the timings.
LARGE_INTEGER lpStartTime, lpCurrentTime, lpFrequency;

// The profile log text data.
// Profile log gets acumulated in this string first, and then
// gets written out when the log gets closed.
TCHAR PROF_LOG[PROF_LOG_MAX_SIZE];

// Current size of the profile log.
UINT nProfLogSize = 0;

// This is the maximum size of the log entry without the
// user-specified message.  It is basically the size of a string
// with an integer and a float.
#define MAX_ENTRY_SIZE_NOMSG (32)

HANDLE hProfMutex;

VOID ProfOpenLog(LPTSTR LogFileName) {

    // Create the mutex.
    if ((hProfMutex = CreateMutex(NULL,
				  FALSE,
				  TEXT("ProfMutex"))) == INVALID_HANDLE_VALUE) {
	RaiseException(GetLastError(), 0, 0, NULL);
        return;
    }

    // Open the profiling log.
    if ((hProfLog = CreateFile(LogFileName,
			       GENERIC_WRITE,
			       0,
			       NULL,
			       CREATE_ALWAYS,
			       FILE_ATTRIBUTE_NORMAL,
			       NULL)) == INVALID_HANDLE_VALUE) {
	RaiseException(GetLastError(), 0, 0, NULL);
        return;
    }

    // Get the current time.
    if (QueryPerformanceCounter(&lpStartTime) == FALSE) {
	RaiseException(GetLastError(), 0, 0, NULL);
        return;        
    }

    // Get the frequency.
    if (QueryPerformanceFrequency(&lpFrequency) == FALSE) {
	RaiseException(GetLastError(), 0, 0, NULL);
        return;        
    }
}

VOID ProfRecordTime(UINT id, LPTSTR msg) {
    FLOAT dt;

    if (WaitForSingleObject(hProfMutex, INFINITE) == WAIT_FAILED) {
	RaiseException(GetLastError(), 0, 0, NULL);
	return;
    }

    // Write the entry only if there is enough space left in
    // the log.
    if (nProfLogSize < PROF_LOG_MAX_SIZE - (MAX_ENTRY_SIZE_NOMSG + _tcslen(msg))) {
	if (QueryPerformanceCounter(&lpCurrentTime) == FALSE) {
	    RaiseException(GetLastError(), 0, 0, NULL);
	    return;
	}
	
	// Get the time stamp for the event.
	dt = (FLOAT)(lpCurrentTime.QuadPart - lpStartTime.QuadPart)/(FLOAT)(lpFrequency.QuadPart);
	
	// Append the entry to the log.
	nProfLogSize+=_stprintf(&PROF_LOG[nProfLogSize], TEXT("%d %s %f\n"), id, msg, dt);
    }

    if (ReleaseMutex(hProfMutex) == FALSE) {
	RaiseException(GetLastError(), 0, 0, NULL);
	return;
    }
}

VOID ProfCloseLog(VOID) {
    ULONG cbWritten;
    DWORD status;

    // Close the mutex.
    // Here we make the assumption that no outside functions will use
    // the mutex anymore.  This should be valid, since all the profiling data
    // has been written.
    status = CloseHandle(hProfMutex);
    ASSERTE(status);

    // Write out the profile log.
    if(!WriteFile(hProfLog,
		  (LPVOID)PROF_LOG,
		  nProfLogSize*sizeof(TCHAR),
		  &cbWritten,
		  NULL)) {

	RaiseException(GetLastError(), 0, 0, NULL);
	return;
    }

    // Close the profile log.
    if (hProfLog != NULL && hProfLog != INVALID_HANDLE_VALUE) {
        status = CloseHandle(hProfLog);
        ASSERTE(status);
    }
}

// end Prof.cpp
