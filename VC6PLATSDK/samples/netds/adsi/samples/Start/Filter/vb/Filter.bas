Attribute VB_Name = "Module1"
Sub Main()

   'Bind to a domain object
   Set dom = GetObject("WinNT://INDEPENDENCE")
   
   'Show all users and groups
   dom.Filter = Array("user", "group")
   For Each obj In dom
      Debug.Print obj.Name & " (" & obj.Class & ")"
   Next
    

End Sub
