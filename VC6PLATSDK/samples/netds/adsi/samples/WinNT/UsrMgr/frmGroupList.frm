VERSION 5.00
Begin VB.Form frmGroupList 
   Caption         =   "Group Browser"
   ClientHeight    =   4320
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3795
   LinkTopic       =   "Form1"
   ScaleHeight     =   4320
   ScaleWidth      =   3795
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox lstGroupPath 
      Height          =   255
      Left            =   3360
      TabIndex        =   3
      Top             =   3840
      Visible         =   0   'False
      Width           =   375
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2040
      TabIndex        =   2
      Top             =   3840
      Width           =   975
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Height          =   375
      Left            =   720
      TabIndex        =   1
      Top             =   3840
      Width           =   1095
   End
   Begin VB.ListBox lstGroup 
      Height          =   3375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   3255
   End
End
Attribute VB_Name = "frmGroupList"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       frmGroupList.frm
'
'  Contents:   List all Groups in a list box for group picker
'
'----------------------------------------------------------------------------

Dim sGroupPath As String

Public Sub SetContainer(cont As IADsContainer)
   Dim grp As IADs
   
   'Reset the list boxex
   lstGroup.Clear
   lstGroupPath.Clear
   sGroupPath = ""
   
   cont.Filter = Array("Group")
   For Each grp In cont
     lstGroup.AddItem grp.Name & " (" & GetGroupType(grp) & ")"
     lstGroupPath.AddItem grp.ADsPath
   Next
End Sub

Public Function GetGroupPath() As String
   GetGroupPath = sGroupPath
End Function

Private Sub cmdCancel_Click()
   sGroupPath = ""
   frmGroupList.Hide
End Sub

Private Sub cmdOK_Click()
   sGroupPath = lstGroupPath.List(lstGroup.ListIndex)
   frmGroupList.Hide
End Sub




Private Sub lstGroup_DblClick()
  cmdOK_Click
End Sub
