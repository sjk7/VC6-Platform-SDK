VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form formQuickFax 
   Caption         =   "Quick Fax"
   ClientHeight    =   7740
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   7905
   LinkTopic       =   "Form1"
   ScaleHeight     =   7740
   ScaleWidth      =   7905
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdSenderInfo 
      Caption         =   "Sender &Information"
      Height          =   495
      Left            =   5880
      TabIndex        =   23
      Top             =   1440
      Width           =   1815
   End
   Begin VB.Frame frameRecipient 
      Caption         =   "Recipient information"
      Height          =   1095
      Left            =   120
      TabIndex        =   15
      Top             =   1080
      Width           =   5535
      Begin VB.TextBox txtRecipientFaxNumber 
         Height          =   285
         Left            =   1680
         TabIndex        =   17
         Top             =   720
         Width           =   3615
      End
      Begin VB.TextBox RecipientName 
         Height          =   285
         Left            =   1680
         TabIndex        =   16
         Top             =   240
         Width           =   3615
      End
      Begin VB.Label lblRecipientFaxNumber 
         Caption         =   "Fax number"
         Height          =   255
         Left            =   120
         TabIndex        =   19
         Top             =   720
         Width           =   1575
      End
      Begin VB.Label lblRecipientName 
         Caption         =   "Name"
         Height          =   255
         Left            =   120
         TabIndex        =   18
         Top             =   240
         Width           =   615
      End
   End
   Begin VB.TextBox ServerNameText 
      Height          =   285
      Left            =   1800
      TabIndex        =   9
      Top             =   240
      Width           =   5895
   End
   Begin VB.Frame AttachmentFrame 
      Caption         =   "Attachment"
      Height          =   1335
      Left            =   120
      TabIndex        =   6
      Top             =   5760
      Width           =   7575
      Begin VB.CheckBox chkAttachment 
         Caption         =   "Include attachment"
         Height          =   255
         Left            =   240
         TabIndex        =   21
         Top             =   240
         Width           =   2535
      End
      Begin VB.CommandButton cmdAttachBrowse 
         Caption         =   "B&rowse..."
         Height          =   375
         Left            =   5160
         TabIndex        =   8
         Top             =   840
         Width           =   1335
      End
      Begin MSComDlg.CommonDialog cdlAttachment 
         Left            =   6960
         Top             =   240
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.TextBox txtAttachmentPath 
         Height          =   285
         Left            =   240
         TabIndex        =   7
         Top             =   840
         Width           =   4575
      End
      Begin VB.Label lblAttachmentPath 
         Caption         =   "Full path and attachment name"
         Height          =   255
         Left            =   240
         TabIndex        =   22
         Top             =   600
         Width           =   3495
      End
   End
   Begin VB.CommandButton CmdClose 
      Caption         =   "&Close"
      Height          =   435
      Left            =   6000
      TabIndex        =   5
      Top             =   7200
      Width           =   1695
   End
   Begin VB.TextBox Subject 
      Height          =   285
      Left            =   1800
      TabIndex        =   2
      Top             =   720
      Width           =   5895
   End
   Begin VB.CommandButton CmdSendFax 
      Caption         =   "&Send"
      Height          =   435
      Left            =   3960
      TabIndex        =   0
      Top             =   7200
      Width           =   1695
   End
   Begin VB.Frame CPFrame 
      Caption         =   "Cover Page (personal)"
      Height          =   3375
      Left            =   120
      TabIndex        =   3
      Top             =   2280
      Width           =   7575
      Begin VB.TextBox txtNote 
         Height          =   1575
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   20
         Top             =   1560
         Width           =   7335
      End
      Begin MSComDlg.CommonDialog cdlBrowse 
         Left            =   6000
         Top             =   240
         _ExtentX        =   847
         _ExtentY        =   847
         _Version        =   393216
      End
      Begin VB.CommandButton cmdCPBrowse 
         Caption         =   "&Browse..."
         Height          =   375
         Left            =   5880
         TabIndex        =   14
         Top             =   840
         Width           =   1215
      End
      Begin VB.TextBox txtCPPath 
         Height          =   285
         Left            =   120
         TabIndex        =   12
         Top             =   840
         Width           =   5535
      End
      Begin VB.CheckBox chkCoverPage 
         Caption         =   "Include cover page"
         Height          =   255
         Left            =   240
         TabIndex        =   11
         Top             =   240
         Width           =   1815
      End
      Begin VB.Label lblCPLabel 
         Caption         =   "Full path and personal cover page name"
         Height          =   255
         Left            =   120
         TabIndex        =   13
         Top             =   600
         Width           =   3375
      End
      Begin VB.Label lblCPText 
         Caption         =   "Cover page note"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   1320
         Width           =   2175
      End
   End
   Begin VB.Label lblServer 
      Caption         =   "Name of fax server (blank for local server)"
      Height          =   495
      Left            =   120
      TabIndex        =   10
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label lblSubject 
      Caption         =   "Fax subject"
      Height          =   255
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   1575
   End
End
Attribute VB_Name = "formQuickFax"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Copyright (c) Microsoft Corporation.  All rights reserved.
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
'OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
'LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
'FITNESS FOR A  PARTICULAR PURPOSE

Option Explicit
Private Sub Form_Load()
    
    'Error handling
    On Error GoTo Error_Handler

    'Set the order for tabbing through text fields
    
    ServerNameText.TabIndex = 0
    Subject.TabIndex = 1
    RecipientName.TabIndex = 2
    txtRecipientFaxNumber.TabIndex = 3
    chkCoverPage.TabIndex = 7
    txtCPPath.TabIndex = 8
    cmdCPBrowse.TabIndex = 9
    txtNote.TabIndex = 10
    chkAttachment.TabIndex = 11
    txtAttachmentPath.TabIndex = 12
    cmdAttachBrowse.TabIndex = 13
    CmdSendFax.TabIndex = 14
    CmdClose.TabIndex = 15
    
    'Reset and disable controls related to cover page and
    'attachments until option is selected. Gray-out textboxes.
    chkCoverPage.Value = 0
    txtCPPath.Enabled = False
    txtCPPath.BackColor = &H80000004
    cmdCPBrowse.Enabled = False
    txtNote.Enabled = False
    txtNote.BackColor = &H80000004
    chkAttachment.Value = 0
    txtAttachmentPath.Enabled = False
    txtAttachmentPath.BackColor = &H80000004
    cmdAttachBrowse.Enabled = False
         
    'As default, create the sender object, and load the default sender information
     Set g_objFaxSender = g_objFaxDocument.Sender
     g_objFaxSender.LoadDefaultSender

Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
         
End Sub
Private Sub chkCoverPage_Click()
    
    '"Include cover page" checkbox not selected
    If chkCoverPage.Value = 0 Then
        'Disable controls for cover page selection
        txtCPPath.Enabled = False
        txtCPPath.BackColor = &H80000004
        cmdCPBrowse.Enabled = False
        txtNote.Enabled = False
        txtNote.BackColor = &H80000004
    End If
    
    'Checkbox selected
    If chkCoverPage.Value = 1 Then
        'Enable controls for cover page selection
        txtCPPath.Enabled = True
        txtCPPath.BackColor = &H80000005
        cmdCPBrowse.Enabled = True
        txtNote.Enabled = True
        txtNote.BackColor = &H80000005
    End If
    
End Sub
Private Sub chkAttachment_Click()
    
    '"Include attachment" checkbox not selected
    If chkAttachment.Value = 0 Then
        'Disable controls for attachment selection
        txtAttachmentPath.Enabled = False
        txtAttachmentPath.BackColor = &H80000004
        cmdAttachBrowse.Enabled = False
    End If
    
    'Checkbox selected
    If chkAttachment.Value = 1 Then
        'Enable controls for attachment selection
        txtAttachmentPath.Enabled = True
        txtAttachmentPath.BackColor = &H80000005
        cmdAttachBrowse.Enabled = True
    End If
    
End Sub
Private Sub cmdAttachBrowse_Click()
    'Browse for attachments
    
    cdlAttachment.DialogTitle = "Select Attachment"
    cdlAttachment.InitDir = "c:"
    cdlAttachment.Filter = "Attachments (*.*)"
    cdlAttachment.ShowOpen
    
    'Place selected path and file in textbox
    txtAttachmentPath.Text = cdlAttachment.FileName

End Sub
Private Sub cmdCPBrowse_Click()
    'Browse for cover pages
    
    cdlBrowse.DialogTitle = "Select Cover Page"
    
    'Set the initial directory to C:
    cdlBrowse.InitDir = "c:"
    
    'Allow only *.cov files to be displayed in dialog
    cdlBrowse.Filter = "Cover pages (*.cov) |*.cov"
    cdlBrowse.ShowOpen
    
    'Place selected path and file in textbox
    txtCPPath.Text = cdlBrowse.FileName

End Sub
Private Sub CmdSendFax_Click()
           
    'Error handling
    On Error GoTo Error_Handler
    
    'Check if the attachment checkbox was selected, but no attachment provided
    If chkAttachment.Value = 1 And txtAttachmentPath.Text = "" Then
        MsgBox "Please provide the path to the attachment and try again."
        Exit Sub
    End If

    'Remove the previous recipient, if there is one. Otherwise, the fax would be sent to
    'recipients that accumulate in the FaxRecipients collection from each previous use of the form.
    If g_objFaxDocument.Recipients.Count = 1 Then g_objFaxDocument.Recipients.Remove (1)
    
    'Set no cover page as default
    g_objFaxDocument.CoverPageType = fcptNONE
    
    'If the checkbox is selected, set cover page type to "local"
    'and set the path and file name to the textbox text
    If chkCoverPage.Value = 1 Then
        g_objFaxDocument.CoverPageType = fcptLOCAL
        g_objFaxDocument.CoverPage = txtCPPath.Text
    End If
    
    'Set the rest of the fax document properties
    g_objFaxDocument.Note = txtNote.Text
    g_objFaxDocument.Subject = Subject.Text
    g_objFaxDocument.Recipients.Add txtRecipientFaxNumber.Text, RecipientName.Text
    g_objFaxDocument.Sender.Name = g_objFaxSender.Name
    g_objFaxDocument.Sender.FaxNumber = g_objFaxSender.FaxNumber
    g_objFaxDocument.Sender.OfficePhone = g_objFaxSender.OfficePhone
    'Include the attachment if the attachment checkbox is selected
    If chkAttachment.Value = 1 Then g_objFaxDocument.Body = txtAttachmentPath.Text
        
    'Submit the document to the server
    Call g_objFaxDocument.Submit(ServerNameText.Text)
       
    'clear all fields
    txtNote.Text = ""
    Subject.Text = ""
    txtRecipientFaxNumber.Text = ""
    RecipientName.Text = ""
    
    'Disable controls related to cover page
    txtCPPath.Enabled = False
    cmdCPBrowse.Enabled = False
    txtNote.Enabled = False
        
    'Disable controls related to attachment
    txtAttachmentPath.Enabled = False
    cmdAttachBrowse.Enabled = False
            
    'Clear checkboxs
    chkCoverPage.Value = 0
    chkAttachment.Value = 0
    
Exit Sub
Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
         
End Sub
Private Sub CmdClose_Click()
    End
End Sub
Private Sub cmdSenderInfo_Click()
    Load formSenderInfo
End Sub

