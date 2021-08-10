VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form BroadcastInfoForm 
   Caption         =   "List of faxes"
   ClientHeight    =   3615
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6960
   LinkTopic       =   "Form2"
   ScaleHeight     =   3615
   ScaleWidth      =   6960
   StartUpPosition =   3  'Windows Default
   Begin MSComctlLib.ListView BCastListView 
      Height          =   2535
      Left            =   240
      TabIndex        =   3
      Top             =   360
      Width           =   6615
      _ExtentX        =   11668
      _ExtentY        =   4471
      View            =   3
      LabelEdit       =   1
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   393217
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      NumItems        =   5
      BeginProperty ColumnHeader(1) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         Text            =   "Subject"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Sender"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "Recipient"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "Submission ID"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   4
         Text            =   "Status"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.CommandButton cmdBCastClose 
      Caption         =   "Close"
      Height          =   375
      Left            =   4560
      TabIndex        =   2
      Top             =   3120
      Width           =   1095
   End
   Begin VB.TextBox BCastNumberFaxes 
      Height          =   375
      Left            =   2640
      TabIndex        =   1
      Top             =   3120
      Width           =   735
   End
   Begin VB.Label lblNumbFaxesInBroadcast 
      Caption         =   "Number of faxes in group"
      Height          =   255
      Left            =   360
      TabIndex        =   0
      Top             =   3240
      Width           =   2295
   End
End
Attribute VB_Name = "BroadcastInfoForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Copyright (c) Microsoft Corporation.  All rights reserved.
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
'OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
'LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
'FITNESS FOR A  PARTICULAR PURPOSE

'ListCount counts the number of faxes in the broadcast
Dim ListCount As Integer
Private Sub Form_Load()

    BroadcastInfoForm.Show
    ListCount = 0
    
    If Not BcastListView_Init() Then
        Exit Sub
    End If

End Sub

Private Function BcastListView_Init() As Boolean

    'Initialize the function to return false
    BcastListView_Init = False
    
    'Error handling
    On Error GoTo Error_Handler
        
    Dim ItmAdd As ListItem
            
    'Clear the list
    BCastListView.ListItems.Clear
    
    'Set focus to Close button
    cmdBCastClose.SetFocus
        
    'Get the jobs collection
    Set objFaxJobs = objFaxServer.Folders.OutgoingQueue.GetJobs
    
    'Get the number of faxes in the collection
    lcount = objFaxJobs.Count()
        
    'List faxes by broadcast (submission ID)
    If CancelFaxForm.CancelBroadcast.Value = True Then
    
        For n = 1 To lcount
        
            'Get the fax job object
            Set objFaxJob = objFaxJobs.Item(n)
            
            'Test if fax is part of this broadcast, if so, add to list
            If objFaxJob.SubmissionId = SubmId Then
                If Not ListAdd() Then
                    Exit Function
                End If
            End If
        
        Next n
    
    End If
    
    'List faxes by sender
    If CancelFaxForm.CancelBySender.Value = True Then
    
        For n = 1 To lcount
        
            'Get the fax job object
            Set objFaxJob = objFaxJobs.Item(n)
            
            'Test if fax has the specified sender, if so, add to list
            If objFaxJob.Sender.Name = Sender Then
                If Not ListAdd() Then
                    Exit Function
                End If
            End If
        Next n
    
    End If
    
    'List faxes by subject
    If CancelFaxForm.CancelBySubject.Value = True Then
    
        For n = 1 To lcount
        
            'Get the fax job object
            Set objFaxJob = objFaxJobs.Item(n)
            
            'Test if fax has the specified subject, if so, add to list
            If objFaxJob.Subject = Subject Then
                If Not ListAdd() Then
                    Exit Function
                End If
            End If
        
        Next n
    
    End If
    
    'Display number of faxes in the group of faxes
    BCastNumberFaxes.Text = ListCount
    
    'Return true
    BcastListView_Init = True
    
    Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Function

Private Sub BCastListView_ColumnClick(ByVal ColumnHeader As ColumnHeader)
'This subroutine allows sorting when the user clicks on a column heading
    
    BCastListView.SortKey = (ColumnHeader.Index - 1)
    BCastListView.Sorted = True
    If BCastListView.SortOrder = lvwAscending Then
        BCastListView.SortOrder = lvwDescending
    Else
        BCastListView.SortOrder = lvwAscending
    End If

End Sub


Private Sub cmdBCastClose_Click()
    
    Unload BroadcastInfoForm

End Sub

Private Function ListAdd() As Boolean
    
    'Initialize the function to return false
    ListAdd = False
    
    'Error handling
    On Error GoTo Error_Handler

    Set ItmAdd = BCastListView.ListItems.Add()

    ListCount = ListCount + 1

    'Call the subroutine that converts the numerical status to a string
    Call SetStatusString

    'Add the fax to the list view
    ItmAdd.Text = objFaxJob.Subject
    ItmAdd.SubItems(1) = objFaxJob.Sender.Name
    ItmAdd.SubItems(2) = objFaxJob.Recipient.Name
    ItmAdd.SubItems(3) = objFaxJob.SubmissionId
    ItmAdd.SubItems(4) = StatusString
        
    'Return true
    ListAdd = True
    
    Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Function

                
