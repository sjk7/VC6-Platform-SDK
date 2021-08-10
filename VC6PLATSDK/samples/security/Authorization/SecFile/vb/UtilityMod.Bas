Attribute VB_Name = "UtilityMod"
' THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
' ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
' THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
' PARTICULAR PURPOSE.
'
' Copyright (C) 1995 - 1999 Microsoft Corporation. All Rights Reserved.
'
' COMMENTS:
'  All buffers are allocated using Visual Basic ReDim so there is no need to explicitely free
'  memory.
'

Option Explicit

' Declare various constants from WIN32...
'
Public Const TokenUser = 1

Public Const TOKEN_QUERY = 8&

Public Const ERROR_INSUFFICIENT_BUFFER = 122 '  dderror

Public Const SECURITY_WORLD_RID = &H0

Public Const ACL_REVISION = (2)

Public Const GENERIC_ALL = &H10000000
Public Const GENERIC_WRITE = &H40000000
Public Const GENERIC_READ = &H80000000

Public Const SECURITY_DESCRIPTOR_REVISION = (1)

Public Const CREATE_ALWAYS = 2

Public Const FILE_ATTRIBUTE_NORMAL = &H80

Public Const INVALID_HANDLE_VALUE = -1

Public Const FORMAT_MESSAGE_FROM_SYSTEM = &H1000

Public Const LANG_ENGLISH = &H9

Public Const SUBLANG_ENGLISH_US = &H1                    '  English (USA)

' Declare various structures from WIN32...
Public Type OVERLAPPED
        Internal As Long
        InternalHigh As Long
        offset As Long
        OffsetHigh As Long
        hEvent As Long
End Type

Public Type SID_AND_ATTRIBUTES
    Sid As Long
    Attributes As Long
End Type

Public Type TOKEN_USER
    User As SID_AND_ATTRIBUTES
End Type

Public Type SID_IDENTIFIER_AUTHORITY
        Value(6) As Byte
End Type

Public Type SECURITY_ATTRIBUTES
        nLength As Long
        lpSecurityDescriptor As Long
        bInheritHandle As Long
End Type

Public Type ACL
        AclRevision As Byte
        Sbz1 As Byte
        AclSize As Integer
        AceCount As Integer
        Sbz2 As Integer
End Type

Public Type SECURITY_DESCRIPTOR
        Revision As Byte
        Sbz1 As Byte
        Control As Long
        Owner As Long
        Group As Long
        Sacl As ACL
        Dacl As ACL
End Type

Public Type ACE_HEADER
        AceType As Byte
        AceFlags As Byte
        AceSize As Long
End Type

Public Type ACCESS_ALLOWED_ACE
        Header As ACE_HEADER
        Mask As Long
        SidStart As Long
End Type

' Declare various APIs from WIN32
'

Public Declare Function GetCurrentProcess Lib "kernel32" () As Long

Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" _
        (Destination As Any, Source As Any, ByVal Length As Long)

Public Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" _
        (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, _
        ByVal dwShareMode As Long, lpSecurityAttributes As SECURITY_ATTRIBUTES, _
        ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, _
        ByVal hTemplateFile As Long) As Long

Public Declare Function WriteFile Lib "kernel32" (ByVal hFile As Long, lpBuffer As Any, _
        ByVal nNumberOfBytesToWrite As Long, lpNumberOfBytesWritten As Long, _
        lpOverlapped As OVERLAPPED) As Long

Public Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long

Public Declare Function OpenProcessToken Lib "advapi32.dll" _
        (ByVal ProcessHandle As Long, ByVal DesiredAccess As Long, _
        TokenHandle As Long) As Long

Public Declare Function GetTokenInformation Lib "advapi32.dll" _
        (ByVal TokenHandle As Long, ByVal TokenInformationClass As Long, _
        TokenInformation As Any, ByVal TokenInformationLength As Long, _
        ReturnLength As Long) As Long

Public Declare Function AllocateAndInitializeSid Lib "advapi32.dll" _
        (pIdentifierAuthority As SID_IDENTIFIER_AUTHORITY, _
        ByVal nSubAuthorityCount As Byte, ByVal nSubAuthority0 As Long, _
        ByVal nSubAuthority1 As Long, ByVal nSubAuthority2 As Long, _
        ByVal nSubAuthority3 As Long, ByVal nSubAuthority4 As Long, _
        ByVal nSubAuthority5 As Long, ByVal nSubAuthority6 As Long, _
        ByVal nSubAuthority7 As Long, lpPSid As Long) As Long

Public Declare Sub FreeSid Lib "advapi32.dll" (pSid As Any)

Public Declare Function CopySid Lib "advapi32.dll" (ByVal nDestinationSidLength As Long, _
        pDestinationSid As Any, pSourceSid As Any) As Long

Public Declare Function GetLengthSid Lib "advapi32.dll" (pSid As Any) As Long

Public Declare Function InitializeAcl Lib "advapi32.dll" (pAcl As ACL, _
        ByVal nAclLength As Long, ByVal dwAclRevision As Long) As Long

Public Declare Function AddAccessAllowedAce Lib "advapi32.dll" (pAcl As ACL, _
        ByVal dwAceRevision As Long, ByVal AccessMask As Long, pSid As Any) As Long

Public Declare Function InitializeSecurityDescriptor Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, ByVal dwRevision As Long) As Long

Public Declare Function SetSecurityDescriptorDacl Lib "advapi32.dll" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, ByVal bDaclPresent As Long, _
        pDacl As ACL, ByVal bDaclDefaulted As Long) As Long

Public Declare Function FormatMessage Lib "kernel32" Alias "FormatMessageA" _
        (ByVal dwFlags As Long, lpSource As Any, ByVal dwMessageId As Long, _
        ByVal dwLanguageId As Long, ByVal lpBuffer As String, ByVal nSize As Long, _
        Arguments As Long) As Long

' Declare some useful 'conversion' function

' StrToPtr returns a long which is the pointer to the passed string.  This is useful when
' calling an API which takes a long which is a pointer and you want to pass a string in.
'
' Sample usage:
' Dim MyStr as String
' Dim MyPtr as Long
'
' MyPtr = StrToPtr(MyStr)
'
Public Declare Function StrToPtr Lib "kernel32" Alias "lstrcpynA" _
        (ByVal lpString1 As String, Optional ByVal lpString2 As String = vbNullString, Optional ByVal iMaxLength As Long = 0) _
        As Long

' AnyToPtr returns a long which is the pointer to the passed data.  This is useful when
' calling an API which takes a long which is a pointer and you want to pass an arbitrary
' structure in.  Note that using this with string does not get you a pointer to the
' string but rather a pointer to the structure which has the string pointer in it.
'
' Sample usage:
' Dim MyData as MyType
' Dim MyPtr as Long
'
' MyPtr = AnyToPtr(MyData)
'
Public Declare Function AnyToPtr Lib "kernel32" Alias "lstrcpynA" _
        (ByRef lpString1 As Any, Optional ByVal lpString2 As String = vbNullString, Optional ByVal iMaxLength As Long = 0) _
        As Long

' ----------------------------------------
' Special purpose API alias
' These are APIs where the API as defined
' in WIN32API.TXT was not of an appropriate
' data type as needed in a certain situation
' The most common problem being the need to
' pass a NULL pointer to an API defined as
' taking a variable of type Any.
' ----------------------------------------

Public Declare Function GetLengthSidPtr Lib "advapi32.dll" Alias "GetLengthSid" _
        (ByVal pSid As Long) As Long

Public Declare Function CopySidPtr2 Lib "advapi32.dll" Alias "CopySid" _
        (ByVal nDestinationSidLength As Long, pDestinationSid As Any, _
        ByVal pSourceSid As Long) As Long

Public Declare Sub FreeSidPtr Lib "advapi32.dll" Alias "FreeSid" (ByVal pSid As Long)

Public Declare Function FormatMessagePtr Lib "kernel32" Alias "FormatMessageA" _
        (ByVal dwFlags As Long, ByVal lpSource As Long, ByVal dwMessageId As Long, _
        ByVal dwLanguageId As Long, ByVal lpBuffer As String, ByVal nSize As Long, _
        Arguments As Long) As Long

Public Declare Function InitializeAclAny Lib "advapi32.dll" Alias "InitializeAcl" (pAcl As Any, _
        ByVal nAclLength As Long, ByVal dwAclRevision As Long) As Long

Public Declare Function AddAccessAllowedAceAny Lib "advapi32.dll" Alias "AddAccessAllowedAce" (pAcl As Any, _
        ByVal dwAceRevision As Long, ByVal AccessMask As Long, pSid As Any) As Long

Public Declare Function SetSecurityDescriptorDaclAny Lib "advapi32.dll" Alias "SetSecurityDescriptorDacl" _
        (pSecurityDescriptor As SECURITY_DESCRIPTOR, ByVal bDaclPresent As Long, _
        pDacl As Any, ByVal bDaclDefaulted As Long) As Long

Public Declare Function WriteFilePtr Lib "kernel32" Alias "WriteFile" (ByVal hFile As Long, _
        ByVal lpBuffer As Long, ByVal nNumberOfBytesToWrite As Long, _
        lpNumberOfBytesWritten As Long, ByVal lpOverlapped As Long) As Long

' Stub API which returns the equivalent to the Win32 API GetLastError after a
' call to a DLL function/sub.

Public Function GetLastError() As Long

GetLastError = Err.LastDllError

End Function

'
'  FUNCTION: GetLastErrorText
'
'  PURPOSE: Retrieves the text associated with the last system error.
'
'  PARAMETERS:
'  none
'
'  RETURN VALUE:
'  A pointer to the error text.
'
'  COMMENTS:
'  The contents of the returned buffer will only be valid until
'  the next call to this routine.
'

Private Function GetLastErrorText() As String

Dim szMsgBuf As String
Dim dwError As Long
Dim dwRes As Long

dwError = GetLastError()

szMsgBuf = String(255, 0)

dwRes = FormatMessagePtr(FORMAT_MESSAGE_FROM_SYSTEM, _
                        0&, _
                        dwError, _
                        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), _
                        szMsgBuf, 255, 0&)
If dwRes = 0 Then
    Debug.Print "FormatMessage failed with " & GetLastError()
    End
End If

GetLastErrorText = szMsgBuf

End Function

'
'  SUB: PERR
'
'  PURPOSE: Display a message box with the last DLL error information displayed
'
'  PARAMETERS:
'  A string to give some context information to the error.
'
'  RETURN VALUE:
'  A pointer to the error text.
'
'  COMMENTS:
'  This sub is used to report a raw error from a DLL call to the user in
'  a message box.  It reports the context information (passed in), the
'  last error as reported by GetLastError and the US English text for that
'  error.
'
Public Sub PERR(s As String)

MsgBox s & " " & GetLastError() & " " & GetLastErrorText(), vbOKOnly

End Sub

' this is a macro in Win32
Private Function MAKELANGID(p As Long, s As Long) As Long

MAKELANGID = s * 1024 + p

End Function

