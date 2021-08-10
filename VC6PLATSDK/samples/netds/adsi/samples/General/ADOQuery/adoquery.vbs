'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996-1999
'
'  File:       adoquery.vbs
'
'
'----------------------------------------------------------------------------


Public Const ADS_SCOPE_BASE = 0
Public Const ADS_SCOPE_ONELEVEL = 1
Public Const ADS_SCOPE_SUBTREE = 2

'--------------------------------------------------------------------------------
' ADO Query
'------------------------------------------------------------------------------

    
    Set con = CreateObject("ADODB.Connection")
    Set com =   CreateObject("ADODB.Command")
    
    'Open a Connection object
    con.Provider = "ADsDSOObject"
    
    '---------------------------------------------------------------------
    ' If you want to be authenticated other than current logged on user
    ' use connection properties of User ID and Password
    '---------------------------------------------------------------------
    'con.Properties("User ID") = "DOMAIN\UserName"
    'con.Properties("Password") = "passwordHere"
    'con.Properties("Encrypt Password") = True  

    '--- For anonymous authentication-----
    '---
    'con.Properties("User ID") = ""
    'con.Properties("Password") = ""
    'con.Properties("Encrypt Password") = False
     

    
    
    '------------------------------------
    ' Open the connection
    '-------------------------------------
    con.Open "Active Directory Provider"
    
    ' Create a command object on this connection
    Set Com.ActiveConnection = con
    
    '--------------------------------------------------
    ' set the query string
    '---------------------------------------------------
    ' For non Active Directory , you should use LDAP://<yourServer>/DN 
    ' For NT 4.0 and Win9x without DS client packate, you must also specify the LDAP://<serverName>/DN
    ' Comment out the replace adDomainPath with the new value
    ' for example: Com.CommandText = "select name from 'LDAP://ntdsdc1/dc=ntdev,dc=microsoft,dc=com' where objectClass='*'"
    ' Exchange Example:"select name from 'LDAP://exchsrv1/O=Microsoft' where objectClass='*'"
    
   
    adDomainPath = "LDAP://yourServer/DC=ArcadiaBay,DC=com"
    Com.CommandText = "select name from '" & adDomainPath & "' where objectClass='*' "  
    'Note: You may also specify the sort, eg. ORDER BY NAME ( after where clause )
    
    '---------------------------------------------------
    ' Or you can use LDAP Dialect, for example,
    '---------------------------------------------------
    ' Ex Com.CommandText = "<LDAP://ntdsdc1/dc=NTDEV,DC=microsof,DC=com>;(objectClass=*);name"
    ' For LDAP Dialect, the valid search scope are base, oneLevel and subtree
    ' Com.CommandText = "<" & adDomainPath & ">;(objectClass=*);name;subtree"
    
    '-----------------------------------------
    'Set the preferences for Search
    '--------------------------------------
    Com.Properties("Page Size") = 1000
    Com.Properties("Timeout") = 30 'seconds
    Com.Properties("searchscope") = ADS_SCOPE_SUBTREE 'Define in ADS_SCOPEENUM
    Com.Properties("Cache Results") = False ' do not cache the result, it results in less memory requirements
    
    '-----------------------------------------------------------------------------------
    ' For LDAP Dialect (<LDAP:...>), there is no way to specify sort order in the string,
    ' Hoever, you can use this SORT ON property to specify sort order.
    ' for SQL Dialect you can use ORDER BY in the SQL Statement
    ' Ex. Com.Properties("Sort On") = "Name"
    
    '--------------------------------------------
    'Execute the query
    '--------------------------------------------
    Set rs = Com.Execute
        
    
    '--------------------------------------
    ' Navigate the record set
    '----------------------------------------
    rs.MoveFirst
    
    While Not rs.EOF
        wscript.echo "Name  = ", rs.Fields("Name").Value
        rs.MoveNext
    Wend
        

      