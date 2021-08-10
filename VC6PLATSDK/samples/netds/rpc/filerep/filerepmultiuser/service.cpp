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

    COMMENTS:

        These funtions may be used by the main service routines
      as well as by the client and server file replication RPC routines.

    IMPORTANT:

        Counter and Queueing code provides the necessary functionality for
      the service and is strictly a sample.  It does not demonstrate how to queue
      user requests properly and write high-performance servers.  The purpose of this
      sample is demostration of RPC features and the following code is refined to
      the extent it allows us to accomplish that.

*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <lm.h>

#include "common.h"

#include "Service.h"

#ifdef DEBUG
#include "DbgMsg.h"
#endif

// We support anonymous, regular, and system
// user groups.
const UINT NumPriGroups = 3;

#ifdef LARGE_RES_BOUNDS

// The maximum number of requests
// that can be placed by anonymous, regular,
// and system accounts respectively on the server.
const UINT ServerReqBounds[] =  {1000, 2000, 3000};

// Equivalent bounds on the client.
const UINT ClientReqBounds[] =  {1000, 2000, 3000};

// The maximum number of requests that can be
// simultaneously handled on the client.
const UINT ClientActiveReqBounds[] =  {100, 500, 1000};

const UINT MaxUserReqs = 1000;

#else

const UINT ServerReqBounds[] =  {10, 20, 30};

const UINT ClientReqBounds[] =  {10, 20, 30};

const UINT ClientActiveReqBounds[] =  {1, 5, 10};

const UINT MaxUserReqs = 5;

#endif

Counter *pServerReqCounters[NumPriGroups];
Counter *pClientReqCounters[NumPriGroups];
Counter *pClientActiveReqCounters[NumPriGroups];

Queue *ClientReqQueues[NumPriGroups];
Queue *ClientActiveReqHashQueues[NumPriGroups];
Queue *ClientActiveReqHashCounters[NumPriGroups];

const UINT RegUsersPri = 1;

/*
  
    FUNCTION: GetUserSid
    
    PURPOSE: Obtains a pointer to the SID for the current user

    PARAMETERS:
        none

    RETURN VALUE:
        Pointer to the SID

    COMMENTS:
        The SID buffer returned by this function is allocated with
        HeapAlloc and should be freed with HeapFree.

*/
PSID GetUserSID() {
    SID_NAME_USE snuType;
    PSID pUserSID = NULL;
    DWORD cbUserSID = 0;

    LPTSTR szUserName = NULL;
    DWORD cbUserName = 0;

    LPTSTR szDomainName = NULL;
    DWORD cbDomainName = 0;

    BOOL fAPISuccess;

#ifdef DEBUG
    TCHAR Msg[MSG_SIZE];

    DbgMsgRecord(TEXT("->GetUserSID\n"));
#endif

    // Get the logged on user name.  First we determine the size
    // of the buffer required and then get the username.

    // Get the size of the name.
    fAPISuccess = GetUserName(szUserName, &cbUserName);

    // API should have failed with insufficient buffer.
    ASSERTE(!fAPISuccess);

#ifdef DEBUG
    _stprintf(Msg, TEXT("GetUserSID: cbUserName=%d\n"), cbUserName);
    DbgMsgRecord(Msg);
#endif

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        AddToMessageLogProcFailure(TEXT("GetUserSID: GetUserName"), GetLastError());
        return NULL;
    }

    // Allocate buffer for the name.
    szUserName = (LPTSTR) AutoHeapAlloc(cbUserName * sizeof(TCHAR));
    if (szUserName == NULL) {
        AddToMessageLog(TEXT("GetUserSID: AutoHeapAlloc failed"));
        return NULL;
    }
   
    // Finally get the name.
    fAPISuccess = GetUserName(szUserName, &cbUserName);
    if (!fAPISuccess) {
        AutoHeapFree(szUserName);
        AddToMessageLogProcFailure(TEXT("GetUserSID: GetUserName"), GetLastError());
        return NULL;
    }

#ifdef DEBUG
    _stprintf(Msg, TEXT("GetUserSID: UserName=%s cbUserName=%d\n"), szUserName, cbUserName), 
    DbgMsgRecord(Msg);
#endif
   
    // Do the same for SID.  First get the size and then allocate the buffer
    // and perform the actual call.
    fAPISuccess = LookupAccountName(NULL, szUserName,
                                    pUserSID, &cbUserSID, szDomainName, &cbDomainName, &snuType);
   
    // API should have failed with insufficient buffer.
    ASSERTE(fAPISuccess);

#ifdef DEBUG
    _stprintf(Msg, TEXT("GetUserSID: cbUserSID=%d\n"), cbUserSID), 
    DbgMsgRecord(Msg);
#endif

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
        AutoHeapFree(szUserName);
        AddToMessageLogProcFailure(TEXT("GetUserSID: LookupAccountName"), GetLastError());
        return NULL;
    }
   
    // Allocate the SID buffer...
    pUserSID = AutoHeapAlloc(cbUserSID);
    if (pUserSID == NULL) {
        AutoHeapFree(szUserName);
        AddToMessageLog(TEXT("GetUserSID: AutoHeapAlloc failed"));
        return NULL;
    }
   
    // And the domain name buffer.
    szDomainName = (LPTSTR) AutoHeapAlloc(cbDomainName * sizeof(TCHAR));
    if (!szDomainName) {
        AutoHeapFree(szUserName);
        AutoHeapFree(pUserSID);
        AddToMessageLog(TEXT("GetUserSID: AutoHeapAlloc failed"));
        return NULL;
    }
   
    // Now get the SID.
    fAPISuccess = LookupAccountName(NULL, szUserName,
                                    pUserSID, &cbUserSID, szDomainName, &cbDomainName, &snuType);
    if (!fAPISuccess) {
        AutoHeapFree(szUserName);
        AutoHeapFree(szDomainName);
        AutoHeapFree(pUserSID);
        AddToMessageLogProcFailure(TEXT("GetUserSID: LookupAccountName"), GetLastError());
        return NULL;
    }

    AutoHeapFree(szUserName);
    AutoHeapFree(szDomainName);

#ifdef DEBUG
    _stprintf(Msg, TEXT("GetUserSID: pUserSID=%p cbUserSID=%d\n"), pUserSID, cbUserSID), 
    DbgMsgRecord(Msg);
#endif

#ifdef DEBUG
    DbgMsgRecord(TEXT("<-GetUserSID\n"));
#endif

    return pUserSID;
}

/*
  
    FUNCTION: GetUserGroups
    
    PURPOSE: Obtains a pointer to the groups that current
    token is member of.

    PARAMETERS:
        none

    COMMENTS:
        The PTOKEN_GROUPS pointer returned by this function is allocated with
        HeapAlloc and should be freed with HeapFree.

*/
PTOKEN_GROUPS GetUserGroups(VOID) {
    DWORD dwSize;
    DWORD dwResult;
    HANDLE hToken;
    PTOKEN_GROUPS pGroupInfo = NULL;
   
#ifdef DEBUG
    DbgMsgRecord(TEXT("->GetUserGroups\n"));
#endif

    // Open a handle to the access token for the calling thread.
    if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, TRUE, &hToken)) {
        AddToMessageLogProcFailure(TEXT("GetUserGroups: OpenProcessToken"), GetLastError());
        return NULL;
    }

    // Call GetTokenInformation to get the buffer size.
    dwSize = 0;
    if(GetTokenInformation(hToken, TokenGroups, NULL, dwSize, &dwSize) == 0) {
        dwResult = GetLastError();
        if(dwResult != ERROR_INSUFFICIENT_BUFFER ) {
            AddToMessageLogProcFailure(TEXT("GetUserGroups: GetTokenInformation"), dwResult);

            CloseHandle(hToken);
            return NULL;
        }
    }
    else {
        // We should have returned with an error above.
        ASSERTE(TRUE);
    }

    // Allocate the buffer.
    if ((pGroupInfo = (PTOKEN_GROUPS) AutoHeapAlloc(dwSize)) == NULL) {
        AddToMessageLog(TEXT("GetUserGroups: AutoHeapAlloc failed"));

        CloseHandle(hToken);
        return NULL;
    }

    // Call GetTokenInformation again to get the group information.
    if(GetTokenInformation(hToken, TokenGroups, pGroupInfo, dwSize, &dwSize) == 0) {
        AddToMessageLogProcFailure(TEXT("GetUserGroups: GetTokenInformation"), GetLastError());

        AutoHeapFree(pGroupInfo);
        CloseHandle(hToken);
        return NULL;
    }
    
#ifdef DEBUG
    DbgMsgRecord(TEXT("<-GetUserGroups\n"));
#endif

    CloseHandle(hToken);
    return pGroupInfo;
}

/*
  
    FUNCTION: IsGroupMember
    
    PURPOSE: Returns true if a given SID is found in a given group.

    PARAMETERS:
        pSID - sid to look for.
        pGroupInfo - group to look in.

*/
BOOL IsGroupMember(PSID pSID, PTOKEN_GROUPS pGroupInfo) {

#ifdef DEBUG
    DbgMsgRecord(TEXT("->IsGroupMember\n"));
#endif

    // Loop through the group SIDs looking for the administrator SID.
    for(UINT i=0; i<pGroupInfo->GroupCount; i++) {
        if (EqualSid(pSID, pGroupInfo->Groups[i].Sid)) {
            // Find out if the SID is enabled in the token
            if (pGroupInfo->Groups[i].Attributes & SE_GROUP_ENABLED) {

#ifdef DEBUG
                DbgMsgRecord(TEXT("<-IsGroupMember\n"));
#endif
                return TRUE;
            }
        }
    }

#ifdef DEBUG
    DbgMsgRecord(TEXT("<-IsGroupMember\n"));
#endif

    return FALSE;
}

PSID pSystemSID = NULL;
PSID pAdminSID = NULL;
PSID pAnonSID = NULL;    

VOID CreateWellKnownSids(VOID) {
    SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;

    // Generate SID for the system if necessary.
    if (pSystemSID == NULL) {
        if (AllocateAndInitializeSid(&SIDAuth, 1,
                                     SECURITY_LOCAL_SYSTEM_RID,
                                     0, 0, 0, 0, 0, 0, 0,
                                     &pSystemSID) == 0) {
            AddToMessageLogProcFailure(TEXT("CreateWellKnownSids: AllocateAndInitializeSid"), GetLastError());
        }
    }

    // Generate SID for the admin group if necessary.
    if (pAdminSID == NULL) {
        if (AllocateAndInitializeSid(&SIDAuth, 1,
                                     DOMAIN_ALIAS_RID_ADMINS,
                                     0, 0, 0, 0, 0, 0, 0,
                                     &pAdminSID) == 0) {
            AddToMessageLogProcFailure(TEXT("CreateWellKnownSids: AllocateAndInitializeSid"), GetLastError());
        }
    }

    // Generate the anonymous SID if necessary.
    if (pAnonSID == NULL) {
        if (AllocateAndInitializeSid(&SIDAuth, 1,
                                     SECURITY_ANONYMOUS_LOGON_RID,
                                     0, 0, 0, 0, 0, 0, 0,
                                     &pAnonSID) == 0) {
            AddToMessageLogProcFailure(TEXT("CreateWellKnownSids: AllocateAndInitializeSid"), GetLastError());
        }
    }
}

VOID DeleteWellKnownSids(VOID) {
    AutoHeapFree(pSystemSID);
    pSystemSID = NULL;
    AutoHeapFree(pAdminSID);
    pAdminSID = NULL;
    AutoHeapFree(pAnonSID);
    pAnonSID = NULL;
}

/*
    FUNCTION: GetCurrentUserPriority()

    PURPOSE: Returns the priority of the current user.
        Priority is an integer between 0 and 2.
        0 - anonymous users
        1 - regular users
        2 - system

    PARAMETERS:
        pPri - pointer to the variable that receives the priority. 

    RETURN VALUE:  True on success, False on error.

    COMMENTS:  Returns 0 on errors.

*/
UINT GetCurrentUserPriority(VOID) {
    PSID pSID;
    PTOKEN_GROUPS pUserGroups;

    UINT Pri;

    // If well-known sids were not allocated, we can't work.
    if (pSystemSID == NULL || pAdminSID == NULL || pAnonSID == NULL) {
        return 0;
    }

    // The SID gets dynamically allocated inside GetUserSID(), so
    // we need to remember about that.
    if ((pSID = GetUserSID()) == NULL) {
        return 0;
    }

    if ((pUserGroups = GetUserGroups()) == NULL) {
        AutoHeapFree(pSID);
        return 0;
    }

    // Test if current SID is system SID or it
    // is a member of the administrator group.
    if (EqualSid(pSID, pSystemSID) || IsGroupMember(pAdminSID, pUserGroups)) {
        // Return system priority.
        Pri = 2;
    }
    // Test if current SID is anonyous SID.
    else if (EqualSid(pSID, pAnonSID)) {
        // Return anonymous priority.
        Pri = 0;
    }
    else {
        // We are left with the regular user priority.
        Pri = 1;
    }

    AutoHeapFree(pSID);
    AutoHeapFree(pUserGroups);
    return Pri;
}

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

    if (dwCurrentState == SERVICE_START_PENDING) {
        ssStatus->dwControlsAccepted = 0;
    }
    else {
        ssStatus->dwControlsAccepted = SERVICE_ACCEPT_STOP;
    }
    
    ssStatus->dwCurrentState = dwCurrentState;
    ssStatus->dwWin32ExitCode = dwWin32ExitCode;
    ssStatus->dwWaitHint = dwWaitHint;
    
    if ((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED)) {
        ssStatus->dwCheckPoint = 0;
    }
    else {
        ssStatus->dwCheckPoint = dwCheckPoint++;
    }
    
    // Report the status of the service to the service control manager.
    if (!(fResult = SetServiceStatus(*sshStatusHandle, ssStatus))) {
        AddToMessageLog(TEXT("ReportStatusToSCMgr: SetServiceStatus failed"));
    }
    return fResult;
}

/*
    FUNCTION: AddToMessageLog(LPTSTR lpszMsg)

    PURPOSE: Allows any thread to log an error message.
      Messages are logged in a simplistic manner with some
      fields omitted.

    PARAMETERS:
        lpszMsg - text for message

    RETURN VALUE:
        none

    COMMENTS:

*/
VOID AddToMessageLog(LPTSTR szMsg2) {
    TCHAR szMsg1[256];
    HANDLE hEventSource;
    LPTSTR lpszStrings[2];
    DWORD dwErr = 0;

    dwErr = GetLastError();
    
    // Use event logging to log the error.
    hEventSource = RegisterEventSource(NULL, SERVICENAME);
    
    _stprintf(szMsg1, TEXT("%s error: %d"), SERVICENAME, dwErr);
    lpszStrings[0] = szMsg1;
    lpszStrings[1] = szMsg2;
    
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

VOID AddToMessageLogProcFailure(LPTSTR ProcName, DWORD ErrCode) {
    TCHAR Msg[MSG_SIZE];
    _stprintf(Msg, TEXT("%s failed with code %d"), ProcName, ErrCode);
    AddToMessageLog(Msg);
}

VOID AddToMessageLogProcFailureEEInfo(LPTSTR ProcName, DWORD ErrCode) {
    TCHAR Msg[MSG_SIZE];
    UINT MsgSize = 0;

    MsgSize += _stprintf(&Msg[MsgSize], TEXT("%s failed with code %d\n"), ProcName, ErrCode);
    GetEEInfoText(Msg, MSG_SIZE, &MsgSize);

    Msg[MsgSize] = 0;

    AddToMessageLog(Msg);
}

VOID AddRpcEEInfo(DWORD Status, LPTSTR Msg) {
    RPC_STATUS rpcstatus;

    RPC_EXTENDED_ERROR_INFO ErrorInfo;

    ErrorInfo.Version = RPC_EEINFO_VERSION;
    ErrorInfo.ComputerName = NULL;
    ErrorInfo.ProcessID = 0;
    ErrorInfo.GeneratingComponent = 0;
    ErrorInfo.Status = Status;
    ErrorInfo.DetectionLocation = 0;
    ErrorInfo.Flags = 0;
    ErrorInfo.NumberOfParameters = 1;
    ErrorInfo.Parameters[0].ParameterType = eeptUnicodeString;
    ErrorInfo.Parameters[0].u.UnicodeString = Msg;

    rpcstatus = RpcErrorAddRecord(&ErrorInfo);

    RpcRaiseException(Status);
}

VOID AddRpcEEInfoAndRaiseException(DWORD Status, LPTSTR Msg) {
    AddRpcEEInfo(Status, Msg);
    RpcRaiseException(Status);
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

// end Service.cpp
