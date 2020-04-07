VERSION 5.00
Begin VB.Form frmObjConstruct 
   Caption         =   "Object Construct Test"
   ClientHeight    =   1035
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3690
   LinkTopic       =   "Form1"
   ScaleHeight     =   1035
   ScaleWidth      =   3690
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdTestOC 
      Caption         =   "Test Object Construction"
      Height          =   615
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   3495
   End
End
Attribute VB_Name = "frmObjConstruct"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdTestOC_Click()
    Dim oct As ObjectConstructLib.clsObjectConstruct
    Set oct = New clsObjectConstruct
End Sub
