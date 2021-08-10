VERSION 5.00
Begin VB.Form frmSetNames 
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
   Begin VB.CommandButton cmdChange 
      Caption         =   "Change"
      Height          =   375
      Left            =   5160
      TabIndex        =   18
      Top             =   120
      Width           =   1215
   End
   Begin VB.TextBox txtContCanName 
      BackColor       =   &H80000013&
      Height          =   375
      Left            =   2040
      Locked          =   -1  'True
      TabIndex        =   17
      Top             =   120
      Width           =   2895
   End
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   5160
      TabIndex        =   8
      Top             =   4560
      Width           =   1335
   End
   Begin VB.CommandButton cmdNext 
      Caption         =   "Next >"
      Default         =   -1  'True
      Height          =   375
      Left            =   3600
      TabIndex        =   7
      Top             =   4560
      Width           =   1335
   End
   Begin VB.TextBox txtSAMAcctName 
      Height          =   375
      Left            =   3120
      TabIndex        =   6
      Top             =   3840
      Width           =   3135
   End
   Begin VB.TextBox txtSAMDomName 
      BackColor       =   &H80000013&
      Height          =   375
      Left            =   0
      Locked          =   -1  'True
      TabIndex        =   15
      Top             =   3840
      Width           =   3015
   End
   Begin VB.ComboBox cmbUPN 
      Height          =   315
      ItemData        =   "frmSetNames.frx":0000
      Left            =   3240
      List            =   "frmSetNames.frx":0002
      Style           =   2  'Dropdown List
      TabIndex        =   5
      Top             =   2760
      Width           =   3135
   End
   Begin VB.TextBox txtUPN 
      Height          =   375
      Left            =   0
      TabIndex        =   4
      Top             =   2760
      Width           =   3015
   End
   Begin VB.TextBox txtFull 
      Height          =   375
      Left            =   1440
      TabIndex        =   3
      Top             =   1800
      Width           =   4215
   End
   Begin VB.TextBox txtInitials 
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   840
      Width           =   975
   End
   Begin VB.TextBox txtLast 
      Height          =   375
      Left            =   1440
      TabIndex        =   2
      Top             =   1320
      Width           =   4215
   End
   Begin VB.TextBox txtFirst 
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   840
      Width           =   2055
   End
   Begin VB.Label lblCreateIn 
      Caption         =   "Create In:"
      Height          =   375
      Left            =   720
      TabIndex        =   16
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "User Logon Name (Pre-Windows 2000):"
      Height          =   255
      Left            =   120
      TabIndex        =   14
      Top             =   3360
      Width           =   3135
   End
   Begin VB.Label lblUPN 
      Caption         =   "User Logon Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   13
      Top             =   2400
      Width           =   1815
   End
   Begin VB.Label lblFull 
      Caption         =   "Full Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   12
      Top             =   1800
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Initials:"
      Height          =   255
      Left            =   3600
      TabIndex        =   11
      Top             =   840
      Width           =   735
   End
   Begin VB.Label lblLast 
      Caption         =   "Last Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label lblFirst 
      Caption         =   "First Name:"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   840
      Width           =   1215
   End
End
Attribute VB_Name = "frmSetNames"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'This form will set the names and UPN for the new account

Private Sub cmdCancel_Click()
' Exit app
End
End Sub

Private Sub cmdChange_Click()
 Dim strNewCont As String
 ' Prompt user for a DN, set the container, and retrieve the canonicalName
 strNewCont = InputBox("Please input a distinguished name for the desired container.  The current containers DN is :" + vbLf + vbLf + strContainerDN, "Set Container")
 SetContainer strNewCont
 txtContCanName.Text = strContainerCanName
End Sub

Private Sub cmdNext_Click()
' Set the global variables to the values
strFirst = Trim(txtFirst.Text)
strLast = Trim(txtLast.Text)
strFullName = Trim(txtFull.Text)
strUPN = Trim(txtUPN) + cmbUPN.Text
strInitials = Trim(txtInitials.Text)

' SAM account name must be less then 20 chars
If txtSAMAcctName.Text = "" Or Len(txtSAMAcctName.Text) < 20 Then
  strSAMAcctName = Trim(txtSAMAcctName.Text)
Else
  MsgBox "DownLevel account name must be present and less then 20 chars"
  Exit Sub
End If

If txtFull.Text = "" Then
  MsgBox "You must have a full name"
  Exit Sub
End If

frmNames.Hide  'Hide this form
frmProps.Show  'Show the next
End Sub

'This form will set the names and UPN for the new account

Private Sub Form_Load()
'Load the domain and UPN suffixes
txtSAMDomName.Text = strDomainName + "\"
txtContCanName.Text = strContainerCanName
For Each vItem In strPossibleUPN
 cmbUPN.AddItem "@" + vItem
Next
cmbUPN.ListIndex = 0
End Sub

Sub UpdateFullName()
 ' Build the fullname
 If Trim(txtInitials.Text) <> "" Then
  txtFull.Text = txtFirst.Text + " " + txtInitials.Text + ". " + txtLast.Text
 Else
  txtFull.Text = txtFirst.Text + " " + txtLast.Text
 End If
End Sub

Private Sub txtFirst_Change()
 UpdateFullName
End Sub


Private Sub txtInitials_Change()
 UpdateFullName
End Sub

Private Sub txtLast_Change()
 UpdateFullName
End Sub

Private Sub txtUPN_Change()
'Build the SAM account name
 txtSAMAcctName.Text = txtUPN.Text
End Sub
