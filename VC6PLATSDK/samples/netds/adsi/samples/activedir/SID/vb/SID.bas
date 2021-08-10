Attribute VB_Name = "SID"
Option Explicit
'This example will demonstrate how to retrieve the SID from a user object
'and used the ADsSID object from ADsSecurity.dll to convert the SID into a
'string which can be seen.
'The sample then uses that string to bind to the object using the <SID=xxx> syntax

'This sample requires ADsSecurity.dll which is located in the \ResourceKit\ directory

Sub Main()
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordSet As ADODB.Recordset
Dim oRootDSE As IADs
Dim oUser As IADsUser
Dim oRebindUser As IADsUser
Dim strUserCommonName As String
Dim strNamingContext As String
Dim strADOQuery As String
Dim pSID() As Byte
Dim oADsSID As ADSSECURITYLib.ADsSID
Dim strHexStringSID As String

'--- Set the Name for the user ----
strUserCommonName = "Craig Wiand"

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

pSID = oUser.Get("objectSid")
Set oADsSID = New ADsSID
oADsSID.SetAs ADS_SID_RAW, pSID
strHexStringSID = oADsSID.GetAs(ADS_SID_HEXSTRING)
MsgBox "The SID for " + oUser.Get("name") + " is " + vbLf + strHexStringSID

' -- Destroy our current objects ---
Set oADsSID = Nothing
Set oUser = Nothing
oRecordSet.Close
Set oRecordSet = Nothing
Set oCmd = Nothing
oConnection.Close
Set oConnection = Nothing

' --- Rebind to the object using the SID with the <SID=xxx> notation --
Set oRebindUser = GetObject("LDAP://<SID=" + strHexStringSID + ">")
MsgBox "We have sucessfully re-bound to " + oRebindUser.Get("name") + " with the SID"

Set oRebindUser = Nothing
End Sub
