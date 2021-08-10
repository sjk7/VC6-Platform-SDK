VERSION 5.00
Begin VB.Form frmConnect 
   Caption         =   "Connect to Computer"
   ClientHeight    =   1245
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4485
   LinkTopic       =   "Form1"
   ScaleHeight     =   1245
   ScaleWidth      =   4485
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   2310
      TabIndex        =   3
      Top             =   750
      Width           =   1065
   End
   Begin VB.CommandButton cmdOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   960
      TabIndex        =   2
      Top             =   750
      Width           =   1095
   End
   Begin VB.TextBox txtComputerName 
      Height          =   300
      Left            =   180
      TabIndex        =   1
      Top             =   345
      Width           =   4065
   End
   Begin VB.Label lblComputer 
      Caption         =   "Computer Name"
      Height          =   225
      Left            =   195
      TabIndex        =   0
      Top             =   90
      Width           =   3450
   End
End
Attribute VB_Name = "frmConnect"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False



Private Sub cmdCancel_Click()
 Tag = ""
 Hide
End Sub

Private Sub cmdOK_Click()
  Tag = txtComputerName
  Hide
End Sub

