Attribute VB_Name = "NDS"
Sub Main()
Dim dso
Dim obj
Dim usrName
Dim password
Dim serverName

'--- WARNING - You should NOT hardcode your userName and password in the code
'------------  You should obtain the user name and password from the user input
'------------  This sample is used for illustration only, not for actual running production code
serverName = "ntmarst2"
userName = "supervisor.ntmarst2"
password = "secretpwd"

'-- Connecting
Set dso = GetObject("NDS:")
Set cont = dso.OpenDSObject("NDS://" & serverName, userName, password, 0)
'--- Enumeration
For Each obj In cont
  Debug.Print obj.Name & " (" & obj.Class & ")"
Next

'--- Attribute Retrieval and Modification
Path = "O=NTMARST2/CN=benny"
ADsPath = "NDS://" & serverName & "/" & Path
Set usr = dso.OpenDSObject(ADsPath, userName, password, 0)
Debug.Print usr.Get("Surname")
usr.Put "SurName", "Johnson"
usr.SetInfo

'--- Object Creation
Path = "O=NTMARST2"
ADsPath = "NDS://" & serverName & "/" & Path
Set cont = dso.OpenDSObject(ADsPath, userName, password, 0)
Set usr = cont.Create("user", "alicew")
usr.Put "cn", "alice"
usr.Put "Surname", "Wonderland"
usr.SetInfo

'---Searching-----
ADsPath = "NDS://" & serverName
Set con = CreateObject("ADODB.Connection")
con.Provider = "ADsDSOObject"
con.Properties("User ID") = userName
con.Properties("Password") = password
con.Open "ADSI"


Set com = CreateObject("ADODB.Command")
Set com.ActiveConnection = con
com.CommandText = "SELECT ADsPath, 'Object Class' FROM '" & ADsPath & "' WHERE Surname='Wonderland'"
Set rs = com.Execute


While Not (rs.EOF)
  Debug.Print rs.Fields("ADsPath")
  rs.MoveNext
Wend



End Sub
