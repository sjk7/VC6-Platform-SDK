Attribute VB_Name = "modRasGetCountryInfo"
Option Explicit

'Type declaration for RASCTRYINFO structure
Public Type RASCTRYINFO
    dwSize As Long
    dwCountryID As Long
    dwNextCountryID As Long
    dwCountryCode As Long
    dwCountryNameOffset As Long
End Type

'Declaration fro RasGetCountryInfo API
Declare Function RasGetCountryInfo Lib "rasapi32" Alias _
    "RasGetCountryInfoA" (lpRasCtryInfo As Long, _
                          lpdwSize As Long) As Long
  
Sub GetCountryCode(lst As ComboBox, CountryCode As Long, CountryID As Long)
    Dim tRasCtryInfo As RASCTRYINFO
    Dim lSize As Long
    Dim nRet As Long
    Dim t_Buff As Long
    Dim t_ptr As Long
    Dim n As Integer
    Dim CountryName(256) As Byte
    Dim t_CountryName1 As String, t_CountryName2 As String
    
    t_CountryName2 = lst
    t_Buff = LocalAlloc(LPTR, 256)
    tRasCtryInfo.dwCountryID = 1
    
    If (t_Buff) Then
        Do While (tRasCtryInfo.dwCountryID <> 0)
            tRasCtryInfo.dwSize = LenB(tRasCtryInfo)
            lSize = 256
            Call CopyMemory(ByVal t_Buff, tRasCtryInfo, LenB(tRasCtryInfo))
        
            nRet = RasGetCountryInfo(ByVal t_Buff, lSize)
            If (nRet <> 0) Then
                MsgBox ("RasGetCountryInfo failed: Error = " & nRet), , "Error"
                Call LocalFree(t_Buff)
                Exit Sub
            End If
            
            Call CopyMemory(tRasCtryInfo, ByVal t_Buff, LenB(tRasCtryInfo))
            t_ptr = t_Buff + tRasCtryInfo.dwCountryNameOffset
            n = lSize - tRasCtryInfo.dwCountryNameOffset
        
            Call CopyMemory(CountryName(0), ByVal t_ptr, n)
        
            t_CountryName1 = (ByteToString(CountryName)) + " (" + Str(tRasCtryInfo.dwCountryCode) + " )"
            If t_CountryName1 = t_CountryName2 Then
                CountryCode = tRasCtryInfo.dwCountryCode
                CountryID = tRasCtryInfo.dwCountryID
                
                Call LocalFree(t_Buff)
                Exit Sub
            End If
            tRasCtryInfo.dwCountryID = tRasCtryInfo.dwNextCountryID
        Loop
        
        Call LocalFree(t_Buff)
    End If
    
End Sub

Sub GetCountryInfo(lst As ComboBox)
    Dim tRasCtryInfo As RASCTRYINFO
    Dim lSize As Long
    Dim nRet As Long
    Dim t_Buff As Long
    Dim tptr As Long
    Dim n As Integer
    Dim CountryName(256) As Byte
        
    t_Buff = LocalAlloc(LPTR, 256)
    tRasCtryInfo.dwCountryID = 1
    
    If (t_Buff) Then
        Do While (tRasCtryInfo.dwCountryID <> 0)
            tRasCtryInfo.dwSize = LenB(tRasCtryInfo)
            lSize = 256
            Call CopyMemory(ByVal t_Buff, tRasCtryInfo, LenB(tRasCtryInfo))
        
            nRet = RasGetCountryInfo(ByVal t_Buff, lSize)
            If (nRet <> 0) Then
                MsgBox ("RasGetCountryInfo failed: Error = " & nRet), , "Error"
                Call LocalFree(t_Buff)
                Exit Sub
            End If
            
            Call CopyMemory(tRasCtryInfo, ByVal t_Buff, LenB(tRasCtryInfo))
            tptr = t_Buff + tRasCtryInfo.dwCountryNameOffset
            n = lSize - tRasCtryInfo.dwCountryNameOffset
        
            Call CopyMemory(CountryName(0), ByVal tptr, n)
        
            lst.AddItem (ByteToString(CountryName)) + " (" + Str(tRasCtryInfo.dwCountryCode) + " )"
            tRasCtryInfo.dwCountryID = tRasCtryInfo.dwNextCountryID
        Loop
        
        Call LocalFree(t_Buff)
    End If
    
    
End Sub
