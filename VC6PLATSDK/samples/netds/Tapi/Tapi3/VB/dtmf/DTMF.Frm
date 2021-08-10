VERSION 5.00
Begin VB.Form frmDTMF 
   Caption         =   "DTMF demo"
   ClientHeight    =   6555
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8010
   LinkTopic       =   "Form1"
   ScaleHeight     =   6555
   ScaleWidth      =   8010
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox cbSelectTerminals 
      Caption         =   "Select Audio Terminals"
      Height          =   195
      Left            =   1680
      TabIndex        =   20
      Top             =   1320
      Width           =   2295
   End
   Begin VB.CommandButton pbRelease 
      Caption         =   "ReleaseCall"
      Enabled         =   0   'False
      Height          =   375
      Left            =   4560
      TabIndex        =   19
      Top             =   1200
      Width           =   2415
   End
   Begin VB.ComboBox cmbAddresses 
      Height          =   315
      Left            =   1800
      TabIndex        =   17
      Top             =   240
      Width           =   2655
   End
   Begin VB.Frame Frame3 
      Caption         =   "Digit Detection"
      Height          =   1695
      Left            =   4913
      TabIndex        =   13
      Top             =   2040
      Width           =   2655
      Begin VB.CommandButton pbStopDetect 
         Caption         =   "Stop Detect"
         Height          =   375
         Left            =   600
         TabIndex        =   15
         Top             =   960
         Width           =   1455
      End
      Begin VB.CommandButton pbStartDetect 
         Caption         =   "Start Detect"
         Height          =   375
         Left            =   600
         TabIndex        =   14
         Top             =   360
         Width           =   1455
      End
   End
   Begin VB.TextBox txtStatus 
      Height          =   2175
      Left            =   218
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Top             =   4320
      Width           =   7575
   End
   Begin VB.CheckBox cbModePulse 
      Caption         =   "Pulse"
      Height          =   255
      Left            =   518
      TabIndex        =   6
      Top             =   3000
      Width           =   1095
   End
   Begin VB.CheckBox cbModeDTMFEND 
      Caption         =   "DTMFEND"
      Height          =   255
      Left            =   518
      TabIndex        =   5
      Top             =   2640
      Width           =   1095
   End
   Begin VB.CheckBox cbModeDTMF 
      Caption         =   "DTMF"
      Height          =   255
      Left            =   518
      TabIndex        =   4
      Top             =   2280
      Value           =   1  'Checked
      Width           =   1095
   End
   Begin VB.CommandButton pbGenerate 
      Caption         =   "Generate"
      Height          =   375
      Left            =   2438
      TabIndex        =   8
      Top             =   3120
      Width           =   1695
   End
   Begin VB.TextBox txtDigitsToGenerate 
      Height          =   285
      Left            =   2318
      MaxLength       =   20
      TabIndex        =   7
      Text            =   "0123456789ABCD*#"
      Top             =   2640
      Width           =   2055
   End
   Begin VB.TextBox txtDestAddress 
      Height          =   285
      Left            =   1800
      MaxLength       =   20
      TabIndex        =   0
      Text            =   "24311"
      Top             =   720
      Width           =   2655
   End
   Begin VB.CommandButton pbDial 
      Caption         =   "Dial"
      Default         =   -1  'True
      Height          =   375
      Left            =   4560
      TabIndex        =   1
      Top             =   240
      Width           =   2415
   End
   Begin VB.CommandButton pbDisconnect 
      Caption         =   "Disconnect"
      Enabled         =   0   'False
      Height          =   375
      Left            =   4560
      TabIndex        =   2
      Top             =   720
      Width           =   2415
   End
   Begin VB.Frame Frame1 
      Caption         =   "Digit Mode"
      Height          =   1335
      Left            =   398
      TabIndex        =   11
      Top             =   2040
      Width           =   1335
   End
   Begin VB.Frame Frame2 
      Caption         =   "Digit Generation"
      Height          =   1695
      Left            =   2078
      TabIndex        =   12
      Top             =   2040
      Width           =   2535
      Begin VB.Label Label1 
         Caption         =   "Digits to generate:"
         Height          =   255
         Left            =   240
         TabIndex        =   16
         Top             =   360
         Width           =   2055
      End
   End
   Begin VB.Line Line2 
      X1              =   240
      X2              =   7680
      Y1              =   3960
      Y2              =   3960
   End
   Begin VB.Label Label3 
      Caption         =   "Origination address:"
      Height          =   255
      Left            =   120
      TabIndex        =   18
      Top             =   240
      Width           =   1455
   End
   Begin VB.Line Line1 
      X1              =   278
      X2              =   7718
      Y1              =   1800
      Y2              =   1800
   End
   Begin VB.Label Label2 
      Caption         =   "Destination dialable address:"
      Height          =   375
      Left            =   120
      TabIndex        =   10
      Top             =   720
      Width           =   1575
   End
   Begin VB.Label lblStatusTitle 
      Caption         =   "Status:"
      Height          =   255
      Left            =   240
      TabIndex        =   9
      Top             =   4080
      Width           =   615
   End
End
Attribute VB_Name = "frmDTMF"
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
' DTMF = makes Tapi3 outgoing asynchronous call, on which DTMF tones can be generated.
'
' This app needs a voice modem to be in the system, because
' this can generate/detect DTMF tones.
' Alternatively, the H323 (IP telephony) line exposed by the H323 provider
' offers DTMF functionality as well.
' It allows the user to make an outgoing call.
' On the call, it selects the default terminals for audio+capture and audio+render
' if it finds any such terminals, and also if the user choses to select them.
' On the call, it allows the user to generate/detect digits - the user can
' do that by pressing the corresponding buttons from the form.
'

Option Explicit

'
'user defined types
'

Enum TestError
    'TErr_NotInitialized = 0
    TErr_Ok = 1
    TErr_Fail = 2
End Enum

'
'Constants defined by tapi.h (tapi2.x), tapi3err.h (tapi3.0) or winerror.h
'for error codes:
'
'Note: all tapi constants are defined as VB constants in the file "tapi.txt", which
'you can find in the subdirectory ..\include that comes with the TAPI3 VB samples.
'If you use VB6.0, you can open the file tapi.txt using VB's tool "API Text Viewer";
'then you can use this tool to copy/paste constants in your code.
'

'tapi3err.h constants
Const LINEGENERATETERM_DONE = &H1
Const LINEGENERATETERM_CANCEL = &H2

'other constants
Const NO_ERROR = 0                  'Err.Number = 0 when there is no error
'Const vbTextCompare = 1
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

'
'global variables
'

'TAPI objects
Private mbInitialized As Boolean
Private WithEvents mobjTapiWithEvents As TAPI
Attribute mobjTapiWithEvents.VB_VarHelpID = -1
Private mobjTapi As TAPI

'current address + related info
Private mobjOrigAddress As ITAddress
Private mnPreviousAddressIndex As Long
Private mvarArrAudioTerminals As Variant

'current call
Private mobjCall As ITBasicCallControl

Private Sub Form_Load()
    
    'initialize UI
    pbDial.Enabled = True
    pbDisconnect.Enabled = False
    pbRelease.Enabled = False

    pbGenerate.Enabled = False
    pbStartDetect.Enabled = False
    pbStopDetect.Enabled = False
    
    'initialize Tapi
    InitializeTapiObjects
    
    'populate combo with all addresses , regardless
    'of their possibility to support the Digit Terminal class
    Call PopulateAddressesCombo(mobjTapi, False)
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
    'release all member data "object" variables
    Call ReleaseAllMembers
    
    'release combo with addresses
    Call DepopulateAddressesCombo
End Sub

'
'This function is called only once, when the form is loaded.
'
'This function populates the combobox with the names of the addresses,
'and memorize also in the "data" field the index of each address
'that corresponds to the collection of addresses from objTapi.
'Then it selects the 1st item in the combo.
'
'If bMustSupportDTMF is set on True, only addresses that have
'the DTMF functionality are put in combo.
'
'Note: we use On Erorr Resume Next, because we want to add as many items as possible
'
Sub PopulateAddressesCombo(objTapi As TAPI, bMustSupportDTMF As Boolean)
On Error Resume Next        'this will catch errors

    Dim nResult As Long
    Dim nIterator As Long, nCount As Long
    Dim collobjAddresses As ITCollection
    Dim objCrtAddress As ITAddress
    
    'don't need to clean combo of previous contents,
    'because this function is called only once
    'cmbAddresses.Clear
    
    Set collobjAddresses = objTapi.Addresses
    nResult = PrintT3Result("PopulateAddressesCombo: objTapi.Addresses")
    
    If nResult = NO_ERROR Then
        'populate combobox with names of all addresses from collobjAddresses
        'attach to each combo item the index of the corresponding address
        nCount = 0
        nCount = collobjAddresses.Count
        
        For nIterator = 1 To nCount
            
            Set objCrtAddress = collobjAddresses.Item(nIterator)
            
            nResult = PrintT3Result("PopulateAddressesCombo: enumerate addresses")
            
            If nResult = NO_ERROR Then
                
                If (bMustSupportDTMF = False Or _
                    bMustSupportDTMF And SupportDTMF(objCrtAddress)) Then
                
                    cmbAddresses.AddItem (objCrtAddress.AddressName)
                    
                    nResult = PrintT3Result("PopulateAddressesCombo: adding addresses in combo")
                    
                    If nResult = NO_ERROR Then
                        cmbAddresses.ItemData(cmbAddresses.NewIndex) = nIterator
                    End If
                    
                End If
            End If
            
            Set objCrtAddress = Nothing
                        
        Next nIterator
    End If
    
    Set collobjAddresses = Nothing
    
    'set selection on 1st item
    If cmbAddresses.ListCount > 0 Then
        cmbAddresses.ListIndex = 0
        'This automatically called cmbAddresses_Click
    End If
    
End Sub

Sub DepopulateAddressesCombo()
    cmbAddresses.Clear
End Sub

Private Sub cmbAddresses_Change()
    Call ChangeAddress
End Sub

Private Sub cmbAddresses_Click()
    Call ChangeAddress
End Sub

Private Sub ChangeAddress()
On Error Resume Next        'this will catch errors
    
    Dim nResult As Long
    Dim nOrigAddressIndex As Long
    
    'pick up the collection of Address objects
    Dim objCollAddresses As ITCollection
    
    Set objCollAddresses = mobjTapi.Addresses
    nResult = PrintT3Result("ChangeAddress: mobjTapi.Addresses")
    If nResult <> NO_ERROR Then
        Call MsgBox("Fatal error: can't get TAPI addresses, exit program", vbCritical)
        Stop    'fatal error
    End If
    
    'find index of address selected by the user
    nOrigAddressIndex = FindOriginationAddressIndex()
    
    '
    'pick up the new address - update all related global variables
    '
    
    If mnPreviousAddressIndex <> nOrigAddressIndex Then
        'If a new address was selected, release the previous one
        'and save a "pointer" to the new one, plus related info
        'If the same address was selected, don't release/save it again,
        'just keep the previous one + its related info.
        
        '
        'clean up previous info
        '
        
        'release previous address
        Set mobjOrigAddress = Nothing
        
        'release old terminals
        Call ReleaseAudioTerminals(mvarArrAudioTerminals)
        
        'wipe out other info
        mnPreviousAddressIndex = 0
        
        '
        'save new info
        '
        
        'validate new index
        If nOrigAddressIndex >= 1 And nOrigAddressIndex <= objCollAddresses.Count Then
            
            'save new address
            Set mobjOrigAddress = objCollAddresses.Item(nOrigAddressIndex)
            
            'save also the new index
            mnPreviousAddressIndex = nOrigAddressIndex
            
            'create new terminals
            Call GetAudioTerminals(mobjOrigAddress, mvarArrAudioTerminals)
        
        End If

    End If
    
    'release objects that are not needed anymore
    '(this decrements the reference count)
    Set objCollAddresses = Nothing
End Sub

Function SupportDTMF(objAddress As ITAddress) As Boolean
On Error Resume Next        'this will catch errors
    
    Dim nResult As Long, nResult1 As Long
    
    Dim objITAddressCapabilities As ITAddressCapabilities
    Dim lGenerateDigitSupport As Long, lMonitorDigitSupport As Long
    
    'prepare return value
    SupportDTMF = False
    
    'query the interface ITAddressCapabilities
    Set objITAddressCapabilities = objAddress
    nResult = PrintT3Result("SupportDTMF: objAddress->Query (ITAddressCapabilities)")
    
    If nResult = NO_ERROR Then
    
        lGenerateDigitSupport = objITAddressCapabilities.AddressCapability(AC_GENERATEDIGITSUPPORT)
        nResult = PrintT3Result("SupportDTMF: AddressCapability(AC_GENERATEDIGITSUPPORT)")
        nResult1 = nResult
        lMonitorDigitSupport = objITAddressCapabilities.AddressCapability(AC_MONITORDIGITSUPPORT)
        nResult = PrintT3Result("SupportDTMF: AddressCapability(AC_MONITORDIGITSUPPORT)")
        
        If nResult = NO_ERROR And nResult1 = NO_ERROR Then
        
            If lGenerateDigitSupport <> 0 And lMonitorDigitSupport <> 0 Then
                SupportDTMF = True
            End If
            
        End If
        
    End If
    
    'release all objects and exit
    Set objITAddressCapabilities = Nothing
    
End Function

Private Sub PrintCallState(State As CALL_STATE)
    Dim strMsg
    
    Select Case State
        Case CS_CONNECTED
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: CS_CONNECTED"
        Case CS_DISCONNECTED
            strMsg = "call state: CS_DISCONNECTED" & Chr(13) & Chr(10)
            strMsg = strMsg & "Call was disconnected. "
            strMsg = strMsg & "Now you should Release it. "
            strMsg = strMsg & "Then you can press Dial again or just quit."
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & strMsg
        Case CS_HOLD
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: CS_HOLD"
        Case CS_IDLE
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: CS_IDLE"
        Case CS_INPROGRESS
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: CS_INPROGRESS"
        Case CS_OFFERING
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: CS_OFFERING"
        Case CS_QUEUED
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: CS_QUEUED"
        Case Else
            txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
            txtStatus.Text = txtStatus.Text & "call state: unknown!!"
    End Select
    
    txtStatus.SelStart = Len(txtStatus.Text)
    txtStatus.SelLength = 0

End Sub

'
'we are interested only in: TE_DIGITEVENT, TE_GENERATEEVENT, TE_CALLSTATE
'
Private Sub mobjTapiWithEvents_Event( _
    ByVal TapiEvent As TAPI3Lib.TAPI_EVENT, _
    ByVal pEvent As Object)
On Error Resume Next

    Dim nResult As Long
    Dim objCallStateEvent As ITCallStateEvent
    Dim CallState As CALL_STATE
    
    Dim strMsg As String, strCallInfoMsg As String
    Dim lCallbackInstance As Long, lTickCount As Long
    Dim objReceivedCallInfo As ITCallInfo
    Dim objCurrentCallInfo As ITCallInfo
    
    '
    'process TE_DIGITEVENT
    '
    
    If TapiEvent = TE_DIGITEVENT Then
    
        Dim bDigit As Byte, lDigitMode As Long
        
        Dim objITDigitDetectionEvent As ITDigitDetectionEvent
        Set objITDigitDetectionEvent = pEvent
        
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objITDigitDetectionEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub
        
        bDigit = objITDigitDetectionEvent.Digit
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.Digit")
        If nResult <> NO_ERROR Then Exit Sub
        
        lDigitMode = objITDigitDetectionEvent.DigitMode
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.DigitMode")
        If nResult <> NO_ERROR Then Exit Sub
        
        lTickCount = objITDigitDetectionEvent.TickCount
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.TickCount")
        If nResult <> NO_ERROR Then Exit Sub
        
        '
        lCallbackInstance = objITDigitDetectionEvent.CallbackInstance
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.CallbackInstance")
        If nResult <> NO_ERROR Then Exit Sub
        
        Set objReceivedCallInfo = objITDigitDetectionEvent.Call
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitDetectionEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub
        
        '
        'check if the received CallInfo matches the call
        'for which our app currently keeps a reference of.
        '
        Set objCurrentCallInfo = mobjCall
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCurrentCallInfo = mobjCall")
        If nResult <> NO_ERROR Then Exit Sub
        
        If objCurrentCallInfo Is objReceivedCallInfo Then
            strCallInfoMsg = "matches current call"
        Else
            strCallInfoMsg = "doesn't match current call! (error)"
            MsgBox ("Call object received in TE_DIGITEVENT doesn't match current call!")
        End If
        Set objCurrentCallInfo = Nothing
        
        
        Set objReceivedCallInfo = Nothing
        Set objITDigitDetectionEvent = Nothing
    
        strMsg = "Event type = TE_DIGITEVENT: "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  bDigit = 0x" & Hex(bDigit) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  lDigitMode = " & lDigitMode & " " & TranslateDigitMode(lDigitMode) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  lTickCount = 0x" & Hex(lTickCount) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  lCallbackInstance = 0x" & Hex(lCallbackInstance) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  objCallInfo = " & strCallInfoMsg & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strMsg
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
        
        Exit Sub
    End If
    
    '
    'process TE_GENERATEEVENT
    '
    
    If TapiEvent = TE_GENERATEEVENT Then
        
        Dim lGenerationTermination As Long
        
        Dim objITDigitGenerationEvent As ITDigitGenerationEvent
        Set objITDigitGenerationEvent = pEvent
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objITDigitGenerationEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub
        
        lGenerationTermination = objITDigitGenerationEvent.GenerationTermination
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.GenerationTermination")
        If nResult <> NO_ERROR Then Exit Sub
        
        lTickCount = objITDigitGenerationEvent.TickCount
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.TickCount")
        If nResult <> NO_ERROR Then Exit Sub
        
        '
        lCallbackInstance = objITDigitGenerationEvent.CallbackInstance
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.CallbackInstance")
        If nResult <> NO_ERROR Then Exit Sub
        
        Set objReceivedCallInfo = objITDigitGenerationEvent.Call
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITDigitGenerationEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub
        
        '
        'check if the received CallInfo matches the call
        'for which our app currently keeps a reference of.
        '
        Set objCurrentCallInfo = mobjCall
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCurrentCallInfo = mobjCall")
        If nResult <> NO_ERROR Then Exit Sub
        
        If objCurrentCallInfo Is objReceivedCallInfo Then
            strCallInfoMsg = "matches current call"
        Else
            strCallInfoMsg = "doesn't match current call! (error)"
            MsgBox ("Call object received in TE_GENERATEEVENT doesn't match current call!")
        End If
        Set objCurrentCallInfo = Nothing
        
        
        Set objReceivedCallInfo = Nothing
        Set objITDigitGenerationEvent = Nothing
    
        strMsg = "Event type = TE_GENERATEEVENT: "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  lGenerationTermination = " & lGenerationTermination & " " & TranslateGenerateTerm(lGenerationTermination) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  lTickCount = 0x" & Hex(lTickCount) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  lCallbackInstance = 0x" & Hex(lCallbackInstance) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  objCallInfo = " & strCallInfoMsg & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strMsg
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
        
        Exit Sub
    End If
    
    '
    'process TE_CALLMEDIA
    '
    
    If TapiEvent = TE_CALLMEDIA Then
    
        Dim lEvent As CALL_MEDIA_EVENT
        Dim lCause As CALL_MEDIA_EVENT_CAUSE
        Dim lError As Long
        Dim strStreamName As String, strTermName As String
        Dim lStreamMediaType As Long, lTermMediaType As Long
        Dim lStreamDirection As TERMINAL_DIRECTION, lTermDirection As TERMINAL_DIRECTION
        
        Dim objITCallMediaEvent As ITCallMediaEvent
        Set objITCallMediaEvent = pEvent
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objITCallMediaEvent = pEvent")
        If nResult <> NO_ERROR Then Exit Sub
        
        lEvent = objITCallMediaEvent.Event
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Event")
        If nResult <> NO_ERROR Then Exit Sub
        
        lCause = objITCallMediaEvent.Cause
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Cause")
        If nResult <> NO_ERROR Then Exit Sub
        
        lError = objITCallMediaEvent.Error
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Error")
        If nResult <> NO_ERROR Then Exit Sub
        
        If Not (objITCallMediaEvent.Stream Is Nothing) Then
            strStreamName = objITCallMediaEvent.Stream.Name
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Stream.Name")
            If nResult <> NO_ERROR Then Exit Sub
            
            lStreamMediaType = objITCallMediaEvent.Stream.MediaType
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Stream.MediaType")
            If nResult <> NO_ERROR Then Exit Sub
            
            lStreamDirection = objITCallMediaEvent.Stream.Direction
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Stream.Direction")
            If nResult <> NO_ERROR Then Exit Sub
            
        Else
            strStreamName = "no stream"
        End If
                
        If Not (objITCallMediaEvent.Terminal Is Nothing) Then
            strTermName = objITCallMediaEvent.Terminal.Name
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Terminal.Name")
            If nResult <> NO_ERROR Then Exit Sub
            
            lTermMediaType = objITCallMediaEvent.Terminal.MediaType
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Terminal.MediaType")
            If nResult <> NO_ERROR Then Exit Sub
            
            lTermDirection = objITCallMediaEvent.Terminal.Direction
            nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Terminal.Direction")
            If nResult <> NO_ERROR Then Exit Sub
            
        Else
            strTermName = "no terminal"
        End If
        
        '
        Set objReceivedCallInfo = objITCallMediaEvent.Call
        nResult = PrintT3Result("mobjTapiWithEvents_Event: objITCallMediaEvent.Call")
        If nResult <> NO_ERROR Then Exit Sub
        
        '
        'check if the received CallInfo matches the call
        'for which our app currently keeps a reference of.
        '
        Set objCurrentCallInfo = mobjCall
        nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCurrentCallInfo = mobjCall")
        If nResult <> NO_ERROR Then Exit Sub
        
        If objCurrentCallInfo Is objReceivedCallInfo Then
            strCallInfoMsg = "matches current call"
        Else
            strCallInfoMsg = "doesn't match current call! (error)"
            MsgBox ("Call object received in TE_CALLMEDIA doesn't match current call!")
        End If
        Set objCurrentCallInfo = Nothing
                
                
        Set objReceivedCallInfo = Nothing
        Set objITCallMediaEvent = Nothing
    
    
        strMsg = "Event type = TE_CALLMEDIA: "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  " & _
            "lEvent = 0x" & Hex(lEvent) & " " & TranslateCallMediaEvent(lEvent) & ", " & _
            "lCause = 0x" & Hex(lCause) & " " & TranslateCallMediaEventCause(lCause) & ", " & _
            "lError = 0x" & Hex(lError) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  " & _
            "stream = " & "'" & strStreamName & "'" & ", " & _
            "mediatype = 0x" & Hex(lStreamMediaType) & ", " & _
            "direction = 0x" & Hex(lStreamDirection) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  " & _
            "terminal = " & "'" & strTermName & "'" & ", " & _
            "mediatype = 0x" & Hex(lTermMediaType) & ", " & _
            "direction = 0x" & Hex(lTermDirection) & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        strMsg = strMsg & "  objCallInfo = " & strCallInfoMsg & " "
        strMsg = strMsg & Chr(13) & Chr(10)
        
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strMsg
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
        
        Exit Sub
    End If
        
    '
    'discard all events we're not interested in
    '
    
    If TapiEvent <> TE_CALLSTATE Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Event type <> TE_CALLSTATE ignored."
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0

        Exit Sub
    End If
    
    '
    'process CallStateEvent-s
    '
    
    'pEvent is an object; query its ITCallStateEvent interface
    Set objCallStateEvent = pEvent
    nResult = PrintT3Result("mobjTapiWithEvents_Event: Set objCallStateEvent = pEvent")
    If nResult <> NO_ERROR Then
        Call MsgBox("Fatal error: can't query for call state event, exit program", vbCritical)
        Stop    'fatal error
    End If
    
    CallState = objCallStateEvent.State
    nResult = PrintT3Result("mobjTapiWithEvents_Event: objCallStateEvent.State")
    If nResult <> NO_ERROR Then
        Call MsgBox("Fatal error: can't retrieve new call state, exit program", vbCritical)
        Stop    'fatal error
    End If
    
    PrintCallState (CallState)
    
    If CallState = CS_DISCONNECTED Then
'
'don't release call here, let the user do this by pressing "Release"
'
'        'release call, you don't need it anymore
'        Set mobjCall = Nothing
'
'        'update UI
'        pbDial.Enabled = True
'        pbDisconnect.Enabled = False
'        pbRelease.Enabled = False
'
'        pbGenerate.Enabled = False
'        pbStartDetect.Enabled = False
'        pbStopDetect.Enabled = False

'
'but since call was disconnected, we still need to update the UI
'
        'update UI
        pbDisconnect.Enabled = False
        pbRelease.Enabled = True
    
    End If
    
    'release all objects that aren't needed anymore
    
    Set objCallStateEvent = Nothing
    Exit Sub

End Sub

Private Sub pbDial_Click()
On Error Resume Next        'this will catch errors
    
    Dim nResult As Long
    Dim nOrigAddressIndex As Long
    Dim strDestAddress As String
    Dim MyError As Long
    
    'second call not supported by this app
    If Not (mobjCall Is Nothing) Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Cannot connect new call. Wait for the previous one to be disconnected."
        
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
    
        Exit Sub
    End If
    
    'check if user typed input data
    strDestAddress = txtDestAddress.Text
    If strDestAddress = "" Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Enter destination addres!"
        
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
    
        Exit Sub
    End If
    
    If mobjOrigAddress Is Nothing Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Select origination address!"
        
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
    
        Exit Sub
    End If
    
    '
    'create the call
    '
    Set mobjCall = mobjOrigAddress.CreateCall( _
        strDestAddress, GetAddressType(mobjOrigAddress), TAPIMEDIATYPE_AUDIO)
    
    nResult = PrintT3Result("pbDial_Click: mobjOrigAddress.CreateCall")
    If nResult <> NO_ERROR Then Exit Sub
    
    '
    'select on the call the Terminals (ignore returned error code)
    '
    
    If cbSelectTerminals.Value = Checked Then
        Call SelectTerminalsOnStreams(mobjCall, mvarArrAudioTerminals)
    End If
    
    '
    'Connect the call; False means that the call is made asynchronously.
    'The call to Connect will return immediately, before the call
    'gets to "connected" state; events will fire each time the
    'state of the call changes (to "connected", "disconnected"),
    'meanwhile the application can go on.
    '
    On Error Resume Next
    mobjCall.Connect (False)
    If Err.Number <> 0 Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "Connect failed."
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0

        Err.Clear
        
        'don't need this failed call anymore
        Set mobjCall = Nothing
    
    Else
        'update UI
        pbDial.Enabled = False
        pbDisconnect.Enabled = True
        pbRelease.Enabled = False
        
        pbGenerate.Enabled = True
        pbStartDetect.Enabled = True
        pbStopDetect.Enabled = True
        
    End If
    
End Sub

Private Sub pbDisconnect_Click()
    
    Dim nResult As Long
    
    If mobjCall Is Nothing Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "There is no call to be disconnected."
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0

        Exit Sub
    End If
    
    mobjCall.Disconnect (DC_NORMAL)
    nResult = PrintT3Result("pbDisconnect_Click: mobjCall.Disconnect")
    If nResult <> NO_ERROR Then Exit Sub
    
End Sub

Private Sub pbRelease_Click()

    'release call
    If mobjCall Is Nothing Then
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & "There is no call to be released."
    
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0

        Exit Sub
    End If
    
    Set mobjCall = Nothing
    
    'update UI
    pbDial.Enabled = True
    pbDisconnect.Enabled = False
    pbRelease.Enabled = False

    pbGenerate.Enabled = False
    pbStartDetect.Enabled = False
    pbStopDetect.Enabled = False

End Sub
    
'
'This function inspects the given address to see what address types
'it supports, and then, for simplicity, returns only one.
'
'We will use the following "priority": domain, phone number, sdp, ipaddress;
'the one that is found first is returned.
'
'Example:
'Modem addresses support the following address types:
' - LINEADDRESSTYPE_PHONENUMBER
'IPCONF address support the following address types:
' - LINEADDRESSTYPE_SDP
'H323 addresses support the followinga address types:
' - LINEADDRESSTYPE_DOMAINNAME
' - LINEADDRESSTYPE_IPADDRESS
' - LINEADDRESSTYPE_PHONENUMBER
'
'The function is written in such a way so that it returns "phone number"
'for modem addresses, "domainname" for h323 addresses and "sdp" for ipconf addresses.
'
'This is for the simplicity of the sample, so that we don't add more UI to ask
'the user to specify the desired address type.
'
Private Function GetAddressType(objAddress As ITAddress) As Long
    
    Dim nResult As Long
    
    'prepare return value
    GetAddressType = 0
    
    'query the interface ITAddressCapabilities
    
    Dim objITAddressCapabilities As ITAddressCapabilities
    Set objITAddressCapabilities = objAddress
    nResult = PrintT3Result("GetAddressType: Set objITAddressCapabilities = objAddress")
    If nResult <> NO_ERROR Then Exit Function
    
    'decide what address type to return
    
    Dim lAddressTypes As Long
    
    lAddressTypes = objITAddressCapabilities.AddressCapability(AC_ADDRESSTYPES)
    nResult = PrintT3Result("GetAddressType: objITAddressCapabilities.AddressCapability(AC_ADDRESSTYPES)")
    If nResult <> NO_ERROR Then Exit Function
    
    If (lAddressTypes And LINEADDRESSTYPE_DOMAINNAME) Then
        GetAddressType = LINEADDRESSTYPE_DOMAINNAME
    ElseIf (lAddressTypes And LINEADDRESSTYPE_PHONENUMBER) Then
        GetAddressType = LINEADDRESSTYPE_PHONENUMBER
    ElseIf (lAddressTypes And LINEADDRESSTYPE_SDP) Then
        GetAddressType = LINEADDRESSTYPE_SDP
    ElseIf (lAddressTypes And LINEADDRESSTYPE_IPADDRESS) Then
        GetAddressType = LINEADDRESSTYPE_IPADDRESS
    End If
    
    Set objITAddressCapabilities = Nothing
    
    'done
    Exit Function
End Function

'
'Finds out what are the default terminals for audio+capture and audio+render,
'on the received address (there might be none);
'makes an array with all of them, then puts them in the received variant;
'If no terminal found for any of the audio+direction combinations,
'"Nothing" (a NULL terminal pointer) will be set at the corresponding index.
'
Private Sub GetAudioTerminals(ByVal objAddress As ITAddress, _
    ByRef rVarArrTerminals As Variant)
On Error Resume Next        'this will catch errors
    
    '
    'prepare return values
    '
    rVarArrTerminals = Empty
    
    Dim nResult As Long
    Dim objTerminalSupport As ITTerminalSupport
    
    '
    'put terminals in array, then put array in variant
    '
    
    'decide dimension of array
    Dim arrTerminals(1 To 2) As ITTerminal
    
    'put the array in a variant
    rVarArrTerminals = arrTerminals
    
    '
    'query terminals and put them in variant (the variant contains an array already)
    'if no terminal found, Nothing will be put in the corresponding items.
    '
    Set objTerminalSupport = objAddress
    
    If Not (objTerminalSupport Is Nothing) Then
    
        'index 1 = the terminal for audio+capture
        Set rVarArrTerminals(1) = objTerminalSupport.GetDefaultStaticTerminal( _
            TAPIMEDIATYPE_AUDIO, TD_CAPTURE)
        nResult = PrintT3Result("GetAudioTerminals: get default terminal for audio+capture")
        
        'index 2 = the terminal for audio+render
        Set rVarArrTerminals(2) = objTerminalSupport.GetDefaultStaticTerminal( _
            TAPIMEDIATYPE_AUDIO, TD_RENDER)
        nResult = PrintT3Result("GetAudioTerminals: get default terminal for audio+render")
    Else
        Set rVarArrTerminals(1) = Nothing
        Set rVarArrTerminals(2) = Nothing
    End If
        
    Set objTerminalSupport = Nothing
    
End Sub

'
'It receives a variant that contains an array of terminals,
'that might contain 0, 1 or 2 terminals (whatever was found as the
'default terminals for audio+in and audio+out); actually the array
'will always have 2 elements, which can be "Nothing" or "Not Nothing"
'
Private Sub ReleaseAudioTerminals(ByRef rVarArrTerminals As Variant)
On Error Resume Next        'this will catch errors

    Dim nIndex As Long
    
    'release terminals
    
    If IsArray(rVarArrTerminals) Then
        For nIndex = LBound(rVarArrTerminals) To UBound(rVarArrTerminals)
            Set rVarArrTerminals(nIndex) = Nothing
        Next nIndex
    End If
    
    'release the array of terminals
    
    rVarArrTerminals = Empty
    
End Sub

Private Sub pbGenerate_Click()
On Error Resume Next        'this will catch errors
        
    Debug.Assert (Not (mobjCall Is Nothing))
        
    Dim nResult As Long
    
    Dim objITLegacyCallMediaControl As ITLegacyCallMediaControl
    
    'get the interface that allows us to generate digits
    Set objITLegacyCallMediaControl = mobjCall
    nResult = PrintT3Result("pbGenerate_Click: Set objITLegacyCallMediaControl = mobjCall")
    If nResult <> NO_ERROR Then Exit Sub
    
    'call GenerateDigits; this might return errors, because we let the
    'user select any digit modes in the same time.
    
    If 0 = StrComp(txtDigitsToGenerate, "Null", vbTextCompare) Then
        'give user a possibility to pass NULL string pointer as "txtDigitsToGenerate"
        Call objITLegacyCallMediaControl.GenerateDigits(vbNullString, GetDigitMode)
    ElseIf 0 = StrComp(txtDigitsToGenerate, "Empty", vbTextCompare) Then
        'give user a possibility to pass an empty string ("") as "txtDigitsToGenerate"
        Call objITLegacyCallMediaControl.GenerateDigits("", GetDigitMode)
    Else
        Call objITLegacyCallMediaControl.GenerateDigits(txtDigitsToGenerate, GetDigitMode)
    End If
    
    'print error, if any
    nResult = PrintT3Result("ITLegacyCallMediaControl.GenerateDigits")
    
    'release all
    Set objITLegacyCallMediaControl = Nothing
    
End Sub

'Read value from "digit mode" check boxes, and or the corresponding
'flags; this is usefull for parameter testing; unimodem should only work
'with DTMF
Function GetDigitMode() As Long
    
    GetDigitMode = 0
    
    If cbModeDTMF.Value = Checked Then
        GetDigitMode = GetDigitMode Or LINEDIGITMODE_DTMF
    End If
    If cbModeDTMFEND.Value = Checked Then
        GetDigitMode = GetDigitMode Or LINEDIGITMODE_DTMFEND
    End If
    If cbModePulse.Value = Checked Then
        GetDigitMode = GetDigitMode Or LINEDIGITMODE_PULSE
    End If
    
End Function

Private Sub cbModeDTMF_Click()
    If cbModeDTMF.Value = Checked Then
        'display possible values
        txtDigitsToGenerate.Text = "0123456789ABCD*#"
    End If
End Sub

Private Sub cbModeDTMFEND_Click()
    If cbModeDTMFEND.Value = Checked Then
        'display possible values
        txtDigitsToGenerate.Text = ""   'no digits can be generated in DTMFEND mode
    End If
End Sub

Private Sub cbModePulse_Click()
    If cbModePulse.Value = Checked Then
        'display possible values
        txtDigitsToGenerate.Text = "0123456789"
    End If
End Sub

Private Sub pbStartDetect_Click()
On Error Resume Next        'this will catch errors
    
    Debug.Assert (Not (mobjCall Is Nothing))
        
    Dim nResult As Long
    
    Dim objITLegacyCallMediaControl As ITLegacyCallMediaControl
    
    'get the interface that allows us to turn on digit detection
    Set objITLegacyCallMediaControl = mobjCall
    nResult = PrintT3Result("pbStartDetect_Click: Set objITLegacyCallMediaControl = mobjCall")
    If nResult <> NO_ERROR Then Exit Sub
    
    'call DetectDigits; this might return errors, because we let the
    'user select any digit modes.
    Call objITLegacyCallMediaControl.DetectDigits(GetDigitMode())
    
    'print error, if any
    nResult = PrintT3Result("ITLegacyCallMediaControl.DetectDigits" & _
        "(" & GetDigitMode() & ")")
    
    'release all
    Set objITLegacyCallMediaControl = Nothing
    
End Sub

Private Sub pbStopDetect_Click()
On Error Resume Next        'this will catch errors
    
    Debug.Assert (Not (mobjCall Is Nothing))
        
    Dim nResult As Long
    
    Dim objITLegacyCallMediaControl As ITLegacyCallMediaControl
    
    'get the interface that allows us to turn off digit detection
    Set objITLegacyCallMediaControl = mobjCall
    nResult = PrintT3Result("pbStopDetect_Click: Set objITLegacyCallMediaControl = mobjCall")
    If nResult <> NO_ERROR Then Exit Sub
    
    'call DetectDigits(0); this might return errors
    Call objITLegacyCallMediaControl.DetectDigits(0)
    
    'print error, if any
    nResult = PrintT3Result("ITLegacyCallMediaControl.DetectDigits(0)")
    
    'release all
    Set objITLegacyCallMediaControl = Nothing
    
End Sub

Function TranslateDigitMode(nDigitMode) As String
    
    Select Case nDigitMode
        Case LINEDIGITMODE_PULSE
            TranslateDigitMode = "LINEDIGITMODE_PULSE"
        Case LINEDIGITMODE_DTMF
            TranslateDigitMode = "LINEDIGITMODE_DTMF"
        Case LINEDIGITMODE_DTMFEND
            TranslateDigitMode = "LINEDIGITMODE_DTMFEND"
        Case Else
            TranslateDigitMode = "Unknown Digit Mode = " & nDigitMode & " !"
    End Select

End Function

Function TranslateGenerateTerm(lGenerationTermination) As String
    
    Select Case lGenerationTermination
        Case LINEGENERATETERM_DONE
            TranslateGenerateTerm = "LINEGENERATETERM_DONE"
        Case LINEGENERATETERM_CANCEL
            TranslateGenerateTerm = "LINEGENERATETERM_CANCEL"
        Case Else
            TranslateGenerateTerm = "Unknown GenerationTermination value = " & lGenerationTermination & " !"
    End Select

End Function

Function TranslateCallMediaEvent(lCallMediaEvent) As String
    
    Select Case lCallMediaEvent
        Case CME_NEW_STREAM
            TranslateCallMediaEvent = "CME_NEW_STREAM"
        Case CME_STREAM_ACTIVE
            TranslateCallMediaEvent = "CME_STREAM_ACTIVE"
        Case CME_STREAM_FAIL
            TranslateCallMediaEvent = "CME_STREAM_FAIL"
        Case CME_STREAM_INACTIVE
            TranslateCallMediaEvent = "CME_STREAM_INACTIVE"
        Case CME_STREAM_NOT_USED
            TranslateCallMediaEvent = "CME_STREAM_NOT_USED"
        Case CME_TERMINAL_FAIL
            TranslateCallMediaEvent = "CME_TERMINAL_FAIL"
        Case Else
            TranslateCallMediaEvent = "Unknown CallMediaEvent = " & lCallMediaEvent & " !"
    End Select

End Function

Function TranslateCallMediaEventCause(lCallMediaEventCause) As String
    
    Select Case lCallMediaEventCause
        Case CMC_BAD_DEVICE
            TranslateCallMediaEventCause = "CMC_BAD_DEVICE"
        Case CMC_CONNECT_FAIL
            TranslateCallMediaEventCause = "CMC_CONNECT_FAIL"
        Case CMC_LOCAL_REQUEST
            TranslateCallMediaEventCause = "CMC_LOCAL_REQUEST"
        Case CMC_MEDIA_RECOVERED
            TranslateCallMediaEventCause = "CMC_MEDIA_RECOVERED"
        Case CMC_MEDIA_TIMEOUT
            TranslateCallMediaEventCause = "CMC_MEDIA_TIMEOUT"
        Case CMC_REMOTE_REQUEST
            TranslateCallMediaEventCause = "CMC_REMOTE_REQUEST"
        Case CMC_UNKNOWN
            TranslateCallMediaEventCause = "CMC_UNKNOWN"
        Case Else
            TranslateCallMediaEventCause = "Unknown CallMediaEventCause = " & lCallMediaEventCause & " !"
    End Select

End Function

'Looks in combo with addresses and sees what address was selected.
'Looks in the related "data" field and finds out the index memorized for
'that address. This index represents the index in the objTapi.objcollAddresses.
'Return 0 if no address is selected.
'Otherwise return its index, which should be a value between 1 and Addresses.Count
Private Function FindOriginationAddressIndex() As Long
On Error Resume Next        'this will catch errors
    
    Dim nResult As Long
    Dim indexAddr As Long
    
    'prepare return value
    FindOriginationAddressIndex = 0
    
    If cmbAddresses.ListCount > 0 Then
        
        'read data field of selected combo item
        indexAddr = cmbAddresses.ItemData(cmbAddresses.ListIndex)
        nResult = PrintT3Result("FindOriginationAddressIndex: retrieve selected address from combo")
        
        If nResult = NO_ERROR Then
            FindOriginationAddressIndex = indexAddr
        End If
    End If
    
    Exit Function
End Function

'Returns the last tapi3 error that caused the function to fail,
'or NO_ERROR if there were no tapi3 failures.
'(i.e.: don't return error codes produced inside error handlers)
Private Function InitializeTapiObjects() As Long
On Error Resume Next
        
    Dim nResult As Long
    
    If mbInitialized = True Then
        InitializeTapiObjects = NO_ERROR
        Exit Function
    End If
        
    txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
    txtStatus.Text = txtStatus.Text & "Tapi initialization: start..."
    
    txtStatus.SelStart = Len(txtStatus.Text)
    txtStatus.SelLength = 0

    frmDTMF.Refresh
    
    'create the Tapi object
    
    Set mobjTapi = New TAPI
    
    nResult = PrintT3Result("New TAPI")
    If nResult <> NO_ERROR Then
        GoTo ErrorExit
    End If
    
    'call Initialize; this must be called before
    'any other tapi functions are called.
    
    mobjTapi.Initialize
    
    nResult = PrintT3Result("objTapi.Initialize")
    If nResult <> NO_ERROR Then
        
        'release tapi object
        
        Set mobjTapi = Nothing
        
        PrintT3Result ("Release objTapi")
       
        GoTo ErrorExit
    End If
    
    'set the EventFilter to accept all defined tapi events
    
    mobjTapi.EventFilter = TAPI3_ALL_TAPI_EVENTS
    
    nResult = PrintT3Result("set objTapi.EventFilter")
    If nResult <> NO_ERROR Then
        
        'shutdown tapi
        
        mobjTapi.Shutdown
            
        PrintT3Result ("objTapi.Shutdown")
        
        'release tapi object
        
        Set mobjTapi = Nothing
            
        PrintT3Result ("Release objTapi")
        
        GoTo ErrorExit
    End If
    
    'register the outgoing interface that will receive the events
    'this is the equivalent of calling "Advise" in c/c++
    
    Set mobjTapiWithEvents = mobjTapi
    
    nResult = PrintT3Result("set objTapiWithEvents")
    If nResult <> NO_ERROR Then
        
        'shutdown tapi
        
        mobjTapi.Shutdown
            
        PrintT3Result ("objTapi.Shutdown")
        
        'release tapi object
        
        Set mobjTapi = Nothing
            
        PrintT3Result ("Release objTapi")
        
        GoTo ErrorExit
    End If
    
NormalExit:
    txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
    txtStatus.Text = txtStatus.Text & "Tapi initialization: finished."
    
    txtStatus.SelStart = Len(txtStatus.Text)
    txtStatus.SelLength = 0

    frmDTMF.Refresh
    
    mbInitialized = True
    InitializeTapiObjects = NO_ERROR
    Exit Function
    
ErrorExit:
    txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
    txtStatus.Text = txtStatus.Text & "Tapi initialization: failed."
    
    txtStatus.SelStart = Len(txtStatus.Text)
    txtStatus.SelLength = 0

    frmDTMF.Refresh
    
    mbInitialized = False
    InitializeTapiObjects = nResult
    Exit Function
End Function

Private Function ReleaseAllMembers() As Long
    
    If mbInitialized = False Then
        Exit Function
    End If
    
    'release all member objects
    
    Set mobjCall = Nothing
    
    Call ReleaseAudioTerminals(mvarArrAudioTerminals)
    
    Set mobjOrigAddress = Nothing
    
    Debug.Assert (Not (mobjTapi Is Nothing))
    
    Set mobjTapiWithEvents = Nothing
    mobjTapi.Shutdown
    Set mobjTapi = Nothing
    
End Function

'
'This function receives a call object and an array with the terminals
'to be selected;
'- it first queries the stream control object from the call object;
'- it then selects each terminal on a stream that matches
'the media type and the terminal direction.
'
'If an error is encountered, the function finishes right away and returns
'that error.
'
'Notes:
' 1 - the received array might contain "Null" terminals (the value Nothing)
'in its items - so we need to check the termials before using them.
' 2 - ITStreamControl is not supported on all addresses (depending on the TSP)
'therefore querying for this interface might fail.
'
Public Function SelectTerminalsOnStreams( _
    objITBCC As ITBasicCallControl, _
    varArrTerminals As Variant) _
    As TestError
On Error Resume Next
    
    Dim MyError As TestError
    SelectTerminalsOnStreams = TErr_Ok
    
    Dim nTermIndex As Long
    
    'get stream control object
    
    Dim objITStreamControl As ITStreamControl
    
    Set objITStreamControl = objITBCC
    MyError = PrintT3Result("Set objITStreamControl = objITBCC")
    If MyError <> 0 Then
        SelectTerminalsOnStreams = TErr_Fail
        Exit Function
    End If
    
    'get streams collection object
    
    Dim objITCollStreams As ITCollection
    
    Set objITCollStreams = objITStreamControl.Streams
    MyError = PrintT3Result("objITStreamControl.Streams")
    If MyError <> 0 Then
        Set objITStreamControl = Nothing
        PrintT3Result ("Set objITStreamControl = Nothing")
        
        SelectTerminalsOnStreams = TErr_Fail
        Exit Function
    End If
    
    'find matching stream for each terminal and select the terminal
    
    Dim objCrtITStream As ITStream
    
    For nTermIndex = LBound(varArrTerminals) To UBound(varArrTerminals)
    
        If Not (varArrTerminals(nTermIndex) Is Nothing) Then
        
            'find matching stream
            MyError = FindMatchingStream( _
                objITCollStreams, varArrTerminals(nTermIndex), objCrtITStream)
            If MyError = TErr_Fail Then
                Set objITCollStreams = Nothing
                PrintT3Result ("Set objITCollStreams = Nothing")
                
                Set objITStreamControl = Nothing
                PrintT3Result ("Set objITStreamControl = Nothing")
            
                SelectTerminalsOnStreams = TErr_Fail
                Exit Function
            End If
            
            'select terminal
            Call objCrtITStream.SelectTerminal(varArrTerminals(nTermIndex))
            MyError = PrintT3Result("objCrtITStream.SelectTerminal")
            If MyError <> 0 Then
            
                Set objCrtITStream = Nothing
                PrintT3Result ("Set objCrtITStream = Nothing")
                
                Set objITCollStreams = Nothing
                PrintT3Result ("Set objITCollStreams = Nothing")
                
                Set objITStreamControl = Nothing
                PrintT3Result ("Set objITStreamControl = Nothing")
            
                SelectTerminalsOnStreams = TErr_Fail
                Exit Function
            End If
            
            'release stream
            Set objCrtITStream = Nothing
            PrintT3Result ("Set objCrtITStream = Nothing")
            
        End If
        
    Next nTermIndex
    
    'release all not needed objects
    Set objITCollStreams = Nothing
    PrintT3Result ("Set objITCollStreams = Nothing")
    
    Set objITStreamControl = Nothing
    PrintT3Result ("Set objITStreamControl = Nothing")
    
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
    
    Dim MyError As TestError
    FindMatchingStream = TErr_Ok
    
    'initialize return value
    Set robjITStream = Nothing
    
    'read media type and direction from terminal
    
    Dim lMediaType As Long, lDirection As TERMINAL_DIRECTION
    
    lMediaType = objITTerminal.MediaType
    MyError = PrintT3Result("objITTerminal.MediaType")
    If MyError <> 0 Then
        FindMatchingStream = TErr_Fail
        Exit Function
    End If
    
    lDirection = objITTerminal.Direction
    MyError = PrintT3Result("objITTerminal.Direction")
    If MyError <> 0 Then
        FindMatchingStream = TErr_Fail
        Exit Function
    End If
    
    'search stream that matches this media and direction
    
    Dim nCount As Long, nIndex As Long
    Dim objCrtStream As ITStream
    Dim lCrtMediaType As Long, lCrtDirection As TERMINAL_DIRECTION
    
    nCount = objITCollStreams.Count
    MyError = PrintT3Result("objITCollStreams.Count")
    If MyError <> 0 Then
        FindMatchingStream = TErr_Fail
        Exit Function
    End If
    
    For nIndex = 1 To nCount
        
        Set objCrtStream = objITCollStreams.Item(nIndex)
        MyError = PrintT3Result("objITCollStreams.Item(nIndex)")
        If MyError <> 0 Then
            FindMatchingStream = TErr_Fail
            Exit Function
        End If
        
        lCrtMediaType = objCrtStream.MediaType
        MyError = PrintT3Result("objCrtStream.MediaType")
        If MyError <> 0 Then
        
            Set objCrtStream = Nothing
            PrintT3Result ("Set objCrtStream = Nothing")
            
            FindMatchingStream = TErr_Fail
            Exit Function
        End If
        
        lCrtDirection = objCrtStream.Direction
        MyError = PrintT3Result("objCrtStream.Direction")
        If MyError <> 0 Then
            
            Set objCrtStream = Nothing
            PrintT3Result ("Set objCrtStream = Nothing")
            
            FindMatchingStream = TErr_Fail
            Exit Function
        End If
        
        If lMediaType = lCrtMediaType And lDirection = lCrtDirection Then
            'set return value
            Set robjITStream = objCrtStream
            PrintT3Result ("Set robjITStream = objCrtStream")
            
            'quit loop, we're done
            Set objCrtStream = Nothing
            PrintT3Result ("Set objCrtStream = Nothing")
            Exit For
        End If
        
        Set objCrtStream = Nothing
        PrintT3Result ("Set objCrtStream = Nothing")
        
    Next nIndex
    
    Exit Function
End Function

'Reads the last error from Err object
'If Err.Number = 0, it means that no error had occurred.
'Returns the error code found in Err.Number when this function is called.
'Before returning, it clears the error.
'
Private Function PrintT3Result(strT3Action As String) As Long
    
    PrintT3Result = NO_ERROR
    
    'log the tapi3 function name that produced this result
    'and, if error, print also error number + description
    
    PrintT3Result = Err.Number
    
    Dim strError As String
    
    If Err.Number = NO_ERROR Then
        strError = "Succes: "
        strError = strError & strT3Action
    
        'success has low logging level
        Debug.Print (strError)
    Else
        strError = "Error: "
        strError = strError & strT3Action & " Err.Number = 0x" & Hex(Err.Number)
        strError = strError & " Err.Descripton = " & Err.Description
    
        'error has high logging level
        Debug.Print (strError)
        txtStatus.Text = txtStatus.Text & Chr(13) & Chr(10)
        txtStatus.Text = txtStatus.Text & strError
        
        txtStatus.SelStart = Len(txtStatus.Text)
        txtStatus.SelLength = 0
    
    End If
    
    Err.Clear
    
End Function
