/*
    Copyright Microsoft Corp. 1992 - 2001

    File Replication Sample
    File Replication Client Utility
    
    FILE: FileRep.cpp
    
    USAGE: 
        FileRep [server name] [remote file] [local file] <options...>

    OPTIONS:
        -n network_address
        -p protocol_sequence
        -e endpoint
        -d print messages
                         
    PURPOSE: Client utility for the file replication application
    
    FUNCTIONS: main() - binds to replication server and requests
        file replication.
    
    COMMENTS:

*/

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <tchar.h>
#include <rpc.h>
#include <Ntdsapi.h>

#include "common.h"

#include "Service.h"

// header file generated by MIDL compiler
#include "FileRepClient.h"

/*
    FUNCTION: PrintUsage()

    PURPOSE: Prints help information.

    PARAMETERS:
        ProgName - name of the executable

    RETURN VALUE:
        none

    COMMENTS:
*/
void PrintUsage(TCHAR *ProgName) {
    _tprintf(TEXT("%s - File Replication Client Utility\n\n"), ProgName);
    _tprintf(TEXT("Usage: %s [server name] [remote file] [local file] <options...> \n\n"), ProgName);
    _tprintf(TEXT("Options:\n"));
    _tprintf(TEXT(" -p protocol_sequence\n"));
    _tprintf(TEXT(" -n network_address\n"));
    _tprintf(TEXT(" -e endpoint\n"));
    _tprintf(TEXT(" -d print messages\n"));
}

/*
    FUNCTION: main()

    PURPOSE: Main funciton for the utility.  It binds to the local server
        and requests file replication.

    PARAMETERS:
        dwArgc - number of command line arguments
        lpszArgv - array of command line arguments

    RETURN VALUE:
        none

    COMMENTS:

*/
INT _cdecl main(int argc, char **argv) {

    INT i;
    RPC_STATUS rpcstatus;

    // Controlls printing out of messages.
    BOOL bDebug = FALSE;

    // Explicit binding handle to the client system service.
    handle_t hFileRepClient = NULL;

    // These are the default values for extablishing connections.
    // Default connection is to a local server over local rpc.
    LPTSTR pszProtocolSequence = TEXT("ncalrpc");
    LPTSTR pszNetworkAddress = NULL;

    // An empty endpoint string is used, since we are going to
    // connect to the endpoint dynamically generated by the
    // RPC run-time library.  Server calls RpcServerUseProtseq to
    // obtain a binding hadnle and a dynamic endpoint.
    LPTSTR pszEndpoint = TEXT("");

    LPTSTR pszUuid = NULL;
    LPTSTR pszOptions = NULL;
    LPTSTR pszStringBinding = NULL;

    LPTSTR ServerName = NULL;
    LPTSTR RemoteFileName = NULL;
    LPTSTR LocalFileName = NULL;

    INT nNumArgs;

    // Quality of service structure to ensure authentication.
    RPC_SECURITY_QOS SecurityQOS;

    // Used in generating the principal name for the local system service.
    TCHAR Name[128];
    DWORD cbName = sizeof(Name);
    TCHAR DomainName[128];
    DWORD cbDomainName = sizeof(DomainName);
    SID_NAME_USE Use;
    SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
    BYTE sidBuffer[100];
    PSID pSID = (PSID)&sidBuffer;

    // Get a common handle on the command line arguments for both 
    // UNICODE and ASCII
#ifdef _UNICODE
    LPWSTR *szArgList = CommandLineToArgvW(GetCommandLine(), &nNumArgs);
    if (NULL == szArgList) {
        _tprintf(TEXT("FileRep main: CommandLineToArgW failed"));
        exit(EXIT_FAILURE);
    }
#else
    char **szArgList = argv;
    nNumArgs = argc;
#endif

    // Check that the correct number of arguments is given.
    if(nNumArgs<4){
        PrintUsage(szArgList[0]);
        exit(EXIT_FAILURE);
    }

    // Extract the required arguments.
    ServerName = szArgList[1];
    RemoteFileName = szArgList[2];
    LocalFileName = szArgList[3];

    // Allow the user to override settings with command line switches.
    for (i = 4; i < nNumArgs; i++) {
        // Well-formed argument switches start with '/' or '-' and are
        // two characters long.
        if (((*szArgList[i] == TEXT('-')) || (*szArgList[i] == TEXT('/'))) && _tcsclen(szArgList[i]) == 2) {

            switch (_totlower(*(szArgList[i]+1))) {

                case TEXT('p'):

                    // Override protocol sequence.

                    // Check that the next argument exists and is not a
                    // switch.
                    if(i+1 < nNumArgs && *szArgList[i+1] != TEXT('-') && *szArgList[i+1] != TEXT('/')) {
                        pszProtocolSequence = szArgList[++i];
                    }
                    // Otherwise we have an empty protocol sequence.
                    else {
                        // We do not allow an empty protocol sequence.
                        _tprintf(TEXT("Protocol sequence can't be \"\".\n"));
                        exit(EXIT_FAILURE);
                    }
                    
                    break;
                    
                case TEXT('n'):

                    // Override the network address.
                    if(i+1 < nNumArgs && *szArgList[i+1] != TEXT('-') && *szArgList[i+1] != TEXT('/')) {
                        pszNetworkAddress = szArgList[++i];
                    }
                    else {
                        pszNetworkAddress = TEXT("");
                    }
                    
                    break;
                    
                case TEXT('e'):

                    // Override the endpoint.
                    if(i+1 < nNumArgs && *szArgList[i+1] != TEXT('-') && *szArgList[i+1] != TEXT('/')) {
                        pszEndpoint = szArgList[++i];
                    }
                    else {
                        pszEndpoint = TEXT("");
                    }
                    
                    break;
                    
                case TEXT('d'):
                    // Turn on debugging.
                    bDebug = TRUE;
                    break; 
                    
                case TEXT('h'):
                case TEXT('?'):
                default:
                    PrintUsage(szArgList[0]);
                    exit(EXIT_SUCCESS);
            }
        }
        else {
            PrintUsage(szArgList[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Concatenate the elements of
    // the string binding into the proper sequence.
    rpcstatus = RpcStringBindingCompose(pszUuid,
                                        pszProtocolSequence,
                                        pszNetworkAddress,
                                        pszEndpoint,
                                        pszOptions,
                                        &pszStringBinding);
    if(bDebug){
        _tprintf(TEXT("RpcStringBindingCompose returned 0x%x\n"), rpcstatus);
        _tprintf(TEXT("pszStringBinding = %s\n"), pszStringBinding);
    }
    RPC_EEINFO_EXIT_IF_FAIL(rpcstatus, TEXT("RpcStringBindingCompose"));

    // Set the binding handle that will be used to bind to the server.
    rpcstatus = RpcBindingFromStringBinding(pszStringBinding, &hFileRepClient);
    if(bDebug) _tprintf(TEXT("RpcBindingFromStringBinding returned 0x%x\n"), rpcstatus);
    RPC_EEINFO_EXIT_IF_FAIL(rpcstatus, TEXT("RpcBindingFromStringBinding"));

    // Free the binding string.
    rpcstatus = RpcStringFree(&pszStringBinding);
    ASSERTE(rpcstatus == RPC_S_OK);

    // Specify quality of service parameters.
    SecurityQOS.Version = RPC_C_SECURITY_QOS_VERSION;
    SecurityQOS.Capabilities = RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH;
    // Dynamic identity tracking is more efficient for a single LRPC call.
    SecurityQOS.IdentityTracking = RPC_C_QOS_IDENTITY_DYNAMIC;
    // The client system service needs to impersonate the security context
    // of the client utility on the remote systems where it may replicate
    // files from.
    // We need to impersonate with level delegate, since the server system
    // service will need to impersonate the user further.
    SecurityQOS.ImpersonationType = RPC_C_IMP_LEVEL_DELEGATE;

    // Generate the principal name for the local system service.
    // We can't just use the a string constant, because then
    // we rely on a particular English-language representation of the
    // principal.

    if (AllocateAndInitializeSid(&SIDAuth, 1,
                                 SECURITY_NETWORK_SERVICE_RID,
                                 0, 0, 0, 0, 0, 0, 0,
                                 &pSID) == 0) {
        printf("AllocateAndInitializeSid failed\n");
        exit(EXIT_FAILURE);
    }

    if (LookupAccountSid(NULL, // name of local or remote computer
                         pSID, // security identifier
                         Name, // account name buffer
                         &cbName, // size of account name buffer
                         DomainName, // domain name
                         &cbDomainName, // size of domain name buffer
                         &Use) == 0) { // SID type
        printf("LookupAccountSid failed\n");
        exit(EXIT_FAILURE);
    }

    if(bDebug) _tprintf(TEXT("Server \"magic name\" is %s\n"), Name);

    // Set authentication and authorisation information for
    // the binding handle.
    // By speciying NULL for the 5th parameter we use the security login
    // context for the current address space.
    // The security level is "PRIVACY" since it is the only level
    // provided by LRPC.
    // We are assured of talking to a local service running with 
    // system privileges.
    rpcstatus = RpcBindingSetAuthInfoEx(hFileRepClient, Name, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_AUTHN_WINNT, NULL, NULL, &SecurityQOS);
    RPC_EEINFO_EXIT_IF_FAIL(rpcstatus, TEXT("RpcBindingSetAuthInfo"));

    // Make the RPC to request file replication.
    RpcTryExcept {
        if(bDebug) _tprintf(TEXT("Calling the remote procedure RequestFile(hFileRepClient, %s, %s, %s)\n"), ServerName, RemoteFileName, LocalFileName);

        RequestFile(hFileRepClient, ServerName, RemoteFileName, LocalFileName);
        
        if(bDebug) _tprintf(TEXT("RequestFile() finished\n"));
    }
    // Return "non-fatal" errors.  Catching fatal errors
    // makes it harder to debug.
    RpcExcept ( ( (RpcExceptionCode() != STATUS_ACCESS_VIOLATION) &&
                  (RpcExceptionCode() != STATUS_DATATYPE_MISALIGNMENT) &&
                  (RpcExceptionCode() != STATUS_PRIVILEGED_INSTRUCTION) &&
                  (RpcExceptionCode() != STATUS_ILLEGAL_INSTRUCTION) &&
                  (RpcExceptionCode() != STATUS_BREAKPOINT))
                  ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH ) {
     
	    PrintProcFailureEEInfo(TEXT("RequestFile"), RpcExceptionCode()); 
        exit(EXIT_FAILURE);
    }
    RpcEndExcept;

    // Free the binding.
    rpcstatus = RpcBindingFree((VOID **)&hFileRepClient);
    ASSERTE(rpcstatus == RPC_S_OK);
    
    if(bDebug) _tprintf(TEXT("Success!\n"));
    
    return(EXIT_SUCCESS);

} // end main()

/*
    MIDL allocate() and free()
*/

VOID __RPC_FAR * __RPC_API midl_user_allocate(size_t len) {
    return(AutoHeapAlloc(len));
}

VOID __RPC_API midl_user_free(VOID __RPC_FAR * ptr) {
    if(ptr != NULL) {
        AutoHeapFree(ptr);
    }
}

// end FileRep.cpp
