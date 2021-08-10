//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Credentials VB Sample: Binding With Alternate Credentials
//
//--------------------------------------------------------------------------

Description
===========
The Credentials sample uses ADSI and the LDAP provider to bind to Active
Directory using specified credentials rather than using the default
credentials of the logged-on user.

The sample allows the user to specify alternate credentials for the current
domain by using a user name that can be:
  1.  NT 4.0 Style name such as MYDOMAIN\MyUser.
  2.  Windows 2000 User Principal Name such as myUser@mydomain.com.
  3.  User name without the domain name such as Administrator.
      In this case, it assumes the domain name is the current domain.
  4.  Distinguished Name such as CN=Administrator,DC=Fabirkam,DC=Com.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Credential.Bas
  *  Credentials.Vpb

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Credentials.Vpb.
  2.  From the Run menu, select Start.

The sample sequentially displays two dialogs where you enter the username
and password of the alternative credentials to use.

Example Output
==============
If the sample executes successfully, a dialog appears with the text
"You have successfully bound to : <domain> as <user name>".  Otherwise,
an error dialog appears that describes an error.

How the Sample Works
====================
The sample uses the IADsOpenDSObject interface to specify the credentials.

See Also
========
IADsOpenDSObject interface
ADsOpenObject and IADsOpenDSObject::OpenDSObject
