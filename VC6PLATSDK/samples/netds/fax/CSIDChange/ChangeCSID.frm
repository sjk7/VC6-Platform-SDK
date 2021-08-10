VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Begin VB.Form ConsoleForm 
   Caption         =   "Fax Device Administration"
   ClientHeight    =   6510
   ClientLeft      =   1305
   ClientTop       =   1305
   ClientWidth     =   7065
   LinkTopic       =   "Form1"
   ScaleHeight     =   6510
   ScaleWidth      =   7065
   Begin VB.Frame frameCsidTsid 
      Caption         =   "Assign a CSID or TSID"
      Height          =   2895
      Left            =   240
      TabIndex        =   6
      Top             =   2760
      Width           =   6615
      Begin VB.CommandButton cmdOK 
         Caption         =   "&OK"
         Height          =   375
         Left            =   5160
         TabIndex        =   13
         Top             =   2400
         Width           =   1095
      End
      Begin VB.TextBox TSIDText 
         Height          =   285
         Left            =   600
         TabIndex        =   12
         Top             =   2400
         Width           =   1935
      End
      Begin VB.TextBox CSIDText 
         Height          =   285
         Left            =   600
         TabIndex        =   11
         Top             =   2040
         Width           =   1935
      End
      Begin VB.OptionButton optAssign 
         Caption         =   "Assign to all devices"
         Height          =   195
         Index           =   0
         Left            =   240
         TabIndex        =   10
         Top             =   1680
         Width           =   2055
      End
      Begin VB.OptionButton optAssign 
         Caption         =   "Assign to selected device"
         Height          =   315
         Index           =   1
         Left            =   240
         TabIndex        =   9
         Top             =   1320
         Width           =   2295
      End
      Begin VB.Label lblCSIDInstructions3 
         Caption         =   "If you insert spaces using the space bar, a blank TSID or CSID will be assigned to the device(s)."
         Height          =   615
         Left            =   240
         TabIndex        =   16
         Top             =   840
         Width           =   6255
      End
      Begin VB.Label CSID_LABEL 
         Caption         =   "CSID"
         Height          =   375
         Left            =   120
         TabIndex        =   15
         Top             =   2040
         Width           =   495
      End
      Begin VB.Label TSID_LABEL 
         Caption         =   "TSID"
         Height          =   255
         Left            =   120
         TabIndex        =   14
         Top             =   2400
         Width           =   375
      End
      Begin VB.Label lblCSIDInstructions2 
         Caption         =   "If you leave a text field empty, that parameter will not be changed."
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   600
         Width           =   6015
      End
      Begin VB.Label lblCSIDInstructions1 
         Caption         =   "A CSID or TSID can contain up to 20 characters."
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   360
         Width           =   4455
      End
   End
   Begin VB.CommandButton cmdClose 
      Caption         =   "&Close"
      Height          =   375
      Left            =   5400
      TabIndex        =   5
      Top             =   5880
      Width           =   1095
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Connect"
      Height          =   375
      Left            =   5280
      TabIndex        =   4
      Top             =   480
      Width           =   975
   End
   Begin MSComctlLib.ListView DeviceListView 
      Height          =   1215
      Left            =   240
      TabIndex        =   3
      Top             =   1200
      Width           =   6615
      _ExtentX        =   11668
      _ExtentY        =   2143
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
         Text            =   "Device Name"
         Object.Width           =   3353
      EndProperty
      BeginProperty ColumnHeader(2) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   1
         Text            =   "Device ID"
         Object.Width           =   2118
      EndProperty
      BeginProperty ColumnHeader(3) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   2
         Text            =   "CSID"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(4) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   3
         Text            =   "TSID"
         Object.Width           =   2540
      EndProperty
      BeginProperty ColumnHeader(5) {BDD1F052-858B-11D1-B16A-00C0F0283628} 
         SubItemIndex    =   4
         Text            =   "Description"
         Object.Width           =   2540
      EndProperty
   End
   Begin VB.TextBox ServerNameText 
      Height          =   285
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Width           =   4815
   End
   Begin VB.Label lblConnectedDevices 
      Caption         =   "Connected Fax Devices"
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   960
      Width           =   3135
   End
   Begin VB.Label lblServerInstructions 
      Caption         =   "Type name of fax server (blank for local server), then press Connect"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   120
      Width           =   4815
   End
End
Attribute VB_Name = "ConsoleForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'Copyright (c) Microsoft Corporation.  All rights reserved.
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
'OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
'LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
'FITNESS FOR A  PARTICULAR PURPOSE

Dim objFaxServer As New FAXCOMEXLib.FaxServer
Dim objFaxDevices As FaxDevices
Dim objFaxDevice As FaxDevice
Dim lCount As Long
Dim TSID As String
Dim CSID As String
Dim FaxServerName As String

Private Sub Form_Load()
    
    'Disable controls until a server is connected
    DeviceListView.Enabled = False
    CSIDText.Enabled = False
    TSIDText.Enabled = False
    cmdOK.Enabled = False
        
    'Disable the option "Assign to all devices" until Connect is pressed
    optAssign.Item(0).Enabled = False
    
    'Disable the option "Assign to selected device" until device is selected
    optAssign.Item(1).Enabled = False
        
    'Set order for user to tab through controls
    ServerNameText.TabIndex = 1
    cmdConnect.TabIndex = 2
    DeviceListView.TabIndex = 3
    optAssign.Item(1).TabIndex = 4
    optAssign.Item(0).TabIndex = 5
    CSIDText.TabIndex = 6
    TSIDText.TabIndex = 7
    cmdOK.TabIndex = 8

    
End Sub

Private Function DeviceListView_Init() As Boolean
 
    'Initialize the function to return false
    DeviceListView_Init = False
    
    'Error handling
    On Error GoTo Error_Handler
    
    'Set the list view properties
    DeviceListView.HideSelection = False
    DeviceListView.FullRowSelect = True
    
    Dim ItmAdd As ListItem
     
    'Clear the list
    DeviceListView.ListItems.Clear
            
    ' Connect to the fax server
    ' "" defaults to the server on which the script is running.
    objFaxServer.Connect FaxServerName
    
    
    'Get the collection of devices
    Set objFaxDevices = objFaxServer.GetDevices()
    
    'Get the number of devices in the collection
    lCount = objFaxDevices.Count()
    
    'Add the devices to the list
    For n = 1 To lCount
        
        Set ItmAdd = DeviceListView.ListItems.Add()
        Set objFaxDevice = objFaxDevices.Item(n)
        
        ItmAdd.Text = objFaxDevice.DeviceName
        ItmAdd.SubItems(1) = objFaxDevice.Id
        ItmAdd.SubItems(2) = objFaxDevice.CSID
        ItmAdd.SubItems(3) = objFaxDevice.TSID
        ItmAdd.SubItems(4) = objFaxDevice.Description
        ItmAdd.Selected = False
        
    Next

    'Return True if the function has succeeded
    DeviceListView_Init = True
    
Exit Function
    
Error_Handler:
    'Display error information
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
    'Disable controls
    DeviceListView.Enabled = False
    CSIDText.Enabled = False
    TSIDText.Enabled = False
    cmdOK.Enabled = False
    optAssign.Item(0).Enabled = False
    optAssign.Item(1).Enabled = False

End Function

Private Sub DeviceListView_ColumnClick(ByVal ColumnHeader As ColumnHeader)
'This subroutine allows sorting when the user clicks on a column heading
    
    DeviceListView.SortKey = (ColumnHeader.Index - 1)
    DeviceListView.Sorted = True
    
    If DeviceListView.SortOrder = lvwAscending Then
        DeviceListView.SortOrder = lvwDescending
    Else
        DeviceListView.SortOrder = lvwAscending
    End If

End Sub

Private Sub ServerNameText_KeyPress(KeyAscii As Integer)
                  
     'Disable controls so that user can't proceed without pressing Connect
     DeviceListView.Enabled = False
     CSIDText.Enabled = False
     TSIDText.Enabled = False
     
     'Disable OK button (will be enabled when CSID or TSID is entered)
     cmdOK.Enabled = False
        
    'Disable the option "Assign to selected device" until device is selected
     optAssign.Item(1).Enabled = False
    
    'Disable the option "Assign to all devices" until Connect is pressed
     optAssign.Item(0).Enabled = False
       
    'Checks if Enter key has been pressed
    If KeyAscii = 13 Then
        'Call the subroutine that is associated with the Connect button
        Call cmdConnect_Click
        'Stop the beep that you usually get when you press Enter
        KeyAscii = 0
    End If
    
End Sub

Private Sub cmdConnect_Click()

    'Set the server name to the value in the text box
     FaxServerName = ServerNameText.Text
     
    'Call the function that lists the devices for that server
    If Not DeviceListView_Init() Then
        Exit Sub
    End If
            
    'Re-enable all of the controls that were disabled
    DeviceListView.Enabled = True
    CSIDText.Enabled = True
    TSIDText.Enabled = True
    optAssign.Item(0).Enabled = True
     
    'Set the option to "All devices"
    optAssign.Item(0).Value = True
   
End Sub

Private Sub DeviceListView_Click()
    
    'When a user selects a device, the "Assign to selected device"
    'option is enabled and selected
    optAssign.Item(1).Enabled = True
    optAssign.Item(1).Value = True
    
    'Set focus to CSID text box
    CSIDText.SetFocus
        
End Sub

Private Sub CSIDText_Change()
    
    'Set the OK button to the default condition if a user types in the text box
    If CSIDText.DataChanged = True Then cmdOK.Default = True
    
    'Restrict the CSID to 20 characters
    CSIDText.MaxLength = 20
    
    'Enable the OK button
    cmdOK.Enabled = True

End Sub

Private Sub TSIDText_Change()
    
    'Set the OK button to the default condition if a user types in the text box
    If TSIDText.DataChanged = True Then cmdOK.Default = True
    
    'Restrict the TSID to 20 characters
    TSIDText.MaxLength = 20
    
    'Enable the OK button
    cmdOK.Enabled = True
    
End Sub

Private Sub cmdOK_Click()
    
    'Error handling
    On Error GoTo Error_Handler
    
    'Calls the subroutine that sets TSID/CSID for a single device, if that option is selected
    If optAssign.Item(1).Value = True Then
        If Not AssignDeviceCsidTsid() Then
            Exit Sub
        End If
    End If
    
    'Calls the subroutine that sets TSID/CSID for all devices, if that option is selected
    If optAssign.Item(0).Value = True Then
        If Not AssignAll() Then
            Exit Sub
        End If
    End If
    
    'Refresh the list view by calling the DeviceListView function
    If Not DeviceListView_Init() Then
        Exit Sub
    End If
        
    'Clear the CSID and TSID text boxes
    CSIDText.Text = ""
    TSIDText.Text = ""
    
    'Set the default option to "Assign to all devices"
    optAssign.Item(0).Value = True
    
    'Disable the option "Assign to selected device" until device is selected
    optAssign.Item(1).Enabled = False
    
Exit Sub

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Sub

Private Function AssignDeviceCsidTsid() As Boolean
    'Assigns the TSID/CSID to a single device
    
    'Initialize the function to return false
    AssignDeviceCsidTsid = False
    
    'Error handling
    On Error GoTo Error_Handler
    
    'Get the collection of devices
    Set objFaxDevices = objFaxServer.GetDevices()
        
    For n = 1 To DeviceListView.ListItems.Count
        
        If DeviceListView.ListItems.Item(n).Selected = True Then
        
            'Get the fax device
            Set objFaxDevice = objFaxDevices.Item(n)
            
            'Set the TSID/CSID, if the text field is not empty
            'If the text field is empty, no change will be made
            If CSIDText.Text <> "" Then objFaxDevice.CSID = CSIDText.Text
            If TSIDText.Text <> "" Then objFaxDevice.TSID = TSIDText.Text
            
            'Save the changes
            objFaxDevice.Save
            
        End If
    
    Next
    
    'List the devices with the new information
    If Not DeviceListView_Init() Then
        Exit Function
    End If
    
    'Return True
    AssignDeviceCsidTsid = True

Exit Function

Error_Handler:
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear

End Function

Private Function AssignAll() As Boolean

    'Assigns the TSID/CSID to all of the devices for the selected server
    
    'Initialize the function to return false
    AssignAll = False
    
    'Error handling
    On Error GoTo Error_Handler

    'Get the collection of devices
    Set objFaxDevices = objFaxServer.GetDevices()
    
    'Get the number of fax devices
    lCount = objFaxDevices.Count()
    
    For n = 1 To lCount
       
       'Get device "n"
       Set objFaxDevice = objFaxDevices.Item(n)
        
       'The following lines assign the new CSID and TSID.
       'If the TSID or CSID field is left blank by the user,
       'the value of the property is not changed.
       If CSIDText.Text <> "" Then objFaxDevice.CSID = CSIDText.Text
       If TSIDText.Text <> "" Then objFaxDevice.TSID = TSIDText.Text
       
       'Save the changes
       objFaxDevice.Save
       
    Next
    
    'List the devices with the new information
    If Not DeviceListView_Init() Then
        Exit Function
    End If

Exit Function

Error_Handler:
      MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
      Err.Clear

End Function

Private Sub cmdClose_Click()
    
    Unload ConsoleForm
    
End Sub
