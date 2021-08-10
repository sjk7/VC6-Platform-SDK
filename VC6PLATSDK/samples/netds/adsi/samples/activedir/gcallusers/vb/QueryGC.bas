Attribute VB_Name = "QueryGC"
Option Explicit

'This sample demostrates how to use Visual Basic to bind to the Global Catalog
'server and query it for all the users in the forest

Sub Main()
Dim oContainer As IADsContainer
Dim oGC As IADs
Dim strGCADsPath As String
Dim var As Variant
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordset As ADODB.Recordset
Dim strADOQuery As String

Set oContainer = GetObject("GC:")  'Bind to the Global catalog.  NT4/Win9x users will have to specify a servername

' -- Once we have the container we enumerate one time to get the GC object
For Each var In oContainer
  Set oGC = var
Next
strGCADsPath = oGC.ADsPath    'cache the ADsPath for the query


'--- Set up the connection ---
Set oConnection = New ADODB.Connection
Set oCmd = New ADODB.Command
oConnection.Provider = "ADsDSOObject"
oConnection.Open "ADs Provider"
Set oCmd.ActiveConnection = oConnection

'--- Build the query string ---
'--LDAP Dialect
strADOQuery = "<" + strGCADsPath + ">;(&(objectCategory=person)(objectClass=user));cn,distinguishedName;subtree"

'-- SQL dialect --
' strADOQuery = "Select cn, distinguishedName from '" + strGCADsPath + "' Where objectCategory = 'person' and objectClass = 'user'"
' oCmd.Properties("SearchScope") = ADS_SCOPE_SUBTREE

oCmd.Properties("Page Size") = 100
oCmd.CommandText = strADOQuery

'--- Execute the query for the user in the directory ---
Set oRecordset = oCmd.Execute
While Not oRecordset.EOF
 'Dump the user information to the debug window
  Debug.Print oRecordset.Fields("cn") + "   " + oRecordset.Fields("distinguishedName")
  
  ' -- Advance the recordset --
  oRecordset.MoveNext
Wend

oRecordset.Close
oConnection.Close

Set oRecordset = Nothing
Set oCmd = Nothing
Set oConnection = Nothing

Set oGC = Nothing
Set oContainer = Nothing
End Sub
