Attribute VB_Name = "Is_GC"
'A Global Catalog server must be a domain controller of some domain in the
'forest.  However, not all domain controllers are Global Catalog servers

'The below sample will bind to a domain controller in the current domain and
'test to see whether that domain controler is a GC

Option Explicit
Sub Main()
On Error Resume Next
Const Is_GC = 1

Dim oRootDSE As IADs
Dim oDsService As IADs
Dim iFlag As Integer
Dim oComputer As IADs
Dim strDirectoryServiceSettings As String
Dim strServerDN As String

Set oRootDSE = GetObject("LDAP://RootDSE")

' --- A specific server can also be specified --
'Dim strServerName As String
'strServerName = "MyServer"
'Set oRootDSE = GetObject("LDAP://" + strServerName + "/RootDSE")

' --- Get the Directory Service setting for that server ---
strDirectoryServiceSettings = oRootDSE.Get("dsServiceName")
Set oDsService = GetObject("LDAP://" & strDirectoryServiceSettings)

' --- Get the server's DN ---
strServerDN = oRootDSE.Get("serverName")
Set oComputer = GetObject("LDAP://" & strServerDN)

iFlag = oDsService.Get("options")

If (iFlag And Is_GC) Then
  MsgBox oComputer.Get("name") + " is a GC"
Else
  MsgBox oComputer.Get("name") + " is a not GC"
End If

Exit Sub

' -- If you wish to make this DC a GC then flip the bit --
oDsService.Put "options", iFlag Or Is_GC
oDsService.SetInfo
End Sub
