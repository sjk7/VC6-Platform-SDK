/****************************************************************************
                   Microsoft RPC Version 2.0
           Copyright Microsoft Corp. 1992 - 2000
                        rpcssm Example

    FILE:       rpcssmp.c

    PURPOSE:    Remote procedures used in server application rpcssms

    FUNCTIONS:  InOutList() - Adds new nodes to the list.

    COMMENTS:   This distributed application uses the rpcssm package.

****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rpcssm.h"    // header file generated by MIDL compiler

void AllocateSmList( PBOX * ppBox, short sListSize );
void InitList( PBOX  pBox, long lStartValue );
void PrintList( PBOX pBox );

void * pvPersistent    = NULL;
void * pvNonPersistent = NULL;

void
InOutList( PBOX * ppBox )
{
    /* As this routine executes in the enabled memory environment,
       a convienient way to allocate a non-persistent memory
       is to use RpcSmAllocate or RpcSsAllocate.
    */

    if ( ppBox) {

        PBOX p = *ppBox;
        while ( p->next )
            p = p->next;

        AllocateSmList( & p->next, 2 );
    }
    else {
        AllocateSmList( ppBox, 5 );
    }

    InitList( *ppBox, 0x98760000 );
    PrintList( *ppBox );

    /* To allocate a memory to be available after the call, means other
       than RpcS*Allocate with default allocators should be used.
    */

    if ( pvPersistent == NULL )
        {
        pvPersistent = malloc(100); /* or midl_user_allocate(100) */
        }

    pvNonPersistent = RpcSsAllocate( 100 );
}

/* The Shutdown procedure tells the server to stop listening */
/* for client requests.                                      */
void Shutdown(void)
{
    RPC_STATUS status;

    /* Freeing the persistent memory */

    if ( pvPersistent )
        free( pvPersistent );

    printf("Calling RpcMgmtStopServerListening\n");
    status = RpcMgmtStopServerListening(NULL);
    printf("RpcMgmtStopServerListening returned: 0x%x\n", status);
    if (status) {
        exit(status);
    }

    printf("Calling RpcServerUnregisterIf\n");
    status = RpcServerUnregisterIf(NULL, NULL, FALSE);
    printf("RpcServerUnregisterIf returned 0x%x\n", status);
    if (status) {
        exit(status);
    }
}

//=====================================================================
//        List allocation/deallocation routines
//=====================================================================

void
AllocateSmList( PBOX * ppBox, short sListSize)
{
    PBOX    pBox, head;
    int     i = 0;

    //.. Allocate a list of boxes, if needed (when *ppBox==NULL).

    if ( *ppBox == NULL ) {

        RPC_STATUS status;

        head = 0;
        for (i = 0; i < sListSize; i++)
        {
            pBox = (PBOX) RpcSmAllocate( sizeof(LBOX), &status);
            if ( status != RPC_S_OK )
            {
                printf("AllocateList FAILED: not enough memory\n");
                break;
            }
            pBox->next = head;
            head = pBox;
        }
        *ppBox = head;
    }
    printf("%d nodes allocated.\n", i);
}

//=====================================================================
//        Initialization and pprint routines
//=====================================================================

void  InitList( PBOX  pBox, long lStartValue )
{
    int i = 0;

    while( pBox ) {
        pBox->data = lStartValue + ++i;
        pBox = pBox->next;
    }
    printf("%d nodes inited.\n", i);
}

// --------------------------------------------------------------------

void
PrintList( PBOX  pBox )
{
    int i = 0;


    while( pBox ) {

        if ( (i % 4) != 0 )
            printf("  data[%d]= %lx", i, pBox->data);
        else
            printf("\n  data[%d]= %lx", i, pBox->data);
        pBox = pBox->next;
        i++;
    }
    printf("\n" );
}


/* end file rpcssmp.c */
