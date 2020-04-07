VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CrmFilesCompensatorVB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'+==========================================================================
'File: CrmFilesCompensatorVB.cls
'
'Summary: Sample of implementing a Compensating Resource Manager (CRM) in VB
'         See CrmFiles for the VC version.
'         This is the CRM Compensator class.
'
'Classes: CrmFilesCompensatorVB
'
'Functions: (optional)
'
'----------------------------------------------------------------------------
'
'This file is part of the Microsoft COM+ Samples.
'
'Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.
'
'This source code is intended only as a supplement to Microsoft
'Development Tools and/or on-line documentation. See these other
'materials for detailed information regarding Microsoft code samples.
'
'THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
'KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
'IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'PARTICULAR PURPOSE.
'=========================================================================+*/

Option Explicit

' CRM COMPENSATOR INTERFACE - MUST BE IMPLEMENTED BY ALL CRM COMPENSATORS
Implements ICrmCompensatorVariants

' interface to the CRM clerk through which log records are written
Dim CrmLogControl As ICrmLogControl

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_SetLogControlVariants
'
'Summary: Delivers an ICrmLogControl interface to the CRM Compensator.
'
'Args: ByVal pLogControl As ICrmLogControl
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Sub ICrmCompensatorVariants_SetLogControlVariants(ByVal pLogControl As ICrmLogControl)

    Set CrmLogControl = pLogControl

    ' Example:
    
    Dim strTransactionUOW As String

    strTransactionUOW = CrmLogControl.TransactionUOW

End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_AbortRecordVariants
'
'Summary: Delivers a log record to the CRM Compensator during the abort phase.
'
'Args: pLogRecord
'
'Returns : Boolean
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Function ICrmCompensatorVariants_AbortRecordVariants(pLogRecord) As Boolean

    On Error GoTo ErrorHandler
        
    Dim Command As Integer
    
    Dim strFileName As String
    
    Dim strTempFileName As String
    
    Dim strPrompt As String
    
    ' get the command
    
    Command = pLogRecord(CommandIndex)
    
    strPrompt = "Command = " + Str(Command)
        
    ' get the source filename
    
    strFileName = pLogRecord(FileNameIndex)
    
    strPrompt = "strFileName = " + strFileName
    
    Dim SourceFileExists As Boolean
    
    ' does the source file exist? - open existing
        
    On Error Resume Next
    
    Open strFileName For Input As #1    ' Input will not create a new file
        
    If Err.Number = 0 Then     ' file already exists
    
        SourceFileExists = True
        
    Else
    
        SourceFileExists = False
        
    End If

    Err.Clear
    
    Close #1
    
    On Error GoTo ErrorHandler
    
    ' do the command
    
    If Command = CommandDeleteFile Then
        
        ' get the temp filename
        
        strTempFileName = pLogRecord(TempFileNameIndex)
    
        strPrompt = "strTempFileName = " + strTempFileName
            
        ' put back the original file
            
        ' is the temp file there? - open existing
        
        Dim TempFileExists As Boolean
        
        On Error Resume Next
    
        Open strTempFileName For Input As #2    ' Input will not create a new file
        
        If Err.Number = 0 Then     ' file already exists
        
            TempFileExists = True
            
        Else
        
            TempFileExists = False
            
        End If
    
        Err.Clear
        
        On Error GoTo ErrorHandler
        
        Close #2
        
        If Not SourceFileExists Then
        
            If Not TempFileExists Then
            
                ' it had better exist, otherwise something is hosed
                                
                MsgBox "ERROR: temp file is missing"
                
                GoTo ErrorHandler
                
            End If
            
            ' original file was not found, so move (rename) the temp file back
            
            Name strTempFileName As strFileName
            
        End If
        
        ' clean up temp file
        
        On Error Resume Next
        
        Kill strTempFileName
        
        ' NOTE: we do not care whether this succeeds or not... worst case we leave temp files around
        
    Else
        
        If Not Command = CommandCreateFile Then
                
            MsgBox "ERROR: invalid command"
            
            GoTo ErrorHandler
            
        End If
        
        ' delete the file we created

        ' does it exist?
        
        If SourceFileExists Then
        
            ' the file exists, so we must delete it
            
            ' IGNORE ERRORS
            
            On Error Resume Next
            
            ' allow for the case where we wrote the log record, but did not create the file
            
            Kill strFileName
            
        End If
        
    End If
    
    ' OPTIONAL: FORGET the record that was just delivered to us?
    
    ICrmCompensatorVariants_AbortRecordVariants = True

    ' NOTE: this forget is not forced - could force on next record if required
    
    Exit Function
    
ErrorHandler:

    MsgBox "AbortRecordVariants ErrorHandler " + Err.Description
    
End Function

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_BeginAbortVariants
'
'Summary: Notifies the CRM Compensator of the abort phase of the transaction
'         completion, and that records are about to be delivered.
'
'Args: ByVal bRecovery As Boolean
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Sub ICrmCompensatorVariants_BeginAbortVariants(ByVal bRecovery As Boolean)
    
    ' do nothing

End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_BeginCommitVariants
'
'Summary: Notifies the CRM Compensator of the commit phase (phase 2) of the
'         transaction completion, and that records are about to be delivered.
'
'Args: ByVal bRecovery As Boolean
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Sub ICrmCompensatorVariants_BeginCommitVariants(ByVal bRecovery As Boolean)
    
    ' do nothing

End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_BeginPrepareVariants
'
'Summary: Notifies the CRM Compensator of the prepare phase of the
'          transaction completion and that records are about to be delivered.
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Sub ICrmCompensatorVariants_BeginPrepareVariants()
    
    ' do nothing

End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_CommitRecordVariants
'
'Summary: Delivers a log record to the CRM Compensator during the commit phase.
'
'Args: pLogRecord
'
'Returns : Boolean
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Function ICrmCompensatorVariants_CommitRecordVariants(pLogRecord) As Boolean
   
    On Error GoTo ErrorHandler
        
    Dim Command As Integer
    
    Dim strFileName As String
    
    Dim strTempFileName  As String
    
    ' get the command
    
    Command = pLogRecord(CommandIndex)
    
    ' get the source filename
    
    strFileName = pLogRecord(FileNameIndex)
    
    If Command = CommandDeleteFile Then
         
        ' get the temp filename
        
        strTempFileName = pLogRecord(TempFileNameIndex)
    
        '  clean up temp file
        
        On Error Resume Next
        
        Kill strTempFileName
        
        ' NOTE: we do not care whether this succeeds or not... worst case we leave temp files around
        
    Else
        
        If Not Command = CommandCreateFile Then
                
            MsgBox "ERROR: invalid command"
            
            GoTo ErrorHandler
            
        End If
              
        ' no cleanup required for "create file"
        
    End If
    
    ' OPTIONAL: FORGET the record that was just delivered to us?
    
    ICrmCompensatorVariants_CommitRecordVariants = True

    ' NOTE: this forget is not forced - could force on next record if required
    
    Exit Function
    
ErrorHandler:

    MsgBox "CommitRecordVariants ErrorHandler " + Err.Description
    
End Function

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_EndAbortVariants
'
'Summary: Notifies the CRM Compensator that it has received all the log
'         records available during the abort phase.
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Sub ICrmCompensatorVariants_EndAbortVariants()
    
    ' do nothing

End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_EndCommitVariants
'
'Summary: Notifies the CRM Compensator that it has delivered all the log
'         records available during the commit phase.
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Sub ICrmCompensatorVariants_EndCommitVariants()
    
    ' do nothing

End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_EndPrepareVariants
'
'Summary: Notifies the CRM Compensator that it has had all the log records
'         available during the prepare phase.
'
'Returns : Boolean
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Function ICrmCompensatorVariants_EndPrepareVariants() As Boolean

    ' VOTE ON THE OUTCOME OF THE TRANSACTION
    
    ICrmCompensatorVariants_EndPrepareVariants = True
    
End Function

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: ICrmCompensatorVariants_PrepareRecordVariants
'
'Summary: Delivers a log record to the CRM Compensator during the prepare phase.
'
'Args: pLogRecord
'
'Returns : Boolean
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Private Function ICrmCompensatorVariants_PrepareRecordVariants(pLogRecord) As Boolean

    ' OPTIONAL: FORGET the record that was just delivered to us?
    
    ICrmCompensatorVariants_PrepareRecordVariants = False

End Function


