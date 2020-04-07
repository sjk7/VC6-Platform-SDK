VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 2  'RequiresTransaction
END
Attribute VB_Name = "IOrder"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
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

Rem Properties relating to execution environment
Dim m_bWriteDB As Boolean
Dim m_bPassNotify As Boolean
Dim m_bNotifyQueued As Boolean
Dim m_bShipQueued As Boolean
Dim m_bIDispatch As Boolean
Dim m_strShipDSN As String
Dim m_strOrderDSN As String

Rem Properties relating to customer order
Dim m_lCustomerId As Long
Dim m_lOrderId As Long
Dim m_astrItem(100) As String
Dim m_alQuantity(100) As Long
Dim m_lItemCount As Long


Dim mon As IStatus




Public Property Let WriteDB(ByVal bWriteDB As Boolean)
    m_bWriteDB = bWriteDB
End Property

Public Property Let UseIDispatch(ByVal bIDispatch As Boolean)
    m_bIDispatch = bIDispatch
End Property

Public Property Let PassNotify(ByVal bPassNotify As Boolean)
    m_bPassNotify = bPassNotify
End Property

Public Property Let NotifyQueued(ByVal bNotifyQueued As Boolean)
    m_bNotifyQueued = bNotifyQueued
End Property

Public Property Let ShipQueued(ByVal bShipQueued As Boolean)
    m_bShipQueued = bShipQueued
End Property

Public Property Let ShipDSN(ByVal strShipDSN As String)
    m_strShipDSN = strShipDSN
End Property

Public Property Let OrderDSN(ByVal strOrderDSN As String)
    m_strOrderDSN = strOrderDSN
End Property

Public Property Let CustomerId(ByVal lCustomerId As Long)
    m_lCustomerId = lCustomerId
End Property

Public Property Let OrderId(ByVal lOrderId As Long)
    m_lOrderId = lOrderId
End Property

Public Sub LineItem(ByVal strItem As String, ByVal lQuantity As Long)
    m_astrItem(m_lItemCount) = strItem
    m_alQuantity(m_lItemCount) = lQuantity
    m_lItemCount = m_lItemCount + 1
End Sub

Public Sub Process()
    Dim Ship As Object
    Dim Notify As Object
    Dim ShipObject As Object
    Dim objContext As ObjectContext
    Dim i
    
    If m_bWriteDB Then
        WriteOrderDB
    End If
    
    If m_bPassNotify Then
        If m_bNotifyQueued Then
            Set Notify = CreateObject("queue:/new:QCNotify.INotify")
        Else
            Rem NOTE: Call new so that we do not have to initialize the
            Rem notify object before passing it... the VB runtime does it for us
            Set Notify = New INotify
        End If
    End If
    
    If m_bShipQueued Then
        mon.MethodCall "Order", "Queued"
        Set Ship = CreateObject("queue:/new:QCShip.IShip")
    Else
        mon.MethodCall "Order", "Direct"
        Set Ship = CreateObject("QCShip.IShip")
    End If
    
    If m_bIDispatch Then
        Set ShipObject = Ship
    
        Rem setup environment
        ShipObject.NotifyExists = m_bPassNotify
        ShipObject.NotifyQueued = m_bNotifyQueued
        ShipObject.OrderDSN = m_strOrderDSN
        ShipObject.ShipDSN = m_strShipDSN
        ShipObject.WriteDB = m_bWriteDB
        ShipObject.UseIDispatch = m_bIDispatch
        
        Rem set up customer order
        ShipObject.CustomerId = m_lCustomerId
        ShipObject.OrderId = m_lOrderId
        For i = 0 To m_lItemCount - 1
            ShipObject.LineItem m_astrItem(i), m_alQuantity(i)
        Next
        
        Rem go for it!

        ShipObject.Process Notify
        
    Else
        
        Rem setup environment
        Ship.NotifyExists = m_bPassNotify
        Ship.NotifyQueued = m_bNotifyQueued
        Ship.OrderDSN = m_strOrderDSN
        Ship.ShipDSN = m_strShipDSN
        Ship.WriteDB = m_bWriteDB
        Ship.UseIDispatch = m_bIDispatch
        
        Rem set up customer order
        Ship.CustomerId = m_lCustomerId
        Ship.OrderId = m_lOrderId
        For i = 0 To m_lItemCount - 1
            Ship.LineItem m_astrItem(i), m_alQuantity(i)
        Next
        
        Rem go for it!
        Ship.Process Notify
    
    End If
    
    Set objContext = GetObjectContext()
    objContext.SetComplete
    
End Sub

Private Sub WriteOrderDB()
    Dim orderDB As New ADODB.Connection
    Dim sqlStmt As String
    Dim i
    
    orderDB.Open m_strOrderDSN
    
    For i = 0 To m_lItemCount - 1
        sqlStmt = "insert into QCSamp2Order (orderid, custid, linenum, item, quantity, status) values (" _
                   + Str$(m_lOrderId) + "," + Str$(m_lCustomerId) + "," + Str$(i) _
                   + ", '" + m_astrItem(i) + "'," + Str$(m_alQuantity(i)) + ", 'Ordered')"
            
        orderDB.Execute sqlStmt
    Next
    
    orderDB.Close
    
    Set orderDB = Nothing
End Sub

Private Sub Class_Initialize()
    m_bWriteDB = False
    m_bPassNotify = False
    m_bNotifyQueued = False
    m_bShipQueued = False
    m_bIDispatch = False
    m_strShipDSN = ""
    m_strOrderDSN = ""
    m_lItemCount = 0
    
    Set mon = GetObject("", "QCMonitor.IStatus")
    mon.AppEvent "Order", "start"
    
End Sub

Private Sub Class_Terminate()
    
    mon.AppEvent "Order", "stop"
End Sub
