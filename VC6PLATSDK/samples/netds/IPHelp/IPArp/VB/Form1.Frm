VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IPArp"
   ClientHeight    =   3780
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   6330
   LinkTopic       =   "Form1"
   ScaleHeight     =   3780
   ScaleWidth      =   6330
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame ArpChangeFrame 
      Caption         =   "ArpChange"
      Height          =   1695
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   6015
      Begin VB.TextBox txtArpDelIF 
         Height          =   375
         Left            =   2640
         TabIndex        =   9
         Top             =   1200
         Width           =   1095
      End
      Begin VB.OptionButton optArpAdd 
         Caption         =   "Add"
         Height          =   255
         Left            =   120
         TabIndex        =   8
         Top             =   360
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.OptionButton optArpDel 
         Caption         =   "Delete"
         Height          =   255
         Left            =   120
         TabIndex        =   7
         Top             =   1200
         Width           =   855
      End
      Begin VB.TextBox txtArpDelIp 
         Height          =   375
         Left            =   1080
         TabIndex        =   6
         Text            =   "157.54.185.33"
         Top             =   1200
         Width           =   1335
      End
      Begin VB.TextBox txtArpAddMac 
         Height          =   375
         Left            =   2760
         TabIndex        =   5
         Text            =   "11-22-33-44-55-66"
         Top             =   360
         Width           =   1455
      End
      Begin VB.TextBox txtArpAddIF 
         Height          =   375
         Left            =   4440
         TabIndex        =   4
         Top             =   360
         Width           =   1095
      End
      Begin VB.TextBox txtArpAddIP 
         Height          =   375
         Left            =   1080
         TabIndex        =   3
         Text            =   "157.54.185.33"
         Top             =   360
         Width           =   1335
      End
      Begin VB.CommandButton cmdArpChange 
         Caption         =   "Do it"
         Height          =   495
         Left            =   4440
         TabIndex        =   2
         Top             =   1080
         Width           =   1335
      End
      Begin VB.Line Line2 
         X1              =   3960
         X2              =   3960
         Y1              =   840
         Y2              =   1680
      End
      Begin VB.Line Line1 
         X1              =   0
         X2              =   6000
         Y1              =   840
         Y2              =   840
      End
      Begin VB.Label Label5 
         Caption         =   "if_addr(optional)"
         Height          =   255
         Left            =   2640
         TabIndex        =   14
         Top             =   960
         Width           =   1335
      End
      Begin VB.Label Label4 
         Caption         =   "inet_addr"
         Height          =   255
         Left            =   1080
         TabIndex        =   13
         Top             =   960
         Width           =   735
      End
      Begin VB.Label Label3 
         Caption         =   "if_addr(optional)"
         Height          =   255
         Left            =   4440
         TabIndex        =   12
         Top             =   120
         Width           =   1215
      End
      Begin VB.Label Label2 
         Caption         =   "eth_addr"
         Height          =   255
         Left            =   2760
         TabIndex        =   11
         Top             =   120
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "inet_addr"
         Height          =   255
         Left            =   1080
         TabIndex        =   10
         Top             =   120
         Width           =   735
      End
   End
   Begin VB.ListBox lstArp 
      Height          =   1425
      Left            =   120
      TabIndex        =   0
      Top             =   2040
      Width           =   6015
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
Dim g_dwDefaultIndex As Long

Function StringToPhysAddr(ByVal strMac As String, bytePhysAddr() As Byte) As Boolean
    Dim tmpstr As String
    Dim Pos1 As Long, Pos2 As Long
    StringToPhysAddr = False
    
    On Error GoTo ErrorPro
    

    Pos1 = 1
    Pos2 = 1
    Pos2 = InStr(1, strMac, "-")
    tmpstr = "&H" & Mid(strMac, Pos1, Pos2 - Pos1)
    bytePhysAddr(0) = CByte(tmpstr)
        
        
    Pos1 = Pos2 + 1
    Pos2 = InStr(Pos1, strMac, "-")
    tmpstr = "&H" & Mid(strMac, Pos1, Pos2 - Pos1)
    bytePhysAddr(1) = CByte(tmpstr)
        
    Pos1 = Pos2 + 1
    Pos2 = InStr(Pos1, strMac, "-")
    tmpstr = "&H" & Mid(strMac, Pos1, Pos2 - Pos1)
    bytePhysAddr(2) = CByte(tmpstr)
    
    Pos1 = Pos2 + 1
    Pos2 = InStr(Pos1, strMac, "-")
    tmpstr = "&H" & Mid(strMac, Pos1, Pos2 - Pos1)
    bytePhysAddr(3) = CByte(tmpstr)
        
    Pos1 = Pos2 + 1
    Pos2 = InStr(Pos1, strMac, "-")
    tmpstr = "&H" & Mid(strMac, Pos1, Pos2 - Pos1)
    bytePhysAddr(4) = CByte(tmpstr)
        
    Pos1 = Pos2 + 1
    tmpstr = "&H" & Mid(strMac, Pos1)
    bytePhysAddr(5) = CByte(tmpstr)
    StringToPhysAddr = True
    Exit Function
ErrorPro:
    StringToPhysAddr = False
    MsgBox "The Mac address format must be like 11-22-aa-bb-bb-dd!"
End Function

Function MyGetIpAddrTable() As Long
    Dim Status As Long, dwActualSize As Long
    Dim fOrder As Boolean
    Dim pIpAddrTable As Long
    
    fOrder = False
    dwActualSize = 0
    MyGetIpAddrTable = 0
    
    Status = GetIpAddrTable(0, dwActualSize, fOrder)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           MsgBox "GetIpAddrTable sizing failed with error " & Status
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

Function PhysAddrToString(PhysAddr() As Byte, PhysAddrLen As Long, strMac As String)
    Dim i As Long
    strMac = ""
    For i = 0 To PhysAddrLen - 1
        strMac = strMac & Hex(PhysAddr(i))
        If i <> PhysAddrLen - 1 Then
            strMac = strMac & "-"
        End If
    Next
End Function

Sub DisplayArpCache(Listx As ListBox)
    Dim pIpNetTable As Long
    Dim dwActualSize As Long
    Dim fOrder As Boolean
    Dim Status As Long
    
    Dim IpNetTableEntry As MIB_IPNETROW
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long

    Dim dwCurrIndex As Long
    
    Dim pIpAddrTable As Long
    Dim szIPAddr As String
    Dim szPrintablePhysAddr As String
    
    Dim tmpstr As String
    Dim tmpstr2 As String
    tmpstr = String(512, 0)
    tmpstr2 = String(256, 0)
    szIPAddr = String(256, 0)
    
    Listx.Clear
   
    pIpAddrTable = MyGetIpAddrTable
    If pIpAddrTable = 0 Then
        MsgBox "Can't get IpAddr Table"
        Exit Sub
    End If
   
    fOrder = True
    dwActualSize = 0
    
    Status = GetIpNetTable(0, dwActualSize, fOrder)
    If Status <> 0 Then
        If Status <> ERROR_INSUFFICIENT_BUFFER Then
           Listx.AddItem "GetIpNetTable sizing failed with error " & Status
           GlobalFree pIpAddrTable
           Exit Sub
        End If
    End If
    
    pIpNetTable = GlobalAlloc(GMEM_FIXED, dwActualSize)
    If pIpNetTable = 0 Then
        Listx.AddItem "GlobalAlloc sizing failed "
        GlobalFree pIpAddrTable
        Exit Sub
    End If
        
    Status = GetIpNetTable(pIpNetTable, dwActualSize, fOrder)
    If Status <> 0 Then
        Listx.AddItem "GetIpNetTable sizing failed with error " & Status & ". Err# is " & Err.LastDllError
        GlobalFree pIpNetTable
        GlobalFree pIpAddrTable
        Exit Sub
    End If
    
    pWorkingPointer = pIpNetTable
    CopyMemory dwNumEntry, ByVal pWorkingPointer, 4
    pWorkingPointer = pWorkingPointer + 4
    
    ZeroMemory IpNetTableEntry, Len(IpNetTableEntry)
    CopyMemory IpNetTableEntry, ByVal pWorkingPointer, Len(IpNetTableEntry)
    dwCurrIndex = IpNetTableEntry.dwIndex
    g_dwDefaultIndex = dwCurrIndex
    
    If InterfaceIdxToInterfaceIp(pIpAddrTable, dwCurrIndex, szIPAddr) = True Then
        Listx.AddItem szIPAddr & " on Interface " & dwCurrIndex
        Listx.AddItem "    IP Address      " & vbTab & "Physical Address " & vbTab & "Type"
        tmpstr = "    "
    Else
        Listx.AddItem "Error: Could not convert Interface number " & dwCurrIndex & " to IP Address"
        GlobalFree pIpNetTable
        GlobalFree pIpAddrTable
        Exit Sub
    End If
    
    For i = 1 To dwNumEntry
        
        ZeroMemory IpNetTableEntry, Len(IpNetTableEntry)
        CopyMemory IpNetTableEntry, ByVal pWorkingPointer, Len(IpNetTableEntry)
        pWorkingPointer = pWorkingPointer + Len(IpNetTableEntry)
        If dwCurrIndex <> IpNetTableEntry.dwIndex Then
            dwCurrIndex = IpNetTableEntry.dwIndex
            If InterfaceIdxToInterfaceIp(pIpAddrTable, dwCurrIndex, szIPAddr) = True Then
                Listx.AddItem szIPAddr & " on Interface " & dwCurrIndex
                Listx.AddItem "    IP Address      " & vbTab & "Physical Address " & vbTab & "Type"
                tmpstr = "    "
            Else
                Listx.AddItem "Error: Could not convert Interface number " & dwCurrIndex & " to IP Address"
                GlobalFree pIpNetTable
                GlobalFree pIpAddrTable
                Exit Sub
            End If
        End If
        PhysAddrToString IpNetTableEntry.bPhysAddr, IpNetTableEntry.dwPhysAddrLen, szPrintablePhysAddr
        
        tmpstr2 = String(256, 0)
        lstrcpy tmpstr2, inet_ntoa(IpNetTableEntry.dwAddr)
        tmpstr2 = Left(tmpstr2, InStr(tmpstr2, Chr(0)) - 1)
        
        tmpstr = tmpstr & tmpstr2 & String(16 - Len(tmpstr2), " ") & vbTab & _
            szPrintablePhysAddr & String(17 - Len(szPrintablePhysAddr), " ") & vbTab
            
        Select Case IpNetTableEntry.dwType
             Case 1
                tmpstr = tmpstr & "other"
            Case 2
                tmpstr = tmpstr & "invalidated"
            Case 3
                tmpstr = tmpstr & "dynamic"
            Case 4
                tmpstr = tmpstr & "static"
            Case Else
                tmpstr = tmpstr & "invalidType"
            
        End Select
        Listx.AddItem tmpstr
        tmpstr = "    "
        
    Next
    
    GlobalFree pIpAddrTable
    GlobalFree pIpNetTable
    
End Sub

Private Sub cmdArpChange_Click()
    Dim dwInetAddr As Long
    Dim dwStatus As Long
    Dim arpEntry As MIB_IPNETROW
    Dim pWorkingPointer As Long
    Dim dwNumEntry As Long
    Dim i As Long
    Dim IpAddrRowEntry As MIB_IPADDRROW
    
    Dim tmpstr As String
    Dim Pos1 As Long
    Dim Pos2 As Long
     
    On Error GoTo ErrorPro
    
    If optArpAdd.Value = True Then
        If txtArpAddIP.Text = "" Or txtArpAddMac = "" Then
            MsgBox "IP and MAC are required"
            Exit Sub
        End If
        dwInetAddr = inet_addr(txtArpAddIP.Text)
        If (dwInetAddr = -1) Then
            MsgBox "IpArp: Bad Argument " & txtArpAddIP.Text
            Exit Sub
        End If
        If txtArpAddIF.Text = "" Then
            arpEntry.dwIndex = g_dwDefaultIndex
        Else
            arpEntry.dwIndex = CLng(txtArpAddIF.Text)
        End If
        arpEntry.dwPhysAddrLen = 6
        
        If StringToPhysAddr(txtArpAddMac.Text, arpEntry.bPhysAddr) = False Then
            Exit Sub
        End If
        arpEntry.dwAddr = dwInetAddr
        arpEntry.dwType = MIB_IPNET_TYPE_STATIC
        dwStatus = SetIpNetEntry(arpEntry)
        If (dwStatus <> 0) Then
            MsgBox "IpArp: couldn't add " & txtArpAddIP.Text & ", dwStatus = " & dwStatus & ", Err# is " & Err.LastDllError
        End If
        
    Else
        If txtArpDelIp.Text = "" Then
            MsgBox "IP is required"
            Exit Sub
        End If
        dwInetAddr = inet_addr(txtArpDelIp.Text)
        If (dwInetAddr = -1) Then
            MsgBox "IpArp: Bad Argument " & txtArpDelIp.Text
            Exit Sub
        End If
        If txtArpDelIF.Text = "" Then
            arpEntry.dwIndex = g_dwDefaultIndex
        Else
            arpEntry.dwIndex = CLng(txtArpDelIF.Text)
        End If
        arpEntry.dwAddr = dwInetAddr
        dwStatus = DeleteIpNetEntry(arpEntry)
        If (dwStatus <> 0) Then
                MsgBox "IpArp: couldn't delete " & txtArpDelIp.Text & ", dwStatus = " & dwStatus & ", Err# is " & Err.LastDllError
        End If
    End If
    
    DisplayArpCache lstArp
    Exit Sub
ErrorPro:
    MsgBox "Invalid data type. Check your input."
End Sub

Private Sub Form_Load()
    DisplayArpCache lstArp
End Sub


Private Sub mnuRefresh_Click()
    DisplayArpCache lstArp
End Sub

