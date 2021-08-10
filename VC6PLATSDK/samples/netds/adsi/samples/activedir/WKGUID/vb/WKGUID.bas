Attribute VB_Name = "WKGUID"
' This sample gets the specified well-known object for the current user's domain.
' Note that the following well-known GUIDs are defined for domainDNS in ntdsapi.h:
Const GUID_USERS_CONTAINER = "a9d1ca15768811d1aded00c04fd8d5cd"
Const GUID_COMPUTRS_CONTAINER = "aa312825768811d1aded00c04fd8d5cd"
Const GUID_SYSTEMS_CONTAINER = "ab1d30f3768811d1aded00c04fd8d5cd"
Const GUID_DOMAIN_CONTROLLERS_CONTAINER = "a361b2ffffd211d1aa4b00c04fd7d83a"
Const GUID_INFRASTRUCTURE_CONTAINER = "2fbac1870ade11d297c400c04fd8d5cd"
Const GUID_DELETED_OBJECTS_CONTAINER = "18e2ea80684f11d2b9aa00c04f79f805"
Const GUID_LOSTANDFOUND_CONTAINER = "ab8153b7768811d1aded00c04fd8d5cd"

Sub main()
Dim oUserContainer As IADs
Dim oRootDSE As IADs
Dim strNamingContext As String

Set oRootDSE = GetObject("LDAP://RootDSE")
strNamingContext = oRootDSE.Get("defaultNamingContext")

'--- Get the Users Container for this domain using the well-known GUID---
Set oUserContainer = GetObject("LDAP://<WKGUID=" + GUID_USERS_CONTAINER + "," + strNamingContext + ">")

MsgBox "The distinguished name for the Users Container is : " + oUserContainer.Get("distinguishedName")

Set oUserContainer = Nothing
Set oRootDSE = Nothing
End Sub
