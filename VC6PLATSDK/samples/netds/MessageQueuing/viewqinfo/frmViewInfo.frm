VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form FrmViewQInfo 
   Caption         =   "ViewInfo"
   ClientHeight    =   5715
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6600
   LinkTopic       =   "Form1"
   ScaleHeight     =   5715
   ScaleWidth      =   6600
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtComputerName 
      Height          =   285
      Left            =   1920
      TabIndex        =   8
      Top             =   360
      Width           =   2055
   End
   Begin VB.CommandButton BtnRefresh 
      Caption         =   "&Refresh"
      Default         =   -1  'True
      Height          =   375
      Left            =   4200
      TabIndex        =   6
      Top             =   360
      Width           =   1335
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   4455
      Left            =   240
      TabIndex        =   0
      Top             =   960
      Width           =   6135
      _ExtentX        =   10821
      _ExtentY        =   7858
      _Version        =   393216
      TabHeight       =   520
      Enabled         =   0   'False
      TabCaption(0)   =   "&Private Queues"
      TabPicture(0)   =   "FrmViewInfo.frx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "listPrivateQueues"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).ControlCount=   1
      TabCaption(1)   =   "&Active Queues"
      TabPicture(1)   =   "FrmViewInfo.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "listActiveQueues"
      Tab(1).ControlCount=   1
      TabCaption(2)   =   "&Computer Status"
      TabPicture(2)   =   "FrmViewInfo.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "btnToggle"
      Tab(2).Control(1)=   "LblComputerStatus"
      Tab(2).Control(2)=   "Label3"
      Tab(2).ControlCount=   3
      Begin VB.CommandButton btnToggle 
         Caption         =   "&Toggle State"
         Height          =   255
         Left            =   -70200
         TabIndex        =   5
         Top             =   720
         Width           =   1215
      End
      Begin VB.ListBox listActiveQueues 
         Height          =   3570
         ItemData        =   "FrmViewInfo.frx":0054
         Left            =   -74760
         List            =   "FrmViewInfo.frx":0056
         TabIndex        =   2
         Top             =   720
         Width           =   5535
      End
      Begin VB.ListBox listPrivateQueues 
         Height          =   3570
         ItemData        =   "FrmViewInfo.frx":0058
         Left            =   240
         List            =   "FrmViewInfo.frx":005A
         TabIndex        =   1
         Top             =   720
         Width           =   5535
      End
      Begin VB.Label LblComputerStatus 
         Caption         =   "N/A"
         Height          =   255
         Left            =   -71520
         TabIndex        =   4
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label3 
         Caption         =   "Message Queuing network connectivity state:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   3
         Top             =   720
         Width           =   3255
      End
   End
   Begin VB.Label Label2 
      Caption         =   "Enter Computer Name"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   360
      Width           =   1575
   End
End
Attribute VB_Name = "FrmViewQInfo"
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


Private Sub BtnRefresh_Click()
    Dim i As Integer
    Dim arr() As Variant
        
    ' If no computer name was entered, use the local computer
    If txtComputerName.Text = "" Then
        txtComputerName.Text = appInfo.Machine
    End If
    
    appInfo.Machine = txtComputerName.Text
    
    ' Setting the mouse pointer to hourglass (the following
    '  code might take some time)
    FrmViewQInfo.MousePointer = vbHourglass
    
    On Error GoTo ErrorHandler
    
    ' Setting the Private Queues list:
    
    ' First - we clear the displayed list
    listPrivateQueues.Clear
    
    ' Then, we obtain an array of private queue names from the
    '  MSMQApplication object
    arr() = appInfo.PrivateQueues
    
    ' And enter the names to the displayed list
    For i = LBound(arr) To UBound(arr)
        listPrivateQueues.AddItem arr(i)
    Next
        
    ' Setting the Active Queues list:
    
    ' First - we clear the displayed list
    listActiveQueues.Clear
    
    ' Then, we obtain an array of active queue names from the
    '  MSMQApplication object
    arr() = appInfo.ActiveQueues
    
    ' And enter the names to the displayed list
    For i = LBound(arr) To UBound(arr)
        listActiveQueues.AddItem arr(i)
    Next
          
    ' Is Message Queuing network connectivity enabled?
    If appInfo.IsConnected Then
        LblComputerStatus = "Connected."
    Else
        LblComputerStatus = "Disconnected."
    End If
          
          
    ' resetting the mouse pointer
    FrmViewQInfo.MousePointer = vbDefault
    SSTab1.Enabled = True
    
    Exit Sub
ErrorHandler:
    MsgBox "Error " + Hex(Err.Number) + " returned." _
        + Chr(13) + Err.Description
    
    ' An error occured, so resseting the application:
    FrmViewQInfo.MousePointer = vbDefault
    SSTab1.Enabled = False
    listActiveQueues.Clear
    listPrivateQueues.Clear
    LblComputerStatus = ""

End Sub

Private Sub btnToggle_Click()
    
    On Error GoTo ErrorHandler
    
    ' Setting the mouse pointer to hourglass (the following
    '  code might take some time)
    FrmViewQInfo.MousePointer = vbHourglass
    
    ' Toggle the connection mode
    If appInfo.IsConnected Then
        appInfo.Disconnect
        LblComputerStatus.Caption = "Disconnected."
    Else
        appInfo.Connect
        LblComputerStatus = "Connected."
    End If
    
    ' reset the mouse pointer
    FrmViewQInfo.MousePointer = vbDefault
    Exit Sub
    
ErrorHandler:
    MsgBox "Error " + Hex(Err.Number) + " returned." _
        + Chr(13) + Err.Description
    FrmViewQInfo.MousePointer = vbDefault
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub

