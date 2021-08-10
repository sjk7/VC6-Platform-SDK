//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  NDS VB Sample: Accessing Novell NDS Server using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The NDS sample illustrates how to access an NDS server through ADSI using
Visual Basic.

This sample uses the NDS: provider and requires a server providing Novell
NetWare Directory Services (NDS).

Sample Files
============
  *  NDS.Bas
  *  NDS.Vbp
  *  NDS.Vbw

Building and Running the Sample
===============================
Before you run this sample, you must install the Gateway and Client
Services for Netware.  See the topic "Setting Up Gateway and Client
Services for Netware" in the Platform SDK.

To build and run this sample
  1.  Open the project NDS.Vbp.
  2.  Open the module NDS.Bas.
  3.  Enter an appropriate server name, user name, and password values
      to replace those in the following lines.
        serverName = "ntmarst2"
        userName = "supervisor.ntmarst2"
        password = "secretpwd"
  4.  Replace the server name and the common name of a user with appropriate
      values in the following line.
        Path = "O=NTMARST2/CN=benny"
  5.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints to the Immediate Window.
  *  First it enumerates all the objects in the NDS ADsPath.
  *  Then it prints the surname of the specified user and changes it.
  *  Then it creates a new user and uses ActiveX Data Objects (ADO) to
     search for the new user an enumerate all of its properties.

Otherwise, an error dialog appears that describes an error.

How the Sample Works
====================
The sample uses the NDS ADsPath to perform the binding and ADO to search
for properites of a specified user.

See Also
========
NDS ADsPath
Searching with ActiveX Data Objects (ADO)
Setting Up Gateway and Client Services for Netware
Using ADSI with NDS Providers
