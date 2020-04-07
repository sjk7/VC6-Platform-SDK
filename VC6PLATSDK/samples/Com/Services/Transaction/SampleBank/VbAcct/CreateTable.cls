VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 1  'NoTransaction
END
Attribute VB_Name = "CreateTable"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ==============================================================================
' Filename: Account.vbp
'
' Summary:  Visual Basic implememtation of the create table class for the bank sample
' Classes:  CreateTable.cls
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

Private Const ERROR_NUMBER = vbObjectError + 0 ' we always return the same error number
Private Const strConnect = "FILEDSN=BankSample"

Public Sub CreateAccount()
' F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
'
' Function: CreateAccount
'
' This function creates the Account table
'
' Args:     None
' Returns:  None
'
' F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---
    
    On Error GoTo ErrorHandler
    
    Dim adoConn As New ADODB.Connection
    adoConn.Open strConnect
   
    ' Add Account Table
    Dim strSQL As String
    
    strSQL = "If not exists (Select name from sysobjects where name = 'Account')" & vbCrLf & _
            "BEGIN" & vbCrLf & _
            "CREATE TABLE dbo.Account (" & vbCrLf & _
                "AccountNo int NOT NULL ," & vbCrLf & _
                "Balance int NULL ," & vbCrLf & _
                "CONSTRAINT PK___1__10 PRIMARY KEY  CLUSTERED" & vbCrLf & _
                "(" & vbCrLf & _
                    "AccountNo" & vbCrLf & _
                ")" & vbCrLf & _
            ")" & vbCrLf & _
            "INSERT INTO Account VALUES (1,1000)" & vbCrLf & _
            "INSERT INTO Account VALUES (2,1000)" & vbCrLf & _
            "END" & vbCrLf
    
    adoConn.Execute strSQL
    
    Set adoConn = Nothing
    
    GetObjectContext.SetComplete
    
    Exit Sub
    
ErrorHandler:

    If Not adoConn Is Nothing Then
        Set adoConn = Nothing
    End If
    
    GetObjectContext.SetAbort
    
    Err.Raise Err.Number, "Bank.CreateTable.CreateAccount", Err.Description
    
End Sub


Public Sub CreateReceipt()
' F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
'
' Function: CreateReceipt
'
' This function creates the Receipt Table
'
' Args:     None
' Returns:  None
'
' F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---
    
    On Error GoTo ErrorHandler
    
    Dim adoConn As New ADODB.Connection
    adoConn.Open strConnect
   
    ' Add ReceiptNo Table
    Dim strSQL As String
    strSQL = strSQL & _
            "If not exists (Select name from sysobjects where name = 'Receipt')" & vbCrLf & _
            "BEGIN" & vbCrLf & _
            "CREATE TABLE Receipt (NextReceipt int)" & vbCrLf & _
            "INSERT INTO Receipt VALUES (1000)" & vbCrLf & _
            "END"
    adoConn.Execute strSQL
  
    Set adoConn = Nothing
    
    GetObjectContext.SetComplete
    
    Exit Sub
    
ErrorHandler:

    If Not adoConn Is Nothing Then
        Set adoConn = Nothing
    End If
    
    GetObjectContext.SetAbort
    
    Err.Raise Err.Number, "Bank.CreateTable.CreateReceipt", Err.Description
    
End Sub
