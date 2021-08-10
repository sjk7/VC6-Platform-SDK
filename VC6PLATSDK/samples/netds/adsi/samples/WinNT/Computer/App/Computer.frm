VERSION 5.00
Begin VB.Form frmComputer 
   Caption         =   "Computer"
   ClientHeight    =   7755
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7590
   LinkTopic       =   "Form1"
   ScaleHeight     =   7755
   ScaleWidth      =   7590
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Refresh 
      Caption         =   "Refresh"
      Height          =   345
      Left            =   3165
      TabIndex        =   27
      Top             =   6390
      Width           =   1290
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "Close"
      Default         =   -1  'True
      Height          =   360
      Left            =   3285
      TabIndex        =   26
      Top             =   7260
      Width           =   1185
   End
   Begin VB.Frame Frame2 
      Caption         =   "Resource"
      Height          =   2580
      Left            =   5100
      TabIndex        =   24
      Top             =   4260
      Width           =   2400
      Begin VB.ListBox lstResource 
         Height          =   1620
         Left            =   180
         TabIndex        =   25
         Top             =   285
         Width           =   1980
      End
   End
   Begin VB.Frame Frame5 
      Caption         =   "Session"
      Height          =   2580
      Left            =   2625
      TabIndex        =   22
      Top             =   4275
      Width           =   2400
      Begin VB.ListBox lstSession 
         Height          =   1620
         Left            =   180
         TabIndex        =   23
         Top             =   285
         Width           =   1980
      End
   End
   Begin VB.CommandButton cmdShare 
      Caption         =   "New..."
      Height          =   345
      Left            =   630
      TabIndex        =   19
      Top             =   6375
      Width           =   1290
   End
   Begin VB.Frame Frame4 
      Caption         =   "Shares"
      Height          =   2580
      Left            =   90
      TabIndex        =   20
      Top             =   4275
      Width           =   2400
      Begin VB.ListBox lstShare 
         Height          =   1620
         Left            =   165
         TabIndex        =   21
         Top             =   285
         Width           =   1980
      End
   End
   Begin VB.TextBox txtProcessorCount 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   4005
      TabIndex        =   17
      Top             =   3285
      Width           =   2445
   End
   Begin VB.TextBox txtOSVersion 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3990
      TabIndex        =   8
      Top             =   2055
      Width           =   2445
   End
   Begin VB.TextBox txtProcessor 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3990
      TabIndex        =   7
      Top             =   2865
      Width           =   2445
   End
   Begin VB.TextBox txtOwner 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3990
      TabIndex        =   6
      Top             =   2460
      Width           =   2445
   End
   Begin VB.TextBox txtOS 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3990
      TabIndex        =   4
      Top             =   1650
      Width           =   2445
   End
   Begin VB.CommandButton cmdChange 
      Caption         =   "Change..."
      Height          =   345
      Left            =   3570
      TabIndex        =   3
      Top             =   240
      Width           =   1365
   End
   Begin VB.TextBox txtDomain 
      BackColor       =   &H8000000F&
      ForeColor       =   &H80000012&
      Height          =   315
      Left            =   1155
      TabIndex        =   2
      Top             =   255
      Width           =   2265
   End
   Begin VB.TextBox txtDivision 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   3990
      TabIndex        =   1
      Top             =   1275
      Width           =   2445
   End
   Begin VB.ListBox lstComputer 
      Height          =   2985
      Left            =   225
      TabIndex        =   0
      Top             =   1065
      Width           =   2010
   End
   Begin VB.Frame Frame1 
      Caption         =   "Properties"
      Height          =   3045
      Left            =   2535
      TabIndex        =   9
      Top             =   930
      Width           =   4935
      Begin VB.Label Label5 
         Caption         =   "Processor Count"
         Height          =   240
         Left            =   150
         TabIndex        =   18
         Top             =   2370
         Width           =   1320
      End
      Begin VB.Label Label4 
         Caption         =   "Processor"
         Height          =   210
         Left            =   180
         TabIndex        =   14
         Top             =   1965
         Width           =   1110
      End
      Begin VB.Label Label3 
         Caption         =   "Owner"
         Height          =   225
         Left            =   180
         TabIndex        =   13
         Top             =   1560
         Width           =   1080
      End
      Begin VB.Label lblSvcType 
         Caption         =   "OS Version"
         Height          =   195
         Left            =   165
         TabIndex        =   12
         Top             =   1155
         Width           =   1125
      End
      Begin VB.Label Label7 
         Caption         =   "OS"
         Height          =   165
         Left            =   180
         TabIndex        =   11
         Top             =   765
         Width           =   810
      End
      Begin VB.Label DisplayName 
         Caption         =   "Division"
         Height          =   210
         Left            =   165
         TabIndex        =   10
         Top             =   375
         Width           =   1485
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Domain"
      Height          =   735
      Left            =   195
      TabIndex        =   15
      Top             =   15
      Width           =   7215
      Begin VB.Label Label1 
         Caption         =   "Name:"
         Height          =   270
         Left            =   255
         TabIndex        =   16
         Top             =   270
         Width           =   750
      End
   End
   Begin VB.Label Label2 
      Caption         =   "Computer:"
      Height          =   240
      Left            =   285
      TabIndex        =   5
      Top             =   780
      Width           =   1275
   End
End
Attribute VB_Name = "frmComputer"
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
'  File:       frmComputer.frm
'
'  Contents:   Main Computer Form
'
'----------------------------------------------------------------------------

Dim cont As IADsContainer
Dim lanSvc As IADsFileService
Public usrName As String
Public usrPassword As String




Private Sub cmdChange_Click()
  ShowConnectDlg
  PopulateComputer frmConnect.GetUserName, frmConnect.GetPassword
  
End Sub

Private Sub ShowConnectDlg()
  frmConnect.Show vbModal, Me
  If (frmConnect.Tag = "") Then
    txtDomain = ""
 Else
    txtDomain = frmConnect.Tag
 End If

End Sub
Private Sub PopulateComputer(user As String, password As String)
Dim o As IADsOpenDSObject
lstComputer.Clear

'Assign the varibles
usrName = user
usrPassword = password
domain = txtDomain
'-------------------------------------------
'- Open based on the credentials supplied
'--------------------------------------------
Set cont = BindObject("WinNT://" & domain)

'--------------------------------------------------------
' Computer is specified eg, dc01,computer
' then get the computer's parent ( which is a domain )
'----------------------------------------------------------
If InStr(txtDomain, ",computer") > 0 Then
  lstComputer.AddItem cont.Name
Else
  'If domain was specified, enumerate all computers in that domain
  cont.Filter = Array("Computer")
  For Each comp In cont
     lstComputer.AddItem comp.Name
  Next
End If

End Sub
Private Function BindObject(adsPath As String) As IADs
Dim o As IADsOpenDSObject
If (usrName <> "") Then
   Set o = GetObject("WinNT:")
   Set BindObject = o.OpenDSObject(adsPath, usrName, usrPassword, 1)
Else
   Set BindObject = GetObject(adsPath)
End If


End Function

Private Function GetCurrentComputer() As IADsComputer

 
 If (lstComputer.Text = "") Then
    Set GetCurrentComputer = Nothing
    Exit Function
 End If
 'If it is already computer object, set the computer
 If (cont.Class = "Computer") Then
    Set GetCurrentComputer = cont
 Else
    Set GetCurrentComputer = cont.GetObject("computer", lstComputer.Text)
 End If

End Function



Private Sub cmdRestart_Click()
Dim op As IADsComputerOperations
Set op = GetCurrentComputer()
'-- ShutDown is NOT IMPLEMENTED in ADSI 2.5
'op.Shutdown (True)
End Sub


Private Sub cmdClose_Click()
End
End Sub

Private Sub cmdShare_Click()
Dim newShare As String
Dim fileShare As IADsFileShare

'-- Get the information
frmShare.Show vbModal, Me
 
newShare = frmShare.txtNewShare
'--- Now create the share
If (newShare <> "") Then
   If (IsEmpty(lanSvc) = False) Then
      Set fileShare = lanSvc.Create("fileShare", newShare)
      fileShare.Path = frmShare.txtPath
      fileShare.SetInfo
      RefreshShare
   End If
End If
 
 
End Sub

Private Sub cmdShutdown_Click()
Dim op As IADsComputerOperations
Set op = GetCurrentComputer()
op.Shutdown (False)

End Sub

Private Sub Form_Load()

 usrName = ""
 usrPassword = ""
 Set lanSvc = Nothing
 '-----------------------------------------------------
 ' Call cmdChange to force the user to select computer
 '------------------------------------------------------
 cmdChange_Click
 



End Sub


Private Sub lstComputer_Click()
Dim cmp As IADsComputer
Dim fileShare As IADsFileShare

Dim rsc As IADsResource
Dim session As IADsSession

    
Set cmp = GetCurrentComputer()

txtDivision = cmp.Division
txtOS = cmp.OperatingSystem
txtOSVersion = cmp.OperatingSystemVersion
txtOwner = cmp.Owner
txtProcessor = cmp.Processor
txtProcessorCount = cmp.ProcessorCount


'Populate File Shares
Set lanSvc = BindObject(cmp.adsPath & "/" & "LanmanServer")

RefreshResource

RefreshSession

RefreshShare

End Sub

Sub RefreshResource()
On Error Resume Next
lstResource.Clear
For Each rsc In lanSvc.Resources
    lstResource.AddItem rsc.Path
Next
End Sub
Sub RefreshSession()
lstSession.Clear
If (IsEmpty(lanSvc) = False) Then
    For Each session In lanSvc.Sessions
      lstSession.AddItem session.Name
    Next
End If
End Sub

Sub RefreshShare()

On Error Resume Next
lstShare.Clear
For Each fileShare In lanSvc
  lstShare.AddItem fileShare.Name
Next
End Sub

Private Sub Refresh_Click()
  RefreshSession
End Sub
