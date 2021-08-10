//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Binding VB Sample: Binding Using the ADSI WinNT Provider
//
//--------------------------------------------------------------------------

Description
===========
The Binding sample demonstrates how to bind to various objects using ADSI
and the WinNT provider.  The sample shows binding to a domain, binding to
a remote machine, and binding to a specific user within a domain.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Binding.Bas
  *  Binding.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Binding.Vbp.
  2.  Open the module Binding.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain
      name, such as FABRIKAM, in the following line.
        DomainName = "INDEPENDENCE" '--- Change the domain accordingly
  4.  Replace the computer name "adsi" with an appropriate computer
      name in the following line.
        ComputerName = "adsi"
  5.  Either
      a.  Create a user named "user1" with password "se*c*ret" in the domain
          -or-
      b.  Replace the user name "user1" and password "se*c*ret" with an
          existing user and password in the following lines.
            Set dom = dso.OpenDSObject("WinNT://" & DomainName, "user1",  _
                                       "se*c*ret", ADS_SECURE_AUTHENTICATION)
            ADsPath = "WinNT://" & DomainName & "/" & "user1"
  6.  From the Run menu, select Start.

When run in the Fabrikam domain, the sample outputs the text
"Domain Name for this computer is WinNT://FABRIKAM".

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the bindings.  The sample
includes the following cases.
  *  Binding to a domain as the current user
  *  Binding to a domain with supplied credentials
  *  Binding to a specified computer in the domain as the current user
  *  Binding to a specified computer in the domain with supplied credentials
  *  Binding to a specified user in the domain

See Also
========
WinNT ADsPath
WinNT Binding String (ADsPath)

