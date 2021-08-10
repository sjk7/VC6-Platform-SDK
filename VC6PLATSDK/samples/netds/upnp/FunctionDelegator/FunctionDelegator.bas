Attribute VB_Name = "modFunctionDelegator"
'***************************************************************
' (c) Copyright 2000 Matthew J. Curland
'
' This file is from the CD-ROM accompanying the book:
' Advanced Visual Basic 6: Power Techniques for Everyday Programs
'   Author: Matthew Curland
'   Published by: Addison-Wesley, July 2000
'   ISBN: 0-201-70712-8
'   http://www.PowerVB.com
'
' You are entitled to license free distribution of any application
'   that uses this file if you own a copy of the book, or if you
'   have obtained the file from a source approved by the author. You
'   may redistribute this file only with express written permission
'   of the author.
'
' This file depends on:
'   References:
'     VBoostTypes6.olb (VBoost Object Types (6.0))
'   Files:
'     None
'   Minimal VBoost conditionals:
'     None
'
' Conditional Compilation Values:
'   FUNCTIONDELEGATOR_NOSTACK = 1 'eliminates support for NewDelegator
'   FUNCTIONDELEGATOR_NOHEAP = 1  'eliminates support for InitDelegator
'
' This file is discussed in Chapter 11.
'***************************************************************
Option Explicit

'Here's the magic asm for doing the function pointer call.
'The stack comes in with the following:
'esp: return address
'esp + 4: this pointer for FunctionDelegator
'All that we need to do is remove the this pointer from the
'stack, replace it with the return address, then jmp to the
'correct function.  In other words, we're just squeezing the
'this pointer completely out of the picture.
'The code is:
'pop ecx (stores return address)
'pop eax (gets the this pointer)
'push ecx (restores the return address)
'jmp DWORD PTR [eax + 4] (jump to address at this + 4, 3 byte instruction)
'The corresponding byte stream for this is: 59 58 51 FF 60 04
'We pad these six bytes with two int 3 commands (CC CC) to get eight
'bytes, which can be stored in a Currency constant.
'Note that the memory location of this constant is not executable, so
'it must be copied into a currency variable.  The address of the variable
'is then used as the forwarding function.

#Const STACKALLOCSUPPORT = FUNCTIONDELEGATOR_NOSTACK = 0
#Const HEAPALLOCSUPPORT = FUNCTIONDELEGATOR_NOHEAP = 0

Private Const cDelegateASM As Currency = -368956918007638.6215@

Private m_DelegateASM As Currency

Private Type DelegatorVTables
    VTable(7) As Long 'OKQI vtable in 0 to 3, FailQI vtable in 4 to 7
End Type

#If STACKALLOCSUPPORT Then
'Structure for a stack allocated Delegator
Private m_VTables As DelegatorVTables
Private m_pVTableOKQI As Long       'Pointer to vtable, no allocation version
Private m_pVTableFailQI As Long     'Pointer to vtable, no allocation version
Public Type FunctionDelegator
    pVTable As Long  'This has to stay at offset 0
    pfn As Long      'This has to stay at offset 4
End Type
#End If 'STACKALLOCSUPPORT

#If HEAPALLOCSUPPORT Then
'Structure for a heap allocated Delegator
Private m_VTablesHeapAlloc As DelegatorVTables
Private m_pVTableHeapAllocOKQI As Long   'Pointer to vtable, heap version
Private m_pVTableHeapAllocFailQI As Long 'Pointer to vtable, heap version
Private Type FunctionDelegatorHeapAlloc
    pVTable As Long  'This has to stay at offset 0
    pfn As Long      'This has to stay at offset 4
    cRefs As Long
End Type
#End If 'HEAPALLOCSUPPORT

#If STACKALLOCSUPPORT Then
'Functions to initialize a Delegator object on an existing FunctionDelegator
Public Function InitDelegator(Delegator As FunctionDelegator, Optional ByVal pfn As Long) As IUnknown
    If m_pVTableOKQI = 0 Then InitVTables
    With Delegator
        .pVTable = m_pVTableOKQI
        .pfn = pfn
    End With
    CopyMemory InitDelegator, VarPtr(Delegator), 4
End Function
Private Sub InitVTables()
Dim pAddRefRelease As Long
    With m_VTables
        .VTable(0) = FuncAddr(AddressOf QueryInterfaceOK)
        .VTable(4) = FuncAddr(AddressOf QueryInterfaceFail)
        pAddRefRelease = FuncAddr(AddressOf AddRefRelease)
        .VTable(1) = pAddRefRelease
        .VTable(5) = pAddRefRelease
        .VTable(2) = pAddRefRelease
        .VTable(6) = pAddRefRelease
        m_DelegateASM = cDelegateASM
        .VTable(3) = VarPtr(m_DelegateASM)
        .VTable(7) = .VTable(3)
        m_pVTableOKQI = VarPtr(.VTable(0))
        m_pVTableFailQI = VarPtr(.VTable(4))
    End With
End Sub
Private Function QueryInterfaceOK(This As FunctionDelegator, riid As Long, pvObj As Long) As Long
    pvObj = VarPtr(This)
    This.pVTable = m_pVTableFailQI
End Function
Private Function AddRefRelease(ByVal This As Long) As Long
    'Nothing to do, memory not refcounted
End Function
#End If 'STACKALLOCSUPPORT

#If HEAPALLOCSUPPORT Then
'Functions to create a refcounted version of the function pointer wrapper object
Public Function NewDelegator(ByVal pfn As Long) As IUnknown
Dim Struct As FunctionDelegatorHeapAlloc
Dim ThisPtr As Long
    If m_pVTableHeapAllocOKQI = 0 Then InitHeapAllocVTables
    With Struct
        ThisPtr = CoTaskMemAlloc(LenB(Struct))
        If ThisPtr = 0 Then Err.Raise 7
        .pVTable = m_pVTableHeapAllocOKQI
        .cRefs = 1
        .pfn = pfn
        CopyMemory ByVal ThisPtr, Struct, LenB(Struct)
        CopyMemory NewDelegator, ThisPtr, 4
    End With
End Function
Private Sub InitHeapAllocVTables()
    With m_VTablesHeapAlloc
        .VTable(0) = FuncAddr(AddressOf QueryInterfaceHeapAllocOK)
        .VTable(4) = FuncAddr(AddressOf QueryInterfaceFail)
        .VTable(1) = FuncAddr(AddressOf AddRefHeapAlloc)
        .VTable(5) = .VTable(1)
        .VTable(2) = FuncAddr(AddressOf ReleaseHeapAlloc)
        .VTable(6) = .VTable(2)
        m_DelegateASM = cDelegateASM
        .VTable(3) = VarPtr(m_DelegateASM)
        .VTable(7) = .VTable(3)
        m_pVTableHeapAllocOKQI = VarPtr(.VTable(0))
        m_pVTableHeapAllocFailQI = VarPtr(.VTable(4))
    End With
End Sub
Private Function QueryInterfaceHeapAllocOK(This As FunctionDelegatorHeapAlloc, riid As Long, pvObj As Long) As Long
    With This
        pvObj = VarPtr(.pVTable)
        .cRefs = .cRefs + 1
        .pVTable = m_pVTableHeapAllocFailQI
    End With
End Function
Private Function AddRefHeapAlloc(This As FunctionDelegatorHeapAlloc) As Long
    With This
        .cRefs = .cRefs + 1
        AddRefHeapAlloc = .cRefs
    End With
End Function
Private Function ReleaseHeapAlloc(This As FunctionDelegatorHeapAlloc) As Long
    With This
        .cRefs = .cRefs - 1
        ReleaseHeapAlloc = .cRefs
        If .cRefs = 0 Then
            'Don't try to step over FreeBuffer, we're freeing
            'This, and the debugger could die.
            CoTaskMemFree VarPtr(.pVTable)
        End If
    End With
End Function
#End If 'HEAPALLOCSUPPORT

Private Function QueryInterfaceFail(ByVal This As Long, riid As Long, pvObj As Long) As Long
    pvObj = 0
    QueryInterfaceFail = E_NOINTERFACE
End Function

Private Function FuncAddr(ByVal pfn As Long) As Long
    FuncAddr = pfn
End Function

