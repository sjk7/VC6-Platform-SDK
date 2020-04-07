VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 2  'RequiresTransaction
END
Attribute VB_Name = "IShip"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Rem ==========================================================================
Rem
Rem This file is part of the Microsoft COM+ Samples.
Rem
Rem Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.
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
Dim m_bNotifyExists As Boolean
Dim m_bNotifyQueued As Boolean
Dim m_bIDispatch As Boolean
Dim m_strShipDSN As String
Dim m_strOrderDSN As String

Rem Properties relating to customer order
Dim m_lCustomerId As Long
Dim m_lOrderId As Long
Dim m_astrItem(100) As String
Dim m_alQuantity(100) As Long
Dim m_lItemCount As Long

Public Property Let WriteDB(ByVal bWriteDB As Boolean)
    m_bWriteDB = bWriteDB
End Property

Public Property Let UseIDispatch(ByVal bIDispatch As Boolean)
    m_bIDispatch = bIDispatch
End Property

Public Property Let NotifyExists(ByVal bNotifyExists As Boolean)
    m_bNotifyExists = bNotifyExists
End Property

Public Property Let NotifyQueued(ByVal bNotifyQueued As Boolean)
    m_bNotifyQueued = bNotifyQueued
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

Public Sub Process(ByVal notify As Object)
    Dim objContext As ObjectContext
    Dim tonotify As INotify
    Dim tonotifyObject As Object
    Dim i

    If m_bWriteDB Then
        WriteShipDB
    End If

    If m_bNotifyExists Then
        Set tonotify = notify
    Else
        If m_bNotifyQueued Then
            Set tonotify = CreateObject("queue:/new:QCNotify.INotify")
        Else
            Set tonotify = CreateObject("QCNotify.INotify")
        End If
    End If
    
    If m_bIDispatch Then
    
        Set tonotifyObject = tonotify
    
        tonotifyObject.WriteDB = m_bWriteDB
        tonotifyObject.OrderDSN = m_strOrderDSN
        tonotifyObject.CustomerId = m_lCustomerId
        tonotifyObject.OrderId = m_lOrderId
        
        For i = 0 To m_lItemCount - 1
            tonotifyObject.LineItem m_astrItem(i), m_alQuantity(i)
        Next
        
        tonotifyObject.Process
    
    Else
    
        tonotify.WriteDB = m_bWriteDB
        tonotify.OrderDSN = m_strOrderDSN
        tonotify.CustomerId = m_lCustomerId
        tonotify.OrderId = m_lOrderId
        
        For i = 0 To m_lItemCount - 1
            tonotify.LineItem m_astrItem(i), m_alQuantity(i)
        Next
        
        tonotify.Process
    
    End If
    
    Set objContext = GetObjectContext()
    objContext.SetComplete
   
End Sub

Private Sub WriteShipDB()
    Dim shipDB As New ADODB.Connection
    Dim sqlStmt As String
    Dim i

    shipDB.Open m_strShipDSN
    
    For i = 0 To m_lItemCount - 1
    
        sqlStmt = "insert into QCSamp2Ship (orderid, custid, linenum, item, quantity) values (" + _
                  Str$(m_lOrderId) + "," + Str$(m_lCustomerId) + "," + Str$(i) + _
                  ", '" + m_astrItem(i) + "'," + Str$(m_alQuantity(i)) + ")"
    
        shipDB.Execute sqlStmt
    Next
    
    shipDB.Close

    Set shipDB = Nothing
End Sub

Private Sub Class_Initialize()
    m_bWriteDB = False
    m_bNotifyExists = False
    m_bNotifyQueued = False
    m_bIDispatch = False
    m_strShipDSN = ""
    m_strOrderDSN = ""
    m_lItemCount = 0
End Sub
