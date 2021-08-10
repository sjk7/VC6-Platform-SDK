VERSION 5.00
Begin VB.Form ChangePwd 
   Caption         =   "WinNT: Change Password"
   ClientHeight    =   2625
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4650
   LinkTopic       =   "Form1"
   ScaleHeight     =   2625
   ScaleWidth      =   4650
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Close"
      Height          =   375
      Left            =   2280
      TabIndex        =   11
      Top             =   2160
      Width           =   1095
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   960
      TabIndex        =   10
      Top             =   2160
      Width           =   1095
   End
   Begin VB.TextBox txtConfirmPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   9
      Top             =   1680
      Width           =   2415
   End
   Begin VB.TextBox txtNewPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   7
      Top             =   1320
      Width           =   2415
   End
   Begin VB.TextBox txtOldPassword 
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   5
      Top             =   960
      Width           =   2415
   End
   Begin VB.TextBox txtDomain 
      Height          =   285
      Left            =   2040
      TabIndex        =   3
      Top             =   600
      Width           =   2415
   End
   Begin VB.TextBox txtUserName 
      Height          =   285
      Left            =   2040
      TabIndex        =   1
      Top             =   240
      Width           =   2415
   End
   Begin VB.Label Label5 
      Caption         =   "&Confirm New Password:"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   1680
      Width           =   1815
   End
   Begin VB.Label Label4 
      Caption         =   "&New Password:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   1320
      Width           =   1455
   End
   Begin VB.Label Label3 
      Caption         =   "&Old Password:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   960
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "&Domain:"
      Height          =   255
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "&User Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "ChangePwd"
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
'  File:       changepwd.frm
'
'  Contents:   Change User's Password
'
'----------------------------------------------------------------------------

Private Sub cmdOK_Click()

Dim o As IADsOpenDSObject
Dim usr As IADsUser

On Error GoTo ErrMsg

If (txtNewPassword <> txtConfirmPassword) Then
   MsgBox "New and Confirm passwords must be the same"
   txtConfirmPassword.SetFocus
   Exit Sub
End If


Set o = GetObject("WinNT:")
Set usr = o.OpenDSObject("WinNT://" & txtDomain & "/" & txtUserName, txtUserName, txtOldPassword, 1)
usr.ChangePassword txtOldPassword, txtNewPassword
MsgBox ("Your password has been changed")
Exit Sub

ErrMsg:
  MsgBox ("Error: " & Err.Number & " " & Err.Description)
  txtUserName.SetFocus

End Sub


Private Sub cmdCancel_Click()
End
End Sub

