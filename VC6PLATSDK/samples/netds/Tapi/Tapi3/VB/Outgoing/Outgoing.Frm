VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Outgoing"
   ClientHeight    =   4260
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4260
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.ComboBox cmbAddressTypes 
      Height          =   315
      Left            =   1920
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   720
      Width           =   2295
   End
   Begin VB.CommandButton pbDial 
      Caption         =   "Dial"
      Default         =   -1  'True
      Height          =   375
      Index           =   0
      Left            =   960
      TabIndex        =   2
      Top             =   1920
      Width           =   3135
   End
   Begin VB.CommandButton pbDisconnect 
      Caption         =   "Disconnect"
      Enabled         =   0   'False
      Height          =   375
      Index           =   1
      Left            =   960
      TabIndex        =   3
      Top             =   2520
      Width           =   3135
   End
   Begin VB.TextBox txtDestAddress 
      Height          =   285
      Left            =   1920
      MaxLength       =   40
      TabIndex        =   1
      Top             =   1320
      Width           =   2295
   End
   Begin VB.Label lblStatus 
      Height          =   855
      Left            =   1800
      TabIndex        =   7
      Top             =   3120
      Width           =   2415
   End
   Begin VB.Label lblStatusTitle 
      Caption         =   "Status:"
      Height          =   255
      Left            =   480
      TabIndex        =   6
      Top             =   3120
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Address:"
      Height          =   255
      Left            =   480
      TabIndex        =   5
      Top             =   1320
      Width           =   1095
   End
   Begin VB.Label Label1 
      Caption         =   "Address Type:"
      Height          =   255
      Left            =   480
      TabIndex        =   4
      Top             =   720
      Width           =   1215
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
' OUTGOING.EXE
'
' Example of making an asynchronous outgoing call with TAPI 3.0
'
' This application will allow a user to make an asynchronous outgoing call
' by using TAPI 3.0. The application will simply look for the 1st address
' that matches the address type selected by the user in the combo box.
' It will actually pick up the address that also supports at least the
' media type "audio" (therefore it will skip all other addresses, even if
' they match the desired address type).
' It will then use that address to make calls. On the call, it will
' select the media type "audio", and, if this is supported too, it will also
' select the media type "video"; for each of these media types it will use
' their default static terminals for capturing and rendering;
' except for "video render" which needs a dynamic terminal to be created.
' The name of the destination address is taken by means of an edit box.
' The app will display messages to announce whenever a call state event fires.
'
' This application has the limitation that it only supports one call
' at a time. But Tapi 3.0 has support for multiple calls per address,
' and the number of calls per address is dictated actually by the
' provider. (e.g. Unimodem would allow only 1 call per address at a time,
' while h323.tsp and ipconf.tsp practically allow any number of calls
' simultaneously on the same address.)
'
' This application does not handle incoming calls.
'

Option Explicit

Enum TestError
    'TErr_NotInitialized = 0
    TErr_Ok = 1
    TErr_Fail = 2
End Enum

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

Dim gobjCall As ITBasicCallControl
Dim gnPreviousAddressIndex As Long
Dim gobjOrigAddress As ITAddress
Dim WithEvents gobjTapiWithEvents As TAPI
Attribute gobjTapiWithEvents.VB_VarHelpID = -1
Dim gobjTapi As TAPI

Private Sub Form_Load()
    
    gnPreviousAddressIndex = 0  'valid indexes are between 1 and addresses count
    
    'populate combo box with names of address types
    'attach to each combo item the address type itself
    
    cmbAddressTypes.AddItem ("Phone Number")
    cmbAddressTypes.ItemData(cmbAddressTypes.NewIndex) = LINEADDRESSTYPE_PHONENUMBER
    
    cmbAddressTypes.AddItem ("Machine Name")
    cmbAddressTypes.ItemData(cmbAddressTypes.NewIndex) = LINEADDRESSTYPE_DOMAINNAME
    
    cmbAddressTypes.AddItem ("IP Address")
    cmbAddressTypes.ItemData(cmbAddressTypes.NewIndex) = LINEADDRESSTYPE_IPADDRESS
    
    'set selection on 1st item
    cmbAddressTypes.ListIndex = 0

End Sub

Private Sub Form_Unload(Cancel As Integer)

'catch all tapi errors but ignore them, since we want to shut down anyway
'but at the same time we want to attempt all possible cleanup
On Error Resume Next
    
    'release all global variables
    
    Set gobjCall = Nothing
    Call CheckError("Releasing gobjCall")
    
    Set gobjOrigAddress = Nothing
    Call CheckError("Releasing gobjOrigAddress")
    
    Set gobjTapiWithEvents = Nothing
    Call CheckError("Releasing gobjTapiWithEvents")
    
    If Not (gobjTapi Is Nothing) Then
        Call gobjTapi.Shutdown
        Call CheckError("Calling gobjTapi.Shutdown")
    End If
    
    Set gobjTapi = Nothing
    Call CheckError("Releasing gobjTapi")
    
    'empty combo box
    Dim i
    For i = 1 To cmbAddressTypes.ListCount
        cmbAddressTypes.RemoveItem (0)
    Next i
End Sub

Private Sub PrintCallState(State As CALL_STATE)
    Select Case State
        Case CS_CONNECTED
            lblStatus.Caption = "call state: CS_CONNECTED"
        Case CS_DISCONNECTED
            Dim strMsg
            strMsg = "call state: CS_DISCONNECTED"
            strMsg = strMsg & Chr(13) & "Call was disconnected. "
            strMsg = strMsg & "Now you can press Dial again or just quit."
            lblStatus.Caption = strMsg
        Case CS_HOLD
            lblStatus.Caption = "call state: CS_HOLD"
        Case CS_IDLE
            lblStatus.Caption = "call state: CS_IDLE"
        Case CS_INPROGRESS
            lblStatus.Caption = "call state: CS_INPROGRESS"
        Case CS_OFFERING
            lblStatus.Caption = "call state: CS_OFFERING"
        Case CS_QUEUED
            lblStatus.Caption = "call state: CS_QUEUED"
        Case Else
            lblStatus.Caption = "call state: unknown!!"
    End Select
End Sub

Private Sub gobjTapiWithEvents_Event( _
    ByVal TapiEvent As TAPI3Lib.TAPI_EVENT, ByVal pEvent As Object)
    
On Error Resume Next

    Dim nResult As Long
    Dim objCallStateEvent As ITCallStateEvent
    
    If TapiEvent <> TE_CALLSTATE Then
        'we are interested only in call state events
        'lblStatus.Caption = "TapiEvent <> TE_CALLSTATE ignored."
        Exit Sub
    End If
    
    'pEvent is an "Unknown" object; query its ITCallStateEvent interface
    Set objCallStateEvent = pEvent
    nResult = CheckError("gobjTapiWithEvents_Event: Set objCallStateEvent = pEvent")
    If nResult <> NO_ERROR Then Exit Sub
    
    Dim nCallState As CALL_STATE
    
    nCallState = objCallStateEvent.State
    nResult = CheckError("gobjTapiWithEvents_Event: objCallStateEvent.State")
    If nResult <> NO_ERROR Then Exit Sub
    
    PrintCallState (nCallState)
    
    '
    'test for special call states: connected & disconnected
    '
    
    If nCallState = CS_CONNECTED Then
        
        'Make visible all video windows from the call
        Dim objITCallInfoTmp As ITCallInfo
        
        Set objITCallInfoTmp = objCallStateEvent.Call
        nResult = CheckError("gobjTapiWithEvents_Event: objCallStateEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub
        
        Call ShowVideoWindowTerminals(objITCallInfoTmp)
        
        Set objITCallInfoTmp = Nothing
        Call CheckError("Releasing objITCallInfoTmp")
        
        Set objCallStateEvent = Nothing
        Call CheckError("Releasing objCallStateEvent")
        
        Exit Sub
        
    End If
    
    If nCallState = CS_DISCONNECTED Then
        
        'release call, you don't need it anymore
        Set gobjCall = Nothing
        Call CheckError("Releasing gobjCall")
        
        'disable Disconnect button, from now on there is no call to disconnect.
        pbDisconnect(1).Enabled = False
        
        'enable Dial button, from now on we should allow the user to place a new call.
        pbDial(0).Enabled = True
        
        Set objCallStateEvent = Nothing
        Call CheckError("Releasing objCallStateEvent")
        
        Exit Sub
        
    End If
    
    'release all objects that aren't needed anymore
    
    Set objCallStateEvent = Nothing
    Call CheckError("Releasing objCallStateEvent")
    
    Exit Sub
End Sub

Private Sub pbDial_Click(index As Integer)
    
On Error Resume Next

    Dim nResult As Long
    Dim bVideoIn As Boolean, bVideoOut As Boolean
    
    Dim objTerminalAudioIn As ITTerminal, objTerminalAudioOut As ITTerminal
    Dim objTerminalVideoIn As ITTerminal, objTerminalVideoOut As ITTerminal
    
    Dim nOrigAddressIndex As Long
    Dim strDestAddress As String
    
    'erase old messages
    lblStatus.Caption = "Dialing..."
    lblStatus.Refresh
    
    'second call not supported by this app
    If Not (gobjCall Is Nothing) Then
        lblStatus.Caption = "Cannot connect new call. Wait for the previous one to be disconnected."
        Exit Sub
    End If
    
    'check if user typed input data
    strDestAddress = txtDestAddress.Text
    If strDestAddress = "" Then
        lblStatus.Caption = "Enter destination addres!"
        Exit Sub
    End If
    
    'global variables might already contain something, from previous run
    
    If gobjTapi Is Nothing Then
    
        'create the Tapi object
        Set gobjTapi = CreateObject("TAPI.TAPI.1")
        nResult = CheckError("pbDial_Click: CreateObject(TAPI.TAPI.1)")
        If nResult <> NO_ERROR Then
            lblStatus.Caption = "Fatal error - initializing TAPI failed! Quit the app and try again."
            lblStatus.Refresh
            Exit Sub
        End If
        
        'call Initialize.  this must be called before
        'any other tapi functions are called.
        Call gobjTapi.Initialize
        nResult = CheckError("pbDial_Click: gobjTapi.Initialize")
        If nResult <> NO_ERROR Then
            lblStatus.Caption = "Fatal error - initializing TAPI failed! Quit the app and try again."
            lblStatus.Refresh
            Exit Sub
        End If
        
        'set the EventFilter to accept all defined tapi events
        gobjTapi.EventFilter = TAPI3_ALL_TAPI_EVENTS
        nResult = CheckError("pbDial_Click: setting EventFilter")
        If nResult <> NO_ERROR Then
            lblStatus.Caption = "Fatal error - initializing TAPI failed! Quit the app and try again."
            lblStatus.Refresh
            Exit Sub
        End If
        
        'register the outgoing interface that will receive the events
        Set gobjTapiWithEvents = gobjTapi
        nResult = CheckError("pbDial_Click: registering for receiving events")
        If nResult <> NO_ERROR Then
            lblStatus.Caption = "Fatal error - initializing TAPI failed! Quit the app and try again."
            lblStatus.Refresh
            Exit Sub
        End If
    End If
    
    'pick up the collection of Address objects
    Dim objCollAddresses As ITCollection
    
    Set objCollAddresses = gobjTapi.Addresses
    nResult = CheckError("pbDial_Click: gobjTapi.Addresses")
    If nResult <> NO_ERROR Then
        lblStatus.Caption = "Can't dial - enumerating TAPI addresses failed!"
        lblStatus.Refresh
        Exit Sub
    End If
    
    'find address that supports the desired type (the one selected in combo)
    nOrigAddressIndex = FindOriginationAddressIndex(objCollAddresses)
    
    'validate the returned value
    If nOrigAddressIndex < 1 Or nOrigAddressIndex > objCollAddresses.Count Then
        lblStatus.Caption = "Could not find an appropriate address to make the call from."
        lblStatus.Refresh
        
        'release not needed objects
        Set objCollAddresses = Nothing
        Call CheckError("Releasing objCollAddresses")
        
        Exit Sub
    End If
    
    '
    'pick up the found address
    '
    
    If gnPreviousAddressIndex <> nOrigAddressIndex Then
        'If another address was selected, release the previous one
        'and save a "pointer" to the new one.
        'If the same address was selected, don't release/save it again,
        'just keep the previous one.
        
        'release previous objects
        Set gobjOrigAddress = Nothing
        Call CheckError("Releasing gobjOrigAddress ")
        
        'save new address
        Set gobjOrigAddress = objCollAddresses.Item(nOrigAddressIndex)
        nResult = CheckError("pbDial_Click: objCollAddresses.Item(" & nOrigAddressIndex & ")")
        If nResult <> NO_ERROR Then
            lblStatus.Caption = "Can't dial - can't fetch the desired address!"
            lblStatus.Refresh
            
            gnPreviousAddressIndex = 0
            Exit Sub
        End If
        
        'save also the new index
        gnPreviousAddressIndex = nOrigAddressIndex
    End If
    
    'release objects that are not needed anymore
    '(this decrements the reference count)
    Set objCollAddresses = Nothing
    Call CheckError("Releasing objCollAddresses ")
    
    '
    'find out if media types video in/out are supported as well
    '
    
    Dim objMediaSupport As ITMediaSupport
    
    'query ITMediaSupport interface from Address object
    Set objMediaSupport = gobjOrigAddress
    Call CheckError("pbDial_Click: Set objMediaSupport = gobjOrigAddress")
    
    'find out if video is supported
    bVideoIn = False
    bVideoOut = False
    
    If Not (objMediaSupport Is Nothing) Then
        If objMediaSupport.QueryMediaType(TAPIMEDIATYPE_VIDEO) Then
            'video "in" is supported for sure (render, window terminal)
            bVideoIn = True
        End If
    End If
    
    'query ITTerminalSupport from Address object
    Dim objTerminalSupport As ITTerminalSupport
    
    Set objTerminalSupport = gobjOrigAddress
    Call CheckError("pbDial_Click: Set objTerminalSupport = gobjOrigAddress")
    
    If Not (objMediaSupport Is Nothing) Then
        If objMediaSupport.QueryMediaType(TAPIMEDIATYPE_VIDEO) Then
        
            'now let's find out if video "out" is also supported
            '(capture, static terminal "camera")
        
            'Null terminals (value = "Nothing") are not valid choices, so refuse them:
            'if GetDefaultStaticTerminal for video + capture returns a null terminal,
            'it means that there is no static terminal for video out,
            'which is equivalent to saying that video out is not supported
            'on this address. In this case, GetDefaultStaticTerminal will also raise
            'an exception, so use "On Error Resume Next" to deal with it,
            'we'll catch the error but ignore it (Err.clear), and look only at the returned
            'value (objTerminalVideoOut) instead
            
            Set objTerminalVideoOut = objTerminalSupport.GetDefaultStaticTerminal( _
                TAPIMEDIATYPE_VIDEO, TD_CAPTURE)
            Err.Clear
                        
            If Not (objTerminalVideoOut Is Nothing) Then
                bVideoOut = True
            End If
            
            'now that we found out if "video out" is supported, we can
            'release the terminal; we don't actually need it here.
            Set objTerminalVideoOut = Nothing
            Call CheckError("Releasing objTerminalVideoOut ")
            
        End If
    End If
    
    'release not needed objects
    Set objMediaSupport = Nothing
    Call CheckError("Releasing objMediaSupport ")
   
    '
    'pick up the default terminal for each media type (except for VideoIn, which
    'needs a dynamic "video window" terminal to be created)
    '
    
    Set objTerminalAudioIn = objTerminalSupport.GetDefaultStaticTerminal( _
        TAPIMEDIATYPE_AUDIO, TD_RENDER)
    Call CheckError("pbDial_Click: objTerminalSupport.GetDefaultStaticTerminal(audio render)")
        
    Set objTerminalAudioOut = objTerminalSupport.GetDefaultStaticTerminal( _
        TAPIMEDIATYPE_AUDIO, TD_CAPTURE)
    Call CheckError("pbDial_Click: objTerminalSupport.GetDefaultStaticTerminal(audio capture)")
    
    If bVideoIn = True Then
        Set objTerminalVideoIn = objTerminalSupport.CreateTerminal( _
            CLSID_String_VideoWindowTerm, TAPIMEDIATYPE_VIDEO, TD_RENDER)
        Call CheckError("pbDial_Click: objTerminalSupport.CreateTerminal(video render)")
    End If
    If bVideoOut = True Then
        Set objTerminalVideoOut = objTerminalSupport.GetDefaultStaticTerminal( _
            TAPIMEDIATYPE_VIDEO, TD_CAPTURE)
        Call CheckError("pbDial_Click: objTerminalSupport.GetDefaultStaticTerminal(video capture)")
    End If
    
    Set objTerminalSupport = Nothing
    Call CheckError("Releasing objTerminalSupport ")
    
    '
    'retrieve from combo box the type of the selected address type
    '
    Dim nSelectedType As Long
    nSelectedType = cmbAddressTypes.ItemData(cmbAddressTypes.ListIndex)
    
    '
    'create the call
    '
    
    Dim lMediaTypes As Long
    lMediaTypes = IIf((bVideoIn = True Or bVideoOut = True), _
        TAPIMEDIATYPE_AUDIO Or TAPIMEDIATYPE_VIDEO, TAPIMEDIATYPE_AUDIO)
        
    Set gobjCall = gobjOrigAddress.CreateCall(strDestAddress, nSelectedType, lMediaTypes)
    nResult = CheckError("pbDial_Click: gobjOrigAddress.CreateCall")
    If nResult <> NO_ERROR Then
        lblStatus.Caption = "Can't dial - failed to create the call!"
        lblStatus.Refresh
        Exit Sub
    End If
    
    'enable Disconnect button, because now we have a call that can be disconnected.
    pbDisconnect(1).Enabled = True
        
    'disable Dial button, we should prevent the user from placing a new call until this one is disconnected.
    pbDial(0).Enabled = False
    
    '
    'select on the call all the terminals
    '
        
    Dim vbCollTerminals As Collection
    Set vbCollTerminals = New Collection
    
    If Not (objTerminalAudioIn Is Nothing) Then
        Call vbCollTerminals.Add(objTerminalAudioIn)
    End If
    If Not (objTerminalAudioOut Is Nothing) Then
        Call vbCollTerminals.Add(objTerminalAudioOut)
    End If
    If Not (objTerminalVideoIn Is Nothing) Then
        Call vbCollTerminals.Add(objTerminalVideoIn)
    End If
    If Not (objTerminalVideoOut Is Nothing) Then
        Call vbCollTerminals.Add(objTerminalVideoOut)
    End If
    
    Call SelectTerminalsOnStreams(gobjCall, vbCollTerminals)
    
    Dim nIndex As Long, nCount As Long
    nCount = vbCollTerminals.Count
    For nIndex = 1 To nCount
        vbCollTerminals.Remove (1)
    Next nIndex
    Set vbCollTerminals = Nothing
    Call CheckError("Releasing vbCollTerminals ")
    
    'release the terminals
    Set objTerminalAudioIn = Nothing
    Call CheckError("Releasing objTerminalAudioIn ")
    
    Set objTerminalAudioOut = Nothing
    Call CheckError("Releasing objTerminalAudioOut ")
    
    Set objTerminalVideoIn = Nothing
    Call CheckError("Releasing objTerminalVideoIn ")
    
    Set objTerminalVideoOut = Nothing
    Call CheckError("Releasing objTerminalVideoOut ")
    
    '
    'Connect the call; False means that the call is made asynchronously.
    'The call to Connect will return immediately, before the call
    'gets to "connected" state; events will fire each time the
    'state of the call changes (to "connected", "disconnected"),
    'meanwhile the application can go on.
    '
    gobjCall.Connect (False)
    If Err.Number <> 0 Then
        Err.Clear
        lblStatus.Caption = "Connect failed."
        
        'don't need this failed call anymore
        Set gobjCall = Nothing
        Call CheckError("Releasing gobjCall ")
        
        'disable Disconnect button, from now on there is no call to disconnect.
        pbDisconnect(1).Enabled = False
        
        'enable Dial button, from now on we should allow the user to place a new call.
        pbDial(0).Enabled = True
        
    End If
    
End Sub

Private Sub pbDisconnect_Click(index As Integer)
On Error Resume Next

    If gobjCall Is Nothing Then
        lblStatus.Caption = "There is no call to be disconnected."
        Exit Sub
    End If
    
    Call gobjCall.Disconnect(DC_NORMAL)
    Call CheckError("pbDisconnect_Click: gobjCall.Disconnect")
    
End Sub

'Search through all addresses and return the index of the one that matches
'the address type selected in the combo box with address types. Also, the
'found address must support at least the media type "audio".
'Return 0 if no address found. Otherwise return its index, which will be
'between 1 and Addresses.Count
Private Function FindOriginationAddressIndex(objCollAddresses As ITCollection) As Long
On Error Resume Next

    Dim nResult As Long
    Dim nSelectedType As Long
    Dim indexAddr As Long
    Dim objCrtAddress As ITAddress
    Dim lAddrTypes As Long
    Dim objMediaSupport As ITMediaSupport
    Dim objAddressCapabilities As ITAddressCapabilities
    Dim bFound As Boolean
    
    'prepare return value
    FindOriginationAddressIndex = 0
    
    '
    'retrieve from combo box the type of the selected address type
    '
    nSelectedType = cmbAddressTypes.ItemData(cmbAddressTypes.ListIndex)
    
    '
    'search through all addresses the first one that matches this type
    'and also supports at least the media types "audio in" and "audio out"
    '
    bFound = False
    
    For indexAddr = 1 To objCollAddresses.Count
        
        nResult = CheckError("FindOriginationAddressIndex: objCollAddresses.Count")
        If nResult <> NO_ERROR Then Exit Function
        
        Set objCrtAddress = objCollAddresses.Item(indexAddr)
        nResult = CheckError("FindOriginationAddressIndex: objCollAddresses.Item(" & "indexAddr" & ")")
        If nResult <> NO_ERROR Then Exit Function
        
        Set objMediaSupport = objCrtAddress
        nResult = CheckError("FindOriginationAddressIndex: Set objMediaSupport = objCrtAddress")
        If nResult <> NO_ERROR Then Exit Function
        
        Set objAddressCapabilities = objCrtAddress
        nResult = CheckError("FindOriginationAddressIndex: Set objAddressCapabilities = objCrtAddress")
        If nResult <> NO_ERROR Then Exit Function
        
        'Note: ignore the addresses exposed by the following 2 providers:
        ' - "kmddsp.tsp" = "TAPI Kernel-Mode Service Provider"
        ' - "ndptsp.tsp" = "NDIS Proxy TAPI Service Provider"
        'because they might be found instead of the modem address,
        'and this sample wants to use the modem for phone calls.
        
        If objMediaSupport.QueryMediaType(TAPIMEDIATYPE_AUDIO) And _
            objCrtAddress.ServiceProviderName <> "kmddsp.tsp" And _
            objCrtAddress.ServiceProviderName <> "ndptsp.tsp" Then
            
            nResult = CheckError("FindOriginationAddressIndex: objCrtAddress.ServiceProviderName")
            If nResult <> NO_ERROR Then Exit Function
            
            lAddrTypes = objAddressCapabilities.AddressCapability(AC_ADDRESSTYPES)
            nResult = CheckError("FindOriginationAddressIndex: objAddressCapabilities.AddressCapability(AC_ADDRESSTYPES)")
            If nResult <> NO_ERROR Then Exit Function
            
            'perform a bitwise "And"
            If lAddrTypes And nSelectedType Then
            
                'This address might be a datamodem or a voice modem
                'or an H323 address. Datamodems are not interesting for
                'our sample, because they wouldn't be able to do streaming
                '(they don't expose the terminals microphone and speakers);
                'therefore let's skip it if it's a datamodem; it is a datamodem
                'address if it doesn't support the interface ITTerminalSupport,
                'it will throw an exception when we try to query for this interface.
                
                Dim objITTerminalSupport As ITTerminalSupport
                
                Set objITTerminalSupport = objCrtAddress
                Err.Clear   'ignore the exception, we need to continue the loop regardless
                
                If Not (objITTerminalSupport Is Nothing) Then
                    bFound = True
                End If
                
                Set objITTerminalSupport = Nothing
                Call CheckError("Releasing objITTerminalSupport ")
                
            End If
            
        End If
        
        Set objAddressCapabilities = Nothing
        Call CheckError("Releasing objAddressCapabilities ")
        
        Set objMediaSupport = Nothing
        Call CheckError("Releasing objMediaSupport ")
        
        Set objCrtAddress = Nothing
        Call CheckError("Releasing objCrtAddress ")
        
        If bFound = True Then Exit For
    Next indexAddr
    
    '
    'return the index of the found address, or 0 if no address found
    '
    If bFound = True Then
        FindOriginationAddressIndex = indexAddr
    Else
        FindOriginationAddressIndex = 0
    End If
    
End Function

'
'This function finds all video windows terminals selected on the call
'and makes them visible.
'
Private Sub ShowVideoWindowTerminals(objCallInfo As ITCallInfo)
On Error Resume Next
    
    Dim objVBCollTerminals As Collection
    Dim objCrtTerminal As ITTerminal
    Dim nCount As Long, nIndex As Long
    Dim objVideoWindow As IVideoWindow
    
    Call Call_GetTerminalsInUse(objCallInfo, objVBCollTerminals)
    
    'if Call_GetTerminalsInUse fails, it returns a "Null" collection.
    If (objVBCollTerminals Is Nothing) Then
        'there is nothing to be "shown"
        Exit Sub
    End If
    
    nCount = objVBCollTerminals.Count
    
    'find all "Video Window" terminals and set their property AutoShow on True;
    'this property is member in IVideoWindow interface
    For nIndex = 1 To nCount
        
        Set objCrtTerminal = objVBCollTerminals.Item(nIndex)
        
        Dim guidCrtTerminalClass
        guidCrtTerminalClass = objCrtTerminal.TerminalClass
        Call CheckError("ShowVideoWindowTerminals: objCrtTerminal.TerminalClass")
        
        '
        'video window terminals
        '
        If guidCrtTerminalClass = CLSID_String_VideoWindowTerm Then
            'query the IVideoWindow interface and set property AutoShow on True
            
            Set objVideoWindow = objCrtTerminal
            Call CheckError("ShowVideoWindowTerminals: Set objVideoWindow = objCrtTerminal")
            
            '
            '  Set the AutoShow member to true
            '
            '  Note that the visibility property is the only one
            '  we can use on this terminal's IVideoWindow
            '  interface before the CME_STREAM_ACTIVE
            '  event is received for the stream. All other methods
            '  will fail until CME_STREAM_ACTIVE has been sent.
            '  Applications that need to control more about a video
            '  window than just its visibility must listen for the
            '  CME_STREAM_ACTIVE event.
            '
            
            If Not (objVideoWindow Is Nothing) Then
                objVideoWindow.AutoShow = True
                Call CheckError("ShowVideoWindowTerminals: setting objVideoWindow.AutoShow")
                
                Set objVideoWindow = Nothing
                Call CheckError("Releasing objVideoWindow ")
                
            End If
        End If
        
        'release terminal (decrement reference count)
        Set objCrtTerminal = Nothing
        Call CheckError("Releasing objCrtTerminal ")
        
    Next nIndex
    
    'release collection
    Set objVBCollTerminals = Nothing
    Call CheckError("Releasing objVBCollTerminals ")
    
End Sub

'
'This function builds and returns a collection with all the ITTerminal objects
'found on all the streams and substreams of the given objITBCC (call object).
'
'It only returns a valid (non null) collection if it encounters no errors;
'if any error is encountered, TErr_Fail is returned, with a "Nothing" rcollTerminals;
'(all previously terminals added in the collection are removed, and the collection
'is released).
'
Public Function Call_GetTerminalsInUse( _
    objITBCC As ITBasicCallControl, _
    ByRef rcollTerminals As Collection) _
    As TestError
On Error Resume Next

    Dim MyError As TestError
    Call_GetTerminalsInUse = TErr_Ok
    
    'initialize return value
    Set rcollTerminals = New Collection
    
    'get stream control from call object
    Dim objITStreamControl As ITStreamControl
    
    Set objITStreamControl = objITBCC
    
    'get all terminals from this stream control (streams + substreams)
    If Not (objITStreamControl Is Nothing) Then
        
        MyError = StreamControl_AddTerminals(objITStreamControl, rcollTerminals)
        If MyError = TErr_Fail Then
            Set objITStreamControl = Nothing
            Call CheckError("Releasing objITStreamControl ")
            
            Dim nIndex
            For nIndex = 1 To rcollTerminals.Count
                rcollTerminals.Remove (1)
            Next nIndex
            
            Set rcollTerminals = Nothing
            Call CheckError("Releasing rcollTerminals ")
            
            Call_GetTerminalsInUse = TErr_Fail
            Exit Function
        End If
    End If
    
    'release not needed objects
    Set objITStreamControl = Nothing
    Call CheckError("Releasing objITStreamControl ")
    
    Exit Function
End Function

'
'This function enumerates each stream from StreamControl object and:
' - ask it to add its terminals to the collection
' - check if it has SubStream control; if it does, then it asks the SubStreamControl
'object to add its terminals into the same collection
'
'If an error is encountered, the function terminates immediately and returns, without
'removing the terminals that it had already added in the collection.
'
Private Function StreamControl_AddTerminals( _
    objITStreamControl As ITStreamControl, _
    collTerminals As Collection) _
    As TestError
On Error Resume Next

    Dim MyError As TestError
    StreamControl_AddTerminals = TErr_Ok
    
    'get stream collection from stream control
    Dim objITCollStreams As ITCollection
    
    Set objITCollStreams = objITStreamControl.Streams
    If Err.Number <> 0 Then
        Err.Clear
        
        StreamControl_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'go through every stream (and their substreams) and get all terminals;
    'add all terminals in the same collection
    
    Dim nCount As Long, nIndex As Long
    
    nCount = objITCollStreams.Count
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITCollStreams = Nothing
        Call CheckError("Releasing objITCollStreams ")
        
        StreamControl_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    Dim objCrtStream As ITStream
    
    For nIndex = 1 To nCount
        
        'get next stream
        Set objCrtStream = objITCollStreams.Item(nIndex)
        If Err.Number <> 0 Then
            Err.Clear
            
            Set objITCollStreams = Nothing
            Call CheckError("Releasing objITCollStreams ")
            
            StreamControl_AddTerminals = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        'ask stream to add its terminals in our collection
        MyError = Stream_AddTerminals(objCrtStream, collTerminals)
        If MyError = TErr_Fail Then
            
            Set objITCollStreams = Nothing
            Call CheckError("Releasing objITCollStreams ")
            
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
                
            StreamControl_AddTerminals = TErr_Fail
            Exit Function
        End If
        
        'if stream has substreams, add terminals from substreams too.
        
        Dim objNextITSubStreamControl As ITSubStreamControl
        
        Set objNextITSubStreamControl = objCrtStream
        Err.Clear   'this might fail; but I'll catch this by testing the returned interface ITSubStreamControl.
        
        If Not (objNextITSubStreamControl Is Nothing) Then
            MyError = SubStreamControl_AddTerminals( _
                objNextITSubStreamControl, collTerminals)
            If MyError = TErr_Fail Then
                
                Set objITCollStreams = Nothing
                Call CheckError("Releasing objITCollStreams ")
                
                Set objCrtStream = Nothing
                Call CheckError("Releasing objCrtStream ")
                
                Set objNextITSubStreamControl = Nothing
                Call CheckError("Releasing objNextITSubStreamControl ")
                    
                StreamControl_AddTerminals = TErr_Fail
                Exit Function
            End If
            
        End If
        
        Set objNextITSubStreamControl = Nothing
        Call CheckError("Releasing objNextITSubStreamControl ")
        
        'release current stream
        Set objCrtStream = Nothing
        Call CheckError("Releasing objCrtStream ")
        
    Next nIndex
    
    'release not needed objects
    Set objITCollStreams = Nothing
    Call CheckError("Releasing objITCollStreams ")
    
    Exit Function
End Function

'
'This function puts in the given collection all terminals that it finds on objITStream;
'(note: it does NOT go on substreams!)
'Before adding a terminal, it checks if the terminal is already in the collection;
'if it is, it doesn't add it any more.
'
'Note: the same terminal could be found twice on 2 different streams or substreams.
'
'If an error is encountered, the function terminates immediately and returns, without
'removing the terminals that it had already added in the collection.
'
Private Function Stream_AddTerminals( _
    objITStream As ITStream, _
    collTerminals As Collection) _
    As TestError
On Error Resume Next

    Dim MyError As TestError
    Stream_AddTerminals = TErr_Ok
    
    'get collection of terminals from stream
    
    Dim objITCollTerminals As ITCollection
    
    Set objITCollTerminals = objITStream.Terminals
    If Err.Number <> 0 Then
        Err.Clear
        
        Stream_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'add each terminal in the received collection, if it's not already there.
    
    Dim nIndex As Long, nCount As Long
    Dim objCrtTerminal As ITTerminal
    
    nCount = objITCollTerminals.Count
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITCollTerminals = Nothing
        Call CheckError("Releasing objITCollTerminals ")
        
        Stream_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
        
    For nIndex = 1 To nCount
        
        'get next terminal
        Set objCrtTerminal = objITCollTerminals.Item(nIndex)
        If Err.Number <> 0 Then
            Err.Clear
            
            Set objITCollTerminals = Nothing
            Call CheckError("Releasing objITCollTerminals ")
            
            Stream_AddTerminals = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        'check if it is already added in the received collection
        Dim objExistingTerminal As ITTerminal
        Dim bFound As Boolean
        
        bFound = False
        For Each objExistingTerminal In collTerminals
            If objCrtTerminal Is objExistingTerminal Then
                bFound = True
                Exit For
            End If
        Next objExistingTerminal
        
        'if terminal is not found, add it in the collection
        If bFound = False Then
            Call collTerminals.Add(objCrtTerminal)
        End If
        
        Set objCrtTerminal = Nothing
        Call CheckError("Releasing objCrtTerminal ")
        
    Next nIndex
            
    Set objITCollTerminals = Nothing
    Call CheckError("Releasing objITCollTerminals ")
    
    Exit Function
End Function

'
'This function enumerates each substream from SubStreamControl object and:
' - ask it to add its terminals to the collection
' - check if it has SubStream control; if it does, then it asks the SubStreamControl
'object to add its terminals into the same collection
'
'If an error is encountered, the function terminates immediately and returns, without
'removing the terminals that it had already added in the collection.
'
Private Function SubStreamControl_AddTerminals( _
    objITSubStreamControl As ITSubStreamControl, _
    collTerminals As Collection) _
    As TestError
On Error Resume Next

    Dim MyError As TestError
    SubStreamControl_AddTerminals = TErr_Ok
    
    'get substream collection from substream control
    Dim objITCollSubStreams As ITCollection
    
    Set objITCollSubStreams = objITSubStreamControl.SubStreams
    If Err.Number <> 0 Then
        Err.Clear
        
        SubStreamControl_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'go through every substream (and their substreams) and get all terminals;
    'add all terminals in the same collection
    
    Dim nCount As Long, nIndex As Long
    
    nCount = objITCollSubStreams.Count
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITCollSubStreams = Nothing
        Call CheckError("Releasing objITCollSubStreams ")
        
        SubStreamControl_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    Dim objCrtSubStream As ITSubStream
    
    For nIndex = 1 To nCount
        
        'get next substream
        Set objCrtSubStream = objITCollSubStreams.Item(nIndex)
        If Err.Number <> 0 Then
            Err.Clear
            
            Set objITCollSubStreams = Nothing
            Call CheckError("Releasing objITCollSubStreams ")
            
            SubStreamControl_AddTerminals = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        'ask substream to add its terminals in our collection
        MyError = SubStream_AddTerminals(objCrtSubStream, collTerminals)
        If MyError = TErr_Fail Then
        
            Set objITCollSubStreams = Nothing
            Call CheckError("Releasing objITCollSubStreams ")
            
            Set objCrtSubStream = Nothing
            Call CheckError("Releasing objCrtSubStream ")
                
            SubStreamControl_AddTerminals = TErr_Fail
            Exit Function
        End If
        
        'if substream has substreams, add terminals from substreams too.
        
        Dim objNextITSubStreamControl As ITSubStreamControl
        
        Set objNextITSubStreamControl = objCrtSubStream
        Err.Clear   'this might fail; but I'll catch this by testing the returned interface ITSubStreamControl.
        
        If Not (objNextITSubStreamControl Is Nothing) Then
            'attn: this is a recursive call; but it probably won't ever happen
            'so far we don't have substreams that have substreams of their own'
            'we only have streams that have substreams, just 2 levels.
            MyError = SubStreamControl_AddTerminals( _
                objNextITSubStreamControl, collTerminals)
            If MyError = TErr_Fail Then
                
                Set objITCollSubStreams = Nothing
                Call CheckError("Releasing objITCollSubStreams ")
                
                Set objCrtSubStream = Nothing
                Call CheckError("Releasing objCrtSubStream ")
                
                Set objNextITSubStreamControl = Nothing
                Call CheckError("Releasing objNextITSubStreamControl ")
                    
                SubStreamControl_AddTerminals = TErr_Fail
                Exit Function
            End If
            
        End If
        
        Set objNextITSubStreamControl = Nothing
        Call CheckError("Releasing objNextITSubStreamControl ")
        
        'release current substream
        Set objCrtSubStream = Nothing
        Call CheckError("Releasing objCrtSubStream ")
        
    Next nIndex
    
    'release not needed objects
    Set objITCollSubStreams = Nothing
    Call CheckError("Releasing objITCollSubStreams ")
    
    Exit Function
End Function

'
'This function puts in the given collection all terminals that it finds on objITSubStream;
'(note: it does NOT go on substreams!)
'Before adding a terminal, it checks if the terminal is already in the collection;
'if it is, it doesn't add it any more.
'
'Note: the same terminal could be found twice on 2 different streams or substreams.
'
'If an error is encountered, the function terminates immediately and returns, without
'removing the terminals that it had already added in the collection.
'
Private Function SubStream_AddTerminals( _
    objITSubStream As ITSubStream, _
    collTerminals As Collection) _
    As TestError
On Error Resume Next

    Dim MyError As TestError
    SubStream_AddTerminals = TErr_Ok
    
    'get collection of terminals from substream
    
    Dim objITCollTerminals As ITCollection
    
    Set objITCollTerminals = objITSubStream.Terminals
    If Err.Number <> 0 Then
        Err.Clear
        
        SubStream_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'add each terminal in the received collection, if it's not already there.
    
    Dim nIndex As Long, nCount As Long
    Dim objCrtTerminal As ITTerminal
    
    nCount = objITCollTerminals.Count
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITCollTerminals = Nothing
        Call CheckError("Releasing objITCollTerminals ")
        
        SubStream_AddTerminals = TErr_Fail
        Exit Function
    End If
    Err.Clear
        
    For nIndex = 1 To nCount
        
        'get next terminal
        Set objCrtTerminal = objITCollTerminals.Item(nIndex)
        If Err.Number <> 0 Then
            Err.Clear
            
            Set objITCollTerminals = Nothing
            Call CheckError("Releasing objITCollTerminals ")
            
            SubStream_AddTerminals = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        'check if it is already added in the received collection
        Dim objExistingTerminal As ITTerminal
        Dim bFound As Boolean
        
        bFound = False
        For Each objExistingTerminal In collTerminals
            If objCrtTerminal Is objExistingTerminal Then
                bFound = True
                Exit For
            End If
        Next objExistingTerminal
        
        'if terminal is not found, add it in the collection
        If bFound = False Then
            Call collTerminals.Add(objCrtTerminal)
        End If
        
        Set objCrtTerminal = Nothing
        Call CheckError("Releasing objCrtTerminal ")
        
    Next nIndex
            
    Set objITCollTerminals = Nothing
    Call CheckError("Releasing objITCollTerminals ")
    
    Exit Function
End Function

'
'This function receives a call object and a (VB) collection with the terminals
'to be selected;
'- it first queries the stream control object from the call object;
'- it then selects each terminal on a stream that matches
'the media type and the terminal direction.
'
'It also ensures the "preview" feature: it creates a video window terminal
'and it selects it on the video+capture stream (if it finds such a stream).
'
'If an error is encountered, the function finishes right away and returns
'that error.
'
Public Function SelectTerminalsOnStreams( _
    ByVal objITBCC As ITBasicCallControl, _
    ByVal collTerminals As Collection) _
    As TestError
On Error Resume Next
    
    Dim MyError As TestError
    SelectTerminalsOnStreams = TErr_Ok
    
    Dim nTermIndex As Long
    
    'get stream control object
    
    Dim objITStreamControl As ITStreamControl
    
    Set objITStreamControl = objITBCC
    If Err.Number <> 0 Then
        Err.Clear
        
        SelectTerminalsOnStreams = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'get streams collection object
    
    Dim objITCollStreams As ITCollection
    
    Set objITCollStreams = objITStreamControl.Streams
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITStreamControl = Nothing
        Call CheckError("Releasing objITStreamControl ")
        
        SelectTerminalsOnStreams = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'find matching stream for each terminal and select the terminal
    
    Dim objCrtITStream As ITStream
    
    For nTermIndex = 1 To collTerminals.Count
        
        'find matching stream
        MyError = FindMatchingStream( _
            objITCollStreams, collTerminals.Item(nTermIndex), objCrtITStream)
        If MyError = TErr_Fail Then
            
            Set objITCollStreams = Nothing
            Call CheckError("Releasing objITCollStreams ")
            
            Set objITStreamControl = Nothing
            Call CheckError("Releasing objITStreamControl ")
        
            SelectTerminalsOnStreams = TErr_Fail
            Exit Function
        End If
        
        'select terminal
        Call objCrtITStream.SelectTerminal(collTerminals.Item(nTermIndex))
        If Err.Number <> 0 Then
            Err.Clear
        
            Set objCrtITStream = Nothing
            Call CheckError("Releasing objCrtITStream ")
            
            Set objITCollStreams = Nothing
            Call CheckError("Releasing objITCollStreams ")
            
            Set objITStreamControl = Nothing
            Call CheckError("Releasing objITStreamControl ")
        
            SelectTerminalsOnStreams = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        'release stream
        Set objCrtITStream = Nothing
        Call CheckError("Releasing objCrtITStream ")
        
    Next nTermIndex
    
    'select a "preview" window on the call
    MyError = SelectPreviewWindow(objITBCC, objITCollStreams)
    If MyError = TErr_Fail Then
        
        Set objITCollStreams = Nothing
        Call CheckError("Releasing objITCollStreams ")
        
        Set objITStreamControl = Nothing
        Call CheckError("Releasing objITStreamControl ")
    
        SelectTerminalsOnStreams = TErr_Fail
        Exit Function
    End If
    
    'release all not needed objects
    Set objITCollStreams = Nothing
    Call CheckError("Releasing objITCollStreams ")
    
    Set objITStreamControl = Nothing
    Call CheckError("Releasing objITStreamControl ")
    
    'done
    Exit Function
End Function

'
'This function searches in objITCollStreams the first stream that matches
'the "media type" and "direction" specified by objITTerminal;
'if it finds such a stream, it returns a reference to it;
'otherwise it returns "Nothing"
'
Private Function FindMatchingStream( _
    ByVal objITCollStreams As ITCollection, _
    ByVal objITTerminal As ITTerminal, _
    ByRef robjITStream As ITStream) _
    As TestError
On Error Resume Next
    
    FindMatchingStream = TErr_Ok
    
    'initialize return value
    Set robjITStream = Nothing
    
    'read media type and direction from terminal
    
    Dim lMediaType As Long, lDirection As TERMINAL_DIRECTION
    
    lMediaType = objITTerminal.MediaType
    If Err.Number <> 0 Then
        Err.Clear
        
        FindMatchingStream = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    lDirection = objITTerminal.Direction
    If Err.Number <> 0 Then
        Err.Clear
        
        FindMatchingStream = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'search stream that matches this media and direction
    
    Dim nCount As Long, nIndex As Long
    Dim objCrtStream As ITStream
    Dim lCrtMediaType As Long, lCrtDirection As TERMINAL_DIRECTION
    
    nCount = objITCollStreams.Count
    If Err.Number <> 0 Then
        Err.Clear
        
        FindMatchingStream = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    For nIndex = 1 To nCount
        
        Set objCrtStream = objITCollStreams.Item(nIndex)
        If Err.Number <> 0 Then
            Err.Clear
            
            FindMatchingStream = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        lCrtMediaType = objCrtStream.MediaType
        If Err.Number <> 0 Then
            Err.Clear
        
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
            
            FindMatchingStream = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        lCrtDirection = objCrtStream.Direction
        If Err.Number <> 0 Then
            Err.Clear
            
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
            
            FindMatchingStream = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        If lMediaType = lCrtMediaType And lDirection = lCrtDirection Then
            'set return value
            Set robjITStream = objCrtStream
            
            'quit loop, we're done
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
            Exit For
        End If
        
        Set objCrtStream = Nothing
        Call CheckError("Releasing objCrtStream ")
        
    Next nIndex
    
    Exit Function
End Function

'
'This function searches in objITCollStreams the first stream that matches
'the given "media type" and "direction";
'if it finds such a stream, it returns a reference to it;
'otherwise it returns "Nothing"
'
Private Function FindStream( _
    objITCollStreams As ITCollection, _
    lMediaType As Long, _
    lDirection As TERMINAL_DIRECTION, _
    ByRef robjITStream As ITStream) _
    As TestError
On Error Resume Next
    
    FindStream = TErr_Ok
    
    'initialize return value
    Set robjITStream = Nothing
    
    'search stream that matches this media and direction
    
    Dim nCount As Long, nIndex As Long
    Dim objCrtStream As ITStream
    Dim lCrtMediaType As Long, lCrtDirection As TERMINAL_DIRECTION
    
    nCount = objITCollStreams.Count
    If Err.Number <> 0 Then
        Err.Clear
        
        FindStream = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    For nIndex = 1 To nCount
        
        Set objCrtStream = objITCollStreams.Item(nIndex)
        If Err.Number <> 0 Then
            Err.Clear
            
            FindStream = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        lCrtMediaType = objCrtStream.MediaType
        If Err.Number <> 0 Then
            Err.Clear
        
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
            
            FindStream = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        lCrtDirection = objCrtStream.Direction
        If Err.Number <> 0 Then
            Err.Clear
            
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
            
            FindStream = TErr_Fail
            Exit Function
        End If
        Err.Clear
        
        If lMediaType = lCrtMediaType And lDirection = lCrtDirection Then
            'set return value
            Set robjITStream = objCrtStream
            
            'quit loop, we're done
            Set objCrtStream = Nothing
            Call CheckError("Releasing objCrtStream ")
            
            Exit For
        End If
        
        Set objCrtStream = Nothing
        Call CheckError("Releasing objCrtStream ")
        
    Next nIndex
    
    Exit Function
End Function

'
'This function searches the video capture stream and, if it finds it,
'it creates a video window terminal and selects it on the found stream.
'
Private Function SelectPreviewWindow( _
    objITBCC As ITBasicCallControl, _
    objITCollStreams As ITCollection) _
    As TestError
On Error Resume Next
    
    Dim MyError As TestError
    SelectPreviewWindow = TErr_Ok
    
    'create video window terminal
    
    Dim objVideoWindow As ITTerminal
    
    MyError = CreateVideoWindowTerminal(objITBCC, objVideoWindow)
    If MyError = TErr_Fail Then
        SelectPreviewWindow = TErr_Fail
        Exit Function
    End If
    
    'find video capture stream
    
    Dim objITStream As ITStream
    
    MyError = FindStream( _
        objITCollStreams, TAPIMEDIATYPE_VIDEO, TD_CAPTURE, objITStream)
    If MyError = TErr_Fail Then
    
        Set objVideoWindow = Nothing
        Call CheckError("Releasing objVideoWindow ")
    
        SelectPreviewWindow = TErr_Fail
        Exit Function
    End If
    
    'select video window terminal on the "video capture" stream
    Call objITStream.SelectTerminal(objVideoWindow)
    If Err.Number <> 0 Then
        Err.Clear
    
        Set objITStream = Nothing
        Call CheckError("Releasing objITStream ")
        
        Set objVideoWindow = Nothing
        Call CheckError("Releasing objVideoWindow ")
    
        SelectPreviewWindow = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'release objects not needed anymore
    
    Set objITStream = Nothing
    Call CheckError("Releasing objITStream ")
    
    Set objVideoWindow = Nothing
    Call CheckError("Releasing objVideoWindow ")

    Exit Function
End Function

'
'This function creates and returns a video window terminal.
'
Private Function CreateVideoWindowTerminal( _
    objITBCC As ITBasicCallControl, _
    ByRef rObjVideoWindowTerminal As ITTerminal) _
    As TestError
On Error Resume Next
    
    CreateVideoWindowTerminal = TErr_Ok
        
    'initialize return value
    Set rObjVideoWindowTerminal = Nothing
    
    'retrieve the call info interface, to get from it the address
    
    Dim objITCallInfo As ITCallInfo
    
    Set objITCallInfo = objITBCC
    If Err.Number <> 0 Then
        Err.Clear
        
        CreateVideoWindowTerminal = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'get the parent address
    
    Dim objITAddress As ITAddress
    
    Set objITAddress = objITCallInfo.Address
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITCallInfo = Nothing
        Call CheckError("Releasing objITCallInfo ")
        
        CreateVideoWindowTerminal = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'retrieve the ITTerminalSupport interface, that allows terminal creation
    
    Dim objITTerminalSupport As ITTerminalSupport
    
    Set objITTerminalSupport = objITAddress
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITAddress = Nothing
        Call CheckError("Releasing objITAddress ")
        
        Set objITCallInfo = Nothing
        Call CheckError("Releasing objITCallInfo ")
        
        CreateVideoWindowTerminal = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    'create the video window terminal
    
    Set rObjVideoWindowTerminal = objITTerminalSupport.CreateTerminal( _
        CLSID_String_VideoWindowTerm, TAPIMEDIATYPE_VIDEO, TD_RENDER)
    If Err.Number <> 0 Then
        Err.Clear
        
        Set objITTerminalSupport = Nothing
        Call CheckError("Releasing objITTerminalSupport ")
        
        Set objITAddress = Nothing
        Call CheckError("Releasing objITAddress ")
        
        Set objITCallInfo = Nothing
        Call CheckError("Releasing objITCallInfo ")
        
        CreateVideoWindowTerminal = TErr_Fail
        Exit Function
    End If
    Err.Clear
    
    '
    'release objects not needed anymore
    '
    
    'release the terminal support interface
    
    Set objITTerminalSupport = Nothing
    Call CheckError("Releasing objITTerminalSupport ")
    
    'release the address
    
    Set objITAddress = Nothing
    Call CheckError("Releasing objITAddress ")
    
    'release the call info interface
    
    Set objITCallInfo = Nothing
    Call CheckError("Releasing objITCallInfo ")
    
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
