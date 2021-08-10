//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Delete VB Sample: Deleting an Object with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Delete sample deletes a new local user account.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Delete.Bas
  *  Delete.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to the domain controller.

To build and run this sample
  1.  Open the project Create.Vbp.
  2.  Open the module Create.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain name,
      such as Fabrikam, in the following line.
        Set cont = GetObject("WinNT://INDEPENDENCE")
  4.  Create, or verify that a user account "JeffSmith" exists in the domain.
  5.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an error
dialog appears that describes an error.

The sample deletes the user "JeffSmith".  You can verify the result by opening
and examining the Active Directory Users and Computers snap-in of the Microsoft
Management Console.

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the
IADsContainer interface to delete the user.

See Also
========
IADsContainer interface
WinNT ADsPath
WinNT Binding String (ADsPath)

