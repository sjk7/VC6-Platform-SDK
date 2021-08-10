//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  UsrMgr VB Sample: Managing Users with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The UsrMgr sample is similar to the Windows NT(R) 4.0 User Manager, but has
fewer features.  The sample can:
  *  browse users, computers, and groups in a specified domain or
     on a particular computer
  *  view user and group information
  *  display user properties, including description, password, and group
     membership
  *  display group memberships and types

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Connect.Frm
  *  frMgroup.Frm
  *  frMgroupList.Frm
  *  Helper.Bas
  *  UsrMgr.Frm
  *  UsrMgr.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project UsrMgr.Vbp.
  2.  From the Run menu, select Start.
  3.  A WinNT: Connect To dialog appears in which you specify the domain
      or computer for the connection.  If you leave the Domain/Computer
      Name blank, the sample uses the local host.  You also specify a
      user who has administratoor credentials or select Use Current
      Credentials.  Select OK after specifying the domain/computer and
      the credentials.
  4.  A User Manager dialog appears with a list of users from which you
      select the user whose properties to display.
  5.  To change the computer, select Change and enter the new computer
      name in the Connect To dialog.
  6.  Select a user from the list of users for whom to display the User
      Name, Full Name, and Description.
  7.  The dialog also displays several password and account properties for
      the selected user, and you can change these properties.
  8.  If you double click a group in the list of groups of which the
      user is a member, a Group dialog appears that displays the Group
      Name, Group Type, Description, and names of members of the group.
  9.  You can also Add to or Remove from the list of groups for the
      selected user.  If you select Add, the Group Browser dialog appears
      that contains a list of groups that you can add.

How the Sample Works
====================
The sample defines the following four forms.

  frmConnect
    Displays the WinNT: Connect To dialog where you specify the domain
    or computer and the credentials to use to bind to objects using the
    WinNT: provider.
  frmGroup
    Displays the Group dialog which shows the properties and members of
    a selected group.
  frmGroupList
    Displays the Group Browser dialog which contains a list of groups
    on the domain/computer from which you can select one to add.
  frmUsrMgr
    Displays the main User Manager dialog for managing users.

See Also
========
IADs interface
IADsContainer interface
IADsGroup interface
IAdsMembers
IADsOpenDSObject interface
IADsUser interface
WinNT Binding String (ADsPath)

