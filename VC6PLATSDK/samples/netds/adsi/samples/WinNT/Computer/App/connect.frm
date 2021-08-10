VERSION 5.00
Begin VB.Form frmConnect 
   Caption         =   "WinnT: Connect To"
   ClientHeight    =   3900
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4515
   LinkTopic       =   "Form2"
   ScaleHeight     =   3900
   ScaleWidth      =   4515
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame2 
      Caption         =   "Administrator Credentials "
      Height          =   1455
      Left            =   105
      TabIndex        =   7
      Top             =   0
      Width           =   4215
      Begin VB.TextBox txtAdminName 
         Height          =   285
         Left            =   1560
         TabIndex        =   10
         Text            =   "Administrator"
         Top             =   360
         Width           =   2415
      End
      Begin VB.TextBox txtAdminPassword 
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   1560
         PasswordChar    =   "*"
         TabIndex        =   9
         Top             =   720
         Width           =   2415
      End
      Begin VB.CheckBox chcCredential 
         Caption         =   "Use Current Credentials"
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   1080
         Width           =   2895
      End
      Begin VB.Label lblAdminName 
         Caption         =   "Use&r Name:"
         Height          =   255
         Left            =   240
         TabIndex        =   12
         Top             =   360
         Width           =   975
      End
      Begin VB.Label lblAdminPassword 
         Caption         =   "Pass&word:"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   720
         Width           =   855
      End
   End
   Begin VB.CommandButton cmdCancel 
      Caption         =   "Cancel"
      Height          =   315
      Left            =   2100
      TabIndex        =   5
      Top             =   3450
      Width           =   1215
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   315
      Left            =   855
      TabIndex        =   4
      Top             =   3450
      Width           =   1095
   End
   Begin VB.TextBox txtConnect 
      Height          =   315
      Left            =   315
      TabIndex        =   2
      Top             =   2820
      Width           =   2490
   End
   Begin VB.OptionButton optComputer 
      Caption         =   "Computer"
      Height          =   255
      Left            =   315
      TabIndex        =   1
      Top             =   2115
      Width           =   1575
   End
   Begin VB.OptionButton optDomain 
      Caption         =   "Domain"
      Height          =   255
      Left            =   330
      TabIndex        =   0
      Top             =   1815
      Width           =   1575
   End
   Begin VB.Frame Frame1 
      Caption         =   "Connect To"
      Height          =   1740
      Left            =   150
      TabIndex        =   3
      Top             =   1560
      Width           =   4170
      Begin VB.Label Label1 
         Caption         =   "Domain/Computer Name:"
         Height          =   195
         Left            =   180
         TabIndex        =   6
         Top             =   990
         Width           =   2130
      End
   End
End
Attribute VB_Name = "frmConnect"
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
'  File:       frmConnect.frm
'
'  Contents:   Connection Dialog
'
'----------------------------------------------------------------------------

Dim usrName As String
Dim usrPassword As String

Private Sub chcCredential_Click()
If (chcCredential.Value = 1) Then
  bCheck = False
 Else
  bCheck = True
 End If
 
 'Now set the controls based on the credential mode
 txtAdminName.Enabled = bCheck
 lblAdminName.Enabled = bCheck
 txtAdminPassword.Enabled = bCheck
 lblAdminPassword.Enabled = bCheck
End Sub

Private Sub cmdCancel_Click()
  frmConnect.Hide
  frmConnect.Tag = ""
End Sub


Private Sub cmdOK_Click()
 
If (optComputer) Then
  bind = txtConnect & ",computer"
Else
  bind = txtConnect
End If
 frmConnect.Tag = bind
 
usrName = ""
usrPassword = ""
If (chcCredential = 0) Then
   usrName = txtAdminName
   usrPassword = txtAdminPassword
End If
 
frmConnect.Hide
End Sub

Private Sub Form_Load()
usrName = ""
usrPassword = ""
chcCredential = 1
chcCredential_Click
End Sub

Public Function GetUserName() As String
  GetUserName = usrName
End Function

Public Function GetPassword() As String
  GetPassword = usrPassword
End Function

