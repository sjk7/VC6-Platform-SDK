//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  GetDomainmode VB Sample: Determining the Operation Mode of a Domain
//
//--------------------------------------------------------------------------

Description
===========
The GetDomainmode sample binds to an Active Directory domain partition
and reads the ntMixedDomain property to determine the operation mode
of the domain.

This sample uses the LDAP: provider and is suitable for Windows 2000 and
later networks running Active Directory.

Sample Files
============
  *  DomainMode.Bas
  *  GetDomainMode.Vbp

Building and Running the Sample
===============================
When you build this sample using Visual Basic, be sure that you have the
Active DS Type Library selected in the References list for the Project.

To build and run this sample
  1.  Open the project GetDomainMode.Vbp.
  2.  From the Run menu, select Start.

Example Output
==============
When you run the sample, a dialog appears with the results.
If execution is successful, text of the dialog is either
"The domain <domain name> is in Native Mode" or
"The domain <domain name> is in Mixed Mode".

Otherwise, the text of the dialog is
"The domain <domain name> is in Error in getting value".

How the Sample Works
====================
The sample defines the following subroutines.

  Main
    Initializes using the IADs interface, calls the GetDomainMode function,
    uninitializes.
  GetDomainMode
    Uses the IADs interfaces to get the ntMixedDomain attribute.

See Also
========
IADs interface
Detecting the Operation Mode of a Domain

