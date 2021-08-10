Attribute VB_Name = "modCommon"
Option Explicit

Global Const LMEM_FIXED = &H0
Global Const LMEM_ZEROINIT = &H40
Global Const LPTR = (LMEM_FIXED Or LMEM_ZEROINIT)

Global Const ERROR_BUFFER_TOO_SMALL = 603

' Function prototype for RtlMoveMemory
Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
         hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)

' Function prototype for LocalAlloc
Declare Function LocalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long

' Function prototype for LocalFree
Declare Function LocalFree Lib "kernel32" (ByVal hMem As Long) As Long

'Declaration for lstrcpyn() API
Declare Function lstrcpyn Lib "kernel32" Alias "lstrcpynA" _
    (lpString1 As Any, ByVal lpString2 As String, ByVal iMaxLen As Integer) As Long

'Declaration for lstrcmp() API
Declare Function lstrcmp Lib "kernel32" Alias "lstrcmpA" _
    (ByVal lpString1 As Any, ByVal lpString2 As Any) As Long
    
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

' This procedure adds the 2 Framing Protocols to the combo box
Sub GetFrameProtocols(lst As ComboBox)
    lst.AddItem "PPP: Windows 95/98/NT/2000, Internet"
    lst.AddItem "SLIP: Unix"
End Sub
