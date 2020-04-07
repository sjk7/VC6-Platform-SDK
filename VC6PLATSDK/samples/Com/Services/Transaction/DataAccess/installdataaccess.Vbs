' ==============================================================================
' Filename: InstallDataAccess.vbs
'
' Description: Sample VB Script that creates an empty application and installs 
' the Data Access components into it
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


Dim ApplicationName 
ApplicationName = "Data Access Sample"

' First, we create the catalog object
Dim catalog
Set catalog = CreateObject("COMAdmin.COMAdminCatalog.1")

' Then we get the applications collection
Dim applications
Set applications = catalog.GetCollection("Applications")

applications.Populate

' Remove all Applications that go by the same name as the package we wish to install
numPackages = Applications.Count
For i = numPackages - 1 To 0 Step -1
    If applications.Item(i).Value("Name") = applicationName Then
        applications.Remove (i)
    End If
Next

' Commit our deletions
applications.SaveChanges

MsgBox "Done", 64, "Install Data Access Sample"

' Add a new appliction
Dim newApplication
Set newApplication = applications.Add
newApplication.Value("Name") = ApplicationName

' Commit new application
applications.SaveChanges

' Refresh Applications
applications.Populate


' Get components collection for new package
'Dim components
'Set components = applications.GetCollection("ComponentsInPackage", newApplication.Value("ID"))
Dim numApplications
numApplications = applications.count
for i = numApplications-1 to 0 step -1
	if applications.item(i).value("Name") = ApplicationName then
		set components = applications.GetCollection("Components", applications.Item(i).Value("ID"))
		appKey = applications.Item(i).Value("ID")
		components.populate
	End if
next


' Install components

' Install ADOKB.dll, RDOKB.dll, and OLEDBKB.dll
'
catalog.InstallComponent appKey, WSHEnv("MSSDK") & "\samples\COM\Services\Transaction\DataAccess\DataAcADO\Debug\ADOKB.dll", "", ""
catalog.InstallComponent appKey, WSHEnv("MSSDK") & "\samples\com\Services\Transaction\DataAccess\DataAcRDO\Debug\RDOKB.dll", "", ""
catalog.InstallComponent appKey, WSHEnv("MSSDK") & "\samples\com\Services\Transaction\DataAccess\DataAcOLEDB\Debug\Oledbkb.dll", "", ""
