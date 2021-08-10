Attribute VB_Name = "Module1"
Sub Main()
Set cont = GetObject("WinNT://INDEPENDENCE")
For Each obj In cont
  Debug.Print obj.Name & " (" & obj.Class & ")"
Next
End Sub
