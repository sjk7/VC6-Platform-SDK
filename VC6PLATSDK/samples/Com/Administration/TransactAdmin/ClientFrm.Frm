VERSION 5.00
Begin VB.Form ClientFrm 
   Caption         =   "COM+ Sample: Transacted Administration"
   ClientHeight    =   4215
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8355
   BeginProperty Font 
      Name            =   "MS Sans Serif"
      Size            =   9.75
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "ClientFrm.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   4215
   ScaleWidth      =   8355
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdClose 
      Caption         =   "C&lose"
      Height          =   495
      Left            =   3120
      TabIndex        =   8
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Frame frmUncommitted 
      Caption         =   "Uncommitted Work"
      Height          =   3495
      Left            =   4560
      TabIndex        =   6
      Top             =   240
      Width           =   3615
      Begin VB.ListBox lstUncommitted 
         Height          =   2940
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Width           =   3135
      End
   End
   Begin VB.Frame Frame2 
      Height          =   1815
      Left            =   480
      TabIndex        =   4
      Top             =   240
      Width           =   3855
      Begin VB.CommandButton cmdAdd 
         Caption         =   "Add >"
         Default         =   -1  'True
         Height          =   495
         Left            =   2640
         TabIndex        =   1
         Top             =   1200
         Width           =   1095
      End
      Begin VB.TextBox txtAppName 
         Height          =   375
         Left            =   240
         TabIndex        =   0
         Top             =   720
         Width           =   3255
      End
      Begin VB.Label Label3 
         Caption         =   "Application Name:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   360
         Width           =   3135
      End
   End
   Begin VB.CommandButton cmdAbort 
      Caption         =   "&Abort"
      Height          =   495
      Left            =   1800
      TabIndex        =   3
      Top             =   2160
      Width           =   1095
   End
   Begin VB.CommandButton cmdCommit 
      Caption         =   "&Commit"
      Height          =   495
      Left            =   480
      TabIndex        =   2
      Top             =   2160
      Width           =   1095
   End
End
Attribute VB_Name = "ClientFrm"
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

'
' AdminClient.vbp
'
' This application provides a simple UI for creating a COM+ application
' using the MkCOMApp component.  Users may create one or more applications
' then commit all of the changes or cause all changes to be rolled back
' by calling SetComplete or SetAbort, respectively.
'
Dim objAdmin As Object
' UI Dirty flag
Dim bDirty

Private Sub SetDirty(bFlag As Boolean)
    bDirty = bFlag
    cmdCommit.Enabled = lstUncommitted.ListCount > 0
    cmdAbort.Enabled = lstUncommitted.ListCount > 0
    cmdAdd.Enabled = bDirty
End Sub

Private Function CheckDirty(sMsg, Optional msgflags As Integer = vbYesNoCancel Or vbQuestion) As Integer
    If bDirty Then
        CheckDirty = MsgBox(sMsg, msgflags, "App add pending")
    End If
End Function

Private Sub ClearUI()
    lstUncommitted.Clear
    txtAppName.Text = ""
    txtAppName.SetFocus
    SetDirty False
End Sub

Private Function QueryClose() As Boolean
    Select Case CheckDirty("Changes are pending, are you sure you want to exit?", vbYesNo Or vbQuestion)
        Case 0
            ' Not dirty
             QueryClose = True
        Case vbYes
             QueryClose = True
        Case vbNo
             QueryClose = False
    End Select
End Function
' Abort the transaction
Private Sub cmdAbort_Click()
    If MsgBox("Abort transaction - are you sure?", vbYesNo Or vbQuestion) = vbYes Then
        objAdmin.CommitChanges False
        ClearUI
    End If
End Sub

Private Sub cmdClose_Click()
    Unload Me
End Sub

' Commit the transaction
Private Sub cmdCommit_Click()

    Select Case CheckDirty("Do you want to add application before committing?")
        Case 0
            ' Not dirty
        Case vbYes
            cmdAdd_Click
        Case vbCancel
            Exit Sub
        Case vbNo
            ' Do nothing
    End Select
    objAdmin.CommitChanges True
    
    ClearUI
End Sub

Private Sub cmdAdd_Click()
    '
    ' Clicked Add button
    ' Add new application and reset UI
    '
    objAdmin.CreateApp txtAppName.Text
    
    ' Add to uncommitted work list
    lstUncommitted.AddItem "Add application """ + txtAppName.Text + """"
    txtAppName.Text = ""
    txtAppName.SetFocus
End Sub

Private Sub Form_Load()
    On Error GoTo errHandler
    SetDirty False
    Set objAdmin = CreateObject("TransactAdmin.MkCOMApp")
    Exit Sub
errHandler:
    MsgBox "An error has occured while attempting to create TransactAdmin.MkCOMApp," + _
    "check that you have built and registered the TransactAdmin application prior to running the AdminClient."
    End
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
    If Not QueryClose Then
        Cancel = 1
    End If
End Sub

Private Sub txtAppName_Change()
    '
    ' Typed characters in text box.  Make sure that leading spaces are
    ' trimmed.  If text is non null, then enable UI for adding
    ' a new application.
    '
    txtAppName.Text = LTrim(txtAppName.Text)
    SetDirty (txtAppName.Text <> "")
End Sub
