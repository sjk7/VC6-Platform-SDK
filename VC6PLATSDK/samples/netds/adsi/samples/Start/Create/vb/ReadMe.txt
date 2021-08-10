//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Create VB Sample: Creating a Local User Account
//
//--------------------------------------------------------------------------

Description
===========
The Create sample creates a new local user account.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Create.Bas
  *  Create.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to the domain controller.

To build and run this sample
  1.  Open the project Create.Vbp.
  2.  Open the module Create.Bas.
  3.  Replace the domain name with the appropriate domain name, such as
      Fabrikam, in the following line.
        Set cont = GetObject("WinNT://seyitb-dev")
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, a dialog appears with the text
"User Created Successfully!!!".  Otherwise, an error dialog appears that
describes an error.

The sample creates a user "JohnD" with the full name "John Doe" and the
password "myPaswrd3".  You can verify the result by opening and examining
the Active Directory Users and Computers snap-in of the Microsoft Management
Console.

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the bindings and the
IADsContainer interface to create the user.

See Also
========
Creating a User
IADsContainer interface
WinNT ADsPath
WinNT Binding String (ADsPath)

