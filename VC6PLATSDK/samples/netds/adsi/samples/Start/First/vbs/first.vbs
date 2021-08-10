'----------------------------------------------------------
'--- This script enumerates ADSI objects in a computer 
'---------------------------------------------------------
Dim machineName, domainName

machineName = "mymachine"

Set comp = GetObject("WinNT://" & machineName & ",computer" )

For each obj in comp
  wscript.echo obj.Name
Next


'----------------------------------------------------------
'--- This script enumerates ADSI objects in a domain
'---------------------------------------------------------
domainName = "myDomain"

Set dom = GetObject("WinNT://" & domainName )

For each obj in dom
  wscript.echo obj.Name
Next

