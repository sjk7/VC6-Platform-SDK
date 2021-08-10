/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992 - 2000
                      Cluuid Example

    FILE:       cluuids.c

    USAGE:      cluuids  -p protocol_sequence
                         -e endpoint
                         -m max calls
                         -n min calls
                         -f flag for RpcServerListen
                         -1 client object uuid
                         -2 manager epv uuid

    PURPOSE:    Server side of RPC distributed application hello

    FUNCTIONS:  main() - registers server as RPC server

    COMMENTS:   Print "hello, world" on the server.
                When you supply a type UUID, the client must
                supply the same UUID.

****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cluuid.h"    // header file generated by MIDL compiler

// the second implementation of the remote procedure
extern void HelloProc2(unsigned char * pszString);

#define PURPOSE \
"This Microsoft RPC Version 2.0 sample program demonstrates how\n\
to supply multiple implementations of the remote procedure\n\
specified in the interface. It also demonstrates how the client\n\
selects among the implementations by providing a client object uuid.\n\n"

#define NULL_UUID_STRING "00000000-0000-0000-0000-000000000000"

void Usage(char * pszProgramName)
{
    fprintf(stderr, "%s", PURPOSE);
    fprintf(stderr, "Usage:  %s\n", pszProgramName);
    fprintf(stderr, " -p protocol_sequence\n");
    fprintf(stderr, " -e endpoint\n");
    fprintf(stderr, " -m maxcalls\n");
    fprintf(stderr, " -n mincalls\n");
    fprintf(stderr, " -f flag_wait_op\n");
    fprintf(stderr, " -1 client uuid\n");
    fprintf(stderr, " -2 manager uuid\n");
    exit(1);
}

/* main:  register the interface, start listening for clients */
void __cdecl main(int argc, char * argv[])
{
    RPC_STATUS status;
    UUID MgrTypeUuid, ClientUuid;
    unsigned char * pszProtocolSequence = "ncacn_np";
    unsigned char * pszSecurity         = NULL;
    unsigned char * pszClientUuid       = NULL_UUID_STRING;
    unsigned char * pszMgrTypeUuid      = "11111111-1111-1111-1111-111111111111";
    unsigned char * pszEndpoint         = "\\pipe\\cluuid";
    unsigned int    cMinCalls           = 1;
    unsigned int    cMaxCalls           = 20;
    unsigned int    fDontWait           = FALSE;
    int i;

    cluuid_SERVER_EPV epv2;    // the mgr_epv for the 2nd implementation

    /* allow the user to override settings with command line switches */
    for (i = 1; i < argc; i++) {
        if ((*argv[i] == '-') || (*argv[i] == '/')) {
            switch (tolower(*(argv[i]+1))) {
            case 'p':  // protocol sequence
                pszProtocolSequence = argv[++i];
                break;
            case 'e':
                pszEndpoint = argv[++i];
                break;
            case 'm':
                cMaxCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'n':
                cMinCalls = (unsigned int) atoi(argv[++i]);
                break;
            case 'f':
                fDontWait = (unsigned int) atoi(argv[++i]);
                break;
            case '1':
                pszMgrTypeUuid = argv[++i];
                break;
            case '2':
                pszClientUuid = argv[++i];
                break;
            case 'h':
            case '?':
            default:
                Usage(argv[0]);
            }
        }
        else
            Usage(argv[0]);
    }

    status = RpcServerUseProtseqEp(pszProtocolSequence,
                                   cMaxCalls,
                                   pszEndpoint,
                                   pszSecurity);  // Security descriptor
    printf("RpcServerUseProtseqEp returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    status = UuidFromString(pszClientUuid, &ClientUuid);
    printf("UuidFromString returned 0x%x = %d\n", status, status);
    if (status) {
        exit(status);
    }

    status = UuidFromString(pszMgrTypeUuid, &MgrTypeUuid);
    printf("UuidFromString returned 0x%x = %d\n", status, status);
    if (status) {
        exit(status);
    }
    if (strcmp (pszMgrTypeUuid, NULL_UUID_STRING) == 0) {
        printf("Register object using non-null uuid %s\n", pszMgrTypeUuid);
        exit(1);
    }

    if (strcmp (pszClientUuid, NULL_UUID_STRING) == 0) {
        printf("Register object using non-null uuid %s\n", pszMgrTypeUuid);
        ClientUuid = MgrTypeUuid;
    }

    RpcObjectSetType(&ClientUuid, &MgrTypeUuid);  // associate type UUID with nil UUID
    printf("RpcObjectSetType returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    status = RpcServerRegisterIf(cluuid_ServerIfHandle, // interface to register
                                 NULL,   // MgrTypeUuid
                                 NULL);  // MgrEpv; null means use default
    printf("RpcServerRegisterIf returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    /* register the second manager epv and associate it with the
       specified uuid.  the second uuid must be non-null so that
       it will not conflict with the NULL uuid already registered
       for this interface
    */
    epv2.HelloProc = HelloProc2;
    epv2.Shutdown = Shutdown;
    status = RpcServerRegisterIf(cluuid_ServerIfHandle, // interface to register
                                 &MgrTypeUuid,  // MgrTypeUuid
                                 &epv2);        // 2nd manager epv
    printf("RpcServerRegisterIf returned 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf("Calling RpcServerListen\n");
    status = RpcServerListen(cMinCalls,
                             cMaxCalls,
                             fDontWait);
    printf("RpcServerListen returned: 0x%x\n", status);
    if (status) {
        exit(status);
    }

    if (fDontWait) {
        printf("Calling RpcMgmtWaitServerListen\n");
        status = RpcMgmtWaitServerListen();  //  wait operation
        printf("RpcMgmtWaitServerListen returned: 0x%x\n", status);
        if (status) {
            exit(status);
        }
    }

} // end main()


/*********************************************************************/
/*                 MIDL allocate and free                            */
/*********************************************************************/

void __RPC_FAR * __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}


/* end file cluuids.c */
