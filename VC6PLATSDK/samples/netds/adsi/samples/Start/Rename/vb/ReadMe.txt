//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Rename VB Sample: Renaming an Object Using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Rename sample renames an Active Directory Object.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Rename.Bas
  *  Rename.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory

To build and run this sample
  1.  Open the project Rename.Vbp.
  2.  Open the module Rename.Bas.
  3.  Create an organizational unit "OU=Marketing" in a domain
      such as "DC=Fabrikam,DC=com", in the following line.
        Set cont = GetObject("LDAP://OU=Marketing,DC=Fabrikam,DC=com")
  4.  Create a user named "Jeff Smith" in the organizational unit as
      specified in the following line.
        Set usr = cont.MoveHere("LDAP://CN=Jeff Smith,OU=Marketing,  _
                                DC=Fabrikam,DC=com",  "CN=J. Smith")
  5.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an
error dialog appears that describes an error.

The sample renames the specified user in the organizational unit.  You can
verify the result by opening and examining the Active Directory Users and
Computers snap-in of the Microsoft Management Console.

How the Sample Works
====================
The sample uses the LDAP: ADsPath to perform the bindings and the
IADsContainer interface to perfrom the rename.

See Also
========
IADsContainer interface
LDAP ADsPath
LDAP Binding String (ADsPath)
