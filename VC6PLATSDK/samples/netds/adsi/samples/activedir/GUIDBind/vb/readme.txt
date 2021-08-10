//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  GuidBind VB Sample: GUID Binding in Active Directory
//
//--------------------------------------------------------------------------

Description
===========
The GuidBind sample shows how to use a GUID to bind to an object
in Active Directory.

Every Active Directory object has an identifying GUID (its objectGUID
property) that never changes, even if the object is renamed or moved in
the Active Directory forest.  The best way to save a reference to an
Active Directory object is to use this GUID, which allows you to retrieve
the object even if it is moved or renamed.

The sample uses the IADs interface to perform the binding.

This sample uses the LDAP: and GC: providers and is suitable for Windows
2000 and later networks running Active Directory.

Sample Files
============
  *  Guid_Bind.Bas
  *  GuidBind.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project GuidBind.Vbp.
  2.  From the Run menu, select Start.
  3.  In the resulting dialog, enter the ADsPath to the desired object.

Example Output
==============
When you specify an ADsPath such as
  LDAP://cn=Test User,cn=Users,dc=fabrikam,dc=com
and the sample successfully binds to the object, you receive a dialog with
the common name of the object.  Otherwise, a dialog with an error appears.

How the Sample Works
====================
The sample defines one module, GuidBind, which initializes and binds to the
object using the IADs interface, determines the GUID of the object, and
rebinds to the object using an ADsPath of the form "GC://<GUID=value>".

See Also
========
IADs interface
Reading an Object's objectGUID and Creating a String Representation of the GUID
Using objectGUID to Bind to an Object
