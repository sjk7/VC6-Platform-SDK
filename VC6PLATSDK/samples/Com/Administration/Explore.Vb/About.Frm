VERSION 5.00
Begin VB.Form About 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About Explore"
   ClientHeight    =   2025
   ClientLeft      =   4245
   ClientTop       =   2985
   ClientWidth     =   4335
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "About.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2025
   ScaleWidth      =   4335
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdMaint 
      Caption         =   "System Info..."
      Height          =   375
      Index           =   1
      Left            =   2400
      TabIndex        =   5
      Top             =   1560
      Width           =   1400
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Height          =   375
      Index           =   0
      Left            =   600
      TabIndex        =   4
      Top             =   1560
      Width           =   1400
   End
   Begin VB.PictureBox picAppIcon 
      BorderStyle     =   0  'None
      Height          =   525
      Left            =   120
      Picture         =   "About.frx":000C
      ScaleHeight     =   525
      ScaleWidth      =   555
      TabIndex        =   0
      Top             =   120
      Width           =   550
   End
   Begin VB.Label lblCopyright 
      Caption         =   "lblCopyright"
      Height          =   255
      Left            =   840
      TabIndex        =   3
      Top             =   960
      Width           =   3375
   End
   Begin VB.Label lblAppVersion 
      Caption         =   "lblAppVersion"
      Height          =   255
      Left            =   840
      TabIndex        =   2
      Top             =   600
      Width           =   3375
   End
   Begin VB.Label lblAppTitle 
      Caption         =   "lblAppTitle"
      Height          =   255
      Left            =   840
      TabIndex        =   1
      Top             =   120
      Width           =   3375
   End
End
Attribute VB_Name = "About"
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
    
    Private Const kcmdOK        As Integer = 0
    Private Const kcmdSysInfo   As Integer = 1
    
Private Sub cmdMaint_Click(Index As Integer)

    Select Case Index
        Case kcmdOK
            'Close the form
            Unload Me
        Case kcmdSysInfo
            'Display the system information
            GetSysInfo
    End Select
    
    Exit Sub
    
End Sub

Private Sub Form_Load()

    'Center this form over it's parent
    With Explorer
        CenterObject Me, CStr(.top) & ";" & CStr(.left) & ";" & CStr(.left + .Width) & ";" & CStr(.top + .Height)
    End With
        
    'Fill in the applications properties
    With App
        lblAppTitle.Caption = .ProductName
        lblAppVersion.Caption = "Version " & .Major & "." & .Minor & "." & .Revision
        lblCopyright.Caption = "Copyright " & Chr(169) & " 1987 - 1998 Microsoft Corporation"
    End With
    
    Exit Sub
    
End Sub

