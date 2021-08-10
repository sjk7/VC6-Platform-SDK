Attribute VB_Name = "Module1"
Sub Main()

'Bind to an object with current credential
Set obj = GetObject("WinNT://INDEPENDENCE")


'Bind to an object with alternate credentials
'In production code DO NOT hard code your credentials in your source
'try getting from the user interactively and delete from the memory after use
Set DSO = GetObject("WinNT:")
Set usr = DSO.OpenDSObject("WinNT://INDEPENDENCE/JSmith,user", "Administrator", "se**cre*t*", ADS_SECURE_AUTHENTICATION)

   
    

End Sub
