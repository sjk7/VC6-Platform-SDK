VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmManageQueue 
   Caption         =   "Manage Queue"
   ClientHeight    =   5985
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6660
   LinkTopic       =   "Form1"
   ScaleHeight     =   5985
   ScaleWidth      =   6660
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Enter queue name"
      Height          =   1215
      Left            =   240
      TabIndex        =   20
      Top             =   720
      Width           =   4815
      Begin VB.TextBox txtFormatName 
         Enabled         =   0   'False
         Height          =   285
         Left            =   1800
         TabIndex        =   24
         Top             =   840
         Width           =   2775
      End
      Begin VB.TextBox txtPathName 
         Height          =   285
         Left            =   1800
         TabIndex        =   23
         Top             =   360
         Width           =   2775
      End
      Begin VB.OptionButton optFormatName 
         Caption         =   "FormatName:"
         Height          =   255
         Left            =   120
         TabIndex        =   22
         Top             =   840
         Width           =   1455
      End
      Begin VB.OptionButton optPathName 
         Caption         =   "PathName:"
         Height          =   255
         Left            =   120
         TabIndex        =   21
         Top             =   360
         Value           =   -1  'True
         Width           =   1095
      End
   End
   Begin VB.CommandButton btnRefresh 
      Caption         =   "&Refresh"
      Default         =   -1  'True
      Height          =   375
      Left            =   5160
      TabIndex        =   3
      Top             =   1560
      Width           =   1215
   End
   Begin VB.TextBox txtComputerName 
      Height          =   285
      Left            =   2520
      TabIndex        =   2
      Top             =   240
      Width           =   2535
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   3375
      Left            =   240
      TabIndex        =   0
      Top             =   2280
      Width           =   6135
      _ExtentX        =   10821
      _ExtentY        =   5953
      _Version        =   393216
      TabHeight       =   520
      Enabled         =   0   'False
      TabCaption(0)   =   "&General Info"
      TabPicture(0)   =   "frmManageQueue.frx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Label3"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "lblMessageCount"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "Label4"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "lblQueueType"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "Label5"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "lblQueuePlacement"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "Label2"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "lblFormatName"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).ControlCount=   8
      TabCaption(1)   =   "&Local Queue"
      TabPicture(1)   =   "frmManageQueue.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Label6"
      Tab(1).Control(1)=   "lblBytesInQueue"
      Tab(1).Control(2)=   "Label7"
      Tab(1).Control(3)=   "lblBytesInJournal"
      Tab(1).Control(4)=   "Label9"
      Tab(1).Control(5)=   "lblJournalMessageCount"
      Tab(1).ControlCount=   6
      TabCaption(2)   =   "&Outgoing Queue"
      TabPicture(2)   =   "frmManageQueue.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "Label8"
      Tab(2).Control(1)=   "Label10"
      Tab(2).Control(2)=   "lblState"
      Tab(2).Control(3)=   "btnResume"
      Tab(2).Control(4)=   "btnPause"
      Tab(2).Control(5)=   "lstNextHops"
      Tab(2).ControlCount=   6
      Begin VB.ListBox lstNextHops 
         Height          =   1035
         ItemData        =   "frmManageQueue.frx":0054
         Left            =   -74760
         List            =   "frmManageQueue.frx":0056
         TabIndex        =   26
         Top             =   2040
         Width           =   5535
      End
      Begin VB.CommandButton btnPause 
         Caption         =   "&Pause"
         Enabled         =   0   'False
         Height          =   255
         Left            =   -74760
         TabIndex        =   25
         Top             =   1200
         Width           =   975
      End
      Begin VB.CommandButton btnResume 
         Caption         =   "&Resume"
         Enabled         =   0   'False
         Height          =   255
         Left            =   -73440
         TabIndex        =   18
         Top             =   1200
         Width           =   1095
      End
      Begin VB.Label lblFormatName 
         Caption         =   "N/A"
         Height          =   255
         Left            =   480
         TabIndex        =   28
         Top             =   2520
         Width           =   5415
      End
      Begin VB.Label Label2 
         Caption         =   "FormatName:"
         Height          =   255
         Left            =   240
         TabIndex        =   27
         Top             =   2160
         Width           =   1215
      End
      Begin VB.Label lblState 
         Caption         =   "N/A"
         Height          =   255
         Left            =   -73560
         TabIndex        =   19
         Top             =   720
         Width           =   1815
      End
      Begin VB.Label Label10 
         Caption         =   "Next Hops:"
         Height          =   255
         Left            =   -74760
         TabIndex        =   17
         Top             =   1680
         Width           =   975
      End
      Begin VB.Label Label8 
         Caption         =   "State: "
         Height          =   255
         Left            =   -74760
         TabIndex        =   16
         Top             =   720
         Width           =   495
      End
      Begin VB.Label lblJournalMessageCount 
         Caption         =   "N/A"
         Height          =   255
         Left            =   -72720
         TabIndex        =   15
         Top             =   1680
         Width           =   1695
      End
      Begin VB.Label Label9 
         Caption         =   "Journal Message Count:"
         Height          =   255
         Left            =   -74760
         TabIndex        =   14
         Top             =   1680
         Width           =   1935
      End
      Begin VB.Label lblBytesInJournal 
         Caption         =   "N/A"
         Height          =   255
         Left            =   -72720
         TabIndex        =   13
         Top             =   1200
         Width           =   1815
      End
      Begin VB.Label Label7 
         Caption         =   "Bytes In Queue:"
         Height          =   255
         Left            =   -74760
         TabIndex        =   12
         Top             =   1200
         Width           =   1575
      End
      Begin VB.Label lblBytesInQueue 
         Caption         =   "N/A"
         Height          =   255
         Left            =   -72720
         TabIndex        =   11
         Top             =   720
         Width           =   2175
      End
      Begin VB.Label Label6 
         Caption         =   "Bytes In Journal:"
         Height          =   255
         Left            =   -74760
         TabIndex        =   10
         Top             =   720
         Width           =   1335
      End
      Begin VB.Label lblQueuePlacement 
         Caption         =   "N/A"
         Height          =   255
         Left            =   1800
         TabIndex        =   9
         Top             =   1680
         Width           =   1455
      End
      Begin VB.Label Label5 
         Caption         =   "Queue Placement:"
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   1680
         Width           =   1335
      End
      Begin VB.Label lblQueueType 
         Caption         =   "N/A"
         Height          =   255
         Left            =   1800
         TabIndex        =   7
         Top             =   1200
         Width           =   1935
      End
      Begin VB.Label Label4 
         Caption         =   "Queue Type:"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   1200
         Width           =   1215
      End
      Begin VB.Label lblMessageCount 
         Caption         =   "N/A"
         Height          =   255
         Left            =   1800
         TabIndex        =   5
         Top             =   720
         Width           =   2415
      End
      Begin VB.Label Label3 
         Caption         =   "Message Count:"
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   720
         Width           =   1335
      End
   End
   Begin VB.Label Label1 
      Caption         =   "Managed Computer Name:"
      Height          =   255
      Left            =   360
      TabIndex        =   1
      Top             =   240
      Width           =   2055
   End
End
Attribute VB_Name = "frmManageQueue"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

' --------------------------------------------------------------------
'
'  Copyright (c) Microsoft Corporation.  All rights reserved
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' --------------------------------------------------------------------

Option Explicit

Dim appInfo As New MSMQApplication

Dim mngqLocalQueue As MSMQQueueManagement
Dim mngoOutgoingQueue As MSMQOutgoingQueueManagement

Private Sub btnPause_Click()
   
    ' Setting the mouse pointer to hourglass (the following
    '  code might take some time)
    frmManageQueue.MousePointer = vbHourglass
    
    On Error GoTo ErrorHandler
    
    ' Pause the queue
    mngoOutgoingQueue.Pause
    
    ' set the pause/resume buttons state
    btnResume.Enabled = True
    btnPause.Enabled = False
     
    ' Get the new state and display it
    Call DisplayQueueState
    
    ' resetting the mouse pointer
    frmManageQueue.MousePointer = vbDefault
    
    Exit Sub
ErrorHandler:
    
    ' resetting the mouse pointer
    frmManageQueue.MousePointer = vbDefault
    MsgBox "Error " + Hex(Err.Number) + " returned." _
        + Chr(13) + Err.Description
 

End Sub

Private Sub DisplayQueueState()
    ' Display the state of the queue
    Select Case mngoOutgoingQueue.State
        Case MQ_QUEUE_STATE_CONNECTED
            lblState.Caption = "Connected"
        Case MQ_QUEUE_STATE_DISCONNECTED
            lblState.Caption = "Disconnected"
        Case MQ_QUEUE_STATE_DISCONNECTING
            lblState.Caption = "Disconnecting"
        Case MQ_QUEUE_STATE_LOCAL_CONNECTION
            lblState.Caption = "Local connection"
        Case MQ_QUEUE_STATE_NEEDVALIDATE
            lblState.Caption = "Need validate"
        Case MQ_QUEUE_STATE_NONACTIVE
            lblState.Caption = "Non active"
        Case MQ_QUEUE_STATE_ONHOLD
            lblState.Caption = "On hold"
        Case MQ_QUEUE_STATE_WAITING
            lblState.Caption = "Waiting"
    End Select

End Sub


Private Sub LocalQueue()
    ' set the valid fields
    lblBytesInJournal.Caption = mngqLocalQueue.BytesInJournal
    lblBytesInQueue.Caption = mngqLocalQueue.BytesInQueue
    lblJournalMessageCount.Caption = mngqLocalQueue.MessageCount
    
    ' empty the not applicable fields.
    lblState.Caption = "N/A"
    lstNextHops.Clear
    btnResume.Enabled = False
    btnPause.Enabled = False

End Sub

Private Sub OutgoingQueue()
    Dim arr() As Variant
    Dim i As Integer

    Call DisplayQueueState
    
    ' Checking if the queue is paused in order to enable/disable
    '  the pause and resume buttons accordingly
    If mngoOutgoingQueue.State = MQ_QUEUE_STATE_ONHOLD Then
        btnResume.Enabled = True
        btnPause.Enabled = False
    Else
        btnResume.Enabled = False
        btnPause.Enabled = True
    End If
    
    ' Set the next hop list
    arr() = mngoOutgoingQueue.NextHops
    For i = LBound(arr) To UBound(arr)
        lstNextHops.AddItem arr(i)
    Next i
            
    ' empty the not applicable fields
    lblBytesInJournal.Caption = "N/A"
    lblBytesInQueue.Caption = "N/A"
    lblJournalMessageCount.Caption = "N/A"

End Sub



Private Sub btnRefresh_Click()
    Dim mngQueue As New MSMQManagement
    
    
    ' Setting the mouse pointer to hourglass (the following
    '  code might take some time)
    frmManageQueue.MousePointer = vbHourglass
    
    On Error GoTo ErrorHandler
    
    ' If no computer name wat entered - the default is the
    ' local computer.
    If txtComputerName.Text = "" Then
        txtComputerName.Text = appInfo.Machine
    End If
   
    ' Check what type of name is used - format name or
    ' path name.
    If optFormatName.Value Then
    
        ' Handle a blank format name
        If txtFormatName.Text = "" Then
            MsgBox " Please enter a valid Format Name"
            frmManageQueue.MousePointer = vbDefault
            Exit Sub
        Else
            ' Init the queue manager with the Formatname parameter
            mngQueue.Init Machine:=txtComputerName.Text, FormatName:=txtFormatName.Text
        End If
    
    Else
        ' Handle a blank PathName
        If txtPathName.Text = "" Then
            MsgBox " Please enter a valid Path Name"
            frmManageQueue.MousePointer = vbDefault
            Exit Sub
        Else
            ' Init the queue manager with the PathName parameter
            mngQueue.Init Machine:=txtComputerName.Text, PathName:=txtPathName.Text
        End If
    End If
    
    ' Set the Message count field
    lblMessageCount.Caption = mngQueue.MessageCount
        
    ' find the type of the queue and display it
    Select Case mngQueue.QueueType
        Case MQ_TYPE_PUBLIC
            lblQueueType.Caption = "Public"
        Case MQ_TYPE_MACHINE
            lblQueueType.Caption = "Machine"
        Case MQ_TYPE_MULTICAST
            lblQueueType.Caption = "Multicast"
        Case MQ_TYPE_PRIVATE
            lblQueueType.Caption = "Private"
        Case MQ_TYPE_CONNECTOR
            lblQueueType.Caption = "Connector"
    End Select
    
    lblFormatName.Caption = mngQueue.FormatName

    ' Check if its a local or outgoing queue
    If mngQueue.IsLocal Then
        ' A local queue
        lblQueuePlacement.Caption = "Local Queue"
                  
        ' set the queue managment object
        Set mngqLocalQueue = mngQueue
        
        Call LocalQueue
        
     Else
        'An outgoing queue
        lblQueuePlacement.Caption = "Outgoing Queue"
        
        ' set the outgoing queue managment object
        Set mngoOutgoingQueue = mngQueue
        
        Call OutgoingQueue
 
    End If
    
    
    
    ' resetting the mouse pointer
    frmManageQueue.MousePointer = vbDefault
    
    ' Enable the tabs.
    SSTab1.Enabled = True
    
    Exit Sub
ErrorHandler:
    MsgBox "Error " + Hex(Err.Number) + " returned." _
        + Chr(13) + Err.Description
    
    ' On error - reset all the fields
    SSTab1.Enabled = False
    frmManageQueue.MousePointer = vbDefault
    lblFormatName.Caption = "N/A"
    lblBytesInJournal.Caption = "N/A"
    lblBytesInQueue.Caption = "N/A"
    lblJournalMessageCount.Caption = "N/A"
    lblState.Caption = "N/A"
    lblMessageCount.Caption = "N/A"
    lblQueuePlacement.Caption = "N/A"
    lblQueueType.Caption = "N/A"
    lstNextHops.Clear
    btnResume.Enabled = False
    btnPause.Enabled = False
 
End Sub


Private Sub btnResume_Click()
    
    ' Setting the mouse pointer to hourglass (the following
    '  code might take some time)
    frmManageQueue.MousePointer = vbHourglass
    
    On Error GoTo ErrorHandler
    
    ' Resume the outgoing queue
    mngoOutgoingQueue.Resume
    
    ' set the pause/resume buttons state
    btnResume.Enabled = False
    btnPause.Enabled = True
    
    
    ' Display the state of the queue
    Call DisplayQueueState
    

    ' resetting the mouse pointer
    frmManageQueue.MousePointer = vbDefault
    
    Exit Sub
ErrorHandler:
    ' resetting the mouse pointer
    frmManageQueue.MousePointer = vbDefault
    MsgBox "Error " + Hex(Err.Number) + " returned." _
        + Chr(13) + Err.Description
 
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub

Private Sub optFormatName_Click()
    
    txtPathName.Enabled = False
    txtFormatName.Enabled = True
    
End Sub

Private Sub optPathName_Click()
    
    txtFormatName.Enabled = False
    txtPathName.Enabled = True
    
End Sub

