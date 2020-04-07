VERSION 5.00
Begin VB.Form frmAdmin 
   Caption         =   "News Flash"
   ClientHeight    =   2865
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4545
   LinkTopic       =   "Form1"
   ScaleHeight     =   2865
   ScaleWidth      =   4545
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame frmPublish 
      Caption         =   "Publish News Flash"
      Height          =   1455
      Left            =   0
      TabIndex        =   4
      Top             =   0
      Width           =   4455
      Begin VB.CheckBox chkQ 
         Caption         =   "Queued"
         Height          =   255
         Left            =   120
         TabIndex        =   12
         Top             =   840
         Width           =   975
      End
      Begin VB.TextBox txtURL 
         Height          =   285
         Left            =   1920
         TabIndex        =   11
         Text            =   "\\stories\today\1234.htm"
         Top             =   960
         Width           =   2295
      End
      Begin VB.TextBox txtHeadline 
         Height          =   285
         Left            =   1920
         TabIndex        =   7
         Text            =   "Exceeds Analyst Expectations"
         Top             =   600
         Width           =   2295
      End
      Begin VB.TextBox txtSymbol 
         Height          =   285
         Left            =   1920
         TabIndex        =   6
         Text            =   "MSFT"
         Top             =   240
         Width           =   2295
      End
      Begin VB.CommandButton cmdPublish 
         Caption         =   "Publish"
         Height          =   375
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   855
      End
      Begin VB.Label Label4 
         Alignment       =   1  'Right Justify
         Caption         =   "URL:"
         Height          =   255
         Left            =   1200
         TabIndex        =   10
         Top             =   960
         Width           =   615
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "Headline:"
         Height          =   255
         Left            =   1080
         TabIndex        =   9
         Top             =   600
         Width           =   735
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         Caption         =   "Symbol:"
         Height          =   255
         Left            =   1080
         TabIndex        =   8
         Top             =   240
         Width           =   735
      End
   End
   Begin VB.Frame frmInstall 
      Caption         =   "Install Event"
      Height          =   1215
      Left            =   0
      TabIndex        =   0
      Top             =   1560
      Width           =   4455
      Begin VB.CheckBox chkParallel 
         Caption         =   "Parallel"
         Height          =   375
         Left            =   120
         TabIndex        =   13
         Top             =   720
         Width           =   975
      End
      Begin VB.TextBox txtAppName 
         Height          =   375
         Left            =   2040
         TabIndex        =   2
         Text            =   "G:\News\NewsEventClass\Debug\NewsEventClass.dll"
         Top             =   240
         Width           =   2175
      End
      Begin VB.CommandButton cmdInstall 
         Caption         =   "Install"
         Height          =   375
         Left            =   120
         TabIndex        =   1
         Top             =   240
         Width           =   855
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         Caption         =   "EC Dll Path:"
         Height          =   255
         Left            =   960
         TabIndex        =   3
         Top             =   360
         Width           =   975
      End
   End
End
Attribute VB_Name = "frmAdmin"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim Admin As Object

'=============================================================================
'Function: cmdInstall_Click
'
'Summary: Processes clicking on the cmdInstall button
'
'=============================================================================
Private Sub cmdInstall_Click()
Dim Appcoll, Compcoll As ICatalogCollection
Dim Comp As ICatalogObject
Dim i
 
On Error GoTo err_cmdInstall
' Install the EventClass
If cmdInstall.Caption = "Install" Then

    Admin.InstallEventClass NewsPublisherApp, txtAppName.Text, "", ""
    If chkParallel.Value Then
    
         Set Appcoll = Admin.GetCollection("Applications")
         Appcoll.Populate
         
         For i = 0 To Appcoll.Count - 1
         If Appcoll.Item(i).Name = NewsPublisherApp Then
         Set Compcoll = Appcoll.GetCollection("Components", Appcoll.Item(i).Key)
         GoTo first
         End If
         Next
         'If we cannot find anything in the collection, then exit the sub
         Err.Raise 100, "NewsFlash", "Error", 0, 0
         
first:
         Compcoll.Populate
         For i = 0 To Compcoll.Count - 1
         If Compcoll.Item(i).Name = NEWSEVENTCLASSNAME Then
         Set Comp = Compcoll.Item(i)
         GoTo second
         End If
         Next
         Err.Raise 100, "NewsFlash", "Error", 0, 0
second:
         Comp.Value("FireInParallel") = True
         Compcoll.SaveChanges
     End If
cmdInstall.Caption = "Uninstall"
Else
'Uninstall the Eventclass
    Set Appcoll = Admin.GetCollection("Applications")
    Appcoll.Populate
    
    For i = 0 To Appcoll.Count - 1
    If Appcoll.Item(i).Name = NewsPublisherApp Then
    Set Compcoll = Appcoll.GetCollection("Components", Appcoll.Item(i).Key)
    GoTo third
    End If
    Next

third:
    Compcoll.Populate
    For i = 0 To Compcoll.Count - 1
    If Compcoll.Item(i).Name = NEWSEVENTCLASSNAME Then
    Compcoll.Remove (i)
    Compcoll.SaveChanges
    GoTo fourth
    End If
    Next
fourth:
    cmdInstall.Caption = "Install"
End If
         
Exit Sub

err_cmdInstall:
    MsgBox Hex$(Err.Number) & ": " & Err.Description

End Sub

Private Sub cmdPublish_Click()
    Dim oTrader As INewsEvent
    Dim sMnkr As String
    
    On Error GoTo err_cmdPublish


    sMnkr = "new:" & EVENTCLSID

    If chkQ.Value Then
        sMnkr = "queue:/" & sMnkr
    End If

    Set oTrader = CreateObject(sMnkr)

    oTrader.NewsFlash Now, txtSymbol.Text, txtHeadline.Text, txtURL.Text
    
Exit Sub

err_cmdPublish:
    MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub
'=============================================================================
'Function: cmdInstall_Click
'
'Summary: Install NewsPublisherApp
'
'=============================================================================
Private Sub Form_Load()
Dim Appcoll As ICatalogCollection
Dim App As ICatalogObject

On Error GoTo err_frmload

' Create COMAdmin object
Set Admin = CreateObject("COMAdmin.COMAdminCatalog.1")

' Create an application to host the Cascaded EventClass
Set Appcoll = Admin.GetCollection("Applications")

Set App = Appcoll.Add
App.Value("Name") = NewsPublisherApp
App.Value("Activation") = 1

' Applicable only if MSMQ is installed

App.Value("QueuingEnabled") = True
App.Value("QueueListenerEnabled") = True

Appcoll.SaveChanges
Exit Sub
err_frmload:
    MsgBox Hex$(Err.Number) & ": " & Err.Description

End Sub
'=============================================================================
'Function: cmdInstall_Click
'
'Summary: Uninstall NewsPublisherApp
'
'=============================================================================
Private Sub Form_Unload(Cancel As Integer)
Dim Appcoll As ICatalogCollection
Dim App As ICatalogObject
Dim i

On Error GoTo err_frmunload

Set Appcoll = Admin.GetCollection("Applications")

Appcoll.Populate

For i = 0 To Appcoll.Count - 1
    If Appcoll.Item(i).Name = NewsPublisherApp Then
    Appcoll.Remove (i)
    Appcoll.SaveChanges
    GoTo jump:
    End If
Next
jump:
Exit Sub
err_frmunload:
    MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub
