Attribute VB_Name = "SCardErr"
'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' Error definitions of the Windows Smart Card API
'


' success result indicated by API call
Public Const NO_ERROR As Long = 0
Public Const SCARD_S_SUCCESS As Long = NO_ERROR

'//
'//  Values are 32 bit values layed out as follows:
'//
'//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
'//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
'//  +---+-+-+-----------------------+-------------------------------+
'//  |Sev|C|R|     Facility          |               Code            |
'//  +---+-+-+-----------------------+-------------------------------+
'//
'//  where
'//
'//      Sev - is the severity code
'//
'//          00 - Success
'//          01 - Informational
'//          10 - Warning
'//          11 - Error
'//
'//      C - is the Customer code flag
'//
'//      R - is a reserved bit
'//
'//      Facility - is the facility code
'//
'//      Code - is the facility's status code
'//
'//
'// Define the facility codes
'//
'Public Const FACILITY_SYSTEM                  0x0
'Public Const FACILITY_SCARD                   0x10


'//
'// Define the severity codes
'//


'//
'// MessageId: SCARD_F_INTERNAL_ERROR
'//
'// MessageText:
'//
'//  An internal consistency check failed
'//
Public Const SCARD_F_INTERNAL_ERROR           As Long = &H80100001

'//
'// MessageId: SCARD_E_CANCELLED
'//
'// MessageText:
'//
'//  The action was cancelled by an SCardCancel request
'//
Public Const SCARD_E_CANCELLED                As Long = &H80100002

'//
'// MessageId: SCARD_E_INVALID_HANDLE
'//
'// MessageText:
'//
'//  The supplied handle was invalid
'//
Public Const SCARD_E_INVALID_HANDLE           As Long = &H80100003

'//
'// MessageId: SCARD_E_INVALID_PARAMETER
'//
'// MessageText:
'//
'//  One or more of the supplied parameters could not be properly interpreted
'//
Public Const SCARD_E_INVALID_PARAMETER        As Long = &H80100004

'//
'// MessageId: SCARD_E_INVALID_TARGET
'//
'// MessageText:
'//
'//  Registry startup information is missing or invalid
'//
Public Const SCARD_E_INVALID_TARGET           As Long = &H80100005

'//
'// MessageId: SCARD_E_NO_MEMORY
'//
'// MessageText:
'//
'//  Not enough memory available to complete this command
'//
Public Const SCARD_E_NO_MEMORY                As Long = &H80100006

'//
'// MessageId: SCARD_F_WAITED_TOO_LONG
'//
'// MessageText:
'//
'//  An internal consistency timer has expired
'//
Public Const SCARD_F_WAITED_TOO_LONG          As Long = &H80100007

'//
'// MessageId: SCARD_E_INSUFFICIENT_BUFFER
'//
'// MessageText:
'//
'//  The data buffer to receive returned data is too small for the returned data
'//
Public Const SCARD_E_INSUFFICIENT_BUFFER      As Long = &H80100008

'//
'// MessageId: SCARD_E_UNKNOWN_READER
'//
'// MessageText:
'//
'//  The specified reader name is not recognized
'//
Public Const SCARD_E_UNKNOWN_READER           As Long = &H80100009

'//
'// MessageId: SCARD_E_TIMEOUT
'//
'// MessageText:
'//
'//  The user-specified timeout value has expired
'//
Public Const SCARD_E_TIMEOUT                  As Long = &H8010000A

'//
'// MessageId: SCARD_E_SHARING_VIOLATION
'//
'// MessageText:
'//
'//  The smart card cannot be accessed because of other connections outstanding
'//
Public Const SCARD_E_SHARING_VIOLATION        As Long = &H8010000B

'//
'// MessageId: SCARD_E_NO_SMARTCARD
'//
'// MessageText:
'//
'//  The operation requires a Smart Card, but no Smart Card is currently in the device
'//
Public Const SCARD_E_NO_SMARTCARD             As Long = &H8010000C

'//
'// MessageId: SCARD_E_UNKNOWN_CARD
'//
'// MessageText:
'//
'//  The specified smart card name is not recognized
'//
Public Const SCARD_E_UNKNOWN_CARD             As Long = &H8010000D

'//
'// MessageId: SCARD_E_CANT_DISPOSE
'//
'// MessageText:
'//
'//  The system could not dispose of the media in the requested manner
'//
Public Const SCARD_E_CANT_DISPOSE             As Long = &H8010000E

'//
'// MessageId: SCARD_E_PROTO_MISMATCH
'//
'// MessageText:
'//
'//  The requested protocols are incompatible with the protocol currently in use with the smart card
'//
Public Const SCARD_E_PROTO_MISMATCH           As Long = &H8010000F

'//
'// MessageId: SCARD_E_NOT_READY
'//
'// MessageText:
'//
'//  The reader or smart card is not ready to accept commands
'//
Public Const SCARD_E_NOT_READY                As Long = &H80100010

'//
'// MessageId: SCARD_E_INVALID_VALUE
'//
'// MessageText:
'//
'//  One or more of the supplied parameters values could not be properly interpreted
'//
Public Const SCARD_E_INVALID_VALUE            As Long = &H80100011

'//
'// MessageId: SCARD_E_SYSTEM_CANCELLED
'//
'// MessageText:
'//
'//  The action was cancelled by the system, presumably to log off or shut down
'//
Public Const SCARD_E_SYSTEM_CANCELLED         As Long = &H80100012

'//
'// MessageId: SCARD_F_COMM_ERROR
'//
'// MessageText:
'//
'//  An internal communications error has been detected
'//
Public Const SCARD_F_COMM_ERROR               As Long = &H80100013

'//
'// MessageId: SCARD_F_UNKNOWN_ERROR
'//
'// MessageText:
'//
'//  An internal error has been detected, but the source is unknown
'//
Public Const SCARD_F_UNKNOWN_ERROR            As Long = &H80100014

'//
'// MessageId: SCARD_E_INVALID_ATR
'//
'// MessageText:
'//
'//  An ATR obtained from the registry is not a valid ATR string
'//
Public Const SCARD_E_INVALID_ATR              As Long = &H80100015

'//
'// MessageId: SCARD_E_NOT_TRANSACTED
'//
'// MessageText:
'//
'//  An attempt was made to end a non-existent transaction
'//
Public Const SCARD_E_NOT_TRANSACTED           As Long = &H80100016

'//
'// MessageId: SCARD_E_READER_UNAVAILABLE
'//
'// MessageText:
'//
'//  The specified reader is not currently available for use
'//
Public Const SCARD_E_READER_UNAVAILABLE       As Long = &H80100017

'//
'// MessageId: SCARD_P_SHUTDOWN
'//
'// MessageText:
'//
'//  PRIVATE -- Internal flag to force server termination
'//
Public Const SCARD_P_SHUTDOWN                 As Long = &H80100018

'//
'// MessageId: SCARD_E_PCI_TOO_SMALL
'//
'// MessageText:
'//
'//  The PCI Receive buffer was too small
'//
Public Const SCARD_E_PCI_TOO_SMALL            As Long = &H80100019

'//
'// MessageId: SCARD_E_READER_UNSUPPORTED
'//
'// MessageText:
'//
'//  The reader driver does not meet minimal requirements for support
'//
Public Const SCARD_E_READER_UNSUPPORTED       As Long = &H8010001A

'//
'// MessageId: SCARD_E_DUPLICATE_READER
'//
'// MessageText:
'//
'//  The reader driver did not produce a unique reader name
'//
Public Const SCARD_E_DUPLICATE_READER         As Long = &H8010001B

'//
'// MessageId: SCARD_E_CARD_UNSUPPORTED
'//
'// MessageText:
'//
'//  The smart card does not meet minimal requirements for support
'//
Public Const SCARD_E_CARD_UNSUPPORTED         As Long = &H8010001C

'//
'// MessageId: SCARD_E_NO_SERVICE
'//
'// MessageText:
'//
'//  The Smart card resource manager is not running
'//
Public Const SCARD_E_NO_SERVICE               As Long = &H8010001D

'//
'// MessageId: SCARD_E_SERVICE_STOPPED
'//
'// MessageText:
'//
'//  The Smart card resource manager has shut down
'//
Public Const SCARD_E_SERVICE_STOPPED          As Long = &H8010001E

'//
'// MessageId: SCARD_E_UNEXPECTED
'//
'// MessageText:
'//
'//  An unexpected card error has occurred
'//
Public Const SCARD_E_UNEXPECTED               As Long = &H8010001F

'//
'// MessageId: SCARD_E_ICC_INSTALLATION
'//
'// MessageText:
'//
'//  No Primary Provider can be found for the smart card
'//
Public Const SCARD_E_ICC_INSTALLATION         As Long = &H80100020

'//
'// MessageId: SCARD_E_ICC_CREATEORDER
'//
'// MessageText:
'//
'//  The requested order of object creation is not supported
'//
Public Const SCARD_E_ICC_CREATEORDER          As Long = &H80100021

'//
'// MessageId: SCARD_E_UNSUPPORTED_FEATURE
'//
'// MessageText:
'//
'//  This smart card does not support the reqested feature
'//
Public Const SCARD_E_UNSUPPORTED_FEATURE      As Long = &H80100022

'//
'// MessageId: SCARD_E_DIR_NOT_FOUND
'//
'// MessageText:
'//
'//  The identified directory does not exist in the smart card
'//
Public Const SCARD_E_DIR_NOT_FOUND            As Long = &H80100023

'//
'// MessageId: SCARD_E_FILE_NOT_FOUND
'//
'// MessageText:
'//
'//  The identified file does not exist in the smart card
'//
Public Const SCARD_E_FILE_NOT_FOUND           As Long = &H80100024

'//
'// MessageId: SCARD_E_NO_DIR
'//
'// MessageText:
'//
'//  The supplied path does not represent a smart card directory
'//
Public Const SCARD_E_NO_DIR                   As Long = &H80100025

'//
'// MessageId: SCARD_E_NO_FILE
'//
'// MessageText:
'//
'//  The supplied path does not represent a smart card file
'//
Public Const SCARD_E_NO_FILE                  As Long = &H80100026

'//
'// MessageId: SCARD_E_NO_ACCESS
'//
'// MessageText:
'//
'//  Access is denied to this file
'//
Public Const SCARD_E_NO_ACCESS                As Long = &H80100027

'//
'// MessageId: SCARD_E_WRITE_TOO_MANY
'//
'// MessageText:
'//
'//  An attempt was made to write more data than would fit in the target object
'//
Public Const SCARD_E_WRITE_TOO_MANY           As Long = &H80100028

'//
'// MessageId: SCARD_E_BAD_SEEK
'//
'// MessageText:
'//
'//  There was an error trying to set the smart card file object pointer
'//
Public Const SCARD_E_BAD_SEEK                 As Long = &H80100029

'//
'// MessageId: SCARD_E_INVALID_CHV
'//
'// MessageText:
'//
'//  The supplied PIN is incorrect
'//
Public Const SCARD_E_INVALID_CHV              As Long = &H8010002A

'//
'// MessageId: SCARD_E_UNKNOWN_RES_MNG
'//
'// MessageText:
'//
'//  An unrecognized error code was returned from a layered component
'//
Public Const SCARD_E_UNKNOWN_RES_MNG          As Long = &H8010002B

'//
'// MessageId: SCARD_E_NO_SUCH_CERTIFICATE
'//
'// MessageText:
'//
'//  The requested certificate does not exist.
'//
Public Const SCARD_E_NO_SUCH_CERTIFICATE      As Long = &H8010002C

'//
'// MessageId: SCARD_E_CERTIFICATE_UNAVAILABLE
'//
'// MessageText:
'//
'//  The requested certificate could not be obtained.
'//
Public Const SCARD_E_CERTIFICATE_UNAVAILABLE  As Long = &H8010002D

'//
'// MessageId: SCARD_E_NO_READERS_AVAILABLE
'//
'// MessageText:
'//
'//  None of the specified readers are currently available for use
'//
Public Const SCARD_E_NO_READERS_AVAILABLE     As Long = &H8010002E

'//
'// These are warning codes.
'//
'//
'// MessageId: SCARD_W_UNSUPPORTED_CARD
'//
'// MessageText:
'//
'//  The reader cannot communicate with the smart card, due to ATR configuration conflicts
'//
Public Const SCARD_W_UNSUPPORTED_CARD         As Long = &H80100065

'//
'// MessageId: SCARD_W_UNRESPONSIVE_CARD
'//
'// MessageText:
'//
'//  The smart card is not responding to a reset
'//
Public Const SCARD_W_UNRESPONSIVE_CARD        As Long = &H80100066

'//
'// MessageId: SCARD_W_UNPOWERED_CARD
'//
'// MessageText:
'//
'//  Power has been removed from the smart card, so that further communication is not possible
'//
Public Const SCARD_W_UNPOWERED_CARD           As Long = &H80100067

'//
'// MessageId: SCARD_W_RESET_CARD
'//
'// MessageText:
'//
'//  The smart card has been reset, so any shared state information is invalid
'//
Public Const SCARD_W_RESET_CARD               As Long = &H80100068

'//
'// MessageId: SCARD_W_REMOVED_CARD
'//
'// MessageText:
'//
'//  The smart card has been removed, so that further communication is not possible
'//
Public Const SCARD_W_REMOVED_CARD             As Long = &H80100069

'//
'// MessageId: SCARD_W_SECURITY_VIOLATION
'//
'// MessageText:
'//
'//  Access was denied because of a security violation
'//
Public Const SCARD_W_SECURITY_VIOLATION       As Long = &H8010006A

'//
'// MessageId: SCARD_W_WRONG_CHV
'//
'// MessageText:
'//
'//  The card cannot be accessed because the wrong PIN was presented
'//
Public Const SCARD_W_WRONG_CHV                As Long = &H8010006B

'//
'// MessageId: SCARD_W_CHV_BLOCKED
'//
'// MessageText:
'//
'//  The card cannot be accessed because the maximum number of PIN entry attempts has been reached
'//
Public Const SCARD_W_CHV_BLOCKED              As Long = &H8010006C

'//
'// MessageId: SCARD_W_EOF
'//
'// MessageText:
'//
'//  The end of the smart card file has been reached
'//
Public Const SCARD_W_EOF                      As Long = &H8010006D

'//
'// MessageId: SCARD_W_CANCELLED_BY_USER
'//
'// MessageText:
'//
'//  The action was cancelled by the user
'//
Public Const SCARD_W_CANCELLED_BY_USER        As Long = &H8010006E

