Attribute VB_Name = "CheckUser"
' This sample will find a user in the current Windows2000 domain based
' on a Common name.  It will then out its IADsUser properties
Sub Main()
Dim oConnection As ADODB.Connection
Dim oCmd As ADODB.Command
Dim oRecordset As ADODB.Recordset
Dim strADOQuery As String
Dim strUserCommonName As String
Dim oUser As IADsUser
Dim oRootDSE As IADs
Dim strNamingContext As String
Dim strOutput As String
Dim vProp As Variant
Dim strProp As String

' --- Change below to a common name of a user in the domain
strUserCommonName = InputBox("Please enter the common name of a user in the domain", "Enter common name")

'-- Get the naming context ----
Set oRootDSE = GetObject("LDAP://RootDSE")
strNamingContext = oRootDSE.Get("defaultNamingContext")

' -- Set up the connection ---
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
Set oRecordset = oCmd.Execute
If oRecordset.RecordCount <> 1 Then
   MsgBox "Did not find exactly one " + strUserCommonName + vbLf + "exiting"
   Exit Sub
End If
oRecordset.MoveFirst

Set oUser = GetObject(oRecordset.Fields("ADsPath"))  'Use the returned ADsPath to bind to the user


On Error Resume Next
strOutput = ""
vProp = (oUser.AccountDisabled)
strOutput = BuildOutput(strOutput, "Account Disabled", vProp)
vProp = oUser.AccountExpirationDate
strOutput = BuildOutput(strOutput, "Account Expiration Date", vProp)
vProp = oUser.AccountExpirationDate
strOutput = BuildOutput(strOutput, "ADsPath :", vProp)
vProp = (oUser.BadLoginAddress)
strOutput = BuildOutput(strOutput, "Bad Login Address", vProp) 'Bad Login Address is not supported in Windows2000
vProp = (oUser.BadLoginCount)
strOutput = BuildOutput(strOutput, "Bad Login Count", vProp)
vProp = (oUser.Class)
strOutput = BuildOutput(strOutput, "Class", vProp)
vProp = (oUser.Department)
strOutput = BuildOutput(strOutput, "Department", vProp)
vProp = (oUser.Description)
strOutput = BuildOutput(strOutput, "Description", vProp)
vProp = (oUser.Division)
strOutput = BuildOutput(strOutput, "Division", vProp)
vProp = (oUser.EmailAddress)
strOutput = BuildOutput(strOutput, "emailAddress", vProp)
vProp = (oUser.EmployeeID)
strOutput = BuildOutput(strOutput, "EmployeeID", vProp)
vProp = (oUser.FaxNumber)
strOutput = BuildOutput(strOutput, "Fax Number", vProp)
vProp = (oUser.FirstName)
strOutput = BuildOutput(strOutput, "First Name", vProp)
vProp = (oUser.FullName)
strOutput = BuildOutput(strOutput, "Full Name", vProp)
vProp = (oUser.GraceLoginsAllowed)
strOutput = BuildOutput(strOutput, "Grace Logins Allowed", vProp) 'Grace Logins Allowed is not supported in Windows2000
vProp = (oUser.GraceLoginsRemaining)
strOutput = BuildOutput(strOutput, "Grace Logins Remaining", vProp) 'Grace Logins Remaining is not supported in Windows2000
vProp = (oUser.Guid)
strOutput = BuildOutput(strOutput, "GUID", vProp)
vProp = (oUser.HomeDirectory)
strOutput = BuildOutput(strOutput, "Home Directory", vProp)
vProp = (oUser.HomePage)
strOutput = BuildOutput(strOutput, "Home Page", vProp)
vProp = (oUser.IsAccountLocked)
strOutput = BuildOutput(strOutput, "Is Account Locked?", vProp)
vProp = (oUser.Languages)
strOutput = BuildOutput(strOutput, "Languages", vProp) 'Languages is not supported in Windows2000
vProp = (oUser.LastFailedLogin)
strOutput = BuildOutput(strOutput, "Last Failed Login", vProp)
vProp = (oUser.LastLogin)
strOutput = BuildOutput(strOutput, "Last Login", vProp)
vProp = (oUser.LastLogoff)
strOutput = BuildOutput(strOutput, "Last Logoff", vProp)
vProp = (oUser.LastName)
strOutput = BuildOutput(strOutput, "Last Name", vProp)
LogonHours_To_String oUser.LoginHours, strProp  'Use ADsHelper.bas to covert Octet String
strOutput = BuildOutput(strOutput, "Login Hours(GMT)", strProp)
vProp = (oUser.LoginScript)
strOutput = BuildOutput(strOutput, "Login Script", vProp)
vProp = (oUser.LoginWorkstations)
strOutput = BuildOutput(strOutput, "Login Workstations", vProp)
vProp = (oUser.Manager)
strOutput = BuildOutput(strOutput, "Manager", vProp)
vProp = (oUser.MaxLogins)
strOutput = BuildOutput(strOutput, "Max Logins", vProp)  'Max Logins is not supported in Windows2000
vProp = (oUser.MaxStorage)
strOutput = BuildOutput(strOutput, "Max Storage", vProp)
vProp = (oUser.Name)
strOutput = BuildOutput(strOutput, "Name", vProp)
vProp = (oUser.NamePrefix)
strOutput = BuildOutput(strOutput, "Name Prefix", vProp)
vProp = (oUser.NameSuffix)
strOutput = BuildOutput(strOutput, "Name Suffix", vProp)
vProp = (oUser.OfficeLocations)
strOutput = BuildOutput(strOutput, "Office Locations", vProp)
vProp = (oUser.OtherName)
strOutput = BuildOutput(strOutput, "Other Name", vProp)
vProp = (oUser.Parent)
strOutput = BuildOutput(strOutput, "Parent", vProp)
vProp = (oUser.PasswordExpirationDate)
strOutput = BuildOutput(strOutput, "Password Expiration Date", vProp)
vProp = (oUser.PasswordLastChanged)
strOutput = BuildOutput(strOutput, "Password Last Changed", vProp)
vProp = (oUser.PasswordMinimumLength)
strOutput = BuildOutput(strOutput, "Password Minimum Length", vProp)
vProp = (oUser.PasswordRequired)
strOutput = BuildOutput(strOutput, "Password Required", vProp)
vProp = (oUser.Picture)
strOutput = BuildOutput(strOutput, "Picture", vProp)
vProp = (oUser.PostalAddresses)
strOutput = BuildOutput(strOutput, "PostalAddresses", vProp)
vProp = (oUser.PostalCodes)
strOutput = BuildOutput(strOutput, "Postal Codes", vProp)
vProp = (oUser.Profile)
strOutput = BuildOutput(strOutput, "Profile", vProp)
vProp = (oUser.RequireUniquePassword)
strOutput = BuildOutput(strOutput, "Require Unique Password", vProp)
vProp = (oUser.Schema)
strOutput = BuildOutput(strOutput, "Schema", vProp)
vProp = (oUser.SeeAlso)
strOutput = BuildOutput(strOutput, "See Also", vProp)
vProp = (oUser.TelephoneHome)
strOutput = BuildOutput(strOutput, "Telephone Home", vProp)
vProp = (oUser.TelephoneMobile)
strOutput = BuildOutput(strOutput, "Telephone Mobile", vProp)
vProp = (oUser.TelephoneNumber)
strOutput = BuildOutput(strOutput, "Telephone Number", vProp)
vProp = (oUser.TelephonePager)
strOutput = BuildOutput(strOutput, "Telephone Pager", vProp)
vProp = (oUser.Title)
strOutput = BuildOutput(strOutput, "Title", vProp)

' The next line will dump the content of the string to the debug window
Debug.Print strOutput

End Sub

Function BuildOutput(strOutputString As String, strText As String, vProperty As Variant) As String
 ' Function will take a text string and a variant property value and build an output string
 If IsArray(vProperty) Then  'If the property is an array
   Dim i As Integer
   Dim strTemp As String
   For i = 0 To UBound(vProperty)
       strTemp = strTemp + vProperty(i) + "# "    'Build a delimited string
   Next
   BuildOutput = strOutputString + strText + " :  " + strTemp + vbLf
Else
  If (vProperty) = "" Then
    BuildOutput = strOutputString + strText + " is not present on the object" + vbLf
  Else
    BuildOutput = strOutputString + strText + " :  " + (vProperty) + vbLf
  End If
End If
  vProperty = ""  'Clear the property
End Function
