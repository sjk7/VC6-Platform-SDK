Attribute VB_Name = "AddGroup"
Option Explicit



Sub CreateGroup(strPath As String, strGroupName As String, strSamAcctName As String, strGroupType As String, bSecurity As Boolean)
' =========================================================
'CreateGroup(strPath As String, strGroupName As String, strSamAcctName As String, strGroupType As String, bSecurity As Boolean)
'   strPath = ADsPath of the Container under which the group will be created
'   strGroupName = Name of the Group to be Created
'   strSamAcctName = Group name as it will appear to pre-Windows2000 machines
'   strGroupType = Type of group to be created(Local,Domain Local, Global, or Universal)
'   bSecurity = Is this a security group?
' =========================================================

 Dim lGroupType As Long
 Dim oContainer As IADsContainer
 Dim oGroup As IADsGroup
 
 '  --- Set the type of Group ------
 lGroupType = 0
 Select Case UCase(strGroupType)
 Case "LOCAL": lGroupType = ADS_GROUP_TYPE_LOCAL_GROUP
 Case "DOMAIN LOCAL": lGroupType = ADS_GROUP_TYPE_DOMAIN_LOCAL_GROUP
 Case "GLOBAL": lGroupType = ADS_GROUP_TYPE_GLOBAL_GROUP
 Case "UNIVERSAL": lGroupType = ADS_GROUP_TYPE_UNIVERSAL_GROUP
 Case Else
    MsgBox "This is not a proper group type"
    Exit Sub
 End Select
 
 
 ' ----  Check to see if it is a Security Group ----
 If bSecurity Then
   lGroupType = lGroupType Or ADS_GROUP_TYPE_SECURITY_ENABLED
 End If
 
 ' ---- Create the Group ----
 Set oContainer = GetObject(strPath)
 Set oGroup = oContainer.Create("group", "cn=" + strGroupName)
 oGroup.Put "sAMAccountName", strSamAcctName
 oGroup.Put "groupType", lGroupType
 oGroup.SetInfo
 
 
 Set oGroup = Nothing
 Set oContainer = Nothing
End Sub
Sub Main()
  Dim oRootDSE As IADs
  Dim strNamingContext As String
  
  ' --- Get the Naming Context ----
  Set oRootDSE = GetObject("LDAP://RootDSE")
  strNamingContext = oRootDSE.Get("defaultNamingContext")
  Set oRootDSE = Nothing
  
  Call CreateGroup("LDAP://cn=Users," + strNamingContext, "My New Group", "NewGroup", "Global", True)
  
End Sub
