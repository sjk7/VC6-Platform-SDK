//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  OtherWko VB Sample: Using otherWellKnownObjects for Rename-Safe Binding
//
//--------------------------------------------------------------------------

Description
===========
The OtherWko sample shows how to use the otherWellKnownObjects property of
a container to store a reference to a child object in the container.  The
reference contains a GUID that identifies the child object and the current
DN of the child object.

If the child object is moved or renamed, Active Directory automatically
updates the DN component of the otherWellKnownObjects value.  The sample
also shows how to use the GUID to bind to the child object.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  OtherWkGUID.Bas
  *  OtherWko.Vpb

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory.

To build and run this sample
  1.  Open the project OtherWko.Vpb.
  2.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, a series of dialogs appears with text
describing the execution of the sample.  The series of text messages, for
the fabrikam.com domain, are the following.

The DN for the container is: CN=MyWKOTestContainer,DC=fabrikam,DC=com
The DN for the subcontainer is: CN=MyWKOTestSubContainer,
   CN=MyWKOTestContainer,DC=fabrikam,DC=com
We have successfully bound to object
   CN=MyWKOTestSubContainer,CN=MyWKOTestContainer,DC=fabrikam,DC=com using the WKGUID
We have successfully bound to the newly moved object: CN=MyNewSubContainer,
   CN=MyWKOTestContainer,DC=fabrikam,DC=com using the WKGUID
 
If an error occurs when you run the sample, an error dialog appears that
describes the error.

How the Sample Works
====================
The sample defines two functions.

  Main
    Binds to the default Naming Context of the current Windows 2000 domain
      using the IADs interface.
    Creates a container named MyWKOTestContainer using the IADsContainer
      interface.
    Creates a child container object named MyWKOTestObject within the
      created container using the IADsContainer interface.
    Calls the AddValueToOtherWKOProperty function.
    Binds to the child container object using WKGUID binding string and
      the IADs interface.
    Renames the child container object using WKGUID binding string.
    Rebinds to the child container object using WKGUID binding string.
  AddValueToOtherWKOProperty
    Adds the GUID string, its length, and the DN of the the child container
    object to the otherWellKnownObject property of the container.
    

See Also
========
IADs interface
IADsContainer interface
Enabling Rename-Safe Binding with the otherWellKnownObjects Property

