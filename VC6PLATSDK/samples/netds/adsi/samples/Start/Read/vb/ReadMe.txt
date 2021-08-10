//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Read VB Sample: Reading Attributes Using ADSI
//
//--------------------------------------------------------------------------

Description
===========
The Read sample reads various single-valued and multi-valued properties of
an Active Directory object.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  Read.Bas
  *  Read.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project Read.Vbp.
  2.  Open the module Read.Bas.
  3.  Replace the domain name "INDEPENDENCE" with the appropriate domain name,
      such as Fabrikam, in the following line.
        Set usr = GetObject("WinNT://INDEPENDENCE/Administrator,user")
  4.  From the Run menu, select Start.

Example Output
==============
If the sample executes successfully, it prints output similar to the following
in the Immediate window.  Otherwise, an error dialog appears that describes an
error.

Administrator
Jeff Smith
Jeff Smith
1
5
0
0
0
0
0
5
15
0
0
0
52
AA
C8
68
F0
94
C8
5F
F8
9F
B4
74
F4
1
0
0
1
5
0
0
0
0
0
5
15
0
0
0
52
AA
C8
68
F0
94
C8
5F
F8
9F
B4
74
F4
1
0
0

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the
IADs interface to read the properties.

See Also
========
IADs interface
WinNT ADsPath
WinNT Binding String (ADsPath)

