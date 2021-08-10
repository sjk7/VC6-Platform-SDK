//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Netscape VB Sample: Accessing Netscape Directories using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Netscape sample illustrates how to access a Netscape directory through
ADSI using Visual Basic.

This sample uses the LDAP: provider and requires a server providing Netscape
directory services.

Sample Files
============
  *  Netscape.Bas
  *  Netscape.Vbp
  *  Netscape.Vbw

Building and Running the Sample
===============================
Before you run this sample, you must install a Netscape Server.  You need
to know the name of this server and one of its naming contexts, for example:
O=Airius.com.

To build and run this sample
  1.  Open the project Netscape.Vbp.
  2.  Open the module Netscape.Bas.
  3.  Enter an appropriate server name and company name values
      to replace those in the following lines.
        server = "nscp01"
        company = "O=Airius.com"
  4.  Replace the user name and password values for a user with valid logon
      credentials in the following line.
        userName = "cn=directory manager"
        password = "password"
  5.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints to the Immediate Window.
  *  First it enumerates all the objects in the specified ADsPath.
  *  Then it uses ActiveX Data Objects (ADO) to search for the specified
     user and enumerates all of its properties.

Otherwise, an error dialog appears that describes an error.

How the Sample Works
====================
The sample uses the LDAP ADsPath to perform the binding and ADO to search
for properites of a specified user.

See Also
========
LDAP ADsPath
Searching with ActiveX Data Objects (ADO)

