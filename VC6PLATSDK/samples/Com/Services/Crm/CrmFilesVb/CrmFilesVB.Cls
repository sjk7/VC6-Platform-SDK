VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "CrmFilesWorkerVB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
'+==========================================================================
'File: CrmFilesWorkerVB.vbp
'
'Summary: Sample of implementing a Compensating Resource Manager (CRM) in VB
'         See CrmFiles for the VC version.
'         This is the CRM Worker class.
'
'Classes: CrmFilesWorker
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

' we will use the same interface as the VC version of CrmFiles
Implements CrmFilesWorker

' the CRM clerk
Dim objClerk As CRMClerk

' interface to the CRM clerk through which log records are written
Dim CrmLogControl As ICrmLogControl

'/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
'Method: GetCrmLogControl
'
'Summary: Get an ICrmLogControl from a clerk
'
'F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/

Private Sub GetCrmLogControl()

    On Error GoTo ErrorHandler
    
    Set objClerk = New CRMClerk     ' create the CRM clerk
    
    Set CrmLogControl = objClerk    ' get ICrmLogControl
    
    Exit Sub
    
ErrorHandler:

    MsgBox "GetCrmLogControl ErrorHandler " + Err.Description
    
End Sub

'/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
'Subroutine: RegisterCrmFilesVBCompensator
'
'Summary: Register the CRM Compensator with the CRM infrastructure.
'
'F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/

Private Sub RegisterCrmFilesVBCompensator()

    On Error GoTo ErrorHandler
    
    ' register our compensator
    
    Dim strProgIdCompensator As String
    
    Dim strDescription As String
    
    strProgIdCompensator = "CrmFilesVB.CrmFilesCompensatorVB"
    
    strDescription = "CrmFilesVB sample VB CRM"
    
    On Error Resume Next
       
    CrmLogControl.RegisterCompensator strProgIdCompensator, strDescription, CRMREGFLAG_ALLPHASES
        
    ' may have to wait while recovery is in progress
    
    While Err.Number = XACT_E_RECOVERYINPROGRESS
    
        DoEvents
        
        CrmLogControl.RegisterCompensator strProgIdCompensator, strDescription, CRMREGFLAG_ALLPHASES
    
    Wend
    
    On Error GoTo ErrorHandler
    
    Exit Sub
    
ErrorHandler:

    Dim strPrompt As String
    
    strPrompt = "RegisterCrmFilesVBCompensator ErrorHandler " + Err.Description
    
    MsgBox strPrompt
    
End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: CrmFilesWorker_CreateFile
'
'Summary: Writes to the log and then creates a file
'
'Args: ByVal bstrFileName As String
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Public Sub CrmFilesWorker_CreateFile(ByVal bstrFileName As String)
    
    On Error GoTo ErrorHandler
    
    If CrmLogControl Is Nothing Then
   
        Call GetCrmLogControl
        
    End If
    
    Call RegisterCrmFilesVBCompensator
    
    ' does the file already exist? we expect this to fail
    
    On Error Resume Next
    
    Err.Clear
    
    Open bstrFileName For Input As #1    ' Input will not create a new file
        
    If Err.Number = 0 Then     ' file already exists
        
        Close #1
        
        GoTo ErrorHandler
        
    End If
    
    Err.Clear
    
    On Error GoTo ErrorHandler
    
    ' WRITE AHEAD - log that we are about to create the file
    
    ' write the "create file" log record

    ' array with 2 elements, lower bound 0, upper bound 1
    
    Dim aLogRecord(1) As Variant
    
    Dim Command As Integer
    
    Command = CommandCreateFile
    
    aLogRecord(CommandIndex) = Command
    
    aLogRecord(FileNameIndex) = bstrFileName
        
    CrmLogControl.WriteLogRecordVariants aLogRecord
    
    ' force the log to ensure this log record is durable in the log
    
    CrmLogControl.ForceLog
    
    ' TRY TO CREATE THE FILE
    
    Open bstrFileName For Append As #2   ' Append will create a new file
    
    Close #2
    
    Exit Sub
    
ErrorHandler:
        
    ' abort transaction directly
    
    Dim strPrompt As String
    
    strPrompt = "CreateFile ErrorHandler " + Err.Description + " " + bstrFileName
    
    MsgBox strPrompt
    
    CrmLogControl.ForceTransactionToAbort
    
End Sub

'M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
'Method: CrmFilesWorker_DeleteFile
'
'Summary: Writes to the log and then renames the file
'
'Args: ByVal bstrFileName As String
'
'M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/

Public Sub CrmFilesWorker_DeleteFile(ByVal bstrFileName As String)
    
    On Error GoTo ErrorHandler
    
    If CrmLogControl Is Nothing Then
   
        Call GetCrmLogControl
        
    End If
    
    Call RegisterCrmFilesVBCompensator
    
    Dim strTempName As String
        
    ' allocate some space

    strTempName = String(32, "*")

    ' the file we're using must be unique, so find a TMP file name

    Dim lRc As Long

    Dim lpszPath As String

    lpszPath = "C:\TEMP"        ' CODEWORK:

    Dim lpPrefixString As String

    lpPrefixString = "CRM"

    Dim wUnique As Long

    wUnique = 0     ' will CREATE a guaranteed unique temp file
    
    'MsgBox "calling GetTempFileName"

    ' NOTE - this will CREATE the unique temp file, so we must delete it later

    lRc = GetTempFileName(lpszPath, lpPrefixString, wUnique, strTempName)

    If (lRc = 0) Then

        MsgBox "GetTempFileName failed"

        GoTo ErrorHandler

    End If
    
    ' does the file exist? we expect this to succeed
        
    Open bstrFileName For Input As #1    ' Input will not create a new file
            
    Close #1
     
    ' file exists - there is a window here in which it might be deleted by someone else

    ' WRITE AHEAD - log that we are about to delete (rename) the file
    
    ' write the "delete file" log record
    
    ' array with 3 elements, lower bound 0, upper bound 2
    
    Dim aLogRecord(2) As Variant
    
    Dim Command As Integer
    
    Command = CommandDeleteFile
    
    aLogRecord(CommandIndex) = Command
    
    aLogRecord(FileNameIndex) = bstrFileName
    
    aLogRecord(TempFileNameIndex) = strTempName
    
    ' DELETE the temp file that was just created so we can rename our existing file
    
    ' NOTE - must do this before we write to the log
    
    ' NOTE - if we crash here, it is possible there is a temp file left around
    
    Kill strTempName
    
    CrmLogControl.WriteLogRecordVariants aLogRecord
    
    ' force the log to ensure this log record is durable in the log
    
    CrmLogControl.ForceLog
        
    ' TRY TO RENAME THE FILE TO A TEMP FILE

    Name bstrFileName As strTempName
        
    Exit Sub
    
ErrorHandler:
        
   ' abort transaction directly
    
    Dim strPrompt As String
    
    strPrompt = "DeleteFile ErrorHandler " + Err.Description + " " + bstrFileName
    
    MsgBox strPrompt

    CrmLogControl.ForceTransactionToAbort
     
End Sub



