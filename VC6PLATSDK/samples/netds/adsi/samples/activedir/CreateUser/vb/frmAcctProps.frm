VERSION 5.00
Begin VB.Form frmAcctProps 
   Caption         =   "Create User"
   ClientHeight    =   4995
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6480
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4995
   ScaleWidth      =   6480
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdFinish 
      Caption         =   "Finish"
      Default         =   -1  'True
      Height          =   375
      Left            =   3360
      TabIndex        =   10
      Top             =   4560
      Width           =   1335
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5040
      TabIndex        =   9
      Top             =   4560
      Width           =   1335
   End
   Begin VB.CommandButton cmdBack 
      Caption         =   "< Back"
      Height          =   375
      Left            =   1680
      TabIndex        =   8
      Top             =   4560
      Width           =   1335
   End
   Begin VB.CheckBox chkAcctDisabled 
      Caption         =   "Accout is disabled"
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   3840
      Width           =   4215
   End
   Begin VB.CheckBox chkNeverExpire 
      Caption         =   "Password Never expires"
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   3360
      Width           =   4215
   End
   Begin VB.CheckBox chkCantChange 
      Caption         =   "User cannot change password"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   2880
      Width           =   4215
   End
   Begin VB.CheckBox chkNextLogon 
      Caption         =   "User must change password at next logon"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   2400
      Width           =   4215
   End
   Begin VB.TextBox txtConfirmPwd 
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   1
      Top             =   1560
      Width           =   3495
   End
   Begin VB.TextBox txtPassword 
      Height          =   375
      IMEMode         =   3  'DISABLE
      Left            =   2040
      PasswordChar    =   "*"
      TabIndex        =   0
      Top             =   960
      Width           =   3495
   End
   Begin VB.Label lblConfirmPwd 
      Caption         =   "Confirm Password:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1560
      Width           =   1815
   End
   Begin VB.Label lblPassword 
      Caption         =   "Password:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1080
      Width           =   1815
   End
End
Attribute VB_Name = "frmAcctProps"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'This form is used to set the user account and password information

Private Sub chkCantChange_Click()
  Call CheckboxChange
End Sub

Private Sub chkNeverExpire_Click()
  Call CheckboxChange
End Sub

Private Sub chkNextLogon_Click()
  Call CheckboxChange
End Sub

Private Sub cmdBack_Click()
 frmProps.Hide 'Hide this form
 frmNames.Show 'Show previous
End Sub

Private Sub cmdCancel_Click()
' Exit app
 End
End Sub

Private Sub cmdFinish_Click()
'Make sure the passwords are the same
If txtPassword.Text <> txtConfirmPwd.Text Then
  MsgBox "The passwords do not match"
  Exit Sub
End If

' Set values to the globals
bMustChangePwd = CBool(chkNextLogon.Value)
bCannotChangePwd = CBool(chkCantChange.Value)
bPasswordNoExpire = CBool(chkNeverExpire.Value)
bAcctDisabled = CBool(chkAcctDisabled.Value)

frmProps.Hide 'Hide this form

CreateUserAccount  'Create the user
End Sub

Sub CheckboxChange()
' The user cannont be forced to change the password at next logon if the password will never expire
  If chkNextLogon And chkNeverExpire.Value Then
    MsgBox "Password never expire cannot be checked with change at next logon"
    chkNextLogon.Value = False
  End If
  
' The user cannot be forced to change the password at next logon if they cannot do so
  If chkNextLogon And chkCantChange.Value Then
     MsgBox "User cannot change password is check with must change at next logon"
     chkCantChange.Value = False
  End If
  
End Sub


Private Sub Form_Load()

End Sub
