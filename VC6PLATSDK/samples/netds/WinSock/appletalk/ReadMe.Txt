THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) Microsoft Corporation.  All Rights Reserved.

AppleTalk PAP Protocol Sample
-----------------------------

The PRPERF sample is a Windows Socket application that demonstrates how to 
use the AppleTalk PAP Protocol. Both a server and a client application are 
included in the source for this sample. The client application reads a file 
and sends the contents to the server application. The server writes the 
bytes received to another file.

Supported OS:

  Windows NT, Windows 2000

Building:

  Using the Windows 2000 Build environment (either debug or release) in the 
  latest Platform SDK, build the sample via the MAKEFILE included by 
  running NMAKE in the directory.
  
Usage:

  This sample illustrates how to use the AppleTalk PAP and ADSP protocol. 
  This sample either acts as a sender or receiver. If acting as the receiver use 
  the -z -t and -n options to specify the zone, type, and object name of your 
  receiver (server). If acting as the sender specify the -s options and 
  the -z -t and -n options refer to the name of the AppleTalk endpoint to 
  connect to (i.e. the receiver). The -n -t -z options specify in string format 
  the AppleTalk Server Name, AppleTalk type name, and AppleTalk zone respectively.
  These three options together specify the AppleTalk endpoint to connect to (or 
  setup for listen) and are specific to the AppleTalk network the computer is on.
  
  Note that AppleTalk is not a routable protocol and on machines that are 
  multihomed (i.e. have more than one network interface card), only one interface
  can be setup to receive incoming AppleTalk connections. This option can
  be enabled or disabled in the Network Connection manager folder. That is, open
  the Network Connections folder and right click on the desired interface and 
  choose properties. From the new dialog select the AppleTalk protocol and
  choose the Properties button.

  The following is a list of all the options and defaults when available:

     -s/c     Server/Client (is this a server or client?) (required)
     -n       AppleTalk Server Name (default = "Windows Adsp")
     -t       AppleTalk Server Type (default = "Windows Sockets")
     -z       AppleTalk Server Zone (default = *)
     -p       Protocol Name (ADSP/PAP) (default = ADSP)
     -b       Number of times to send a 4k buffer (Default = 5)
     -l       Number of times to re-start prperf (Default = 1) (Client only)
     -v       Verify Integrity of data transmission
     -y       Change ADSP to use SOCK_RDM instead of SOCK_STREAM

