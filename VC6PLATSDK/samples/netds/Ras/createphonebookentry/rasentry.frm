VERSION 5.00
Begin VB.Form frmRasEntry 
   Caption         =   "RasEntry"
   ClientHeight    =   6990
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9450
   LinkTopic       =   "Form1"
   ScaleHeight     =   6990
   ScaleWidth      =   9450
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox lstRasEntries 
      Height          =   2010
      Left            =   7200
      Sorted          =   -1  'True
      TabIndex        =   20
      Top             =   1320
      Width           =   1935
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   7440
      TabIndex        =   18
      Top             =   6480
      Width           =   1575
   End
   Begin VB.CommandButton cmdDeleteEntry 
      Caption         =   "Delete Entry"
      Height          =   375
      Left            =   7440
      TabIndex        =   17
      Top             =   5520
      Width           =   1575
   End
   Begin VB.CommandButton cmdRasSetEntry 
      Caption         =   "Create Entry"
      Height          =   375
      Left            =   7440
      TabIndex        =   16
      Top             =   4560
      Width           =   1575
   End
   Begin VB.TextBox txtszEntryName 
      Height          =   285
      Left            =   7200
      TabIndex        =   15
      Top             =   960
      Width           =   1935
   End
   Begin VB.Frame Networking 
      Caption         =   "Networking"
      Height          =   2535
      Left            =   240
      TabIndex        =   9
      Top             =   4320
      Width           =   6495
      Begin VB.Frame NetworkProtocols 
         Caption         =   "Network Protocols"
         Height          =   855
         Left            =   240
         TabIndex        =   12
         Top             =   1440
         Width           =   5055
         Begin VB.CheckBox chkTCPIP 
            Caption         =   "TCP/IP"
            Height          =   255
            Left            =   240
            TabIndex        =   13
            Top             =   360
            Width           =   1215
         End
      End
      Begin VB.ComboBox cmbFrameProtocol 
         Height          =   315
         Left            =   240
         TabIndex        =   11
         Top             =   720
         Width           =   4095
      End
      Begin VB.Label Label5 
         Caption         =   "Type of dialup server I am calling:"
         Height          =   255
         Left            =   240
         TabIndex        =   10
         Top             =   360
         Width           =   2535
      End
   End
   Begin VB.Frame General 
      Caption         =   "General"
      Height          =   3495
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   6495
      Begin VB.TextBox txtszAreaCode 
         Height          =   285
         Left            =   5280
         TabIndex        =   19
         Top             =   1680
         Width           =   735
      End
      Begin VB.CheckBox chkCountryAreaCode 
         Caption         =   "Use Telephony Properties"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   2280
         Value           =   1  'Checked
         Width           =   2295
      End
      Begin VB.ComboBox cmbCountryCode 
         Height          =   315
         Left            =   1440
         TabIndex        =   6
         Top             =   1680
         Width           =   2415
      End
      Begin VB.TextBox txtszPhoneNumber 
         Height          =   285
         Left            =   1440
         TabIndex        =   4
         Top             =   1080
         Width           =   2415
      End
      Begin VB.ComboBox cmbRasDevices 
         Height          =   315
         Left            =   1440
         TabIndex        =   2
         Top             =   360
         Width           =   3735
      End
      Begin VB.Label Label4 
         Caption         =   "Area Code:"
         Height          =   285
         Left            =   4320
         TabIndex        =   7
         Top             =   1680
         Width           =   855
      End
      Begin VB.Label Label3 
         Caption         =   "Country Code:"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   1680
         Width           =   1095
      End
      Begin VB.Label Label2 
         Caption         =   "Phone Number:"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   1080
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "Dial Using:"
         Height          =   255
         Left            =   120
         TabIndex        =   1
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.Label Label6 
      Caption         =   "Phonebook Entry Name:"
      Height          =   255
      Left            =   7200
      TabIndex        =   14
      Top             =   600
      Width           =   1935
   End
End
Attribute VB_Name = "frmRasEntry"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' Copyright (c) 2002  Microsoft Corporation.  All Rights Reserved.
'
' Abstract: This sample shows how to create a phonebook entry (Dial Up
' Networking Connectoid) using the RasSetEntryProperties API. It also shows
' how to delete an exisitng entry using the RasDeleteEntry API.
'
' RAS APIs used:
'                    RasSetEntryProperties
'                    RasGetCountryInfo
'                    RasEnumDevices
'                    RasEnumEntries
'                    RasValidateEntryName
'                    RasDeleteEntry
'

Option Explicit

Private Sub chkCountryAreaCode_Click()
If chkCountryAreaCode.Value = 0 Then
    txtszAreaCode.Enabled = False
    cmbCountryCode.Enabled = False
Else
    txtszAreaCode.Enabled = True
    cmbCountryCode.Enabled = True
End If
End Sub

Private Sub cmdDeleteEntry_Click()
    Dim nRet As Long
    
    nRet = RasDeleteEntry(vbNullString, txtszEntryName.Text)
    If nRet = 0 Then
        MsgBox "Entry: " + txtszEntryName.Text + " deleted successfully"
        lstRasEntries.Clear
        Call GetEntries(lstRasEntries)
        txtszEntryName.Text = ""
    Else
         MsgBox "Error: Could not delete " + txtszEntryName.Text
    End If
End Sub

Private Sub cmdExit_Click()
 End
End Sub

Private Sub cmdRasSetEntry_Click()
    Dim lpRasEntry As RasEntry
    Dim nRet As Long
    Dim CountryCode As Long, CountryID As Long
    Dim DeviceType As String
    
    nRet = RasValidateEntryName(vbNullString, txtszEntryName.Text)
    If nRet = 183 Then
        MsgBox "Entry name " & txtszEntryName & " already exists"
        Exit Sub
    Else
        If nRet = 123 Then
            MsgBox "Entry name " & txtszEntryName & " is invalid"
            Exit Sub
        End If
    End If
    lpRasEntry.dwSize = LenB(lpRasEntry)
        
    If chkCountryAreaCode.Value = 1 Then
        lpRasEntry.dwfOptions = lpRasEntry.dwfOptions + RASEO_UseCountryAndAreaCodes
        Call GetCountryCode(cmbCountryCode, CountryCode, CountryID)
        lpRasEntry.dwCountryCode = CountryCode
        lpRasEntry.dwCountryID = CountryID
        nRet = lstrcpyn(lpRasEntry.szAreaCode(0), txtszAreaCode.Text, UBound(lpRasEntry.szAreaCode))
    End If

    nRet = lstrcpyn(lpRasEntry.szLocalPhoneNumber(0), txtszPhoneNumber.Text, UBound(lpRasEntry.szLocalPhoneNumber))
    Call GetDeviceType(cmbRasDevices, DeviceType)

    nRet = lstrcpyn(lpRasEntry.szDeviceType(0), DeviceType, UBound(lpRasEntry.szDeviceType))
    nRet = lstrcpyn(lpRasEntry.szDeviceName(0), cmbRasDevices, UBound(lpRasEntry.szDeviceName))

    If cmbFrameProtocol = "PPP: Windows 95/98/NT/2000, Internet" Then
        lpRasEntry.dwFramingProtocol = RASFP_Ppp
    Else
        lpRasEntry.dwFramingProtocol = RASFP_Slip
    End If

    If chkTCPIP.Value = 1 Then
        lpRasEntry.dwfNetProtocols = lpRasEntry.dwfNetProtocols + RASNP_Ip
    End If

    nRet = RasSetEntryProperties(vbNullString, txtszEntryName.Text, lpRasEntry, ByVal LenB(lpRasEntry), ByVal 0&, 0&)
   
    If nRet = 0 Then
         MsgBox "Entry: " + txtszEntryName.Text + " created successfully"
         lstRasEntries.AddItem txtszEntryName
         txtszEntryName.Text = ""
         txtszPhoneNumber.Text = ""
         txtszAreaCode.Text = ""
         chkTCPIP.Value = 0
      Else
         MsgBox "Got an error: " & nRet
      End If
End Sub

Private Sub Form_Load()
    Dim Index As Integer
    Call GetDevices(cmbRasDevices)
    cmbRasDevices.Text = cmbRasDevices.List(0)
    
    Call GetCountryInfo(cmbCountryCode)
    cmbCountryCode.Text = cmbCountryCode.List(0)
    
    Call GetFrameProtocols(cmbFrameProtocol)
    cmbFrameProtocol.Text = cmbFrameProtocol.List(0)
    Call GetEntries(lstRasEntries)
End Sub

Private Sub lstRasEntries_Click()
    txtszEntryName.Text = lstRasEntries.Text
End Sub
