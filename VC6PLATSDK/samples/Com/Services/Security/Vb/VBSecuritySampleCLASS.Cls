VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "VBSecuritySampleClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Function AmIAnAdministrator() As Integer

On Error GoTo ErrorHandler

Dim objCtx As ObjectContext

Set objCtx = GetObjectContext()

If objCtx Is Nothing Then
    'Return Error Code
    AmIAnAdministrator = 2
    Exit Function
End If

If Not objCtx.IsSecurityEnabled Then
    'Return Error Code
    AmIAnAdministrator = 2
    Exit Function
End If

' Find out if the caller is in the right role.
' If the Administrator role does not exist, and error will
' be raised and we will drop into the error handler.
If objCtx.IsCallerInRole("Administrator") Then
    'Return True
    AmIAnAdministrator = 1
Else
    'Return False
    AmIAnAdministrator = 0
End If
Exit Function

ErrorHandler:
'An error will be caused if the Administrator role does
'not exist.
If Err.Number = mtsErrCtxRoleNotFound Then
    AmIAnAdministrator = 0
Else
    AmIAnAdministrator = 2
End If

End Function

Public Function WhoAmI() As String

Dim objCtx As ObjectContext

Set objCtx = GetObjectContext()

If objCtx Is Nothing Then
    'Don't return anything
    Exit Function
End If

'Check if security is enabled.
If Not objCtx.IsSecurityEnabled Then
    'Don't return anything
    Exit Function
End If

WhoAmI = objCtx.Security.GetDirectCallerName

End Function
