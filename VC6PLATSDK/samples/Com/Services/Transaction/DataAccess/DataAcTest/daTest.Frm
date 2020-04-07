VERSION 5.00
Begin VB.Form frmTest 
   Caption         =   "Data Access Test  Application"
   ClientHeight    =   5820
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3390
   LinkTopic       =   "Form1"
   ScaleHeight     =   5820
   ScaleWidth      =   3390
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton cmdOLEDBKB 
      Caption         =   "OLEDBKB Test"
      Height          =   975
      Left            =   240
      TabIndex        =   3
      ToolTipText     =   "This button demonstrates the use of the OLEDBoOmponent oledb.dll"
      Top             =   3480
      Width           =   2895
   End
   Begin VB.CommandButton cmdExit 
      Caption         =   "Exit"
      Height          =   975
      Left            =   240
      TabIndex        =   4
      Top             =   4560
      Width           =   2895
   End
   Begin VB.CommandButton cmdRDOKB 
      Caption         =   "RDOKB Test"
      Height          =   975
      Left            =   240
      TabIndex        =   2
      ToolTipText     =   "This button demonstrates the use of the RDOComponent in rdokb.dll"
      Top             =   2400
      Width           =   2895
   End
   Begin VB.CommandButton cmdADO 
      Caption         =   "ADO Test"
      Default         =   -1  'True
      Height          =   975
      Left            =   240
      TabIndex        =   0
      ToolTipText     =   "This button demonstrates using ADO from within VB"
      Top             =   240
      Width           =   2895
   End
   Begin VB.CommandButton cmdADOKB 
      Caption         =   "ADOKB Test"
      Height          =   975
      Left            =   240
      TabIndex        =   1
      ToolTipText     =   "This button demonstrates the use of the ADOComponent in adokb.dll"
      Top             =   1320
      Width           =   2895
   End
End
Attribute VB_Name = "frmTest"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
' ==============================================================================
' Filename: DATest.vbp
'
' Summary:  Visual Basic sample application to demonstrate Data Access components
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

Private Sub cmdADO_Click()
    Dim objADORS As Recordset
    Dim Source As String
    Dim Connect As String
    
    Source = "select au_fname from authors where au_lname='White'"
    Connect = "DSN=pubs;Uid=sa;Pwd=;Database=pubs"
    
    Set objADORS = CreateObject("ADODB.Recordset")
    
    objADORS.Open Source, Connect, adOpenForwardOnly, adLockReadOnly, adCmdText
    MsgBox objADORS.Fields.Item("au_fname").Value, vbInformation, "Data Access Tester"
End Sub
Private Sub cmdADOKB_Click()
    Dim objADO As ADOComponent
    Dim result As Variant
    Set objADO = CreateObject("ADOComponent.ADOComponent.1")
    objADO.SimpleQuery result
    
    MsgBox result
End Sub
Private Sub cmdRDOKB_Click()
    Dim objRDO As RDOComponent
    Dim result As Variant
    Set objRDO = CreateObject("RdoComponent.RdoComponent.1")
    objRDO.SimpleQuery result
    MsgBox result
End Sub
Private Sub cmdOLEDBKB_Click()
    Dim objOLEDB As OLEDBComponent
    Dim result As String
    Set objOLEDB = CreateObject("OLEDBComponent.OLEDBComponent.1")
    objOLEDB.SimpleQuery result
    MsgBox result
End Sub
Private Sub cmdExit_Click()
    Unload Me
End Sub

