Attribute VB_Name = "Binding"
Sub Main()

'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       bind.bas
'
'  Contents:   Show how to bind to an ADSI object
'
'----------------------------------------------------------------------------

Dim dso As IADsOpenDSObject

'-----------------------------------------------------
'--- BINDING TO A DOMAIN -----------------------------
'------------------------------------------------------
DomainName = "INDEPENDENCE" '--- Change the domain accordingly

'--- Binding to a domain as currently logged on user
Set dom = GetObject("WinNT://" & DomainName)


'--- Binding to a domain with supplied credential
'---In production code DO NOT hard code credential info in your source
'---Try getting from the user interactively and delete after use
Set dso = GetObject("WinNT:")
Set dom = dso.OpenDSObject("WinNT://" & DomainName, "user1", "se*c*ret", ADS_SECURE_AUTHENTICATION)


'-----------------------------------------------------
'--- BINDING TO A REMOTE MACHINE  --------------------
'------------------------------------------------------
ComputerName = "adsi"

'--- Binding to a computer as currently logged on user
Set comp = GetObject("WinNT://" & ComputerName & ",computer")


'--- Binding to a computer with supplied credential
'---In production code DO NOT hard code credential info in your source
'---Try getting from the user interactively and delete after use

Set dso = GetObject("WinNT:")
Set comp = dso.OpenDSObject("WinNT://" & ComputerName & ",computer", "user1", "se*c*ret", ADS_SECURE_AUTHENTICATION)

'-- and you can find out which domain this computer is joined to
Debug.Print "Domain Name for this computer is " & comp.Parent



'-----------------------------------------------------
'--- BINDING TO A USER IN A DOMAIN  --------------------
'------------------------------------------------------
ADsPath = "WinNT://" & DomainName & "/" & "user1"
'-- adsPath == WinNT://INDEPENDENCE/Administrator

Set dom = GetObject(ADsPath)




End Sub
