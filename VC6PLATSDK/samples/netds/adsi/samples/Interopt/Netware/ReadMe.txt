//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Netware VB Sample: Accessing Netware using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Netware sample illustrates how to access a Novell Netware Server
through ADSI using Visual Basic.

This sample uses the NWCOMPAT: provider and requires a Novell NetWare
Server.

Sample Files
============
  *  Netware.Bas
  *  Netware.Vbp
  *  Netware.Vbw

Building and Running the Sample
===============================
Before you run this sample, you must install the Gateway and Client
Services for Netware.  See the topic "Setting Up Gateway and Client
Services for Netware" in the Platform SDK.

Before you run this sample, you must log on to the NetWare Server.
To log on to the NetWare Server
  1.  Open a command window.
  2.  Type the command
        net use \\<server_name> /U:<domain_name>\<user_name>
      where
        <server_name>   Name of the NetWare Server
        <domain_name>   Name of the domain to log on.
        <user_name>     Name of user to log on.

To build and run this sample
  1.  Open the project Netware.Vbp.
  2.  Open the module Netware.Bas.
  3.  Enter an appropriate server name to replace that in the following line.
        serverName = "ntmarst2"
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints to the Immediate Window.
  *  First it enumerates all the objects in the NWCOMPAT container.
  *  Then it creates a new user and sets a full name.
  *  Finally, since searching is not supported by the NWCOMPAT: provider,
     it uses a filter to limit the type of objects when it enumerates objects.

If an error occurs, an error dialog appears that describes the error.

How the Sample Works
====================
The sample uses the NWCOMPAT: provider to perform the binding and the
IADsContainer::put_Filter method to perform the filter.

See Also
========
IADSContainer method
Setting Up Gateway and Client Services for Netware
Setting Up Gateway and Client Services for Netware 3.x


