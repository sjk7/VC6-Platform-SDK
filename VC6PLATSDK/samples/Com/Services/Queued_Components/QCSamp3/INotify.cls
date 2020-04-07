VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 1  'Persistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 2  'RequiresTransaction
END
Attribute VB_Name = "INotify"
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
Dim m_strOrderDSN As String
Dim m_bWriteDB As Boolean

Rem Properties relating to order
Dim m_lOrderId As Long
Dim m_lCustomerId As Long
Dim m_astrItem(100) As String
Dim m_alQuantity(100) As Long
Dim m_lItemCount As Long

Public Property Let OrderDSN(ByVal strOrderDSN As String)
    m_strOrderDSN = strOrderDSN
End Property

Public Property Let WriteDB(ByVal bWriteDB As Boolean)
    m_bWriteDB = bWriteDB
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
    Dim objContext As ObjectContext
    
    If m_bWriteDB Then
        UpdateOrderDB
    End If
      
    MsgBox "Completed order " + Str$(m_lOrderId) + " for customer " + Str$(m_lCustomerId)
    Set objContext = GetObjectContext()
    objContext.SetComplete

End Sub

Private Sub UpdateOrderDB()
    Dim orderDB As New ADODB.Connection
    Dim sqlStmt As String
    Dim i
    
    orderDB.Open m_strOrderDSN
    
    For i = 0 To m_lItemCount - 1
    
        sqlStmt = "update QCSamp2Order set status = 'shipped' where orderid = " + _
                  Str$(m_lOrderId) + " and custid = " + Str$(m_lCustomerId) + _
                  " and linenum = " + Str$(i) + " and item = '" + m_astrItem(i) + "'"
                
        orderDB.Execute sqlStmt
    
    Next
    
    orderDB.Close
    
End Sub

Private Sub Class_Initialize()
    m_lCustomerId = 0
    m_lOrderId = 0
    m_bWriteDB = False
    m_strOrderDSN = ""
    m_lItemCount = 0
End Sub

Private Sub Class_InitProperties()
    m_lCustomerId = 0
    m_lOrderId = 0
    m_bWriteDB = False
    m_strOrderDSN = ""
    m_lItemCount = 0
End Sub

Private Sub Class_ReadProperties(PropBag As PropertyBag)
    Dim i
    m_lCustomerId = PropBag.ReadProperty("CustomerId", 99)
    m_lOrderId = PropBag.ReadProperty("OrderId", 99)
    m_strOrderDSN = PropBag.ReadProperty("OrderDSN", "")
    m_bWriteDB = PropBag.ReadProperty("WriteDB", False)
    m_lItemCount = PropBag.ReadProperty("ItemCount", 0)
    For i = 0 To m_lItemCount - 1
        m_astrItem(i) = PropBag.ReadProperty("Item" + Str$(i), "BadItem")
        m_alQuantity(i) = PropBag.ReadProperty("Quantity" + Str$(i), -1)
    Next
End Sub

Private Sub Class_WriteProperties(PropBag As PropertyBag)
    Dim i
    Call PropBag.WriteProperty("CustomerId", m_lCustomerId, 88)
    Call PropBag.WriteProperty("OrderId", m_lOrderId, 88)
    Call PropBag.WriteProperty("OrderDSN", m_strOrderDSN, "")
    Call PropBag.WriteProperty("WriteDB", m_bWriteDB, False)
    Call PropBag.WriteProperty("ItemCount", m_lItemCount, 0)
    For i = 0 To m_lItemCount - 1
        Call PropBag.WriteProperty("Item" + Str$(i), m_astrItem(i), "BadItem")
        Call PropBag.WriteProperty("Quantity" + Str$(i), m_astrItem(i), -1)
    Next
End Sub
