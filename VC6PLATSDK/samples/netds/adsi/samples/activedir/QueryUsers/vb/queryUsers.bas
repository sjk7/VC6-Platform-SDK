Attribute VB_Name = "Module1"
Option Explicit
'This sample will use ADO to query the current domain based on a filter provided by the user
'The user is prompted via an InputBox for the filter and the attributes to be returned are define in the code below
'The results will be displayed in the debug window

Sub Main()
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordSet As ADODB.Recordset
Dim oField As ADODB.Field
Dim oRootDSE As IADs
Dim strNamingContext As String
Dim strADOQuery As String
Dim strAttributes As String
Dim strFilter As String

'  --- Define the attributes to be returned from the query ---
strAttributes = "name,distinguishedName,cn,givenName,sn"

' --- Get a filter from the user ---
strFilter = Trim(InputBox("Please input a filter to find users.  Entering nothing will return all users." + vbLf + vbLf + "Example : (sn=Smith) finds all users with the last name Smith", "Enter a filter"))


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
strADOQuery = "<LDAP://" + strNamingContext + ">;(&(objectCategory=person)(objectClass=user)" + strFilter + ");" + strAttributes + ";subtree"
oCmd.CommandText = strADOQuery
oCmd.Properties("Page Size") = 500
'--- Execute the query for the user in the directory ---
Set oRecordSet = oCmd.Execute

While Not oRecordSet.EOF
  For Each oField In oRecordSet.Fields
    'Output each field and value to the debug window
     Debug.Print oField.Name + " :  " + oField.Value
  Next
  oRecordSet.MoveNext
  Debug.Print  'Prints blank line
Wend

' -- Clean up --
oRecordSet.Close
oConnection.Close
Set oField = Nothing
Set oRecordSet = Nothing
Set oCmd = Nothing
Set oConnection = Nothing
End Sub
