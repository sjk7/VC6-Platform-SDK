VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
'-----------------------------------------------------------
' This program is to set FullName and Description in a user
'----------------------------------------------------------
Dim usr As IADsUser

dom = "YOURDOMAIN" 'Replace with your domain

'-- Binding to a user object
'---Note the ',user' is optional. It's used for performance
Set usr = GetObject("WinNT://" & dom & "/Administrator")

usr.FullName = "John Smith"
usr.Description = "Administrator for " & dom
usr.SetInfo 'Commit the changes to DS

End Sub
