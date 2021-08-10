//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Computer VB Sample: Binding to a Computer Using the ADSI WinNT Provider
//
//--------------------------------------------------------------------------

Description
===========
The Computer sample binds to a specified computer using ADSI and the WinNT
provider.  Then the sample demonstrates enumerating services on the
computer; displaying service properties; stopping, starting, and pausing
services; enumerating, creating, and deleting file shares on the computer;
and enumerating sessions and resources on the computer.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Computer.Bas
  *  Computer.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Computer.Vbp.
  2.  Open the module Computer.Bas.
  3.  Search for, and replace occurences of the domain name INDEPENDENCE
      with the name of the domain you want to use.
  4.  Search for, and replace occurences of the computer name SEATTLE with
      the name of the computer you want to use.
  5.  From the Run menu, select Start.

Example Output
==============
If the sample runs successfully, it prints output in the Immediate window
similar to the following for the FABRIKAMNT computer in the Fabrikam domain.

Fabrikam                            (Division)
Windows NT                          (OperatingSystem)
4.0                                 (OperatingSystemVersion)
Test User                           (Owner)
x86 Family 6 Model 8 Stepping 1     (Processor)
Uniprocessor Free                   (ProcessorCount)
Alerter  Alerter                    (Services)
Browser  Computer Browser
ClipSrv  ClipBook Server
DHCP  DHCP Client
EventLog  EventLog
LanmanServer  Server
LanmanWorkstation  Workstation
LicenseService  License Logging Service
LmHosts  TCP/IP NetBIOS Helper
Messenger  Messenger
NetDDE  Network DDE
NetDDEdsdm  Network DDE DSDM
Netlogon  Net Logon
NtLmSsp  NT LM Security Support Provider
PlugPlay  Plug and Play
ProtectedStorage  Protected Storage
Replicator  Directory Replicator
RPCLOCATOR  Remote Procedure Call (RPC) Locator
RpcSs  Remote Procedure Call (RPC) Service
Schedule  Schedule
Spooler  Spooler
TapiSrv  Telephony Service
UPS  UPS
Display Name: Computer Browser
Order Group: 
Host Name: WinNT://FABRIKAM/FABRIKAMNT
Startup: Automatic
Dependencies: 
  LanmanWorkstation
  LanmanServer
  LmHosts
Service Type: Win32 Share Process
Error Control: No Error
NETLOGON  0 C:\WINNT\system32\Repl\Import\Scripts
TestU\TESTCOMPUTER 3058
\FABRIKAMNT 241

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
then uses the following interfaces to perform the specified tasks.

  *  IADsComputer             Enumerate services
  *  IADsService              Display service properties
  *  IADsServiceOperations    Stop, start, and pause a service
  *  IADsFileShare            Create and delete a file share
  *  IADsFileService,         Enumerate sessions
     IADsSession   
  *  IADsResource             Enumerate resources

See Also
========
IADsComputer interface
IADsFileService interface
IADsFileShare interface
IADsResource interface
IADsService interface
IADsServiceOperations interface
IADsSession interface
WinNT Binding String (ADsPath)
