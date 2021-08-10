/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    System Service Procedures

    FILE: Service.c
    
    PURPOSE: Provides file replication service function definitions.
    
    FUNCTIONS:
        IsLocalSystem - Checks whether the service is running as
	    local system.
        ReportStatusToSCMgr - Changes the service's status and
            registers change with SCM.
        AddToMessageLog - Adds a string to the system message log.

    COMMENTS: These funtions may be used by the main service routines
        as well as by the client and server file replication RPC routines.

*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "common.h"

#include "Service.h"

/*
    FUNCTION: ReportStatusToSCMgr()

    PURPOSE: Sets the current status of the service and
             reports it to the Service Control Manager

    PARAMETERS:
        dwCurrentState - the state of the service
        dwWin32ExitCode - error code to report
        dwWaitHint - worst case estimate to next checkpoint

    RETURN VALUE:
        TRUE - success
        FALSE - failure

    COMMENTS:

*/
BOOL ReportStatusToSCMgr(SERVICE_STATUS_HANDLE *sshStatusHandle,
			 SERVICE_STATUS *ssStatus,
			 DWORD dwCurrentState,
			 DWORD dwWin32ExitCode,
			 DWORD dwWaitHint){

    static DWORD dwCheckPoint = 1;
    BOOL fResult = TRUE;

    if (dwCurrentState == SERVICE_START_PENDING)
        ssStatus->dwControlsAccepted = 0;
    else
        ssStatus->dwControlsAccepted = SERVICE_ACCEPT_STOP;
    
    ssStatus->dwCurrentState = dwCurrentState;
    ssStatus->dwWin32ExitCode = dwWin32ExitCode;
    ssStatus->dwWaitHint = dwWaitHint;
    
    if ( ( dwCurrentState == SERVICE_RUNNING ) || ( dwCurrentState == SERVICE_STOPPED ) ) {
        ssStatus->dwCheckPoint = 0;
    }
    else {
        ssStatus->dwCheckPoint = dwCheckPoint++;
    }
    
    // Report the status of the service to the service control manager.
    if (!(fResult = SetServiceStatus(*sshStatusHandle, ssStatus))) {
        AddToMessageLog(TEXT("SetServiceStatus failed"));
    }
    return fResult;
}

/*
    FUNCTION: AddToMessageLog(LPTSTR lpszMsg)

    PURPOSE: Allows any thread to log an error message

    PARAMETERS:
        lpszMsg - text for message

    RETURN VALUE:
        none

    COMMENTS:

*/
VOID AddToMessageLog(LPTSTR lpszMsg){
    TCHAR szMsg[256];
    HANDLE hEventSource;
    LPTSTR lpszStrings[2];
    DWORD dwErr = 0;

    dwErr = GetLastError();
    
    // Use event logging to log the error.
    hEventSource = RegisterEventSource(NULL, SERVICENAME);
    
    _stprintf(szMsg, TEXT("%s error: %d"), SERVICENAME, dwErr);
    lpszStrings[0] = szMsg;
    lpszStrings[1] = lpszMsg;
    
    if (hEventSource != NULL) {
        ReportEvent(hEventSource, // handle of event source
		    EVENTLOG_ERROR_TYPE, // event type
		    0, // event category
		    0, // event ID
		    NULL, // current user's SID
		    2, // strings in lpszStrings
		    0, // no bytes of raw data
		    (LPCTSTR *) lpszStrings, // array of error strings
		    NULL); // no raw data
        
        (VOID) DeregisterEventSource(hEventSource);
    }
}

// Heap for use by midl_user_allocate and midl_user_free.
HANDLE RpcHeap;

/*
    MIDL allocate() and free()
*/

VOID __RPC_FAR * __RPC_API midl_user_allocate(size_t len) {
    return(HeapAlloc(RpcHeap, 0, len));
}

VOID __RPC_API midl_user_free(VOID __RPC_FAR * ptr) {
    if(ptr != NULL) {
        HeapFree(RpcHeap, 0, ptr);
    }
}

// end Service.c
