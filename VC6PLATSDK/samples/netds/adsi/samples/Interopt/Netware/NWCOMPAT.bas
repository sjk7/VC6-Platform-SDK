Attribute VB_Name = "NWCOMPAT"
Sub Main()
Dim dso
Dim obj
Dim usrName
Dim password
Dim serverName

serverName = "ntmarst2"


'-- Connecting
'-- Assuming you have logged on to the Netware Server
adsPathName = "NWCOMPAT://" & serverName
Set cont = GetObject(adsPathName)

'--- Enumeration
For Each obj In cont
  Debug.Print obj.Name & " (" & obj.Class & ")"
Next

'--- Object Creation
adsPath = "NWCOMPAT://" & serverName
Set cont = GetObject(adsPath)
Set usr = cont.Create("user", "alicew")
usr.SetInfo

'--- Attribute Retrieval and Modification
objPath = "alicew,user"
adsPath = "NWCOMPAT://" & serverName & "/" & objPath
Set usr = GetObject(adsPath)
usr.FullName = "Alice I. Wonderland"
usr.SetInfo

Debug.Print usr.FullName



'--- Filtering
adsPath = "NWCOMPAT://" & serverName
Set con = GetObject(adsPath)
con.Filter = Array("user", "group") 'Show user and group

For Each acct In con
   Debug.Print acct.Name & " (" & acct.Class & ")"
Next
End Sub
