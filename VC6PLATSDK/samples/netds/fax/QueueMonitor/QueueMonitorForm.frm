VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form QMonitorForm 
   Caption         =   "Outgoing Queue Monitor"
   ClientHeight    =   8355
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   10365
   LinkTopic       =   "Form1"
   ScaleHeight     =   8355
   ScaleWidth      =   10365
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox TextNumbFaxes 
      Appearance      =   0  'Flat
      BackColor       =   &H80000004&
      BorderStyle     =   0  'None
      Height          =   285
      Left            =   1800
      TabIndex        =   5
      Top             =   1320
      Width           =   615
   End
   Begin VB.TextBox ServerNameText 
      Height          =   285
      Left            =   120
      TabIndex        =   3
      Top             =   600
      Width           =   4815
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   375
      Left            =   5400
      TabIndex        =   2
      Top             =   600
      Width           =   975
   End
   Begin MSComctlLib.ListView FaxQueueListView 
      Height          =   6015
      Left            =   120
      TabIndex        =   1
      Top             =   1680
      Width           =   9975
      _ExtentX        =   17595
      _ExtentY        =   10610
      View            =   3
      Arrange         =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   7
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Subject"
         Object.Width           =   2470
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Submission Time"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Fax Number"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "Recipient Name"
         Object.Width           =   2646
      EndProperty
      BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   4
         Text            =   "Status"
         Object.Width           =   2823
      EndProperty
      BeginProperty ColumnHeader(6) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   5
         Text            =   "Extended Status"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(7) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   6
         Text            =   "Job ID"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   375
      Left            =   8280
      TabIndex        =   0
      Top             =   7800
      Width           =   1815
   End
   Begin VB.Label LabelNumbFaxes 
      Caption         =   "Faxes in the queue:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   1320
      Width           =   1455
   End
   Begin VB.Label lblServer 
      Caption         =   "Type name of fax server (blank for local server), then press Connect"
      Height          =   495
      Left            =   120
      TabIndex        =   4
      Top             =   360
      Width           =   4815
   End
End
Attribute VB_Name = "QMonitorForm"
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
Dim WithEvents g_objfaxserver As FAXCOMEXLib.FaxServer
Attribute g_objfaxserver.VB_VarHelpID = -1
Dim g_objFaxJob As FAXCOMEXLib.FaxOutgoingJob
Dim g_StatusString As String
Dim g_ExStatusString As String
Dim g_ItmAdd As ListItem
Dim g_FaxJobStatus As FAXCOMEXLib.FaxJobStatus

'Create variables to contain the job status and extended status
Dim StatusValue As Variant
Dim ExStatusValue As Variant
Private Sub Form_Load()
    
    'Initialize the FaxServer object.
    Set g_objfaxserver = New FAXCOMEXLib.FaxServer
    ServerNameText.TabIndex = 0
    
    'Set list background to gray
    FaxQueueListView.BackColor = &H80000004

End Sub
Private Sub cmdConnect_Click()
    Dim FaxServerName As String
    
    'Error handling
    On Error GoTo Error_Handler
    
    'Set list background to gray
    FaxQueueListView.BackColor = &H80000004

    'Clear the list and the number-of-faxes field
    FaxQueueListView.ListItems.Clear
    TextNumbFaxes.Text = " "
            
    'Set the server name to the value in the text box
     FaxServerName = ServerNameText.Text
     
     ' Connect to the fax server
     g_objfaxserver.Connect FaxServerName
     
   'Register for events
    g_objfaxserver.ListenToServerEvents fsetOUT_QUEUE
 
    'Call the subroutine that lists the jobs
    If Not FaxQueueListView_Init() Then
        Exit Sub
    End If
    
    'Set list background to white
    FaxQueueListView.BackColor = &H80000005

Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    
End Sub
Private Sub ServerNameText_KeyPress(KeyAscii As Integer)
                  
    'Set list background to gray
    FaxQueueListView.BackColor = &H80000004
    'Put a blank string in the number of faxes text box
    TextNumbFaxes.Text = " "
    
    'Checks if Enter key has been pressed
    If KeyAscii = 13 Then
        'Call the subroutine that is associated with the Connect button
        Call cmdConnect_Click
        'Stop the beep that you usually get when you press Enter
        KeyAscii = 0
    End If
    
End Sub
Private Function FaxQueueListView_Init() As Boolean
     
    'Initialize the function to return false
    FaxQueueListView_Init = False
       
    'Error handling
    On Error GoTo Error_Handler
   
    Dim objFaxOutgoingJobs As FAXCOMEXLib.FaxOutgoingJobs
    
    FaxQueueListView.ListItems.Clear
    
    'Get the collection of jobs
    Set objFaxOutgoingJobs = g_objfaxserver.Folders.OutgoingQueue.GetJobs
    
    'Get the number of jobs
    Dim lcount As Long
    lcount = objFaxOutgoingJobs.Count()
        
    'Add the jobs to the list view
    Dim n As Integer
    For n = 1 To lcount
        
        Set g_objFaxJob = objFaxOutgoingJobs.Item(n)
                     
        StatusValue = g_objFaxJob.Status
        ExStatusValue = g_objFaxJob.ExtendedStatusCode

    
        'Call the functions that convert the numerical status
        'and extended status to strings
        If Not SetStatusString() Then
            Exit Function
        End If
        
        If Not SetExStatusString() Then
            Exit Function
        End If
        
        'Add the fax to the list view
        'Note that this may display private information from the fax
        Set g_ItmAdd = FaxQueueListView.ListItems.Add()
        g_ItmAdd.Text = g_objFaxJob.Subject
        g_ItmAdd.SubItems(1) = Format(g_objFaxJob.SubmissionTime)
        g_ItmAdd.SubItems(2) = g_objFaxJob.Recipient.FaxNumber
        g_ItmAdd.SubItems(3) = g_objFaxJob.Recipient.Name
        g_ItmAdd.SubItems(4) = g_StatusString
        g_ItmAdd.SubItems(5) = g_ExStatusString
        g_ItmAdd.SubItems(6) = g_objFaxJob.Id
        
        'Remove canceled or completed broadcast jobs, though they remain in the outgoing queue
        'Without this code, if you stop and start the program, canceled broadcast faxes will be listed.
        If StatusValue = fjsCANCELED Then FaxQueueListView.ListItems.Remove (g_ItmAdd.Index)
        If StatusValue = fjsCOMPLETED Then FaxQueueListView.ListItems.Remove (g_ItmAdd.Index)
        
        'Re-initialize the status and extended status variables
        StatusValue = 0
        ExStatusValue = 0
        
    Next
    
    'Update the field that displays the number of faxes
    TextNumbFaxes = FaxQueueListView.ListItems.Count
    
    'Return True if the function has succeeded
    FaxQueueListView_Init = True
      
Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Function
Private Sub FaxQueueListView_ColumnClick(ByVal ColumnHeader As ColumnHeader)
'This subroutine allows sorting when the user clicks on a column heading
    
    FaxQueueListView.SortKey = (ColumnHeader.Index - 1)
    FaxQueueListView.Sorted = True
    
    If FaxQueueListView.SortOrder = lvwAscending Then
        FaxQueueListView.SortOrder = lvwDescending
    Else
        FaxQueueListView.SortOrder = lvwAscending
    End If

End Sub
Private Sub g_objFaxServer_OnOutgoingJobAdded(ByVal pFaxServer As FAXCOMEXLib.IFaxServer, ByVal bstrJobId As String)
    
     'Error handling
     On Error Resume Next
     Err.Clear

     'Add the new job to the list
      Set g_objFaxJob = g_objfaxserver.Folders.OutgoingQueue.GetJob(bstrJobId)
     
     'Error handling
     If Err.Number <> 0 Then
         MsgBox "Error number: " & Err.Number & ", " & Err.Description
         Exit Sub
     End If
     
     'Get the job status and extended status
     StatusValue = g_objFaxJob.Status
     ExStatusValue = g_objFaxJob.ExtendedStatusCode
          
     'Call the functions that convert the numerical status
     'and extended status to strings
     If Not SetStatusString() Then
        Exit Sub
     End If
        
     If Not SetExStatusString() Then
        Exit Sub
     End If
     
     'Add the fax to the list view
     Set g_ItmAdd = FaxQueueListView.ListItems.Add(FaxQueueListView.ListItems.Count + 1)
     g_ItmAdd.Text = g_objFaxJob.Subject
     g_ItmAdd.SubItems(1) = Format(g_objFaxJob.SubmissionTime)
     g_ItmAdd.SubItems(2) = g_objFaxJob.Recipient.FaxNumber
     g_ItmAdd.SubItems(3) = g_objFaxJob.Recipient.Name
     g_ItmAdd.SubItems(4) = g_StatusString
     g_ItmAdd.SubItems(5) = g_ExStatusString
     g_ItmAdd.SubItems(6) = g_objFaxJob.Id
          
     'Update the field that displays the number of faxes
     TextNumbFaxes = FaxQueueListView.ListItems.Count
              
     'Error handling
     If Err.Number <> 0 Then
         MsgBox "Error number: " & Err.Number & ", " & Err.Description
         Exit Sub
     End If
End Sub
Private Sub g_objFaxServer_OnOutgoingJobChanged(ByVal pFaxServer As FAXCOMEXLib.IFaxServer, ByVal bstrJobId As String, ByVal g_FaxJobStatus As FAXCOMEXLib.IFaxJobStatus)
    
    'Store the status and extended status values for use in the status string functions
    StatusValue = g_FaxJobStatus.Status
    ExStatusValue = g_FaxJobStatus.ExtendedStatusCode
    
    'Error handling
    On Error Resume Next
    Err.Clear

    'itmFound will hold a specific item from the list
    Dim itmFound As ListItem
    'The FaxIndex variable keeps track of where the fax is on the list view
    Dim FaxIndex As Integer

    'Get the fax from the list view
    Set itmFound = FaxQueueListView.FindItem(bstrJobId, 1, , 0)
            
    'Error handling
    If Err.Number <> 0 Then
         MsgBox "Error number: " & Err.Number & ", " & Err.Description
         Exit Sub
    End If
    
    'Get the list index for the item
    FaxIndex = itmFound.Index
            
    'Call the functions that convert the numerical status
    'and extended status to strings
    If Not SetStatusString() Then
        Exit Sub
    End If
    
    If Not SetExStatusString() Then
        Exit Sub
    End If
    
    'Update the status and extended status columns for the changed item
    FaxQueueListView.ListItems.Item(FaxIndex).ListSubItems(4).Text = g_StatusString
    FaxQueueListView.ListItems.Item(FaxIndex).ListSubItems(5).Text = g_ExStatusString
    
    'Remove canceled or completed broadcast jobs, though they remain in the outgoing queue
    'To do this, create a call to the OnOutgoingJobRemoved event, which would not be called
    'automatically under these circumstances.
    If StatusValue = fjsCANCELED Then Call g_objFaxServer_OnOutgoingJobRemoved(pFaxServer, bstrJobId)
    If StatusValue = fjsCOMPLETED Then Call g_objFaxServer_OnOutgoingJobRemoved(pFaxServer, bstrJobId)
    
    'Re-initialize the status and extended status values
    StatusValue = 0
    ExStatusValue = 0
    
    'Error handling
    If Err.Number <> 0 Then
         MsgBox "Error number: " & Err.Number & ", " & Err.Description
         Exit Sub
    End If
End Sub
Private Sub g_objFaxServer_OnOutgoingJobRemoved(ByVal pFaxServer As FAXCOMEXLib.IFaxServer, ByVal bstrJobId As String)
        
    'This subroutine removes items that have been completed or canceled
        
    'Error handling
    On Error Resume Next
    Err.Clear

    Dim itmFound As ListItem
    
    'The FaxIndex variable keeps track of where the fax is on the list view
    Dim FaxIndex As Integer
    'Get the fax from the list view
    Set itmFound = FaxQueueListView.FindItem(bstrJobId, 1, , 0)
    FaxIndex = itmFound.Index
       
    'The next line handles attempts to remove broadcast faxes that are still in the queue,
    'but have been removed from the list
    If FaxIndex = 0 Then Exit Sub
    
    FaxQueueListView.ListItems.Remove (FaxIndex)
    
    'Update the field that displays the number of faxes
     TextNumbFaxes = FaxQueueListView.ListItems.Count

    'Error handling
    If Err.Number <> 0 Then
         MsgBox "Error number: " & Err.Number & ", " & Err.Description
         Exit Sub
    End If

End Sub
Private Function SetStatusString() As Boolean

    'Initialize the function to return false
    SetStatusString = False
    
    'Error Handling
    On Error GoTo Error_Handler:
    
    'Subroutine to replace status values with strings
    If StatusValue = fjsPENDING Then g_StatusString = "Pending"
    If StatusValue = fjsINPROGRESS Then g_StatusString = "In Progress"
    If StatusValue = fjsFAILED Then g_StatusString = "Failed"
    If StatusValue = fjsPAUSED Then g_StatusString = "Paused"
    If StatusValue = fjsNOLINE Then g_StatusString = "No Line"
    If StatusValue = fjsRETRYING Then g_StatusString = "Retrying"
    If StatusValue = fjsRETRIES_EXCEEDED Then g_StatusString = "Retries Exceeded"
    If StatusValue = fjsCOMPLETED Then g_StatusString = "Completed"
    If StatusValue = fjsCANCELED Then g_StatusString = "Canceled"
    If StatusValue = fjsCANCELING Then g_StatusString = "Canceling"
    If StatusValue = fjsROUTING Then g_StatusString = "Routing"
    If StatusValue = fjsPENDING + fjsPAUSED Then g_StatusString = "Pending (paused)"
    If StatusValue = fjsRETRYING + fjsPAUSED Then g_StatusString = "Retrying (paused)"
    If StatusValue = fjsPENDING + fjsNOLINE Then g_StatusString = "Pending (no line)"
    If StatusValue = fjsRETRYING + fjsNOLINE Then g_StatusString = "Retrying (no line)"
    
    'Return True
    SetStatusString = True
    
Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    
End Function
Private Function SetExStatusString() As Boolean

    'Initialize the function to return false
    SetExStatusString = False
    
    'Error Handling
    On Error GoTo Error_Handler:
    
    'Subroutine to replace extended status values with strings
    If ExStatusValue = fjesANSWERED Then g_ExStatusString = "Answered"
    If ExStatusValue = fjesBAD_ADDRESS Then g_ExStatusString = "Bad address"
    If ExStatusValue = fjesBUSY Then g_ExStatusString = "Busy"
    If ExStatusValue = fjesCALL_ABORTED Then g_ExStatusString = "Call aborted"
    If ExStatusValue = fjesCALL_BLACKLISTED Then g_ExStatusString = "Call blacklisted"
    If ExStatusValue = fjesCALL_COMPLETED Then g_ExStatusString = "Call completed"
    If ExStatusValue = fjesCALL_DELAYED Then g_ExStatusString = "Call delayed"
    If ExStatusValue = fjesDIALING Then g_ExStatusString = "Dialing"
    If ExStatusValue = fjesDISCONNECTED Then g_ExStatusString = "Disconnected"
    If ExStatusValue = fjesFATAL_ERROR Then g_ExStatusString = "Fatal error"
    If ExStatusValue = fjesHANDLED Then g_ExStatusString = "Handled"
    If ExStatusValue = fjesINITIALIZING Then g_ExStatusString = "Initializing"
    If ExStatusValue = fjesLINE_UNAVAILABLE Then g_ExStatusString = "Line unavailable"
    If ExStatusValue = fjesNO_ANSWER Then g_ExStatusString = "No answer"
    If ExStatusValue = fjesNO_DIAL_TONE Then g_ExStatusString = "No dial tone"
    If ExStatusValue = fjesNONE Then g_ExStatusString = "None"
    If ExStatusValue = fjesTRANSMITTING Then g_ExStatusString = "Transmitting"

    'Return True
    SetExStatusString = True
    
Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Function
Private Sub cmdClose_Click()
    Unload QMonitorForm
End Sub
