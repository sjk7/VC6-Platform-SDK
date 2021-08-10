Attribute VB_Name = "OtherWKO"
'This program demostrates how to use the otherWellKnownObjects property to make an object rename safe.
'For more information on this see the following topic in the help file:
'   "Enabling rename-safe binding with the otherWellKnownObjects property"

'This program does the following:
'1. Creates a container (MyWKOTestContainer) in the current Window 2000 domain.
'2. Creates a container object (MyWKOTestObject) within the container.
'3. Adds a value for the container object on the otherWellKnownObject property of the container.
'4. Binds to the container object using WKGUID binding string.
'5. Renames the container object using WKGUID binding string
'6. Binds to the container object using WKGUID binding string
'7. Optionally, cleans up by removing the container and leaf object.



Const MyWKOTestObjectGUID = "df447b5eaa5b11d28d5300c04f79ab81"

Sub Main()
Dim oDomain As IADsContainer
Dim oContainer As IADsContainer
Dim strNameOfContainer As String
Dim oSubContainer As IADs
Dim strNameOfSubContainer As String
Dim strNewNameofSubContainer As String
Dim oRootDSE As IADs
Dim strNamingContext As String
Dim strDNContainer As String
Dim strDNSubContainer As String
Dim oRebindWKO As IADs
Dim oIADs As IADs

strNameOfContainer = "MyWKOTestContainer"
strNameOfSubContainer = "MyWKOTestSubContainer"
strNewNameofSubContainer = "MyNewSubContainer"

Set oRootDSE = GetObject("LDAP://RootDSE")
strNamingContext = oRootDSE.Get("defaultNamingContext")
Set oRootDSE = Nothing

' ---Get the domain object as a container
Set oDomain = GetObject("LDAP://" + strNamingContext)

' -- Create a Container beneath the domain
Set oContainer = oDomain.Create("container", "cn=" + strNameOfContainer)
oContainer.SetInfo

' --- Create a container object beneath the container
Set oSubContainer = oContainer.Create("container", "cn=" + strNameOfSubContainer)
oSubContainer.SetInfo

' --- Output the distinguished Names ---
strDNContainer = oContainer.Get("distinguishedName") 'QI for IADs
MsgBox "The DN for the container is: " + strDNContainer
strDNSubContainer = oSubContainer.Get("distinguishedName") 'QI for IADs
MsgBox "The DN for the subcontainer is: " + strDNSubContainer

Call AddValueToOtherWKOProperty(strDNContainer, MyWKOTestObjectGUID, strDNSubContainer)

' --- Use the WKGUID to bind to the object ---
Set oRebindWKO = GetObject("LDAP://<WKGUID=" + MyWKOTestObjectGUID + "," + strDNContainer + ">")
MsgBox "We have sucessfully bound to object" + vbLf + oRebindWKO.Get("distinguishedName") + " using the WKGUID"

' --- Destroy both objects ---
Set oRebindWKO = Nothing
Set oSubContainer = Nothing

' --- Rename the object using its ADsPath --
Set oIADs = GetObject("LDAP://" + strDNSubContainer)
oContainer.MoveHere oIADs.ADsPath, "cn=" + strNewNameofSubContainer

' --- Use the WKGUID to bind to the object ---
Set oRebindWKO = GetObject("LDAP://<WKGUID=" + MyWKOTestObjectGUID + "," + strDNContainer + ">")
MsgBox "We have sucessfully bound to the newly moved object " + oRebindWKO.Get("distinguishedName") + " using the WKGUID"

' -- Destroy objects ---
Set oRebindWKO = Nothing
Set oContainer = Nothing
Set oDomain = Nothing

Exit Sub

' --- This will allow you to destroy those containers which were created ---
Dim oDeleteOps As IADsDeleteOps
Set oDeleteOps = GetObject("LDAP://" + strDNContainer)

' DeleteOps will perform a subtree delete from the container specified
oDeleteOps.DeleteObject 0



End Sub


Public Sub AddValueToOtherWKOProperty(szContainerDN As String, szWKOGUID As String, szWKOObjectDN As String)
'AddValueToOtherWKOProperty( szContainerDN As String,  //DN for container whose otherWellKnownObjects property to modify
'                            szWKOGUID As String,  //WKO GUID for the well-known object.
'                            szWKOObjectDN As String)  //DN of the well-known object.

'Function will bind to the container and place the size of the string GUID, the String GUID, and the DN
'of the Well known object in the OtherWellKnownObjects property.


'This will allow us to bind to this container and find the subContainer

Dim lLength As Long
Dim szDNwithOctetString As String
Dim oIADs As IADs
lLength = Len(szWKOGUID)  ' Length of the string

' -- Build the DN with Octet-String  ---
szDNwithOctetString = "B:" + CStr(lLength) + ":" + szWKOGUID + ":" + szWKOObjectDN

' -- Put the property on the object ---
Set oIADs = GetObject("LDAP://" + szContainerDN)
oIADs.Put "otherWellKnownObjects", szDNwithOctetString
oIADs.SetInfo
Set oIADs = Nothing
End Sub
