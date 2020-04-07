VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "IStatus"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Rem ==========================================================================
Rem
Rem This file is part of the Microsoft COM+ Samples.
Rem
Rem Copyright (C) 1995-1999 Microsoft Corporation. All rights reserved.
Rem
Rem This source code is intended only as a supplement to Microsoft
Rem Development Tools and/or on-line documentation. See these other
Rem materials for detailed information regarding Microsoft code samples.
Rem
Rem THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
Rem KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
Rem IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
Rem PARTICULAR PURPOSE.
Rem
Rem ==========================================================================

Option Explicit
Dim iColor As Long
Dim PauseTime, Start, Finish, TotalTime As Integer

Public Sub AppEvent(ByVal appName As String, ByVal appStatus As String)
    
' Method: AppEvent
' Parameters:
'   appName (String) - This is the name of the calling component.
'   appStatus (String) - caller uses this to indicate whether it is starting or
'                        stopping
'
    
' Order Component - if starting, set color to green.  if stopping, set color
' to red and clear text on arrow to ship component.
'
  If (appName = "Order") Then
    If (appStatus = "start") Then
      Monitor.ShapeOrder.FillColor = &H80FF80
      Monitor.LblOrder.BackColor = &H80FF80
    ElseIf (appStatus = "stop") Then
      Monitor.ShapeOrder.FillColor = &HFF&
      Monitor.LblOrder.BackColor = &HFF&
      Monitor.lblOrderShip.Caption = ""
    End If
        
' Ship Component - if starting, set color to green.  if stopping, set color to
' red and clear text on arrow to notify component.
'
  ElseIf (appName = "Ship") Then
    If (appStatus = "start") Then
      Monitor.ShapeShip.FillColor = &H80FF80
      Monitor.LblShip.BackColor = &H80FF80
    ElseIf (appStatus = "stop") Then
      Monitor.ShapeShip.FillColor = &HFF&
      Monitor.LblShip.BackColor = &HFF&
      Monitor.lblShipNotify.Caption = ""
    End If
    
' Notify Component - if starting, set color to green.  if stopping, set color
' to red and clear text on arrow from ship to notify component.
'
  ElseIf (appName = "Notify") Then
    If (appStatus = "start") Then
      Monitor.ShapeNotify.FillColor = &H80FF80
      Monitor.lblNotify.BackColor = &H80FF80
    ElseIf (appStatus = "stop") Then
      Monitor.ShapeNotify.FillColor = &HFF&
      Monitor.lblNotify.BackColor = &HFF&
      Monitor.lblShipNotify.Caption = ""
    End If
  Else
  'Error
  End If

' Pause to give viewer timet to see change in display
'
   PauseTime = 1   ' Set duration in seconds
   Start = Timer   ' Set start time (now)
   Do While Timer < Start + PauseTime
      DoEvents   ' Yield to other processes
   Loop

End Sub

Public Sub MethodCall(ByVal CompName As String, ByVal CallType As String)
'
' Method: MethodCall
' Parameters:
'   CompName (String) - name of calling component
'   CallType (String) - indicates whether call was direct or queued
'
' This method changes the text on the arrows from one component box to another.
' There are two arrows, from Order to Ship and from Ship to Notify.   CompName
' indicates the originating component.  CallType indicates the way the component
' is being called (e.g. Direct, Queued, etc.).
'
    If (CompName = "Order") Then
        Monitor.lblOrderShip.Caption = CallType
    ElseIf (CompName = "Ship") Then
        Monitor.lblShipNotify.Caption = CallType
    Else
    End If
    
' Pause to give viewer timet to see change in display
'
   PauseTime = 1   ' Set duration in seconds
   Start = Timer   ' Set start time (now)
   Do While Timer < Start + PauseTime
      DoEvents   ' Yield to other processes.
   Loop


End Sub
