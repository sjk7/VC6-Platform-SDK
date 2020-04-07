Attribute VB_Name = "basRegistry"
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

'Registry security options
Public Const READ_CONTROL = &H20000
Public Const KEY_QUERY_VALUE = &H1
Public Const KEY_SET_VALUE = &H2
Public Const KEY_CREATE_SUB_KEY = &H4
Public Const KEY_ENUMERATE_SUB_KEYS = &H8
Public Const KEY_NOTIFY = &H10
Public Const KEY_CREATE_LINK = &H20
Public Const KEY_ALL_ACCESS = KEY_QUERY_VALUE + KEY_SET_VALUE + _
                                KEY_CREATE_SUB_KEY + KEY_ENUMERATE_SUB_KEYS + _
                                KEY_NOTIFY + KEY_CREATE_LINK + READ_CONTROL
                     
'Registry root keys
Public Const HKEY_LOCAL_MACHINE = &H80000002
Public Const HKEY_CLASSES_ROOT = &H80000000
Public Const HKEY_CURRENT_CONFIG = &H80000005
Public Const HKEY_CURRENT_USER = &H80000001
Public Const HKEY_DYN_DATA = &H80000006
Public Const HKEY_PERFORMANCE_DATA = &H80000004
Public Const HKEY_USERS = &H80000003

'Registry API return value
Public Const ERROR_SUCCESS = 0
Public Const ERROR_FAIL = -1

'Registry datatypes
Public Const REG_SZ     As Integer = 1
Public Const REG_DWORD  As Integer = 4

'Primary registry location for SysInfo application
Public Const kRegKeySysInfoKey                  As String = "SOFTWARE\Microsoft\Shared Tools\MSINFO"
Public Const kRegKeySysInfoSubKey               As String = "PATH"

'Secondary registry location for SysInfo application
Public Const kRegKeySysInfoSecondaryKey         As String = "SOFTWARE\Microsoft\Shared Tools Location"
Public Const kRegValueSysInfoSecondarySubKey    As String = "MSINFO"

'Registry API declarations
Public Declare Function RegOpenKeyEx Lib "advapi32" Alias "RegOpenKeyExA" (ByVal hKey As Long, ByVal lpSubKey As String, ByVal ulOptions As Long, ByVal samDesired As Long, ByRef phkResult As Long) As Long
Public Declare Function RegQueryValueEx Lib "advapi32" Alias "RegQueryValueExA" (ByVal hKey As Long, ByVal lpValueName As String, ByVal lpReserved As Long, ByRef lpType As Long, ByVal lpData As String, ByRef lpcbData As Long) As Long
Public Declare Function RegCloseKey Lib "advapi32" (ByVal hKey As Long) As Long

Public Sub GetSysInfo()
  
    Dim SysInfoFileSpec As String
    Dim sErrorMsg       As String
    
    'Attempt to get the SysInfo app location from the primary registry location
    If Not GetRegKeyValue(HKEY_LOCAL_MACHINE, kRegKeySysInfoKey, kRegKeySysInfoSubKey, SysInfoFileSpec) Then
        'Failed to find the information in the primary location, attempt to read it from its secondary location
        If Not GetRegKeyValue(HKEY_LOCAL_MACHINE, kRegKeySysInfoSecondaryKey, kRegValueSysInfoSecondarySubKey, SysInfoFileSpec) Then
            GoTo SysInfoErr:
        End If
    End If
    
    'Launch the SysInfo application
    Call Shell(SysInfoFileSpec, vbNormalFocus)
    
    Exit Sub
    
SysInfoErr:
    sErrorMsg = "System Information Is Unavailable At This Time." & vbCrLf & vbCrLf
    sErrorMsg = sErrorMsg & "Press OK to continue."
    MsgBox sErrorMsg, (vbOKOnly + vbInformation), "Error"
    
    Exit Sub
    
End Sub

Public Sub CloseRegKey(ByVal hKey As Long)

    Dim lRetCode    As Long
    
    'Close the registry key
    lRetCode = RegCloseKey(hKey)
    
    Exit Sub
    
End Sub

Public Function OpenRegKey(ByVal KeyRoot As Long, ByVal KeyName As String, Optional ByVal Options As Long = 0, Optional ByVal SecurityFlags As Long = KEY_ALL_ACCESS) As Long
    
    Dim lRetCode    As Long
    Dim hKey        As Long
    
    'Default return value
    OpenRegKey = ERROR_FAIL
    
    'Attempt to open the registry key
    lRetCode = RegOpenKeyEx(KeyRoot, KeyName, Options, SecurityFlags, hKey)
    
    'Set return value if we successfully opened the registry key
    If (ERROR_SUCCESS = lRetCode) Then
        OpenRegKey = hKey
    End If
    
    Exit Function
    
End Function

Public Function GetRegKeyValue(KeyRoot As Long, KeyName As String, SubKeyRef As String, ByRef KeyVal As String) As Boolean

    Dim sRegData    As String
    Dim lCtr        As Long
    Dim lRetCode    As Long
    Dim hKey        As Long
    Dim lKeyValType As Long
    Dim lKeyValSize  As Long

    'Default return value
    GetRegKeyValue = False
    
    'Open the registry key
    hKey = OpenRegKey(KeyRoot, KeyName)
    
    'Continue only if the key is successfully opened
    If (ERROR_FAIL = hKey) Then GoTo GetKeyError:
    
    'Setup prior to reading the value from the registry
    lKeyValSize = 1024
    sRegData = String$(lKeyValSize, 0)
    
    'Attempt to get the value in the currently open registry key
    lRetCode = RegQueryValueEx(hKey, SubKeyRef, 0, lKeyValType, sRegData, lKeyValSize)
    
    'Continue only if we successfully read the value
    If (lRetCode <> ERROR_SUCCESS) Then GoTo GetKeyError:
    
    'Strip off any tailing nulls
    If (Chr(0) = right$(sRegData, 1)) Then
        sRegData = left(sRegData, lKeyValSize - 1)
    Else
        sRegData = left(sRegData, lKeyValSize)
    End If
    
    'Handle various registry data types
    Select Case lKeyValType
        Case REG_SZ
            KeyVal = sRegData
        Case REG_DWORD
            For lCtr = Len(sRegData) To 1 Step -1
                KeyVal = KeyVal & Hex(Asc(Mid(sRegData, lCtr, 1)))
            Next
            KeyVal = Format$("&h" & KeyVal)
    End Select
    
    GetRegKeyValue = True
    
GetKeyBail:
    CloseRegKey hKey
    Exit Function
    
GetKeyError:
    KeyVal = ""
    GoTo GetKeyBail:
    
End Function
