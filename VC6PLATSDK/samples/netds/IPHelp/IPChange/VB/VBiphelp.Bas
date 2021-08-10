Attribute VB_Name = "VBIPHelp"
'Author:
'    Wei Hua                 August 20, 1999
'
'    Revision History:
'    Who         When         What
'    --------    --------     ---------------------------------
'    Wei Hua     08-20-99     created

Option Explicit

'VB Defines from:/*++
'
'Module Name:'
'
'    iptypes.h

Global Const MAX_ADAPTER_DESCRIPTION_LENGTH = 128 '// arb.
Global Const MAX_ADAPTER_NAME_LENGTH = 256        '// arb.
Global Const MAX_ADAPTER_ADDRESS_LENGTH = 8       '// arb.
Global Const DEFAULT_MINIMUM_ENTITIES = 32        '// arb.
Global Const MAX_HOSTNAME_LEN = 128               '// arb.
Global Const MAX_DOMAIN_NAME_LEN = 128            '// arb.
Global Const MAX_SCOPE_ID_LEN = 256               '// arb.

'//
'// types
'//

'// Node Type

Global Const BROADCAST_NODETYPE = 1
Global Const PEER_TO_PEER_NODETYPE = 2
Global Const MIXED_NODETYPE = 4
Global Const HYBRID_NODETYPE = 8

'// Adapter Type

Global Const IF_OTHER_ADAPTERTYPE = 0
Global Const IF_ETHERNET_ADAPTERTYPE = 1
Global Const IF_TOKEN_RING_ADAPTERTYPE = 2
Global Const IF_FDDI_ADAPTERTYPE = 3
Global Const IF_PPP_ADAPTERTYPE = 4
Global Const IF_LOOPBACK_ADAPTERTYPE = 5
Global Const IF_SLIP_ADAPTERTYPE = 6

'//
'// IP_ADDRESS_STRING - store an IP address as a dotted decimal string
'//

Type IP_ADDR_STRING
    Next As Long
    IpAddress As String * 16
    IpMask As String * 16
    Context As Long
End Type

'//
'// ADAPTER_INFO - per-adapter information. All IP addresses are stored as
'// strings
'//
Global Const MY_MAX_ADAPTER_NAME_LENGTH = MAX_ADAPTER_NAME_LENGTH + 4
Global Const MY_MAX_ADAPTER_DESCRIPTION_LENGTH = MAX_ADAPTER_DESCRIPTION_LENGTH + 4
Type IP_ADAPTER_INFO
    Next As Long
    ComboIndex As Long
    AdapterName As String * MY_MAX_ADAPTER_NAME_LENGTH
    Description As String * MY_MAX_ADAPTER_DESCRIPTION_LENGTH
    AddressLength As Long
    Address(MAX_ADAPTER_ADDRESS_LENGTH - 1) As Byte
    Index As Long
    Type As Long
    DhcpEnabled As Long
    CurrentIpAddress As Long
    IpAddressList As IP_ADDR_STRING
    GatewayList As IP_ADDR_STRING
    DhcpServer As IP_ADDR_STRING
    HaveWins As Long
    PrimaryWinsServer As IP_ADDR_STRING
    SecondaryWinsServer As IP_ADDR_STRING
    LeaseObtained As Long
    LeaseExpires As Long
End Type


'//
'// IP_PER_ADAPTER_INFO - per-adapter IP information such as DNS server list.
'//

Type IP_PER_ADAPTER_INFO
    AutoconfigEnabled As Long
    AutoconfigActive As Long
    CurrentDnsServer As Long    'PIP_ADDR_STRING
    DnsServerList As IP_ADDR_STRING
End Type

'//
'// FIXED_INFO - the set of IP-related information which does not depend on DHCP
'//

Global Const MY_MAX_HOSTNAME_LEN = MAX_HOSTNAME_LEN + 4
Global Const MY_MAX_DOMAIN_NAME_LEN = MAX_DOMAIN_NAME_LEN + 4
Global Const MY_MAX_SCOPE_ID_LEN = MAX_SCOPE_ID_LEN + 4
Type FIXED_INFO
    HostName As String * MY_MAX_HOSTNAME_LEN
    DomainName As String * MY_MAX_DOMAIN_NAME_LEN
    CurrentDnsServer As Long
    DnsServerList As IP_ADDR_STRING
    NodeType As Long
    ScopeId  As String * MY_MAX_SCOPE_ID_LEN
    EnableRouting As Long
    EnableProxy As Long
    EnableDns As Long
End Type



'VB Defines from:
'
'    ipifcons.h
'
'Abstract:
'    Constants needed for the Interface Object
'


'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// Media types                                                              //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////

Global Const MIN_IF_TYPE = 1

Global Const IF_TYPE_OTHER = 1                    '// None of the below
Global Const IF_TYPE_REGULAR_1822 = 2
Global Const IF_TYPE_HDH_1822 = 3
Global Const IF_TYPE_DDN_X25 = 4
Global Const IF_TYPE_RFC877_X25 = 5
Global Const IF_TYPE_ETHERNET_CSMACD = 6
Global Const IF_TYPE_IS088023_CSMACD = 7
Global Const IF_TYPE_ISO88024_TOKENBUS = 8
Global Const IF_TYPE_ISO88025_TOKENRING = 9
Global Const IF_TYPE_ISO88026_MAN = 10
Global Const IF_TYPE_STARLAN = 11
Global Const IF_TYPE_PROTEON_10MBIT = 12
Global Const IF_TYPE_PROTEON_80MBIT = 13
Global Const IF_TYPE_HYPERCHANNEL = 14
Global Const IF_TYPE_FDDI = 15
Global Const IF_TYPE_LAP_B = 16
Global Const IF_TYPE_SDLC = 17
Global Const IF_TYPE_DS1 = 18                     '// DS1-MIB
Global Const IF_TYPE_E1 = 19                      '// Obsolete; see DS1-MIB
Global Const IF_TYPE_BASIC_ISDN = 20
Global Const IF_TYPE_PRIMARY_ISDN = 21
Global Const IF_TYPE_PROP_POINT2POINT_SERIAL = 22 '// proprietary serial
Global Const IF_TYPE_PPP = 23
Global Const IF_TYPE_SOFTWARE_LOOPBACK = 24
Global Const IF_TYPE_EON = 25                     '// CLNP over IP
Global Const IF_TYPE_ETHERNET_3MBIT = 26
Global Const IF_TYPE_NSIP = 27                    '// XNS over IP
Global Const IF_TYPE_SLIP = 28                    '// Generic Slip
Global Const IF_TYPE_ULTRA = 29                   '// ULTRA Technologies
Global Const IF_TYPE_DS3 = 30                     '// DS3-MIB
Global Const IF_TYPE_SIP = 31                     '// SMDS, coffee
Global Const IF_TYPE_FRAMERELAY = 32              '// DTE only
Global Const IF_TYPE_RS232 = 33
Global Const IF_TYPE_PARA = 34                    '// Parallel port
Global Const IF_TYPE_ARCNET = 35
Global Const IF_TYPE_ARCNET_PLUS = 36
Global Const IF_TYPE_ATM = 37                     '// ATM cells
Global Const IF_TYPE_MIO_X25 = 38
Global Const IF_TYPE_SONET = 39                   '// SONET or SDH
Global Const IF_TYPE_X25_PLE = 40
Global Const IF_TYPE_ISO88022_LLC = 41
Global Const IF_TYPE_LOCALTALK = 42
Global Const IF_TYPE_SMDS_DXI = 43
Global Const IF_TYPE_FRAMERELAY_SERVICE = 44      '// FRNETSERV-MIB
Global Const IF_TYPE_V35 = 45
Global Const IF_TYPE_HSSI = 46
Global Const IF_TYPE_HIPPI = 47
Global Const IF_TYPE_MODEM = 48                   '// Generic Modem
Global Const IF_TYPE_AAL5 = 49                    '// AAL5 over ATM
Global Const IF_TYPE_SONET_PATH = 50
Global Const IF_TYPE_SONET_VT = 51
Global Const IF_TYPE_SMDS_ICIP = 52               '// SMDS InterCarrier Interface
Global Const IF_TYPE_PROP_VIRTUAL = 53            '// Proprietary virtual/internal
Global Const IF_TYPE_PROP_MULTIPLEXOR = 54        '// Proprietary multiplexing
Global Const IF_TYPE_IEEE80212 = 55               '// 100BaseVG
Global Const IF_TYPE_FIBRECHANNEL = 56
Global Const IF_TYPE_HIPPIINTERFACE = 57
Global Const IF_TYPE_FRAMERELAY_INTERCONNECT = 58 '// Obsolete, use 32 or 44
Global Const IF_TYPE_AFLANE_8023 = 59             '// ATM Emulated LAN for 802.3
Global Const IF_TYPE_AFLANE_8025 = 60             '// ATM Emulated LAN for 802.5
Global Const IF_TYPE_CCTEMUL = 61                 '// ATM Emulated circuit
Global Const IF_TYPE_FASTETHER = 62               '// Fast Ethernet (100BaseT)
Global Const IF_TYPE_ISDN = 63                    '// ISDN and X.25
Global Const IF_TYPE_V11 = 64                     '// CCITT V.11/X.21
Global Const IF_TYPE_V36 = 65                     '// CCITT V.36
Global Const IF_TYPE_G703_64K = 66                '// CCITT G703 at 64Kbps
Global Const IF_TYPE_G703_2MB = 67                '// Obsolete; see DS1-MIB
Global Const IF_TYPE_QLLC = 68                    '// SNA QLLC
Global Const IF_TYPE_FASTETHER_FX = 69            '// Fast Ethernet (100BaseFX)
Global Const IF_TYPE_CHANNEL = 70
Global Const IF_TYPE_IEEE80211 = 71               '// Radio spread spectrum
Global Const IF_TYPE_IBM370PARCHAN = 72           '// IBM System 360/370 OEMI Channel
Global Const IF_TYPE_ESCON = 73                   '// IBM Enterprise Systems Connection
Global Const IF_TYPE_DLSW = 74                    '// Data Link Switching
Global Const IF_TYPE_ISDN_S = 75                  '// ISDN S/T interface
Global Const IF_TYPE_ISDN_U = 76                  '// ISDN U interface
Global Const IF_TYPE_LAP_D = 77                   '// Link Access Protocol D
Global Const IF_TYPE_IPSWITCH = 78                '// IP Switching Objects
Global Const IF_TYPE_RSRB = 79                    '// Remote Source Route Bridging
Global Const IF_TYPE_ATM_LOGICAL = 80             '// ATM Logical Port
Global Const IF_TYPE_DS0 = 81                     '// Digital Signal Level 0
Global Const IF_TYPE_DS0_BUNDLE = 82              '// Group of ds0s on the same ds1
Global Const IF_TYPE_BSC = 83                     '// Bisynchronous Protocol
Global Const IF_TYPE_ASYNC = 84                   '// Asynchronous Protocol
Global Const IF_TYPE_CNR = 85                     '// Combat Net Radio
Global Const IF_TYPE_ISO88025R_DTR = 86           '// ISO 802.5r DTR
Global Const IF_TYPE_EPLRS = 87                   '// Ext Pos Loc Report Sys
Global Const IF_TYPE_ARAP = 88                    '// Appletalk Remote Access Protocol
Global Const IF_TYPE_PROP_CNLS = 89               '// Proprietary Connectionless Proto
Global Const IF_TYPE_HOSTPAD = 90                 '// CCITT-ITU X.29 PAD Protocol
Global Const IF_TYPE_TERMPAD = 91                 '// CCITT-ITU X.3 PAD Facility
Global Const IF_TYPE_FRAMERELAY_MPI = 92          '// Multiproto Interconnect over FR
Global Const IF_TYPE_X213 = 93                    '// CCITT-ITU X213
Global Const IF_TYPE_ADSL = 94                    '// Asymmetric Digital Subscrbr Loop
Global Const IF_TYPE_RADSL = 95                   '// Rate-Adapt Digital Subscrbr Loop
Global Const IF_TYPE_SDSL = 96                    '// Symmetric Digital Subscriber Loop
Global Const IF_TYPE_VDSL = 97                    '// Very H-Speed Digital Subscrb Loop
Global Const IF_TYPE_ISO88025_CRFPRINT = 98       '// ISO 802.5 CRFP
Global Const IF_TYPE_MYRINET = 99                 '// Myricom Myrinet
Global Const IF_TYPE_VOICE_EM = 100               '// Voice recEive and transMit
Global Const IF_TYPE_VOICE_FXO = 101              '// Voice Foreign Exchange Office
Global Const IF_TYPE_VOICE_FXS = 102              '// Voice Foreign Exchange Station
Global Const IF_TYPE_VOICE_ENCAP = 103            '// Voice encapsulation
Global Const IF_TYPE_VOICE_OVERIP = 104           '// Voice over IP encapsulation
Global Const IF_TYPE_ATM_DXI = 105                '// ATM DXI
Global Const IF_TYPE_ATM_FUNI = 106               '// ATM FUNI
Global Const IF_TYPE_ATM_IMA = 107                '// ATM IMA
Global Const IF_TYPE_PPPMULTILINKBUNDLE = 108     '// PPP Multilink Bundle
Global Const IF_TYPE_IPOVER_CDLC = 109            '// IBM ipOverCdlc
Global Const IF_TYPE_IPOVER_CLAW = 110            '// IBM Common Link Access to Workstn
Global Const IF_TYPE_STACKTOSTACK = 111           '// IBM stackToStack
Global Const IF_TYPE_VIRTUALIPADDRESS = 112       '// IBM VIPA
Global Const IF_TYPE_MPC = 113                    '// IBM multi-proto channel support
Global Const IF_TYPE_IPOVER_ATM = 114             '// IBM ipOverAtm
Global Const IF_TYPE_ISO88025_FIBER = 115         '// ISO 802.5j Fiber Token Ring
Global Const IF_TYPE_TDLC = 116                   '// IBM twinaxial data link control
Global Const IF_TYPE_GIGABITETHERNET = 117
Global Const IF_TYPE_HDLC = 118
Global Const IF_TYPE_LAP_F = 119
Global Const IF_TYPE_V37 = 120
Global Const IF_TYPE_X25_MLP = 121                '// Multi-Link Protocol
Global Const IF_TYPE_X25_HUNTGROUP = 122          '// X.25 Hunt Group
Global Const IF_TYPE_TRANSPHDLC = 123
Global Const IF_TYPE_INTERLEAVE = 124             '// Interleave channel
Global Const IF_TYPE_FAST = 125                   '// Fast channel
Global Const IF_TYPE_IP = 126                     '// IP (for APPN HPR in IP networks)
Global Const IF_TYPE_DOCSCABLE_MACLAYER = 127     '// CATV Mac Layer
Global Const IF_TYPE_DOCSCABLE_DOWNSTREAM = 128   '// CATV Downstream interface
Global Const IF_TYPE_DOCSCABLE_UPSTREAM = 129     '// CATV Upstream interface
Global Const IF_TYPE_A12MPPSWITCH = 130           '// Avalon Parallel Processor
Global Const IF_TYPE_TUNNEL = 131                 '// Encapsulation interface
Global Const IF_TYPE_COFFEE = 132                 '// Coffee pot
Global Const IF_TYPE_CES = 133                    '// Circuit Emulation Service
Global Const IF_TYPE_ATM_SUBINTERFACE = 134       '// ATM Sub Interface
Global Const IF_TYPE_L2_VLAN = 135                '// Layer 2 Virtual LAN using 802.1Q
Global Const IF_TYPE_L3_IPVLAN = 136              '// Layer 3 Virtual LAN using IP
Global Const IF_TYPE_L3_IPXVLAN = 137             '// Layer 3 Virtual LAN using IPX
Global Const IF_TYPE_DIGITALPOWERLINE = 138       '// IP over Power Lines
Global Const IF_TYPE_MEDIAMAILOVERIP = 139        '// Multimedia Mail over IP
Global Const IF_TYPE_DTM = 140                    '// Dynamic syncronous Transfer Mode
Global Const IF_TYPE_DCN = 141                    '// Data Communications Network
Global Const IF_TYPE_IPFORWARD = 142              '// IP Forwarding Interface
Global Const IF_TYPE_MSDSL = 143                  '// Multi-rate Symmetric DSL
Global Const IF_TYPE_IEEE1394 = 144               '// IEEE1394 High Perf Serial Bus

Global Const MAX_IF_TYPE = 144

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// Access types                                                             //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////

Global Const IF_ACCESS_LOOPBACK = 1
Global Const IF_ACCESS_BROADCAST = 2
Global Const IF_ACCESS_POINTTOPOINT = 3
Global Const IF_ACCESS_POINTTOMULTIPOINT = 4

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// Connection Types                                                         //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////

Global Const IF_CONNECTION_DEDICATED = 1
Global Const IF_CONNECTION_PASSIVE = 2
Global Const IF_CONNECTION_DEMAND = 3


Global Const IF_ADMIN_STATUS_UP = 1
Global Const IF_ADMIN_STATUS_DOWN = 2
Global Const IF_ADMIN_STATUS_TESTING = 3

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// The following are the the operational states for WAN and LAN interfaces. //
'// The order of the states seems weird, but is done for a purpose. All      //
'// states >= CONNECTED can transmit data right away. States >= DISCONNECTED //
'// can tx data but some set up might be needed. States < DISCONNECTED can   //
'// not transmit data.                                                       //
'// A card is marked UNREACHABLE if DIM calls InterfaceUnreachable for       //
'// reasons other than failure to connect.                                   //
'//                                                                          //
'// NON_OPERATIONAL -- Valid for LAN Interfaces. Means the card is not       //
'//                      working or not plugged in or has no address.        //
'// UNREACHABLE     -- Valid for WAN Interfaces. Means the remote site is    //
'//                      not reachable at this time.                         //
'// DISCONNECTED    -- Valid for WAN Interfaces. Means the remote site is    //
'//                      not connected at this time.                         //
'// CONNECTING      -- Valid for WAN Interfaces. Means a connection attempt  //
'//                      has been initiated to the remote site.              //
'// CONNECTED       -- Valid for WAN Interfaces. Means the remote site is    //
'//                      connected.                                          //
'// OPERATIONAL     -- Valid for LAN Interfaces. Means the card is plugged   //
'//                      in and working.                                     //
'//                                                                          //
'// It is the users duty to convert these values to MIB-II values if they    //
'// are to be used by a subagent                                             //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////

Global Const IF_OPER_STATUS_NON_OPERATIONAL = 0
Global Const IF_OPER_STATUS_UNREACHABLE = 1
Global Const IF_OPER_STATUS_DISCONNECTED = 2
Global Const IF_OPER_STATUS_CONNECTING = 3
Global Const IF_OPER_STATUS_CONNECTED = 4
Global Const IF_OPER_STATUS_OPERATIONAL = 5

Global Const MIB_IF_TYPE_OTHER = 1
Global Const MIB_IF_TYPE_ETHERNET = 6
Global Const MIB_IF_TYPE_TOKENRING = 9
Global Const MIB_IF_TYPE_FDDI = 15
Global Const MIB_IF_TYPE_PPP = 23
Global Const MIB_IF_TYPE_LOOPBACK = 24
Global Const MIB_IF_TYPE_SLIP = 28

Global Const MIB_IF_ADMIN_STATUS_UP = 1
Global Const MIB_IF_ADMIN_STATUS_DOWN = 2
Global Const MIB_IF_ADMIN_STATUS_TESTING = 3

Global Const MIB_IF_OPER_STATUS_NON_OPERATIONAL = 0
Global Const MIB_IF_OPER_STATUS_UNREACHABLE = 1
Global Const MIB_IF_OPER_STATUS_DISCONNECTED = 2
Global Const MIB_IF_OPER_STATUS_CONNECTING = 3
Global Const MIB_IF_OPER_STATUS_CONNECTED = 4
Global Const MIB_IF_OPER_STATUS_OPERATIONAL = 5

'VB Defines from:
'
'    iprtrmib.h
'
'Abstract:
'    This file contains:
'        o Definitions of the MIB_XX structures passed to and from the IP Router Manager
'            to query and set MIB variables handled by the IP Router Manager
'        o The Global Consts for the MIB variables IDs  handled by the IP Router Manager
'            and made accessible by the MprAdminMIBXXX APIs
'        o The Routing PID of the IP Router Manager (as mentioned in ipinfoid.h)

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// This is the Id for IP Router Manager.  The Router Manager handles        //
'// MIB-II, Forwarding MIB and some enterprise specific information.         //
'// Calls made with any other ID are passed on to the corresponding protocol //
'// For example, an MprAdminMIBXXX call with a protocol ID of PID_IP and    //
'// a routing Id of 0xD will be sent to the IP Router Manager and then       //
'// forwarded to OSPF                                                        //
'// This lives in the same number space as the protocol Ids of RIP, OSPF     //
'// etc, so any change made to it should be done keeping this in mind        //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////


Global Const IPRTRMGR_PID = 10000

Global Const ANY_SIZE = 1

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// The following Global Consts are the Ids of the MIB variables made accessible  //
'// to the user via MprAdminMIBXXX Apis.  It will be noticed that these are  //
'// not the same as RFC 1213, since the MprAdminMIBXXX APIs work on rows and //
'// groups instead of scalar variables                                       //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////


Global Const IF_NUMBER = 0
Global Const IF_TABLE = (IF_NUMBER + 1)
Global Const IF_ROW = (IF_TABLE + 1)
Global Const IP_STATS = (IF_ROW + 1)
Global Const IP_ADDRTABLE = (IP_STATS + 1)
Global Const IP_ADDRROW = (IP_ADDRTABLE + 1)
Global Const IP_FORWARDNUMBER = (IP_ADDRROW + 1)
Global Const IP_FORWARDTABLE = (IP_FORWARDNUMBER + 1)
Global Const IP_FORWARDROW = (IP_FORWARDTABLE + 1)
Global Const IP_NETTABLE = (IP_FORWARDROW + 1)
Global Const IP_NETROW = (IP_NETTABLE + 1)
Global Const ICMP_STATS = (IP_NETROW + 1)
Global Const TCP_STATS = (ICMP_STATS + 1)
Global Const TCP_TABLE = (TCP_STATS + 1)
Global Const TCP_ROW = (TCP_TABLE + 1)
Global Const UDP_STATS = (TCP_ROW + 1)
Global Const UDP_TABLE = (UDP_STATS + 1)
Global Const UDP_ROW = (UDP_TABLE + 1)
Global Const MCAST_MFE = (UDP_ROW + 1)
Global Const MCAST_MFE_STATS = (MCAST_MFE + 1)
Global Const BEST_IF = (MCAST_MFE_STATS + 1)
Global Const BEST_ROUTE = (BEST_IF + 1)
Global Const PROXY_ARP = (BEST_ROUTE + 1)
Global Const MCAST_IF_ENTRY = (PROXY_ARP + 1)
Global Const MCAST_GLOBAL = (MCAST_IF_ENTRY + 1)
Global Const IF_STATUS = (MCAST_GLOBAL + 1)
Global Const MCAST_BOUNDARY = (IF_STATUS + 1)
Global Const MCAST_SCOPE = (MCAST_BOUNDARY + 1)
Global Const DEST_MATCHING = (MCAST_SCOPE + 1)
Global Const DEST_LONGER = (DEST_MATCHING + 1)
Global Const DEST_SHORTER = (DEST_LONGER + 1)
Global Const ROUTE_MATCHING = (DEST_SHORTER + 1)
Global Const ROUTE_LONGER = (ROUTE_MATCHING + 1)
Global Const ROUTE_SHORTER = (ROUTE_LONGER + 1)

Global Const NUMBER_OF_EXPORTED_VARIABLES = (ROUTE_SHORTER + 1)

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// MIB_OPAQUE_QUERY is the structure filled in by the user to identify a    //
'// MIB variable                                                             //
'//                                                                          //
'//  dwVarId     ID of MIB Variable (One of the Ids Global Constd above)          //
'//  dwVarIndex  Variable sized array containing the indices needed to       //
'//              identify a variable. NOTE: Unlike SNMP we dont require that //
'//              a scalar variable be indexed by 0                           //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////

Type MIB_OPAQUE_QUERY
    dwVarId As Long
    rgdwVarIndex As Long ' DWORD  rgdwVarIndex[ANY_SIZE];
End Type

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// The following are the structures which are filled in and returned to the //
'// user when a query is made, OR  are filled in BY THE USER when a set is   //
'// done                                                                     //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////

Type MIB_IFNUMBER
    dwValue As Long
End Type

Global Const MAXLEN_IFDESCR = 256
Global Const MAXLEN_PHYSADDR = 8
Global Const MAX_INTERFACE_NAME_LEN = 256

Type MIB_IFROW
    wszName(MAX_INTERFACE_NAME_LEN - 1) As Integer 'WCHAR   wszName[MAX_INTERFACE_NAME_LEN];
    dwIndex  As Long
    dwType  As Long
    dwMtu  As Long
    dwSpeed  As Long
    dwPhysAddrLen  As Long
    bPhysAddr(MAXLEN_PHYSADDR - 1) As Byte
    dwAdminStatus As Long
    dwOperStatus  As Long
    dwLastChange  As Long
    dwInOctets  As Long
    dwInUcastPkts  As Long
    dwInNUcastPkts  As Long
    dwInDiscards  As Long
    dwInErrors  As Long
    dwInUnknownProtos  As Long
    dwOutOctets As Long
    dwOutUcastPkts As Long
    dwOutNUcastPkts As Long
    dwOutDiscards  As Long
    dwOutErrors  As Long
    dwOutQLen As Long
    dwDescrLen As Long
    bDescr(MAXLEN_IFDESCR - 1) As Byte
End Type

Type MIB_IFTABLE
    dwNumEntries As Long
    table As MIB_IFROW ' MIB_IFROW table[ANY_SIZE];
End Type

'Global Const SIZEOF_IFTABLE(X) (FIELD_OFFSET(MIB_IFTABLE,table[0]) + ((X) * sizeof(MIB_IFROW)) + ALIGN_SIZE)

Type MIBICMPSTATS
    dwMsgs As Long
    dwErrors As Long
    dwDestUnreachs As Long
    dwTimeExcds  As Long
    dwParmProbs As Long
    dwSrcQuenchs As Long
    dwRedirects  As Long
    dwEchos As Long
    dwEchoReps As Long
    dwTimestamps As Long
    dwTimestampReps As Long
    dwAddrMasks  As Long
    dwAddrMaskReps As Long
End Type

Type MIBICMPINFO
    icmpInStats As MIBICMPSTATS
    icmpOutStats As MIBICMPSTATS
End Type

Type MIB_ICMP
    Stats As MIBICMPINFO
End Type

Type MIB_UDPSTATS
    dwInDatagrams As Long
    dwNoPorts As Long
    dwInErrors As Long
    dwOutDatagrams As Long
    dwNumAddrs As Long
End Type

Type MIB_UDPROW
    dwLocalAddr As Long
    dwLocalPort As Long
End Type

Type MIB_UDPTABLE
    dwNumEntries As Long
    table As MIB_UDPROW ' MIB_UDPROW  table[ANY_SIZE];
End Type

'Global Const SIZEOF_UDPTABLE(X) (FIELD_OFFSET(MIB_UDPTABLE, table[0]) + ((X) * sizeof(MIB_UDPROW)) + ALIGN_SIZE)

Type MIB_TCPSTATS
    dwRtoAlgorithm As Long
    dwRtoMin As Long
    dwRtoMax As Long
    dwMaxConn As Long
    dwActiveOpens As Long
    dwPassiveOpens As Long
    dwAttemptFails As Long
    dwEstabResets As Long
    dwCurrEstab As Long
    dwInSegs As Long
    dwOutSegs As Long
    dwRetransSegs As Long
    dwInErrs As Long
    dwOutRsts As Long
    dwNumConns As Long
End Type

Global Const MIB_TCP_RTO_OTHER = 1
Global Const MIB_TCP_RTO_CONSTANT = 2
Global Const MIB_TCP_RTO_RSRE = 3
Global Const MIB_TCP_RTO_VANJ = 4

Global Const MIB_TCP_MAXCONN_DYNAMIC = -1

Type MIB_TCPROW
    dwState As Long
    dwLocalAddr As Long
    dwLocalPort As Long
    dwRemoteAddr As Long
    dwRemotePort As Long
End Type

Global Const MIB_TCP_STATE_CLOSED = 1
Global Const MIB_TCP_STATE_LISTEN = 2
Global Const MIB_TCP_STATE_SYN_SENT = 3
Global Const MIB_TCP_STATE_SYN_RCVD = 4
Global Const MIB_TCP_STATE_ESTAB = 5
Global Const MIB_TCP_STATE_FIN_WAIT1 = 6
Global Const MIB_TCP_STATE_FIN_WAIT2 = 7
Global Const MIB_TCP_STATE_CLOSE_WAIT = 8
Global Const MIB_TCP_STATE_CLOSING = 9
Global Const MIB_TCP_STATE_LAST_ACK = 10
Global Const MIB_TCP_STATE_TIME_WAIT = 11
Global Const MIB_TCP_STATE_DELETE_TCB = 12

Type MIB_TCPTABLE
    dwNumEntries As Long
    table As MIB_TCPROW 'MIB_TCPROW table[ANY_SIZE];
End Type

'Global Const SIZEOF_TCPTABLE(X) (FIELD_OFFSET(MIB_TCPTABLE,table[0]) + ((X) * sizeof(MIB_TCPROW)) + ALIGN_SIZE)

Global Const MIB_USE_CURRENT_TTL = -1
Global Const MIB_USE_CURRENT_FORWARDING = -1

Type MIB_IPSTATS
    dwForwarding As Long
    dwDefaultTTL As Long
    dwInReceives As Long
    dwInHdrErrors As Long
    dwInAddrErrors As Long
    dwForwDatagrams As Long
    dwInUnknownProtos As Long
    dwInDiscards As Long
    dwInDelivers As Long
    dwOutRequests As Long
    dwRoutingDiscards As Long
    dwOutDiscards As Long
    dwOutNoRoutes As Long
    dwReasmTimeout As Long
    dwReasmReqds As Long
    dwReasmOks As Long
    dwReasmFails As Long
    dwFragOks As Long
    dwFragFails As Long
    dwFragCreates As Long
    dwNumIf As Long
    dwNumAddr As Long
    dwNumRoutes As Long
End Type

Global Const MIB_IP_FORWARDING = 1
Global Const MIB_IP_NOT_FORWARDING = 2

Type MIB_IPADDRROW
    dwAddr As Long
    dwIndex As Long
    dwMask As Long
    dwBCastAddr As Long
    dwReasmSize As Long
    unused1 As Integer
    unused2 As Integer
End Type

Type MIB_IPADDRTABLE
    dwNumEntries As Long
    table As MIB_IPADDRROW ' MIB_IPADDRROW table[ANY_SIZE];
End Type

'Global Const SIZEOF_IPADDRTABLE(X) (FIELD_OFFSET(MIB_IPADDRTABLE,table[0]) + ((X) * sizeof(MIB_IPADDRROW)) + ALIGN_SIZE)

Type MIB_IPFORWARDNUMBER
    dwValue As Long
End Type

Type MIB_IPFORWARDROW
    dwForwardDest As Long
    dwForwardMask As Long
    dwForwardPolicy As Long
    dwForwardNextHop As Long
    dwForwardIfIndex As Long
    dwForwardType As Long
    dwForwardProto As Long
    dwForwardAge As Long
    dwForwardNextHopAS As Long
    dwForwardMetric1 As Long
    dwForwardMetric2 As Long
    dwForwardMetric3 As Long
    dwForwardMetric4 As Long
    dwForwardMetric5 As Long
End Type

Global Const MIB_IPROUTE_TYPE_OTHER = 1
Global Const MIB_IPROUTE_TYPE_INVALID = 2
Global Const MIB_IPROUTE_TYPE_DIRECT = 3
Global Const MIB_IPROUTE_TYPE_INDIRECT = 4

Global Const MIB_IPROUTE_METRIC_UNUSED = -1

'//
'// THESE MUST MATCH the ids in routprot.h
'//

Global Const MIB_IPPROTO_OTHER = 1
Global Const MIB_IPPROTO_LOCAL = 2
Global Const MIB_IPPROTO_NETMGMT = 3
Global Const MIB_IPPROTO_ICMP = 4
Global Const MIB_IPPROTO_EGP = 5
Global Const MIB_IPPROTO_GGP = 6
Global Const MIB_IPPROTO_HELLO = 7
Global Const MIB_IPPROTO_RIP = 8
Global Const MIB_IPPROTO_IS_IS = 9
Global Const MIB_IPPROTO_ES_IS = 10
Global Const MIB_IPPROTO_CISCO = 11
Global Const MIB_IPPROTO_BBN = 12
Global Const MIB_IPPROTO_OSPF = 13
Global Const MIB_IPPROTO_BGP = 14

Global Const MIB_IPPROTO_NT_AUTOSTATIC = 10002
Global Const MIB_IPPROTO_NT_STATIC = 10006
Global Const MIB_IPPROTO_NT_STATIC_NON_DOD = 10007

Type MIB_IPFORWARDTABLE
    dwNumEntries As Long
    table As MIB_IPFORWARDROW 'MIB_IPFORWARDROW    table[ANY_SIZE];
End Type

'Global Const SIZEOF_IPFORWARDTABLE(X) (FIELD_OFFSET(MIB_IPFORWARDTABLE,table[0]) + ((X) * sizeof(MIB_IPFORWARDROW)) + ALIGN_SIZE)

Type MIB_IPNETROW
    dwIndex As Long
    dwPhysAddrLen As Long
    bPhysAddr(MAXLEN_PHYSADDR - 1) As Byte
    dwAddr As Long
    dwType As Long
End Type

Global Const MIB_IPNET_TYPE_OTHER = 1
Global Const MIB_IPNET_TYPE_INVALID = 2
Global Const MIB_IPNET_TYPE_DYNAMIC = 3
Global Const MIB_IPNET_TYPE_STATIC = 4

Type MIB_IPNETTABLE
    dwNumEntries As Long
    table As MIB_IPNETROW 'MIB_IPNETROW      table[ANY_SIZE];
End Type

'Global Const SIZEOF_IPNETTABLE(X) (FIELD_OFFSET(MIB_IPNETTABLE, table[0]) + ((X) * sizeof(MIB_IPNETROW)) + ALIGN_SIZE)

Type MIB_IPMCAST_OIF
    dwOutIfIndex As Long
    dwNextHopAddr As Long
    pvReserved As Long
    dwReserved As Long
End Type

Type MIB_IPMCAST_MFE
    dwGroup As Long
    dwSource As Long
    dwSrcMask As Long
    dwUpStrmNgbr As Long
    dwInIfIndex As Long
    dwInIfProtocol As Long
    dwRouteProtocol As Long
    dwRouteNetwork As Long
    dwRouteMask As Long
    ulUpTime As Long
    ulExpiryTime  As Long
    ulTimeOut As Long
    ulNumOutIf As Long
    fFlags As Long
    dwReserved As Long
    rgmioOutInfo As MIB_IPMCAST_OIF ' MIB_IPMCAST_OIF rgmioOutInfo[ANY_SIZE];
End Type

Type MIB_MFE_TABLE
    dwNumEntries As Long
    table As MIB_IPMCAST_MFE ' MIB_IPMCAST_MFE table[ANY_SIZE];
End Type

'Global Const SIZEOF_BASIC_MIB_MFE          \
'    (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE, rgmioOutInfo[0]))

'Global Const SIZEOF_MIB_MFE(X)             \
'    (SIZEOF_BASIC_MIB_MFE + ((X) * sizeof(MIB_IPMCAST_OIF)))


Type MIB_IPMCAST_OIF_STATS
    dwOutIfIndex As Long
    dwNextHopAddr As Long
    pvDialContext As Long
    ulTtlTooLow As Long
    ulFragNeeded As Long
    ulOutPackets As Long
    ulOutDiscards As Long
End Type

Type MIB_IPMCAST_MFE_STATS
    dwGroup As Long
    dwSource As Long
    dwSrcMask As Long
    dwUpStrmNgbr As Long
    dwInIfIndex As Long
    dwInIfProtocol As Long
    dwRouteProtocol As Long
    dwRouteNetwork As Long
    dwRouteMask As Long
    ulUpTime As Long
    ulExpiryTime As Long
    ulNumOutIf As Long
    ulInPkts As Long
    ulInOctets As Long
    ulPktsDifferentIf As Long
    ulQueueOverflow As Long
    rgmiosOutStats As MIB_IPMCAST_OIF_STATS ' MIB_IPMCAST_OIF_STATS   rgmiosOutStats[ANY_SIZE];
End Type

Type MIB_MFE_STATS_TABLE
    dwNumEntries As Long
    table As MIB_IPMCAST_MFE_STATS ' MIB_IPMCAST_MFE_STATS   table[ANY_SIZE];
End Type

'Global Const SIZEOF_BASIC_MIB_MFE_STATS    \
'    (ULONG)(FIELD_OFFSET(MIB_IPMCAST_MFE_STATS, rgmiosOutStats[0]))

'Global Const SIZEOF_MIB_MFE_STATS(X)       \
'    (SIZEOF_BASIC_MIB_MFE_STATS + ((X) * sizeof(MIB_IPMCAST_OIF_STATS)))

Type MIB_IPMCAST_GLOBAL
    dwEnable As Long
End Type

Type MIB_IPMCAST_IF_ENTRY
    dwIfIndex As Long
    dwTtl As Long
    dwProtocol As Long
    dwRateLimit As Long
    ulInMcastOctets As Long
    ulOutMcastOctets As Long
End Type

Type MIB_IPMCAST_IF_TABLE
    dwNumEntries As Long
    table As MIB_IPMCAST_IF_ENTRY ' MIB_IPMCAST_IF_ENTRY   table[ANY_SIZE];
End Type

'Global Const SIZEOF_MCAST_IF_TABLE(X) (FIELD_OFFSET(MIB_IPMCAST_IF_TABLE,table[0]) + ((X) * sizeof(MIB_IPMCAST_IF_ENTRY)) + ALIGN_SIZE)

Type MIB_IPMCAST_BOUNDARY
    dwIfIndex As Long
    dwGroupAddress As Long
    dwGroupMask As Long
    dwStatus As Long
End Type

Type MIB_IPMCAST_BOUNDARY_TABLE
    dwNumEntries As Long
    table As MIB_IPMCAST_BOUNDARY ' MIB_IPMCAST_BOUNDARY   table[ANY_SIZE];
End Type

'Global Const SIZEOF_BOUNDARY_TABLE(X) (FIELD_OFFSET(MIB_IPMCAST_BOUNDARY_TABLE,table[0]) + ((X) * sizeof(MIB_IPMCAST_BOUNDARY)) + ALIGN_SIZE)

Type MIB_BOUNDARYROW
    dwGroupAddress As Long
    dwGroupMask As Long
End Type

'// Structure matching what goes in the registry in a block of type
'// IP_MCAST_LIMIT_INFO.  This contains the fields of
'// MIB_IPMCAST_IF_ENTRY which are configurable.

Type MIB_MCAST_LIMIT_ROW
    dwTtl As Long
    dwRateLimit As Long
End Type

Global Const MAX_SCOPE_NAME_LEN = 255

'//
'// Scope names are unicode.  SNMP and MZAP use UTF-8 encoding.
'//

'typedef WCHAR   SN_CHAR;
'typedef SN_CHAR SCOPE_NAME_BUFFER[MAX_SCOPE_NAME_LEN+1], *SCOPE_NAME;

Type MIB_IPMCAST_SCOPE
    dwGroupAddress As Long
    dwGroupMask As Long
    snNameBuffer(MAX_SCOPE_NAME_LEN) As Integer ' SCOPE_NAME_BUFFER snNameBuffer;
    dwStatus As Long
End Type

Type MIB_IPDESTROW
    ForwardRow As MIB_IPFORWARDROW

    dwForwardPreference As Long
    dwForwardViewSet As Long
End Type

Type MIB_IPDESTTABLE
    dwNumEntries As Long
    table As MIB_IPDESTROW ' MIB_IPDESTROW     table[ANY_SIZE];
End Type

Type MIB_BEST_IF
    dwDestAddr As Long
    dwIfIndex As Long
End Type

Type MIB_PROXYARP
    dwAddress As Long
    dwMask As Long
    dwIfIndex As Long
End Type

Type MIB_IFSTATUS
    dwIfIndex As Long
    dwAdminStatus As Long
    dwOperationalStatus As Long
    bMHbeatActive As Byte
    bMHbeatAlive As Byte
End Type

'//////////////////////////////////////////////////////////////////////////////
'//                                                                          //
'// All the info passed to (SET/CREATE) and from (GET/GETNEXT/GETFIRST)      //
'// IP Router Manager is encapsulated in the following "discriminated"       //
'// union.  To pass, say MIB_IFROW, use the following code                   //
'//                                                                          //
'//  PMIB_OPAQUE_INFO    pInfo;                                              //
'//  PMIB_IFROW          pIfRow;                                             //
'//  DWORD rgdwBuff[(MAX_MIB_OFFSET + sizeof(MIB_IFROW))/sizeof(DWORD) + 1]; //
'//                                                                          //
'//  pInfo   = (PMIB_OPAQUE_INFO)rgdwBuffer;                                 //
'//  pIfRow  = (MIB_IFROW *)(pInfo->rgbyData);                               //
'//                                                                          //
'//  This can also be accomplished by using the following macro              //
'//                                                                          //
'//  DEFINE_MIB_BUFFER(pInfo,MIB_IFROW, pIfRow);                             //
'//                                                                          //
'//////////////////////////////////////////////////////////////////////////////


'typedef struct _MIB_OPAQUE_INFO
'{
'    DWORD  dwId;
'
'    Union
'    {
'        ULONGLONG   ullAlign;
'        BYTE        rgbyData[1];
'    };
'
'}MIB_OPAQUE_INFO, *PMIB_OPAQUE_INFO;

Type MIB_OPAQUE_INFO
    dwId As Long
    rgbyData(63) As Byte
End Type

Global Const MAX_MIB_OFFSET = 8

'Global Const MIB_INFO_SIZE(S)                \
'   (MAX_MIB_OFFSET + sizeof(S))

'Global Const MIB_INFO_SIZE_IN_DWORDS(S)      \
'    ((MIB_INFO_SIZE(S))/sizeof(DWORD) + 1)

'Global Const DEFINE_MIB_BUFFER(X,Y,Z)                                        \
'    DWORD       __rgdwBuff[MIB_INFO_SIZE_IN_DWORDS(Y)]; \
'    PMIB_OPAQUE_INFO    X = (PMIB_OPAQUE_INFO)__rgdwBuff;               \
'    Y *                 Z = (Y *)(X->rgbyData)


'Global Const CAST_MIB_INFO(X,Y,Z)    Z = (Y)(X->rgbyData)

'VB Defines from:/*++
'
'Module Name:'
'
'    IPEXPORT.h

'//
'// IP type definitions.
'//
'typedef unsigned long   IPAddr;     // An IP address.
'typedef unsigned long   IPMask;     // An IP subnet mask.
'typedef unsigned long   IP_STATUS;  // Status code returned from IP APIs.

'//
'// The ip_option_information structure describes the options to be
'// included in the header of an IP packet. The TTL, TOS, and Flags
'// values are carried in specific fields in the header. The OptionsData
'// bytes are carried in the options area following the standard IP header.
'// With the exception of source route options, this data must be in the
'// format to be transmitted on the wire as specified in RFC 791. A source
'// route option should contain the full route - first hop thru final
'// destination - in the route data. The first hop will be pulled out of the
'// data and the option will be reformatted accordingly. Otherwise, the route
'// option should be formatted as specified in RFC 791.
'//
Type ip_option_information
    Ttl As Byte             '// Time To Live
    Tos As Byte             '// Type Of Service
    Flags As Byte           '// IP header flags
    OptionsSize As Byte     '// Size in bytes of options data
    OptionsData As Long     '// Pointer to options data
End Type

'//
'// The icmp_echo_reply structure describes the data returned in response
'// to an echo request.
'//
Type icmp_echo_reply
    Address As Long         '// Replying address
    Status As Long          '// Reply IP_STATUS
    RoundTripTime As Long   '// RTT in milliseconds
    DataSize As Integer     '// Reply data size in bytes
    Reserved As Integer     '// Reserved for system use
    Data As Long            '// Pointer to the reply data
    Options As ip_option_information      '// Reply options
End Type

'/*NOINC*/

'typedef struct ip_option_information IP_OPTION_INFORMATION,
'                                     FAR *PIP_OPTION_INFORMATION;

'typedef struct icmp_echo_reply ICMP_ECHO_REPLY,
'                               FAR *PICMP_ECHO_REPLY;

'/*INC*/



Type ArpRequestBuffer
   DestAddress As Long
   SrcAddress As Long
End Type

'/*NOINC*/

'typedef struct ArpRequestBuffer ARP_SEND_REPLY,
'                               FAR *PARP_SEND_REPLY;

Type TCP_RESERVE_PORT_RANGE
   UpperRange As Integer
   LowerRange As Integer
End Type

Global Const MAX_ADAPTER_NAME = 128

Type IP_ADAPTER_INDEX_MAP
   Index As Long
   AdapterName(MAX_ADAPTER_NAME - 1) As Integer 'WCHAR  Name[MAX_ADAPTER_NAME];
End Type

Type IP_INTERFACE_INFO
     NumAdapters As Long
     Adapter As IP_ADAPTER_INDEX_MAP 'IP_ADAPTER_INDEX_MAP Adapter[1];
End Type

Type IP_UNIDIRECTIONAL_ADAPTER_ADDRESS
     NumAdapters As Long
     Address As Long 'IPAddr  Address[1];
End Type

Type IP_ADAPTER_ORDER_MAP
    NumAdapters As Long
    AdapterOrder As Long ' ULONG AdapterOrder[1];
End Type

'//
'// IP_STATUS codes returned from IP APIs
'//

Global Const IP_STATUS_BASE = 11000

Global Const IP_SUCCESS = 0
Global Const IP_BUF_TOO_SMALL = (IP_STATUS_BASE + 1)
Global Const IP_DEST_NET_UNREACHABLE = (IP_STATUS_BASE + 2)
Global Const IP_DEST_HOST_UNREACHABLE = (IP_STATUS_BASE + 3)
Global Const IP_DEST_PROT_UNREACHABLE = (IP_STATUS_BASE + 4)
Global Const IP_DEST_PORT_UNREACHABLE = (IP_STATUS_BASE + 5)
Global Const IP_NO_RESOURCES = (IP_STATUS_BASE + 6)
Global Const IP_BAD_OPTION = (IP_STATUS_BASE + 7)
Global Const IP_HW_ERROR = (IP_STATUS_BASE + 8)
Global Const IP_PACKET_TOO_BIG = (IP_STATUS_BASE + 9)
Global Const IP_REQ_TIMED_OUT = (IP_STATUS_BASE + 10)
Global Const IP_BAD_REQ = (IP_STATUS_BASE + 11)
Global Const IP_BAD_ROUTE = (IP_STATUS_BASE + 12)
Global Const IP_TTL_EXPIRED_TRANSIT = (IP_STATUS_BASE + 13)
Global Const IP_TTL_EXPIRED_REASSEM = (IP_STATUS_BASE + 14)
Global Const IP_PARAM_PROBLEM = (IP_STATUS_BASE + 15)
Global Const IP_SOURCE_QUENCH = (IP_STATUS_BASE + 16)
Global Const IP_OPTION_TOO_BIG = (IP_STATUS_BASE + 17)
Global Const IP_BAD_DESTINATION = (IP_STATUS_BASE + 18)


'//
'// The next group are status codes passed up on status indications to
'// transport layer protocols.
'//
Global Const IP_ADDR_DELETED = (IP_STATUS_BASE + 19)
Global Const IP_SPEC_MTU_CHANGE = (IP_STATUS_BASE + 20)
Global Const IP_MTU_CHANGE = (IP_STATUS_BASE + 21)
Global Const IP_UNLOAD = (IP_STATUS_BASE + 22)
Global Const IP_ADDR_ADDED = (IP_STATUS_BASE + 23)
Global Const IP_MEDIA_CONNECT = (IP_STATUS_BASE + 24)
Global Const IP_MEDIA_DISCONNECT = (IP_STATUS_BASE + 25)
Global Const IP_BIND_ADAPTER = (IP_STATUS_BASE + 26)
Global Const IP_UNBIND_ADAPTER = (IP_STATUS_BASE + 27)
Global Const IP_DEVICE_DOES_NOT_EXIST = (IP_STATUS_BASE + 28)
Global Const IP_DUPLICATE_ADDRESS = (IP_STATUS_BASE + 29)
Global Const IP_INTERFACE_METRIC_CHANGE = (IP_STATUS_BASE + 30)
Global Const IP_RECONFIG_SECFLTR = (IP_STATUS_BASE + 31)
Global Const IP_NEGOTIATING_IPSEC = (IP_STATUS_BASE + 32)
Global Const IP_INTERFACE_WOL_CAPABILITY_CHANGE = (IP_STATUS_BASE + 33)
Global Const IP_DUPLICATE_IPADD = (IP_STATUS_BASE + 34)

Global Const IP_GENERAL_FAILURE = (IP_STATUS_BASE + 50)
Global Const MAX_IP_STATUS = IP_GENERAL_FAILURE
Global Const IP_PENDING = (IP_STATUS_BASE + 255)


'//
'// Values used in the IP header Flags field.
'//
Global Const IP_FLAG_DF = &H2             '// Don't fragment this packet.

'//
'// Supported IP Option Types.
'//
'// These types define the options which may be used in the OptionsData field
'// of the ip_option_information structure.  See RFC 791 for a complete
'// description of each.
'//
Global Const IP_OPT_EOL = 0              '// End of list option
Global Const IP_OPT_NOP = 1              '// No operation
Global Const IP_OPT_SECURITY = &H82      '// Security option
Global Const IP_OPT_LSRR = &H83          '// Loose source route
Global Const IP_OPT_SSRR = &H89          '// Strict source route
Global Const IP_OPT_RR = &H7             '// Record route
Global Const IP_OPT_TS = &H44            '// Timestamp
Global Const IP_OPT_SID = &H88           '// Stream ID (obsolete)
Global Const IP_OPT_ROUTER_ALERT = &H94 '// Router Alert Option

Global Const MAX_OPT_SIZE = 40           '// Maximum length of IP options in bytes

'#ifdef CHICAGO

'// Ioctls code exposed by Memphis tcpip stack.
'// For NT these ioctls are define in ntddip.h  (private\inc)

Global Const IOCTL_IP_RTCHANGE_NOTIFY_REQUEST = 101
Global Const IOCTL_IP_ADDCHANGE_NOTIFY_REQUEST = 102
Global Const IOCTL_ARP_SEND_REQUEST = 103
Global Const IOCTL_IP_INTERFACE_INFO = 104
Global Const IOCTL_IP_GET_BEST_INTERFACE = 105
Global Const IOCTL_IP_UNIDIRECTIONAL_ADAPTER_ADDRESS = 106

'#End If


'#endif // IP_EXPORT_INCLUDED


'''''''''''''''''''''''''''
'functions

Public Declare Function GetNetworkParams Lib "IPHlpApi" (FixedInfo As Any, pOutBufLen As Long) As Long
Public Declare Function GetAdaptersInfo Lib "IPHlpApi" (IpAdapterInfo As Any, pOutBufLen As Long) As Long
Public Declare Function GetIpStatistics Lib "IPHlpApi" (pStat As MIB_IPSTATS) As Long
Public Declare Function GetIcmpStatistics Lib "IPHlpApi" (pStat As MIB_ICMP) As Long
Public Declare Function GetTcpStatistics Lib "IPHlpApi" (pStat As MIB_TCPSTATS) As Long
Public Declare Function GetUdpStatistics Lib "IPHlpApi" (pStat As MIB_UDPSTATS) As Long
Public Declare Function GetTcpTable Lib "IPHlpApi" (ByVal pTcpTable As Long, pdwSize As Long, ByVal bOrder As Boolean) As Long
Public Declare Function GetUdpTable Lib "IPHlpApi" (ByVal pUdpTable As Long, pdwSize As Long, ByVal bOrder As Boolean) As Long
Public Declare Function GetInterfaceInfo Lib "IPHlpApi" (ByVal pIfTable As Long, dwOutBufLen As Long) As Long
Public Declare Function IpReleaseAddress Lib "IPHlpApi" (AdapterInfo As IP_ADAPTER_INDEX_MAP) As Long
Public Declare Function IpRenewAddress Lib "IPHlpApi" (AdapterInfo As IP_ADAPTER_INDEX_MAP) As Long
Public Declare Function GetIpForwardTable Lib "IPHlpApi" (ByVal pIpForwardTable As Long, pdwSize As Long, ByVal bOrder As Boolean) As Long
Public Declare Function GetIpAddrTable Lib "IPHlpApi" (ByVal pIpAddrTable As Long, pdwSize As Long, ByVal bOrder As Boolean) As Long
Public Declare Function SetIpForwardEntry Lib "IPHlpApi" (pRoute As MIB_IPFORWARDROW) As Long
Public Declare Function DeleteIpForwardEntry Lib "IPHlpApi" (pRoute As MIB_IPFORWARDROW) As Long
Public Declare Function DeleteIPAddress Lib "IPHlpApi" (ByVal NTEContext As Long) As Long
Public Declare Function AddIPAddress Lib "IPHlpApi" (ByVal Address As Long, ByVal IpMask As Long, ByVal IfIndex As Long, _
    NTEContext As Long, NTEInstance As Long) As Long
Public Declare Function GetIpNetTable Lib "IPHlpApi" (ByVal pIpNetTable As Long, pdwSize As Long, ByVal bOrder As Boolean) As Long
Public Declare Function DeleteIpNetEntry Lib "IPHlpApi" (pArpEntry As MIB_IPNETROW) As Long
Public Declare Function SetIpNetEntry Lib "IPHlpApi" (pArpEntry As MIB_IPNETROW) As Long

Global Const ERROR_BUFFER_OVERFLOW = 111
Global Const ERROR_INSUFFICIENT_BUFFER = 122
Public Const GMEM_FIXED = &H0

Public Declare Function GlobalAlloc Lib "Kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long
Public Declare Function GlobalFree Lib "Kernel32" (ByVal hMem As Long) As Long
Public Declare Sub CopyMemory Lib "Kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Global Const WSA_DESCRIPTIONLEN = 256
Global Const WSA_DescriptionSize = WSA_DESCRIPTIONLEN + 1
Global Const WSA_SYS_STATUS_LEN = 128
Global Const WSA_SysStatusSize = WSA_SYS_STATUS_LEN + 1

Type WSADataType
    wVersion As Integer
    wHighVersion As Integer
    szDescription As String * WSA_DescriptionSize
    szSystemStatus As String * WSA_SysStatusSize
    iMaxSockets As Integer
    iMaxUdpDg As Integer
    lpVendorInfo As Long
End Type

Public Declare Function WSAStartup Lib "ws2_32.DLL" (ByVal wVR As Long, lpWSAD As WSADataType) As Long
Public Declare Function WSACleanup Lib "ws2_32.DLL" () As Long
Public Declare Function inet_ntoa Lib "ws2_32.DLL" (ByVal in_n As Long) As Long
Public Declare Function inet_addr Lib "ws2_32.DLL" (ByVal cp As String) As Long
Public Declare Function ntohl Lib "ws2_32.DLL" (ByVal netlong As Long) As Long
Public Declare Function ntohs Lib "ws2_32.DLL" (ByVal netshort As Long) As Long
Public Declare Function lstrcpy Lib "Kernel32" Alias "lstrcpyA" (ByVal lpString1 As String, ByVal lpString2 As Long) As Long
Public Declare Sub ZeroMemory Lib "Kernel32" Alias "RtlZeroMemory" (Dest As Any, ByVal numBytes As Long)

Public Function TCPIPStartup() As Boolean
  Dim rc As Integer   'Return code
  Dim wVersionRequested As Long   'Version requested for winsocks
  Dim WSAData As WSADataType          'Detais os winsock implementation
  
  wVersionRequested = &H202
  TCPIPStartup = True
  rc = WSAStartup(wVersionRequested, WSAData)
  If rc <> 0 Then
    MsgBox ("RC: " & rc & " Unable to start winsocks" & ", Error " & Err.LastDllError)
    Call TCPIPShutDown
    TCPIPStartup = False
    Exit Function
  End If

End Function

Public Function TCPIPShutDown() As Boolean
    WSACleanup
End Function

