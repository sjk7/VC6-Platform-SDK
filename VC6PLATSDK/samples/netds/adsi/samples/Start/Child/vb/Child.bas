Attribute VB_Name = "Module1"

Sub Main()

'Bind to the parent's destination
Set cont = GetObject("LDAP://OU=myou1,DC=mydomain2,DC=mydomain1,DC=microsoft,DC=com")

'---- Moving a user from one organization to another
Set usr = cont.MoveHere("LDAP://CN=Mike Smith,OU=anotherou,DC=mydomain2,DC=mydomain1,DC=microsoft,DC=com", vbNullString)


End Sub
