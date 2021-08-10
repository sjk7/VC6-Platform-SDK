Attribute VB_Name = "IsMember"
'This sample will find a user in the current domain base on the Common name
'It then uses the tokenGroups property to determine which security groups
'the user is a member of
'This sample makes use of ADsSID which is located on ADsSecurity.dll
'ADsSid is used to convert the SIDs of the groups to a more readable form

Sub Main()
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordSet As ADODB.Recordset
Dim oRootDSE As IADs
Dim oUser As IADsUser
Dim strUserCommonName As String
Dim strNamingContext As String
Dim strADOQuery As String
Dim vAllGroupSids() As Variant
Dim var As Variant
Dim pSid() As Byte
Dim oADsSid As ADsSID
Dim strListGroups As String

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
' strADOQuery = "Select cn, AdsPath from 'LDAP://" + strNamingContext +"' Where objectCategory = 'person' and objectClass = 'user' and cn = '"+ strUserCommonName + "'"
'oCmd.Properties("SearchScope") = ADS_SCOPE_SUBTREE

oCmd.CommandText = strADOQuery

'--- Execute the query for the user in the directory ---
Set oRecordSet = oCmd.Execute
If oRecordSet.RecordCount <> 1 Then
   MsgBox "Did not find exactly one record for " + strUserCommonName + vbLf + "exiting"
   Exit Sub
End If
oRecordSet.MoveFirst

Set oUser = GetObject(oRecordSet.Fields("ADsPath"))  'Use the returned

' -- Create an instance of ADsSID --
Set oADsSid = New ADsSID
strListGroups = ""

' -- Load the tokenGroups property into Cache and retrieve it --
oUser.GetInfoEx Array("tokenGroups"), 0
vAllGroupSids = oUser.Get("tokenGroups")  ' tokenGroups returns an variant array
For Each var In vAllGroupSids             ' each variant contains an array of Bytes which is the SID
   pSid = var    'get the Byte() from the Variant
   oADsSid.SetAs ADS_SID_RAW, pSid  'pass the raw value into ADsSid
   strListGroups = strListGroups + oADsSid.GetAs(ADS_SID_SAM) + vbLf  'retrieve the value as a SAM account name
Next

' -- Display results --
 'Debug.Print strListGroups   'To the debug window
 MsgBox strListGroups
End Sub
