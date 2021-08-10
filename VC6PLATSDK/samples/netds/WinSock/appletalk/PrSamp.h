/*++

Copyright 1994 - 2000 Microsoft Corporation

Module Name: prperf.c


Abstract: This Sample Windows Socket Application demonstrates use of
          the AppleTalk PAP Protocol. Both a server and a client
          application are included in this source file. The client
          app reads a file and sends the contents to the server. The
          server writes out the received bytes to another file.


--*/

BOOL
DoServer();

BOOL
DoClient();

BOOL
OpenSocketRegisterAndListen();

unsigned long
PerfThread(LPVOID lpvTest);

BOOL
CheckForRecv(SOCKET s);

BOOL
CheckForSend(SOCKET s);

void
usage();
