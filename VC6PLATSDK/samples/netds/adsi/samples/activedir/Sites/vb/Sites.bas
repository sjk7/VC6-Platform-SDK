Attribute VB_Name = "Sites"
Sub main()

Dim oRoot As IADs
Dim strConfigurationRoot As String
Dim oSitesRoot As IADsContainer
Dim oSite As IADs
Dim strSiteName As String
Dim strSubnetName As String

strSiteName = "MyNewSite"
strSubnetName = "200.50.10.0/24"  ' IP Address/Bitmask

'--- Get path to the configuration container ---
Set oRoot = GetObject("LDAP://RootDSE")

strConfigurationRoot = oRoot.Get("configurationNamingContext")
Set oRoot = GetObject("LDAP://" & strConfigurationRoot)

'--- Get Sites Container and filter for sites---
Set oSitesRoot = oRoot.GetObject("sitesContainer", "CN=Sites")
oSitesRoot.Filter = Array("site")


''''''''''''''''''''''''''''''''''''''''''''''''''
'  Enumerate each site
''''''''''''''''''''''''''''''''''''''''''''''''''
For Each oSite In oSitesRoot
  Debug.Print oSite.Name
Next

Create_Site_And_Subnet oSitesRoot, strSiteName, strSubnetName

Destroy_Site_And_Subnet oSitesRoot, strSiteName, strSubnetName

End Sub

Sub Create_Site_And_Subnet(oSitesRoot As IADs, strSiteName As String, strSubnetName As String)
''''''''''''''''''''''''''''''''''''''''''''''''''
' Function will create a new site and a subnet
''''''''''''''''''''''''''''''''''''''''''''''''''

Set oNewSite = oSitesRoot.Create("site", "CN=" & strSiteName)
oNewSite.SetInfo


'--- Create Servers Container, LLS & NTDS Settings Objs---

Set oNewServersContainer = oNewSite.Create("serversContainer", "CN=Servers")
oNewServersContainer.SetInfo

Set oNewNTDSSiteSettings = oNewSite.Create("nTDSSiteSettings", "CN=NTDS Site Settings")
oNewNTDSSiteSettings.SetInfo

Set oNewSiteLicensingSettings = oNewSite.Create("licensingSiteSettings", "CN=Licensing Site Settings")
oNewSiteLicensingSettings.SetInfo

MsgBox "Site created and subcontainers created!"


' -- Get Path to the Subnets container--
Set oSubnetsRoot = oSitesRoot.GetObject("subnetsContainer", "CN=Subnets")


' -- Create Subnet--
Set oNewSubnet = oSubnetsRoot.Create("subnet", "CN=" & strSubnetName)
oNewSubnet.Put "siteObject", oNewSite.Get("distinguishedName")
oNewSubnet.Put "description", CStr(strSiteName)
oNewSubnet.SetInfo

MsgBox "Subnet Created"
End Sub

Sub Destroy_Site_And_Subnet(oSitesRoot As IADs, strSiteName As String, strSubnetName As String)
''''''''''''''''''''''''''''''''''''''''''''''''''
' Function will use IADsDeleteOps and IADsContainer.Delete
' to remove an existing site and a subnet
''''''''''''''''''''''''''''''''''''''''''''''''''
Dim oDeleteOp As IADsDeleteOps
Dim oSubnetsRoot As IADsContainer

Set oDeleteOp = oSitesRoot.GetObject("site", "CN=" & strSiteName)
oDeleteOp.DeleteObject (0)
MsgBox "Site and subcontainers deleted!"

Set oSubnetsRoot = oSitesRoot.GetObject("subnetsContainer", "CN=Subnets")
oSubnetsRoot.Delete "subnet", "CN=" & strSubnetName
MsgBox "Subnet deleted!"
End Sub


