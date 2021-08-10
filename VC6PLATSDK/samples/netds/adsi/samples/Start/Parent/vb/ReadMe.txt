//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Parent VB Sample: Binding to an Object's Parent Using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Parent sample demonstrates how to bind to a parent of an object.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Parent.Bas
  *  Parent.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Parent.Vbp.
  2.  Open the module Parent.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain
      name, such as FABRIKAM, and the user name "JJohnson" with an existing
      user in the domain in the following line.
        Set usr = GetObject("WinNT://INDEPENDENCE/JJohnson,user")
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, there is no output.  Otherwise, an
error dialog appears that describes an error.

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the IADs
interface to get the parent property of the specified user.

See Also
========
IADs interface
WinNT ADsPath
WinNT Binding String (ADsPath)

