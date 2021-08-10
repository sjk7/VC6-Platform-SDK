VERSION 5.00
Begin VB.Form DeviceControl 
   AutoRedraw      =   -1  'True
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Generic UCP"
   ClientHeight    =   8895
   ClientLeft      =   7410
   ClientTop       =   7845
   ClientWidth     =   7530
   ClipControls    =   0   'False
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6.476
   ScaleMode       =   0  'User
   ScaleWidth      =   3.256
   StartUpPosition =   2  'CenterScreen
   Begin VB.Frame deviceDiscFrame 
      Height          =   7335
      Left            =   240
      TabIndex        =   0
      Top             =   840
      Width           =   7095
      Begin VB.CommandButton cmdInvoke 
         Caption         =   "&Invoke"
         Height          =   495
         Left            =   3840
         TabIndex        =   28
         Top             =   6720
         Width           =   1095
      End
      Begin VB.CommandButton cmdClose 
         Caption         =   "&Close"
         Height          =   495
         Left            =   5640
         TabIndex        =   29
         Top             =   6720
         Width           =   1095
      End
      Begin VB.CommandButton cmdQuery 
         Caption         =   "&Query"
         Height          =   495
         Left            =   2040
         TabIndex        =   27
         Top             =   6720
         Width           =   1095
      End
      Begin VB.CommandButton cmdViewSCPD 
         Caption         =   "&View Service       Desc."
         Height          =   495
         Left            =   300
         TabIndex        =   26
         Top             =   6720
         Width           =   1095
      End
      Begin VB.CommandButton cmdPresentation 
         Caption         =   "View P&resentation"
         Height          =   375
         Left            =   4200
         TabIndex        =   13
         Top             =   3300
         Width           =   1455
      End
      Begin VB.CommandButton cmdDevProp 
         Caption         =   "Device &Properties"
         Height          =   375
         Left            =   1680
         TabIndex        =   11
         Top             =   3300
         Width           =   1455
      End
      Begin VB.CommandButton cmdDiscovery 
         Caption         =   "Start &Discovery"
         Height          =   375
         Left            =   2880
         TabIndex        =   6
         Top             =   1680
         Width           =   1455
      End
      Begin VB.ComboBox cboActionName 
         Height          =   315
         Left            =   1855
         TabIndex        =   21
         Top             =   5280
         Width           =   4980
      End
      Begin VB.ComboBox cboVariable 
         Height          =   315
         Left            =   1855
         TabIndex        =   19
         Top             =   4860
         Width           =   4980
      End
      Begin VB.TextBox txtSCPDUrl 
         Height          =   315
         Left            =   1855
         TabIndex        =   17
         Top             =   4440
         Width           =   4980
      End
      Begin VB.TextBox txtActionOut 
         Height          =   315
         Left            =   1855
         Locked          =   -1  'True
         TabIndex        =   25
         Top             =   6120
         Width           =   4980
      End
      Begin VB.TextBox txtActionArgument 
         Height          =   315
         Left            =   1855
         TabIndex        =   23
         Top             =   5700
         Width           =   4980
      End
      Begin VB.ComboBox cboService 
         Height          =   315
         Left            =   105
         Style           =   2  'Dropdown List
         TabIndex        =   15
         Top             =   4020
         Width           =   6735
      End
      Begin VB.Frame Frame1 
         Height          =   1335
         Left            =   240
         TabIndex        =   12
         Top             =   240
         Width           =   6615
         Begin VB.OptionButton optFindByType 
            Caption         =   "Find by &Type"
            Height          =   195
            Left            =   240
            TabIndex        =   2
            Top             =   360
            Width           =   1335
         End
         Begin VB.OptionButton optFindByUDN 
            Caption         =   "Find by &UDN"
            Height          =   195
            Left            =   2520
            TabIndex        =   3
            Top             =   360
            Width           =   1695
         End
         Begin VB.OptionButton optAsyncFind 
            Caption         =   "&Async Find"
            Height          =   195
            Left            =   4920
            TabIndex        =   4
            Top             =   360
            Width           =   1335
         End
         Begin VB.ComboBox cboFind 
            Height          =   315
            Left            =   120
            TabIndex        =   5
            Text            =   "comboFind"
            Top             =   720
            Width           =   6255
         End
      End
      Begin VB.ComboBox cboDevice 
         Height          =   315
         IntegralHeight  =   0   'False
         Left            =   105
         Style           =   2  'Dropdown List
         TabIndex        =   10
         Top             =   2835
         Width           =   6735
      End
      Begin VB.Label lblStatus 
         BorderStyle     =   1  'Fixed Single
         Height          =   255
         Left            =   960
         TabIndex        =   8
         Top             =   2160
         Width           =   5895
      End
      Begin VB.Label staticText 
         Caption         =   "Status"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   7
         Top             =   2160
         Width           =   855
      End
      Begin VB.Label staticText 
         Caption         =   "Service Desc. URL"
         Height          =   255
         Index           =   3
         Left            =   105
         TabIndex        =   16
         Top             =   4440
         Width           =   1575
      End
      Begin VB.Label staticText 
         Caption         =   "Query Variable : "
         Height          =   255
         Index           =   4
         Left            =   105
         TabIndex        =   18
         Top             =   4890
         Width           =   1575
      End
      Begin VB.Label staticText 
         Caption         =   "Query State Value / Action Out Arguments "
         Height          =   375
         Index           =   7
         Left            =   105
         TabIndex        =   24
         Top             =   6120
         Width           =   1575
      End
      Begin VB.Label staticText 
         Caption         =   "Action Arguments :"
         Height          =   255
         Index           =   6
         Left            =   105
         TabIndex        =   22
         Top             =   5790
         Width           =   1575
      End
      Begin VB.Label staticText 
         Caption         =   "Invoke Action :"
         Height          =   255
         Index           =   5
         Left            =   105
         TabIndex        =   20
         Top             =   5340
         Width           =   1575
      End
      Begin VB.Label staticText 
         Caption         =   "Choose Service"
         Height          =   255
         Index           =   2
         Left            =   105
         TabIndex        =   14
         Top             =   3735
         Width           =   1575
      End
      Begin VB.Label staticText 
         Caption         =   "Devices Found"
         Height          =   255
         Index           =   1
         Left            =   105
         TabIndex        =   9
         Top             =   2520
         Width           =   1455
      End
   End
   Begin VB.Label GenericUCPlLabel 
      Alignment       =   2  'Center
      Caption         =   "Generic UCP"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   18
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   1860
      TabIndex        =   1
      Top             =   120
      Width           =   3735
   End
   Begin VB.Label staticText 
      Caption         =   "Events"
      Height          =   255
      Index           =   8
      Left            =   240
      TabIndex        =   30
      Top             =   8400
      Width           =   855
   End
   Begin VB.Label lblEvent 
      BorderStyle     =   1  'Fixed Single
      Height          =   495
      Left            =   1200
      TabIndex        =   31
      Top             =   8280
      Width           =   6135
   End
End
Attribute VB_Name = "DeviceControl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------------------------------
'
'  Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
' This consists of the functions related to the main form of Generic UCP.
' This performs discovery, control and eventing of the discovered UPNP devices

'+--------------------------------------------------------------------------------------------------
'
'  Function : Form_Load
'
'  Purpose : Initialize the variables when the form is loaded
'
'  Arguments: None
'
'  Return: None
'
'  Note:
'
'
'


Private Sub Form_Load()

'Initialize variables
lblStatus.Caption = "Device discovery. Choose the type of device discovery and proceed"
Set g_currentDevice = Nothing
optAsyncFind.value = True  'Select Async Find as default search
g_fDevFindHandle = False ' Async Find is not proceeding
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : Form_Unload
'
'  Purpose : Called when the form is unloaded
'
'  Arguments: Cancel [in] Called when the form is unloaded with cancel button
'
'  Return:
'
'  Note: We release all the pointers to the device array and service array
'
'
'
Private Sub Form_Unload(Cancel As Integer)
Set g_currentDevice = Nothing
Set g_currentService = Nothing
ReDim g_deviceArray(0)
ReDim g_serviceArray(0)
g_fDevFindHandle = False
End ' End the program
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdClose_Click
'
'  Purpose : Close the application
'
'  Arguments:
'
'  Return:
'
'  Note: Called when the Close button is clicked
'
'
'

Private Sub cmdClose_Click()
Unload Me
End ' Just exit the application. The objects will automatically clean up
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : optFindByType_Click
'
'  Purpose : Initialize the lists with the appropriate list of device types
'
'  Arguments:
'
'  Return:
'
'  Note: Called when the FindByType radio button is clicked
'
'
'


'FindbyType is clicked and initialize the list for it
Private Sub optFindByType_Click()

Call StopAsyncFindIfStarted
Call ClearAllDataStructures(True)
Call initializeDevTypeList ' Initialize the device Type List
cboFind.ListIndex = 0

End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : optAsyncFind_Click
'
'  Purpose : Initialize the lists with the appropriate list of device types
'
'  Arguments:
'
'  Return:
'
'  Note: Called when the AsyncFind radio button is clicked
'
'
'
Private Sub optAsyncFind_Click()

Call StopAsyncFindIfStarted
Call ClearAllDataStructures(True)
Call initializeDevTypeList ' Initialize  the device type list
cboFind.ListIndex = 0

End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : optFindByUdn_Click
'
'  Purpose : Initialize the lists with the appropriate list of UDNs
'
'  Arguments:
'
'  Return:
'
'  Note: Called when the FindByUdn radio button is clicked
'
'
'

Private Sub optFindByUDN_Click()

Call StopAsyncFindIfStarted
Call ClearAllDataStructures(True)
Call initializeUDNList ' UDNs are initialized in the list
cboFind.ListIndex = 0
End Sub



'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdDiscovery_Click
'
'  Purpose : Start the search for devices according to the type of search chosen
'
'  Arguments:
'
'  Return:
'
'  Note: Called when the Start Discovery button is clicked
'
'
'
Private Sub cmdDiscovery_Click()
On Error GoTo Error

Dim strFindText As String

Call StopAsyncFindIfStarted
Call ClearAllDataStructures(False)

'Depending upon the type of search, proceed with the right one
If optFindByType.value = False And optFindByUDN.value = False And optAsyncFind.value = False Then
    MsgBox "Must choose either FindByType or FindByUdn or AsyncFind"
    Exit Sub
End If

If cboFind.ListIndex = -1 And cboFind.Text = "" Then
    MsgBox "Select one of the items from the list"
    Exit Sub
End If

' We must get the search criteria here
If optFindByType.value = True Or optAsyncFind.value = True Then
    ' We must convert the string value to the appropriate string to use
    If (cboFind.ListIndex = -1) Then
        strFindText = cboFind.Text
    Else
        strFindText = g_deviceTypeArray(cboFind.ListIndex)
    End If
ElseIf optFindByUDN.value = True Then
    strFindText = cboFind.Text
End If


' We have all the information necessary to start the search
Set g_devFinder = CreateObject("UPnP.UPnPDeviceFinder.1") ' Create a device finder object
If optFindByType.value = True Then
    'FindByType
    Call ProcessFindByType(strFindText)
ElseIf optFindByUDN.value = True Then
    'FindByUDN
    Call ProcessFindByUDN(strFindText)
ElseIf optAsyncFind.value = True Then
    'AsyncFind
    Call ProcessAsyncFind(strFindText)
    Exit Sub ' We are exiting here
End If

' Set the current device for the first two cases of search
If cboDevice.ListCount > 0 Then
    Set g_currentDevice = g_deviceArray(0)
End If
lblStatus.Caption = " End of discovery process"

Set g_devFinder = Nothing ' Release the device finder object
Exit Sub
Error:
ErrorPrint (Err.Number)
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : ProcessFindByType
'
'  Purpose : Process the FindByType search.
'
'  Arguments: strDeviceType [in] Device type to be searched
'
'  Return:
'
'  Note:
'
'
'
Private Sub ProcessFindByType(strDeviceType As String)
'On Error GoTo Error

Dim devices
Dim device As UPnPDevice
Dim iCount As Integer
Dim iIndex As Integer
'FindByType
lblStatus.Caption = "Proceeding with FindbyType"
Set devices = g_devFinder.FindByType(strDeviceType, FD_ANY)
iCount = devices.count
If iCount = 0 Then ' No devices found
    MsgBox "Found no devices for type given"
    Exit Sub
End If
ReDim Preserve g_deviceArray(iCount)

' Add all the found devices to the list
iIndex = 0
For Each device In devices
    Set g_deviceArray(iIndex) = device
    cboDevice.AddItem device.FriendlyName
    iIndex = iIndex + 1
Next
cboDevice.ListIndex = 0
Exit Sub

Error:
ErrorPrint (Err.Number)
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : ProcessFindByUDN
'
'  Purpose : Process the FindByUDN search.
'
'  Arguments: strDeviceUDN [in] Device UDN to be searched
'
'  Return:
'
'  Note:
'
'
'
Private Sub ProcessFindByUDN(strDeviceUDN As String)

On Error GoTo Error
Dim device As UPnPDevice
'FindByUDN
lblStatus.Caption = "Proceeding with FindByUDN"
Set device = g_devFinder.FindByUDN(strDeviceUDN)
If device Is Nothing Then
    MsgBox "Found no device with the Udn given"
    lblStatus.Caption = ""
    Exit Sub
End If
'Add the found device to the device list
ReDim Preserve g_deviceArray(UBound(g_deviceArray) + 1)
Set g_deviceArray(UBound(g_deviceArray) - 1) = device
cboDevice.AddItem device.FriendlyName
cboDevice.ListIndex = 0
Exit Sub

Error:
ErrorPrint (Err.Number)
End Sub



'+--------------------------------------------------------------------------------------------------
'
'  Function : ProcessAsyncFind
'
'  Purpose : Process the AsyncFind search.
'
'  Arguments: strDeviceType [in] Device type to be searched
'
'  Return:
'
'  Note:
'
'
'
Private Sub ProcessAsyncFind(strDeviceType As String)
On Error GoTo Error

Dim xCallbackInterface As CallbackIUnknownLib.DeviceFinderCallBackInterface
Dim objCallback As Object
Dim ptinfo As ITypeInfo ' For the Async Find used in LoadTypeLibEx
Dim ptcomp As ITypeComp ' For the Async Find used in LoadTypeLibEx

lblStatus.Caption = "Proceeding with AsyncFind"
With LoadTypeLibEx(App.Path & "\cbklib.tlb", REGKIND_NONE).GetTypeComp
    .BindType "DeviceFinderCallbackInterface", 0, ptinfo, ptcomp
End With
    
Set xCallbackInterface = InitDelegator(g_devFD, AddressOf deviceFinderCallback)
Set objCallback = CreateStdDispatch(Nothing, ObjPtr(xCallbackInterface), ptinfo)
g_lDevFindHandle = g_devFinder.CreateAsyncFind(strDeviceType, FD_ANY, objCallback)
g_devFinder.StartAsyncFind (g_lDevFindHandle) 'Start the async find
g_fDevFindHandle = True

Exit Sub
Error:
ErrorPrint (Err.Number)
End Sub



'+--------------------------------------------------------------------------------------------------
'
'  Function : cboDevice_Click
'
'  Purpose : To initialize the variables when one of the devices is chosen from the device list
'
'  Arguments:
'
'  Return:
'
'  Note:
'
'
'

'Function when we select a particular device from the device list
'We make the g_currentDevice as the selected device
'Also we list the services for the selected device in the service list
Private Sub cboDevice_Click()
On Error GoTo Error
Dim services As UPnPServices
Dim service As UPnPService

Enabled = False

If cboDevice.ListIndex = -1 Then
    Set g_currentDevice = Nothing ' No device is selected
    Enabled = True
Else
    Set g_currentDevice = g_deviceArray(cboDevice.ListIndex) ' Select the current device
    Call devProperties.Form_Load ' Load up the device properties so that the current device is reflected in the device properties dialog box
    cboDevice.ToolTipText = cboDevice.List(cboDevice.ListIndex)
    
    ' Here after we select a device, we are going to list the services in the services combo
    lblEvent.Caption = ""
    cboService.Clear
    ' Since we have selected a new device, we have to create a new service list
    ReDim g_serviceArray(0) ' Clear the service array
    Set services = g_currentDevice.services
    If services.count = 0 Then
        MsgBox "Found no services"
        Enabled = True
        Exit Sub
    End If
    For Each service In services
        ReDim Preserve g_serviceArray(UBound(g_serviceArray) + 1)
        Set g_serviceArray(UBound(g_serviceArray) - 1) = service
        cboService.AddItem service.Id
     Next
    Enabled = True
    cboService.ListIndex = 0 ' Select the first service as the current service
    Call cboService_Click ' To add callback for the currently selected service
End If
Exit Sub

Error:
With Err
    ErrorPrint (.Number)
    Enabled = True
End With
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdDevProp_Click
'
'  Purpose : To show the device properties dialog of the chosen device
'
'  Arguments:
'
'  Return:
'
'  Note:
'
'
'

Private Sub cmdDevProp_Click()

If g_currentDevice Is Nothing Then
    MsgBox "No device selected"
    Exit Sub
End If
Load devProperties
devProperties.Show ' Show the device properties for the selected device
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdPresentation_Click
'
'  Purpose : To show the presentation page for the chosen device
'
'  Arguments:
'
'  Return:
'
'  Note: This needs IE to be installed.
'
'
'

Private Sub cmdPresentation_Click()
On Error GoTo Error
Dim oIE As SHDocVw.InternetExplorer

If g_currentDevice Is Nothing Then
    MsgBox "No device selected"
    Exit Sub
End If

If g_currentDevice.PresentationURL = "" Then
    MsgBox "Selected Device has no presentation url"
    Exit Sub
End If

Set oIE = CreateObject("InternetExplorer.Application") ' Create a new instance of IE
If oIE Is Nothing Then
    MsgBox "Can't instantiate Internet Explorer"
    Exit Sub
End If

oIE.Navigate g_currentDevice.PresentationURL
oIE.Visible = True
Exit Sub

Error:
With Err
    ErrorPrint (.Number)
End With
End Sub





'+--------------------------------------------------------------------------------------------------
'
'  Function : cboService_Click
'
'  Purpose : Initialize the variables when one of the services in the service list is chosen
'
'  Arguments:
'
'  Return:
'
'  Note:
'
'
'

Private Sub cboService_Click()

Set g_currentService = Nothing
If cboService.ListIndex = -1 Then
    Set g_currentService = Nothing
Else
    lblEvent.Caption = ""
    lblEvent.Refresh
    Set g_currentService = g_serviceArray(cboService.ListIndex)
    Call AddServiceCbFunction(g_currentService)
End If
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdViewSCPD_Click
'
'  Purpose : To show the service description of the service in a separate dialog
'
'  Arguments:
'
'  Return:
'
'  Note:    Assumes SCPD is present in the text box for SCPD Url
'
'
'
Private Sub cmdViewSCPD_Click()
On Error GoTo Error

' We have to start up a new scpd viewer with the scpd url in the box
' Check whether the scpd url is filled in
If txtSCPDURL.Text = "" Then
    MsgBox "SCPD Url is null"
    Exit Sub
End If

' Load the scpd url in the scpdviewer
SCPDViewer.txtSCPDURL.Text = txtSCPDURL.Text
Call SCPDViewer.cmdBrowse_Click 'First load up the scpd url as xml document
Call SCPDViewer.cmdGenActions_Click 'Generate the list of actions by parsing through the xml tree
Call SCPDViewer.cmdGenVariable_Click 'Generate the list of state variables by parsing through the xml tree
Load SCPDViewer
SCPDViewer.Show 'Show up the scpd viewer dialog box
Exit Sub
Error:
With Err
    ErrorPrint (.Number)
End With
End Sub



'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdQuery_Click
'
'  Purpose : To query a variable for the chosen service
'
'  Arguments:
'
'  Return:
'
'  Note:    Assumes the variable name is present in the variable list to be queried
'
'
'
Private Sub cmdQuery_Click()
On Error GoTo Error
Dim RetVal As Variant

txtActionOut.Text = "" 'Clear up the previous text
' First check whether the device and the service have been selected
If g_currentDevice Is Nothing Then
    MsgBox "No device selected"
    Exit Sub
End If
If g_currentService Is Nothing Then
    MsgBox "No service selected"
    Exit Sub
End If
'Check for the validity of the variable name
If cboVariable.Text = "" Then
    MsgBox "Please specify a query variable"
    Exit Sub
End If
RetVal = g_currentService.QueryStateVariable(cboVariable.Text)
txtActionOut.Text = RetVal ' Print the query state variable in the action out field
Exit Sub
Error:
With Err
    ErrorPrint (.Number)
End With
End Sub




'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdInvoke_Click
'
'  Purpose : To invoke an action for the chosen service
'
'  Arguments:
'
'  Return:
'
'  Note:    Assumes the action name is present in the action list to be invoked
'
'
'
Private Sub cmdInvoke_Click()
On Error GoTo Error

Dim actionArgs() ' Array of the arguments to pass for invokeaction
Dim actionOutArgs As Variant ' Out argument array

Dim RetVal As Variant
Dim count As Long
Dim argsout As Variant

txtActionOut.Text = "" 'Clear up the previous text
' First check whether the device and the service have been selected
If g_currentDevice Is Nothing Then
    MsgBox "No device selected"
    Exit Sub
End If
If g_currentService Is Nothing Then
    MsgBox "No service selected"
    Exit Sub
End If
'Check for the validity of the action name
If cboActionName.Text = "" Then
    MsgBox "Enter a action name"
    Exit Sub
End If

' Here we have to make the argument list and invoke action
Call ConvertArgsToArray(actionArgs()) ' We convert the argument text to array of arguments
'Invoke the action
RetVal = g_currentService.InvokeAction(cboActionName.Text, actionArgs, actionOutArgs)
' We should print the return value and action out arguments to the appropriate field in the dialog
If RetVal <> Empty Then
    txtActionOut.Text = txtActionOut.Text + " " + CStr(RetVal) ' Return argument
End If
For count = 0 To UBound(actionOutArgs)
    txtActionOut.Text = txtActionOut.Text + " " + CStr(actionOutArgs(count)) ' Out arguments
Next count
Exit Sub

Error:
With Err
    ErrorPrint (.Number)
End With
End Sub





'+--------------------------------------------------------------------------------------------------
'
'  Function : ConvertArgsToArray
'
'  Purpose : To convert the argument text to a list of arguments
'
'  Arguments:
'
'  Return:
'
'  Note:    We use space character as the separator
'
'
'
Private Sub ConvertArgsToArray(ByRef actionArgs())
Dim numOfArgs, count
Dim strParseTokens() As String

ReDim actionArgs(0)
If txtActionArgument.Text <> "" Then
numOfArgs = ParseString(txtActionArgument.Text, " ", strParseTokens())
ReDim Preserve actionArgs(numOfArgs)
For count = 0 To numOfArgs - 1
    actionArgs(count) = strParseTokens(count)
Next
End If
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : AddDevice
'
'  Purpose : To add a device to the device list
'
'  Arguments:
'
'  Return:
'
'  Note:    Called during Asynchronous search
'
'

Public Sub AddDevice(ByVal device As Variant)
Dim strDeviceName As String

'Add the device to the array after allocating the memory for it
ReDim Preserve g_deviceArray(UBound(g_deviceArray) + 1)
Set g_deviceArray(UBound(g_deviceArray) - 1) = device
strDeviceName = device.FriendlyName
cboDevice.AddItem strDeviceName
If g_currentDevice Is Nothing Then
    cboDevice.ListIndex = 0
    Set g_currentDevice = g_deviceArray(0)
End If
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : RemoveDevice
'
'  Purpose : To remove the device from the device list
'
'  Arguments:
'
'  Return:
'
'  Note:    Called during Asynchronous search
'
'

Public Sub RemoveDevice(ByVal devUDN As Variant)
Dim strDeviceUDN As String
Dim iIndex As Integer
Dim iInnerIndex As Integer
Dim iUpperBound As Integer
iIndex = 0
While (iIndex < UBound(g_deviceArray))
If g_deviceArray(iIndex).UniqueDeviceName = devUDN Then
    ' Remove the device
    ' Before that check if it is the current device
    If cboDevice.ListIndex = iIndex Then
        If (UBound(g_deviceArray) > 1) Then
            If (iIndex <> 0) Then
                cboDevice.ListIndex = 0
                Set g_currentDevice = g_deviceArray(0)
            Else
                cboDevice.ListIndex = 1
                Set g_currentDevice = g_deviceArray(1)
            End If
        Else
            ' it is the single device
            cboDevice.ListIndex = -1
            Set g_currentDevice = Nothing
        End If
    End If
    cboDevice.RemoveItem (iIndex)
    iInnerIndex = iIndex
    iUpperBound = UBound(g_deviceArray)
    While iInnerIndex < iUpperBound - 1
        Set g_deviceArray(iInnerIndex) = g_deviceArray(iInnerIndex + 1)
        iInnerIndex = iInnerIndex + 1
    Wend
    ReDim Preserve g_deviceArray(iUpperBound - 1)
    ' Dont increase the iIndex since we have to check the new element at the current index
Else
    iIndex = iIndex + 1 ' Else increase the index to proceed
End If
Wend

End Sub



'+--------------------------------------------------------------------------------------------------
'
'  Function : AddDeviceTypeToArray
'
'  Purpose : To add a device type to the list of device types stored globally
'
'  Arguments:
'
'  Return:
'
'  Note:    Called during initializing the findCombo list for FindByType or AsyncFind search
'
'
Public Sub AddDeviceTypeToArray(ByVal deviceType As Variant, ByVal DeviceTypeName As Variant)
ReDim Preserve g_deviceTypeArray(UBound(g_deviceTypeArray) + 1)
g_deviceTypeArray(UBound(g_deviceTypeArray) - 1) = deviceType ' Maintain the map between the list and the array of device types
cboFind.AddItem DeviceTypeName ' Add the device type friendly name to the list
cboFind.ListIndex = 0
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : AddServiceToArray
'
'  Purpose : To add a service to the list of services stored globally
'
'  Arguments:
'
'  Return:
'
'  Note:    Called during instantiation of the services for the device chosen (cboDevice_Click)
'
'
Public Sub AddServiceToArray(ByVal service As Variant)
ReDim Preserve g_serviceArray(UBound(g_serviceArray) + 1)
Set g_serviceArray(UBound(g_serviceArray) - 1) = service
cboService.AddItem service.Id
If g_currentService Is Nothing Then
    cboService.ListIndex = 0
    Set g_currentService = g_serviceArray(0)
End If
End Sub






'+--------------------------------------------------------------------------------------------------
'
'  Function : txtSCPDUrl_Validate
'
'  Purpose : To load the variable list and action list for the given SCPD url
'
'  Arguments:
'
'  Return:
'
'  Note:    Called when a url is entered in the SCPD url text box
'
'
Private Sub txtSCPDUrl_Validate(Cancel As Boolean)
On Error GoTo Error
' Update the lists
If txtSCPDURL.Text = "" Then
    Exit Sub ' No SCPD url is loaded
End If
' Load the scpd url in the scpdviewer
SCPDViewer.txtSCPDURL.Text = txtSCPDURL.Text
Call SCPDViewer.cmdBrowse_Click 'First call up the loading of the scpd xml file
Call SCPDViewer.cmdGenActions_Click ' loading up the actions
Call SCPDViewer.cmdGenVariable_Click ' loading up the variables
Load SCPDViewer
Exit Sub
Error:
With Err
    ErrorPrint (.Number)
End With
End Sub


