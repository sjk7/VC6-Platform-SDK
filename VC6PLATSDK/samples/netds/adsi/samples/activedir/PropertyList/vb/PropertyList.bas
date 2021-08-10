Attribute VB_Name = "PropertyList"
Option Explicit
Sub Main()
Dim oPropertyList As IADsPropertyList
Dim oPropertyEntry As PropertyEntry
Dim lCount As Long
Dim strValues As String
Dim i As Long
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordSet As ADODB.Recordset
Dim oRootDSE As IADs
Dim strUserCommonName As String
Dim strNamingContext As String
Dim strADOQuery As String

'--- Set the Name for the user ----
strUserCommonName = "Administrator"

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

Set oPropertyList = GetObject(oRecordSet.Fields("ADsPath"))  'Use the returned ADsPath to bind to the user
oPropertyList.GetInfo  'populate the cache
lCount = oPropertyList.PropertyCount

' --Output to the debug window ---
Debug.Print "The object has " + CStr(lCount) + " properties" + vbLf

' --Loop through each of the properties and output their values ---
For i = 0 To lCount - 1
  strValues = ""
  Set oPropertyEntry = oPropertyList.Next
  EnumeratePropertyValue oPropertyEntry, strValues
  Debug.Print oPropertyEntry.Name + " :  " + strValues
Next

Set oPropertyList = Nothing
End Sub
