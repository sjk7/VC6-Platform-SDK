VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Dispenser Client"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Press Me"
      Height          =   1695
      Left            =   840
      TabIndex        =   0
      Top             =   720
      Width           =   1935
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Dim x As New DISP1Lib.LDisp
Dim y As Long
Dim z As Long
Dim a As Long
x.Alloc z
x.Alloc a
Dim exp As String
exp = "The dispenser client will allocate two resources and display their "
exp = exp & "addresses. It will then de-allocate and re-allocate them, and then again "
exp = exp & "print their addresses.  You should see the same two addresses displayed again, "
exp = exp & "this time in reverse order."

MsgBox exp
MsgBox z & ", " & a
x.DeAlloc z
x.DeAlloc a
x.Alloc z
x.Alloc a
MsgBox z & ", " & a
End Sub
