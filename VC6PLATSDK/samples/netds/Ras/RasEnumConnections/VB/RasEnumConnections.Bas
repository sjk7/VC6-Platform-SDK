Attribute VB_Name = "Module1"
'Needed constants
Global Const LMEM_FIXED = &H0
Global Const LMEM_ZEROINIT = &H40
Global Const LPTR = (LMEM_FIXED Or LMEM_ZEROINIT)

Global Const ERROR_BUFFER_TOO_SMALL = 603
Global Const RAS_MaxEntryName = 256
Global Const RAS_MaxDeviceType = 16
Global Const RAS_MaxDeviceName = 128



Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" ( _
         hpvDest As Any, hpvSource As Any, ByVal cbCopy As Long)

' Function prototype for LocalAlloc
Declare Function LocalAlloc Lib "kernel32" (ByVal wFlags As Long, ByVal dwBytes As Long) As Long

' Function prototype for LocalFree
Declare Function LocalFree Lib "kernel32" (ByVal hMem As Long) As Long


Public Type rasconn
    'set dwsize to 412 (size of this RASCONN structure/Type)
    dwSize As Long
    hRasConn As Long
    szEntryName(RAS_MaxEntryName) As Byte
    szDeviceType(RAS_MaxDeviceType) As Byte
    szDeviceName(RAS_MaxDeviceName) As Byte
End Type

Public Declare Function RasEnumConnections Lib "RASAPI32.DLL" _
    Alias "RasEnumConnectionsA" ( _
                                 lprasconn As Any, _
                                 lpcb As Long, _
                                 lpcConnections As Long) As Long

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
