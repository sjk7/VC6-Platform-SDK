VERSION 5.00
Begin VB.Form devProperties 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Device Properties"
   ClientHeight    =   8355
   ClientLeft      =   150
   ClientTop       =   450
   ClientWidth     =   9630
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   8355
   ScaleWidth      =   9630
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Height          =   6855
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   9375
      Begin VB.TextBox txtSerialNumber 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   25
         Top             =   6240
         Width           =   7280
      End
      Begin VB.TextBox txtUPC 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   23
         Top             =   5700
         Width           =   7280
      End
      Begin VB.TextBox txtModelURL 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   21
         Top             =   5160
         Width           =   7280
      End
      Begin VB.TextBox txtModelDescription 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   19
         Top             =   4620
         Width           =   7280
      End
      Begin VB.TextBox txtModelNumber 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   17
         Top             =   4080
         Width           =   7280
      End
      Begin VB.TextBox txtModelName 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   15
         Top             =   3540
         Width           =   7280
      End
      Begin VB.TextBox txtManufacturerURL 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   13
         Top             =   3000
         Width           =   7280
      End
      Begin VB.TextBox txtManufacturer 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   11
         Top             =   2460
         Width           =   7280
      End
      Begin VB.TextBox txtPresentationURL 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   9
         Top             =   1920
         Width           =   7280
      End
      Begin VB.TextBox txtDeviceType 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   7
         Top             =   1380
         Width           =   7280
      End
      Begin VB.TextBox txtFriendlyName 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   5
         Top             =   840
         Width           =   7280
      End
      Begin VB.TextBox txtUDN 
         Height          =   375
         Left            =   1800
         Locked          =   -1  'True
         TabIndex        =   3
         Top             =   300
         Width           =   7280
      End
      Begin VB.Label labelDev 
         Caption         =   "UDN :"
         Height          =   375
         Index           =   0
         Left            =   240
         TabIndex        =   2
         Top             =   300
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "friendlyName :"
         Height          =   375
         Index           =   1
         Left            =   240
         TabIndex        =   4
         Top             =   840
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "deviceType :"
         Height          =   375
         Index           =   2
         Left            =   240
         TabIndex        =   6
         Top             =   1400
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "presentationURL :"
         Height          =   375
         Index           =   3
         Left            =   240
         TabIndex        =   8
         Top             =   1950
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "manufacturer :"
         Height          =   375
         Index           =   4
         Left            =   240
         TabIndex        =   10
         Top             =   2500
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "manufacturerURL :"
         Height          =   375
         Index           =   5
         Left            =   240
         TabIndex        =   12
         Top             =   3050
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "modelName :"
         Height          =   375
         Index           =   6
         Left            =   240
         TabIndex        =   14
         Top             =   3600
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "modelNumber :"
         Height          =   375
         Index           =   7
         Left            =   240
         TabIndex        =   16
         Top             =   4150
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "modelDescription :"
         Height          =   375
         Index           =   8
         Left            =   240
         TabIndex        =   18
         Top             =   4700
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "modelURL :"
         Height          =   375
         Index           =   9
         Left            =   240
         TabIndex        =   20
         Top             =   5250
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "UPC :"
         Height          =   375
         Index           =   10
         Left            =   240
         TabIndex        =   22
         Top             =   5800
         Width           =   1605
      End
      Begin VB.Label labelDev 
         Caption         =   "serialNumber :"
         Height          =   375
         Index           =   11
         Left            =   240
         TabIndex        =   24
         Top             =   6360
         Width           =   1605
      End
   End
   Begin VB.CommandButton cmdOk 
      Caption         =   "Ok"
      Height          =   495
      Left            =   4200
      TabIndex        =   26
      Top             =   7680
      Width           =   1095
   End
   Begin VB.Label labelDeviceProperties 
      Alignment       =   2  'Center
      Caption         =   "Device Properties"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3240
      TabIndex        =   0
      Top             =   120
      Width           =   3375
   End
End
Attribute VB_Name = "devProperties"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'--------------------------------------------------------------------------
'
'  Copyright (C) Microsoft Corporation. All rights reserved.
'
'--------------------------------------------------------------------------
' This is a simple form which displays the properties of the device when loaded
' This assumes that the g_currentDevice in the DeviceControl form is already loaded


'+--------------------------------------------------------------------------------------------------
'
'  Function : cmdOk_Click
'
'  Purpose : To close the dialog
'
'  Arguments:
'
'  Return:
'
'  Note:
'
'
Private Sub cmdOk_Click()
Unload Me
End Sub


'+--------------------------------------------------------------------------------------------------
'
'  Function : Form_Load
'
'  Purpose : To initialize the various text boxes with the properties of the device
'
'  Arguments:
'
'  Return:
'
'  Note:
'
'

' Simply copies the properties of the g_currentDevice in the DeviceControl to the appropriate fields
Public Sub Form_Load()
' This form just loads up the value of the device and displays the properties
txtUDN.Text = g_currentDevice.UniqueDeviceName
txtFriendlyName.Text = g_currentDevice.FriendlyName
txtDeviceType.Text = g_currentDevice.Type
txtPresentationURL.Text = g_currentDevice.PresentationURL
txtManufacturer.Text = g_currentDevice.ManufacturerName
txtManufacturerURL.Text = g_currentDevice.ManufacturerURL
txtModelName.Text = g_currentDevice.ModelName
txtModelNumber.Text = g_currentDevice.ModelNumber
txtModelDescription.Text = g_currentDevice.Description
txtModelURL.Text = g_currentDevice.ModelURL
txtUPC.Text = g_currentDevice.UPC
txtSerialNumber.Text = g_currentDevice.SerialNumber
' Attach to tooltip too
txtUDN.ToolTipText = g_currentDevice.UniqueDeviceName
txtFriendlyName.ToolTipText = g_currentDevice.FriendlyName
txtDeviceType.ToolTipText = g_currentDevice.Type
txtPresentationURL.ToolTipText = g_currentDevice.PresentationURL
txtManufacturer.ToolTipText = g_currentDevice.ManufacturerName
txtManufacturerURL.ToolTipText = g_currentDevice.ManufacturerURL
txtModelName.ToolTipText = g_currentDevice.ModelName
txtModelNumber.ToolTipText = g_currentDevice.ModelNumber
txtModelDescription.ToolTipText = g_currentDevice.Description
txtModelURL.ToolTipText = g_currentDevice.ModelURL
txtUPC.ToolTipText = g_currentDevice.UPC
txtSerialNumber.ToolTipText = g_currentDevice.SerialNumber
End Sub

