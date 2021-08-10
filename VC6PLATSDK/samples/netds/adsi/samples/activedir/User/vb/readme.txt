//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  User VB Sample: Using the IADsUser Interface
//
//--------------------------------------------------------------------------

Description
===========
The User sample binds to a user object in Active Directory and uses
the IADsUser interface to retrieve information about the user.

The sample uses ActiveX Data Objects (ADO) to search for the user.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  ADsHelper.Bas
  *  CheckUser.Bas
  *  User.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project User.Vbp.
  2.  From the Run menu, select Start.

Example Output
==============
A dialog appears that asks for the Common Name of a user in the domain
to query.  If the sample runs successfully, it prints output similar to
the following for "Test User" in Fabrikam.Com in the Immediate window.

Class :  user
Department :  Test
Description :  A user account for samples
Division is not present on the object
emailAddress :  testu@fabrikam.com
EmployeeID is not present on the object
Fax Number is not present on the object
First Name :  Test
Full Name :  Test User
Grace Logins Allowed is not present on the object
Grace Logins Remaining is not present on the object
GUID :  29a396ba0f015e4db6fb7adc3de3a348
Home Directory is not present on the object
Home Page :  http://www.fabrikam.com/~testu
Last Name :  User
Login Hours(GMT) is not present on the object
Login Script is not present on the object
Login Workstations is not present on the object
Manager is not present on the object
Max Logins is not present on the object
Max Storage is not present on the object
Name :  CN=Test User
Name Prefix is not present on the object
Name Suffix is not present on the object
Office Locations :  Penthouse
Other Name is not present on the object
Parent :  LDAP://CN=Users,DC=fabrikam,DC=com
Password Expiration Date is not present on the object
Postal Codes :  99999
Profile is not present on the object
Require Unique Password is not present on the object
Schema :  LDAP://schema/user
See Also is not present on the object
Telephone Home :  888-555-1234
Telephone Mobile is not present on the object
Telephone Number :  888-555-1212
Telephone Pager is not present on the object
Title :  Director of Testing

If the sample does not run successfully, a dialog appears with an
error message.

How the Sample Works
====================
The sample uses the IADs interface to bind to Active Directory, searches
for the specified user using ADO, and retrieves the user's properties
using the IADsUser interface.  It uses conversion functions in the
ADsHelper.Bas module to convert properties to strings.

See Also
========
IADs interface
IADsUser interface
Searching with ActiveX Data Objects (ADO)

