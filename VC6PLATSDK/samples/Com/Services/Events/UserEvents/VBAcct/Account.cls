VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 3  'UsesTransaction
END
Attribute VB_Name = "Account"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ==============================================================================
' Filename: Account.vbp
'
' Summary:  Visual Basic implememtation of the account class for the bank sample
' Classes:  Account.cls
'
' This file is part of the Microsoft COM+ Samples
'
' Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved
'
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation.  See these other
' materials for detailed information reagrding Microsoft code samples.
'
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'

Option Explicit

Private Const APP_ERROR = -2147467008
Private lngBalance As Long

Private Sub Class_Initialize()
    lngBalance = 1000
End Sub

Public Function Post(ByVal lngAccountNo As Long, ByVal lngAmount As Long) As String
' F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
'
' Function: Post
'
' This function posts a banking transaction to an account
'
' Args:     lngAccount -    Account to be posted
'           lngAmount -     Amount to be posted
' Returns:  String -        Account Balance
'
' F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---

    
    Dim strResult As String
    
    On Error GoTo ErrorHandler
    
    ' check if account is overdrawn
    If (lngBalance) < 0 Then
        Err.Raise Number:=APP_ERROR, Description:="Error. Account " + Str$(lngAccountNo) + " would be overdrawn by " + Str$(lngBalance) + ". Balance is still " + Str$(lngBalance - lngAmount) + "."
    Else
        lngBalance = lngBalance + lngAmount
        If lngAmount < 0 Then
            strResult = strResult & "Debit from account " & lngAccountNo & ", "
        Else
            strResult = strResult & "Credit to account " & lngAccountNo & ", "
        End If
        strResult = strResult + "balance is $" & Str$(lngBalance) & ". (VB)"
    End If

    Dim objMtsLocator As New CoMTSLocator
    Dim objEventDispatcher As New COMEvents
    Dim varEvent As Variant

    ' Locate the event dispatcher
    Set objEventDispatcher = objMtsLocator.GetEventDispatcher
    
    ' Fire a user event to notify potential listeners of the transaction
    varEvent = strResult
    objEventDispatcher.PostEvent varEvent
   
    
    ' cleanup
    Post = strResult
    
 Exit Function


ErrorHandler:
    
    Post = ""                       ' indicate that an error occurred
    Err.Raise Err.Number, "Bank.Accout.Post", Err.Description
    
End Function

