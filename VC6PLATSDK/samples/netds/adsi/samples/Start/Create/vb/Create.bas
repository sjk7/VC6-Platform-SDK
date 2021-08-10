Attribute VB_Name = "Module1"
Sub Main()
    On Error Resume Next
    
    Set cont = GetObject("WinNT://seyitb-dev")
    If Err Then HandleError ("Err in GetObject, check machine name!")
    
    '---- Creating a local user account.
    Set usr = cont.Create("user", "JohnD")
    If Err Then HandleError ("Error Creating User")
    
    usr.FullName = "John Doe"
    'In production code, do NOT hard code your password in the source
    usr.SetPassword ("myPaswrd3")
    If Err Then HandleError ("Error in Setting Password")
    
    usr.SetInfo
    If Err Then HandleError ("Error in SetInfo")
    
    MsgBox ("User Created Successfully!!!")

End Sub

Sub HandleError(msg As String)
    MsgBox (msg + vbLf + Err.Description)
    End
End Sub
