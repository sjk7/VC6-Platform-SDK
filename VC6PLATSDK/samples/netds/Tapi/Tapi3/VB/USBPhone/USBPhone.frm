VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "USB Phone Sample"
   ClientHeight    =   8835
   ClientLeft      =   4920
   ClientTop       =   705
   ClientWidth     =   8190
   LinkTopic       =   "Form1"
   ScaleHeight     =   8835
   ScaleWidth      =   8190
   Begin VB.Frame fraManualControl 
      Caption         =   "Manual Control"
      Height          =   3375
      Left            =   4440
      TabIndex        =   23
      Top             =   2880
      Width           =   3495
      Begin VB.CommandButton cmdStopTone 
         Caption         =   "Stop Tone"
         Height          =   375
         Left            =   360
         TabIndex        =   16
         Top             =   2760
         Width           =   2655
      End
      Begin VB.CommandButton cmdRingBack 
         Caption         =   "Ring Back"
         Height          =   375
         Left            =   1680
         TabIndex        =   15
         Top             =   2280
         Width           =   1335
      End
      Begin VB.CommandButton cmdError 
         Caption         =   "Error"
         Height          =   375
         Left            =   360
         TabIndex        =   14
         Top             =   2280
         Width           =   1335
      End
      Begin VB.CommandButton cmdBusy 
         Caption         =   "Busy"
         Height          =   375
         Left            =   1680
         TabIndex        =   13
         Top             =   1920
         Width           =   1335
      End
      Begin VB.CommandButton cmdDialTone 
         Caption         =   "Dial Tone"
         Height          =   375
         Left            =   360
         TabIndex        =   12
         Top             =   1920
         Width           =   1335
      End
      Begin VB.CommandButton cmdStopRinger 
         Caption         =   "Stop Ringer"
         Height          =   375
         Left            =   360
         TabIndex        =   11
         Top             =   960
         Width           =   2655
      End
      Begin VB.CommandButton cmdStartRinger 
         Caption         =   "Start Ringer"
         Height          =   375
         Left            =   360
         TabIndex        =   10
         Top             =   600
         Width           =   2655
      End
   End
   Begin VB.CheckBox chkPhoneHandling 
      Caption         =   "Enable Phone Handling"
      Height          =   375
      Left            =   360
      TabIndex        =   1
      Top             =   2280
      Width           =   2295
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   3240
      TabIndex        =   17
      Top             =   8280
      Width           =   1695
   End
   Begin VB.Frame fraStatus 
      Caption         =   "Status"
      Height          =   1455
      Left            =   240
      TabIndex        =   0
      Top             =   6600
      Width           =   7695
      Begin VB.Label lblH323Info 
         Caption         =   "All calls are made and received on H323 line."
         Height          =   255
         Left            =   720
         TabIndex        =   22
         Top             =   240
         Width           =   5895
      End
      Begin VB.Label lblStatus 
         Height          =   615
         Left            =   720
         TabIndex        =   20
         Top             =   720
         Width           =   6735
      End
   End
   Begin VB.TextBox txtInfo 
      BackColor       =   &H80000004&
      Height          =   1455
      Left            =   360
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   2
      TabStop         =   0   'False
      Top             =   480
      Width           =   7455
   End
   Begin VB.Frame fraInfo 
      Caption         =   "Phone Information"
      Height          =   1815
      Left            =   240
      TabIndex        =   3
      Top             =   240
      Width           =   7695
   End
   Begin VB.Frame fraUsePhone 
      Caption         =   "Use USB Phone"
      Height          =   3375
      Left            =   240
      TabIndex        =   18
      Top             =   2880
      Width           =   3735
      Begin VB.CommandButton cmdAnswer 
         Caption         =   "Answer Call"
         Enabled         =   0   'False
         Height          =   375
         Left            =   240
         TabIndex        =   8
         Top             =   2760
         Width           =   1455
      End
      Begin VB.CommandButton cmdDisconnect 
         Caption         =   "Disconnect"
         Enabled         =   0   'False
         Height          =   375
         Left            =   2040
         TabIndex        =   9
         Top             =   2760
         Width           =   1455
      End
      Begin VB.Frame fraAddressType 
         Caption         =   "Destination Address Type"
         Height          =   855
         Left            =   240
         TabIndex        =   6
         Top             =   1200
         Width           =   3255
         Begin VB.OptionButton optPhoneNumber 
            Caption         =   "Phone Number"
            Height          =   315
            Left            =   120
            TabIndex        =   21
            Top             =   480
            Width           =   2415
         End
         Begin VB.OptionButton optIPAddress 
            Caption         =   "Machine Name or IP Address"
            Height          =   255
            Left            =   120
            TabIndex        =   5
            Top             =   240
            Value           =   -1  'True
            Width           =   2535
         End
      End
      Begin VB.CommandButton cmdPlaceCall 
         Caption         =   "Place Call"
         Height          =   375
         Left            =   240
         TabIndex        =   7
         Top             =   2280
         Width           =   1455
      End
      Begin VB.TextBox txtDestAddress 
         Height          =   375
         Left            =   240
         TabIndex        =   4
         Top             =   600
         Width           =   3255
      End
      Begin VB.Label lblDestAddress 
         Caption         =   "Destination Address:"
         Height          =   255
         Left            =   240
         TabIndex        =   19
         Top             =   360
         Width           =   1455
      End
   End
   Begin VB.Label lblHSSDisplay 
      ForeColor       =   &H80000001&
      Height          =   255
      Left            =   6120
      TabIndex        =   25
      Top             =   2400
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Label lblHookSwitchState 
      Caption         =   "Hook Switch State:"
      Height          =   255
      Left            =   4560
      TabIndex        =   24
      Top             =   2400
      Visible         =   0   'False
      Width           =   1455
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'---------------------------------------------------------------------------------------
'
'       Copyright (C) 1997-2000 Microsoft Corporation. All rights reserved.
'
'---------------------------------------------------------------------------------------
'
'
' Purpose   : Demonstrate how to make and receive calls on a USB phone using TAPI 3.0
'
' Exe Name  : USBPhone.EXE
'
' Details   : USBPhone Sample is a Visual Basic sample TAPI 3.0 application that makes
'             and receives audio calls on a USB phone using H323 Line. This sample was
'             developed using Visual Basic 6.
'
'             This sample shows the use of USB phone in two states, when phone handling
'             is enabled and when it is disabled. In both states outgoing and incoming
'             audio calls can be handled.
'
'             When phone handling is enabled certain functions happen automatically.
'             For example, generation of dial tone when handset is picked up, call being
'             automatically dialed on pressing '#' after a phone number is entered etc.
'             These things will not happen if phone handling is disabled. Developer needs
'             to write specific code to accomplish these things or can enable phone
'             handling to do these things for them.
'
'             This sample demonstrates the use of following three TAPI interfaces:
'             1) ITPhone
'             2) ITAutomatedPhoneControl
'             3) ITPhoneEvent
'
'----------------------------------------------------------------------------------------



Option Explicit

' Constants defined by tapi3err.h (tapi3.0) for error codes
Const TAPI_E_INUSE = &H8004000B
Const TAPI_E_NODEVICE = &H80040021
Const TAPI_E_INVALCALLSTATE = &H80040010
Const TAPI_E_RESOURCEUNAVAIL = &H80040052

'other constants
Const NO_ERROR = 0                  'Err.Number = 0 when there is no error

' Note: All tapi constants are defined as VB constants in the file "tapi.txt", which
' you can find in the subdirectory ..\include that comes with the TAPI3 VB samples.
' If you use VB6.0, you can open the file tapi.txt using VB's tool "API Text Viewer";
' then you can use this tool to copy/paste constants in your code.

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
                            TE_PHONEEVENT Or _
                            TE_QOSEVENT Or _
                            TE_QUEUE Or _
                            TE_REQUEST Or _
                            TE_TAPIOBJECT

Private g_objTapi As TAPI
Private g_objPhone As ITPhone
Private g_objAddress As ITAddress
Private g_objCallInfo As ITCallInfo
Private g_lRegistrationToken As Long
Private g_objCall As ITBasicCallControl
Private WithEvents g_objTapiWithEvents As TAPI
Attribute g_objTapiWithEvents.VB_VarHelpID = -1
Private g_objAutoPhoneCtrl As ITAutomatedPhoneControl
Private g_bCalledByMe As Boolean    ' Used for managing User Interface(UI)


Private Sub Form_Load()
    
    Call CreateTAPIObject
    Call GetPhone
    Call OpenPhone
    Call GetAddress
    Call RegisterForReceivingCalls
    Call DisplayPhoneInfo

End Sub

Private Sub CreateTAPIObject()
On Error Resume Next

    Dim nResult As Long
    
    ' Create TAPI object.
    Set g_objTapi = New TAPI
    nResult = CheckError("CreateTAPIObject: Creating TAPI")
    If nResult <> NO_ERROR Then Exit Sub
    
    ' TAPI needs to be initalized before any other method can be called on it.
    Call g_objTapi.Initialize
    nResult = CheckError("CreateTAPIObject: Initializing TAPI")
    If nResult <> NO_ERROR Then Exit Sub
    
    ' Set the EventFilter to accept phone events
    g_objTapi.EventFilter = TAPI3_ALL_TAPI_EVENTS
    nResult = CheckError("CreateTAPIObject: Setting EventFilter.")
    If nResult <> NO_ERROR Then Exit Sub
    
    ' Register the outgoing interface that will receive the events
    Set g_objTapiWithEvents = g_objTapi
    nResult = CheckError("CreateTAPIObject: Registering for receiving events.")
    If nResult <> NO_ERROR Then Exit Sub
    
End Sub


Private Sub GetPhone()
On Error Resume Next

    Dim nResult As Long
    
    Dim objITTAPI2 As ITTAPI2
    Dim objColPhones As ITCollection
    
    Dim dwPhoneCapability As Long
    Dim bPhoneExists As Boolean
    Dim iIndex As Integer, iNumberOfPhones As Integer
 
    If (g_objTapi Is Nothing) Then
        Exit Sub
    End If
    
    ' Get ITTAPI2 object, to get a collection of phones connected to the system
    Set objITTAPI2 = g_objTapi
    nResult = CheckError("GetPhone: Set objITTAPI2 = g_objTapi")
    If nResult <> NO_ERROR Then
        If nResult = &HD Then   'this is type mismatch error, generated by VB when QueryInterface fails
            MsgBox "This version of Windows doesn't expose USBPhone functionality. Please upgrade to XP or higher Windows version.", vbOKOnly + vbCritical, "Run on the correct Operating System"
        Else
            MsgBox "Fatal error: can't get to USBPhone interfaces, bailing.", vbOKOnly + vbCritical, "Fatal Error"
        End If
        
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
    
    Set objColPhones = objITTAPI2.Phones
    nResult = CheckError("GetPhone: objITTAPI2.Phones")
    If nResult <> NO_ERROR Then Exit Sub
    
    ' Go through the collection one by one until we get the USB phone.
    ' We can recognize a USB phone by checking if it is Generic or not.
    iNumberOfPhones = objColPhones.Count
    nResult = CheckError("GetPhone: objColPhones.Count")
    If nResult <> NO_ERROR Then Exit Sub
    
    bPhoneExists = False
    
    For iIndex = 1 To iNumberOfPhones
        Set g_objPhone = objColPhones.Item(iIndex)
        nResult = CheckError("GetPhone: objColPhones.Item(" & iIndex & ")")
        If nResult <> NO_ERROR Then Exit Sub
        
        dwPhoneCapability = g_objPhone.PhoneCapsLong(PCL_GENERICPHONE)
        nResult = CheckError("GetPhone: g_objPhone.PhoneCapsLong(PCL_GENERICPHONE)")
        If nResult <> NO_ERROR Then Exit Sub
        
        If dwPhoneCapability = 1 Then
            bPhoneExists = True
            Exit For
        End If
        
        Set g_objPhone = Nothing
        Call CheckError("Releasing g_objPhone ")
    Next iIndex
    
    ' Freeing memory
    Set objITTAPI2 = Nothing
    Call CheckError("Releasing objITTAPI2 ")
    
    Set objColPhones = Nothing
    Call CheckError("Releasing objColPhones ")
    
    If bPhoneExists = False Then
        MsgBox "No phone found. Please connect a USB phone.", vbOKOnly + vbCritical, "Connect a USB Phone to system"
        Unload Me           ' Free memory and shutdown TAPI
        End                 ' Quit application
    End If
 
End Sub


Private Sub OpenPhone()
    
    If (g_objPhone Is Nothing) Then
        Exit Sub
    End If
    
    ' A USB phone is connected. Phone must be openend to receive events and to set its state.
    ' Also to get ITAutomatedPhoneControl Interface Phone must be opened first.
       
    Dim strMsg As String
    
    On Error GoTo CheckError
        ' Open phone as an owner, PP_OWNER
        Call g_objPhone.Open(PP_OWNER)
        
        ' Get the ITAutomatedPhoneControl Interface for controlling phone features
        Set g_objAutoPhoneCtrl = g_objPhone
        
        ' Make sure that error-handling code is not executed if no error happens
        Exit Sub
                
CheckError:
    If (Err.Number = TAPI_E_INUSE) Then
        ' Inform user that phone is in use by some other application and cannot be opened.
        strMsg = "The Phone is already in use. "
        strMsg = strMsg & "Close the application using the phone and start this sample again."
        MsgBox strMsg, vbCritical + vbOKOnly
        Unload Me   ' Free memory and shutdown TAPI
        End         ' Quit the application
    End If
    
End Sub


Private Sub GetAddress()
On Error Resume Next

    If (g_objPhone Is Nothing) Then
        Exit Sub
    End If
    
    ' By default this sample uses H323 Line to make and receive calls.
    ' In this sub procedure we setect an H323 line by searching for an address
    ' that has 'h323.tsp' as it Service Provider Name
    
    Dim nResult As Long
    
    Dim nCount As Long
    Dim strServiceProviderName As String
    Dim strMsg As String
    Dim iIndex As Integer
    Dim objColOfAddresses As ITCollection
        
    Set objColOfAddresses = g_objPhone.Addresses
    nResult = CheckError("GetAddress: g_objPhone.Addresses")
    If nResult <> NO_ERROR Then Exit Sub
    
    nCount = objColOfAddresses.Count
    nResult = CheckError("GetAddress: objColOfAddresses.Count")
    If nResult <> NO_ERROR Then Exit Sub

    For iIndex = 1 To nCount
    
        Set g_objAddress = objColOfAddresses.Item(iIndex)
        nResult = CheckError("GetAddress: objColOfAddresses.Item(" & iIndex & ")")
        If nResult <> NO_ERROR Then Exit Sub
        
        strServiceProviderName = g_objAddress.ServiceProviderName
        nResult = CheckError("GetAddress: g_objAddress.ServiceProviderName")
        If nResult <> NO_ERROR Then Exit Sub
        
        If strServiceProviderName = "h323.tsp" Then
            Exit For
        Else
            Set g_objAddress = Nothing
            Call CheckError("Releasing g_objAddress ")
        End If
        
    Next iIndex
    
    ' Free memory
    Set objColOfAddresses = Nothing
    Call CheckError("Releasing objColOfAddresses ")
    
    If (g_objAddress Is Nothing) Then
        strMsg = "Phone couldn't find an H323 address and this sample makes "
        strMsg = strMsg & "and receives calls on H323 line. Please make sure that"
        strMsg = strMsg & " H323 Service provider is installed in Phone and Modem"
        strMsg = strMsg & " options of control pannel."
        MsgBox strMsg, vbCritical + vbOKOnly, "H323 line not found"
        Unload Me       ' Free memory and shutdown TAPI
        End             ' Quit program
    End If
   
End Sub

Private Sub RegisterForReceivingCalls()
    
    If (g_objTapi Is Nothing) Then
        Exit Sub
    End If
    
    ' The RegisterCallNotifications method sets which new call notifications
    ' an application will receive. The application must call the method for
    ' each address, indicating media type or types it can handle, and specifying
    ' the privileges it requests.
   
    Dim strMsg As String
    Dim fOwner As Boolean, fMonitor As Boolean
    Dim lMediaTypes As Long, lCallbackInstance As Long
    
    fOwner = True
    fMonitor = False
    lMediaTypes = TAPIMEDIATYPE_AUDIO
    lCallbackInstance = 1
    
    ' fOwner = True, receive incoming calls with owner priveliges
    ' fMonitor = False, will not monior calls
    ' lMediaTypes = TAPIMEDIATYPE_AUDIO, USB phone supports only Audio
    ' lCallbackInstance = 1, used by tapi3.dll
    ' g_lRegistrationToken, return value used by ITTAPI::UnregisterNotifications
    
    On Error GoTo HandleError
    
    g_lRegistrationToken = g_objTapi.RegisterCallNotifications( _
        g_objAddress, fMonitor, fOwner, lMediaTypes, lCallbackInstance)
    
    Exit Sub
    
HandleError:
    strMsg = "Registeration for call notifications failed. "
    strMsg = strMsg & "Sample will not be able to answer incoming calls." & Chr(13)
    strMsg = strMsg & "Error Code: 0x" & Hex(Err.Number) & Chr(13)
    strMsg = strMsg & "Error Description: " & Err.Description
    MsgBox strMsg, vbExclamation & vbOKOnly, "Call Notification failed"
    lblStatus.Caption = strMsg
    Err.Clear
    Resume Next
        
End Sub

Private Sub DisplayPhoneInfo()
On Error Resume Next

    If (g_objPhone Is Nothing) Then
        Exit Sub
    End If
    
    Dim nResult As Long
    Dim nCount As Long
    Dim objColAddress As ITCollection
    Dim objAddress As ITAddress
    Dim iIndex As Integer
    
    ' UI Stuff: Used for adding a tab between text in text boxes
    Dim AddTab As String
    AddTab = Chr(9)
    ' UI Stuff: Used for adding line feed for formating text in text boxes
    Dim LineFeed As String
    LineFeed = Chr(13) + Chr(10)

    ' Displaying information about USB phone
    txtInfo.Text = ""
    txtInfo.Text = "Phone Name:" & AddTab & g_objPhone.PhoneCapsString(PCS_PHONENAME) & LineFeed
    nResult = CheckError("DisplayPhoneInfo: g_objPhone.PhoneCapsString(PCS_PHONENAME)")
    If nResult <> NO_ERROR Then Exit Sub
    
    txtInfo.Text = txtInfo.Text & "Provider Info:" & AddTab & g_objPhone.PhoneCapsString(PCS_PROVIDERINFO) & LineFeed
    nResult = CheckError("DisplayPhoneInfo: g_objPhone.PhoneCapsString(PCS_PROVIDERINFO)")
    If nResult <> NO_ERROR Then Exit Sub
    
    txtInfo.Text = txtInfo.Text & LineFeed & "Phone is available on following Addresses:" & LineFeed
    
    Set objColAddress = g_objPhone.Addresses
    nResult = CheckError("DisplayPhoneInfo: g_objPhone.Addresses")
    If nResult <> NO_ERROR Then
        txtInfo.Text = txtInfo.Text & LineFeed & "Error: can't retrieve addresses from phone!" & LineFeed
        Exit Sub
    End If
    
    nCount = objColAddress.Count
    nResult = CheckError("DisplayPhoneInfo: objColAddress.Count")
    If nResult <> NO_ERROR Then
        txtInfo.Text = txtInfo.Text & LineFeed & "Error: can't retrieve address count from phone!" & LineFeed
        Exit Sub
    End If
    
    For iIndex = 1 To nCount
        Set objAddress = objColAddress.Item(iIndex)
        nResult = CheckError("DisplayPhoneInfo: objColAddress.Item(" & iIndex & ")")
        If nResult <> NO_ERROR Then
            txtInfo.Text = txtInfo.Text & LineFeed & "Error: can't retrieve address item from phone!" & LineFeed
            'Exit Sub   - don't exit, instead loop to next address
        End If
            
        If Not (objAddress Is Nothing) Then
            txtInfo.Text = txtInfo.Text & AddTab & AddTab & objAddress.AddressName & LineFeed
            nResult = CheckError("DisplayPhoneInfo: objAddress.AddressName")
            If nResult <> NO_ERROR Then
                txtInfo.Text = txtInfo.Text & LineFeed & "Error: can't retrieve address name!" & LineFeed
                'Exit Sub   - don't exit, instead loop to next address
            End If
                
            Set objAddress = Nothing
            Call CheckError("Releasing objAddress ")
        End If
        
    Next iIndex

End Sub


Private Sub g_objTapiWithEvents_Event(ByVal TapiEvent As TAPI3Lib.TAPI_EVENT, ByVal pEvent As Object)
        
    ' We are interested only in phone events, call state events and call notification
    If TapiEvent = TE_PHONEEVENT Then
        Call HandlePhoneEvent(pEvent)
    
    ElseIf TapiEvent = TE_CALLSTATE Then
        Call HandleCallStateEvent(pEvent)
                
    ElseIf TapiEvent = TE_CALLNOTIFICATION Then
        Call HandleCallNotificationEvent(pEvent)

    End If
     
End Sub


Private Sub HandlePhoneEvent(ByVal pEvent As Object)
On Error Resume Next

    Dim nResult As Long
        
    Dim objPhoneEvent As ITPhoneEvent
    Dim PhoneEvent As PHONE_EVENT
    Dim ButtonState As PHONE_BUTTON_STATE
           
    ' pEvent is an "Unknown" object; query its ITPhoneEvent interface
    Set objPhoneEvent = pEvent
    nResult = CheckError("HandlePhoneEvent: Set objPhoneEvent = pEvent")
    If nResult <> NO_ERROR Then Exit Sub
    
    PhoneEvent = objPhoneEvent.Event
    nResult = CheckError("HandlePhoneEvent: objPhoneEvent.Event")
    If nResult <> NO_ERROR Then Exit Sub
           
    Select Case PhoneEvent
        
        Case PE_DIALING
            ' UI stuff:
            txtDestAddress.Text = ""
            optPhoneNumber.Value = True
            Call DisableUsePhoneControls
            
        Case PE_BUTTON
            ' Display text for digit buttons (0-9) only
            Dim nButtonLampId As Long
            Dim nButtonState As PHONE_BUTTON_STATE
            
            nButtonLampId = objPhoneEvent.ButtonLampId
            nResult = CheckError("HandlePhoneEvent: objPhoneEvent.ButtonLampId")
            If nResult <> NO_ERROR Then Exit Sub
            
            nButtonState = objPhoneEvent.ButtonState
            nResult = CheckError("HandlePhoneEvent: objPhoneEvent.ButtonState")
            If nResult <> NO_ERROR Then Exit Sub
            
            If nButtonLampId < 10 Then
                ' If a button is pressed down then disply button text in text box
                ' and ignore PBS_UP state of button.
                If nButtonState = PBS_DOWN Then
                    txtDestAddress.Text = txtDestAddress.Text & nButtonLampId
                End If
            End If
        
        Case PE_HOOKSWITCH
            ' Handles hook switch event and displays hook swtich state in UI
            Dim nHookSwitchState As PHONE_HOOK_SWITCH_STATE
            
            nHookSwitchState = objPhoneEvent.HookSwitchState
            nResult = CheckError("HandlePhoneEvent: objPhoneEvent.HookSwitchState")
            If nResult <> NO_ERROR Then Exit Sub
            
            If nHookSwitchState = PHSS_OFFHOOK Then
                lblHSSDisplay.Caption = "OFF HOOK"
                lblHSSDisplay.ForeColor = &H80000001
            Else
                 lblHSSDisplay.Caption = "ON HOOK"
                 lblHSSDisplay.ForeColor = &H8000000D
            End If
        
        Case PE_NUMBERGATHERED
            ' Pass 'True' as destination address has been entered using
            ' phone keypad hence it can only be a phone number
            Call PlaceCall(True)
            
        Case PE_DISCONNECT
            ' UI Stuff:
            Call EnableUsePhoneControls
        
    End Select
    
    ' Free memory
    Set objPhoneEvent = Nothing
    Call CheckError("Releasing objPhoneEvent ")
    
End Sub


Private Sub HandleCallStateEvent(ByVal pEvent As Object)
On Error Resume Next

    Dim nResult As Long
    
    Dim objCallStateEvent As ITCallStateEvent
    Dim CallState As CALL_STATE
    
    ' pEvent is an "Unknown" object; query its ITCallStateEvent interface
    Set objCallStateEvent = pEvent
    nResult = CheckError("HandleCallStateEvent: Set objCallStateEvent = pEvent")
    If nResult <> NO_ERROR Then Exit Sub
    
    CallState = objCallStateEvent.State
    nResult = CheckError("HandleCallStateEvent: objCallStateEvent.State")
    If nResult <> NO_ERROR Then Exit Sub

    Select Case CallState
                       
        Case CS_INPROGRESS
            ' UI Stuff:
            Call PrintCallState(CallState)
            Call DisableUsePhoneControls
            If chkPhoneHandling = 0 Then
                cmdDisconnect.Enabled = True
                Call cmdDisconnect.SetFocus
            End If
                           
                        
        Case CS_DISCONNECTED
            Call PrintCallState(CallState)
            
            If chkPhoneHandling = 0 Then
                If Not (g_objAutoPhoneCtrl Is Nothing) Then
                    Call g_objAutoPhoneCtrl.UnselectCall(g_objCallInfo)
                    nResult = CheckError("HandleCallStateEvent: g_objAutoPhoneCtrl.UnselectCall")
                    'If nResult <> NO_ERROR Then Exit Sub - ignore error, want to continue with releasing call
                End If
            End If
            
            ' release the call control interface
            Set g_objCallInfo = Nothing
            Call CheckError("Releasing g_objCallInfo ")
            
            Set g_objCall = Nothing
            Call CheckError("Releasing g_objCall ")
            
            ' UI stuff:
            Call EnableUsePhoneControls
            cmdDisconnect.Enabled = False
            cmdAnswer.Enabled = False
            
            
        Case CS_OFFERING
            Dim nCallState As CALL_STATE
            
            nCallState = g_objCallInfo.CallState
            nResult = CheckError("HandleCallStateEvent: g_objCallInfo.CallState")
            If nResult <> NO_ERROR Then Exit Sub
            
            If nCallState = CS_OFFERING Then
                ' User Interface stuff:
                Call PrintCallState(CallState)
                Call DisableUsePhoneControls
                If chkPhoneHandling = 0 Then
                    cmdAnswer.Enabled = True
                    Call cmdAnswer.SetFocus
                End If
            Else
                ' current call on phone is in connected state thus incoming call should be ignored.
                lblStatus.Caption = lblStatus.Caption & Chr(13) & "Incoming call was ignored because phone is in use"
            End If
            
        Case Else
            Call PrintCallState(CallState)
    
    End Select
    
    ' Free memory
    Set objCallStateEvent = Nothing
    Call CheckError("Releasing objCallStateEvent ")
    
End Sub

Private Sub HandleCallNotificationEvent(ByVal pEvent As Object)
On Error Resume Next

    Dim nResult As Long
    
    Dim objCallNotificationEvent As ITCallNotificationEvent
    Dim CallNotificationState As CALL_NOTIFICATION_EVENT
    
    Dim strMsg As String

    ' pEvent is an "Unknown" object; query its ITCallStateEvent interface
    Set objCallNotificationEvent = pEvent
    nResult = CheckError("HandleCallNotificationEvent: Set objCallNotificationEvent = pEvent")
    If nResult <> NO_ERROR Then Exit Sub
    
    ' Receive the incoming call only if no other call exists
    If (g_objCallInfo Is Nothing) Then
        
        Set g_objCallInfo = objCallNotificationEvent.Call
        nResult = CheckError("HandleCallNotificationEvent: objCallNotificationEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub
        
        Set g_objCall = g_objCallInfo
        nResult = CheckError("HandleCallNotificationEvent: Set g_objCall = g_objCallInfo")
        If nResult <> NO_ERROR Then Exit Sub
        
        PrintCallState (g_objCallInfo.CallState)
        nResult = CheckError("HandleCallNotificationEvent: g_objCallInfo.CallState")
        If nResult <> NO_ERROR Then Exit Sub
        
        If chkPhoneHandling = 1 Then
            
            Call g_objAutoPhoneCtrl.SelectCall(g_objCallInfo, True)
            
            'SelectCall can actually fail; treat the error right here:
            If (Err.Number = TAPI_E_INVALCALLSTATE) Then
                strMsg = "Unable to answer call because call is in CS_DISCONNECTED state." & Chr(13)
            End If
            
            If Err.Number <> NO_ERROR Then
                strMsg = strMsg & "Error Code: 0x" & Hex(Err.Number) & Chr(13)
                strMsg = strMsg & "Error Description: " & Err.Description
                MsgBox strMsg, vbExclamation & vbOKOnly, "Unable to answer call"
                lblStatus.Caption = strMsg
                Err.Clear
            End If
        
        End If
    
    End If
    
End Sub


Private Sub PrintCallState(State As CALL_STATE)
    
    Dim strMsg As String
    
    Select Case State
        
        Case CS_INPROGRESS
            If chkPhoneHandling.Value = 0 Then
                strMsg = "Call state: CS_INPROGRESS" & Chr(13) & "Click Disconnect button to end call"
            Else
                strMsg = "Call state: CS_INPROGRESS" & Chr(13) & "Press phone hook switch to end call"
            End If
            lblStatus.Caption = strMsg
        
        Case CS_OFFERING
            If chkPhoneHandling.Value = 0 Then
                strMsg = "Call state: CS_OFFERING" & Chr(13) & "Click Answer button to receive call"
            Else
                strMsg = "Call state: CS_OFFERING" & Chr(13) & "Press phone hook switch to receive call"
            End If
            lblStatus.Caption = strMsg
        
        Case CS_CONNECTED
            If chkPhoneHandling.Value = 0 Then
                strMsg = "Call state: CS_CONNECTED" & Chr(13) & "Click Disconnect button to end call"
            Else
                strMsg = "Call state: CS_CONNECTED" & Chr(13) & "Press phone hook switch to end call"
            End If
            lblStatus.Caption = strMsg
        
        Case CS_DISCONNECTED
            strMsg = "Call state: CS_DISCONNECTED"
            lblStatus.Caption = strMsg
        
        Case CS_HOLD
            lblStatus.Caption = "Call state: CS_HOLD"
        
        Case CS_IDLE
            lblStatus.Caption = "Call state: CS_IDLE"
        
        Case CS_QUEUED
            lblStatus.Caption = "Call state: CS_QUEUED"
        
        Case Else
            lblStatus.Caption = "Call state: Unknown!!"
    
    End Select

End Sub


Private Sub cmdPlaceCall_Click()
    ' If destination address is a phone number pass true to PlaceCall routine to select line type
    ' as 'phonenumber' otherwise seltect line type as 'IPAddress'

    If (optPhoneNumber.Value = True) Then
        Call PlaceCall(True)
    Else
        Call PlaceCall(False)
    End If
    
End Sub


Private Sub PlaceCall(bIsPhoneNumber As Boolean)
    
    Dim strMsg As String, strDestAddress As String
    
    ' UI Stuff: Erase old messages
    lblStatus.Caption = "Dialing ..."
    
    ' Check it a call already exist
    If (g_objCall Is Nothing) Then
        
        ' No call exists, we can procede with making a new call.
        ' Check if user entered destination address data.
        strDestAddress = txtDestAddress.Text
        If strDestAddress = "" Then
            lblStatus.Caption = "Enter destination address!"
            Call EnableUsePhoneControls
            
        Else
            On Error GoTo HandleError
            ' If destination address is phone # use Phone address type
            ' otherwise use IP address type (machine name)
            If (bIsPhoneNumber = True) Then
                Set g_objCall = g_objAddress.CreateCall(strDestAddress, LINEADDRESSTYPE_PHONENUMBER, TAPIMEDIATYPE_AUDIO)
            Else
                Set g_objCall = g_objAddress.CreateCall(strDestAddress, LINEADDRESSTYPE_IPADDRESS, TAPIMEDIATYPE_AUDIO)
            End If
            
            Set g_objCallInfo = g_objCall
            ' Select call on phone object. 'True' means that SelectCall method will automatically
            ' select terminals associated with the phone. Otherwise terminals need to be explicitly
            ' selected.
            Call g_objAutoPhoneCtrl.SelectCall(g_objCallInfo, True)
            Call g_objCall.Connect(False)
            
            ' Print call state
            Call PrintCallState(g_objCallInfo.CallState)
            
        End If
            
    Else
       ' Second call not supported by this app
       lblStatus.Caption = "Cannot connect new call. Wait for the previous one to be disconnected."
        
    End If
    
    Exit Sub
    
HandleError:
    strMsg = "Unable to connect call" & Chr(13)
    strMsg = strMsg & "Error Code: 0x" & Hex(Err.Number) & Chr(13)
    strMsg = strMsg & "Error Description: " & Err.Description
    MsgBox strMsg, vbExclamation & vbOKOnly, "Placing call failed"
    lblStatus.Caption = strMsg
    Err.Clear
    
End Sub


Private Sub chkPhoneHandling_Click()
    
    Dim bPhoneHandlingEnabled As Boolean
    Dim State As PHONE_HOOK_SWITCH_STATE
    Dim strMsg As String
    
    On Error GoTo HandleError
    
    If g_bCalledByMe Then
        ' This event happended because developer reset a user interface control so just
        ' reset the boolean variable and quit this sub without executing any other code
        g_bCalledByMe = False
        
    Else
        ' Is phone on hook or off hook? if off hook then inform user that phone must be on
        ' on hook before PhoneHandling can be enabled or disabled
        State = g_objPhone.HookSwitchState(PHSD_HANDSET)
        
        Do While State <> PHSS_ONHOOK
            strMsg = "Please put the handset onhook and then press OK."
            If MsgBox(strMsg, vbOKCancel + vbInformation, "Phone must be onhook") = vbCancel Then
                ' Resetting check box to its previous value. This will cause a recursive call
                ' to this method. Make 'g_bCalledByMe' TRUE so this code portion is not
                ' executed again and message box will not show up again.
                g_bCalledByMe = True
                
                If chkPhoneHandling.Value Then
                    chkPhoneHandling.Value = 0
                Else
                    chkPhoneHandling.Value = 1
                End If
            
                Exit Sub
            End If
            State = g_objPhone.HookSwitchState(PHSD_HANDSET)
        Loop
        
        ' If the check box is not checked disable PhoneHandling otherwise enable it
        If chkPhoneHandling.Value = 0 Then
            g_objAutoPhoneCtrl.PhoneHandlingEnabled = False
            Call EnableManualControls       ' Manging User Interface
        
        ElseIf chkPhoneHandling.Value = 1 Then
            ' Stop ringer and tone if they are playing
            Call g_objAutoPhoneCtrl.StopRinger
            Call g_objAutoPhoneCtrl.StopTone
            g_objAutoPhoneCtrl.PhoneHandlingEnabled = True
            Call DisableManualControls      ' Manging User Interface
        
        End If
      
    End If
    
    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler

End Sub


Private Sub cmdAnswer_Click()
    
On Error Resume Next

    Dim nResult As Long
    Dim nCallState As CALL_STATE
    
    nCallState = g_objCallInfo.CallState
    nResult = CheckError("cmdAnswer_Click: g_objCallInfo.CallState")
    If nResult <> NO_ERROR Then Exit Sub
    
    If nCallState = CS_OFFERING Then
        
        Call g_objAutoPhoneCtrl.SelectCall(g_objCallInfo, True)
        nResult = CheckError("cmdAnswer_Click: g_objAutoPhoneCtrl.SelectCall")
        If nResult <> NO_ERROR Then Exit Sub
        
        If chkPhoneHandling = 0 Then
            cmdAnswer.Enabled = False
            cmdDisconnect.Enabled = True
            Call cmdDisconnect.SetFocus
            
            Call g_objCall.Answer
            nResult = CheckError("cmdAnswer_Click: g_objCall.Answer")
            If nResult <> NO_ERROR Then Exit Sub
            
        End If
        
    ElseIf nCallState = CS_CONNECTED Then
        lblStatus.Caption = "Call is already connected."
    
    Else
        lblStatus.Caption = "No call to answer"
        
    End If

End Sub


Private Sub cmdDisconnect_Click()
    ' If phoneHandling is enabled call will be disconnected with hook switch. If phone
    ' handling is disabled than call needs to be disconnected over here.
    If (g_objCall Is Nothing) Then
        lblStatus.Caption = "There is no call to be disconnected."
        lblStatus.Refresh
    
    Else
        On Error GoTo ErrorHandler
        g_objCall.Disconnect (DC_NORMAL)
        On Error GoTo 0
        
        Call EnableUsePhoneControls
    End If
    
    Exit Sub
    
ErrorHandler:
    lblStatus.Caption = "Disconnect failed" & Chr(13)
    lblStatus.Caption = lblStatus.Caption & "Error Code: 0x" & Hex(Err.Number) & Chr(13)
    lblStatus.Caption = lblStatus.Caption & "Error Description: " & Err.Description
    Err.Clear
    Resume Next
    
End Sub


Private Sub cmdStartRinger_Click()
    
    On Error GoTo HandleError
    
    ' First argument means any type of ring is accepatable
    ' Second argument means ring shoud be played in an endless loop
    Call g_objAutoPhoneCtrl.StartRinger(0, 0)
    lblStatus.Caption = "Ringer has started."
    
    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler

End Sub


Private Sub cmdStopRinger_Click()
    
    On Error GoTo HandleError
    
    Call g_objAutoPhoneCtrl.StopRinger
    lblStatus.Caption = "Ringer was stopped."

    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler

End Sub


Private Sub cmdBusy_Click()
    
    On Error GoTo HandleError
        
    ' Argument '0' means tone should be played as an endless loop
    Call g_objAutoPhoneCtrl.StartTone(PT_BUSY, 0)
    lblStatus.Caption = "Busy tone is being generated."
    
    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler

End Sub


Private Sub cmdDialTone_Click()

    On Error GoTo HandleError

    ' Argument '0' means tone should be played as an endless loop
    Call g_objAutoPhoneCtrl.StartTone(PT_NORMALDIALTONE, 0)
    lblStatus.Caption = "Dial tone is being generated."
    
    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler

End Sub


Private Sub cmdError_Click()

    On Error GoTo HandleError
    
    ' Argument '0' means tone should be played as an endless loop
    Call g_objAutoPhoneCtrl.StartTone(PT_ERRORTONE, 0)
    lblStatus.Caption = "Error tone is being generated."
    
    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler
        
End Sub


Private Sub cmdRingBack_Click()
    
    On Error GoTo HandleError
    
    ' Argument '0' means tone should be played as an endless loop
    Call g_objAutoPhoneCtrl.StartTone(PT_RINGBACK, 0)
    lblStatus.Caption = "Ring back is being generated."

    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler
        
End Sub


Private Sub cmdStopTone_Click()

    On Error GoTo HandleError

    Call g_objAutoPhoneCtrl.StopTone
    lblStatus.Caption = "All Tones have been stopped."

    Exit Sub
    
HandleError:
    Call AutoPhoneCtrlErrorHandler

End Sub


Private Sub AutoPhoneCtrlErrorHandler()
    ' This is general sub routine for printing error messages for various
    ' ITAutomatedPhoneControl methods
    
    Dim strMsg As String

    Select Case Err.Number
    
        Case TAPI_E_INUSE
            strMsg = "Another application has audio render device open." & Chr(13)
        Case TAPI_E_NODEVICE
            strMsg = "The phone object does not have associated audio render device." & Chr(13)
        Case TAPI_E_RESOURCEUNAVAIL
            strMsg = "The device has been removed" & Chr(13)
               
    End Select
    
    strMsg = strMsg & "Error Code: 0x" & Hex(Err.Number) & Chr(13)
    strMsg = strMsg & "Error Description: " & Err.Description
    MsgBox strMsg, vbExclamation & vbOKOnly
    lblStatus.Caption = strMsg
    
    Err.Clear
       
End Sub


Private Sub DisableUsePhoneControls()
    
    ' Managing User Interface of application
    chkPhoneHandling.Enabled = False
    txtDestAddress.Locked = True
    txtDestAddress.BackColor = &H80000004
    optPhoneNumber.Enabled = False
    optIPAddress.Enabled = False
    cmdPlaceCall.Enabled = False
    
End Sub


Private Sub EnableUsePhoneControls()
    
    ' Managing User Interface of application
    txtDestAddress.Text = ""
    chkPhoneHandling.Enabled = True
    txtDestAddress.Locked = False
    txtDestAddress.BackColor = &H80000005
    optPhoneNumber.Enabled = True
    optIPAddress.Enabled = True
    cmdPlaceCall.Enabled = True
    
End Sub


Private Sub DisableManualControls()
    
    ' Managing User Interface of application
    cmdDisconnect.Enabled = False
    fraManualControl.Enabled = False
    cmdStartRinger.Enabled = False
    cmdStopRinger.Enabled = False
    cmdDialTone.Enabled = False
    cmdBusy.Enabled = False
    cmdError.Enabled = False
    cmdRingBack.Enabled = False
    cmdStopTone.Enabled = False
    lblHookSwitchState.Visible = True
    lblHSSDisplay.Visible = True
    lblStatus.Caption = ""
    
End Sub


Private Sub EnableManualControls()
    
    ' Managing User Interface of application
    fraManualControl.Enabled = True
    cmdStartRinger.Enabled = True
    cmdStopRinger.Enabled = True
    cmdDialTone.Enabled = True
    cmdBusy.Enabled = True
    cmdError.Enabled = True
    cmdRingBack.Enabled = True
    cmdStopTone.Enabled = True
    lblHookSwitchState.Visible = False
    lblHSSDisplay.Visible = False

End Sub


Private Sub cmdExit_Click()
    
    ' Free memory and shutdown TAPI
    Unload Me

End Sub


Private Sub Form_Unload(Cancel As Integer)

'catch all tapi errors but ignore them, since we want to shut down anyway
'but at the same time we want to attempt all possible cleanup
On Error Resume Next

    ' Close the phone
    If Not (g_objPhone Is Nothing) Then
        Call g_objPhone.Close
        Call CheckError("Form_Unload: g_objPhone.Close ")
    End If
    
    ' Freeing memory
    Set g_objCallInfo = Nothing
    Call CheckError("Form_Unload: releasing g_objCallInfo ")
    
    Set g_objCall = Nothing
    Call CheckError("Form_Unload: releasing g_objCall ")
    
    Set g_objAutoPhoneCtrl = Nothing
    Call CheckError("Form_Unload: releasing g_objAutoPhoneCtrl ")
    
    Set g_objPhone = Nothing
    Call CheckError("Form_Unload: releasing g_objPhone ")
    
    Set g_objAddress = Nothing
    Call CheckError("Form_Unload: releasing g_objAddress ")
    
    Set g_objTapiWithEvents = Nothing
    Call CheckError("Form_Unload: releasing g_objTapiWithEvents ")
                
    ' Shutting down TAPI
    If Not (g_objTapi Is Nothing) Then
        Call g_objTapi.Shutdown
        Call CheckError("Form_Unload: g_objTapi.Shutdown")
    End If
    
    Set g_objTapi = Nothing
    Call CheckError("Form_Unload: releasing g_objTapi ")
           
End Sub


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
