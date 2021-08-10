VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Incoming"
   ClientHeight    =   5025
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4815
   LinkTopic       =   "Form1"
   ScaleHeight     =   5025
   ScaleWidth      =   4815
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton pbDisconnect 
      Caption         =   "Disconnect"
      Height          =   375
      Index           =   1
      Left            =   1440
      TabIndex        =   3
      Top             =   2760
      Width           =   2055
   End
   Begin VB.CommandButton pbAnswer 
      Caption         =   "Answer"
      Default         =   -1  'True
      Height          =   375
      Index           =   0
      Left            =   1440
      TabIndex        =   2
      Top             =   2160
      Width           =   2055
   End
   Begin VB.CommandButton RegisterForReceiveCall 
      Caption         =   "Register the Application  for Receiving Calls"
      Height          =   615
      Left            =   1440
      TabIndex        =   1
      Top             =   1200
      Width           =   2055
   End
   Begin VB.Frame Frame1 
      Caption         =   "Register"
      Height          =   1815
      Left            =   240
      TabIndex        =   4
      Top             =   240
      Width           =   4335
      Begin VB.ComboBox cmbAddressTypes 
         Height          =   315
         Left            =   1800
         TabIndex        =   0
         Top             =   360
         Width           =   2175
      End
      Begin VB.Label Label1 
         Caption         =   "Calls you want to receive:"
         Height          =   495
         Left            =   360
         TabIndex        =   5
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.Label lblStatus 
      Height          =   1335
      Left            =   1080
      TabIndex        =   7
      Top             =   3480
      Width           =   3495
   End
   Begin VB.Label lblStatusTitle 
      Caption         =   "Status:"
      Height          =   255
      Left            =   360
      TabIndex        =   6
      Top             =   3480
      Width           =   615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------------------------------
'
'  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
'
' INCOMING.EXE
'
' Example of receiving calls with TAPI 3.0
'
' This application will allow a user to receive audio calls
' by using TAPI 3.0.
'
' The application will simply look for the 1st address that is able
' to receive calls of the specified type (phone calls, or h323 calls -
' the user is allowed to decide). The address is also chosen
' only if it supports the "audio" media type.
' It will register then itself on this address to receive calls.
' On the received calls, it will select 2 terminals before
' calling answer. The terminals are the default terminals for
' "audio capture" and "audio render". (The app expects a sound card
' to be installed.)
' The app will display messages to announce whenever a new call
' arrives and also when a call state event fires.
'
' This application does not make outgoing calls.
'

Option Explicit

Const TAPI3_ALL_TAPI_EVENTS = _
                            TE_ACDGROUP Or _
                            TE_ADDRESS Or _
                            TE_AGENT Or _
                            TE_AGENTHANDLER Or _
                            TE_AGENTSESSION Or _
                            TE_CALLHUB Or _
                            TE_CALLINFOCHANGE Or _
                            TE_CALLMEDIA Or _
                            TE_CALLNOTIFICATION Or _
                            TE_CALLSTATE Or _
                            TE_DIGITEVENT Or _
                            TE_GENERATEEVENT Or _
                            TE_PRIVATE Or _
                            TE_QOSEVENT Or _
                            TE_QUEUE Or _
                            TE_REQUEST Or _
                            TE_TAPIOBJECT

'other constants
Const NO_ERROR = 0                  'Err.Number = 0 when there is no error

Dim gobjTapi As TAPI
Dim WithEvents gobjTapiWithEvents As TAPI
Attribute gobjTapiWithEvents.VB_VarHelpID = -1

Dim gobjAddress As ITAddress
Dim glRegistrationToken As Long

Dim gobjReceivedCallInfo As ITCallInfo

Dim gbSupportedCall As Boolean

Private Sub Form_Load()
    
    pbAnswer(0).Enabled = False
    
    'populate combo box with names of call types
    'attach to each combo item the address type that
    'can receive that type of call
    
    cmbAddressTypes.AddItem ("Phone Calls")
    cmbAddressTypes.ItemData(cmbAddressTypes.NewIndex) = LINEADDRESSTYPE_PHONENUMBER
    
    cmbAddressTypes.AddItem ("H323 Calls")
    cmbAddressTypes.ItemData(cmbAddressTypes.NewIndex) = LINEADDRESSTYPE_DOMAINNAME
    
    'set selection on 1st item
    cmbAddressTypes.ListIndex = 0

End Sub

Private Sub Form_Unload(Cancel As Integer)

'catch all tapi errors but ignore them, since we want to shut down anyway
'but at the same time we want to attempt all possible cleanup
On Error Resume Next

    'release all global objects
    
    Set gobjReceivedCallInfo = Nothing
    Set gobjAddress = Nothing
    Set gobjTapiWithEvents = Nothing
    If Not (gobjTapi Is Nothing) Then
        Call gobjTapi.Shutdown
    End If
    Set gobjTapi = Nothing
    
    'empty combo box
    Dim i
    For i = 1 To cmbAddressTypes.ListCount
        cmbAddressTypes.RemoveItem (0)
    Next i
End Sub

Private Sub DisplayCallState(State As CALL_STATE)
    Dim strMsg As String
    
    Select Case State
        Case CS_CONNECTED
            strMsg = "call state: CS_CONNECTED" & Chr(13)
            strMsg = strMsg & "The call was answered, now you can disconnect "
            strMsg = strMsg & "or wait for disconnected state. "
            strMsg = strMsg & "Don't press Answer before new call arrives. "
            lblStatus.Caption = strMsg
        
        Case CS_DISCONNECTED
            strMsg = "call state: CS_DISCONNECTED" & Chr(13)
            strMsg = strMsg & "Call will be released. "
            strMsg = strMsg & "New incoming calls will be accepted. "
            lblStatus.Caption = strMsg
            
        Case CS_HOLD
            lblStatus.Caption = "call state: CS_HOLD"
        Case CS_IDLE
            lblStatus.Caption = "call state: CS_IDLE"
        
        Case CS_INPROGRESS
            lblStatus.Caption = "call state: CS_INPROGRESS"
        
        Case CS_OFFERING
            If gbSupportedCall = True Then
                strMsg = "call state: CS_OFFERING"
                strMsg = strMsg & Chr(13) & "A call was received. You can answer it"
                lblStatus.Caption = strMsg
            End If
        
        Case CS_QUEUED
            lblStatus.Caption = "call state: CS_QUEUED"
        
        Case Else
            lblStatus.Caption = "call state: unknown!!"
    End Select
    
    lblStatus.Refresh
End Sub

Private Sub pbAnswer_Click(index As Integer)
On Error Resume Next

    Dim strMsg
    Dim nResult As Long
        
    If gobjReceivedCallInfo Is Nothing Then
        strMsg = "There is no call to be answered!"
        lblStatus.Caption = strMsg
        lblStatus.Refresh
        Exit Sub
    End If
        
    Dim nCallState As CALL_STATE
    
    nCallState = gobjReceivedCallInfo.CallState
    nResult = CheckError("pbAnswer_Click: gobjReceivedCallInfo.CallState")
    If nResult <> NO_ERROR Then Exit Sub
    
    If Not (nCallState = CS_OFFERING) Then
        strMsg = "Cannot answer call that doesn't have offering state."
        strMsg = strMsg & " Did you already press Answer?"
        lblStatus.Caption = strMsg
        lblStatus.Refresh
        Exit Sub
    End If
'
'Not all addresses support ITTerminalSupport and ITStreamControl
'therefore we need to be prepared for exceptions.
'
    
    'query ITBasicCallControl, the call control interface
    Dim objCallControl As ITBasicCallControl
    
    Set objCallControl = gobjReceivedCallInfo
    nResult = CheckError("pbAnswer_Click: Set objCallControl = gobjReceivedCallInfo")
    If nResult <> NO_ERROR Then Exit Sub
    
    '
    'prepare the terminals (take the default terminals for
    'rendering and capturing "audio")
    '
    'query ITTerminalSupport from Address object
    Dim objTerminalSupport As ITTerminalSupport
    
    Set objTerminalSupport = gobjAddress
    nResult = CheckError("pbAnswer_Click: Set objTerminalSupport = gobjAddress")
    If nResult <> NO_ERROR Then Exit Sub
    
    If Not (objTerminalSupport Is Nothing) Then
        Dim objTerminal1 As ITTerminal
        Dim objTerminal2 As ITTerminal
        
        Set objTerminal1 = objTerminalSupport.GetDefaultStaticTerminal( _
            TAPIMEDIATYPE_AUDIO, TD_CAPTURE)
        nResult = CheckError("pbAnswer_Click: objTerminalSupport.GetDefaultStaticTerminal (audio capture)")
        If nResult <> NO_ERROR Then Exit Sub
        
        Set objTerminal2 = objTerminalSupport.GetDefaultStaticTerminal( _
            TAPIMEDIATYPE_AUDIO, TD_RENDER)
        nResult = CheckError("pbAnswer_Click: objTerminalSupport.GetDefaultStaticTerminal (audio render)")
        If nResult <> NO_ERROR Then Exit Sub
        
        'release not needed objects
        Set objTerminalSupport = Nothing
        Call CheckError("Releasing objTerminalSupport")
        '
        'Select the terminals before answering - select them one by one;
        'we'll need the ITStreamControl interface for doing this.
        'Select each terminal on the corresponding stream.
        '
        
        Dim objStreamControl As ITStreamControl
        
        Set objStreamControl = objCallControl
        nResult = CheckError("pbAnswer_Click: Set objStreamControl = objCallControl")
        If nResult <> NO_ERROR Then Exit Sub
        
        If Not (objStreamControl Is Nothing) Then
            Dim objITCollStreams As ITCollection
            
            Set objITCollStreams = objStreamControl.Streams
            nResult = CheckError("pbAnswer_Click: objStreamControl.Streams")
            If nResult <> NO_ERROR Then Exit Sub
            
            Dim nIndex As Long, objCrtStream As ITStream
            
            For nIndex = 1 To objITCollStreams.Count
                
                Set objCrtStream = objITCollStreams.Item(nIndex)
                nResult = CheckError("pbAnswer_Click: objITCollStreams.Item(" & nIndex & ")")
                If nResult <> NO_ERROR Then Exit Sub
                
                If objCrtStream.MediaType = TAPIMEDIATYPE_AUDIO Then
                    If objCrtStream.Direction = TD_CAPTURE Then
                        If Not (objTerminal1 Is Nothing) Then
                            Call objCrtStream.SelectTerminal(objTerminal1)
                        End If
                    End If
                    If objCrtStream.Direction = TD_RENDER Then
                        If Not (objTerminal2 Is Nothing) Then
                            Call objCrtStream.SelectTerminal(objTerminal2)
                        End If
                    End If
                End If
                
                Set objCrtStream = Nothing
                Call CheckError("Releasing objCrtStream")
                
            Next nIndex
        
            Set objITCollStreams = Nothing
            Call CheckError("Releasing objITCollStreams")
            
            Set objStreamControl = Nothing
            Call CheckError("Releasing objStreamControl")
        End If
        
        Set objTerminal1 = Nothing
        Call CheckError("Releasing objTerminal1")
        
        Set objTerminal2 = Nothing
        Call CheckError("Releasing objTerminal2")
    End If
    
    'Answer
    objCallControl.Answer
    nResult = CheckError("pbAnswer_Click: objCallControl.Answer")
    If nResult <> NO_ERROR Then Exit Sub
    
    'disable the button
    pbAnswer(0).Enabled = False
    
    'release the call control interface
    Set objCallControl = Nothing
    Call CheckError("Releasing objCallControl")
    
End Sub

Private Sub pbDisconnect_Click(index As Integer)
On Error Resume Next

    Dim nResult As Long
    
    If gobjReceivedCallInfo Is Nothing Then
        Dim strMsg As String
        strMsg = "There is no call to be disconnected."
        lblStatus.Caption = strMsg
        lblStatus.Refresh
        Exit Sub
    End If
    
    'disconnect the call: need to query its call control interface for this
    Dim objCallControl As ITBasicCallControl
    
    Set objCallControl = gobjReceivedCallInfo
    nResult = CheckError("pbDisconnect_Click: Set objCallControl = gobjReceivedCallInfo")
    If nResult <> NO_ERROR Then Exit Sub
    
    Call objCallControl.Disconnect(DC_NORMAL)
    nResult = CheckError("pbDisconnect_Click: objCallControl.Disconnect ")
    If nResult <> NO_ERROR Then Exit Sub
    
    'release the call control interface
    Set objCallControl = Nothing
    Call CheckError("Releasing objCallControl")
        
End Sub

'this "callback" function must be reentrant
Private Sub gobjTapiWithEvents_Event( _
    ByVal TapiEvent As TAPI3Lib.TAPI_EVENT, _
    ByVal pEvent As Object)

On Error Resume Next

    Dim nResult As Long
    Dim strMsg
    
    If TapiEvent = TE_CALLNOTIFICATION Then
        
        'in the case of TE_CALLNOTIFICATION, pEvent contains
        'an ITCallNotficationEvent interface, but since
        'pEvent is declared as Object, we must specifically
        'query for that interface
        
        Dim objCallNotificationEvent As ITCallNotificationEvent
        
        Set objCallNotificationEvent = pEvent
        nResult = CheckError("gobjTapiWithEvents_Event: Set objCallNotificationEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub
        
        'decide if we can take this call: this sample app only
        'supports one call at a time, so if it already has a call,
        'it will reject any other call that arrives in the same time.
        '
        
        gbSupportedCall = True
        
        If Not (gobjReceivedCallInfo Is Nothing) Then
            
            gbSupportedCall = False
            
            strMsg = "This app doesn't support a second call. "
            strMsg = strMsg & "Unsupported second call will be rejected!"
            lblStatus.Caption = strMsg
            lblStatus.Refresh
            
            'Note: objCallNotificationEvent.Call actually contains an
            'ITCallInfo interface, but by assigning it to an ITBasicCallControl
            'interface, we actually query for the interface "ITBasicCallControl"
            Dim objReceivedCallControl As ITBasicCallControl
            
            Set objReceivedCallControl = objCallNotificationEvent.Call
            nResult = CheckError("gobjTapiWithEvents_Event: objCallNotificationEvent.Call")
            If nResult <> NO_ERROR Then Exit Sub
            
            'Reject the not supported call by calling Disconnect
            'Note: this second call will arrive only if the tsp (tapi service provider)
            'supports more than 1 call per address.
            Dim code As DISCONNECT_CODE
            code = DC_REJECTED
            Call objReceivedCallControl.Disconnect(code)
            nResult = CheckError("gobjTapiWithEvents_Event: objReceivedCallControl.Disconnect(DC_REJECTED)")
            If nResult <> NO_ERROR Then Exit Sub
            
            'release all objects that are not needed any longer
            
            Set objReceivedCallControl = Nothing
            Call CheckError("Releasing objReceivedCallControl")
            
            Set objCallNotificationEvent = Nothing
            Call CheckError("Releasing objReceivedCallControl")
            
            Exit Sub
            
        End If
        
        'query ITCallInfo interface for the new call, and store it
        Set gobjReceivedCallInfo = objCallNotificationEvent.Call
        nResult = CheckError("gobjTapiWithEvents_Event: objCallNotificationEvent.Call")
        If nResult <> NO_ERROR Then
            Set gobjReceivedCallInfo = Nothing
            Exit Sub
        End If
        
        'reenable the button
        pbAnswer(0).Enabled = True
    
        Set objCallNotificationEvent = Nothing
        Call CheckError("Releasing objCallNotificationEvent")
        
        Exit Sub
    End If
    
    If TapiEvent = TE_CALLSTATE Then
        
        'for this type of event, the object pEvent must be
        'queried for its ITCallStateEvent interface
        Dim objCallStateEvent As ITCallStateEvent
        
        Set objCallStateEvent = pEvent
        nResult = CheckError("gobjTapiWithEvents_Event: Set objCallStateEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub
        
        Dim State As CALL_STATE
        Dim objEventCallInfo As ITCallInfo
        
        'extract the call object from pEvent (from its
        'ITCallStateEvent interface)
        
        Set objEventCallInfo = objCallStateEvent.Call
        nResult = CheckError("gobjTapiWithEvents_Event: Set objEventCallInfo = objCallStateEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub
        
        State = objCallStateEvent.State
        nResult = CheckError("gobjTapiWithEvents_Event: objCallStateEvent.State")
        If nResult <> NO_ERROR Then Exit Sub
        
        If objEventCallInfo Is gobjReceivedCallInfo Then
        
            DisplayCallState (State)
            
            If State = CS_DISCONNECTED Then
                'after call is disconnected, you don't need
                'its object anymore; you can only release it
                Set gobjReceivedCallInfo = Nothing
                Call CheckError("Releasing gobjReceivedCallInfo")
            End If
        
        End If
        
        'release not needed objects
        Set objEventCallInfo = Nothing
        Call CheckError("Releasing objEventCallInfo")
        
        Set objCallStateEvent = Nothing
        Call CheckError("Releasing objCallStateEvent")
        
        Exit Sub
    End If
    
    Exit Sub
End Sub

Private Sub RegisterForReceiveCall_Click()
On Error Resume Next

    Dim nResult As Long
    Dim strMsg As String
    
    'don't let the user do this in the middle of a call
    If Not (gobjReceivedCallInfo Is Nothing) Then
        lblStatus.Caption = "Don't do this in the middle of a call."
        lblStatus.Refresh
        
        Exit Sub
    End If
    
    RegisterForReceiveCall.MousePointer = vbHourglass
    
    'If the TAPI object was not created yet, create it
    'now, also initialize it and register the outgoing
    'interface; we'll perform all these only once per app.
    '
    If gobjTapi Is Nothing Then
        
        lblStatus.Caption = "Initializing TAPI ..."
        lblStatus.Refresh
        
        'create the tapi object
        Set gobjTapi = New TAPI
        nResult = CheckError("RegisterForReceiveCall_Click: Creating TAPI object")
        If nResult <> NO_ERROR Then
            RegisterForReceiveCall.MousePointer = vbDefault
            lblStatus.Caption = "Initializing TAPI failed! Quit the app and retry."
            Exit Sub
        End If
        
        'call Initialize before calling any other tapi function
        Call gobjTapi.Initialize
        nResult = CheckError("RegisterForReceiveCall_Click: gobjTapi.Initialize")
        If nResult <> NO_ERROR Then
            RegisterForReceiveCall.MousePointer = vbDefault
            lblStatus.Caption = "Initializing TAPI failed! Quit the app and retry."
            Exit Sub
        End If
        
        'set the EventFilter to accept all defined tapi events
        gobjTapi.EventFilter = TAPI3_ALL_TAPI_EVENTS
        nResult = CheckError("RegisterForReceiveCall_Click: setting the EventFilter")
        If nResult <> NO_ERROR Then
            RegisterForReceiveCall.MousePointer = vbDefault
            lblStatus.Caption = "Initializing TAPI failed! Quit the app and retry."
            Exit Sub
        End If
        
        'register the outgoing interface (the one that will actually
        'receive and process the events)
        Set gobjTapiWithEvents = gobjTapi
        nResult = CheckError("RegisterForReceiveCall_Click: registering for events")
        If nResult <> NO_ERROR Then
            RegisterForReceiveCall.MousePointer = vbDefault
            lblStatus.Caption = "Initializing TAPI failed! Quit the app and retry."
            Exit Sub
        End If
    
        lblStatus.Caption = "Initializing TAPI finished."
        lblStatus.Refresh
        
    End If
    
    'pick up the collection of addresses
    '
    Dim objcollAddress As ITCollection
    
    Set objcollAddress = gobjTapi.Addresses
    nResult = CheckError("RegisterForReceiveCall_Click: gobjTapi.Addresses")
    If nResult <> NO_ERROR Then
        RegisterForReceiveCall.MousePointer = vbDefault
        lblStatus.Caption = "Fatal error! Quit the app and retry."
        Exit Sub
    End If
    
    'search address that supports the desired address type and media type
    '
    Dim nAddressIndex
    nAddressIndex = FindAddressIndex(objcollAddress)
    
    If nAddressIndex < 1 Or nAddressIndex > objcollAddress.Count Then
        
        strMsg = "Could not find an appropriate address for this address type!"
        lblStatus.Caption = strMsg
        lblStatus.Refresh
        
        'release all "not global" objects
        Set objcollAddress = Nothing
        Call CheckError("Releasing objcollAddress")
        
        RegisterForReceiveCall.MousePointer = vbDefault
        Exit Sub
    End If
    
    'If RegisterCallNotifications had been previously called,
    'unregister here, before registering for the new address
    'This is not a required step, a TAPI3 app can register for
    'receiving call notifications on more than one address in
    'the same time, but the app must be able to handle multiple
    'calls on multiple addresses.
    'This sample prefers to register on only one address at a time.
    If glRegistrationToken <> 0 Then
        
        Call gobjTapi.UnregisterNotifications(glRegistrationToken)
        nResult = CheckError("RegisterForReceiveCall_Click: gobjTapi.UnregisterNotifications")
        If nResult <> NO_ERROR Then
            RegisterForReceiveCall.MousePointer = vbDefault
            lblStatus.Caption = "Fatal error! Quit the app and retry."
            Exit Sub
        End If
        
        glRegistrationToken = 0
    End If
        
    'pick up the "N"-th address - the address on which
    'you want to register for receiving calls
    Set gobjAddress = objcollAddress.Item(nAddressIndex)
    nResult = CheckError("RegisterForReceiveCall_Click: objcollAddress.Item(" & nAddressIndex & ")")
    If nResult <> NO_ERROR Then
        RegisterForReceiveCall.MousePointer = vbDefault
        lblStatus.Caption = "Fatal error! Quit the app and retry."
        Exit Sub
    End If
    
    Set objcollAddress = Nothing    'no more needed, release
    Call CheckError("Releasing objcollAddress")
    
    'Register (specify) media types for which you want to receive calls;
    'only calls that have this media type will be offered to the app.
    'The media types must be passed to RegisterCallNotifications
    'bits in a "dword", which in VB is actually a "long".
    '
    
    Dim fOwner As Boolean, fMonitor As Boolean
    Dim lMediaTypes As Long, lCallbackInstance As Long
    
    'fOwner = True ensures that app receives incoming calls
    'and their call state events
    fOwner = True
    fMonitor = False
    lMediaTypes = TAPIMEDIATYPE_AUDIO
    lCallbackInstance = 1
    
    glRegistrationToken = gobjTapi.RegisterCallNotifications( _
        gobjAddress, fMonitor, fOwner, lMediaTypes, lCallbackInstance)
    If Err.Number <> 0 Then
        strMsg = "Registering for receiving calls failed." & Chr(13) & _
            "If you have a data modem, replace it with a voice modem. " & _
            "Quit the app and try again."
        lblStatus.Caption = strMsg
        lblStatus.Refresh
        
        RegisterForReceiveCall.MousePointer = vbDefault
        Exit Sub
    End If
    
    'from now on the app is able to receive calls made on the
    'specified address, with the specified media type
    
    RegisterForReceiveCall.MousePointer = vbDefault

    lblStatus.Caption = _
        "Registration for calls succeeded. " & Chr(13) & "Waiting for a call..."
    lblStatus.Refresh
    Exit Sub
End Sub

'Search through all addresses and return the index of the one that matches
'the address type selected in the combo box with address types. Also, the
'found address must support at least the media types "audio".
'Return 0 if no address found. Otherwise return its index, which will be
'between 1 and Addresses.Count
'Note: filter out the addresses exposed by the following 2 providers:
' - "kmddsp.tsp" = "TAPI Kernel-Mode Service Provider"
' - "ndptsp.tsp" = "NDIS Proxy TAPI Service Provider"
'because they might be found instead of the modem address, and this
'sample wants to use the modem for the phone calls.
Private Function FindAddressIndex(objCollAddresses As ITCollection) As Long
On Error Resume Next

    Dim nResult As Long
    Dim nSelectedType As Long
    Dim indexAddr As Long
    Dim objCrtAddress As ITAddress
    Dim lAddrTypes As Long
    Dim objMediaSupport As ITMediaSupport
    Dim objAddressCaps As ITAddressCapabilities
    Dim lMediaTypes As Long
    Dim bFound As Boolean
    
    'prepare return value
    FindAddressIndex = 0
    
    '
    'retrieve from combo box the type of the selected address type
    '
    nSelectedType = cmbAddressTypes.ItemData(cmbAddressTypes.ListIndex)
    
    '
    'search through all addresses the first one that matches this type
    'and also supports the media type "audio"
    '
    bFound = False
    
    For indexAddr = 1 To objCollAddresses.Count
        
        Set objCrtAddress = objCollAddresses.Item(indexAddr)
        nResult = CheckError("FindAddressIndex: objCollAddresses.Item(" & indexAddr & ")")
        If nResult <> NO_ERROR Then Exit Function
        
        '
        'reject the addresses exposed by kmddsp.tsp and ndptsp.tsp,
        'because they might be found instead of the modem address
        '
        If objCrtAddress.ServiceProviderName <> "kmddsp.tsp" And _
            objCrtAddress.ServiceProviderName <> "ndptsp.tsp" Then
        
            nResult = CheckError("FindAddressIndex: objCrtAddress.ServiceProviderName")
            If nResult <> NO_ERROR Then Exit Function
            
            Set objMediaSupport = objCrtAddress
            nResult = CheckError("FindAddressIndex: Set objMediaSupport = objCrtAddress")
            If nResult <> NO_ERROR Then Exit Function
            
            Set objAddressCaps = objCrtAddress
            nResult = CheckError("FindAddressIndex: Set objAddressCaps = objCrtAddress")
            If nResult <> NO_ERROR Then Exit Function
            
            lMediaTypes = objMediaSupport.MediaTypes
            nResult = CheckError("FindAddressIndex: objMediaSupport.MediaTypes")
            If nResult <> NO_ERROR Then Exit Function
            
            '
            'note: objMediaSupport.MediaTypes is a long that has
            'a bit set for each supported media type;
            'check if the bit for "audio" is set.
            '
            If lMediaTypes And TAPIMEDIATYPE_AUDIO Then
                
                lAddrTypes = objAddressCaps.AddressCapability(AC_ADDRESSTYPES)
                nResult = CheckError("FindAddressIndex: objAddressCaps.AddressCapability(AC_ADDRESSTYPES)")
                If nResult <> NO_ERROR Then Exit Function
                
                'Note: take in account that:
                '- modem lines support LINEADDRESSTYPE_PHONENUMBER only
                '- h323 lines support LINEADDRESSTYPE_DOMAINNAME,
                'LINEADDRESSTYPE_EMAILNAME, LINEADDRESSTYPE_IPADDRESS
                'and LINEADDRESSTYPE_PHONENUMBER!
                '
                
                If nSelectedType = LINEADDRESSTYPE_PHONENUMBER Then
                    'the user selected "phone calls"
                    'we must expect such an address to support
                    'LINEADDRESSTYPE_PHONENUMBER but not LINEADDRESSTYPE_DOMAINNAME
                    
                    If lAddrTypes And LINEADDRESSTYPE_PHONENUMBER Then
                        If lAddrTypes And LINEADDRESSTYPE_DOMAINNAME Then
                            'it's not a modem, it's an H323 address!
                            'just skip it.
                        Else
                            'It might be a modem, or Dialogic line, etc.
                            'if it's a modem it might be a data modem or a voice modem.
                            'If it's a data modem, it will fail on RegisterCallNotifications(audio)
                            'so we'd better skip it.
                            
                            'since beta3, it's easy to figure out if this is datamodem or
                            'not: a voice modem would support ITTerminalsSupport,
                            'but a datamodem wouldn't; so we could filter out datamodems
                            'right here (before giving the user a chance to try
                            'to register on it), by checking if the ITTerminalsSupport
                            'is supported or not; if it's not supported, an error
                            'will be generated; so let's catch errors too
                            
                            Dim objITTerminalSupport As ITTerminalSupport
                            
                            Set objITTerminalSupport = objAddressCaps
                            nResult = CheckError("FindAddressIndex: Set objITTerminalSupport = objAddressCaps")
                            If nResult <> NO_ERROR Then Exit Function
                            
                            If Not (objITTerminalSupport Is Nothing) Then
                                bFound = True   'it's not a data modem
                            End If
                            
                            Set objITTerminalSupport = Nothing
                            Call CheckError("Releasing objITTerminalSupport")
                        End If
                        
                    End If
                    
                End If
                
                If nSelectedType = LINEADDRESSTYPE_DOMAINNAME Then
                    'the user selected "h323 calls"
                    'we must expect such an address to support
                    'LINEADDRESSTYPE_DOMAINNAME; it's enough to check only
                    'for this flag.
                    
                    If lAddrTypes And LINEADDRESSTYPE_DOMAINNAME Then
                        bFound = True
                    End If
                End If
                
            End If
            
            Set objAddressCaps = Nothing
            Call CheckError("Releasing objAddressCaps")
            
            Set objMediaSupport = Nothing
            Call CheckError("Releasing objMediaSupport")
        
        End If
        
        Set objCrtAddress = Nothing
        Call CheckError("Releasing objCrtAddress")
        
        If bFound = True Then Exit For
    Next indexAddr
    
    '
    'return the index of the found address, or 0 if no address found
    '
    If bFound = True Then
        FindAddressIndex = indexAddr
    Else
        FindAddressIndex = 0
    End If
    Exit Function
End Function

'Reads the last error from Err object
'If Err.Number = 0, it means that no error has occurred.
'If no error, prints a success message in the debugger; if error occurred, also puts up an error message box.
'Returns the error code found in Err.Number when this function is called.
'Before returning, it clears the error.
'
Private Function CheckError(strMessage As String) As Long

    Dim strError As String
    
    CheckError = Err.Number
    
    If Err.Number = NO_ERROR Then
        strError = "Succes: "
        strError = strError & strMessage
    
        'success has low logging level
        Debug.Print (strError)
    Else
        strError = "Error: "
        strError = strError & strMessage & " Err.Number = 0x" & Hex(Err.Number)
        strError = strError & " Err.Descripton = " & Err.Description
    
        'error has high logging level
        Debug.Print (strError)
        Call MsgBox(strError, vbExclamation)
    End If
    
    Err.Clear

End Function
