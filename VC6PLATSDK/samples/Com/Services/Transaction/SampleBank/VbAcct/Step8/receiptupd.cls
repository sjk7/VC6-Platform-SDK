VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "UpdateReceipt"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
' ==============================================================================
' Filename: Account.vbp
'
' Summary:  Visual Basic implememtation of the GetReceipt component for the bank sample
' Classes:  UpdateReceipt.cls
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

Public Function Update() As Long
' F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++
'
' Function: Update
'
' This function the receipt and returns the next receipt value
'
' Args:     None
' Returns:  Long -  next receipt value
'            -1 if Error
'
' F-F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---
    On Error GoTo ErrorHandler
    
    ' get result set and then update table with new receipt number
    Dim adoConn As New ADODB.Connection
    Dim adoRsReceipt As ADODB.Recordset
    Dim lngNextReceipt As Long
    Dim strSQL As String
  
    strSQL = "Update Receipt set NextReceipt = NextReceipt + 100"
    
    adoConn.Open strConnect
    
    ' Assume that if there is an ado error then the receipt
    ' table does not exist
    On Error GoTo ErrorCreateTable

TryAgain:
    
    adoConn.Execute strSQL
    
    strSQL = "Select NextReceipt from Receipt"
    Set adoRsReceipt = adoConn.Execute(strSQL)
    lngNextReceipt = adoRsReceipt!NextReceipt
    
    Set adoConn = Nothing
    Set adoRsReceipt = Nothing
  
    GetObjectContext.SetComplete          ' we are finished and happy

    Update = lngNextReceipt
    
    Exit Function

ErrorCreateTable:

    On Error GoTo ErrorHandler
   
    ' create the receipt table
    Dim objCreateTable As CreateTable
    Set objCreateTable = CreateObject("Bank.CreateTable")
    objCreateTable.CreateReceipt
      
    GoTo TryAgain
    
ErrorHandler:
    
    If Not adoConn Is Nothing Then
        Set adoConn = Nothing
    End If
    If Not adoRsReceipt Is Nothing Then
        Set adoRsReceipt = Nothing
    End If
    
    GetObjectContext.SetAbort      ' we are unhappy
    
    Update = -1                    ' indicate that an error occured
    
    Err.Raise Err.Number, "Bank.UpdateReceipt.Update", Err.Description
    
End Function

