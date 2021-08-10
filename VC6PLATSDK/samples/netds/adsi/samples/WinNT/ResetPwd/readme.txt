//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  ResetPwd VB Sample: Resetting Passwords with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The ResetPwd sample demonstrates how to reset a user's password using ADSI
and the WinNT provider.  The sample can reset either the domain password or
the password of the local user account when proper credentials are entered.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  ResetPwd.Frm
  *  ResetPwd.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project ResetPwd.Vbp.
  2.  From the Run menu, select Start.
  3.  In the WinNT: Reset Password dialog that appears enter:
      *  User Name and Password of a user who has permission to make
         the password change, or select Use Current Credentials if you
         have such permission.
      *  User Name of the account to change
      *  Domain of the account to change
      *  New Password
      *  New Password Confirmation

If the sample executes successfully, a dialog appears that says
"Password has been reset".  If the new password and the
confirmation that you enter do not agree, a dialog with the text
"New and Confirm passwords must be the same" appears.  If another
error occurs, a dialog with the error appears.

How the Sample Works
====================
The sample uses the WinNT ADsPath to bind to the domain controller and
the IADsOpenDSObject and IADsUser interfaces to effect the password change.

See Also
========
IADsOpenDSObject interface
IADsUser interface
WinNT Binding String (ADsPath)

