Attribute VB_Name = "Module1"
Sub Main()

    Dim con As New Connection, rs As New Recordset
    Dim Com As New Command
     
    
    'Open a Connection object
    con.Provider = "ADsDSOObject"
    con.Open "Active Directory Provider"
    
    ' Create a command object on this connection
    Set Com.ActiveConnection = con
    Com.CommandText = "select name from 'LDAP://DC=Fabrikam,DC=com' where objectCategory='group'"
    
    Set rs = Com.Execute
        
    
    '--------------------------------------
    ' Navigate the record set
    '----------------------------------------
    While Not rs.EOF
       'For Single Value attribute
       Debug.Print rs.Fields("Name")
       rs.MoveNext
    Wend
    

End Sub
