Attribute VB_Name = "BindtoParent"
'This sample will find a user in the current domain and retrieve the distinguished name
'of that users parent object.  The name of the user is stored in the variable
'strUserCommonName below.  You will want to change this to fit the environment

Sub Main()
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordSet As ADODB.Recordset
Dim oRootDSE As IADs
Dim oUser As IADsUser
Dim oParent As IADs
Dim strUserCommonName As String
Dim strNamingContext As String
Dim strADOQuery As String

'--- Set the Name for the user ----
strUserCommonName = "Bugs Bunny"

'--- Get the Naming Context ----
Set oRootDSE = GetObject("LDAP://RootDSE")
strNamingContext = oRootDSE.Get("defaultNamingContext")
Set oRootDSE = Nothing


'--- Set up the connection ---
Set oConnection = New ADODB.Connection
Set oCmd = New ADODB.Command
oConnection.Provider = "ADsDSOObject"
oConnection.Open "ADs Provider"
Set oCmd.ActiveConnection = oConnection

'--- Build the query string ---
'--LDAP Dialect
strADOQuery = "<LDAP://" + strNamingContext + ">;(&(objectCategory=person)(objectClass=user)(cn=" + strUserCommonName + "));cn,adspath;subtree"

'-- SQL dialect --
' strADOQuery = "Select cn, AdsPath from 'LDAP://" + strNamingContext + "' Where objectCategory = 'person' and objectClass = 'user' and cn = '" + strUserCommonName + "'"
'oCmd.Properties("SearchScope") = ADS_SCOPE_SUBTREE

oCmd.CommandText = strADOQuery

'--- Execute the query for the user in the directory ---
Set oRecordSet = oCmd.Execute
If oRecordSet.RecordCount <> 1 Then
   MsgBox "Did not find exactly one record for " + strUserCommonName + vbLf + "exiting"
   Exit Sub
End If
oRecordSet.MoveFirst

Set oUser = GetObject(oRecordSet.Fields("ADsPath"))  'Use the returned ADsPath to bind to the user
' Debug.Print oUser.Name
Set oParent = GetObject(oUser.Parent)   'Retrieve the ADsPath of the User's parent and bind to that object
' Debug.Print oParent.ADsPath

MsgBox "The Parent for " + strUserCommonName + " is " + vbLf + oParent.Get("distinguishedName")
 
 
' --- Clean Up ------
Set oUser = Nothing
Set oParent = Nothing

oRecordSet.Close
oConnection.Close
Set oRecordSet = Nothing
Set oCmd = Nothing
Set oConnection = Nothing
End Sub
