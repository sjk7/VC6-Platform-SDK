//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  First VC Sample: Committing Changes with ADSI
//
//--------------------------------------------------------------------------

Description
===========
The First sample creates a user and then commits the changes to the directory.

This sample uses the WinNT: provider and is suitable for Windows NT(R) 4.0
networks as well as Windows 2000 and later networks running Active Directory.

Sample Files
============
  *  First.Cpp
  *  First.Dsp
  *  First.Dsw
  *  makefile
  *  StdAfx.Cpp
  *  StdAfx.h

Building the Sample
===================
When you build this sample using Visual Studio, be sure that you have the
INCLUDE directory for the Platform SDK set first in the Options list of
include files.

You must run this sample in a Windows domain where you have permission to
write to the domain controller.

To build this sample
  1.  Open the workspace First.Dsw.
  2.  Open the source file First.Cpp.
  3.  Replace the domain name "INDEPENDENCE" with an appropriate domain name,
      such as "FABRIKAM", in the following line.
        hr = ADsGetObject(L"WinNT://INDEPENDENCE",  \
                          IID_IADsContainer, (void**) &pCont );
  4.  From the Build menu, select Build.

You can also build this sample at a command prompt using the supplied
makefile.

Running the Sample
==================
To run this sample
  1.  Open a command prompt and change to the directory where you built
      the sample.
  2.  Type the command "First.exe".

You can also run the sample by selecting Execute First.exe from
the Build menu.

Example Output
==============
If the sample executes successfully, there is no output.

The sample creates a user named "jsmith".  You can verify the result by
opening and examining the Active Directory Users and Computers snap-in of
the Microsoft Management Console.

How the Sample Works
====================
The sample uses the WinNT ADsPath to perform the binding and the IADs and
IADsContainer interfaces to create and commit the object in the domain.

See Also
========
IADs interface
IADsContainer interface
WinNT ADsPath
WinNT Binding String (ADsPath)

