' ==============================================================================
' Filename: InstDLL.vbs
'
' Description: Sample VB Script that creates an empty application and installs 
' the Sample Bank components into it
'
' This file is part of the Microsoft COM+ Samples
'
' Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved
'
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation.  See these other
' materials for detailed information reagrding Microsoft code samples.
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
Dim WSHShell
Dim WSHEnv
Set WSHShell = CreateObject("Wscript.Shell")
Set WSHEnv = WSHShell.Environment("Process")

Dim Path
Path = ".\"

Dim ApplicationName 
ApplicationName = "Sample Bank"

' First, we create the catalog object
Dim catalog
Set catalog = CreateObject("COMAdmin.COMAdminCatalog.1")

' Then we export it
catalog.ExportApplication "Sample Bank", ".\SampleBank.MSI", 2
