VERSION 5.00
Object = "{EAB22AC0-30C1-11CF-A7EB-0000C05BAE0B}#1.1#0"; "shdocvw.dll"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "HTTP MSMQ"
   ClientHeight    =   9375
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   10965
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   9375
   ScaleWidth      =   10965
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtQueueName 
      Height          =   375
      Left            =   5640
      TabIndex        =   10
      Top             =   240
      Width           =   3255
   End
   Begin VB.TextBox txtMachineName 
      Height          =   375
      Left            =   1320
      TabIndex        =   9
      Top             =   240
      Width           =   2415
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   7335
      Left            =   0
      TabIndex        =   0
      Top             =   1200
      Width           =   10965
      _ExtentX        =   19341
      _ExtentY        =   12938
      _Version        =   393216
      Tabs            =   2
      TabHeight       =   520
      TabCaption(0)   =   "Send"
      TabPicture(0)   =   "httpm.frx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "Label3"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "Label4"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "Label11"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "cbSend"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "txtTitle"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "txtBody"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "txtTTRQ"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).ControlCount=   7
      TabCaption(1)   =   "Browse"
      TabPicture(1)   =   "httpm.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "Label8"
      Tab(1).Control(1)=   "Label9"
      Tab(1).Control(2)=   "Label10"
      Tab(1).Control(3)=   "lbLookupId"
      Tab(1).Control(4)=   "Label12"
      Tab(1).Control(5)=   "WebBrowser1"
      Tab(1).Control(6)=   "cbStartPeek"
      Tab(1).Control(7)=   "cbPrev"
      Tab(1).Control(8)=   "cbNext"
      Tab(1).Control(9)=   "tbRcvLabel"
      Tab(1).Control(10)=   "tbRcvBody"
      Tab(1).ControlCount=   11
      Begin VB.TextBox txtTTRQ 
         Height          =   375
         Left            =   960
         TabIndex        =   22
         Text            =   "30"
         Top             =   3060
         Width           =   495
      End
      Begin VB.TextBox tbRcvBody 
         Enabled         =   0   'False
         Height          =   375
         Left            =   -74880
         TabIndex        =   19
         Top             =   5160
         Width           =   3255
      End
      Begin VB.TextBox tbRcvLabel 
         Enabled         =   0   'False
         Height          =   375
         Left            =   -74880
         TabIndex        =   18
         Top             =   3480
         Width           =   3255
      End
      Begin VB.CommandButton cbNext 
         Caption         =   "&Next >"
         Height          =   375
         Left            =   -73440
         TabIndex        =   14
         Top             =   2040
         Width           =   1215
      End
      Begin VB.CommandButton cbPrev 
         Caption         =   "< &Previous"
         Height          =   375
         Left            =   -74880
         TabIndex        =   13
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton cbStartPeek 
         Caption         =   "&View First Message"
         Height          =   495
         Left            =   -74880
         TabIndex        =   12
         Top             =   1320
         Width           =   2655
      End
      Begin SHDocVwCtl.WebBrowser WebBrowser1 
         Height          =   4815
         Left            =   -71520
         TabIndex        =   11
         Top             =   1860
         Width           =   7335
         ExtentX         =   12938
         ExtentY         =   8493
         ViewMode        =   0
         Offline         =   0
         Silent          =   0
         RegisterAsBrowser=   0
         RegisterAsDropTarget=   1
         AutoArrange     =   0   'False
         NoClientEdge    =   0   'False
         AlignLeft       =   0   'False
         NoWebView       =   0   'False
         HideFileNames   =   0   'False
         SingleClick     =   0   'False
         SingleSelection =   0   'False
         NoFolders       =   0   'False
         Transparent     =   0   'False
         ViewID          =   "{0057D0E0-3573-11CF-AE69-08002B2E1262}"
         Location        =   "http:///"
      End
      Begin VB.TextBox txtBody 
         Height          =   375
         Left            =   4560
         TabIndex        =   3
         Text            =   "Message Body"
         Top             =   1980
         Width           =   3495
      End
      Begin VB.TextBox txtTitle 
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Text            =   "This is the message label"
         Top             =   1980
         Width           =   3255
      End
      Begin VB.CommandButton cbSend 
         Caption         =   "&Send"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   615
         Left            =   4560
         TabIndex        =   1
         Top             =   2820
         Width           =   1695
      End
      Begin VB.Label Label12 
         Caption         =   "Msg LookupID:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   23
         Top             =   5880
         Width           =   1095
      End
      Begin VB.Label Label11 
         Caption         =   "Time-To-Reach-Queue (sec):"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   240
         TabIndex        =   21
         Top             =   2580
         Width           =   3255
      End
      Begin VB.Label lbLookupId 
         Caption         =   "Label11"
         Height          =   255
         Left            =   -73680
         TabIndex        =   20
         Top             =   5880
         Width           =   1695
      End
      Begin VB.Label Label10 
         Caption         =   "SOAP envelope:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   -70920
         TabIndex        =   17
         Top             =   1320
         Width           =   2175
      End
      Begin VB.Label Label9 
         Caption         =   "Message body:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   -74880
         TabIndex        =   16
         Top             =   4440
         Width           =   2055
      End
      Begin VB.Label Label8 
         Caption         =   "Message label:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   -74880
         TabIndex        =   15
         Top             =   2880
         Width           =   1815
      End
      Begin VB.Label Label4 
         Caption         =   "Message body:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Left            =   4560
         TabIndex        =   5
         Top             =   1500
         Width           =   3495
      End
      Begin VB.Label Label3 
         Caption         =   "Message label:"
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   12
            Charset         =   0
            Weight          =   700
            Underline       =   -1  'True
            Italic          =   -1  'True
            Strikethrough   =   0   'False
         EndProperty
         Height          =   495
         Left            =   240
         TabIndex        =   4
         Top             =   1500
         Width           =   2295
      End
   End
   Begin VB.Label lbFormatName 
      Caption         =   "....place holder for format name display......"
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   720
      Width           =   9015
   End
   Begin VB.Label Label5 
      Caption         =   "Queue name:"
      Height          =   375
      Left            =   4080
      TabIndex        =   7
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Computer name:"
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
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
Dim QueueName As String
Dim FormatName As String

Dim rcvQInfo As New MSMQQueueInfo
Dim rcvQ As MSMQQueue
Dim lastLookupId As Variant
Dim lastmsgRec As MSMQMessage

' Get and display the HTTP format name of the queue.
Private Sub SetAndDisplayFormatName()
    FormatName = "DIRECT=http://" + txtMachineName.Text + "/MSMQ/" + txtQueueName.Text
    lbFormatName.Caption = "Format name for the queue is: " + FormatName
End Sub

'Peek at the next message.
Private Sub cbNext_Click()
  On Error GoTo error_handler
  Set lastmsgRec = rcvQ.PeekNextByLookupId(lastLookupId)
  ' Display the message.
  Call DisplayLastRecvMessage

Exit Sub

error_handler:
    MsgBox "Press the 'View First Message' button first, in order to display the first message in the queue." _
           , , "msmqhttp"
End Sub
'Peek at the previous message.
Private Sub cbPrev_Click()
 On Error GoTo error_handler
 Set lastmsgRec = rcvQ.PeekPreviousByLookupId(lastLookupId)
  'Display the message.
  Call DisplayLastRecvMessage
Exit Sub

error_handler:
    MsgBox "Press the 'View First Message' button first, in order to display the first message in the queue." _
           , , "msmqhttp"
End Sub

Private Sub cbSend_Click()
  ' Declare the required objects.
  Dim qinfo As New MSMQQueueInfo
  Dim q As MSMQQueue
  Dim m As New MSMQMessage

  ' Create a destination queue and open it with SEND access.
  
  On Error GoTo error_handler
  qinfo.FormatName = FormatName
  Set q = qinfo.Open(MQ_SEND_ACCESS, MQ_DENY_NONE)
  
  ' Send message with a string body type.
  m.Label = txtTitle.Text
  m.Body = txtBody.Text
  m.MaxTimeToReachQueue = txtTTRQ.Text
  m.Send q
  
  ' Close the queue.
  q.Close
  
Exit Sub

error_handler:
    If txtMachineName.Text = "" Or txtQueueName.Text = "" Then
        MsgBox "Please fill in a computer name and a queue name." _
               , , "msmqhttp"
    Else
        MsgBox "Error " + Hex(Err.Number) + " returned." _
               + Chr(13) + Err.Description, , "msmqhttp"
    End If
End Sub

'
' Displaying a SOAP envelope using
' Internet Explorer to browse the XML file
'
Private Sub DisplayLastRecvMessage()
  Dim soapenv As String
  
  On Error GoTo error_handler
  tbRcvLabel.Text = lastmsgRec.Label
  tbRcvBody.Text = lastmsgRec.Body
  lastLookupId = lastmsgRec.LookupId
  
  lbLookupId.Caption = lastLookupId
  
  'Copy the SOAP envelope to a string.
  soapenv = lastmsgRec.SoapEnvelope
  
  'Write the SOAP envelope in a temporary file.
  Open "c:\tt.xml" For Output As #1
    Print #1, soapenv
  Close

  ' Display the file in the browser window.
  WebBrowser1.Navigate "c:\tt.xml"

Exit Sub

error_handler:
    MsgBox "There are no more messages in the queue.", , "msmqhttp"
End Sub
' Peek at the first message.
Private Sub cbStartPeek_Click()
  ' Declare the required objects.

 On Error GoTo error_handler
 rcvQInfo.FormatName = FormatName

  ' Open the destination queue with RECEIVE access.
  Set rcvQ = rcvQInfo.Open(MQ_RECEIVE_ACCESS, MQ_DENY_NONE)
  
  ' Peek at the first message in the queue.
  Set lastmsgRec = rcvQ.PeekFirstByLookupId
  ' Display the message.
  Call DisplayLastRecvMessage
Exit Sub

error_handler:
    If txtMachineName.Text = "" Or txtQueueName.Text = "" Then
        MsgBox "Please fill in a computer name and a queue name." _
               , , "msmqhttp"
    Else
        MsgBox "Error " + Hex(Err.Number) + " returned." _
               + Chr(13) + Err.Description, , "msmqhttp"
    End If
End Sub

Private Sub Form_Load()
    lbFormatName.Caption = ""
End Sub


Private Sub txtMachineName_Change()
    Call SetAndDisplayFormatName
End Sub

Private Sub txtQueueName_Change()
    Call SetAndDisplayFormatName
End Sub
