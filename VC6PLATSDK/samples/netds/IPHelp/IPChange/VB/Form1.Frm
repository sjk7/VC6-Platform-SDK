VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "IPChange"
   ClientHeight    =   3570
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   8445
   LinkTopic       =   "Form1"
   ScaleHeight     =   3570
   ScaleWidth      =   8445
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame IPChangeFrame 
      Caption         =   "IPChange"
      Height          =   1455
      Left            =   120
      TabIndex        =   1
      Top             =   120
      Width           =   8055
      Begin VB.CommandButton cmdIPChange 
         Caption         =   "Do it"
         Height          =   375
         Left            =   4200
         TabIndex        =   12
         Top             =   960
         Width           =   975
      End
      Begin VB.TextBox txtIndexToAdd 
         Height          =   375
         Left            =   1440
         TabIndex        =   11
         Top             =   360
         Width           =   1215
      End
      Begin VB.TextBox txtMaskToAdd 
         Height          =   375
         Left            =   5040
         TabIndex        =   10
         Text            =   "255.0.0.0"
         Top             =   360
         Width           =   1335
      End
      Begin VB.TextBox txtIPToAdd 
         Height          =   375
         Left            =   2880
         TabIndex        =   9
         Text            =   "157.55.80.9"
         Top             =   360
         Width           =   1335
      End
      Begin VB.TextBox txtCxtToDel 
         Height          =   375
         Left            =   1800
         TabIndex        =   5
         Top             =   960
         Width           =   735
      End
      Begin VB.OptionButton optIPChangeDelete 
         Caption         =   "Delete"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   960
         Width           =   855
      End
      Begin VB.OptionButton optIPChangeAdd 
         Caption         =   "Add"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Value           =   -1  'True
         Width           =   735
      End
      Begin VB.Line Line2 
         X1              =   3240
         X2              =   3240
         Y1              =   840
         Y2              =   1440
      End
      Begin VB.Label Label4 
         Caption         =   "Subnet Mask"
         Height          =   255
         Left            =   5040
         TabIndex        =   8
         Top             =   120
         Width           =   975
      End
      Begin VB.Label Label3 
         Caption         =   "IP"
         Height          =   255
         Left            =   2880
         TabIndex        =   7
         Top             =   120
         Width           =   495
      End
      Begin VB.Label Label2 
         Caption         =   "On this Index"
         Height          =   255
         Left            =   1440
         TabIndex        =   6
         Top             =   120
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "Context:"
         Height          =   255
         Left            =   1200
         TabIndex        =   4
         Top             =   960
         Width           =   975
      End
      Begin VB.Line Line1 
         X1              =   120
         X2              =   6840
         Y1              =   840
         Y2              =   840
      End
   End
   Begin VB.ListBox lstIPChange 
      Height          =   1620
      Left            =   120
      TabIndex        =   0
      Top             =   1680
      Width           =   8055
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

Sub DisplayIPChangeAdapter(Listx As ListBox)
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
    Dim AdapterInfoBuffer() As Byte

    Dim tmpStr As String
    Dim tmpStr2 As String
    tmpStr = String(512, 0)
    tmpStr2 = String(256, 0)
   
    Listx.Clear
    AdapterInfoSize = 0
    error = GetAdaptersInfo(ByVal 0&, AdapterInfoSize)
    If error <> 0 Then
        If error <> ERROR_BUFFER_OVERFLOW Then
           MsgBox "GetAdaptersInfo sizing failed with error " & error
           Exit Sub
        End If
    End If
    ReDim AdapterInfoBuffer(AdapterInfoSize - 1)
    AdapterInfoBuffer(AdapterInfoSize - 1) = 0 'make sure memory is committed.


 ' Get actual adapter information
   error = GetAdaptersInfo(AdapterInfoBuffer(0), AdapterInfoSize)
   If error <> 0 Then
      MsgBox "GetAdaptersInfo failed with error " & error & ", Err# is " & Err.LastDllError
      Exit Sub
   End If
   
   'Allocate memory
   CopyMemory AdapterInfo, AdapterInfoBuffer(0), Len(AdapterInfo)
   pAdapt = AdapterInfo.Next
   Listx.AddItem "Adapter         " & vbTab & "MAC Address        " & vbTab & "Index           " _
            & vbTab & "Context " & vbTab & "IP Address      " & vbTab & "Subnet Mask     "
   
   Do
      tmpStr = ""
      CopyMemory Buffer2, AdapterInfo, Len(Buffer2)
      tmpStr2 = Left(Buffer2.Description, 14) 'limit 14 chars
      tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
      
      PhysicalAddress = ""
      For i = 0 To Buffer2.AddressLength - 1
          PhysicalAddress = PhysicalAddress & Hex(Buffer2.Address(i))
          If i < Buffer2.AddressLength - 1 Then
             PhysicalAddress = PhysicalAddress & "-"
          End If
      Next
      tmpStr2 = Left(PhysicalAddress, 17) 'limit 14 chars
      tmpStr = tmpStr & tmpStr2 & String(18 - Len(tmpStr2), " ") & vbTab

      tmpStr2 = Buffer2.Index
      tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
      
      tmpStr2 = Buffer2.IpAddressList.Context
      tmpStr = tmpStr & tmpStr2 & String(8 - Len(tmpStr2), " ") & vbTab
                  
      tmpStr2 = Buffer2.IpAddressList.IpAddress
      tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
      tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
      
      tmpStr2 = Buffer2.IpAddressList.IpMask
      tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
      tmpStr = tmpStr & tmpStr2
      
      Listx.AddItem tmpStr
      pAddrStr = Buffer2.IpAddressList.Next
      Do While pAddrStr <> 0
         If pAddrStr <> 0 Then
            CopyMemory Buffer2.IpAddressList, ByVal pAddrStr, Len(Buffer2.IpAddressList)
         End If
         
         tmpStr = ""
         tmpStr = String(16, " ") & vbTab & String(16, " ") & vbTab & String(16, " ") & vbTab
         CopyMemory Buffer, Buffer2.IpAddressList, Len(Buffer)
         
         tmpStr2 = Buffer.Context
         tmpStr = tmpStr & tmpStr2 & String(8 - Len(tmpStr2), " ") & vbTab
         
         tmpStr2 = Buffer.IpAddress
         tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
         tmpStr = tmpStr & tmpStr2 & String(16 - Len(tmpStr2), " ") & vbTab
        
         tmpStr2 = Buffer.IpMask
         tmpStr2 = Left(tmpStr2, InStr(tmpStr2, Chr(0)) - 1)
         tmpStr = tmpStr & tmpStr2
        
         Listx.AddItem tmpStr
         
         pAddrStr = Buffer.Next
    Loop
    
    pAdapt = Buffer2.Next
    If pAdapt <> 0 Then
        CopyMemory AdapterInfo, ByVal pAdapt, Len(AdapterInfo)
    End If
   Loop While pAdapt <> 0

End Sub
Private Sub Command2_Click()
    Dim Status As Long, dwOutBufLen As Long
    Dim pIfTable As Long
    Dim i As Long
    Dim curIndex As Long
    Dim pWorkingPointer As Long
    Dim NumAdapters As Long
    Dim curAdapter As IP_ADAPTER_INDEX_MAP
    Dim bMatch As Boolean
    
    
    If txtIndex.Text = "" Then
        MsgBox "Please enter an adapter index in the Adapter Index box!"
        Exit Sub
    End If
    
    curIndex = CLng(txtIndex.Text)
    
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
            Exit For
        End If
    Next
    
    If bMatch = False Then
        MsgBox "You might have entered an invalid adapter index!"
    End If

    GlobalFree pIfTable

End Sub

Private Sub cmdIPChange_Click()
    Dim NewIP As Long, NewMask As Long, Index As Long, NTEContext As Long, NTEInstance As Long, Context As Long
    Dim dwStatus As Long
    On Error GoTo ErrorPro
    
    If optIPChangeAdd.Value = True Then
        NewIP = inet_addr(txtIPToAdd.Text)
        If (NewIP = -1) Then
            MsgBox "IpChange: Bad IP " & txtIPToAdd.Text
            Exit Sub
        End If
        NewMask = inet_addr(txtMaskToAdd.Text)
        If (NewMask = -1 And txtMaskToAdd.Text <> "255.255.255.255") Then
            MsgBox "IpChange: Bad Mask " & txtMaskToAdd.Text
            Exit Sub
        End If
        Index = CLng(txtIndexToAdd.Text)
        dwStatus = AddIPAddress(NewIP, NewMask, Index, NTEContext, NTEInstance)
        If dwStatus <> 0 Then
            MsgBox "AddIPAddress failed with error " & dwStatus & ", " & NTEContext & ", Err# is " & Err.LastDllError
        End If
    Else
        Context = CLng(txtCxtToDel.Text)
        dwStatus = DeleteIPAddress(Context)
        If dwStatus <> 0 Then
            MsgBox "AddIPAddress failed with error " & dwStatus & ", Err# is " & Err.LastDllError
        End If
    End If
    DisplayIPChangeAdapter lstIPChange
    Exit Sub
ErrorPro:
    MsgBox "Invalid Data type. Check your inputs."
End Sub

Private Sub Form_Load()
    TCPIPStartup
    DisplayIPChangeAdapter lstIPChange
End Sub

Private Sub Form_Unload(Cancel As Integer)
    TCPIPShutDown
End Sub


Private Sub mnuRefresh_Click()
    DisplayIPChangeAdapter lstIPChange
End Sub
