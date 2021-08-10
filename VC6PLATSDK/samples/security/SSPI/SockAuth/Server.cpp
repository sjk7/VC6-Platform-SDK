/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    server.cpp

Abstract:

    A command line app that establishes an authenticated connection
   with a client.

Revision History:

--*/

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "security.h"
#include "comm.h"
#define SECURITY_WIN32
#include "sspi.h"


#define SOCKET_BUFF_SIZE   65536
#define SMALL_BUFF         256

BOOL AcceptAuthSocket (SOCKET *s);
BOOL CloseAuthSocket (SOCKET *s);
BOOL DoAuthentication (SOCKET s);

static PBYTE g_pInBuf = NULL;
static DWORD g_cbMaxMessage = 0;
static unsigned short g_usPort = 2000;
static TCHAR g_lpPackageName[SMALL_BUFF];
static BOOL  g_fUseConfidentiality = FALSE;
static BOOL  g_fUseIntegrity = FALSE;
static BOOL  g_fVerbose = FALSE;

void Usage(void)
{

   printf ("usage: server [ <options> ]\n");
   printf ("\n");
   printf ("    -h              show usage\n");
   printf ("    -p<package>     name of security package (default = negotiate).\n");
   printf ("    -c              message confidentiality (encryption).\n");
   printf ("    -i              message integrity (signing).\n");
   printf ("    -v              verbose mode.\n");
   printf ("\n");
   printf ("  example: server -pnegotiate -c\n");

}

void main (int argc, char *argv[])
{
   PCHAR pMessage = NULL;
   DWORD cbMessage = 0;
   PBYTE pDataToClient = NULL;
   DWORD cbDataToClient = 0;
   PCHAR pUserName = NULL;
   DWORD cbUserName = 0;
   SOCKET s = 0;

   int    i;
   int    iOption;
   char   *pszOption = NULL;

   printf("\nUse \"%s /h\" to see the options for this sample application\n\n",
      argv[0]);

   // default package is negotiate
   //
   lstrcpy(g_lpPackageName, "Negotiate");

   for(i = 1; i < argc; i++) 
   {
      if(argv[i][0] == '/') argv[i][0] = '-';

      if(argv[i][0] != '-') 
      {
         printf("**** Invalid argument \"%s\"\n", argv[i]);
         Usage();
         return;
      }
      iOption = argv[i][1];
      pszOption = &argv[i][2];

      switch(iOption) 
      {
      case 'h':
         Usage();
         return;

      case 'p':
         lstrcpyn(g_lpPackageName, pszOption, 1024);
         break;

      case 'c':
         g_fUseConfidentiality = TRUE;
         break;

      case 'i':
         g_fUseIntegrity = TRUE;
         break;

      case 'v':
         g_fVerbose = TRUE;
         break;

      default:
         printf("**** Invalid option \"%s\"\n", argv[i]);
         Usage();
         return;

      }

   }

   // initialize
   //
   if (!InitWinsock ())
      goto cleanup;

   if (!InitPackage (g_lpPackageName, g_fVerbose))
      goto cleanup;

   g_pInBuf = (PBYTE) malloc (SOCKET_BUFF_SIZE);
   
   if (NULL == g_pInBuf) 
      goto cleanup;

   //
   // Start looping for clients
   //
   while(TRUE)
   {

      printf("Waiting for client to connect...\n");

      // Make an authenticated connection with client
      //
      if (!AcceptAuthSocket (&s))
         goto endsession;

      // impersonate the client
      //
      if (!ImpersonateContext (s))
         goto endsession;

      GetUserName (NULL, &cbUserName);
      pUserName = (PCHAR) malloc (cbUserName);

      if (!pUserName)
         goto cleanup;

      if (!GetUserName (pUserName, &cbUserName))
         goto cleanup;

      // display the user name
      //
      printf ("Client connected as user %s\n", pUserName);

      // revert to self
      //
      if (!RevertContext (s))
         goto cleanup;

      //
      // Send back the client's username
      //
      cbMessage = cbUserName;
      pMessage = pUserName;

      // do the appropriate operation as the context attributes indicate
      //
      if(g_fUseConfidentiality)
      {
         EncryptThis (
            s, 
            (PBYTE) pMessage,
            cbMessage,
            &pDataToClient, 
            &cbDataToClient
            );    
      }

      else 
      {
         // only sign if we didn't encrypt
         //
         if(g_fUseIntegrity)
         {
            SignThis (
               s, 
               (PBYTE) pMessage,
               cbMessage,
               &pDataToClient, 
               &cbDataToClient
               );
         }

         // do the default and just send the raw message
         //
         else
         {
            pDataToClient = (PBYTE) malloc(cbMessage);
            memcpy(pDataToClient, pMessage, cbMessage);
            cbDataToClient = cbMessage;
         }

      }


endsession:

      // send data to client
      //
      if (!SendBytes (s, pDataToClient, cbDataToClient))
         goto cleanup;


      if (s)
      {
         CloseAuthSocket (&s);
         s = 0;
      }

      if (pUserName)
      {
         free (pUserName);
         pUserName = NULL;
         cbUserName = 0;
      }

      if(pDataToClient)
      {
         free (pDataToClient);
         pDataToClient = NULL;
         cbDataToClient = 0;
      }

      g_fUseConfidentiality = 0;
      g_fUseIntegrity =0;

      printf("\n");

   }

cleanup:

   if (g_pInBuf)
      free (g_pInBuf);

   TermPackage ();

   TermWinsock ();


}

BOOL AcceptAuthSocket (SOCKET *s)
/*++

 Routine Description:

    Establishes an authenticated socket connection with a client and
   initializes any needed security package resources.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SOCKET sockListen;
   SOCKET sockClient;
   SOCKADDR_IN sin;
   int nRes;

   // create listening socket
   //
   sockListen = socket (PF_INET, SOCK_STREAM, 0);
   if (INVALID_SOCKET == sockListen)  {
      fprintf (stderr, "Failed to create socket: %u\n", GetLastError ());
      return(FALSE);
   }

   // bind to local port
   //
   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = 0;
   sin.sin_port = htons(g_usPort);
   nRes = bind (sockListen, (LPSOCKADDR) &sin, sizeof (sin));
   if (SOCKET_ERROR == nRes)  {
      fprintf (stderr, "bind failed: %u\n", GetLastError ());
      return(FALSE);
   }

   // listen for client
   //
   nRes = listen (sockListen, 1);
   if (SOCKET_ERROR == nRes)  {
      fprintf (stderr, "listen failed: %u\n", GetLastError ());
      return(FALSE);
   }

   // accept client
   //
   sockClient = accept (sockListen, NULL, NULL);
   if (INVALID_SOCKET == sockClient)  {
      fprintf (stderr, "accept failed: %u\n", GetLastError ());
      return(FALSE);
   }

   closesocket (sockListen);

   // return socket even if we fail next steps
   //
   *s = sockClient;

   if (!InitSession (sockClient))
      return(FALSE);

   if (!DoAuthentication (sockClient))
      return(FALSE);

   return(TRUE);
}  

BOOL CloseAuthSocket (SOCKET *s)
/*++

 Routine Description:

    Closes a socket and releases security resources associated with
   the socket

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   TermSession (*s);
   shutdown (*s, 2);
   closesocket (*s);
   *s = 0;
   return(TRUE);
}  

BOOL DoAuthentication (SOCKET s)
/*++

 Routine Description:

    Manages the authentication conversation with the client via the
    supplied socket handle.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   DWORD cbIn, cbOut;
   BOOL done = FALSE;
   ULONG attrib = 0;
   PBYTE pOutBuf = NULL;
   
   if (g_fUseConfidentiality)
      attrib |= ASC_REQ_CONFIDENTIALITY;

   if (g_fUseIntegrity)
      attrib |= ASC_REQ_INTEGRITY;

   do {
      if (!ReceiveMsg (
         s, 
         g_pInBuf, 
         g_cbMaxMessage, 
         &cbIn))

         return(FALSE);
      
      pOutBuf = NULL;

      if (!GenServerContext (
         s, 
         g_pInBuf, 
         cbIn, 
         &pOutBuf, 
         &cbOut, 
         &done, 
         &attrib))

         return(FALSE);
      
      if (!SendMsg (s, pOutBuf, cbOut))
         return(FALSE);

      // done with package allocated buffer - free it
      if(pOutBuf)
         FreeContextBuffer(pOutBuf);

   }
   while(!done);

   if(g_fVerbose)
      printf("Context Attributes = 0x%08x\n", attrib);

   // check the context flags and see if we got what we want
   //
   if (g_fUseConfidentiality && !(attrib & ASC_RET_CONFIDENTIALITY))
   {
      fprintf (stderr, "** confidentiality flags not set on context\n");
      
      // The application can decide to either terminate the conversation 
      // or continue. We are going to let the client make these decisions 
      // and continue.
      //
      g_fUseConfidentiality = FALSE;
   }

   if (g_fUseIntegrity && !(attrib & ASC_RET_INTEGRITY))
   {
      fprintf (stderr, " ** integrity flags not set on context\n");
      
      // The application can decide to either terminate the conversation 
      // or continue. We are going to let the client make these decisions 
      // and continue.
      //
      g_fUseIntegrity = FALSE;
   }

   // or the client could have requested the context flags and the package obliged
   //
   g_fUseConfidentiality = (attrib & ASC_RET_CONFIDENTIALITY);

   g_fUseIntegrity = (attrib & ASC_RET_INTEGRITY);


   return(TRUE);
}  
