Attribute VB_Name = "Module1"
Sub Main()

'Bind to the parent container.
Set cont = GetObject("LDAP://OU=Marketing,DC=Fabrikam,DC=com")

'---- Renaming an object within the same container.
Set usr = cont.MoveHere("LDAP://CN=Jeff Smith,OU=Marketing,DC=Fabrikam,DC=com", "CN=J. Smith")


End Sub
