VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IPRoute"
   ClientHeight    =   5205
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   7155
   LinkTopic       =   "Form1"
   ScaleHeight     =   5205
   ScaleWidth      =   7155
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "IP Route"
      Height          =   1575
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6855
      Begin VB.TextBox txtMetric 
         Height          =   375
         Left            =   6360
         TabIndex        =   9
         Text            =   "1"
         Top             =   840
         Width           =   375
      End
      Begin VB.TextBox txtInterface 
         Height          =   375
         Left            =   5040
         TabIndex        =   8
         Text            =   "157.55.80.9"
         Top             =   840
         Width           =   1335
      End
      Begin VB.TextBox txtGateway 
         Height          =   375
         Left            =   3720
         TabIndex        =   7
         Text            =   "157.55.80.1"
         Top             =   840
         Width           =   1335
      End
      Begin VB.TextBox txtMask 
         Height          =   375
         Left            =   2400
         TabIndex        =   6
         Text            =   "255.0.0.0"
         Top             =   840
         Width           =   1335
      End
      Begin VB.TextBox txtDest 
         Height          =   375
         Left            =   1080
         TabIndex        =   5
         Text            =   "157.0.0.0"
         Top             =   840
         Width           =   1335
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Do It"
         Height          =   375
         Left            =   120
         TabIndex        =   4
         Top             =   840
         Width           =   855
      End
      Begin VB.OptionButton optDelete 
         Caption         =   "Delete"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   480
         Width           =   975
      End
      Begin VB.OptionButton optAdd 
         Caption         =   "Add"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   240
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.Label Label5 
         Caption         =   "Please enter route information appropriate to your machine:"
         BeginProperty Font 
            Name            =   "MS Sans Serif"
            Size            =   8.25
            Charset         =   0
            Weight          =   400
            Underline       =   -1  'True
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   255
         Left            =   1080
         TabIndex        =   15
         Top             =   240
         Width           =   4455
      End
      Begin VB.Label Label4 
         Caption         =   "Metric:"
         Height          =   255
         Left            =   6240
         TabIndex        =   14
         Top             =   600
         Width           =   495
      End
      Begin VB.Label Label3 
         Caption         =   "Interface:"
         Height          =   255
         Left            =   5040
         TabIndex        =   13
         Top             =   600
         Width           =   855
      End
      Begin VB.Label Label2 
         Caption         =   "Gateway:"
         Height          =   255
         Left            =   3720
         TabIndex        =   12
         Top             =   600
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "Mask:"
         Height          =   255
         Left            =   2400
         TabIndex        =   11
         Top             =   600
         Width           =   615
      End
      Begin VB.Label Dest 
         Caption         =   "Dest:"
         Height          =   255
         Left            =   1080
         TabIndex        =   10
         Top             =   600
         Width           =   615
      End
   End
   Begin VB.ListBox List1 
      BeginProperty Font 
         Name            =   "Microsoft Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2790
      Left            =   120
      TabIndex        =   0
      Top             =   2160
      Width           =   6855
   End
   Begin VB.Label Label6 
      Caption         =   "Routing Table:"
      Height          =   255
      Left            =   120
      TabIndex        =   16
      Top             =   1800
      Width           =   1215
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

Function MyGetIpAddrTable() As Long
    Dim Status As Long, dwActualSize As Long
    Dim fOrder As Boolean
    Dim pIpAddrTable As Long
    
    fOrder = True
    dwActualSize = 0
    MyGetIpAddrTable = 0
    
    Status = GetIpAddrTable(0, dwActualSize, fOrder)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           MsgBox "GetIpAddrTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
           Exit Function
        End If
    End If
    
    pIpAddrTable = GlobalAlloc(GMEM_FIXED, dwActualSize)
    If pIpAddrTable = 0 Then
        MsgBox "GlobalAlloc sizing failed "
        Exit Function
    End If
        
    Status = GetIpAddrTable(pIpAddrTable, dwActualSize, fOrder)
    If Status <> 0 Then
        MsgBox "GetIpAddrTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
        GlobalFree pIpAddrTable
        Exit Function
    End If
    MyGetIpAddrTable = pIpAddrTable 'Caller of this function should free pIpAddrTable
    
End Function
Function InterfaceIpToIdxAndMask(pIpAddrTable As Long, ByVal strIP As String, dwIndex As Long, dwMask As Long) As Boolean
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    Dim IpAddrRowEntry As MIB_IPADDRROW
    Dim dwIfIpAddr As Long
    InterfaceIpToIdxAndMask = False
    
    If pIpAddrTable = 0 Then
        MsgBox "IpAddrTable pointer is NULL!"
        Exit Function
    End If
    
    dwIfIpAddr = inet_addr(strIP)
    If dwIfIpAddr = -1 Then Exit Function

    pWorkingPointer = pIpAddrTable
    CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    For i = 1 To dwNumEntry
        
        ZeroMemory IpAddrRowEntry, Len(IpAddrRowEntry)
        CopyMemory IpAddrRowEntry, ByVal pWorkingPointer, Len(IpAddrRowEntry)
        pWorkingPointer = pWorkingPointer + Len(IpAddrRowEntry)
        
        If dwIfIpAddr = IpAddrRowEntry.dwAddr Then
        
            dwIndex = IpAddrRowEntry.dwIndex
            dwMask = IpAddrRowEntry.dwMask
            InterfaceIpToIdxAndMask = True
            Exit Function
        End If
    Next
End Function

Function InterfaceIdxToInterfaceIp(pIpAddrTable As Long, dwIndex As Long, strIP As String) As Boolean

    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    Dim IpAddrRowEntry As MIB_IPADDRROW
    InterfaceIdxToInterfaceIp = False
    
    If pIpAddrTable = 0 Then
        MsgBox "IpAddrTable pointer is NULL!"
        Exit Function
    End If
    
    pWorkingPointer = pIpAddrTable
    CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    For i = 1 To dwNumEntry
        
        ZeroMemory IpAddrRowEntry, Len(IpAddrRowEntry)
        CopyMemory IpAddrRowEntry, ByVal pWorkingPointer, Len(IpAddrRowEntry)
        pWorkingPointer = pWorkingPointer + Len(IpAddrRowEntry)
        
        If dwIndex = IpAddrRowEntry.dwIndex Then
        
            strIP = String(256, 0)
            lstrcpy strIP, inet_ntoa(IpAddrRowEntry.dwAddr)
            strIP = Left(strIP, InStr(strIP, Chr(0)) - 1)
            InterfaceIdxToInterfaceIp = True
            Exit Function
        End If
    Next

End Function

Sub MyGetIpForwardTable(Listx As ListBox)
    Dim Status As Long, dwActualSize As Long
    Dim fOrder As Boolean
    Dim pIpRouteTab As Long
    
    Dim RouteTableEntry As MIB_IPFORWARDROW
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    Dim dwCurrIndex As Long
    
    Dim pIpAddrTable As Long
    
    Dim tmpStr As String
    Dim tmpStr2 As String
    tmpStr = String(512, 0)
    tmpStr2 = String(256, 0)
   
    pIpAddrTable = MyGetIpAddrTable
    If pIpAddrTable = 0 Then
        MsgBox "Can't get IpAddr Table"
        Exit Sub
    End If
    
    fOrder = True
    dwActualSize = 0
    
    Status = GetIpForwardTable(0, dwActualSize, fOrder)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           Listx.AddItem "GetIpForwardTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
           GlobalFree pIpAddrTable
           Exit Sub
        End If
    End If
    
    pIpRouteTab = GlobalAlloc(GMEM_FIXED, dwActualSize)
    If pIpRouteTab = 0 Then
        Listx.AddItem "GlobalAlloc sizing failed "
        GlobalFree pIpAddrTable
        Exit Sub
    End If
        
    Status = GetIpForwardTable(pIpRouteTab, dwActualSize, fOrder)
    If Status <> 0 Then
        Listx.AddItem "GetIpForwardTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
        GlobalFree pIpRouteTab
        GlobalFree pIpAddrTable
        Exit Sub
    End If
    
    Listx.Clear
    Listx.AddItem "Network Address " & vbTab & "Netmask          " & vbTab & "Gateway Address " & vbTab & "Interface       " & vbTab & "Metric"
    
    pWorkingPointer = pIpRouteTab
    CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    For i = 1 To dwNumEntry
        tmpStr = ""
        ZeroMemory RouteTableEntry, Len(RouteTableEntry)
        CopyMemory RouteTableEntry, ByVal pWorkingPointer, Len(RouteTableEntry)
        pWorkingPointer = pWorkingPointer + Len(RouteTableEntry)
        
        tmpStr2 = String(256, 0)
        lstrcpy tmpStr2, inet_ntoa(RouteTableEntry.dwForwardDest)
        tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
        tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
        
        tmpStr2 = String(256, 0)
        lstrcpy tmpStr2, inet_ntoa(RouteTableEntry.dwForwardMask)
        tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
        tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
        
        tmpStr2 = String(256, 0)
        lstrcpy tmpStr2, inet_ntoa(RouteTableEntry.dwForwardNextHop)
        tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
        tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
        
        dwCurrIndex = RouteTableEntry.dwForwardIfIndex
        If InterfaceIdxToInterfaceIp(pIpAddrTable, dwCurrIndex, tmpStr2) = False Then
            MsgBox "InterfaceIdxToInterfaceIp failed"
            Exit For
        End If
        tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
        
        tmpStr = tmpStr & RouteTableEntry.dwForwardMetric1
        
        Listx.AddItem tmpStr
    Next
    
    GlobalFree pIpAddrTable
    GlobalFree pIpRouteTab

End Sub

Private Sub Command1_Click()
    Dim dwStatus As Long

    Dim routeEntry As MIB_IPFORWARDROW      '// Ip routing table row entry
    Dim pIpAddrTable As Long                '// Ip Addr Table
    Dim dwIfIndex As Long                   '// Interface index number
    Dim dwIfMask As Long                    '// Interface Subnet Mask
    Dim dwIfIpAddr As Long                  '// Interface Ip Address
    
    Dim Status As Long, dwActualSize As Long
    Dim fOrder As Boolean
    Dim pIpRouteTab As Long
    Dim RouteTableEntry As MIB_IPFORWARDROW
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    Dim dwForwardDest As Long
         
    
    If optAdd.Value = True Then
    
        On Error GoTo ErrorPro
    
    ''''''''''''''''start of add route'''''''''''''''''''''''
    
        If txtDest.Text = "" Or txtMask.Text = "" Or txtGateway.Text = "" Or txtInterface.Text = "" Then
            MsgBox "Please enter the route information"
            Exit Sub
        End If
        routeEntry.dwForwardDest = inet_addr(txtDest.Text)
        If (routeEntry.dwForwardDest = -1) Then
            MsgBox "IpRoute: Bad Destination " & txtDest.Text
            Exit Sub
        End If
        routeEntry.dwForwardMask = inet_addr(txtMask.Text)
        If (routeEntry.dwForwardMask = -1 And txtMask.Text <> "255.255.255.255") Then
            MsgBox "IpRoute: Bad Mask " & txtMask.Text
            Exit Sub
        End If
        routeEntry.dwForwardNextHop = inet_addr(txtGateway.Text)
        If (routeEntry.dwForwardDest = -1) Then
            MsgBox "IpRoute: Bad Gateway " & txtGateway.Text
            Exit Sub
        End If
        If ((routeEntry.dwForwardMask And routeEntry.dwForwardDest) <> routeEntry.dwForwardDest) Then
            MsgBox "IpRoute: Invalid Mask " & txtMask.Text
            Exit Sub
        End If
        
        dwIfIpAddr = inet_addr(txtInterface.Text)
        If (dwIfIpAddr = -1) Then
            MsgBox "IpRoute: Bad Interface " & txtInterface.Text
            Exit Sub
        End If
        
        routeEntry.dwForwardMetric1 = CLng(txtMetric)
        
        On Error GoTo 0

        
        pIpAddrTable = MyGetIpAddrTable
        If pIpAddrTable = 0 Then
            MsgBox "Can't get IpAddr Table"
            Exit Sub
        End If

        If InterfaceIpToIdxAndMask(pIpAddrTable, txtInterface.Text, dwIfIndex, dwIfMask) = False Then
            MsgBox "IpRoute: Bad Interface " & txtInterface
            GlobalFree pIpAddrTable
            Exit Sub
        End If
        
        routeEntry.dwForwardIfIndex = dwIfIndex
    
        routeEntry.dwForwardMetric1 = CLng(txtMetric)
        routeEntry.dwForwardProto = MIB_IPPROTO_LOCAL
        routeEntry.dwForwardMetric2 = -1
        routeEntry.dwForwardMetric3 = -1
        routeEntry.dwForwardMetric4 = -1
    
        dwStatus = SetIpForwardEntry(routeEntry)
        If (dwStatus <> 0) Then
            MsgBox "IpRoute: couldn't add " & txtDest.Text & ", dwStatus = " & dwStatus & ". Err# is " & Err.LastDllError
            GlobalFree pIpAddrTable
            Exit Sub
        End If
        
        GlobalFree pIpAddrTable
       
    ''''''''''''''''end of add route'''''''''''''''''''''''
    
    Else
    ''''''''''''''''start of delete route route'''''''''''''''''''''''
        On Error GoTo ErrorPro
        If txtDest.Text = "" Then
            MsgBox "Please enter the dest route information"
            Exit Sub
        End If
         
        dwForwardDest = inet_addr(txtDest.Text)
        If (dwForwardDest = -1) Then
            MsgBox "IpRoute: Bad Destination " & txtDest.Text
            Exit Sub
        End If
        On Error GoTo 0
        fOrder = True
        dwActualSize = 0
         
        dwStatus = GetIpForwardTable(0, dwActualSize, fOrder)
        If dwStatus <> 0 Then
            If dwStatus <> ERROR_INSUFFICIENT_BUFFER Then
                MsgBox "GetIpForwardTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
                Exit Sub
            End If
        End If
         
        pIpRouteTab = GlobalAlloc(GMEM_FIXED, dwActualSize)
        If pIpRouteTab = 0 Then
            MsgBox "GlobalAlloc sizing failed "
            Exit Sub
        End If
             
        dwStatus = GetIpForwardTable(pIpRouteTab, dwActualSize, fOrder)
        If dwStatus <> 0 Then
            MsgBox "GetIpForwardTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
            GlobalFree pIpRouteTab
            Exit Sub
        End If
                  
        pWorkingPointer = pIpRouteTab
        CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
        pWorkingPointer = pWorkingPointer + 4
        Dim bMatchingDest As Boolean
        bMatchingDest = False
        
        For i = 1 To dwNumEntry
            ZeroMemory RouteTableEntry, Len(RouteTableEntry)
            CopyMemory RouteTableEntry, ByVal pWorkingPointer, Len(RouteTableEntry)
            pWorkingPointer = pWorkingPointer + Len(RouteTableEntry)
            If (dwForwardDest = RouteTableEntry.dwForwardDest) Then
               
                dwStatus = DeleteIpForwardEntry(RouteTableEntry)
                If (dwStatus <> 0) Then
                    MsgBox "IpRoute: couldn't delete " & txtDest.Text & ", dwStatus = " & dwStatus
                End If
                bMatchingDest = True
                Exit For
            End If
        Next
        If bMatchingDest = False Then MsgBox "No routes matching " & txtDest.Text & " to delete"
        GlobalFree pIpRouteTab

    ''''''''''''''''end of delete route'''''''''''''''''''''''
    End If
            
    MyGetIpForwardTable List1
    Exit Sub
ErrorPro:
    MsgBox "Incorrect data types. Please check your route information"
End Sub

Private Sub Command2_Click()
    List1.Clear

End Sub

Private Sub Form_Load()
    TCPIPStartup
    MyGetIpForwardTable List1
End Sub

Private Sub Form_Unload(Cancel As Integer)
    TCPIPShutDown
End Sub

Private Sub mnuRefresh_Click()
    MyGetIpForwardTable List1
End Sub

Private Sub optAdd_Click()
    optAdd.Value = True
    txtDest.Text = "157.0.0.0"
    txtMask.Text = "255.0.0.0"
    txtGateway.Text = "157.55.80.1"
    txtInterface = "157.55.80.9"
    txtMetric.Text = "1"
End Sub

Private Sub optDelete_Click()
    optDelete.Value = True
    txtDest.Text = "157.0.0.0"
    txtMask.Text = ""
    txtGateway.Text = ""
    txtInterface.Text = ""
    txtMetric.Text = ""
End Sub
