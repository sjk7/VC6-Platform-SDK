VERSION 5.00
Begin VB.Form frmFileTest 
   Caption         =   "Compensating Resource Manager sample - create/delete files"
   ClientHeight    =   3615
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6465
   LinkTopic       =   "Form1"
   ScaleHeight     =   3615
   ScaleWidth      =   6465
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame frmLanguage 
      Caption         =   "Use CRM developed with:"
      Height          =   2055
      Left            =   3360
      TabIndex        =   6
      Top             =   1200
      Width           =   2535
      Begin VB.OptionButton optVJ 
         Caption         =   "Visual J++"
         Height          =   375
         Left            =   360
         TabIndex        =   9
         Top             =   1440
         Width           =   1095
      End
      Begin VB.OptionButton optVB 
         Caption         =   "Visual Basic"
         Height          =   255
         Left            =   360
         TabIndex        =   8
         Top             =   960
         Width           =   1335
      End
      Begin VB.OptionButton optVC 
         Caption         =   "Visual C"
         Height          =   255
         Left            =   360
         TabIndex        =   7
         Top             =   480
         Value           =   -1  'True
         Width           =   1335
      End
   End
   Begin VB.CommandButton cmdAbort 
      Caption         =   "Abort"
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   2880
      Width           =   1695
   End
   Begin VB.CommandButton cmdCommit 
      Caption         =   "Commit"
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   2280
      Width           =   1695
   End
   Begin VB.CommandButton cmdDeleteFile 
      Caption         =   "Delete File"
      Height          =   375
      Left            =   360
      TabIndex        =   3
      Top             =   1680
      Width           =   1695
   End
   Begin VB.CommandButton cmdCreateFile 
      Caption         =   "Create File"
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Top             =   1080
      Width           =   1695
   End
   Begin VB.TextBox txtFileName 
      Height          =   285
      Left            =   360
      TabIndex        =   0
      Top             =   480
      Width           =   5895
   End
   Begin VB.Label Label1 
      Caption         =   "Filename:"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   120
      Width           =   1935
   End
End
Attribute VB_Name = "frmFileTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

' This file is part of the Microsoft COM Technology Samples.
'
' Copyright (C) 1998 Microsoft Corporation. All rights reserved.
'
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation. See these other
' materials for detailed information regarding Microsoft code samples.
'
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.


Option Explicit

Dim FilesTest As CrmFilesTest

Private Sub cmdAbort_Click()

    On Error GoTo ErrorHandler
    
    FilesTest.Abort
    
    Exit Sub
    
ErrorHandler:

    ' allow mtsErrCtxAborted
    
    Dim strPrompt As String
    
    If (Err.Number <> mtsErrCtxAborted) Then
    
        strPrompt = "Error on Abort: " + Str$(Err.Number)
        
        MsgBox strPrompt
    
    End If
    
End Sub

Private Sub cmdCommit_Click()

    On Error GoTo ErrorHandler
    
    FilesTest.Commit
    
    Exit Sub
    
ErrorHandler:

    ' allow mtsErrCtxAborted
    
    Dim strPrompt As String
    
    If (Err.Number <> mtsErrCtxAborted) Then
    
        strPrompt = "Error on Commit: " + Str$(Err.Number)
        
        MsgBox strPrompt
    
    End If
    
End Sub

Private Sub cmdCreateFile_Click()

    Dim SelectedLanguage As Long
    
    If optVC Then SelectedLanguage = 0
    If optVB Then SelectedLanguage = 1
    If optVJ Then SelectedLanguage = 2
    
    FilesTest.Language = SelectedLanguage
    
    FilesTest.FileName = txtFileName
    
    FilesTest.CreateFile
    
End Sub

Private Sub cmdDeleteFile_Click()

Dim SelectedLanguage As Long
    
    If optVC Then SelectedLanguage = 0
    If optVB Then SelectedLanguage = 1
    If optVJ Then SelectedLanguage = 2
    
    FilesTest.Language = SelectedLanguage
    
    FilesTest.FileName = txtFileName
    
    FilesTest.DeleteFile
    
End Sub

Private Sub Form_Load()

    Set FilesTest = New CrmFilesTest

End Sub

Private Sub Form_Unload(Cancel As Integer)

    Set FilesTest = Nothing
    
End Sub
