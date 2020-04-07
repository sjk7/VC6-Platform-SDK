VERSION 5.00
Begin VB.Form InputForm 
   Caption         =   "COM+ Queued Component Sample Driver"
   ClientHeight    =   6348
   ClientLeft      =   60
   ClientTop       =   348
   ClientWidth     =   8508
   LinkTopic       =   "Form1"
   ScaleHeight     =   6348
   ScaleWidth      =   8508
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox CustomerInput 
      Height          =   285
      Left            =   1200
      TabIndex        =   1
      Top             =   960
      Width           =   2655
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   9
      Left            =   3120
      TabIndex        =   23
      Top             =   4680
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   9
      Left            =   120
      TabIndex        =   22
      Top             =   4680
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   8
      Left            =   3120
      TabIndex        =   21
      Top             =   4440
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   8
      Left            =   120
      TabIndex        =   20
      Top             =   4440
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   7
      Left            =   3120
      TabIndex        =   19
      Top             =   4200
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   7
      Left            =   120
      TabIndex        =   18
      Top             =   4200
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   6
      Left            =   3120
      TabIndex        =   17
      Top             =   3960
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   6
      Left            =   120
      TabIndex        =   16
      Top             =   3960
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   5
      Left            =   3120
      TabIndex        =   15
      Top             =   3720
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   5
      Left            =   120
      TabIndex        =   14
      Top             =   3720
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   4
      Left            =   3120
      TabIndex        =   13
      Top             =   3480
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   4
      Left            =   120
      TabIndex        =   12
      Top             =   3480
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   3
      Left            =   3120
      TabIndex        =   11
      Top             =   3240
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   3
      Left            =   120
      TabIndex        =   10
      Top             =   3240
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   2
      Left            =   3120
      TabIndex        =   9
      Top             =   3000
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   2
      Left            =   120
      TabIndex        =   8
      Top             =   3000
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   1
      Left            =   3120
      TabIndex        =   7
      Top             =   2760
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   1
      Left            =   120
      TabIndex        =   6
      Top             =   2760
      Width           =   2895
   End
   Begin VB.TextBox QuantityInput 
      Height          =   285
      Index           =   0
      Left            =   3120
      TabIndex        =   5
      Top             =   2520
      Width           =   735
   End
   Begin VB.TextBox ItemInput 
      Height          =   285
      Index           =   0
      Left            =   120
      TabIndex        =   4
      Top             =   2520
      Width           =   2895
   End
   Begin VB.Frame Frame3 
      Caption         =   "General"
      Height          =   1095
      Left            =   4440
      TabIndex        =   40
      Top             =   840
      Width           =   3735
      Begin VB.CheckBox IDispatch 
         Caption         =   "Use IDispatch Interface"
         Height          =   255
         Left            =   240
         TabIndex        =   26
         Top             =   720
         Width           =   3015
      End
      Begin VB.CheckBox WriteDB 
         Caption         =   "Update Database"
         Height          =   255
         Left            =   240
         TabIndex        =   25
         Top             =   360
         Width           =   3135
      End
   End
   Begin VB.TextBox ShipDSNInput 
      Height          =   285
      Left            =   5760
      TabIndex        =   33
      Text            =   "QCSampleShip"
      Top             =   5760
      Width           =   2415
   End
   Begin VB.TextBox OrderDSNInput 
      Height          =   285
      Left            =   5760
      TabIndex        =   32
      Text            =   "QCSampleOrder"
      Top             =   5280
      Width           =   2415
   End
   Begin VB.Frame Frame2 
      Caption         =   "Shipping"
      Height          =   735
      Left            =   4440
      TabIndex        =   35
      Top             =   2160
      Width           =   3735
      Begin VB.CheckBox Queued 
         Caption         =   "Queued Ship Component"
         Height          =   255
         Left            =   240
         TabIndex        =   27
         Top             =   360
         Width           =   2295
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Notification"
      Height          =   1815
      Left            =   4440
      TabIndex        =   34
      Top             =   3120
      Width           =   3735
      Begin VB.OptionButton QueuedPass 
         Caption         =   "Pass Queued Notify Component"
         Height          =   255
         Left            =   240
         TabIndex        =   31
         Top             =   1440
         Width           =   2655
      End
      Begin VB.OptionButton Pass 
         Caption         =   "Pass Notify Component, Not Queued"
         Height          =   255
         Left            =   240
         TabIndex        =   30
         Top             =   1080
         Width           =   3015
      End
      Begin VB.OptionButton QueuedNoPass 
         Caption         =   "No Interface Passing, Queued Component"
         Height          =   255
         Left            =   240
         TabIndex        =   29
         Top             =   720
         Width           =   3375
      End
      Begin VB.OptionButton NoPass 
         Caption         =   "No Interface Passing, Not Queued"
         Height          =   195
         Left            =   240
         TabIndex        =   28
         Top             =   360
         Value           =   -1  'True
         Width           =   2895
      End
   End
   Begin VB.CommandButton Process 
      Caption         =   "Process"
      Default         =   -1  'True
      Height          =   495
      Left            =   1320
      TabIndex        =   24
      Top             =   5400
      Width           =   1815
   End
   Begin VB.TextBox OrderInput 
      Height          =   285
      Left            =   1200
      TabIndex        =   3
      Top             =   1440
      Width           =   2655
   End
   Begin VB.Label Label8 
      Caption         =   "Quantity"
      Height          =   255
      Left            =   3120
      TabIndex        =   42
      Top             =   2160
      Width           =   975
   End
   Begin VB.Label Label7 
      Caption         =   "Item"
      Height          =   255
      Left            =   120
      TabIndex        =   41
      Top             =   2160
      Width           =   1095
   End
   Begin VB.Label Label6 
      Caption         =   "Customer Order"
      Height          =   375
      Left            =   120
      TabIndex        =   39
      Top             =   360
      Width           =   2895
   End
   Begin VB.Label Label5 
      Caption         =   "Execution Environment"
      Height          =   375
      Left            =   4440
      TabIndex        =   38
      Top             =   360
      Width           =   3015
   End
   Begin VB.Label Label4 
      Caption         =   "Ship Database"
      Height          =   255
      Left            =   4440
      TabIndex        =   37
      Top             =   5760
      Width           =   1215
   End
   Begin VB.Label Label3 
      Caption         =   "Order Database"
      Height          =   255
      Left            =   4440
      TabIndex        =   36
      Top             =   5280
      Width           =   1215
   End
   Begin VB.Label Label2 
      Caption         =   "Order Id"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   1440
      Width           =   1695
   End
   Begin VB.Label Label1 
      Caption         =   "Customer Id"
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   960
      Width           =   1575
   End
End
Attribute VB_Name = "InputForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Rem ==========================================================================
Rem
Rem This file is part of the Microsoft COM+ Samples.
Rem
Rem Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.
Rem
Rem This source code is intended only as a supplement to Microsoft
Rem Development Tools and/or on-line documentation. See these other
Rem materials for detailed information regarding Microsoft code samples.
Rem
Rem THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
Rem KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
Rem IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
Rem PARTICULAR PURPOSE.
Rem
Rem ==========================================================================

Option Explicit

Rem variables to hold context from form

Dim QueuedComponents As Boolean
Dim WriteDatabase As Boolean
Dim PassNotify As Boolean
Dim QueuedNotify As Boolean
Dim UseIDispatch As Boolean
Dim OrderDSN As String
Dim ShipDSN As String

Rem initialise all the state to match the default form state

Private Sub Form_Load()
    QueuedComponents = False
    WriteDatabase = False
    PassNotify = False
    QueuedNotify = False
    UseIDispatch = False
End Sub

Private Sub IDispatch_Click()
    UseIDispatch = IDispatch.Value
End Sub

Private Sub NoPass_Click()
    PassNotify = False
    QueuedNotify = False
End Sub

Private Sub QueuedNoPass_Click()
    PassNotify = False
    QueuedNotify = True
End Sub

Private Sub Pass_Click()
    PassNotify = True
    QueuedNotify = False
End Sub

Private Sub QueuedPass_Click()
    PassNotify = True
    QueuedNotify = True
End Sub

Private Sub Queued_Click()
    QueuedComponents = Queued.Value
End Sub

Private Sub WriteDB_Click()
    WriteDatabase = WriteDB.Value
End Sub

Private Sub Process_Click()
    Dim order As IOrder
    Dim Item(100) As String
    Dim Quantity(100) As Integer
    Dim LineItemCount As Integer
    Dim i
    
    LineItemCount = 0
    OrderDSN = OrderDSNInput.Text
    ShipDSN = ShipDSNInput.Text
    
    Rem We may get an error from the table creation
    Rem This is Ok, the tables may already exist
    
    On Error GoTo orderit
    
    If WriteDatabase Then
        Dim orderDB As New ADODB.Connection
        Dim shipDB As New ADODB.Connection
        
        orderDB.Open OrderDSN
        orderDB.Execute "create table QCSamp2Order (orderid int, custid int, linenum int, item varchar(255), quantity int, status varchar(25))"
        orderDB.Close
        Set orderDB = Nothing
        
        shipDB.Open ShipDSN
        shipDB.Execute "create table QCSamp2Ship (orderid int, custid int, linenum int, item varchar(255), quantity int)"
        shipDB.Close
        Set shipDB = Nothing
    End If
    
orderit:
    On Error GoTo 0
    
    Set order = CreateObject("QCOrder.IOrder")

    
    Rem setup execution environment
    order.NotifyQueued = QueuedNotify
    order.PassNotify = PassNotify
    order.ShipQueued = QueuedComponents
    order.WriteDB = WriteDatabase
    order.OrderDSN = OrderDSN
    order.ShipDSN = ShipDSN
    order.UseIDispatch = UseIDispatch
    
    Rem setup customer order
    order.CustomerId = CustomerInput.Text
    order.OrderId = OrderInput.Text
    
    Rem add the line items
    For i = ItemInput.LBound To ItemInput.UBound
        If (ItemInput.Item(i).Text <> "") And (QuantityInput.Item(i).Text <> "") Then
            Item(LineItemCount) = ItemInput.Item(i).Text
            Quantity(LineItemCount) = QuantityInput.Item(i).Text
            LineItemCount = LineItemCount + 1
        End If
    Next
    
    For i = 0 To LineItemCount - 1
        order.LineItem Item(i), Quantity(i)
    Next
    
    Rem go for it
    order.Process
    
    Set order = Nothing

End Sub

