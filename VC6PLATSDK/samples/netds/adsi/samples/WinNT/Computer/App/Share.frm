VERSION 5.00
Begin VB.Form frmShare 
   Caption         =   "New Share"
   ClientHeight    =   1695
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4215
   LinkTopic       =   "Form1"
   ScaleHeight     =   1695
   ScaleWidth      =   4215
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtPath 
      Height          =   330
      Left            =   1290
      TabIndex        =   3
      Top             =   645
      Width           =   2745
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2205
      TabIndex        =   5
      Top             =   1200
      Width           =   1050
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   975
      TabIndex        =   4
      Top             =   1185
      Width           =   1050
   End
   Begin VB.TextBox txtNewShare 
      Height          =   315
      Left            =   1290
      TabIndex        =   1
      Top             =   150
      Width           =   2715
   End
   Begin VB.Label Label2 
      Caption         =   "&Path:"
      Height          =   210
      Left            =   105
      TabIndex        =   2
      Top             =   705
      Width           =   1080
   End
   Begin VB.Label Label1 
      Caption         =   "&Share Name:"
      Height          =   300
      Left            =   75
      TabIndex        =   0
      Top             =   195
      Width           =   1170
   End
End
Attribute VB_Name = "frmShare"
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
'  File:       frmShare.frm
'
'  Contents:   Accepting Share Information
'
'----------------------------------------------------------------------------

Private Sub cmdCancel_Click()
 Hide
End Sub

Private Sub cmdOK_Click()
 If (txtNewShare = "" Or txtPath = "") Then
     MsgBox ("Must enter share name and path name")
     Exit Sub
 End If
 
 
 Hide
End Sub

Private Sub Form_Load()
  txtNewShare = ""
  txtPath = ""
End Sub

