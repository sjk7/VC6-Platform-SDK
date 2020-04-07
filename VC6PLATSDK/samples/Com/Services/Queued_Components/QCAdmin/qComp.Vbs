' QComp.vbs - Mark (or unmark) all a component's interfaces QUEUEABLE that can be so marked

Option Explicit

' Parse command line

Dim ArgumentCollection, Argument

Dim bSilent 
Dim bEnable
Dim programID

bSilent = False
bEnable = True
programID = ""

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
		programID = Argument
    End If
    
Next

If programID = "" Then
	Usage
End If

' Locate the Component in its COM+ Application

Dim catalog
Dim ApplicationCollection, Application
Dim ComponentCollection, Component, SelectedComponent

Set SelectedComponent = Nothing

Set catalog = Wscript.CreateObject("COMAdmin.COMAdminCatalog.1")
Set ApplicationCollection = catalog.GetCollection("Applications")
ApplicationCollection.Populate

For Each Application In ApplicationCollection 
	Set ComponentCollection = ApplicationCollection.GetCollection("Components", Application.Value("ID"))
	ComponentCollection.Populate
	For Each Component In ComponentCollection
		' Program IDs are case-insensitive
		If LCase(Component.Value("ProgID")) = LCase(programID) Then
			Set SelectedComponent = Component
			Exit For
		End If
	Next
Next

If SelectedComponent Is Nothing Then
	If Not bSilent Then
		Wscript.Echo "Program ID " & programID & " not found."
	End If
	Wscript.Quit 1
End If

' Try to mark all the component's interfaces that can be marked QUEUEABLE

Dim InterfaceCollection, Interface

Set InterfaceCollection = ComponentCollection.GetCollection("InterfacesForComponent", SelectedComponent.Value("CLSID"))
InterfaceCollection.Populate

Dim InterfaceCount
InterfaceCount = 0

For Each Interface In InterfaceCollection
	If Interface.Value("QueuingSupported") Then
		Interface.Value("QueuingEnabled") = bEnable
		InterfaceCount = InterfaceCount + 1
	End If
Next

' If any interfaces were changed, save our changes.

If InterfaceCount > 0 Then
	InterfaceCollection.SaveChanges
	If Not bSilent Then
		If bEnable Then
			Wscript.Echo "QComp /E " & programID & " success."
		Else
			Wscript.Echo "QComp /D " & programID & " success."
		End If
	End If
	Wscript.Quit 0 ' Normal completion
End If

' No interfaces were QUEUEABLE

If bEnable Then
	If Not bSilent Then
		Wscript.Echo "QComp /E " & programID & " has no QUEUEABLE interfaces"
	End If
End If

Wscript.Quit 2

Sub Usage
	If Not bSilent Then
		Wscript.Echo "Usage: QComp [/Enable] [/Disable] [/Silent] [/Verbose] ProgramId"
	End If
	Wscript.Quit 9
End Sub
	