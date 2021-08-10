Attribute VB_Name = "Computer"
Sub Main()

'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       computer.bas
'
'  Contents:   Computer, Services, FileShare, Resources and Sessions
'
'----------------------------------------------------------------------------


Dim comp As IADsComputer
Dim svc As IADsService
Dim svcOp As IADsServiceOperations
Dim fileShare As IADsFileShare
Dim fileSvc As IADsFileService
Dim session As IADsSession
Dim resource As IADsResource




'--- Defined in winnt.h ----------------

Const SERVICE_BOOT_START = &H0
Const SERVICE_SYSTEM_START = &H1
Const SERVICE_AUTO_START = &H2
Const SERVICE_DEMAND_START = &H3
Const SERVICE_DISABLED = &H4
'
' Error control type
'
Const SERVICE_ERROR_IGNORE = &H0
Const SERVICE_ERROR_NORMAL = &H1
Const SERVICE_ERROR_SEVERE = &H2
Const SERVICE_ERROR_CRITICAL = &H3

Const SERVICE_KERNEL_DRIVER = &H1
Const SERVICE_FILE_SYSTEM_DRIVER = &H2
Const SERVICE_ADAPTER = &H4
Const SERVICE_RECOGNIZER_DRIVER = &H8

Const SERVICE_DRIVER = &HB
Const SERVICE_WIN32_OWN_PROCESS = &H10
Const SERVICE_WIN32_SHARE_PROCESS = &H20
Const SERVICE_WIN32 = &H30
Const SERVICE_INTERACTIVE_PROCESS = &H100
                                        




'-----------------------------------------
'--- BINDING TO COMPUTER OBJECT
'-----------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer") '--- Change ComputerName accordingly
'OR----you can include the domain name
Set comp = GetObject("WinNT://INDEPENDENCE/SEATTLE,computer")

Debug.Print comp.Division
Debug.Print comp.OperatingSystem
Debug.Print comp.OperatingSystemVersion
Debug.Print comp.Owner
Debug.Print comp.Processor
Debug.Print comp.ProcessorCount


'-------------------------------------------
'--- ENUMERATE SERVICES IN A COMPUTER
'-------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
comp.Filter = Array("Service")

For Each svc In comp
   Debug.Print svc.Name & "  " & svc.DisplayName
Next

'----------------------------------------------
'--- DISPLAY SERVICE'S PROPERTIES
'-----------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set svc = comp.GetObject("Service", "Browser")
Debug.Print "Display Name: " & svc.DisplayName
Debug.Print "Order Group: " & svc.LoadOrderGroup
Debug.Print "Host Name: " & svc.HostComputer

s = "Startup: "

Select Case svc.StartType
  Case SERVICE_BOOT_START
     s = s + "Boot Start"
  Case SERVICE_SYSTEM_START
     s = s + "System Start"
  Case SERVICE_AUTO_START
    s = s + "Automatic"
  Case SERVICE_DEMAND_START
    s = s + "Manual"
  Case SERVICE_DISABLED
    s = s + "Disabled"
  Case Else
    s = s + "Unknown"
End Select
Debug.Print s

'Dependencies
Debug.Print "Dependencies: "
For Each dpc In svc.Dependencies
    Debug.Print "  " & dpc
Next

'Service Type
s = "Service Type: "
Select Case svc.ServiceType

Case SERVICE_KERNEL_DRIVER
     s = s + "Kernel Driver"
Case SERVICE_FILE_SYSTEM_DRIVER
     s = s + "File System Driver"
Case SERVICE_ADAPTER
     s = s + "Adapter"
Case SERVICE_RECOGNIZER_DRIVER
     s = s + "Recognizer Driver"
Case SERVICE_WIN32_OWN_PROCESS
     s = s + "Win32 Process"
Case SERVICE_WIN32_SHARE_PROCESS
     s = s + "Win32 Share Process"
Case SERVICE_WIN32
     s = s + "Win32"
Case SERVICE_INTERACTIVE_PROCESS
     s = s + "Interactive Process"
End Select
Debug.Print s

'Error Control
s = "Error Control: "
Select Case svc.ErrorControl

Case SERVICE_ERROR_IGNORE
   s = s + "Service ignores error"
Case SERVICE_ERROR_NORMAL
   s = s + "No Error"
Case SERVICE_ERROR_SEVERE
   s = s + "Severe error"
Case SERVICE_ERROR_CRITICAL
  s = s + "Critical error"
Case Else
  s = s + "Unknown"
End Select
Debug.Print s

'----------------------------------------------
'--- STOPPING, STARTING AND PAUSING A SERVICE
'-----------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set svcOp = comp.GetObject("Service", "Browser")
'Stopping
svcOp.Stop
'Starting
svcOp.Start
'Pausing
svcOp.Pause




'------------------------------------------
'---- ENUMERATING FILE SHARES IN A COMPUTER
'-------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set svc = GetObject(comp.ADsPath & "/" & "LanmanServer")
For Each fileShare In svc
      Debug.Print fileShare.Name & " " & " " & fileShare.CurrentUserCount & " " & fileShare.Path
Next

'------------------------------------------
'---- CREATING A FILE SHARE IN A COMPUTER
'-------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set svc = GetObject(comp.ADsPath & "/" & "LanmanServer")
Set fileShare = svc.Create("FileShare", "public")
fileShare.Path = "c:\public"
fileShare.SetInfo


'------------------------------------------
'---- DELETING A FILE SHARE IN A COMPUTER
'-------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set svc = GetObject(comp.ADsPath & "/" & "LanmanServer")
svc.Delete "FileShare", "public"


'--------------------------------------------
'---- ENUMERATING SESSIONS IN A COMPUTER
'---------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set fileSvc = GetObject(comp.ADsPath & "/" & "LanmanServer")
For Each session In fileSvc.Sessions
   Debug.Print session.Name & " " & session.ConnectTime
Next

'--------------------------------------------
'---- ENUMERATING RESOURCES IN A COMPUTER
'---------------------------------------------
Set comp = GetObject("WinNT://SEATTLE,computer")
Set fileSvc = GetObject(comp.ADsPath & "/" & "LanmanServer")
For Each resource In fileSvc.Resources
   Debug.Print resource.Name & " - " & resource.User
Next

End Sub
