//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  IsGC VB Sample: Determining whether a DC is a Global Catalog server
//
//--------------------------------------------------------------------------

Description
===========
The IsGC sample determines whether a domain controller is also a global
catalog server.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Is_GC.Bas
  *  IsGC.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project IsGC.Vbp.
  2.  From the Run menu, select Start.

Example Output
==============
When you run the sample, a dialog appears with either the text
"<domain_controller> is a GC" or "<domain_controller> is not a GC".
If an error occurs, a dialog with an error appears.

How the Sample Works
====================
The sample reads the rootDSE of the domain controller, gets its dsServiceName
property, and uses that property to get the NTDS Settings object for the
domain controller.  It checks the options property of the NTDS Settings object
to see if the domain controller is also a global catalog server.

See Also
========
Global Catalog Server
Serverless Binding and RootDSE
