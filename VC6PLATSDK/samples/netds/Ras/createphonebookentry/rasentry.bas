Attribute VB_Name = "modRasEntry"
Option Explicit

'**********************************
'*     Constant Declarations      *
'**********************************
'constants needed for UDTs
Public Const UNLEN = 256
Public Const DNLEN = 15
Public Const PWLEN = 256
Public Const MAX_PATH = 259

' Constants needed for RASENTRY
Public Const RAS_MaxAreaCode = 10
Public Const RAS_MaxDeviceType = 16
Public Const RAS_MaxPhoneNumber = 128
Public Const RAS_MaxIpAddress = 15
Public Const RAS_MaxIpxAddress = 21

Public Const RAS_MaxPadType = 32
Public Const RAS_MaxX25Address = 200
Public Const RAS_MaxFacilities = 200
Public Const RAS_MaxUserData = 200

Public Const RAS_MaxEntryName = 256
Public Const RAS_MaxDeviceName = 128
Public Const RAS_MaxCallbackNumber = 128

' Structure for various IP Addresses, cA.cB.cC.cD
Public Type RASIPADDR
    cA As Byte
    cb As Byte
    cC As Byte
    cD As Byte
End Type

' RASENTRY 'dwfOptions' bit flags.

Public Const RASEO_UseCountryAndAreaCodes = &H1
Public Const RASEO_SpecificIpAddr = &H2
Public Const RASEO_SpecificNameServers = &H4
Public Const RASEO_IpHeaderCompression = &H8
Public Const RASEO_RemoteDefaultGateway = &H10
Public Const RASEO_DisableLcpExtensions = &H20
Public Const RASEO_TerminalBeforeDial = &H40
Public Const RASEO_TerminalAfterDial = &H80
Public Const RASEO_ModemLights = &H100
Public Const RASEO_SwCompression = &H200
Public Const RASEO_RequireEncryptedPw = &H400
Public Const RASEO_RequireMsEncryptedPw = &H800
Public Const RASEO_RequireDataEncryption = &H1000
Public Const RASEO_NetworkLogon = &H2000
Public Const RASEO_UseLogonCredentials = &H4000
Public Const RASEO_PromoteAlternates = &H8000
Public Const RASEO_SecureLocalFiles = &H10000

' RASENTRY 'dwfNetProtocols' bit flags.

Public Const RASNP_NetBEUI = &H1
Public Const RASNP_Ipx = &H2
Public Const RASNP_Ip = &H4

' RASENTRY 'dwFramingProtocols' bit flags.

Public Const RASFP_Ppp = &H1
Public Const RASFP_Slip = &H2
Public Const RASFP_Ras = &H4

Public Type RasEntry
    dwSize As Long
    dwfOptions As Long
'
'   Location/phone number.
'
    dwCountryID As Long
    dwCountryCode As Long
    szAreaCode(RAS_MaxAreaCode) As Byte
    szLocalPhoneNumber(RAS_MaxPhoneNumber) As Byte
    dwAlternateOffset As Long
'
'   PPP/Ip
'
    ipaddr As RASIPADDR
    ipaddrDns As RASIPADDR
    ipaddrDnsAlt As RASIPADDR
    ipaddrWins As RASIPADDR
    ipaddrWinsAlt As RASIPADDR
 '
 '  Framing
 '
    dwFrameSize As Long
    dwfNetProtocols As Long
    dwFramingProtocol As Long
'
'   Scripting
'
    szScript(MAX_PATH)  As Byte
'
'   AutoDial
'
    szAutodialDll(MAX_PATH)  As Byte
    szAutodialFunc(MAX_PATH)  As Byte
'
'   Device
'
    szDeviceType(RAS_MaxDeviceType)    As Byte
    szDeviceName(RAS_MaxDeviceName)   As Byte
'
'   X.25
'
    szX25PadType(RAS_MaxPadType)    As Byte
    szX25Address(RAS_MaxX25Address)   As Byte
    szX25Facilities(RAS_MaxFacilities) As Byte
    szX25UserData(RAS_MaxUserData) As Byte
    dwChannels As Long
'
'   Reserved
'
    dwReserved1 As Long
    dwReserved2 As Long
'
'   The remaining part of the structure is commented
'   so that this code will work on Windows 95  too.
'   Uncommenting this code on Windows 95 will cause
'   RasSetEntryProperties or RasGetEntryProperties to
'   return Error 87, ERROR_INVALID_PARAMETER
'
'   Multilink
'
   ' dwSubEntries As Long
   ' dwDialMode As Long
   ' dwDialExtraPercent As Long
   ' dwDialExtraSampleSeconds As Long
   ' dwHangUpExtraPercent As Long
   ' dwHangUpExtraSampleSeconds As Long
'
'   Idle timeout
'
    'dwIdleDisconnectSeconds As Long
End Type

' Declaration for the RasSetEntryProperties API
Public Declare Function RasSetEntryProperties Lib "rasapi32.dll" Alias "RasSetEntryPropertiesA" ( _
    ByVal lpszPhonebook As String, _
    ByVal lpszRasEntryName As String, _
    lpRasEntry As Any, _
    ByVal dwEntryInfoSize As Long, _
    lpcbDeviceInfo As Any, _
    ByVal dwDeviceInfoSize As Long) As Long
    
' Declaration for the RasDeleteEntry API
Public Declare Function RasDeleteEntry Lib "rasapi32.dll" Alias "RasDeleteEntryA" ( _
    ByVal lpszPhonebook As String, _
    ByVal lpszEntry As String) As Long

' Declaration for the RasValidateEntryName API
Public Declare Function RasValidateEntryName Lib "rasapi32.dll" Alias "RasValidateEntryNameA" ( _
    ByVal lpszPhonebook As String, _
    ByVal lpszEntry As String) As Long

