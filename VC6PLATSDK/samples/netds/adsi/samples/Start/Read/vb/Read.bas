Attribute VB_Name = "Module1"
Sub Main()
Set usr = GetObject("WinNT://INDEPENDENCE/Administrator,user")

'---- Reading a single value attribute
Debug.Print usr.Name
Debug.Print usr.FullName

'Or you can also use generic Get
Debug.Print usr.Get("FullName")

'---- Reading Multivalue attributes
sid = usr.Get("objectSID")
For Each sidByte In sid
  Debug.Print Hex(sidByte)
Next

'Or you can also use LBound and UBound for multivalue attribute
For i = LBound(sid) To UBound(sid)
    Debug.Print Hex(sid(i))
Next i


End Sub
