//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Group VB Sample: Manipulating Groups with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Group sample demonstrates various techniques for manipulating groups
using ADSI.

The sample includes creating local and global groups in a domain; creating
a local group in a computer; adding a user to domain global or local groups;
adding a user to a local group on a computer; adding a global group to a
local group in a domain; enumerating groups in a domain or a computer;
enumerating group membership; removing members from a group; and
determining whether a user belongs to a particular group.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Group.Bas
  *  Group.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Group.Vbp.
  2.  Open the module Group.Bas.
  3.  Search for, and replace occurences of the domain name INDEPENDENCE
      with the name of the domain you want to use.
  4.  Search for, and replace occurences of the computer name SEATTLE with
      the name of the computer you want to use.
  5.  From the Run menu, select Start.

Example Output
==============
If the sample runs successfully, it prints output in the Immediate window
similar to the following for the FABRIKAMNT computer in the Fabrikam domain.

Local Groups---
Account Operators
Administrators
Backup Operators
Guests
Print Operators
Replicator
Server Operators
Users
DSys
TheSmiths
Global Groups---
Domain Admins
Domain Guests
Domain Users
PM
Groups:
Account Operators
Administrators
Backup Operators
Guests
Print Operators
Replicator
Server Operators
Users
DSys
TheSmiths
Domain Admins
Domain Guests
Domain Users
PM
JSmith   (User)
PM   (Group)
No

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
then uses the IADsGroup interface to perform the several tasks.

See Also
========
IADsGroup interface
WinNT Binding String (ADsPath)
