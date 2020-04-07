VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form Explorer 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "COM+ Admin SDK Sample (VB)"
   ClientHeight    =   5820
   ClientLeft      =   2085
   ClientTop       =   2055
   ClientWidth     =   8115
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   9
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5820
   ScaleWidth      =   8115
   Begin ComctlLib.Toolbar tbrExplorer 
      Align           =   1  'Align Top
      Height          =   420
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   8115
      _ExtentX        =   14314
      _ExtentY        =   741
      ButtonWidth     =   609
      ButtonHeight    =   582
      Appearance      =   1
      ImageList       =   "imgTBImages"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   19
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Connect"
            Description     =   "Connect"
            Object.ToolTipText     =   "Connect"
            Object.Tag             =   "Connect"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Sep1"
            Description     =   "Sep1"
            Object.Tag             =   "Sep1"
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Refresh"
            Description     =   "Refresh the current collection"
            Object.ToolTipText     =   "Refresh"
            Object.Tag             =   "Refresh"
            ImageIndex      =   11
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Sep2"
            Description     =   "Sep2"
            Object.Tag             =   "Sep2"
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Add"
            Description     =   "Add"
            Object.ToolTipText     =   "Add"
            Object.Tag             =   "Add"
            ImageIndex      =   16
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "SaveChanges"
            Description     =   "Save Changes"
            Object.ToolTipText     =   "Save Changes"
            Object.Tag             =   "SaveChanges"
            ImageIndex      =   15
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Remove"
            Description     =   "Remove"
            Object.ToolTipText     =   "Remove"
            Object.Tag             =   "Remove"
            ImageIndex      =   14
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Sep3"
            Description     =   "Sep3"
            Object.Tag             =   "Sep3"
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button9 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "StartApp"
            Description     =   "Start App"
            Object.ToolTipText     =   "Start Application"
            Object.Tag             =   "StartApp"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button10 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "StopApp"
            Description     =   "Stop Application"
            Object.ToolTipText     =   "Stop Application"
            Object.Tag             =   "StopApp"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button11 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "InstallApp"
            Description     =   "Install Application"
            Object.ToolTipText     =   "Install Application"
            Object.Tag             =   "InstallApp"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button12 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ExportApp"
            Description     =   "Export Application"
            Object.ToolTipText     =   "Export Application"
            Object.Tag             =   "ExportApp"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button13 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Sep4"
            Description     =   "Sep4"
            Object.Tag             =   "Sep4"
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button14 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "InstallComp"
            Description     =   "Install Component"
            Object.ToolTipText     =   "Install Component"
            Object.Tag             =   "InstallComp"
            ImageIndex      =   12
         EndProperty
         BeginProperty Button15 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "ImportComp"
            Description     =   "Import Component"
            Object.ToolTipText     =   "Import Component"
            Object.Tag             =   "ImportComp"
            ImageIndex      =   6
         EndProperty
         BeginProperty Button16 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Sep5"
            Description     =   "Sep5"
            Object.Tag             =   "Sep5"
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button17 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Utilities"
            Description     =   "Utilities"
            Object.ToolTipText     =   "Utilities"
            Object.Tag             =   "Utilities"
            ImageIndex      =   17
         EndProperty
         BeginProperty Button18 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Sep7"
            Description     =   "Sep7"
            Object.Tag             =   "Sep7"
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button19 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "About"
            Description     =   "About"
            Object.ToolTipText     =   "About"
            Object.Tag             =   "About"
            ImageIndex      =   10
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin VB.Frame fraPreviousCollections 
      Caption         =   "Previous Collections"
      Height          =   1335
      Left            =   0
      TabIndex        =   8
      Top             =   4080
      Width           =   3255
      Begin VB.ListBox lbParentCollections 
         Height          =   900
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   3015
      End
   End
   Begin ComctlLib.StatusBar sbrStatus 
      Align           =   2  'Align Bottom
      Height          =   375
      Left            =   0
      TabIndex        =   18
      Top             =   5445
      Width           =   8115
      _ExtentX        =   14314
      _ExtentY        =   661
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   4
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   10909
            MinWidth        =   8819
            Key             =   "Status"
            Object.Tag             =   "Status"
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   1
            Alignment       =   1
            AutoSize        =   2
            Enabled         =   0   'False
            Object.Width           =   979
            MinWidth        =   176
            TextSave        =   "CAPS"
            Key             =   "Caps"
            Object.Tag             =   "Caps"
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   2
            Alignment       =   1
            AutoSize        =   2
            Enabled         =   0   'False
            Object.Width           =   873
            MinWidth        =   176
            TextSave        =   "NUM"
            Key             =   "Num"
            Object.Tag             =   "Num"
         EndProperty
         BeginProperty Panel4 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   5
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   1429
            MinWidth        =   176
            TextSave        =   "9:48 AM"
            Key             =   "Time"
            Object.Tag             =   "Time"
         EndProperty
      EndProperty
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Tahoma"
         Size            =   9
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Frame fraCollections 
      Caption         =   "Related Collections"
      Height          =   1935
      Left            =   0
      TabIndex        =   6
      Top             =   2040
      Width           =   3315
      Begin VB.ListBox lbRelatedCollections 
         Height          =   1530
         Left            =   120
         TabIndex        =   7
         Top             =   240
         Width           =   3060
      End
   End
   Begin VB.Frame fraObjects 
      Caption         =   "Objects && Property Information"
      Height          =   4935
      Left            =   3360
      TabIndex        =   10
      Top             =   480
      Width           =   4750
      Begin VB.CommandButton cmdSetProperty 
         Caption         =   "Set"
         Height          =   315
         Left            =   3240
         TabIndex        =   17
         Top             =   4440
         Width           =   1375
      End
      Begin VB.TextBox txtPropValue 
         Height          =   315
         Left            =   120
         TabIndex        =   16
         Top             =   4440
         Width           =   3015
      End
      Begin VB.ListBox lbProperties 
         Height          =   3630
         Left            =   2400
         TabIndex        =   14
         Top             =   480
         Width           =   2200
      End
      Begin VB.ListBox lbObjects 
         Height          =   3630
         Left            =   120
         TabIndex        =   12
         Top             =   480
         Width           =   2205
      End
      Begin VB.Label lblPropValue 
         Caption         =   "Property value:"
         Height          =   255
         Left            =   120
         TabIndex        =   15
         Top             =   4200
         Width           =   2295
      End
      Begin VB.Label lblProperties 
         Caption         =   "Properties:"
         Height          =   255
         Left            =   2400
         TabIndex        =   13
         Top             =   240
         Width           =   1335
      End
      Begin VB.Label lblObjects 
         Caption         =   "Objects:"
         Height          =   255
         Left            =   120
         TabIndex        =   11
         Top             =   240
         Width           =   2055
      End
   End
   Begin VB.Frame fraCatalog 
      Caption         =   "Catalog Information"
      Height          =   1455
      Left            =   0
      TabIndex        =   1
      Top             =   480
      Width           =   3315
      Begin VB.Label lblCurrCollectionName 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   285
         Left            =   120
         TabIndex        =   5
         Top             =   1080
         Width           =   3060
      End
      Begin VB.Label lblCurrCollectionDesc 
         Caption         =   "Current Collection:"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   840
         Width           =   1695
      End
      Begin VB.Label lblComputerDesc 
         Caption         =   "Computer Name:"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   240
         Width           =   1815
      End
      Begin VB.Label lblServerName 
         Alignment       =   2  'Center
         BorderStyle     =   1  'Fixed Single
         Height          =   285
         Left            =   120
         TabIndex        =   3
         Top             =   480
         Width           =   3060
      End
   End
   Begin ComctlLib.ImageList imgTBImages 
      Left            =   3000
      Top             =   480
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   17
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":0000
            Key             =   "Connect"
            Object.Tag             =   "Connect"
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":031A
            Key             =   "Start"
            Object.Tag             =   "Start"
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":0634
            Key             =   "Stop"
            Object.Tag             =   "Stop"
         EndProperty
         BeginProperty ListImage4 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":094E
            Key             =   "Create"
            Object.Tag             =   "Create"
         EndProperty
         BeginProperty ListImage5 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":0C68
            Key             =   "Install"
            Object.Tag             =   "Install"
         EndProperty
         BeginProperty ListImage6 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":0F82
            Key             =   "Import"
            Object.Tag             =   "Import"
         EndProperty
         BeginProperty ListImage7 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":129C
            Key             =   "Export"
            Object.Tag             =   "Export"
         EndProperty
         BeginProperty ListImage8 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":15B6
            Key             =   "Roles"
            Object.Tag             =   "Roles"
         EndProperty
         BeginProperty ListImage9 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":18D0
            Key             =   "CreateQComp"
            Object.Tag             =   "CreateQComp"
         EndProperty
         BeginProperty ListImage10 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":1BEA
            Key             =   "About"
            Object.Tag             =   "About"
         EndProperty
         BeginProperty ListImage11 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":1F04
            Key             =   "Refresh"
            Object.Tag             =   "Refresh"
         EndProperty
         BeginProperty ListImage12 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":221E
            Key             =   "NavigateTo"
            Object.Tag             =   "NavigateTo"
         EndProperty
         BeginProperty ListImage13 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":2538
            Key             =   "Back"
            Object.Tag             =   "Back"
         EndProperty
         BeginProperty ListImage14 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":2852
            Key             =   "Delete"
            Object.Tag             =   "Delete"
         EndProperty
         BeginProperty ListImage15 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":2B6C
            Key             =   "Save"
            Object.Tag             =   "Save"
         EndProperty
         BeginProperty ListImage16 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":2E86
            Key             =   "New"
            Object.Tag             =   "New"
         EndProperty
         BeginProperty ListImage17 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Explorer.frx":31A0
            Key             =   "RouterUtil"
            Object.Tag             =   "RouterUtil"
         EndProperty
      EndProperty
   End
End
Attribute VB_Name = "Explorer"
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
    
    Private Const kItemNotSelected  As Integer = -1
    
    'Toolbar button index constants
    Private Const ktbConnect        As Integer = 1
    Private Const ktbSep1           As Integer = 2
    Private Const ktbRefresh        As Integer = 3
    Private Const ktbSep2           As Integer = 4
    Private Const ktbAdd            As Integer = 5
    Private Const ktbSaveChanges    As Integer = 6
    Private Const ktbRemove         As Integer = 7
    Private Const kbtSep3           As Integer = 8
    Private Const ktbStartApp       As Integer = 9
    Private Const ktbStopApp        As Integer = 10
    Private Const ktbInstallApp     As Integer = 11
    Private Const ktbExportApp      As Integer = 12
    Private Const ktbSep4           As Integer = 13
    Private Const ktbInstallComp    As Integer = 14
    Private Const ktbImportComp     As Integer = 15
    Private Const ktbSep5           As Integer = 16
    Private Const ktbUtility        As Integer = 17
    Private Const ktbSep7           As Integer = 18
    Private Const ktbAbout          As Integer = 19
    
    Public g_Catalog                As Object
    Public g_CurrCollection         As Object
    Public g_ErrorInfo              As Integer
    

Private Function CheckDirty() As Boolean
    
    Dim iSaveChoice As Integer
    
    'Default return value
    CheckDirty = False
    
    'Prompt the user only if the "Save Changes" toolbar button has been enabled
    If tbrExplorer.Buttons(ktbSaveChanges).Enabled Then
        'Prompt the user
        iSaveChoice = MsgBox("Do you wish to save changes before continuing?", (vbYesNoCancel + vbExclamation), "Save Changes?")
        'Execute users selection
        Select Case iSaveChoice
            Case vbYes, vbNo
                'Set return value
                CheckDirty = True
                'Save the changes (if needed)
                With tbrExplorer
                    'Toggle "Save Changes" toolbar button to prevent recursive call
                    .Buttons(ktbSaveChanges).Enabled = False
                    If (vbYes = iSaveChoice) Then
                        tbrExplorer_ButtonClick .Buttons(ktbSaveChanges)
                    End If
                End With
            Case vbCancel
                'do nothing
        End Select
    Else
        'Nothing is dirty, set value to indicate to caller to continue with processing
        CheckDirty = True
    End If
    
    Exit Function
    
End Function

Private Sub ToggleUtilityBtn(NewState As Boolean)

    'Set the new state for the Utility toolbar button
    tbrExplorer.Buttons(ktbUtility).Enabled = NewState
    
    Exit Sub
    
End Sub

Private Sub ToggleConnectBtns(NewState As Boolean)

    'Set the new state for the Connect toolbar button
    tbrExplorer.Buttons(ktbConnect).Enabled = NewState
    
    Exit Sub
    
End Sub

Private Sub InitPersistanceBtns()

    Dim iCtr As Integer
    
    'Initialize the state of the Persistance (i.e., Add/Save/Remove) toolbar buttons
    For iCtr = ktbAdd To ktbRemove
        tbrExplorer.Buttons(iCtr).Enabled = False
    Next
    
    Exit Sub
    
End Sub

Private Sub InitRefreshBtn()
    
    'Initialize the state of the Refresh toolbar button
    tbrExplorer.Buttons(ktbRefresh).Enabled = True
    
    Exit Sub
    
End Sub

Private Sub ToggleAppBtns(NewState As Boolean)

    Dim iCtr As Integer
    
    'Set the new state for the Applications toolbar buttons
    For iCtr = ktbStartApp To ktbExportApp
        tbrExplorer.Buttons(iCtr).Enabled = NewState
    Next

    Exit Sub
    
End Sub

Private Sub ToggleComponentBtns(NewState As Boolean)

    Dim iCtr As Integer
    
    'Set the new state for the Components toolbar buttons
    For iCtr = ktbInstallComp To ktbImportComp
        tbrExplorer.Buttons(iCtr).Enabled = NewState
    Next

    Exit Sub
    
End Sub

Private Sub InitToolbarState()

    'Enable connect since we are on the root
    ToggleConnectBtns True
    'Initialize the navigation buttons
    InitRefreshBtn
    'Initialize the persistence buttons
    InitPersistanceBtns
    'Enable "root" based actions (i.e., these are always available)
    ToggleAppBtns True
    ToggleComponentBtns True
    ToggleUtilityBtn True
    
    Exit Sub
    
End Sub

Private Function CreateCatalog() As Boolean

    'Default return value
    CreateCatalog = False
    
    'Attempt to get a reference to the COM+ Admin catalog
    Set g_Catalog = CreateObject("COMAdmin.COMAdminCatalog.1")
    
    'Initialize the stack used to navigate the collection hierarchy
    InitStack
    
    'Set the current collection to the "Root"
    Set g_CurrCollection = g_Catalog.GetCollection("Root")
    
    'Push new current collection onto the stack
    Push g_CurrCollection
    
    'Enumerate the current collections 1) objects, 2) object properties, and 3) related collection information
    NavigateTo g_CurrCollection

    'Success return value
    CreateCatalog = True
    
    Exit Function
    
End Function

Public Sub NavigateTo(CurrCollection As Object)

    On Error GoTo NTErr:
    
    Dim RelatedCollections  As Object
    Dim ObjectProperties    As Object
    Dim ObjWork             As Object
    Dim RelatedObj          As Integer
    
    ' Reset it to negative one since we are not sure one exists.
    g_ErrorInfo = -1
    'Update the UI with the currently selected collection name
    lblCurrCollectionName.Caption = CurrCollection.Name
    
    'Clear the list controls (i.e., make ready to re-populate)
    lbRelatedCollections.Clear
    lbProperties.Clear
    
    '///////////////////////////////////////////////////////////////////////////////////////////////
    '// *** RelatedCollectionInfo ***
    '// Get a reference to the current collections RelatedCollectionInfo collection,  populate
    '// it, and then fill a listbox with all the current collections available related collections
    '//
    Set RelatedCollections = CurrCollection.GetCollection("RelatedCollectionInfo", "")
    RelatedCollections.Populate
    RelatedObj = 0
    For Each ObjWork In RelatedCollections
        lbRelatedCollections.AddItem (ObjWork.Name)
        If ObjWork.Name = "ErrorInfo" Then g_ErrorInfo = RelatedObj
        RelatedObj = RelatedObj + 1
    Next

    'Cleanup object variable for reuse
    Set ObjWork = Nothing
    
    '/////////////////////////////////////////////////////////////////////////////////////////
    '// *** PropertyInfo ***
    '// Get a reference to the current collections PropertyInfo collection, populate it,
    '// and then fill a listbox with all the current collections available properties
    '//
    Set ObjectProperties = CurrCollection.GetCollection("PropertyInfo", "")
    ObjectProperties.Populate
    For Each ObjWork In ObjectProperties
       lbProperties.AddItem (ObjWork.Name)
    Next
    
    '/////////////////////////////////////////////////////////////////////////////////////////
    '// *** Collection objects ***
    '// Populate the current collection with it's available objects and display them
    '//
    CurrCollection.Populate
    DisplayObjects CurrCollection
    
    'Update toolbar and edit control state according to current collection
    With CurrCollection
        'Make sure all "root" base actions are enabled
        ToggleAppBtns True
        ToggleComponentBtns True
        ToggleUtilityBtn True
        'Set edit buttons state
        tbrExplorer.Buttons(ktbAdd).Enabled = .AddEnabled
        tbrExplorer.Buttons(ktbRemove).Enabled = .RemoveEnabled
        tbrExplorer.Buttons(ktbSaveChanges).Enabled = False
    End With
    
NTBail:
    'Local cleanup
    Set ObjWork = Nothing
    Set ObjectProperties = Nothing
    Set RelatedCollections = Nothing
    
    Exit Sub

NTErr:
    If Not ErrHandler(Err.Number, Err.Description, "Explorer::NavigateTo()") Then
        GoTo NTBail:
    Else
        Resume Next
    End If

End Sub

Private Sub DisplayObjects(CurrentCollection As Object)

    Dim oWork As Object
    
    With lbObjects
        'Clear the "object" list control
        .Clear
        'Add each of the objects in the current collection to the list control
        For Each oWork In CurrentCollection
            .AddItem (oWork.Name)
        Next
        'Set the object listbox control selection
        If .ListCount > 0 Then
            .Selected(0) = True
        End If
    End With
    
    'Set the property listbox control selection
    With lbProperties
        If .ListCount > 0 Then
            .Selected(0) = True
        End If
    End With
    
    Exit Sub
    
End Sub

Private Sub DisplayValue()

    Dim vPropValue      As Variant
    Dim iObjListIndex   As Integer
    Dim iPropListIndex  As Integer
    Dim bValOK          As Boolean
    
    'Cache to values for use
    iObjListIndex = lbObjects.ListIndex
    iPropListIndex = lbProperties.ListIndex
    
    'Continue only if the user has currently selected objects
    If iObjListIndex > kItemNotSelected Then
        'Display the property value and set modifiable attribute of the control used
        '   to display the property value, dependent upon whether or not a property
        '   is selected
        Select Case iPropListIndex
            Case kItemNotSelected
                'Disable  the property value control is no properties available or selected
                With txtPropValue
                    .Text = ""
                    .Locked = True
                End With
            Case Else
                With g_CurrCollection.Item(iObjListIndex)
                    'Handle WRITE ONLY property
                    If .IsPropertyWriteOnly(lbProperties.List(iPropListIndex)) Then
                        'Write only, display nothing
                        txtPropValue.Text = ""
                    Else
                        'Get the value of the selected property
                        On Error GoTo BadVal:
                        vPropValue = .Value(lbProperties.List(iPropListIndex))
                        bValOK = True
                        GoTo ValOK:
BadVal:
                        vPropValue = ""
                        bValOK = False
ValOK:
                        On Error GoTo 0
                        'Handle ErrorInfo collection vs. others
                        If g_CurrCollection.Name = "ErrorInfo" And iPropListIndex = 1 Then
                            txtPropValue.Text = MapError(CLng(vPropValue))
                        Else
                            txtPropValue.Text = vPropValue
                        End If
                    End If
                    'Handle READ ONLY property
                    If .IsPropertyReadOnly(lbProperties.List(iPropListIndex)) Or bValOK = False Then
                        With txtPropValue
                            .Locked = True
                            .BackColor = &H80000000
                        End With
                    Else
                        With txtPropValue
                            .Locked = False
                            .BackColor = &H80000005
                        End With
                    End If
                End With
        End Select
        
        'Toggle the ability to update property values depending on the state of the
        '   properties edit control
        cmdSetProperty.Enabled = Not txtPropValue.Locked
    End If

    Exit Sub
    
End Sub

Private Sub SetMPReady()

    'Set the mousepointer to normal if it already isn't
    If (vbNormal <> Me.MousePointer) Then
        ToggleMP Me
    End If
    
    Exit Sub
    
End Sub

Private Sub SetMPBusy()

    'Set the mousepointer to busy (i.e., hourglass) if it isn't already
    If (vbHourglass <> Me.MousePointer) Then
        ToggleMP Me
    End If
    
    Exit Sub
    
End Sub

Private Sub SetStatus(Optional sDescription As String = "Ready")

    'Set the status bar description
    sbrStatus.Panels(1).Text = sDescription
    
    Exit Sub
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
        
    'Prompt to save changes (if needed) before continuing, and if needed cancel the form
    '   unload if instructed to do so by the user
    If Not CheckDirty() Then
        Cancel = True
        Exit Sub
    End If
    
    'Cleanup/release of objects stored on the navigation stack
    ReleaseStack
    
    'Release the reference to the current collection
    Set g_CurrCollection = Nothing
    
    'Release the reference to the current catalog
    Set g_Catalog = Nothing
    
    Exit Sub
    
End Sub

Private Sub Form_Load()

    'Center the form on the screen
    CenterObject Me
    
    'Update the UI
    SetStatus
    
    ' Set the ErrorInfo spot in the list to be non-existant
    g_ErrorInfo = -1
    'Initialize the navigation stack object
    InitStack
    
    'Initialize the toolbar state
    InitToolbarState
        
    'Create the COM+ Admin catalog, otherwise inform the user and bail
    If Not CreateCatalog() Then
        MsgBox "Cannot create the required COM+ Administrative catalog and collection objects." & _
                vbCrLf & vbCrLf & "Press OK to close the application.", (vbCritical + vbOKOnly), "Error"
        Unload Me
        Exit Sub
    End If
    
    'Display the server name we are connected to (default = local)
    lblServerName.Caption = "local"
    
    Exit Sub
    
End Sub

Private Sub cmdSetProperty_Click()
    
    On Error GoTo SBErr:
    
    Dim iObjListIndex   As Integer
    Dim iPropListIndex  As Integer
    
    'Update the UI
    SetStatus
    
    'Toggle the mousepointer
    SetMPBusy
    
    'Cache the values for local use
    iObjListIndex = lbObjects.ListIndex
    iPropListIndex = lbProperties.ListIndex
    
    'Continue only if an object and property are selected
    If (iObjListIndex > kItemNotSelected) And (iPropListIndex > kItemNotSelected) Then
        'Set the new property value
        g_CurrCollection.Item(iObjListIndex).Value(lbProperties.List(iPropListIndex)) = txtPropValue.Text
        'Enable save button
        tbrExplorer.Buttons(ktbSaveChanges).Enabled = True
    End If
    
SBBail:
    SetMPReady
    Exit Sub

SBErr:
    If Not ErrHandler(Err.Number, Err.Description, "Explorer::cmdSetProperty_Click") Then
        DisplayValue
        GoTo SBBail:
    Else
        Resume Next
    End If

End Sub

Private Sub lbParentCollections_Click()
    
    Dim iCtr                    As Integer
    Dim iCurrentSelectionIndex  As Integer
    Dim iListCount              As Integer
            
                        
    'Prompt to save changes (if needed) before continuing
    If Not CheckDirty() Then
        Exit Sub
    End If
    
    'Cache for local use
    iCurrentSelectionIndex = lbParentCollections.ListIndex
    
    'Continue only if a related collection has been selected
    If (iCurrentSelectionIndex > kItemNotSelected) Then
        'Cleanup of parent collections listbox and setting of the current collection reference
        With lbParentCollections
            'Cache for local use
            iListCount = .ListCount - 1
            For iCtr = iListCount To iCurrentSelectionIndex Step -1
                'Remove the item
                .RemoveItem iCtr
                If (iCtr = iCurrentSelectionIndex) Then
                    'If this is the item the user just selected, set it as the current collection....
                    Set g_CurrCollection = Pop()
                Else
                    '... otherwise just remove the item from the stack
                    Pop
                End If
            Next
        End With
        'Re-init property edit controls
        txtPropValue.Text = ""
        cmdSetProperty.Enabled = False
        'Navigate to the new collection
        NavigateTo g_CurrCollection
    End If
    
    Exit Sub
    
End Sub

Private Sub lbRelatedCollections_Click()
    
    Dim sCollectionKey  As String
    Dim iColListIndex   As Integer
    Dim iObjListIndex   As Integer
    Dim oTmps           As Object
            
    'Prompt to save changes (if needed) before continuing
    If Not CheckDirty() Then
        Exit Sub
    End If
    
    'Cache the values for use
    iColListIndex = lbRelatedCollections.ListIndex
    iObjListIndex = lbObjects.ListIndex
    
    'Continue only if a related collection has been selected
    If iColListIndex > kItemNotSelected Then
        'Get the current objects key
        ' If this is the error collection, we need to skip touching anything
        ' before we ask for the collection, or the error information will be deleted.
        If lbRelatedCollections.List(iColListIndex) <> "ErrorInfo" Then
            'If we are on the root, re-get the collection
            If g_CurrCollection.Name = "Root" Then
                 Set g_CurrCollection = g_Catalog.GetCollection("Root")
             End If
            If iObjListIndex > kItemNotSelected Then
                sCollectionKey = g_CurrCollection.Item(iObjListIndex).Key
            Else
                'need to check that we have a key if we need one
                Select Case (lbRelatedCollections.List(iColListIndex))
                    Case "RelatedCollectionInfo", "PropertyInfo", "Root", "Catalog", "ErrorInfo", _
                         "Applications", "DCOMProtocols", "InprocServers", "JNECDataSources", _
                        "LocalComputer", "ApplicationCluster", "ComputerList", "TransientSubscriptions"
                        ' No Key needed
                    Case "RolesForMethod", "RolesForInterface", "MethodsForInterface", "InterfacesForComponent", _
                    "RolesForComponent", "Roles", "JNECDataSourceTables", "UsersInRole", "Components"
                        MsgBox "Need to select an object to open the collection from."
                        Exit Sub
                    Case Else
                        ' Collection hasn't been added here yet
                        MsgBox "This collection doesn't have a key check yet, it should be added"
                        Exit Sub
                End Select
            End If
        Else
            ' We don't want to get a key if we are on the error collection because it will throw out
            ' our error information making the call
            sCollectionKey = ""
        End If
        
        SetMPBusy
        
        'Get a reference to the new collection
        Set oTmps = g_CurrCollection.GetCollection(lbRelatedCollections.List(iColListIndex), (sCollectionKey))
        'Set the parent collection name so we can navigate backwards to it
        With lbParentCollections
            If (0 = .ListCount) Then
                .AddItem g_CurrCollection.Name
            Else
                .AddItem String(.ListCount, Chr(32)) & g_CurrCollection.Name, .ListCount
            End If
        End With
        'Push the current collection onto the navigation stack
        Push g_CurrCollection
        'Set the new current collection
        Set g_CurrCollection = oTmps
        'Navigate to the new collection
        NavigateTo g_CurrCollection
    End If
    
    SetMPReady
    Exit Sub
    
End Sub

Private Sub lbObjects_Click()
        
    'Update the status bar
    SetStatus
    'Display the selected value
    DisplayValue
    
    Exit Sub
    
End Sub

Private Sub lbProperties_Click()
        
    'Prompt to save changes (if needed) before continuing
    If Not CheckDirty() Then
        Exit Sub
    Else
        'Update the status bar
        SetStatus
        'Display the selected value
        DisplayValue
    End If
    
    Exit Sub
    
End Sub

Private Sub tbrExplorer_ButtonClick(ByVal Button As ComctlLib.Button)
On Error GoTo Err
    Dim myErr$
    Dim sCollectionKey  As String
    Dim iSaveChoice     As Integer
    Dim iColListIndex   As Integer
    Dim iObjListIndex   As Integer
    Dim oTmps           As Object
    
    'Toggle the mousepointer
    SetMPBusy
    
    'First check for a "dirty" form and prompt to save changes if needed
    If Button.Index <> ktbAdd And _
       Button.Index <> ktbSaveChanges And _
       Button.Index <> ktbRemove And _
       Button.Index <> ktbAbout Then
       
        If Not CheckDirty() Then
            Exit Sub
        End If
    End If 'validation that only the correct buttons have the save question
    
    'Execute requested command
    Select Case Button.Index
        Case ktbConnect
            'Display the form
            Connect.Show vbModal, Me
        Case ktbRefresh
            'Navigate to the current collection object
            NavigateTo g_CurrCollection
        Case ktbAdd
            'Add the new collection and save the change
            With g_CurrCollection
                .Add
            End With
            'Redisplay the current collections objects
            DisplayObjects g_CurrCollection
            tbrExplorer.Buttons(ktbSaveChanges).Enabled = True
        Case ktbSaveChanges
            'Attempt to save changes
            g_CurrCollection.SaveChanges
            'Disable the save button since the catalog is clean
            tbrExplorer.Buttons(ktbSaveChanges).Enabled = False
        Case ktbRemove
            'Cache to value for local use
            iObjListIndex = lbObjects.ListIndex
            'Continue only if an object has been selected
            If iObjListIndex > kItemNotSelected Then
                'Remove the object from the collection
                g_CurrCollection.Remove iObjListIndex
                'Redisplay the current collections objects
                DisplayObjects g_CurrCollection
                'Enable the save button to allow saving of this change
                tbrExplorer.Buttons(ktbSaveChanges).Enabled = True
            End If
        Case ktbStartApp
            'Load the form for setup
            Load AppUtil
            With AppUtil
                'Setup the form
                .FormCaption = "Start Application"
                .FormType = 0
                'Display the form
                .Show vbModal, Me
            End With
        Case ktbStopApp
            'Load the form for setup
            Load AppUtil
            With AppUtil
                'Setup the form
                .FormCaption = "Stop Application"
                .FormType = 1
                'Display the form
                .Show vbModal, Me
            End With
        Case ktbInstallApp
            'Display the form
            AppInstall.Show vbModal, Me
        Case ktbExportApp
            'Display the form
            AppExport.Show vbModal, Me
        Case ktbInstallComp
            'Display the form
            CompInstall.Show vbModal, Me
        Case ktbImportComp
            'Display the form
            CompImport.Show vbModal, Me
        Case ktbUtility
            'Display the form
            Utility.Show vbModal, Me
        Case ktbAbout
            'Display the about box
            About.Show vbModal, Me
        Case Else
            MsgBox "Invalid toolbar button index:  " & Button.Index, (vbInformation + vbOKOnly), "Error"
    End Select
    
    'Restore the mousepointer
    SetMPReady
    
    'Update the UI
    SetStatus
    
    Exit Sub
Err:
    ErrHandler Err.Number, Err.Description, Button.Key
    SetMPReady
    SetStatus

End Sub

Private Sub txtPropValue_GotFocus()

    'Select the currently displayed text
    SelectText txtPropValue
    
    Exit Sub
    
End Sub
