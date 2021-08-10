//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Move VB Sample: Moving an Object Using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Move sample moves an object from one container to another by moving
a user from one organizational unit to another.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Move.Bas
  *  Move.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory

To build and run this sample
  1.  Open the project Move.Vbp.
  2.  Open the module Move.Bas.
  3.  Replace the destination organizational unit with an existing one,
      such as "OU=Another Example Org Unit" in the following line.
        Set cont = GetObject("LDAP://OU=DSys,DC=Fabrikam,DC=com")
  4.  Create a user named "Mike Smith" in a source organizational
      unit, such as "OU=Example Org Unit", in the domain and change the
      organizational unit in the following line.
        Set usr = cont.MoveHere("LDAP://CN=Mike Smith,OU=MCS,  _
                                DC=Fabrikam,DC=com", vbNullString)
  5.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an
error dialog appears that describes an error.

The sample moves the specified user from the source to the destination
organizational unit.  You can verify the result by opening and examining
the Active Directory Users and Computers snap-in of the Microsoft Management
Console.

How the Sample Works
====================
The sample uses the LDAP: ADsPath to perform the bindings and the
IADsContainer interface to perfrom the move.

See Also
========
IADsContainer interface
LDAP ADsPath
LDAP Binding String (ADsPath)

