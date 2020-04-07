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
Dim WSHShell
Dim WSHEnv
Set WSHShell = CreateObject("Wscript.Shell")
Set WSHEnv = WSHShell.Environment("Process")

' Create the Object Construct application
Dim ApplicationName
ApplicationName = "Object Construct"

' First, we create the catalog object
Dim catalog
Set catalog = CreateObject("COMAdmin.COMAdminCatalog.1")

' Then we get the applications collection
Dim applications
Set applications = catalog.GetCollection("Applications")

applications.populate

' Remove all Applications that go by the same name as the package we wish to install
numPackages = applications.Count
For i = numPackages - 1 To 0 Step -1
    If applications.Item(i).Value("Name") = ApplicationName Then
        applications.Remove i
    End If
Next

' Commit our deletions
applications.SaveChanges

' Add a new application
Dim newApplication
Set newApplication = applications.Add
newApplication.Value("Name") = ApplicationName
newApplication.Value("Activation") = "1"

' Commit new application
applications.SaveChanges

Set components = applications.GetCollection("Components", newApplication.Value("ID"))

' Install components
'   - ObjectConstructLib.dll

catalog.InstallComponent newApplication.Value("ID"), WSHEnv("MSSDK") & "Samples\COM\Services\ObjectConstruct\Bin\ObjectConstructLib.dll", "", ""

' Configure installed components
'
components.populate
For Each component In components
    Select Case component.Value("ProgID")            
        Case "ObjectConstructLib.clsObjectConstruct"
		component.Value("ConstructionEnabled") = True
		component.Value("ConstructorString") = "My Object Construction String"
    End Select
Next

' Commit the changes to the components
components.SaveChanges

MsgBox "Object Construct Configured in the COM+ Catalog"
