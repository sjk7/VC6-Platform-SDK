VERSION 5.00
Begin VB.Form frmMain 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "User Events - Visual Basic"
   ClientHeight    =   2430
   ClientLeft      =   5040
   ClientTop       =   5325
   ClientWidth     =   8205
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   2430
   ScaleWidth      =   8205
   Begin VB.Frame Frame7 
      Caption         =   "Language"
      Height          =   735
      Left            =   0
      TabIndex        =   10
      Top             =   1200
      Width           =   1815
      Begin VB.OptionButton VB 
         Caption         =   "VB"
         Height          =   255
         Left            =   600
         TabIndex        =   12
         Top             =   360
         Width           =   255
      End
      Begin VB.OptionButton VC 
         Caption         =   "Option2"
         Height          =   255
         Left            =   1320
         TabIndex        =   11
         Top             =   360
         Width           =   255
      End
      Begin VB.Label Label12 
         Alignment       =   2  'Center
         Caption         =   "Visual Basic"
         Height          =   375
         Left            =   120
         TabIndex        =   14
         Top             =   240
         Width           =   495
      End
      Begin VB.Label Label11 
         Alignment       =   2  'Center
         Caption         =   "Visual C++"
         Height          =   375
         Left            =   840
         TabIndex        =   13
         Top             =   240
         Width           =   495
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Result"
      Height          =   1095
      Left            =   1920
      TabIndex        =   7
      Top             =   1200
      Width           =   6255
      Begin VB.TextBox Result 
         Height          =   735
         Left            =   120
         MultiLine       =   -1  'True
         TabIndex        =   8
         Top             =   240
         Width           =   6015
      End
   End
   Begin VB.CommandButton Close 
      Cancel          =   -1  'True
      Caption         =   "&Close"
      Height          =   375
      Left            =   5760
      TabIndex        =   4
      Top             =   720
      Width           =   2415
   End
   Begin VB.CommandButton btnPost 
      Caption         =   "&Post"
      Default         =   -1  'True
      Height          =   375
      Index           =   0
      Left            =   5760
      TabIndex        =   3
      Top             =   240
      Width           =   2415
   End
   Begin VB.Frame Frame1 
      Caption         =   "Your Account Information"
      Height          =   855
      Left            =   0
      TabIndex        =   0
      Top             =   120
      Width           =   5655
      Begin VB.TextBox Account 
         Height          =   285
         Left            =   1860
         TabIndex        =   1
         Top             =   360
         Width           =   1215
      End
      Begin VB.TextBox Amount 
         Height          =   285
         Left            =   4200
         TabIndex        =   2
         Top             =   360
         Width           =   1215
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         Caption         =   "&Account Number"
         Height          =   315
         Left            =   240
         TabIndex        =   9
         Top             =   360
         Width           =   1515
      End
      Begin VB.Label Label3 
         Caption         =   "Label3"
         Height          =   15
         Left            =   300
         TabIndex        =   6
         Top             =   2100
         Width           =   615
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         Caption         =   "A&mount"
         Height          =   315
         Left            =   3240
         TabIndex        =   5
         Top             =   360
         Width           =   915
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ==============================================================================
' Filename: VBBank.vbp
'
' Summary:  Visual Basic client for demonstrating User Events in COM+
' Classes:  Account.cls
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

Option Explicit

Private Sub Form_Load()
    Account = 1
    Amount = 100
    Result = ""
    VB = 1
End Sub

Private Sub btnPost_Click(Index As Integer)
    
    Screen.MousePointer = 11
    On Error GoTo ErrorHandler
    
    ' Decide which language to use
    Dim ProgID As String
    If VC = True Then
        ProgID = "VCBank.Account"
    Else ' VB is the default
        ProgID = "VBBank.Account"
    End If
    
    ' Create UserEvents object
    On Error GoTo objError
    Dim obj As Object
    Set obj = CreateObject(ProgID)
    On Error GoTo ErrorHandler
    
    If obj Is Nothing Then
        Screen.MousePointer = 0
        MsgBox "Create object " + ProgID + "failed."
        Exit Sub
    End If
    
    ' Call the object
    Dim Res As Variant
    Res = obj.Post(CLng(Account), CLng(Amount))
    
    Set obj = Nothing
   
    Result = Res
    Screen.MousePointer = 0
    Exit Sub
    
objError:
    MsgBox "Error " & Err.Number & ": Make sure the Sample Bank package has been correctly installed in COM+."
    Screen.MousePointer = 0
    Err.Clear
    Exit Sub
    
ErrorHandler:
    Screen.MousePointer = 0
    MsgBox Err.Number & "(" & Err.Source & ") :" & Err.Description
    Err.Clear

End Sub

Private Sub Close_Click()
    End
End Sub

