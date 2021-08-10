//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  BindtoParent VB Sample: Binding to an Object's Parent
//
//--------------------------------------------------------------------------

Description
===========
The BindtoParent sample uses ADSI to bind to the local domain partition in
Active Directory.  It then searches for a specified user object.  When it
finds the object, the sample binds to the parent of that object, which is the
container of the user object in the Active Directory hierarchy.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  BindParent.Vbp
  *  BindtoParent.Bas

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project BindParent.Vbp.
  2.  Open the module BindToParent.Bas.
  3.  Edit the following line to include the Common Name of the desired user
        strUserCommonName = "Bugs Bunny"
  4.  From the Run menu, select Start.

If the sample executes successfully, a dialog appears with the text
"The Parent for <Selected User> is CN=Users, DC=fabrikam, DC=com".

Otherwise, a dialog appears with the text "Did not find exactly one record
for <Selected User> Exiting".

How the Sample Works
====================
The sample uses ActiveX Data Objects (ADO) to search for the selected user.

See Also
========
IADs interface
IADsUser interface
Searching with ActiveX Data Objects (ADO)
