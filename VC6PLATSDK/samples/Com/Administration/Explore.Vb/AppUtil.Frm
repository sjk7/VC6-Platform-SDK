VERSION 5.00
Begin VB.Form AppUtil 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Start/Stop App"
   ClientHeight    =   1470
   ClientLeft      =   5505
   ClientTop       =   3090
   ClientWidth     =   4470
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "AppUtil.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1470
   ScaleWidth      =   4470
   ShowInTaskbar   =   0   'False
   Begin VB.PictureBox picIconStop 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   480
      Left            =   600
      Picture         =   "AppUtil.frx":000C
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   5
      Top             =   1800
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.PictureBox picIconStart 
      AutoSize        =   -1  'True
      BorderStyle     =   0  'None
      Height          =   480
      Left            =   0
      Picture         =   "AppUtil.frx":044E
      ScaleHeight     =   480
      ScaleWidth      =   480
      TabIndex        =   4
      Top             =   1800
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.TextBox txtAppID 
      Height          =   315
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   4215
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Index           =   0
      Left            =   480
      TabIndex        =   2
      Top             =   960
      Width           =   1215
   End
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2760
      TabIndex        =   3
      Top             =   960
      Width           =   1215
   End
   Begin VB.Label lblAppIDDesc 
      Caption         =   "Application ID:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3500
   End
End
Attribute VB_Name = "AppUtil"
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

    Private Const kFormTypeStart    As Integer = 0
    Private Const kformtypestop     As Integer = 1
    
    Private Const kcmdOK            As Integer = 0
    Private Const kcmdCancel        As Integer = 1
    
    Private m_lFormType             As Long
    
Public Property Let FormType(Flag As Long)

    'Set the specific form type to display (i.e., Start vs. Stop)
    m_lFormType = Flag
    
    'Set the forms icon depending upon what type of form we are displaying
    Select Case Flag
        Case kFormTypeStart
            Me.Icon = picIconStart.Picture
        Case kformtypestop
            Me.Icon = picIconStop.Picture
    End Select
    
    Exit Property
    
End Property

Public Property Let FormCaption(NewCaption As String)

    'Set the forms new caption
    Me.Caption = NewCaption
    
    Exit Property
    
End Property

Private Sub cmdMaint_Click(Index As Integer)

    On Error GoTo cmdMaintErr:
    
    Select Case Index
        Case kcmdOK
            'Attempt to execute application utility command depending upon which form type
            '   is displayed (i.e., Start vs. Stop)
            If (kFormTypeStart = m_lFormType) Then
                Explorer.g_Catalog.StartApplication Trim$(txtAppID.Text)
            Else
                Explorer.g_Catalog.ShutdownApplication Trim$(txtAppID.Text)
            End If
        Case kcmdCancel
            'do nothing
    End Select
    
cmdMaintBail:
    Unload Me
    Exit Sub

cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "StartStopApp::cmdMaint_Click") Then
        GoTo cmdMaintBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub Form_Load()

    'Set the default form type
    FormType = kFormTypeStart

    'Center this form over it's parent
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
