Attribute VB_Name = "basCommon"
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

    'Structure used to store RECT elements as strings
    Public Type strRECT
        left    As String
        top     As String
        right   As String
        bottom  As String
    End Type
    
Public Sub ToggleMP(frm As Form)
'Generic routine used to toggle the specified forms mousepointer depending upong
'   the it's current setting

    With frm
        If .MousePointer = vbNormal Then
            .MousePointer = vbHourglass
        Else
            .MousePointer = vbNormal
        End If
    End With
    
    Exit Sub
    
End Sub

Public Sub SelectText(ctl As TextBox)
'Generic routine used to select the currently displayed text in the specified
'   textbox

    With ctl
        .SelStart = 0
        .SelLength = Len(.Text)
    End With
    
    Exit Sub
    
End Sub

Public Sub CenterObject(objCenterMe As Object, Optional CANVAS As String = "")
'Generic routine used to center an object over it's parent

    Dim rectWork        As strRECT
    Dim iCtr            As Integer
    Dim lDelimiterPos   As Long

    'Determine coordinates from what is passed us
    If ("" = CANVAS) Then
        'Center the object over the canvas
        With objCenterMe
            .left = (Screen.Width - .Width) / 2
            .top = (Screen.Height - .Height) / 2
        End With
    Else
        'Get the delimiter position
        lDelimiterPos = InStr(CANVAS, ";")
        'Fill in the strRECT structure
        For iCtr = 1 To 4
            'CANVAS argument MUST conform to pattern    ->  top;left;right;bottom
            If (0 = lDelimiterPos) And (4 <> iCtr) Then Exit Sub
            Select Case iCtr
                Case 1
                    rectWork.top = Mid$(CANVAS, 1, lDelimiterPos - 1)
                Case 2
                    rectWork.left = Mid$(CANVAS, 1, lDelimiterPos - 1)
                Case 3
                    rectWork.right = Mid$(CANVAS, 1, lDelimiterPos - 1)
                Case 4
                    rectWork.bottom = Trim$(CANVAS)
            End Select
            If (lDelimiterPos < Len(CANVAS)) Then
                CANVAS = Mid(CANVAS, lDelimiterPos + 1)
            Else
                CANVAS = ""
            End If
            lDelimiterPos = InStr(CANVAS, ";")
        Next
        'Validate the arguments
        With rectWork
            If Not IsNumeric(.top) Then Exit Sub
            If Not IsNumeric(.left) Then Exit Sub
            If Not IsNumeric(.right) Then Exit Sub
            If Not IsNumeric(.bottom) Then Exit Sub
        End With
        'Attempt to center the object
        With objCenterMe
            .left = CLng(rectWork.left) + (((CLng(rectWork.right) - CLng(rectWork.left)) - .Width) / 2)
            .top = CLng(rectWork.top) + (((CLng(rectWork.bottom) - CLng(rectWork.top)) - .Height) / 2)
        End With
    End If
    
    Exit Sub
    
End Sub

Public Function ErrHandler(ErrNumber As Long, ErrDescription As String, RoutineName As String) As Boolean
'Generic error handling routine

    'No error processing within the error handler
    On Error Resume Next
    
    Dim sWork   As String
    Dim sTmp    As String
    
    'Default return value
    ErrHandler = False
    
    'Build the error message
    sWork = "[" & Hex(ErrNumber) & "]  " & RoutineName & vbCrLf & vbCrLf
    
    'Attempt to obtain additional error information from the specific error number
    sTmp = MapError(ErrNumber)
    If sTmp <> CStr(ErrNumber) Then
        sWork = sWork & sTmp
    Else
        sWork = sWork & ErrDescription
    End If
    
    'Display the error message to the user
    MsgBox sWork, (vbCritical + vbOKOnly), "Error"
    
    If ErrNumber = COMAdminErrObjectErrors Then
        If RoutineName = "CompInstall::cmdMaint_Click" _
        Or RoutineName = "AppInstall::cmdMaint_Click" Then
            'Get a reference to the error collection from the catalog object
            'Set the parent collection name so we can navigate backwards to it
            With Explorer.lbParentCollections
                If (0 = .ListCount) Then
                    .AddItem Explorer.g_CurrCollection.Name
                Else
                    .AddItem String(.ListCount, Chr(32)) & Explorer.g_CurrCollection.Name, .ListCount
                End If
            End With
            'Push the current collection onto the navigation stack
            Push Explorer.g_CurrCollection
            'Set the new current collection
            Set Explorer.g_CurrCollection = Explorer.g_Catalog.GetCollection("ErrorInfo")
            'Navigate to the new collection
            Explorer.NavigateTo Explorer.g_CurrCollection
        Else
            ' 6 is the SaveChanges button
            Explorer.tbrExplorer.Buttons(6).Enabled = False
            Explorer.lbRelatedCollections.ListIndex = Explorer.g_ErrorInfo
        End If
    End If


    Exit Function
    
End Function

Public Function MapError(ErrorCode As Long) As String
'Generic error mapping routine used to map COM Admin error codes to COM Admin error descriptions

    Select Case ErrorCode
        Case COMAdminErrObjectErrors
            MapError = "Errors occured accessing one or more objects - the ErrorInfo collection may have more detail"
        Case COMAdminErrObjectInvalid
            MapError = "One or more of the objects properties are missing or invalid"
        Case COMAdminErrKeyMissing
            MapError = " The object was not found in the catalog"
        Case COMAdminErrAlreadyInstalled
            MapError = "The object is already registered"
        '////////////////////////////////////////////////////////////////////////////////
        '**** NOTE:  Commented out following block to account for error codes
        '               enums removed from the interface  *rah* 02/10/1999
        'Case COMAdminErrPDFWriteFail
        '    MapError = "Error occured writing to the package file"
        'Case COMAdminErrPDFReadFail
        '    MapError = "Error occured reading the package file"
        'Case COMAdminErrPDFVersion
        '    MapError = "Invalid version number in PDF file"
        '////////////////////////////////////////////////////////////////////////////////
        Case COMAdminErrBadPath
            MapError = "The file path is invalid"
        '////////////////////////////////////////////////////////////////////////////////
        '**** NOTE:  Commented out following block to account for error codes
        '               enums removed from the interface  *rah* 02/10/1999
        'Case COMAdminErrPackageExists
        '    MapError = "The package is already installed"
        '////////////////////////////////////////////////////////////////////////////////
        Case COMAdminErrRoleExists
            MapError = "The role already exists"
        Case COMAdminErrCantCopyFile
            MapError = "A error occured copying the file"
        Case COMAdminErrNoUser
            MapError = "A userid in role is invalid"
        Case COMAdminErrInvalidUserids
            MapError = "One or more users in the package file are not valid on this computer"
        Case COMAdminErrNoRegistryCLSID
            MapError = "The component CLSID is missing or corrupt"
        Case COMAdminErrBadRegistryProgID
            MapError = "The component progID is missing or corrupt"
        Case COMAdminErrAuthenticationLevel
            MapError = "Unable to set required authentication level for update request"
        Case COMAdminErrUserPasswdNotValid
            MapError = "The user/password set for package identity are not valid"
        Case COMAdminErrCLSIDOrIIDMismatch
            MapError = "Package file CLSIDs/IIDs do not match corresponding DLLs"
        Case COMAdminErrRemoteInterface
            MapError = "Remote interface"
        Case COMAdminErrDllRegisterServer
            MapError = "DllRegisterServer failed on component install"
        Case COMAdminErrNoServerShare
            MapError = "No server file share available to full component files to client"
        Case COMAdminErrDllLoadFailed
            MapError = "Dll could not be loaded"
        Case COMAdminErrBadRegistryLibID
            MapError = "Registered Typelib ID is not valid"
        '**** NOTE:  Commented out following block to account for error codes enums removed from the interface  *rah* 02/10/1999
        'Case COMAdminErrPackDirNotFound
        '    MapError = "Package install directory not found"
        Case COMAdminErrRegistrarFailed
            MapError = "Errors occured while in the component registrar"
        Case COMAdminErrCompFileDoesNotExist
            MapError = "The component file does not exist"
        Case COMAdminErrCompFileLoadDLLFail
            MapError = "The component DLL could not be loaded"
        Case COMAdminErrCompFileGetClassObj
            MapError = "GetClassObject failed in the component DLL"
        Case COMAdminErrCompFileClassNotAvail
            MapError = "The component DLL does not support the components listed in the TypeLib"
        Case COMAdminErrCompFileBadTLB
            MapError = "The TypeLib could not be loaded"
        Case COMAdminErrCompFileNotInstallable
            MapError = "The file does not contain components or component information"
        Case COMAdminErrNotChangeable
            MapError = "Changes to this object and its sub-objects have been disabled"
        Case COMAdminErrNotDeletable
            MapError = "The delete function has been disabled for this object"
        Case COMAdminErrSession
            MapError = "The server catalog version is not supported"
        Case COMAdminErrCompFileNoRegistrar
            MapError = "The registrar referenced in this file is not available"
        Case COMAdminErrCoReqCompInstalled
            MapError = "A component in the same DLL is already installed"
        Case Else
            MapError = CStr(ErrorCode)
    End Select

    Exit Function
    
End Function

