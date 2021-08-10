VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MoveMoney"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ==============================================================================
' Filename: Account.vbp
'
' Summary:  Visual Basic implememtation of the MoveMoney component for the bank sample
' Classes:  MoveMoney.cls
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

Public PrimeAccount As Long
Public SecondAccount As Long

Private Const ERROR_NUMBER = vbObjectError + 0
Private Const APP_ERROR = -2147467008

Public Function Perform(ByVal lngPrimeAccount As Long, ByVal lngSecondAccount As Long, ByVal lngAmount As Long, ByVal lngTranType As Long) As String
' F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
'
' Function: Perform
'
' This function performs a bank transaction
'
' Args:     lngPrimeAccount -   "From" Account
'           lngSecondAccount -  "To" Account
'           lngAmount -         Amount of transaction
'           lngTranType -       Transaction Type
'                               (1 = Withdrawal,
'                                2 = Deposit,
'                                3 = Transfer)
'
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
    
    ' create the account object using our context
    Dim objAccount As Bank.Account
    Set objAccount = CreateObject("Bank.Account")
    
    If objAccount Is Nothing Then
        Err.Raise ERROR_NUMBER, Description:="Could not create account object"
    End If

    ' call the post function based on the transaction type
    Select Case lngTranType
        
        Case 1
            strResult = objAccount.Post(lngPrimeAccount, 0 - lngAmount)
            If strResult = "" Then
                Err.Raise ERROR_NUMBER, Description:=strResult
            End If
    
        Case 2
            strResult = objAccount.Post(lngPrimeAccount, lngAmount)
                If strResult = "" Then
                    Err.Raise ERROR_NUMBER, Description:=strResult
            End If
            
        Case 3
            Dim strResult1 As String, strResult2 As String
            ' do the credit
            strResult1 = objAccount.Post(lngSecondAccount, lngAmount)
            If strResult1 = "" Then
                Err.Raise ERROR_NUMBER, Description:=strResult1
            Else
                ' then do the debit
                strResult2 = objAccount.Post(lngPrimeAccount, 0 - lngAmount)
                If strResult2 = "" Then
                    Err.Raise ERROR_NUMBER, Description:=strResult2    ' debit failed
                Else
                    strResult = strResult1 + "  " + strResult2
                End If
            End If
            
        Case Else
            Err.Raise ERROR_NUMBER, Description:="Invalid Transaction Type"
    
    End Select
    
    ' Get Receipt Number for the transaction
    Dim objReceiptNo As Bank.GetReceipt
    Dim lngReceiptNo As Long
  
    Set objReceiptNo = CreateObject("Bank.GetReceipt")
    lngReceiptNo = objReceiptNo.GetNextReceipt
    If lngReceiptNo > 0 Then
        strResult = strResult & "; Receipt No: " & Str$(lngReceiptNo)
    End If
    
    GetObjectContext.SetComplete                  ' we are finished and happy
    
    Perform = strResult
     
    Exit Function
 
ErrorHandler:

    GetObjectContext.SetAbort                      ' we are unhappy
    
    Perform = ""                            ' indicate that an error occured
    
    Err.Raise Err.Number, "Bank.MoveMoney.Perform", Err.Description
    
End Function
Public Function StatefulPerform(ByVal lngAmount As Long, ByVal lngTranType As Long) As String
' F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
'
' Function: StatefulPerform
'
' This function performs a bank transaction using current state
'
' Args:     lngAmount -         Amount of transaction
'           lngTranType -       Transaction Type
'                               (1 = Withdrawal,
'                                2 = Deposit,
'                                3 = Transfer)
'
' Returns:  String -        Account Balance
'
' F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---
   StatefulPerform = Perform(PrimeAccount, SecondAccount, lngAmount, lngTranType)
End Function

