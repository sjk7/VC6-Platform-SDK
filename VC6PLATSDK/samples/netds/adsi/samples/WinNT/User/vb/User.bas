Attribute VB_Name = "User"
Sub Main()

'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       user.bas
'
'  Contents:   Creating User, Setting user's properties, Renaming and Deleting User
'
'----------------------------------------------------------------------------

Const UF_PASSWORD_CANT_CHANGE = &H40
Const UF_DONT_EXPIRE_PASSWD = &H10000

Dim usr As IADsUser


'--------------------------------------
'--- CREATING A USER
'-----------------------------------------
domainName = "INDEPENDENCE" '--- Change DomainName accordingly
'--- Binding to a domain as currently logged on user
Set dom = GetObject("WinNT://" & domainName)
'--- Create user
Set usr = dom.Create("user", "JSmith") '--- Change UserName accordingly
usr.SetInfo


'---------------------------------------------
'--- SETTING FULLNAME AND DESCRIPTION
'------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.FullName = "John Smith"
usr.Description = "DSys WOSD Program Manager"
usr.SetInfo

'--------------------------------------------
'-- SETTING PASSWORD
'-- Do Not hard code secrets in your production source
'---------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.SetPassword "secret"

'----------------------------------------------
'--- CHANGING PASSWORD
'---Do Not hard code secrets in your production source
'------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.ChangePassword "secret", "password"


'----------------------------------------------------
'--- MUST CHANGE PASSWORD NEXT TIME LOGGIN
'----------------------------------------------------
usr.Put "PasswordExpired", CLng(1)
usr.SetInfo

'-- To clear this flag
usr.Put "PasswordExpired", CLng(0)
usr.SetInfo





'---------------------------------------------------
'--- CAN NOT CHANGE PASSWORD
'------------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.Put "userFlags", usr.Get("UserFlags") Or UF_PASSWORD_CANT_CHANGE
usr.SetInfo
'-----to clear this flag - use Xor : allow user to change his/her password
usr.Put "userFlags", usr.Get("UserFlags") Xor UF_PASSWORD_CANT_CHANGE
usr.SetInfo

'---------------------------------------------
'---- PASSWORD NEVER EXPIRES
'---------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.Put "userFlags", usr.Get("UserFlags") Or UF_DONT_EXPIRE_PASSWD
usr.SetInfo
'To clear this flag - use XOr
usr.Put "userFlags", usr.Get("UserFlags") Xor UF_DONT_EXPIRE_PASSWD
usr.SetInfo

'------------------------------------------------
'--- ACCOUNT DISABLED
'-------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.AccountDisabled = True 'disabled the account
usr.SetInfo
'To enabled an acount
usr.AccountDisabled = False 'enabled the account
usr.SetInfo

'----------------------------------------------
'--- ACCOUNT EXPIRATION
'----------------------------------------------
usr.AccountExpirationDate = Now() + 90
usr.SetInfo
'-- to set account expiration to never
usr.AccountExpirationDate = "01/01/1970"
usr.SetInfo

'-------------------------------------------------
'--- ACCOUNT LOCKOUT
'-------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.IsAccountLocked = False
usr.SetInfo


'-------------------------------------------------
'---- LOGIN WORKSTATIONS
'--------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.LoginWorkstations = Array("jupiter", "mars", "venus")
usr.SetInfo
' To display workstations the user can loggon to
For Each wksName In usr.LoginWorkstations
   Debug.Print wksName
Next
' To allow user to login for all workstation (default)
usr.LoginWorkstations = vbNullString
usr.SetInfo

'--------------------------------------------------------
' --- PASSWORD EXPIRATION
'--------------------------------------------------------
expInDay = 60&
expInSec = expInDay * (3600& * 24&)
Set dom = GetObject("WinNT://INDEPENDENCE")
dom.Put "MaxPasswordAge", CLng(expInSec)
dom.SetInfo

'--------------------------------------------------------
'--- SETTING HOME DIRECTORY AND HOME DRIVE
'--------------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.HomeDirectory = "UserHomeDirHere"
usr.HomeDirDrive = "HomeDirDriveHere"
usr.SetInfo

'--------------------------------------------------------
'--- SETTING LOGIN SCRIPT
'--------------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
usr.LoginScript = "LoginScriptHere"
usr.SetInfo


'--------------------------------------------------------
'--- GETTING PRIMARY GROUP ID
'--------------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
grpPrimaryID = usr.Get("PrimaryGroupID")


'--------------------------------------------------------
'--- GETTING SID
'--------------------------------------------------------
Set usr = GetObject("WinNT://INDEPENDENCE/jsmith,user")
sid = usr.Get("objectSID")
For Each element In sid
   Debug.Print Hex(element)
Next


'--------------------------------------------------------
'--- RENAMING A USER
'--------------------------------------------------------
Set dom = GetObject("WinNT://INDEPENDENCE")
Set usr = dom.MoveHere("WinNT://INDEPENDENCE/jsmith,user", "jjohnson")
usr.FullName = "Jane Johnson"
usr.SetInfo




'--------------------------------------------------------
'--- DELETING A USER
'--------------------------------------------------------
Set dom = GetObject("WinNT://INDEPENDENCE")
dom.Delete "user", "jjohnson"



End Sub
