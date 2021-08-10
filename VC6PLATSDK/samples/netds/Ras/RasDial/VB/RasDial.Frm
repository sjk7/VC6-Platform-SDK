VERSION 5.00
Begin VB.Form frmRasDial 
   Caption         =   "RasDial"
   ClientHeight    =   3330
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7410
   LinkTopic       =   "Form1"
   ScaleHeight     =   3330
   ScaleWidth      =   7410
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Quit 
      Caption         =   "Quit"
      Height          =   375
      Left            =   5160
      TabIndex        =   12
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton HangUp 
      Caption         =   "Hang Up"
      Height          =   375
      Left            =   3120
      TabIndex        =   11
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton Dial 
      Caption         =   "Dial"
      Height          =   375
      Left            =   1080
      TabIndex        =   10
      Top             =   2760
      Width           =   1215
   End
   Begin VB.TextBox strDomain 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   1800
      TabIndex        =   4
      Top             =   2160
      Width           =   1215
   End
   Begin VB.TextBox strPassword 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      IMEMode         =   3  'DISABLE
      Left            =   1800
      PasswordChar    =   "*"
      TabIndex        =   3
      Top             =   1680
      Width           =   1215
   End
   Begin VB.TextBox strUserName 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   1800
      TabIndex        =   2
      Text            =   "test"
      Top             =   1200
      Width           =   1215
   End
   Begin VB.TextBox strCallBackNumber 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   1800
      TabIndex        =   1
      Top             =   720
      Width           =   1215
   End
   Begin VB.TextBox strPhoneNumber 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Left            =   1800
      TabIndex        =   0
      Text            =   "12345"
      Top             =   240
      Width           =   1215
   End
   Begin VB.Label Label8 
      Caption         =   "Connection Status"
      Height          =   255
      Left            =   3480
      TabIndex        =   18
      Top             =   240
      Width           =   1335
   End
   Begin VB.Label Label7 
      Caption         =   "Server Ip Address"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3480
      TabIndex        =   17
      Top             =   2040
      Width           =   1695
   End
   Begin VB.Label Label6 
      Caption         =   "Client Ip Address"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3480
      TabIndex        =   16
      Top             =   1200
      Width           =   1575
   End
   Begin VB.Label lblServerIp 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5160
      TabIndex        =   15
      Top             =   2040
      Width           =   1935
   End
   Begin VB.Label lblClientIp 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5160
      TabIndex        =   14
      Top             =   1200
      Width           =   1935
   End
   Begin VB.Label lblConnect 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "Not Connected"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5160
      TabIndex        =   13
      Top             =   240
      Width           =   1935
   End
   Begin VB.Label Label5 
      Caption         =   "Domain"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   2160
      Width           =   1335
   End
   Begin VB.Label Label4 
      Caption         =   "Password"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   8
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Label Label3 
      Caption         =   "Username"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   7
      Top             =   1200
      Width           =   1335
   End
   Begin VB.Label Label2 
      Caption         =   "Callback Number"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   6
      Top             =   720
      Width           =   1575
   End
   Begin VB.Label Label1 
      Caption         =   "Phone Number"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   240
      Width           =   1575
   End
End
Attribute VB_Name = "frmRasDial"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'
'       RAS API's used:
'           RasDial
'           RasHangUp
'           RasGetProjectionInfo
'

Option Explicit
Option Base 0

'Global declaration
Dim hRasConn As Long

'Do the RasDial
Private Sub Dial_Click()
    Dim lngnRet As Long
    Dim strIpAddress(15) As Byte
    Dim strServerIpAddress(15) As Byte
    Dim i As Integer
    
    Dial.Enabled = False
    ' Dial out
    lngnRet = fcnRasDial(strPhoneNumber, strCallBackNumber, _
                         strUserName, strPassword, strDomain, _
                         hRasConn)
    If lngnRet <> 0 Then
        ' Handle the RasDial error
        MsgBox fcnRasErrorString(lngnRet), , _
                "RasDial Error: " & lngnRet
    Else
        ' No error, RasDial succeeded
        HangUp.Enabled = True
        Dial.Enabled = False
        lblConnect.Caption = "Connected to " & strPhoneNumber
        
        ' Get the IP addresses using RasGetProjectionInfo
        lngnRet = fcnRasGetProjectionInfo(hRasConn, strIpAddress(), strServerIpAddress())
        If lngnRet <> 0 Then
        ' Handle the RasGetProjectionInfo error
            MsgBox fcnRasErrorString(lngnRet), , _
                "RasGetProjectionInfo Error: " & lngnRet
        Else
        ' No error, RasGetProjectionInfo succeeded
            For i = 0 To 15
                lblClientIp.Caption = lblClientIp.Caption & Chr(strIpAddress(i))
                lblServerIp.Caption = lblServerIp.Caption & Chr(strServerIpAddress(i))
            Next i
        End If
    End If
End Sub

'Initialize the form
Private Sub Form_Load()
    HangUp.Enabled = False
    Dial.Enabled = False
End Sub

'Hang Up
Private Sub HangUp_Click()
    Dim lngnRet As Long
    
    HangUp.Enabled = False
    lngnRet = fcnRasHangUp(hRasConn)
    If lngnRet <> 0 Then
        MsgBox fcnRasErrorString(lngnRet), , _
                "Hang up Error:" & lngnRet
    End If
    
    ' Clean up the various text boxes and labels
    lblConnect.Caption = "Not Connected"
    lblClientIp.Caption = ""
    lblServerIp.Caption = ""
    strPhoneNumber = ""
    strCallBackNumber = ""
    strUserName = ""
    strPassword = ""
    strDomain = ""
    Dial.Enabled = False
End Sub

'Quit
Private Sub Quit_Click()
    End
End Sub


Private Sub strPhoneNumber_Change()
    Dial.Enabled = True
End Sub
