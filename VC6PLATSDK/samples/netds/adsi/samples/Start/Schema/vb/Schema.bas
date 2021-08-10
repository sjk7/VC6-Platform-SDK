Attribute VB_Name = "Module1"
Sub Main()

   'Bind to a schema container
   Set Scm = GetObject("WinNT://INDEPENDENCE/Schema")
   
   'Show all items in the schema container
   For Each obj In Scm
      Debug.Print obj.Name & " (" & obj.Class & ")"
   Next
   
   'You can also bind to an object and get the schema location
   Set dom = GetObject("WinNT://INDEPENDENCE")
   Debug.Print dom.Schema
   Set Class = GetObject(dom.Schema)
   'Mandatory attributes
   For Each prop In Class.MandatoryProperties
      Debug.Print prop
   Next
   
   'Optional attributes
   For Each prop In Class.OptionalProperties
      Debug.Print prop
   Next
   
    

End Sub
