//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  PropertyList VB Sample: Using ADSI Property Lists
//
//--------------------------------------------------------------------------

Description
===========
The PropertyList sample uses ADSI to bind to Active Directory and ActiveX
Data Objects (ADO) to search for a specified user.  It then uses the IADs,
IADsPropertyList, and IADsPropertyEntry interfaces to enumerate the attributes
of the user.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  ADsHelper.Bas
  *  ADsPropertyList.Vbp
  *  PropertyList.Bas

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

Also, you must install and register the ADsSecurity.Dll file from the
Active Directory 2.5 SDK.  To register the DLL
  1. Open a command prompt and change to the directory where you
     installed the ADsSecurity.Dll file.
  2. Type the command "regsvr32 ADsSecurity.Dll".
Then be sure that you have the ADsSecurity 2.5 Type Library selected in
the References list for the Project.

To build and run this sample
  1.  Open the project ADsPropertyList.Vbp.
  2.  Open the module PropertyList.Bas.
  3.  Edit the following line to include the Common Name of the desired user
        strUserCommonName = "Administrator"
  4.  From the Run menu, select Start.

Example Output
==============
The sample prints its output to the Immediate window.  The output
is similar to the following, which is for "Test User" in the
Fabrikam.Com domain.

objectClass :  top# person# organizationalPerson# user
cn :  Test User
sn :  User
givenName :  Test
distinguishedName :  CN=Test User,CN=Users,DC=fabrikam,DC=com
instanceType :  4
whenCreated :  6/30/2002 8:12:00 PM
whenChanged :  6/30/2002 10:38:44 PM
displayName :  Test User
uSNCreated :  &H012392 (LargeInteger)
uSNChanged :  &H012424 (LargeInteger)
nTSecurityDescriptor :  Value of type NT Security Descriptor
name :  Test User
objectGUID :  Property is a GUID
userAccountControl :  66080
badPwdCount :  0
codePage :  0
countryCode :  0
badPasswordTime :  0
lastLogoff :  0
lastLogon :  0
pwdLastSet :  6/30/2002 3:38:44 PM
primaryGroupID :  513
objectSid :  01050000000000051500000052AAC868F094C85FF89FB47468040000
accountExpires :  -1
logonCount :  0
sAMAccountName :  TestU
sAMAccountType :  805306368
userPrincipalName :  TestU@fabrikam.com
objectCategory :  CN=Person,CN=Schema,CN=Configuration,DC=fabrikam,DC=com

If an error occurs, a dialog appears with an error message.

How the Sample Works
====================
The sample defines two modules, PropertyList.Bas and ADsHelper.Bas.  These
modules contain the following functions as well as several conversion
functions.

  Main
    Initializes using the IADs interface, searchs for the specified user
    using Active Data Objects (ADO), enumerates the attributes of the user
    using the IADsPropertyList and IADsPropertyEntry interfaces and the
    EnumeratePropertyValue function, and uninitializes.
  EnumeratePropertyValue
    Converts a property entry to a string that describes its value.

See Also
========
IADs interface
IADsPropertyEntry
IADsPropertyList
Searching with ActiveX Data Objects (ADO)

