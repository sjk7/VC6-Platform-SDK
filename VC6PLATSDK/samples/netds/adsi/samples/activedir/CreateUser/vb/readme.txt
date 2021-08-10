//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  CreateUser VB Sample: Creating a User Account in Active Directory
//
//--------------------------------------------------------------------------

Description
===========
The CreateUser sample uses ADSI with the LDAP provider to create a domain
account for a user.  The sample displays a user interface to collect values
for the various properties of a user account.

The sample sets mandatory properties such as sAMAccountName as well as
additional optional properties.  The sample uses the IADsContainer, IADsUser,
and IADs interfaces to create and initialize the user object.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Create_User.Bas
  *  CreateUser.Vpb
  *  frmAcctProps.Frm
  *  frmSetNames.Frm

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

You must run this sample in a Windows domain where you have permission to
write to Active Directory.

To build and run this sample
  1.  Open the project CreateUser.Vpb.
  2.  From the Run menu, select Start.

The sample sequentially displays two dialogs where you enter properties
for the account of the user to create.

Example Output
==============
If the sample executes successfully, a dialog appears with the text
"User <specified user name> has been successfully created".  Otherwise,
an error dialog appears that describes an error.

The sample creates a user with the name you specify in the Users group.
You can verify the result by opening and examining the Active Directory
Users and Computers console.

How the Sample Works
====================
The sample defines one code module and two forms.

  Create_User.Bas
    Uses the IADs interface to determine the default Naming Context
    and other properties of the domain and displays the frmSetNames
    and frmAcctProps forms.  It uses the IADs, IADsContainer, and IADsUser
    interfaces to create the user account.
  frmAcctProps.Frm
    Sets the password and password properties for the user.
  frmSetNames.Frm
    Sets the DN, SAM, and UPN names for the user.

See Also
========
Creating a User
IADs interface
IADsContainer interface
IADsUser interface


