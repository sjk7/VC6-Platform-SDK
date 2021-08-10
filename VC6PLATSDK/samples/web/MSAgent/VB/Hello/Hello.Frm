VERSION 5.00
Object = "{F5BE8BC2-7DE6-11D0-91FE-00C04FD701A5}#2.0#0"; "AgentCtl.dll"
Begin VB.Form Form1 
   Caption         =   "Hello, World"
   ClientHeight    =   1680
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   1680
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox TextBox 
      Appearance      =   0  'Flat
      Height          =   615
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   1
      ToolTipText     =   "Type something in here for the Genie to say, then press the Say it! button"
      Top             =   120
      Width           =   4335
   End
   Begin VB.CommandButton Button 
      Caption         =   "Say it!"
      Height          =   495
      Left            =   1920
      TabIndex        =   0
      ToolTipText     =   "Type some text into the text box, then press this button to hear Genie say it"
      Top             =   960
      Width           =   1215
   End
   Begin AgentObjectsCtl.Agent Agent1 
      Left            =   240
      Top             =   960
      _cx             =   847
      _cy             =   847
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim Genie As IAgentCtlCharacterEx
Const DATAPATH = "genie.acs"


Private Sub Form_Load()
    Agent1.Characters.Load "Genie", DATAPATH
    Set Genie = Agent1.Characters("Genie")
    Genie.LanguageID = &H409
    TextBox.Text = "Hello World!"
End Sub

Private Sub Button_Click()
    Genie.Show
    Genie.Speak TextBox.Text
    Genie.Hide
End Sub



