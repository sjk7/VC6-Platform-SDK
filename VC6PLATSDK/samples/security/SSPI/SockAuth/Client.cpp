/*++

Copyright (c) Microsoft Corporation. All rights reserved.

Module Name:

    client.cpp

Abstract:

    A command line app that establishes an authenticated connection
   with a server.

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
#define BIG_BUFF           2048
#define SMALL_BUFF         256

BOOL ConnectAuthSocket (SOCKET *s);
BOOL CloseAuthSocket (SOCKET s);
BOOL DoAuthentication (SOCKET s);

static PBYTE g_pInBuf = NULL;
static unsigned short g_usPort = 2000;
static TCHAR g_szPackageName[SMALL_BUFF];
static BOOL  g_fUseConfidentiality = FALSE;
static BOOL  g_fUseIntegrity = FALSE;
static TCHAR g_szServer[SMALL_BUFF] = "";
static TCHAR g_szTarget[SMALL_BUFF] = "";
static TCHAR * g_pTarget = NULL;
static BOOL  g_fVerbose;


void Usage(void)
{

   printf ("usage: client -s<server> [ <options> ]\n");
   printf ("\n");
   printf ("    -h              show usage\n");
   printf ("    -s<server>      name of server. (required)\n");
   printf ("    -t<targetname>  SPN or security context of server account (req. for Negotiate/Kerb).\n");
   printf ("    -p<package>     name of security package.\n");
   printf ("    -c              message confidentiality (encryption).\n");
   printf ("    -i              message integrity (signing).\n");
   printf ("    -v              verbose mode.\n");
   printf ("\n");
   printf ("  example: client -swinbase -pnegotiate -c\n");

}

void main(int argc, char *argv[])
{

   SOCKET s;
   DWORD  cbRead;
   BYTE   Data[BIG_BUFF];
   PCHAR  pMessage;

   int    i;
   int    iOption;
   char   *pszOption;

   if(argc <= 1)
   {
      Usage();
      return;
   }

   // default package is negotiate
   //
   lstrcpy(g_szPackageName, "Negotiate");

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

      case 's':
	     lstrcpyn(g_szServer, pszOption, SMALL_BUFF);
         break;

      case 't':
         lstrcpyn(g_szTarget, pszOption, SMALL_BUFF);
         g_pTarget = g_szTarget;  
         break;

      case 'p':
	     lstrcpyn(g_szPackageName, pszOption, SMALL_BUFF);
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
         printf("**** Invalid option \"%S\"\n", argv[i]);
         Usage();
         return;

      }

   }

   if(!lstrcmp(g_szServer,""))
   {
      Usage();
      return;
   }

   // initialize
   //
   if (!InitWinsock ())
      exit (EXIT_FAILURE);

   if (!InitPackage (g_szPackageName, g_fVerbose))
      exit (EXIT_FAILURE);

   g_pInBuf = (PBYTE) malloc (SOCKET_BUFF_SIZE);
   
   if (NULL == g_pInBuf)
      exit (EXIT_FAILURE);

   // connect to server
   //
   if (!ConnectAuthSocket (&s))
   {
      exit (EXIT_FAILURE);
   }

   if (!ReceiveBytes (s, Data, BIG_BUFF, &cbRead) || (cbRead == 0))
   {
      printf("No response from server, authentication most likely failed\n");
   }
   else
   {
      printf ("Authentication Succeeded!\n");

      // display the results
      //
      if(g_fUseConfidentiality)
      {
         pMessage = (PCHAR) DecryptThis (s, Data, &cbRead);
      }
      else if(g_fUseIntegrity)
      {
         pMessage = (PCHAR) VerifyThis (s, Data, &cbRead);
      }
      else
         pMessage = (PCHAR) Data;

      printf ("Connected to server as user: %.*s", cbRead, pMessage);
   }

   printf ("\n");

   // terminate
   //
   CloseAuthSocket (s);

   TermPackage ();

   TermWinsock ();

   if(g_pInBuf)
      free (g_pInBuf);

   exit (EXIT_SUCCESS);
}

BOOL ConnectAuthSocket (SOCKET *s)
/*++

 Routine Description:

    Establishes an authenticated socket connection with a server and
   initializes any needed security package resources.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   SOCKET sockServer;
   unsigned long ulAddress;
   struct hostent *pHost;
   SOCKADDR_IN sin;
   DWORD dwRes;

   // lookup the address for the server name
   //
   ulAddress = inet_addr (g_szServer);
   if (INADDR_NONE == ulAddress) {
      pHost = gethostbyname (g_szServer);
      if (NULL == pHost) {
         dwRes = GetLastError ();
         fprintf (stderr, "Unable to resolve host name: %u\n", dwRes);
         return(FALSE);
      }

      memcpy((char FAR *)&ulAddress, pHost->h_addr, pHost->h_length);
   }

   // create the socket
   //
   sockServer = socket (PF_INET, SOCK_STREAM, 0);
   if (INVALID_SOCKET == sockServer) {
      fprintf (stderr, "Unable to create socket: %u\n", GetLastError ());
      return(FALSE);
   }

   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = ulAddress;
   sin.sin_port = htons (g_usPort);

   // connect to remote endpoint
   //
   if (connect (sockServer, (LPSOCKADDR) &sin, sizeof (sin))) {
      fprintf (stderr, "connect failed: %u\n", GetLastError ());
      closesocket (sockServer);
      return(FALSE);
   }

   // Make this an authenticated connection
   //
   if (!InitSession (sockServer)) {
      closesocket (sockServer);
      return(FALSE);
   }

   if (!DoAuthentication (sockServer)) {
      closesocket (sockServer);
      return(FALSE);
   }

   *s = sockServer;

   return(TRUE);
}

BOOL CloseAuthSocket (SOCKET s)
/*++

 Routine Description:

    Closes a socket and releases security resources associated with
   the socket

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   TermSession (s);
   shutdown (s, 2);
   closesocket (s);
   return(TRUE);
}  

BOOL DoAuthentication (SOCKET s)
/*++

 Routine Description:

    Manges the authentication conversation with the server via the
    supplied socket handle.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
   BOOL done = FALSE;
   DWORD cbOut = 0;
   DWORD cbIn = 0;
   ULONG attrib = 0;
   PBYTE pOutBuf = NULL;

   
   if (g_fUseConfidentiality)
      attrib |= ISC_REQ_CONFIDENTIALITY;

   if (g_fUseIntegrity)
      attrib |= ISC_REQ_INTEGRITY;

   cbOut = 0;

   if (!GenClientContext (s, NULL, 0, &pOutBuf, &cbOut, &done, &attrib, g_pTarget))
      return(FALSE);

   if (!SendMsg (s, pOutBuf, cbOut))
      return(FALSE);

   // done with package allocated buffer - free it
   if(pOutBuf)
      FreeContextBuffer(pOutBuf);
   
   while (!done) {

      if (!ReceiveMsg (s, g_pInBuf, SOCKET_BUFF_SIZE, &cbIn))
         return(FALSE);

      cbOut = 0;
      pOutBuf = NULL;

      if (!GenClientContext (s, g_pInBuf, cbIn, &pOutBuf, &cbOut, &done, &attrib, g_pTarget))
         return(FALSE);

      if (!SendMsg (s, pOutBuf, cbOut))
         return(FALSE);

      // done with package allocated buffer - free it
      if(pOutBuf)
         FreeContextBuffer(pOutBuf);
      
   }

   if(g_fVerbose)
      printf("Context Attributes = 0x%08x\n", attrib);

   // check the context flags and make sure we got what we want
   //
   if (g_fUseConfidentiality && !(attrib & ISC_RET_CONFIDENTIALITY))
   {
      fprintf (stderr, "** confidentiality flags not set on context\n");
      //
      // the application can decide to either terminate the conversation or continue.
      // we are going to let the client make these decisions and continue
      //
      g_fUseConfidentiality = FALSE;
   }

   if (g_fUseIntegrity && !(attrib & ISC_REQ_INTEGRITY))
   {
      fprintf (stderr, " ** integrity flags not set on context\n");
      //
      // the application can decide to either terminate the conversation or continue.
      // we are going to let the client make these decisions and continue
      //
      g_fUseIntegrity = FALSE;
   }

   return(TRUE);
}
