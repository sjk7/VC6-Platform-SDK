Attribute VB_Name = "modCallback"
'--------------------------------------------------------------------------
'
'  Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
Option Explicit
Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)


'+--------------------------------------------------------------------------------------------------
'
'  Function : serviceCallback
'
'  Purpose : Callback for the service to send back events and service died messages
'
'  Arguments:
'               callbackType  Type of callback
'               svcObj        Service for which callback is called
'               varName       Variable Name for which the event is called
'               value         Variable value
'
'  Return:
'
'  Note:   This is called when the events are received or the service object dies

Function serviceCallback(ByVal callbackType As Variant, ByVal svcObj As Variant, ByVal varName As Variant, ByVal value As Variant) As Long
On Error GoTo Error
Dim strTemp
If callbackType = "VARIABLE_UPDATE" Then ' This is a variable update for the service object
    strTemp = CStr(value)
    DeviceControl.lblEvent.Caption = "Variable " + varName + " changed to " + strTemp + " in " + svcObj.Id + vbCrLf
    DeviceControl.lblEvent.Refresh
    Sleep 200
ElseIf callbackType = "SERVICE_INSTANCE_DIED" Then ' The service object died and hence we have received the callback
    DeviceControl.lblEvent.Caption = "Service " + svcObj.Id + " died"
End If
serviceCallback = 0
Exit Function
Error:
With Err
    If .Number > 0 Then
        serviceCallback = .Number Or &H800A0000
    Else
        serviceCallback = .Number
    End If
End With
End Function

'+--------------------------------------------------------------------------------------------------
'
'  Function : deviceFinderCallback
'
'  Purpose : Callback for the device finder to add devices, remove devices and search complete
'
'  Arguments:
'               device  Device which is being added or removed
'               UDN     UDN of the device being added or removed
'               callbackType Type of callback
'
'  Return:
'
'  Note:   This is called when the events are received or the service object dies


Function deviceFinderCallback(ByVal device As Variant, ByVal UDN As Variant, ByVal callbackType As Variant) As Long
On Error GoTo Error

If callbackType = 0 Then ' A new device is found
   DeviceControl.AddDevice (device)
   DeviceControl.lblStatus.Caption = "Found Device " & device.FriendlyName
   DeviceControl.lblStatus.Refresh
ElseIf callbackType = 1 Then
    DeviceControl.RemoveDevice (UDN)
    DeviceControl.lblStatus.Caption = "Device " + device.FriendlyName + " is removed"
    DeviceControl.lblStatus.Refresh
ElseIf callbackType = 2 Then
    DeviceControl.lblStatus.Caption = "Device Search Completed"
    If DeviceControl.cboDevice.ListCount = 0 Then
        MsgBox "Found no devices"
    End If
End If
DeviceControl.lblStatus.Refresh
deviceFinderCallback = 0
Exit Function
Error:
With Err
    If .Number > 0 Then
        deviceFinderCallback = .Number Or &H800A0000
    Else
        deviceFinderCallback = .Number
    End If
End With
End Function


