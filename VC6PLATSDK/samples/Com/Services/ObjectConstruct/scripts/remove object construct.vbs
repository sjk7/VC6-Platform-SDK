' This file is part of the Microsoft COM+ Samples
'
' Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved
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

' Remove the Object Construct application
Dim ApplicationName
ApplicationName = "Object Construct"

' First, we create the catalog object
Dim catalog
Set catalog = CreateObject("COMAdmin.COMAdminCatalog.1")

' Then we get the applications collection
Dim applications
Set applications = catalog.GetCollection("Applications")

applications.Populate

' Remove all Applications that go by the app name
numPackages = applications.Count
For i = numPackages - 1 To 0 Step -1
    If applications.Item(i).Value("Name") = ApplicationName Then
        applications.Remove i
    End If
Next

' Commit our deletions
applications.SaveChanges

MsgBox "Object Construct Removed From COM+ Catalog"