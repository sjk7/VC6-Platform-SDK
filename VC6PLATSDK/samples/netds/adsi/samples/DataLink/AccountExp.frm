VERSION 5.00
Begin VB.Form frmDataEnv 
   Caption         =   "Active Directory Data Report"
   ClientHeight    =   5010
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8520
   LinkTopic       =   "Form1"
   ScaleHeight     =   5010
   ScaleWidth      =   8520
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdADSQL 
      Caption         =   "Active Directory - SQL Join"
      Height          =   450
      Left            =   2715
      TabIndex        =   1
      Top             =   2430
      Width           =   2340
   End
   Begin VB.CommandButton cmdAccExp 
      Caption         =   "Account Expiration"
      Height          =   450
      Left            =   1335
      TabIndex        =   0
      Top             =   615
      Width           =   2025
   End
   Begin VB.Image Image3 
      Height          =   1350
      Left            =   1110
      Picture         =   "AccountExp.frx":0000
      Top             =   2085
      Width           =   1515
   End
   Begin VB.Image Image2 
      Height          =   825
      Left            =   345
      Picture         =   "AccountExp.frx":05FC
      Top             =   450
      Width           =   825
   End
   Begin VB.Image Image1 
      Height          =   11520
      Left            =   30
      Picture         =   "AccountExp.frx":10EB
      Top             =   -120
      Width           =   15360
   End
End
Attribute VB_Name = "frmDataEnv"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdAccExp_Click()
AccountExp.Show
End Sub

Private Sub cmdADSQL_Click()
HeteroJoin.Show
End Sub
