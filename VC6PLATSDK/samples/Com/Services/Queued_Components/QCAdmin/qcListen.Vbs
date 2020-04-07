' QCListen.vbs - Enable or Disable COM+ QC Listener & start application

Option Explicit

' Parse command line

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

' Locate the SelectedApplication in the COM+ catalog

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

' Verify that the App is QueuingEnabled

If Not SelectedApplication.Value("QueuingEnabled") Then
	If Not bSilent Then
		Wscript.Echo "Application " & applName & " is not QueuingEnabled"
	End If
	Wscript.Quit 2
End If

' Enable or disable the listener

SelectedApplication.Value("QueueListenerEnabled") = bEnable
ApplicationCollection.SaveChanges

' If we're enabling the listener, start the app 

If bEnable Then

	' Make sure that the app contains at least one component
     
	Dim ComponentCollection       
    Set ComponentCollection = ApplicationCollection.GetCollection("Components", SelectedApplication.Value("ID"))
    ComponentCollection.populate
               
    If ComponentCollection.Count < 1 Then
		If not bSilent Then
	        Wscript.Echo "Unable to start application " & applName & " as it has no components."
		End If
        WScript.Quit 3
    End If

	Set ComponentCollection = Nothing
	Set SelectedApplication = Nothing
	Set ApplicationCollection = Nothing
	
	' Start the application (by getting an interface to a component's class object)
    
    catalog.StartApplication applName
    
    If Not bSilent Then
        Wscript.Echo "QCListen /Enable " & applName & " success"
    End If
    
Else ' Not bEnable

    If Not bSilent Then
        MsgBox "QCListen /Disable " & applName & " success"
    End If

End If

Wscript.Quit 0

Sub Usage
	Wscript.Echo "Usage: QCListen [/Enable] [/Disable] [/Silent] [/Verbose] ApplicationName"
	Wscript.Quit 9
End Sub
	