' ==============================================================================
' Filename: UninstallSampleBank.vbs
'
' Description: Sample VB Script that uninstalls the Sample Bank package
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

Dim applicationName
applicationName = "Sample Bank"

' First, we create the catalog object
Dim catalog
Set catalog = CreateObject("COMAdmin.COMAdminCatalog.1")

' Then we get the packages collection
Dim applications
Set applications = catalog.GetCollection("Applications")
applications.populate

' Remove all packages that go by the same name as the package we wish to uninstall
numPackages = applications.Count
For i = numPackages - 1 To 0 Step -1
    If applications.Item(i).Value("Name") = applicationName Then
        applications.Remove (i)
    End If
Next

' Commit our deletions
applications.savechanges

MsgBox "Done", 64, "Uninstall User EVents"