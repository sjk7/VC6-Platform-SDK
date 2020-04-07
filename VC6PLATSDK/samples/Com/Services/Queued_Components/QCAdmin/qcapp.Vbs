' QCApp.vbs - Enable or Disable COM+ Application for queuing

Option Explicit

Dim ArgumentCollection, Argument

Dim bSilent 
Dim bEnable
Dim applName

bSilent = False
bEnable = True
applName = ""

Set ArgumentCollection = Wscript.Arguments

For Each Argument In ArgumentCollection
    
	If Left(Argument, 1) = "/" Or Left(Argument, 1) = "-" Then
		Dim c2
		c2 = LCase(Mid(Argument,2,1))
		If     c2 = "v" Then
			bSilent = False
		ElseIf c2 = "s" Then
			bSilent = True
		ElseIf c2 = "e" Then
			bEnable = True
		ElseIf c2 = "d" Then
			bEnable = False
		Else
			Usage
		End If

    ElseIf Left(Argument, 1) = "?" Then
		Usage
	Else
		applName = Argument
    End If
    
Next

If applName = "" Then
	Usage
End If

' Locate the COM+ Application in the COM+ catalog

Dim catalog
Dim ApplicationCollection, Application, SelectedApplication

Set SelectedApplication = Nothing

Set catalog = Wscript.CreateObject("COMAdmin.COMAdminCatalog.1")
Set ApplicationCollection = catalog.GetCollection("Applications")
ApplicationCollection.Populate

For Each Application In ApplicationCollection
	' App names are case-insensitive
	If LCase(Application.Value("Name")) = LCase(applName) Then
		Set SelectedApplication = Application
		Exit For
	End If
Next

If SelectedApplication Is Nothing Then
	If Not bSilent Then
		Wscript.Echo applName & " not found in COM+ Applications."
	End If
	Wscript.Quit 1
End If

SelectedApplication.Value("QueuingEnabled") = bEnable
ApplicationCollection.SaveChanges
	
If Not bSilent Then
	If bEnable Then
		Wscript.Echo "QCApp /Enable " & applName & " success"
	Else
		Wscript.Echo "QCApp /Disable " & applName & " success"
	End If
End If

Wscript.Quit 0

Sub Usage
	If Not bSilent Then
		Wscript.Echo "Usage: QCApp [/Enable] [/Disable] [/Silent] [/Verbose] ApplicationName"
	End If
	Wscript.Quit 9
End Sub
	