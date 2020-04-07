' ==============================================================================
' Filename: InstalSampleBank.vbs
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


Dim ApplicationName 
ApplicationName = "Sample Bank"

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

' Install VBAcct.dll, VCAcct.dll, and VJAcct.dll
'
catalog.InstallComponent appKey, WSHEnv("MSSDK") & "\samples\com\Services\Transaction\SampleBank\vbacct\vbacct.dll", "", ""
catalog.InstallComponent appKey, WSHEnv("MSSDK") & "\samples\com\Services\Transaction\SampleBank\vcacct\debug\vcacct.dll", "", ""
catalog.InstallComponent appKey, WSHEnv("MSSDK") & "\samples\com\Services\Transaction\SampleBank\vjacct\vjacct.dll", "", ""


' Configure installed components
'
numApplications = applications.Count
for i = numApplications-1 to 0 step -1
	if applications.Item(i).Value("Name") = ApplicationName then
		Set components = applications.GetCollection("Components", applications.Item(i).Value("ID"))
		components.Populate
	end if
next

numComponents = components.Count
for i = numComponents-1 to 0 step -1
	if components.Item(i).Value("ProgID") = "VBBank.MoveMoney" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "3"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"
	elseif components.Item(i).Value("ProgID") = "VBBank.Account" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "3"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VBBank.GetReceipt" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "2"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VBBank.UpdateReceipt" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "4"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VBBank.CreateTable" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "1"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VCBank.MoveMoney" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "3"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"
	elseif components.Item(i).Value("ProgID") = "VCBank.Account" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "3"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VCBank.GetReceipt" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "2"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VCBank.UpdateReceipt" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "4"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VJBank.MoveMoney" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "3"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"
	elseif components.Item(i).Value("ProgID") = "VJBank.Account" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "3"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VJBank.GetReceipt" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "2"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	elseif components.Item(i).Value("ProgID") = "VJBank.UpdateReceipt" then
		components.Item(i).Value("Synchronization") = "3"
		components.Item(i).Value("Transaction") = "4"
		components.Item(i).Value("JustInTimeActivation") = "1"
		components.Item(i).Value("IISIntrinsics") = "1"		
	end if
next

' Commit the changes to the components
components.SaveChanges

' Create the 'Managers' role in the package
Dim roles
Dim newRole
Set roles = applications.GetCollection("Roles", appKey)
Set newRole = roles.Add
newRole.Value("Name") = "Managers"
roles.SaveChanges

MsgBox "Done", 64, "Install Sample Bank"