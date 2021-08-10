Attribute VB_Name = "Create_User"
Option Explicit
'This sample will demostrate how to create a user with an interface similar to
'Users and Computers-New Object User

'Note: that the sample was created to demonstrate which properties would be
'set on the user object and is not necessary the most efficient design

Public strContainerDN As String   'Contains the DN for the container where the user will be created
Public strContainerCanName As String   'Contains the Canonical Name of the container

Public strFirst As String              'Contains the users first name
Public strLast As String               'Contains the users last name
Public strInitials As String           'Contains the users initials
Public strFullName As String           'Contains the users full name
Public strUPN As String                'Contains the users user principal name
Public strSAMAcctName As String        'Contains the users SAM account(downlevel) name
Public strPassword As String           'Contains the users password
Public bMustChangePwd As Boolean       'User must change password flag
Public bCannotChangePwd As Boolean     'User cannot change password flag
Public bPasswordNoExpire As Boolean    'User's password will not expire flag
Public bAcctDisabled As Boolean        'Account is disabled flag

Public strDomainName As String             'Contains the downlevel domain name
Public strPossibleUPN() As Variant      'Contains the possible UPN's for this forest

Public frmNames As New frmSetNames
Public frmProps As New frmAcctProps



Const WK_GUID_USERS_CONTAINER = "94850635a4ebf7478a0e01e725fd428a"

Sub Main()

  Dim oRootDSE As IADs
  Dim strNamingContext As String
  Dim strConfigContext As String
  Dim strRootContext As String
  Dim oContainer As IADsContainer
  Dim oDomain As IADs
  Dim oPartitions As IADs
  Dim lCount As Long
  Dim strCanonical As String
  Dim strDNSName As String
 
  ' --- Get the Naming Contexts ----
  Set oRootDSE = GetObject("LDAP://RootDSE")
  strNamingContext = oRootDSE.Get("defaultNamingContext")
  strConfigContext = oRootDSE.Get("configurationNamingContext")

 
 ' -- Get current Domain name --
 Set oDomain = GetObject("LDAP://" + strNamingContext)
 strDomainName = oDomain.Get("name")

 Set oPartitions = GetObject("LDAP://cn=Partitions," + strConfigContext)


'''''''''''''''''''''''''''''''''''''''''''''
'-- Get the UPN suffixes ---
'''''''''''''''''''''''''''''''''''''''''''''

'-Get the DNS name of the domain-
oDomain.GetInfoEx Array("canonicalName"), 0
strCanonical = oDomain.Get("canonicalName")
strDNSName = Left(strCanonical, Len(strCanonical) - 1) 'clip off "/"
'MsgBox strDNSName
On Error Resume Next
 strPossibleUPN = oPartitions.GetEx("uPNSuffixes")  'If no addition suffixes are specified this value will be NULL
 lCount = UBound(strPossibleUPN)
 If lCount > 0 Then  'found additional suffixes
   ReDim Preserve strPossibleUPN(lCount + 1)
   strPossibleUPN(lCount + 1) = strDNSName
 Else
  strPossibleUPN = Array(strDNSName)
 End If
On Error GoTo 0
 
' set to the Users container
SetContainer "cn=Users," + strNamingContext

 
frmNames.Show  'Show this form
 
 
' Set oUser = oContainer.Create("user", "cn=" + strUserName)
' oGroup.Put "sAMAccountName", strSAMAcctName
' oGroup.SetInfo

 '--- Clean up ---

 Set oContainer = Nothing
 Set oPartitions = Nothing
 Set oRootDSE = Nothing
End Sub

Sub SetContainer(strNewDN As String)
' --- Get the DN and CanonicalName of the container passed in ---
Dim oCont As IADsContainer
 On Error Resume Next
 Set oCont = GetObject("LDAP://" + strNewDN)
 If Err.Number <> 0 Then
   MsgBox "Invalid DN specified"
 Else
  strContainerDN = oCont.Get("distinguishedName")
  oCont.GetInfoEx Array("canonicalName"), 0
  strContainerCanName = oCont.Get("canonicalName")
 End If
 
Set oCont = Nothing
End Sub


Public Sub CreateUserAccount()
' This function will actually create the user account in the directory
' in the container specified with the attributes given

Dim oContainer As IADsContainer
Dim oUser As IADsUser
Dim vUserAcctControl As Variant

' --- Get the specified container
Set oContainer = GetObject("LDAP://" + strContainerDN)

' --- Create the user object ---
Set oUser = oContainer.Create("user", "cn=" + strFullName)

' --- Set the properties via thier LDAP name ---
If strFirst <> "" Then
  oUser.Put "givenName", strFirst     'oUser.firstname = strFirst
End If

If strLast <> "" Then
  oUser.Put "sn", strLast             'oUser.lastname = strLast
End If

If strInitials <> "" Then
  oUser.Put "initials", strInitials
End If

oUser.Put "displayName", strFullName
oUser.Put "sAMAccountName", strSAMAcctName
oUser.Put "userPrincipalName", strUPN


' --- Write the object to the directory ---
oUser.SetInfo

' --- Set the user's password ---
oUser.SetPassword strPassword

If bMustChangePwd Then  'Must Change password
  oUser.Put "pwdLastSet", 0
End If

If bCannotChangePwd Then 'User cannont change password
  UserCannotChange oUser
End If

If bPasswordNoExpire Then
   vUserAcctControl = oUser.Get("userAccountControl")
   oUser.Put "userAccountControl", vUserAcctControl Or ADS_UF_DONT_EXPIRE_PASSWD
End If

If bAcctDisabled Then  'Account is disabled
  oUser.AccountDisabled = True
Else
  oUser.AccountDisabled = False
End If
  
'--- Set Account information ---
oUser.SetInfo

MsgBox "User " + strFullName + " has been sucessfully created!"

Set oUser = Nothing
End
End Sub
Sub UserCannotChange(oUserObject As IADsUser)
 Dim oSecDescriptor As SecurityDescriptor
 Dim oDACL As AccessControlList
 Dim oACE As New AccessControlEntry
 Dim oACE2 As New AccessControlEntry
 
 Const CHANGE_PASSWORD_GUID = "{ab721a53-1e2f-11d0-9819-00aa0040529b}"

 'In order to preven the user from changing his/her own password we place a
 'disallow access control entry on the object for that permission
 
 '-- Create the Access Control Entry for Self---
 oACE.Trustee = "NT AUTHORITY\SELF"
 oACE.AceFlags = 0
 oACE.AceType = ADS_ACETYPE_ACCESS_DENIED_OBJECT
 oACE.Flags = ADS_FLAG_OBJECT_TYPE_PRESENT
 oACE.ObjectType = CHANGE_PASSWORD_GUID
 oACE.AccessMask = ADS_RIGHT_DS_CONTROL_ACCESS
 
 ' --- Create the Access Control Entry for Everyone---
 oACE2.Trustee = "EVERYONE"
 oACE2.AceFlags = 0
 oACE2.AceType = ADS_ACETYPE_ACCESS_DENIED_OBJECT
 oACE2.Flags = ADS_FLAG_OBJECT_TYPE_PRESENT
 oACE2.ObjectType = CHANGE_PASSWORD_GUID
 oACE2.AccessMask = ADS_RIGHT_DS_CONTROL_ACCESS
 
 '--- Get this objects Security Descriptor
 Set oSecDescriptor = oUserObject.Get("ntSecurityDescriptor")
 
 '--- Get the Discretionary ACL ---
 Set oDACL = oSecDescriptor.DiscretionaryAcl
 
 '-- Add our new ACEs and replace DACL---
 oDACL.AddAce oACE
 oDACL.AddAce oACE2
 
 ' -- Put the Security Descriptor back on the object --
 oUserObject.Put "ntSecurityDescriptor", oSecDescriptor
 oUserObject.SetInfo
 
 ' -- Clean up --
 Set oACE = Nothing
 Set oACE2 = Nothing
 Set oDACL = Nothing
 Set oSecDescriptor = Nothing
End Sub
