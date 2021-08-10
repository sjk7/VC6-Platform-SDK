//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Sites VB Sample: Creating a Site and Subnet
//
//--------------------------------------------------------------------------

Description
===========
The Sites sample binds to the Sites container in the Configuration partition
of an Active Directory forest, creates a new site object, and creates a set
of subcontainers under the site object.

The sample then creates a new subnet object in the Subnets container and
associates the new site with the new subnet.  The sample also shows how
to use the IADsDeleteOps interface to delete an object along with the
entire subtree under the object.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Sites.Bas
  *  Sites.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To run the sample, you need to have permissions, or belong to a group
that has permissions, to write to the CN=Configuration, CN=Sites
object of the domain, as well as to create and delete all child objects.

To build and run this sample
  1.  Open the project Sites.Vbp.
  2.  Open the module Sites.Bas.
  3.  Optionally, edit the following lines to change the names of the
      new site and new subnet.
        strSiteName = "MyNewSite"
        strSubnetName = "200.50.10.0/24"  ' IP Address/Bitmask
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, a series of dialogs appears with
the following messages.

  "Site created and subcontainers created!"
  "Subnet created"
  "Site and subcontainers deleted!"
  "Subnet deleted!"

Otherwise, a dialog appears with an error message.

How the Sample Works
====================
The sample uses the IADs interface to bind to the Configuration partition
of Active Directory and to get the root of the Sites container.
It defines two functions, Create_Site_And_Subnet and Destroy_Site_And_Subnet,
that use the IADsContainer and IADsDeleteOps interfaces to do the creation
and destruction.

See Also
========
IADs interface
IADsContainer interface
IADsDeleteOps
IADsDeleteOps interface


