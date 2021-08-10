VERSION 5.00
Begin VB.Form frmService 
   Caption         =   "Service"
   ClientHeight    =   4815
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7125
   LinkTopic       =   "Form1"
   ScaleHeight     =   4815
   ScaleWidth      =   7125
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "Refresh Status"
      Height          =   375
      Left            =   5280
      TabIndex        =   23
      Top             =   240
      Width           =   1575
   End
   Begin VB.TextBox txtSvcStatus 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3960
      TabIndex        =   22
      Top             =   3240
      Width           =   2445
   End
   Begin VB.TextBox txtSvcType 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3960
      TabIndex        =   11
      Top             =   2055
      Width           =   2445
   End
   Begin VB.TextBox txtOrderGroup 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3960
      TabIndex        =   10
      Top             =   2865
      Width           =   2445
   End
   Begin VB.TextBox txtErrorControl 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3960
      TabIndex        =   9
      Top             =   2460
      Width           =   2445
   End
   Begin VB.TextBox txtStartType 
      BackColor       =   &H8000000F&
      Height          =   315
      Left            =   3960
      TabIndex        =   7
      Top             =   1650
      Width           =   2445
   End
   Begin VB.CommandButton cmdChange 
      Caption         =   "Change..."
      Height          =   345
      Left            =   3570
      TabIndex        =   6
      Top             =   240
      Width           =   1365
   End
   Begin VB.TextBox txtComputer 
      BackColor       =   &H8000000F&
      ForeColor       =   &H80000012&
      Height          =   315
      Left            =   1155
      TabIndex        =   5
      Top             =   255
      Width           =   2265
   End
   Begin VB.TextBox txtDisplayName 
      BackColor       =   &H8000000F&
      Height          =   285
      Left            =   3960
      TabIndex        =   4
      Top             =   1275
      Width           =   2445
   End
   Begin VB.CommandButton cmdPause 
      Caption         =   "Pause"
      Height          =   360
      Left            =   5445
      TabIndex        =   3
      Top             =   4020
      Width           =   1170
   End
   Begin VB.CommandButton cmdStop 
      Caption         =   "Stop"
      Height          =   360
      Left            =   4095
      TabIndex        =   2
      Top             =   4020
      Width           =   1170
   End
   Begin VB.CommandButton cmdStart 
      Caption         =   "Start"
      Height          =   360
      Left            =   2775
      TabIndex        =   1
      Top             =   4035
      Width           =   1170
   End
   Begin VB.ListBox lstService 
      Height          =   3570
      Left            =   225
      TabIndex        =   0
      Top             =   1065
      Width           =   2010
   End
   Begin VB.Frame Frame1 
      Caption         =   "Properties"
      Height          =   2745
      Left            =   2535
      TabIndex        =   12
      Top             =   930
      Width           =   4470
      Begin VB.Label Label5 
         Caption         =   "Status"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   2280
         Width           =   855
      End
      Begin VB.Label Label4 
         Caption         =   "Order Group:"
         Height          =   210
         Left            =   120
         TabIndex        =   17
         Top             =   1965
         Width           =   1110
      End
      Begin VB.Label Label3 
         Caption         =   "Error Control:"
         Height          =   225
         Left            =   120
         TabIndex        =   16
         Top             =   1560
         Width           =   1080
      End
      Begin VB.Label lblSvcType 
         Caption         =   "Service Type:"
         Height          =   195
         Left            =   120
         TabIndex        =   15
         Top             =   1155
         Width           =   1125
      End
      Begin VB.Label Label7 
         Caption         =   "Startup:"
         Height          =   165
         Left            =   120
         TabIndex        =   14
         Top             =   765
         Width           =   810
      End
      Begin VB.Label DisplayName 
         Caption         =   "Display Name:"
         Height          =   210
         Left            =   120
         TabIndex        =   13
         Top             =   375
         Width           =   1485
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Operations"
      Height          =   945
      Left            =   2505
      TabIndex        =   18
      Top             =   3705
      Width           =   4500
   End
   Begin VB.Frame Frame3 
      Caption         =   "Computer "
      Height          =   735
      Left            =   195
      TabIndex        =   19
      Top             =   15
      Width           =   4920
      Begin VB.Label Label1 
         Caption         =   "Name:"
         Height          =   270
         Left            =   255
         TabIndex        =   20
         Top             =   270
         Width           =   750
      End
   End
   Begin VB.Label Label2 
      Caption         =   "Services:"
      Height          =   240
      Left            =   285
      TabIndex        =   8
      Top             =   780
      Width           =   1275
   End
End
Attribute VB_Name = "frmService"
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
'  File: frmService.frm
'
'  Contents: Display Service's Properties for a given computer.  Start, stop, Pause
'            using IADsServiceOperations
'
'----------------------------------------------------------------------------


Dim cont As IADsContainer

'--- Defined in winnt.h ----------------

Const SERVICE_BOOT_START = &H0
Const SERVICE_SYSTEM_START = &H1
Const SERVICE_AUTO_START = &H2
Const SERVICE_DEMAND_START = &H3
Const SERVICE_DISABLED = &H4

'
' Error control type
'
Const SERVICE_ERROR_IGNORE = &H0
Const SERVICE_ERROR_NORMAL = &H1
Const SERVICE_ERROR_SEVERE = &H2
Const SERVICE_ERROR_CRITICAL = &H3

Const SERVICE_KERNEL_DRIVER = &H1
Const SERVICE_FILE_SYSTEM_DRIVER = &H2
Const SERVICE_ADAPTER = &H4
Const SERVICE_RECOGNIZER_DRIVER = &H8

Const SERVICE_DRIVER = &HB
Const SERVICE_WIN32_OWN_PROCESS = &H10
Const SERVICE_WIN32_SHARE_PROCESS = &H20
Const SERVICE_WIN32 = &H30
Const SERVICE_INTERACTIVE_PROCESS = &H100


Const ADS_SERVICE_STOPPED = &H1
Const ADS_SERVICE_START_PENDING = &H2
Const ADS_SERVICE_STOP_PENDING = &H3
Const ADS_SERVICE_RUNNING = &H4
Const ADS_SERVICE_CONTINUE_PENDING = &H5
Const ADS_SERVICE_PAUSE_PENDING = &H6
Const ADS_SERVICE_PAUSED = &H7
Const ADS_SERVICE_ERROR = &H8



Private Sub cmdChange_Click()
  ShowComputerDlg
  PopulateService (txtComputer)
End Sub

Private Sub ShowComputerDlg()
  frmConnect.Show vbModal, Me
  If (frmConnect.Tag = "") Then
    txtComputer = "LocalHost"
 Else
    txtComputer = frmConnect.Tag
 End If

End Sub
Private Sub PopulateService(computerStr As String)
On Error Resume Next
lstService.Clear
Set cont = GetObject("WinNT://" & computerStr & ",computer")

cont.Filter = Array("Service")
For Each svc In cont
  lstService.AddItem svc.Name
Next

End Sub

Private Function GetCurrentService() As IADsService
 If (lstService.Text = "") Then
    Set GetCurrentService = Nothing
    Exit Function
 End If
    
 Set GetCurrentService = cont.GetObject("service", lstService.Text)

End Function

Private Sub cmdPause_Click()
On Error Resume Next
Dim svc As IADsService
Dim svcOp As IADsServiceOperations

    
Set svc = GetCurrentService()
Set svcOp = svc

svcOp.Pause
'Refresh the status by simulating user's selection
lstService_Click


End Sub

Private Sub cmdRefresh_Click()
 lstService_Click
End Sub

Private Sub cmdStart_Click()
On Error Resume Next
Dim svc As IADsService
Dim svcOp As IADsServiceOperations

    
Set svc = GetCurrentService()
Set svcOp = svc

svcOp.Start

'Refresh the status by simulating user's selection
lstService_Click

End Sub

Private Sub cmdStop_Click()
On Error Resume Next
Dim svc As IADsService
Dim svcOp As IADsServiceOperations

    
Set svc = GetCurrentService()
Set svcOp = svc

svcOp.Stop

'Refresh the status by simulating user's selection
lstService_Click

End Sub

Private Sub Form_Load()
 
' Call cmdChange to force the user to select computer
 cmdChange_Click
 



End Sub


Private Sub lstService_Click()
Dim svc As IADsService
Dim svcOps As IADsServiceOperations
    
Set svc = GetCurrentService()

txtDisplayName = svc.DisplayName




'Order Group
txtOrderGroup = svc.LoadOrderGroup

Select Case svc.StartType
  Case SERVICE_BOOT_START
    txtStartType = "Boot Start"
  Case SERVICE_SYSTEM_START
    txtStartType = "System Start"
  Case SERVICE_AUTO_START
    txtStartType = "Automatic"
  Case SERVICE_DEMAND_START
    txtStartType = "Manual"
  Case SERVICE_DISABLED
    txtStartType = "Disabled"
  Case Else
    txtStartType = "Unknown"
End Select

'Error Control
Select Case svc.ErrorControl

Case SERVICE_ERROR_IGNORE
   txtErrorControl = "Service ignores error"
Case SERVICE_ERROR_NORMAL
   txtErrorControl = "No Error"
Case SERVICE_ERROR_SEVERE
 txtErrorControl = "Severe error"
Case SERVICE_ERROR_CRITICAL
 txtErrorControl = "Critical error"
Case Else
  txtErrorControl = "Unknown"
End Select

'-------------------------------------------
' Service Type
'---------------------------------------------
Select Case svc.ServiceType

Case SERVICE_KERNEL_DRIVER
     txtSvcType = "Kernel Driver"
Case SERVICE_FILE_SYSTEM_DRIVER
     txtSvcType = "File System Driver"
Case SERVICE_ADAPTER
     txtSvcType = "Adapter"
Case SERVICE_RECOGNIZER_DRIVER
     txtSvcType = "Recognizer Driver"
Case SERVICE_WIN32_OWN_PROCESS
     txtSvcType = "Win32 Process"
Case SERVICE_WIN32_SHARE_PROCESS
     txtSvcType = "Win32 Share Process"
Case SERVICE_WIN32
     txtSvcType = "Win32"
Case SERVICE_INTERACTIVE_PROCESS
     txtSvcType = "Interactive Process"
End Select
                                        
'--- Get the Service Status
Set svcOps = svc

Select Case svcOps.Status
Case ADS_SERVICE_STOPPED:
   txtSvcStatus = "Stopped"
Case ADS_SERVICE_START_PENDING:
   txtSvcStatus = "Start Pending"
Case ADS_SERVICE_STOP_PENDING:
   txtSvcStatus = "Stop Pending"
Case ADS_SERVICE_RUNNING:
   txtSvcStatus = "Running"
Case ADS_SERVICE_CONTINUE_PENDING:
  txtSvcStatus = "Continue Pending"
Case ADS_SERVICE_PAUSE_PENDING:
 txtSvcStatus = "Pause Pending"
Case ADS_SERVICE_PAUSED:
 txtSvcStatus = "Paused"
Case ADS_SERVICE_ERROR:
 txtSvcStatus = "Error"
End Select

Set svc = Nothing
Set svcOps = Nothing
End Sub

