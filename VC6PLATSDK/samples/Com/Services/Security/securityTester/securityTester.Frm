VERSION 5.00
Begin VB.Form frmSecurityTester 
   Caption         =   "Security Tester"
   ClientHeight    =   4365
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5085
   LinkTopic       =   "Form1"
   ScaleHeight     =   4365
   ScaleWidth      =   5085
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton cmdVJAre 
      Caption         =   "VJ - Are You an Administrator?"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   1515
      TabIndex        =   6
      Top             =   2640
      Width           =   2055
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   1515
      TabIndex        =   5
      Top             =   3480
      Width           =   2055
   End
   Begin VB.CommandButton cmdVCAre 
      Caption         =   "VC - Are You an Administrator?"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   2655
      TabIndex        =   3
      Top             =   1800
      Width           =   2055
   End
   Begin VB.CommandButton cmdVCWho 
      Caption         =   "VC - Who is logged on?"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   375
      TabIndex        =   2
      Top             =   1800
      Width           =   2055
   End
   Begin VB.CommandButton cmdVBAre 
      Caption         =   "VB - Are You an Administrator?"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   2655
      TabIndex        =   1
      Top             =   960
      Width           =   2055
   End
   Begin VB.CommandButton cmdVBWho 
      Caption         =   "VB - Who is Logged on?"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   375
      TabIndex        =   0
      Top             =   960
      Width           =   2055
   End
   Begin VB.Label Label1 
      Caption         =   "Click each button to test one of the Security Methods"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   15.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   360
      TabIndex        =   4
      Top             =   120
      Width           =   4215
   End
End
Attribute VB_Name = "frmSecurityTester"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim obj     As VBSecuritySampleClass
Dim objvc   As IVCSecuritySampleClass
Dim objvj   As VJSecuritySampleClass_Dispatch


Private Sub cmdExit_Click()

    End
    
End Sub

Private Sub cmdVBWho_Click()

    MsgBox obj.WhoAmI

End Sub


Private Sub cmdVBAre_Click()
    Dim x As Integer
    x = obj.AmIAnAdministrator
        
    If x = 0 Then MsgBox ("Return is '0': You are not an Administrator")
    If x = 1 Then MsgBox ("Return is '1': You are an Administrator")
    If x = 2 Then MsgBox ("Return is '2': There is an error")
    If x = 3 Then MsgBox ("Return is '3': Can't find Administrator role")
        
End Sub

Private Sub cmdVCWho_Click()

    MsgBox objvc.WhoAmI
        
End Sub

Private Sub cmdVCAre_Click()

    Dim y As Integer
    y = objvc.AmIAnAdministrator

    If y = 0 Then MsgBox ("Return is '0': You are not an Administrator")
    If y = 1 Then MsgBox ("Return is '1': You are an Administrator")
    If y = 2 Then MsgBox ("Return is '2': There is an error")
    If y = 3 Then MsgBox ("Return is '3': Can't find Administrator role")
        
End Sub

Private Sub cmdVJAre_Click()

    Dim y As Integer
    z = objvc.AmIAnAdministrator

    If z = 0 Then MsgBox ("Return is '0': You are not an Administrator")
    If z = 1 Then MsgBox ("Return is '1': You are an Administrator")
    If z = 2 Then MsgBox ("Return is '2': There is an error or Security is not enabled")
        
End Sub

Private Sub Form_Load()

    Set obj = CreateObject("VBSecuritySample.VBSecuritySampleClass")
    Set objvc = CreateObject("VCSecuritySampleClass.VCSecuritySampleClass.1")
    Set objvj = CreateObject("VJSecuritySample.VJSecuritySampleClass")
       
End Sub
