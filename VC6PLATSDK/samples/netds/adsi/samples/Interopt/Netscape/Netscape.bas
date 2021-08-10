Attribute VB_Name = "Module1"
Sub Main()
Dim server
Dim company
Dim userName
Dim password
Dim dso
'-- For searching----
Dim con
Dim command
Dim rs


server = "nscp01"
company = "O=Airius.com"
ADsPath = "LDAP://" & server & "/" & company

'-- Supplied Credentials -----
'--- WARNING: UserName and Password should NOT be hardcoded in the real product code
'----------   This sample is used for illustration purpose only.
'----------------------------------------------------------------------------
userName = "cn=directory manager"
password = "password"

'----For anonymous credentials, use "" ---
'userName = ""
'password = ""

Set dso = GetObject("LDAP:")
Set cont = dso.OpenDSObject(ADsPath, userName, password, 0)

'---- Enumerating a container

For Each obj In cont
  Debug.Print obj.Name & " (" & obj.Class & ")"
Next

'---- Searching-------
Set con = CreateObject("ADODB.Connection")
con.Provider = "ADsDSOObject"
con.Properties("User ID") = userName
con.Properties("Password") = password
con.Open "ADSI"


Set com = CreateObject("ADODB.Command")
Set com.ActiveConnection = con
com.CommandText = "SELECT ADsPath FROM '" & ADsPath & "' WHERE cn='a*'"
Set rs = com.Execute


While Not (rs.EOF)
   Debug.Print rs.Fields("ADsPath")
   rs.MoveNext
Wend




End Sub
