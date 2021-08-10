VERSION 5.00
Begin VB.Form ResetPwd 
   Caption         =   "WinNT: Reset Password"
   ClientHeight    =   3705
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4650
   LinkTopic       =   "Form1"
   ScaleHeight     =   3705
   ScaleWidth      =   4650
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Administrator Credentials "
      Height          =   1455
      Left            =   240
      TabIndex        =   15
      Top             =   120
      Width           =   4215
      Begin VB.CheckBox chcCredential 
         Caption         =   "Use Current Credentials"
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   1080
         Width           =   2895
      End
      Begin VB.TextBox txtAdminPassword 
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   1560
         PasswordChar    =   "*"
         TabIndex        =   3
         Top             =   720
         Width           =   2415
      End
      Begin VB.TextBox txtAdminName 
         Height          =   285
         Left            =   1560
         TabIndex        =   1
         Text            =   "Administrator"
         Top             =   360
         Width           =   2415
      End
      Begin VB.Label lblAdminPassword 
         Caption         =   "Pass&word:"
         Height          =   255
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   855
      End
      Begin VB.Label lblAdminName 
         Caption         =   "Use&r Name:"
         Height          =   255
         Left            =   240
         TabIndex        =   0
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Close"
      Height          =   375
      Left            =   2280
      TabIndex        =   14
      Top             =   3240
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   960
      TabIndex        =   13
      Top             =   3240
      Width           =   1095
   End
   Begin VB.TextBox txtConfirmPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   12
      Top             =   2760
      Width           =   2415
   End
   Begin VB.TextBox txtNewPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   10
      Top             =   2400
      Width           =   2415
   End
   Begin VB.TextBox txtDomain 
      Height          =   285
      Left            =   2040
      TabIndex        =   8
      Top             =   2040
      Width           =   2415
   End
   Begin VB.TextBox txtUserName 
      Height          =   285
      Left            =   2040
      TabIndex        =   6
      Top             =   1680
      Width           =   2415
   End
   Begin VB.Label Label5 
      Caption         =   "&Confirm New Password:"
      Height          =   255
      Left            =   240
      TabIndex        =   11
      Top             =   2760
      Width           =   1815
   End
   Begin VB.Label Label4 
      Caption         =   "&New Password:"
      Height          =   255
      Left            =   240
      TabIndex        =   9
      Top             =   2400
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "&Domain:"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   2040
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "&User Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   1680
      Width           =   975
   End
End
Attribute VB_Name = "ResetPwd"
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
'  File: ResetPwd.frm
'
'  Contents: Reset Password, you must have Administrative privilage
'
'----------------------------------------------------------------------------

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

Private Sub ResetFields()
   txtNewPassword = ""
   txtConfirmPassword = ""
   txtUserName = ""
End Sub

Private Sub cmdCancel_Click()
  End
End Sub

Private Sub cmdOK_Click()

Dim o As IADsOpenDSObject
Dim usr As IADsUser

On Error GoTo ErrMsg

If (txtNewPassword <> txtConfirmPassword) Then
   MsgBox "New and Confirm passwords must be the same"
   txtConfirmPassword.SetFocus
   Exit Sub
End If


If (chcCredential.Value = 1) Then
    Set usr = GetObject("WinNT://" & txtDomain & "/" & txtUserName & ",user")
Else
    Set o = GetObject("WinNT:")
    Set usr = o.OpenDSObject("WinNT://" & txtDomain & "/" & txtUserName & ",user", txtAdminName, txtAdminPassword, 1)
End If

usr.SetPassword txtNewPassword
MsgBox ("Password has been reset")
ResetFields
Exit Sub

ErrMsg:
  MsgBox ("Error: " & Err.Number & " " & Err.Description)
  txtUserName.SetFocus

End Sub

