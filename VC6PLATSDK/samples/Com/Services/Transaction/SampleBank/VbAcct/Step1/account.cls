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
Public Function POST(ByRef lngAccount As Long, ByRef lngAmount As Long) As String
POST:
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


    On Error GoTo ErrorHandler
    POST = "Hello from Account!!!"
    Exit Function
    ' Return the error message indicating that an error occurred.
ErrorHandler:
    Err.Raise Err.Number, "Bank.Account.Post", Err.Description
End Function
