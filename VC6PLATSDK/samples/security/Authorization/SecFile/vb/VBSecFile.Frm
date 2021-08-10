VERSION 5.00
Begin VB.Form VBSecFileSample
   Caption         =   "VBSecFile Sample"
   ClientHeight    =   1755
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   3075
   LinkTopic       =   "Form1"
   ScaleHeight     =   1755
   ScaleWidth      =   3075
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1
      Caption         =   "Create file"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1095
   End
   Begin VB.Label Result
      Height          =   855
      Left            =   240
      TabIndex        =   1
      Top             =   840
      Width           =   2655
   End
End
Attribute VB_Name = "VBSecFileSample"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'
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

Private Sub Command1_Click()

Dim psidUser() As Byte
Dim psidEveryone() As Byte
Dim pAcl() As Byte
Dim sd As SECURITY_DESCRIPTOR
Dim sa As SECURITY_ATTRIBUTES
Dim bRes As Long
Dim dwBytesWritten, cbMsg, cbAcl As Long
Dim szMsg As String
Dim ACL As ACL
Dim ACCESS_ALLOWED_ACE As ACCESS_ALLOWED_ACE
Dim hFile As Long

Const USER_ACCESS = GENERIC_ALL
Const WORLD_ACCESS = GENERIC_READ
Const FILENAME = "testfile.txt"

Result.Caption = "Created " & FILENAME & " with special access."

szMsg = "Protected data" & Chr(13)

'
' Get the SIDs we'll need for the DACL
'
GetUserSid psidUser
CreateWorldSid psidEveryone

' Allocate space for the ACL
    ' For information about computing the size of the ACL, see
    ' the Win32 SDK reference entry for InitializeAcl()
'
cbAcl = Len(ACL) + _
            GetLengthSid(psidUser(0)) + Len(ACCESS_ALLOWED_ACE) - Len(ACCESS_ALLOWED_ACE.SidStart) + _
            GetLengthSid(psidEveryone(0)) + Len(ACCESS_ALLOWED_ACE) - Len(ACCESS_ALLOWED_ACE.SidStart)

ReDim pAcl(cbAcl) As Byte

bRes = InitializeAclAny(pAcl(0), cbAcl, ACL_REVISION)
If bRes = 0 Then
    PERR ("InitializeAcl")
    End
End If

' Add Aces for User and World
'
bRes = AddAccessAllowedAceAny(pAcl(0), ACL_REVISION, USER_ACCESS, psidUser(0))
If bRes = 0 Then
    PERR ("AddAccessAllowedAce")
    End
End If

bRes = AddAccessAllowedAceAny(pAcl(0), ACL_REVISION, WORLD_ACCESS, psidEveryone(0))
If bRes = 0 Then
    PERR ("AddAccessAllowedAce")
    End
End If

' Put together the security descriptor
'
bRes = InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION)
If bRes = 0 Then
    PERR ("InitializeSecurityDescriptor")
    End
End If

bRes = SetSecurityDescriptorDaclAny(sd, 1&, pAcl(0), 0&)
If bRes = 0 Then
    PERR ("SetSecurityDescriptorDacl")
    End
End If

' Add the security descriptor to the sa structure
'
sa.nLength = Len(sa)
sa.lpSecurityDescriptor = AnyToPtr(sd)
sa.bInheritHandle = 0

' Generate the file using the security attributes that
' we've assembled
'
hFile = CreateFile(FILENAME, _
                    GENERIC_READ + GENERIC_WRITE, _
                    0, _
                    sa, _
                    CREATE_ALWAYS, _
                    FILE_ATTRIBUTE_NORMAL, _
                    0)
If hFile = INVALID_HANDLE_VALUE Then
    PERR "CreateFile"
    End
End If

cbMsg = Len(szMsg)

bRes = WriteFilePtr(hFile, StrToPtr(szMsg), cbMsg, dwBytesWritten, 0)
If bRes = 0 Then
    PERR "WriteFile"
    End
End If

If CloseHandle(hFile) = 0 Then
    PERR "CloseHandle"
    End
End If

Result.Caption = "Created " & FILENAME & " with special access."

End Sub

'
'  SUB: GetUserSid
'
'  PURPOSE: Obtains the SID for the current user
'
'  PARAMETERS:
'  An dynamic array of bytes
'
'  COMMENTS:
'  The passed array of byte is redim'ed to match the size required to hold the user SID
'
Private Sub GetUserSid(ByRef pUserSID() As Byte)

Dim hToken As Long
Dim bRes As Long
Dim cbBuffer, cbRequired As Long
Dim pUserInfo() As Byte
Dim UserInfo As TOKEN_USER

' The User's SID can be obtained from the process token
'
bRes = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, hToken)
If bRes = 0 Then
    PERR "OpenProcessToken"
    End
End If

' Set buffer size to 0 for first call to determine
' the size of buffer we need.
'
cbBuffer = 0
ReDim pUserInfo(1) As Byte
bRes = GetTokenInformation(hToken, TokenUser, pUserInfo(0), cbBuffer, cbRequired)
If GetLastError() <> ERROR_INSUFFICIENT_BUFFER Then
    PERR "GetTokenInformation1"
    End
End If

' Allocate a buffer for our token user data
'
cbBuffer = cbRequired
ReDim pUserInfo(cbBuffer) As Byte

' Make the "real" call
'
bRes = GetTokenInformation(hToken, TokenUser, pUserInfo(0), cbBuffer, cbRequired)
If bRes = 0 Then
    PERR "GetTokenInformation2"
    End
End If

' Convert the result byte array into a TOKEN_USER structure
CopyMemory UserInfo, pUserInfo(0), Len(UserInfo)

' Make another copy of the SID for the return value
'
cbBuffer = GetLengthSidPtr(UserInfo.User.Sid)

ReDim pUserSID(cbBuffer)
bRes = CopySidPtr2(cbBuffer, pUserSID(0), UserInfo.User.Sid)
If bRes = 0 Then
    PERR "CopySid"
    End
End If

End Sub

'
'  SUB: CreateWorldSid
'
'  PURPOSE: Creates a SID that represents "Everyone"
'
'  PARAMETERS:
'  An dynamic array of bytes
'
'  COMMENTS:
'  The passed array of byte is redim'ed to match the size required
'  to hold the world SID.
'
'  The SID Authority and RID used here are defined in winnt.h.
'
Private Sub CreateWorldSid(ByRef pSid() As Byte)

Dim authWorld As SID_IDENTIFIER_AUTHORITY
Dim psidWorld As Long
Dim bRes As Long
Dim cbSid As Long

' authWorld = SECURITY_WORLD_SID_AUTHORITY
authWorld.Value(0) = 0
authWorld.Value(1) = 0
authWorld.Value(2) = 0
authWorld.Value(3) = 0
authWorld.Value(4) = 0
authWorld.Value(5) = 1

bRes = AllocateAndInitializeSid(authWorld, _
            1, _
            SECURITY_WORLD_RID, _
            0, _
            0, _
            0, _
            0, _
            0, _
            0, _
            0, _
            psidWorld)

If bRes = 0 Then
    PERR "AllocateAndInitializeSid"
    End
End If

' Make a copy of the SID
cbSid = GetLengthSidPtr(psidWorld)

ReDim pSid(cbSid) As Byte

bRes = CopySidPtr2(cbSid, pSid(0), psidWorld)
If bRes = 0 Then
    PERR "CopySid"
    End
End If

FreeSid psidWorld

End Sub

