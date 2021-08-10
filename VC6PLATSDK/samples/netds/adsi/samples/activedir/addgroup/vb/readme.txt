//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  AddGroup VB Sample: Adding a group to Active Directory
//
//--------------------------------------------------------------------------

Description
===========
The AddGroup sample adds a group to the Users group in Active Directory.

The sample uses the IADsContainer interface to create the group and the
IADs interface to set properties for the group.  The sample specifies
whether the group is a local, global, or universal group,  It also
specifies whether the new group is a distribution group, such as an email
distribution list, or a security group for use in access-control entries
(ACEs).

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  AddGroup.Bas
  *  AddGroup.Vpb

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory.

To build and run this sample
  1.  Open the project AddGroup.Vpb.
  2.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an
error dialog appears that describes an error.

The sample creates a group named "My New Group" in the Users group.  You
can verify the result by opening and examining the Active Directory Users
and Computers snap-in of the Microsoft Management Console.

How the Sample Works
====================
The sample defines the following subroutines.

  main
    Uses the IADs interface to determine the default Naming Context
    and calls the CreateGroup function.
  CreateGroup
    Uses the IADsContainer interface to create a group and uses the
    IADsGroup interface to set its properties.

See Also
========
IADs interface
IADsContainer interface
IADsGroup interface
Creating Groups in a Domain

