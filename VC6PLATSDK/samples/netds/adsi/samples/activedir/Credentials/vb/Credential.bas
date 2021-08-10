Attribute VB_Name = "Credential"
'This sample uses OpenDSObject to pass credentials to the server instead of using the
'credentials of the currently logged in user.

'With the LDAP provider for Active Directory, you may pass in bstrUserName as one of the following strings:

' -The name of a user account, such as jsmith.
' -The user path from a previous version of Windows NT, such as AcardiaBay\jsmith.
' -Distinguished Name, such as CN=jsmith, OUT=Sales, DC=ArcardiaBay, DC=Com.
' -User Principal Name (UPN), such as jsmith@Arcadiabay.com.
'To use the UPN, you must set the appropriate UPN value for the userPrincipalName property of the user.


Sub Main()
Dim oDSObj As IADsOpenDSObject
Dim oRootDSE As IADs
Dim strNamingContext As String
Dim oAuth As IADs
Dim strUsername As String
Dim strPassword As String

' --- Retrieve the current domain ---
Set oRootDSE = GetObject("LDAP://RootDSE")
strNamingContext = oRootDSE.Get("defaultNamingContext")
Set oRootDSE = Nothing


'--- Prompt for Credentials ----
strUsername = InputBox("Please enter a username to bind as:", "Enter a username")
strPassword = InputBox("Please enter a password for the user:", "Enter a password")

' --- Use OpenDSObject to bind with credentials ---
Set oDSObj = GetObject("LDAP:")
Set oAuth = oDSObj.OpenDSObject("LDAP://" + strNamingContext, strUsername, strPassword, ADS_SECURE_AUTHENTICATION)
MsgBox "You have successfully bound to : " & oAuth.Get("Name") & " as " & strUsername

' -- Clean up --
Set oDSObj = Nothing
Set oAuth = Nothing
End Sub
