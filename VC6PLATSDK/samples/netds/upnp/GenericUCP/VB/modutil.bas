Attribute VB_Name = "modUtil"
'--------------------------------------------------------------------------
'
'  Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
Option Explicit


'+--------------------------------------------------------------------------------------------------
'
'  Function : initializeDevTypeList
'
'  Purpose : To initialize the device type list stored globally
'
'  Arguments:
'
'  Return:
'
'  Note:    Called when FindByType or AsyncFind search is selected
'
Public Function initializeDevTypeList() As Boolean
Dim fso As New FileSystemObject
Dim devTypeFile As TextStream ' Device type file
Dim devTypeString As String 'String storing the line read from the file
Dim splitString As Variant 'Variant for splitting the string into device type and friendly name

ReDim g_deviceTypeArray(0)

If Not fso.FolderExists(App.Path & "\devType.txt") Then
    ' We must read from the file and then initialize the list
    Set devTypeFile = fso.OpenTextFile(App.Path & "\devType.txt", ForReading)
    While (Not devTypeFile.AtEndOfStream())
        devTypeString = devTypeFile.ReadLine() 'Read one line at a time
        If devTypeString <> "" Then
            splitString = Split(devTypeString, " ", 2) ' Split the string into device type and the friendly name
            Call DeviceControl.AddDeviceTypeToArray(splitString(0), splitString(1)) 'Add the device type into the list
        End If
    Wend
    devTypeFile.Close
End If
End Function



'+--------------------------------------------------------------------------------------------------
'
'  Function : initializeUDNList
'
'  Purpose : To initialize the udn list in the find combo box
'
'  Arguments:
'
'  Return:
'
'  Note:    Called when FindByUDN search is selected
'
' This is the module which contains the function which initializes the UDN list
Public Function initializeUDNList() As Boolean
Dim fso As New FileSystemObject
Dim udnFile As TextStream
Dim udnString As String '  string for storing the line read from the udn file

If Not fso.FolderExists(App.Path & "\udn.txt") Then
    ' We must read from the file and then initialize the list
    ' We read one line at a time and then add it to the list
    Set udnFile = fso.OpenTextFile(App.Path & "\udn.txt", ForReading)
    While (Not udnFile.AtEndOfStream())
        udnString = udnFile.ReadLine()
        If udnString <> "" Then 'The line read must not be empty
            DeviceControl.cboFind.AddItem udnString
        End If
    Wend
    udnFile.Close
End If
End Function


'+--------------------------------------------------------------------------------------------------
'
'  Function : ClearAllDataStructures
'
'  Purpose : To clear the data structures stored globally
'
'  Arguments:
'            fClearCboFind  Boolean whether to clear the find combo box or not
'
'  Return:
'
'  Note:
'

Public Sub ClearAllDataStructures(fClearCboFind As Boolean)

'Clear the variables

'Clear the find combo if necessary
If fClearCboFind = True Then
    DeviceControl.cboFind.Clear
End If

'Clear the other combo boxes
DeviceControl.cboDevice.Clear
DeviceControl.cboDevice.ToolTipText = ""
DeviceControl.cboService.Clear

DeviceControl.lblStatus.Caption = ""
DeviceControl.lblEvent.Caption = ""

Set g_currentDevice = Nothing
Set g_currentService = Nothing

ReDim g_deviceArray(0) ' Clear the device array
ReDim g_serviceArray(0) ' Clear the service array

End Sub

'+--------------------------------------------------------------------------------------------------
'
'  Function : StopAsyncFindIfStarted
'
'  Purpose : To stop the async find if it is proceeding
'
'  Arguments:
'
'  Return:
'
'  Note:



Public Sub StopAsyncFindIfStarted()

If g_fDevFindHandle = True Then
    g_devFinder.CancelAsyncFind (g_lDevFindHandle)
    Set g_devFinder = Nothing ' We are releasing the device finder object
    g_fDevFindHandle = False
    DeviceControl.lblStatus.Caption = "AsyncFind Cancelled"
End If
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : ParseString
'
'  Purpose : Function to parse the arguments in various tokens
'
'  Arguments:
'
'  Return:
'
'  Note:
'
Function ParseString(strTarget As String, strSep As String, ByRef saTokens() As String) As Integer
    Dim strWorkT, strWorkS  As String
    Dim iStart, iLen, iSepLen, iSep, iFound As Integer
    ParseString = 0
    ' Make sure we have something to work on
    If strTarget = vbNullString Then
        Exit Function
    End If
    If strSep = vbNullString Then
        Exit Function
    End If
    ' Scan string one character at a time looking for the separator
    iLen = Len(strTarget)
    iSepLen = Len(strSep)
    iStart = 1
    iFound = 0
    ReDim saTokens(10) As String
    saTokens(0) = vbNullString
    Do
        iSep = InStr(Mid$(strTarget, iStart), strSep)
        If iSep > 0 Then ' found a separator
            If UBound(saTokens) <= iFound Then ' Add 10 elements if needed
                ReDim Preserve saTokens(UBound(saTokens) + 10) As String
            End If
            saTokens(iFound) = Mid$(strTarget, iStart, iSep - 1)
            iFound = iFound + 1
            iStart = iStart + iSep + iSepLen - 1
        End If
    Loop Until iSep = 0
    ' Either no separators found or multiple separators at this point
    If iFound > 0 Then ' Fill in last token element
        If iLen >= iStart Then
            saTokens(iFound) = Mid$(strTarget, iStart)
        Else
            saTokens(iFound) = vbNullString
        End If
    Else ' We didn't find any
        saTokens(0) = strTarget
    End If
    ' Return the number of elements used
    ParseString = iFound + 1
End Function


'+--------------------------------------------------------------------------------------------------
'
'  Function : RemoveSecondFromFirstString
'
'  Purpose : Removes the second string from the first string if it exists
'
'  Arguments:
'
'  Return:
'
'  Note:
'


Public Function RemoveSecondFromFirstString(ByVal first_string As String, ByVal second_string As String) As String

    If first_string = "" Then
        RemoveSecondFromFirstString = Null
    ElseIf Len(first_string) < Len(second_string) Then
        RemoveSecondFromFirstString = Null
    ElseIf StrComp(Left(first_string, Len(second_string)), second_string) <> 0 Then
        ' Check if the second string forms the first part of the first string
        RemoveSecondFromFirstString = Null
    Else
        RemoveSecondFromFirstString = Right(first_string, Len(first_string) - Len(second_string))
    End If
End Function


'+--------------------------------------------------------------------------------------------------
'
'  Function : AddServiceCbkFunction
'
'  Purpose : Add the callback for the given service
'
'  Arguments:
'           upnpSvc Service to add callback
'
'  Return:
'
'  Note:
'

'Add the service callback function so that the service selected can receive events
Public Sub AddServiceCbFunction(upnpSvc As UPnPService)
On Error GoTo Error
Dim xCallbackInterface As CallbackIUnknownLib.ServiceCallBackInterface
Dim ptinfo As ITypeInfo
Dim ptcomp As ITypeComp
Dim objCallback As Object

With LoadTypeLibEx(App.Path & "\cbklib.tlb", REGKIND_NONE).GetTypeComp
    .BindType "ServiceCallbackInterface", 0, ptinfo, ptcomp
End With
Set xCallbackInterface = InitDelegator(g_serviceFD, AddressOf serviceCallback)
Set objCallback = CreateStdDispatch(Nothing, ObjPtr(xCallbackInterface), ptinfo)
upnpSvc.AddCallback objCallback ' Add the callback
Exit Sub
Error:
With Err
    ErrorPrint (.Number)
End With
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : ErrorPrint
'
'  Purpose : Generic Error print handler
'
'  Arguments:
'
'  Return:
'
'  Note:
'

Public Sub ErrorPrint(ByVal ErrValue As Long)
Dim Msg As String

' This prints the various values
Select Case ErrValue
Case UPNP_E_ROOT_ELEMENT_EXPECTED
    MsgBox "Error: Root Element Expected"
Case UPNP_E_DEVICE_ELEMENT_EXPECTED
    MsgBox "Error: Device Element Expected"
Case UPNP_E_SERVICE_ELEMENT_EXPECTED
    MsgBox "Error: Service Element Expected"
Case UPNP_E_SERVICE_NODE_INCOMPLETE
    MsgBox "Error: Service Node incomplete"
Case UPNP_E_DEVICE_NODE_INCOMPLETE
    MsgBox "Error: Device node incomplete"
Case UPNP_E_ICON_ELEMENT_EXPECTED
    MsgBox "Error: Icon element expected"
Case UPNP_E_ICON_NODE_INCOMPLETE
    MsgBox "Error: Icon node incomplete"
Case UPNP_E_INVALID_ACTION
    MsgBox "Error: Invalid action"
Case UPNP_E_INVALID_ARGUMENTS
    MsgBox "Error: Invalid arguments"
Case UPNP_E_OUT_OF_SYNC
    MsgBox "Error: Service Out of sync"
Case UPNP_E_ACTION_REQUEST_FAILED
    MsgBox "Error: Action Request Failed"
Case UPNP_E_TRANSPORT_ERROR
    MsgBox "Error: Transport Error "
Case UPNP_E_VARIABLE_VALUE_UNKNOWN
    MsgBox "Error: Variable Value Unknown"
Case UPNP_E_INVALID_VARIABLE
    MsgBox "Error: Invalid Variable"
Case UPNP_E_DEVICE_ERROR
    MsgBox "Error: Device Error"
Case UPNP_E_PROTOCOL_ERROR
    MsgBox "Error: Protocol Error"
Case UPNP_E_ERROR_PROCESSING_RESPONSE
    MsgBox "Error: Error processing response"
Case UPNP_E_DEVICE_TIMEOUT
    MsgBox "Error: Device Timeout"
Case UPNP_E_DEVICE_SPECIFIC_ERROR
    MsgBox "Error: Device specific error"
Case UPNP_E_INVALID_DOCUMENT
    MsgBox "Error: Invalid Document"
Case UPNP_E_EVENT_SUBSCRIPTION_FAILED
    MsgBox "Error: Event Subscription failed"
Case UPNP_E_UPNP_NOT_INSTALLED:
    MsgBox "Error: Can't create ActiveX component" + vbCrLf + "        Probably UPnP is not installed"
Case Else
   Msg = "Error &H" & Hex(Err.Number) & " was generated by " _
         & Err.Source & Chr(13) & Err.Description
   MsgBox Msg, , "Error", Err.HelpFile, Err.HelpContext
End Select
End Sub

