//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Computer VB Sample: Creating a Computer Account in Active Directory
//
//--------------------------------------------------------------------------

Description
===========
The Computer sample uses ADSI with the LDAP provider to create a domain
account for a computer.

The sample uses a well-known GUID to bind to the Computers container of
a domain.  It sets the sAMAccountName, password, and other attributes of
the new computer object.  It also modifies the object's security descriptor
to allow a specified trustee full access to the object.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Computer.Frm
  *  Computer.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory.

To build and run this sample
  1.  Open the project Computer.Vbp.
  2.  Open the code for the Computer.Frm form.
  3.  Edit the following lines to include the appropriate computer name,
      domain name, and user name.
        sComputer = "myMachine"
        sUserOrGroup = "MyDomain\MyUserName"
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, a blank dialog appears.  Otherwise,
a dialog appears with text indicating an error.  

The sample creates a computer with the name you specify in the Computers
group.  You can verify the result by opening and examining the Active
Directory Users and Computers snap-in in the Microsoft Management Console.

See Also
========
IADs interface

