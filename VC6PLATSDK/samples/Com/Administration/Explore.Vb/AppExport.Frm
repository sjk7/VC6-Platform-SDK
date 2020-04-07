VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form AppExport 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Export Application"
   ClientHeight    =   4080
   ClientLeft      =   6150
   ClientTop       =   4590
   ClientWidth     =   4935
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "AppExport.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4080
   ScaleWidth      =   4935
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Enabled         =   0   'False
      Height          =   315
      Left            =   4440
      TabIndex        =   9
      Top             =   3120
      Width           =   375
   End
   Begin VB.TextBox txtExportFileSpec 
      Height          =   315
      Left            =   120
      TabIndex        =   8
      Top             =   3120
      Width           =   4215
   End
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2880
      TabIndex        =   11
      Top             =   3600
      Width           =   1215
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Height          =   375
      Index           =   0
      Left            =   600
      TabIndex        =   10
      Top             =   3600
      Width           =   1215
   End
   Begin VB.TextBox txtAppID 
      Height          =   315
      Left            =   120
      TabIndex        =   6
      Top             =   2520
      Width           =   4215
   End
   Begin VB.Frame fraOptions 
      Caption         =   "Export Client Only"
      Height          =   2055
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   4695
      Begin VB.OptionButton optExportUsers 
         Caption         =   "Export Clients"
         Height          =   375
         Index           =   2
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   4500
      End
      Begin VB.CheckBox chkOverwriteFiles 
         Caption         =   "Overwrite Files"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   1560
         Width           =   4500
      End
      Begin VB.OptionButton optExportUsers 
         Caption         =   "Export Users"
         Height          =   375
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   600
         Width           =   4500
      End
      Begin VB.OptionButton optExportUsers 
         Caption         =   "Do not export users"
         Height          =   375
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Value           =   -1  'True
         Width           =   4500
      End
   End
   Begin MSComDlg.CommonDialog cmdlgBrowse 
      Left            =   0
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label lblExportFileSpecDesc 
      Caption         =   "Exported File Path and Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   2880
      Width           =   4200
   End
   Begin VB.Label Label1 
      Caption         =   "Application ID:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   2280
      Width           =   4200
   End
End
Attribute VB_Name = "AppExport"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ----------------------------------------------------------------------------
' 
' This file is part of the Microsoft COM+ Samples.
' 
' Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
' 
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation. See these other
' materials for detailed information regarding Microsoft code samples.
' 
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
' 
' ----------------------------------------------------------------------------

Option Explicit

    Private Const kcmdOK            As Integer = 0
    Private Const kcmdCancel        As Integer = 1
    
    Private Const koptNoUsers       As Integer = 0
    Private Const koptUsers         As Integer = 1
    Private Const koptClientOnly    As Integer = 2
    
Private Function GetExportOptions() As Long

    'Default return value
    GetExportOptions = 0
    
    'Set flag that determines whether or not we are to install users or clients
    Select Case True
        Case CBool(optExportUsers(koptNoUsers).Value)
            GetExportOptions = COMAdminExportNoUsers
        Case CBool(optExportUsers(koptUsers).Value)
            GetExportOptions = COMAdminExportUsers
        Case CBool(optExportUsers(koptClientOnly).Value)
            GetExportOptions = COMAdminExportApplicationProxy
    End Select
    
    'Set the flag as to whether or not we are to overwrite existing files
    If CBool(chkOverwriteFiles.Value) Then
        GetExportOptions = GetExportOptions + COMAdminInstallForceOverwriteOfFiles
    End If

    Exit Function
    
End Function

Private Sub cmdMaint_Click(Index As Integer)

    On Error GoTo cmdMaintErr:
    
    Select Case Index
        Case kcmdOK
            'Attempt to export the application
            Explorer.g_Catalog.ExportApplication Trim$(txtAppID.Text), Trim$(txtExportFileSpec.Text), GetExportOptions()
        Case kcmdCancel
            'do nothing
    End Select
    
cmdMaintBail:
    Unload Me
    Exit Sub
    
cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "AppExport::cmdMaint_Click") Then
        GoTo cmdMaintBail:
    Else
        Resume Next
    End If
    

End Sub

Private Sub Form_Load()

    'Center the form over it's parent
    With Explorer
        CenterObject Me, CStr(.top) & ";" & CStr(.left) & ";" & CStr(.left + .Width) & ";" & CStr(.top + .Height)
    End With
        
    Exit Sub
    
End Sub

Private Sub txtAppID_GotFocus()

    'Select the currently displayed text
    SelectText txtAppID
    
    Exit Sub
    
End Sub

Private Sub txtExportFileSpec_GotFocus()

    'Select the currently displayed text
    SelectText txtExportFileSpec
    
    Exit Sub
    
End Sub
