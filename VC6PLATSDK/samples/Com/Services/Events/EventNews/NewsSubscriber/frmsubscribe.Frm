VERSION 5.00
Begin VB.Form frmSubscribe 
   Caption         =   "Subscriber"
   ClientHeight    =   6825
   ClientLeft      =   720
   ClientTop       =   345
   ClientWidth     =   5385
   LinkTopic       =   "Form1"
   ScaleHeight     =   6825
   ScaleWidth      =   5385
   Begin VB.Frame frmCascade 
      Caption         =   "Cascaded Event Class"
      Height          =   1935
      Left            =   0
      TabIndex        =   7
      Top             =   4800
      Width           =   5295
      Begin VB.CommandButton cmdInstall 
         Caption         =   "Install"
         Height          =   375
         Left            =   240
         TabIndex        =   18
         Top             =   360
         Width           =   1095
      End
      Begin VB.TextBox txtCascadeDllName 
         Height          =   285
         Left            =   2880
         TabIndex        =   17
         Text            =   "G:\News\CascadeEC\Debug\CascadeEC.dll"
         Top             =   960
         Width           =   2175
      End
      Begin VB.TextBox txtCascadeAppName 
         Height          =   285
         Left            =   2880
         TabIndex        =   14
         Text            =   "CascadeApp"
         Top             =   480
         Width           =   2175
      End
      Begin VB.CheckBox chkCascQueued 
         Caption         =   "Queued"
         Height          =   375
         Left            =   1920
         TabIndex        =   9
         Top             =   1320
         Width           =   1215
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "DLL Path :"
         Height          =   255
         Index           =   1
         Left            =   1680
         TabIndex        =   16
         Top             =   960
         Width           =   975
      End
      Begin VB.Label Label3 
         Alignment       =   1  'Right Justify
         Caption         =   "App Name:"
         Height          =   255
         Index           =   0
         Left            =   1680
         TabIndex        =   15
         Top             =   480
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Persistent Subscriber"
      Height          =   1095
      Left            =   0
      TabIndex        =   5
      Top             =   3600
      Width           =   5295
      Begin VB.OptionButton optPersCascade 
         Caption         =   "Cascaded"
         Height          =   255
         Left            =   2640
         TabIndex        =   13
         Top             =   480
         Width           =   1215
      End
      Begin VB.OptionButton optPersDirect 
         Caption         =   "Direct"
         Height          =   255
         Left            =   1680
         TabIndex        =   12
         Top             =   480
         Width           =   855
      End
      Begin VB.CheckBox chkPersQueued 
         Caption         =   "Queued"
         Height          =   255
         Left            =   3960
         TabIndex        =   8
         Top             =   480
         Width           =   1095
      End
      Begin VB.CommandButton cmdPersist 
         Caption         =   "Subscribe"
         Height          =   375
         Left            =   120
         TabIndex        =   6
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Transient Subscriber"
      Height          =   3375
      Left            =   0
      TabIndex        =   0
      Top             =   120
      Width           =   5295
      Begin VB.OptionButton optTransCascade 
         Caption         =   "Cascaded"
         Height          =   195
         Left            =   3120
         TabIndex        =   11
         Top             =   480
         Width           =   1215
      End
      Begin VB.OptionButton optTransDirect 
         Caption         =   "Direct"
         Height          =   195
         Left            =   1680
         TabIndex        =   10
         Top             =   480
         Value           =   -1  'True
         Width           =   1095
      End
      Begin VB.CheckBox chkBad 
         Caption         =   "Bad Subscriber"
         Height          =   255
         Left            =   120
         TabIndex        =   4
         Top             =   2880
         Width           =   1455
      End
      Begin VB.CommandButton cmdClear 
         Caption         =   "Clear"
         Height          =   375
         Left            =   3960
         TabIndex        =   3
         Top             =   2880
         Width           =   1215
      End
      Begin VB.CommandButton cmdTransient 
         Caption         =   "Subscribe"
         Height          =   375
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Width           =   1215
      End
      Begin VB.ListBox lstNews 
         Height          =   1815
         Left            =   120
         TabIndex        =   1
         Top             =   960
         Width           =   5055
      End
   End
End
Attribute VB_Name = "frmSubscribe"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Implements NewsEvent
Dim g_oAdmin As Object
Dim g_CascadeApp, g_TransID

Private Sub cmdClear_Click()
    lstNews.Clear
End Sub
'=============================================================================
'Function: cmdInstall_Click
'
'Summary: Installs the Cascaded EventClass on the local machine
'and also makes it a persistent subscriber for CLSID_NewsEvent eventclass
'=============================================================================
Private Sub cmdInstall_Click()
Dim Appcoll, Compcoll, Subcoll As ICatalogCollection
Dim App, Comp, SubObj As ICatalogObject
Dim i, j

On Error GoTo err_cmdInstall

Set Appcoll = g_oAdmin.GetCollection("Applications")

If cmdInstall.Caption = "Install" Then
    
    ' Create an application to host the Cascaded EventClass
    Set App = Appcoll.Add
    g_CascadeApp = txtCascadeAppName.Text
    App.Value("Name") = g_CascadeApp
    App.Value("Activation") = 1
    
    ' Applicable only if MSMQ client is installed
    App.Value("QueuingEnabled") = True
    App.Value("QueueListenerEnabled") = True
    
    Appcoll.SaveChanges
    
    ' Install Cascade EventClass
    g_oAdmin.InstallEventClass txtCascadeAppName.Text, txtCascadeDllName.Text, "", ""
    
    ' Create a persistent subscription for this component (Subscriber to CLSID_NewsEvent)
    Appcoll.Populate
    For i = 0 To Appcoll.Count - 1
    If Appcoll.Item(i).Name = txtCascadeAppName.Text Then
        ' Now get the COMPONENTS collection
        Set Compcoll = Appcoll.GetCollection("Components", Appcoll.Item(i).Key)
        Compcoll.Populate
        
        For j = 0 To Compcoll.Count - 1
        If Compcoll.Item(j).Name = CASCADEEVENTCLASSNAME Then
        ' Now get the SUBSCRIPTIONS collection
            Set Subcoll = Compcoll.GetCollection("SubscriptionsForComponent", Compcoll.Item(j).Key)
            Subcoll.Populate
            GoTo jump1
        End If
        Next
    End If
    Next
    Err.Raise 100, "NewsSubscriber", "Error", 0, 0

jump1:

    Set SubObj = Subcoll.Add
    SubObj.Value("EventCLSID") = EVENTCLSID
    SubObj.Value("Name") = CascadeSubscription
    Subcoll.SaveChanges
    cmdInstall.Caption = "Uninstall"
    optPersCascade.Enabled = True
    optTransCascade.Enabled = True
        
Else
     ' Remove the application (this in turn uninstalls the eventclass and removes the subscription)
    Appcoll.Populate
    For j = 0 To Appcoll.Count - 1
        If Appcoll.Item(j).Name = g_CascadeApp Then
        Appcoll.Remove (j)
        Appcoll.SaveChanges
        cmdInstall.Caption = "Install"
        optPersCascade.Enabled = False
        optTransCascade.Enabled = False
        Exit Sub
        End If
    Next
End If

Exit Sub

err_cmdInstall:
    
    MsgBox Hex$(Err.Number) & ": " & Err.Description

End Sub
'=============================================================================
'Function: cmdPersist_Click
'
'Summary: Registers a Persistent subscription for the the CASCADEEVENTCLSID, if
' cascaded is checked else registers a persistent subscription for the EVENTCLSID
' on the local machine
'=============================================================================
Private Sub cmdPersist_Click()

Dim Appcoll, Compcoll, Subcoll As ICatalogCollection
Dim App, Comp, SubObj As ICatalogObject
Dim i, j, k

On Error GoTo err_cmdSubscribe

' Get the APPLICATIONS collection
Set Appcoll = g_oAdmin.GetCollection("Applications")
Appcoll.Populate

For i = 0 To Appcoll.Count - 1
 If Appcoll.Item(i).Name = NewsSubscriberApp Then
     ' Now get the COMPONENTS collection
     Set Compcoll = Appcoll.GetCollection("Components", Appcoll.Item(i).Key)
     Compcoll.Populate
     GoTo First:
  End If
Next
Err.Raise 100, "NewsFlash", "Error", 0, 0


First:
For i = 0 To Compcoll.Count - 1
  If Compcoll.Item(i).Name = PERSISTATLNAME Then
     ' Now get the SUBSCRIPTIONS collection
      Set Subcoll = Compcoll.GetCollection("SubscriptionsForComponent", Compcoll.Item(i).Key)
      Subcoll.Populate
      GoTo Second:
  End If
Next
Err.Raise 100, "NewsFlash", "Error", 0, 0

Second:
If cmdPersist.Caption = "Subscribe" Then
    ' Add a new subscription
    Set SubObj = Subcoll.Add
    If optPersCascade.Value Then
        SubObj.Value("EventCLSID") = CASCADEEVENTCLSID
    Else
        SubObj.Value("EventCLSID") = EVENTCLSID
    End If
    
    SubObj.Value("Name") = PersistentSubscription
    If chkPersQueued.Value Then
        SubObj.Value("Queued") = True
    End If
    Subcoll.SaveChanges
   
    If chkPersQueued.Value Then
        chkPersQueued.Enabled = False
    End If
    cmdPersist.Caption = "Unsubscribe"
    
    'start the application
    g_oAdmin.StartApplication (NewsSubscriberApp)
Else
    ' Remove the subscription
    For k = 0 To Subcoll.Count - 1
    If Subcoll.Item(k).Name = PersistentSubscription Then
    Subcoll.Remove (k)
    Subcoll.SaveChanges
    cmdPersist.Caption = "Subscribe"
    chkPersQueued.Enabled = True
    GoTo exitSub
    End If
    Next
End If
exitSub:

Exit Sub

err_cmdSubscribe:
    MsgBox Hex$(Err.Number) & ": " & Err.Description

End Sub
'=============================================================================
'Function: cmdTransient_Click
'
'Summary: Registers a Persistent subscription for the the CASCADEEVENTCLSID, if
' cascaded is checked else registers a persistent subscription for the EVENTCLSID
' on the local machine
'=============================================================================
Private Sub cmdTransient_Click()
Dim Subcoll As ICatalogCollection
Dim SubObj As ICatalogObject
Dim k


On Error GoTo err_cmdCascade

   
' Get the TRANSIENTSUBSCRIPTIONS collection
Set Subcoll = g_oAdmin.GetCollection("TransientSubscriptions")

If cmdTransient.Caption = "Subscribe" Then
    ' Add a new subscription
    Set SubObj = Subcoll.Add
    If optTransCascade.Value Then
        SubObj.Value("EventCLSID") = CASCADEEVENTCLSID
    Else
        SubObj.Value("EventCLSID") = EVENTCLSID
    End If
    
    SubObj.Value("Name") = TransientSubscription
    SubObj.Value("SubscriberInterface") = Me

    Subcoll.SaveChanges
    cmdTransient.Caption = "Unsubscribe"
    g_TransID = SubObj.Value("ID")
Else
    Subcoll.Populate
    ' Remove the subscription
    For k = 0 To Subcoll.Count - 1
    If Subcoll.Item(k).Value("ID") = g_TransID Then
    Subcoll.Remove (k)
    Subcoll.SaveChanges
    GoTo jump2
    End If
    Next
    
jump2:
    cmdTransient.Caption = "Subscribe"
End If

Exit Sub
err_cmdCascade:
    MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub
'=============================================================================
'Function: Form_Load
'
'Summary: Called when the Form is loaded
'This will create AdminCatalog object and install NewsPublisherApp
'=============================================================================
Private Sub Form_Load()
Dim Appcoll As ICatalogCollection
Dim App As ICatalogObject
Dim i

On Error GoTo err_frmload
optPersCascade.Enabled = False
optTransCascade.Enabled = False

' Create COMAdmin object
Set g_oAdmin = CreateObject("COMAdmin.COMAdminCatalog.1")

Set Appcoll = g_oAdmin.GetCollection("Applications")

' check if an APP named NewsSubscriberApp is already created. If not, then create one

Appcoll.Populate

For i = 0 To Appcoll.Count - 1
    If Appcoll.Item(i).Name = NewsSubscriberApp Then
    GoTo exitSub
    End If
Next
    
' Create an application to host the subscriber
Set App = Appcoll.Add
App.Value("Name") = NewsSubscriberApp
App.Value("Activation") = 1

' Applicable if MSMQ client is installed
App.Value("QueuingEnabled") = True
App.Value("QueueListenerEnabled") = True

Appcoll.SaveChanges

' Install the PersistATL subscriber component
g_oAdmin.InstallComponent NewsSubscriberApp, COMPONENT, "", ""

exitSub:

Exit Sub
err_frmload:
    MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub

Private Sub Form_Unload(Cancel As Integer)
Dim Appcoll, Subcoll As ICatalogCollection
Dim App As ICatalogObject
Dim i, j, k

On Error GoTo err_frmunload

Set Appcoll = g_oAdmin.GetCollection("Applications")

Appcoll.Populate

'Remove NewsPublisher and CascadePub application
For i = 0 To 2

    For j = 0 To Appcoll.Count - 1
        If Appcoll.Item(j).Name = g_CascadeApp Or Appcoll.Item(j).Name = NewsSubscriberApp Then
        Appcoll.Remove (j)
        Appcoll.SaveChanges
        GoTo jump
    End If
Next
jump:
Next

' Remove the transient subscription
Set Subcoll = g_oAdmin.GetCollection("TransientSubscriptions")
Subcoll.Populate
' Remove the subscription
For k = 0 To Subcoll.Count - 1
    If Subcoll.Item(k).Value("ID") = g_TransID Then
        Subcoll.Remove (k)
        Subcoll.SaveChanges
        GoTo jump2
    End If
Next
jump2:

Exit Sub
err_frmunload:
    MsgBox Hex$(Err.Number) & ": " & Err.Description
End Sub


Private Sub NewsEvent_LongQuote(ByVal Symbol As String, ByVal BidPrice As Double, ByVal AskPrice As Double, ByVal LastTradeTime As String, ByVal LastTradePrice As Double, ByVal NetChange As Double, ByVal DailyHigh As Double, ByVal DailyLow As Double, ByVal AskSize As Long, ByVal BidSize As Long, ByVal OpenPrice As Double, ByVal ClosePrice As Double, ByVal CloseDate As String)

End Sub

Private Sub NewsEvent_NewsFlash(ByVal dtTimeStamp As Date, ByVal Symbol As String, ByVal Headline As String, ByVal URL As String)
    Dim lCount As Long

    lstNews.AddItem CStr(dtTimeStamp) & ":: " & Symbol & ":  " & Headline
    lCount = lstNews.ListCount - 1
    lstNews.ListIndex = lCount
    If lCount > 20 Then
        lstNews.RemoveItem 0
    End If
    If chkBad.Value Then
        MsgBox CStr(dtTimeStamp) & ":: " & Symbol & ": " & Headline
    End If
End Sub

Private Sub NewsEvent_ShortQuote(ByVal Symbol As String, ByVal BidPrice As Double, ByVal AskPrice As Double, ByVal LastTradeTime As Date, ByVal LastTradePrice As Double, ByVal NetChange As Double, ByVal DailyHigh As Double, ByVal DailyLow As Double)

End Sub

Private Sub txtCascadeCLSID_Change()

End Sub
