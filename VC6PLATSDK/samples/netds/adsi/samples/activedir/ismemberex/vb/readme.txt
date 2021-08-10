//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  IsMemberEx VB Sample: Enumerating the Security Groups of a User
//
//--------------------------------------------------------------------------

Description
===========
The IsMemberEx sample uses ADSI to bind to Active Directory and ActiveX
Data Objects (ADO) to search for a specified user.  It then enumerates the
security groups to which the specified user belongs.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  IsMemberEx.Bas
  *  IsMemberEx.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

Also, you must install and register the ADsSecurity.Dll file from the
Active Directory 2.5 SDK.  To register the DLL:
  1. Open a command prompt and change to the directory where you
     installed the ADsSecurity.Dll file.
  2. Type the command "regsvr32 ADsSecurity.Dll".
Then be sure that you have the ADsSecurity 2.5 Type Library selected in
the References list for the Project.

To build and run this sample
  1.  Open the project IsMemberEx.Vbp.
  2.  Open the module IsMemberEx.Bas.
  3.  Edit the following line to include the Common Name of the desired user
        strUserCommonName = "Bugs Bunny"
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, a dialog appears that lists the security
groups of which the specified user is a member.  If an error occurs, an error
dialog appears with the error.

How the Sample Works
====================
The sample program retrieves the tokenGroups property of the specified user
object in Active Directory.  This property contains SIDs that identify the
security groups to which the user belongs.  The sample then uses the ADsSID
object in the ADsSecurity.Dll to convert the binary SID to the SAM account
name of the group that it identifies.  It then lists the names of the
groups.

See Also
========
IADs interface
IADsUser interface
Searching with ActiveX Data Objects (ADO)

