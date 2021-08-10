VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IPRenew"
   ClientHeight    =   4530
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   6630
   LinkTopic       =   "Form1"
   ScaleHeight     =   4530
   ScaleWidth      =   6630
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "IPRenew"
      Height          =   1455
      Left            =   3720
      TabIndex        =   2
      Top             =   120
      Width           =   2655
      Begin VB.TextBox txtIndex 
         Height          =   285
         Left            =   1440
         TabIndex        =   6
         Top             =   240
         Width           =   735
      End
      Begin VB.OptionButton optRelease 
         Caption         =   "Release"
         Height          =   255
         Left            =   240
         TabIndex        =   5
         Top             =   960
         Width           =   975
      End
      Begin VB.OptionButton optRenew 
         Caption         =   "Renew"
         Height          =   255
         Left            =   240
         TabIndex        =   4
         Top             =   600
         Value           =   -1  'True
         Width           =   1095
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Do it"
         Height          =   375
         Left            =   1440
         TabIndex        =   3
         Top             =   840
         Width           =   735
      End
      Begin VB.Label Label1 
         Caption         =   "Adapter Index: "
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   240
         Width           =   1095
      End
   End
   Begin VB.ListBox List2 
      Height          =   1035
      Left            =   240
      TabIndex        =   1
      Top             =   360
      Width           =   3135
   End
   Begin VB.ListBox List1 
      Height          =   2400
      Left            =   240
      TabIndex        =   0
      Top             =   1920
      Width           =   6135
   End
   Begin VB.Label Label3 
      Caption         =   "Adapter Info Details"
      Height          =   375
      Left            =   240
      TabIndex        =   9
      Top             =   1560
      Width           =   1815
   End
   Begin VB.Label Label2 
      Caption         =   "Adapter Index and Description:"
      Height          =   375
      Left            =   240
      TabIndex        =   8
      Top             =   120
      Width           =   2535
   End
   Begin VB.Menu mnuRresh 
      Caption         =   "Refresh"
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Sub DisplayAdatersInfo(Listx As ListBox, ListIndex As ListBox)
    Dim error As Long
    Dim AdapterInfoSize As Long
    Dim i As Integer
    Dim PhysicalAddress  As String
    Dim NewTime As Date
    Dim AdapterInfo As IP_ADAPTER_INFO
    Dim AddrStr As IP_ADDR_STRING
    Dim Buffer As IP_ADDR_STRING
    Dim pAddrStr As Long
    Dim pAdapt As Long
    Dim Buffer2 As IP_ADAPTER_INFO
    Dim AdapterInfoBuffer As Long
    
    AdapterInfoSize = 0
    error = GetAdaptersInfo(ByVal 0&, AdapterInfoSize)
    If error <> 0 Then
        If error <> ERROR_BUFFER_OVERFLOW Then
           MsgBox "GetAdaptersInfo sizing failed with error " & error
           Exit Sub
        End If
    End If

    AdapterInfoBuffer = GlobalAlloc(GMEM_FIXED, AdapterInfoSize)
    If AdapterInfoBuffer = 0 Then
        MsgBox "GlobalAlloc sizing failed "
        Exit Sub
    End If

 ' Get actual adapter information
   error = GetAdaptersInfo(ByVal AdapterInfoBuffer, AdapterInfoSize)
   If error <> 0 Then
      MsgBox "GetAdaptersInfo failed with error " & error & ", Err# is " & Err.LastDllError
      GlobalFree AdapterInfoBuffer
      Exit Sub
   End If
   
   ListIndex.Clear
   Listx.Clear
   
   'Allocate memory
   CopyMemory AdapterInfo, ByVal AdapterInfoBuffer, Len(AdapterInfo)
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
      ListIndex.AddItem "Index " & Buffer2.Index & ": " & Buffer2.Description
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
         CopyMemory Buffer, Buffer2.IpAddressList, Len(Buffer)
         Listx.AddItem "IP Address: " & Buffer.IpAddress
         Listx.AddItem "Subnet Mask: " & Buffer.IpMask
         pAddrStr = Buffer.Next
         If pAddrStr <> 0 Then
            CopyMemory Buffer2.IpAddressList, ByVal pAddrStr, Len(Buffer2.IpAddressList)
         End If
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
        CopyMemory AdapterInfo, ByVal pAdapt, Len(AdapterInfo)
    End If
    Listx.AddItem "***********"
    Listx.AddItem ""
   Loop While pAdapt <> 0
   
   GlobalFree AdapterInfoBuffer
End Sub

Private Sub Command1_Click()
    Dim Status As Long, dwOutBufLen As Long
    Dim pIfTable As Long
    Dim i As Long
    Dim curIndex As Long
    Dim pWorkingPointer As Long
    Dim NumAdapters As Long
    Dim curAdapter As IP_ADAPTER_INDEX_MAP
    Dim bMatch As Boolean
    
    On Error GoTo ErrorPro
    
    If txtIndex.Text = "" Then
        MsgBox "Please enter an adapter index in the Adapter Index box!"
        Exit Sub
    End If
    
    curIndex = CLng(txtIndex.Text)
    
    On Error GoTo 0
    
    dwOutBufLen = 0
    
    Status = GetInterfaceInfo(0, dwOutBufLen)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           MsgBox "GetInterfaceInfo sizing failed with error " & Status
           Exit Sub
        End If
    End If
    pIfTable = GlobalAlloc(GMEM_FIXED, dwOutBufLen)
    
    If pIfTable = 0 Then
        MsgBox "GlobalAlloc sizing failed "
        Exit Sub
    End If
    
    Status = GetInterfaceInfo(pIfTable, dwOutBufLen)
    If Status <> 0 Then
        MsgBox "GetInterfaceInfo failed with error " & Status & ", Err# is " & Err.LastDllError
        GlobalFree pIfTable
        Exit Sub
    End If
    
    pWorkingPointer = pIfTable
    CopyMemory NumAdapters, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    
    bMatch = False
    For i = 0 To NumAdapters - 1
        CopyMemory curAdapter, ByVal pWorkingPointer, Len(curAdapter)
        pWorkingPointer = pWorkingPointer + Len(curAdapter)
        If curIndex = curAdapter.Index Then
            bMatch = True
            If optRelease.Value = True Then
                Status = IpReleaseAddress(curAdapter)
                If Status <> 0 Then
                    MsgBox "IpReleaseAddress failed with error " & Status & ", Err# is " & Err.LastDllError
                    GlobalFree pIfTable
                    Exit Sub
                End If
            Else
                Status = IpRenewAddress(curAdapter)
                If Status <> 0 Then
                    MsgBox "IpReleaseAddress failed with error " & Status & ", Err# is " & Err.LastDllError
                    GlobalFree pIfTable
                    Exit Sub
                End If
            End If
            DisplayAdatersInfo List1, List2
            Exit For
        End If
    Next
    
    If bMatch = False Then
        MsgBox "You might have entered an invalid adapter index!"
    End If

    GlobalFree pIfTable
    Exit Sub
    
ErrorPro:
    MsgBox "Invalid data type. Please enter integer index"
End Sub

Private Sub Form_Load()
    TCPIPStartup
    
    DisplayAdatersInfo List1, List2
End Sub

Private Sub Form_Unload(Cancel As Integer)
    TCPIPShutDown
End Sub

Private Sub mnuRresh_Click()
    DisplayAdatersInfo List1, List2
End Sub

