VERSION 5.00
Begin VB.Form frmMonitor 
   Caption         =   "Compensating Resource Manager Sample - Monitor Log Records"
   ClientHeight    =   5265
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7275
   LinkTopic       =   "Form1"
   ScaleHeight     =   5265
   ScaleWidth      =   7275
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox chkAbortTransaction 
      Caption         =   "Abort Transaction"
      Height          =   375
      Left            =   480
      TabIndex        =   4
      Top             =   840
      Width           =   1575
   End
   Begin VB.CommandButton cmdMonitor 
      Caption         =   "Go"
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Top             =   240
      Width           =   1575
   End
   Begin VB.ListBox lstOutput 
      Height          =   3570
      Left            =   240
      TabIndex        =   1
      Top             =   1560
      Width           =   6855
   End
   Begin VB.TextBox txtTransactionUOW 
      Height          =   285
      Left            =   2400
      TabIndex        =   0
      Top             =   720
      Width           =   4455
   End
   Begin VB.Label lblTransactionUOW 
      Caption         =   "Transaction Unit of Work ID"
      Height          =   255
      Left            =   2400
      TabIndex        =   3
      Top             =   360
      Width           =   3735
   End
End
Attribute VB_Name = "frmMonitor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

' This file is part of the Microsoft COM Technology Samples.
'
' Copyright (C) 1998 Microsoft Corporation. All rights reserved.
'
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation. See these other
' materials for detailed information regarding Microsoft code samples.
'
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.


Dim MonComp As CrmMonComp

Private Sub cmdMonitor_Click()
    
    Set MonComp = New CrmMonComp
    
    Dim sTransactionUOW As String
    
    sTransactionUOW = txtTransactionUOW
    
    ' must be upper case for match
    
    sTransactionUOW = UCase(sTransactionUOW)
    
    MonComp.TransactionUOW = sTransactionUOW
    
    Dim NumberOfClerks
    
    NumberOfClerks = MonComp.FindClerks
    
    lstOutput.Clear
    
    ' transaction info
    
    lstOutput.AddItem "Transaction Unit of Work ID = " + sTransactionUOW
    
    If NumberOfClerks = 0 Then
    
        lstOutput.AddItem "No CRMs found for this transaction"
        
        Exit Sub
        
    End If
    
    lstOutput.AddItem "Transaction State = " + MonComp.TransactionState
    
    lstOutput.AddItem "Activity ID = " + MonComp.ActivityId
    
    lstOutput.AddItem "# of CRMs = " + Str(NumberOfClerks)
    
    lstOutput.AddItem "----------"
    
    ' for each clerk

    For ClerkIndex = 0 To (NumberOfClerks - 1)
            
        MonComp.SetClerk ClerkIndex
        
        lstOutput.AddItem "CRM # " + Str(ClerkIndex)
        
        lstOutput.AddItem "Compensator ProgId = " + MonComp.ProgId
        
        lstOutput.AddItem "Description = " + MonComp.Description
        
        Dim NumberOfLogRecords
        
        NumberOfLogRecords = MonComp.NumberOfLogRecords
        
        lstOutput.AddItem "# log records = " + Str(NumberOfLogRecords)
        
        lstOutput.AddItem "----------"
        
        ' get the column headers
        
        Dim ColHeaders
            
        ColHeaders = MonComp.ColumnHeaders
        
        Dim FormattedRecord
        
        ' for each log record

        For LogRecordIndex = 0 To NumberOfLogRecords - 1
        
            MonComp.SetRecord LogRecordIndex
            
            FormattedRecord = MonComp.FormattedRecord
            
            lstOutput.AddItem "log record # " + Str(LogRecordIndex)
            
            If IsArray(ColHeaders) Then

                ' is an array here
                
                Dim i
                
                i = 1
    
                For Each Col In ColHeaders
    
                    ' just list each field
    
                    lstOutput.AddItem ColHeaders(i) + " = " + FormattedRecord(i)
    
                    i = i + 1
    
                Next Col
            
            Else
            
                ' is not an array
                
                lstOutput.AddItem ColHeaders
                
                lstOutput.AddItem FormattedRecord
                    
            End If
            
                lstOutput.AddItem "-----"

        Next LogRecordIndex
        
    Next ClerkIndex
    
    If chkAbortTransaction Then
          
        MonComp.AbortTransaction
        
    End If
    
End Sub

