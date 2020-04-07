Attribute VB_Name = "GuidHelp"
Option Explicit

' Declare some GUID handling helper functions
Declare Function CoCreateGuid Lib "ole32.dll" (pGUID As GUID) As Long
Declare Function CLSIDFromProgID Lib "ole32.dll" (ByVal lpszProgID As Long, pCLSID As Any) As Long
Declare Function StringFromGUID2 Lib "ole32.dll" (rguid As Any, ByVal lpstrCLSID As Long, ByVal cbMax As Long) As Long
Declare Sub CoTaskMemFree Lib "ole32.dll" (pv As Long)
Public Type GUID
   GUID1  As Long
   GUID2  As Integer
   GUID3  As Integer
   GUID4(7)  As Byte
End Type
Function NewGuid() As String
    Dim bytGUID()         As Byte
    Dim udtGUID           As GUID
    Dim lHR        As Long
    Dim lngLen       As Long
    Dim strGUID As String
    
    lHR = CoCreateGuid(udtGUID)
    
    lngLen = 40
    bytGUID = String(lngLen, 0)
    lHR = StringFromGUID2(udtGUID, VarPtr(bytGUID(0)), lngLen)
    
    strGUID = bytGUID
    If InStr(strGUID, Chr(0)) > 1 Then strGUID = Left(strGUID, InStr(strGUID, Chr(0)) - 1)
    NewGuid = strGUID

    
End Function
Function sCLSIDFromProgID(sProgID As String) As String
    Dim udtGUID           As GUID
    Dim strGUID      As String
    Dim bytProgID() As Byte
    Dim bytGUID()         As Byte
    Dim lHR        As Long
    Dim lngLen       As Long

    ' Gather the CLSID of the VB Subscriber
    lngLen = 40
    bytGUID = String(lngLen, 0)
    bytProgID = String(100, 0)
    bytProgID = sProgID & Chr(0)
    lHR = CLSIDFromProgID(VarPtr(bytProgID(0)), udtGUID)
    If (lHR <> 0) Then
         Err.Raise lHR, "Form_Load", "CLSIDFromProgID Error"
    End If
    lHR = StringFromGUID2(udtGUID, VarPtr(bytGUID(0)), lngLen)
    strGUID = bytGUID
    sCLSIDFromProgID = Left(strGUID, InStr(strGUID, Chr(0)) - 1)
    
End Function
