VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Begin VB.Form AppInstall 
   Caption         =   "Install Application"
   ClientHeight    =   5730
   ClientLeft      =   10980
   ClientTop       =   2415
   ClientWidth     =   5070
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "AppInstall.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   5730
   ScaleWidth      =   5070
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2880
      TabIndex        =   18
      Top             =   5280
      Width           =   1215
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Height          =   375
      Index           =   0
      Left            =   720
      TabIndex        =   17
      Top             =   5280
      Width           =   1215
   End
   Begin VB.Frame fraOptions 
      Caption         =   "Install Options"
      Height          =   3855
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   4815
      Begin VB.TextBox txtPWD 
         Height          =   315
         IMEMode         =   3  'DISABLE
         Left            =   360
         PasswordChar    =   "*"
         TabIndex        =   9
         Top             =   2880
         Width           =   4095
      End
      Begin VB.TextBox txtUID 
         Height          =   315
         Left            =   360
         TabIndex        =   7
         Top             =   2280
         Width           =   4095
      End
      Begin VB.TextBox txtRemoteServerName 
         Height          =   315
         Left            =   360
         TabIndex        =   5
         Top             =   1680
         Width           =   4095
      End
      Begin VB.CheckBox chkRemoteServerInstall 
         Caption         =   "Remote Server Install"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   1080
         Width           =   4215
      End
      Begin VB.OptionButton optInstallUsers 
         Caption         =   "Install with Users"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   600
         Width           =   2175
      End
      Begin VB.CheckBox chkOverwriteFiles 
         Caption         =   "Overwrite Existing Files"
         Height          =   255
         Left            =   120
         TabIndex        =   10
         Top             =   3480
         Width           =   4000
      End
      Begin VB.OptionButton optInstallUsers 
         Caption         =   "Install without Users"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Value           =   -1  'True
         Width           =   2175
      End
      Begin VB.Label lblPWD 
         Caption         =   "Password:"
         Height          =   255
         Left            =   360
         TabIndex        =   8
         Top             =   2640
         Width           =   1935
      End
      Begin VB.Label lblUID 
         Caption         =   "User ID:"
         Height          =   255
         Left            =   360
         TabIndex        =   6
         Top             =   2040
         Width           =   1935
      End
      Begin VB.Label lblRemoteServerName 
         Caption         =   "Remote Server Name:"
         Height          =   255
         Left            =   360
         TabIndex        =   4
         Top             =   1440
         Width           =   1935
      End
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Enabled         =   0   'False
      Height          =   315
      Index           =   1
      Left            =   4440
      TabIndex        =   16
      Top             =   4800
      Width           =   375
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Height          =   315
      Index           =   0
      Left            =   4440
      TabIndex        =   13
      Top             =   4200
      Width           =   375
   End
   Begin VB.TextBox txtInstallDir 
      Height          =   315
      Left            =   240
      TabIndex        =   15
      Top             =   4800
      Width           =   4095
   End
   Begin VB.TextBox txtAppFile 
      Height          =   315
      Left            =   240
      TabIndex        =   12
      Top             =   4200
      Width           =   4095
   End
   Begin MSComDlg.CommonDialog cmdlgBrowse 
      Left            =   0
      Top             =   0
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Label1 
      Caption         =   "Install Directory:"
      Height          =   255
      Left            =   240
      TabIndex        =   14
      Top             =   4560
      Width           =   1935
   End
   Begin VB.Label lblAppFileDesc 
      Caption         =   "Application File:"
      Height          =   255
      Left            =   240
      TabIndex        =   11
      Top             =   3960
      Width           =   1935
   End
End
Attribute VB_Name = "AppInstall"
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

    Private Const kcmdOK                        As Integer = 0
    Private Const kcmdCancel                    As Integer = 1
    
    Private Const kcmdBrowseAppFile             As Integer = 0
    Private Const kcmdBrowseInstallDir          As Integer = 1
    
    Private Const koptNoUsers                   As Integer = 0
    Private Const koptUsers                     As Integer = 1
    
Private Sub ToggleRemoteServerState(Flag As Boolean)

    Dim lBackColor  As Long
    
    'Determine the backcolor for our text boxes
    If Flag Then
        lBackColor = &H80000005
    Else
        lBackColor = &H80000000
    End If
    
    With txtRemoteServerName
        .Text = ""
        .BackColor = lBackColor
        .Enabled = Flag
    End With
    
    With txtUID
        .Text = ""
        .BackColor = lBackColor
        .Enabled = Flag
    End With
    
    With txtPWD
        .Text = ""
        .BackColor = lBackColor
        .Enabled = Flag
    End With
    
    Exit Sub
    
End Sub

Private Function GetInstallOptions() As Long

    'Default return value
    GetInstallOptions = 0
    
    'Set flag that determines whether or not we are to install users along with the application
    Select Case True
        Case CBool(optInstallUsers(koptNoUsers).Value)
            GetInstallOptions = COMAdminInstallNoUsers
        Case CBool(optInstallUsers(koptNoUsers).Value)
            GetInstallOptions = COMAdminInstallUsers
    End Select
    
    'Set the flag as to whether or not we are to overwrite existing files
    If CBool(chkOverwriteFiles.Value) Then
        GetInstallOptions = GetInstallOptions + COMAdminInstallForceOverwriteOfFiles
    End If

    Exit Function
    
End Function
   
Private Sub chkRemoteServerInstall_Click()
    
    ToggleRemoteServerState CBool(chkRemoteServerInstall.Value)
    
    Exit Sub
    
End Sub

Private Sub cmdBrowse_Click(Index As Integer)

    On Error GoTo cmdBrowseErr:
    
    Dim sFilter         As String
    Dim sTitle          As String
    Dim iFilterIndex    As Integer
    
    'Common dialog setup
    Select Case Index
        Case kcmdBrowseAppFile
            sFilter = "All Files (*.*) | *.*"
            sTitle = "Select Application To Install"
            iFilterIndex = 1
        Case kcmdBrowseInstallDir
            'Browsing for directories not currently implemented
            GoTo cmdBrowseBail:
    End Select

    'Get the filename
    With cmdlgBrowse
        .CancelError = False
        .Flags = cdlOFNHideReadOnly
        .Filter = sFilter
        .DialogTitle = sTitle
        .FileName = ""
        .FilterIndex = iFilterIndex
        .ShowOpen
        txtAppFile.Text = .FileName
    End With

cmdBrowseBail:
    Exit Sub
    
cmdBrowseErr:
    If Not ErrHandler(Err.Number, Err.Description, "CompImport::cmdBrowse_Click") Then
        GoTo cmdBrowseBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub cmdMaint_Click(Index As Integer)

    On Error GoTo cmdMaintErr:
    
    Select Case Index
        Case kcmdOK
            'Perform local vs remote server installation
            If CBool(chkRemoteServerInstall.Value) Then
                Explorer.g_Catalog.InstallApplication Trim$(txtAppFile.Text), Trim$(txtInstallDir.Text), GetInstallOptions(), Trim$(txtUID.Text), Trim$(txtPWD.Text), Trim$(txtRemoteServerName.Text)
            Else
                Explorer.g_Catalog.InstallApplication Trim$(txtAppFile.Text), Trim$(txtInstallDir.Text), GetInstallOptions()
            End If
        Case kcmdCancel
            'do nothing
    End Select
    
cmdMaintBail:
    Unload Me
    Exit Sub
    
cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "AppInstall::cmdMaint_Click") Then
        GoTo cmdMaintBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub Form_Load()

    'Center this form over it's parent
    With Explorer
        CenterObject Me, CStr(.top) & ";" & CStr(.left) & ";" & CStr(.left + .Width) & ";" & CStr(.top + .Height)
    End With
    
    'Set the initial state for the controls used to gather remote server information
    ToggleRemoteServerState False
    
    Exit Sub
    
End Sub

Private Sub txtAppFile_GotFocus()
    
    'Select the currently displayed text
    SelectText txtAppFile
    
    Exit Sub
    
End Sub

Private Sub txtInstallDir_GotFocus()

    'Select the currently displayed text
    SelectText txtInstallDir
    
    Exit Sub
    
End Sub
