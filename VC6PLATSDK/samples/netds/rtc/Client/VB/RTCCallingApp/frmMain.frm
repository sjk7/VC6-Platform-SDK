VERSION 5.00
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "RTC Core API Sample"
   ClientHeight    =   6900
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   9615
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6900
   ScaleWidth      =   9615
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame fraVideoR 
      Caption         =   "Video Receive"
      Height          =   1815
      Left            =   6960
      TabIndex        =   33
      Top             =   2520
      Width           =   2175
      Begin VB.PictureBox picVideoR 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000B&
         ForeColor       =   &H80000008&
         Height          =   1455
         Left            =   120
         ScaleHeight     =   1425
         ScaleWidth      =   1905
         TabIndex        =   34
         Top             =   240
         Width           =   1935
      End
   End
   Begin VB.Frame fraVideoS 
      Caption         =   "Video Send"
      Height          =   1815
      Left            =   6960
      TabIndex        =   31
      Top             =   360
      Width           =   2175
      Begin VB.PictureBox picVideoS 
         Appearance      =   0  'Flat
         BackColor       =   &H8000000B&
         ForeColor       =   &H80000008&
         Height          =   1455
         Left            =   120
         ScaleHeight     =   1425
         ScaleWidth      =   1905
         TabIndex        =   32
         Top             =   240
         Width           =   1935
      End
   End
   Begin VB.Frame fraAnswer 
      Caption         =   "Answer a call"
      Height          =   1575
      Left            =   4320
      TabIndex        =   29
      Top             =   360
      Width           =   2175
      Begin VB.CommandButton cmdAnswer 
         Caption         =   "Answer"
         Enabled         =   0   'False
         Height          =   375
         Left            =   480
         TabIndex        =   9
         Top             =   960
         Width           =   1215
      End
      Begin VB.CheckBox chkAutoAnswer 
         Caption         =   "Auto Answer"
         Height          =   255
         Left            =   480
         TabIndex        =   8
         Top             =   480
         Width           =   1215
      End
   End
   Begin VB.Frame fraKeyPad 
      Caption         =   "Generate DTMF Tones"
      Enabled         =   0   'False
      Height          =   2055
      Left            =   4320
      TabIndex        =   28
      Top             =   2280
      Width           =   2175
      Begin VB.CommandButton cmdKey 
         Caption         =   "#"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Microsoft Sans Serif"
            Size            =   9.75
            Charset         =   0
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   11
         Left            =   1320
         TabIndex        =   21
         Top             =   1440
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "0"
         Enabled         =   0   'False
         Height          =   375
         Index           =   0
         Left            =   840
         TabIndex        =   20
         Top             =   1440
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "*"
         Enabled         =   0   'False
         BeginProperty Font 
            Name            =   "Symbol"
            Size            =   12
            Charset         =   2
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   375
         Index           =   10
         Left            =   360
         TabIndex        =   19
         Top             =   1440
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "9"
         Enabled         =   0   'False
         Height          =   375
         Index           =   9
         Left            =   1320
         TabIndex        =   18
         Top             =   1080
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "8"
         Enabled         =   0   'False
         Height          =   375
         Index           =   8
         Left            =   840
         TabIndex        =   17
         Top             =   1080
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "7"
         Enabled         =   0   'False
         Height          =   375
         Index           =   7
         Left            =   360
         TabIndex        =   16
         Top             =   1080
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "6"
         Enabled         =   0   'False
         Height          =   375
         Index           =   6
         Left            =   1320
         TabIndex        =   15
         Top             =   720
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "5"
         Enabled         =   0   'False
         Height          =   375
         Index           =   5
         Left            =   840
         TabIndex        =   14
         Top             =   720
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "4"
         Enabled         =   0   'False
         Height          =   375
         Index           =   4
         Left            =   360
         TabIndex        =   13
         Top             =   720
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "3"
         Enabled         =   0   'False
         Height          =   375
         Index           =   3
         Left            =   1320
         TabIndex        =   12
         Top             =   360
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "2"
         Enabled         =   0   'False
         Height          =   375
         Index           =   2
         Left            =   840
         TabIndex        =   11
         Top             =   360
         Width           =   495
      End
      Begin VB.CommandButton cmdKey 
         Caption         =   "1"
         Enabled         =   0   'False
         Height          =   375
         Index           =   1
         Left            =   360
         TabIndex        =   10
         Top             =   360
         Width           =   495
      End
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   375
      Left            =   3960
      TabIndex        =   22
      Top             =   6240
      Width           =   1215
   End
   Begin VB.Frame fraStatus 
      Caption         =   "Status"
      Height          =   1215
      Left            =   480
      TabIndex        =   26
      Top             =   4680
      Width           =   8655
      Begin VB.Label lblStatus 
         Caption         =   "RTC Core 1.0 API sample. "
         Height          =   615
         Left            =   600
         TabIndex        =   27
         Top             =   360
         Width           =   7575
      End
   End
   Begin VB.Frame fraCall 
      Caption         =   "Make a call"
      Height          =   3975
      Left            =   480
      TabIndex        =   23
      Top             =   360
      Width           =   3375
      Begin VB.CommandButton cmdWizard 
         Caption         =   "Tuning Wizard"
         Height          =   375
         Left            =   360
         TabIndex        =   30
         Top             =   3360
         Width           =   1215
      End
      Begin VB.CommandButton cmdTerminate 
         Caption         =   "Terminate"
         Enabled         =   0   'False
         Height          =   375
         Left            =   1680
         TabIndex        =   7
         Top             =   2880
         Width           =   1215
      End
      Begin VB.CommandButton cmdConnect 
         Caption         =   "Connect"
         Height          =   375
         Left            =   360
         TabIndex        =   6
         Top             =   2880
         Width           =   1215
      End
      Begin VB.TextBox txtDestination 
         Height          =   285
         Left            =   1200
         TabIndex        =   5
         Top             =   2280
         Width           =   1935
      End
      Begin VB.TextBox txtLocalURI 
         Height          =   285
         Left            =   1200
         TabIndex        =   4
         Top             =   1920
         Width           =   1935
      End
      Begin VB.Frame fraSessionType 
         Caption         =   "Session Type"
         Height          =   1215
         Left            =   240
         TabIndex        =   0
         Top             =   360
         Width           =   2895
         Begin VB.OptionButton optPhtoPh 
            Caption         =   "Phone to Phone"
            Height          =   255
            Left            =   240
            TabIndex        =   3
            Top             =   840
            Width           =   2055
         End
         Begin VB.OptionButton optPCtoPhone 
            Caption         =   "PC to Phone"
            Height          =   255
            Left            =   240
            TabIndex        =   2
            Top             =   600
            Width           =   1935
         End
         Begin VB.OptionButton optPCtoPC 
            Caption         =   "PC to PC"
            Height          =   255
            Left            =   240
            TabIndex        =   1
            Top             =   360
            Width           =   2415
         End
      End
      Begin VB.Label lblDestination 
         Caption         =   "End URI:"
         Height          =   255
         Left            =   240
         TabIndex        =   25
         Top             =   2280
         Width           =   735
      End
      Begin VB.Label lblLocalURI 
         Caption         =   "Local URI:"
         Height          =   255
         Left            =   240
         TabIndex        =   24
         Top             =   1920
         Width           =   855
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------------------------------------------
'
'               Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------------------
'
'
' Purpose   : To demonstrate PC-to-PC, PC-to-Phone and Phone-to-Phone audio/video
'             communication using RTC Client API v1.0.
'
' Details   : RTCSampleVB.vbp is a Visual Basic sample application for RTC Client API.
'             This sample was developed using Visual Basic 6.0 (SP5).
'             This sample demonstrates methods in following five interfaces:
'                1) IRTCClient
'                2) IRTCSession
'                3) IRTCEventNotification
'                4) IRTCSessionStateChangeEvent
'                5) IRTCMediaEvent
'             Comments starting with 'UI:' suggest that the proceeding programming
'             statement is used primarily for maintaining User Interface.
'
' Author    : Ashar Khan    v1.00   (03-14-2001)
'           : Ashar Khan    v1.01   (01-08-2002) Minor updates to the sample.
'
'--------------------------------------------------------------------------------------




' Force explicit declaration of variables
Option Explicit


' Flags for CreateSession/AddBuddy
Const RTCCS_FORCE_PROFILE = &H1
Const RTCCS_FAIL_ON_REDIRECT = &H2

' Media Types
Const RTCMT_AUDIO_SEND = &H1
Const RTCMT_AUDIO_RECEIVE = &H2
Const RTCMT_VIDEO_SEND = &H4
Const RTCMT_VIDEO_RECEIVE = &H8
Const RTCMT_T120_SENDRECV = &H10
Const RTCMT_ALL_RTP = &HF
Const RTCMT_ALL = &H1F

' Session types
Const RTCSI_PC_TO_PC = &H1
Const RTCSI_PC_TO_PHONE = &H2
Const RTCSI_PHONE_TO_PHONE = &H4
Const RTCSI_IM = &H8

' Transports
Const RTCTR_UDP = &H1
Const RTCTR_TCP = &H2
Const RTCTR_TLS = &H4

' Registration Flags
Const RTCRF_REGISTER_INVITE_SESSIONS = &H1
Const RTCRF_REGISTER_MESSAGE_SESSIONS = &H2
Const RTCRF_REGISTER_PRESENCE = &H4
Const RTCRF_REGISTER_ALL = &H7

' Event filters
Const RTCEF_CLIENT = &H1
Const RTCEF_REGISTRATION_STATE_CHANGE = &H2
Const RTCEF_SESSION_STATE_CHANGE = &H4
Const RTCEF_SESSION_OPERATION_COMPLETE = &H8
Const RTCEF_PARTICIPANT_STATE_CHANGE = &H10
Const RTCEF_MEDIA = &H20
Const RTCEF_INTENSITY = &H40
Const RTCEF_MESSAGING = &H80
Const RTCEF_BUDDY = &H100
Const RTCEF_WATCHER = &H200
Const RTCEF_PROFILE = &H400
Const RTCEF_ALL = &H7FF


' UI: Constants related to the IVideoInterface. These are used
' to place the video window in its proper position in the sample.
' This is related more to managing UI.
Const WS_CHILD = &H40000000
Const WS_CLIPSIBLINGS = &H4000000


' MY_RTC_EVENTFILTERS will be used to register for receiving events.
Const MY_RTC_EVENTFILTERS = _
                        RTCEF_CLIENT Or _
                        RTCEF_SESSION_STATE_CHANGE Or _
                        RTCEF_MEDIA

                        
' Variables related to RTC Client API
Private g_objRTCClient As RTCClient
Private g_objSession As IRTCSession
Private g_objProfile As IRTCProfile
Private g_objVideoSend As IVideoWindow
Private g_objVideoRecv As IVideoWindow
Private g_objParticipant As IRTCParticipant
Private WithEvents g_objRTCClientWithEvents As RTCClient
Attribute g_objRTCClientWithEvents.VB_VarHelpID = -1


Private Sub Form_Load()
    
    On Error GoTo CheckError
        
    ' Create RTCClient object.
    Set g_objRTCClient = New RTCClient
    ' RTCClient needs to be initialized before any other method can be called on it.
    Call g_objRTCClient.Initialize
    ' Set the EventFilter to accept events.
    g_objRTCClient.EventFilter = MY_RTC_EVENTFILTERS
    ' Register the outgoing interface that will receive the events.
    Set g_objRTCClientWithEvents = g_objRTCClient
    ' Start listening for incoming sessions on a dynamic port and a registered static
    ' port 5060. Any other application can send packet to this registered port 5060.
    g_objRTCClient.ListenForIncomingSessions = RTCLM_BOTH
    ' Prepare the sample to send and receive both audio and video
    Call g_objRTCClient.SetPreferredMediaTypes(RTCMT_AUDIO_SEND Or _
                                               RTCMT_VIDEO_SEND Or _
                                               RTCMT_AUDIO_RECEIVE Or _
                                               RTCMT_VIDEO_RECEIVE, True)
    
    ' Get IVideoWindow objects for Incoming and outgoing video streams.
    ' These objects can be set even before a session is created.
    Set g_objVideoSend = g_objRTCClient.IVideoWindow(RTCVD_PREVIEW)
    Set g_objVideoRecv = g_objRTCClient.IVideoWindow(RTCVD_RECEIVE)
    
    ' UI: Display local user uri in text box and update status.
    txtLocalURI.Text = g_objRTCClient.LocalUserURI
    lblStatus.Caption = "RTCClient is initialized and ready to make/receive calls."
    
    Exit Sub
        
        
' Error checking code.
CheckError:
    Call PrintError
Resume Next
    
End Sub


'====================================================================================
'
'                          RTC(Client)API Event Handlers
'
'====================================================================================


Private Sub g_objRTCClientWithEvents_Event(ByVal RTCEvent As RTCCORELib.RTC_EVENT, ByVal pEvent As Object)
    ' This procedure is the required procedure for receiving events. Events are
    ' sent to this proceudre and then its upto the developer to call correct method
    ' depending on which event is received.
    
    ' Call appropriate procedure to handle each type of event
    Select Case RTCEvent
      
        Case RTCE_SESSION_STATE_CHANGE
            Call SessionStateEvent(pEvent)
          
        Case RTCE_MEDIA
            Call MediaEvent(pEvent)
            
    End Select

End Sub


Private Sub SessionStateEvent(ByVal pEvent As Object)

    Dim state As RTC_SESSION_STATE
    Dim objSessionEvent As IRTCSessionStateChangeEvent
    
    On Error GoTo CheckError
    
    ' pEvent is an "Unknown" object, query it
    ' to get IRTCSessionStateChangeEvent interface
    Set objSessionEvent = pEvent
    state = objSessionEvent.state
    
    Select Case state
    
        Case RTCSS_IDLE
            lblStatus.Caption = "IDLE"
            
        Case RTCSS_INCOMING
            ' Answer incoming only if there is no other session connected
            If ((g_objSession Is Nothing) Or (g_objSession.state <> RTCSS_CONNECTED)) Then
                lblStatus.Caption = "INCOMING"
                cmdTerminate.Enabled = True
                cmdConnect.Enabled = False
                cmdAnswer.Enabled = True
                ' Play a ring on the local PC to alert user of incoming call.
                Call g_objRTCClient.PlayRing(RTCRT_PHONE, True)
                ' Get the incoming session.
                Set g_objSession = objSessionEvent.Session
                ' Automatically answer if Auto Answer is checked.
                If chkAutoAnswer.Value = 1 Then
                    Call g_objSession.Answer
                End If
            End If
            
        Case RTCSS_ANSWERING
            lblStatus.Caption = "ANSWERING"
            ' Stop the ringing and release the audio render device.
            Call g_objRTCClient.PlayRing(RTCRT_PHONE, False)
            ' UI: Answer button has been pressed, now disable it.
            cmdAnswer.Enabled = False
           
        Case RTCSS_INPROGRESS
            lblStatus.Caption = "INPROGRESS"
            ' UI: Disable and enable appropriate buttons.
            cmdConnect.Enabled = False
            cmdTerminate.Enabled = True
            cmdWizard.Enabled = False
            
        Case RTCSS_CONNECTED
            lblStatus.Caption = "CONNECTED"
            ' Session is in connected state. DTMF tones can be generated
            ' for PC-to-PC and PC-to-Phone session types.
            Call EnableDTMFUI
            
        Case RTCSS_DISCONNECTED
            ' Free session and participant objects
            Set g_objSession = Nothing
            Set g_objParticipant = Nothing
            ' SendDTMF method should only be called when session is in connected state
            ' and session is of type PC-to-PC or PC-to-Phone. It is responsibility of
            ' devleoper to make sure that user is not able to call this method in any
            ' other state.
            Call DisableDTMFUI
            ' UI: Display 'Disconnected' as status.
            lblStatus.Caption = "DISCONNECTED"
            ' UI: Disable answer button
            cmdAnswer.Enabled = False
            ' UI: Disable terminate button
            cmdTerminate.Enabled = False
            ' UI: Enable connect button
            cmdConnect.Enabled = True
        
    End Select
    
    ' Free memory
    Set objSessionEvent = Nothing
    
    Exit Sub
    
CheckError:
    Call PrintError
Resume Next
    
End Sub


Private Sub MediaEvent(ByVal pEvent As Object)

    Dim MediaType As Long
    Dim objMediaEvent As IRTCMediaEvent
    Dim EventType As RTC_MEDIA_EVENT_TYPE
    
    On Error GoTo CheckError
    
    ' pEvent is an "Unknown" object,
    ' query it to get IRTCMediaEvent interface
    Set objMediaEvent = pEvent
    EventType = objMediaEvent.EventType
    MediaType = objMediaEvent.MediaType

    Select Case EventType

        Case RTCMET_STARTED
            If MediaType = RTCMT_VIDEO_SEND Then
                ' Remove the frame around the windows
                g_objVideoSend.WindowStyle = WS_CHILD Or WS_CLIPSIBLINGS
                ' Set the picture control as the parent so
                ' that video appears within the control.
                g_objVideoSend.Owner = picVideoS.hWnd
                ' Resizing and positioning. For more
                ' information look in SDK for IVideoInterface.
                Call g_objVideoSend.SetWindowPosition(0, 0, 130, 104)
                g_objVideoSend.Visible = 1
                
            End If
             
            If MediaType = RTCMT_VIDEO_RECEIVE Then
                ' Remove the frame around the windows
                g_objVideoRecv.WindowStyle = WS_CHILD Or WS_CLIPSIBLINGS
                ' Set the picture control as the parent so
                ' that video appears within the control.
                g_objVideoRecv.Owner = picVideoR.hWnd
                ' Resizing and positioning. For more
                ' information look in SDK for IVideoInterface.
                Call g_objVideoRecv.SetWindowPosition(0, 0, 130, 104)
                g_objVideoRecv.Visible = 1
            End If
        
        Case RTCMET_STOPPED
            On Error Resume Next
            If MediaType = RTCMT_VIDEO_RECEIVE Then
                g_objVideoRecv.Visible = 0
                g_objVideoRecv.Owner = 0
            Else
                g_objVideoSend.Visible = 0
                g_objVideoSend.Owner = 0
            End If
            
   End Select

    Set objMediaEvent = Nothing
    
    Exit Sub
    
CheckError:
    Call PrintError
Resume Next
    
End Sub


'====================================================================================
'
'                          Event Handlers for User Actions
'
'====================================================================================


Private Sub cmdConnect_Click()
    
    Dim strLocalURI As String
    Dim strDestURI As String
    
    On Error GoTo CheckError
    
    ' To make a call:
    ' (1) First create a session to get session object.
    ' (2) Then add a participant to the session object to initiate a call.
    
    ' (1) Create a session depending on session type selected by the user.
    If optPCtoPC.Value = True Then
        strDestURI = Trim(txtDestination.Text)
        Set g_objSession = g_objRTCClient.CreateSession(RTCST_PC_TO_PC, vbNullString, Nothing, 0)
    ElseIf optPCtoPhone = True Then
        ' Before calling to a telephone from a PC, the end user would have to
        ' subscribe to an IP telephony service. The service provider will provide
        ' the necessary IP to PSTN gateway to make this call. It is assumed that
        ' the user has setup such a gateway.
    
        ' Phone URI should be of the form "sip:+12223334444@gateway.com;user=phone"
        strDestURI = Trim(txtDestination.Text)
        Set g_objSession = g_objRTCClient.CreateSession(RTCST_PC_TO_PHONE, vbNullString, Nothing, 0)
    Else
        ' To make Phone to Phone call, g_objProfile must contain a valid Profile object.
        ' It is upto the user to setup the infrastructure and create a proper profile
        ' based on their local settings. This code has been provided as an example.
        ' It will fail with proper error code.
        Set g_objProfile = Nothing
        strLocalURI = Trim(txtLocalURI.Text)
        strDestURI = Trim(txtDestination.Text)
        Set g_objSession = g_objRTCClient.CreateSession(RTCST_PHONE_TO_PHONE, strLocalURI, g_objProfile, 0)
    End If
    
    '(2) Add participant to initiate call.
    Set g_objParticipant = g_objSession.AddParticipant(strDestURI, "Any Name")
    
    Exit Sub
        
' Error checking code.
CheckError:
    Call PrintError
Resume Next
    
End Sub


Private Sub cmdAnswer_Click()
    
    On Error GoTo CheckError
    
    ' Answer an incoming session
    Call g_objSession.Answer
    
    Exit Sub

CheckError:
    Call PrintError
Resume Next
    
End Sub


Private Sub cmdTerminate_Click()
    
    On Error GoTo CheckError
    
    If g_objSession.state = RTCSS_INCOMING Then
        ' Reject an Incoming call
        Call g_objSession.Terminate(RTCTR_REJECT)
        ' Stop the ringing and release the audio render device.
        Call g_objRTCClient.PlayRing(RTCRT_PHONE, False)
    Else
        ' Terminate a session normally
        Call g_objSession.Terminate(RTCTR_NORMAL)
    End If
    
    Exit Sub

CheckError:
    Call PrintError
Resume Next
    
End Sub


Private Sub cmdKey_Click(Index As Integer)
    
    ' Using an array of controls. Based on Index simply call
    ' SendDTMF method on RTCClient object with correct constant.
    
    On Error GoTo CheckError
    
    Select Case Index
    
        Case 0
            g_objRTCClient.SendDTMF (RTC_DTMF_0)
        Case 1
            g_objRTCClient.SendDTMF (RTC_DTMF_1)
        Case 2
            g_objRTCClient.SendDTMF (RTC_DTMF_2)
        Case 3
            g_objRTCClient.SendDTMF (RTC_DTMF_3)
        Case 4
            g_objRTCClient.SendDTMF (RTC_DTMF_4)
        Case 5
            g_objRTCClient.SendDTMF (RTC_DTMF_5)
        Case 6
            g_objRTCClient.SendDTMF (RTC_DTMF_6)
        Case 7
            g_objRTCClient.SendDTMF (RTC_DTMF_7)
        Case 8
            g_objRTCClient.SendDTMF (RTC_DTMF_8)
        Case 9
            g_objRTCClient.SendDTMF (RTC_DTMF_9)
        Case 10
            g_objRTCClient.SendDTMF (RTC_DTMF_STAR)
        Case 11
            g_objRTCClient.SendDTMF (RTC_DTMF_POUND)
            
    End Select

    Exit Sub

CheckError:
    Call PrintError
Resume Next

End Sub


Private Sub cmdWizard_Click()

    On Error GoTo CheckError

    ' This method is synchronous and returns once the tuning wizard is complete.
    ' Tuning wizard should only be called when no active session is present.
    Dim hwndParent As Long
    hwndParent = frmMain.hWnd
    
    ' hwndParent is a handle to applications main form.
    Call g_objRTCClient.InvokeTuningWizard(hwndParent)

    Exit Sub

CheckError:
    Call PrintError
Resume Next

End Sub


Private Sub optPCtoPC_Click()
    
    ' UI: Display local user uri and ask user to enter destination address.
    txtLocalURI.Text = g_objRTCClient.LocalUserURI
    txtDestination.Text = "Enter address to call"

End Sub


Private Sub optPCtoPhone_Click()
    
    ' UI: Display local user uri and ask user to enter destination number.
    txtLocalURI.Text = g_objRTCClient.LocalUserURI
    txtDestination.Text = "Enter number to call."

End Sub


Private Sub optPhtoPh_Click()
    
    ' UI: Inform the user that Phone to Phone call will not succeed
    lblStatus.Caption = "Making a Phone to Phone call requires a valid Profile. The user needs " & _
                        "to setup proper infrastructure and create this profile based on their " & _
                        "local settings. This code has been provided as an example. " & _
                        "It will fail with proper error code."
                
    ' UI: Ask user to enter Local and Destination phone numbers.
    txtLocalURI.Text = "Enter number to call from."
    txtDestination.Text = "Enter number to call."
    
End Sub


Private Sub optPhtoPh_LostFocus()
    ' UI: Clear the message that was printed above
    lblStatus.Caption = ""
    
End Sub


Private Sub cmdExit_Click()
    
    ' Free memory and shutdown RTCClient object
    Unload Me
    
End Sub


Private Sub Form_Unload(Cancel As Integer)
    
    On Error Resume Next
    
    ' Terminating any connected session because sample is shutting down
    If Not (g_objSession Is Nothing) Then
        g_objSession.Terminate (RTCTR_SHUTDOWN)
    End If
    
    ' Shutting down RTCClient object
    If Not (g_objRTCClient Is Nothing) Then
        ' Shutdown must be called before the client object is released.
        Call g_objRTCClient.Shutdown
    End If
    
    ' Freeing memory
    Set g_objSession = Nothing
    Set g_objVideoSend = Nothing
    Set g_objVideoRecv = Nothing
    Set g_objParticipant = Nothing
    Set g_objRTCClientWithEvents = Nothing
    Set g_objRTCClient = Nothing

End Sub


'====================================================================================
'
'                          Procedures for Maintaining User Interface
'
'====================================================================================


Private Sub DisableDTMFUI()
    
    Dim iIndex As Integer
    
    ' UI: Disable each DTMF button
    fraKeyPad.Enabled = False
    For iIndex = 0 To 11
        cmdKey(iIndex).Enabled = False
    Next
    
    ' Tuning wizard should only be started when there is no active session.
    cmdWizard.Enabled = True
    
End Sub


Private Sub EnableDTMFUI()
    
    Dim iIndex As Integer
    
    ' UI: Enable each DTMF button.
    fraKeyPad.Enabled = True
    For iIndex = 0 To 11
        cmdKey(iIndex).Enabled = True
    Next
    
    ' Tuning wizard should only be started when there is no active session.
    cmdWizard.Enabled = False

End Sub


Private Sub PrintError()
    
    ' This procedure is called when an error happens to print error number
    lblStatus.Caption = "ERROR: 0x" & Hex(Err.Number)
    Err.Clear

End Sub

