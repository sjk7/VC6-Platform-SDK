VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   450
   ClientLeft      =   6600
   ClientTop       =   6045
   ClientWidth     =   3495
   LinkTopic       =   "Form1"
   ScaleHeight     =   450
   ScaleWidth      =   3495
   Begin VB.TextBox Text1 
      Height          =   3255
      Left            =   0
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   0
      Width           =   4695
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
'+==========================================================================
'  File:    Form1.frm
'  Summary: Simple demo of non-blocking method calls in Visual Basic
'
'-----------------------------------------------------------------------------
'
'This file is part of the Microsoft COM+ Samples.
'
'Copyright (C) 1995-1998 Microsoft Corporation. All rights reserved.
'
'This source code is intended only as a supplement to Microsoft
'Development Tools and/or on-line documentation. See these other
'materials for detailed information regarding Microsoft code samples.
'
'THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
'KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
'IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
'PARTICULAR PURPOSE.
'
'==========================================================================+*/

'Define struct to hold the async IID
Private Type GUID
    Data1 As Long
    Data2 As Integer
    Data3 As Integer
    Data4(7) As Byte
End Type

'Text form of the async IID
Private Const szIID_AsyncIFullServ As String = "{D3140113-D43F-4718-9119-EF62D631F2AB}"
Private Declare Function CLSIDFromString Lib "OLE32" (ByVal lpszCLSID As Long, pclsid As GUID) As Long

'Helper dll functions
Private Declare Function GetCallObject Lib "..\Release\x86\HelpDll" Alias "_GetCallObject@20" (ByVal pCf As ICallFactory, riid1 As GUID, ByVal pUnkOuter As Long, riid2 As GUID, ppv As Object) As Long
Private Declare Function WaitCallObject Lib "..\Release\x86\HelpDll" Alias "_WaitCallObject@8" (ByVal pSync As ISynchronize, ByVal dwMilli As Long) As Long

Private IID_AsyncIFullServ As GUID
Private hr As Long
Private i As Long
Private pICallFactory As ICallFactory
Private pISynchronize As ISynchronize
Private pAsyncIFullServ As AsyncFullServ
Private pFullServ As FullServ

Private Sub Form_Load()

'Get the async IID for use in CreateCall
hr = CLSIDFromString(StrPtr(szIID_AsyncIFullServ), IID_AsyncIFullServ)
If hr <> 0 Then Err.Raise hr

'Create the server
Set pFullServ = CreateObject("FullSvr.FullServ")

'QueryInterface for ICallFactory
Set pICallFactory = pFullServ

'Call CreateCall through helper dll
hr = GetCallObject(pICallFactory, IID_AsyncIFullServ, 0, IID_AsyncIFullServ, pAsyncIFullServ)

If hr <> 0 Then Err.Raise hr

'QueryInterface for ISynchronize
Set pISynchronize = pAsyncIFullServ

'Begin the call
Call pAsyncIFullServ.Begin_Sum(2, 3)
If hr <> 0 Then Err.Raise hr

Text1.Text = "Waiting for call completion"

'Call wait through helper dll
hr = WaitCallObject(pISynchronize, -1)
If hr <> 0 Then Err.Raise hr

'Finish the call
i = pAsyncIFullServ.Finish_Sum()

Text1.Text = "Sum of 2 and 3 is: " + Str(i)

End Sub
