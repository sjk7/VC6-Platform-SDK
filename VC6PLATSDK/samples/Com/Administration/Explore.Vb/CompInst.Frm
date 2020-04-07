VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form CompInstall 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Install Component"
   ClientHeight    =   3135
   ClientLeft      =   4815
   ClientTop       =   1950
   ClientWidth     =   4695
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "CompInst.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3135
   ScaleWidth      =   4695
   ShowInTaskbar   =   0   'False
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Height          =   315
      Index           =   0
      Left            =   4200
      TabIndex        =   4
      Top             =   840
      Width           =   375
   End
   Begin VB.TextBox txtComponent 
      Height          =   315
      Left            =   120
      TabIndex        =   3
      Top             =   840
      Width           =   3975
   End
   Begin VB.ComboBox cboApps 
      Height          =   330
      Left            =   120
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   240
      Width           =   4455
   End
   Begin VB.TextBox txtProxyStub 
      Height          =   315
      Left            =   120
      TabIndex        =   9
      Top             =   2040
      Width           =   3975
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Height          =   315
      Index           =   2
      Left            =   4200
      TabIndex        =   10
      Top             =   2040
      Width           =   375
   End
   Begin VB.CommandButton cmdBrowse 
      Caption         =   "..."
      Height          =   315
      Index           =   1
      Left            =   4200
      TabIndex        =   7
      Top             =   1440
      Width           =   375
   End
   Begin VB.TextBox txtTypeLib 
      Height          =   315
      Left            =   120
      TabIndex        =   6
      Top             =   1440
      Width           =   3975
   End
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2760
      TabIndex        =   12
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Height          =   375
      Index           =   0
      Left            =   720
      TabIndex        =   11
      Top             =   2640
      Width           =   1215
   End
   Begin MSComDlg.CommonDialog cmdlgBrowse 
      Left            =   2280
      Top             =   480
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
   End
   Begin VB.Label lblAppDesc 
      Caption         =   "Application:"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   3975
   End
   Begin VB.Label lblProxyStubDesc 
      Caption         =   "Proxy/Stub DLL (optional):"
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1800
      Width           =   3975
   End
   Begin VB.Label lblTypeLibDesc 
      Caption         =   "Type Library (optional):"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1200
      Width           =   3975
   End
   Begin VB.Label lblComponentDesc 
      Caption         =   "Component:"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   3975
   End
End
Attribute VB_Name = "CompInstall"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ----------------------------------------------------------------------------
' 
' This file is part of the Microsoft COM+ Samples.
' 
' Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
' 
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation. See these other
' materials for detailed information regarding Microsoft code samples.
' 
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
' 
' ----------------------------------------------------------------------------

Option Explicit

    Private Const kcmdOK                As Integer = 0
    Private Const kcmdCancel            As Integer = 1
    
    Private Const kcmdBrowseComponent   As Integer = 0
    Private Const kcmdBrowseTypeLib     As Integer = 1
    Private Const kcmdBrowseProxyStub   As Integer = 2

Private Sub LoadAppComboBox()

    Dim oApplications   As Object
    Dim oApp            As Object
    Dim oComponents     As Object
    
    'Clear the applications combobox
    cboApps.Clear
    
    'Get a reference to the current collections application collection
    Set oApplications = Explorer.g_Catalog.GetCollection("Applications")
    oApplications.Populate
    
    'Continue only if we have a valid reference
    If Not oApplications Is Nothing Then
        'Enable the applications combobox and set active backcolor
        With cboApps
            .Enabled = True
            .BackColor = &H80000005
        End With
        'Load each application into the combobox
        For Each oApp In oApplications
            cboApps.AddItem oApp.Name
        Next
        'Set the initial application selection (note, this will cause the component combo to be loaded)
        If (0 < cboApps.ListCount) Then
            cboApps.ListIndex = 0
            'Make sure the OK button is enabled
            cmdMaint(kcmdOK).Enabled = True
        Else
            'No applications available, disable the applications combobox control
            With cboApps
                .Enabled = False
                .BackColor = &H80000000
            End With
            'Disable the OK button (i.e., nothing to do)
            cmdMaint(kcmdOK).Enabled = False
        End If
    Else
        'Cannot get a reference to the Applications collection.  Disable the applications
        '   combobox and set inactive backcolor
        With cboApps
            .Enabled = False
            .BackColor = &H80000000
        End With
        'Disable the OK button (i.e., nothing to do)
        cmdMaint(kcmdOK).Enabled = False
    End If
    
    Exit Sub
    
End Sub

Private Sub cmdBrowse_Click(Index As Integer)

    On Error GoTo cmdBrowseErr:
    
    Dim sTitle          As String
    
    'Set the dialogs title depending on which browse button has been selected
    Select Case Index
        Case kcmdBrowseComponent
            sTitle = "Select Component To Install"
        Case kcmdBrowseTypeLib
            sTitle = "Select TypeLib To Install"
        Case kcmdBrowseProxyStub
            sTitle = "Select Proxy/Stub To Install"
    End Select
    
    'Prompt the user for the specified file and update the associated text box
    With cmdlgBrowse
        .CancelError = False
        .Flags = cdlOFNHideReadOnly
        .Filter = "All Files (*.*) | *.*"
        .DialogTitle = sTitle
        .filename = ""
        .FilterIndex = 1
        .ShowOpen
        Select Case Index
            Case kcmdBrowseComponent
                txtComponent.Text = Trim$(.filename)
            Case kcmdBrowseTypeLib
                txtTypeLib.Text = Trim$(.filename)
            Case kcmdBrowseProxyStub
                txtProxyStub.Text = Trim$(.filename)
        End Select
    End With
    
cmdBrowseBail:
    Exit Sub
    
cmdBrowseErr:
    If Not ErrHandler(Err.Number, Err.Description, "CompInstall::cmdBrowse_Click") Then
        GoTo cmdBrowseBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub cmdMaint_Click(Index As Integer)

    On Error GoTo cmdMaintErr:
    
    Select Case Index
        Case kcmdOK
            'Attempt to install the specified component
            Explorer.g_Catalog.InstallComponent cboApps.List(cboApps.ListIndex), Trim$(txtComponent.Text), Trim$(txtTypeLib.Text), Trim$(txtProxyStub.Text)
        Case kcmdCancel
            'do nothing
    End Select
    
cmdMaintBail:
    Unload Me
    Exit Sub
    
cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "CompInstall::cmdMaint_Click") Then
        GoTo cmdMaintBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub Form_Load()

    'Center the form over it's parent
    With Explorer
        CenterObject Me, CStr(.top) & ";" & CStr(.left) & ";" & CStr(.left + .Width) & ";" & CStr(.top + .Height)
    End With
    
    'Build a list of available applications
    LoadAppComboBox
    
    Exit Sub
    
End Sub

Private Sub txtComponent_GotFocus()
    
    'Select the currently displayed text
    SelectText txtComponent
    
    Exit Sub
    
End Sub

Private Sub txtProxyStub_GotFocus()

    'Select the currently displayed text
    SelectText txtProxyStub
    
    Exit Sub
    
End Sub

Private Sub txtTypeLib_GotFocus()

    'Select the currently displayed text
    SelectText txtTypeLib
    
    Exit Sub
    
End Sub
