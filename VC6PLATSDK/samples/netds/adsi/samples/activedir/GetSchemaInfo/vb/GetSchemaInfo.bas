Attribute VB_Name = "GetSchemaInfo"
Public Sub GetSchemaInformation(strCategory As String, strFilter As String)
 Dim oRootDSE As IADs
 Dim oConnection As New ADODB.Connection
 Dim oCmd As New ADODB.Command
 Dim oRecordSet As ADODB.Recordset
 Dim oField As ADODB.Field
 Dim strSchema As String
 Dim strAttributes As String
 Dim strQueryFilter As String
 Dim strQuery As String
 Dim oOutput As RichTextBox
 
 'Get a handle to the output window
 Set oOutput = frmSchemaInfo.Controls("rtxtOutput")
 
 'set the attributes which will be returned
 strAttributes = "cn,adspath,ldapDisplayName,objectClass,objectCategory"

  'Build query filter
 If (strCategory <> "") And (strFilter <> "") Then
   strQueryFilter = "(&" + strCategory + strFilter + ")"
 Else
   strQueryFilter = strCategory + strFilter
 End If
 
 Set oRootDSE = GetObject("LDAP://RootDSE")
 strSchema = oRootDSE.Get("schemaNamingContext")
 
 oConnection.Provider = "ADsDSOObject"
 oConnection.Open "ADs Provider"
 Set oCmd.ActiveConnection = oConnection
 strQuery = "<LDAP://" + strSchema & ">;" + strQueryFilter + ";" + strAttributes + ";onelevel"
 frmSchemaInfo.txtQuery = strQuery
 oCmd.CommandText = strQuery
 oCmd.Properties("Page Size") = 100
 Set oRecordSet = oCmd.Execute
 frmSchemaInfo.txtRecordCount.Text = oRecordSet.RecordCount
  While Not oRecordSet.EOF
   Dim strTemp As String
   For Each oField In oRecordSet.Fields
     If IsArray(oField.Value) Then
       Dim vProp As Variant
       strTemp = ""
       For Each vProp In oField.Value
           strTemp = strTemp + vProp + "# "
       Next
     Else
       strTemp = oField.Value
     End If
     oOutput.Text = oOutput.Text + oField.Name + " :  " + strTemp + vbLf
   Next
   oRecordSet.MoveNext
   oOutput.Text = oOutput.Text + vbLf
   DoEvents
  Wend
End Sub
