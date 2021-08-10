Attribute VB_Name = "Module1"
Sub Main()
Set cont = GetObject("WinNT://INDEPENDENCE")

'---- Deleting a user
cont.Delete "user", "JohnD"

End Sub
