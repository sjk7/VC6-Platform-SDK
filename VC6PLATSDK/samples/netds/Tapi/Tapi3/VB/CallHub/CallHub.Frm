VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form frmCallHubs 
   Caption         =   "CallHub Demo"
   ClientHeight    =   8370
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9900
   LinkTopic       =   "Form1"
   ScaleHeight     =   8370
   ScaleWidth      =   9900
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox txtDescriptionMC 
      Height          =   2535
      Left            =   5040
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   6
      Top             =   360
      Width           =   4575
   End
   Begin ComctlLib.TreeView gTreeMonitoredCalls 
      Height          =   2535
      Left            =   360
      TabIndex        =   5
      Top             =   360
      Width           =   4575
      _ExtentX        =   8070
      _ExtentY        =   4471
      _Version        =   327682
      LabelEdit       =   1
      Style           =   6
      Appearance      =   1
   End
   Begin VB.CommandButton pbUnloadCH 
      Caption         =   "UnloadCallHubs"
      Height          =   375
      Left            =   2760
      TabIndex        =   4
      Top             =   7920
      Width           =   1935
   End
   Begin VB.CommandButton pbLoadCH 
      Caption         =   "Reload CallHubs"
      Height          =   375
      Left            =   600
      TabIndex        =   3
      Top             =   7920
      Width           =   1935
   End
   Begin VB.TextBox txtMessages 
      Height          =   1815
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   2
      Top             =   6000
      Width           =   9255
   End
   Begin VB.TextBox txtDescriptionCH 
      Height          =   2415
      Left            =   5040
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   1
      Top             =   3240
      Width           =   4575
   End
   Begin ComctlLib.TreeView gTreeCallHubs 
      Height          =   2415
      Left            =   360
      TabIndex        =   0
      Top             =   3240
      Width           =   4575
      _ExtentX        =   8070
      _ExtentY        =   4260
      _Version        =   327682
      LabelEdit       =   1
      Style           =   6
      Appearance      =   1
   End
   Begin VB.Label Label3 
      Caption         =   "Events"
      Height          =   255
      Left            =   360
      TabIndex        =   9
      Top             =   5760
      Width           =   2775
   End
   Begin VB.Label Label2 
      Caption         =   "Call Hubs"
      Height          =   255
      Left            =   360
      TabIndex        =   8
      Top             =   3000
      Width           =   2775
   End
   Begin VB.Label Label1 
      Caption         =   "Monitored Calls"
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   120
      Width           =   2775
   End
End
Attribute VB_Name = "frmCallHubs"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'
'--------------------------------------------------------------------------
'
'  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
'
'Notes:
'   - if we want to receive call state events for monitored calls, we have
'   to keep a reference to the call object, when it arrives on TE_CALLNOTIFICATION
'
'

Option Explicit

Private gobjTAPI As TAPI
Private WithEvents gobjTapiWithEvents As TAPI
Attribute gobjTapiWithEvents.VB_VarHelpID = -1
Private gCollVBlRegister As Collection          'VB collection with lRegister values

'
'For each tree, define a collection to keep the data related to each node.
'(Note: this should be possible with Node.Tag, but it's not, since that is a
'Variant/String and doesn't allow me to set objects in it - actually, this is
'a bug in VB5 which has been fixed for VB6.)
'So these collections should correspond exactly to the collections of Nodes from
'each tree, and each item will contain the Object (data) displayed in the
'corresponding node.
Private gTreeCollDataMC As New Collection
Private gTreeCollDataCH As New Collection

Private Sub Form_Load()
On Error Resume Next

    Dim nResult As Long

    '
    'create and initialize TAPI object
    '
    Set gobjTAPI = New TAPI
    nResult = CheckError("Form_Load: New TAPI")
    If nResult <> NO_ERROR Then
        MsgBox "Can't create TAPI object, bailing.", vbOKOnly + vbCritical, "Fatal Error"
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
    
    Call gobjTAPI.Initialize
    nResult = CheckError("Form_Load: gobjTAPI.Initialize")
    If nResult <> NO_ERROR Then
        MsgBox "Can't initialize TAPI, bailing.", vbOKOnly + vbCritical, "Fatal Error"
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
    
    '
    'set the EventFilter to accept all defined tapi events
    '
    gobjTAPI.EventFilter = TAPI3_ALL_TAPI_EVENTS
    nResult = CheckError("Form_Load: gobjTAPI.EventFilter")
    If nResult <> NO_ERROR Then
        MsgBox "Some TAPI events might be missed!", vbOKOnly + vbExclamation, "Warning"
    End If
    
    '
    'advise the notification interface
    '
    Set gobjTapiWithEvents = gobjTAPI
    nResult = CheckError("Form_Load: Set gobjTapiWithEvents = gobjTAPI")
    If nResult <> NO_ERROR Then
        MsgBox "Can't register for receiving events, bailing.", vbOKOnly + vbCritical, "Fatal Error"
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
    
    '
    'register for receiving call hub events
    'on all addresses, (for all media types)
    '
    
    Set gCollVBlRegister = New Collection
    
    Dim dwSupportedMediaTypes As Long
    Dim varArrAddresses, bMonitor, bOwner, lCallbackInstance
    varArrAddresses = GetAllAddresses(gobjTAPI)
    bMonitor = True
    bOwner = False
        
    'register the addresses one by one, using only the mediatypes
    'supported on that address
    Dim nIndex, lRegister As Long
    For nIndex = LBound(varArrAddresses) To UBound(varArrAddresses)
        Dim objITMediaSupport As ITMediaSupport
        
        Set objITMediaSupport = varArrAddresses(nIndex)
        nResult = CheckError("Form_Load: Set objITMediaSupport = varArrAddresses(" & nIndex & ")")
        'If nResult <> NO_ERROR Then Exit Sub   - ignore error, skip to next address item
        
        If Not (objITMediaSupport Is Nothing) Then
        
            dwSupportedMediaTypes = objITMediaSupport.MediaTypes
            nResult = CheckError("Form_Load: objITMediaSupport.MediaTypes")
            If nResult <> NO_ERROR Then dwSupportedMediaTypes = 0  ' - ignore error, skip to next address
            
            Set objITMediaSupport = Nothing
            CheckError ("Form_Load: Releasing objITMediaSupport")
            
            If dwSupportedMediaTypes <> 0 Then
            
                'Let's use the address index as lCallbackInstance.
                'In this way, all events related to an address should
                'have as lCallbackInstance the same number as the index
                'of the address
                lCallbackInstance = nIndex
                
                lRegister = gobjTAPI.RegisterCallNotifications( _
                    varArrAddresses(nIndex), bMonitor, bOwner, _
                    dwSupportedMediaTypes, _
                    lCallbackInstance)
                nResult = CheckError("Form_Load: gobjTAPI.RegisterCallNotifications")
                'If nResult <> NO_ERROR Then Exit Sub  - ignore error, skip to next address
                
                If nResult = NO_ERROR Then
                    'remember lRegister, in case you want to call UnregisterNotifications
                    gCollVBlRegister.Add (lRegister)
                End If
                
            End If
            
        End If
        
    Next nIndex
    
    FreeAddresses (varArrAddresses)        'Note: VB would do this anyway
        
    'populate tree with all call hubs
    
    Call CHTree_Load(gTreeCallHubs, gTreeCollDataCH, gobjTAPI.CallHubs)
    nResult = CheckError("Form_Load: gobjTAPI.CallHubs")
    If nResult <> NO_ERROR Then
        MsgBox "Can't populate tree with CallHubs, bailing.", vbOKOnly + vbCritical, "Fatal Error"
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
    
    Call gTreeCallHubs.Refresh
    
    'populate tree with all monitored calls
    
    Call MCTree_Load(gTreeMonitoredCalls, gTreeCollDataMC, gobjTAPI.Addresses)
    nResult = CheckError("Form_Load: gobjTAPI.Addresses")
    If nResult <> NO_ERROR Then
        MsgBox "Can't populate tree with Addresses, bailing.", vbOKOnly + vbCritical, "Fatal Error"
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
    
    Call gTreeMonitoredCalls.Refresh
    
End Sub

Private Sub Form_Unload(Cancel As Integer)

'catch all tapi errors but ignore them, since we want to shut down anyway
'but at the same time we want to attempt all possible cleanup
On Error Resume Next

'
'Let's first make sure we won't receive any events during clean up:
'(because during clean up we modify the trees with data, while the trees with
'objects remain unchanged; if events are fired at this point, the
'2 types of trees will be out of sync, and errors will occur trying to
'access data that doesn't exist anymore; this should be fixed with VB 6.0,
'that allows saving "object" data directly in the tree - then the separate
'trees of data won't be needed anymore.
'
' - unregister from receiving notifications
    Dim nIndex, nCount
    nCount = gCollVBlRegister.Count
    For nIndex = 1 To nCount
        Call gobjTAPI.UnregisterNotifications(gCollVBlRegister.Item(nIndex))
        Call CheckError("Form_Unload: gobjTAPI.UnregisterNotifications")
    Next nIndex
    
' - "unadvise" by releasing the "callback" object, the one that receives events:
    Set gobjTapiWithEvents = Nothing
    Call CheckError("Form_Unload: Set gobjTapiWithEvents = Nothing")

'now go ahead with shutting down and releasing all the objects
    
    Call MCTree_Unload(gTreeMonitoredCalls, gTreeCollDataMC)
    
    Call CHTree_Unload(gTreeCallHubs, gTreeCollDataCH)
    
'this is part of "releasing all objects" but it has been moved to the top of the function
'
'    Dim nIndex, nCount
'    nCount = gCollVBlRegister.Count
'    For nIndex = 1 To nCount
'        gobjTAPI.UnregisterNotifications (gCollVBlRegister.Item(nIndex))
'    Next nIndex
'
    For nIndex = 1 To nCount
        gCollVBlRegister.Remove (1)
    Next nIndex
    Set gCollVBlRegister = Nothing
    
'this is part of "releasing all objects" but it has been moved to the top of the function
'
'    Set gobjTapiWithEvents = Nothing
    
    Call gobjTAPI.Shutdown
    Call CheckError("Form_Unload: gobjTAPI.Shutdown")
    
    Set gobjTAPI = Nothing
    Call CheckError("Form_Unload: Releasing gobjTAPI")
    
End Sub

Private Sub pbLoadCH_Click()
    '
    'first of all, destroy old tree
    '
    Call CHTree_Unload(gTreeCallHubs, gTreeCollDataCH)
    Call gTreeCallHubs.Refresh

    'repopulate tree with all call hubs
    
    Call CHTree_Load(gTreeCallHubs, gTreeCollDataCH, gobjTAPI.CallHubs)
    
End Sub

Private Sub pbUnloadCH_Click()

    Call CHTree_Unload(gTreeCallHubs, gTreeCollDataCH)
    Call gTreeCallHubs.Refresh

End Sub

Private Sub gTreeCallHubs_NodeClick(ByVal Node As ComctlLib.Node)
    'display information about node
    Call CHTree_DisplayNode(Node, gTreeCollDataCH)
End Sub

Private Sub gTreeMonitoredCalls_NodeClick(ByVal Node As ComctlLib.Node)
    'display information about node
    Call MCTree_DisplayNode(Node, gTreeCollDataMC)
End Sub

Private Sub gobjTapiWithEvents_Event( _
    ByVal TapiEvent As TAPI3Lib.TAPI_EVENT, _
    ByVal pEvent As Object)
On Error Resume Next
    
    Dim nResult As Long
    Dim objITCallInfo As ITCallInfo
    
    PrintEvent (TapiEvent)
    
    '
    'process the events
    '
    
    Select Case TapiEvent
    
        '
        'update tree with callhubs
        '
        Case TE_CALLHUB
            Call PrintCallHubEvent(pEvent.Event)
            
            Dim objITCallHub As ITCallHub
            Set objITCallHub = pEvent.CallHub
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.CallHub")
            If nResult <> NO_ERROR Then Exit Sub
            
            Set objITCallInfo = pEvent.Call
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.Call")
            If nResult <> NO_ERROR Then Exit Sub
            
            Select Case pEvent.Event
                Case CHE_CALLHUBNEW
                    
                    Call CHTree_AddNewCallHub( _
                        gTreeCallHubs, gTreeCollDataCH, objITCallHub)
                    
                Case CHE_CALLHUBIDLE
                    
                    Call CHTree_RemoveCallHub( _
                        gTreeCallHubs, gTreeCollDataCH, objITCallHub)
                    
                    '
                    'the selection might have changed
                    '(if removed CallHub was currently selected),
                    'so refresh displayed info
                    '
                    Call CHTree_DisplaySelectedNode(gTreeCallHubs, gTreeCollDataCH)
                    
                Case CHE_CALLJOIN
                    Call CHTree_AddNewParticipantCall( _
                        gTreeCallHubs, gTreeCollDataCH, objITCallInfo, objITCallHub)
                        
                Case CHE_CALLLEAVE
                    Call CHTree_RemoveParticipantCall( _
                        gTreeCallHubs, gTreeCollDataCH, objITCallInfo)
                    
                    '
                    'the selection might have changed
                    '(if removed participant was currently selected),
                    'so refresh displayed info
                    '
                    Call CHTree_DisplaySelectedNode(gTreeCallHubs, gTreeCollDataCH)
                
                Case Else
                    'don't need this case, because PrintCallHubEvent
                    'already detected invalid value of pEvent.Event
            End Select
            
            'if node is currently selected, re - display (refresh) its info
            '(e.g. number of participant calls might have changed)
            
            If CHTree_IsCallHubSelected(gTreeCallHubs, gTreeCollDataCH, objITCallHub) Then
                Call CHTree_DisplaySelectedNode(gTreeCallHubs, gTreeCollDataCH)
            End If
    
        Case TE_CALLINFOCHANGE
            Call PrintCallInfoChangeEvent(pEvent)
            
            'if node containing this call is currently selected,
            're - display (refresh) its info
            
            'ATTN: the nodes from both trees (HubCalls, MonCalls)
            'can contain this call. So refresh both trees.
            
            Set objITCallInfo = pEvent.Call
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.Call")
            If nResult <> NO_ERROR Then Exit Sub
            
            If CHTree_IsParticipantCallSelected(gTreeCallHubs, gTreeCollDataCH, objITCallInfo) Then
                Call CHTree_DisplaySelectedNode(gTreeCallHubs, gTreeCollDataCH)
            End If
            
            If MCTree_IsCallSelected(gTreeMonitoredCalls, gTreeCollDataMC, objITCallInfo) Then
                Call MCTree_DisplaySelectedNode(gTreeMonitoredCalls, gTreeCollDataMC)
            End If
    
        '
        'update tree with monitored calls
        '
        Case TE_CALLNOTIFICATION
            
            Set objITCallInfo = pEvent.Call
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.Call")
            If nResult <> NO_ERROR Then Exit Sub
            
            PrintCallNotificationEvent (pEvent.Event)   'must always be CNE_MONITOR !
            Call MCTree_AddNewCall(gTreeMonitoredCalls, gTreeCollDataMC, objITCallInfo)
            
        Case TE_CALLSTATE
            Call PrintCallStateEvent(pEvent)
            
            'if node is currently selected, re - display (refresh) its info
            
            'ATTN: the nodes from both trees (HubCalls, MonCalls)
            'can contain this call. So refresh both trees.
            
            Set objITCallInfo = pEvent.Call
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.Call")
            If nResult <> NO_ERROR Then Exit Sub
            
            If CHTree_IsParticipantCallSelected(gTreeCallHubs, gTreeCollDataCH, objITCallInfo) Then
                Call CHTree_DisplaySelectedNode(gTreeCallHubs, gTreeCollDataCH)
            End If
            
            If MCTree_IsCallSelected(gTreeMonitoredCalls, gTreeCollDataMC, objITCallInfo) Then
                Call MCTree_DisplaySelectedNode(gTreeMonitoredCalls, gTreeCollDataMC)
            End If
    
            Dim nCallState As CALL_STATE
            
            nCallState = pEvent.State
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.State")
            If nResult <> NO_ERROR Then Exit Sub
            
            Select Case nCallState
                Case CS_DISCONNECTED
                    Call MCTree_RemoveCall(gTreeMonitoredCalls, gTreeCollDataMC, objITCallInfo)
                    
                    '
                    'the selection might have changed
                    '(if removed call was currently selected),
                    'so refresh displayed info
                    '
                    Call MCTree_DisplaySelectedNode(gTreeMonitoredCalls, gTreeCollDataMC)
                Case CS_INPROGRESS
                Case CS_OFFERING
                Case CS_CONNECTED
                Case CS_HOLD
                Case CS_IDLE
                Case CS_QUEUED
                Case Else
                    'don't need this case, because PrintCallStateEvent
                    'already detected invalid value of pEvent.State
            End Select
        
        Case TE_ADDRESS
            Call PrintAddressEvent(pEvent.Event)
        
        
        Case TE_DIGITEVENT
            Call PrintDigitDetectionEvent(pEvent)
            
            Set objITCallInfo = pEvent.Call
            nResult = CheckError("gobjTapiWithEvents_Event: pEvent.Call")
            If nResult <> NO_ERROR Then Exit Sub
            
            'check if call is in the tree with "monitored calls"
            If Not IsCallInTree( _
                gTreeMonitoredCalls, gTreeCollDataMC, objITCallInfo) Then
                
                MsgBox ("ERROR: TE_DIGITEVENT - can't find node that contains this call, in MonCalls Tree")
                
            End If
            
            'check if call is in the tree with "call hubs"
            If Not IsCallInTree( _
                gTreeCallHubs, gTreeCollDataCH, objITCallInfo) Then
                
                MsgBox ("ERROR: TE_DIGITEVENT - can't find node that contains this call, in CallHub Tree")
                
            End If
            
        Case TE_GENERATEEVENT
            Call PrintUnexpectedEvent("TE_GENERATEEVENT")
        
        
        Case TE_CALLMEDIA
            Call PrintUnexpectedEvent("TE_CALLMEDIA")
        Case TE_PRIVATE
            Call PrintUnexpectedEvent("TE_PRIVATE")
        Case TE_TAPIOBJECT
            Call PrintUnexpectedEvent("TE_TAPIOBJECT")
        Case TE_QOSEVENT
            Call PrintUnexpectedEvent("TE_QOSEVENT")
        
        Case TE_ACDGROUP
            Call PrintUnexpectedEvent("TE_ACDGROUP")
        Case TE_AGENT
            Call PrintUnexpectedEvent("TE_AGENT")
        Case TE_AGENTHANDLER
            Call PrintUnexpectedEvent("TE_AGENTHANDLER")
        Case TE_AGENTSESSION
            Call PrintUnexpectedEvent("TE_AGENTSESSION")
        Case TE_QUEUE
            Call PrintUnexpectedEvent("TE_QUEUE")
        Case TE_REQUEST
            Call PrintUnexpectedEvent("TE_REQUEST")
        
        Case Else
            'don't need this case, because PrintEvent (TapiEvent)
            'already detected invalid value of TapiEvent
    End Select
    
    'Note: no need to release something given by tapi3,
    'release only what we asked for (queried) from tapi3.
    'In other words, we don't need to release pEvent.
End Sub
