Attribute VB_Name = "modGlobalVariables"
'--------------------------------------------------------------------------
'
'  Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
' Constants

'Error Constants defined to enable proper error reporting
Public Const UPNP_E_ROOT_ELEMENT_EXPECTED = &H80040200
Public Const UPNP_E_DEVICE_ELEMENT_EXPECTED = &H80040201
Public Const UPNP_E_SERVICE_ELEMENT_EXPECTED = &H80040202
Public Const UPNP_E_SERVICE_NODE_INCOMPLETE = &H80040203
Public Const UPNP_E_DEVICE_NODE_INCOMPLETE = &H80040204
Public Const UPNP_E_ICON_ELEMENT_EXPECTED = &H80040205
Public Const UPNP_E_ICON_NODE_INCOMPLETE = &H80040206
Public Const UPNP_E_INVALID_ACTION = &H80040207
Public Const UPNP_E_INVALID_ARGUMENTS = &H80040208
Public Const UPNP_E_OUT_OF_SYNC = &H80040209
Public Const UPNP_E_ACTION_REQUEST_FAILED = &H80040210
Public Const UPNP_E_TRANSPORT_ERROR = &H80040211
Public Const UPNP_E_VARIABLE_VALUE_UNKNOWN = &H80040212
Public Const UPNP_E_INVALID_VARIABLE = &H80040213
Public Const UPNP_E_DEVICE_ERROR = &H80040214
Public Const UPNP_E_PROTOCOL_ERROR = &H80040215
Public Const UPNP_E_ERROR_PROCESSING_RESPONSE = &H80040216
Public Const UPNP_E_DEVICE_TIMEOUT = &H80040217
Public Const UPNP_E_DEVICE_SPECIFIC_ERROR = &H80040300
Public Const UPNP_E_INVALID_DOCUMENT = &H80040500
Public Const UPNP_E_EVENT_SUBSCRIPTION_FAILED = &H80040501
Public Const UPNP_E_UPNP_NOT_INSTALLED = &H1AD

'-------------------------------------------------------------------------
'   DOM Constants
'-------------------------------------------------------------------------
Public Const READYSTATE_COMPLETE = 4

'Global Variables

Public g_devFinder As Object ' This will store the device finder object and needs to be global for the purpose of cancelling the find
Public g_deviceArray()  ' Maps the devices in the device list to the device objects
Public g_serviceArray()  ' Maps the services in the service list to the service objects

' For maintaining the list of device types
Public g_deviceTypeArray() As String 'Maps the friendly names of the device type list to the actual device types

' The objects which keep track of the current selected Device and current selected Service
Public g_currentDevice As UPnPDevice
Public g_currentService As UPnPService

Public g_lDevFindHandle As Long ' for the async find
Public g_fDevFindHandle As Boolean

' Objects for maintaining the callbacks
Public g_devFD As FunctionDelegator
Public g_serviceFD As FunctionDelegator

'-------------------------------------------------------------------------
'   Private Attributes
'-------------------------------------------------------------------------


Public g_XMLNodeFlag As Boolean

Public global_xml_node As IXMLDOMNode ' This is used to maintain currently selected xml node

