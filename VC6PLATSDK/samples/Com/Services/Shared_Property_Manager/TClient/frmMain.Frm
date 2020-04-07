VERSION 5.00
Begin VB.Form frmMain 
   AutoRedraw      =   -1  'True
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Tic-Tac-Toe client"
   ClientHeight    =   5550
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   9300
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6366.517
   ScaleMode       =   0  'User
   ScaleWidth      =   9423.598
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox lossesT 
      Height          =   375
      Left            =   5280
      Locked          =   -1  'True
      TabIndex        =   16
      Text            =   "0"
      Top             =   3000
      Width           =   375
   End
   Begin VB.TextBox tiesT 
      Height          =   375
      Left            =   4680
      Locked          =   -1  'True
      TabIndex        =   15
      Text            =   "0"
      Top             =   3000
      Width           =   375
   End
   Begin VB.TextBox winsT 
      Height          =   375
      Left            =   4080
      Locked          =   -1  'True
      TabIndex        =   12
      Text            =   "0"
      Top             =   3000
      Width           =   375
   End
   Begin VB.OptionButton Hard 
      Caption         =   "Hard"
      Height          =   255
      Left            =   4440
      TabIndex        =   10
      Top             =   1440
      Value           =   -1  'True
      Width           =   1095
   End
   Begin VB.OptionButton Easy 
      Caption         =   "Easy"
      Height          =   255
      Left            =   4440
      TabIndex        =   9
      Top             =   1800
      Width           =   855
   End
   Begin VB.TextBox Nombre 
      Height          =   285
      Left            =   4440
      TabIndex        =   8
      Top             =   600
      Width           =   1335
   End
   Begin VB.Timer ServerPoll 
      Enabled         =   0   'False
      Interval        =   300
      Left            =   3840
      Top             =   0
   End
   Begin VB.TextBox Result 
      Height          =   285
      Left            =   120
      Locked          =   -1  'True
      TabIndex        =   7
      Top             =   5160
      Width           =   5895
   End
   Begin VB.CommandButton Exit 
      Caption         =   "Exit Tic-Tac-Toe"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      TabIndex        =   5
      Top             =   4560
      Width           =   2055
   End
   Begin VB.TextBox Name2 
      Height          =   315
      Left            =   2520
      Locked          =   -1  'True
      TabIndex        =   4
      Top             =   600
      Width           =   1215
   End
   Begin VB.TextBox Name1 
      Height          =   285
      Left            =   120
      Locked          =   -1  'True
      TabIndex        =   3
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton PlayHuman 
      Caption         =   "Play against a Human"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      TabIndex        =   1
      Top             =   4080
      Width           =   2055
   End
   Begin VB.CommandButton PlayComputer 
      Caption         =   "Play against the computer"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   3960
      TabIndex        =   0
      Top             =   3600
      Width           =   2055
   End
   Begin VB.Image bmpSmallX 
      Height          =   315
      Left            =   8640
      Picture         =   "frmMain.frx":0000
      Top             =   2400
      Visible         =   0   'False
      Width           =   315
   End
   Begin VB.Image bmpSmallO 
      Height          =   315
      Left            =   8160
      Picture         =   "frmMain.frx":017E
      Top             =   2400
      Visible         =   0   'False
      Width           =   315
   End
   Begin VB.Image bmpNull 
      Height          =   315
      Left            =   8400
      Picture         =   "frmMain.frx":02FC
      Top             =   2880
      Visible         =   0   'False
      Width           =   315
   End
   Begin VB.Image bmpBigX 
      Height          =   900
      Left            =   8040
      Picture         =   "frmMain.frx":047A
      Top             =   1200
      Visible         =   0   'False
      Width           =   900
   End
   Begin VB.Image bmpBigO 
      Height          =   900
      Left            =   8040
      Picture         =   "frmMain.frx":0C7C
      Top             =   120
      Visible         =   0   'False
      Width           =   900
   End
   Begin VB.Image Image12 
      Height          =   900
      Left            =   1440
      Top             =   3960
      Width           =   900
   End
   Begin VB.Label Label4 
      Caption         =   "Losses"
      Height          =   255
      Left            =   5280
      TabIndex        =   18
      Top             =   2640
      Width           =   495
   End
   Begin VB.Label Label3 
      Caption         =   "Ties"
      Height          =   255
      Left            =   4680
      TabIndex        =   17
      Top             =   2640
      Width           =   375
   End
   Begin VB.Label Label2 
      Caption         =   "Wins"
      Height          =   255
      Left            =   4080
      TabIndex        =   14
      Top             =   2640
      Width           =   375
   End
   Begin VB.Label SessionLabel 
      Caption         =   "This session:"
      Height          =   255
      Left            =   4440
      TabIndex        =   13
      Top             =   2280
      Width           =   975
   End
   Begin VB.Label ComputerLabel 
      Caption         =   "Select degree of difficulty"
      Height          =   255
      Left            =   4320
      TabIndex        =   11
      Top             =   1080
      Width           =   1935
   End
   Begin VB.Image Image02 
      Height          =   900
      Left            =   240
      Top             =   3960
      Width           =   900
   End
   Begin VB.Image Image22 
      Height          =   900
      Left            =   2760
      Top             =   3960
      Width           =   900
   End
   Begin VB.Image Image21 
      Height          =   900
      Left            =   2760
      Top             =   2640
      Width           =   900
   End
   Begin VB.Image Image10 
      Height          =   915
      Left            =   1440
      Top             =   1320
      Width           =   945
   End
   Begin VB.Image Image20 
      Height          =   900
      Left            =   2760
      Top             =   1320
      Width           =   900
   End
   Begin VB.Image Image01 
      Height          =   900
      Left            =   240
      Top             =   2640
      Width           =   900
   End
   Begin VB.Image Image11 
      Height          =   900
      Left            =   1440
      Top             =   2640
      Width           =   900
   End
   Begin VB.Image Image00 
      Height          =   900
      Left            =   240
      Top             =   1320
      Width           =   900
   End
   Begin VB.Label NameLabel 
      Caption         =   "Your name is..."
      Height          =   255
      Left            =   4560
      TabIndex        =   6
      Top             =   240
      Width           =   1095
   End
   Begin VB.Image Player2 
      Height          =   315
      Left            =   3000
      Top             =   120
      Width           =   315
   End
   Begin VB.Image Player1 
      Height          =   315
      Left            =   600
      Top             =   120
      Width           =   315
   End
   Begin VB.Image GameScreen 
      Height          =   3615
      Left            =   120
      Picture         =   "frmMain.frx":147E
      Top             =   1320
      Width           =   3615
   End
   Begin VB.Label Label1 
      Caption         =   "Versus"
      Height          =   255
      Left            =   1680
      TabIndex        =   2
      Top             =   360
      Width           =   495
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' Filename: tClient.vbp
'
' Description:  Tic-Tac-Toe Client
'
' This file is provided as part of the Microsoft Transaction Server
' Software Development Kit
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
' WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
' INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES
' OF MERCHANTABILITY AND/OR FITNESS FOR A  PARTICULAR
' PURPOSE.
'
' Copyright (C) 1997 Microsoft Corporation, All rights reserved

Option Explicit

Private viper As Boolean
Private organic As Boolean
Private playing As Boolean
Private gameID As Long
Private localX As Long
Private localY As Long
Private localOrder As Long
Private localName As String
Private remoteName As String
Private easyComputer As Boolean
Private wins As Long
Private ties As Long
Private losses As Long

Private localPic As Picture
Private remotePic As Picture

Private full(3, 3) As Long
Private waiting As Boolean

Private Sub Easy_Click()
    easyComputer = True
End Sub

Private Sub Form_Load()
    Me.Left = GetSetting(App.Title, "Settings", "MainLeft", 1000)
    Me.Top = GetSetting(App.Title, "Settings", "MainTop", 1000)
    Me.Width = GetSetting(App.Title, "Settings", "MainWidth", 6500)
    Me.Height = GetSetting(App.Title, "Settings", "MainHeight", 6500)
    
    ' Make sure the Tic-Tac-Toe components are properly installed in COM+
    On Error GoTo objError
    Dim computer As Object
    Dim human As Object
    Set computer = CreateObject("tServer.Computer")
    Set human = CreateObject("tServer.Human")
    On Error GoTo 0
    
    ' Init
    localName = "tClient User"
    remoteName = "No one"
    viper = False
    organic = False
    playing = False
    gameID = -1
    waiting = False
    ServerPoll.Enabled = False
    easyComputer = False
    wins = 0
    ties = 0
    losses = 0
    
    Nombre = localName
    Name1 = "No one"
    Name2 = remoteName
    Player1.Picture = bmpNull
    Player2.Picture = bmpNull
    Result = "Press a button and start a game"
    
    Exit Sub
    
objError:
    MsgBox "Error " & Err.Number & ": Make sure the Tic-Tac-Toe package(tServer.dll) has been correctly installed into a COM+ Application."
    End
End Sub


Private Sub Form_Unload(Cancel As Integer)
    Dim i As Integer

    'Close all sub forms
    For i = Forms.Count - 1 To 1 Step -1
        Unload Forms(i)
    Next
    If Me.WindowState <> vbMinimized Then
        SaveSetting App.Title, "Settings", "MainLeft", Me.Left
        SaveSetting App.Title, "Settings", "MainTop", Me.Top
        SaveSetting App.Title, "Settings", "MainWidth", Me.Width
        SaveSetting App.Title, "Settings", "MainHeight", Me.Height
    End If
End Sub

Private Sub Hard_Click()
    easyComputer = False
End Sub

Private Sub Image00_Click()
    
    If playing And full(0, 0) = 0 Then
        If localOrder = 1 Then
            Image00.Picture = bmpBigX
        Else
            Image00.Picture = bmpBigO
        End If
    
        MovePiece 0, 0
    End If
    
End Sub

Private Sub Image01_Click()
    
    If playing And full(0, 1) = 0 Then
        If localOrder = 1 Then
            Image01.Picture = bmpBigX
        Else
            Image01.Picture = bmpBigO
        End If
    
        MovePiece 0, 1
    End If
    
End Sub

Private Sub Image02_Click()

    If playing And full(0, 2) = 0 Then
        If localOrder = 1 Then
            Image02.Picture = bmpBigX
        Else
            Image02.Picture = bmpBigO
        End If
    
        MovePiece 0, 2
    End If
    
End Sub

Private Sub Image10_Click()
    
    If playing And full(1, 0) = 0 Then
        If localOrder = 1 Then
            Image10.Picture = bmpBigX
        Else
            Image10.Picture = bmpBigO
        End If
    
        MovePiece 1, 0
    End If
    
End Sub

Private Sub Image11_Click()

    If playing And full(1, 1) = 0 Then
        If (localOrder = 1) Then
            Image11.Picture = bmpBigX
        Else
            Image11.Picture = bmpBigO
        End If
    
        MovePiece 1, 1
    End If
    
End Sub

Private Sub Image12_Click()
    
    If playing And full(1, 2) = 0 Then
        If localOrder = 1 Then
            Image12.Picture = bmpBigX
        Else
            Image12.Picture = bmpBigO
        End If
    
        MovePiece 1, 2
    End If
    
End Sub

Private Sub Image20_Click()
    
    If playing And full(2, 0) = 0 Then
        If localOrder = 1 Then
            Image20.Picture = bmpBigX
        Else
            Image20.Picture = bmpBigO
        End If
    
        MovePiece 2, 0
    End If
    
End Sub

Private Sub Image21_Click()
    
    If playing And full(2, 1) = 0 Then
        If localOrder = 1 Then
            Image21.Picture = bmpBigX
        Else
            Image21.Picture = bmpBigO
        End If
    
        MovePiece 2, 1
    End If
    
End Sub

Private Sub Image22_Click()
    
    If playing And full(2, 2) = 0 Then
        If localOrder = 1 Then
            Image22.Picture = bmpBigX
        Else
            Image22.Picture = bmpBigO
        End If
    
        MovePiece 2, 2
    End If
    
End Sub

Private Sub Nombre_Change()
    localName = Nombre
End Sub


Private Sub PlayHuman_Click()
      
    ' Present hourglass pointer
    Me.MousePointer = vbHourglass
    
    ' Clean up screen
    ClearScreen
    InitArray
    
    ' Create server human object
    Dim human As Object
    Set human = CreateObject("tServer.Human")
    If human Is Nothing Then
        MsgBox "Create object " + "tServer.Human" + " failed."
        Exit Sub
    End If
    
    ' Notify server of new game
    Dim order As Variant
    Dim player2Name As Variant
    Dim gameNumber As Variant
    human.EnterNewGame localName, gameNumber, player2Name, order
    remoteName = player2Name
    gameID = gameNumber
    
    ' Set up screen
    Name1 = localName
    Name2 = remoteName
    PlayComputer.Enabled = False
    PlayHuman.Enabled = False
    Nombre.Locked = True
    Easy.Enabled = False
    Hard.Enabled = False
    
    ' Set up local variables
    viper = False
    organic = True
    playing = False
    ServerPoll.Enabled = True
    
    ' Set up order
    localOrder = order
    If order = 1 Then
        Player1.Picture = bmpSmallX
        Player2.Picture = bmpSmallO
        Set localPic = bmpBigX
        Set remotePic = bmpBigO
        Result = "You are now in game " & gameID & ", we are waiting for another 'human' to join the game."
    Else
        Player1.Picture = bmpSmallO
        Player2.Picture = bmpSmallX
        Set localPic = bmpBigO
        Set remotePic = bmpBigX
        Result = "Game " & gameID & " against '" & remoteName & "' has begun.  Waiting for '" & remoteName & "' to move."
        waiting = True
    End If
    
    ' Clean up
    Set human = Nothing
    
    ' Return control
    Me.MousePointer = vbArrow
    
End Sub

Private Sub PlayComputer_Click()

    ' Present hourglass pointer
    Me.MousePointer = vbHourglass
    
    ' Clean up screen
    InitArray
    ClearScreen
    
    ' Create server computer object
    Dim computer As Object
    Set computer = CreateObject("tServer.Computer")
    If computer Is Nothing Then
        MsgBox "Create object " + "tServer.Computer" + " failed."
        Exit Sub
    End If
    
    ' Notify server of new game
    Dim lGameID As Variant
    Dim order As Variant
    Dim foeX As Variant
    Dim foeY As Variant
    computer.AddNewGame easyComputer, lGameID, order, foeX, foeY
    gameID = lGameID

    ' Set up screen
    If easyComputer = True Then
        remoteName = "I am, I think"
    Else
        remoteName = "I think I am"
    End If
    Name1 = localName
    Name2 = remoteName
    PlayComputer.Enabled = False
    PlayHuman.Enabled = False
    Nombre.Locked = True
    Easy.Enabled = False
    Hard.Enabled = False
    
    ' Set up local variables
    viper = True
    organic = False
    playing = True
    
    ' Set up order
    localOrder = order
    If order = 1 Then
        Player1.Picture = bmpSmallX
        Player2.Picture = bmpSmallO
        Set localPic = bmpBigX
        Set remotePic = bmpBigO

    Else
        Player1.Picture = bmpSmallO
        Player2.Picture = bmpSmallX
        Set localPic = bmpBigO
        Set remotePic = bmpBigX
       
        ' Process opponent's first move
        Display remotePic, foeX, foeY
        full(foeX, foeY) = 1
        
    End If
    
    ' Clean up
    Set computer = Nothing
    
    ' Return control
    Result = "Game " & gameID & " against '" & remoteName & "' has begun.  It is now your turn."
    Me.MousePointer = vbArrow
    
End Sub

Private Sub Exit_Click()
    ' Notify opponent of exit
    End
End Sub

Private Sub MovePiece(X As Long, Y As Long)

    Dim win As Variant
    If viper Then
        
        ' Create server computer object
        Dim computer As Object
        Set computer = CreateObject("tServer.Computer")
        If computer Is Nothing Then
            MsgBox "Create object " + "tServer.Computer" + " failed."
            Exit Sub
        End If
    
        ' Submit move
        Dim foeX As Variant
        Dim foeY As Variant
        computer.NewMove gameID, easyComputer, X, Y, foeX, foeY, win
         
        ' Win protocol
        ' ============
        ' 0  -> moves did not end game
        ' 1  -> player won
        ' -1 -> computer won
        ' 2  -> player's move tied the game
        ' -2 -> computer's move tied the game
    
        ' Display local move
        Display localPic, X, Y
        full(X, Y) = 1
        
        ' Check for win or loss
        If Abs(win) = 1 Then
            If win = 1 Then
                wins = wins + 1
                winsT = wins
                Result = "Congratulations!  You won your game against '" & remoteName & "'."
                Cleanup
                Exit Sub
            Else
                Display remotePic, foeX, foeY
                losses = losses + 1
                lossesT = losses
                Result = "Too bad, '" & remoteName & "' won.  Better luck next time!"
                Cleanup
                Exit Sub
            End If
        Else
            If Abs(win) = 2 Then
                If win = 2 Then
                    Display remotePic, foeX, foeY
                End If
                ties = ties + 1
                tiesT = ties
                Result = "You tied '" & remoteName & ".' " & " Keep trying!"
                Cleanup
                Exit Sub
            Else
                ' Display opponent's move
                Display remotePic, foeX, foeY
                full(foeX, foeY) = 1
            End If
        End If
        
        ' Clean up
        Set computer = Nothing
    
        Result = "It is now your turn."

    Else
    
        ' Shut down server polling
        ServerPoll.Enabled = False
        
        ' Create server human object
        Dim human As Object
        Set human = CreateObject("tServer.Human")
        If human Is Nothing Then
            MsgBox "Create object " + "tServer.Human" + " failed."
            Exit Sub
        End If
        
        ' Submit move
        human.NewMove gameID, localOrder, X, Y, win
        
        ' Win protocol
        ' ============
        ' 0  -> move did not end game
        ' 1  -> player won
        ' -1 -> remote player won (won't occur in this function)
        ' 2  -> player's move tied the game
        ' -2 -> remote player's move tied the game (won't occur in this function)
        
        ' Display local move
        Display localPic, X, Y
        full(X, Y) = 1
        
        ' Check for win or loss
        If win = 1 Then
            wins = wins + 1
            winsT = wins
            Result = "Congratulations!  You won your game against '" & remoteName & "'."
            Cleanup
            Exit Sub
        Else
            If win = 2 Then
                ties = ties + 1
                tiesT = ties
                Result = "You tied '" & remoteName & ".' " & " Keep trying!"
                Cleanup
                Exit Sub
            Else
                ' Reenable server polling
                ServerPoll.Enabled = True
            End If
        End If

        ' We're waiting for a move or we finished the game
        playing = False
        
        ' Clean up
        Set human = Nothing
        
        Result = "Waiting for '" & remoteName & "'s next move."
    End If

End Sub

Private Sub Display(pic As Picture, X As Variant, Y As Variant)

    Dim hash As Long
    hash = X * 10 + Y
    
    Select Case hash
    
        Case 0
            Image00.Picture = pic
        Case 1
            Image01.Picture = pic
        Case 2
            Image02.Picture = pic
        Case 10
            Image10.Picture = pic
        Case 11
            Image11.Picture = pic
        Case 12
            Image12.Picture = pic
        Case 20
            Image20.Picture = pic
        Case 21
            Image21.Picture = pic
        Case 22
            Image22.Picture = pic
        Case Else
            MsgBox ("Invalid Display Parameter")
            
    End Select
    
End Sub

Private Sub Cleanup()

    ' Reset variables
    playing = False
    viper = False
    organic = False
    PlayHuman.Enabled = True
    PlayComputer.Enabled = True
    Nombre.Locked = False
    Easy.Enabled = True
    Hard.Enabled = True

End Sub

Private Sub InitArray()
    
    Dim i, j As Long
    For i = 0 To 2
        For j = 0 To 2
            full(i, j) = 0
        Next
    Next

End Sub


Private Sub ServerPoll_Timer()

    If organic And Not playing Then

        ' Create server human object
        Dim human As Object
        Set human = CreateObject("tServer.Human")
        If human Is Nothing Then
            MsgBox "Create object " + "tServer.Human" + " failed."
            Exit Sub
        End If
    
        ' Poll server
        Dim name As Variant
        Dim foeX As Variant
        Dim foeY As Variant
        Dim win As Variant
        Dim update As Variant
        human.GetNewMove gameID, localOrder, name, foeX, foeY, win, update
        
        ' Win protocol
        ' ============
        ' 0  -> move did not end game
        ' 1  -> player won (won't occur in this function)
        ' -1 -> remote player won
        ' 2  -> player's move tied the game (won't occur in this function)
        ' -2 -> remote player's move tied the game
    
        ' Routine move
        If update = 1 Then
        
            ' Stop polling
            ServerPoll.Enabled = False
            
            ' Display opponent's move
            Display remotePic, foeX, foeY
            full(foeX, foeY) = 2
            
            ' Check for win or loss
            If win = -1 Then
                losses = losses + 1
                lossesT = losses
                Result = "Too bad, '" & remoteName & "' won.  Better luck next time!"
                Cleanup
                Exit Sub
            Else
                If win = -2 Then
                    ties = ties + 1
                    tiesT = ties + 1
                    Result = "You tied '" & remoteName & ".' " & " Keep trying!"
                    Cleanup
                    Exit Sub
                Else
                    Result = "'" & remoteName & "' has moved.  It is now your turn."
                    playing = True
                End If
            End If
        Else
            ' Player just joined
            If update = 2 Then
                remoteName = name
                Name2 = remoteName
                Result = "'" & remoteName & "' has joined your game.  It is now your turn."
                playing = True
            End If
        End If
        
        ' Clean up
        Set human = Nothing
    
    End If

End Sub

Private Sub ClearScreen()

    Image00.Picture = LoadPicture
    Image10.Picture = LoadPicture
    Image20.Picture = LoadPicture
    Image01.Picture = LoadPicture
    Image11.Picture = LoadPicture
    Image21.Picture = LoadPicture
    Image02.Picture = LoadPicture
    Image12.Picture = LoadPicture
    Image22.Picture = LoadPicture
    
End Sub

