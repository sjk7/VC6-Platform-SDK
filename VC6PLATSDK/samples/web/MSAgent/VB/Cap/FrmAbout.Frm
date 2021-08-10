VERSION 5.00
Begin VB.Form frmAbout 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "About Microsoft Animation Previewer"
   ClientHeight    =   1425
   ClientLeft      =   4215
   ClientTop       =   1920
   ClientWidth     =   5730
   ClipControls    =   0   'False
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   983.56
   ScaleMode       =   0  'User
   ScaleWidth      =   5380.766
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.PictureBox picIcon 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      ClipControls    =   0   'False
      Height          =   540
      Left            =   240
      Picture         =   "frmAbout.frx":0000
      ScaleHeight     =   337.12
      ScaleMode       =   0  'User
      ScaleWidth      =   337.12
      TabIndex        =   1
      Top             =   240
      Width           =   540
   End
   Begin VB.CommandButton cmdOK 
      Cancel          =   -1  'True
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   345
      Left            =   4290
      TabIndex        =   0
      Top             =   225
      Width           =   1260
   End
   Begin VB.Label Label1 
      Caption         =   "(VB version)"
      Height          =   210
      Left            =   1050
      TabIndex        =   4
      Top             =   510
      Width           =   2970
   End
   Begin VB.Label lblTitle 
      Caption         =   "Microsoft Character Animation Previewer"
      ForeColor       =   &H00000000&
      Height          =   285
      Left            =   1050
      TabIndex        =   2
      Top             =   240
      Width           =   2970
   End
   Begin VB.Label lblVersion 
      Caption         =   "Copyright (c) 1998, Microsoft Corporation"
      Height          =   240
      Left            =   1050
      TabIndex        =   3
      Top             =   1095
      Width           =   3885
   End
End
Attribute VB_Name = "frmAbout"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdOK_Click()
  Unload Me
End Sub

Private Sub cmdSysInfo_Click()

End Sub

Private Sub Form_Load()
  'Me.Caption = "About " & App.Title
  lblVersion.Caption = "Version " & App.Major & "." & App.Minor & "." & App.Revision
  lblTitle.Caption = App.Title
End Sub

Private Sub lblDescription_Click()

End Sub
