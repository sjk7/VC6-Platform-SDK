VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IPConfig"
   ClientHeight    =   4545
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   6705
   LinkTopic       =   "Form1"
   ScaleHeight     =   4545
   ScaleWidth      =   6705
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox List1 
      Height          =   4155
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   6375
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
Sub GetIpConfigInfo(Listx As ListBox)
    Dim error As Long
    Dim FixedInfoSize As Long
    Dim AdapterInfoSize As Long
    Dim i As Integer
    Dim PhysicalAddress  As String
    Dim NewTime As Date
    Dim AdapterInfo As IP_ADAPTER_INFO
    Dim AddrStr As IP_ADDR_STRING
    Dim FixedInfo As FIXED_INFO
    Dim Buffer As IP_ADDR_STRING
    Dim pAddrStr As Long
    Dim pAdapt As Long
    Dim Buffer2 As IP_ADAPTER_INFO
    Dim FixedInfoBuffer() As Byte
    Dim AdapterInfoBuffer() As Byte
    
    Listx.Clear
    'Get the main IP configuration information for this machine using a FIXED_INFO structure
    FixedInfoSize = 0
    error = GetNetworkParams(ByVal 0&, FixedInfoSize)
    If error <> 0 Then
        If error <> ERROR_BUFFER_OVERFLOW Then
           MsgBox "GetNetworkParams sizing failed with error " & error
           Exit Sub
        End If
    End If
    ReDim FixedInfoBuffer(FixedInfoSize - 1)

    error = GetNetworkParams(FixedInfoBuffer(0), FixedInfoSize)
    If error = 0 Then
            CopyMemory FixedInfo, FixedInfoBuffer(0), Len(FixedInfo)
            Listx.AddItem "Host Name:  " & FixedInfo.HostName
            Listx.AddItem "DNS Servers:  " & FixedInfo.DnsServerList.IpAddress
            pAddrStr = FixedInfo.DnsServerList.Next
            Do While pAddrStr <> 0
                  CopyMemory Buffer, ByVal pAddrStr, Len(Buffer)
                  Listx.AddItem "DNS Servers:  " & Buffer.IpAddress
                  pAddrStr = Buffer.Next
            Loop
            
            Select Case FixedInfo.NodeType
                       Case 1
                                  Listx.AddItem "Node type: Broadcast"
                       Case 2
                                   Listx.AddItem "Node type: Peer to peer"
                       Case 4
                                    Listx.AddItem "Node type: Mixed"
                       Case 8
                                    Listx.AddItem "Node type: Hybrid"
                       Case Else
                                    Listx.AddItem "Unknown node type"
            End Select
            
            Listx.AddItem "NetBIOS Scope ID:  " & FixedInfo.ScopeId
            If FixedInfo.EnableRouting Then
                       Listx.AddItem "IP Routing Enabled "
            Else
                       Listx.AddItem "IP Routing not enabled"
            End If
            If FixedInfo.EnableProxy Then
                       Listx.AddItem "WINS Proxy Enabled "
            Else
                       Listx.AddItem "WINS Proxy not Enabled "
            End If
            If FixedInfo.EnableDns Then
                      Listx.AddItem "NetBIOS Resolution Uses DNS "
            Else
                      Listx.AddItem "NetBIOS Resolution Does not use DNS  "
            End If
    Else
            MsgBox "GetNetworkParams failed with error " & error & ", Err# is " & Err.LastDllEror
            Exit Sub
    End If
    
    Listx.AddItem "*************"
    'Enumerate all of the adapter specific information using the IP_ADAPTER_INFO structure.
    'Note:  IP_ADAPTER_INFO contains a linked list of adapter entries.
    
    AdapterInfoSize = 0
    error = GetAdaptersInfo(ByVal 0&, AdapterInfoSize)
    If error <> 0 Then
        If error <> ERROR_BUFFER_OVERFLOW Then
           MsgBox "GetAdaptersInfo sizing failed with error " & error
           Exit Sub
        End If
    End If
    ReDim AdapterInfoBuffer(AdapterInfoSize - 1)
    
 ' Get actual adapter information
   error = GetAdaptersInfo(AdapterInfoBuffer(0), AdapterInfoSize)
   If error <> 0 Then
      MsgBox "GetAdaptersInfo failed with error " & error & ", Err# is " & Err.LastDllEror
      Exit Sub
   End If
   
   'Allocate memory
   CopyMemory AdapterInfo, AdapterInfoBuffer(0), Len(AdapterInfo)
   pAdapt = AdapterInfo.Next

   Do
      CopyMemory Buffer2, AdapterInfo, Len(Buffer2)
      Select Case Buffer2.Type
             Case MIB_IF_TYPE_ETHERNET
                  Listx.AddItem "Adapter name: Ethernet adapter " & AdapterInfo.AdapterName
             Case MIB_IF_TYPE_TOKENRING
                  Listx.AddItem "Adapter name: Token Ring adapter " & AdapterInfo.AdapterName
             Case MIB_IF_TYPE_FDDI
                  Listx.AddItem "Adapter name: FDDI adapter " & AdapterInfo.AdapterName
             Case MIB_IF_TYPE_PPP
                  Listx.AddItem "Adapter name: PPP adapter" & AdapterInfo.AdapterName
             Case MIB_IF_TYPE_LOOPBACK
                  Listx.AddItem "Adapter name: Loopback adapter " & AdapterInfo.AdapterName
             Case MIB_IF_TYPE_SLIP
                  Listx.AddItem "Adapter name: Slip adapter " & AdapterInfo.AdapterName
             Case Else
                  Listx.AddItem "Adapter name: Other adapter " & AdapterInfo.AdapterName
      End Select
      Listx.AddItem "AdapterDescription: " & Buffer2.Description

      PhysicalAddress = ""
      For i = 0 To Buffer2.AddressLength - 1
          PhysicalAddress = PhysicalAddress & Hex(Buffer2.Address(i))
          If i < Buffer2.AddressLength - 1 Then
             PhysicalAddress = PhysicalAddress & "-"
          End If
      Next
      Listx.AddItem "Physical Address: " & PhysicalAddress
    
      If Buffer2.DhcpEnabled Then
         Listx.AddItem "DHCP Enabled "
      Else
         Listx.AddItem "DHCP disabled"
      End If

      Listx.AddItem "IP Address: " & Buffer2.IpAddressList.IpAddress
      Listx.AddItem "Subnet Mask: " & Buffer2.IpAddressList.IpMask
      pAddrStr = Buffer2.IpAddressList.Next
      Do While pAddrStr <> 0
         If pAddrStr <> 0 Then
            CopyMemory Buffer2.IpAddressList, ByVal pAddrStr, Len(Buffer2.IpAddressList)
         End If
         CopyMemory Buffer, Buffer2.IpAddressList, Len(Buffer)
         Listx.AddItem "IP Address: " & Buffer.IpAddress
         Listx.AddItem "Subnet Mask: " & Buffer.IpMask
         pAddrStr = Buffer.Next
    Loop
    
    Listx.AddItem "Default Gateway: " & Buffer2.GatewayList.IpAddress
    pAddrStr = Buffer2.GatewayList.Next
    Do While pAddrStr <> 0
       CopyMemory Buffer, Buffer2.GatewayList, Len(Buffer)
       Listx.AddItem "IP Address: " & Buffer.IpAddress
       pAddrStr = Buffer.Next
       If pAddrStr <> 0 Then
          CopyMemory Buffer2.GatewayList, ByVal pAddrStr, Len(Buffer2.GatewayList)
       End If
    Loop

    Listx.AddItem "DHCP Server: " & Buffer2.DhcpServer.IpAddress
    Listx.AddItem "Primary WINS Server: " & Buffer2.PrimaryWinsServer.IpAddress
    Listx.AddItem "Secondary WINS Server: " & Buffer2.SecondaryWinsServer.IpAddress

    ' Display time
    NewTime = DateAdd("s", Buffer2.LeaseObtained, #1/1/1970#)
    Listx.AddItem "Lease Obtained: " & CStr(Format(NewTime, "dddd, mmm d hh:mm:ss yyyy"))
     
    NewTime = DateAdd("s", Buffer2.LeaseExpires, #1/1/1970#)
    Listx.AddItem "Lease Expires :  " & CStr(Format(NewTime, "dddd, mmm d hh:mm:ss yyyy"))
    pAdapt = Buffer2.Next
    If pAdapt <> 0 Then
        CopyMemory AdapterInfo, ByVal pAdapt, LenB(AdapterInfo)
    End If
    Listx.AddItem "*************"
   Loop While pAdapt <> 0

End Sub


Private Sub Form_Load()
    TCPIPStartup
    GetIpConfigInfo List1
End Sub

Private Sub Form_Unload(Cancel As Integer)
    TCPIPShutDown
End Sub

Private Sub mnuRefresh_Click()
    GetIpConfigInfo List1
End Sub
