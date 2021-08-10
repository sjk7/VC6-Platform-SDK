//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Search VB Sample: Searching Active Directory with ADO
//
//--------------------------------------------------------------------------

Description
===========
The Search sample uses ActiveX Data Objects with the SQL syntax to search
Active Directory for objects that match a specified filter.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  Search.Bas
  *  Search.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Search.Vbp.
  2.  Open the module Search.Bas.
  3.  Replace the domain with an appropriate one in the following line.
        Com.CommandText = "select name from 'LDAP://DC=Fabrikam,DC=com'  _
                           where objectCategory='group'"
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints output similar to the following
in the Immediate window.  Otherwise, an error dialog appears that describes an
error.

HelpServicesGroup
Administrators
Users
Guests
Print Operators
Backup Operators
Replicator
Remote Desktop Users
Network Configuration Operators
Domain Computers
Domain Controllers
Schema Admins
Enterprise Admins
Cert Publishers
Domain Admins
Domain Users
Domain Guests
Group Policy Creator Owners
RAS and IAS Servers
Server Operators
Account Operators
Pre-Windows 2000 Compatible Access
Incoming Forest Trust Builders
DnsAdmins
DnsUpdateProxy
DHCP Users
DHCP Administrators
Win2K Group Name
My New Group

How the Sample Works
====================
The sample uses the LDAP: ADsPath to perform the bindings and ActiveX
Data Objects to perfrom the search.

See Also
========
Searching with ActiveX Data Objects (ADO)

