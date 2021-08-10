//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  RootDSE VB Sample: Retrieving the Distinguished Name
//                     of a Domain Partition
//
//--------------------------------------------------------------------------

Description
===========
The RootDSE sample binds to rootDSE of an Active Directory server
and retrieves the defaultNamingContext property, which contains the
distinguished name of the domain partition.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  RootDSE.Bas
  *  RootDSE.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project RootDSE.Vbp.
  2.  From the Run menu, select Start.

The sample displays a dialog with the distinguished name of the domain.

How the Sample Works
====================
The sample uses the IADs interface to get and print the defaultNamingContext
property of the root of the directory information tree of the directory server.

See Also
========
IADs interface
Serverless Binding and RootDSE

