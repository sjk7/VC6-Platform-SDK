Attribute VB_Name = "SCardAPI"
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Declarations of the Windows Smart Card API
'
' Note: variable names, such as those in typedef's and function
'       parameters, have been retained from the C++ API definition
'

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Defines

' The context is a user context, and any
' database operations are performed within the
' domain of the user.
Public Const SCARD_SCOPE_USER As Long = 0

' The context is that of the current terminal,
' and any database operations are performed
' within the domain of that terminal.  (The
' calling application must have appropriate
' access permissions for any database actions.)
Public Const SCARD_SCOPE_TERMINAL As Long = 1

' The context is the system context, and any
' database operations are performed within the
' domain of the system.  (The calling
' application must have appropriate access
' permissions for any database actions.)
Public Const SCARD_SCOPE_SYSTEM As Long = 2

' Flag to have Resource Manager allocate buffer space
Public Const SCARD_AUTOALLOCATE As Long = -1

' Strings for managing the Smart Card Database
Public Const SCARD_ALL_READERS     As String = "SCard$AllReaders" + vbNullChar + vbNullChar
Public Const SCARD_DEFAULT_READERS As String = "SCard$DefaultReaders" + vbNullChar + vbNullChar
Public Const SCARD_LOCAL_READERS   As String = "SCard$LocalReaders" + vbNullChar + vbNullChar
Public Const SCARD_SYSTEM_READERS  As String = "SCard$SystemReaders" + vbNullChar + vbNullChar

' Primary Provider Id
Public Const SCARD_PROVIDER_PRIMARY As Long = 1
' Crypto Service Provider Id
Public Const SCARD_PROVIDER_CSP     As Long = 2

' There is no active protocol
Public Const SCARD_PROTOCOL_UNDEFINED   As Long = 0

' T=0 is the active protocol
Public Const SCARD_PROTOCOL_T0          As Long = 1

' T=1 is the active protocol
Public Const SCARD_PROTOCOL_T1          As Long = 2

' Raw is the active protocol.
Public Const SCARD_PROTOCOL_RAW         As Long = &H10000

' This is the mask of ISO defined transmission protocols
Public Const SCARD_PROTOCOL_Tx          As Long = SCARD_PROTOCOL_T0 Or SCARD_PROTOCOL_T1

' Use the default transmission parameters / card clock freq.
Public Const SCARD_PROTOCOL_DEFAULT     As Long = &H80000000

' Use optimal transmission parameters / card clock freq.
' Since using the optimal parameters is the default case no bit is defined to be 1
Public Const SCARD_PROTOCOL_OPTIMAL     As Long = &H0

' This application is not willing to share this
' card with other applications.
Public Const SCARD_SHARE_EXCLUSIVE      As Long = 1

' This application is willing to share this
' card with other applications.
Public Const SCARD_SHARE_SHARED         As Long = 2

' This application demands direct control of
' the reader, so it is not available to other
' applications.
Public Const SCARD_SHARE_DIRECT         As Long = 3

' Don't do anything special on close
Public Const SCARD_LEAVE_CARD           As Long = 0

' Reset the card on close
Public Const SCARD_RESET_CARD           As Long = 1

' Power down the card on close
Public Const SCARD_UNPOWER_CARD         As Long = 2

' Eject the card on close
Public Const SCARD_EJECT_CARD           As Long = 3

' Nothing bigger than this from getAttr
Public Const MAXIMUM_ATTR_STRING_LENGTH As Long = 32
' Limit the readers on the system
Public Const MAXIMUM_SMARTCARD_READERS  As Long = 10

' This value implies the driver is unaware
' of the current state of the reader.
Public Const SCARD_UNKNOWN              As Long = 0
' This value implies there is no card in
' the reader.
Public Const SCARD_ABSENT               As Long = 1
' This value implies there is a card is
' present in the reader, but that it has
' not been moved into position for use.
Public Const SCARD_PRESENT              As Long = 2
' This value implies there is a card in the
'  reader in position for use.  The card is
'  not powered.
Public Const SCARD_SWALLOWED            As Long = 3
' This value implies there is power is
' being provided to the card, but the
' Reader Driver is unaware of the mode of
' the card.
Public Const SCARD_POWERED              As Long = 4
' This value implies the card has been
' reset and is awaiting PTS negotiation.
Public Const SCARD_NEGOTIABLE           As Long = 5
' This value implies the card has been
' reset and specific communication
' protocols have been established.
Public Const SCARD_SPECIFIC             As Long = 6

' Ioctl parameters for IOCTL_SMARTCARD_POWER
' Power down the card.
Public Const SCARD_POWER_DOWN           As Long = 0
' Cycle power and reset the card.
Public Const SCARD_COLD_RESET           As Long = 1
' Force a reset on the card.
Public Const SCARD_WARM_RESET           As Long = 2

' Smartcard IOCTL class
Public Const FILE_DEVICE_SMARTCARD      As Long = &H310000

' Reader action IOCTLs
Public Const IOCTL_SMARTCARD_POWER           As Long = FILE_DEVICE_SMARTCARD + &H4
Public Const IOCTL_SMARTCARD_GET_ATTRIBUTE   As Long = FILE_DEVICE_SMARTCARD + &H8
Public Const IOCTL_SMARTCARD_SET_ATTRIBUTE   As Long = FILE_DEVICE_SMARTCARD + &HC
Public Const IOCTL_SMARTCARD_CONFISCATE      As Long = FILE_DEVICE_SMARTCARD + &H10
Public Const IOCTL_SMARTCARD_TRANSMIT        As Long = FILE_DEVICE_SMARTCARD + &H14
Public Const IOCTL_SMARTCARD_EJECT           As Long = FILE_DEVICE_SMARTCARD + &H18
Public Const IOCTL_SMARTCARD_SWALLOW         As Long = FILE_DEVICE_SMARTCARD + &H1C
Public Const IOCTL_SMARTCARD_IS_PRESENT      As Long = FILE_DEVICE_SMARTCARD + &H28
Public Const IOCTL_SMARTCARD_IS_ABSENT       As Long = FILE_DEVICE_SMARTCARD + &H2C
Public Const IOCTL_SMARTCARD_SET_PROTOCOL    As Long = FILE_DEVICE_SMARTCARD + &H30
Public Const IOCTL_SMARTCARD_GET_STATE       As Long = FILE_DEVICE_SMARTCARD + &H38
Public Const IOCTL_SMARTCARD_GET_LAST_ERROR  As Long = FILE_DEVICE_SMARTCARD + &H3C

' Vendor information definitions - classes
Public Const SCARD_CLASS_VENDOR_INFO    As Long = &H10000
' Communication definitions
Public Const SCARD_CLASS_COMMUNICATIONS As Long = &H20000
' Protocol definitions
Public Const SCARD_CLASS_PROTOCOL       As Long = &H30000
' Power Management definitions
Public Const SCARD_CLASS_POWER_MGMT     As Long = &H40000
' Security Assurance definitions
Public Const SCARD_CLASS_SECURITY       As Long = &H50000
' Mechanical characteristic definitions
Public Const SCARD_CLASS_MECHANICAL     As Long = &H60000
' Vendor specific definitions
Public Const SCARD_CLASS_VENDOR_DEFINED As Long = &H70000
' Interface Device Protocol options
Public Const SCARD_CLASS_IFD_PROTOCOL   As Long = &H80000
' ICC State specific definitions
Public Const SCARD_CLASS_ICC_STATE      As Long = &H90000
' System-specific definitions
Public Const SCARD_CLASS_SYSTEM         As Long = &H7FFF0000
' Vendor information definitions - items
Public Const SCARD_ATTR_VENDOR_NAME              As Long = SCARD_CLASS_VENDOR_INFO + &H100
Public Const SCARD_ATTR_VENDOR_IFD_TYPE          As Long = SCARD_CLASS_VENDOR_INFO + &H101
Public Const SCARD_ATTR_VENDOR_IFD_VERSION       As Long = SCARD_CLASS_VENDOR_INFO + &H102
Public Const SCARD_ATTR_VENDOR_IFD_SERIAL_NO     As Long = SCARD_CLASS_VENDOR_INFO + &H103
Public Const SCARD_ATTR_CHANNEL_ID               As Long = SCARD_CLASS_COMMUNICATIONS + &H110
Public Const SCARD_ATTR_PROTOCOL_TYPES           As Long = SCARD_CLASS_PROTOCOL + &H120
Public Const SCARD_ATTR_DEFAULT_CLK              As Long = SCARD_CLASS_PROTOCOL + &H121
Public Const SCARD_ATTR_MAX_CLK                  As Long = SCARD_CLASS_PROTOCOL + &H122
Public Const SCARD_ATTR_DEFAULT_DATA_RATE        As Long = SCARD_CLASS_PROTOCOL + &H123
Public Const SCARD_ATTR_MAX_DATA_RATE            As Long = SCARD_CLASS_PROTOCOL + &H124
Public Const SCARD_ATTR_MAX_IFSD                 As Long = SCARD_CLASS_PROTOCOL + &H125
Public Const SCARD_ATTR_POWER_MGMT_SUPPORT       As Long = SCARD_CLASS_POWER_MGMT + &H131
Public Const SCARD_ATTR_USER_TO_CARD_AUTH_DEVICE As Long = SCARD_CLASS_SECURITY + &H140
Public Const SCARD_ATTR_USER_AUTH_INPUT_DEVICE   As Long = SCARD_CLASS_SECURITY + &H142
Public Const SCARD_ATTR_CHARACTERISTICS          As Long = SCARD_CLASS_MECHANICAL + &H150
Public Const SCARD_ATTR_CURRENT_PROTOCOL_TYPE    As Long = SCARD_CLASS_IFD_PROTOCOL + &H201
Public Const SCARD_ATTR_CURRENT_CLK              As Long = SCARD_CLASS_IFD_PROTOCOL + &H202
Public Const SCARD_ATTR_CURRENT_F                As Long = SCARD_CLASS_IFD_PROTOCOL + &H203
Public Const SCARD_ATTR_CURRENT_D                As Long = SCARD_CLASS_IFD_PROTOCOL + &H204
Public Const SCARD_ATTR_CURRENT_N                As Long = SCARD_CLASS_IFD_PROTOCOL + &H205
Public Const SCARD_ATTR_CURRENT_W                As Long = SCARD_CLASS_IFD_PROTOCOL + &H206
Public Const SCARD_ATTR_CURRENT_IFSC             As Long = SCARD_CLASS_IFD_PROTOCOL + &H207
Public Const SCARD_ATTR_CURRENT_IFSD             As Long = SCARD_CLASS_IFD_PROTOCOL + &H208
Public Const SCARD_ATTR_CURRENT_BWT              As Long = SCARD_CLASS_IFD_PROTOCOL + &H209
Public Const SCARD_ATTR_CURRENT_CWT              As Long = SCARD_CLASS_IFD_PROTOCOL + &H20A
Public Const SCARD_ATTR_CURRENT_EBC_ENCODING     As Long = SCARD_CLASS_IFD_PROTOCOL + &H20B
Public Const SCARD_ATTR_EXTENDED_BWT             As Long = SCARD_CLASS_IFD_PROTOCOL + &H20C
Public Const SCARD_ATTR_ICC_PRESENCE             As Long = SCARD_CLASS_ICC_STATE + &H300
Public Const SCARD_ATTR_ICC_INTERFACE_STATUS     As Long = SCARD_CLASS_ICC_STATE + &H301
Public Const SCARD_ATTR_CURRENT_IO_STATE         As Long = SCARD_CLASS_ICC_STATE + &H302
Public Const SCARD_ATTR_ATR_STRING               As Long = SCARD_CLASS_ICC_STATE + &H303
Public Const SCARD_ATTR_ICC_TYPE_PER_ATR         As Long = SCARD_CLASS_ICC_STATE + &H304
Public Const SCARD_ATTR_ESC_RESET                As Long = SCARD_CLASS_VENDOR_DEFINED + &HA000
Public Const SCARD_ATTR_ESC_CANCEL               As Long = SCARD_CLASS_VENDOR_DEFINED + &HA003
Public Const SCARD_ATTR_ESC_AUTHREQUEST          As Long = SCARD_CLASS_VENDOR_DEFINED + &HA005
Public Const SCARD_ATTR_MAXINPUT                 As Long = SCARD_CLASS_VENDOR_DEFINED + &HA007
Public Const SCARD_ATTR_DEVICE_UNIT              As Long = SCARD_CLASS_SYSTEM + &H1
Public Const SCARD_ATTR_DEVICE_IN_USE            As Long = SCARD_CLASS_SYSTEM + &H2
Public Const SCARD_ATTR_DEVICE_FRIENDLY_NAME_A   As Long = SCARD_CLASS_SYSTEM + &H3
Public Const SCARD_ATTR_DEVICE_SYSTEM_NAME_A     As Long = SCARD_CLASS_SYSTEM + &H4
Public Const SCARD_ATTR_DEVICE_FRIENDLY_NAME_W   As Long = SCARD_CLASS_SYSTEM + &H5
Public Const SCARD_ATTR_DEVICE_SYSTEM_NAME_W     As Long = SCARD_CLASS_SYSTEM + &H6
Public Const SCARD_ATTR_SUPRESS_T1_IFS_REQUEST   As Long = SCARD_CLASS_SYSTEM + &H7

' types for tracking cards within readers

' state of a reader
Type SCARD_READERSTATEA
    ' reader name
    szReader        As String
    ' user defined data
    pvUserData      As Long
    ' current state of reader at time of call
    dwCurrentState  As Long
    ' state of reader after state change
    dwEventState    As Long
    ' Number of bytes in the returned ATR
    cbAtr           As Long
    ' Atr of inserted card, (extra alignment bytes)
    rgbAtr(35)      As Byte
End Type

' The application is unaware of the current state, and would like to
' know.  The use of this value results in an immediate return
' from state transition monitoring services.  This is represented by
' all bits set to zero.
Public Const SCARD_STATE_UNAWARE     As Long = &H0

' The application requested that this reader be ignored.  No other
' bits will be set.
Public Const SCARD_STATE_IGNORE      As Long = &H1

' This implies that there is a difference between the state
' believed by the application, and the state known by the Service
' Manager.  When this bit is set, the application may assume a
' significant state change has occurred on this reader.
Public Const SCARD_STATE_CHANGED     As Long = &H2

' This implies that the given reader name is not recognized by
' the Service Manager.  If this bit is set, then SCARD_STATE_CHANGED
' and SCARD_STATE_IGNORE will also be set.
Public Const SCARD_STATE_UNKNOWN     As Long = &H4

' This implies that the actual state of this reader is not
' available.  If this bit is set, then all the following bits are clear.
Public Const SCARD_STATE_UNAVAILABLE As Long = &H8

' This implies that there is not card in the reader.  If this bit
' is set, all the following bits will be clear.
Public Const SCARD_STATE_EMPTY       As Long = &H10

' This implies that there is a card in the reader.
Public Const SCARD_STATE_PRESENT     As Long = &H20

' This implies that there is a card in the reader with an ATR
' matching one of the target cards.  If this bit is set,
' SCARD_STATE_PRESENT will also be set.  This bit is only returned
' on the SCardLocateCard() service.
Public Const SCARD_STATE_ATRMATCH    As Long = &H40

' This implies that the card in the reader is allocated for exclusive
' use by another application.  If this bit is set,
' SCARD_STATE_PRESENT will also be set.
Public Const SCARD_STATE_EXCLUSIVE   As Long = &H80

' This implies that the card in the reader is in use by one or more'
' other applications, but may be connected to in shared mode.  If
' this bit is set, SCARD_STATE_PRESENT will also be set.
Public Const SCARD_STATE_INUSE       As Long = &H100

' This implies that the card in the reader is unresponsive or not
' supported by the reader or software.
Public Const SCARD_STATE_MUTE        As Long = &H200

' This implies that the card in the reader has not been powered up.
Public Const SCARD_STATE_UNPOWERED   As Long = &H400

' types for providing access to the I/O capabilities of the reader drivers

' I/O request control
Type SCARD_IO_REQUEST
    ' Protocol identifier
    dwProtocol As Long
    ' Protocol Control Information Length
    dbPciLength As Long
End Type

' T=0 command
Type SCARD_T0_Command
    ' the instruction class
    bCla As Byte
    ' the instruction code within the instruction class
    bIns As Byte
    ' first parameter of the function
    bP1 As Byte
    ' second parameter of the function
    bP2 As Byte
    ' size of the I/O transfer
    bP3 As Byte
End Type

' T=0 request
Type SCARD_T0_REQUEST
    ' I/O request control
    ioRequest As SCARD_IO_REQUEST
    ' first return code from the instruction
    bSw1 As Byte
    ' second return code from the instruction
    bSw2 As Byte
    ' I/O command
    CmdBytes As SCARD_T0_Command
End Type

' T=1 request
Type SCARD_T1_REQUEST
    ' I/O request control
    ioRequest As SCARD_IO_REQUEST
End Type

' smart card dialog definitions

' show UI only if required to select card
Public Const SC_DLG_MINIMAL_UI      As Long = 1

' do not show UI in any case
Public Const SC_DLG_NO_UI           As Long = 2

' show UI in every case
Public Const SC_DLG_FORCE_UI        As Long = 4

' dialog error returns
Public Const SCERR_NOCARDNAME       As Long = &H4000
Public Const SCERR_NOGUIDS          As Long = &H8000


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Functions

Public Declare Function SCardEstablishContext _
Lib "winscard.dll" _
( _
    ByVal dwScope As Long, _
    ByVal pvReserved1 As Any, _
    ByVal pvReserved2 As Any, _
    ByRef phContext As Long _
    ) As Long

Public Declare Function SCardReleaseContext _
Lib "winscard.dll" _
( _
    ByVal hContext As Long _
    ) As Long

Public Declare Function SCardFreeMemory _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal pvMem As Long _
    ) As Long
    
Public Declare Function SCardCancel _
Lib "winscard.dll" _
( _
    ByVal hContext As Long _
    ) As Long
    
Public Declare Function SCardReconnect _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal dwShareMode As Long, _
    ByVal dwPreferredProtocols As Long, _
    ByVal dwInitialization As Long, _
    ByRef pdwActiveProtocol _
    ) As Long
    
Public Declare Function SCardDisconnect _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal dwDisposition As Long _
    ) As Long

Public Declare Function SCardBeginTransaction _
Lib "winscard.dll" _
( _
    ByVal hCard As Long _
    ) As Long

Public Declare Function SCardEndTransaction _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal dwDisposition As Long _
    ) As Long

Public Declare Function SCardTransmit _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByRef pioSendPci As SCARD_IO_REQUEST, _
    ByRef pbSendBuffer As Byte, _
    ByVal cbSendLength As Long, _
    ByRef pioRecvPci As SCARD_IO_REQUEST, _
    ByRef pbRecvBuffer As Byte, _
    ByRef pcbRecvLength As Long _
    ) As Long

Public Declare Function SCardControl _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal dwControlCode As Long, _
    ByRef pvInBuffer As Byte, _
    ByVal cbInBufferSize As Long, _
    ByRef pvOutBuffer As Byte, _
    ByVal cbOutBufferSize As Long, _
    ByRef pcbBytesReturned As Long _
    ) As Long

Public Declare Function SCardGetAttrib _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal dwAttrId As Long, _
    ByRef pbAttr As Byte, _
    ByRef pcbAttrLen As Long _
    ) As Long

Public Declare Function SCardSetAttrib _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal dwAttrId As Long, _
    ByRef pbAttr As Byte, _
    ByVal cbAttrLen As Long _
    ) As Long
    
Public Declare Function SCardListReaderGroupsA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal mszGroups As String, _
    ByRef pcchGroups As Long _
    ) As Long
    
Public Declare Function SCardListReadersA _
Lib "winscard.dll" _
( _
    ByVal SCARDCONTEXT As Long, _
    ByVal mszGroups As String, _
    ByVal mszReaders As String, _
    ByRef pcchReaders As Long _
    ) As Long

Public Declare Function SCardListCardsA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByRef pbAtr As Byte, _
    ByRef rgguidInterfaces As GUID, _
    ByVal cguidInterfaceCount As Long, _
    ByVal mszCards As String, _
    ByRef pcchCards As Long _
    ) As Long

' second declaration for passing NULL through ATR and GUID parameters
Public Declare Function SCardListCardsA2 _
Lib "winscard.dll" _
Alias "SCardListCardsA" _
( _
    ByVal hContext As Long, _
    ByVal pbAtr As Long, _
    ByVal rgguidInterfaces As Long, _
    ByVal cguidInterfaceCount As Long, _
    ByVal mszCards As String, _
    ByRef pcchCards As Long _
    ) As Long

' third declaration for passing NULL through ATR and GUID parameters, BYTE name parameter
Public Declare Function SCardListCardsA3 _
Lib "winscard.dll" _
Alias "SCardListCardsA" _
( _
    ByVal hContext As Long, _
    ByVal pbAtr As Long, _
    ByVal rgguidInterfaces As Long, _
    ByVal cguidInterfaceCount As Long, _
    ByRef mszCards As Byte, _
    ByRef pcchCards As Long _
    ) As Long

Public Declare Function SCardListInterfacesA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szCard As String, _
    ByRef pguidInterfaces As GUID, _
    ByRef pcguidInterfaces As Long _
    ) As Long
    
Public Declare Function SCardGetProviderIdA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szCard As String, _
    ByRef pguidProviderId As GUID _
    ) As Long
    
Public Declare Function SCardGetCardTypeProviderNameA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szCardName As String, _
    ByVal dwProviderId As Long, _
    ByVal szProvider As String, _
    ByRef pcchProvider As Long _
    ) As Long

Public Declare Function SCardIntroduceReaderGroupA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szGroupName As String _
    ) As Long
    
Public Declare Function SCardForgetReaderGroupA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szGroupName As String _
    ) As Long
    
Public Declare Function SCardIntroduceReaderA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szReadeName As String, _
    ByVal szDeviceName As String _
    ) As Long
    
Public Declare Function SCardForgetReaderA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szReaderName As String _
    ) As Long
    
Public Declare Function SCardAddReaderToGroupA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szReaderName As String, _
    ByVal szGroupName As String _
    ) As Long
    
Public Declare Function SCardRemoveReaderFromGroupA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szReaderName As String, _
    ByVal szGroupName As String _
    ) As Long
    
Public Declare Function SCardIntroduceCardTypeA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szCardName As String, _
    ByRef pguidPrimaryProvider As GUID, _
    ByRef pguidInterfaces As GUID, _
    ByVal dwInterfaceCount As Long, _
    ByVal pbAtr As String, _
    ByVal pbAtrMask As String, _
    ByVal cbAtrLen As Long _
    ) As Long

Public Declare Function SCardSetCardTypeProviderNameA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szCardName As String, _
    ByVal dwProviderId As Long, _
    ByVal szProvider As String _
    ) As Long

Public Declare Function SCardForgetCardTypeA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szCardName As String _
    ) As Long
    
Public Declare Function SCardLocateCardsA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal mszCards As String, _
    ByRef rgReaderStates As SCARD_READERSTATEA, _
    ByVal cReaders As Long _
    ) As Long

Public Declare Function SCardGetStatusChangeA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal dwTimeout As Long, _
    ByRef rgReaderStates As SCARD_READERSTATEA, _
    ByVal cReaders As Long _
    ) As Long
 
Public Declare Function SCardConnectA _
Lib "winscard.dll" _
( _
    ByVal hContext As Long, _
    ByVal szReader As String, _
    ByVal dwShareMode As Long, _
    ByVal dwPreferredProtocols As Long, _
    ByRef phCard As Long, _
    ByRef pdwActiveProtocol As Long _
    ) As Long
    
Public Declare Function SCardStatusA _
Lib "winscard.dll" _
( _
    ByVal hCard As Long, _
    ByVal mszReaderNames As String, _
    ByRef pcchReaderLen As Long, _
    ByRef pdwState As Long, _
    ByRef pdwProtocol As Long, _
    ByRef pbAtr As Byte, _
    ByRef pcbAtrLen As Long _
    ) As Long
    

'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Helper Defines

' Null value suitable for passing in as parameter
Public Const lngNull As Long = 0

' GUID data type
Type GUID
    Data1 As Long
    Data2 As Integer
    Data3 As Integer
    Data4(0 To 7) As Byte
End Type

' flags for API error message reporting
Enum EFORMAT_MESSAGE
    FORMAT_MESSAGE_NONE = &H0
    FORMAT_MESSAGE_ALLOCATE_BUFFER = &H100
    FORMAT_MESSAGE_IGNORE_INSERTS = &H200
    FORMAT_MESSAGE_FROM_STRING = &H400
    FORMAT_MESSAGE_FROM_HMODULE = &H800
    FORMAT_MESSAGE_FROM_SYSTEM = &H1000
    FORMAT_MESSAGE_ARGUMENT_ARRAY = &H2000
    FORMAT_MESSAGE_MAX_WIDTH_MASK = &HFF
End Enum


'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Helper Functions

' pull an error message from a system image
Public Declare Function FormatMessageA _
Lib "kernel32" _
( _
    ByVal dwFlags As Long, _
    ByVal lpSources As Long, _
    ByVal dwMessageId As Long, _
    ByVal dwLanguageId As Long, _
    ByVal lpBuffer As String, _
    ByVal nSize As Long, _
    ByVal Arguments As Long _
    ) As Long

' ApiErrorMessage
'
' returns the message associated with an error code
'
' assumptions:
'
'   error code is a system error
'
' arguments:
'
'   lngError - supplies the error code
'
' return value:
'
'   string - contains the system message of the error, or
'            the empty string if no message could be found
'
Public Function ApiErrorMessage(ByVal lngError As Long) As String
    ' length of message
    Dim lngMessageLen   As Long
    ' message holder
    Dim strMessage      As String
    ' initialize message holder
    strMessage = String(256, vbNullChar)
    
    ' look up error from system
    lngMessageLen = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM Or _
                      FORMAT_MESSAGE_IGNORE_INSERTS, _
                      lngNull, lngError, 0&, strMessage, Len(strMessage), lngNull)
                      
    If lngMessageLen Then
        ' truncate message to reported length, less c-style null terminator
        ApiErrorMessage = Left$(strMessage, lngMessageLen - 1)
    Else
        ' return empty string
        ApiErrorMessage = ""
    End If
End Function


' ParseMultistring
'
' converts C++ type multistring to VB type array of strings
' and reports the number of strings in array
'
' assumptions:
'
'   first parameter actually contains a good format multistring
'   no checking is done for bad format, empty string, or null pointer
'
' arguments:
'
'   strMultistring - supplies the multistring to be converted,
'       whose format is concatenated null terminated strings, with an
'       additional null terminator at the end of the last string
'
'   intReaderCount - returns the number of strings in the array
'       note that an array with 4 strings will have indexes 0 to 3
'
' return value:
'
'   an array of strings - can contain one empty element if no readers found
'   indirectly through second parameter, the count of strings in the array
'
Public Function ParseMultistring( _
    ByRef strMultistring As String, _
    ByRef intReaderCount As Integer _
    ) As Variant
    
    ' string parsed out from multistring
    Dim strCurrent As String
    ' copy of multistring, so that calling program still has a good copy
    Dim strWorking As String
    ' reader names in array of strings
    Dim arrReaderNames() As String
    ' position of first null terminator within the multistring
    Dim lngNullPosition As Long
    
    ' initialize current string to empty
    strCurrent = ""
    ' make a copy of the input multistring
    strWorking = strMultistring
    ' set count of readers to zero
    intReaderCount = 0
    ' get position of first null terminator
    lngNullPosition = InStr(strWorking, vbNullChar)
    
    ' when all strings and their individual null terminators have been
    ' parsed out of the multistring, only the final null terminator will remain
    While (lngNullPosition > 1)
        ' resize the array to add another element, preserving old elements
        ReDim Preserve arrReaderNames(intReaderCount)
        ' parse out the first string in the multistring
    strCurrent = Left(strWorking, lngNullPosition - 1)
        ' copy this string into the array
        arrReaderNames(intReaderCount) = strCurrent
        ' delete this string from the multistring
        strWorking = Right(strWorking, Len(strWorking) - (lngNullPosition + 1) + 1)
        ' get position of the first null terminator
        lngNullPosition = InStr(strWorking, vbNullChar)
        ' increase the string count by one for the string just parsed
        intReaderCount = intReaderCount + 1
    Wend
    
    ' return the completed array
    ParseMultistring = arrReaderNames
    
End Function ' ParseMultistring


