Attribute VB_Name = "RootDSE"
Option Explicit
' Get the name for the Schema container for this domain
'  then retrieve the naming context for this domain.



Sub Main()
Dim oRoot As IADs
'    /////////////////////////////////////////////////////////////////////////////
'    // NOTE: If your client is NT 4.0 or Win 9.x without the DS Client, you
'    // must put the server name in front of the LDAP://.  For example
'    // GetObject("LDAP://myDC/RootDSE")
'    // If your client is Windows 2000, you don't need to specify the servername.
'    // The locator service in Windows 2000 will automatically locate the best DC for you
'    /////////////////////////////////////////////////////////////////////////////////////

Set oRoot = GetObject("LDAP://RootDSE")
MsgBox oRoot.Get("defaultNamingContext")
Set oRoot = Nothing
End Sub
