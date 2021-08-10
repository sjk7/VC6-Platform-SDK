//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  WKGUID VB Sample: Using Well-Known GUIDs
//
//--------------------------------------------------------------------------

Description
===========
The WKGUID sample uses the well-known GUID of the Users container to bind
to the Users container in the default naming context.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  WKGUID.Bas
  *  WKGUID.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project WKGUID.Vbp.
  2.  From the Run menu, select Start.

A dialog appears with the text
 "The distinguished name for the Users Container is:
  CN=Users,DC=fabrikam, DC=com"
when run in the Fabrikam.Com domain.

How the Sample Works
====================
You can also use well-known GUIDs to bind to other well-known containers,
such as the Computers container.  The complete list includes:

  *  GUID_USERS_CONTAINER_W
  *  GUID_COMPUTRS_CONTAINER_W
  *  GUID_SYSTEMS_CONTAINER_W
  *  GUID_DOMAIN_CONTROLLERS_CONTAINER_W
  *  GUID_INFRASTRUCTURE_CONTAINER_W
  *  GUID_DELETED_OBJECTS_CONTAINER_W
  *  GUID_LOSTANDFOUND_CONTAINER_W

See Also
========
IADs interface
Binding to Well-Known Objects Using WKGUID

