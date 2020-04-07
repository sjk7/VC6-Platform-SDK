VERSION 5.00
Begin VB.Form Connect 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Connect"
   ClientHeight    =   2175
   ClientLeft      =   6255
   ClientTop       =   4110
   ClientWidth     =   4110
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "Connect.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2175
   ScaleWidth      =   4110
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2400
      TabIndex        =   5
      Top             =   1680
      Width           =   1455
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   4
      Top             =   1680
      Width           =   1455
   End
   Begin VB.Frame fraComputer 
      Caption         =   "Computer"
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3855
      Begin VB.TextBox txtServerName 
         BackColor       =   &H80000000&
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   315
         Left            =   360
         TabIndex        =   3
         Top             =   960
         Width           =   3135
      End
      Begin VB.OptionButton optComputer 
         Caption         =   "A remote computer:"
         Height          =   375
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   600
         Width           =   2655
      End
      Begin VB.OptionButton optComputer 
         Caption         =   "This computer"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Value           =   -1  'True
         Width           =   2655
      End
   End
End
Attribute VB_Name = "Connect"
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

    Private Const kcmdOK                As Integer = 0
    Private Const kcmdCancel            As Integer = 1
    
    Private Const koptLocalComputer     As Integer = 0
    Private Const koptRemoteComputer    As Integer = 1

Private Sub ToggleCtls()

    'Toggle the state of the forms controls depending upon the currently selected
    '   connection type (i.e., local vs. remote)
    If CBool(optComputer(koptLocalComputer).Value) Then
        InitCtls
    Else
        With txtServerName
            .Text = ""
            .Locked = False
            .BackColor = &H80000005
            .SetFocus
        End With
    End If
    
    Exit Sub
    
End Sub

Private Sub InitCtls()
 
    'Set the default/initial state of the forms controls
    optComputer(koptLocalComputer).Value = True
    
    With txtServerName
        .Text = ""
        .Locked = True
        .BackColor = &H80000000
    End With
    
    Exit Sub
    
End Sub

Private Sub cmdMaint_Click(Index As Integer)

    Dim sServerName As String
        
    Me.MousePointer = vbHourglass
        
    Select Case Index
        Case kcmdOK
            'Define the server's name we are attempting to connect to
            If CBool(optComputer(koptLocalComputer).Value) Then
                sServerName = "local"
            Else
                sServerName = Trim$(txtServerName.Text)
            End If
            'Attempt to connect to the new server and display it's "root" contents
            With Explorer
                'Connect to the new server
                If sServerName <> "local" Then
                    .g_Catalog.Connect sServerName
                Else
                    .g_Catalog.Connect ""
                End If
                'Set the current collection to the new servers "root" collection
                Set .g_CurrCollection = .g_Catalog.GetCollection("Root")
                'Navigate to and display the new servers "root" collection
                .NavigateTo .g_CurrCollection
                'Update the main forms current computer name
                .lblServerName.Caption = sServerName
            End With
        Case kcmdCancel
            'do nothing
    End Select
    Me.MousePointer = vbNormal
    
cmdMaintBail:
    Unload Me
    Exit Sub
    
cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "ServerDlg::cmdMaint_Click") Then
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
    
    'Set/initialize the form's controls state
    InitCtls
    
    Exit Sub
    
End Sub

Private Sub optComputer_Click(Index As Integer)

    'Toggle the form's controls state to reflect desired connection type (i.e., local vs. remote)
    ToggleCtls
    
    Exit Sub
    
End Sub

Private Sub txtServerName_GotFocus()

    'Select the currently displayed text only if the current connect type is remote
    If CBool(optComputer(koptRemoteComputer).Value) Then
        SelectText txtServerName
    End If
    
    Exit Sub
    
End Sub
