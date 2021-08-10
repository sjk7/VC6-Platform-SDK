//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  SID VB Sample: Retrieving a User's SID
//
//--------------------------------------------------------------------------

Description
===========
The SID sample binds to a specified user object in Active Directory,
retrieves the user's SID, and then uses the ADsSID object in the
ADsSecurity.Dll file to convert the binary SID to a SID string format.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  SID.Bas
  *  SID.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

Also, you must install and register the ADsSecurity.Dll file from the
Active Directory 2.5 SDK.  To register the DLL
  1.  Open a command prompt and change to the directory where you
      installed the ADsSecurity.Dll file.
  2.  Type the command "regsvr32 ADsSecurity.Dll".
Then be sure that you have the ADsSecurity 2.5 Type Library selected in
the References list for the Project.

To build and run this sample
  1.  Open the project SID.Vbp.
  2.  Open the module SID.Bas.
  3.  Edit the following line to include the Common Name of the desired user
        strUserCommonName = "Craig Wiand"
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, a dialog appears with the text
"The SID for <Selected User> is NNNNNNNNNNNNNNN...NNN".  Then
a second dialog appears with the text "We have successfully re-bound to the
<Selected User> with the SID".

Otherwise, a dialog appears with the text "Did not find exactly one record
for <Selected User> Exiting".

How the Sample Works
====================
The sample uses the IADs interface to bind to Active Directory, ActiveX Data
Objects (ADO) to search for the selected user, and the IADsUser interface to
rebind to the selected user.

See Also
========
IADs interface
IADsUser interface
Searching with ActiveX Data Objects (ADO)

