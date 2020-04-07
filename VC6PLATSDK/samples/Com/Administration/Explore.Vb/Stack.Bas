Attribute VB_Name = "basStack"
' ----------------------------------------------------------------------------
' 
' This file is part of the Microsoft COM+ Samples.
' 
' Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
' 
' This source code is intended only as a supplement to Microsoft
' Development Tools and/or on-line documentation. See these other
' materials for detailed information regarding Microsoft code samples.
' 
' THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
' KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
' IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
' 
' ----------------------------------------------------------------------------

Option Explicit

    Private Const kDefaultStackBase As Integer = 0
    Private Const kDefaultStackTop  As Integer = 10
    
    Private m_Stack()       As Object
    Private m_iStackTop     As Integer
    Private m_bInitialized  As Boolean
   
Public Sub ReleaseStack()

    Dim iPtr As Integer
    
    'Continue only if we have a previously initialized stack
    If Not m_bInitialized Then Exit Sub
    
    'Release references to each of the objects held on the stack
    For iPtr = UBound(m_Stack) To LBound(m_Stack) Step -1
        Set m_Stack(iPtr) = Nothing
    Next
    
    Erase m_Stack

    m_bInitialized = False
    
    Exit Sub
    
End Sub

Private Function GetMaxStackElements() As Integer

    'Default return value
    GetMaxStackElements = 0
    
    'No need to calculate the size of the stack if it isn't initialized
    If Not m_bInitialized Then Exit Function
    
    GetMaxStackElements = UBound(m_Stack) - LBound(m_Stack) + 1
    
    Exit Function
    
End Function

Private Sub ResizeStack()
    
    'Do not attempt to resize an uninitalized stack
    If Not m_bInitialized Then Exit Sub
    
    'Increase the stack size while preserving the contents
    ReDim Preserve m_Stack(0 To UBound(m_Stack) + 5) As Object

    Exit Sub
    
End Sub

Public Sub InitStack()

    Dim iPtr As Integer
    
    'Handle initialization of a previously active stack
    If m_bInitialized Then
        ReleaseStack
    End If
    
    'Right size the array to the default size
    ReDim m_Stack(kDefaultStackBase To kDefaultStackTop) As Object
    
    'Set the current stack top (i.e., the stack is empty)
    m_iStackTop = -1
    
    'The stack object is now ready for use, toggle the flag
    m_bInitialized = True
    
    Exit Sub
    
End Sub

Public Sub Push(obj As Object)

    'Make sure we have initialized the stack before adding to it
    If Not m_bInitialized Then
        InitStack
    End If
    
    'Set the new "top level" on the stack
    m_iStackTop = m_iStackTop + 1

    'Bounds check the stack and resize if necessary
    If m_iStackTop >= GetMaxStackElements() Then
        ResizeStack
    End If
    
    'Add the item to the stack
    Set m_Stack(m_iStackTop) = obj
    
    Exit Sub
    
End Sub

Public Function Pop() As Object

    'Default return value
    Set Pop = Nothing
    
    'Continue only if we have a previously initialized stack with
    If (Not m_bInitialized) Or (m_iStackTop < 0) Then Exit Function
    
    'Set the return value
    Set Pop = m_Stack(m_iStackTop)
    
    'Remove the item from the stack
    Set m_Stack(m_iStackTop) = Nothing
    
    'Decrement the stack pointer
    m_iStackTop = m_iStackTop - 1
    
    Exit Function
    
End Function


