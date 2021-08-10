VERSION 5.00
Begin VB.Form frmUsrMgr 
   Caption         =   "WinNT: User Manager"
   ClientHeight    =   6885
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7410
   FillColor       =   &H8000000F&
   LinkTopic       =   "Form1"
   ScaleHeight     =   6885
   ScaleWidth      =   7410
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtUserName 
      Height          =   285
      Left            =   3600
      TabIndex        =   11
      Top             =   840
      Width           =   3450
   End
   Begin VB.TextBox txtFullName 
      Height          =   285
      Left            =   3600
      TabIndex        =   15
      Top             =   1245
      Width           =   3450
   End
   Begin VB.ListBox lstGroupPath 
      Height          =   255
      Left            =   6105
      TabIndex        =   24
      Top             =   4380
      Visible         =   0   'False
      Width           =   855
   End
   Begin VB.ListBox lstGroup 
      Height          =   1620
      Left            =   2655
      TabIndex        =   21
      Top             =   4515
      Width           =   3285
   End
   Begin VB.PictureBox Picture1 
      Height          =   60
      Left            =   -420
      ScaleHeight     =   0
      ScaleWidth      =   7725
      TabIndex        =   20
      Top             =   570
      Width           =   7785
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Height          =   375
      Left            =   3060
      TabIndex        =   19
      Top             =   6465
      Width           =   1215
   End
   Begin VB.TextBox txtDescription 
      Height          =   285
      Left            =   3585
      TabIndex        =   17
      Top             =   1680
      Width           =   3495
   End
   Begin VB.Frame Frame1 
      Caption         =   "Account"
      Height          =   1035
      Left            =   4965
      TabIndex        =   12
      Top             =   2880
      Width           =   2280
      Begin VB.TextBox txtAcctDate 
         Height          =   285
         Left            =   1095
         TabIndex        =   18
         Top             =   630
         Width           =   1080
      End
      Begin VB.OptionButton optAcctEndOf 
         Caption         =   "End of "
         Height          =   375
         Left            =   240
         TabIndex        =   16
         Top             =   600
         Width           =   975
      End
      Begin VB.OptionButton optAcctNever 
         Caption         =   "Never Expires"
         Height          =   255
         Left            =   240
         TabIndex        =   14
         Top             =   240
         Width           =   1935
      End
   End
   Begin VB.CheckBox chkAcctLockedOut 
      Caption         =   "Account Locked Out"
      Height          =   435
      Left            =   2520
      TabIndex        =   10
      Top             =   3540
      Width           =   2295
   End
   Begin VB.CheckBox chkAcctDisabled 
      Caption         =   "Account Disabled"
      Height          =   495
      Left            =   2520
      TabIndex        =   8
      Top             =   3135
      Width           =   2295
   End
   Begin VB.CheckBox chkPwdNever 
      Caption         =   "Password Never Expires"
      Height          =   495
      Left            =   2520
      TabIndex        =   7
      Top             =   2745
      Width           =   2295
   End
   Begin VB.CheckBox chkCantChange 
      Caption         =   "User Cannot Change Password"
      Height          =   375
      Left            =   2520
      TabIndex        =   6
      Top             =   2460
      Width           =   3495
   End
   Begin VB.CheckBox chkMustChange 
      Caption         =   "User Must Change Password at Next Logon"
      Height          =   375
      Left            =   2520
      TabIndex        =   5
      Top             =   2100
      Width           =   3495
   End
   Begin VB.CommandButton cmdChange 
      Caption         =   "Change..."
      Height          =   360
      Left            =   2865
      TabIndex        =   3
      Top             =   60
      Width           =   1080
   End
   Begin VB.TextBox txtDomain 
      BackColor       =   &H8000000F&
      Enabled         =   0   'False
      Height          =   285
      Left            =   840
      TabIndex        =   2
      Top             =   120
      Width           =   1935
   End
   Begin VB.ListBox lstUser 
      Height          =   5520
      Left            =   120
      TabIndex        =   0
      Top             =   735
      Width           =   2205
   End
   Begin VB.Frame Frame2 
      Caption         =   "Group "
      Height          =   2310
      Left            =   2475
      TabIndex        =   22
      Top             =   3990
      Width           =   4770
      Begin VB.CommandButton frmRemove 
         Caption         =   "Remove"
         Height          =   375
         Left            =   3600
         TabIndex        =   26
         Top             =   1200
         Width           =   975
      End
      Begin VB.CommandButton cmdAdd 
         Caption         =   "Add..."
         Height          =   375
         Left            =   3600
         TabIndex        =   25
         Top             =   720
         Width           =   975
      End
      Begin VB.Label lblExplain 
         Caption         =   "Double Click to view more..."
         Height          =   210
         Left            =   120
         TabIndex        =   23
         Top             =   240
         Width           =   2100
      End
   End
   Begin VB.Label Label4 
      Caption         =   "User Name:"
      Height          =   255
      Left            =   2505
      TabIndex        =   9
      Top             =   840
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "Full Name"
      Height          =   255
      Left            =   2520
      TabIndex        =   13
      Top             =   1245
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "Description"
      Height          =   255
      Left            =   2520
      TabIndex        =   4
      Top             =   1710
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Domain:"
      Height          =   255
      Left            =   75
      TabIndex        =   1
      Top             =   135
      Width           =   855
   End
End
Attribute VB_Name = "frmUsrMgr"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       frmUsrMgr.frm
'
'  Contents:   List and Display User's Properties
'
'----------------------------------------------------------------------------
Dim cont As IADsContainer
Const UF_PASSWORD_CANT_CHANGE = &H40
Const UF_DONT_EXPIRE_PASSWD = &H10000
Const E_ADS_PROPERTY_NOT_FOUND = &H8000500D


Private Sub cmdAdd_Click()
  Dim grp As IADsGroup
  Dim usr As IADsUser
  
  On Error Resume Next
  
  frmGroupList.SetContainer cont
  frmGroupList.Show vbModal, Me
  sGroupPath = frmGroupList.GetGroupPath()
  If (sGroupPath <> "") Then
     Set grp = GetObject(sGroupPath)
     Set usr = cont.GetObject("user", lstUser.Text)
     grp.Add (usr.ADsPath)
     PopulateMemberOf usr
  End If
End Sub

Private Sub cmdChange_Click()
   ShowConnectDlg
End Sub

Private Sub ShowConnectDlg()
  frmConnect.Show vbModal, Me
  If (frmConnect.Tag <> "") Then
    txtDomain = frmConnect.Tag
  End If
  Populate frmConnect.GetUserName, frmConnect.GetPassword
End Sub
Private Sub cmdClose_Click()
 End
End Sub

Private Sub cmdOK_Click()
Dim usr As IADsUser
Set usr = cont.GetObject("user", lstUser.Text)
Call ModifyUser(usr)

End Sub





'----------------------------------------------------------------------------
'
'  Microsoft Active Directory 2.5 Sample Code
'
'  Copyright (C) Microsoft Corporation, 1996 - 1999
'
'  File:       frmUsrMgr.frm
'
'  Contents:   Displaying User's Properties
'
'----------------------------------------------------------------------------


Private Sub Form_Load()
  ShowConnectDlg
End Sub

Private Sub Populate(usrName As String, usrPassword As String)
Dim o As IADsOpenDSObject

'-- Reset the user list
lstUser.Clear

'- Open based on the credentials supplied
If (usrName <> "") Then
   Set o = GetObject("WinNT:")
   Set cont = o.OpenDSObject("WinNT://" & txtDomain, usrName, usrPassword, 1)
Else
    Set cont = GetObject("WinNT://" & txtDomain)
End If


'----- Adding all users in that domain to the list box------
cont.Filter = Array("user")
For Each usr In cont
   lstUser.AddItem usr.Name
Next

End Sub



Private Sub frmRemove_Click()
Dim usr As IADsUser
Dim grp As IADsGroup


'----- Remove the group membership ------'

sPath = lstGroupPath.List(lstGroup.ListIndex)


If (sPath <> "") Then
  Set usr = cont.GetObject("user", lstUser.Text)
  Set grp = GetObject(sPath)
  grp.Remove (usr.ADsPath) 'To remove the group, you should pass the user/group ADsPath
  PopulateMemberOf usr
End If


End Sub



Private Sub lstGroup_DblClick()
Dim o As IADs

sPath = lstGroupPath.List(lstGroup.ListIndex)
Debug.Print sPath
Set o = GetDirObject(sPath)

'Show the Group Form --------------------
frmGroup.SetObject o
frmGroup.Show vbModal, Me


End Sub

Private Sub lstUser_Click()
Dim usr As IADsUser

Set usr = cont.GetObject("user", lstUser.Text)
Call PopulateUser(usr)


End Sub

'---- Populating User
Private Sub PopulateUser(usr)
Dim usrFlags As Long
Dim dExpire As Date



'-- UserName, Full Name and Description ------
txtUserName = usr.Name
txtFullName = usr.FullName
txtDescription = usr.Description
txtAcctDate = ""

'----------------------------------
'  Password
'------------------------------------
'-Must Change Next time Logon
chkMustChange.Value = usr.Get("PasswordExpired")

'- Cannot Change Password
usrFlags = usr.Get("userFlags")
If (usrFlags And UF_PASSWORD_CANT_CHANGE) Then
   chkCantChange.Value = 1
Else
   chkCantChange.Value = 0
End If

'- Password Never Expires
If (usrFlags And UF_DONT_EXPIRE_PASSWD) Then
   chkPwdNever.Value = 1
Else
   chkPwdNever.Value = 0
End If




'----------------------------------
'  Account
'------------------------------------
'---- Account Disable -------------------
If (usr.AccountDisabled) Then
  chkAcctDisabled.Value = 1
Else
  chkAcctDisabled.Value = 0
End If
 

'---- Account Expiration -----------------
On Error Resume Next

dExpire = usr.AccountExpirationDate
If (Err.Number = E_ADS_PROPERTY_NOT_FOUND) Then   'Property Not found in the cache
   optAcctNever = True
Else
   optAcctEndOf = True
   txtAcctDate = Format(dExpire, "mm/dd/yyyy")
End If




'---- Account Locked-out --------------
chkAcctLockedOut.Value = 0
If (usr.IsAccountLocked) Then
   chkAcctLockedOut.Enabled = True
Else
   chkAcctLockedOut.Enabled = False
End If

'---------------------------------
' Group Membership
'---------------------------------
'-reset group list

PopulateMemberOf usr



End Sub

Private Sub PopulateMemberOf(ByVal usr As IADsUser)
  lstGroup.Clear
  lstGroupPath.Clear
  

  For Each grp In usr.Groups
    sGroupType = GetGroupType(grp)
    lstGroup.AddItem grp.Name & " (" & sGroupType & ")"
    lstGroupPath.AddItem grp.ADsPath
  Next
End Sub

Private Sub ModifyUser(usr)
Dim usrFlags As Long
Dim dExpire As Date
Dim bRename As Boolean

bRename = False

If (usr.Name <> txtUserName) Then 'We need to rename
  'Rename can be done via IADsContainer::MoveHere
  cont.MoveHere usr.ADsPath, txtUserName
  Set usr = cont.GetObject("user", txtUserName) 'Now get the new object
  bRename = True
End If

'-- Full Name and Description ------
usr.FullName = txtFullName
usr.Description = txtDescription

'----------------------------------
'  Password
'------------------------------------
'-Must Change Next time Logon
' 1 - Must change next time logon
' 0 - Clear the 'must change'
usr.Put ("PasswordExpired"), chkMustChange.Value

'--- Get User Flags ----
usrFlags = usr.Get("userFlags")

'- Cannot Change Password
If (chkCantChange.Value = 1) Then
   usrFlags = usrFlags Or UF_PASSWORD_CANT_CHANGE
Else
   usrFlags = usrFlags And Not (UF_PASSWORD_CANT_CHANGE)
End If

'- Password Never Expires
If (chkPwdNever = 1) Then
  usrFlags = usrFlags Or UF_DONT_EXPIRE_PASSWD
Else
  usrFlags = usrFlags And Not (UF_DONT_EXPIRE_PASSWD)
End If

'-- Set the user flags
usr.Put "userFlags", CLng(usrFlags)

'----------------------------------
'  Account
'------------------------------------
'---- Account Disable -------------------
If (chkAcctDisabled.Value = 1) Then
    usr.AccountDisabled = True
Else
    usr.AccountDisabled = False
End If

 

If (optAcctNever) Then
   usr.AccountExpirationDate = CDate("01/01/1981")
Else
   usr.AccountExpirationDate = CDate(txtAcctDate)
End If


'---- Account Locked-out --------------
If (chkAcctLockedOut.Enabled = True And chkAcctLockedOut.Value = 0) Then
   chkAcctLockedOut.Enabled = False
End If
  
'--- Commit to the Directory
usr.SetInfo

End Sub




Function GetDirObject(ByVal sPath As String)

If (frmConnect.GetUserName <> "") Then
   Set o = GetObject("WinNT:")
   Set GetDirObject = o.OpenDSObject(sPath, frmConnect.GetUserName, frmConnect.GetPassword, 1)
Else
   Set GetDirObject = GetObject(sPath)
End If

End Function

