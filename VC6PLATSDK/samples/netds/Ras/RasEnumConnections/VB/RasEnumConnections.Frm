VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "RasEnumconnections"
   ClientHeight    =   1995
   ClientLeft      =   3450
   ClientTop       =   3420
   ClientWidth     =   5025
   LinkTopic       =   "Form1"
   ScaleHeight     =   1995
   ScaleWidth      =   5025
   Begin VB.ListBox List1 
      Height          =   450
      Left            =   240
      TabIndex        =   2
      Top             =   600
      Width           =   4455
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Quit"
      Height          =   375
      Left            =   1800
      TabIndex        =   0
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Active RAS connections"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   1440
      TabIndex        =   1
      Top             =   120
      Width           =   2175
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    End
End Sub

Private Sub Form_Load()
    Dim tRasConn As rasconn
    Dim cb As Long
    Dim cConnections As Long
    Dim t_Buff As Long
    Dim t_ptr As Long
    Dim i As Long
    Dim nRet As Long
    
    'Initialize sizes
    cb = LenB(tRasConn) '412
    
    tRasConn.dwSize = cb
    
    ' Allocate input buffer with enough room for at least one structure
    t_Buff = LocalAlloc(LPTR, cb)
    
    If (t_Buff) Then
        ' Copy the initialized structure/type since it already has the dwSize member set
        ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
        ' to CopyMemory because VB passes parameters by reference by default
        Call CopyMemory(ByVal t_Buff, tRasConn, LenB(tRasConn))
        
        ' Call RasEnumConnections API
        nRet = RasEnumConnections(ByVal t_Buff, cb, cConnections)
        
        'Check return value
        If (ERROR_BUFFER_TOO_SMALL = nRet And cb <> 0) Then
            'Since buffer is too small allocate enough space to hold all connections in memory
            Call LocalFree(t_Buff)
            t_Buff = LocalAlloc(LPTR, cb)
        ElseIf (nRet = 0 And cConnections = 0) Then
            Call MsgBox(("No active connections"), , "Attention")
            Call LocalFree(t_Buff)
            Exit Sub
        ElseIf (nRet <> 0) Then
            Call MsgBox("RasEnumConnections returns " & nRet)
            Call LocalFree(t_Buff)
            Exit Sub
        End If
        
        If (t_Buff) Then
            
            If (nRet <> 0) Then
                'Copy the initialized structure/type since it already has the dwSize member set
                ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
                ' to CopyMemory because VB passes parameters by reference by default
                Call CopyMemory(ByVal t_Buff, tRasConn, cb)
            
                nRet = RasEnumConnections(ByVal t_Buff, cb, cConnections)
            End If
            
            If (nRet = 0) Then
                t_ptr = t_Buff
                For i = 1 To cConnections
                    Call CopyMemory(tRasConn, ByVal t_ptr, LenB(tRasConn))
                    
                    'Add each connections to the list box
                    List1.AddItem (ByteToString(tRasConn.szEntryName) & _
                                   " is connected via " & _
                                   ByteToString(tRasConn.szDeviceName))
                                   
                    t_ptr = t_ptr + tRasConn.dwSize
                Next i
            Else
                Call MsgBox(("RasEnumConnections failed: Error = " & nRet), , "Error")
            End If
            
            Call LocalFree(t_Buff)
        End If

    Else
        Call MsgBox("LocalAlloc failed", , "Error")
    End If
    
End Sub
