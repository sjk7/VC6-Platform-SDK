VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
Const UF_WORKSTATION_TRUST_ACCOUNT = &H1000
Const UF_ACCOUNTDISABLE = &H2
Const UF_PASSWD_NOTREQD = &H20
Const ADS_GUID_COMPUTRS_CONTAINER = "aa312825768811d1aded00c04fd8d5cd"
Const ADS_ACETYPE_ACCESS_ALLOWED = 0
Const ADS_ACEFLAG_INHERIT_ACE = 2



'---------- PARAMETERS -------------------------------------
lFlag = UF_WORKSTATION_TRUST_ACCOUNT Or UF_ACCOUNTDISABLE Or UF_PASSWD_NOTREQD
sComputer = "myMachine"
sUserOrGroup = "MyDomain\MyUserName" 'who can joins this computer

'--- BUILD WELL KNOWN GUID ADS PATH FOR COMPUTER CONTAINER-------
Set rootDSE = GetObject("LDAP://RootDSE")
sPath = "LDAP://<WKGUID=" & ADS_GUID_COMPUTRS_CONTAINER
sPath = sPath + ","
sPath = sPath + rootDSE.Get("defaultNamingContext")
sPath = sPath + ">"
Set compCont = GetObject(sPath)
sPath = "LDAP://" & compCont.Get("distinguishedName")
Set compCont = GetObject(sPath)

'------- CREATE A COMPUTER OBJECT --------------
Set comp = compCont.Create("computer", "CN=" & sComputer)
comp.Put "samAccountName", sComputer + "$"
comp.Put "userAccountControl", lFlag
comp.SetInfo

'----- SET INITIAL PASSWORD-------------------
sPwd = sComputer
sPwd = StrConv(sPwd, vbLowerCase)
comp.SetPassword sPwd

'----- SET ACL -------------------

Set sd = comp.Get("ntSecurityDescriptor")
Set dacl = sd.DiscretionaryAcl

'--ACE
Set ace = CreateObject("AccessControlEntry")
ace.AccessMask = -1 'Full Permission (Allowed)
ace.AceType = ADS_ACETYPE_ACCESS_ALLOWED
ace.AceFlags = ADS_ACEFLAG_INHERIT_ACE
ace.Trustee = sUserOrGroup

'- ACL
dacl.AddAce ace
sd.DiscretionaryAcl = dacl

'- SD
comp.Put "ntSecurityDescriptor", Array(sd)
comp.SetInfo


'---- ENABLE THE ACCOUNT ----------
comp.AccountDisabled = False
comp.SetInfo


End Sub
