VERSION 5.00
Object = "{6FBA474E-43AC-11CE-9A0E-00AA0062BB4C}#1.0#0"; "SYSINFO.OCX"
Begin VB.Form sys 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Microsoft Smart Card API VB Test"
   ClientHeight    =   5445
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   9930
   Icon            =   "scrdvb.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   5445
   ScaleWidth      =   9930
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame fraSetup 
      Caption         =   "Setup Information"
      Height          =   2415
      Left            =   120
      TabIndex        =   3
      Top             =   240
      Width           =   9615
      Begin SysInfoLib.SysInfo SysInfo1 
         Left            =   480
         Top             =   1200
         _ExtentX        =   1005
         _ExtentY        =   1005
         _Version        =   393216
      End
      Begin VB.ListBox lstCards 
         Height          =   1425
         Left            =   3600
         TabIndex        =   2
         Top             =   600
         Width           =   2895
      End
      Begin VB.Frame fraOutput 
         Caption         =   "Output"
         Height          =   1815
         Left            =   7080
         TabIndex        =   8
         Top             =   360
         Width           =   2175
         Begin VB.OptionButton optAppend 
            Caption         =   "Append"
            Height          =   375
            Left            =   240
            TabIndex        =   9
            Top             =   1080
            Width           =   1815
         End
         Begin VB.OptionButton optOverwrite 
            Caption         =   "Overwrite"
            Height          =   375
            Left            =   240
            TabIndex        =   10
            Top             =   480
            Value           =   -1  'True
            Width           =   1695
         End
      End
      Begin VB.ComboBox cmbReaderList 
         Height          =   315
         ItemData        =   "scrdvb.frx":1272
         Left            =   240
         List            =   "scrdvb.frx":1274
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   600
         Width           =   2895
      End
      Begin VB.Label lblCard 
         Caption         =   "Smart Cards known to system"
         Height          =   255
         Left            =   3600
         TabIndex        =   7
         Top             =   360
         Width           =   2175
      End
      Begin VB.Label lblReader 
         Caption         =   "Smart Card Reader in use"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   360
         Width           =   2415
      End
   End
   Begin VB.TextBox txtOutputWindow 
      BeginProperty Font 
         Name            =   "Courier New"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1935
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      TabStop         =   0   'False
      ToolTipText     =   "Program output will appear here."
      Top             =   3360
      Width           =   9615
   End
   Begin VB.CommandButton btnClose 
      Cancel          =   -1  'True
      Caption         =   "&Close"
      Height          =   375
      Left            =   8400
      TabIndex        =   5
      Top             =   2880
      Width           =   1335
   End
   Begin VB.CommandButton btnRuntests 
      Caption         =   "&Run Tests"
      Default         =   -1  'True
      Height          =   375
      Left            =   6960
      TabIndex        =   4
      ToolTipText     =   "Click to begin running the selected tests"
      Top             =   2880
      Width           =   1335
   End
End
Attribute VB_Name = "sys"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' declarations of global data
'
' output header info - test title
Const strTestTitle As String = "MS Smart Card API VB Test"
' output header info - separator bar
Const strBar As String = "------------------------------------------------------"
' output reporting text
Const strSpacer As String = ".................................................."
Const strTab As String = "  "
Const strPass As String = "PASS"
Const strFail As String = "FAIL"
Const intPassLength As Integer = 4
' max length of output line in window or output file
Const intOutputMax As Integer = 50
' size of byte buffer, 0 to 99
Const intByteMax As Integer = 99
' size of string buffer
Const intBufferSize As Integer = 2048
' overall pass/fail flag
Dim lngOverallResult As Long
' os version flag
Dim bIsWindows2kB2 As Boolean



Private Sub Form_Load()
    ' result of api call
    Dim lngResult As Long
    ' list of readers
    Dim strReaders As String
    ' length of list of readers
    Dim lngReadersLen As Long
    ' array of card names as strings
    Dim astrCards As Variant
    ' array of reader names as strings
    Dim astrReaders As Variant
    ' cardinality of array astrCards
    Dim intCardCount As Integer
    ' cardinality of array astrReaders
    Dim intReaderCount As Integer
    ' list of cards
    Dim strCards As String
    ' length of card names as strings
    Dim lngCardsLen As Long
    ' message for no readers found
    Const strErrNoReaders As String = "no readers found"
    ' message for no cards found
    Const strErrNoCards As String = "no cards found"
    
    ' determine OS version (some APIs are not available before Windows 2000 Beta2)
    If 2 = SysInfo1.OSPlatform And 4 <= SysInfo1.OSVersion And 1877 <= SysInfo1.OSBuild Then
        bIsWindows2kB2 = True
    Else
        bIsWindows2kB2 = False
    End If
    
    ' populate combobox of reader names
    ' initialize variables for api call
    strReaders = String(intBufferSize, vbNullChar)
    lngReadersLen = Len(strReaders)
    
    ' get reader list
    ' pass in implicit request for all readers, both valid and invalid,
    '    using NULL context, NULL group parameters
    lngResult = SCardListReadersA(&O0, vbNullString, strReaders, lngReadersLen)
    If SCARD_S_SUCCESS = lngResult Then
        ' process returned multistring
        astrReaders = ParseMultistring(strReaders, intReaderCount)
        If 0 < intReaderCount Then
            ' put readers into combobox
            For i = 1 To intReaderCount
                cmbReaderList.AddItem astrReaders(i - 1)
            Next i
        Else
            ' no readers actually returned by api call
            cmbReaderList.AddItem strErrNoReaders
        End If
    Else
        ' could not get list of readers
        OutputLine (ApiErrorMessage(lngResult))
        cmbReaderList.AddItem strErrNoReaders
    End If
        
    ' set combobox to first item in list
    cmbReaderList.Text = cmbReaderList.List(0)
    
    ' populate listbox of card names
    strCards = String(intBufferSize, vbNullChar)
    lngCardsLen = Len(strCards)
    
    ' get card list
    ' pass in implicit request for all cards
    '    using NULL context, NULL ATR and Interface arrays
    lngResult = SCardListCardsA2(&O0, lngNull, lngNull, 0, _
                    strCards, lngCardsLen)
    If SCARD_S_SUCCESS = lngResult Then
        ' process returned multistring
        astrCards = ParseMultistring(strCards, intCardCount)
        If 0 < intCardCount Then
            ' put cards into listbox
            For i = 1 To intCardCount
                lstCards.AddItem astrCards(i - 1)
            Next i
        Else
            ' no card actually returned by api call
            lstCards.AddItem strErrNoCards
        End If
    Else
        ' could not get list of cards
        OutputLine (ApiErrorMessage(lngResult))
        lstCards.AddItem strErrNoCards
    End If
    
    'set listbox to first item in list
    lstCards.Text = lstCards.List(0)

End Sub ' Form_Load

Private Sub btnClose_Click()
    End
End Sub ' btnClose_Click()

Private Sub btnRuntests_Click()
    ' clear output screen if indicate by Overwrite/Append radio buttons
    If optOverwrite.Value = True Then
        txtOutputWindow.Text = ""
    End If

    ' initialize overall result
    lngOverallResult = SCARD_S_SUCCESS
    
    ' alphabetical, by name, list of variables used in API calls
    '
    ' buffer, resizable, for list of cards returned from API call
    Dim abyCardList() As Byte
    ' buffer for card control reply
    Dim abyControlBuffer(0 To MAXIMUM_ATTR_STRING_LENGTH - 1) As Byte
    ' buffer for card command - sized for particular command used
    Dim abyGetChallenge(0 To 4) As Byte
    ' buffer for reply to card command - sized arbitrarily
    Dim abyRecvBuffer(0 To intByteMax) As Byte
    ' buffer for card control minor io control
    Dim abySendBuffer(0 To 3) As Byte
    ' attribute buffer
    Dim abytAttr(MAXIMUM_ATTR_STRING_LENGTH) As Byte
    ' guid array of card interface pointers supplied to API call, sized arbitrarily
    Dim agInterfaces(0 To 1) As GUID
    ' guid array of card interface pointers returned from API call, sized arbitrarily
    Dim aguiInterfaces(0 To 3) As GUID
    ' array of card names
    Dim astrCards As Variant
    ' array of reader group names
    Dim astrGroups As Variant
    ' array of reader names
    Dim astrReaders As Variant
    ' count of cards
    Dim intCardCount As Integer
    ' count of reader groups
    Dim intGroupCount As Integer
    ' count of readers
    Dim intReaderCount As Integer
    ' guid of card PrimaryProvider
    Dim guiPrimaryProvider As GUID
    ' length of attribute buffer
    Dim lngAttrLen As Long
    ' active protocol negotiated
    Dim lngActiveProtocol As Long
    ' handle to card
    Dim lngCard As Long
    ' length of list of cards
    Dim lngCardsLen As Long
    ' length of buffer for list of cards returned from API call
    Dim lngCardListLen As Long
    ' Resource Manager context
    Dim lngContext As Long
    ' length of card Control buffer
    Dim lngControlBufferLen As Long
    ' length of card Control reply
    Dim lngControlReplyLen As Long
    ' length of CSP name buffer
    Dim lngCSPBufferLen As Long
    ' length of list of groups
    Dim lngGroupsLen As Long
    ' length of list of GUIDs returned from API call
    Dim lngInterfaceReturnCount As Long
    ' result of api call
    Dim lngResult As Long
    ' length of list of readers
    Dim lngReadersLen As Long
    ' cardinality of readerstate array
    Dim lngReaderStateLen As Long
    ' state of current reader
    Dim lngState As Long
    ' structure for card communication
    Dim pioSendPci As SCARD_IO_REQUEST
    ' ATR of card
    Dim strATR As String
    ' ATR mask of card
    Dim strATRMask As String
    ' list of card returned from api call
    Dim strCardList As String
    ' list of cards supplied to API call
    Dim strCards As String
    ' CSP name supplied to association with introduced card
    Dim strCSPName As String
    ' CSP name returned from association with introduced card
    Dim strCSPBuffer As String
    ' currently selected reader
    Dim strCurrentReader As String
    ' device name to be introduced
    Dim strDeviceName As String
    ' list of reader groups
    Dim strGroups As String
    ' reader name to be introduced
    Dim strReaderName As String
    ' reader group name to be introduced
    Dim strReaderGroupName As String
    ' secondary output info
    Dim strOut As String
    ' list of readers
    Dim strReaders As String
    ' array of readerstate with only one element
    Dim udtReaderStates(2) As SCARD_READERSTATEA


    ' output test header
    OutputLine strBar
    OutputLine (strTestTitle + Format(Now, " dd-mmmm-yy hh:mm:ss AM/PM"))
    OutputLine strBar
    
    ' establish context
    ' initialize input variable
    lngContext = lngNull
    ' context as SCARD_SCOPE_SYSTEM
    ' context as SCARD_SCOPE_USER
    lngResult = SCardEstablishContext(SCARD_SCOPE_SYSTEM, lngNull, lngNull, lngContext)
    ' evaluate return from API call
    Call EvaluateResult("SCardEstablishContext", lngResult)
    
    ' get status change - card insertion
    ' set reader to the one selected in UI
    strCurrentReader = cmbReaderList.Text
    ' look in only one reader
    lngReaderStateLen = 1
    ' look for card in this reader
    udtReaderStates(0).szReader = strCurrentReader + vbNullChar
    ' assume that current state of reader is unknown
    udtReaderStates(0).dwCurrentState = 0
    
    lngResult = SCardGetStatusChangeA(lngContext, lngTimeout, udtReaderStates(0), _
                                        lngReaderStateLen)
        
    Call EvaluateResult("SCardGetStatusChangeA", lngResult)
    
    If SCARD_S_SUCCESS = lngResult Then
        ' report state of card in reader
        DisplayEventState (udtReaderStates(0).dwEventState)
    End If
    
     ' connect to card
    ' set handle to card to null
    lngCard = lngNull
    ' set currect protocol to neutral value
    lngActiveProtocol = 0
        
    lngResult = SCardConnectA(lngContext, strCurrentReader, SCARD_SHARE_SHARED, _
                    SCARD_PROTOCOL_Tx, lngCard, lngActiveProtocol)
                        
    Call EvaluateResult("SCardConnectA", lngResult)
    
    If SCARD_S_SUCCESS = lngResult Then
        ' report protocol
        strOut = strTab + "Protocol : "
        If SCARD_PROTOCOL_T0 = lngActiveProtocol Then
            strOut = strOut + "T0"
        ElseIf SCARD_PROTOCOL_T1 = lngActiveProtocol Then
            strOut = strOut + "T1"
        Else
            strOut = strOut + "UNKNOWN"
        End If
        OutputLine strOut
    ElseIf SCARD_E_UNKNOWN_READER = lngResult Then
        ' currently selected reader is not valid
        ' error already reported, but also report reader name to user
        OutputLine strTab + strCurrentReader
    End If
    
    ' cancel all transactions in the context
    lngResult = SCardCancel(lngContext)
    Call EvaluateResult("SCardCancel", lngResult)
    
    ' reconnect to card
    lngResult = SCardReconnect(lngCard, SCARD_SHARE_SHARED, SCARD_PROTOCOL_Tx, _
                    SCARD_LEAVE_CARD, lngActiveProtocol)
        
    Call EvaluateResult("SCardReconnect", lngResult)
    
    ' report protocol
    If SCARD_S_SUCCESS = lngResult Then
        strOut = strTab + "Protocol : "
        If SCARD_PROTOCOL_T0 = lngActiveProtocol Then
            strOut = strOut + "T0"
        ElseIf SCARD_PROTOCOL_T1 = lngActiveProtocol Then
            strOut = strOut + "T1"
        Else
            strOut = strOut + "UNKNOWN"
        End If
        OutputLine strOut
    End If
    
    ' begin transaction locking
    ' check that handle to card is valid
    lngResult = SCardBeginTransaction(lngCard)
    Call EvaluateResult("SCardBeginTransaction", lngResult)
    
    ' get attribute - current protocol
    ' check that handle to card is valid beforehand
    Erase abytAttr
    lngAttrLen = MAXIMUM_ATTR_STRING_LENGTH
        
    lngResult = SCardGetAttrib(lngCard, SCARD_ATTR_CURRENT_PROTOCOL_TYPE, _
                abytAttr(0), lngAttrLen)
        
    Call EvaluateResult("SCardGetAttrib", lngResult)
    
    ' report attribute found
    If SCARD_S_SUCCESS = lngResult Then
        strOut = strTab + "Protocol : "
        If abytAttr(0) = 1 Then
            strOut = strOut + "T0"
        ElseIf abytAttr(0) = 2 Then
            strOut = strOut + "T1"
        Else
            strOut = strOut + "UNKNOWN"
        End If
        OutputLine strOut
    End If
    
    ' get status
    strReaders = String(intBufferSize, vbNullChar)
    lngReadersLen = Len(strReaders)
    lngState = 0
    lngActiveProtocol = 0
    Erase abytAttr
    lngAttrLen = MAXIMUM_ATTR_STRING_LENGTH
    
    lngResult = SCardStatusA(lngCard, strReaders, lngReadersLen, _
                lngState, lngActiveProtocol, abytAttr(0), lngAttrLen)
        
    Call EvaluateResult("SCardStatusA", lngResult)
    
    If SCARD_S_SUCCESS = lngResult Then
        ' report all reader names for the current reader
        astrReaders = ParseMultistring(strReaders, intReaderCount)
        DisplayStringArray astrReaders, intReaderCount
            
        ' report state of reader
        Select Case lngState
            Case SCARD_SPECIFIC
                strOut = strTab + "SCARD_SPECIFIC"
            Case SCARD_NEGOTIABLE
                strOut = strTab + "SCARD_NEGOTIABLE"
            Case SCARD_POWERED
                strOut = strTab + "SCARD_POWERED"
            Case SCARD_SWALLOWED
                strOut = strTab + "SCARD_SWALLOWED"
            Case SCARD_ABSENT
                strOut = strTab + "SCARD_ABSENT"
            Case SCARD_UNKNOWN
                strOut = strTab + "SCARD_UNKNOWN"
            Case Else
                strOut = strTab + "State indeterminate"
        End Select
        OutputLine strOut
            
        ' report protocol, if any, negotiated with this reader
        Select Case lngActiveProtocol
            Case SCARD_PROTOCOL_T0
                strOut = strTab + "SCARD_PROTOCOL_T0"
            Case SCARD_PROTOCOL_T1
                strOut = strTab + "SCARD_PROTOCOL_T1"
            Case SCARD_PROTOCOL_RAW
                strOut = strTab + "SCARD_PROTOCOL_RAW"
            Case Else
                strOut = strTab + "Protocol indeterminate"
        End Select
        OutputLine strOut
            
        ' report atr of card, if any, in this reader
        DisplayATRArray abytAttr, lngAttrLen
            
    End If
    
    ' transmit command - get challenge
    ' initialize card command string
    abyGetChallenge(0) = &HC0
    abyGetChallenge(1) = &H84
    abyGetChallenge(2) = &H0
    abyGetChallenge(3) = &H0
    abyGetChallenge(4) = &H8
       
    pioSendPci.dwProtocol = SCARD_PROTOCOL_T0
    pioSendPci.dbPciLength = Len(pioSendPci)
        
    lngResult = SCardTransmit(lngCard, pioSendPci, abyGetChallenge(0), _
                    UBound(abyGetChallenge) - LBound(abyGetChallenge) + 1, _
                    pioSendPci, abyRecvBuffer(0), _
                    UBound(abyRecvBuffer) - LBound(abyRecvBuffer) + 1)
    
    Call EvaluateResult("SCardTransmit", lngResult)
    
    ' locate card
    ' clear buffer
    strCards = String(intBufferSize, vbNullChar)
    ' API needs card name(s) parameter as multistring
    strCards = "GemSAFE" + vbNullChar + vbNullChar
    ' look in only one reader
    lngReaderStateLen = 1
    ' look for card in this reader
    udtReaderStates(0).szReader = strCurrentReader + vbNullChar
    ' assume that current state of reader is unknown
    udtReaderStates(0).dwCurrentState = 0
   
    lngResult = SCardLocateCardsA(lngContext, strCards, _
                    udtReaderStates(0), lngReaderStateLen)
                        
    Call EvaluateResult("SCardLocateCardsA", lngResult)
    
    If SCARD_S_SUCCESS = lngResult Then
        ' report state of reader
        ' if card(s) found in reader, dwEventState will
        '    show ATR_MATCH; see SCardAPI for SCARD_STATE_* descriptions
        DisplayEventState (udtReaderStates(0).dwEventState)
    End If
       
    ' set attribute
    Erase abytAttr
    lngAttrLen = MAXIMUM_ATTR_STRING_LENGTH
    Const ERROR_NOT_SUPPORTED As Long = 50
    
    lngResult = SCardSetAttrib(lngCard, SCARD_ATTR_DEFAULT_DATA_RATE, _
                    abytAttr(0), lngAttrLen)
                    
    If ERROR_NOT_SUPPORTED = lngResult Then
        ' expected result, should not be able to change data rate
        lngResult = SCARD_S_SUCCESS
    End If
    
    Call EvaluateResult("SCardSetAttrib", lngResult)
        
    ' control card
    ' initialize buffer length and reply length
    lngControlBufferLen = MAXIMUM_ATTR_STRING_LENGTH
    lngControlReplyLen = 0
    
    ' SCARD_ATTR_ATR_STRING
    ' little endian format, for value see scardapi.bas
    abySendBuffer(0) = &H3
    abySendBuffer(1) = &H3
    abySendBuffer(2) = &H9
    abySendBuffer(3) = &H0
    
    lngResult = SCardControl(lngCard, IOCTL_SMARTCARD_GET_ATTRIBUTE, abySendBuffer(0), _
                        UBound(abySendBuffer) - LBound(abySendBuffer) + 1, _
                        abyControlBuffer(0), lngControlBufferLen, lngControlReplyLen)
                        
    Call EvaluateResult("SCardControl", lngResult)
    
    If SCARD_S_SUCCESS = lngResult Then
        ' report result
        DisplayATRArray abyControlBuffer, lngControlReplyLen
    End If
       
    ' end transaction locking
    lngResult = SCardEndTransaction(lngCard, SCARD_LEAVE_CARD)
    Call EvaluateResult("SCardEndTransaction", lngResult)
    
    ' disconnect
    lngResult = SCardDisconnect(lngCard, SCARD_LEAVE_CARD)
    Call EvaluateResult("SCardDisconnect", lngResult)
    
    ' list reader groups
    ' clear group name buffer
    strGroups = String(intBufferSize, vbNullChar)
    ' reset buffer size
    lngGroupsLen = Len(strGroups)
    ' reset group name count
    intGroupCount = 0
        
    ' request all groups associated with current context
    lngResult = SCardListReaderGroupsA(lngContext, strGroups, lngGroupsLen)
    Call EvaluateResult("ScardListReaderGroupsA", lngResult)
    
    ' report group names returned
    If SCARD_S_SUCCESS = lngResult Then
        ' process returned multistring
        astrGroups = ParseMultistring(strGroups, intGroupCount)
        DisplayStringArray astrGroups, intGroupCount
    End If
    
    ' list readers
    ' set group name for certain type calls
    strGroups = "MyCompanyReaders"
    ' clear reader name buffer
    strReaders = String(intBufferSize, vbNullChar)
    ' reset buffer size
    lngReadersLen = Len(strReaders)
    ' reset reader name count
    inReaderCount = 0
        
    ' pass in explicit request for a particular reader group
    'lngResult = SCardListReadersA(lngContext, strGroups, strReaders, lngReadersLen)
        
    ' pass in explicit request for all readers valid under current context
    'lngResult = SCardListReadersA(lngContext, SCARD_DEFAULT_READERS, _
                    strReaders, lngReadersLen)
        
    ' pass in implicit request for all readers via NULL context, NULL Group parameters
    lngResult = SCardListReadersA(&O0, vbNullString, strReaders, lngReadersLen)
        
    ' pass in implicit request for all valid readers via NULL Group parameter
    'lngResult = SCardListReadersA(lngContext, vbNullString, strReaders, lngReadersLen)
        
    Call EvaluateResult("SCardListReadersA", lngResult)
    
    ' report reader names returned
    If SCARD_S_SUCCESS = lngResult Then
        ' process returned multistring
        astrReaders = ParseMultistring(strReaders, intReaderCount)
        DisplayStringArray astrReaders, intReaderCount
    End If
    
    ' list cards
    ' clear card name buffer
    strCards = String(intBufferSize, vbNullChar)
    ' reset buffer size
    lngCardsLen = Len(strCards)
        
    ' pass in implicit request for all cards via NULL ATR, NULL Interface parameters
    lngResult = SCardListCardsA2(lngContext, lngNull, lngNull, 0, _
                    strCards, lngCardsLen)
    
    Call EvaluateResult("SCardListCardsA", lngResult)
    
    ' report card names returned
    If SCARD_S_SUCCESS = lngResult Then
        ' process returned multistring
        astrCards = ParseMultistring(strCards, intCardCount)
        DisplayStringArray astrCards, intCardCount
    End If
    
    ' introduce reader group (ANSI)
    ' set group name
    strReaderGroupName = "BogusGroup"
    
    lngResult = SCardIntroduceReaderGroupA(lngContext, strReaderGroupName)
    Call EvaluateResult("SCardIntroduceReaderGroupA", lngResult)
    
    ' introduce reader (ANSI)
    ' set reader friendly name
    strReaderName = "Bogus Reader PCMCIA"
    ' set reader device name
    strDeviceName = "Bogus Reader 0"
        
    lngResult = SCardIntroduceReaderA(lngContext, strReaderName, strDeviceName)
        
    Call EvaluateResult("SCardIntroduceReaderA", lngResult)
    
    ' add reader to group (ANSI)
    lngResult = SCardAddReaderToGroupA(lngContext, strReaderName, strReaderGroupName)
    Call EvaluateResult("SCardAddReaderToGroupA", lngResult)
     
    ' remove reader from group (ANSI)
    lngResult = SCardRemoveReaderFromGroupA(lngContext, strReaderName, strReaderGroupName)
    Call EvaluateResult("SCardRemoveReaderFromGroupA", lngResult)
    
    ' forget reader group
    lngResult = SCardForgetReaderGroupA(lngContext, strReaderGroupName)
    Call EvaluateResult("SCardForgetReaderGroupA", lngResult)
    
    ' forget reader
    lngResult = SCardForgetReaderA(lngContext, strReaderName)
    Call EvaluateResult("SCardForgetReaderA", lngResult)
     
    ' introduce a card (ANSI)
    ' initialize card name
    strCards = "BogusCard" + vbNullChar
    ' initialize ATR
    strATR = Chr(&H3B) + Chr(&HE2) + Chr(&H0) + Chr(&H0) _
            + Chr(&H40) + Chr(&H20) + Chr(&H49) + Chr(&H0)
        
    ' initialize ATRMask
    strATRMask = Chr(&HFF) + Chr(&HFF) + Chr(&HFF) + Chr(&HFF) _
                + Chr(&HFF) + Chr(&HFF) + Chr(&HFF) + Chr(&H0)
        
    ' initialize primary provider
    ' {9FBF0887-57AD-0AA3-1385-AE83F8928334}
    guiPrimaryProvider.Data1 = &H9FBF0887
    guiPrimaryProvider.Data2 = &H57AD
    guiPrimaryProvider.Data3 = &HAA3
    guiPrimaryProvider.Data4(0) = &H13
    guiPrimaryProvider.Data4(1) = &H85
    guiPrimaryProvider.Data4(2) = &HAE
    guiPrimaryProvider.Data4(3) = &H83
    guiPrimaryProvider.Data4(4) = &HF8
    guiPrimaryProvider.Data4(5) = &H92
    guiPrimaryProvider.Data4(6) = &H83
    guiPrimaryProvider.Data4(7) = &H34
       
    ' initialize first interface
    ' {9FBF0887-57AD-0AA3-1385-AE83F892833B}
    agInterfaces(0).Data1 = &H9FBF0887
    agInterfaces(0).Data2 = &H57AD
    agInterfaces(0).Data3 = &HAA3
    agInterfaces(0).Data4(0) = &H13
    agInterfaces(0).Data4(1) = &H85
    agInterfaces(0).Data4(2) = &HAE
    agInterfaces(0).Data4(3) = &H83
    agInterfaces(0).Data4(4) = &HF8
    agInterfaces(0).Data4(5) = &H92
    agInterfaces(0).Data4(6) = &H83
    agInterfaces(0).Data4(7) = &H3B
       
    ' initialize second interface
    ' {9FBF0887-57AD-0AA3-1385-AE83F8928348}
    agInterfaces(1).Data1 = &H9FBF0887
    agInterfaces(1).Data2 = &H57AD
    agInterfaces(1).Data3 = &HAA3
    agInterfaces(1).Data4(0) = &H13
    agInterfaces(1).Data4(1) = &H85
    agInterfaces(1).Data4(2) = &HAE
    agInterfaces(1).Data4(3) = &H83
    agInterfaces(1).Data4(4) = &HF8
    agInterfaces(1).Data4(5) = &H92
    agInterfaces(1).Data4(6) = &H83
    agInterfaces(1).Data4(7) = &H48
        
    ' atr only, no primary provider, no interfaces, no atr mask
    'lngResult = SCardIntroduceCardTypeA(lngContext, strCards, vbNullString, _
    '                vbNullString, 0, strATR, vbNullString, Len(strATR))
        
    ' atr, primary provider, interfaces, atr mask
    lngResult = SCardIntroduceCardTypeA(lngContext, strCards, guiPrimaryProvider, _
                     agInterfaces(0), UBound(agInterfaces) - LBound(agInterfaces) + 1, _
                     strATR, strATRMask, Len(strATR))
        
    Call EvaluateResult("SCardIntroduceCardTypeA", lngResult)
    
    ' set card CSP name if we're on Windows 2000 Beta2 or higher
    If bIsWindows2kB2 = True Then

        strCSPName = "Bogus Cryptographic Service Provider" + vbNullChar
        
        lngResult = SCardSetCardTypeProviderNameA(lngContext, strCards, _
                            SCARD_PROVIDER_CSP, strCSPName)
        
        Call EvaluateResult("SCardSetCardTypeProviderNameA", lngResult)
    End If
    
    ' list cards here to see newly introduced card in list
    '     use  getlength then redim
    
    ' first call uses NULL name buffer to get expected length of buffer
    lngResult = SCardListCardsA2(lngContext, lngNull, lngNull, 0, _
                    lngNull, lngCardListLen)
        
    Call EvaluateResult("SCardListCardsA-Length", lngResult)
    If SCARD_S_SUCCESS = lngResult Then
        ' make call to SCardListCardsA2 with resized buffer
        ReDim abyCardList(lngCardListLen)
           
        lngResult = SCardListCardsA3(lngContext, lngNull, lngNull, 0, _
                        abyCardList(0), lngCardListLen)
            
        Call EvaluateResult("SCardListCardsA-Redim", lngResult)
        ' process returned byte array
        strCardList = StrConv(abyCardList, vbUnicode)
        astrCards = ParseMultistring(strCardList, intCardCount)
        DisplayStringArray astrCards, intCardCount
    End If
    
    ' list interfaces of card just introduced
    ' reset buffer size
    lngInterfaceReturnCount = UBound(aguiInterfaces) - LBound(aguiInterfaces) + 1
      
    lngResult = SCardListInterfacesA(lngContext, strCards, aguiInterfaces(0), _
                   lngInterfaceReturnCount)
        
    Call EvaluateResult("SCardListInterfacesA", lngResult)
    If SCARD_S_SUCCESS = lngResult Then
        ' report interfaces just introduced
        For i = 0 To lngInterfaceReturnCount - 1
            DisplayGuid aguiInterfaces(i)
        Next i
    End If
    
    ' get card provider id
    ' set card name
    strCards = "BogusCard" + vbNullChar
        
    lngResult = SCardGetProviderIdA(lngContext, strCards, guiPrimaryProvider)
    Call EvaluateResult("SCardGetProviderIdA", lngResult)
    
    ' report PrimaryProvider guid
    If SCARD_S_SUCCESS = lngResult Then
        DisplayGuid guiPrimaryProvider
    End If
    
    ' get name of service provider if we're on Windows 2000 Beta2 or higher
    '   for provider types, see SCardAPI.bas SCARD_PROVIDER_*
    If bIsWindows2kB2 = True Then
        strCSPBuffer = String(intBufferSize, vbNullChar)
        lngCSPBufferLen = Len(strCSPBuffer)

        lngResult = SCardGetCardTypeProviderNameA(lngContext, strCards, _
                        SCARD_PROVIDER_CSP, strCSPBuffer, lngCSPBufferLen)
    
        Call EvaluateResult("SCardGetCardTypeProviderNameA", lngResult)
   
        ' report provider name
        If SCARD_S_SUCCESS = lngResult Then
            strOut = strTab + Left(strCSPBuffer, lngCSPBufferLen - 1)
            OutputLine strOut
        End If
    End If
   
    ' forget a card - the one just introduced (ANSI)
    lngResult = SCardForgetCardTypeA(lngContext, strCards)
        
    Call EvaluateResult("SCardForgetCardTypeA", lngResult)
    
    ' release context
    lngResult = SCardReleaseContext(lngContext)
        
    Call EvaluateResult("SCardReleaseContext", lngResult)
    
    ' report overall fail/success for easy scanning
    OutputLine strBar
    strOut = strTestTitle + Left(strSpacer, intOutputMax - Len(strTestTitle) _
                - intPassLength)
    If SCARD_S_SUCCESS = lngOverallResult Then
        strOut = strOut + strPass
    Else
        strOut = strOut + strFail
    End If
    OutputLine strOut
    OutputLine strBar

    ' separate this test run from others
    OutputLine ""
    
End Sub ' btnRuntests_Click()

Private Sub DisplayGuid(guiGuid As GUID)
    Dim strOut As String
    Dim strTemp As String
    Dim strByte As String
    
    ' indent
    strOut = strTab + "{"
    
    ' pairwise reverse the first (long) part of the guid
    strTemp = Hex(guiGuid.Data1)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte
    strTemp = Left(strTemp, 6)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte
    strTemp = Left(strTemp, 4)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte
    strTemp = Left(strTemp, 2)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte + "-"
    
    ' pairwise reverse the second (integer) part of the guid
    strTemp = Hex(guiGuid.Data2)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte
    strTemp = Left(strTemp, 2)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte + "-"
    
    ' pairwise reverse the third (integer) part of the guid
    strTemp = Hex(guiGuid.Data3)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte
    strTemp = Left(strTemp, 2)
    strByte = Right(strTemp, 2)
    strOut = strOut + strByte + "-"
    
    ' output the fourth (byte array) part of the guid
    For i = 0 To 7
        strOut = strOut + Hex(guiGuid.Data4(i))
    Next i
    strOut = strOut + "}"
    OutputLine strOut
    
End Sub ' DisplayGuid

Private Sub DisplayStringArray(astrArray As Variant, intArraySize As Integer)
    
    Dim strOut As String
    
    If 0 < intArraySize Then
        ' output array elements
        For i = 1 To intArraySize
            OutputLine strTab + astrArray(i - 1)
        Next i
    Else
        ' no elements in array
        OutputLine strTab + "none found"
    End If

End Sub ' DisplayStringArray

Private Sub DisplayEventState(dwEventState As Long)
    
    Dim strOut As String
    
    strOut = strTab + "eventstate: 0x" + Hex(dwEventState)
    OutputLine strOut
  
    If dwEventState And SCARD_STATE_UNAWARE Then
        strOut = strTab + "SCARD_STATE_UNAWARE"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_IGNORE Then
        strOut = strTab + "SCARD_STATE_IGNORE"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_CHANGED Then
        strOut = strTab + "SCARD_STATE_CHANGED"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_UNKNOWN Then
        strOut = strTab + "SCARD_STATE_UNKNOWN"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_UNAVAILABLE Then
        strOut = strTab + "SCARD_STATE_UNAVAILABLE"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_EMPTY Then
        strOut = strTab + "SCARD_STATE_EMPTY"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_PRESENT Then
        strOut = strTab + "SCARD_STATE_PRESENT"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_ATRMATCH Then
        strOut = strTab + "SCARD_STATE_ATRMATCH"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_EXCLUSIVE Then
        strOut = strTab + "SCARD_STATE_EXCLUSIVE"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_INUSE Then
        strOut = strTab + "SCARD_STATE_INUSE"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_MUTE Then
        strOut = strTab + "SCARD_STATE_MUTE"
        OutputLine strOut
    End If
    If dwEventState And SCARD_STATE_UNPOWERED Then
        strOut = strTab + "SCARD_STATE_UNPOWERED"
        OutputLine strOut
    End If
     
End Sub

Private Sub DisplayATRArray(abytArray, lngArraySize As Long)
    
    Dim strOut As String
    ' indent
    strOut = strTab
    
    For i = 0 To lngArraySize - 1
        If 0 <> i And 0 = (i Mod 8) Then
            ' format lines eight bytes long
            strOut = strOut + vbCrLf + strTab
        ElseIf 0 <> i And 0 = (i Mod 4) Then
            ' format within line for four byte blocks
            strOut = strOut + strTab
        End If
        
        If 0 = abytArray(i) Then
            ' display zero as double zero for readability
            strOut = strOut + "00 "
        ElseIf 14 > abytArray(i) Then
            ' display single digit hex with leading zero
            strOut = strOut + "0" + Hex(abytArray(i)) + " "
        Else
            ' convert decimals in array to hex for display
            strOut = strOut + Hex(abytArray(i)) + " "
        End If
    Next i
    
    OutputLine strOut

End Sub

Private Sub EvaluateResult(strFnName As String, lngResult As Long)
    ' output string
    Dim strOut As String
    ' string for text output of error value
    Dim strErrorValue As String
    ' leading zero padding for low hex values
    Dim strLeader As String
    strLeader = "00000000"
    
    ' print function name and pass/fail result
    strOut = strFnName + Left(strSpacer, intOutputMax - Len(strFnName) - intPassLength)
    
    If SCARD_S_SUCCESS = lngResult Then
        ' concatenate PASS tagline to output
        OutputLine strOut + strPass
    Else
        ' mark overall result flag
        lngOverallResult = SCARD_F_UNKNOWN_ERROR
        ' concatenate FAIL tagline to output
        OutputLine strOut + strFail
        ' convert result decimal number to hex string
        strErrorValue = Hex(lngResult)
        ' pad with leading zeros if necessary
        lngHexResultLen = Len(strErrorValue)
        strErrorValue = strTab + "Error: 0x" _
                        + Left(strLeader, 8 - lngHexResultLen) + strErrorValue
        OutputLine strErrorValue
        ' give message associated with error code
        strOut = ApiErrorMessage(lngResult)
        If 0 <> Len(strOut) Then
            OutputLine strTab + strOut
        End If
    End If
    
End Sub ' EvaluateResult

Private Sub OutputLine(strOut As String)

    txtOutputWindow.Text = txtOutputWindow.Text + strOut + vbCrLf
    
End Sub ' Output

