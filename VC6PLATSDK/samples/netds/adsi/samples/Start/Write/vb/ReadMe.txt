//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Write VB Sample: Setting Properties Using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Write sample sets various single-valued and multi-valued properties of
an Active Directory object.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Write.Bas
  *  Write.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory.

To build and run this sample
  1.  Open the project Write.Vbp.
  2.  Open the module Write.Bas.
  3.  Replace the domain name, organizational unit, and user name with
      appropriate values in the following line.
        Set usr = GetObject("LDAP://CN=Jane Johnson,OU=DSys,  _
                             DC=Fabrikam,DC=com")
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an
error dialog appears that describes an error.

The sample sets and commits the properites of the specified user.  You can
verify the result by opening and examining the Active Directory Users and
Computers snap-in of the Microsoft Management Console.

How the Sample Works
====================
The sample uses the LDAP: ADsPath to perform the bindings and the
IADsUser interface to set the givenName, sn, and otherTelephone properties
of the selected user.

See Also
========
IADsUser interface
LDAP ADsPath
LDAP Binding String (ADsPath)
