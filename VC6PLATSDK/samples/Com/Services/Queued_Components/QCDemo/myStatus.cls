VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "myStatus"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
Implements IStatus
Dim iColor As Integer

Private Sub IStatus_AppEvent(ByVal appName As String, ByVal appStatus As String)

    If (appStatus = "start") Then
        iColor = &H80FF80
    Else
        iColor = &HFF&
    End If

    If (appName = "Order") Then
        Monitor.ShapeOrder.FillColor = iColor
        Monitor.LblOrder.BackColor = iColor
    ElseIf (appName = "Ship") Then
        Monitor.ShapeShip.FillColor = iColor
        Monitor.LblShip.BackColor = iColor
    ElseIf (appName = "Notify") Then
        Monitor.ShapeNotify.FillColor = iColor
        Monitor.lblNotify.BackColor = iColor
    Else
    'Error
    
    End If
    

End Sub

Private Sub IStatus_MethodCall(ByVal CompName As String, CallType As String)

End Sub
