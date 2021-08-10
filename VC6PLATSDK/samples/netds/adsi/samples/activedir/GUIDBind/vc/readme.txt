//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  GuidBind VC Sample: GUID Binding in Active Directory
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

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  ADSIHelpers.Cpp
  *  ADSIHelpers.h
  *  GuidBind.Dsp
  *  GuidBind.Dsw
  *  Main.Cpp
  *  makefile

Building the Sample
===================
When you build this sample using Visual Studio, be sure that you have the
INCLUDE directory for the Platform SDK set first in the Options list of
include files.

To build this sample
  1.  Open the workspace GuidBind.Dsw.
  2.  From the Build menu, select Build.

You can also build this sample at a command prompt using the supplied
makefile.

Running the Sample
==================
To run this sample
  1.  Open a command prompt and change to the directory where you built
      the sample.
  2.  Type the command "GuidBind.exe".
  3.  At the prompt, enter the ADsPath to an object to bind to.

You can also run the sample by selecting Execute GuidBind.exe from the
Build menu.

Example Output
==============
Running the sample produces the following output.  For this example
the input ADsPath was "LDAP://cn=Test User,cn=Users,dc=fabrikam,dc=com".

This code binds to a directory object by ADsPath, retrieves the GUID,
 then rebinds by GUID.

Specify the ADsPath of the object to bind to :
LDAP://cn=Test User,cn=Users,dc=fabrikam,dc=com
Binding to LDAP://cn=Test User,cn=Users,dc=fabrikam,dc=com
 The GUID for
LDAP://cn=Test User,cn=Users,dc=fabrikam,dc=com
is
29a396ba0f015e4db6fb7adc3de3a348

Successfully RE bound to
LDAP://cn=Test User,cn=Users,dc=fabrikam,dc=com
Using the path:
LDAP://<GUID=29a396ba0f015e4db6fb7adc3de3a348>

The value of the GUID will differ for different domains and users.

How the Sample Works
====================
The sample binds to the specified object using the IADs interface,
determines the GUID of the object, and rebinds to the object
using an ADsPath of the form "LDAP://<GUID=value>".

See Also
========
IADs interface
Reading an Object's objectGUID and Creating a String Representation of the GUID
Using objectGUID to Bind to an Object
