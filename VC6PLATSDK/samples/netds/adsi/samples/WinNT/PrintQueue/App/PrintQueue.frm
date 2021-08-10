VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form frmPrintQueue 
   Caption         =   "Print Queue and Print Jobs"
   ClientHeight    =   5700
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7800
   LinkTopic       =   "Form1"
   ScaleHeight     =   5700
   ScaleWidth      =   7800
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtPrintStatus 
      BackColor       =   &H80000004&
      Height          =   285
      Left            =   4200
      TabIndex        =   16
      Top             =   2400
      Width           =   2655
   End
   Begin VB.TextBox txtModel 
      BackColor       =   &H80000004&
      Height          =   285
      Left            =   4200
      TabIndex        =   15
      Top             =   2040
      Width           =   2655
   End
   Begin VB.TextBox txtPrintPath 
      BackColor       =   &H80000004&
      Height          =   285
      Left            =   4200
      TabIndex        =   10
      Top             =   1680
      Width           =   2655
   End
   Begin VB.TextBox txtLocation 
      BackColor       =   &H80000004&
      Height          =   285
      Left            =   4200
      TabIndex        =   9
      Top             =   1320
      Width           =   2655
   End
   Begin VB.TextBox txtDescription 
      BackColor       =   &H80000004&
      Height          =   285
      Left            =   4200
      TabIndex        =   8
      Top             =   960
      Width           =   2655
   End
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "Refresh Status"
      Height          =   375
      Left            =   5280
      TabIndex        =   7
      Top             =   240
      Width           =   1575
   End
   Begin VB.CommandButton cmdChange 
      Caption         =   "Change..."
      Height          =   345
      Left            =   3570
      TabIndex        =   2
      Top             =   240
      Width           =   1365
   End
   Begin VB.TextBox txtComputer 
      BackColor       =   &H8000000F&
      ForeColor       =   &H80000012&
      Height          =   315
      Left            =   1155
      TabIndex        =   1
      Top             =   255
      Width           =   2265
   End
   Begin VB.ListBox lstPrintQueue 
      Height          =   4155
      Left            =   225
      TabIndex        =   0
      Top             =   1065
      Width           =   2130
   End
   Begin VB.Frame Frame1 
      Caption         =   "Print Jobs"
      Height          =   2865
      Left            =   2520
      TabIndex        =   4
      Top             =   2760
      Width           =   5175
      Begin MSComctlLib.ListView lstPrintJob 
         Height          =   2415
         Left            =   240
         TabIndex        =   18
         Top             =   240
         Width           =   4815
         _ExtentX        =   8493
         _ExtentY        =   4260
         LabelWrap       =   -1  'True
         HideSelection   =   -1  'True
         _Version        =   393217
         ForeColor       =   -2147483640
         BackColor       =   -2147483643
         BorderStyle     =   1
         Appearance      =   1
         NumItems        =   0
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "Computer "
      Height          =   735
      Left            =   195
      TabIndex        =   5
      Top             =   15
      Width           =   4920
      Begin VB.Label Label1 
         Caption         =   "Name:"
         Height          =   270
         Left            =   255
         TabIndex        =   6
         Top             =   270
         Width           =   750
      End
   End
   Begin VB.Label Label6 
      Caption         =   "Print Status"
      Height          =   255
      Left            =   2640
      TabIndex        =   17
      Top             =   2400
      Width           =   975
   End
   Begin VB.Label Label5 
      Caption         =   "Model"
      Height          =   255
      Left            =   2640
      TabIndex        =   14
      Top             =   2040
      Width           =   975
   End
   Begin VB.Label Label4 
      Caption         =   "Printer Path"
      Height          =   255
      Left            =   2640
      TabIndex        =   13
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Location"
      Height          =   255
      Left            =   2640
      TabIndex        =   12
      Top             =   1320
      Width           =   1335
   End
   Begin VB.Label lblText 
      Caption         =   "Description"
      Height          =   255
      Left            =   2640
      TabIndex        =   11
      Top             =   960
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Print Queue:"
      Height          =   240
      Left            =   285
      TabIndex        =   3
      Top             =   780
      Width           =   1275
   End
End
Attribute VB_Name = "frmPrintQueue"
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
'  File: frmPrintQueue.frm
'
'  Contents: Display PrintQueue's and Print Job's Properties for a given computer.
'
'----------------------------------------------------------------------------

'--- Variable Constants--------------
Dim cont As IADsContainer





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
lstPrintQueue.Clear
Set cont = GetObject("WinNT://" & computerStr & ",computer")

cont.Filter = Array("PrintQueue")
For Each pq In cont
  lstPrintQueue.AddItem pq.Name
Next

End Sub

Private Function GetCurrentPrintQueue() As IADsPrintQueue
 If (lstPrintQueue.Text = "") Then
    Set GetCurrentPrintQueue = Nothing
    Exit Function
 End If
    
 Set GetCurrentPrintQueue = cont.GetObject("printQueue", lstPrintQueue.Text)

End Function


Private Sub cmdRefresh_Click()
  lstPrintQueue_Click
End Sub

Private Sub Form_Load()
 
'---- Print Jobs
lstPrintJob.ColumnHeaders.Add , , "Description"
lstPrintJob.ColumnHeaders.Add , , "User"
lstPrintJob.ColumnHeaders.Add , , "Printed"
lstPrintJob.ColumnHeaders.Add , , "Status"
    
    
'--- Set to Report View ---------------
lstPrintJob.View = 3
' Call cmdChange to force the user to select computer
 cmdChange_Click


End Sub


Private Sub lstPrintQueue_Click()
Dim pq As IADsPrintQueue
Dim pQOps As IADsPrintQueueOperations
Dim pj As IADsPrintJob
Dim pjOps As IADsPrintJobOperations

    

Set pq = GetCurrentPrintQueue()

'-------Print Queue --------------------------
On Error Resume Next
txtDescription = pq.Description
txtPrintPath = pq.PrinterPath
txtLocation = pq.Location
txtModel = pq.Model




'----- Print Queue Operations ---------
Set pQOps = pq
txtPrintStatus = GetPrintStatus(pQOps.status)

'---- Print Jobs and Print Job Operations ---------------------
lstPrintJob.ListItems.Clear ' Clear the user interface
For Each pj In pQOps.PrintJobs
   Set pjOps = pj
   Set newLine = lstPrintJob.ListItems.Add(, , pj.Description)
   newLine.SubItems(1) = pj.User
   newLine.SubItems(2) = CStr(pjOps.PagesPrinted)
   newLine.SubItems(3) = GetJobStatus(pjOps.status)
Next


End Sub
