' QCStart.vbs - Start a COM+ application

Option Explicit

' Parse command line

Dim ArgumentCollection
Dim Argument
Dim programID
Dim AdminCatalog

programID = ""

Set ArgumentCollection = Wscript.Arguments

For Each Argument In ArgumentCollection
    
    If Left(Argument, 1) = "?" Then
	Usage
    Else
	programID = Argument
    End If
    
Next

If programID = "" Then
	Usage
End If

set AdminCatalog = CreateObject("COMAdmin.COMAdminCatalog")
AdminCatalog.StartApplication(programID)

Wscript.Quit 0 ' Normal completion

Sub Usage
    Wscript.Echo "Usage: QCStart ProgramId"
    Wscript.Quit 9
End Sub
	