Attribute VB_Name = "Tools"

'
'--------------------------------------------------------------------------
'
'  Copyright (C) 1997-1999 Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
'
'Tools.bas
'

Option Explicit

Public Const NO_ERROR = 0                  'Err.Number = 0 when there is no error

Public Function GetAllAddresses(objTAPI As TAPI) As Variant
On Error Resume Next
    
    Dim arrAddresses() As ITAddress
    
    Dim objCrtAddress As ITAddress
    Dim nAddrCount As Long
    
    nAddrCount = 0
    For Each objCrtAddress In objTAPI.Addresses
        
        nAddrCount = nAddrCount + 1
        
        ReDim Preserve arrAddresses(1 To nAddrCount)
        
        Set arrAddresses(nAddrCount) = objCrtAddress
        
        Set objCrtAddress = Nothing
    Next
    
    GetAllAddresses = arrAddresses
    
End Function

Public Function FreeAddresses(varArrAddresses As Variant) As Long
On Error Resume Next

    Dim nIndex
    
    If IsArray(varArrAddresses) Then
        For nIndex = LBound(varArrAddresses) To UBound(varArrAddresses)
            Set varArrAddresses(nIndex) = Nothing
            Call CheckError("FreeAddresses: Releasing varArrAddresses(" & nIndex & ")")
        Next nIndex
    End If
    
End Function

Public Function PrintEvent(TapiEvent As TAPI_EVENT) As Long

    Dim strEvent As String
    
    Select Case TapiEvent
                
        Case TE_CALLHUB
            strEvent = "Tapi_Event: TE_CALLHUB"
        
        Case TE_CALLNOTIFICATION
            strEvent = "Tapi_Event: TE_CALLNOTIFICATION"
        Case TE_CALLSTATE
            strEvent = "Tapi_Event: TE_CALLSTATE"
        
        Case TE_ADDRESS
            strEvent = "Tapi_Event: TE_ADDRESS"
            
        Case TE_CALLINFOCHANGE
            strEvent = "Tapi_Event: TE_CALLINFOCHANGE"
        
        Case TE_DIGITEVENT
            strEvent = "Tapi_Event: TE_DIGITEVENT"
        Case TE_GENERATEEVENT
            strEvent = "Tapi_Event: TE_GENERATEEVENT"
        
        Case TE_CALLMEDIA
            strEvent = "Tapi_Event: TE_CALLMEDIA"
        Case TE_PRIVATE
            strEvent = "Tapi_Event: TE_PRIVATE"
        Case TE_TAPIOBJECT
            strEvent = "Tapi_Event: TE_TAPIOBJECT"
        Case TE_REQUEST
            strEvent = "Tapi_Event: TE_REQUEST"
            
        Case TE_ACDGROUP
            strEvent = "Tapi_Event: TE_ACDGROUP"
        Case TE_AGENT
            strEvent = "Tapi_Event: TE_AGENT"
        Case TE_AGENTHANDLER
            strEvent = "Tapi_Event: TE_AGENTHANDLER"
        Case TE_AGENTSESSION
            strEvent = "Tapi_Event: TE_AGENTSESSION"
        Case TE_QOSEVENT
            strEvent = "Tapi_Event: TE_QOSEVENT"
        Case TE_QUEUE
            strEvent = "Tapi_Event: TE_QUEUE"
        
        
        Case Else
            strEvent = "Tapi_Event: Unknown Event!"
            
    End Select
    
    'let's put an extra line before a new event, to space them in the output window.
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
End Function

Public Function PrintCallNotificationEvent( _
    CallNotificationEvent As CALL_NOTIFICATION_EVENT) As Long
    
    Dim strEvent As String
    
    Select Case CallNotificationEvent
                
        Case CNE_MONITOR
            strEvent = "Call_Notification_Event: CNE_MONITOR"
        Case CNE_OWNER
            strEvent = "Call_Notification_Event: CNE_OWNER"
        
        Case Else
            strEvent = "Call_Notification_Event: Unknown Event (CNE_)!"
    End Select
    
    '
    'in fact, this application is now registered only for monitoring,
    'so it should only receive monitor events;
    '
    If CallNotificationEvent <> CNE_MONITOR Then
        MsgBox ("ERROR: call notification event <> CNE_MONITOR!")
    End If
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh

End Function

'
'this will print: call state, cause, and callbackinstance
'
Public Function PrintCallStateEvent( _
    objITCallStateEvent As ITCallStateEvent) As Long
On Error Resume Next

    Dim nResult As Long
    
    Dim State As CALL_STATE
    Dim Cause As CALL_STATE_EVENT_CAUSE
    Dim lCallbackInstance As Long
    
    State = objITCallStateEvent.State
    nResult = CheckError("PrintCallStateEvent: objITCallStateEvent.State")
    If nResult <> NO_ERROR Then Exit Function
    
    Cause = objITCallStateEvent.Cause
    nResult = CheckError("PrintCallStateEvent: objITCallStateEvent.Cause")
    If nResult <> NO_ERROR Then Exit Function
    
    lCallbackInstance = objITCallStateEvent.CallbackInstance
    nResult = CheckError("PrintCallStateEvent: objITCallStateEvent.CallbackInstance")
    If nResult <> NO_ERROR Then Exit Function
    
    '
    'print call state
    '
    Dim strState As String
    
    strState = "CallState: " & TranslateCallState(State)
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strState
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh

    '
    'print call state event cause
    '
    Dim strCause As String
    
    Select Case Cause
                
        Case CEC_DISCONNECT_BADADDRESS
            strCause = "CallStateEventCause: CEC_DISCONNECT_BADADDRESS"
        Case CEC_DISCONNECT_BUSY
            strCause = "CallStateEventCause: CEC_DISCONNECT_BUSY"
        Case CEC_DISCONNECT_CANCELLED
            strCause = "CallStateEventCause: CEC_DISCONNECT_CANCELLED"
        Case CEC_DISCONNECT_FAILED
            strCause = "CallStateEventCause: CEC_DISCONNECT_FAILED"
        Case CEC_DISCONNECT_NOANSWER
            strCause = "CallStateEventCause: CEC_DISCONNECT_NOANSWER"
        Case CEC_DISCONNECT_NORMAL
            strCause = "CallStateEventCause: CEC_DISCONNECT_NORMAL"
        Case CEC_DISCONNECT_REJECTED
            strCause = "CallStateEventCause: CEC_DISCONNECT_REJECTED"
        Case CEC_NONE
            strCause = "CallStateEventCause: CEC_NONE"
        
        Case Else
            strCause = "CallStateEventCause: Unknown Event (CEC_)!"
    End Select
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strCause
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
    
    '
    'print callback instance
    '
    Dim strCallbackInstance As String
    
    strCallbackInstance = "CallState-CallbackInstance = 0x" & Hex(lCallbackInstance)
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strCallbackInstance
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh

End Function

Public Function PrintCallHubEvent(CallHubEvent As CALLHUB_EVENT) As Long

    Dim strEvent As String
    
    Select Case CallHubEvent
                
        Case CHE_CALLJOIN
            strEvent = "CallHubEvent: CHE_CALLJOIN"
        Case CHE_CALLLEAVE
            strEvent = "CallHubEvent: CHE_CALLLEAVE"
            
        Case CHE_CALLHUBNEW
            strEvent = "CallHubEvent: CHE_CALLHUBNEW"
        Case CHE_CALLHUBIDLE
            strEvent = "CallHubEvent: CHE_CALLHUBIDLE"
        
        Case Else
            strEvent = "CallHubEvent: Unknown CALLHUB_EVENT (CHE_)!"
    End Select
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh

End Function

Public Function PrintAddressEvent(AddressEvent As ADDRESS_EVENT)

    Dim strEvent As String
    
    Select Case AddressEvent
                
        Case AE_CAPSCHANGE
            strEvent = "AddressEvent: AE_CAPSCHANGE"
        Case AE_CONFIGCHANGE
            strEvent = "AddressEvent: AE_CONFIGCHANGE"
        Case AE_FORWARD
            strEvent = "AddressEvent: AE_FORWARD"
        Case AE_RINGING
            strEvent = "AddressEvent: AE_RINGING"
        Case AE_STATE
            strEvent = "AddressEvent: AE_STATE"
        
        Case Else
            strEvent = "AddressEvent: Unknown ADDRESS_EVENT (AE_)!"
    End Select
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
End Function

Public Function PrintCallInfoChangeEvent( _
    objCallInfoChangeEvent As ITCallInfoChangeEvent) As Long
On Error Resume Next

    Dim nResult As Long
    
    'print CallbackInstance member (this should be the nIndex of the address - see RegisterCallNotifications)
    
    Dim strCallbackInstance As String
    
    strCallbackInstance = _
        "CallInfoChange-CallbackInstance = " & _
        "0x" & Hex(objCallInfoChangeEvent.CallbackInstance)
    nResult = CheckError("PrintCallInfoChangeEvent: objCallInfoChangeEvent.CallbackInstance")
    If nResult <> NO_ERROR Then Exit Function
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strCallbackInstance
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
    
    'print "cause" member
    Dim nCallInfoChangeCause As CALLINFOCHANGE_CAUSE
    nCallInfoChangeCause = objCallInfoChangeEvent.Cause
    nResult = CheckError("PrintCallInfoChangeEvent: objCallInfoChangeEvent.Cause")
    If nResult <> NO_ERROR Then Exit Function

    Call PrintCallInfoChangeCause(nCallInfoChangeCause)
End Function

Public Function PrintCallInfoChangeCause(CallInfoChangeCause As CALLINFOCHANGE_CAUSE)

    Dim strEvent As String
    
    Select Case CallInfoChangeCause
        
        'expected call info change events (for this monitoring app)
        '
        Case CIC_NUMMONITORS
            strEvent = "CallInfoChangeCause: CIC_NUMMONITORS"
        Case CIC_NUMOWNERDECR
            strEvent = "CallInfoChangeCause: CIC_NUMOWNERDECR"
        Case CIC_NUMOWNERINCR
            strEvent = "CallInfoChangeCause: CIC_NUMOWNERINCR"
        
        '
        Case CIC_APPSPECIFIC
            strEvent = "CallInfoChangeCause: CIC_APPSPECIFIC"
        Case CIC_BEARERMODE
            strEvent = "CallInfoChangeCause: CIC_BEARERMODE"
        Case CIC_CALLDATA
            strEvent = "CallInfoChangeCause: CIC_CALLDATA"
        Case CIC_CALLEDID
            strEvent = "CallInfoChangeCause: CIC_CALLEDID"
        Case CIC_CALLERID
            strEvent = "CallInfoChangeCause: CIC_CALLERID"
        Case CIC_CALLID
            strEvent = "CallInfoChangeCause: CIC_CALLID"
        Case CIC_CHARGINGINFO
            strEvent = "CallInfoChangeCause: CIC_CHARGINGINFO"
        Case CIC_COMPLETIONID
            strEvent = "CallInfoChangeCause: CIC_COMPLETIONID"
        Case CIC_CONNECTEDID
            strEvent = "CallInfoChangeCause: CIC_CONNECTEDID"
        Case CIC_DEVSPECIFIC
            strEvent = "CallInfoChangeCause: CIC_DEVSPECIFIC"
        Case CIC_HIGHLEVELCOMP
            strEvent = "CallInfoChangeCause: CIC_HIGHLEVELCOMP"
        Case CIC_LOWLEVELCOMP
            strEvent = "CallInfoChangeCause: CIC_LOWLEVELCOMP"
        Case CIC_MEDIATYPE
            strEvent = "CallInfoChangeCause: CIC_MEDIATYPE"
'these were already listed at the top
'        Case CIC_NUMMONITORS
'            strEvent = "CallInfoChangeCause: CIC_NUMMONITORS"
'        Case CIC_NUMOWNERDECR
'            strEvent = "CallInfoChangeCause: CIC_NUMOWNERDECR"
'        Case CIC_NUMOWNERINCR
'            strEvent = "CallInfoChangeCause: CIC_NUMOWNERINCR"
        Case CIC_ORIGIN
            strEvent = "CallInfoChangeCause: CIC_ORIGIN"
        Case CIC_OTHER
            strEvent = "CallInfoChangeCause: CIC_OTHER"
        Case CIC_PRIVILEGE
            strEvent = "CallInfoChangeCause: CIC_PRIVILEGE"
        Case CIC_RATE
            strEvent = "CallInfoChangeCause: CIC_RATE"
        Case CIC_REASON
            strEvent = "CallInfoChangeCause: CIC_REASON"
        Case CIC_REDIRECTINGID
            strEvent = "CallInfoChangeCause: CIC_REDIRECTINGID"
        Case CIC_REDIRECTIONID
            strEvent = "CallInfoChangeCause: CIC_REDIRECTIONID"
        Case CIC_RELATEDCALLID
            strEvent = "CallInfoChangeCause: CIC_RELATEDCALLID"
        Case CIC_TREATMENT
            strEvent = "CallInfoChangeCause: CIC_TREATMENT"
        Case CIC_TRUNK
            strEvent = "CallInfoChangeCause: CIC_TRUNK"
        Case CIC_USERUSERINFO
            strEvent = "CallInfoChangeCause: CIC_USERUSERINFO"
        
        Case Else
            strEvent = "CallInfoChangeCause: Unknown CALLINFOCHANGE_CAUSE (CIC_)! " & _
                       "Unknown CIC_ value = 0x" & Hex(CallInfoChangeCause)
    End Select
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
End Function

Public Function PrintDigitDetectionEvent(objDigitEvent As ITDigitDetectionEvent)
On Error Resume Next
    Dim nResult As Long
    
    Dim strEvent As String
    strEvent = ""
    
    'already checked if the call is in tree (see gobjTapiWithEvents_Event - IsCallInTree)
    'objDigitEvent.Call
    
    strEvent = strEvent & "DigitDetectionEvent: CallbackInstance = 0x" & _
        Hex(objDigitEvent.CallbackInstance)
    nResult = CheckError("PrintDigitDetectionEvent: objDigitEvent.CallbackInstance")
    If nResult <> NO_ERROR Then Exit Function
    
    strEvent = strEvent & Chr(13) & Chr(10)
    
    strEvent = strEvent & "DigitDetectionEvent: Digit = 0x" & _
        Hex(objDigitEvent.Digit)
    nResult = CheckError("PrintDigitDetectionEvent: objDigitEvent.Digit")
    If nResult <> NO_ERROR Then Exit Function
    
    strEvent = strEvent & Chr(13) & Chr(10)
    
    strEvent = strEvent & "DigitDetectionEvent: DigitMode = " & _
        TranslateDigitMode(objDigitEvent.DigitMode)
    nResult = CheckError("PrintDigitDetectionEvent: objDigitEvent.DigitMode")
    If nResult <> NO_ERROR Then Exit Function
    
    strEvent = strEvent & Chr(13) & Chr(10)
    
    strEvent = strEvent & "DigitDetectionEvent: TickCount = 0x" & _
        Hex(objDigitEvent.TickCount)
    nResult = CheckError("PrintDigitDetectionEvent: objDigitEvent.TickCount")
    If nResult <> NO_ERROR Then Exit Function
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
End Function

Public Function PrintUnexpectedEvent(strEventName As String)

    Dim strEvent As String
    
    strEvent = strEventName & " - this type of event not processed by this monitoring app!"
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
End Function

Public Function PrintWarning(strWarningMsg As String)

    Dim strEvent As String
    
    strEvent = "WARNING: " & strWarningMsg
    
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & Chr(13) & Chr(10)
    frmCallHubs.txtMessages.Text = frmCallHubs.txtMessages.Text & strEvent
    
    frmCallHubs.txtMessages.SelStart = Len(frmCallHubs.txtMessages.Text)
    frmCallHubs.txtMessages.SelLength = 0
    frmCallHubs.txtMessages.Refresh
End Function

Public Function TranslateCallState(State As CALL_STATE) As String

    Dim strState As String
    
    Select Case State
                
        Case CS_DISCONNECTED
            strState = "CS_DISCONNECTED"
        Case CS_INPROGRESS
            strState = "CS_INPROGRESS"
        Case CS_OFFERING
            strState = "CS_OFFERING"
        Case CS_CONNECTED
            strState = "CS_CONNECTED"
        Case CS_HOLD
            strState = "CS_HOLD"
        Case CS_IDLE
            strState = "CS_IDLE"
        Case CS_QUEUED
            strState = "CS_QUEUED"
        
        Case Else
            strState = "ERROR: Unknown call state (CS_)!"
    End Select

    TranslateCallState = strState
    
End Function

Public Function TranslatePrivilege(Privilege As CALL_PRIVILEGE) As String

    Dim strPrivilege As String
    
    Select Case Privilege
                
        Case CP_MONITOR
            strPrivilege = "CP_MONITOR"
        Case CP_OWNER
            strPrivilege = "CP_OWNER"
        
        Case Else
            strPrivilege = "ERROR: Unknown call privilege (CP_)!"
    End Select

    TranslatePrivilege = strPrivilege

End Function

Function TranslateDigitMode(lDigitMode) As String
    
    Select Case lDigitMode
        Case LINEDIGITMODE_PULSE
            TranslateDigitMode = "LINEDIGITMODE_PULSE"
        Case LINEDIGITMODE_DTMF
            TranslateDigitMode = "LINEDIGITMODE_DTMF"
        Case LINEDIGITMODE_DTMFEND
            TranslateDigitMode = "LINEDIGITMODE_DTMFEND"
        Case Else
            TranslateDigitMode = "Unknown Digit Mode = " & lDigitMode & " !"
    End Select

End Function

'Reads the last error from Err object
'If Err.Number = 0, it means that no error has occurred.
'If no error, prints a success message in the debugger; if error occurred, also puts up an error message box.
'Returns the error code found in Err.Number when this function is called.
'Before returning, it clears the error.
'
Public Function CheckError(strMessage As String) As Long

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

