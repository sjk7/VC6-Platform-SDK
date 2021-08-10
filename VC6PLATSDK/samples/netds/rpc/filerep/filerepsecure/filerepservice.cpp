/*

    File Replication Sample
    Server System Service

    FILE: FileRepService.cpp
    
    PURPOSE: Provides file replication services.
    
    USAGE: 
        FileRepService

    FUNCTIONS:
        main() - calls the StartServiceCtrlDispatcher function to
            connect to the SCM and start the control dispatcher thread.
        ServiceMain() - the entry point for the service.
        ServiceCtrl() - this function is called by the dispatcher thread.
            It handles the control code passed to it.
        ServiceStart() - performs actual initialization and starts the service.
            Makes the RPC server listen for calls.
        ServiceStop() - stops listening for RPCs.

    COMMENTS:

*/

#define SECURITY_WIN32

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <rpc.h>
#include <Ntdsapi.h>
#include <Ntsecapi.h>
#include <Security.h>
#include <Secext.h>
#include <Dsgetdc.h>
#include <Lm.h>

// Generated by the MIDL compiler
#include "FileRepServer.h"
#include "FileRepClient.h"

// Contains declarations for system service functions.
#include "Service.h"

// Common definitions
#include "common.h"

/*
    Internal funtion declarations.
    See definitions for more info.
*/

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);

VOID WINAPI ServiceCtrl(DWORD Opcode);

VOID ServiceStart(DWORD dwArgc, LPTSTR *lpszArgv);

VOID ServiceStop();

/*
    Internal variables
*/

// status handle of the service
SERVICE_STATUS_HANDLE sshStatusHandle;

// current status of the service
SERVICE_STATUS ssStatus;

BOOL bServerListening = FALSE;

/*
    FUNCTION: main()

    PURPOSE: main() calls StartServiceCtrlDispatcher to register the
        main service thread.    When this call returns,
        the service has stopped.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
*/
VOID _cdecl main(int argc, char **argv){

    // Since we provide a single service there is only
    // one entry in the service dispatch table
    SERVICE_TABLE_ENTRY DispatchTable[] = {
        { SERVICENAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { NULL, NULL }
    };

    // The service control manager may be starting the service with
    // this call, so we must call StartServiceCtrlDispatcher.
    if (!StartServiceCtrlDispatcher(DispatchTable)) {
        AddToMessageLog(TEXT("StartServiceCtrlDispatcher failed"));
    }
}

/*
    FUNCTION: ServiceMain

    PURPOSE: To perform actual initialization of the client service.    It
        is the entry point into the service.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
        This routine performs the service initialization and then calls
        the user defined ServiceStart() routine to perform majority
        of the work.
*/
VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv) {

    // Initial service configuration
    ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS; 
    ssStatus.dwCurrentState = SERVICE_START_PENDING; 
    ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ssStatus.dwWin32ExitCode = 0; 
    ssStatus.dwServiceSpecificExitCode = 0; 
    ssStatus.dwCheckPoint = 0; 
    ssStatus.dwWaitHint = 0; 
    
    sshStatusHandle = RegisterServiceCtrlHandler(SERVICENAME, ServiceCtrl);

    // Tell the SCM that the service is starting up.
    if (!SetServiceStatus(sshStatusHandle, &ssStatus)) {
        AddToMessageLog(TEXT("ServiceMain: SetServiceStatus failed\n"));
        return; 
    } 
    
    // Initialize the service and start it.
    ServiceStart(dwArgc, lpszArgv);

    return; 
}

/*
    FUNCTION: ServiceCtrl

    PURPOSE: This function is called by the SCM whenever
        ControlService() is called on this service.

    PARAMETERS:
        dwCtrlCode - type of control requested

    RETURN VALUE:
        none

    COMMENTS:
*/

VOID WINAPI ServiceCtrl(DWORD Opcode) { 

    // We only handle the STOP control requsts.
    switch(Opcode) {

        case SERVICE_CONTROL_STOP: 
            // Stop the service. 
            ServiceStop();
            break;

        default: 
            AddToMessageLog(TEXT("ServiceCtrl: unrecognized or unimplemented opcode\n"));
    }

    return; 
}


/*
    RPC configuration.
*/

// The service listens to all the protseqs listed in this array.
// It listens for replication utilities on local RPC and for
// remote requests on TCP/IP
LPTSTR ServerProtocolArray[] = { TEXT("ncacn_ip_tcp"),
				 TEXT("ncalrpc") };

// Used in RpcServerUseProtseq.
// Specifies the maximum number of concurrent remote 
// procedure call requests the server wants to handle. 
ULONG cMaxCallsListen = RPC_C_PROTSEQ_MAX_REQS_DEFAULT;

// Similarly, but for RpcServerListen.
ULONG cMaxCallsExecute = RPC_C_LISTEN_MAX_CALLS_DEFAULT;

// Used in RpcServerListen().  The minnimum number of threads listening.
ULONG cMinimumThreads = 2;

RPC_BINDING_VECTOR * pBindingVector = NULL;

// Status variable for the RPC calls.
RPC_STATUS status;

/*
    FUNCTION: RpcServerIfCallback

    PURPOSE: Security callback funtion for the server interface

    PARAMETERS:
        Interface - the UUID and version of the interface.
        Context - server binding handle representing the client. 

    RETURN VALUE:
        Returns RPC_S_OK if the client is allowed to call methods in this
        interface.  A different return code will cause the client to receive
        the exception RPC_S_ACCESS_DENIED.

    COMMENTS:

        Specifying a security-callback function allows the server application
        to restrict access to its interfaces on a per-client basis.

        By default the server run time will dispatch unauthenticated calls
        even if the server has called RpcServerRegisterAuthInfo. If the
        server wants to accept only authenticated clients it must then call
        RpcBindingInqAuthClient to retrieve the security level, or attempt
        to impersonate the client with RpcImpersonateClient. 

        When a server application specifies a security-callback function
        for an interface, the RPC run time automatically rejects
        unauthenticated calls to that interface. In addition, the run-time
        records the interfaces that each client has used. When a client
        makes an RPC to an interface that it has not used during the
        current communication session, the RPC run-time library will
        call the interface's security-callback function. 

        In some cases, the RPC run time may call the security-callback
        function more than once per client, per interface.

*/
RPC_STATUS __stdcall RpcServerIfCallback (
  IN void *Interface,
  IN void *Context
) {
    ULONG ulAuthnLevel;
    ULONG ulAuthnSvc;

    // Get client security info.
    if (RpcBindingInqAuthClient(Context,
				NULL,
				NULL,
				&ulAuthnLevel,
				&ulAuthnSvc,
				NULL) != RPC_S_OK) {
      
        return RPC_S_ACCESS_DENIED;
    }

    // Make sure the client has adequate security measures and uses the expected
    // security provider.
    if (ulAuthnLevel != RPC_C_AUTHN_LEVEL_PKT_PRIVACY || ulAuthnSvc != RPC_C_AUTHN_GSS_KERBEROS) {

        return RPC_S_ACCESS_DENIED;
    }

    return RPC_S_OK;
};

/*
    FUNCTION: ServiceStart

    PURPOSE: Actual code of the service
             that does the work.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:
        Starts the service listening for RPC requests.
*/
VOID ServiceStart (DWORD dwArgc, LPTSTR *lpszArgv){

    UINT i;

    // Array of generated SPNs.
    TCHAR **Spn;
    // Number of generated SPNs.
    ULONG ulSpn = 1;

    PDOMAIN_CONTROLLER_INFO pDomainControllerInfo;

    HANDLE hDS;

    TCHAR lpCompDN[128];
    ULONG ulCompDNSize = sizeof(lpCompDN);

    // Message buffer.
    TCHAR Msg[128];

    // Report the status to the service control manager.
    if (!ReportStatusToSCMgr(&sshStatusHandle, &ssStatus, SERVICE_START_PENDING, NO_ERROR, 1000)) {
        AddToMessageLog(TEXT("ReportStatusToSCMgr failed\n"));
	ServiceStop();
        return;
    }

    // Service initialization

    // Register the service interfaces.

    // The server interface has a security callback RpcServerIfCallback.
    // The RPC run time will automatically reject unauthenticated calls to
    // this interface.
    status = RpcServerRegisterIfEx(s_FileRepServer_v1_0_s_ifspec,
				   NULL,
				   NULL,
				   RPC_IF_ALLOW_SECURE_ONLY,
				   RPC_C_LISTEN_MAX_CALLS_DEFAULT,
				   &RpcServerIfCallback);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerRegisterIf(s_FileRepServer_v1_0_s_ifspec, ...) failed\n"));
	ServiceStop();
        return;
    }

    status = RpcServerRegisterIf(FileRepClient_v1_0_s_ifspec, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerRegisterIf(FileRepClient_v1_0_s_ifspec, ...) failed\n"));
	ServiceStop();
        return;
    }

    for (i = 0; i < sizeof(ServerProtocolArray)/sizeof(unsigned char *); i++) {

        // Use the protocol sequences specified in ProtocolArray
        // for receiving RPCs.
        status = RpcServerUseProtseq((_TUCHAR *)ServerProtocolArray[i], cMaxCallsListen, NULL);
        if (status != RPC_S_OK){
            AddToMessageLog(TEXT("ServiceStart: RpcServerUseProtseq failed\n"));
	    ServiceStop();
            return;
        }
    }

    // Obtain a binding vector for the server.
    status = RpcServerInqBindings(&pBindingVector);
    if (status != RPC_S_OK) {
        AddToMessageLog(TEXT("ServiceStart: RpcServerInqBindings failed\n"));
	ServiceStop();
        return;
    }
    
    // Register the the services in the endpoint map
    // of the host computer.
    status = RpcEpRegister(s_FileRepServer_v1_0_s_ifspec, pBindingVector, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcEpRegister(s_FileRepServer_v1_0_s_ifspec, ...) failed\n"));
	ServiceStop();
        return;
    }
    status = RpcEpRegister(FileRepClient_v1_0_s_ifspec, pBindingVector, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcEpRegister(FileRepClient_v1_0_s_ifspec, ...) failed\n"));
	ServiceStop();
        return;
    }

    //
    // Set the security info for the client system service.
    //

    // Principal name is NULL for local system service.
    status = RpcServerRegisterAuthInfo(NULL, RPC_C_AUTHN_WINNT, NULL, NULL);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerRegisterAuthInfo failed"));
	ServiceStop();
        return;
    }

    //
    // Set the security info for the server system service.
    //

    BOOL NoFailure = TRUE;

    // Generate the SPN.
    status = DsGetSpn(DS_SPN_NB_HOST, // Type of SPN to create.
                      SERVICENAME, // Service class
                      NULL, // DN of this service.
                      0, // Use the default instance port.
                      0, // Number of additional instance names.
                      NULL, // No additional instance names.
                      NULL, // No additional instance ports.
                      &ulSpn, // Size of SPN array.
                      &Spn); // Returned SPN(s).
    if (status != RPC_S_OK){
        _stprintf(Msg, TEXT("ServiceStart: DsGetSpn failed with code %d\n"), status);
        AddToMessageLog(Msg);
        ServiceStop();
        return;
    }

    // Get the name of our domain.
    if (status = DsGetDcName(NULL,
                             NULL,
                             NULL,
                             NULL,
                             DS_RETURN_DNS_NAME,
                             &pDomainControllerInfo) != NO_ERROR) {
        _stprintf(Msg, TEXT("ServiceStart: DsGetDcName failed with code %d\n"), status);
        AddToMessageLog(Msg);
        NoFailure = FALSE;
    }

        if (NoFailure) {
            // Bind to the domain controller for our domain.
            if ((status = DsBind(pDomainControllerInfo->DomainName, NULL, &hDS)) != ERROR_SUCCESS) {
                _stprintf(Msg, TEXT("ServiceStart: DsBind failed with code %d\n"), status);
                        AddToMessageLog(Msg);
                        NoFailure = FALSE;
            }
        }

        if (NoFailure) {
            if ((status = NetApiBufferFree(pDomainControllerInfo)) != NERR_Success) {
                    _stprintf(Msg, TEXT("ServiceStart: NetApiBufferFree failed with code %d\n"), status);
                        AddToMessageLog(Msg);
                        ServiceStop();
                        return;
                }

            if (GetComputerObjectName(NameFullyQualifiedDN, lpCompDN, &ulCompDNSize) == 0){
            _stprintf(Msg, TEXT("ServiceStart: GetComputerObjectName failed with code %d\n"), GetLastError());
                        AddToMessageLog(Msg);
                        ServiceStop();
                        return;
                }

                // We could check whether the SPN is already registered for this
                // computer's DN, but we don't have to.  Modification is performed
                // permissively by this function, so that adding a value that already 
                // exists does not return an error.  This way we can opt for the internal
                // check instead of doing it ourselves.
        status = DsWriteAccountSpn(hDS, DS_SPN_ADD_SPN_OP, lpCompDN, ulSpn, (LPCTSTR *)Spn);
        if (status != NO_ERROR) {
            _stprintf(Msg, TEXT("ServiceStart: DsWriteAccountSpn failed with code %d\n"), status);
            AddToMessageLog(Msg);
            return;
        }
        DsUnBind(&hDS);
        }

    // We use Kerberos for authentication on the server.
    status = RpcServerRegisterAuthInfo(Spn[0], RPC_C_AUTHN_GSS_KERBEROS, NULL, NULL);
    if (status != RPC_S_OK){
        _stprintf(Msg, TEXT("ServiceStart: RpcServerRegisterAuthInfo"), status);
        AddToMessageLog(Msg);
        ServiceStop();
        return;
    }

    // Don't forget to deallocate the principal name array.
    DsFreeSpnArray(ulSpn, Spn);

    // Create the heap to be used by midl_user_allocate and midl_user_free
    RpcHeap = HeapCreate(0, RPC_HEAP_SIZE_INIT, RPC_HEAP_SIZE_MAX);
    
#ifdef PROF
    ProfOpenLog(TEXT("FileRepService.prof"));
#endif

    // Start accepting client calls.
    // The last argument's being 1 indicates that RpcServerListen
    // should return immediately after completing function processing. 
    status = RpcServerListen(cMinimumThreads, cMaxCallsExecute, 1);
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerListen failed\n"));
	ServiceStop();
        return;
    }

    bServerListening = TRUE;

    // Tell The SCM that the service is running.
    if (!ReportStatusToSCMgr(&sshStatusHandle, &ssStatus, SERVICE_RUNNING, NO_ERROR, 0)){
        AddToMessageLog(TEXT("ServiceStart: ReportStatusToSCMgr failed"));
	ServiceStop();
        return;
    }

    // End of initialization

    // RpcMgmtWaitServerListen() will block until the server has
    // stopped listening.
    status = RpcMgmtWaitServerListen();
    if (status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcMgmtWaitServerListen failed"));
	ServiceStop();
        return;
    }
    
    // Cleanup
    
    // Delete the binding vector.
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    if(status != RPC_S_OK){
        AddToMessageLog(TEXT("ServiceStart: RpcServerUnregisterIf failed"));
        return;
    }
    
    return;
}


/*
    FUNCTION: ServiceStop

    PURPOSE: Stops a service

    PARAMETERS:
        none

    RETURN VALUE:
        none

    COMMENTS:

*/        
VOID ServiceStop() {
    RPC_STATUS status;

    // Stops the server, wakes up the main thread.
    if (bServerListening) {
        status = RpcMgmtStopServerListening(NULL);
	if(status != RPC_S_OK) {
	    AddToMessageLog(TEXT("ServiceStop: RpcMgmtStopServerListening failed."));
	    return;
	}
	bServerListening = FALSE;
    }

    // Tell The SCM that the service is stopped.
    if(!ReportStatusToSCMgr(&sshStatusHandle, &ssStatus, SERVICE_STOPPED, NO_ERROR, 0)) {
        AddToMessageLog(TEXT("ServiceStop: ReportStatusToSCMgr failed"));
        return;
    }

#ifdef PROF
    ProfCloseLog();
#endif

}

// end FileRepService.cpp
