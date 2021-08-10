Attribute VB_Name = "Module1"
Sub Main()

'Bind to an object
Set usr = GetObject("WinNT://INDEPENDENCE/JJohnson,user")

'---- Getting a parent object via IADs::get_Parent
Set cont = GetObject(usr.Parent)


End Sub
