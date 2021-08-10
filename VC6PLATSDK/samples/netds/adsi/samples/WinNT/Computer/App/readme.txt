//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Computer App Sample: Binding to a Computer Using the ADSI WinNT Provider
//
//--------------------------------------------------------------------------

Description
===========
The Computer sample binds to a specified computer using ADSI and the WinNT
provider.  The sample requests the user to provide logon credentials and a
domain or computer for the connection.  Then the sample displays computers
in the domain and properties, shares, sessions, and resources for the
computers.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Computer.Frm
  *  Computer.Vbp
  *  Connect.Frm
  *  Share.Frm

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Computer.Vbp.
  2.  From the Run menu, select Start.
  3.  In the "WinNT:Connect To" dialog, enter a user name and password,
      specify whether to connect to a domain or a computer, and enter
      the appropriate domain name or domain/computer name.
  4.  From the list of computers in the domain, select the desired
      computer to display its properties, shares, sessions, and resources.
  5.  In the Shares frame, select New, and in the "New Share" dialog enter
      the name and path for a new share to create.

How the Sample Works
====================
The sample defines three forms:

  frmComputer
    Binds to the domain controller and does most of the processing.
  frmConnect
    Supplies the logon credentials and domain/computer name.
  frmShare
    Supplies the name and path of a share to create on the computer.

See Also
========
IADsComputer interface
IADsComputerOperations interface
IADsContainer interface
IADsFileService interface
IADsFileShare interface
IADsOpenDSObject interface
IADsResource interface
IADsSession interface
WinNT Binding String (ADsPath)

