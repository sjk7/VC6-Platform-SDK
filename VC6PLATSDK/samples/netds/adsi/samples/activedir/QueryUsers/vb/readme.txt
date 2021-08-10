//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  QueryUsers VB Sample: Searching for Users in Active Directory
//
//--------------------------------------------------------------------------

Description
===========
The QueryUsers sample queries an Active Directory domain partition for user
objects that match a specified filter.

The sample uses ActiveX Data Objects (ADO) to perform the search.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  QueryUsers.Bas
  *  QueryUsers.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project QueryUsers.Vbp.
  2.  From the Run menu, select Start.
  3.  When a dialog appears, enter a filter to find users.
      If you leave the filter blank, the sample lists all users.

Example Output
==============
The sample prints its output to the Immediate window.  The output
is similar to the following, which is for the filter (sn=User)
in the Fabrikam.Com domain.

name :  Test User
distinguishedName :  CN=Test User,CN=Users,DC=fabrikam,DC=com
cn :  Test User
givenName :  Test
sn :  User

If an error occurs, a dialog appears with an error message.

How the Sample Works
====================
The sample initializes using the IADs interface, searchs for the specified
user using Active Data Objects (ADO), and enumerates the name,
distinguishedName, cn, givenName, snattributes attrributes of the user,
and uninitializes.

See Also
========
IADs interface
Searching with ActiveX Data Objects (ADO)

