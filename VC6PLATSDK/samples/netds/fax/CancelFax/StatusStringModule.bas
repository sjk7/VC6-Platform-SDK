Attribute VB_Name = "StatusStringModule"
'Copyright (c) Microsoft Corporation.  All rights reserved.
'THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY
'OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT
'LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR
'FITNESS FOR A  PARTICULAR PURPOSE


    'The following objects and variables have to be declared
    'in a module, since they are used across the module and the forms.
    Public objFaxJob As FaxOutgoingJob
    Public StatusString As String
    Public objFaxJobs As FaxOutgoingJobs
    Public objFaxServer As New FAXCOMEXLib.FaxServer
    Public SubmId As String
    Public Sender As String
    Public Subject As String
    
    
Public Function SetStatusString() As Boolean
    
    'Initialize the function to return false
    SetStatusString = False
    
    'Error handling
    On Error GoTo Error_Handler

    'Set the status string based on the numeric value of the status
    
    If objFaxJob.Status = fjsPENDING Then StatusString = "Pending"
    If objFaxJob.Status = fjsINPROGRESS Then StatusString = "In Progress"
    If objFaxJob.Status = fjsFAILED Then StatusString = "Failed"
    If objFaxJob.Status = fjsPAUSED Then StatusString = "Paused"
    If objFaxJob.Status = fjsNOLINE Then StatusString = "No Line"
    If objFaxJob.Status = fjsRETRYING Then StatusString = "Retrying"
    If objFaxJob.Status = fjsRETRIES_EXCEEDED Then StatusString = "Retries Exceeded"
    If objFaxJob.Status = fjsCOMPLETED Then StatusString = "Completed"
    If objFaxJob.Status = fjsCANCELED Then StatusString = "Canceled"
    If objFaxJob.Status = fjsCANCELING Then StatusString = "Canceling"
    If objFaxJob.Status = fjsROUTING Then StatusString = "Routing"
    If objFaxJob.Status = fjsPENDING + fjsPAUSED Then StatusString = "Pending (paused)"
    If objFaxJob.Status = fjsRETRYING + fjsPAUSED Then StatusString = "Retrying (paused)"
    If objFaxJob.Status = fjsPENDING + fjsNOLINE Then StatusString = "Pending (no line)"
    If objFaxJob.Status = fjsRETRYING + fjsNOLINE Then StatusString = "Retrying (no line)"

    'Return True
    SetStatusString = True
    
    Exit Function
    
Error_Handler:
    'Display error information
    MsgBox "Error number: " & Hex(Err.Number) & ", " & Err.Description
    Err.Clear
End Function
