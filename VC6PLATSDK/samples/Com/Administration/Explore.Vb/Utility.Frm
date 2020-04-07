VERSION 5.00
Begin VB.Form Utility 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "COM+ Admin Utilities"
   ClientHeight    =   2010
   ClientLeft      =   6015
   ClientTop       =   3315
   ClientWidth     =   3855
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "Utility.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2010
   ScaleWidth      =   3855
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2280
      TabIndex        =   5
      Top             =   1560
      Width           =   1215
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Height          =   375
      Index           =   0
      Left            =   360
      TabIndex        =   4
      Top             =   1560
      Width           =   1215
   End
   Begin VB.Frame fraUtilityOptions 
      Caption         =   "Utility Options"
      Height          =   1335
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3615
      Begin VB.OptionButton optUtilityOption 
         Caption         =   "Refresh"
         Height          =   255
         Index           =   2
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   3000
      End
      Begin VB.OptionButton optUtilityOption 
         Caption         =   "Stop"
         Height          =   255
         Index           =   1
         Left            =   120
         TabIndex        =   2
         Top             =   600
         Width           =   3000
      End
      Begin VB.OptionButton optUtilityOption 
         Caption         =   "Start"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Value           =   -1  'True
         Width           =   3000
      End
   End
End
Attribute VB_Name = "Utility"
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

    Private Const kcmdOK                    As Integer = 0
    Private Const kcmdCancel                As Integer = 1
    
    Private Const koptUtilityOptionStart    As Integer = 0
    Private Const koptUtilityOptionStop     As Integer = 1
    Private Const koptUtilityOptionRefresh  As Integer = 2
    
    
Private Sub RefreshUtil()

    On Error GoTo RUErr:

    'Attempt to execute the refresh utility
    Explorer.g_Catalog.RefreshRouter
        
RUBail:
    Exit Sub

RUErr:
    If Not ErrHandler(Err.Number, Err.Description, "Utility::RefreshUtil") Then
        GoTo RUBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub StopUtil()

    On Error GoTo SUErr:

    'Attempt to execute the stop utility
    Explorer.g_Catalog.StopRouter
    
SUBail:
    Exit Sub

SUErr:
    If Not ErrHandler(Err.Number, Err.Description, "Utility::StopUtil") Then
        GoTo SUBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub StartUtil()

    On Error GoTo SUErr:

    'Attempt to execute the start utility
    Explorer.g_Catalog.StartRouter
    
SUBail:
    Exit Sub

SUErr:
    If Not ErrHandler(Err.Number, Err.Description, "Utility::StartUtil") Then
        GoTo SUBail:
    Else
        Resume Next
    End If
    
End Sub
    
Private Sub cmdMaint_Click(Index As Integer)

    On Error GoTo cmdMaintErr:
    
    'Execute the user specified command
    Select Case Index
        Case kcmdOK
            Select Case True
                Case CBool(optUtilityOption(koptUtilityOptionStart).Value)
                    StartUtil
                Case CBool(optUtilityOption(koptUtilityOptionStop).Value)
                    StopUtil
                Case CBool(optUtilityOption(koptUtilityOptionRefresh).Value)
                    RefreshUtil
            End Select
        Case kcmdCancel
            'do nothing
    End Select
    
cmdMaintBail:
    Unload Me
    Exit Sub
    
cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "RouterUtil::cmdMaint_Click") Then
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
        
    Exit Sub
    
End Sub
