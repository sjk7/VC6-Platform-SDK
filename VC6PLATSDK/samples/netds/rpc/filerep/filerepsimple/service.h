#pragma once
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

// Name of the executable
#define APPNAME "FileRepService"

// Internal name of the service
#define SERVICENAME "FileRepService"

// Displayed name of the service
#define SERVICEDISPLAYNAME "File Replication Service"

// List of service dependencies
#define DEPENDENCIES "RPCSS\0\0"

#ifdef PROF
#include "Prof.h"
#endif

/*
    These are prototypes for shared service functions.
    See function definitions in Service.c for help.
*/

BOOL ReportStatusToSCMgr(SERVICE_STATUS_HANDLE *sshStatusHandle,
			 SERVICE_STATUS *ssStatus,
			 DWORD dwCurrentState,
			 DWORD dwWin32ExitCode,
			 DWORD dwWaitHint);

VOID AddToMessageLog(LPTSTR lpszMsg);

// The initial size of the RPC heap
#define RPC_HEAP_SIZE_INIT (1024*1024)
#define RPC_HEAP_SIZE_MAX (128*1024*1024)

// Heap for use by midl_user_allocate and midl_user_free.
extern HANDLE RpcHeap;

// end Service.h
