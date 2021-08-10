VERSION 5.00
Object = "{F5BE8BC2-7DE6-11D0-91FE-00C04FD701A5}#2.0#0"; "AGENTCTL.DLL"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.1#0"; "COMDLG32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "[No character loaded] - Microsoft Character Animation Previewer"
   ClientHeight    =   5385
   ClientLeft      =   150
   ClientTop       =   720
   ClientWidth     =   5580
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   5385
   ScaleWidth      =   5580
   StartUpPosition =   3  'Windows Default
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   4320
      Top             =   3120
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   327680
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Move"
      Enabled         =   0   'False
      Height          =   360
      Index           =   3
      Left            =   4335
      TabIndex        =   18
      Top             =   4770
      Width           =   1170
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Speak"
      Enabled         =   0   'False
      Height          =   360
      Index           =   2
      Left            =   4335
      TabIndex        =   17
      Top             =   2670
      Width           =   1170
   End
   Begin VB.CommandButton Command1 
      Caption         =   "&Play"
      Enabled         =   0   'False
      Height          =   360
      Index           =   0
      Left            =   4335
      TabIndex        =   15
      Top             =   255
      Width           =   1170
   End
   Begin VB.CommandButton Command1 
      Caption         =   "S&top"
      Enabled         =   0   'False
      Height          =   360
      Index           =   1
      Left            =   4335
      TabIndex        =   16
      Top             =   735
      Width           =   1170
   End
   Begin VB.Frame AnimationFrame 
      Caption         =   "&Animations for"
      Enabled         =   0   'False
      Height          =   2355
      Left            =   60
      TabIndex        =   0
      Top             =   15
      Width           =   4155
      Begin VB.CheckBox OutputStyleOption 
         Caption         =   "Stop &before next action"
         Enabled         =   0   'False
         Height          =   330
         Index           =   1
         Left            =   1995
         TabIndex        =   3
         Top             =   1950
         Value           =   1  'Checked
         Width           =   1995
      End
      Begin VB.CheckBox OutputStyleOption 
         Caption         =   "Play sound &effects"
         Enabled         =   0   'False
         Height          =   330
         Index           =   0
         Left            =   105
         TabIndex        =   2
         Top             =   1950
         Value           =   1  'Checked
         Width           =   1725
      End
      Begin VB.ListBox AnimationListBox 
         Enabled         =   0   'False
         Height          =   1620
         Left            =   90
         Sorted          =   -1  'True
         TabIndex        =   1
         Top             =   240
         Width           =   3900
      End
   End
   Begin VB.Frame SpeechOutputFrame 
      Caption         =   "Speech &Output"
      Enabled         =   0   'False
      Height          =   2085
      Left            =   60
      TabIndex        =   4
      Top             =   2445
      Width           =   4170
      Begin VB.TextBox SpeakText 
         BackColor       =   &H8000000F&
         Enabled         =   0   'False
         Height          =   930
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   5
         Top             =   255
         Width           =   3900
      End
      Begin VB.CheckBox BalloonStyleOption 
         Caption         =   "Display &word balloon"
         Enabled         =   0   'False
         Height          =   285
         Index           =   0
         Left            =   120
         TabIndex        =   6
         Top             =   1290
         Width           =   1935
      End
      Begin VB.CheckBox BalloonStyleOption 
         Caption         =   "Si&ze to text"
         Enabled         =   0   'False
         Height          =   285
         Index           =   3
         Left            =   2895
         TabIndex        =   9
         Top             =   1665
         Width           =   1095
      End
      Begin VB.CheckBox BalloonStyleOption 
         Caption         =   "Auto &pace"
         Enabled         =   0   'False
         Height          =   285
         Index           =   2
         Left            =   1605
         TabIndex        =   8
         Top             =   1665
         Width           =   1215
      End
      Begin VB.CheckBox BalloonStyleOption 
         Caption         =   "A&uto hide"
         Enabled         =   0   'False
         Height          =   300
         Index           =   1
         Left            =   420
         TabIndex        =   7
         Top             =   1650
         Width           =   1200
      End
   End
   Begin VB.Frame PositionFrame 
      Caption         =   "Position"
      Enabled         =   0   'False
      Height          =   720
      Left            =   60
      TabIndex        =   10
      Top             =   4575
      Width           =   4170
      Begin VB.TextBox CharPosn 
         BackColor       =   &H8000000F&
         Enabled         =   0   'False
         Height          =   285
         Index           =   1
         Left            =   1845
         TabIndex        =   14
         Top             =   255
         Width           =   570
      End
      Begin VB.TextBox CharPosn 
         BackColor       =   &H8000000F&
         Enabled         =   0   'False
         Height          =   285
         Index           =   0
         Left            =   375
         TabIndex        =   12
         Top             =   255
         Width           =   570
      End
      Begin VB.Label CharPosnLabel 
         Caption         =   "&Y:"
         Enabled         =   0   'False
         Height          =   300
         Index           =   1
         Left            =   1620
         TabIndex        =   13
         Top             =   300
         Width           =   270
      End
      Begin VB.Label CharPosnLabel 
         Caption         =   "&X:"
         Enabled         =   0   'False
         Height          =   270
         Index           =   0
         Left            =   135
         TabIndex        =   11
         Top             =   300
         Width           =   270
      End
   End
   Begin AgentObjectsCtl.Agent MyAgent 
      Left            =   4920
      Top             =   3120
      _cx             =   847
      _cy             =   847
   End
   Begin VB.Menu FileMenu 
      Caption         =   "&File"
      Begin VB.Menu FileOpen 
         Caption         =   "&Open..."
      End
      Begin VB.Menu FileSep1 
         Caption         =   "-"
      End
      Begin VB.Menu FileExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu HelpMenu 
      Caption         =   "&Help"
      Begin VB.Menu HelpAbout 
         Caption         =   "&About Microsoft Character Animation Previewer"
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Dim Character As IAgentCtlCharacterEx
Dim NewBalloonStyleOption As Integer
Dim CharLoaded As Boolean
Dim IgnoreSizeEvent As Boolean
Dim CurrentIndex As Integer

Const BalloonOn = 1
Const SizeToText = 2
Const AutoHide = 4
Const AutoPace = 8

Private Declare Function GetWindowsDirectory Lib "kernel32" Alias "GetWindowsDirectoryA" (ByVal lpBuffer As String, ByVal nSize As Long) As Long
Sub SetBalloonStyleOptions()
'------------------------------------------------
'-- This subroutine sets the check boxes for the
'-- the word balloon settings
'------------------------------------------------

'-- Check to see if the balloon is on

If Character.Balloon.Style And BalloonOn Then
    BalloonStyleOption(0).Value = 1
Else
    BalloonStyleOption(0).Value = 0
End If

'-- Check to see if Auto-Hide is on

If Character.Balloon.Style And AutoHide Then
    BalloonStyleOption(1).Value = 1
Else
    BalloonStyleOption(1).Value = 0
End If

'-- Check to see if Auto-Pace is on

If Character.Balloon.Style And AutoPace Then
    BalloonStyleOption(2).Value = 1
Else
    BalloonStyleOption(2).Value = 0
End If

'-- Check to see if Size-To-Text is on

If Character.Balloon.Style And SizeToText Then
    BalloonStyleOption(3).Value = 1
Else
    BalloonStyleOption(3).Value = 0
End If


'-- Set the controls based on Advanced Character Options

If Not Character.Balloon.Enabled Then
    BalloonStyleOption(0).Enabled = False
    BalloonStyleOption(1).Enabled = False
    BalloonStyleOption(2).Enabled = False
    BalloonStyleOption(2).Enabled = False
Else
    BalloonStyleOption(0).Enabled = True
    BalloonStyleOption(1).Enabled = True
    BalloonStyleOption(2).Enabled = True
    BalloonStyleOption(2).Enabled = True
End If

End Sub
Function GetWindowsDir() As String
    Dim Temp As String
    Dim Ret As Long
    Const MAX_LENGTH = 145

    Temp = String$(MAX_LENGTH, 0)
    Ret = GetWindowsDirectory(Temp, MAX_LENGTH)
    Temp = Left$(Temp, Ret)
    If Temp <> "" And Right$(Temp, 1) <> "\" Then
        GetWindowsDir = Temp & "\"
    Else
        GetWindowsDir = Temp
    End If
End Function


Private Sub AnimationListBox_Click()

'-- Enable the Play button
Command1(0).Enabled = True

End Sub

Sub EnableControls()
'-----------------------------------
'-- Enable the controls on the page
'-----------------------------------

'-- Enable the Animation List Box
AnimationFrame.Enabled = True
AnimationListBox.Enabled = True


'-- Enable the Stop and Move buttons
Command1(1).Enabled = True
Command1(3).Enabled = True

'-- Enable the Play Sound Effects option only
'-- if enabled in the Advanced Character Options

If MyAgent.AudioOutput.Enabled And MyAgent.AudioOutput.SoundEffects Then
    OutputStyleOption(0).Enabled = True
End If


'-- Enable the Stop Before Play option

OutputStyleOption(1).Enabled = True


'-- Enable the Balloon Style options
BalloonStyleOption(0).Enabled = True
BalloonStyleOption(1).Enabled = True
BalloonStyleOption(2).Enabled = True
BalloonStyleOption(3).Enabled = True


'-- Enable the Speech Text Box
SpeechOutputFrame.Enabled = True
SpeakText.Enabled = True
SpeakText.BackColor = vbWindowBackground


'-- Enable the X,Y position fields
PositionFrame.Enabled = True

CharPosnLabel(0).Enabled = True
CharPosn(0).Enabled = True
CharPosn(0).BackColor = vbWindowBackground

CharPosnLabel(1).Enabled = True
CharPosn(1).Enabled = True
CharPosn(1).BackColor = vbWindowBackground

End Sub

Private Sub AnimationListBox_DblClick()

Command1_Click (0)

End Sub

Private Sub AnimationListBox_GotFocus()
'-----------------------------------------------
'-- Make certain that the Move button isn't left
'-- as the default even if there is no selection
'-- in the list
'-----------------------------------------------
Command1(3).Default = False

'-----------------------------------------------
'-- Make certain that the Play button is the
'-- default button when the list box has focus.
'-----------------------------------------------
Command1(0).Default = True

End Sub

Private Sub BalloonStyleOption_GotFocus(Index As Integer)
'-----------------------------------------------
'-- If a balloon style option gets the focus
'-- and the Speak button is enabled, make the
'-- the Speak button the default button
'-----------------------------------------------
If Command1(2).Enabled Then
    Command1(2).Default = True
End If

End Sub

Private Sub CharPosn_Change(Index As Integer)
'-------------------------------------------
'-- If X or Y is empty then disable
'-- disable the Move button
'-------------------------------------------
If CharPosn(0).Text = "" Or CharPosn(1).Text = "" Then
    Command1(3).Enabled = False
    Command1(3).Default = False
Else
    Command1(3).Enabled = True
    Command1(3).Default = True
End If

'-- Check to determine if we get numeric input for
'-- the position, if not goto BadInput
On Error GoTo BadInput
PosnInput = CInt(CharPosn(Index).Text)
Exit Sub

BadInput:
    Beep
    CharPosn(Index).SelStart = 0
    CharPosn(Index).SelLength = Len(CharPosn(Index).Text)

End Sub

Private Sub FileExit_Click()

Set Character = Nothing
MyAgent.Characters.Unload "CharacterID"
End

End Sub

Private Sub HelpAbout_Click()
frmAbout.Show
End Sub

Private Sub MyAgent_AgentPropertyChange()
'-----------------------------------------------------
'-- Check to see if the user changed settings in
'-- Advanced Character Options
'-----------------------------------------------------

'-- Check to see if the user changed
'-- Play Character Sound Effects
'-- in Advanced Character Options
If Not MyAgent.AudioOutput.SoundEffects Then
    OutputStyleOption(0).Enabled = False
Else
    OutputStyleOption(0).Enabled = True
End If


'-- Check to see if the user changed
'-- Display Spoken Output In Word Balloon option
'-- in Advanced Character Options
If Not Character.Balloon.Enabled Then
    BalloonStyleOption(0).Enabled = False
    BalloonStyleOption(1).Enabled = False
    BalloonStyleOption(2).Enabled = False
    BalloonStyleOption(3).Enabled = False
    
Else
    BalloonStyleOption(0).Enabled = True
    BalloonStyleOption(1).Enabled = True
    BalloonStyleOption(2).Enabled = True
    BalloonStyleOption(3).Enabled = True
    
End If

End Sub

Private Sub MyAgent_Command(ByVal UserInput As Object)
'-----------------------------------------------------
'-- If the user selects the Advanced Character Options
'-- command in the character's pop-up menu
'-- make the window visible
'-----------------------------------------------------

If UserInput.Name = "AdvCharOptions" Then
    MyAgent.PropertySheet.Visible = True
End If

End Sub

Private Sub MyAgent_DragComplete(ByVal CharacterID As String, ByVal Button As Integer, ByVal Shift As Integer, ByVal X As Integer, ByVal Y As Integer)
'-----------------------------------------------------
'-- If the user drags the character
'-- update the character position fields
'-----------------------------------------------------

CharPosn(0) = Character.Left
CharPosn(1) = Character.Top

End Sub

Private Sub OutputStyleOption_Click(Index As Integer)
'-----------------------------------------------------
'-- If the Play Sound Effects option is changed
'-- set the character's output option
'-----------------------------------------------------

If Index = 0 Then
    If OutputStyleOption(0).Value Then
        Character.SoundEffectsOn = True
    Else
        Character.SoundEffectsOn = False
    End If
   
End If

End Sub

Private Sub BalloonStyleOption_Click(Index As Integer)
'-----------------------------------------------------
'-- When the user changes a balloon style option
'-- update the character's word balloon settings
'-----------------------------------------------------

Select Case Index

Case 0 '-- The balloon display option
    If BalloonStyleOption(0).Value = 0 Then
        Character.Balloon.Style = Character.Balloon.Style And (Not BalloonOn)
        BalloonStyleOption(1).Enabled = False
        BalloonStyleOption(2).Enabled = False
        BalloonStyleOption(3).Enabled = False
    Else
        Character.Balloon.Style = Character.Balloon.Style Or BalloonOn
        BalloonStyleOption(1).Enabled = True
        BalloonStyleOption(2).Enabled = True
        BalloonStyleOption(3).Enabled = True
    End If
    
Case 1 '-- The Auto-Hide option
    If BalloonStyleOption(1).Value = 0 Then
        Character.Balloon.Style = Character.Balloon.Style And (Not AutoHide)
    Else
        Character.Balloon.Style = Character.Balloon.Style Or AutoHide
    End If
    
Case 2 '-- The Auto-Pace option
    If BalloonStyleOption(2).Value = 0 Then
        Character.Balloon.Style = Character.Balloon.Style And (Not AutoPace)
    Else
        Character.Balloon.Style = Character.Balloon.Style Or AutoPace
    End If
    
Case 3 '-- The Size-To-Text option
    If BalloonStyleOption(3).Value = 0 Then
        Character.Balloon.Style = Character.Balloon.Style And (Not SizeToText)
    Else
        Character.Balloon.Style = Character.Balloon.Style Or SizeToText
    End If
    
End Select

End Sub

Private Sub Command1_Click(Index As Integer)
'-------------------------------------------------
'-- This routine processes the Play, Stop, Speak,
'-- and Move buttons
'-------------------------------------------------

'-- If Stop Before Play is set, stop the character
'-- before the next request
If OutputStyleOption(1).Value Then
    Character.Stop
End If

Select Case Index

Case 0 '-- The Play button was clicked, play an animation

    '-- Play the animaton selected in the list box
    Character.Play AnimationListBox.List(AnimationListBox.ListIndex)

Case 1 '-- The Stop button was chosen, stop the animation
    
    Character.Stop

Case 2 '-- The Speak button was chosen
    
    '-- Speak the text if there is text
    If Not SpeakText.Text = "" Then
        Character.Speak SpeakText.Text
    End If
    
    SpeakText.SetFocus
    SpeakText.SelStart = 0
    SpeakText.SelLength = Len(SpeakText.Text)
    
    
Case 3 '-- The Move button was chosen, move to the X,Y position
    
    Character.MoveTo CInt(CharPosn(0).Text), CInt(CharPosn(1).Text)
        
    CharPosn(CurrentIndex).SetFocus
    CharPosn(CurrentIndex).SelStart = 0
    CharPosn(CurrentIndex).SelLength = Len(CharPosn(CurrentIndex).Text)


End Select

End Sub

Private Sub FileOpen_Click()
    
'-- Set a flag to track success
OpenSuccess = False
        
CommonDialog1.CancelError = True

On Error GoTo ErrHandler
    
CommonDialog1.Flags = cdlOFNHideReadOnly

'-- Get the Windows directory name
Dim DirName As String
DirName = GetWindowsDir()

'-- Append the Agent Chars subdirectory
CommonDialog1.InitDir = DirName + "msagent\chars"

'-- Add the filter
CommonDialog1.Filter = "Microsoft Agent Characters (*.acs)|*.acs"
CommonDialog1.FilterIndex = 1

'-- Show the Open dialog
CommonDialog1.ShowOpen
    
'--Unload the previous character
On Error Resume Next
Set Character = Nothing
MyAgent.Characters.Unload "CharacterID"
    
'-- Load the new character
On Error GoTo ErrHandler
MyAgent.Characters.Load "CharacterID", CommonDialog1.filename

OpenSuccess = True

Set Character = MyAgent.Characters("CharacterID")

Form1.Caption = Character.Name + " - Microsoft Character Animation Previewer"


'-- Set the character loaded flag
CharLoaded = True

'-- Set the character's language
Character.LanguageID = &H409

'-- Update the caption for the animation list box
AnimationFrame.Caption = "&Animations for " + Character.Name

'-- Disable the Play button to avoid trying to play a null animation selection
Command1(0).Enabled = False

'-- Load the character's animation into the list box
AnimationListBox.Clear
For Each AnimationName In Character.AnimationNames
        AnimationListBox.AddItem AnimationName
Next
   
'-- Move the character to starting position
Character.Left = (Form1.Left + 3450) / Screen.TwipsPerPixelX
Character.Top = (Form1.Top + 900) / Screen.TwipsPerPixelY

'-- Show the character
Character.Show

'-- Update the X,Y position fields with the character's
'-- current position
CharPosn(0).Text = CStr(Character.Left)
CharPosn(1).Text = CStr(Character.Top)

'-- Update the state of the balloon style options
SetBalloonStyleOptions

'-- Initialize the pop-up menu commands
InitPopupMenuCmds
   
'-- Update the state of the controls to match the
'-- character's settings
EnableControls

AnimationListBox.SetFocus

Exit Sub
    
ErrHandler:
    If (Err.Number <> cdlCancel) Then
        If (OpenSuccess = False) Then
            MsgBox "There was an error opening the file " & CommonDialog1.filename
            
        End If

        Set Character = Nothing
    
    End If

End Sub
Private Sub Form_Load()
'----------------------------------------------------------
'-- When the form loads, set the IgnoreSizeEvent flag
'-- (used to differentiate when the Character Animation
'-- Previewer window is restored), set the CharLoaded flag
'-- (used to track when a character is loaded),
'-- and set the initial state of the status bar.
'----------------------------------------------------------
IgnoreSizeEvent = True

CharLoaded = False

End Sub
Sub InitPopupMenuCmds()
'-----------------------------------------------------
'-- Add a command to the character to provide access
'-- to the Advanced Character Options
'-----------------------------------------------------
Character.Commands.RemoveAll
Character.Commands.Add "AdvCharOptions", "&Advanced Character Options"

End Sub
Private Sub Form_Resize()
'-------------------------------------------------------
'-- This routines hides or shows the character when the
'-- Character Animation Previewer window is mininized or
'-- restored

If IgnoreSizeEvent Then
    IgnoreSizeEvent = False
    Exit Sub
End If

If CharLoaded Then
    If Form1.WindowState = vbMinimized Then
        Character.Hide True
    ElseIf Form1.WindowState = vbNormal Then
        Character.Show True
    End If
End If

End Sub
Private Sub SpeakText_Change()
'---------------------------------------------------
'-- The routine makes certain that there is text to
'-- speak before enabling the Speak button
'---------------------------------------------------

If SpeakText.Text = "" Then
    Command1(2).Enabled = False
    Command1(2).Default = False
Else
    Command1(2).Enabled = True
    Command1(2).Default = True
End If

End Sub


Private Sub CharPosn_GotFocus(Index As Integer)
'--------------------------------------------------
'-- This routine handles what happens when the
'-- X,Y position fields get the focus
'--------------------------------------------------

'-- Make the Move button the default button
Command1(3).Default = True

'-- Select the text in the field
CharPosn(Index).SelStart = 0
CharPosn(Index).SelLength = Len(CharPosn(Index).Text)

'-- Set a flag to remember the text field we are in
CurrentIndex = Index

End Sub

Private Sub SpeakText_GotFocus()
'--------------------------------------------------
'-- If the user clicks on this text box and
'-- it's enabled make The Speak button the
'-- default button
'--------------------------------------------------
If Command1(2).Enabled Then
    Command1(2).Default = True
    SpeakText.SelStart = 0
    SpeakText.SelLength = Len(SpeakText.Text)
End If

End Sub
