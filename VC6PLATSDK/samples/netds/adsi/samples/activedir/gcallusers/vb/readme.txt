//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  GCallUsers VB Sample: Searching the Global Catalog
//
//--------------------------------------------------------------------------

Description
===========
The GCallUsers sample searches the global catalog to enumerate users in
an Active Directory forest.

The sample uses ActiveX Data Objects (ADO) to perform the search.

This sample uses the GC: provider and is suitable for Windows 2000 and later
networks running Active Directory.

Sample Files
============
  *  GCAllUsers.Vpb
  *  QueryGC.Bas

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project GCAllUsers.Vpb.
  2.  From the Run menu, select Start.

Example Output
==============
When you run the sample, view the Immediate window to see the results.
The sample produces output similar to the following.

Administrator   CN=Administrator,CN=Users,DC=fabrikam,DC=com
Guest   CN=Guest,CN=Users,DC=fabrikam,DC=com
Test User   CN=Test User,CN=Users,DC=fabrikam,DC=com

How the Sample Works
====================
The sample uses the IADs and IADsContainer interfaces to bind to and to get
the global catalog object. The sample uses Active Data Objects to construct
a query and enumerate the selected attributes for found users.

See Also
========
IADs interface
IADsContainer interface
Searching with ActiveX Data Objects (ADO)

