Attribute VB_Name = "Module1"
Option Explicit

' Constants needed for LocalAlloc
Global Const LMEM_FIXED = &H0
Global Const LMEM_ZEROINIT = &H40
Global Const LPTR = (LMEM_FIXED Or LMEM_ZEROINIT)

Global Const ERROR_BUFFER_TOO_SMALL = 603

' Constant needed for RASENTRYNAME
Global Const RAS_MaxEntryName = 256

' Function prototype for RasEnumEntries
Declare Function RasEnumEntries Lib "rasapi32.dll" Alias "RasEnumEntriesA" ( _
            ByVal reserved As String, _
            ByVal szPhoneBook As String, _
            lpRasEntries As Any, _
            lpcb As Long, _
            lpcEntries As Long) As Long
    
' Type definition for RASENTRYNAME
Type RASENTRYNAME
    dwSize As Long
    szEntryName(RAS_MaxEntryName) As Byte
End Type

' Function prototype for CopyMemory
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
            hpvDest As Any, _
            hpvSource As Any, _
            ByVal cbCopy As Long)

' Function prototype for LocalAlloc
Declare Function LocalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long

' Function prototype for LocalFree
Declare Function LocalFree Lib "kernel32" (ByVal hMem As Long) As Long


' Subroutine to list the phonebook entries
Sub GetEntries(lst As ComboBox)
    Dim tRasEntryName As RASENTRYNAME
    Dim cb As Long
    Dim cEntries As Long
    Dim t_Buff As Long
    Dim t_ptr As Long
    Dim nRet As Long
    Dim i As Long
    
    cb = LenB(tRasEntryName)
    
    ' Initialize the dwSize field
    tRasEntryName.dwSize = cb
    
    ' Allocate input buffer with enough room for at least one structure
    t_Buff = LocalAlloc(LPTR, cb)
    
    If (t_Buff) Then
        ' Initialize the first entry
        ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
        ' to CopyMemory because VB passes parameters by reference by default
        Call CopyMemory(ByVal t_Buff, tRasEntryName, LenB(tRasEntryName))
        
        ' Call RasEnumEntries to enumerate the phonebook entries
        ' in the default system phonebook
        nRet = RasEnumEntries(vbNullString, vbNullString, ByVal t_Buff, cb, cEntries)
        
        'Check return value
        If (ERROR_BUFFER_TOO_SMALL = nRet And cb <> 0) Then
            Call LocalFree(t_Buff)
            t_Buff = LocalAlloc(LPTR, cb)
        ElseIf (0 <> nRet) Then
            Call MsgBox(("RasEnumEntries failed: Error = " & CStr(nRet)), , "Error")
            Call LocalFree(t_Buff)
            Exit Sub
        End If
        
        If (t_Buff) Then
            If (nRet <> 0) Then
                Call CopyMemory(ByVal t_Buff, tRasEntryName, LenB(tRasEntryName))
                
                ' Call RasEnumEntries to enumerate the phonebook entries
                ' in the default system phonebook
                nRet = RasEnumEntries(vbNullString, vbNullString, ByVal t_Buff, cb, cEntries)
            End If
            
            If nRet = 0 Then ' RasEnumEntries returned success
                t_ptr = t_Buff
                
                ' Copy the values of the first entry
                Call CopyMemory(tRasEntryName, ByVal t_ptr, LenB(tRasEntryName))
                
                ' Add phonebook entries to the combo box
                For i = 1 To cEntries
                    Call CopyMemory(tRasEntryName, ByVal t_ptr, LenB(tRasEntryName))
                    lst.AddItem (ByteToString(tRasEntryName.szEntryName))
                    t_ptr = t_ptr + tRasEntryName.dwSize
                Next i
            Else
                Call MsgBox(("RasEnumEntries failed = ") + CStr(nRet), , "Error")
            End If
            
            ' Free the allocated input buffer
            Call LocalFree(t_Buff)
            
        Else ' RasEnumEntries returned an error
            Call MsgBox(("LocalAlloc failed!"), , "Error")
        End If
        
       
    Else
        Call MsgBox(("LocalAlloc failed!"), , "Error")
    End If
    
End Sub

' This function takes in a Byte array and converts into a String
Function ByteToString(bytearray() As Byte) As String
    Dim i As Integer, t As String
    i = 0
    t = ""
    While i < UBound(bytearray) And bytearray(i) <> 0
        t = t & Chr$(bytearray(i))
        i = i + 1
    Wend
    ByteToString = t
End Function
