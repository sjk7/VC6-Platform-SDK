Attribute VB_Name = "modRasEnumDevices"
Option Explicit

' Constants for RASDEVINFO
Global Const RAS_MaxDeviceType = 16
Global Const RAS_MaxDeviceName = 128

' Type definition for RASDEVINFO
Type RASDEVINFO
    dwSize As Long
    szDeviceType(RAS_MaxDeviceType) As Byte
    szDeviceName(RAS_MaxDeviceName) As Byte
End Type

' Declaration for RasEnumDevices API
Declare Function RasEnumDevices Lib "rasapi32.dll" Alias "RasEnumDevicesA" ( _
    lpRasDevInfo As Any, _
    lpcb As Long, _
    lpcDevices As Long) As Long
    
Sub GetDeviceType(lst As ComboBox, DeviceType As String)
    Dim tRasDevInfo As RASDEVINFO
    Dim cb As Long
    Dim cDevices As Long
    Dim t_Buff As Long
    Dim nRet As Long
    Dim t_ptr As Long
    Dim i As Long
    Dim t_ModemName1 As String, t_ModemName2 As String
    
    t_ModemName1 = lst
    
    cb = LenB(tRasDevInfo)
    ' Initialize the dwSize field
    tRasDevInfo.dwSize = cb
    
    ' Allocate input buffer with enough room for at least one structure
    t_Buff = LocalAlloc(LPTR, cb)
    
    If (t_Buff) Then
        ' Initialize the first entry
        ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
        ' to CopyMemory because VB passes parameters by reference by default
        Call CopyMemory(ByVal t_Buff, tRasDevInfo, LenB(tRasDevInfo))
      
        ' Call RasEnumDevices with structure that has dwSize set
        nRet = RasEnumDevices(ByVal t_Buff, cb, cDevices)
        
        If (ERROR_BUFFER_TOO_SMALL = nRet And cb <> 0) Then
            Call LocalFree(t_Buff)
            t_Buff = LocalAlloc(LPTR, cb)
        ElseIf (nRet <> 0) Then
            Call MsgBox(("RasEnumDevices failed: Error = " & CStr(nRet)), , "Error")
            Call LocalFree(t_Buff)
            Exit Sub
        End If
        
        If (t_Buff) Then
            If (nRet <> 0) Then
            
                ' Initialize the first entry
                ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
                ' to CopyMemory because VB passes parameters by reference by default
                Call CopyMemory(ByVal t_Buff, tRasDevInfo, LenB(tRasDevInfo))
                
                ' Call RasEnumDevices to enumerate the Ras capable devices
                nRet = RasEnumDevices(ByVal t_Buff, cb, cDevices)
            End If
            
            If 0 = nRet Then ' RasEnumDevices returned no errors
                t_ptr = t_Buff
                ' List the entries into the combo box
                For i = 1 To cDevices
                    Call CopyMemory(tRasDevInfo, ByVal t_ptr, LenB(tRasDevInfo))
                    t_ModemName2 = (ByteToString(tRasDevInfo.szDeviceName))
                    
                    'If we found the modem name that's selected in the combobox,
                    'set the device type and exit
                    If t_ModemName1 = t_ModemName2 Then
                        DeviceType = (ByteToString(tRasDevInfo.szDeviceType))
                        Call LocalFree(t_Buff)
                        Exit Sub
                    End If
                    t_ptr = t_ptr + LenB(tRasDevInfo)
                Next i
            Else ' RasEnumDevices returned an error
                Call MsgBox("RasEnumDevices returns " & CStr(nRet))
            End If
            
            ' Free the allocated input buffer
            Call LocalFree(t_Buff)
        Else
            Call MsgBox("LocalAlloc failed!", , "Error")
        End If
    Else
        Call MsgBox("LocalAlloc failed!", , "Error")
    End If
End Sub

' Subroutine to list the RAS capable devices
Sub GetDevices(lst As ComboBox)
    Dim tRasDevInfo As RASDEVINFO
    Dim cb As Long
    Dim cDevices As Long
    Dim t_Buff As Long
    Dim nRet As Long
    Dim t_ptr As Long
    Dim i As Long
    
    cb = LenB(tRasDevInfo)
    ' Initialize the dwSize field
    tRasDevInfo.dwSize = cb
    
    ' Allocate input buffer with enough room for at least one structure
    t_Buff = LocalAlloc(LPTR, cb)
    
    If (t_Buff) Then
        ' Initialize the first entry
        ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
        ' to CopyMemory because VB passes parameters by reference by default
        Call CopyMemory(ByVal t_Buff, tRasDevInfo, LenB(tRasDevInfo))
      
        ' Call RasEnumDevices with structure that has dwSize set
        nRet = RasEnumDevices(ByVal t_Buff, cb, cDevices)
        
        If (ERROR_BUFFER_TOO_SMALL = nRet And cb <> 0) Then
            Call LocalFree(t_Buff)
            t_Buff = LocalAlloc(LPTR, cb)
        Else
            Call MsgBox(("RasEnumDevices failed: Error = " & CStr(nRet)), , "Error")
            Call LocalFree(t_Buff)
            Exit Sub
        End If
        
        If (t_Buff) Then
            If (nRet <> 0) Then
            
                ' Initialize the first entry
                ' Since t_Buff is the actual memory address we need to pass it by value (ByVal)
                ' to CopyMemory because VB passes parameters by reference by default
                Call CopyMemory(ByVal t_Buff, tRasDevInfo, LenB(tRasDevInfo))
                
                ' Call RasEnumDevices to enumerate the Ras capable devices
                nRet = RasEnumDevices(ByVal t_Buff, cb, cDevices)
            End If
            
            If 0 = nRet Then ' RasEnumDevices returned no errors
                t_ptr = t_Buff
                ' List the entries into the combo box
                For i = 1 To cDevices
                    Call CopyMemory(tRasDevInfo, ByVal t_ptr, LenB(tRasDevInfo))
                    lst.AddItem (ByteToString(tRasDevInfo.szDeviceName))
                    t_ptr = t_ptr + LenB(tRasDevInfo)
                Next i
            Else ' RasEnumDevices returned an error
                Call MsgBox("RasEnumDevices returns " & CStr(nRet))
            End If
            
            ' Free the allocated input buffer
            Call LocalFree(t_Buff)
        Else
            Call MsgBox("LocalAlloc failed!", , "Error")
        End If
    Else
        Call MsgBox("LocalAlloc failed!", , "Error")
    End If
End Sub
