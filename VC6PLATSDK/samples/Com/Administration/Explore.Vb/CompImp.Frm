VERSION 5.00
Begin VB.Form CompImport 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Import Component"
   ClientHeight    =   3135
   ClientLeft      =   4275
   ClientTop       =   2460
   ClientWidth     =   4215
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   Icon            =   "CompImp.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3135
   ScaleWidth      =   4215
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox txtComponent 
      Height          =   315
      Left            =   120
      TabIndex        =   6
      Top             =   2160
      Width           =   3975
   End
   Begin VB.Frame fraImportOptions 
      Caption         =   "Import By"
      Height          =   1095
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   3975
      Begin VB.OptionButton optImportType 
         Caption         =   "ProgID"
         Height          =   195
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Value           =   -1  'True
         Width           =   975
      End
      Begin VB.OptionButton optImportType 
         Caption         =   "CLSID"
         Height          =   195
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   855
      End
   End
   Begin VB.ComboBox cboApps 
      Height          =   330
      Left            =   120
      Sorted          =   -1  'True
      Style           =   2  'Dropdown List
      TabIndex        =   4
      Top             =   1560
      Width           =   3975
   End
   Begin VB.CommandButton cmdMaint 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Index           =   0
      Left            =   600
      TabIndex        =   7
      Top             =   2640
      Width           =   1215
   End
   Begin VB.CommandButton cmdMaint 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Index           =   1
      Left            =   2280
      TabIndex        =   8
      Top             =   2640
      Width           =   1215
   End
   Begin VB.Label lblIDDesc 
      Caption         =   "ProgID:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   1920
      Width           =   3975
   End
   Begin VB.Label lblAppDesc 
      Caption         =   "Application:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   1320
      Width           =   3975
   End
End
Attribute VB_Name = "CompImport"
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

    Private Const kcmdOK        As Integer = 0
    Private Const kcmdCancel    As Integer = 1
    
    Private Const koptProgID    As Integer = 0
    Private Const koptCLSID     As Integer = 1

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

Private Sub cmdMaint_Click(Index As Integer)

    On Error GoTo cmdMaintErr:
    
    Select Case Index
        Case kcmdOK
            'Attempt to import the component
            With cboApps
                Explorer.g_Catalog.ImportComponent .List(.ListIndex), Trim$(txtComponent.Text)
            End With
        Case kcmdCancel
            'do nothing
    End Select
    
cmdMaintBail:
    Unload Me
    Exit Sub
    
cmdMaintErr:
    If Not ErrHandler(Err.Number, Err.Description, "CompImport::cmdMaint_Click") Then
        GoTo cmdMaintBail:
    Else
        Resume Next
    End If
    
End Sub

Private Sub Form_Load()

    'Center this form over it's parent
    With Explorer
        CenterObject Me, CStr(.top) & ";" & CStr(.left) & ";" & CStr(.left + .Width) & ";" & CStr(.top + .Height)
    End With
    
    'Build a list of available applications
    LoadAppComboBox
    
    Exit Sub
    
End Sub

Private Sub optImportType_Click(Index As Integer)

    'Set the description depending on what type of component ID that is going
    '   to be used to install the application
    Select Case Index
        Case koptProgID
            lblIDDesc.Caption = "ProgID:"
        Case koptCLSID
            lblIDDesc.Caption = "CLSID:"
    End Select
    
    Exit Sub
    
End Sub

Private Sub txtComponent_GotFocus()

    'Select the currently displayed text
    SelectText txtComponent
    
    Exit Sub

End Sub
