//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Binding VB Sample: Binding with Current and Alternate Credentials
//
//--------------------------------------------------------------------------

Description
===========
The Binding sample demonstrates how to bind to a domain using the credentials
of the currently logged-on user and with credentials of a specified user.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Binding.Bas
  *  Binding.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Binding.Vbp.
  2.  Open the module Binding.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain
      name, such as FABRIKAM, in the following line.
        Set obj = GetObject("WinNT://INDEPENDENCE")
  4.  Replace the domain name, user name, and Administrator password
      with appropriate values in the following line.
        Set usr = DSO.OpenDSObject("WinNT://INDEPENDENCE/JSmith,user",  _
                  "Administrator", "se**cre*t*", ADS_SECURE_AUTHENTICATION)
  5.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an
error dialog appears that describes an error.

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the
IADsOpenDSObject interface to bind with the credentials of the specified
user.

See Also
========
IADs interface
WinNT ADsPath
WinNT Binding String (ADsPath)

