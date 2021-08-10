// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright Microsoft Corp. 1992 - 2000
//
// FILE:      AsyncRPCp.c
//
// PURPOSE:   Remote procedures that are linked with the server
//            side of RPC distributed application
//
// COMMENTS:  The Microsoft RPC AsyncRPC sample program demonstrates
//            the use of the [async] attribute and the related asynchronous
//            RPC API functions. The asynchronous function will take certain
//            amount of time to finish. In the process, it also periodically
//            checks whether the call has been cancelled by the client. 
//            For more information, see MSDN online reference.
//
// WRITTEN BY:    Mike Liu
//

#include <stdlib.h>
#include <stdio.h>
#include "AsyncRPC.h" // header file generated by MIDL compiler

const char PERCENT = '%';
const unsigned long DEFAULT_NONASYNC_DELAY     = 1000;  // in miliseconds
const unsigned long ASYNC_CANCEL_CHECK         = 500;   // in miliseconds

// Non-asynchronous routine which can be called
// by a client when an asynchronous routine is running.
void NonAsyncFunc(IN RPC_BINDING_HANDLE hBinding,
                  IN unsigned char * pszMessage)
{
   Sleep(DEFAULT_NONASYNC_DELAY);
   fprintf(stderr, "\n\nReceived (%s) via NonAsyncFunc\n\n", pszMessage);
}


// Asynchronous routine. It sends back the notification
// when it is done.
void AsyncFunc(IN PRPC_ASYNC_STATE pAsync,
               IN RPC_BINDING_HANDLE hBinding,
               IN unsigned long nAsychDelay)
{
   int nReply = 1;
   RPC_STATUS status;
   unsigned long nTmpAsychDelay;
   int i;

   if (nAsychDelay < 0)
      nAsychDelay = DEFAULT_ASYNC_DELAY;

   nAsychDelay *= 1000;  // convert to ms

   // We only call RpcServerTestCancel if the call
   // takes longer than ASYNC_CANCEL_CHECK ms
   if (nAsychDelay > ASYNC_CANCEL_CHECK)
   {
      nTmpAsychDelay = nAsychDelay/100;

      for (i = 0; i < 100; i++)
      {
         Sleep(nTmpAsychDelay);

         if (i%5 == 0)
         {
            // Report the progress of the asynchronous function
            fprintf(stderr, "\rRunning AsyncFunc (%lu ms) (%d%c) ... ",
                    nAsychDelay, i+5, PERCENT);

            // Check whether the call is cancelled by the client
            status = RpcServerTestCancel(RpcAsyncGetCallHandle(pAsync));
            if (status == RPC_S_OK)
            {
               fprintf(stderr, "\nAsyncFunc has been cancelled!!!\n");
               break;
            }
            else if (status != RPC_S_CALL_IN_PROGRESS)
            {
               printf("RpcServerTestCancel returned 0x%x\n", status);
               exit(status); 
            }
         }
      }
   }
   else
      Sleep(nAsychDelay);

   printf("\nCalling RpcAsyncCompleteCall\n");
   status = RpcAsyncCompleteCall(pAsync, &nReply);
   printf("RpcAsyncCompleteCall returned 0x%x\n", status);
   if (status)
      exit(status);
}


void Shutdown(IN RPC_BINDING_HANDLE hBinding)
{
   RPC_STATUS status;

   printf("Calling RpcMgmtStopServerListening\n");
   status = RpcMgmtStopServerListening(NULL);
   printf("RpcMgmtStopServerListening returned: 0x%x\n", status);
   if (status)
      exit(status);

   printf("Calling RpcServerUnregisterIf\n");
   status = RpcServerUnregisterIf(NULL, NULL, FALSE);
   printf("RpcServerUnregisterIf returned 0x%x\n", status);
   if (status)
      exit(status);
}
