//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  User VB Sample: Manipulating Users with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The User sample binds to specified objects using ADSI and the WinNT provider
and demonstrates various techniques for manipulating users.

The sample illustrates:

  *  creating a user
  *  setting FullName and Description properties for a user
  *  setting and changing a user's password
  *  manipulating other password-related properties, such as password
     expiration and account lockout
  *  setting which workstations a user can log in through
  *  setting a user's home directory, home drive, and login script
  *  getting a user's primary group ID and SID
  *  renaming a user
  *  deleting a user

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  User.Bas
  *  User.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project User.Vbp.
  2.  Open the module User.Bas.
  3.  Search for, and replace occurences of the domain name INDEPENDENCE
      with the name of the domain you want to use.
  4.  From the Run menu, select Start.

Example Output
==============
If the sample runs successfully, it prints output in the Immediate window
similar to the following.

jupiter
mars
venus
1
5
0
0
0
0
0
5
15
0
0
0
9D
13
29
F
CF
5
E0
77
F8
17
F2
3D
9
4
0
0

If an error occurs, a dialog appears with an error message.

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
then uses the IAdsUser interface to perform the tasks.

See Also
========
IADsUser interface
WinNT Binding String (ADsPath)

