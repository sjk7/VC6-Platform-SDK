VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
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

Private Const ERROR_NUMBER = vbObjectError + 0
Private Const APP_ERROR = -2147467008
Private Const strConnect = "FILEDSN=BankSample"

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
    
    ' check for security
    If (lngAmount > 500 Or lngAmount < -500) Then
        If Not GetObjectContext.IsCallerInRole("Managers") Then
            Err.Raise Number:=APP_ERROR, Description:="Need 'Managers' role for amounts over $500"
        End If
    End If
    
    ' obtain the ADO environment and connection
    Dim adoConn As New ADODB.Connection
    Dim varRows As Variant
    
    adoConn.Open strConnect
   
    On Error GoTo ErrorCreateTable

    ' update the balance
    Dim strSQL As String
    strSQL = "UPDATE Account SET Balance = Balance + " + Str$(lngAmount) + " WHERE AccountNo = " + Str$(lngAccountNo)
    
TryAgain:
    adoConn.Execute strSQL, varRows

    ' if anything else happens
    On Error GoTo ErrorHandler
  
    ' get resulting balance which may have been further updated via triggers
    strSQL = "SELECT Balance FROM Account WHERE AccountNo = " + Str$(lngAccountNo)
    
    Dim adoRS As ADODB.Recordset
    Set adoRS = adoConn.Execute(strSQL)
    If adoRS.EOF Then
        Err.Raise Number:=APP_ERROR, Description:="Error. Account " + Str$(lngAccountNo) + " not on file."
    End If

    Dim lngBalance As Long
    lngBalance = adoRS.Fields("Balance").Value
    
    ' check if account is overdrawn
    If (lngBalance) < 0 Then
        Err.Raise Number:=APP_ERROR, Description:="Error. Account " + Str$(lngAccountNo) + " would be overdrawn by " + Str$(lngBalance) + ". Balance is still " + Str$(lngBalance - lngAmount) + "."
    Else
        If lngAmount < 0 Then
            strResult = strResult & "Debit from account " & lngAccountNo & ", "
        Else
            strResult = strResult & "Credit to account " & lngAccountNo & ", "
        End If
        strResult = strResult + "balance is $" & Str$(lngBalance) & ". (VB)"
    End If

    ' cleanup
    Set adoRS = Nothing
    Set adoConn = Nothing
    
    GetObjectContext.SetComplete          ' we are finished and happy
    
    Post = strResult
    
 Exit Function

ErrorCreateTable:
    On Error GoTo ErrorHandler
    
    ' create the account table
    Dim objCreateTable As CreateTable
    Set objCreateTable = CreateObject("Bank.CreateTable")
    objCreateTable.CreateAccount
      
    GoTo TryAgain

ErrorHandler:
    ' cleanup
    If Not adoRS Is Nothing Then
        Set adoRS = Nothing
    End If
    If Not adoConn Is Nothing Then
        Set adoConn = Nothing
    End If
    
    GetObjectContext.SetAbort              ' we are unhappy
    
    Post = ""                       ' indicate that an error occurred
    
    Err.Raise Err.Number, "Bank.Accout.Post", Err.Description
    
End Function

