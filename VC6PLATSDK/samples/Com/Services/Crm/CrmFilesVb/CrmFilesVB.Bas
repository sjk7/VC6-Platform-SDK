Attribute VB_Name = "CrmFilesConstants"
Public Const XACT_E_RECOVERYINPROGRESS = -2147799170#

Public Const CommandIndex = 0
Public Const FileNameIndex = 1
Public Const TempFileNameIndex = 2

Public Const CommandCreateFile = 1
Public Const CommandDeleteFile = 2

Declare Function GetTempFileName Lib "kernel32" Alias "GetTempFileNameA" (ByVal lpszPath As String, ByVal lpPrefixString As String, ByVal wUnique As Long, ByVal lpTempFileName As String) As Long



