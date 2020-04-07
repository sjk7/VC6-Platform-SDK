VERSION 5.00
Begin VB.Form Monitor 
   Caption         =   "Queued Components - Monitor"
   ClientHeight    =   4416
   ClientLeft      =   48
   ClientTop       =   348
   ClientWidth     =   5652
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4416
   ScaleWidth      =   5652
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton NotifyStart 
      Caption         =   "Start"
      Height          =   252
      Left            =   600
      TabIndex        =   9
      Top             =   3360
      Width           =   492
   End
   Begin VB.CommandButton ShipStart 
      Caption         =   "Start"
      Height          =   252
      Left            =   3840
      TabIndex        =   8
      Top             =   1440
      Width           =   492
   End
   Begin VB.CommandButton ShipStop 
      Caption         =   "Stop"
      Height          =   252
      Left            =   4680
      TabIndex        =   1
      Top             =   1440
      Width           =   492
   End
   Begin VB.CommandButton NotifyStop 
      Caption         =   "Stop"
      Height          =   252
      Left            =   1440
      TabIndex        =   0
      Top             =   3360
      Width           =   492
   End
   Begin VB.Label Label1 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      Caption         =   "Timings are artificially lengthened for visibility"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   10.2
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   468
      TabIndex        =   7
      Top             =   3960
      Width           =   4836
   End
   Begin VB.Line Line6 
      X1              =   2160
      X2              =   2280
      Y1              =   2640
      Y2              =   2400
   End
   Begin VB.Line Line5 
      X1              =   2160
      X2              =   2400
      Y1              =   2640
      Y2              =   2520
   End
   Begin VB.Line Line4 
      X1              =   3600
      X2              =   3480
      Y1              =   720
      Y2              =   600
   End
   Begin VB.Line Line3 
      X1              =   3600
      X2              =   3480
      Y1              =   720
      Y2              =   840
   End
   Begin VB.Label lblOrderShip 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      Caption         =   "Idle"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   10.2
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   2616
      TabIndex        =   6
      Top             =   360
      Width           =   420
   End
   Begin VB.Label lblShipNotify 
      AutoSize        =   -1  'True
      Caption         =   "Idle"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   10.2
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   3000
      TabIndex        =   5
      Top             =   2040
      Width           =   420
   End
   Begin VB.Line Line2 
      X1              =   3600
      X2              =   2160
      Y1              =   960
      Y2              =   2640
   End
   Begin VB.Line Line1 
      X1              =   2160
      X2              =   3600
      Y1              =   720
      Y2              =   720
   End
   Begin VB.Label lblNotify 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H000000FF&
      Caption         =   "Notify"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   792
      TabIndex        =   4
      Top             =   2520
      Width           =   828
   End
   Begin VB.Label LblShip 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H000000FF&
      Caption         =   "Ship"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   4200
      TabIndex        =   3
      Top             =   600
      Width           =   612
   End
   Begin VB.Label LblOrder 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H000000FF&
      Caption         =   "Order"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   876
      TabIndex        =   2
      Top             =   600
      Width           =   780
   End
   Begin VB.Shape ShapeNotify 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   1092
      Left            =   360
      Top             =   2160
      Width           =   1812
   End
   Begin VB.Shape ShapeShip 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   1092
      Left            =   3600
      Top             =   240
      Width           =   1812
   End
   Begin VB.Shape ShapeOrder 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   1092
      Left            =   360
      Top             =   240
      Width           =   1812
   End
End
Attribute VB_Name = "Monitor"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Rem ==========================================================================
Rem
Rem This file is part of the Microsoft COM+ Samples.
Rem
Rem Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.
Rem
Rem This source code is intended only as a supplement to Microsoft
Rem Development Tools and/or on-line documentation. See these other
Rem materials for detailed information regarding Microsoft code samples.
Rem
Rem THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
Rem KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
Rem IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
Rem PARTICULAR PURPOSE.
Rem
Rem ==========================================================================

Private Sub Form_Load()
'
' Clear the labels on arrows to component boxes
'
    Monitor.lblOrderShip.Caption = ""
    Monitor.lblShipNotify.Caption = ""
End Sub

Private Sub NotifyStart_Click()
'
' Start the Notify component
'
  Dim cat As COMAdminCatalog
  
  Set cat = CreateObject("COMAdmin.COMAdminCatalog.1")
  cat.StartApplication "QCNotify"
  
End Sub

Private Sub NotifyStop_Click()
'
' Stop the Notify component
'
  Dim cat As COMAdminCatalog
  
  Set cat = CreateObject("COMAdmin.COMAdminCatalog.1")
  cat.ShutdownApplication "QCNotify"
  
End Sub

Private Sub ShipStart_Click()
'
' Start the Ship component
'
  Dim cat As COMAdminCatalog
  
  Set cat = CreateObject("COMAdmin.COMAdminCatalog.1")
  cat.StartApplication "QCShip"
  
End Sub

Private Sub ShipStop_Click()
'
' Stop the Ship component
'
  Dim cat As COMAdminCatalog
  
  Set cat = CreateObject("COMAdmin.COMAdminCatalog.1")
  cat.ShutdownApplication "QCShip"
  
End Sub
