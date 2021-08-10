Attribute VB_Name = "Guid_Bind"
'When programming for the Active Directory the best way to persist
'information about objects is to use its GUID.  Doing this will allow
'the object to easily be retrieved even if it has moved or renamed.

Sub Main()
Dim oIADsObject As IADs
Dim oIADsByGuid As IADs
Dim strADsPath As String
Dim strGUID As String

' --- Get the ADsPath of an object --
'For more information on how to build an LDAP ADsPath see: "ADsPaths" in the help file
strADsPath = InputBox("Please enter a ADsPath to an object in the directory")
'strADsPath = "LDAP://cn=Bugs Bunny,cn=Users,dc=corp,dc=com"

'--- Retrieve that objects GUID ---
Set oIADsObject = GetObject(strADsPath)
strGUID = oIADsObject.Guid
'The IADs.GUID syntax must be used,
'oIADsObject.Get("objectGuid") will not return the string in the expected form
Set oIADsObject = Nothing


'--- Rebind with GUID ---
'The global catalog will contain the GUID of every object in the
'enterprise.  The <GUID=xxxx> syntax is used to retrieve the object.
'<GUID=xxxx> and <SID=xxxx> formats are only available in Active Directory.

strADsPath = "GC://<GUID=" + strGUID + ">"

Set oIADsByGuid = GetObject(strADsPath)
MsgBox oIADsByGuid.Get("Name")


End Sub
