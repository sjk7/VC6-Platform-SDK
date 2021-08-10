Set usr = GetObject("LDAP://CN=Guest,CN=Users,DC=actived,dc=nttest, dc=microsoft,dc=com")
wscript.echo Usr.Name
Usr.Say 
wscript.echo usr.Get("samAccountName")
