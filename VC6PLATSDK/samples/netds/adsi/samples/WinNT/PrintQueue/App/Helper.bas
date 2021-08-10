Attribute VB_Name = "Helper"
'-----------------------------------------------
'---------Public Constants----------------------
'------------------------------------------------

'----- Print Status ------------------
Public Const PRINTER_STATUS_PAUSED = &H1
Public Const PRINTER_STATUS_ERROR = &H2
Public Const PRINTER_STATUS_PENDING_DELETION = &H4
Public Const PRINTER_STATUS_PAPER_JAM = &H8
Public Const PRINTER_STATUS_PAPER_OUT = &H10
Public Const PRINTER_STATUS_MANUAL_FEED = &H20
Public Const PRINTER_STATUS_PAPER_PROBLEM = &H40
Public Const PRINTER_STATUS_OFFLINE = &H80
Public Const PRINTER_STATUS_IO_ACTIVE = &H100
Public Const PRINTER_STATUS_BUSY = &H200
Public Const PRINTER_STATUS_PRINTING = &H400
Public Const PRINTER_STATUS_OUTPUT_BIN_FULL = &H800
Public Const PRINTER_STATUS_NOT_AVAILABLE = &H1000
Public Const PRINTER_STATUS_WAITING = &H2000
Public Const PRINTER_STATUS_PROCESSING = &H4000
Public Const PRINTER_STATUS_INITIALIZING = &H8000
Public Const PRINTER_STATUS_WARMING_UP = &H10000
Public Const PRINTER_STATUS_TONER_LOW = &H20000
Public Const PRINTER_STATUS_NO_TONER = &H40000
Public Const PRINTER_STATUS_PAGE_PUNT = &H80000
Public Const PRINTER_STATUS_USER_INTERVENTION = &H100000
Public Const PRINTER_STATUS_OUT_OF_MEMORY = &H200000
Public Const PRINTER_STATUS_DOOR_OPEN = &H400000
Public Const PRINTER_STATUS_SERVER_UNKNOWN = &H800000
Public Const PRINTER_STATUS_POWER_SAVE = &H1000000


Public Const JOB_STATUS_PAUSED = &H1
Public Const JOB_STATUS_ERROR = &H2
Public Const JOB_STATUS_DELETING = &H4
Public Const JOB_STATUS_SPOOLING = &H8
Public Const JOB_STATUS_PRINTING = &H10
Public Const JOB_STATUS_OFFLINE = &H20
Public Const JOB_STATUS_PAPEROUT = &H40
Public Const JOB_STATUS_PRINTED = &H80
Public Const JOB_STATUS_DELETED = &H100
Public Const JOB_STATUS_BLOCKED_DEVQ = &H200
Public Const JOB_STATUS_USER_INTERVENTION = &H400
Public Const JOB_STATUS_RESTART = &H800



Public Function GetPrintStatus(status As Long) As String

s = ""

If (status = 0) Then
  GetPrintStatus = "OK"
  Exit Function
End If



If (status And PRINTER_STATUS_PAUSED) Then
  s = s + " Pause"
End If

If (status And PRINTER_STATUS_PAUSED) Then
  s = s + " Pause"
End If

If (status And PRINTER_STATUS_ERROR) Then
  s = s + " Error"
End If

If (status And PRINTER_STATUS_PENDING_DELETION) Then
  s = s + " Pending Deletion"
End If


If (status And PRINTER_STATUS_PENDING_DELETION) Then
     s = s + " Pending Deletion"
End If

If (status And PRINTER_STATUS_PAPER_JAM) Then
     s = s + " Paper Jam"
End If

If (status And PRINTER_STATUS_PAPER_OUT) Then
     s = s + " Paper Out"
End If

If (status And PRINTER_STATUS_MANUAL_FEED) Then
     s = s + " Manual Feed"
End If

If (status And PRINTER_STATUS_PAPER_PROBLEM) Then
     s = s + " Paper Problem"
End If

If (status And PRINTER_STATUS_OFFLINE) Then
     s = s + " OffLine"
End If

If (status And PRINTER_STATUS_IO_ACTIVE) Then
     s = s + " IO Active"
End If

If (status And PRINTER_STATUS_BUSY) Then
     s = s + " Busy"
End If

If (status And PRINTER_STATUS_PRINTING) Then
     s = s + " Printing"
End If

If (status And PRINTER_STATUS_OUTPUT_BIN_FULL) Then
     s = s + " Output Bin Full"
End If

If (status And PRINTER_STATUS_NOT_AVAILABLE) Then
     s = s + " Not Available"
End If

If (status And PRINTER_STATUS_WAITING) Then
     s = s + " Waiting"
End If

If (status And PRINTER_STATUS_PROCESSING) Then
     s = s + " Processing"
End If

If (status And PRINTER_STATUS_INITIALIZING) Then
     s = s + " Initializing"
End If


If (status And PRINTER_STATUS_WARMING_UP) Then
     s = s + " Warming up"
End If

If (status And PRINTER_STATUS_TONER_LOW) Then
     s = s + " Toner Low"
End If

If (status And PRINTER_STATUS_NO_TONER) Then
     s = s + " No Toner"
End If

If (status And PRINTER_STATUS_PAGE_PUNT) Then
     s = s + " Can print Current Page"
End If

If (status And PRINTER_STATUS_USER_INTERVENTION) Then
     s = s + " User Intervention"
End If

If (status And PRINTER_STATUS_OUT_OF_MEMORY) Then
     s = s + " Out of Memory"
End If

If (status And PRINTER_STATUS_DOOR_OPEN) Then
     s = s + " Door Open"
End If

If (status And PRINTER_STATUS_SERVER_UNKNOWN) Then
     s = s + " Server Unknown"
End If

If (status And PRINTER_STATUS_POWER_SAVE) Then
     s = s + " Power Save"
End If

GetPrintStatus = s

End Function



Public Function GetJobStatus(status As Long) As String

s = ""

If (status = 0) Then
  GetJobStatus = "OK"
  Exit Function
End If


If (status And JOB_STATUS_PAUSED) Then
  s = s + " Paused"
End If

If (status And JOB_STATUS_ERROR) Then
 s = s + " Error"
End If

If (status And JOB_STATUS_DELETING) Then
 s = s + " Deleting"
End If

If (status And JOB_STATUS_SPOOLING) Then
 s = s + " Spooling"
End If

If (status And JOB_STATUS_PRINTING) Then
 s = s + " Printing"
End If

If (status And JOB_STATUS_OFFLINE) Then
 s = s + " Offline"
End If

If (status And JOB_STATUS_PAPEROUT) Then
 s = s + " Paper Out"
End If

If (status And JOB_STATUS_PRINTED) Then
 s = s + " Printed"
End If

If (status And JOB_STATUS_DELETED) Then
 s = s + " Deleted"
End If


If (status And JOB_STATUS_BLOCKED_DEVQ) Then
 s = s + " Blocked"
End If

If (status And JOB_STATUS_USER_INTERVENTION) Then
 s = s + " User Intervention"
End If

If (status And JOB_STATUS_RESTART) Then
 s = s + " Restart"
End If


GetJobStatus = s
End Function


