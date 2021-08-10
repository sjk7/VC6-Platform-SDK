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
Set usr = GetObject("LDAP://CN=Guest,CN=Users,DC=actived,DC=nttest,DC=microsoft,DC=com")
Debug.Print usr.Name
usr.Say

'Test to prove it you can still access the ADSI interface
'after your extension was called
Debug.Print usr.Get("samAccountName")

End Sub
