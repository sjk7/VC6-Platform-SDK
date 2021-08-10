VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form CancelFaxForm 
   Caption         =   "Fax Cancelation"
   ClientHeight    =   7005
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6870
   LinkTopic       =   "Form1"
   ScaleHeight     =   7005
   ScaleWidth      =   6870
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "Refresh"
      Height          =   495
      Left            =   360
      TabIndex        =   20
      Top             =   3600
      Width           =   1455
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   375
      Left            =   5400
      TabIndex        =   19
      Top             =   840
      Width           =   1215
   End
   Begin MSComctlLib.ListView FaxListView 
      Height          =   1935
      Left            =   360
      TabIndex        =   18
      Top             =   1560
      Width           =   6255
      _ExtentX        =   11033
      _ExtentY        =   3413
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   0   'False
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   16777215
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   5
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Subject"
         Object.Width           =   2117
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Sender Name"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Recipient Name"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "Submission ID"
         Object.Width           =   2117
      EndProperty
      BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   4
         Text            =   "Status"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.Frame frameCancel 
      Caption         =   "Cancel"
      Height          =   2055
      Left            =   120
      TabIndex        =   11
      Top             =   4920
      Width           =   3375
      Begin VB.OptionButton CancelBySubject 
         Caption         =   "all faxes with this subject"
         Height          =   195
         Left            =   120
         TabIndex        =   17
         Top             =   600
         Width           =   2055
      End
      Begin VB.OptionButton CancelBySender 
         Caption         =   "all faxes from this sender"
         Height          =   195
         Left            =   120
         TabIndex        =   16
         Top             =   840
         Width           =   2055
      End
      Begin VB.OptionButton CancelBroadcast 
         Caption         =   "all faxes in the broadcast"
         Height          =   195
         Left            =   120
         TabIndex        =   15
         Top             =   1080
         Width           =   2055
      End
      Begin VB.CommandButton cmdOK 
         Caption         =   "&OK"
         Height          =   435
         Left            =   2280
         TabIndex        =   14
         Top             =   1440
         Width           =   975
      End
      Begin VB.CommandButton cmdBcastInfo 
         Caption         =   "&View list of faxes"
         Height          =   675
         Left            =   2280
         TabIndex        =   13
         Top             =   600
         Width           =   975
      End
      Begin VB.OptionButton CancelSelected 
         Caption         =   "the selected fax"
         Height          =   195
         Left            =   120
         TabIndex        =   12
         Top             =   360
         Width           =   2175
      End
   End
   Begin VB.TextBox NumbFaxesText 
      BackColor       =   &H8000000F&
      BorderStyle     =   0  'None
      Height          =   195
      Left            =   1560
      TabIndex        =   10
      Top             =   1320
      Width           =   615
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   435
      Left            =   5760
      TabIndex        =   8
      Top             =   6360
      Width           =   975
   End
   Begin VB.TextBox IdText 
      Height          =   285
      Left            =   4440
      TabIndex        =   4
      Top             =   4080
      Width           =   1815
   End
   Begin VB.TextBox SenderText 
      Height          =   285
      Left            =   4440
      TabIndex        =   3
      Top             =   4440
      Width           =   1815
   End
   Begin VB.TextBox SubjectText 
      Height          =   285
      Left            =   4440
      TabIndex        =   2
      Top             =   3720
      Width           =   1815
   End
   Begin VB.TextBox ServerNameText 
      Height          =   285
      Left            =   360
      TabIndex        =   0
      Top             =   840
      Width           =   4815
   End
   Begin VB.Label lblOutgoingFaxes 
      Caption         =   "Outgoing faxes:"
      Height          =   255
      Left            =   360
      TabIndex        =   9
      Top             =   1320
      Width           =   1215
   End
   Begin VB.Label ID_LABEL 
      Caption         =   "Submission ID"
      Height          =   255
      Left            =   3360
      TabIndex        =   7
      Top             =   4080
      Width           =   1095
   End
   Begin VB.Label SENDER_LABEL 
      Caption         =   "Sender"
      Height          =   255
      Left            =   3360
      TabIndex        =   6
      Top             =   4440
      Width           =   615
   End
   Begin VB.Label SUBJECT_LABEL 
      Caption         =   "Subject"
      Height          =   255
      Left            =   3360
      TabIndex        =   5
      Top             =   3720
      Width           =   615
   End
   Begin VB.Label SERVER_SUBMIT_LABEL 
      Caption         =   $"CancelFaxForm1.frx":0000
      Height          =   615
      Left            =   360
      TabIndex        =   1
      Top             =   120
      Width           =   4695
   End
End
Attribute VB_Name = "CancelFaxForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'Copyright (c) Microsoft Corporation.  All rights reserved.
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
'OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
'LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
'FITNESS FOR A  PARTICULAR PURPOSE

'Several objects and variables are declared in a module,
'since they are used across the module and the two forms.

Dim objFaxDevices As FaxDevices
Dim lcount As Long
Dim Id As String
Dim Connected As String

Private Sub Form_Load()
        
    'Disable features until needed
    CancelSelected.Enabled = False
    CancelBySubject.Enabled = False
    CancelBySender.Enabled = False
    CancelBroadcast.Enabled = False
    cmdBcastInfo.Enabled = False
    FaxListView.Enabled = False
    cmdOK.Enabled = False
    cmdBcastInfo.Enabled = False
    IdText.Enabled = False
    SenderText.Enabled = False
    cmdRefresh.Enabled = False
End Sub

Private Function FaxListView_Init() As Boolean
    
    'Initialize the function to return false
    FaxListView_Init = False
    
    'Error handling
    On Error GoTo Error_Handler
       
    FaxListView.HideSelection = False
    FaxListView.FullRowSelect = True
    Dim ItmAdd As ListItem
     
    'Clear the list
    FaxListView.ListItems.Clear
    
    'Clear the text box that shows the number of faxes
    NumbFaxesText.Text = ""
        
    ' Refresh the outgoing queue
    objFaxServer.Folders.OutgoingQueue.Refresh
    
    'Get the jobs collection
    Set objFaxJobs = objFaxServer.Folders.OutgoingQueue.GetJobs
    
    'Get the number of faxes in the collection
    lcount = objFaxJobs.Count()
    
    'Add items to the list view
    Dim n As Integer
  
    For n = 1 To lcount

        Set ItmAdd = FaxListView.ListItems.Add()
        Set objFaxJob = objFaxJobs.Item(n)
    
        'Call the function that converts the numerical status to a string
        Call SetStatusString
    
        'Add the fax to the list view
        ItmAdd.Text = objFaxJob.Subject
        ItmAdd.SubItems(1) = objFaxJob.Sender.Name
        ItmAdd.SubItems(2) = objFaxJob.Recipient.Name
        ItmAdd.SubItems(3) = objFaxJob.SubmissionId
        ItmAdd.SubItems(4) = StatusString
        ItmAdd.Selected = False
                
    Next
    
    'Display number of faxes
    NumbFaxesText.Text = FaxListView.ListItems.Count
    
    'Return true
    FaxListView_Init = True
    
    Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Function

Private Sub FaxListView_ColumnClick(ByVal ColumnHeader As ColumnHeader)
'This subroutine allows sorting when the user clicks on a column heading
    
    FaxListView.SortKey = (ColumnHeader.Index - 1)
    FaxListView.Sorted = True
    
    If FaxListView.SortOrder = lvwAscending Then
        FaxListView.SortOrder = lvwDescending
    Else
        FaxListView.SortOrder = lvwAscending
    End If

End Sub

Private Sub FaxListView_Click()

    'The next line ensures that you can't click when there are no faxes listed
    If objFaxJobs.Count = 0 Then Exit Sub
    
    'Close the broadcast list form if it's open
    Unload BroadcastInfoForm
    
    FaxListView.SetFocus
   
    'Enable controls
    CancelSelected.Enabled = True
    CancelBySubject.Enabled = True
    CancelBySender.Enabled = True
    CancelBroadcast.Enabled = True
    cmdOK.Enabled = True
        
    'Set cancelation of the selected fax option as default
    CancelSelected.SetFocus
    
    'Set objFaxJob equal to the selected item on the list
    Set objFaxJob = objFaxJobs.Item(FaxListView.SelectedItem.Index)
    
    'Disable the OK button if the listed fax has a canceling or canceled status
    If objFaxJob.Status = fjsCANCELED Then cmdOK.Enabled = False
    If objFaxJob.Status = fjsCANCELING Then cmdOK.Enabled = False
    
    'Place the fax information into the text boxes
    SenderText.Text = objFaxJob.Sender.Name
    SubjectText.Text = objFaxJob.Subject
    IdText.Text = objFaxJob.SubmissionId
        
    'Set variables to use in cancellation subroutines
    Sender = objFaxJob.Sender.Name
    Subject = objFaxJob.Subject
    SubmId = objFaxJob.SubmissionId
    Id = objFaxJob.Id
    
End Sub

Private Sub ServerNameText_KeyPress(KeyAscii As Integer)
    
    'Checks if Enter key has been pressed
    If KeyAscii = 13 Then
        
        'Call the subroutine that is associated with the Connect button
        Call cmdConnect_Click
        
        'Stop the beep that you usually get when you press Enter
        KeyAscii = 0
                
    End If
    
End Sub
Private Sub cmdConnect_Click()
    
    'Initialize error handling
    On Error GoTo Error_Handler
    
    'Clear the list of faxes
    FaxListView.ListItems.Clear
        
    'Clear the text box that shows the number of faxes
    NumbFaxesText.Text = ""
      
    'Check if this is the first server submitted. If not, have to unpause and unblock
    'outgoing queue on current server before assigning new server
    If Connected = "True" Then
        
       objFaxServer.Folders.OutgoingQueue.Paused = False
       objFaxServer.Folders.OutgoingQueue.Blocked = False
        
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
            
    End If
     
    'Set the FaxServerName equal to the value in the text box
    FaxServerName = ServerNameText.Text

    ' Connect to the fax server
    objFaxServer.Connect FaxServerName
    Connected = "True"
    
    If Connected = "True" Then
    'Pause and block outgoing queue on server
    objFaxServer.Folders.OutgoingQueue.Paused = True
    objFaxServer.Folders.OutgoingQueue.Blocked = True
    
    'Save the change to the outgoing queue
    objFaxServer.Folders.OutgoingQueue.Save
    
    End If
            
    'Connect succeeded, enable the refresh button and list view
    'and call the function that lists the faxes
    cmdRefresh.Enabled = True
    FaxListView.Enabled = True
    If Not FaxListView_Init() Then
            Exit Sub
    End If

Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    'Unblock the queue if connected to server
    If Connected = "True" Then
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    End If
    'Disconnect since error is likely due to access issues
    objFaxServer.Disconnect
    Connected = "False"
    'Disable the Refresh button
    cmdRefresh.Enabled = False
    
    Err.Clear
    
End Sub

Private Sub cmdOK_Click()
    
    'Disable the option buttons until another item is selected from the list
    CancelSelected.Enabled = False
    CancelBySubject.Enabled = False
    CancelBySender.Enabled = False
    CancelBroadcast.Enabled = False

    'Call a function based on the selected option
    If CancelBroadcast.Value = True Then
        If Not fCancelBroadcast() Then
            Exit Sub
        End If
    End If
    
    If CancelBySubject.Value = True Then
        If Not fCancelBySubject() Then
            Exit Sub
        End If
    End If
    
    If CancelBySender.Value = True Then
        If Not fCancelBySender() Then
            Exit Sub
        End If
    End If
    
    If CancelSelected.Value = True Then
        If Not fCancelSelected() Then
            Exit Sub
        End If
    End If
    
    'Disable the OK and View List buttons. They will be enabled when another fax is selected
    cmdOK.Enabled = False
    cmdBcastInfo.Enabled = False
    
End Sub

Private Function fCancelBySubject() As Boolean
    
    'Initialize the function to return false
    fCancelBySubject = False
    
    'Initialize error handling
    On Error GoTo Error_Handler
        
    For n = 1 To lcount
        Set objFaxJob = objFaxJobs.Item(n)
        
        'Test for faxes that were canceled but not deleted
        If objFaxJob.Status <> fjsCANCELED Then
            If objFaxJob.Subject = Subject Then objFaxJob.Cancel
        End If
        
    Next
    
    'Save changes to the outgoing queue
    objFaxServer.Folders.OutgoingQueue.Save
   
    'Refresh the list of faxes
    If Not FaxListView_Init() Then
         Exit Function
    End If

    'Return True
    fCancelBySubject = True

    Exit Function
    
Error_Handler:
    'Display error information
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    'Unblock the queue if connected to server
    If Connected = "True" Then
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    End If
End Function
Private Function fCancelBySender() As Boolean

    'Initialize the function to return false
    fCancelBySender = False
    
    'Initialize error handling
    On Error GoTo Error_Handler
    
    For n = 1 To lcount
    
        Set objFaxJob = objFaxJobs.Item(n)
        
        'Test for faxes that were canceled but not deleted
        If objFaxJob.Status <> fjsCANCELED Then
            If objFaxJob.Sender.Name = Sender Then objFaxJob.Cancel
        End If
        
    Next
       
    'Save changes to the outgoing queue
    objFaxServer.Folders.OutgoingQueue.Save
    
    'Refresh the list of faxes
    If Not FaxListView_Init() Then
        Exit Function
    End If
    
    'Return True
    fCancelBySender = True

    Exit Function
    
Error_Handler:
    'Display error information
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    'Unblock the queue if connected to server
    If Connected = "True" Then
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    End If
End Function

Private Function fCancelSelected() As Boolean
    
    'Initialize the function to return false
    fCancelSelected = False
    
    'Initialize error handling
    On Error GoTo Error_Handler
    
    'Cancel the job
    objFaxServer.Folders.OutgoingQueue.GetJob(Id).Cancel
        
   'Save changes to the outgoing queue
    objFaxServer.Folders.OutgoingQueue.Save
    
    'Refresh the list of faxes
    If Not FaxListView_Init() Then
        Exit Function
    End If

    'Return True
    fCancelSelected = True

    Exit Function
    
Error_Handler:
    'Display error information
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    'Unblock the queue if connected to server
    If Connected = "True" Then
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    End If
End Function

Private Function fCancelBroadcast() As Boolean

    'Initialize the function to return false
    fCancelBroadcast = False
    
    'Initialize error handling
    On Error GoTo Error_Handler

    For n = 1 To lcount
        Set objFaxJob = objFaxJobs.Item(n)
        
        'Test for faxes that were canceled but not deleted
        If objFaxJob.Status <> fjsCANCELED Then
            If objFaxJob.SubmissionId = SubmId Then objFaxJob.Cancel
        End If
        
    Next
    
    'Save changes to the outgoing queue
    objFaxServer.Folders.OutgoingQueue.Save
        
    'Refresh the list of faxes
    If Not FaxListView_Init() Then
        Exit Function
    End If
    
    'Return True
    fCancelBroadcast = True

    Exit Function
    
Error_Handler:
    'Display error information
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    'Unblock the queue if connected to server
    If Connected = "True" Then
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    End If
End Function

Private Sub cmdClose_Click()
    
    'Initialize error handling
    On Error GoTo Error_Handler
       
    'Unpause and unblock outgoing queue on server, but only if server
    'is actually connected (in case user clicks Close without first connecting)
    
    If Connected = "True" Then
        
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    
    End If
    
      
    'Close the form
    Unload CancelFaxForm
    Unload BroadcastInfoForm

Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    
End Sub

Private Sub CancelSelected_Click()
    Unload BroadcastInfoForm
    cmdBcastInfo.Enabled = False
    'Disable the OK button if fax has canceled or canceling status
    If objFaxJob.Status = fjsCANCELED Then cmdOK.Enabled = False
    If objFaxJob.Status = fjsCANCELING Then cmdOK.Enabled = False
End Sub

Private Sub CancelBySubject_Click()
    Unload BroadcastInfoForm
    cmdBcastInfo.Enabled = True
    cmdOK.Enabled = True
    cmdOK.SetFocus
End Sub
Private Sub CancelBySender_Click()
    Unload BroadcastInfoForm
    cmdBcastInfo.Enabled = True
    cmdOK.Enabled = True
    cmdOK.SetFocus
End Sub
Private Sub CancelBroadcast_Click()
    Unload BroadcastInfoForm
    cmdBcastInfo.Enabled = True
    cmdOK.Enabled = True
    cmdOK.SetFocus
End Sub
Private Sub cmdBCastInfo_Click()
    Load BroadcastInfoForm
End Sub
Private Sub cmdRefresh_Click()
    Call FaxListView_Init
End Sub

Private Sub Form_Unload(Cancel As Integer)
'Unblock the queue when the form is closed, if connected to server
    If Connected = "True" Then
        objFaxServer.Folders.OutgoingQueue.Paused = False
        objFaxServer.Folders.OutgoingQueue.Blocked = False
        'Save the change to the outgoing queue
        objFaxServer.Folders.OutgoingQueue.Save
    End If
End Sub

