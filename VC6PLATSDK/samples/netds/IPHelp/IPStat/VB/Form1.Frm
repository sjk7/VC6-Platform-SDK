VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IPStat"
   ClientHeight    =   8235
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9390
   LinkTopic       =   "Form1"
   ScaleHeight     =   8235
   ScaleWidth      =   9390
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox List3 
      Height          =   3180
      Left            =   3480
      TabIndex        =   2
      Top             =   240
      Width           =   5775
   End
   Begin VB.ListBox List2 
      Height          =   4350
      Left            =   120
      TabIndex        =   1
      Top             =   3720
      Width           =   9135
   End
   Begin VB.ListBox List1 
      Height          =   3180
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   3135
   End
   Begin VB.Label Label3 
      Caption         =   "Tcp Connection Table:"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   3480
      Width           =   1815
   End
   Begin VB.Label Label2 
      Caption         =   "UDP Listener Table:"
      Height          =   255
      Left            =   3480
      TabIndex        =   4
      Top             =   0
      Width           =   1695
   End
   Begin VB.Label Label1 
      Caption         =   "Statistics:"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   0
      Width           =   1335
   End
   Begin VB.Menu mnuRefresh 
      Caption         =   "Refresh"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Sub MyGetIpStatistics(listx As ListBox)
    Dim mibIPSTATS As MIB_IPSTATS
    Dim Error As Long
    Dim szSpace As String
    szSpace = "   "
    
    Error = GetIpStatistics(mibIPSTATS)
    If Error <> 0 Then
        MsgBox "GetIpStatistics failed " & Err.LastDllError
        Exit Sub
    End If
    
    With listx
        .AddItem "IP Statistics:"
        .AddItem szSpace & "dwForwarding: " & mibIPSTATS.dwForwarding
        .AddItem szSpace & "dwDefaultTTL: " & mibIPSTATS.dwDefaultTTL
        .AddItem szSpace & "dwInReceives: " & mibIPSTATS.dwInReceives
        .AddItem szSpace & "dwInHdrErrors: " & mibIPSTATS.dwInHdrErrors
        .AddItem szSpace & "dwInAddrErrors: " & mibIPSTATS.dwInAddrErrors
        .AddItem szSpace & "dwForwDatagrams: " & mibIPSTATS.dwForwDatagrams
        .AddItem szSpace & "dwInUnknownProtos: " & mibIPSTATS.dwInUnknownProtos
        .AddItem szSpace & "dwInDiscards: " & mibIPSTATS.dwInDiscards
        .AddItem szSpace & "dwInDelivers: " & mibIPSTATS.dwInDelivers
        .AddItem szSpace & "dwOutRequests: " & mibIPSTATS.dwOutRequests
        .AddItem szSpace & "dwRoutingDiscards: " & mibIPSTATS.dwRoutingDiscards
        .AddItem szSpace & "dwOutDiscards: " & mibIPSTATS.dwOutDiscards
        .AddItem szSpace & "dwOutNoRoutes: " & mibIPSTATS.dwOutNoRoutes
        .AddItem szSpace & "dwReasmTimeout: " & mibIPSTATS.dwReasmTimeout
        .AddItem szSpace & "dwReasmReqds: " & mibIPSTATS.dwReasmReqds
        .AddItem szSpace & "dwReasmOks: " & mibIPSTATS.dwReasmOks
        .AddItem szSpace & "dwReasmFails: " & mibIPSTATS.dwReasmFails
        .AddItem szSpace & "dwFragOks: " & mibIPSTATS.dwFragOks
        .AddItem szSpace & "dwFragFails: " & mibIPSTATS.dwFragFails
        .AddItem szSpace & "dwFragCreates: " & mibIPSTATS.dwFragCreates
        .AddItem szSpace & "dwNumIf: " & mibIPSTATS.dwNumIf
        .AddItem szSpace & "dwNumAddr: " & mibIPSTATS.dwNumAddr
        .AddItem szSpace & "dwNumRoutes: " & mibIPSTATS.dwNumRoutes
    End With
    
End Sub

Sub MyGetIcmpStatistics(listx As ListBox)
    Dim mibICMP As MIB_ICMP
    Dim Error As Long
    Dim szSpace As String
    szSpace = "   "
    
    Error = GetIcmpStatistics(mibICMP)
    If Error <> 0 Then
        MsgBox "GetIcmpStatistics failed " & Err.LastDllError
        Exit Sub
    End If
        
    With listx
        .AddItem "ICMP Statistics:"
        .AddItem szSpace & "dwMsgs: " & "In: " & mibICMP.Stats.icmpInStats.dwMsgs & " Out: " & mibICMP.Stats.icmpOutStats.dwMsgs
        .AddItem szSpace & "dwErrors: " & "In: " & mibICMP.Stats.icmpInStats.dwErrors & " Out: " & mibICMP.Stats.icmpOutStats.dwErrors
        .AddItem szSpace & "dwDestUnreachs: " & "In: " & mibICMP.Stats.icmpInStats.dwDestUnreachs & " Out: " & mibICMP.Stats.icmpOutStats.dwDestUnreachs
        .AddItem szSpace & "dwTimeExcds: " & "In: " & mibICMP.Stats.icmpInStats.dwTimeExcds & " Out: " & mibICMP.Stats.icmpOutStats.dwTimeExcds
        .AddItem szSpace & "dwParmProbs: " & "In: " & mibICMP.Stats.icmpInStats.dwParmProbs & " Out: " & mibICMP.Stats.icmpOutStats.dwParmProbs
        .AddItem szSpace & "dwSrcQuenchs: " & "In: " & mibICMP.Stats.icmpInStats.dwSrcQuenchs & " Out: " & mibICMP.Stats.icmpOutStats.dwSrcQuenchs
        .AddItem szSpace & "dwRedirects: " & "In: " & mibICMP.Stats.icmpInStats.dwRedirects & " Out: " & mibICMP.Stats.icmpOutStats.dwRedirects
        .AddItem szSpace & "dwEchos: " & "In: " & mibICMP.Stats.icmpInStats.dwEchos & " Out: " & mibICMP.Stats.icmpOutStats.dwEchos
        .AddItem szSpace & "dwEchoReps: " & "In: " & mibICMP.Stats.icmpInStats.dwEchoReps & " Out: " & mibICMP.Stats.icmpOutStats.dwEchoReps
        .AddItem szSpace & "dwTimestamps: " & "In: " & mibICMP.Stats.icmpInStats.dwTimestamps & " Out: " & mibICMP.Stats.icmpOutStats.dwTimestamps
        .AddItem szSpace & "dwTimestampReps: " & "In: " & mibICMP.Stats.icmpInStats.dwTimestampReps & " Out: " & mibICMP.Stats.icmpOutStats.dwTimestampReps
        .AddItem szSpace & "dwAddrMasks: " & "In: " & mibICMP.Stats.icmpInStats.dwAddrMasks & " Out: " & mibICMP.Stats.icmpOutStats.dwAddrMasks
        .AddItem szSpace & "dwAddrMaskReps: " & "In: " & mibICMP.Stats.icmpInStats.dwAddrMaskReps & " Out: " & mibICMP.Stats.icmpOutStats.dwAddrMaskReps
    End With
End Sub


Sub MyGetTcpStatistics(listx As ListBox)
    Dim mibTCPSTATS As MIB_TCPSTATS
    Dim Error As Long
    Dim szSpace As String
    szSpace = "   "
    
    Error = GetTcpStatistics(mibTCPSTATS)
    If Error <> 0 Then
        MsgBox "GetTcpStatistic failed " & Err.LastDllError
        Exit Sub
    End If
           
    With listx
        .AddItem "TCP Statistics:"
        .AddItem szSpace & "dwRtoAlgorithm: " & mibTCPSTATS.dwRtoAlgorithm
        .AddItem szSpace & "dwRtoMin: " & mibTCPSTATS.dwRtoMin
        .AddItem szSpace & "dwRtoMax: " & mibTCPSTATS.dwRtoMax
        .AddItem szSpace & "dwMaxConn: " & mibTCPSTATS.dwMaxConn
        .AddItem szSpace & "dwActiveOpens: " & mibTCPSTATS.dwActiveOpens
        .AddItem szSpace & "dwPassiveOpens: " & mibTCPSTATS.dwPassiveOpens
        .AddItem szSpace & "dwAttemptFails: " & mibTCPSTATS.dwAttemptFails
        .AddItem szSpace & "dwEstabResets: " & mibTCPSTATS.dwEstabResets
        .AddItem szSpace & "dwCurrEstab: " & mibTCPSTATS.dwCurrEstab
        .AddItem szSpace & "dwInSegs: " & mibTCPSTATS.dwInSegs
        .AddItem szSpace & "dwOutSegs: " & mibTCPSTATS.dwOutSegs
        .AddItem szSpace & "dwRetransSegs: " & mibTCPSTATS.dwRetransSegs
        .AddItem szSpace & "dwInErrs: " & mibTCPSTATS.dwInErrs
        .AddItem szSpace & "dwNumConns: " & mibTCPSTATS.dwNumConns
    End With
End Sub
Sub MyGetUdpStatistics(listx As ListBox)
    Dim mibUDPSTATS As MIB_UDPSTATS
    Dim Error As Long
    Dim szSpace As String
    szSpace = "   "
    
    Error = GetUdpStatistics(mibUDPSTATS)
    If Error <> 0 Then
        MsgBox "GetUdpStatistics failed " & Err.LastDllError
        Exit Sub
    End If
           
    With listx
        .AddItem "UDP Statistics:"
        .AddItem szSpace & "dwInDatagrams: " & mibUDPSTATS.dwInDatagrams
        .AddItem szSpace & "dwNoPorts: " & mibUDPSTATS.dwNoPorts
        .AddItem szSpace & "dwInErrors: " & mibUDPSTATS.dwInErrors
        .AddItem szSpace & "dwOutDatagrams: " & mibUDPSTATS.dwOutDatagrams
        .AddItem szSpace & "dwNumAddrs: " & mibUDPSTATS.dwNumAddrs
    End With
End Sub

Sub MyGetTcpTable(listx As ListBox)
    Dim Status As Long, dwActualSize As Long
    Dim fOrder As Boolean
    Dim pTcpTable As Long
    
    Dim TcpTableEntry As MIB_TCPROW
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    
    Dim tmpStr As String
    Dim tmpStr2 As String
    tmpStr = String(512, 0)
    tmpStr2 = String(256, 0)
   
    fOrder = True
    dwActualSize = 0
    
    Status = GetTcpTable(0, dwActualSize, fOrder)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           MsgBox "GetTcpTable sizing failed with error " & Status
           Exit Sub
        End If
    End If
    
    pTcpTable = GlobalAlloc(GMEM_FIXED, dwActualSize)
    If pTcpTable = 0 Then
        MsgBox "GlobalAlloc sizing failed "
        Exit Sub
    End If
        
    Status = GetTcpTable(pTcpTable, dwActualSize, fOrder)
    If Status <> 0 Then
        MsgBox "GetTcpTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
        GlobalFree pTcpTable
        Exit Sub
    End If
    
    pWorkingPointer = pTcpTable
    CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    For i = 1 To dwNumEntry
        ZeroMemory TcpTableEntry, Len(TcpTableEntry)
        CopyMemory TcpTableEntry, ByVal pWorkingPointer, Len(TcpTableEntry)
        pWorkingPointer = pWorkingPointer + Len(TcpTableEntry)
        
        tmpStr2 = String(256, 0)
        tmpStr = "Loc Addr: "
        lstrcpy tmpStr2, inet_ntoa(TcpTableEntry.dwLocalAddr)
        tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
        tmpStr = tmpStr & tmpStr2 & ", " & vbTab
        
        tmpStr = tmpStr & "Loc Port: " & (ntohs(TcpTableEntry.dwLocalPort And &HFFFF) And &HFFFF&) & ", " & vbTab

        tmpStr2 = String(256, 0)
        tmpStr = tmpStr & "Remote Addr: "
        lstrcpy tmpStr2, inet_ntoa(TcpTableEntry.dwRemoteAddr)
        tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
        tmpStr = tmpStr & tmpStr2 & ", " & vbTab
        
        If TcpTableEntry.dwState = MIB_TCP_STATE_LISTEN Then
            tmpStr = tmpStr & "Remote Port: 0, " & vbTab
        Else
            tmpStr = tmpStr & "Remote Port: " & (ntohs(TcpTableEntry.dwRemotePort And &HFFFF) And &HFFFF&) & ", " & vbTab
        End If
        
        Select Case TcpTableEntry.dwState
            Case MIB_TCP_STATE_CLOSED:
                tmpStr = tmpStr & "State: Closed"
            Case MIB_TCP_STATE_TIME_WAIT:
                tmpStr = tmpStr & "State: TIME_WAIT"
            Case MIB_TCP_STATE_LAST_ACK:
                tmpStr = tmpStr & "State: LAST_ACK"
            Case MIB_TCP_STATE_CLOSING:
                tmpStr = tmpStr & "State: CLOSING"
            Case MIB_TCP_STATE_CLOSE_WAIT:
                tmpStr = tmpStr & "State: CLOSE_WAIT"
            Case MIB_TCP_STATE_FIN_WAIT1:
                tmpStr = tmpStr & "State: FIN_WAIT1"
            Case MIB_TCP_STATE_ESTAB:
                tmpStr = tmpStr & "State: ESTAB"
            Case MIB_TCP_STATE_SYN_RCVD:
                tmpStr = tmpStr & "State: SYN_RCVD"
            Case MIB_TCP_STATE_SYN_SENT:
                tmpStr = tmpStr & "State: SYN_SENT"
            Case MIB_TCP_STATE_LISTEN:
                tmpStr = tmpStr & "State: LISTEN"
            Case MIB_TCP_STATE_DELETE_TCB:
                tmpStr = tmpStr & "State: DELETE"
            Case Else
                tmpStr = tmpStr & "State: Error: unknown state!"
        End Select
        
        listx.AddItem tmpStr
        
    Next
    
    
    GlobalFree pTcpTable

End Sub

Sub MyGetUdpTable(listx As ListBox)
    Dim Status As Long, dwActualSize As Long
    Dim fOrder As Boolean
    Dim pUdpTable As Long
    
    Dim UdpTableEntry As MIB_UDPROW
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    
    Dim tmpStr As String
    Dim tmpStr2 As String
    tmpStr = String(512, 0)
    tmpStr2 = String(256, 0)
   
    fOrder = True
    dwActualSize = 0
    
    Status = GetUdpTable(0, dwActualSize, fOrder)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           MsgBox "GetUdpTable sizing failed with error " & Status
           Exit Sub
        End If
    End If
    
    pUdpTable = GlobalAlloc(GMEM_FIXED, dwActualSize)
    If pUdpTable = 0 Then
        MsgBox "GlobalAlloc sizing failed "
        Exit Sub
    End If
        
    Status = GetUdpTable(pUdpTable, dwActualSize, fOrder)
    If Status <> 0 Then
        MsgBox "GetUdpTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
        GlobalFree pUdpTable
        Exit Sub
    End If
    
    pWorkingPointer = pUdpTable
    CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    For i = 1 To dwNumEntry
        ZeroMemory UdpTableEntry, Len(UdpTableEntry)
        CopyMemory UdpTableEntry, ByVal pWorkingPointer, Len(UdpTableEntry)
        pWorkingPointer = pWorkingPointer + Len(UdpTableEntry)
        
        tmpStr2 = String(256, 0)
        tmpStr = "Loc Addr: "
        lstrcpy tmpStr2, inet_ntoa(UdpTableEntry.dwLocalAddr)
        tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
        tmpStr = tmpStr & tmpStr2 & ", " & vbTab
        tmpStr = tmpStr & "Loc Port: " & (ntohs(UdpTableEntry.dwLocalPort And &HFFFF) And &HFFFF&)
        
        listx.AddItem tmpStr
    Next
    
    GlobalFree pUdpTable

End Sub

Private Sub Form_Load()
    TCPIPStartup
    
    mnuRefresh_Click
    
    TCPIPShutDown
End Sub

Private Sub mnuRefresh_Click()
    List1.Clear
    List2.Clear
    List3.Clear
    
    MyGetIpStatistics List1
    List1.AddItem "*************"
    MyGetIcmpStatistics List1
    List1.AddItem "*************"
    MyGetTcpStatistics List1
    List1.AddItem "*************"
    MyGetUdpStatistics List1
    
    MyGetTcpTable List2
    MyGetUdpTable List3
End Sub
