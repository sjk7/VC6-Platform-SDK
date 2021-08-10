//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Filter VB Sample: Filtering a Container's Objects with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Filter sample enumerates selected objects in a container, printing the
name and class of the filtered objects in a specified WinNT domain.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Filter.Bas
  *  Filter.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Filter.Vbp.
  2.  Open the module Filter.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain name,
      such as Fabrikam, in the following line.
        Set dom = GetObject("WinNT://INDEPENDENCE")
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints output similar to the following
in the Immediate window.  Otherwise, an error dialog appears that describes an
error.

Administrator (User)
Guest (User)
TestU (User)
user1 (User)
DnsUpdateProxy (Group)
Domain Admins (Group)
Domain Computers (Group)
Domain Controllers (Group)
Domain Guests (Group)
Domain Users (Group)
Downlevel Name (Group)
Enterprise Admins (Group)
Group Policy Creator Owners (Group)
NewGroup (Group)
Schema Admins (Group)
Administrators (Group)
Users (Group)
Guests (Group)
Print Operators (Group)
Backup Operators (Group)
Replicator (Group)
Remote Desktop Users (Group)
Network Configuration Operators (Group)
Server Operators (Group)
Account Operators (Group)
Pre-Windows 2000 Compatible Access (Group)
Incoming Forest Trust Builders (Group)
Cert Publishers (Group)
RAS and IAS Servers (Group)
HelpServicesGroup (Group)
DnsAdmins (Group)
DHCP Users (Group)
DHCP Administrators (Group)

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the
IADsContainer interface to filter (only user and group objects) and
enumerate the objects in the domain.

See Also
========
IADsContainer interface
WinNT ADsPath
WinNT Binding String (ADsPath)

