Attribute VB_Name = "Module1"
Sub Main()

   'Bind to a user
   Set usr = GetObject("LDAP://CN=Jane Johnson,OU=DSys,DC=Fabrikam,DC=com")
   
   'Modify single attributes
   usr.Put "givenName", "Jane"
   usr.Put "sn", "Johnson"
   
   'Modify multivalue attributes
   usr.Put "otherTelephone", Array("425 844 1234", "425 924 4321")
   
   'Commit to the directory
   usr.SetInfo
    

End Sub
