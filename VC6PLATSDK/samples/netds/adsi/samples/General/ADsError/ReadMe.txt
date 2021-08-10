//+-------------------------------------------------------------------------
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  ADsError VC Sample: ADSI Error Message Supplier
//
//--------------------------------------------------------------------------

Description
===========
The ADsError sample implements an in-process COM server that supplies the
error message text for a Win32, SSPI, ADSI, or extended ADSI error code.

Sample Files
============
  *  ADsError.Cpp
  *  ADsError.Def
  *  ADsError.Dsp
  *  ADsError.Dsw
  *  ADsError.h
  *  ADsError.Idl
  *  ADsError.Rc
  *  ADsError.Rgs
  *  ADsError_i.c
  *  ADsError_p.c
  *  ADsErrorps.Def
  *  ADsErrorps.Mk
  *  Client\ADsErrClient.Frm
  *  Client\ADsErrClient.Vbp
  *  Client\ADsErrClient.Vbw
  *  DllData.c
  *  IADsError.Cpp
  *  IADsError.h
  *  makefile
  *  Resource.h
  *  StdAfx.Cpp
  *  StdAfx.h

Building the Sample
===================
When you build this sample using Visual Studio, be sure that you have the
INCLUDE directory for the Platform SDK set first in the Options list of
include files.

To build this sample
  1.  Open the workspace ADsError.Dsw.
  2.  From the Build menu, select Build.

This runs the Microsoft IDL compiler, which creates the type library for
the COM object.  It also compiles the resources and source files, and links
all modules to produce the DLL file for the COM server.  It then registers
the DLL file in the Registry.

You can also build this sample at a command prompt using the supplied
makefile.  If you use the makefile, you'll need to register the DLL file
manually.  To register the DLL file
  1.  Open a command prompt and change to the directory that contains the
      ADsError.Dll file.
  2.  Type the command
        regsvr32.exe ADsError.Dll

Running the Sample
==================
To run this sample you can use a simple VB client program to produce an
error, which the ADsError server processes.  To run the VB client program
  1.  Open the project Client\ADsErrClient.Vbp.
  2.  From the Project menu, select References and be sure that you have
      the ADsError 1.0 Type Library selected in the list of Available
      References for the Project.
  3.  Open the code module for the ADsErrClient.Frm form and view the
      Form_Load function.
  4.  Replace the binding string with an existent domain, but include a
      non-existent organizational unit, such as "OU=Org Unit",
      before the domain in the following line.
        Set rec = GetObject("LDAP://DC=Fabrikam,DC=Com")
  5.  From the Run menu, select Start.

A dialog appears with an error message.  For example, the text of the
error message for the binding string of Step 4 is similar to:

  There is no such object on the server.
   -- Extended Error:LDAP Provider: 0000208D: NameErr: DSID-031001BE,
      problem 2001 (NO_OBJECT), data 0, best match of: 'DC=Fabrikam,DC=Com'

Selecting OK dismisses the dialog, and a blank form for the client appears.

You can try modifying the ADsErrClient code to produce other types of errors.

How the Sample Works
====================
The sample constructs a COM server using the following key files.

  ADsError.Idl
    Contains the MIDL source for the ADsError.Dll file.  It declares a COM
    interface and method (IADsError::GetErrorMessage) for the error message
    server, names the type library (ADsError 1.0 Type Library), and defines
    GUIDs for the interface, method, and type library.
  ADsError.Def
    Declares the exported entry points for the ADsError.Dll file.
  ADsError.Cpp
    Implements the entry points for the ADsError server.
  IADsError.Cpp
    Implements the IADsError::GetErrorMessage method of the ADsError server.

The simple VB client creates an instance of the ADsError object with the
statement
  Set adsErr = CreateObject("ADsError")
When an error occurs, it displays the error with the statement
  MsgBox adsErr.GetErrorMessage(Err.Number)

See Also
========
ADSI Service Providers


